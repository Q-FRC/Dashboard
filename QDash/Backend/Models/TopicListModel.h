// SPDX-FileCopyrightText: Copyright 2026 crueter
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <QStandardItemModel>
#include <ankerl/unordered_dense.h>

#include "Services/StructStore.h"

class TopicStore;

class TopicListModel : public QStandardItemModel {
    Q_OBJECT

public:
    enum TLMRoleTypes { NAME = Qt::UserRole, TYPE, TOPIC, DISPLAY_TYPE };

    TopicListModel(TopicStore *store, QObject *parent = nullptr);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Q_INVOKABLE void reload();

    void add(const QString &toAdd);
    void remove(const QString &toRemove);

private:
    QStringList m_data;
    TopicStore *m_store;

    // struct helpers
    void addStructChildren(QStandardItem *parent, const QString &topicPath,
                           const QString &typeString);
    void populateStructChildren(QStandardItem *parent, const QString &topicPath,
                                const QList<StructNode> &tree);

    void addArrayListener(QStandardItem *parent, const std::string &topicPath,
                          const std::string &typeString);
    void repopulateArray(const QString &topicPath, const std::string &elementType,
                         const std::string &typeString, const wpi::nt::Value &value);

    void populateArrayChildren(QStandardItem *parent, const QString &topicPrefix,
                               const QString &type, qsizetype len, const QList<StructNode> &tree);
    QStandardItem *makeArrayChild(const QString &topicPrefix, qsizetype i, const QString &type,
                                  const QList<StructNode> &tree);

    // used to track paths
    QHash<QString, QStandardItem *> m_items;

    // per-topic struct connections for structs awaiting their schema
    ankerl::unordered_dense::map<std::string, QMetaObject::Connection> m_schemaListeners;

    // struct array elements awaiting their schema
    struct ArraySchemaPending {
        std::string typeString;
        std::string elementType;
        std::vector<uint8_t> lastValue;
    };

    // element type -> topic -> pending array data
    QHash<QString, QHash<QString, ArraySchemaPending>> m_arraySchemaPending;
};
