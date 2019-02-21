// Copyright (c) 2013-2019 LG Electronics, Inc.
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
import "../keyboard-common"

Rectangle {
    id: root
    objectName: "hidPredictionItem"
    property QtObject chineseStyle: []
    property alias wordText: word.text
    property int contentWidth: word.contentWidth
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
            verticalAlignment: Text.AlignBottom
            font.family: root.chineseStyle.hidSuggestionButton.fontFamily
            color: root.chineseStyle.hidSuggestionButton.normal.fgColor
            font.pixelSize: root.chineseStyle.hidSuggestionButton.normal.fontSize
            elide: Text.ElideRight
            text: ""
        }

        Text {
            id: hotkey
            objectName: "hotkey"
            height: parent.height * 3 / 7
            anchors.horizontalCenter: parent.horizontalCenter
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignTop
            font.family: root.chineseStyle.hidSuggestionButton.fontFamily
            color: root.chineseStyle.hidSuggestionButton.focus.subtitleColor
            font.pixelSize: root.chineseStyle.hidSuggestionButton.focus.subtitleSize
        }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        onReleased: {
            root.released();
            if (removed) return;
            if (root.state === "Disable") return;
            if (mouseArea.containsMouse)
                root.state = "Normal";
        }
        onPressed: {
            root.pressed();
            if (removed) return;
            if (root.state === "Disable") return;
            if (mouseArea.containsMouse)
                root.focus = mouseArea.containsMouse;
            if (!root.focus)
                root.state = "Select";
            else
                root.state = "Normal";
        }
        onEntered: {
            root.state = "Focus";
            root.entered();
        }
        onExited: {
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
                color: root.chineseStyle.hidSuggestionButton.normal.bgColor
                border.color: root.chineseStyle.hidSuggestionButton.normal.borderColor
                border.width: root.chineseStyle.hidSuggestionButton.normal.borderWidth
            }
            PropertyChanges {
                target: word
                color: root.chineseStyle.hidSuggestionButton.normal.fgColor
                font.pixelSize: root.chineseStyle.hidSuggestionButton.normal.fontSize
            }
            PropertyChanges {
                target: hotkey
                color: root.chineseStyle.hidSuggestionButton.normal.subtitleColor
                font.pixelSize: root.chineseStyle.hidSuggestionButton.normal.subtitleSize
            }
        },
        State {
            name: "Focus"; extend: "Enabled"
            PropertyChanges {
                target: root
                color: root.chineseStyle.hidSuggestionButton.focus.bgColor
                border.color: root.chineseStyle.hidSuggestionButton.focus.borderColor
                border.width: root.chineseStyle.hidSuggestionButton.focus.borderWidth
            }
            PropertyChanges {
                target: word
                color: root.chineseStyle.hidSuggestionButton.focus.fgColor
                font.pixelSize: root.chineseStyle.hidSuggestionButton.focus.fontSize
            }
            PropertyChanges {
                target: hotkey
                color: root.chineseStyle.hidSuggestionButton.focus.subtitleColor
                font.pixelSize: root.chineseStyle.hidSuggestionButton.focus.subtitleSize
            }
        },
        State {
            name: "Select"; extend: "Enabled"
            PropertyChanges {
                target: root
                color: root.chineseStyle.hidSuggestionButton.select.bgColor
                border.color: root.chineseStyle.hidSuggestionButton.select.borderColor
                border.width: root.chineseStyle.hidSuggestionButton.select.borderWidth
            }
            PropertyChanges {
                target: word
                color: root.chineseStyle.hidSuggestionButton.select.fgColor
                font.pixelSize: root.chineseStyle.hidSuggestionButton.select.fontSize
            }
            PropertyChanges {
                target: hotkey
                color: root.chineseStyle.hidSuggestionButton.select.subtitleColor
                font.pixelSize: root.chineseStyle.hidSuggestionButton.select.subtitleSize
            }
        },
        State {
            name: "Disable"; extend: "Disabled"
            PropertyChanges {
                target: root
                color: root.chineseStyle.hidSuggestionButton.disable.bgColor
                border.width: root.chineseStyle.hidSuggestionButton.disable.borderWidth
            }
            PropertyChanges {
                target: word
                color: root.chineseStyle.hidSuggestionButton.disable.fgColor
            }
            PropertyChanges {
                target: hotkey
                color: root.chineseStyle.hidSuggestionButton.disable.subtitleColor
            }
            PropertyChanges {
                target: mouseArea
                enabled: false
            }
        },
        State { name: "Enabled";  PropertyChanges { target: root; enabled: true  } },
        State { name: "Disabled"; PropertyChanges { target: root; enabled: false } }
    ]
}
