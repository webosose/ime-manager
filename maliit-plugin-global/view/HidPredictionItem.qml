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
    objectName: "hidPredictionItem"
    property QtObject globalStyle: GlobalStyle {}
    property alias wordWidth: word.contentWidth
    property alias wordText: word.text
    property alias hotKeyText: hotkey.text
    property bool removed: false
    signal pressed()
    signal released()
    signal entered()
    signal exited()

    Column {
        anchors.fill: parent

        Text {
            id: word
            objectName: "word"
            height: parent.height * 4 / 7
            anchors.horizontalCenter: parent.horizontalCenter
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment:   Text.AlignBottom
            font.family:    root.globalStyle.hidPredictionButton.fontFamily
            font.pixelSize: root.globalStyle.hidPredictionButton.normal.fontSize
            elide: Text.ElideRight
        }

        Text {
            id: hotkey
            objectName: "hotkey"
            height: parent.height * 3 / 7
            anchors.horizontalCenter: parent.horizontalCenter
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment:   Text.AlignTop
            font.family:    root.globalStyle.hidPredictionButton.fontFamily
            font.pixelSize: root.globalStyle.hidPredictionButton.normal.subtitleSize
        }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent

        hoverEnabled: true
        onReleased: {
            if (!root.focus) return;
            root.released();
            if (removed) return;
            if (root.state === "Disable") return;
            root.focus = mouseArea.containsMouse;
            if (!root.focus)
                root.state = "Normal";
        }
        onPressed: {
            root.pressed();
            if (removed) return;
            if (root.state === "Disable") return;
            root.focus = mouseArea.containsMouse;
            if (!root.focus)
                root.state = "Normal";
        }
        onEntered: {
            if (root.state === "Disable") return;
            if (mouseArea.pressed) return;
            root.focus = true;
            root.entered();
        }
        onExited: {
            if (root.state === "Disable") return;
            root.focus = false;
            root.state = "Normal";
            root.exited();
        }
    }

    state: "Normal"
    states: [
        State {
            name: ""; extend: "Enabled"
        },
        State {
            name: "Normal"; extend: "Enabled"
            PropertyChanges {
                target: root
                color: root.globalStyle.hidPredictionButton.normal.bgColor
                border.color: root.globalStyle.hidPredictionButton.normal.borderColor
                border.width: root.globalStyle.hidPredictionButton.normal.borderWidth
            }
            PropertyChanges {
                target: word
                color: root.globalStyle.hidPredictionButton.normal.fgColor
                font.pixelSize: root.globalStyle.hidPredictionButton.normal.fontSize
            }
            PropertyChanges {
                target: hotkey
                color: root.globalStyle.hidPredictionButton.normal.subtitleColor
                font.pixelSize: root.globalStyle.hidPredictionButton.normal.subtitleSize
            }
        },
        State {
            name: "Focus"; extend: "Enabled"
            when: root.enabled && root.focus && !mouseArea.pressed
            PropertyChanges {
                target: root
                color: root.globalStyle.hidPredictionButton.focus.bgColor
                border.color: root.globalStyle.hidPredictionButton.focus.borderColor
                border.width: root.globalStyle.hidPredictionButton.focus.borderWidth
            }
            PropertyChanges {
                target: word
                color: root.globalStyle.hidPredictionButton.focus.fgColor
                font.pixelSize: root.globalStyle.hidPredictionButton.focus.fontSize
            }
            PropertyChanges {
                target: hotkey
                color: root.globalStyle.hidPredictionButton.focus.subtitleColor
                font.pixelSize: root.globalStyle.hidPredictionButton.focus.subtitleSize
            }
        },
        State {
            name: "Select"; extend: "Enabled"
            when: root.enabled && root.focus && mouseArea.pressed
            PropertyChanges {
                target: root
                color: root.globalStyle.hidPredictionButton.select.bgColor
                border.color: root.globalStyle.hidPredictionButton.select.borderColor
                border.width: root.globalStyle.hidPredictionButton.select.borderWidth
            }
            PropertyChanges {
                target: word
                color: root.globalStyle.hidPredictionButton.select.fgColor
                font.pixelSize: root.globalStyle.hidPredictionButton.select.fontSize
            }
            PropertyChanges {
                target: hotkey
                color: root.globalStyle.hidPredictionButton.select.subtitleColor
                font.pixelSize: root.globalStyle.hidPredictionButton.select.subtitleSize
            }
        },
        State {
            name: "Disable"; extend: "Disabled"
            PropertyChanges {
                target: root
                color: root.globalStyle.hidPredictionButton.disable.bgColor
                border.width: root.globalStyle.hidPredictionButton.disable.borderWidth
                focus: false
            }
            PropertyChanges {
                target: word
                color: root.globalStyle.hidPredictionButton.disable.fgColor
            }
            PropertyChanges {
                target: hotkey
                color: root.globalStyle.hidPredictionButton.disable.subtitleColor
            }
        },
        State { name: "Enabled";  PropertyChanges { target: root; enabled: true  } },
        State { name: "Disabled"; PropertyChanges { target: root; enabled: false } }
    ]
}
