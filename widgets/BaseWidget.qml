import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15

import QFRCDashboard 1.0
import DirectionFlags 1.0

Rectangle {
    id: rect
    width: 100
    height: 100
    z: 2

    property int item_titleFontSize: 20

    property alias titleField: titleField

    color: Constants.widgetBg

    Drag.active: dragArea.drag.active

    signal resizeBegin(var drag)
    signal resizeEnd(var drag)
    signal dragEnd(var drag)
    signal cancelDrag()

    onResizeBegin: (drag) => {
                       drag.source = this
                       rep.beginResize(drag)
                   }

    onResizeEnd: (drag) => {
                     drag.source = this
                     rep.endResize(drag)
                 }

    onDragEnd: (drag) => {
                   let source = Qt.rect(drag.source.mcolumn, drag.source.mrow, drag.source.mcolumnSpan, drag.source.mrowSpan)
                   rep.intersectionCheck(drag, source)
               }

    onCancelDrag: rep.fullCancelDrag()

    property point beginDrag
    property rect beginResize

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

    Menu {
        id: rcMenu

        MenuItem {
            text: "Delete Widget"
            onTriggered: twm.remove(model.row, model.column)
        }

        MenuItem {
            text: "Configure"
            onTriggered: openConf(rcMenu.parent)
        }
    }

    MouseArea {
        id: dragArea
        z: 0

        acceptedButtons: Qt.AllButtons

        anchors {
            fill: parent

            margins: 6
        }

        drag.target: parent

        pressAndHoldInterval: 100

        onPressed: (mouse) => {
                       if (mouse.button === Qt.RightButton) {
                           drag.target = null
                           rcMenu.popup()
                       }
                       else if (mouse.button === Qt.LeftButton) {
                           drag.target = parent

                           rect.beginDrag = Qt.point(parent.x, parent.y);
                           rect.Drag.hotSpot = Qt.point(mouse.x, mouse.y)
                           parent.z = 3

                           resizeBegin(rect.Drag)
                       }
                   }

        onReleased: {
            if (!rect.caught) {
                backAnimX.from = rect.x;
                backAnimX.to = beginDrag.x;
                backAnimY.from = rect.y;
                backAnimY.to = beginDrag.y;
                backAnim.start()

                cancelDrag()
            } else {
                rect.Drag.drop()

                // dragEnd(rect.Drag)

                parent.z = 2
                cancelDrag()
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
        SmoothedAnimation { id: resizeBackAnimX; target: rect; property: "x"; duration: 250 }
        SmoothedAnimation { id: resizeBackAnimY; target: rect; property: "y"; duration: 250 }
        SmoothedAnimation { id: resizeBackAnimWidth; target: rect; property: "width"; duration: 250 }
        SmoothedAnimation { id: resizeBackAnimHeight; target: rect; property: "height"; duration: 250 }

        onFinished: {
            width = rect.beginResize.width
            height = rect.beginResize.height
            x = rect.beginResize.x
            y = rect.beginResize.y
        }
    }

    function resetResize(mouse) {
        rect.beginDrag = Qt.point(rect.x, rect.y)
        rect.beginResize = Qt.rect(rect.x, rect.y, rect.width, rect.height);
        rect.Drag.hotSpot = Qt.point(mouse.x, mouse.y)
        rect.z = 3

        resizeBegin(rect.Drag)
    }

    function releaseResize() {
        if (!rect.caught) {
            resizeBackAnimX.from = rect.x;
            resizeBackAnimX.to = beginResize.x;
            resizeBackAnimY.from = rect.y;
            resizeBackAnimY.to = beginResize.y;
            resizeBackAnimWidth.from = rect.width;
            resizeBackAnimWidth.to = beginResize.width;
            resizeBackAnimHeight.from = rect.height;
            resizeBackAnimHeight.to = beginResize.height;
            resizeBackAnim.start()

            cancelDrag()
        } else {
            rect.Drag.drop()

            resizeEnd(rect.Drag)

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

    TextField {
        id: titleField
        font.pixelSize: item_titleFontSize
        font.bold: true

        text: model.title
        color: "#FFFFFF"

        anchors {
            top: parent.top
            left: parent.left
            right: parent.right

            topMargin: 8
            leftMargin: 8
            rightMargin: 8
        }

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }
}
