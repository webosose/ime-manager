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
import "../keyboard-common"
import "variables.js" as Variables
import "../keyboard-common/commonvariables.js" as CommonVariables

Rectangle {
    id: numberKeyboard
    objectName: "numberKeyboard"
    color: commonStyle.bgColor

    property string mode: "Normal"

    signal sendKey(int keycode, bool shift, int eventType)
    signal sendText(string text)
    signal meetTopBoundary()
    signal meetBottomBoundary()

    onFocusChanged: {
        if (focus) CommonVariables.savedFocusItem = numberRepeater.itemAt(5);
    }

    Keys.onPressed: {
        if (event.key === Qt.Key_Up) {
            numberKeyboard.meetTopBoundary()
            event.accepted =  true;
        }

        if (event.key === Qt.Key_Down) {
            numberKeyboard.meetBottomBoundary()
            event.accepted =  true;
        }
    }

    Row {
        anchors.top: parent.top
        anchors.topMargin: commonStyle.numberKeyboard.topMargin
        anchors.left: parent.left
        anchors.leftMargin: commonStyle.numberKeyboard.leftMargin
        spacing: commonStyle.numberKeyboard.seperator

        /* Symbol Button */
        ButtonBase {
            id: symbolButton
            objectName: "symbolButton"

            signal meetRightBoundary()

            buttonStyle: commonStyle.numberButton
            width: commonStyle.numberKeyboard.funcButtonWidth
            height: commonStyle.numberKeyboard.cellHeight

            text: (numberKeyboard.mode === "Symbol") ? "1 2 3" : "* + /"

            onReleased: {
                switch (numberKeyboard.mode) {
                case "Normal":
                    numberKeyboard.mode = "Symbol";
                    break;
                case "Symbol":
                    numberKeyboard.mode = "Normal";
                    break;
                default:
                    numberKeyboard.mode = "Normal";
                    break;
                }
            }

            Keys.onPressed: {
                if (event.key === Qt.Key_Right) {
                    meetRightBoundary();
                    event.accepted = true;
                }
            }

            KeyNavigation.left : enterButton

            onMeetRightBoundary: numberView.setKeyNavigation(0)

            function setKeyNavigation() {
                symbolButton.focus = true;
            }
        }

        /* Numbers */
        Row {
            id: numberView
            objectName: "numberView"

            spacing: commonStyle.numberKeyboard.cellSpace
            property variant model

            signal meetLeftBoundary()
            signal meetRightBoundary()

            Repeater {
                id: numberRepeater
                objectName: "numberRepeater"
                model: numberView.model

                NumberButton {
                    width: commonStyle.numberKeyboard.cellWidth
                    height: commonStyle.numberKeyboard.cellHeight
                    mainChar: modelData.mainChar
                    symbolChar: modelData.symbolChar
                    onTextKeyPressed: numberKeyboard.sendText(text)

                    KeyNavigation.left:  numberRepeater.itemAt(index - 1)
                    KeyNavigation.right: numberRepeater.itemAt(index + 1)
                    Keys.onPressed: event.accepted = checkNavigationKey(index, event.key)
                }
                onItemRemoved: item.removed = true
            }

            onMeetLeftBoundary: symbolButton.setKeyNavigation()
            onMeetRightBoundary: tabButtons.setKeyNavigation()

            function setKeyNavigation(index) {
                if (index === 0)
                    numberRepeater.itemAt(0).focus = true;
                else if (index === 9)
                    numberRepeater.itemAt(9).focus = true;
            }
        }

        /* Function Keys */
        Row {
            id: tabButtons
            objectName: "tabButtons"
            spacing: commonStyle.numberKeyboard.cellSpace

            signal meetLeftBoundary()

            /* Delete Button */
            ButtonBase {
                id: deleteButton
                objectName: "deleteButton"
                image: (state !== "Select") ? "qrc:///images/clear.png" : "qrc:///images/clear-dark.png"
                onReleased: sendKey(14, false, eventType)

                width: commonStyle.numberKeyboard.funcButtonWidth
                height: commonStyle.numberKeyboard.cellHeight

                KeyNavigation.right: enterButton
                Keys.onPressed: {
                    if (event.key === Qt.Key_Left) {
                        tabButtons.meetLeftBoundary();
                        event.accepted = true;
                    }
                }
            }

            /* Enter Button */
            ButtonBase {
                id: enterButton
                objectName: "enterButton"
//#IF_COMMERCIAL
                text: PluginProxy.numKeyEnterLabel
//#ELSE
/*
                text: "入力"
*/
//#END
                onReleased: sendKey(28, false, eventType)

                width: commonStyle.numberKeyboard.enterButtonWidth
                height: commonStyle.numberKeyboard.cellHeight

                KeyNavigation.left: deleteButton
            }

            onMeetLeftBoundary: numberView.setKeyNavigation(9)

            function setKeyNavigation() {
                deleteButton.focus = true;
            }

            Connections {
                target: PluginProxy
                onKeyReleased : {
                    if (isReleased && (symbolButton.state === "Select"))
                        symbolButton.state = "Focus";
                    else if (isReleased && (deleteButton.state === "Select"))
                        deleteButton.state = "Focus";
                    else if (isReleased && (enterButton.state === "Select"))
                        enterButton.state = "Focus";
                }
            }
        }
    }
    Component.onCompleted: drawNumberLayout()


    function drawNumberLayout() {
        var model = [];
        var key;

        for (var i = 0; i < 10; i++) {
            key = new Object;
            key.mainChar = Variables.numbers[i];
            key.symbolChar = Variables.numberSymbols[i];
            model.push(key);
        }
        numberView.model = model;
    }

    function checkNavigationKey(index, key) {
        var accepted = false;

        if (key === Qt.Key_Left && index === 0) {
            numberView.meetLeftBoundary();
            accepted = true;
        } else if (key === Qt.Key_Right && index === 9) {
            numberView.meetRightBoundary();
            accepted = true;
        }

        return accepted;
    }

    function setDefaultFocus() {
        numberRepeater.itemAt(5).focus = true;
    }

    function setFocusToEnter() {
        enterButton.focus = true;
    }

    function setToDefault() {
        mode = "Normal";
    }
}
