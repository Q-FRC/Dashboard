// SPDX-FileCopyrightText: Copyright 2026 crueter
// SPDX-License-Identifier: GPL-3.0-or-later

#include "Services/EntryStore.h"
#include "Services/TopicStore.h"
#include "TopicListModel.h"

#include <QRegularExpression>

TopicListModel::TopicListModel(TopicStore *store, QObject *parent)
    : QStandardItemModel(parent), m_store(store)
{
    QHash<int, QByteArray> rez = QStandardItemModel::roleNames();
    rez.insert(TLMRoleTypes::NAME, "name");
    rez.insert(TLMRoleTypes::TYPE, "type");
    rez.insert(TLMRoleTypes::TOPIC, "topic");
    rez.insert(TLMRoleTypes::DISPLAY_TYPE, "displayType");

    QStandardItemModel::setItemRoleNames(rez);

    connect(m_store, &TopicStore::topicPublished, this, [this](const std::string &topicName) {
        // a newly-published topic (e.g. a struct parent gaining its type)
        // may make previously-unresolvable subfield subscriptions resolvable
        m_store->queueReconcile();
        add(QString::fromStdString(topicName));
    });

    // TODO: handle unpublishing
    // topics->remove(QString::fromStdString(topicName));

    connect(m_store, &TopicStore::disconnected, this, [this]() {
        // clear schema listeners
        for (auto &conn : std::as_const(m_schemaListeners))
            QObject::disconnect(conn.second);
        m_schemaListeners.clear();
        m_arraySchemaPending.clear();

        clear();
        m_items.clear();
    });

    // a newly-arrived struct schema may make subfield subscriptions resolvable
    // and may allow struct arrays to populate if they were missing their schema
    connect(m_store->structStore(), &StructStore::schemaAdded, this,
            [this](const QString &typeName) {
                m_store->queueReconcile();

                // retry any arrays that couldn't populate without their schema
                const auto it = m_arraySchemaPending.find(typeName);
                if (it == m_arraySchemaPending.end())
                    return;

                for (auto t = it.value().begin(); t != it.value().end(); ++t) {
                    const QString &topic = t.key();
                    const auto &pending = t.value();

                    if (!m_items.contains(topic))
                        continue;

                    if (pending.lastValue.empty())
                        continue;

                    const auto value = wpi::nt::Value::MakeRaw(pending.lastValue);
                    repopulateArray(topic, pending.elementType, pending.typeString, value);
                }

                m_arraySchemaPending.erase(it);
            });
}

