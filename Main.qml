import QtQuick
import QtQuick.Controls

import QFRCDashboard

ApplicationWindow {
    id: window
    width: Constants.width
    height: Constants.height
    visible: true
    title: qsTr("QFRCDashboard")

    menuBar: MenuBar {
        Menu {
            title: qsTr("&NT")
            Action {
                text: qsTr("&Server Settings...")
                onTriggered: screen.serverSettings()
                shortcut: "Ctrl+E"
            }
        }

        Menu {
            title: qsTr("&File")
            Action {
                text: qsTr("&Save")
                onTriggered: screen.save()
                shortcut: "Ctrl+S"
            }
            Action {
                text: qsTr("Save &As...")
                onTriggered: screen.saveAsAction()
                shortcut: "Ctrl+Shift+S"
            }
            Action {
                text: qsTr("&Open...")
                onTriggered: screen.loadAction()
                shortcut: "Ctrl+O"
            }
        }

        Menu {
            title: qsTr("&Tab")
            Action {
                text: qsTr("&New Tab")
                onTriggered: screen.newTab()
                shortcut: "Ctrl+T"
            }

            Action {
                text: qsTr("&Close Tab")
                onTriggered: screen.closeTab()
                shortcut: "Ctrl+W"
            }

            Action {
                text: qsTr("Tab &Size")
                onTriggered: screen.tabSize()
                shortcut: "Ctrl+R"
            }

            Action {
                text: qsTr("&Rename Tab")
                onTriggered: screen.renameTab()
                shortcut: "Ctrl+N"
            }
        }
    }

    MainScreen {
        id: screen
        anchors.fill: parent
    }
}

