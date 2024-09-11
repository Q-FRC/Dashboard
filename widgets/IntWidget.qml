import QtQuick 2.15
import QtQuick.Controls 2.15

BaseWidget {
    property string topic: "/FMSInfo/MatchNumber"
    SpinBox {
        id: spin

        function updateTopic(ntTopic, ntValue) {
            if (ntTopic === topic) {
                value = ntValue
            }
        }

        value: 0

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
