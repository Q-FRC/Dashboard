import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 6.6

import Qt.labs.qmlmodels

import QFRCDashboard

Rectangle {
    width: Constants.width
    height: Constants.height
    color: Constants.bg

    function add(title, topic, type) {
        twm.add(title, topic, type)
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
            return grid.height / grid.rows
        }

        function prefWidth(item) {
            return colWidth() * item.Layout.columnSpan
        }

        function prefHeight(item) {
            return rowWidth() * item.Layout.rowSpan
        }

        Repeater {
            model: twm

            delegate: DelegateChooser {
                id: chooser
                role: "type"
                DelegateChoice {
                    roleValue: "int"
                    IntWidget {


                        Layout.row: model.row
                        Layout.column: model.column
                        Layout.rowSpan: model.rowSpan
                        Layout.columnSpan: model.colSpan

                        Layout.margins: 8

                        Layout.preferredWidth: grid.prefWidth(this)
                        Layout.preferredHeight: grid.prefHeight(this)
                    }
                }
                DelegateChoice {
                    roleValue: "string"
                    TextWidget {


                        Layout.row: model.row
                        Layout.column: model.column
                        Layout.rowSpan: model.rowSpan
                        Layout.columnSpan: model.colSpan

                        Layout.margins: 8

                        Layout.preferredWidth: grid.prefWidth(this)
                        Layout.preferredHeight: grid.prefHeight(this)
                    }
                }

                DelegateChoice {
                    roleValue: "double"
                    DoubleWidget {


                        Layout.row: model.row
                        Layout.column: model.column
                        Layout.rowSpan: model.rowSpan
                        Layout.columnSpan: model.colSpan

                        Layout.margins: 8

                        Layout.preferredWidth: grid.prefWidth(this)
                        Layout.preferredHeight: grid.prefHeight(this)
                    }
                }

                DelegateChoice {
                    roleValue: "bool"
                    BoolWidget {


                        Layout.row: model.row
                        Layout.column: model.column
                        Layout.rowSpan: model.rowSpan
                        Layout.columnSpan: model.colSpan

                        Layout.margins: 8

                        Layout.preferredWidth: grid.prefWidth(this)
                        Layout.preferredHeight: grid.prefHeight(this)
                    }
                }

                DelegateChoice {
                    roleValue: "dial"
                    IntDialWidget {


                        Layout.row: model.row
                        Layout.column: model.column
                        Layout.rowSpan: model.rowSpan
                        Layout.columnSpan: model.colSpan

                        Layout.margins: 8

                        Layout.preferredWidth: grid.prefWidth(this)
                        Layout.preferredHeight: grid.prefHeight(this)
                    }
                }

                DelegateChoice {
                    roleValue: "doubleDial"
                    DoubleDialWidget {


                        Layout.row: model.row
                        Layout.column: model.column
                        Layout.rowSpan: model.rowSpan
                        Layout.columnSpan: model.colSpan

                        Layout.margins: 8

                        Layout.preferredWidth: grid.prefWidth(this)
                        Layout.preferredHeight: grid.prefHeight(this)
                    }
                }

                DelegateChoice {
                    roleValue: "color"
                    ColorWidget {


                        Layout.row: model.row
                        Layout.column: model.column
                        Layout.rowSpan: model.rowSpan
                        Layout.columnSpan: model.colSpan

                        Layout.margins: 8

                        Layout.preferredWidth: grid.prefWidth(this)
                        Layout.preferredHeight: grid.prefHeight(this)
                    }
                }
            }
        }

        GridHandler {
            id: rep
        }
    }
}
