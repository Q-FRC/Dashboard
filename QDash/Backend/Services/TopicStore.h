// SPDX-FileCopyrightText: Copyright 2026 crueter
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "wpi/nt/GenericEntry.hpp"
#include "wpi/nt/NetworkTableInstance.hpp"
#include "wpi/nt/NetworkTableValue.hpp"

#include <QJSValue>
#include <QObject>
#include <QQmlEngine>
#include <QTimer>
#include <ankerl/unordered_dense.h>

class EntryStore;
class StructManager;
class StructStore;
class Logger;

class TopicStore : public QObject {
    Q_OBJECT
private:
    Logger *m_logs;
    QQmlEngine *m_engine;
    wpi::nt::NetworkTableInstance m_instance;

    StructStore *m_structStore;
    EntryStore *m_entries;
    StructManager *m_structs;

    // reconcile queue
    QTimer m_reconcileTimer;

    // Subscriptions //

    // represents a subscription (either to a topic or a struct child)
    struct Subscription {
        QString rawTopic; // the original topic the caller asked for
        QStringList path; // the struct child path, if applicable
        QJSValue func;
    };

    ankerl::unordered_dense::map<std::string, QList<Subscription>> m_subscriptions;

    // private iface //

    // Dispatch struct resolution to the queue, or call functions
    void handleValue(const std::string &topic, const std::string &typeString,
                     const wpi::nt::Value &value);
    void callConsumers(const std::string &topic, const QVariant &value);

    // {re-,}make the callback
    void addCallback(const std::string &topic);

public slots:
    // queue structure reconciliation
    void queueReconcile();

private slots:
    // re-resolve all subscriptions against the current structure
    void reconcile();

public:
    TopicStore(QQmlEngine *engine, Logger *logs, QObject *parent = nullptr);

    wpi::nt::GenericEntry getRawEntry(const std::string_view &path);
    std::vector<wpi::nt::ConnectionInfo> getConnections() const;

    StructStore *structStore() const;
    StructManager *structManager() const;
    EntryStore *entryStore() const;

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
