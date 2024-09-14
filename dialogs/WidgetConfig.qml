import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick.Layouts

import Qt.labs.qmlmodels
import QFRCDashboard

Dialog {
    id: widgetConf
    anchors.centerIn: parent
    width: parent.width / 2
    height: parent.width / 1.5

    property var item

    function openUp(item) {
        lm.clear()
        for (var p in item) {
            if(p.startsWith("item_") && typeof item[p] !== "function") {
                lm.append({"name": p, "type": MetaObjectHelper.typeName(item, p), "itemValue": item[p]})
            }
        }

        this.item = item

        open()
    }

    ListModel {
        id: lm
        dynamicRoles: true
    }

    function displayText(text) {
        const result = text.substring(5).replace(/([A-Z])/g, " $1");
        return result.charAt(0).toUpperCase() + result.slice(1);
    }

    function getValues() {
        for (let i = 0; i < listView.count; ++i) {
            let idx = lm.get(i)
            item[idx.name] = idx.itemValue
        }
    }

    ListView {
        anchors {
            top: parent.top
            bottom: buttonBox.bottom
            left: parent.left
            right: parent.right

            margins: 8
        }

        id: listView

        clip: true

        boundsBehavior: Flickable.StopAtBounds

        model: lm
        delegate: DelegateChooser {
            role: "type"

            // TODO: may want to find a way to avoid all this repeat code
            DelegateChoice {
                roleValue: "QString"

                RowLayout {
                    function getValue() {
                        return txt.text
                    }

                    clip: true
                    width: parent.width

                    uniformCellSizes: true

                    Label {
                        Layout.fillWidth: true

                        text: displayText(model.name)
                        font.pixelSize: 15
                        color: "white"
                    }

                    TextField {
                        id: txt
                        Layout.fillWidth: true

                        font.pixelSize: 15
                        text: model.itemValue

                        onTextEdited: model.itemValue = text;
                    }
                }
            }

            DelegateChoice {
                roleValue: "int"

                RowLayout {
                    function getValue() {
                        return sb.value
                    }

                    clip: true
                    width: parent.width

                    uniformCellSizes: true

                    Label {
                        Layout.fillWidth: true

                        text: displayText(model.name)
                        font.pixelSize: 15
                        color: "white"
                    }

                    SpinBox {
                        to: 1000
                        id: sb

                        Layout.fillWidth: true

                        font.pixelSize: 15
                        value: model.itemValue

                        onValueModified: model.itemValue = value
                    }
                }
            }

            DelegateChoice {
                roleValue: "double"

                RowLayout {
                    function getValue() {
                        return sb.value / 100.0
                    }

                    clip: true
                    width: parent.width

                    uniformCellSizes: true

                    Label {
                        Layout.fillWidth: true

                        text: displayText(model.name)
                        font.pixelSize: 15
                        color: "white"
                    }

                    DoubleSpinBox {
                        to: 1000 * 100

                        id: dsb
                        font.pixelSize: 15
                        Layout.fillWidth: true

                        value: model.itemValue * 100.0

                        onValueModified: model.itemValue = value / 100.0
                    }
                }
            }
        }
    }

    DialogButtonBox {
        anchors {
            bottom: parent.bottom
            left: parent.left
            right: parent.right

            margins: 8
        }

        id: buttonBox
        standardButtons: DialogButtonBox.Ok | DialogButtonBox.Cancel

        onAccepted: {
            getValues()
            widgetConf.accept()
        }

        onRejected: {
            widgetConf.reject()
        }
    }
}
