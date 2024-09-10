import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs

import QFRCDashboard

Dialog {
    width: 500
    height: 500

    anchors.centerIn: parent

    function openUp() {
        open()
    }

    ListView {
        id: listView
        clip: true
        anchors.fill: parent
        model: topics

        focus: true

        delegate: ItemDelegate {
            height: 30
            width: 450

            highlighted: ListView.isCurrentItem
            onClicked: ListView.view.currentIndex = index

            Text {
                clip: true
                anchors.fill: parent

                text: name
                font.pixelSize: 17
                color: "#FFFFFF"
            }
        }
    }
}
