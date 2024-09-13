#include "models/TabWidgetsModel.h"
#include <QRect>

TabWidgetsModel::TabWidgetsModel(QObject *parent)
    : QAbstractListModel(parent)
{}

int TabWidgetsModel::rowCount(const QModelIndex &parent) const
{
    return m_data.count();
}

QVariant TabWidgetsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    Widget w = m_data[index.row()];

    switch (role) {
    case TITLE:
        return w.title;
    case TOPIC:
        return w.topic;
    case COL:
        return w.col;
    case ROW:
        return w.row;
    case COLSPAN:
        return w.colSpan;
    case ROWSPAN:
        return w.rowSpan;
    case TYPE:
        return w.type;
    default:
        break;
    }

    return QVariant();
}

bool TabWidgetsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        Widget &w = m_data[index.row()];

        switch (role) {
        case TITLE:
            w.title = value.toString();
            break;
        case COL:
            w.col = value.toInt();
            break;
        case ROW:
            w.row = value.toInt();
            break;
        case COLSPAN:
            w.colSpan = value.toInt();
            break;
        case ROWSPAN:
            w.rowSpan = value.toInt();
            break;
        }
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

Qt::ItemFlags TabWidgetsModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable; // FIXME: Implement me!
}

void TabWidgetsModel::add(QString title, QString topic, QString type)
{
    static char i = 0;
    Widget w;
    w.title = title;
    w.topic = topic;
    w.type = type;
    w.row = i / 3;
    w.col = i % 3;
    ++i;

    w.rowSpan = 1;
    w.colSpan = 1;

    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_data << w;
    endInsertRows();

    emit unoccupiedCellsChanged();
}

bool TabWidgetsModel::remove(int row, int column, const QModelIndex &parent)
{
    for (size_t i = 0; i < rowCount(); ++i) {
        Widget w = m_data[i];
        if ((column >= w.col && column <= w.col + w.colSpan) &&
            (row >= w.row && row <= w.row + w.colSpan)) {

            beginRemoveRows(parent, i, i);
            m_data.remove(i);
            endRemoveRows();

            return true;
        }
    }

    return false;
}

int TabWidgetsModel::rows() const
{
    return m_rows;
}

void TabWidgetsModel::setRows(int newRows)
{
    if (m_rows == newRows)
        return;
    m_rows = newRows;
    emit rowsChanged();
}

int TabWidgetsModel::cols() const
{
    return m_cols;
}

void TabWidgetsModel::setCols(int newCols)
{
    if (m_cols == newCols)
        return;
    m_cols = newCols;
    emit colsChanged();
}

bool TabWidgetsModel::cellOccupied(int row, int col, int rowSpan, int colSpan, QRectF ignore)
{
    QRect itemRect = QRect(col, row, colSpan, rowSpan);
    if (col + colSpan > cols() || row + rowSpan > rows()) return true;

    for (const Widget &w : m_data) {
        QRect dataRect = QRect(w.col, w.row, w.colSpan, w.rowSpan);

        if (dataRect.intersects(ignore.toRect())) {
            continue;
        }

        if (dataRect.intersects(itemRect)) {
            return true;
        }
    }

    return false;
}


QHash<int, QByteArray> TabWidgetsModel::roleNames() const
{
    QHash<int,QByteArray> rez;
    rez[TITLE] = "title";
    rez[TOPIC] = "topic";
    rez[TYPE] = "type";
    rez[COL] = "column";
    rez[ROW] = "row";
    rez[ROWSPAN] = "rowSpan";
    rez[COLSPAN] = "colSpan";

    return rez;
}

int TabWidgetsModel::unoccupiedCells() const
{
    int c = 0;

    for (const Widget &w : m_data) {
        c += w.rowSpan * w.colSpan;
    }

    return c;
}
