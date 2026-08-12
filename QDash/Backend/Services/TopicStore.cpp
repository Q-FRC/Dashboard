// SPDX-FileCopyrightText: Copyright 2026 crueter
// SPDX-License-Identifier: GPL-3.0-or-later

#include "BuildConfig/BuildConfig.h"
#include "Services/Logger.h"
#include "Services/StructStore.h"
#include "Services/TopicStore.h"
#include "wpi/nt/GenericEntry.hpp"
#include "wpi/nt/NetworkTableEntry.hpp"
#include "wpi/nt/NetworkTableType.hpp"
#include "wpi/nt/NetworkTableValue.hpp"

TopicStore::TopicStore(QQmlEngine *engine, Logger *logs, QObject *parent)
    : QObject(parent), m_logs(logs), m_engine(engine),
      m_instance{wpi::nt::NetworkTableInstance::GetDefault()},
      m_structStore{new StructStore(m_instance, m_logs)}
{
    m_instance.StartClient(BuildConfig.APPLICATION_NAME.toStdString());

    // Pending Structs //
    connect(m_structStore, &StructStore::schemaAdded, this, [this](const QString &typeName) {
        QHashIterator iter(m_pendingStructs);
        while (iter.hasNext()) {
            iter.next();
            const auto topic = iter.key();
            const auto pending = iter.value();

            // try to decode the struct again
            dispatch(topic, pending.typeName, pending.value);
        }
    });

    // Values //
    const auto callback = [this](const wpi::nt::Event &event) {
        const auto data = event.GetValueEventData();
        if (!data)
            return;

        const auto topic = QString::fromStdString(wpi::nt::GetTopicName(data->topic));

        bool subscribed = false;
        {
            std::lock_guard lock(m_subMutex);
            subscribed = m_subscribed.contains(topic);
        }
        if (!subscribed)
            return;

        const std::string typeString = wpi::nt::GetTopicTypeString(data->topic);
        const auto value = data->value;

        QMetaObject::invokeMethod(
            this, [this, topic, typeString, value] { dispatch(topic, typeString, value); });
    };

    m_instance.AddListener({{""}}, wpi::nt::EventFlags::VALUE_ALL, callback);

    // Connections //
    m_instance.AddConnectionListener(true, [this](const wpi::nt::Event &event) {
        bool connected = event.Is(wpi::nt::EventFlags::CONNECTED);
        QString remoteIP = QString::fromStdString(event.GetConnectionInfo()->remote_ip);

        QMetaObject::invokeMethod(this, [this, remoteIP, connected] {
            emit connectedStateChanged(connected);

            if (connected) {
                m_logs->info("NT", "Client connected to " + remoteIP);
                emit this->connected(remoteIP);
            } else {
                m_logs->info("NT", "Client disconnected");
                emit this->disconnected();
            }
        });
    });

    // Topic Publishes //
    m_instance.AddListener({{""}}, wpi::nt::EventFlags::PUBLISH,
                           [this](const wpi::nt::Event &event) {
                               std::string topicName(event.GetTopicInfo()->name);
                               QMetaObject::invokeMethod(this, [this, topicName]() {
                                   m_logs->debug("NT", "Received topic announcement for " +
                                                           QString::fromStdString(topicName));
                                   emit topicPublished(topicName);
                               });
                           });

    // Topic Unpublishes //
    m_instance.AddListener({{""}}, wpi::nt::EventFlags::UNPUBLISH,
                           [this](const wpi::nt::Event &event) {
                               std::string topicName(event.GetTopicInfo()->name);
                               QMetaObject::invokeMethod(this, [this, topicName]() {
                                   m_logs->debug("NT", "Received topic unpublish event for " +
                                                           QString::fromStdString(topicName));
                                   emit topicUnpublished(topicName);
                               });
                           });
}

QVariant TopicStore::decodeValue(const std::string &typeString, const wpi::nt::Value &ntValue)
{
    if (typeString.starts_with("struct:")) {
        return m_structStore->decode(typeString, ntValue.GetRaw());
    }
    return toVariant(ntValue);
}

