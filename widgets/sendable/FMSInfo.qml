import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15

import QFDFlags
import QFRCDashboard

BaseWidget {
    property string item_topic

    property int item_fontSize: 18

    ColumnLayout {
        anchors {
            top: titleField.bottom
            topMargin: 8

            left: parent.left
            right: parent.right

            leftMargin: 10
            rightMargin: 10
        }

        Text {
            Layout.fillWidth: true
            color: "#FFFFFF"

            property int matchNumber: 0
            property string matchType: "Unknown"
            property list<string> matchTypeMap: ["Unknown", "Practice", "Quals", "Elims",];

            id: match

            font.pixelSize: item_fontSize

            function updateTopic(ntTopic, value) {
                if (ntTopic === item_topic + "/MatchNumber") {
                    matchNumber = value
                } else if (ntTopic === item_topic + "/MatchType") {
                    matchType = matchTypeMap[value]
                }
            }

            horizontalAlignment: Text.AlignHCenter

            text: matchType + " Match " + matchNumber

            Component.onCompleted: {
                topicStore.topicUpdate.connect(updateTopic)
                item_topic = model.topic
                topicStore.subscribe(item_topic + "/MatchNumber")
                topicStore.subscribe(item_topic + "/MatchType")
            }

            Component.onDestruction: {
                if (topicStore !== null) {
                    topicStore.topicUpdate.disconnect(updateTopic)
                    topicStore.unsubscribe(item_topic + "/MatchNumber")
                    topicStore.unsubscribe(item_topic + "/MatchType")
                }
            }
        }

        Text {
            Layout.fillWidth: true
            color: "#FFFFFF"

            property int stationNumber: 1
            property string alliance: "Red"

            id: station

            font.pixelSize: item_fontSize

            function updateTopic(ntTopic, value) {
                if (ntTopic === item_topic + "/StationNumber") {
                    stationNumber = value
                } else if (ntTopic === item_topic + "/IsRedAlliance") {
                    alliance = value ? "Red" : "Blue"
                }
            }

            horizontalAlignment: Text.AlignHCenter

            text: "Station: " + alliance + " " + stationNumber;

            Component.onCompleted: {
                topicStore.topicUpdate.connect(updateTopic)
                item_topic = model.topic
                topicStore.subscribe(item_topic + "/StationNumber")
                topicStore.subscribe(item_topic + "/IsRedAlliance")
            }

            Component.onDestruction: {
                if (topicStore !== null) {
                    topicStore.topicUpdate.disconnect(updateTopic)
                    topicStore.unsubscribe(item_topic + "/StationNumber")
                    topicStore.unsubscribe(item_topic + "/IsRedAlliance")
                }
            }
        }

        Text {
            Layout.fillWidth: true
            color: "#FFFFFF"

            property string eventName: "Unknown Event"

            id: event

            font.pixelSize: item_fontSize

            function updateTopic(ntTopic, value) {
                if (ntTopic === item_topic + "/EventName") {
                    eventName = value
                }
            }

            horizontalAlignment: Text.AlignHCenter

            text: "Event: " + eventName;

            Component.onCompleted: {
                topicStore.topicUpdate.connect(updateTopic)
                item_topic = model.topic
                topicStore.subscribe(item_topic + "/EventName")
            }

            Component.onDestruction: {
                if (topicStore !== null) {
                    topicStore.topicUpdate.disconnect(updateTopic)
                    topicStore.unsubscribe(item_topic + "/EventName")
                }
            }
        }

        Text {
            Layout.fillWidth: true
            color: "#FFFFFF"

            property string gameSpecificMessage: "None"

            id: gsm

            font.pixelSize: item_fontSize

            function updateTopic(ntTopic, value) {
                if (ntTopic === item_topic + "/GameSpecificMessage") {
                    gameSpecificMessage = value
                }
            }

            horizontalAlignment: Text.AlignHCenter

            text: "Game Specific Message: " + gameSpecificMessage;

            Component.onCompleted: {
                topicStore.topicUpdate.connect(updateTopic)
                item_topic = model.topic
                topicStore.subscribe(item_topic + "/GameSpecificMessage")
            }

            Component.onDestruction: {
                if (topicStore !== null) {
                    topicStore.topicUpdate.disconnect(updateTopic)
                    topicStore.unsubscribe(item_topic + "/GameSpecificMessage")
                }
            }
        }

        Text {
            Layout.fillWidth: true
            color: "#FFFFFF"

            property string state: "Unknown"

            id: stateText

            font.pixelSize: item_fontSize

            function updateTopic(ntTopic, value) {
                if (ntTopic === item_topic + "/FMSControlData") {
                    let word = topicStore.toWord(value)

                    state = ""

                    if (word & QFDFlags.Auto) {
                        state += "Autonomous";
                    }
                    else if (word & QFDFlags.Test) {
                        state += "Testing";
                    } else {
                        state += "Teleop";
                    }

                    if (word & QFDFlags.Enabled) {
                        state += " Enabled";
                    } else if (word & QFDFlags.EStop) {
                        state += " E-Stopped";
                    } else {
                        state += " Disabled";
                    }
                }
            }

            horizontalAlignment: Text.AlignHCenter

            text: "Robot State: " + state;

            Component.onCompleted: {
                topicStore.topicUpdate.connect(updateTopic)
                item_topic = model.topic
                topicStore.subscribe(item_topic + "/FMSControlData")
            }

            Component.onDestruction: {
                if (topicStore !== null) {
                    topicStore.topicUpdate.disconnect(updateTopic)
                    topicStore.unsubscribe(item_topic + "/FMSControlData")
                }
            }
        }
    }

    onItem_topicChanged: {
        model.topic = item_topic
    }
}
