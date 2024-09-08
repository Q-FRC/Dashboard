import QtQuick 2.15
import QtQuick.Controls 2.15

import QFRCDashboard 1.0
import DirectionFlags 1.0

Rectangle {
    id: rect
    width: 100
    height: 100
    color: Constants.widgetBg

    Drag.active: dragArea.drag.active

    signal resizeBegin(var drag)

    property point beginDrag
    property point beginResize

    property bool caught: false

    property int mrow
    property int mcolumn
    property int mrowSpan
    property int mcolumnSpan

    onMrowChanged: model.row = mrow
    onMcolumnChanged: model.column = mcolumn
    onMrowSpanChanged: model.rowSpan = mrowSpan
    onMcolumnSpanChanged: model.colSpan = mcolumnSpan

    Component.onCompleted: {
        mrow = model.row
        mcolumn = model.column
        mrowSpan = model.rowSpan
        mcolumnSpan = model.colSpan
    }

    Frame {
        anchors.fill: parent
    }

    MouseArea {
        id: dragArea
        z: 0

        anchors {
            fill: parent

            margins: 6
        }

        drag.target: parent

        onPressed: (mouse) => {
                       rect.beginDrag = Qt.point(parent.x, parent.y);
                       rect.Drag.hotSpot = Qt.point(mouse.x, mouse.y)
                       parent.z = 3
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
                parent.z = 2
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
    }

    ParallelAnimation {
        id: resizeBackAnim
        SmoothedAnimation { id: resizeBackAnimX; target: rect; property: "width"; duration: 250 }
        SmoothedAnimation { id: resizeBackAnimY; target: rect; property: "height"; duration: 250 }

        onFinished: {
            width = rect.beginResize.x
            height = rect.beginResize.y
        }
    }

    function resetResize(mouse) {
        rect.beginDrag = Qt.point(rect.x, rect.y)
        rect.beginResize = Qt.point(rect.width, rect.height);
        rect.Drag.hotSpot = Qt.point(mouse.x, mouse.y)
        rect.z = 3

        resizeBegin(rect.Drag)
    }

    function releaseResize() {
        if (!rect.caught) {
            resizeBackAnimX.from = rect.width;
            resizeBackAnimX.to = beginResize.x;
            resizeBackAnimY.from = rect.height;
            resizeBackAnimY.to = beginResize.y;
            resizeBackAnim.start()
        } else {
            rect.Drag.drop()
            rect.z = 2
        }
    }

    /* RESIZE ANCHORS */
    Repeater {
        model: [
            DirectionFlags.RIGHT,
            DirectionFlags.LEFT,
            DirectionFlags.TOP,
            DirectionFlags.BOTTOM,

            DirectionFlags.RIGHT | DirectionFlags.TOP,
            DirectionFlags.RIGHT | DirectionFlags.BOTTOM,
            DirectionFlags.LEFT | DirectionFlags.TOP,
            DirectionFlags.LEFT | DirectionFlags.BOTTOM
        ]

        ResizeAnchor {
            required property int modelData
            direction: modelData
        }
    }

    /* ACTUAL DATA */

    Text {
        font.pixelSize: 20
        text: model.title
        color: "#FFFFFF"

        anchors.fill: parent

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }
}
