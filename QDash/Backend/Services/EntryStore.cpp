// SPDX-FileCopyrightText: Copyright 2026 crueter
// SPDX-License-Identifier: GPL-3.0-or-later

#include "EntryStore.h"
#include "wpi/nt/GenericEntry.hpp"
#include "wpi/nt/NetworkTableInstance.hpp"

EntryStore::EntryStore(wpi::nt::NetworkTableInstance &instance) : m_instance{instance} {}

void EntryStore::removeEntry(const std::string &topic)
{
    // remove entry
    m_entries.erase(topic);

    // remove callbacks
    // persistent callbacks are not affected by this
    if (const auto it = m_callbackHandles.find(topic); it != m_callbackHandles.end()) {
        m_instance.RemoveListener(it->second);
        m_callbackHandles.erase(it);
    }
}

wpi::nt::GenericEntry &EntryStore::getEntry(const std::string &topic, const std::string &typeString)
{
    // entry is cached and has a matching typestring
    if (const auto it = m_entries.find(topic);
        it != m_entries.end() && it->second.typeString == typeString)
        return it->second.entry;

    // make a new entry
    auto &tracked = m_entries[topic];
    tracked.entry = wpi::nt::GenericEntry(m_instance.GetTopic(topic).GetGenericEntry(typeString));
    tracked.typeString = typeString;
    return tracked.entry;
}

void EntryStore::addCallback(const std::string &topic,
                             std::function<void(const wpi::nt::Event &)> callback)
{
    // remove any previous subscription listener so re-makes don't stack
    if (const auto it = m_callbackHandles.find(topic); it != m_callbackHandles.end())
        m_instance.RemoveListener(it->second);

    const auto ntTopic = m_instance.GetTopic(topic);
    const auto handle =
        m_instance.AddListener(ntTopic, wpi::nt::EventFlags::VALUE_ALL, std::move(callback));

    m_callbackHandles.emplace(topic, handle);
}

void EntryStore::addPersistentCallback(const std::string &topic,
                                       std::function<void(const wpi::nt::Event &)> callback)
{
    // dedup so re-registrations don't stack
    if (m_persistentCallbacks.contains(topic))
        return;

    const auto ntTopic = m_instance.GetTopic(topic);
    const auto handle =
        m_instance.AddListener(ntTopic, wpi::nt::EventFlags::VALUE_ALL, std::move(callback));

    m_persistentCallbacks.emplace(topic, handle);
}

void EntryStore::setValue(const std::string &topic, const std::string &typeString,
                          const wpi::nt::Value &value)
{
    getEntry(topic, typeString).Set(value);
}

wpi::nt::Value EntryStore::getValue(const std::string &topic, const std::string &typeString)
{
    return getEntry(topic, typeString).Get();
}

void EntryStore::clear()
{
    for (auto &[_, handle] : m_callbackHandles)
        m_instance.RemoveListener(handle);
    for (auto &[_, handle] : m_persistentCallbacks)
        m_instance.RemoveListener(handle);

    m_callbackHandles.clear();
    m_persistentCallbacks.clear();
    m_entries.clear();
}
