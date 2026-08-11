// SPDX-FileCopyrightText: Copyright 2026 crueter
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "wpi/nt/NetworkTableEntry.hpp"
#include "wpi/nt/NetworkTableInstance.hpp"
#include "wpi/nt/NetworkTableValue.hpp"

#include <QHash>
#include <QJSValue>
#include <QMultiHash>
#include <QObject>
#include <QQmlEngine>

class StructStore;
class Logger;

class Listener : public QObject {
    Q_OBJECT

public:
    Listener(QQmlEngine *engine, wpi::nt::NetworkTableInstance instance, StructStore *structStore,
             QString topic, QObject *parent);

    QString topic() const;

    /**
     * @brief addListener Add a subscriber to this listener.
     * @param func The function to call for this subscriber.
     */
    void addListener(const QJSValue &func);

    /**
     * @brief rmListener Remove a subscriber from this listener.
     * @param func The function to remove from the listener.
     * @return Whether or not the function was removed.
     */
    bool rmListener(const QJSValue &func);

    /**
     * @brief empty Check if this listener is empty.
     * @return Whether or not this listener has no associated functions.
     */
    bool empty();

    /**
     * @brief updateEvent Update this listener's subscribers from the provided event data.
     * @param event The NetworkTables event associated with this update.
     *   Set to a blank event or omit to automatically fetch the data from NT.
     */
    Q_INVOKABLE void updateEvent(const wpi::nt::Event &event = wpi::nt::Event());

    /**
     * @brief update Update all subscribers with the provided value.
     */
    void update(const QVariant &value);

    /**
     * @brief unpublish Unpublish this listener's associated NT entry,
     *  and remove the underlying handle.
     */
    void unpublish();

    /**
     * @brief setValue Set the value of this listener's associated NT entry.
     * @param value The value to publish to NetworkTables.
     */
    void setValue(const QVariant &value);

    /**
     * @brief getValue Get the value of this listener's associated NT entry.
     * @return The value retrieved from NetworkTables.
     */
    QVariant getValue();

private:
    QString m_topic = {};
    NT_Listener m_handle = 0;
    wpi::nt::ListenerCallback m_callback = wpi::nt::ListenerCallback();
    QList<QJSValue> m_funcs = {};
    wpi::nt::NetworkTableEntry m_entry = wpi::nt::NetworkTableEntry{};

    QQmlEngine *m_engine = nullptr;
    wpi::nt::NetworkTableInstance m_instance;
    StructStore *m_structStore;

    QVariant decodeValue(const wpi::nt::Value &ntValue);

    bool operator==(const Listener &other) const;
};

class TopicStore : public QObject {
    Q_OBJECT
private:
    Q_INVOKABLE Listener *entry(const QString &topic);

    QHash<QString, Listener *> m_listeners;

    Logger *m_logs;
    QQmlEngine *m_engine;
    wpi::nt::NetworkTableInstance m_instance;
    StructStore *m_structStore;

public:
    static QVariant toVariant(const wpi::nt::Value &value);
    static wpi::nt::Value toValue(const QVariant &value);

    TopicStore(QQmlEngine *engine, Logger *logs, QObject *parent = nullptr);

    wpi::nt::NetworkTableEntry getRawEntry(const std::string_view &path);
    std::vector<wpi::nt::ConnectionInfo> getConnections() const;
    StructStore *structStore() const;

    void setServer(const std::string &server);
    void setServerTeam(const int team);
    void startDSClient();
    void disconnectServer();

    // The QJSValue is the function this subscription is connected to
    // So each subscription's unique ID is just the function itself.
    Q_INVOKABLE void subscribe(const QString &ntTopic, const QJSValue &func);
    Q_INVOKABLE void unsubscribe(const QString &ntTopic, const QJSValue &func);

    Q_INVOKABLE void subscribeOneShot(const QString &ntTopic,
                                      std::function<void(QVariant)> callback);

    Q_INVOKABLE QVariant getValue(const QString &topic);
    Q_INVOKABLE void setValue(const QString &topic, const QVariant &value);

    Q_INVOKABLE void forceUpdate(const QString &topic);

    QString typeString(const QString &topic);
signals:
    void connected(const QString remoteIP);
    void disconnected();
    void connectedStateChanged(bool connectedState);

    void topicPublished(const std::string &topicName);
    void topicUnpublished(const std::string &topicName);
};
