import QtQuick 2.15
import QtQuick.Controls 2.15

import QtMultimedia

import QFRCDashboard

BaseWidget {
    property string item_URL

    MediaPlayer {
        id: player
        source: item_URL
        videoOutput: VideoOutput {
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
