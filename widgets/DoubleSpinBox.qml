import QtQuick 2.8
import QtQuick.Controls 2.1

SpinBox {
    id: spinbox

    editable: true

    from: 0
    value: 100
    to: 1000 * 100.0
    stepSize: 100

    property string suffix: ""

    property int decimals: 2
    property real realValue: value / 100.0

    validator: DoubleValidator {
        bottom: Math.min(spinbox.from, spinbox.to)
        top:  Math.max(spinbox.from, spinbox.to)
    }

    textFromValue: function(value, locale) {
        let x = Math.round(value) / 100.

        if (String(x).includes("E")) {
            x = String(x).split("E")[0];
        }

        return x + suffix;
    }

    valueFromText: function(text, locale) {
        return Number.fromLocaleString(locale, text.replace(suffix, "")) * 100.0
    }
}
