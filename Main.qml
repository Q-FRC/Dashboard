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
        }
    }

    MainScreen {
        id: screen
        anchors.fill: parent
    }
}

