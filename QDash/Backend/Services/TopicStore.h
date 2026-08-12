// SPDX-FileCopyrightText: Copyright 2026 crueter
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <mutex>
#include "wpi/nt/NetworkTableEntry.hpp"
#include "wpi/nt/NetworkTableInstance.hpp"
#include "wpi/nt/NetworkTableValue.hpp"

#include <QHash>
#include <QJSValue>
#include <QObject>
#include <QQmlEngine>
#include <QSet>

class StructStore;
class Logger;

class TopicStore : public QObject {
    Q_OBJECT
private:
    Logger *m_logs;
    QQmlEngine *m_engine;
    wpi::nt::NetworkTableInstance m_instance;
    StructStore *m_structStore;

    QVariant decodeValue(const std::string &typeString, const wpi::nt::Value &ntValue);

    void dispatch(const QString &topic, const std::string &typeString, const wpi::nt::Value &value);

    // get the struct parent of this pseudotopic, if applicable
    QString structParent(const std::string &topic);

    // topics with at least one subscriber
    std::mutex m_subMutex;
    QSet<QString> m_subscribed;

    // {topic, subscriber function}
    QHash<QString, QList<QJSValue>> m_consumers;

    // struct parents
    typedef struct PseudoTopic {
        QString path;
        QJSValue func;
    } PseudoTopic;

    // {parent struct, path + func}
    QMultiHash<QString, PseudoTopic> m_pseudoTopics;

    typedef struct PendingStruct {
        std::string typeName;
        wpi::nt::Value value;
    } PendingStruct;

    QHash<QString, PendingStruct> m_pendingStructs;

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
