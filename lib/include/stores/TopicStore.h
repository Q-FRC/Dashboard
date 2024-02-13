#ifndef TopicStore_H
#define TopicStore_H

#include "networktables/NetworkTableEntry.h"
#include "Globals.h"

#include <QMultiHash>
#include <QHash>
#include <QObject>

class BaseWidget;

struct Listener {
    std::string topic;
    QString label;
    nt::NetworkTableEntry *entry;
    BaseWidget *subscriber;
    NT_Listener listenerHandle;
    TopicTypes desiredType;
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

    static nt::NetworkTableEntry *subscribe(std::string ntTopic, BaseWidget *subscriber, TopicTypes desiredType = TopicTypes::None, QString label = "", bool writeOnly = false);

    static void unsubscribe(std::string ntTopic, BaseWidget *subscriber);
    static void unsubscribe(nt::NetworkTableEntry *entry, BaseWidget *subscriber);

    static double getDoubleFromEntry(nt::NetworkTableEntry *entry);
};

#endif // TopicStore_H
