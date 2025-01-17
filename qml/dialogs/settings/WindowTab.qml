import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import QFRCDashboard

ColumnLayout {
    spacing: 15 * Constants.scalar

    function accept() {
        console.log("Before", settings.resizeToDS)
        scale.accept()
        resize.accept()
        console.log("after", settings.resizeToDS)
    }

    function open() {
        console.log("Before", settings.resizeToDS)
        scale.open()
        resize.open()
        console.log("after", settings.resizeToDS)
    }

    LabeledDoubleSpinBox {
        Layout.fillWidth: true

        hoverEnabled: true
        id: scale
        label: "Custom Scaling Factor"

        ToolTip.visible: hovered
        ToolTip.text: "Useful for high-DPI screens, this scalar is applied on top of the existing window-size scalar."

        stepSize: 0.1
        from: 0.1
        to: 10.0

        bindTarget: settings
        bindedProperty: "scale"
    }

    LabeledCheckbox {
        id: resize
        label: "Resize to Driver Station?"

        bindTarget: settings
        bindedProperty: "resizeToDS"
    }
}
