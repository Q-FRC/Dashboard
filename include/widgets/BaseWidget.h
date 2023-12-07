#pragma once

#include "networktables/NetworkTableEntry.h"
#include "Globals.h"

#include <QFrame>
#include <QLabel>
#include <QGridLayout>
#include <QLineEdit>
#include <QJsonObject>

class BaseWidget : public QFrame
{
    Q_OBJECT

    Q_PROPERTY(QString title READ title WRITE setTitle)
    Q_PROPERTY(QString Topic READ topic WRITE setTopic REQUIRED)
protected:
    WidgetTypes m_type;
    QGridLayout *m_layout;

    QLineEdit *m_title;
    bool m_ready = false;

    nt::NetworkTableEntry *m_entry;
public:
    explicit BaseWidget(const WidgetTypes &type = WidgetTypes::StringDisplay, const QString &title = "", const QString &topic = "");
    ~BaseWidget();

    bool ready();
    void setReady(bool ready);

    QFont titleFont();
    void setTitleFont(const QFont &font);

    QString title();
    void setTitle(const QString &title);

    QString topic();
    virtual void setTopic(const QString &topic);

    virtual QMenu *constructContextMenu(WidgetData data);

    virtual void setValue(const nt::Value &value);

    void paintEvent(QPaintEvent *event);

    QJsonObject saveObject();
    WidgetData fromJson(QJsonObject obj, int tabIdx);

    static BaseWidget *defaultWidgetFromTopic(QString ntTopic, WidgetTypes type);

signals:
    void reconfigRequested(BaseWidget *widget, WidgetData data);
    void deleteRequested();
private:
    QVariant readDoubleProperty(const QMetaProperty &property, const QJsonValue &value);
    QVariant readIntProperty(const QMetaProperty &property, const QJsonValue &value);
    QVariant readBoolProperty(const QMetaProperty &property, const QJsonValue &value);
    QVariant readColorProperty(const QMetaProperty &property, const QJsonValue &value);
    QVariant readMapProperty(const QMetaProperty &property, const QJsonValue &value);
    QVariant readListProperty(const QMetaProperty &property, const QJsonValue &value);
    QVariant readFileProperty(const QMetaProperty &property, const QJsonValue &value);
    QVariant readFontProperty(const QMetaProperty &property, const QJsonValue &value);
    QVariant readStringProperty(const QMetaProperty &property, const QJsonValue &value);
    QVariant readShapeProperty(const QMetaProperty &property, const QJsonValue &value);

    QJsonValue writeDoubleProperty(const QMetaProperty &property);
    QJsonValue writeIntProperty(const QMetaProperty &property);
    QJsonValue writeBoolProperty(const QMetaProperty &property);
    QJsonValue writeColorProperty(const QMetaProperty &property);
    QJsonValue writeMapProperty(const QMetaProperty &property);
    QJsonValue writeListProperty(const QMetaProperty &property);
    QJsonValue writeFileProperty(const QMetaProperty &property);
    QJsonValue writeFontProperty(const QMetaProperty &property);
    QJsonValue writeStringProperty(const QMetaProperty &property);
    QJsonValue writeShapeProperty(const QMetaProperty &property);
};
