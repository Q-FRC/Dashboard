import QtQuick
import QtQuick.Controls

import QFRCDashboard

Dialog {
    id: config

    width: 300

    header: Rectangle {
        color: Constants.accent
        topLeftRadius: 20
        topRightRadius: 20

        height: 40
        width: parent.width

        Text {
            id: txt

            text: "Configure Widget"
            font.pixelSize: 24
            font.bold: true

            color: "white"

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            anchors {
                fill: parent
                margins: 8
            }
        }
    }

    background: Rectangle {
        color: "transparent"
    }

    contentItem: Rectangle {
        color: Constants.palette.dialogBg
        radius: 20
        anchors.fill: parent
    }

    parent: Overlay.overlay
    anchors.centerIn: parent
}
