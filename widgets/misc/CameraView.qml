import QtQuick 2.15
import QtQuick.Controls 2.15

import QtMultimedia

import QFRCDashboard

BaseWidget {
    property string item_host: "127.0.0.1"

    property int item_port: 1181
    property int portMax: 65535

    property int item_quality: 0
    property int qualityMax: 100

    property int item_fps: 0
    property int fpsMax: 240

    property size item_resolution: Qt.size(0, 0)

    onItem_fpsChanged: player.resetSource()
    onItem_portChanged: player.resetSource()
    onItem_qualityChanged: player.resetSource()
    onItem_resolutionChanged: player.resetSource()
    onItem_hostChanged: player.resetSource()

    Rectangle {
        anchors {
            top: titleField.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom

            margins: 8
        }

        MediaPlayer {
            id: player

            source: ""

            function restartVideo() {
                if (player.playbackState === StoppedState) {
                    player.playbackStateChanged.disconnect(restartVideo)
                    player.start()
                }
            }

            function resetSource() {
                source = Qt.url(item_host + ":" + item_port + "/stream.mjpg?" +
                        (item_quality !== 0 ? "compression=" + item_quality + "&" : "") +
                        (item_fps !== 0 ? "fps=" + item_fps + "&" : "") +
                        (item_resolution !== Qt.size(0, 0) ? "resolution=" + item_resolution.width + "x" + item_resolution.height : ""))
            }

            onSourceChanged: {
                player.playbackStateChanged.connect(restartVideo)
                player.stop()
                console.log(source)
            }

            videoOutput: video
            onErrorOccurred: console.error("CameraView: error:", errorString)
        }

        VideoOutput {
            id: video
            anchors.fill: parent
        }
    }
}
