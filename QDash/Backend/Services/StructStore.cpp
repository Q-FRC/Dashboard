// SPDX-FileCopyrightText: Copyright 2026 crueter
// SPDX-License-Identifier: GPL-3.0-or-later

#include <format>
#include "StructStore.h"
#include "wpi/nt/ntcore_cpp.hpp"
#include "wpi/util/struct/DynamicStruct.hpp"

StructStore::StructStore(wpi::nt::NetworkTableInstance instance, Logger *logger, QObject *parent)
    : QObject{parent}, m_instance(instance), m_logger(logger), m_database()
{
    // schema subscriber
    m_instance.AddListener(
        {{"/.schema"}}, wpi::nt::EventFlags::VALUE_ALL, [this](const wpi::nt::Event &event) {
            const auto *data = event.GetValueEventData();
            if (!data)
                return;

            // validation
            const auto name = wpi::nt::GetTopicName(data->topic);
            if (!name.starts_with("/.schema/struct:"))
                return;
            if (wpi::nt::GetTopicTypeString(data->topic) != "structschema")
                return;

            std::string_view ts(name);
            ts.remove_prefix(9);                      // remove `/.schema/`
            std::string_view typeName = ts.substr(7); // remove `struct:`

            // copy the raw schema bytes; the span is only valid during this callback
            const auto bytes = data->value.GetRaw();
            const std::string schema{reinterpret_cast<const char *>(bytes.data()), bytes.size()};

            // NT callbacks run on a separate thread, so do all Qt/database work on the main thread
            QMetaObject::invokeMethod(
                this,
                [this, typeName = std::string(typeName), schema] {
                    std::string err;
                    m_database.Add(typeName, schema, &err);

                    if (err != "") {
                        m_logger->critical("StructStore", QString::fromStdString(std::format(
                                                              "Failed to parse struct: {}", err)));
                    }

                    m_logger->debug(
                        "StructStore",
                        QStringLiteral("Received struct schema for type %1").arg(typeName));

                    emit schemaAdded(QString::fromStdString(typeName));
                },
                Qt::QueuedConnection);
        });
}

bool StructStore::isStruct(const std::string_view typeString)
{
    return typeString.contains("struct:");
}

const wpi::util::StructDescriptor *StructStore::find(QString type)
{
    return find(type.toStdString());
}

const wpi::util::StructDescriptor *StructStore::find(const std::string_view type)
{
    return m_database.Find(type);
}

QVariant StructStore::decode(const std::string_view typeString, std::span<const uint8_t> data)
{
    if (!isStruct(typeString)) {
        m_logger->critical("StructStore",
                           QStringLiteral("Type string %1 is not a struct")
                               .arg(QString::fromUtf8(typeString.data(), typeString.size())));
        return {};
    }

    // strip struct: prefix
    std::string_view name = typeString.substr(7);

    m_logger->debug("StructStore", QStringLiteral("Decoding struct with type %1").arg(name));

    // if this is an array, decode each object individually
    // using the struct schema of the individual object type (like pose2d[] etc)
    if (name.ends_with("[]")) {
        name.remove_suffix(2);

        const auto *desc = find(name);
        if (desc == nullptr || !desc->IsValid()) {
            m_logger->critical("StructStore",
                               QStringLiteral("Invalid struct descriptor for type %1")
                                   .arg(QString::fromUtf8(name.data(), name.size())));
            return {};
        }

        // decode each element individually into a list
        const size_t elementSize = desc->GetSize();
        QVariantList out;
        out.reserve(data.size() / elementSize);
        for (size_t offset = 0; offset + elementSize <= data.size(); offset += elementSize) {
            out.append(decodeStruct(desc, data.subspan(offset, elementSize)));
        }

        return out;
    }

    // single objects get parsed as-is
    return decodeStruct(find(name), data);
}

QList<StructNode> StructStore::schemaTree(const std::string_view typeString)
{
    if (!isStruct(typeString)) {
        m_logger->critical("StructStore",
                           QStringLiteral("Type string %1 is not a struct")
                               .arg(QString::fromUtf8(typeString.data(), typeString.size())));
        return {};
    }

    // strip struct: prefix
    std::string_view name = typeString.substr(7);

    const auto *desc = find(name);

    if (desc == nullptr || !desc->IsValid())
        return {};

    return fieldTree(desc);
}

