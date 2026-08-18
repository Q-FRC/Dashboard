// SPDX-FileCopyrightText: Copyright 2026 crueter
// SPDX-License-Identifier: GPL-3.0-or-later

#include "BuildConfig/BuildConfig.h"
#include "Services/Logger.h"
#include "Services/QtNTInterface.h"

#include "Services/EntryStore.h"
#include "Services/StructManager.h"
#include "Services/StructStore.h"
#include "Services/TopicStore.h"

#include "wpi/nt/GenericEntry.hpp"
#include "wpi/nt/NetworkTableType.hpp"
#include "wpi/nt/NetworkTableValue.hpp"
#include "wpi/nt/ntcore_cpp.hpp"

TopicStore::TopicStore(QQmlEngine *engine, Logger *logs, QObject *parent)
    : QObject(parent), m_logs(logs), m_engine(engine),
      m_instance{wpi::nt::NetworkTableInstance::GetDefault()},
      m_structStore{new StructStore(m_instance, m_logs, this)},
      m_entries(new EntryStore(m_instance, this)),
      m_structs{new StructManager(m_instance, m_structStore, m_entries, m_logs, this)}
{
    m_instance.StartClient(BuildConfig.APPLICATION_NAME.toStdString());

    // Reconcile Queue
    m_reconcileTimer.setInterval(50);
    m_reconcileTimer.setSingleShot(true);
    m_reconcileTimer.callOnTimeout(this, &TopicStore::reconcile);

    // Pending Structs //
    connect(
        m_structs, &StructManager::structValueReady, this,
        [this](const std::string &topic, const QVariant &value) { callConsumers(topic, value); });

    // Connections //
    m_instance.AddConnectionListener(true, [this](const wpi::nt::Event &event) {
        bool connected = event.Is(wpi::nt::EventFlags::CONNECTED);
        QString remoteIP = QString::fromStdString(event.GetConnectionInfo()->remote_ip);

        QMetaObject::invokeMethod(this, [this, remoteIP, connected] {
            // reset callbacks before widgets can update anything
            if (connected)
                reconcile();

            emit connectedStateChanged(connected);

            if (connected) {
                m_logs->info("NT", QStringLiteral("Client connected to %1").arg(remoteIP));
                emit this->connected(remoteIP);
            } else {
                m_logs->info("NT", "Client disconnected");

                // clear struct and entry caches
                m_structs->clear();
                m_entries->clear();

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
    // this topic doesn't have a value yet, the callback will deliver it
    if (!value.IsValid())
        return;

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

    // cache path values (i.e. multiple widgets subscribed to the same struct subfield)
    QHash<QString, QVariant> cache;

    for (const Subscription &sub : std::as_const(it->second)) {
        QVariant v;
        if (sub.path.isEmpty()) {
            v = value;
        } else {
            const QString key = sub.rawTopic % "/" % sub.path.join('/');
            const auto hit = cache.constFind(key);
            if (hit != cache.cend()) {
                v = hit.value();
            } else {
                v = m_structs->getField(value, sub.path);
                cache.insert(key, v);
            }
        }

        sub.func.call({m_engine->toScriptValue(v)});
    }
}

void TopicStore::addCallback(const std::string &topic)
{
    // don't listen to unpublished topics
    if (m_instance.GetTopic(topic).GetType() == wpi::nt::NetworkTableType::UNASSIGNED)
        return;

    // now add callback
    m_entries->addCallback(topic, [this, topic](const wpi::nt::Event &event) {
        const auto data = event.GetValueEventData();
        if (!data)
            return;

        const std::string typeString = wpi::nt::GetTopicTypeString(data->topic);
        const auto value = data->value;

        QMetaObject::invokeMethod(
            this, [this, topic, typeString, value] { handleValue(topic, typeString, value); });
    });
}

void TopicStore::queueReconcile()
{
    QMetaObject::invokeMethod(&m_reconcileTimer, qOverload<>(&QTimer::start));
}

// called from QML
void TopicStore::subscribe(const QString &topic, const QJSValue &func)
{
    if (topic == "")
        return;

    // add subscription
    const auto resolved = m_structs->resolve(topic);
    const auto source = resolved.source.toStdString();

    const Subscription newSub(topic, resolved.path, func);
    m_subscriptions[source].append(newSub);

    // log
    if (resolved.path.isEmpty()) {
        m_logs->debug("TopicStore", QStringLiteral("Subscribed to topic %1").arg(topic));
    } else {
        m_logs->debug("TopicStore",
                      QStringLiteral("Subscribed to pseudo-topic %1, with struct parent %2")
                          .arg(topic, resolved.source));
    }

    addCallback(source);
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

    // topics that lost all subscribers
    for (const auto &[oldSource, list] : m_subscriptions) {
        if (!migrated.contains(oldSource)) {
            m_entries->removeEntry(oldSource);
        }
    }

    m_subscriptions = std::move(migrated);

    // make callbacks as needed
    for (const auto &[source, subs] : m_subscriptions) {
        if (!subs.isEmpty())
            addCallback(source);
    }
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
    m_entries->removeEntry(toDrop);

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
    const auto source = topic.toStdString();
    if (m_structs->publish(source, value))
        return;

    const auto typeString = m_instance.GetTopic(source).GetTypeString();
    m_entries->setValue(source, typeString, QtNTInterface::toValue(value));
}

void TopicStore::forceUpdate(const QString &topic)
{
    m_logs->debug("TopicStore", "Force-updating topic " + topic);

    const auto source = m_structs->resolve(topic).source.toStdString();
    const auto typeString = m_instance.GetTopic(source).GetTypeString();

    // this topic has not been published yet
    if (typeString.empty())
        return;

    const auto &entry = m_entries->getEntry(source, typeString);
    handleValue(source, typeString, entry.Get());
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

StructManager *TopicStore::structManager() const
{
    return m_structs;
}

EntryStore *TopicStore::entryStore() const
{
    return m_entries;
}

// NT Interface //
wpi::nt::GenericEntry TopicStore::getRawEntry(const std::string_view &path)
{
    return m_instance.GetTopic(path).GetGenericEntry();
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
