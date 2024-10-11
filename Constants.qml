pragma Singleton
import QtQuick

QtObject {
    readonly property int width: 900;
    readonly property int height: 600;

    property var palette: light

    function setLight() {
        palette = light
    }

    function setDark() {
        palette = dark
    }

    property QtObject dark: QtObject {
        id: dark

        readonly property color bg: "#111111";
        readonly property color widgetBg: "#272727";

        readonly property color accent: "#ec202a"

        readonly property color tab: "#ec5a5c"
        readonly property color text: "#FFFFFF"

        readonly property color menu: "#222222"
        readonly property color menuBorder: "#AAAAAA"
        readonly property real menuBaseOpacity: 0.3
        readonly property color menuItem: bg
    }

    property QtObject light: QtObject {
        readonly property color bg: "#FFFFFF";
        readonly property color widgetBg: "#DEDEDE";

        readonly property color accent: "#ec5a5c"

        readonly property color tab: "#ec686a"
        readonly property color text: "#000000"

        readonly property color menu: "#DDDDDD"
        readonly property color menuBorder: "#222222"
        readonly property real menuBaseOpacity: 0.8
        readonly property color menuItem: bg
    }
}
