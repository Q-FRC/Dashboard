#include "models/TabWidgetsModel.h"
#include <QJsonArray>
#include <QJsonObject>
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
    case PROPERTIES:
        return w.properties;
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
        case TYPE:
            w.type = value.toString();
            break;
        case TOPIC:
            w.topic = value.toString();
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
        case PROPERTIES:
            w.properties = value.toMap();
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

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

void TabWidgetsModel::add(Widget w)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_data << w;
    endInsertRows();

    emit unoccupiedCellsChanged();
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

void TabWidgetsModel::setEqualTo(TabWidgetsModel *w)
{
    beginResetModel();
    m_data.clear();
    endResetModel();

    beginInsertRows(QModelIndex(), 0, w->data().count() - 1);
    m_data << w->data();
    endInsertRows();

    m_rows = w->rows();
    m_cols = w->cols();
}

QList<Widget> TabWidgetsModel::data()
{
    return m_data;
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
    qDebug() << cols() << col + colSpan;
    if (col + colSpan > cols() || row + rowSpan > rows()) return true;

    for (const Widget &w : m_data) {
        QRect dataRect = QRect(w.col, w.row, w.colSpan, w.rowSpan);

        if (dataRect.intersects(ignore.toRect())) {
            continue;
        }

        if (dataRect.intersects(itemRect)) {
            qDebug() << dataRect << itemRect;
            return true;
        }
    }

    qDebug() << "NOPE!" << itemRect;

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
    rez[PROPERTIES] = "properties";

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

QJsonArray TabWidgetsModel::saveObject() const
{
    QJsonArray arr;

    for (const Widget &w : m_data) {
        QJsonObject obj;
        obj.insert("title", w.title);
        obj.insert("topic", w.topic);
        obj.insert("type", w.type);
        obj.insert("column", w.col);
        obj.insert("row", w.row);
        obj.insert("rowSpan", w.rowSpan);
        obj.insert("colSpan", w.colSpan);

        QJsonObject prop;

        QMapIterator iter(w.properties);

        while (iter.hasNext()) {
            iter.next();
            prop.insert(iter.key(), iter.value().toJsonValue());
        }

        obj.insert("properties", prop);

        arr.append(obj);
    }

    return arr;
}

TabWidgetsModel *TabWidgetsModel::loadObject(QObject *parent, const QJsonArray &arr)
{
    TabWidgetsModel *model = new TabWidgetsModel(parent);

    for (const QJsonValueConstRef ref : arr) {
        QJsonObject obj = ref.toObject();

        Widget w;
        w.title = obj.value("title").toString("");
        w.topic = obj.value("topic").toString("");
        w.type = obj.value("type").toString("");
        w.col = obj.value("column").toInt(0);
        w.row = obj.value("row").toInt(0);
        w.rowSpan= obj.value("rowSpan").toInt(0);
        w.colSpan = obj.value("colSpan").toInt(0);

        QJsonObject properties = obj.value("properties").toObject();

        QVariantMap props;
        for (const QString &key : properties.keys()) {
            props.insert(key, properties.value(key));
        }

        w.properties = props;

        model->add(w);
    }

    return model;
}
