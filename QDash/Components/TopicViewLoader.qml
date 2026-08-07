// SPDX-FileCopyrightText: Copyright 2026 crueter
// SPDX-License-Identifier: GPL-3.0-or-later

import Carboxyl.Contour
import QtQuick
import QtQuick.Controls

Loader {
    id: loader

    height: parent.height
    width: (parent.width / 3)

    property rect geometry: Qt.rect(0, 0, 0, 0)

    signal addWidget(string name, string topic, string type)
    signal closed
    signal dragging(point pos)
    signal dropped(point pos)
    signal opened

    function open() {
        active = true
    }

    SmoothedAnimation {
        id: menuAnim

        property bool closing

        duration: 500
        property: "anchors.leftMargin"
        target: tv

        onFinished: {
            geometry = mapToItem(mainScreen, Qt.rect(x, y, width, height))
            if (closing) {
                loader.active = false
            }
        }
    }

    function openAnim() {
        menuAnim.from = -(mainScreen.width / 3)
        menuAnim.to = 0
        menuAnim.closing = false
        menuAnim.start()
    }

    function close() {
        menuAnim.to = -(mainScreen.width / 3)
        menuAnim.from = 0
        menuAnim.closing = true
        menuAnim.start()
    }

    property Component src: TopicView {
        onAddWidget: (title, topic, type) => loader.addWidget(title, topic, type)
        onDragging: pos => loader.dragging(pos)
        onDropped: pos => loader.dropped(pos)
        onAnimationFinished: state => {
            if (!state)
                close()
        }
    }

    active: false
    asynchronous: true
    sourceComponent: active ? src : undefined

    onLoaded: openAnim()
}
