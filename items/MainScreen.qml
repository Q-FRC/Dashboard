import QtCore
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 6.6
import QtQuick.Dialogs

import QFRCDashboard

Rectangle {
    id: mainScreen
    width: Constants.width
    height: Constants.height
    color: Constants.bg

    property string filename: ""
    property bool readyDragging

    function openConf(item) {
        widgetConf.openUp(item)
    }

    Component.onCompleted: {
        if (settings.loadRecent && !settings.recentFiles.empty) {
            filename = settings.recentFiles[0]
            tlm.load(filename)
        }
    }

    function drag(pos, fromList) {
        if (currentTab() !== null) {
            let w = currentTab().latestWidget
            w.x = pos.x
            w.y = pos.y - (fromList ? tabs.height : 0)

            w.width = 1
            w.height = 1

            w.visible = false

            if (!readyDragging) {
                w.dragArea.drag.target = w
                readyDragging = true

                mainScreen.z = 3
            }
            w.resizeBegin(w.Drag)
        }
    }

    function drop(pos) {
        if (currentTab() !== null) {
            let w = currentTab().latestWidget
            if (!w.caught) {
                w.cancelDrag()
                currentTab().removeLatest()
            } else {
                let p = currentTab().gridHandler.occupied()
                if (p.x === -1 || p.y === -1) {
                    w.cancelDrag()
                    currentTab().removeLatest()
                } else {
                    w.mrow = p.x
                    w.mcolumn = p.y

                    w.z = 2
                    w.visible = true
                    w.cancelDrag()
                }
            }
        }
    }


    TopicView {
        id: tv

        onAddWidget: (title, topic, type) => {
                         currentTab().add(title, topic, type)
                     }

        anchors {
            left: parent.left
            leftMargin: -(parent.width / 3)

            top: parent.top
            bottom: parent.bottom
        }

        onOpen: {
            menuAnim.from = -(parent.width / 3)
            menuAnim.to = 0
            menuAnim.start()
        }

        onClose: {
            menuAnim.to = -(parent.width / 3)
            menuAnim.from = 0
            menuAnim.start()
        }

        onDragging: pos => drag(this, pos);

        onDropped: pos => drop(this, pos);
    }

    TopicView {
        id: cl

        isCamera: true

        onAddCamera: (name, source, urls) => {
                         currentTab().addCamera(name, source, urls)
                     }

        anchors {
            right: parent.right
            rightMargin: -(parent.width / 3)

            top: parent.top
            bottom: parent.bottom
        }

        onOpen: {
            menuAnim.from = -(parent.width / 3)
            menuAnim.to = 0
            menuAnim.start()
        }

        onClose: {
            menuAnim.to = -(parent.width / 3)
            menuAnim.from = 0
            menuAnim.start()
        }

        onDragging: pos => drag(this, pos)

        onDropped: pos => drop(this, pos)
    }

    TabNameDialog {
        id: tabNameDialog
    }

    TabNameDialog {
        id: tabRenameDialog
    }

    TabSizeDialog {
        id: tabSizeDialog
    }

    WidgetConfig {
        id: widgetConf
    }

    /** SAVE */
    FileDialog {
        id: saveDialog
        currentFolder: StandardPaths.writableLocation(
                           StandardPaths.HomeLocation)
        fileMode: FileDialog.SaveFile
        defaultSuffix: "json"
        selectedNameFilter.index: 0
        nameFilters: ["JSON files (*.json)", "All files (*)"]
    }

    function save() {
        if (filename === "")
            return saveAsAction()

        tlm.save(filename)
    }

    function saveAs() {
        filename = saveDialog.selectedFile

        tlm.save(filename)
    }

    function saveAsAction() {
        saveDialog.accepted.connect(saveAs)
        saveDialog.open()
    }

    /** LOAD */
    FileDialog {
        id: loadDialog
        currentFolder: StandardPaths.writableLocation(
                           StandardPaths.HomeLocation)
        fileMode: FileDialog.OpenFile
        defaultSuffix: "json"
        selectedNameFilter.index: 0
        nameFilters: ["JSON files (*.json)", "All files (*)"]
    }

    function load() {
        filename = loadDialog.selectedFile
        tlm.load(filename)
    }

    function loadAction() {
        loadDialog.accepted.connect(load)
        loadDialog.open()
    }

    /** TAB SETTINGS */
    function addTab() {
        tabNameDialog.accepted.disconnect(addTab)
        tlm.add(tabNameDialog.tabName.text)
        swipe.setCurrentIndex(swipe.count - 1)
    }

    function newTab() {
        tabNameDialog.accepted.connect(addTab)
        tabNameDialog.openUp("")
    }

    function tabRename() {
        tabRenameDialog.accepted.disconnect(tabRename)
        currentTab().setName(tabRenameDialog.tabName.text)
    }

    function renameTab() {
        tabRenameDialog.accepted.connect(tabRename)
        tabRenameDialog.openUp(currentTab().name())
    }

    function setSize() {
        tabSizeDialog.accepted.disconnect(setSize)
        currentTab().setSize(tabSizeDialog.rowValue.value,
                             tabSizeDialog.columnValue.value)
    }

    function tabSize() {
        tabSizeDialog.accepted.connect(setSize)
        tabSizeDialog.openUp(currentTab().rows(), currentTab().cols())
    }

    function currentTab() {
        return swipe.currentItem
    }

    /** CLOSE TAB */
    MessageDialog {
        id: tabClose
        title: "Close Tab?"
        text: "Are you sure you want to close this tab?"
        buttons: MessageDialog.Yes | MessageDialog.No

        onAccepted: {
            tlm.remove(swipe.currentIndex)
        }
    }

    function closeTab() {
        tabClose.open()
    }

    /** SERVER SETTINGS */
    ServerDialog {
        id: serverDialog
    }

    function serverSettings() {
        serverDialog.open()
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

                onCopying: pos => drag(pos, false)

                onDropped: pos => drop(pos)
            }
        }
    }

    TabBar {
        id: tabs

        anchors {
            top: parent.top
            left: tv.right
            right: cl.left
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
