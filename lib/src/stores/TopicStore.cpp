#include "stores/TopicStore.h"
#include "stores/FilterStore.h"

#include "widgets/BaseWidget.h"

#include "Globals.h"

QList<Listener> TopicStore::Listeners{};
QHash<std::string, nt::NetworkTableEntry *> TopicStore::topicEntryMap{};

TopicStore::TopicStore()
{
    throw std::runtime_error("TopicStore is a static class.");
}

bool TopicStore::hasEntry(std::string topic) {
    for (const Listener &listener : Listeners) {
        if (topic == listener.topic) {
            return true;
        }
    }
    return false;
}

bool TopicStore::hasEntry(QString topic) {
    return hasEntry(topic.toStdString());
}

bool TopicStore::widgetSubscribed(std::string topic, BaseWidget *subscriber) {
    return !getEntry(topic, subscriber).isNull;
}

bool TopicStore::widgetSubscribed(QString topic, BaseWidget *subscriber) {
    return !getEntry(topic, subscriber).isNull;
}

Listener TopicStore::getEntry(std::string topic, BaseWidget *subscriber) {
    for (Listener listener : Listeners) {
        if (listener.topic == topic && listener.subscriber == subscriber) {
            return listener;
        }
    }

    Listener l;
    l.isNull = true;
    return l;
}

Listener TopicStore::getEntry(QString topic, BaseWidget *subscriber) {
    return getEntry(topic.toStdString(), subscriber);
}

bool Listener::operator==(const Listener &other) const {
    return (other.topic == this->topic) &&
           (other.entry == this->entry) &&
           (other.label == this->label) &&
           (other.subscriber == this->subscriber) &&
           (other.listenerHandle == this->listenerHandle) &&
           (other.desiredType == this->desiredType) &&
           (other.isNull == this->isNull);
}

nt::NetworkTableEntry *TopicStore::subscribe(std::string ntTopic, BaseWidget *subscriber, TopicTypes desiredType, QString label, bool writeOnly) {
    Listener listener;
    nt::NetworkTableEntry *entry = nullptr;
    if (hasEntry(ntTopic)) {
        entry = new nt::NetworkTableEntry(nt::GetEntry(Globals::inst.GetHandle(), ntTopic));

        listener = {
            ntTopic,
            label,
            entry,
            subscriber,
            0,
            desiredType,
            false
        };

        topicEntryMap.insert(ntTopic, entry);
    }

    if (!entry) entry = topicEntryMap.value(ntTopic);

    if (!writeOnly) {
        nt::ListenerCallback updateWidget = [entry, subscriber, desiredType, label, ntTopic](const nt::Event &event = nt::Event()) {
            nt::Value value;
            if (!event.Is(nt::EventFlags::kValueAll)) {
                value = entry->GetValue();
            } else {
                value = event.GetValueEventData()->value;
            }

            // ensure thread-safety
            // this is mild anal cancer
            if (value.IsValid()) {
                QMetaObject::invokeMethod(subscriber, [subscriber, value, label, desiredType, ntTopic] {
                    if (FilterStore::topicTypeForNTType((nt::NetworkTableType) value.type())
                        != desiredType) {
                        qCritical() << "Type for topic" <<
                            QString::fromStdString(ntTopic) <<
                            "for widget" <<
                            subscriber->title() <<
                            "is of incorrect type" <<
                            (int) value.type() <<
                            "; expected" <<
                            (int) desiredType;
                        return;
                    }

                    if (subscriber->ready()) {
                        if (subscriber->isEnabled()) {
                            subscriber->setValue(value, label);
                            subscriber->update();
                        }
                    } else {
                        connect(subscriber, &BaseWidget::isReady, subscriber, [subscriber, value, label] {
                                subscriber->setValue(value, label);
                                subscriber->update();
                            }, Qt::SingleShotConnection);
                    }
                }); // QMetaObject and its consequences have been a disaster for the human race
            }
        };

        NT_Listener handle = Globals::inst.AddListener(Globals::inst.GetEntry(ntTopic), nt::EventFlags::kValueAll, updateWidget);

        listener.listenerHandle = handle;
    }

    Listeners.append(listener);

    return entry;
}

void TopicStore::unsubscribe(std::string ntTopic, BaseWidget *subscriber) {
    if (!hasEntry(ntTopic) || !widgetSubscribed(ntTopic, subscriber)) return;

    Listener listener = getEntry(ntTopic, subscriber);
    Listeners.removeOne(listener);

    if (!hasEntry(ntTopic)) listener.entry->Unpublish();
    Globals::inst.RemoveListener(listener.listenerHandle);
}

void TopicStore::unsubscribe(nt::NetworkTableEntry *entry, BaseWidget *subscriber) {
    unsubscribe(entry->GetName(), subscriber);
}

double TopicStore::getDoubleFromEntry(nt::NetworkTableEntry *entry) {
    nt::Value value = entry->GetValue();

    if (value.IsBoolean()) {
        return (double) entry->GetBoolean(0);
    } else if (value.IsDouble()) {
        return entry->GetDouble(0.);
    } else if (value.IsInteger()) {
        return (double) entry->GetInteger(0);
    }

    return 0.;
}
