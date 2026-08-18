// SPDX-FileCopyrightText: Copyright 2026 crueter
// SPDX-License-Identifier: GPL-3.0-or-later

#include <optional>
#include "Services/EntryStore.h"
#include "Services/StructStore.h"
#include "StructManager.h"

StructManager::StructManager(wpi::nt::NetworkTableInstance &instance, StructStore *store,
                             EntryStore *entries, Logger *logger, QObject *parent)
    : QObject{parent}, m_instance(instance), m_store(store), m_entries(entries), m_logger(logger)
{
    // Pending Structs //
    connect(m_store, &StructStore::schemaAdded, this, [this](const QString &typeName) {
        std::vector<std::string> toErase;
        for (const auto &[topic, pending] : m_pending) {
            if (!m_store->isReady(pending.typeName))
                continue;

            const auto decoded = m_store->decode(pending.typeName, pending.value.GetRaw());
            if (decoded.isNull() || !decoded.isValid())
                continue;

            toErase.push_back(topic);
            emit structValueReady(topic, decoded);
        }

        for (const auto &topic : toErase)
            m_pending.erase(topic);
    });
}

StructManager::Resolved StructManager::resolve(const std::string &topic)
{
    return resolve(QString::fromStdString(topic));
}

StructManager::Resolved StructManager::resolve(const QString &topic)
{
    const auto parent = structParent(topic);
    if (parent.isEmpty())
        return {topic, {}};

    const auto path = topic.mid(parent.size()).split('/', Qt::SkipEmptyParts);
    return {parent, path};
}

bool StructManager::publish(const std::string &topic, const QVariant &value)
{
    const auto typeString = m_instance.GetTopic(topic).GetTypeString();
    if (StructStore::isStruct(typeString)) {
        writeStruct(typeString, topic, value);
        return true;
    }

    // subfield
    const auto resolved = resolve(topic);
    const auto source = resolved.source.toStdString();

    // this is a plain topic
    if (resolved.path.isEmpty())
        return false;

    // get parent struct data
    const auto parentTypeStr = m_instance.GetTopic(source).GetTypeString();
    const auto parentValue = m_entries->getValue(source, parentTypeStr);

    // the parent topic hasn't received a value, ignore
    if (!parentValue.IsValid() || !parentValue.IsRaw())
        return true;

    const auto rawData = parentValue.GetRaw();
    const auto decoded = m_store->decode(parentTypeStr, rawData);

    bool empty = true;
    switch (decoded.typeId()) {
    case QMetaType::Type::QVariantMap:
        empty = decoded.toMap().isEmpty();
        break;
    case QMetaType::Type::QVariantList:
        empty = decoded.toList().isEmpty();
        break;
    }

    if (empty) {
        m_logger->debug("StructManager", QStringLiteral("Parent %1 not cached, dropping write op")
                                             .arg(QString::fromStdString(source)));
        return true;
    }

    // and write
    QVariant newValue = setField(decoded, resolved.path, value);
    writeStruct(parentTypeStr, resolved.source.toStdString(), newValue);
    return true;
}

void StructManager::drop(const std::string &topic)
{
    m_pending.erase(topic);
}

StructManager::Result StructManager::process(const std::string &topic,
                                             const std::string &typeString,
                                             const wpi::nt::Value &value)
{
    // this is not a struct
    if (!StructStore::isStruct(typeString))
        return Plain;

    const QVariant decoded = m_store->decode(typeString, value.GetRaw());
    if (decoded.isNull() || !decoded.isValid()) {
        // schema hasn't arrived yet, so enqueue
        PendingStruct pending(typeString, value);
        m_pending.insert_or_assign(topic, pending);

        return Pending;
    }

    // struct is ready
    m_pending.erase(topic);
    emit structValueReady(topic, decoded);
    return Handled;
}

QVariant StructManager::getField(const QVariant &value, const QStringList &path)
{
    if (path.isEmpty())
        return {};

    bool isLeaf = path.size() == 1;
    QString key = path.first();

    // descend or return current value
    const auto returnValue = [this, path, isLeaf](const QVariant &value) {
        return isLeaf ? value : getField(value, path.mid(1));
    };

    switch (value.typeId()) {
    case QMetaType::Type::QVariantMap: {
        const auto map = value.toMap();

        if (!map.contains(key))
            return value;
        return returnValue(map.value(key));
    }

    case QMetaType::Type::QVariantList: {
        const auto list = value.toList();

        // key will just be the index
        auto idx = parseArrayIndex(key, list.size());
        if (!idx.has_value())
            return value;

        return returnValue(list.at(idx.value()));
    }

    default: {
        return value;
    }
    }
}

QVariant StructManager::setField(QVariant value, const QStringList &path, const QVariant &toSet)
{
    if (path.isEmpty())
        return {};

    bool isLeaf = path.size() == 1;
    QString key = path.first();

    const auto updateContainer = [this, isLeaf, path, &toSet](auto &container, const auto &key) {
        // fetch subvalue
        QVariant subvalue;
        if constexpr (std::is_same_v<std::decay_t<decltype(container)>, QVariantMap>) {
            subvalue = container.value(key);
        } else {
            subvalue = container.at(key);
        }

        // store
        if (isLeaf) {
            container[key] = toSet;
        } else {
            container[key] = setField(subvalue, path.mid(1), toSet);
        }
    };

    switch (value.typeId()) {
    case QMetaType::Type::QVariantMap: {
        auto map = value.toMap();
        updateContainer(map, key);
        return map;
    }

    case QMetaType::Type::QVariantList: {
        auto list = value.toList();

        // key will just be the index
        auto idx = parseArrayIndex(key, list.size());
        if (!idx.has_value())
            return value;

        updateContainer(list, idx.value());
        return list;
    }

    default: {
        return value;
    }
    }
}

void StructManager::clear()
{
    m_pending.clear();
}

QString StructManager::structParent(const QString &topic) const
{
    const auto segments = topic.split('/');
    int n = segments.size() - 1;
    for (; n > 0; --n) {
        const auto parent = segments.sliced(0, n).join('/');
        const auto parentType = m_instance.GetTopic(parent.toStdString()).GetTypeString();

        if (StructStore::isStruct(parentType))
            return parent;
    }

    return {};
}

void StructManager::writeStruct(const std::string &typeString, const std::string &topic,
                                const QVariant &value)
{
    const auto data = m_store->encode(typeString, value);
    m_entries->setValue(topic, typeString, wpi::nt::Value::MakeRaw(data));
}

std::optional<int> StructManager::parseArrayIndex(const QString &index, const size_t max)
{
    // key will just be the index
    bool ok = false;
    int idx = index.toInt(&ok);

    // invalid or malformed index
    if (!ok || idx < 0 || idx >= max)
        return std::nullopt;

    return idx;
}
