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
            }
        }

        GridHandler {
            id: rep
        }
    }
}
