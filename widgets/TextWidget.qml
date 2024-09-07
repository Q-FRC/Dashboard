import QtQuick 2.15
import QtQuick.Controls

import QFRCDashboard

Rectangle {
    id: rect
    width: 100
    height: 100
    color: Constants.widgetBg

    Drag.active: mouseArea.drag.active

    property point beginDrag

    property bool caught: false

    property int mrow
    property int mcolumn

    onMrowChanged: model.row = mrow
    onMcolumnChanged: model.column = mcolumn

    Frame {
        anchors.fill: parent
    }

    MouseArea {
        id: mouseArea

        anchors.fill: parent
        drag.target: parent

        onPressed: {
            rect.beginDrag = Qt.point(parent.x, parent.y);
            parent.anchors.centerIn = undefined
            rect.Drag.hotSpot = Qt.point(mouse.x, mouse.y)
        }

        onReleased: {
            if (!rect.caught) {
                backAnimX.from = rect.x;
                backAnimX.to = beginDrag.x;
                backAnimY.from = rect.y;
                backAnimY.to = beginDrag.y;
                backAnim.start()
            } else {
                rect.Drag.drop()
            }
        }

        ParallelAnimation {
            id: backAnim
            SmoothedAnimation { id: backAnimX; target: rect; property: "x"; duration: 250 }
            SmoothedAnimation { id: backAnimY; target: rect; property: "y"; duration: 250 }

            onFinished: {
                x = rect.beginDrag.x
                y = rect.beginDrag.y
            }
        }

        Text {
            font.pixelSize: 20
            text: model.title
            color: "#FFFFFF"

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }
}
