import QtQuick 2.15
import QtQuick.Controls 2.15

import QFRCDashboard

BaseWidget {
    property string item_topic

    property int item_fontSize: 15
    property double item_stepSize: 0.1

    DoubleSpinBox {
        id: spin

        font.pixelSize: item_fontSize

        function updateTopic(ntTopic, ntValue) {
            if (ntTopic === topic) {
                value = ntValue * 100.0
            }
        }

        value: 0
        stepSize: item_stepSize * 100.0

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

        onValueModified: {
            realValue = value / 100.0
            topicStore.setValue(topic, realValue)
        }

    }
}
