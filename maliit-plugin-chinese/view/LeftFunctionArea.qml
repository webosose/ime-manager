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
import "languages.js" as Languages
import "../keyboard-common/commonvariables.js" as CommonVariables

Item {
    id: root
    objectName: "leftFunctionArea"
    state: "Normal"

    property string currLanguage: Languages.SIMPLIFIED_CHINESE
    property string previousState
    signal languageButtonPressed()
    signal shiftClicked(string state)
    signal symbolClicked(string state)
    signal meetLeftBoundary(int row)
    signal meetRightBoundary(int row)
    signal meetTopBoundary(int column)
    signal meetBottomBoundary(int column)

    function setKeyNavigation(row) {
        if (row === 0) languageChangeButton.focus = true;
        else if (row === 1) symbolButton.focus = true;
        else if (row === 2) shiftButton.focus = true;
        else shiftButton.focus = true;
    }

    Keys.onPressed: {
        if (event.key === Qt.Key_Up) {
            meetTopBoundary(0);
            event.accepted = true;
        } else if (event.key === Qt.Key_Down) {
            meetBottomBoundary(0);
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
        spacing: style.left.cellSpace

        /* Language Button */
        ButtonBase {
            id: languageChangeButton
            objectName: "languageChangeButton"
            property int row: 0
            text: Keyboard.languageLabel
            onClicked: {
                languageButtonPressed();
            }

            Keys.onReleased: {
                languageButtonPressed();
            }

            width: root.width
            height: style.left.cellHeight
            KeyNavigation.down: symbolButton
        }

        /* Symbol Button */
        ButtonBase {
            id: symbolButton
            objectName: "symbolButton"
            property int row: 1
            text: (root.state === "Symbol") ? (currLanguage !== Languages.SIMPLIFIED_CHINESE) ? "漢" : "中" : "+ = [ ]"
            onReleased: {
                switch (root.state) {
                case "Normal":
                    previousState = "Normal";
                    root.state = "Symbol";
                    break;
                case "Normal-Shift":
                    previousState = "Normal-Shift";
                    root.state = "Symbol";
                    break;
                case "Symbol":
                    root.state = previousState;
                    break;
                default:
                    break;
                }
                symbolClicked(root.state);
            }
            width: root.width
            height: style.left.cellHeight
            KeyNavigation.up: languageChangeButton
            KeyNavigation.down: shiftButton
        }

        /* Shift Button */
        ButtonBase {
            id: shiftButton
            objectName: "shiftButton"
            property int row: 2
            text: Keyboard.shiftLabel

            onReleased: {
                switch (root.state) {
                case "Normal":
                    root.state = "Normal-Shift";
                    break;
                case "Normal-Shift":
                    root.state = "Normal";
                    break;
                case "Symbol":
                    root.state = "Normal-Shift";
                    break;
                default:
                    break;
                }
                shiftClicked(root.state);
            }
            width: root.width
            height: style.left.cellHeight
            KeyNavigation.up: symbolButton
        }
    }

    states: [
        State {
            name: "Normal"
            when: !Keyboard.shifted
            StateChangeScript {
                script: CommonVariables.savedFocusItem = shiftButton
            }
        },
        State {
            name: "Normal-Shift"
            when: Keyboard.shifted
            StateChangeScript {
                script: CommonVariables.savedFocusItem = shiftButton
            }
        },
        State {
            name: "Symbol"
        }
    ]

    function setToDefault() {
        shiftButton.state = "Normal";
    }

    Connections {
        target: PluginProxy
        onKeyReleased : {
            if (isReleased && (languageChangeButton.state === "Select"))
                languageChangeButton.state = "Focus";
            else if (isReleased && (symbolButton.state === "Select"))
                symbolButton.state = "Focus";
            else if (isReleased && (shiftButton.state === "Select"))
                shiftButton.state = "Focus";
        }
    }
}
