import QtCore
import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs

import QtQuick.Controls.Universal

import QFRCDashboard

ApplicationWindow {
    id: window
    width: Constants.width
    height: Constants.height
    visible: true
    title: conn.title

    flags: Qt.FramelessWindowHint | Qt.Window

    Universal.theme: settings.theme === "light" ? Universal.Light : Universal.Dark
    Universal.accent: accents.qml(
                          settings.accent) // "qml" is the Universal Theme accent. Affects checkboxes, etc.

    property string filename: ""

    function resetScalar() {
        Constants.scalar = Math.sqrt(
                    Math.min(width / Constants.width,
                             height / Constants.height)) * settings.scale
    }

    function dsResize() {
        if (settings.resizeToDS) {
            console.debug("DS Resize")

            height = platformHelper.screenHeight() - 234
            width = platformHelper.screenWidth()

            // TODO: test on windows & verify geometry
            // check if it works with scaling as well
            x = 0
            y = 0
        }
    }

    onWidthChanged: {
        resetScalar()
    }

    onHeightChanged: {
        resetScalar()
    }

    // Dialogs
    AccentEditor {
        id: accentEditor
    }

    AboutDialog {
        id: about
    }

    NotificationPopup {
        id: notif

        x: parent.width - width - 10
        y: parent.height - height - 10
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

        onAccepted: saveAs()
    }

    function save() {
        if (filename === "")
            return saveDialog.open()

        tlm.save(filename)
    }

    function saveAs() {
        filename = saveDialog.selectedFile

        tlm.save(filename)
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

        onAccepted: load()
    }

    function load() {
        filename = loadDialog.selectedFile
        tlm.load(filename)
    }

    /** SERVER SETTINGS */
    SettingsDialog {
        id: settingsDialog
    }

    /** REMOTE LAYOUTS */
    MessageDialog {
        id: fail
        buttons: MessageDialog.Ok
        title: "Error"
        text: "You must be connected to a robot to download remote layouts."

        modality: Qt.WindowModal
    }

    RemoteLayoutsDialog {
        id: remoteLayouts
    }

    /** TITLE BAR */
    TitleBar {
        id: titleBar

        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }

        onMinimize: window.visibility = Window.Minimized
        onMaximize: {
            if (window.visibility === Window.Maximized) {
                window.visibility = Window.Windowed
            } else {
                window.visibility = Window.Maximized
            }
        }
        onClose: window.close()
        onBeginDrag: window.startSystemMove()
    }

    /** MENU BAR */
    MenuBar {
        id: menubar
        contentWidth: parent.width

        anchors {
            top: titleBar.bottom
            left: parent.left
            right: parent.right
        }

        Menu {
            contentWidth: 175
            title: qsTr("&File")
            Action {
                text: qsTr("&Save")
                onTriggered: save()
                shortcut: "Ctrl+S"
            }
            Action {
                text: qsTr("Save &As")
                onTriggered: saveDialog.open()
                shortcut: "Ctrl+Shift+S"
            }
            Action {
                text: qsTr("&Open...")
                onTriggered: loadDialog.open()
                shortcut: "Ctrl+O"
            }
            Menu {
                title: qsTr("&Recent Files...")
                Repeater {
                    model: settings.recentFiles

                    delegate: MenuItem {
                        text: qsTr("&" + index + ". " + platformHelper.baseName(
                                       modelData))
                        onTriggered: {
                            if (modelData === "" || modelData === null)
                                return
                            tlm.clear()
                            tlm.load(modelData)
                        }
                    }
                }
            }
            Action {
                text: qsTr("Remote &Layouts...")
                onTriggered: remoteLayouts.openDialog()
                shortcut: "Ctrl+L"
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
                text: qsTr("Configu&re Tab")
                onTriggered: screen.configTab()
                shortcut: "Ctrl+R"
            }
        }

        Menu {
            title: qsTr("&Edit")
            Action {
                text: qsTr("&Paste Widget")
                onTriggered: screen.paste()
                shortcut: "Ctrl+V"
            }

            Action {
                text: qsTr("&Settings")
                shortcut: "Ctrl+,"
                onTriggered: settingsDialog.openDialog()
            }
        }

        Menu {
            title: qsTr("&About")
            MenuBarItem {
                text: qsTr("&About")
                onTriggered: about.open()
            }
        }
    }

    /** THE REST */
    Component.onCompleted: {
        Constants.setTheme(settings.theme)
        Constants.setAccent(settings.accent)

        resetScalar()
        settings.scaleChanged.connect(resetScalar)

        dsResize()
        settings.resizeToDSChanged.connect(dsResize)

        if (settings.loadRecent && settings.recentFiles.length > 0) {
            filename = settings.recentFiles[0]
            if (filename === "" || filename === null)
                return
            tlm.load(filename)
        }
    }

    MainScreen {
        id: screen
        anchors {
            top: menubar.bottom
            left: parent.left
            right: parent.right
            bottom: toolbar.top
        }
    }

    ToolBar {
        id: toolbar

        anchors {
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }

        implicitHeight: 30 * Constants.scalar
        Text {
            anchors.fill: parent

            text: "Status: " + conn.status
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter

            leftPadding: 18 * Constants.scalar
            color: Constants.palette.text
            font.pixelSize: 16 * Constants.scalar
        }
    }

    /* RESIZE ANCHORS */
    Repeater {
        model: [Qt.RightEdge, Qt.LeftEdge, Qt.TopEdge, Qt.BottomEdge, Qt.RightEdge
            | Qt.TopEdge, Qt.RightEdge | Qt.BottomEdge, Qt.LeftEdge
            | Qt.TopEdge, Qt.LeftEdge | Qt.BottomEdge]

        ResizeAnchor {
            required property int modelData
            direction: modelData

            mouseArea.onPressed: window.startSystemResize(direction)
            mouseArea.drag.target: null

            divisor: 80 / Constants.scalar
        }
    }
}
