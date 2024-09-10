import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 6.6
import QtQuick.Dialogs

import QFRCDashboard

Rectangle {
    width: Constants.width
    height: Constants.height
    color: Constants.bg

    TopicView {
        id: topicView
        z: 4

        anchors {
            left: parent.left
            leftMargin: -320
            top: parent.top
            bottom: parent.bottom
        }

        width: 360
        height: parent.height

        SmoothedAnimation { id: menuAnim; target: topicView; property: "anchors.leftMargin"; duration: 500 }

        onOpen: {
            menuAnim.from = -320
            menuAnim.to = 0
            menuAnim.start()
        }

        onClose: {
            menuAnim.to = -320
            menuAnim.from = 0
            menuAnim.start()
        }
    }

    TabNameDialog {
        id: tabNameDialog
    }

    TabListModel {
        id: tlm
    }

    function addTab() {
        tabNameDialog.accepted.disconnect(addTab)
        tlm.add(tabNameDialog.tabName.text);
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
            left: topicView.right
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
