#include "TabListModel.h"

TabListModel::TabListModel(QObject *parent)
    : QAbstractListModel(parent)
{}

int TabListModel::rowCount(const QModelIndex &parent) const
{
    return m_data.count();
}

QVariant TabListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    Tab t = m_data[index.row()];

    switch (role) {
    case TITLE:
        return t.title;
    default:
        break;
    }

    return QVariant();
}

bool TabListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        // FIXME: Implement me!
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

Qt::ItemFlags TabListModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable; // FIXME: Implement me!
}

void TabListModel::add(QString title)
{
    static char i = 0;
    Tab t;
    t.title = title;

    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_data << t;
    endInsertRows();
    }

bool TabListModel::remove(int row, int column, const QModelIndex &parent)
{
    return false;
}

QHash<int, QByteArray> TabListModel::roleNames() const
{
    QHash<int,QByteArray> rez;
    rez[TITLE] = "title";

    return rez;
}
