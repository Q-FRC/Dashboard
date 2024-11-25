import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15

import QtMultimedia

import QFRCDashboard

TextField {
    required property string label

    /** any of: string, int, double */
    property string type: "string"

    /** what property to bind to */
    required property string bindedProperty

    /** the target to bind the property to */
    required property var bindTarget

    id: textField
    font.pixelSize: 18

    color: Constants.palette.text

    function open() {
        text = bindTarget[bindedProperty]
    }

    function accept() {
        bindTarget[bindedProperty] = text
    }

    background: Rectangle {
        color: Constants.palette.bg
        width: parent.width
        border.color: Constants.palette.text
        border.width: 2
        radius: 5
    }

    Text {
        id: floatingLabel
        text: label
        color: Constants.palette.text

        font.pixelSize: 15

        anchors {
            left: textField.left
            bottom: textField.top

            bottomMargin: -4
            leftMargin: 10
        }
    }

    validator: RegularExpressionValidator {
        regularExpression: {
            switch (type) {
            case "double":
                return /^\d*\.?\d*$/;
            case "int":
                return /^[-+]?[1-9]\d*$/;
            default:
            case "string":
                return /.*/;
            }
        }
    }
}
