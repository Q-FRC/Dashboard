#ifndef TYPESTORE_H
#define TYPESTORE_H

#include "Globals.h"

#include <QObject>
#include <QAction>

class BaseWidget;

class TypeStore : public QObject
{
    Q_OBJECT
private:
    QMultiMap<TopicTypes, WidgetTypes> m_typeWidgetMap{};
    QMap<WidgetTypes, QString> m_widgetNameMap{};
public:
    explicit TypeStore();

    void registerType(TopicTypes topicType, WidgetTypes widgetType, QString displayName);
    QList<QAction *> generateActionsForTopic(Globals::Topic topic, bool emitTopic = false);
    QMenu *generateMenuForTopic(Globals::Topic topic, bool emitTopic = false);

    QString widgetDisplayName(WidgetTypes type);

public slots:
    void emitWidget(BaseWidget *widget, WidgetData data);
signals:
    void widgetReady(BaseWidget *widget, WidgetData data);
    void topicSelected(const Globals::Topic &topic);
};

#endif // TYPESTORE_H
