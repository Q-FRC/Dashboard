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
        contentWidth: parent.width

        Menu {
            title: qsTr("&Settings")
            Action {
                text: qsTr("&Server Settings...")
                onTriggered: screen.serverSettings()
                shortcut: "Ctrl+E"
            }
            MenuItem {
                text: "&Load Most Recent File?"
                checkable: true
                checked: settings.loadRecent
                onCheckedChanged: settings.loadRecent = checked
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
            Menu {
                title: qsTr("&Recent Files...")
                Repeater {
                    model: settings.recentFiles

                    delegate: MenuItem {
                        text: qsTr("&" + index + ". " + modelData)
                        onTriggered: tlm.load(modelData)
                    }
                }
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