QVariant TopicListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch (role) {
    case NAME:
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
    if (fullPath.isEmpty() || fullPath == "/" || fullPath.startsWith("/.schema"))
        return;

    const QStringList segments = fullPath.split('/', Qt::SkipEmptyParts);

    // search for a .type entry, aka complex types
    QStringList parentSegments = segments;
    parentSegments.removeLast();
    QString parentPath('/' + parentSegments.join('/'));

    wpi::nt::GenericEntry typeEntry = m_store->getRawEntry(parentPath.toStdString() + "/.type");
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
                    m_store->subscribeOneShot(fullPath, [this, parentPath](const QVariant &value) {
                        QStandardItem *parent = m_items.value(parentPath, nullptr);
                        if (!parent)
                            return;

                        // and set the parent node type
                        parent->setData(parentPath, TOPIC);
                        parent->setData(value.toString(), TYPE);
                        parent->setData(value.toString(), DISPLAY_TYPE);
                    });
                } else {
                    // if type is already determined, awesome
                    parentItem->setData(parentPath, TOPIC);
                    parentItem->setData(QString::fromStdString(value), TYPE);
                    parentItem->setData(QString::fromStdString(value), DISPLAY_TYPE);
                }
            }

            // leaf nodes always have data
            // TODO: Separate field that indicates mutability
            item->setData(fullPath, TOPIC);

            const auto type = m_store->typeString(fullPath);
            item->setData(type, DISPLAY_TYPE);

            // telemetry is usually read-only, so use the display types if possible
            if (fullPath.contains("/Telemetry/"))
                item->setData(QStringLiteral("%1Display").arg(type), TYPE);
            else
                item->setData(type, TYPE);

            // struct handler
            if (type.startsWith("struct:"))
                addStructChildren(item, fullPath, type);
        } else {
            // TODO: move this to a separate store
#ifdef QDASH_CAMVIEW
            if (parentItem->text() == "CameraPublisher") {
                item->setData("/CameraPublisher/" + segment, TOPIC);
                item->setData("camera", TYPE);
                item->setData("camera", DISPLAY_TYPE);
            } else
#endif
            {
                item->setData("", TYPE);
                item->setData("", DISPLAY_TYPE);
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

void TopicListModel::addStructChildren(QStandardItem *parent, const QString &topicPath,
                                       const QString &typeString)
{
    // arrays require special handling
    if (typeString.endsWith("[]")) {
        addArrayListener(parent, topicPath.toStdString(), typeString.toStdString());
        return;
    }

    const QList<StructNode> tree = m_store->structStore()->schemaTree(typeString.toStdString());
    if (!tree.isEmpty()) {
        populateStructChildren(parent, topicPath, tree);
        return;
    }

    // the schema has not arrived yet, try to repopulate
    const auto stdTopic = topicPath.toStdString();
    if (const auto it = m_schemaListeners.find(stdTopic); it != m_schemaListeners.end())
        QObject::disconnect(it->second);

    m_schemaListeners[stdTopic] =
        connect(m_store->structStore(), &StructStore::schemaAdded, this,
                [this, typeString, topicPath](const QString &typeName) {
                    QStandardItem *parent = m_items.value(topicPath, nullptr);
                    if (!parent)
                        return;

                    const auto tree = m_store->structStore()->schemaTree(typeString);
                    if (!tree.isEmpty() && parent->rowCount() == 0)
                        populateStructChildren(parent, topicPath, tree);
                });
}

void TopicListModel::populateStructChildren(QStandardItem *parent, const QString &topicPath,
                                            const QList<StructNode> &tree)
{
    for (const StructNode &node : tree) {
        const QString childTopic = topicPath % "/" % node.name;
        auto *child = new QStandardItem(node.name);

        child->setData(childTopic, TOPIC);
        child->setData(node.type, DISPLAY_TYPE);

        // TODO: only apply this to primitives
        child->setData(QStringLiteral("%1Display").arg(node.type), TYPE);

        // TODO: cleanup, do some dedup with the struct array impl
        if (!node.children.isEmpty()) {
            if (node.isArray) {
                populateArrayChildren(child, childTopic, node.structType, node.arrayLength,
                                      node.children);
            } else {
                populateStructChildren(child, childTopic, node.children);
            }
        }

        parent->appendRow(child);
    }
}

// listen for array changes and make children as necessary
void TopicListModel::addArrayListener(QStandardItem *parent, const std::string &topicPath,
                                      const std::string &typeString)
{
    const auto qTopic = QString::fromStdString(topicPath);

    const std::string elementType =
        typeString.ends_with("[]") ? typeString.substr(0, typeString.size() - 2) : typeString;

    // don't overwrite TopicStore subscriptions
    // TODO: maybe hook into TopicStore?
    m_store->entryStore()->addPersistentCallback(
        topicPath, [this, qTopic, elementType, typeString](const wpi::nt::Event &event) {
            const auto data = event.GetValueEventData();
            if (!data)
                return;

            QMetaObject::invokeMethod(this,
                                      [this, qTopic, elementType, typeString, value = data->value] {
                                          repopulateArray(qTopic, elementType, typeString, value);
                                      });
        });

    // the value may have been published before this listener was registered
    QMetaObject::invokeMethod(
        this,
        [this, qTopic, elementType, typeString, topicPath] {
            const auto value = m_store->entryStore()->getEntry(topicPath, typeString).Get();
            if (value.IsValid())
                repopulateArray(qTopic, elementType, typeString, value);
        },
        Qt::QueuedConnection);
}

void TopicListModel::repopulateArray(const QString &topicPath, const std::string &elementType,
                                     const std::string &typeString, const wpi::nt::Value &value)
{
    auto *node = m_items.value(topicPath);
    if (!node)
        return;

    const auto structStore = m_store->structStore();

    const auto len = structStore->arrayLength(typeString, value.GetRaw());
    const auto tree = structStore->schemaTree(elementType);

    // the schema hasn't arrived yet, remember the value and retry when it does
    if (len == 0 && tree.isEmpty()) {
        const auto raw = value.GetRaw();
        const QString typeKey = QString::fromStdString(
            elementType.starts_with("struct:") ? elementType.substr(7) : elementType);

        ArraySchemaPending pending{.typeString = typeString,
                                   .elementType = elementType,
                                   .lastValue = raw | std::ranges::to<std::vector>()};
        m_arraySchemaPending[typeKey][topicPath] = pending;

        return;
    }

    if (len == node->rowCount() && !tree.isEmpty())
        return;

    populateArrayChildren(node, topicPath, QString::fromStdString(elementType), len, tree);
}

QStandardItem *TopicListModel::makeArrayChild(const QString &topicPrefix, qsizetype i,
                                              const QString &type, const QList<StructNode> &tree)
{
    const QString childTopic = arrayChildPath(topicPrefix, i);
    auto *child = new QStandardItem(QStringLiteral("[%1]").arg(i));
    child->setData(childTopic, TOPIC);
    child->setData(type, DISPLAY_TYPE);
    child->setData(type, TYPE);

    if (!tree.isEmpty())
        populateStructChildren(child, childTopic, tree);

    return child;
}

QString TopicListModel::arrayChildPath(const QString &prefix, const qsizetype i)
{
    return QStringLiteral("%1/%2").arg(prefix).arg(i);
}

void TopicListModel::populateArrayChildren(QStandardItem *parent, const QString &topicPrefix,
                                           const QString &type, qsizetype len,
                                           const QList<StructNode> &tree)
{
    // only account for changes to array length
    const auto cur = parent->rowCount();

    if (len < cur) {
        parent->removeRows(len, cur - len);
        for (qsizetype i = len; i < cur; ++i)
            m_items.remove(arrayChildPath(topicPrefix, i));
        return;
    }

    for (qsizetype i = cur; i < len; ++i) {
        auto *child = makeArrayChild(topicPrefix, i, type, tree);
        parent->appendRow(child);
        m_items.insert(arrayChildPath(topicPrefix, i), child);
    }
}
