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

import "commonvariables.js" as CV

Rectangle {
    id: btn     // id on the first line makes it easy to find an object

    // property declarations
    property alias text: txt.text
    property variant buttonStyle: style.button
    property alias fontSize: txt.font.pixelSize
    property alias fontSizeMode: txt.fontSizeMode
    property string fontfamily: ""
    property url image
    property int contentWidth: txt.contentWidth
    property bool removed: false
    property bool locked: false
    property bool allowRepeat: true
    property int enterPriority: executeBeforeRelease
    readonly property int executeBeforeRelease: 0
    readonly property int releaseBeforeExecute: 1

    // signal declarations
    signal pressed(int eventType)
    signal released(int eventType)
    signal clicked()
    signal entered()
    signal exited()
    signal executed()   // signal for Ok button of the Remote
    signal ttsService(string text)

    property int currentEvent: CV.MouseEvent

    onFocusChanged: {
        if (focus) btn.ttsService(text);
    }

    // JavaScript functions
    onEnabledChanged: {
        // stop the timer
        starter.stop();
        ticker.stop();
    }

    // object properties
    state: "Normal"
    color: (btn.locked && buttonStyle.lockedNormal) ? buttonStyle.lockedNormal.bgColor : buttonStyle.normal.bgColor
    border.color: (btn.locked && buttonStyle.lockedNormal) ? buttonStyle.lockedNormal.borderColor : buttonStyle.normal.borderColor
    border.width: (btn.locked && buttonStyle.lockedNormal) ? buttonStyle.lockedNormal.borderWidth : buttonStyle.normal.borderWidth

    Keys.onPressed: {
        if (event.key === Qt.Key_Execute) {
            btn.currentEvent = CV.KeyBoardEvent;
            if (enterPriority === releaseBeforeExecute) {
                btn.released(btn.currentEvent);
                btn.executed();
            } else {
                btn.executed();
                btn.state = "Select"
                btn.released(btn.currentEvent);
            }
            event.accepted = true;
        }
    }

    // child objects
    Image {
        id: img
        source: image
        smooth: true
        anchors.centerIn: btn
    }

    Text {
        id: txt
        anchors.fill: parent
        anchors.margins: buttonStyle.minimumMargin !== undefined ? buttonStyle.minimumMargin : 2
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.family: fontfamily !== "" ? fontfamily : (buttonStyle.fontFamily ? buttonStyle.fontFamily : commonStyle.defaultFontFamily)
        font.weight: buttonStyle.fontWeight ? buttonStyle.fontWeight : Font.Normal
        text: ""
        color: buttonStyle.normal.fgColor
        font.pixelSize: buttonStyle.normal.fontSize
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true

        onReleased: {
            starter.stop();
            ticker.stop();

            if (!btn.focus) return;
            btn.currentEvent = CV.MouseEvent;
            btn.released(btn.currentEvent);

            if (removed) return;
            if (btn.state === "Disable") return;
            btn.focus = mouseArea.containsMouse;
            if (!btn.focus)
                btn.state = "Normal";

            // Check and change the JP PlugIn "space"button image
            if (btn.text === " ") {
                btn.image = "qrc:///images/spacebar.png";
            }
        }

        onPressed: {
            btn.currentEvent = CV.MouseEvent;
            btn.pressed(btn.currentEvent);
            if (allowRepeat)
                starter.restart();
            if (removed) return;
            if (btn.state === "Disable") return;
            btn.focus = mouseArea.containsMouse;
            if (!btn.focus)
                btn.state = "Normal";

            // Check and change the JP PlugIn "space"button image
            if (btn.text === " ") {
                btn.image = "qrc:///images/spacebar-dark.png";
            }
        }

        onEntered: {
            if (btn.state === "Disable") return;
            if (mouseArea.pressed) return;
            btn.focus = true;
            btn.entered();
        }

        onExited: {
            starter.stop();
            ticker.stop();

            if (btn.state === "Disable") return;
            btn.focus = false;
            btn.state = "Normal";
            btn.exited();
        }

        onClicked:{
            btn.clicked();
        }
    }

    MultiPointTouchArea {
        id: touchArea
        anchors.fill: parent
        mouseEnabled : false
        minimumTouchPoints: 1
        maximumTouchPoints: 1

        onPressed: {
            btn.currentEvent = CV.TouchEvent;
            btn.pressed(btn.currentEvent);
            if (allowRepeat)
                starter.restart();
            if (removed) return;
            if (btn.state === "Disable") return;
            btn.focus = true;
            if (!btn.focus)
                btn.state = "Normal";

            // Check and change the JP PlugIn "space"button image
            if (btn.text === " ") {
                btn.image = "qrc:///images/spacebar-dark.png";
            }
        }

        onReleased: {
            starter.stop();
            ticker.stop();

            if (!btn.focus) return;
            btn.currentEvent = CV.TouchEvent;
            btn.released(btn.currentEvent);
            if (removed) return;
            if (btn.state === "Disable") return;
            btn.focus = false;
            if (!btn.focus)
                btn.state = "Normal";

            // Check and change the JP PlugIn "space"button image
            if (btn.text === " ") {
                btn.image = "qrc:///images/spacebar.png";
            }
        }
    }

    function releaseButton() {
        if (btn.state === "Select") {
            starter.stop();
            ticker.stop();
            if (btn.state !== "Disable")
                btn.state = "Focus";
        }
    }

    Timer {
        id: starter
        interval: 500; running:false; repeat: false
        onTriggered: ticker.restart()
    }

    Timer {
        id: ticker
        interval: 160; running: false; repeat: true
        onTriggered: {
            if (btn.state !== "Select") {
                starter.stop();
                ticker.stop();
                return;
            }
            btn.released(btn.currentEvent);
        }
    }

    // states
    states: [
        State {
            name: ""; extend: "Enabled"
        },
        State {
            name: "Normal"; extend: "Enabled"
        },
        State {
            name: "Focus"; extend: "Enabled"
            when: btn.enabled && btn.focus && !mouseArea.pressed
            PropertyChanges {
                target: btn
                color: (locked && buttonStyle.lockedFocus) ? buttonStyle.lockedFocus.bgColor : buttonStyle.focus.bgColor
                border.color: (locked && buttonStyle.lockedFocus) ? buttonStyle.lockedFocus.borderColor : buttonStyle.focus.borderColor
                border.width: (locked && buttonStyle.lockedFocus) ? buttonStyle.lockedFocus.borderWidth : buttonStyle.focus.borderWidth
            }
            PropertyChanges {
                target: txt
                color: buttonStyle.focus.fgColor
                font.pixelSize: buttonStyle.focus.fontSize
            }
            StateChangeScript {
                script: {
                    CV.savedFocusItem = btn;
                }
            }
        },
        State {
            name: "Select"; extend: "Enabled"
            when: btn.enabled && btn.focus && mouseArea.pressed
            PropertyChanges {
                target: btn
                color: buttonStyle.select.bgColor
                border.color: buttonStyle.select.borderColor
                border.width: buttonStyle.select.borderWidth
            }
            PropertyChanges {
                target: txt
                color: buttonStyle.select.fgColor
                font.pixelSize: buttonStyle.select.fontSize
            }
        },
        State {
            name: "Disable"; extend: "Disabled"
            PropertyChanges {
                target: btn
                color: buttonStyle.disable.bgColor
                border.color: buttonStyle.disable.borderColor
                border.width: buttonStyle.disable.borderWidth
                focus: false
            }
            PropertyChanges {
                target: txt
                color: buttonStyle.disable.fgColor
                font.pixelSize: buttonStyle.disable.fontSize
            }
        },
        State { name: "Enabled"; PropertyChanges { target: btn; enabled: true; } },
        State { name: "Disabled"; PropertyChanges { target: btn; enabled: false; } }
    ]

    // transitions
}
