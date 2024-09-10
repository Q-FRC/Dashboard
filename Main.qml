import QtQuick
import QtQuick.Controls

import QFRCDashboard

ApplicationWindow {
    width: Constants.width
    height: Constants.height
    visible: true
    title: qsTr("Hello World")

    TopicView {
        id: topicView
    }

    menuBar: MenuBar {
        Menu {
            title: qsTr("&Widgets")
            Action {
                text: qsTr("New &String Widget")
                onTriggered: screen.currentTab().add("Test", "string")
                shortcut: "Ctrl+S"
            }

            Action {
                text: qsTr("New &Integer Widget")
                onTriggered: screen.currentTab().add("Test", "int")
                shortcut: "Ctrl+I"
            }

            Action {
                text: qsTr("&New Widget")
                onTriggered: topicView.openUp()
                shortcut: "Ctrl+N"
            }
        }

        Menu {
            title: qsTr("&Tab")
            Action {
                text: qsTr("&New Tab")
                onTriggered: screen.newTab()
                shortcut: "Ctrl+T"
            }
        }
    }

    MainScreen {
        id: screen
        anchors.fill: parent
    }
}

