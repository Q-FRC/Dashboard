// SPDX-FileCopyrightText: Copyright 2026 crueter
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <QStandardItemModel>

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

    // used to track paths
    QHash<QString, QStandardItem *> m_items;
};
