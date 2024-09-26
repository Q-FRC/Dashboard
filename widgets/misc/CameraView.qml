import QtQuick 2.15
import QtQuick.Controls 2.15

import QtMultimedia

import QFRCDashboard

BaseWidget {
    property string item_URL

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
            source: item_URL
            videoOutput: video
        }

        VideoOutput {
            id: video
            anchors.fill: parent
        }
    }

    function restartVideo() {
        if (player.playbackState === StoppedState) {
            player.playbackStateChanged.disconnect(restartVideo)
            player.start()
        }
    }

    onItem_URLChanged: {
        player.playbackStateChanged.connect(restartVideo)
        player.stop()
    }
}