void TopicStore::dispatch(const QString &topic, const std::string &typeString,
                          const wpi::nt::Value &value)
{
    auto queueSchema = [this, topic, typeString, value]() {
        // struct whose schema hasn't arrived yet
        if (typeString.starts_with("struct:")) {
            m_pendingStructs.insert(topic, {std::string{typeString}, value});
        }
    };

    auto call = [this, topic](const QString &effectiveTopic, const QVariant &value) {
        const auto funcs = m_consumers.value(effectiveTopic);
        const auto arg = m_engine->toScriptValue(value);
        for (const QJSValue &func : funcs) {
            func.call({arg});
        }
    };

    // pseudotopic handling
    if (m_pseudoTopics.contains(topic)) {
        const QVariant decoded = decodeValue(typeString, value);

        // TODO: dedup these pathways
        if (decoded.isNull() || !decoded.isValid()) {
            queueSchema();
            return;
        }

        m_pendingStructs.remove(topic);

        const std::function<QVariant(const QVariantMap, const QStringList)> walk =
            [this, &walk](const QVariantMap &map, const QStringList &path) -> QVariant {
            QString key = path.first();
            QVariant value = map[key];

            if (path.size() > 1) {
                if (value.typeId() == QMetaType::Type::QVariantMap) {
                    return walk(value.toMap(), path.mid(1));
                }
                // TODO: Handle lists here.
            }

            return value;
        };

        // now go through all pseudotopics...
        for (const PseudoTopic &t : m_pseudoTopics.values(topic)) {
            // and walk through the struct
            const auto path = t.path.split('/');
            const auto value = walk(decoded.toMap(), path);

            // then call the update func
            call(QStringLiteral("%1/%2").arg(topic, t.path), value);
        }
    }

    // topic was unsubscribed since the event was queued
    if (!m_consumers.contains(topic))
        return;

    const QVariant decoded = decodeValue(typeString, value);
    if (decoded.isNull() || !decoded.isValid()) {
        queueSchema();
        return;
    }

    // remove from queue, if applicable
    m_pendingStructs.remove(topic);

    call(topic, decoded);
}

QString TopicStore::structParent(const QString &topic)
{
    const auto segments = topic.split('/');
    int n = segments.size() - 1;
    for (; n > 0; --n) {
        const auto parent = segments.sliced(0, n).join('/');
        const auto parentType = m_instance.GetTopic(parent.toStdString()).GetTypeString();

        if (StructStore::isStruct(parentType)) {
            return parent;
        }
    }

    return {};
}

void TopicStore::subscribe(const QString &topic, const QJSValue &func)
{
    if (topic == "")
        return;

    m_consumers[topic].append(func);

    const auto structParent = this->structParent(topic);
    if (structParent.isEmpty()) {
        m_logs->debug("TopicStore", "Subscribed to topic " + topic);

        std::lock_guard lock(m_subMutex);
        m_subscribed.insert(topic);
        return;
    }

    PseudoTopic pseudoTopic{
        .path = topic.last(topic.length() - structParent.length() - 1),
        .func = func,
    };

    m_logs->debug("TopicStore",
                  QStringLiteral("Subscribed to pseudo-topic %1, with struct parent %2")
                      .arg(topic, structParent));

    m_pseudoTopics.insert(structParent, pseudoTopic);
    std::lock_guard lock(m_subMutex);
    m_subscribed.insert(structParent);
}

void TopicStore::unsubscribe(const QString &topic, const QJSValue &func)
{
    auto it = m_consumers.find(topic);
    if (it == m_consumers.end())
        return;

    for (qsizetype i = 0; i < it->size(); ++i)
        if (it->at(i).strictlyEquals(func)) {
            it->removeAt(i);
            break;
        }

    const bool lastConsumer = it->isEmpty();
    if (lastConsumer) {
        m_consumers.erase(it);
        m_pendingStructs.remove(topic);
        std::lock_guard lock(m_subMutex);
        m_subscribed.remove(topic);
    }

    // drop this subscription's pseudotopic entry
    for (auto iter = m_pseudoTopics.begin(); iter != m_pseudoTopics.end();) {
        if (iter.value().func.strictlyEquals(func))
            iter = m_pseudoTopics.erase(iter);
        else
            ++iter;
    }

    // nothing subscribes to the struct anymore
    if (lastConsumer) {
        const auto parent = structParent(topic);
        const QString parentTopic = parent.isEmpty() ? topic : parent;
        if (StructStore::isStruct(m_instance.GetTopic(parentTopic.toStdString()).GetTypeString()) &&
            !m_consumers.contains(parentTopic) && !m_pseudoTopics.contains(parentTopic)) {
            m_structPublishers.erase(parentTopic);
            m_pendingStructs.remove(parentTopic);
            std::lock_guard lock(m_subMutex);
            m_subscribed.remove(parentTopic);
        }
    }

    m_logs->debug("TopicStore", "Unsubscribed from topic " + topic);
}

