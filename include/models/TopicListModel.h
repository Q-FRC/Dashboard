#ifndef TOPICLISTMODEL_H
#define TOPICLISTMODEL_H

#include <QAbstractListModel>
#include <qqmlintegration.h>

class TopicListModel : public QAbstractListModel
{
    QML_ELEMENT
    Q_OBJECT

public:
    enum TLMRoleTypes {
        NAME = Qt::UserRole,
    };

    TopicListModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section,
                        Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Q_INVOKABLE void reload();

    void add(const QString &toAdd);
    void remove(const QString &toRemove);

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QStringList m_data;
};

#endif // MODELSTOPICLISTMODEL_H
