# SPDX-FileCopyrightText: Copyright 2026 crueter
# SPDX-License-Identifier: GPL-3.0-or-later

qt_add_library(QDashServices STATIC
    ConnManager.cpp ConnManager.h
    SettingsManager.cpp SettingsManager.h
    Logger.cpp Logger.h
    TopicStore.cpp TopicStore.h
    StructStore.h StructStore.cpp
    StructManager.h StructManager.cpp
    QtNTInterface.h QtNTInterface.cpp)

target_link_libraries(QDashServices PRIVATE
    ntcore
    Qt6::Core Qt6::Qml Qt6::Gui)

target_link_libraries(QDashServices PUBLIC
    unordered_dense::unordered_dense)