void TopicStore::subscribeOneShot(const QString &topic, std::function<void(QVariant)> callback)
{
    if (topic.isEmpty() || !callback)
        return;

    wpi::nt::NetworkTableEntry entry = m_instance.GetEntry(topic.toStdString());

    // The lambda needs to reference its own handle in order to destruct it.
    // Shared pointer is used because otherwise you get weird thread contention stuff,
    // and also we can't just delete an integer.
    auto handle = std::make_shared<NT_Listener>(0);

    auto ntCallback = [callback, handle, entry, this](const wpi::nt::Event &event) mutable {
        QVariant value = toVariant(event.GetValueEventData()->value);
        callback(value);

        entry.Unpublish();
        m_instance.RemoveListener(*handle);
    };

    *handle = m_instance.AddListener(entry, wpi::nt::EventFlags::VALUE_ALL, ntCallback);

    m_logs->debug("TopicStore", "One-shot subscription requested to topic " + topic);
}

void TopicStore::setValue(const QString &topic, const QVariant &value)
{
    // write struct to nt
    const auto writeStruct = [this](const std::string &typeString, const QString &topic,
                                    const QVariant &value) {
        const auto data = m_structStore->encode(typeString, value);

        // cache struct publishers, if applicable
        if (!m_structPublishers.contains(topic)) {
            m_structPublishers.emplace(
                topic, wpi::nt::GenericEntry(
                           m_instance.GetTopic(topic.toStdString()).GetGenericEntry(typeString)));
        }

        m_structPublishers[topic].SetRaw(data);
    };

    const auto strTopic = topic.toStdString();
    const auto topicType = m_instance.GetTopic(strTopic).GetTypeString();

    // direct struct write
    if (StructStore::isStruct(topicType)) {
        return writeStruct(topicType, topic, value);
    }

    // regular field
    const auto structParent = this->structParent(topic);
    if (structParent.isEmpty()) {
        m_instance.GetEntry(strTopic).SetValue(toValue(value));
        return;
    }

    // struct subfield
    const std::function<QVariant(const QVariantMap, const QStringList, const QVariant)> walk =
        [this, &walk](const QVariantMap &map, const QStringList &path,
                      const QVariant &newValue) -> QVariant {
        QVariantMap mutableMap = map;

        QString key = path.first();
        QVariant value = map[key];

        if (path.size() > 1) {
            if (value.typeId() == QMetaType::Type::QVariantMap) {
                mutableMap[key] = walk(value.toMap(), path.mid(1), newValue);
            }
            // TODO: Handle lists here.
        } else {
            mutableMap[key] = newValue;
        }

        return mutableMap;
    };

    const auto path = topic.mid(structParent.size()).split('/', Qt::SkipEmptyParts);

    // get existing struct data
    const auto parentEntry = m_instance.GetEntry(structParent.toStdString());
    const auto parentTypeStr = parentEntry.GetTopic().GetTypeString();
    const auto rawData = parentEntry.GetRaw({});
    const auto decoded = m_structStore->decode(parentTypeStr, rawData).toMap();

    QVariant newValue = walk(decoded, path, value);
    writeStruct(parentTypeStr, structParent, newValue);
}

void TopicStore::forceUpdate(const QString &topic)
{
    m_logs->debug("TopicStore", "Force-updating topic " + topic);

    // check for struct parents...
    const auto structParent = this->structParent(topic);

    QString name;
    if (structParent.isEmpty()) {
        if (!m_consumers.contains(topic))
            return;

        name = topic;
    } else {
        name = structParent;
    }

    const auto entry = m_instance.GetEntry(name.toStdString());
    dispatch(name, entry.GetTopic().GetTypeString(), entry.GetValue());
}

