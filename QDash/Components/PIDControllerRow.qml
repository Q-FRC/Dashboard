// SPDX-FileCopyrightText: Copyright 2026 crueter
// SPDX-License-Identifier: GPL-3.0-or-later

import Carboxyl.Clover

import Carboxyl.Contour

import QDash.Components
import QDash.Controls
import QDash.Core
import QDash.Widgets
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts

RowLayout {
    required property string label
    required property string topic

    function setValue(value) {
        // TODO: handle izone properly
        if (Number.isFinite(value)) {
            spinbox.value = value
        }
    }

    DoubleSpinBox {
        id: spinbox

        editable: true
        enabled: widget.connected

        font.pixelSize: widget.fontSize

        from: widget.lowerBound
        to: widget.upperBound
        stepSize: widget.stepSize

        value: 0

        onValueModified: widget.setValue(topic, value)
    }

    Label {
        text: label
        font.pixelSize: widget.fontSize
    }

    Component.onCompleted: widget.spinboxMap.set(topic, this)
}
