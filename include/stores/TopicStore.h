#ifndef TopicStore_H
#define TopicStore_H

#include "networktables/NetworkTableEntry.h"
#include "Globals.h"

#include <QMultiHash>
#include <QHash>
#include <QObject>
#include <qqmlintegration.h>

struct Listener {
    QString topic;
    NT_Listener listenerHandle;
    nt::ListenerCallback callback;
    int numSubscribed;
    bool isNull;

    bool operator==(const Listener &other) const;
};

class TopicStore : public QObject
{
    Q_OBJECT
    QML_ELEMENT
private:
    bool hasEntry(QString topic);

    Q_INVOKABLE Listener entry(QString topic);

    QList<Listener> Listeners;
    QHash<QString, nt::NetworkTableEntry> topicEntryMap;

public:
    static QVariant toVariant(const nt::Value &value);
    static nt::Value toValue(const QVariant &value);

    TopicStore(QObject *parent = nullptr);

    Q_INVOKABLE void subscribe(QString ntTopic);
    Q_INVOKABLE void unsubscribe(QString ntTopic);

    double getDoubleFromEntry(nt::NetworkTableEntry entry);

    Q_INVOKABLE QVariant getValue(QString topic);
    Q_INVOKABLE void setValue(QString topic, const QVariant &value);

    QString typeString(QString topic);
signals:
    void topicUpdate(QString topic, QVariant newValue);
};

#endif // TopicStore_H
