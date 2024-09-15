import QtQuick 2.15
import QtQuick.Controls 2.15

import QFRCDashboard

BaseWidget {
    property string item_topic

    property int item_checkboxSize: 20

    property color item_falseColor: "#FF0000"
    property color item_trueColor: "#00FF00"

    Menu {
        id: switchMenu
        title: "Switch Widget..."

        MenuItem {
            text: "Checkbox"
            onTriggered: {
                model.type = "bool"
            }
        }
    }

    Component.onCompleted: {
        rcMenu.addMenu(switchMenu)
    }

    Rectangle {
        id: rect

        function updateTopic(ntTopic, ntValue) {
            if (ntTopic === item_topic) {
                color = ntValue ? item_trueColor : item_falseColor
            }
        }

        anchors {
            top: titleField.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom

            margins: 10
        }

        Component.onCompleted: {
            topicStore.topicUpdate.connect(updateTopic)
            item_topic = model.topic
        }

        Component.onDestruction: {
            if (topicStore !== null) {
                topicStore.topicUpdate.disconnect(updateTopic)
                topicStore.unsubscribe(item_topic)
            }
        }
    }

    onItem_topicChanged: {
        topicStore.unsubscribe(topic)
        topicStore.subscribe(item_topic)
        model.topic = item_topic
        rect.updateTopic(item_topic, topicStore.getValue(item_topic))
    }
}
