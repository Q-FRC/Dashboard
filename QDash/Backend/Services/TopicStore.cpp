// SPDX-FileCopyrightText: Copyright 2026 crueter
// SPDX-License-Identifier: GPL-3.0-or-later

#include "BuildConfig/BuildConfig.h"
#include "Services/Logger.h"
#include "Services/StructStore.h"
#include "Services/TopicStore.h"
#include "wpi/nt/NetworkTableType.hpp"

TopicStore::TopicStore(QQmlEngine *engine, Logger *logs, QObject *parent)
    : QObject(parent), m_logs(logs), m_engine(engine),
      m_instance{wpi::nt::NetworkTableInstance::GetDefault()},
      m_structStore{new StructStore(m_instance, m_logs)}
{
    m_instance.StartClient(BuildConfig.APPLICATION_NAME.toStdString());

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

bool Listener::operator==(const Listener &other) const
{
    return (other.topic() == m_topic);
}

Listener::Listener(QQmlEngine *engine, wpi::nt::NetworkTableInstance instance,
                   StructStore *structStore, QString topic, QObject *parent)
    : QObject(parent), m_topic(topic), m_engine(engine), m_instance{instance},
      m_structStore(structStore)
{
    m_topic = topic;
    m_entry = m_instance.GetEntry(topic.toStdString());

    // bind callback and handle
    m_callback = [this](const wpi::nt::Event &event) {
        const auto data = event.GetValueEventData();
        const auto ntValue = data ? data->value : m_entry.GetValue();

        const auto raw = ntValue.GetRaw();

        // queue invocation so it gets passed to QSG
        // must decode stuff here as well because structStore isn't thread-safe
        QMetaObject::invokeMethod(
            this,
            [this, raw, ntValue]() {
                QVariant value = decodeValue(ntValue);
                update(value);
            },
            Qt::QueuedConnection);
    };

    // always re-fire on struct schemas
    if (m_entry.GetTopic().GetTypeString().starts_with("struct:")) {
        connect(m_structStore, &StructStore::schemaAdded, this,
                [this](const QString &typeName) { m_callback(wpi::nt::Event()); });
    }

    m_handle = m_instance.AddListener(m_entry, wpi::nt::EventFlags::VALUE_ALL, m_callback);
}

QString Listener::topic() const
{
    return m_topic;
}

void Listener::addListener(const QJSValue &func)
{
    m_funcs.emplaceBack(func);

    updateEvent();
}

bool Listener::rmListener(const QJSValue &func)
{
    // QJSValue lacks an operator== :(
    for (qsizetype i = 0; i < m_funcs.size(); ++i) {
        const QJSValue &f = m_funcs.at(i);
        if (f.strictlyEquals(func)) {
            m_funcs.removeAt(i);
            return true;
        }
    }

    return false;
}

bool Listener::empty()
{
    return m_funcs.empty();
}

void Listener::updateEvent(const wpi::nt::Event &event)
{
    QVariant value;
    if (!event.Is(wpi::nt::EventFlags::VALUE_ALL))
        value = getValue();
    else // TODO(crueter): Evaluate perf
        value = TopicStore::toVariant(event.GetValueEventData()->value);

    update(value);
}

void Listener::update(const QVariant &value)
{
    if (value.isNull() || !value.isValid())
        return;

    for (const QJSValue &func : std::as_const(m_funcs)) {
        func.call({m_engine->toScriptValue(value)});
    }
}

void Listener::unpublish()
{
    m_entry.Unpublish();
    m_instance.RemoveListener(m_handle);
}

void Listener::setValue(const QVariant &value)
{
    m_entry.SetValue(TopicStore::toValue(value));
}

QVariant Listener::getValue()
{
    return TopicStore::toVariant(m_entry.GetValue());
}

QVariant Listener::decodeValue(const wpi::nt::Value &ntValue)
{
    const auto typeString = m_entry.GetTopic().GetTypeString();
    if (typeString.starts_with("struct:")) {
        return m_structStore->decode(typeString, ntValue.GetRaw());
    }
    return TopicStore::toVariant(ntValue);
}

void TopicStore::subscribe(const QString &topic, const QJSValue &func)
{
    if (topic == "")
        return;

    Listener *listener = entry(topic);

    if (!listener) {
        // TODO: fmt
        m_logs->debug("TopicStore", "Creating new listener for topic " + topic);

        listener = new Listener(m_engine, m_instance, m_structStore, topic, this);
        m_listeners.insert(topic, listener);
    }

    listener->addListener(func);

    m_logs->debug("TopicStore", "Subscribed to topic " + topic);
}

void TopicStore::unsubscribe(const QString &topic, const QJSValue &func)
{
    Listener *l = entry(topic);
    if (!l)
        return;

    l->rmListener(func);

    if (l->empty()) {
        m_logs->debug("TopicStore", "Destructing listener for topic " + topic);
        l->unpublish();
        m_listeners.remove(topic);
        l->deleteLater();
    }

    m_logs->debug("TopicStore", "Unsubscribed from topic " + topic);
}

void TopicStore::subscribeOneShot(const QString &topic, std::function<void(QVariant)> callback)
{
    if (topic.isEmpty() || !callback)
        return;

    wpi::nt::NetworkTableEntry entry = m_instance.GetEntry(topic.toStdString());
    "string";

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

QVariant TopicStore::getValue(const QString &topic)
{
    Listener *l = entry(topic);
    if (l)
        return l->getValue();

    return QVariant{};
}

void TopicStore::setValue(const QString &topic, const QVariant &value)
{
    Listener *l = entry(topic);
    if (l)
        l->setValue(value);
}

void TopicStore::forceUpdate(const QString &topic)
{
    m_logs->debug("TopicStore", "Force-updating topic " + topic);

    Listener *l = entry(topic);
    if (l)
        l->updateEvent();
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

Listener *TopicStore::entry(const QString &topic)
{
    return m_listeners.value(topic, nullptr);
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
