import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs

import QFRCDashboard

Row {
    signal open
    signal close

    signal addWidget(string name, string topic, string type)

    function widgetAdd(name, topic, type) {
        button.text = ">>"
        close()
        addWidget(name, topic, type)
    }

    Rectangle {
        id: topicView
        width: parent.width - 40
        height: parent.height
        color: "#222222"
        border {
            color: "light grey"
            width: 3
        }

        TreeView {
            id: treeView
            anchors.fill: parent
            anchors.margins: 10
            clip: true

            boundsBehavior: Flickable.StopAtBounds

            // modified from Qt's example TreeView
            selectionModel: ItemSelectionModel { }

            // The model needs to be a QAbstractItemModel
            model: topics

            delegate: Item {
                TapHandler {
                    onDoubleTapped: if (!hasChildren) widgetAdd(model.name, model.topic, model.type)
                }

                // implicitWidth: padding + label.x + label.implicitWidth + padding
                implicitHeight: label.implicitHeight * 1.5

                implicitWidth: topicView.width - 20

                readonly property real indentation: 20
                readonly property real padding: 5

                // Assigned to by TreeView:
                required property TreeView treeView
                required property bool isTreeNode
                required property bool expanded
                required property int hasChildren
                required property int depth
                required property int row
                required property int column
                required property bool current

                // Rotate indicator when expanded by the user
                // (requires TreeView to have a selectionModel)
                property Animation indicatorAnimation: NumberAnimation {
                    target: indicator
                    property: "rotation"
                    from: expanded ? 0 : 90
                    to: expanded ? 90 : 0
                    duration: 100
                    easing.type: Easing.OutQuart
                }
                TableView.onPooled: indicatorAnimation.complete()
                TableView.onReused: if (current) indicatorAnimation.start()
                onExpandedChanged: indicator.rotation = expanded ? 90 : 0

                Rectangle {
                    id: background
                    anchors.fill: parent
                    color: row === treeView.currentRow ? palette.highlight : "black"
                    opacity: (treeView.alternatingRows && row % 2 !== 0) ? 0.3 : 0.1
                }

                Label {
                    id: indicator
                    x: padding + (depth * indentation)
                    anchors.verticalCenter: parent.verticalCenter
                    visible: isTreeNode && hasChildren
                    text: "▶"

                    TapHandler {
                        onSingleTapped: {
                            let index = treeView.index(row, column)
                            treeView.selectionModel.setCurrentIndex(index, ItemSelectionModel.NoUpdate)
                            treeView.toggleExpanded(row)
                        }
                    }

                    font.pixelSize: 17
                }

                Label {
                    id: label
                    x: padding + (isTreeNode ? (depth + 1) * indentation : 0)
                    anchors.verticalCenter: parent.verticalCenter
                    width: parent.width - padding - x - typeLabel.width
                    clip: true
                    text: model.name

                    font.pixelSize: 17
                }

                Label {
                    id: typeLabel
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    clip: true
                    text: model.type

                    font.pixelSize: 17
                }
            }
        }
    }

    Button {
        id: button
        text: ">>"

        width: 40
        height: 37

        onClicked: {
            if (text === ">>") {
                open()
                text = "<<"
            } else {
                close()
                text = ">>"
            }
        }
    }
}
