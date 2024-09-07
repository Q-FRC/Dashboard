import QtQuick 2.15

import QFRCDashboard

Rectangle {
    width: 100
    height: 100
    color: Constants.widgetBg

    Text {
        font.pixelSize: 20
        text: model.title
        color: "#FFFFFF"
    }
}
