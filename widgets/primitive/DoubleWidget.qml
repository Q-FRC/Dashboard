import QtQuick 2.15
import QtQuick.Controls 2.15

import QFRCDashboard

BaseWidget {
    property string item_topic

    property int item_fontSize: 15
    property double item_stepSize: 0.1

    property double item_lowerBound: 0
    property double item_upperBound: 100

    Menu {
        id: switchMenu
        title: "Switch Widget..."

        MenuItem {
            text: "Dial"
            onTriggered: {
                model.type = "doubleDial"
                model.properties.clear()
            }
        }
    }

    Component.onCompleted: {
        rcMenu.addMenu(switchMenu)
    }

    DoubleSpinBox {
        id: spin

        font.pixelSize: item_fontSize

        function updateTopic(ntTopic, ntValue) {
            if (ntTopic === item_topic) {
                value = ntValue * 100.0
            }
        }

        value: 0
        stepSize: item_stepSize * 100.0

        from: item_lowerBound * 100.0
        to: item_upperBound * 100.0

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
            item_topic = model.topic
        }

        Component.onDestruction: {
            if (topicStore !== null) {
                topicStore.topicUpdate.disconnect(updateTopic)
                topicStore.unsubscribe(item_topic)
            }
        }

        onValueModified: {
            realValue = value / 100.0
            topicStore.setValue(item_topic, realValue)
        }
    }

    onItem_topicChanged: {
        topicStore.unsubscribe(topic)
        topicStore.subscribe(item_topic)
        model.topic = item_topic
        spin.value = topicStore.getValue(item_topic) * 100.0
    }
}