QString TopicStore::typeString(const QString &topic)
{
    wpi::nt::NetworkTableEntry entry = m_instance.GetEntry(topic.toStdString());
    wpi::nt::NetworkTableType type = entry.GetType();

    switch (type) {
    case wpi::nt::NetworkTableType::BOOLEAN:
        return "bool";
    case wpi::nt::NetworkTableType::DOUBLE:
        return "double";
    case wpi::nt::NetworkTableType::FLOAT:
        return "double";
    case wpi::nt::NetworkTableType::STRING:
        return "string";
    case wpi::nt::NetworkTableType::INTEGER:
        return "int";
    case wpi::nt::NetworkTableType::RAW:
        return QString::fromStdString(entry.GetTopic().GetTypeString());
    // case wpi::nt::NetworkTableType::kBooleanArray:
    //     return "reef";
    // case wpi::nt::NetworkTableType::kStringArray:
    //     return "errors";
    default:
        return "";
    }
}

QVariant TopicStore::toVariant(const wpi::nt::Value &value)
{
    QVariant v;

    if (!value.IsValid())
        return v;

    if (value.IsBoolean())
        v = value.GetBoolean();
    else if (value.IsString())
        v = QString::fromStdString(std::string(value.GetString()));
    else if (value.IsDouble())
        v = value.GetDouble();
    else if (value.IsFloat())
        v = value.GetFloat();
    else if (value.IsInteger())
        v = QVariant::fromValue(value.GetInteger());

    else if (value.IsBooleanArray()) {
        const std::span<const int> a = value.GetBooleanArray();
        QList<int> newList;
        newList.reserve(a.size());
        for (const int i : a)
            newList << i;

        v = QVariant::fromValue(newList);
    } else if (value.IsStringArray()) {
        const std::span<const std::string> a = value.GetStringArray();
        QStringList newList;
        newList.reserve(a.size());
        for (const std::string &s : a)
            newList << QString::fromStdString(s);

        v = QVariant::fromValue(newList);
    } else if (value.IsDoubleArray()) {
        const std::span<const double> a = value.GetDoubleArray();
        QList<double> newList;
        newList.reserve(a.size());
        for (const double d : a)
            newList << d;

        v = QVariant::fromValue(newList);
    } else if (value.IsIntegerArray()) {
        const std::span<const int64_t> a = value.GetIntegerArray();
        QList<int64_t> newList;
        newList.reserve(a.size());
        for (const int64_t i : a)
            newList << i;

        v = QVariant::fromValue(newList);
    } else if (value.IsRaw()) {
        const std::span<const uint8_t> a = value.GetRaw();
        QString newStr;
        newStr.reserve(a.size());
        for (const uint8_t i : a) {
            newStr = newStr % QChar(i);
        }
        v = newStr;
    }

    return v;
}

wpi::nt::Value TopicStore::toValue(const QVariant &value)
{
    if (!value.isValid())
        goto end;

    switch (value.typeId()) {
    case QMetaType::Type::QString:
        return wpi::nt::Value::MakeString(std::string_view{value.toString().toStdString()});
    case QMetaType::Type::Bool:
        return wpi::nt::Value::MakeBoolean(value.toBool());
    case QMetaType::Type::Double:
        return wpi::nt::Value::MakeDouble(value.toDouble());
    case QMetaType::Type::Float:
        return wpi::nt::Value::MakeFloat(value.toFloat());
    case QMetaType::Type::Int:
        return wpi::nt::Value::MakeInteger(value.toInt());
    case QMetaType::Type::QStringList: {
        std::vector<std::string> v;
        for (const QString &s : value.toStringList()) {
            v.emplace_back(s.toStdString());
        }

        return wpi::nt::Value::MakeStringArray(v);
    }
    default:
        break;
    }

    if (value.typeId() == qMetaTypeId<QList<bool>>()) {
        std::vector<int> v;
        for (const QVariant &b : value.toList()) {
            v.emplace_back(b.toBool());
        }

        return wpi::nt::Value::MakeBooleanArray(v);
    }

end:
    return wpi::nt::Value();
}

StructStore *TopicStore::structStore() const
{
    return m_structStore;
}

// NT Interface //
wpi::nt::NetworkTableEntry TopicStore::getRawEntry(const std::string_view &path)
{
    return m_instance.GetEntry(path);
}

std::vector<wpi::nt::ConnectionInfo> TopicStore::getConnections() const
{
    return m_instance.GetConnections();
}

void TopicStore::setServer(const std::string &server)
{
    m_instance.SetServer(server.c_str());
}

void TopicStore::setServerTeam(const int team)
{
    m_instance.SetServerTeam(QString::number(team).toStdString());
}

void TopicStore::startDSClient()
{
    m_instance.StartDSClient();
}

void TopicStore::disconnectServer()
{
    m_instance.Disconnect();
}
