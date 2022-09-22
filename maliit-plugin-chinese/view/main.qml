// Copyright (c) 2013-2022 LG Electronics, Inc.
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
import QtQuick.Window 2.2

import com.meego.maliit 1.0
import WebOSServices 1.0

import "../keyboard-common"
import "../keyboard-common/commonvariables.js" as CommonVariables
import "languages.js" as Languages

Item {
    id: root
    objectName: "mainCnPlugin"
    enabled: false
    y: screenHeight + 1000

    // Keyboard App Id for Luna Service
    property string appId: PluginProxy.maliitServiceId + ".chinese"

    property QtObject style: Style {id: commonStyle}
    property QtObject styleFhd: Style {id: commonStyleFhd}
    property QtObject styleHd: StyleHd {id: commonStyleHd}
    property QtObject chineseStyle: ChineseStyle {id: chineseStyle}
    property QtObject chineseStyleFhd: ChineseStyle {id: chineseStyleFhd}
    property QtObject chineseStyleHd: ChineseStyleHd {id: chineseStyleHd}
    property bool pointerVisible: false
    property bool setFocusFirstAfterEnabled: false
    property int contentType: Keyboard.contentType
    property bool hiddenText: Keyboard.hiddenText
    property int inputSource: Keyboard.inputSource
    property int enterKeyType: Keyboard.enterKeyType
    property int windowWidth: Screen.width
    property int windowHeight: ((Screen.width >= 1920 && Screen.height >= 1080) || (Screen.width >= 1080 && Screen.height >= 1920))? 324 : 217
    property int screenHeight: Screen.height
    property string resolution: (windowHeight > 242) ? "fhd" : "hd"
    signal keyPressed(string rawcode, bool shift, int eventType)
    signal textKeyPressed(string text)
    signal switchContext()
    signal clearAllPressed()
    signal showRequested(bool reset)
    signal hideRequested(bool reset)
    signal shiftPressed(string state)
    signal symbolPressed(string state)
    signal meetTopBoundary()
    signal meetBottomBoundary()
    signal moveCursorPosition(int direction, int eventType)

    property real xScale: Screen.width/style.keyboardDefaultWidth
    transform: Scale {xScale: root.xScale; origin.x: root.width/2;} //TODO: Simple decision for now

    onWindowWidthChanged: {
        PluginProxy.resetPanelHeight();
    }

    onResolutionChanged: {
        if (resolution == "hd") {
            root.style = root.styleHd
            root.chineseStyle = root.chineseStyleHd
            normalKeyboard.chineseStyle = root.chineseStyleHd
            hidWidget.chineseStyle = root.chineseStyleHd
        } else {
            root.style = root.styleFhd
            root.chineseStyle = root.chineseStyleFhd
            normalKeyboard.chineseStyle = root.chineseStyleFhd
            hidWidget.chineseStyle = root.chineseStyle
        }
    }

    onSetFocusFirstAfterEnabledChanged: {
        console.warn("onSetFocusAfterEnabledChanged : " + setFocusFirstAfterEnabled);
        if (setFocusFirstAfterEnabled){
            setDefaultFocusOnVirtualKeybaord();
            setFocusFirstAfterEnabled = false;
        }
    }

    function setFocusToEnter() {
        if (state === "Normal-Keyboard")
            normalKeyboard.setFocusToEnter();
        else if (state === "Number-Keyboard")
            numberKeyboard.setFocusToEnter();
    }

    // Normal Keyboard
    NormalKeyboard {
        id: normalKeyboard
        objectName: "normalKeyboard"
        enterKeyType: root.enterKeyType
        width: style.keyboardDefaultWidth
        height: style.keyboardDefaultHeight
        anchors.horizontalCenter: parent.horizontalCenter
        enabled: false
        y: windowHeight

        // slots
        onKeyPressed: root.keyPressed(rawcode, shift, eventType)
        onTextKeyPressed: root.textKeyPressed(text)
        onSwitchContext: root.switchContext()
        onClearAllPressed: root.clearAllPressed()
        onShiftPressed: root.shiftPressed(state)
        onSymbolPressed: root.symbolPressed(state)
    }

    // Number Keyboard
    NumberKeyboard {
        id: numberKeyboard
        objectName: "numberKeyboard"
        width: style.keyboardDefaultWidth
        height: style.numberKeyboard.height
        anchors.horizontalCenter: parent.horizontalCenter
        enabled: false
        y: windowHeight

        // slots
        onSendKey: root.keyPressed(keycode, shift, eventType)
        onSendText: root.textKeyPressed(text)
    }

    // HID Suggestion
    HidSuggestionWidget {
        id: hidWidget
        objectName: "hidWidget"
        width: style.keyboardDefaultWidth
        height: root.chineseStyle.hidSuggestion.height
        anchors.horizontalCenter: parent.horizontalCenter
        enabled: false
        y: windowHeight
        Keys.onPressed: onSendKey(event.key)
    }

    Keys.onPressed: {
        if (event.key === Qt.Key_Cancel || event.key === Qt.Key_Up) {
            hideRequested(true);
            event.accepted = true;
        }
    }

    onMeetTopBoundary: hideRequested(true);
    onMeetBottomBoundary: hideRequested(true);

    states: [
        State {
            name: "Active"
            PropertyChanges {
                target: root
                enabled: true
                y: 0
            }
            StateChangeScript {
                script: showRequested(false)
            }
        },
        State {
            name: "Normal-Keyboard"; extend: "Active"
            when: inputSource === 1 && (contentType !== Maliit.NumberContentType && contentType !== Maliit.PhoneNumberContentType)
            PropertyChanges {
                target: normalKeyboard
                enabled: true
                y: 0
                focus: true
            }
            StateChangeScript {
                script: Keyboard.resetPanelHeight();
            }
        },
        State {
            name: "Hid-Suggestion"; extend: "Active"
            when: inputSource === 0 && (Suggestion.preedit.length > 0 || Suggestion.list.length > 0)
            PropertyChanges {
                target: hidWidget
                enabled: true
                y: 0
                focus: true
            }
            StateChangeScript {
                script: Keyboard.setPanelHeight(hidWidget.height);
            }
        },
        State {
            name: "Number-Keyboard"; extend: "Active"
            when: inputSource === 1 && (contentType === Maliit.NumberContentType || contentType === Maliit.PhoneNumberContentType)
            PropertyChanges {
                target: numberKeyboard
                enabled: true
                y: 0
                focus: true
            }
            StateChangeScript {
                script: Keyboard.setPanelHeight(numberKeyboard.height);
            }
        },
        State {
            name: "Hide"
            when: inputSource === 0 && Suggestion.preedit.length === 0 && Suggestion.list.length === 0
            StateChangeScript {
                script: hideRequested(false)
            }
        }
    ]

    Connections {
        target: Keyboard

        onLanguageChanged: {
            // set the default fonts
            if (language === Languages.SIMPLIFIED_CHINESE)
                style.setDefaultFont("zh-Hans");
            else
                style.setDefaultFont("zh-Hant");

            normalKeyboard.setLanguage(language, data);
            hidWidget.setLanguage(language);
        }

        onVisibleChanged: {
            console.warn("IMEManager CN visible : " + visible);
            if (!visible) {
                if (state === "Normal-Keyboard")
                    normalKeyboard.setDefaultFocus();
                else if (state === "Number-Keyboard")
                    numberKeyboard.setDefaultFocus();
                } else {
                    setFocusFirstAfterEnabled = Qt.binding(function(){
                        return state === "Normal-Keyboard" ? normalKeyboard.enabled : numberKeyboard.enabled;
                    })
                }
            }

        onCursorVisibleChanged: {
            root.pointerVisible = cursorVisible;
            setDefaultFocusOnVirtualKeybaord();
        }

       onForceFocusTo: {
           switch (label) {
           case "Enter":
               setFocusToEnter();
               break;
           default:
               break;
           }
       }
       onHidNavKeysPressed: {
            setDefaultFocusOnVirtualKeybaord();
       }
    }

    function setDefaultFocusOnVirtualKeybaord() {
        if (root.pointerVisible) {
            if (CommonVariables.savedFocusItem)
                CommonVariables.savedFocusItem.focus = false;
        }
        else if (CommonVariables.savedFocusItem && CommonVariables.savedFocusItem.visible)
            CommonVariables.savedFocusItem.focus = true;
        else if (state == "Normal-Keyboard")
            normalKeyboard.setDefaultFocus();
        else if (state == "Number-Keyboard")
            numberKeyboard.setDefaultFocus();
    }
}

