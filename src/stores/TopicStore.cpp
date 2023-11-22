#include "stores/TopicStore.h"
#include "widgets/BaseWidget.h"

#include "Globals.h"

QHash<std::string, nt::NetworkTableEntry *> TopicStore::topicEntryMap{};
QMultiHash<std::string, BaseWidget *> TopicStore::topicSubscriberMap{};

TopicStore::TopicStore()
{
    throw std::runtime_error("TopicStore is a static class.");
}

nt::NetworkTableEntry *TopicStore::subscribe(std::string ntTopic, BaseWidget *subscriber) {
    if (!topicEntryMap.contains(ntTopic)) {
        nt::NetworkTableEntry *entry =
            new nt::NetworkTableEntry(nt::GetEntry(Globals::inst.GetHandle(), ntTopic));

        topicEntryMap.insert(ntTopic, entry);
    }

    if (!topicSubscriberMap.contains(ntTopic, subscriber)) topicSubscriberMap.insert(ntTopic, subscriber);

    nt::NetworkTableEntry *entry = topicEntryMap.value(ntTopic);

    Globals::inst.AddListener(entry->GetTopic(), nt::EventFlags::kValueAll, [entry, subscriber](const nt::Event &event) {
        nt::Value value = entry->GetValue();
        if (value.IsValid()) subscriber->setValue(entry->GetValue());
    });
    return topicEntryMap.value(ntTopic);
    // TODO: account for multi-topic subscriptions
}

void TopicStore::unsubscribe(std::string ntTopic, BaseWidget *subscriber) {
    if (!topicEntryMap.contains(ntTopic)) return;
    if (!topicSubscriberMap.contains(ntTopic, subscriber)) return;

    topicSubscriberMap.remove(ntTopic, subscriber);

    if (!topicSubscriberMap.contains(ntTopic)) {
        nt::NetworkTableEntry *entry = topicEntryMap.value(ntTopic);

        entry->Unpublish();

        topicEntryMap.remove(ntTopic);
    }
}

void TopicStore::unsubscribe(nt::NetworkTableEntry *entry, BaseWidget *subscriber) {
    unsubscribe(entry->GetName(), subscriber);
}
