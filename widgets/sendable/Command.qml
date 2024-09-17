import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15

import QFRCDashboard

BaseWidget {
    property string item_topic

    property int item_fontSize: 18

    Button {
        id: cmdButton

        anchors {
            verticalCenter: parent.verticalCenter
            horizontalCenter: parent.horizontalCenter
        }

        font.pixelSize: item_fontSize

        property bool running: false
        property string name: "Command"

        function updateTopic(ntTopic, value) {
            if (ntTopic === item_topic + "/.name") {
                name = value
            } else if (ntTopic === item_topic + "/running") {
                running = value
            }
        }

        onClicked: {
            running = !running
            topicStore.setValue(item_topic + "/running", running)
        }

        text: name

        Component.onCompleted: {
            topicStore.topicUpdate.connect(updateTopic)
            item_topic = model.topic
            topicStore.subscribe(item_topic + "/.name")
            topicStore.subscribe(item_topic + "/running")
        }

        Component.onDestruction: {
            if (topicStore !== null) {
                topicStore.topicUpdate.disconnect(updateTopic)
                topicStore.unsubscribe(item_topic + "/.name")
                topicStore.unsubscribe(item_topic + "/running")
            }
        }
    }

    onItem_topicChanged: {
        model.topic = item_topic
    }
}
