// SPDX-FileCopyrightText: Copyright 2026 crueter
// SPDX-License-Identifier: GPL-3.0-or-later

#include "QtNTInterface.h"

QVariant QtNTInterface::toVariant(const wpi::nt::Value &value)
{
    QVariant v;

    if (!value.IsValid())
        return v;

    if (value.IsBoolean())
        v = value.GetBoolean();
    else if (value.IsString())
        v = QString::fromStdString(std::string(value.GetString()));
    else if (value.IsDouble())
        v = value.GetDouble();
    else if (value.IsFloat())
        v = value.GetFloat();
    else if (value.IsInteger())
        v = QVariant::fromValue(value.GetInteger());

    else if (value.IsBooleanArray()) {
        const std::span<const int> a = value.GetBooleanArray();
        QList<int> newList;
        newList.reserve(a.size());
        for (const int i : a)
            newList << i;

        v = QVariant::fromValue(newList);
    } else if (value.IsStringArray()) {
        const std::span<const std::string> a = value.GetStringArray();
        QStringList newList;
        newList.reserve(a.size());
        for (const std::string &s : a)
            newList << QString::fromStdString(s);

        v = QVariant::fromValue(newList);
    } else if (value.IsDoubleArray()) {
        const std::span<const double> a = value.GetDoubleArray();
        QList<double> newList;
        newList.reserve(a.size());
        for (const double d : a)
            newList << d;

        v = QVariant::fromValue(newList);
    } else if (value.IsIntegerArray()) {
        const std::span<const int64_t> a = value.GetIntegerArray();
        QList<int64_t> newList;
        newList.reserve(a.size());
        for (const int64_t i : a)
            newList << i;

        v = QVariant::fromValue(newList);
    } else if (value.IsRaw()) {
        const std::span<const uint8_t> a = value.GetRaw();
        QString newStr;
        newStr.reserve(a.size());
        for (const uint8_t i : a) {
            newStr = newStr % QChar(i);
        }
        v = newStr;
    }

    return v;
}

wpi::nt::Value QtNTInterface::toValue(const QVariant &value)
{
    if (!value.isValid())
        return {};

    switch (value.typeId()) {
    case QMetaType::Type::QString:
        return wpi::nt::Value::MakeString(std::string_view{value.toString().toStdString()});
    case QMetaType::Type::Bool:
        return wpi::nt::Value::MakeBoolean(value.toBool());
    case QMetaType::Type::Double:
        return wpi::nt::Value::MakeDouble(value.toDouble());
    case QMetaType::Type::Float:
        return wpi::nt::Value::MakeFloat(value.toFloat());
    case QMetaType::Type::Int:
        return wpi::nt::Value::MakeInteger(value.toInt());
    case QMetaType::Type::QStringList: {
        std::vector<std::string> v;
        for (const QString &s : value.toStringList()) {
            v.emplace_back(s.toStdString());
        }

        return wpi::nt::Value::MakeStringArray(v);
    }
    default:
        break;
    }

    if (value.typeId() == qMetaTypeId<QList<bool>>()) {
        std::vector<int> v;
        for (const QVariant &b : value.toList()) {
            v.emplace_back(b.toBool());
        }

        return wpi::nt::Value::MakeBooleanArray(v);
    }

    return {};
}
