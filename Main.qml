import QtQuick
import QtQuick.Controls

import QFRCDashboard

ApplicationWindow {
    width: Constants.width
    height: Constants.height
    visible: true
    title: qsTr("QFRCDashboard")

    menuBar: MenuBar {
        Menu {
            title: qsTr("&Tab")
            Action {
                text: qsTr("&New Tab")
                onTriggered: screen.newTab()
                shortcut: "Ctrl+T"
            }

            Action {
                text: qsTr("Tab &Size")
                onTriggered: screen.tabSize()
                shortcut: "Ctrl+S"
            }

            Action {
                text: qsTr("&Rename Tab")
                onTriggered: screen.renameTab()
                shortcut: "Ctrl+R"
            }
        }
    }

    MainScreen {
        id: screen
        anchors.fill: parent
    }
}

