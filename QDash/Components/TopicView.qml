// SPDX-FileCopyrightText: Copyright 2026 crueter
// SPDX-License-Identifier: GPL-3.0-or-later

import Carboxyl.Contour

import QDash.Widgets
import QtQuick
import QtQuick.Controls

Row {
    id: tv

    signal addWidget(string name, string topic, string type)
    signal dragging(point pos)
    signal dropped(point pos)
    signal animationFinished(bool open)

    Rectangle {
        id: topicView

        color: palette.base
        height: parent.height
        radius: 10
        width: parent.width

        border {
            color: palette.windowText
            width: 3
        }

        CarboxylLabeledTextField {
            id: search

            font.pixelSize: 16
            label: "Search"

            onTextEdited: topicsSorted.setFilterWildcard("*" + text + "*")

            anchors {
                left: parent.left
                margins: 10
                right: parent.right
                top: parent.top
                topMargin: 18
            }
        }

        QDashScrollView {
            id: scroll

            sensitivity: 0.45

            anchors {
                bottom: parent.bottom
                left: parent.left
                margins: 10
                right: parent.right
                top: search.bottom
            }

            contentWidth: treeView.implicitWidth
            contentHeight: treeView.implicitHeight

            // modified from Qt's example TreeView
            TreeView {
                id: treeView

                clip: true
                model: topicsSorted

                interactive: false
                implicitWidth: scroll.availableWidth
                implicitHeight: contentHeight

                selectionModel: ItemSelectionModel {}

                delegate: Item {
                    required property int column
                    required property bool current
                    required property int depth
                    required property bool expanded
                    required property int hasChildren
                    readonly property real indentation: 20

                    // Rotate indicator when expanded by the user
                    // (requires TreeView to have a selectionModel)
                    property Animation indicatorAnimation: NumberAnimation {
                        duration: 100
                        easing.type: Easing.OutQuart
                        from: expanded ? 0 : 90
                        property: "rotation"
                        target: indicator
                        to: expanded ? 90 : 0
                    }
                    required property bool isTreeNode
                    readonly property real padding: 5
                    required property int row

                    // Assigned to by TreeView:
                    required property TreeView treeView

                    // implicitWidth: padding + label.x + label.implicitWidth + padding
                    implicitHeight: label.implicitHeight * 1.5
                    implicitWidth: topicView.width - 20

                    TableView.onPooled: indicatorAnimation.complete()
                    TableView.onReused: if (current)
                        indicatorAnimation.start()
                    onExpandedChanged: indicator.rotation = expanded ? 90 : 0

                    DragHandler {
                        id: dh

                        property bool ready: false

                        function drag() {
                            let global = mapToItem(topicView, centroid.position)
                            if (!topicView.contains(global)) {
                                if (!ready) {
                                    addWidget(model.name, model.topic, model.type)

                                    ready = true
                                }

                                dragging(mapToItem(mainScreen, centroid.position))
                            }
                        }

                        enabled: model.type !== "" && WidgetTypeList.types.includes(model.type)
                        target: null

                        onActiveChanged: if (!active && ready) {
                            ready = false
                            dropped(centroid.position)
                        }
                        xAxis.onActiveValueChanged: drag()
                        yAxis.onActiveValueChanged: drag()
                    }

                    Rectangle {
                        id: background

                        anchors.fill: parent
                        color: row === treeView.currentRow ? palette.highlight : (treeView.alternatingRows && row % 2 !== 0) ? palette.base : palette.alternateBase
                    }

                    Label {
                        id: indicator

                        anchors.verticalCenter: parent.verticalCenter
                        font.pixelSize: 16
                        text: "▶"
                        visible: isTreeNode && hasChildren
                        x: padding + (depth * indentation)

                        TapHandler {
                            onSingleTapped: {
                                let index = treeView.index(row, column)
                                treeView.selectionModel.setCurrentIndex(index, ItemSelectionModel.NoUpdate)
                                treeView.toggleExpanded(row)
                            }
                        }
                    }

                    Label {
                        id: label

                        anchors.verticalCenter: parent.verticalCenter
                        clip: true
                        font.pixelSize: 16
                        text: model.name
                        width: parent.width - padding - x - typeLabel.width
                        x: padding + (isTreeNode ? (depth + 1) * indentation : 0)
                    }

                    Label {
                        id: typeLabel

                        anchors.right: parent.right
                        anchors.rightMargin: 5
                        anchors.verticalCenter: parent.verticalCenter
                        clip: true
                        font.pixelSize: 16
                        text: model.displayType
                    }
                }
            }
        }
    }
}
