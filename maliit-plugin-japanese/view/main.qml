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
import QtQuick.Window 2.2

import com.meego.maliit 1.0
import WebOSServices 1.0

import "japanesestyle.js" as JapaneseStyle
import "../keyboard-common/commonvariables.js" as CommonVariables
import "../keyboard-common"

Rectangle {
    id: root
    objectName: "mainJpPlugin"
    enabled: false

    // Keyboard App Id for Luna Service
    property string appId: PluginProxy.maliitServiceId + ".japanese"

    property Style style: Style {id: commonStyle}
    property int contentType: PluginProxy.contentType
    property int inputSource: PluginProxy.inputSource
    property int hidMode: PluginProxy.hidMode
    property int windowHeight: JapaneseStyle.windowHeight
    property bool hiddenText: PluginProxy.hiddenText
    property int enterKeyType: PluginProxy.enterKeyType
    property int windowWidth: Screen.width
    property bool pointerVisible: false
    property bool setFocusFirstAfterEnabled: false

    color: style.bgColor

    signal keyPressed(string rawcode, bool shift, int eventType)
    signal textKeyPressed(string text)
    signal switchContext()
    signal clearAllPressed()
    signal clickInputCharacterChangeButton(string mode)
    signal setHidModeFromVkb(int mode)
    signal showRequested(bool reset)
    signal hideRequested(bool reset)
    signal switchSymbolMode(bool isSymbol)
    signal meetTopBoundary()
    signal moveCursorPosition(int direction, int eventType)

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

    function setFocusToHID() {
        hidWidget.setFocusToHID();
    }

    function inputModeReset() {
        if (state === "Normal-Keyboard") {
            normalKeyboard.setToDefault();
        } else if (state === "Number-Keyboard") {
            numberKeyboard.setToDefault();
        }
        root.switchSymbolMode(false);
    }

    property real xScale: Screen.width/style.keyboardDefaultWidth
    transform: Scale {xScale: root.xScale; origin.x: root.width/2;} //TODO: Simple decision for now

    onWindowWidthChanged: {
        PluginProxy.resetPanelHeight();
    }

    // Normal Keyboard
    NormalKeyboard {
        id: normalKeyboard
        objectName: "normalKeyboard"
        enterKeyType: root.enterKeyType
        width: commonStyle.keyboardDefaultWidth
        height: JapaneseStyle.windowHeight
        anchors.horizontalCenter: parent.horizontalCenter
        enabled: false
        y: windowHeight
        // slots
        onKeyPressed: root.keyPressed(rawcode, shift, eventType)
        onChangeLanguage: root.switchContext()
        onActivateSTT: root.activateSTT()
        onClearAllPressed: root.clearAllPressed()
        onClickInputCharacterChangeButton: {
            root.clickInputCharacterChangeButton(mode);
            mode === "Hiragana"
                    ? PluginProxy.resetPanelHeight()
                    : PluginProxy.setPanelHeight(JapaneseStyle.windowHeightKatakanaAndEnglish);
        }
        onChangeToSymbolMode: {
            root.switchSymbolMode(true);
        }
        onChangeToHiraganaMode: {
            root.switchSymbolMode(false);
        }
        onMeetTopBoundary: hideRequested(true)
        onMeetBottomBoundary: hideRequested(true)
    }

    // Number Keyboard
    NumberKeyboard {
        id: numberKeyboard
        objectName: "numberKeyboard"
        width: commonStyle.keyboardDefaultWidth
        height: commonStyle.numberKeyboard.height
        anchors.horizontalCenter: parent.horizontalCenter
        enabled: false
        y: windowHeight

        // slots
        onSendKey: root.keyPressed(keycode, shift, eventType)
        onSendText: root.textKeyPressed(text)

        onMeetTopBoundary: hideRequested(true)
        onMeetBottomBoundary: hideRequested(true)
    }

    // HID Prediction
    HidPredictionWidget {
        id: hidWidget
        objectName: "hidWidget"
        width: commonStyle.keyboardDefaultWidth
        height: JapaneseStyle.hidPrediction.height
        anchors.horizontalCenter: parent.horizontalCenter
        enabled: false
        y: windowHeight

        onSetHidModeFromVkb: root.setHidModeFromVkb(mode)
        Keys.onPressed: onSendKey(event.key)
    }

    Keys.onPressed: {
//#IF_COMMERCIAL
        if (event.key === Qt.Key_Cancel || event.key === Qt.Key_Up) {
//#ELSE
/*
        if (event.key === Qt.Key_Cancel) {
*/
//#END
            hideRequested(true);
            event.accepted = true;
        }
    }

    states: [
        State {
            name: "Active"
            PropertyChanges {
                target: root
                enabled: true
                y: 0
            }
            StateChangeScript {
                script:showRequested(false)
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
                script: PluginProxy.resetPanelHeight()
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
                script: PluginProxy.setPanelHeight(numberKeyboard.height)
            }
        },
        State {
            name: "Hid-Prediction"; extend: "Active"
            when: inputSource === 0 && Prediction.list.length > 0
            PropertyChanges {
                target: hidWidget
                enabled: true
                head: 0
                y: 0
                focus: true
            }
            StateChangeScript {
                script: PluginProxy.setPanelHeight(JapaneseStyle.hidPrediction.height)
            }
        },
        State {
            name: "Hide"
            when: inputSource === 0 && Prediction.list.length === 0
            StateChangeScript {
                script: hideRequested(false)
            }
        }
    ]

    Connections {
        target: PluginProxy
        onVisibleChanged: {
            console.warn("IMEManager JP visible : " + visible);
            if (!visible) {
                root.switchSymbolMode(false);
                // reset height Normal-Keyboard only - WOSLQEVENT-44774
                if (state == "Normal-Keyboard")
                    normalKeyboard.setToDefault();
                else if (state === "Number-Keyboard")
                    numberKeyboard.setDefaultFocus();
            } else {
                setFocusFirstAfterEnabled = Qt.binding(function(){
                    return state === "Normal-Keyboard" ? normalKeyboard.enabled : numberKeyboard.enabled;
                })
            }
        }
        onLanguageChanged: {
            commonStyle.setDefaultFont("ja");
            root.inputModeReset();
        }
        onHidModeChanged: hidWidget.setHidModeFromHid(hidMode)
        onUnfixedStatusChanged: normalKeyboard.setEnterKeyText(unfixedStatus)
        onCursorVisibleChanged: {
            console.warn("IMEManager cursor visible : " + cursorVisible);
            root.pointerVisible = cursorVisible;
            setDefaultFocusOnVirtualKeybaord();
        }
        onContentTypeChanged: {
            if (contentType === Maliit.NumberContentType || contentType === Maliit.PhoneNumberContentType) {
                hidWidget.setHidModeforNumberContent();
            }
        }
        onForceFocusTo: {
            switch (label) {
            case "Enter":
                setFocusToEnter();
                break;
            case "HID":
                setFocusToHID();
                break;
            default:
                break;
            }
        }
    }

    function setDefaultFocusOnVirtualKeybaord() {
        if (root.pointerVisible && CommonVariables.savedFocusItem)
            CommonVariables.savedFocusItem.focus = false;
        else if (CommonVariables.savedFocusItem && CommonVariables.savedFocusItem.visible)
            CommonVariables.savedFocusItem.focus = true;
        else if (state == "Normal-Keyboard")
            normalKeyboard.setDefaultFocus();
        else if (state == "Number-Keyboard")
            numberKeyboard.setDefaultFocus();
    }
}
