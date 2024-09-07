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
            }
        }

        Repeater {
            model: grid.rows * grid.columns

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

                DropArea {
                    anchors.fill: parent
                    onEntered: (drag) => {
                                   if (twm.cellOccupied(parent.Layout.row, parent.Layout.column) &&
                                       !(parent.Layout.column === drag.source.mcolumn && parent.Layout.row === drag.source.mrow)) {
                                       drag.source.caught = false;
                                       parent.border.color = "red"
                                   } else {
                                       drag.source.caught = true;
                                       parent.border.color = "light green"
                                   }
                               }
                    onExited: {
                        drag.source.caught = false;
                        parent.border.color = "gray"
                    }
                    onDropped: (drag) => {
                                   drag.source.mrow = parent.Layout.row
                                   drag.source.mcolumn = parent.Layout.column
                                   drag.source.Layout.row = parent.Layout.row
                                   drag.source.Layout.column = parent.Layout.column

                                   drag.accept()

                                   parent.border.color = "gray"

                                   drag.source.anchors.centerIn = delRect
                               }
                }
            }
        }
    }
}
