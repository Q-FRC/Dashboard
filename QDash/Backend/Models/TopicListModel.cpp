// SPDX-FileCopyrightText: Copyright 2026 crueter
// SPDX-License-Identifier: GPL-3.0-or-later

#include "Services/TopicStore.h"
#include "TopicListModel.h"

TopicListModel::TopicListModel(TopicStore *store, QObject *parent)
    : QStandardItemModel(parent), m_store(store)
{
    QHash<int, QByteArray> rez = QStandardItemModel::roleNames();
    rez.insert(TLMRoleTypes::NAME, "name");
    rez.insert(TLMRoleTypes::TYPE, "type");
    rez.insert(TLMRoleTypes::TOPIC, "topic");

    QStandardItemModel::setItemRoleNames(rez);

    connect(m_store, &TopicStore::topicPublished, this,
            [this](const std::string &topicName) { add(QString::fromStdString(topicName)); });

    // TODO: handle unpublishing
    // topics->remove(QString::fromStdString(topicName));

    connect(m_store, &TopicStore::disconnected, this, [this]() { clear(); });
}

QVariant TopicListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == TLMRoleTypes::NAME) {
        return itemFromIndex(index)->text();
    }

    return QStandardItemModel::data(index, role);
}

void TopicListModel::reload()
{
    fetchMore(QModelIndex());
}

void TopicListModel::add(const QString &fullPath)
{
    if (fullPath.isEmpty() || fullPath == "/")
        return;

    const QStringList segments = fullPath.split('/', Qt::SkipEmptyParts);

    // search for a .type entry, aka sendables (now tunables?)
    QStringList parentSegments = segments;
    parentSegments.removeLast();
    QString parentPath('/' + parentSegments.join('/'));

    wpi::nt::NetworkTableEntry typeEntry =
        m_store->getRawEntry(parentPath.toStdString() + "/.type");
    bool hasTypeEntry = typeEntry.Exists();

    QStandardItem *parentItem = invisibleRootItem();
    QString currentPath;

    for (size_t i = 0; i < segments.size(); ++i) {
        const QString &segment = segments.at(i);
        currentPath += '/' % segment;
        const bool isLast = (i == segments.size() - 1);

        // check if the parent node has already been visited
        // if yes, cool, descend into it
        // if not, the node will be made later
        if (QStandardItem *parent = m_items.value(currentPath, nullptr)) {
            parentItem = parent;
            continue;
        }

        // make node
        QStandardItem *item = new QStandardItem(segment);
        item->setData(currentPath, TOPIC);

        // leaf
        if (isLast) {
            // if .type exists, this is a tunable
            // so reflect that value onto its parent node
            if (hasTypeEntry && segment == ".type") {
                const std::string value = typeEntry.GetString("invalid");
                if (value == "invalid") {
                    // subscribe once to grab the type
                    m_store->subscribeOneShot(
                        fullPath, [this, parentItem, parentPath](const QVariant &value) mutable {
                            // and set the parent node type
                            parentItem->setData(parentPath, TOPIC);
                            parentItem->setData(value.toString(), TYPE);
                        });
                } else {
                    // if type is already determined, awesome
                    parentItem->setData(parentPath, TOPIC);
                    parentItem->setData(QString::fromStdString(value), TYPE);
                }
            }

            // leaf nodes always have data
            // TODO: Separate field that indicates mutability
            item->setData(fullPath, TOPIC);
            item->setData(m_store->typeString(fullPath), TYPE);
        } else {
            // TODO: move this to a separate store
#ifdef QDASH_CAMVIEW
            if (parentItem->text() == "CameraPublisher") {
                item->setData("/CameraPublisher/" + segment, TOPIC);
                item->setData("camera", TYPE);
            } else
#endif
            {
                item->setData("", TYPE);
            }
        }

        parentItem->appendRow(item);
        m_items.insert(currentPath, item);
        parentItem = item;
    }
}

void TopicListModel::remove(const QString &toRemove)
{
    if (toRemove.isEmpty())
        return;

    QStringList split = toRemove.split('/');
    if (split.at(0).isEmpty())
        split.remove(0);

    QStandardItem *parentItem = invisibleRootItem();
    for (const QString &sub : std::as_const(split)) {
        auto results = findItems(sub, Qt::MatchRecursive | Qt::MatchExactly | Qt::MatchWrap);

        if (results.isEmpty())
            return;
        else {
            for (QStandardItem *item : std::as_const(results)) {
                if (item == nullptr)
                    continue;

                if (item->parent() == nullptr || item->parent() == parentItem) {
                    if (!item->hasChildren()) {
                        parentItem->removeRow(item->row());
                        if (!parentItem->hasChildren()) {
                            if (parentItem->parent() == nullptr) {
                                removeRow(parentItem->row());
                            } else {
                                parentItem->parent()->removeRow(parentItem->row());
                            }
                        }
                    }

                    parentItem = item;
                }
            }
        }
    }
}
