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
                id: newWidget
                text: qsTr("&New Widget")
                onTriggered: screen.add("Test")
                shortcut: "Ctrl+N"
            }
        }
    }

    MainScreen {
        id: screen
        anchors.fill: parent
    }
}

