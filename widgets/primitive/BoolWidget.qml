import QtQuick 2.15
import QtQuick.Controls 2.15

import QFRCDashboard

BaseWidget {
    property string topic

    CheckBox {
        id: control

        function updateTopic(ntTopic, ntValue) {
            if (ntTopic === topic) {
                checked = ntValue
            }
        }

        checked: false

        anchors {
            centerIn: parent
        }

        indicator.implicitHeight: 20
        indicator.implicitWidth: 20

        Component.onCompleted: {
            topicStore.topicUpdate.connect(updateTopic)
            topicStore.subscribe(topic)
            checked = topicStore.getValue(topic)
        }

        Component.onDestruction: {
            if (topicStore !== null) {
                topicStore.topicUpdate.disconnect(updateTopic)
                topicStore.unsubscribe(topic)
            }
        }

        onToggled: topicStore.setValue(topic, checked)

    }
}
