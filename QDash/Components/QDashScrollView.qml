// SPDX-FileCopyrightText: Copyright 2026 crueter
// SPDX-License-Identifier: GPL-3.0-or-later

import QtQuick 6.8
import QtQuick.Controls

ScrollView {
    id: scroll

    property double sensitivity: 1

    WheelHandler {
        target: scroll

        onWheel: event => {
            const sensitivity = scroll.sensitivity / 1500
            scroll.ScrollBar.vertical.position -= event.pixelDelta.y * sensitivity
            scroll.ScrollBar.vertical.position = Math.max(Math.min(scroll.ScrollBar.vertical.position, 1.0 - scroll.ScrollBar.vertical.size), 0.0)
        }
    }
}
