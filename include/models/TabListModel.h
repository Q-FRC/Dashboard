#ifndef TABLISTMODEL_H
#define TABLISTMODEL_H

#include <QAbstractListModel>
#include <qqmlintegration.h>

typedef struct {
    QString title;

    int rows;
    int cols;
} Tab;

class TabListModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT

public:
    enum TLMRoleTypes {
        TITLE = Qt::UserRole,
        ROWS,
        COLS
    };

    explicit TabListModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    // Add data:
    Q_INVOKABLE void add(QString title);

    // Remove data:
    Q_INVOKABLE bool remove(int row, int column, const QModelIndex &parent = QModelIndex());

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<Tab> m_data;
};
#endif // TABLISTMODEL_H
