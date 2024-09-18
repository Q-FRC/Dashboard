#include "TabListModel.h"
#include "Globals.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonObject>

void reconnectServer() {
    std::string server = Globals::server.server;
    bool isTeamNumber = Globals::server.teamNumber;
    int port = Globals::server.port;
    // QString switchTopic = Globals::server.switchTopic;

    if (server.empty()) return;

    if (isTeamNumber) {
        int team;
        try {
            team = std::stoi(server);
        } catch (std::invalid_argument const &) {
            return;
        }

        Globals::inst.SetServerTeam(team, port);
    } else {
        Globals::inst.SetServer(server.c_str(), port);
    }

    Globals::inst.Disconnect();

    // QString serverTopic = Globals::server.switchTopic;

    // Globals::server = data;

    // if (serverTopic != switchTopic) {
    //     emit switchTopicChanged();
    // }
}

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
    case ROWS:
        return t.rows;
    case COLS:
        return t.cols;
    case WIDGETS:
        return QVariant::fromValue(t.model);
    default:
        break;
    }

    return QVariant();
}

bool TabListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        Tab &t = m_data[index.row()];
        switch (role) {
        case TITLE:
            t.title = value.toString();
        case ROWS:
            t.rows = value.toInt();
        case COLS:
            t.cols = value.toInt();
        case WIDGETS:
            t.model = value.value<TabWidgetsModel *>();
        default:
            break;
        }
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

Qt::ItemFlags TabListModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

void TabListModel::add(Tab t)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_data << t;
    endInsertRows();
}

void TabListModel::add(QString title)
{
    static char i = 0;
    Tab t;
    t.title = title;
    t.rows = 3;
    t.cols = 5;

    t.model = nullptr;

    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_data << t;
    endInsertRows();
}

bool TabListModel::remove(int row, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row);
    m_data.remove(row);
    endRemoveRows();

    return true;
}

void TabListModel::save(const QString &filename) const
{
    QString name = filename;
    name.replace("file://", "");
    QFile file(name);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << ":(";
        return;
    }

    // addRecentFile(file);
    // refreshRecentFiles();

    QTextStream stream(&file);
    stream << saveObject().toJson();
    file.close();
}

QJsonDocument TabListModel::saveObject() const
{
    QJsonObject doc;
    doc.insert("useTeamNumber", useTeam());
    doc.insert("port", getPort());
    doc.insert("ip", ip());

    QJsonArray arr;

    for (const Tab &t : m_data) {
        QJsonObject obj;

        obj.insert("title", t.title);
        obj.insert("rows", t.rows);
        obj.insert("cols", t.cols);
        obj.insert("widgets", t.model->saveObject());

        arr.append(obj);
    }

    doc.insert("tabs", arr);

    return QJsonDocument(doc);
}

void TabListModel::loadObject(const QJsonDocument &doc)
{
    QJsonObject ob = doc.object();

    Globals::server.server = ob.value("ip").toString().toStdString();
    Globals::server.port = ob.value("port").toInt();
    Globals::server.teamNumber = ob.value("useTeamNumber").toBool();

    reconnectServer();

    QJsonArray arr = ob.value("tabs").toArray();

    for (const QJsonValueRef ref : arr) {
        QJsonObject obj = ref.toObject();

        Tab t;

        t.title = obj.value("title").toString();
        t.rows = obj.value("rows").toInt();
        t.cols = obj.value("cols").toInt();
        t.model = TabWidgetsModel::loadObject(this, obj.value("widgets").toArray());

        add(t);
    }
}

void TabListModel::load(const QString &filename)
{
    QString name = filename;
    name.replace("file://", "");

    QFile file(name);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    // addRecentFile(file);
    // refreshRecentFiles();

    QTextStream stream(&file);
    QByteArray data = stream.readAll().toUtf8();

    QJsonDocument doc = QJsonDocument::fromJson(data);

    loadObject(doc);
    file.close();
}

QHash<int, QByteArray> TabListModel::roleNames() const
{
    QHash<int,QByteArray> rez;
    rez[TITLE] = "title";
    rez[ROWS] = "rows";
    rez[COLS] = "cols";
    rez[WIDGETS] = "widgets";

    return rez;
}

int TabListModel::getPort() const
{
    return Globals::server.port;
}

void TabListModel::setPort(int newPort)
{
    Globals::server.port = newPort;
    emit portChanged();
    reconnectServer();
}

QString TabListModel::ip() const
{
    return QString::fromStdString(Globals::server.server);
}

void TabListModel::setIp(const QString &newIp)
{
    Globals::server.server = newIp.toStdString();
    emit ipChanged();
    reconnectServer();
}

bool TabListModel::useTeam() const
{
    return Globals::server.teamNumber;
}

void TabListModel::setUseTeam(bool newUseTeam)
{
    Globals::server.teamNumber = newUseTeam;
    emit useTeamChanged();
    reconnectServer();
}
