import QtQuick 2.15
import QtQuick.Controls 2.15

import QFRCDashboard 1.0
import DirectionFlags 1.0

Rectangle {
    id: resizeAnchor
    property int margin

    required property int direction

    property bool hasLeft: direction & DirectionFlags.LEFT
    property bool hasRight: direction & DirectionFlags.RIGHT
    property bool hasTop: direction & DirectionFlags.TOP
    property bool hasBottom: direction & DirectionFlags.BOTTOM

    property bool horiz: hasLeft || hasRight
    property bool vert: hasTop || hasBottom

    color: "transparent"

    anchors {
        left: !hasRight ? parent.left : undefined
        right: !hasLeft ? parent.right : undefined
        top: !hasBottom ? parent.top : undefined
        bottom: !hasTop ? parent.bottom : undefined

        leftMargin: horiz ? 0 : margin
        rightMargin: horiz ? 0 : margin
        topMargin: vert ? 0 : margin
        bottomMargin: vert ? 0 : margin
    }

    function redoMargin() {
        margin = Math.min(parent.width, parent.height) / 14

        anchors.leftMargin = horiz ? 0 : margin
        anchors.rightMargin = horiz ? 0 : margin
        anchors.topMargin = vert ? 0 : margin
        anchors.bottomMargin = vert ? 0 : margin

        if (vert) height = margin
        if (horiz) width = margin
    }

    Component.onCompleted: {
        redoMargin()
        parent.onWidthChanged.connect(redoMargin)
        parent.onHeightChanged.connect(redoMargin)
    }

    MouseArea {
        id: mouseArea
        z: 1

        anchors.fill: parent

        cursorShape: {
            if (horiz && vert) {
                if ((hasLeft && hasTop) || (hasRight && hasBottom)) {
                    return Qt.SizeFDiagCursor
                } else {
                    return Qt.SizeBDiagCursor
                }
            } else if (horiz) {
                return Qt.SizeHorCursor
            } else {
                return Qt.SizeVerCursor
            }
        }

        drag.target: parent
        drag.axis: {
            if (horiz && vert) {
                return Drag.XAndYAxis
            } else if (horiz) {
                return Drag.XAxis
            } else if (vert) {
                return Drag.YAxis
            }
        }

        onPressed: (mouse) => resetResize(mouse)

        onReleased: releaseResize()

        onMouseXChanged: {
            if (drag.active) {
                if (hasRight) {
                    parent.parent.width = parent.parent.width + mouseX
                } else if (hasLeft) {
                    parent.parent.width = parent.parent.width - mouseX
                    parent.parent.x = parent.parent.x + mouseX
                }

                resizeBegin(rect.Drag)
            }
        }

        onMouseYChanged: {
            if (drag.active) {
                if (hasBottom) {
                    parent.parent.height = parent.parent.height + mouseY
                } else if (hasTop) {
                    parent.parent.height = parent.parent.height - mouseY
                    parent.parent.y = parent.parent.y + mouseY
                }

                resizeBegin(rect.Drag)
            }
        }
    }
}
