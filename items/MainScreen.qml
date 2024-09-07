import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 6.6
import QtQuick.Dialogs

import QFRCDashboard

Rectangle {
    width: Constants.width
    height: Constants.height
    color: Constants.bg

    Dialog {
        id: tabNameDialog

        anchors.centerIn: parent

        function openUp() {
            open()
            tabName.focus = true
            tabName.text = ""
        }

        Column {
            anchors.fill: parent
            spacing: 5

            Text {
                text: "Input new tab name:"
                font.pixelSize: 20
                color: "white"
            }

            TextField {
                id: tabName
                font.pixelSize: 20
                placeholderText: "New Tab"
            }

            DialogButtonBox {
                Shortcut {
                    context: Qt.WidgetWithChildrenShortcut
                    sequences: [Qt.Key_Escape]

                    onActivated: tabNameDialog.reject()
                }

                Button {
                    text: qsTr("Ok")
                    DialogButtonBox.buttonRole: DialogButtonBox.AcceptRole
                }
                Button {
                    text: qsTr("Cancel")
                    DialogButtonBox.buttonRole: DialogButtonBox.RejectRole
                }

                width: tabName.width
                font.pixelSize: 15

                onAccepted: tabNameDialog.accept()
                onRejected: tabNameDialog.reject()
            }
        }
    }

    TabListModel {
        id: tlm
    }

    function addTab() {
        tabNameDialog.accepted.disconnect(addTab)
        tlm.add(tabName.text);
        swipe.setCurrentIndex(swipe.count - 1)
    }

    function newTab() {
        tabNameDialog.accepted.connect(addTab)
        tabNameDialog.openUp()
    }

    function currentTab() {
        return swipe.currentItem
    }

    SwipeView {
        id: swipe

        z: 0

        anchors {
            top: tabs.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }

        currentIndex: tabs.currentIndex
        Repeater {
            id: swRep
            model: tlm

            Tab {
                width: swipe.width
                height: swipe.height
            }
        }
    }

    TabBar {
        id: tabs

        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }

        position: TabBar.Footer
        currentIndex: swipe.currentIndex

        Repeater {
            id: tabRep
            model: tlm

            TabButton {
                text: model.title
                font.pixelSize: 18
                width: Math.max(100, tabs.width / 6)
            }
        }
    }
}
