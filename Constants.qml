pragma Singleton
import QtQuick

QtObject {
    readonly property int width: 900;
    readonly property int height: 600;

    property var palette: dark
    property string rootAccent: "red"

    property color accent: "#ec202a"
    property color tab: "#ec5a5c"

    function setLight() {
        palette = light
    }

    function setDark() {
        palette = dark
    }

    function setAccent(newAccent) {
        switch (newAccent) {
        case "red":
            accent = "#ec202a"
            tab = "#ec5a5c"
            break;
        case "blue":
            accent = "#1352ff"
            tab = "#4520ff"
            break;
        default:
            break;
        }
    }

    property QtObject dark: QtObject {
        id: dark

        readonly property color bg: "#111111";
        readonly property color widgetBg: "#272727";
        readonly property color dialogBg: "#404040";

        readonly property color text: "#FFFFFF"

        readonly property color menu: "#222222"
        readonly property color menuBorder: "#AAAAAA"
        readonly property real menuBaseOpacity: 0.3
        readonly property color menuItem: bg
    }

    property QtObject light: QtObject {
        readonly property color bg: "#FFFFFF";
        readonly property color widgetBg: "#EDEDED";
        readonly property color dialogBg: "#DCDCDC";

        readonly property color text: "#000000"

        readonly property color menu: "#DDDDDD"
        readonly property color menuBorder: "#222222"
        readonly property real menuBaseOpacity: 0.8
        readonly property color menuItem: bg
    }
}
