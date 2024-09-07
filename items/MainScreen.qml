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

    // GRIDLAYOUT
    // WITH REPEATER
    GridLayout {
        id: grid
        rows: 4
        columns: 4

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

                z: 1
            }
        }

        Repeater {
            model: grid.rows * grid.columns

            delegate: Rectangle {
                required property int modelData

                color: Constants.bg
                z: 0
                border {
                    color: "gray"
                    width: 2
                }

                Layout.row: modelData % grid.rows
                Layout.column: modelData / grid.columns

                Layout.preferredWidth: grid.prefWidth(this)
                Layout.preferredHeight: grid.prefHeight(this)

                Component.onCompleted: {
                    Layout.minimumWidth = grid.prefWidth(this)
                    Layout.minimumHeight = grid.prefHeight(this)

                    console.log(width + " " + height)
                    console.log(Layout.row + " " + Layout.column)
                }
            }
        }
    }
}