QVariant StructStore::decodeStruct(const wpi::util::StructDescriptor *desc,
                                   std::span<const uint8_t> data)
{
    if (desc == nullptr || !desc->IsValid()) {
        m_logger->critical("StructStore", QStringLiteral("Invalid struct descriptor"));
        return {};
    }

    // awesome
    if (data.size() < desc->GetSize()) {
        m_logger->critical("StructStore", QStringLiteral("Struct size mismatch, data=%1, desc=%2")
                                              .arg(data.size(), desc->GetSize()));
        return {};
    }

    // decode each field individually into the map
    QVariantMap out;
    for (const auto &field : desc->GetFields()) {
        const auto name = QString::fromStdString(field.GetName());
        const auto decoded = decodeField(&field, data);

        out.insert(name, decoded);
    }

    return out;
}

QVariant StructStore::decodeField(const wpi::util::StructFieldDescriptor *field,
                                  std::span<const uint8_t> data)
{
    // field offsets are based off of the owning struct
    const wpi::util::DynamicStruct ds(field->GetParent(), data);

    const auto type = field->GetType();

    // "char" is actually a string, and is declared as an array...
    // so we have to skip the array path entirely
    if (type == wpi::util::StructFieldType::CHAR) {
        const std::string_view s = ds.GetStringField(field);
        return QString::fromUtf8(s.data(), s.size());
    }

    // i is the array index. non-arrays can just use 0
    const auto element = [&](size_t i = 0) -> QVariant {
        switch (type) {
        case wpi::util::StructFieldType::BOOL:
            return ds.GetBoolField(field, i);
        case wpi::util::StructFieldType::INT8:
        case wpi::util::StructFieldType::INT16:
        case wpi::util::StructFieldType::INT32:
        case wpi::util::StructFieldType::INT64:
            // C's number types give me aneurysm
            return QVariant(static_cast<qlonglong>(ds.GetIntField(field, i)));
        case wpi::util::StructFieldType::UINT8:
        case wpi::util::StructFieldType::UINT16:
        case wpi::util::StructFieldType::UINT32:
        case wpi::util::StructFieldType::UINT64:
            return QVariant::fromValue<quint64>(static_cast<quint64>(ds.GetUintField(field, i)));
        case wpi::util::StructFieldType::FLOAT:
            return ds.GetFloatField(field, i);
        case wpi::util::StructFieldType::DOUBLE:
            return ds.GetDoubleField(field, i);
        case wpi::util::StructFieldType::STRUCT:
            // recursive structs :)
            return decodeStruct(field->GetStruct(), ds.GetStructField(field, i).GetData());
        default:
            m_logger->critical("StructStore",
                               QStringLiteral("Invalid struct type %1").arg((int) type));
            return {};
        }
    };

    // plain fields
    if (!field->IsArray()) {
        return element();
    }

    // decodde each element
    const size_t size = field->GetArraySize();
    QVariantList list;
    list.reserve(size);
    for (size_t i = 0; i < size; ++i) {
        list.append(element(i));
    }

    return list;
}

QList<StructNode> StructStore::fieldTree(const wpi::util::StructDescriptor *desc)
{
    QList<StructNode> out;
    for (const auto &field : desc->GetFields())
        out.append(fieldNode(&field));
    return out;
}

StructNode StructStore::fieldNode(const wpi::util::StructFieldDescriptor *field)
{
    StructNode node;
    node.name = QString::fromStdString(field->GetName());
    node.type = fieldTypeString(field);
    node.isArray = field->IsArray();
    node.children = field->GetType() == wpi::util::StructFieldType::STRUCT
                        ? fieldTree(field->GetStruct())
                        : QList<StructNode>{};

    return node;
}

QString StructStore::fieldTypeString(const wpi::util::StructFieldDescriptor *field)
{
    const auto type = field->GetType();
    QString base;
    switch (type) {
    case wpi::util::StructFieldType::CHAR:
        base = "char";
        break;
    case wpi::util::StructFieldType::BOOL:
        base = "bool";
        break;
    case wpi::util::StructFieldType::INT8:
    case wpi::util::StructFieldType::INT16:
    case wpi::util::StructFieldType::INT32:
    case wpi::util::StructFieldType::INT64:
    case wpi::util::StructFieldType::UINT8:
    case wpi::util::StructFieldType::UINT16:
    case wpi::util::StructFieldType::UINT32:
    case wpi::util::StructFieldType::UINT64:
        base = "int";
        break;
    case wpi::util::StructFieldType::FLOAT:
    case wpi::util::StructFieldType::DOUBLE:
        base = "double";
        break;
    case wpi::util::StructFieldType::STRUCT:
        base =
            QStringLiteral("struct:%1").arg(QString::fromStdString(field->GetStruct()->GetName()));
        break;
    }

    return field->IsArray() ? QStringLiteral("%1[%2]").arg(base).arg(field->GetArraySize()) : base;
}
