import QtQuick 2.15
import QtQuick.Controls 2.15

import QFRCDashboard

BaseWidget {
    property string item_topic

    property int item_fontSize: 15

    TextField {
        id: textField

        font.pixelSize: item_fontSize

        function updateTopic(ntTopic, value) {
            if (ntTopic === topic) {
                text = value
            }
        }

        text: ""

        anchors {
            verticalCenter: parent.verticalCenter
            topMargin: titleField.height

            left: parent.left
            right: parent.right

            leftMargin: 10
            rightMargin: 10
        }

        Component.onCompleted: {
            topicStore.topicUpdate.connect(updateTopic)
            topicStore.subscribe(topic)
            text = topicStore.getValue(topic)
        }

        Component.onDestruction: {
            if (topicStore !== null) {
                topicStore.topicUpdate.disconnect(updateTopic)
                topicStore.unsubscribe(topic)
            }
        }

        onTextEdited: topicStore.setValue(topic, text)
    }
}
