import QtQuick 2.15
import QtQuick.Controls 2.15

BaseWidget {
    TextField {
        id: textField

        text: "yoo"

        anchors {
            verticalCenter: parent.verticalCenter
            topMargin: titleField.height

            left: parent.left
            right: parent.right

            leftMargin: 10
            rightMargin: 10
        }
    }
}
