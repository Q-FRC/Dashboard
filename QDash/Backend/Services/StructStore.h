// SPDX-FileCopyrightText: Copyright 2026 crueter
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <string_view>
#include <QObject>
#include <ankerl/unordered_dense.h>
#include "Services/Logger.h"
#include "wpi/nt/NetworkTableInstance.hpp"
#include "wpi/util/struct/DynamicStruct.hpp"

typedef struct StructNode {
    QString name;
    QString type;
    QString structType;
    qsizetype arrayLength = 0;
    QList<StructNode> children;
    bool isArray = false;
} StructNode;

class StructStore : public QObject {
    Q_OBJECT
public:
    explicit StructStore(wpi::nt::NetworkTableInstance instance, Logger *logger,
                         QObject *parent = nullptr);

    static bool isStruct(const std::string_view typeString);

    // TODO
    const wpi::util::StructDescriptor *find(QString type);
    const wpi::util::StructDescriptor *find(const std::string_view type);

    // TODO: Make a better decode/encode API
    QVariant decode(const std::string_view typeString, std::span<const uint8_t> data);
    std::vector<uint8_t> encode(const std::string_view typeString, const QVariant &value);

    // get the array length of a struct
    qsizetype arrayLength(const std::string_view typeString, std::span<const uint8_t> data);

    QList<StructNode> schemaTree(const std::string_view typeString);
    QList<StructNode> schemaTree(const QString &typeString);

private:
    wpi::util::StructDescriptorDatabase m_database;
    wpi::nt::NetworkTableInstance m_instance;
    Logger *m_logger;

    // schema cache
    ankerl::unordered_dense::map<std::string, QList<StructNode>> m_treeCache;

    // decode helpers
    QVariant decodeStruct(const wpi::util::StructDescriptor *desc, std::span<const uint8_t> data);
    QVariant decodeField(const wpi::util::StructFieldDescriptor *field,
                         std::span<const uint8_t> data);

    // encode helpers
    bool encodeStruct(const wpi::util::StructDescriptor *desc, const QVariantMap &map,
                      wpi::util::MutableDynamicStruct &ds);
    void encodeField(const wpi::util::StructFieldDescriptor *field, const QVariant &value,
                     wpi::util::MutableDynamicStruct &ds);

    // schema tree helpers
    QList<StructNode> fieldTree(const wpi::util::StructDescriptor *desc);
    StructNode fieldNode(const wpi::util::StructFieldDescriptor *field);
    QString fieldTypeString(const wpi::util::StructFieldDescriptor *field);

signals:
    void schemaAdded(QString typeName);
};
