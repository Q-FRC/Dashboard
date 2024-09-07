import QtQuick
import QtQuick.Controls

import QFRCDashboard

ApplicationWindow {
    width: Constants.width
    height: Constants.height
    visible: true
    title: qsTr("Hello World")

    menuBar: MenuBar {
        Menu {
            title: qsTr("&Widgets")
            Action {
                text: qsTr("&New Widget")
                onTriggered: screen.currentTab().add("Test")
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

