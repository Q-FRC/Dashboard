// SPDX-FileCopyrightText: Copyright 2026 crueter
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <ankerl/unordered_dense.h>
#include "wpi/nt/GenericEntry.hpp"
#include "wpi/nt/NetworkTableInstance.hpp"
#include "wpi/nt/NetworkTableValue.hpp"
#include "wpi/nt/ntcore_c.h"

class EntryStore {
public:
    explicit EntryStore(wpi::nt::NetworkTableInstance &instance);

    // manual map management
    void removeEntry(const std::string &topic);
    wpi::nt::GenericEntry &getEntry(const std::string &topic, const std::string &typeString);

    void addCallback(const std::string &topic,
                     std::function<void(const wpi::nt::Event &)> callback);

    // always-on callback, only removed by clear()
    void addPersistentCallback(const std::string &topic,
                               std::function<void(const wpi::nt::Event &)> callback);

    // helpers
    void setValue(const std::string &topic, const std::string &typeString,
                  const wpi::nt::Value &value);
    wpi::nt::Value getValue(const std::string &topic, const std::string &typeString);

    // clear everything
    void clear();

private:
    wpi::nt::NetworkTableInstance m_instance;

    // entry, plus requested type string
    struct TrackedEntry {
        wpi::nt::GenericEntry entry;
        std::string typeString;
    };

    // topic str -> GenericEntry
    ankerl::unordered_dense::map<std::string, TrackedEntry> m_entries;

    // topic str -> subscription callback handle
    ankerl::unordered_dense::map<std::string, NT_Listener> m_callbackHandles;

    // topic str -> always-on callback handle
    ankerl::unordered_dense::map<std::string, NT_Listener> m_persistentCallbacks;
};
