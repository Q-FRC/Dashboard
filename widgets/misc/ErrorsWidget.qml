import QtQuick 2.15
import QtQuick.Controls 2.15

import QFRCDashboard

BaseWidget {
    property string item_topic

    property int item_fontSize: 15

    property list<string> errors

    ListView {
        id: listView

        model: errors.length / 2
        delegate: Row {
            required property int modelData

            spacing: 5
            Image {
                source: "qrc:/" + errors[modelData * 2]
                width: item_fontSize
                height: item_fontSize
            }

            Text {
                font.pixelSize: item_fontSize
                color: Constants.palette.text
                text: errors[modelData * 2 + 1]
                wrapMode: Text.WrapAnywhere
            }
        }

        boundsBehavior: Flickable.StopAtBounds

        anchors {
            top: titleField.bottom
            bottom: parent.bottom

            left: parent.left
            right: parent.right

            margins: 10
        }
    }

    function updateTopic(ntTopic, value) {
        if (ntTopic === item_topic) {
            errors = value
        }
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

    onItem_topicChanged: {
        topicStore.unsubscribe(topic)
        topicStore.subscribe(item_topic)
        model.topic = item_topic
        errors = topicStore.getValue(topic)
        listView.model = errors.length / 2
    }
}
