import QtQuick 2.15
import QtQuick.Controls 2.15

import QFRCDashboard

BaseWidget {
    property string item_topic

    property int item_fontSize: 15
    property int item_stepSize: 1

    SpinBox {
        id: spin

        font.pixelSize: item_fontSize

        function updateTopic(ntTopic, ntValue) {
            if (ntTopic === topic) {
                value = ntValue
            }
        }

        value: 0
        stepSize: item_stepSize

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
            value = topicStore.getValue(topic)
        }

        Component.onDestruction: {
            if (topicStore !== null) {
                topicStore.topicUpdate.disconnect(updateTopic)
                topicStore.unsubscribe(topic)
            }
        }

        onValueModified: topicStore.setValue(topic, value)

    }
}
