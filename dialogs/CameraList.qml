import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs

import QFRCDashboard

Row {
    id: cl
    signal open
    signal close

    signal addWidget(string name, string source, var urls)
    signal dragging(point pos)
    signal dropped(point pos)

    function widgetAdd(name, source, urls) {
        button.text = "<<"
        close()
        addWidget(name, source, urls)
    }

    Button {
        id: button
        text: "<<"

        width: 41
        height: 41

        onClicked: {
            if (text === "<<") {
                open()
                text = ">>"
            } else {
                close()
                text = "<<"
            }
        }
    }

    Rectangle {
        id: cameraList
        width: parent.width - 40
        height: parent.height
        color: "#222222"
        border {
            color: "light grey"
            width: 3
        }

        ListView {
            id: listView
            anchors.fill: parent
            anchors.margins: 10
            clip: true

            boundsBehavior: Flickable.StopAtBounds

            model: cameras

            delegate: Item {
                DragHandler {
                    id: dh
                    target: null

                    property bool ready: false

                    onActiveChanged: if (!active && ready) {
                                         ready = false
                                         dropped(centroid.position)
                                     }

                    yAxis.onActiveValueChanged: {
                        let global = mapToItem(topicView, centroid.position)
                        if (!topicView.contains(global)) {
                            if (!ready) {
                                widgetAdd(model.name, model.source, model.urls)
                                ready = true
                            }

                            let p = mapToItem(tv, centroid.position)
                            p.x += tv.x
                            dragging(p)
                        }
                    }

                    xAxis.onActiveValueChanged: {
                        let global = mapToItem(topicView, centroid.position)
                        if (!topicView.contains(global)) {
                            if (!ready) {
                                widgetAdd(model.name, "model.topic", model.type)
                                ready = true
                            }

                            let p = mapToItem(tv, centroid.position)
                            p.x += tv.x
                            dragging(p)
                        }
                    }
                }

                implicitHeight: label.implicitHeight * 1.5

                implicitWidth: cameraList.width - 20

                Rectangle {
                    id: background
                    anchors.fill: parent
                    color: row === treeView.currentRow ? palette.highlight : "black"
                    opacity: (treeView.alternatingRows
                              && row % 2 !== 0) ? 0.3 : 0.1
                }

                Label {
                    id: label
                    x: padding + (isTreeNode ? (depth + 1) * indentation : 0)
                    anchors.verticalCenter: parent.verticalCenter
                    width: parent.width - padding - x
                    clip: true
                    text: model.name

                    font.pixelSize: 17
                }
            }
        }
    }
}
