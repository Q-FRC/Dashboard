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
public:
    explicit TypeStore(QWidget *parent = nullptr);

    void registerType(TopicTypes topicType, WidgetTypes widgetType);
    QList<QAction *> generateActionsForType(TopicTypes type, std::string ntTopic);
    QMenu *generateMenuForType(TopicTypes type, std::string ntTopic);

public slots:
    void emitWidget(BaseWidget *widget, WidgetData data);
signals:
    void widgetReady(BaseWidget *widget, WidgetData data);
    void dialogShown();
};

#endif // TYPESTORE_H
