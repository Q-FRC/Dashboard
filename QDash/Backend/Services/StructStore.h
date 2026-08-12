// SPDX-FileCopyrightText: Copyright 2026 crueter
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <string_view>
#include <QObject>
#include "Services/Logger.h"
#include "wpi/nt/NetworkTableInstance.hpp"
#include "wpi/util/struct/DynamicStruct.hpp"

typedef struct StructNode {
    QString name;
    QString type;
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

    QVariant decode(const std::string_view typeString, std::span<const uint8_t> data);
    QList<StructNode> schemaTree(const std::string_view typeString);

private:
    wpi::util::StructDescriptorDatabase m_database;
    wpi::nt::NetworkTableInstance m_instance;
    Logger *m_logger;

    // decode helpers
    QVariant decodeStruct(const wpi::util::StructDescriptor *desc, std::span<const uint8_t> data);
    QVariant decodeField(const wpi::util::StructFieldDescriptor *field,
                         std::span<const uint8_t> data);

    // schema tree helpers
    QList<StructNode> fieldTree(const wpi::util::StructDescriptor *desc);
    StructNode fieldNode(const wpi::util::StructFieldDescriptor *field);
    QString fieldTypeString(const wpi::util::StructFieldDescriptor *field);

signals:
    void schemaAdded(QString typeName);
};
