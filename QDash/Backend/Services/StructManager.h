// SPDX-FileCopyrightText: Copyright 2026 crueter
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <QObject>
#include <ankerl/unordered_dense.h>
#include "wpi/nt/GenericEntry.hpp"
#include "wpi/nt/NetworkTableInstance.hpp"

class StructStore;
class Logger;

// The general interface between structs and NetworkTables
class StructManager : public QObject {
    Q_OBJECT
public:
    explicit StructManager(wpi::nt::NetworkTableInstance instance, StructStore *store,
                           Logger *logger, QObject *parent = nullptr);

    enum Result {
        Handled, // decoded
        Pending, // waiting for schema
        Plain,   // this is not a struct
    };

    // {source, path}
    // the subscribed topic and remaining path
    struct Resolved {
        QString source;
        QStringList path;
    };

    // topic -> {struct I/A, remaining path}
    Resolved resolve(const std::string &topic);
    Resolved resolve(const QString &topic);

    // feed a value event for a struct source topic
    Result process(const std::string &topic, const std::string &typeString,
                   const wpi::nt::Value &value);

    // write a struct or subfield to NT
    // returns false if topic isn't a struct
    bool publish(const std::string &topic, const QVariant &value);

    // forget a topic entirely
    void drop(const std::string &topic);

    // struct modifiers
    QVariant getField(const QVariant &value, const QStringList &path);
    QVariant setField(QVariant value, const QStringList &path, const QVariant &toSet);

private:
    QString structParent(const QString &topic) const;
    void writeStruct(const std::string &typeString, const std::string &topic,
                     const QVariant &value);

    wpi::nt::NetworkTableInstance m_instance;
    StructStore *m_store;
    Logger *m_logger;

    // publisher cache
    ankerl::unordered_dense::map<std::string, wpi::nt::GenericEntry> m_publishers;

    // structs that are still awaiting their schemas
    typedef struct PendingStruct {
        std::string typeName;
        wpi::nt::Value value;
    } PendingStruct;

    ankerl::unordered_dense::map<std::string, PendingStruct> m_pending;

    // helper for array index parsing
    static std::optional<int> parseArrayIndex(const QString &index, const size_t max);
signals:
    void structValueReady(const std::string &topic, const QVariant &value);
};
