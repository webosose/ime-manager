// Copyright (c) 2013-2018 LG Electronics, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0

import QtQuick 2.0

Rectangle {
    id: root
    objectName: "micImage"
    anchors.centerIn: parent
    width: parent.width
    height: sttStyle.micBackground.height
    color: sttStyle.mic.bgColor
    visible: true
    state: "off"
    clip: true

    // Clickable offimage
    signal clicked()
    signal entered()
    signal exited()

    property int energyLevel: 0

    onStateChanged: {
        printLog("=== micImage onStateChanged ===")
        printLog("state : " + state)
        if(state === "off") // if STT plugin is deactivated, state changed to "off"
            initialize()
    }
    function initialize() {
        energyLevel = 0;
    }

    Rectangle {
        id: micBorder
        objectName: "micBorder"
        anchors.centerIn: parent
        width: sttStyle.mic.micBorderWidth + energyLevel*2
        height: width
        color: "transparent"
        opacity: 0.31
        border.color: "gray"
        border.width: (width - sttStyle.mic.micBorderWidth)/2
        radius: width*0.5
        visible: false
        onVisibleChanged: {
            printLog("micBorder.visible : " + micBorder.visible)
        }

        Behavior on width {
            id: micBorderWidthBehavior
            enabled: false
            PropertyAnimation { properties: "width"; easing.type: Easing.Linear; duration: 90 }
        }
    }

    Rectangle {
        id: hideImage
        objectName: "hideImage"
        anchors.horizontalCenter: parent.horizontalCenter
        width: sttStyle.mic.width
        height: sttStyle.mic.height
        color: sttStyle.mic.bgColor
        visible: false
        onVisibleChanged: {
            printLog("hideImage.visible : " + hideImage.visible)
        }
    }

    MouseArea {
        id: offImage
        objectName: "offImage"
        anchors.centerIn: parent
        width: offImageImg.width
        height: offImageImg.height
        clip: true
        hoverEnabled: true
        visible: false
        onVisibleChanged: {
            printLog("offImage.visible : " + offImage.visible)
        }
        onEntered: root.entered()
        onExited: root.exited()
        onClicked: root.clicked()
        Rectangle {
            id: centerfilledRound
            objectName: "centerfilledRound"
            anchors.centerIn: parent
            width: offImageImg.width
            height: offImageImg.height
            color: sttStyle.mic.focusedColor
            radius: offImageImg.width*0.5
            visible: root.activeFocus? true : false
        }
        Image {
            id: offImageImg
            anchors.fill: parent
            objectName: "offImageImg"
            source: "qrc:///stt/images/nlp_sequence_ready.png"
        }
    }
    Image {
        id: readyImage
        objectName: "readyImage"
        anchors.centerIn: parent
        width: height
        height: sttStyle.mic.micImageHeight
        source: "qrc:///stt/images/nlp_sequence_on.png"
        clip: true
        visible: false
        onVisibleChanged: {
            printLog("readyImage.visible : " + readyImage.visible)
        }
    }

    SequentialAnimation {
        id: readyAnimation
        objectName: "readyAnimation"
        loops: Animation.Infinite

        PropertyAnimation {
            target: root
            property: "energyLevel"
            easing.type: Easing.CosineCurve
            from: 0
            to: 15
            duration: 250
        }
        PropertyAnimation {
            target: root
            property: "energyLevel"
            easing.type: Easing.CosineCurve
            from: 0
            to: 20
            duration: 250
        }

        onRunningChanged: {
            root.energyLevel = 0
        }
    }


    Image {
        id: energyLevelImage
        objectName: "energyLevelImage"
        anchors.centerIn: parent
        width: height
        height: sttStyle.mic.micImageHeight
        source: "qrc:///stt/images/nlp_sequence_on.png"
        clip: true
        visible: false
        onVisibleChanged: {
            printLog("energyLevelImage.visible : " + energyLevelImage.visible)
        }
    }

    Image {
        id: progressImage
        objectName: "progressImage"
        anchors.centerIn: parent
        width: height
        height: sttStyle.mic.micImageHeight
        source: "qrc:///stt/images/nlp_sequence_progress.png"
        visible: false
        onVisibleChanged: {
            printLog("progressImage.visible : " + progressImage.visible)
            if(visible) {
                rotation = 0;
                progressAnimation.start()
            }
            else
                progressAnimation.stop()
        }

        NumberAnimation on rotation {
            id: progressAnimation
            objectName: "progressAnimation"
            loops: Animation.Infinite
            running: false
            from: 0
            to: 360
            duration: 600
        }
    }

    Image {
        id: errorImage
        objectName: "errorImage"
        anchors.horizontalCenter: parent.horizontalCenter
        width: sttStyle.mic.width
        height: sttStyle.mic.height
        source: "qrc:///stt/images/nlp_sequence_error_dimmed.png"
        visible: false
        onVisibleChanged: {
            printLog("errorImage.visible : " + errorImage.visible)
        }
    }

    states: [
        State {
            name: "hide"
            PropertyChanges { target: hideImage; visible: true }
        },
        State {
            name: "off" // if STT plugin is deactivated, state changed to "off"
            PropertyChanges { target: offImage; visible: true }
        },
        State {
            name: "ready"
            PropertyChanges { target: readyImage; visible: true }
            PropertyChanges { target: micBorder; visible: true }
            PropertyChanges { target: readyAnimation; running: true}
        },
        State {
            name: "energyLevel"
            PropertyChanges { target: energyLevelImage; visible: true }
            PropertyChanges { target: micBorder; visible: true }
            PropertyChanges { target: micBorderWidthBehavior; explicit: true; enabled: true}
        },
        State {
            name: "processing"
            PropertyChanges { target: progressImage; visible: true }
            PropertyChanges { target: readyImage; visible: true }
        },
        State {
            name: "error"
            PropertyChanges { target: errorImage; visible: true }
        },
        State {
            name: "langSelect"
            PropertyChanges { target: hideImage; visible: true }
        }
    ]
}
