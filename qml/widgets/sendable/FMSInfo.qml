import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts

import QFDFlags
import QFRCDashboard

SendableWidget {
    id: widget

    topics: ["MatchNumber", "MatchType", "EventName", "IsRedAlliance", "GameSpecificMessage", "FMSControlData"]

    property int item_fontSize: 18

    function update(topic, value) {
        switch (topic) {
        case "MatchNumber":
        {
            match.matchNumber = value
            break
        }
        case "MatchType":
        {
            match.matchType = value
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
        case "GameSpecificMessage":
        {
            gsm.gameSpecificMessage = value
            break
        }
        case "FMSControlData":
        {
            let word = topicStore.toWord(value)

            let state = ""

            if (word & QFDFlags.Auto) {
                state += "Autonomous"
            } else if (word & QFDFlags.Test) {
                state += "Testing"
            } else {
                state += "Teleop"
            }

            if (word & QFDFlags.Enabled) {
                state += " Enabled"
            } else if (word & QFDFlags.EStop) {
                state += " E-Stopped"
            } else {
                state += " Disabled"
            }

            stateText.state = state
            break
        }
        }
    }

    ColumnLayout {
        anchors {
            top: titleField.bottom
            topMargin: 8

            left: parent.left
            right: parent.right

            leftMargin: 10
            rightMargin: 10
        }

        Rectangle {
            id: rect

            Layout.fillWidth: true
            property bool isRedAlliance: false

            radius: 4 * Constants.scalar

            color: isRedAlliance ? "red" : "blue"

            implicitHeight: item_fontSize * 2 * Constants.scalar

            Text {
                anchors.fill: parent

                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                color: Constants.palette.text

                property int matchNumber: 0
                property string matchType: "Unknown"
                property string eventName: "Event"
                property list<string> matchTypeMap: ["Unknown", "Practice", "Quals", "Elims"]

                id: match

                font.pixelSize: item_fontSize * Constants.scalar

                text: eventName + ": " + matchType + " Match " + matchNumber
            }
        }

        Text {
            Layout.fillWidth: true
            color: Constants.palette.text

            property string gameSpecificMessage: ""

            id: gsm

            font.pixelSize: item_fontSize * Constants.scalar

            horizontalAlignment: Text.AlignHCenter

            text: gameSpecificMessage

            visible: gameSpecificMessage !== ""
        }

        Text {
            Layout.fillWidth: true
            color: Constants.palette.text

            property string state: "Unknown"

            id: stateText

            font.pixelSize: item_fontSize * Constants.scalar

            horizontalAlignment: Text.AlignHCenter

            text: state
        }
    }

    BaseConfigDialog {
        id: config

        function openDialog() {
            topicField.open()
            titleFontField.open()
            fontField.open()

            open()
        }

        onAccepted: {
            topicField.accept()
            titleFontField.accept()
            fontField.accept()
        }

        ColumnLayout {
            id: layout
            spacing: 12 * Constants.scalar

            anchors {
                top: parent.top
                bottom: parent.bottom
                left: parent.left
                right: parent.right

                topMargin: 5 * Constants.scalar

                rightMargin: 5
            }

            SectionHeader {
                label: "Font Settings"
            }

            RowLayout {
                uniformCellSizes: true

                LabeledSpinBox {
                    Layout.fillWidth: true

                    id: titleFontField

                    label: "Title Font Size"

                    bindedProperty: "item_titleFontSize"
                    bindTarget: widget
                }

                LabeledSpinBox {
                    Layout.fillWidth: true

                    id: fontField

                    label: "Font Size"

                    bindedProperty: "item_fontSize"
                    bindTarget: widget
                }
            }

            SectionHeader {
                label: "NT Settings"
            }

            LabeledTextField {
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignTop

                id: topicField

                label: "Topic"

                bindedProperty: "item_topic"
                bindTarget: widget
            }
        }
    }
}
