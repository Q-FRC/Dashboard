// SPDX-FileCopyrightText: Copyright 2026 crueter
// SPDX-License-Identifier: GPL-3.0-or-later

#include "BuildConfig/BuildConfig.h"
#include "Services/Logger.h"
#include "Services/QtNTInterface.h"
#include "Services/StructManager.h"
#include "Services/StructStore.h"
#include "Services/TopicStore.h"
#include "wpi/nt/GenericEntry.hpp"
#include "wpi/nt/NetworkTableEntry.hpp"
#include "wpi/nt/NetworkTableType.hpp"
#include "wpi/nt/NetworkTableValue.hpp"

TopicStore::TopicStore(QQmlEngine *engine, Logger *logs, QObject *parent)
    : QObject(parent), m_logs(logs), m_engine(engine),
      m_instance{wpi::nt::NetworkTableInstance::GetDefault()},
      m_structStore{new StructStore(m_instance, m_logs)},
      m_structs{new StructManager(m_instance, m_structStore, m_logs, this)}
{
    m_instance.StartClient(BuildConfig.APPLICATION_NAME.toStdString());

    // Pending Structs //
    connect(
        m_structs, &StructManager::structValueReady, this,
        [this](const std::string &topic, const QVariant &value) { callConsumers(topic, value); });

    // Values //
    const auto callback = [this](const wpi::nt::Event &event) {
        const auto data = event.GetValueEventData();
        if (!data)
            return;

        const auto topic = wpi::nt::GetTopicName(data->topic);

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
            this, [this, topic, typeString, value] { handleValue(topic, typeString, value); });
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

void TopicStore::handleValue(const std::string &topic, const std::string &typeString,
                             const wpi::nt::Value &value)
{
    const auto result = m_structs->process(topic, typeString, value);
    switch (result) {
    case StructManager::Handled:
    case StructManager::Pending:
        // the structValueReady listener will handle these
        break;
    case StructManager::Plain:
        callConsumers(topic, QtNTInterface::toVariant(value));
        break;
    }
}

void TopicStore::callConsumers(const std::string &topic, const QVariant &value)
{
    const auto it = m_subscriptions.find(topic);
    if (it == m_subscriptions.end())
        return;
    const auto list = it->second;

    for (const Subscription &sub : std::as_const(it->second)) {
        // if this is a subfield, grab it from the struct
        const QVariant v = sub.path.isEmpty() ? value : m_structs->getField(value, sub.path);
        sub.func.call({m_engine->toScriptValue(v)});
    }
}

// called from QML
void TopicStore::subscribe(const QString &topic, const QJSValue &func)
{
    if (topic == "")
        return;

    // add subscription
    const auto resolved = m_structs->resolve(topic);
    const Subscription newSub(topic, resolved.path, func);
    m_subscriptions[resolved.source.toStdString()].append(newSub);

    // log
    if (resolved.path.isEmpty()) {
        m_logs->debug("TopicStore", QStringLiteral("Subscribed to topic %1").arg(topic));
    } else {
        m_logs->debug("TopicStore",
                      QStringLiteral("Subscribed to pseudo-topic %1, with struct parent %2")
                          .arg(topic, resolved.source));
    }

    std::lock_guard lock(m_subMutex);
    m_subscribed.insert(resolved.source.toStdString());
}

// called when the NT topology changes
// attempt to re-resolve subscriptions that may now have a struct parent
void TopicStore::reconcile()
{
    // Rebuild into a fresh map
    decltype(m_subscriptions) migrated;

    for (const auto &[oldSource, list] : m_subscriptions) {
        for (const Subscription &sub : list) {
            const auto re = m_structs->resolve(sub.rawTopic);

            Subscription updated = sub;
            updated.path = re.path;
            migrated[re.source.toStdString()].append(updated);
        }
    }

    m_subscriptions = std::move(migrated);

    // keep the value-listener filter in sync with the (possibly migrated) sources
    std::lock_guard lock(m_subMutex);
    for (const auto &[source, subs] : m_subscriptions)
        if (!subs.isEmpty())
            m_subscribed.insert(source);
}

void TopicStore::unsubscribe(const QString &topic, const QJSValue &func)
{
    const auto source = m_structs->resolve(topic).source.toStdString();

    auto it = m_subscriptions.find(source);
    if (it == m_subscriptions.end())
        return;

    // remove the function
    auto &list = it->second;
    for (qsizetype i = 0; i < list.size(); ++i) {
        if (list.at(i).func.strictlyEquals(func)) {
            list.removeAt(i);
            break;
        }
    }

    // if other subscribers remain, we are done
    if (!list.isEmpty())
        return;

    // this is the last remaining subscription, so drop it
    const auto toDrop = it->first;
    m_subscriptions.erase(it);
    m_structs->drop(toDrop);

    std::lock_guard lock(m_subMutex);
    m_subscribed.erase(source);

    m_logs->debug("TopicStore", "Unsubscribed from topic " + topic);
}

void TopicStore::subscribeOneShot(const QString &topic, std::function<void(QVariant)> callback)
{
    if (topic.isEmpty() || !callback)
        return;

    wpi::nt::Topic ntTopic = m_instance.GetTopic(topic.toStdString());

    // The lambda needs to reference its own handle in order to destruct it.
    // Shared pointer is used because otherwise you get weird thread contention stuff,
    // and also we can't just delete an integer.
    auto handle = std::make_shared<NT_Listener>(0);

    auto ntCallback = [this, callback, handle](const wpi::nt::Event &event) mutable {
        const auto data = event.GetValueEventData();
        if (!data)
            return;

        QVariant value = QtNTInterface::toVariant(data->value);
        QMetaObject::invokeMethod(this, [callback, value] { callback(value); });

        m_instance.RemoveListener(*handle);
    };

    *handle = m_instance.AddListener(ntTopic, wpi::nt::EventFlags::VALUE_ALL, ntCallback);

    m_logs->debug("TopicStore", "One-shot subscription requested to topic " + topic);
}

void TopicStore::setValue(const QString &topic, const QVariant &value)
{
    // structs are handled by StructManager
    if (!m_structs->publish(topic.toStdString(), value))
        m_instance.GetEntry(topic.toStdString()).SetValue(QtNTInterface::toValue(value));
}

void TopicStore::forceUpdate(const QString &topic)
{
    m_logs->debug("TopicStore", "Force-updating topic " + topic);

    const auto source = m_structs->resolve(topic).source.toStdString();
    const auto entry = m_instance.GetEntry(source);
    handleValue(source, entry.GetTopic().GetTypeString(), entry.GetValue());
}

QString TopicStore::typeString(const QString &topic)
{
    const auto ntTopic = m_instance.GetTopic(topic.toStdString());
    const auto type = ntTopic.GetType();

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
    default:
        return QString::fromStdString(ntTopic.GetTypeString());
    }
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
