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

SendableWidget {
    id: widget

    readOnly: false
    roleString: "PIDController"

    propertyKeys: ["stepSize", "fontSize", "lowerBound", "upperBound"]
    topics: ["p", "i", "d", "izone", "setpoint"]

    // /{p,i,d} and izone correspond to constants
    // setpoint is the controller's current setpoint

    // map for topic to spinbox ref
    property var spinboxMap: new Map()

    property int fontSize: 12
    property double lowerBound: -100.0
    property double stepSize: 0.1
    property double upperBound: 100.0

    function update(topic, value) {
        widget.connected = true

        let spinbox = widget.spinboxMap.get(topic)
        if (spinbox) {
            spinbox.setValue(value)
        }
    }

    // FIXME: this widget is not draggable or right-clickable because the scroll view eats inputs
    QDashScrollView {
        id: scroll

        anchors {
            bottom: parent.bottom
            left: parent.left
            leftMargin: 10
            right: parent.right
            rightMargin: 10
            top: titleField.bottom
            topMargin: 10
        }

        ColumnLayout {
            PIDControllerRow {
                label: "P"
                topic: "p"
            }

            PIDControllerRow {
                label: "I"
                topic: "i"
            }

            PIDControllerRow {
                label: "D"
                topic: "d"
            }

            PIDControllerRow {
                label: "Setpoint"
                topic: "setpoint"
            }

            PIDControllerRow {
                label: "I Zone"
                topic: "izone"
            }
        }
    }

    // TODO(crueter): Alongside deduping the loader stuff, most of this is just
    // type-label-property, with maybe a few extras... possible schema candidate?
    configComponent: Component {
        ColumnLayout {
            anchors.fill: parent
            anchors.leftMargin: 2
            clip: true
            spacing: 12

            SectionHeader {
                label: "Font Settings"
            }

            RowLayout {
                LabeledSpinBox {
                    bindedProperty: "titleFontSize"
                    label: "Title Font Size"
                }

                LabeledSpinBox {
                    bindedProperty: "fontSize"
                    label: "Font Size"
                }
            }

            SectionHeader {
                label: "Spin Box Settings"
            }

            RowLayout {
                LabeledDoubleSpinBox {
                    bindedProperty: "lowerBound"
                    label: "Lower Bound"
                }

                LabeledDoubleSpinBox {
                    bindedProperty: "upperBound"
                    label: "Upper Bound"
                }
            }

            LabeledDoubleSpinBox {
                bindedProperty: "stepSize"
                from: 0
                label: "Step Size"
                stepSize: 0.1
            }

            SectionHeader {
                label: "NT Settings"
            }

            LabeledTextField {
                bindedProperty: "item_topic"
                label: "Topic"
            }
        }
    }
}
