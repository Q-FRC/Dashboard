// SPDX-FileCopyrightText: Copyright 2026 crueter
// SPDX-License-Identifier: GPL-3.0-or-later

import Carboxyl.Clover
import QDash.Components

import QDash.Controls
import QDash.Widgets

import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts

SendableWidget {
    id: widget

    readOnly: true
    roleString: "DriverStation"

    propertyKeys: ["fontSize"]
    topics: ["MatchNumber", "MatchType", "EventName", "IsRedAlliance", "ControlWord", "OpMode"]

    property int fontSize: 16

    function update(topic, value) {
        widget.connected = true
        switch (topic) {
        case "MatchNumber":
            {
                match.matchNumber = value
                break
            }
        case "MatchType":
            {
                match.matchType = match.matchTypeMap[value]
                break
            }
        case "EventName":
            {
                match.eventName = value
                break
            }
        case "IsRedAlliance":
            {
                rect.isRedAlliance = value
                break
            }
        case "ControlWord":
            {
                // TODO: fms? ds? estop? probably not
                stateText.robotMode = stateText.robotModeMap[value.robotMode]
                stateText.robotEnabled = value.enabled
                break
            }
        case "OpMode":
            {
                opModeText.text = value
                break
            }
        }
    }

    ColumnLayout {
        spacing: 2

        anchors {
            left: parent.left
            leftMargin: 5

            right: parent.right
            rightMargin: 5

            top: titleField.bottom
            topMargin: 4
        }

        Rectangle {
            id: rect

            property bool isRedAlliance: false

            color: isRedAlliance ? "red" : "blue"
            implicitHeight: match.contentHeight + 2
            implicitWidth: match.contentWidth + 8
            Layout.alignment: Qt.AlignCenter
            radius: 4

            Label {
                id: match

                property string eventName: ""
                property int matchNumber: 0
                property string matchType: ""
                property list<string> matchTypeMap: ["", "Practice", "Quals", "Elims"]

                anchors.fill: parent
                enabled: widget.connected
                font.pixelSize: fontSize
                horizontalAlignment: Text.AlignHCenter
                text: {
                    let eventStr = eventName === "" ? "" : `${eventName}: `
                    let matchTypeStr = matchType === "" ? "" : `${matchType} `
                    let matchStr = `Match ${matchNumber}`

                    return `${eventStr}${matchTypeStr}${matchStr}`
                }

                verticalAlignment: Text.AlignVCenter
            }
        }

        Label {
            id: stateText

            property string robotMode: ""
            property string opMode: ""
            property bool robotEnabled: false

            property list<string> robotModeMap: ["", "Autonomous", "Teleoperated", "Utility"]

            Layout.fillWidth: true
            enabled: widget.connected
            font.pixelSize: fontSize
            horizontalAlignment: Text.AlignHCenter
            text: {
                let modeStr = robotMode === "" ? "" : `${robotMode} `
                let enabledStr = robotEnabled ? "Enabled" : "Disabled"

                return `${modeStr}${enabledStr}`
            }
        }

        Label {
            id: opModeText

            Layout.fillWidth: true
            enabled: widget.connected
            font.pixelSize: fontSize
            horizontalAlignment: Text.AlignHCenter

            visible: text !== ""
        }
    }

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
                label: "NT Settings"
            }

            LabeledTextField {
                bindedProperty: "item_topic"
                label: "Topic"
            }
        }
    }
}
