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

Item {
    id: root
    objectName: "leftFunctionAreaJapanese"
    state: "Hiragana"

    property string currLanguage: "日本語"
    property bool supportShiftMode: false
    property bool requestChangeLanguage: false
    property var buttonArray: [languageChangeButton, symbolButton, inputModeToggleButton, shiftButton]

    signal clickLanguageButton()
    signal clickInputCharacterChangeButton()
    signal meetLeftBoundary(int row)
    signal meetRightBoundary(int row)
    signal meetTopBoundary(int column)
    signal meetBottomBoundary()
    signal setSymbolMode()
    signal unsetSymbolMode()

    function setKeyNavigation(row) {
        if (buttonArray[row] && buttonArray[row].visible) {
            buttonArray[row].focus = true;
            return;
        }
        findVisibleButton(row).focus = true;
    }

    function findVisibleButton(row) {
        row = ( row >= buttonArray.length ) ? buttonArray.length-1 : row;
        for ( var i = row; i < buttonArray.length; i--) {
            if (buttonArray[i].visible) return buttonArray[i];
        }
        return buttonArray[0];
    }

    Keys.onPressed: {
        if (event.key === Qt.Key_Up) {
            meetTopBoundary(0);
            event.accepted = true;
        } else if (event.key === Qt.Key_Down) {
            meetBottomBoundary();
            event.accepted = true;
        } else if (event.key === Qt.Key_Left) {
            meetLeftBoundary(CommonVariables.savedFocusItem.row);
            event.accepted = true;
        } else if (event.key === Qt.Key_Right) {
            meetRightBoundary(CommonVariables.savedFocusItem.row);
            event.accepted = true;
        }
    }

    Column {
        spacing: commonStyle.left.cellSpace

        /* Language Button */
        ButtonBase {
            id: languageChangeButton
            objectName: "languageChangeButton"

            property int row: 0

            text: currLanguage

            onReleased: {
                changeLanguage();
            }

            function changeLanguage() {
                console.warn( "@@@@@@@@ VKB JPN btn released" + requestChangeLanguage);
                requestChangeLanguage = true;
                languageChangeButton.state = Qt.binding(function(){
                    return requestChangeLanguage ? "Disable" : "Normal";
                })

                shiftButton.state = "Hiragana";
                clickLanguageButton();
            }

            width: root.width
            height: commonStyle.left.cellHeight

            KeyNavigation.down: symbolButton
        }

        /* Symbol Button */
        ButtonBase {
            id: symbolButton
            objectName:"symbolButton"

            property int row: 1

            text: (root.state === "Symbol") ? Variables.HiraganaCaption : Variables.FullWidthSymbolCaption
            onReleased: {
                switch (root.state) {
                case "Hiragana":
                case "Katakana":
                case "FullWidth-English":
                case "FullWidth-English-Shift":
                case "FullWidth-English-Shift-Lock":
                    root.state = "Symbol";
                    supportShiftMode = false;
                    setSymbolMode();
                    break;
                case "Symbol":
                    root.state = "Hiragana";
                    unsetSymbolMode();
                    break;
                default:
                    break;
                }
                clickInputCharacterChangeButton();
            }

            width: root.width
            height: commonStyle.left.cellHeight

            KeyNavigation.up: languageChangeButton
            KeyNavigation.down: inputModeToggleButton
            Keys.onPressed: {
                if (event.key === Qt.Key_Down && inputModeToggleButton.visible === false) {
                    meetBottomBoundary();
                    event.accepted = true;
                }
            }
        }

        /* Input Mode Toggle Button */
        ButtonBase {
            id: inputModeToggleButton
            objectName: "inputModeToggleButton"

            property int row: 2

            visible: (root.state !== "Symbol") ? true : false;
            text: {
                switch (root.state) {
                case "Hiragana":
                    return Variables.KatakanaCaption;
                case "Symbol":
                    return Variables.HiraganaCaption;
                case "Katakana":
                    return Variables.FullWidthEnglishCaption;
                case "FullWidth-English":
                case "FullWidth-English-Shift":
                case "FullWidth-English-Shift-Lock":
                    return Variables.HiraganaCaption;
                }
            }

            onReleased: {
                switch (root.state) {
                case "Hiragana":
                    root.state = "Katakana";
                    break;
                case "Katakana":
                    root.state = "FullWidth-English";
                    supportShiftMode = true;
                    break;
                case "FullWidth-English":
                case "FullWidth-English-Shift":
                case "FullWidth-English-Shift-Lock":
                    root.state = "Hiragana";
                    supportShiftMode = false;
                    break;
                }
                clickInputCharacterChangeButton();
            }

            width: root.width
            height: commonStyle.left.cellHeight

            KeyNavigation.up: symbolButton
            KeyNavigation.down: shiftButton
            Keys.onPressed: {
                if (event.key === Qt.Key_Down && !supportShiftMode) {
                    meetBottomBoundary();
                    event.accepted = true;
                }
            }
        }

        /* Shift Button */
        ButtonBase {
            id: shiftButton
            objectName: "shiftButton"

            property int row: 3
            property url iconOff:  "qrc:///images/shift.png"
            property url iconDown: "qrc:///images/shift-dark.png"
            property url iconOn:   "qrc:///images/shift-on.png"
            property url iconOnFocus: "qrc:///images/shift-on-focused.png"

            visible: supportShiftMode ? true : false
            image: {
                var icon = iconOff;
                switch (state) {
                case "":
                case "Normal":
                    if (root.state === "FullWidth-English-Shift" || root.state === "FullWidth-English-Shift-Lock")
                        icon = iconOn;
                    break;
                case "Focus":
                    if (root.state === "FullWidth-English-Shift" || root.state === "FullWidth-English-Shift-Lock")
                        icon = iconOnFocus;
                    break;
                case "Select":
                    icon = (commonStyle.webosVariant === "standard") ? iconDown : iconOnFocus;
                    break;
                case "Disable":
                    icon = "";
                    break;
                default:
                    icon = iconOff;
                }
                return icon;
            }

            onReleased: {
                switch (root.state) {
                case "Hiragana":
                case "Katakana":
                case "Symbol":
                    break;
                case "FullWidth-English":
                    root.state = "FullWidth-English-Shift";
                    break;
                case "FullWidth-English-Shift":
                    root.state = "FullWidth-English-Shift-Lock";
                    shiftButton.locked = true;
                    break;
                case "FullWidth-English-Shift-Lock":
                    root.state = "FullWidth-English";
                    shiftButton.locked = false;
                    break;
                }
                clickInputCharacterChangeButton();
            }
            onEntered: {
                if (root.state == "FullWidth-English-Shift-Lock")
                    state = "Focus"
            }
            width: root.width
            height: commonStyle.left.cellHeight

            KeyNavigation.up: inputModeToggleButton
        }
    }

    states: [
        State { name: "Hiragana" },
        State { name: "Katakana" },
        State { name: "FullWidth-English"; StateChangeScript { script: setToDefault() } },
        State { name: "FullWidth-English-Shift" },
        State { name: "FullWidth-English-Shift-Lock" },
        State { name: "Symbol" }
    ]

    function setToDefault() {
        shiftButton.state = "Normal";
        clickInputCharacterChangeButton();
        shiftButton.locked = false;

        if (shiftButton.state === "Disable")
            return;
        else if (shiftButton.focus)
            shiftButton.state = "Focus"
        else
            shiftButton.state = "Normal";
    }

    Connections {
        target: PluginProxy
        onKeyReleased : {
            if (isReleased && (languageChangeButton.state === "Select"))
                languageChangeButton.state = "Focus";
            else if (isReleased && (symbolButton.state === "Select"))
                symbolButton.state = "Focus";
            else if (isReleased && (inputModeToggleButton.state === "Select"))
                inputModeToggleButton.state = "Focus";
            else if (isReleased && (shiftButton.state === "Select"))
                shiftButton.state = "Focus";
        }
        onLanguageChanged: {
            console.warn("onLanguageChanged on leftFunctionAreaJapanese");
            requestChangeLanguage = false;
        }

    }
}
