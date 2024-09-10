#ifndef TOPICLISTMODEL_H
#define TOPICLISTMODEL_H

#include <QStandardItemModel>
#include <qqmlintegration.h>

class TopicListModel : public QStandardItemModel
{
    QML_ELEMENT
    Q_OBJECT

public:
    enum TLMRoleTypes {
        NAME = Qt::UserRole,
    };

    TopicListModel(QObject *parent = nullptr);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Q_INVOKABLE void reload();

    void add(const QString &toAdd);
    void remove(const QString &toRemove);

private:
    QStringList m_data;
};

#endif // MODELSTOPICLISTMODEL_H
