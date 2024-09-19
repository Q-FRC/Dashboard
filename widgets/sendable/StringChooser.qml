import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15

import QFRCDashboard

BaseWidget {
    property string item_topic

    property int item_fontSize: 18

    ComboBox {
        anchors {
            verticalCenter: parent.verticalCenter
            horizontalCenter: parent.horizontalCenter

            left: parent.left
            right: parent.right

            margins: 8
        }

        font.pixelSize: item_fontSize

        property list<string> choices
        property string active

        property bool readyToUpdate: true

        model: choices

        function updateTopic(ntTopic, value) {
            if (ntTopic === item_topic + "/options") {
                choices = value
            } else if (ntTopic === item_topic + "/active") {
                if (!readyToUpdate) {
                    readyToUpdate = true;
                    return;
                }

                active = value
                currentIndex = indexOfValue(active)
            }
        }

        function connected(conn) {
            if (conn) {
                readyToUpdate = false;

                topicStore.setValue(item_topic + "/selected", currentText)
            }
        }

        Component.onCompleted: {
            topicStore.topicUpdate.connect(updateTopic)
            item_topic = topic
            topicStore.subscribe(item_topic + "/options")
            topicStore.subscribe(item_topic + "/active")
            topicStore.subscribe(item_topic + "/selected")
        }

        Component.onDestruction: {
            if (topicStore !== null) {
                topicStore.topicUpdate.disconnect(updateTopic)
                topicStore.unsubscribe(item_topic + "/options")
                topicStore.unsubscribe(item_topic + "/active")
                topicStore.unsubscribe(item_topic + "/selected")
            }
        }

        onCurrentIndexChanged: {
            topicStore.setValue(item_topic + "/selected", valueAt(currentIndex))
        }
    }

    onItem_topicChanged: {
        topic = item_topic
    }
}
