import QtQuick 2.15
import QtQuick.Controls 2.15

import QFRCDashboard

BaseWidget {
    property string item_topic

    property int item_checkboxSize: 20

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

        indicator.implicitHeight: item_checkboxSize
        indicator.implicitWidth: item_checkboxSize

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
