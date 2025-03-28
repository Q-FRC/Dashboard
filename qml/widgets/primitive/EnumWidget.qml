import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts
import QtQuick.Shapes 2.15

import QFRCDashboard

BaseWidget {
    id: widget
    property string item_topic

    // @disable-check M311
    property var item_shape: "Rectangle"

    property list<string> shapeChoices: ["Rectangle", "Circle", "Triangle"]

    property string itemValue

    property list<var> item_colorMap: []

    Menu {
        id: switchMenu
        title: "Switch Widget..."

        MenuItem {
            text: "Text"
            onTriggered: {
                model.type = "string"
            }
        }

        MenuItem {
            text: "Text Display"
            onTriggered: {
                model.type = "textDisplay"
            }
        }
    }

    function colorFromMap(value) {
        for (var i = 0; i < item_colorMap.length; ++i) {
            let obj = item_colorMap[i]

            if (obj["Value"] === value) {
                return obj["Color"]
            }
        }

        return "#000000"
    }

    function setColor() {
        shape.itemColor = colorFromMap(itemValue)
        shape.itemShape = item_shape
        shape.setColor()
    }

    function updateTopic(ntTopic, ntValue) {
        if (ntTopic === item_topic) {
            itemValue = ntValue
            setColor()
        }
    }

    Component.onCompleted: {
        topicStore.topicUpdate.connect(updateTopic)
        item_topic = model.topic

        rcMenu.addMenu(switchMenu)
    }

    Component.onDestruction: {
        if (topicStore !== null) {
            topicStore.topicUpdate.disconnect(updateTopic)
            topicStore.unsubscribe(item_topic)
        }
    }

    onItem_colorMapChanged: setColor()
    onItem_shapeChanged: setColor()

    ShapeHandler {
        id: shape

        itemShape: item_shape

        anchors {
            top: titleField.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom

            margins: 10
        }
    }

    onItem_topicChanged: {
        topicStore.unsubscribe(topic)
        topicStore.subscribe(item_topic)
        model.topic = item_topic

        topicStore.forceUpdate(item_topic)
    }

    BaseConfigDialog {
        id: config

        function openDialog() {
            topicField.open()
            titleFontField.open()
            colorTable.open()
            shapeField.open()

            open()
        }

        onAccepted: {
            topicField.accept()
            titleFontField.accept()
            colorTable.accept()
            shapeField.accept()
        }

        ScrollView {
            clip: true

            contentWidth: width - 5 * Constants.scalar - effectiveScrollBarWidth

            anchors {
                top: parent.top
                bottom: parent.bottom
                left: parent.left
                right: parent.right

                topMargin: 5 * Constants.scalar

                rightMargin: 5
            }

            ColumnLayout {
                id: layout
                spacing: 12 * Constants.scalar

                anchors.fill: parent
                anchors.leftMargin: 2

                clip: true

                SectionHeader {
                    label: "Font Settings"
                }

                LabeledSpinBox {
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignTop

                    id: titleFontField

                    label: "Title Font Size"

                    bindedProperty: "item_titleFontSize"
                    bindTarget: widget
                }

                SectionHeader {
                    label: "Color Settings"
                }

                ColorTable {
                    id: colorTable

                    Layout.fillWidth: true
                    clip: true

                    label: "Color Map"

                    bindedProperty: "item_colorMap"
                    bindTarget: widget
                }

                LabeledComboBox {
                    id: shapeField

                    Layout.fillWidth: true
                    choices: shapeChoices

                    label: "Shape"

                    bindedProperty: "item_shape"
                    bindTarget: widget
                }

                SectionHeader {
                    label: "NT Settings"
                }

                LabeledTextField {
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignTop

                    id: topicField

                    label: "Topic"

                    bindedProperty: "item_topic"
                    bindTarget: widget
                }
            }
        }
    }
}
