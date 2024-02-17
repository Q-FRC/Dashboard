#ifndef TopicStore_H
#define TopicStore_H

#include "networktables/NetworkTableEntry.h"
#include "Globals.h"

#include <QMultiHash>
#include <QHash>
#include <QObject>

class BaseWidget;
using WidgetPtr = std::shared_ptr<BaseWidget>;

struct Listener {
    std::string topic;
    QString label;
    nt::NetworkTableEntry *entry;
    WidgetPtr subscriber;
    NT_Listener listenerHandle;
    nt::ListenerCallback callback;
    NT_Type desiredType;
    bool isNull;

    bool operator==(const Listener &other) const;
};

class TopicStore : public QObject
{
    Q_OBJECT
private:
    static bool hasEntry(std::string topic);
    static bool hasEntry(QString topic);

    static bool widgetSubscribed(std::string topic, BaseWidget *subscriber);
    static bool widgetSubscribed(QString topic, BaseWidget *subscriber);

    static Listener getEntry(std::string topic, BaseWidget *subscriber);
    static Listener getEntry(QString topic, BaseWidget *subscriber);
public:
    static QList<Listener> Listeners;
    static QHash<std::string, nt::NetworkTableEntry *> topicEntryMap;

    TopicStore();

    static nt::NetworkTableEntry *subscribe(std::string ntTopic, WidgetPtr subscriber, NT_Type desiredType = NT_UNASSIGNED, QString label = "", bool writeOnly = false);

    static void unsubscribe(std::string ntTopic, WidgetPtr subscriber);
    static void unsubscribe(QString ntTopic, WidgetPtr subscriber);
    static void unsubscribe(nt::NetworkTableEntry *entry, WidgetPtr subscriber);
    static double getDoubleFromEntry(nt::NetworkTableEntry *entry);

    static void updateTopic(std::string topic, WidgetPtr subscriber, QString label);
};

#endif // TopicStore_H

