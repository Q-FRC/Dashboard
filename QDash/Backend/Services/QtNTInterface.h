// SPDX-FileCopyrightText: Copyright 2026 crueter
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <QVariant>
#include <wpi/nt/NetworkTableValue.hpp>

class QtNTInterface {
public:
    static QVariant toVariant(const wpi::nt::Value &value);
    static wpi::nt::Value toValue(const QVariant &value);
};
