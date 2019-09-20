// Copyright (c) 2019 LG Electronics, Inc.
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

import "japanesestyle.js" as JapaneseStyle

Rectangle {
    id: root
    objectName: "hidPredictionItem"
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
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment:   Text.AlignTop
            font.family:    JapaneseStyle.hidPredictionButton.fontFamily
            font.pixelSize: JapaneseStyle.hidPredictionButton.normal.fontSize
            elide: Text.ElideRight
        }

        Text {
            id: hotkey
            objectName: "hotkey"
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment:   Text.AlignBottom
            font.family:    JapaneseStyle.hidPredictionButton.fontFamily
            font.pixelSize: JapaneseStyle.hidPredictionButton.normal.subtitleSize
        }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        onReleased: {
            if (removed) return;
            if (root.state === "Disable") return;
            if (mouseArea.containsMouse)
                root.state = "Focus";
            else
                root.state = "Normal";
            root.released();
        }
        onPressed: {
            if (removed) return;
            if (root.state === "Disable") return;
            if (mouseArea.containsMouse)
                root.state = "Select";
            else
                root.state = "Normal";
            root.pressed();
        }
        onEntered: {
            if (root.state === "Disable") return;
            root.state = "Focus";
            root.entered();
        }
        onExited: {
            if (root.state === "Disable") return;
            root.state = "Normal";
            root.exited();
        }
    }

    state: "Normal"
    states: [
        State {
            name: "Normal"; extend: "Enabled"
            PropertyChanges {
                target: root
                color: JapaneseStyle.hidPredictionButton.normal.bgColor
                border.color: JapaneseStyle.hidPredictionButton.normal.borderColor
                border.width: JapaneseStyle.hidPredictionButton.normal.borderWidth
            }
            PropertyChanges {
                target: word
                color: JapaneseStyle.hidPredictionButton.normal.fgColor
                font.pixelSize: JapaneseStyle.hidPredictionButton.normal.fontSize
            }
            PropertyChanges {
                target: hotkey
                color: JapaneseStyle.hidPredictionButton.normal.subtitleColor
                font.pixelSize: JapaneseStyle.hidPredictionButton.normal.subtitleSize
            }
        },
        State {
            name: "Focus"; extend: "Enabled"
            PropertyChanges {
                target: root
                color: JapaneseStyle.hidPredictionButton.focus.bgColor
                border.color: JapaneseStyle.hidPredictionButton.focus.borderColor
                border.width: JapaneseStyle.hidPredictionButton.focus.borderWidth
            }
            PropertyChanges {
                target: word
                color: JapaneseStyle.hidPredictionButton.focus.fgColor
                font.pixelSize: JapaneseStyle.hidPredictionButton.focus.fontSize
            }
            PropertyChanges {
                target: hotkey
                color: JapaneseStyle.hidPredictionButton.focus.subtitleColor
                font.pixelSize: JapaneseStyle.hidPredictionButton.focus.subtitleSize
            }
        },
        State {
            name: "Select"; extend: "Enabled"
            PropertyChanges {
                target: root
                color: JapaneseStyle.hidPredictionButton.select.bgColor
                border.color: JapaneseStyle.hidPredictionButton.select.borderColor
                border.width: JapaneseStyle.hidPredictionButton.select.borderWidth
            }
            PropertyChanges {
                target: word
                color: JapaneseStyle.hidPredictionButton.select.fgColor
                font.pixelSize: JapaneseStyle.hidPredictionButton.select.fontSize
            }
            PropertyChanges {
                target: hotkey
                color: JapaneseStyle.hidPredictionButton.select.subtitleColor
                font.pixelSize: JapaneseStyle.hidPredictionButton.select.subtitleSize
            }
        },
        State {
            name: "Disable"; extend: "Disabled"
            PropertyChanges {
                target: root
                color: JapaneseStyle.hidPredictionButton.disable.bgColor
                border.width: JapaneseStyle.hidPredictionButton.disable.borderWidth
            }
            PropertyChanges {
                target: word
                color: JapaneseStyle.hidPredictionButton.disable.fgColor
            }
            PropertyChanges {
                target: hotkey
                color: JapaneseStyle.hidPredictionButton.disable.subtitleColor
            }
        },
        State { name: "Enabled";  PropertyChanges { target: root; enabled: true  } },
        State { name: "Disabled"; PropertyChanges { target: root; enabled: false } }
    ]
}
