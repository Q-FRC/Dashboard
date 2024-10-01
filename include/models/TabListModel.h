#ifndef TABLISTMODEL_H
#define TABLISTMODEL_H

#include <QAbstractListModel>
#include <QJsonArray>
#include <QJsonDocument>
#include <qdir.h>
#include <qqmlintegration.h>

#include "TabWidgetsModel.h"

typedef struct {
    QString title;

    int rows;
    int cols;

    TabWidgetsModel *model;
} Tab;

class TabListModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT

public:
    enum TLMRoleTypes {
        TITLE = Qt::UserRole,
        ROWS,
        COLS,
        WIDGETS
    };

    explicit TabListModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    // Add data:
    Q_INVOKABLE void add(Tab t);
    Q_INVOKABLE void add(QString title);

    // Remove data:
    Q_INVOKABLE bool remove(int row, const QModelIndex &parent = QModelIndex());

    Q_INVOKABLE void save(const QString &filename = "");
    Q_INVOKABLE QJsonDocument saveObject() const;
    Q_INVOKABLE void loadObject(const QJsonDocument &doc);
    Q_INVOKABLE void load(const QString &fileName = "");

    bool useTeam() const;
    void setUseTeam(bool newUseTeam);

    QString ip() const;
    void setIp(const QString &newIp);

    int getPort() const;
    void setPort(int newPort);

    QStringList recentFiles() const;
    void setRecentFiles(const QStringList &newRecentFiles);

    bool loadRecent() const;
    void setLoadRecent(bool newLoadRecent);

    void addRecentFile(QFile &file);

signals:
    void useTeamChanged();

    void ipChanged();

    void portChanged();

    void recentFilesChanged();

    void loadRecentChanged();

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<Tab> m_data;

    Q_PROPERTY(bool useTeam READ useTeam WRITE setUseTeam NOTIFY useTeamChanged FINAL)
    Q_PROPERTY(QString ip READ ip WRITE setIp NOTIFY ipChanged FINAL)
    Q_PROPERTY(int port READ getPort WRITE setPort NOTIFY portChanged FINAL)
    Q_PROPERTY(QStringList recentFiles READ recentFiles WRITE setRecentFiles NOTIFY recentFilesChanged FINAL)
    Q_PROPERTY(bool loadRecent READ loadRecent WRITE setLoadRecent NOTIFY loadRecentChanged FINAL)
};
#endif // TABLISTMODEL_H
