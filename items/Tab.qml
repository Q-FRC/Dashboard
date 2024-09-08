import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 6.6

import QFRCDashboard

Rectangle {
    width: Constants.width
    height: Constants.height
    color: Constants.bg

    function add(title) {
        twm.add(title)
    }

    TabWidgetsModel {
        id: twm

        rows: 3
        cols: 3
    }

    GridLayout {
        id: grid
        rows: 3
        columns: 3

        anchors.fill: parent

        columnSpacing: 0
        rowSpacing: 0

        function colWidth() {
            return grid.width / grid.columns
        }

        function rowWidth() {
            return grid.height / grid.rows;
        }

        function prefWidth(item){
            return colWidth() * item.Layout.columnSpan
        }

        function prefHeight(item){
            return rowWidth() * item.Layout.rowSpan
        }

        Repeater {
            model: twm

            delegate: TextWidget {
                Layout.row: model.row
                Layout.column: model.column
                Layout.rowSpan: model.rowSpan
                Layout.columnSpan: model.colSpan

                Layout.margins: 8

                Layout.preferredWidth: grid.prefWidth(this)
                Layout.preferredHeight: grid.prefHeight(this)

                z: 2

                onResizeBegin: (drag) => {
                                   drag.source = this
                                   rep.beginDrag(drag)
                               }
            }
        }

        Repeater {
            id: rep
            model: grid.rows * grid.columns

            signal dragBegin(var drag, var valid)

            function beginDrag(drag) {
                let valid = true
                for (var x in validResize) {
                    if (x === false) valid = false
                }

                dragBegin(drag, valid)
                drag.source.caught = valid
            }

            property list<bool> validResize

            delegate: Rectangle {
                id: delRect
                required property int modelData

                color: Constants.bg
                z: 1
                border {
                    color: "gray"
                    width: 2
                }

                Layout.row: modelData % grid.rows
                Layout.column: modelData / grid.columns

                Layout.preferredWidth: grid.prefWidth(this)
                Layout.preferredHeight: grid.prefHeight(this)

                function valueInRange(value, min, max) {
                    return (value >= min) && (value <= max)
                }

                function intersects(A, B) {
                    let xOverlap = valueInRange(A.x, B.x, B.x + B.width) ||
                        valueInRange(B.x, A.x, A.x + A.width);

                    let yOverlap = valueInRange(A.y, B.y, B.y + B.height) ||
                        valueInRange(B.y, A.y, A.y + A.height);

                    return xOverlap && yOverlap;
                }

                function rectDrag(drag) {
                    let sourceRect = Qt.rect(drag.source.x, drag.source.y, drag.source.width, drag.source.height)
                    let myRect = Qt.rect(x, y, width, height)

                    if (intersects(sourceRect, myRect)) {
                        drop.dragEnter(drag)
                    } else {
                        border.color = "gray"
                        border.width = 2
                    }
                }

                Component.onCompleted: {
                    rep.dragBegin.connect(rectDrag)
                }

                DropArea {
                    id: drop
                    anchors.fill: parent

                    function validSpot(drag) {
                        return twm.cellOccupied(parent.Layout.row, parent.Layout.column, parent.Layout.rowSpan, parent.Layout.columnSpan) &&
                                !(parent.Layout.column === drag.source.mcolumn && parent.Layout.row === drag.source.mrow)
                    }

                    function validResize(drag) {
                        return twm.cellOccupied(parent.Layout.row, parent.Layout.column, parent.Layout.rowSpan, parent.Layout.columnSpan) &&
                                !(parent.Layout.columnSpan === drag.source.mcolumnSpan && parent.Layout.rowSpan === drag.source.mrowSpan)
                    }

                    function dragEnter(drag, valid) {
                        parent.border.width = 5

                        rep.validResize[modelData] = validResize(drag)
                        parent.border.color = valid ? "light green" : "red"
                    }

                    onEntered: (drag) => {
                                   {
                                       parent.border.width = 5

                                       if (validSpot(drag)) {
                                           drag.source.caught = false
                                           parent.border.color = "red"
                                       } else {
                                           drag.source.caught = true
                                           parent.border.color = "light green"
                                       }
                                   }
                               }

                    onExited: {
                        drag.source.caught = false;
                        parent.border.color = "gray"
                        parent.border.width = 2
                    }
                    onDropped: (drag) => {
                                   drag.source.mrow = parent.Layout.row
                                   drag.source.mcolumn = parent.Layout.column
                                   drag.source.Layout.row = parent.Layout.row
                                   drag.source.Layout.column = parent.Layout.column

                                   drag.accept()

                                   parent.border.color = "gray"
                                   parent.border.width = 2
                               }
                }
            }
        }
    }
}
