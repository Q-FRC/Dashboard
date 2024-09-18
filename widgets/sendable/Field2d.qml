import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15
import QtQuick.Shapes 2.15

import QFRCDashboard

BaseWidget {
    property string item_topic

    property double item_robotWidthMeters: 0.5
    property double item_robotLengthMeters: 0.5

    property double fieldWidth: 8.2296;
    property double fieldLength: 8.2296 * 2.;

    function redraw() {
        robot.redraw()
    }

    onItem_robotLengthMetersChanged: redraw()
    onItem_robotWidthMetersChanged: redraw()

    onWidthChanged: redraw()
    onHeightChanged: redraw()

    Image {
        id: field

        y: titleField.height + 10

        x: 8
        width: parent.width - 16
        height: parent.height - titleField.height - 16

        fillMode: Image.PreserveAspectFit
        source: "qrc:/2024Field.png"
    }

    Rectangle {
        color: "transparent"
        border {
            color: "red"
            width: 2
        }

        property double xMeters: 0
        property double yMeters: 0
        property double angleDeg: 0

        id: robot

        function updateTopic(ntTopic, value) {
            if (ntTopic === item_topic + "/Robot") {
                xMeters = value[0]
                yMeters = value[1]
                angleDeg = value[2]
                redraw()
            }
        }

        function redraw() {
            let meterRatio = field.paintedHeight / fieldWidth

            height = item_robotWidthMeters * meterRatio
            width = item_robotLengthMeters * meterRatio

            let xPixels = xMeters * meterRatio
            let yPixels = yMeters * meterRatio

            let realFieldX = field.x + (field.width - field.paintedWidth) / 2
            let realFieldY = field.y + (field.height - field.paintedHeight) / 2

            let bottomLeft = Qt.point(realFieldX, realFieldY + field.paintedHeight)

            x = bottomLeft.x + xPixels
            y = bottomLeft.y - yPixels - height

            rotation = -angleDeg

            path.redraw(x, y, height, width, angleDeg)
        }

        Component.onCompleted: {
            topicStore.topicUpdate.connect(updateTopic)
            item_topic = model.topic
            topicStore.subscribe(item_topic + "/Robot")
        }

        Component.onDestruction: {
            if (topicStore !== null) {
                topicStore.topicUpdate.disconnect(updateTopic)
                topicStore.unsubscribe(item_topic + "/Robot")
            }
        }
    }

    Shape {
        id: shape

        ShapePath {
            id: path
            strokeWidth: 3
            strokeColor: "light green"

            PathLine {
                id: start
            }
            PathLine {
                id: middle
            }
            PathLine {
                id: end
            }

            function redraw(x, y, h, w, rot) {
                shape.x = x
                shape.y = y

                shape.width = w
                shape.height = h

                start.x = w
                start.y = h / 2

                middle.x = 0
                middle.y = h

                end.x = 0
                end.y = 0

                shape.rotation = -rot
            }
        }
    }

    onItem_topicChanged: {
        model.topic = item_topic
    }
}
