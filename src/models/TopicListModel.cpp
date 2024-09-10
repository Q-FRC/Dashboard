#include "TopicListModel.h"

TopicListModel::TopicListModel(QObject *parent)
    : QAbstractListModel(parent)
{}

QVariant TopicListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    switch (section) {
    case 0:
        return "Topic";
    default:
        return "unknown";
    }
}

int TopicListModel::rowCount(const QModelIndex &parent) const
{
    return m_data.count();
}

QVariant TopicListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == TLMRoleTypes::NAME) {
        return m_data.at(index.row());
    } else
        return QVariant();

    return QVariant();
}

void TopicListModel::reload()
{
    fetchMore(QModelIndex());
}

void TopicListModel::add(const QString &toAdd)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_data << toAdd;
    endInsertRows();
}

void TopicListModel::remove(const QString &toRemove)
{
    int idx = m_data.indexOf(toRemove);
    beginRemoveRows(QModelIndex(), idx, idx);
    m_data.remove(idx);
    endRemoveRows();
}

QHash<int, QByteArray> TopicListModel::roleNames() const
{
    QHash<int, QByteArray> rez;
    rez.insert(TLMRoleTypes::NAME, "name");

    return rez;
}
