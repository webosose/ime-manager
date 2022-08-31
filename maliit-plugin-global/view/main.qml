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
import "StringResource"

Rectangle {
    id: root
    objectName: "mainGlPlugin"
    enabled: false
    y: screenHeight + 1000;

    // Keyboard App Id for Luna Service
    property string appId: PluginProxy.maliitServiceId + ".globalPlugin"

    property QtObject style: Style {id: commonStyle}
    property QtObject styleFhd: Style {id: commonStyleFhd}
    property QtObject styleHd: StyleHd {id: commonStyleHd}
    property QtObject globalStyle: GlobalStyle {id: globalStyle}
    property QtObject globalStyleFhd: GlobalStyle {id: globalStyleFhd}
    property QtObject globalStyleHd: GlobalStyleHd {id: globalStyleHd}
    property QtObject globalStringModel: StringModel {}
    property string label    : ""
    property string langCode : ""
    property string audioGuidance: "off"
    property bool pointerVisible : false
    property bool setFocusFirstAfterEnabled : false
    property int contentType: PluginProxy.contentType
    property bool hiddenText: PluginProxy.hiddenText
    property int inputSource: PluginProxy.inputSource
    property int enterKeyType: PluginProxy.enterKeyType
    property int windowWidth: Screen.width
    property int windowHeight: ((Screen.width >= 1920 && Screen.height >= 1080) || (Screen.width >= 1080 && Screen.height >= 1920))? 324 : 217
    property int screenHeight: Screen.height
    property string resolution: (windowHeight > 242) ? "fhd" : "hd"
    signal keyPressed(string rawcode, bool shift, int eventType)
    signal textKeyPressed(string text)
    signal switchContext()
    signal clearAllPressed()
    signal moveCursorPosition(int direction,int eventType)
    signal showRequested(bool reset)
    signal hideRequested(bool reset)
    signal keysymPressed(string keysym, int eventType)
    signal meetTopBoundary()

    color: style.bgColor

    property real xScale: Screen.width/style.keyboardDefaultWidth
    transform: Scale {xScale: root.xScale; origin.x: root.width/2;} //TODO: Simple decision for now

    function setFocusToEnter() {
        if (state === "Normal-Keyboard")
            normalKeyboard.setFocusToEnter();
        else if (state === "Number-Keyboard")
            numberKeyboard.setFocusToEnter();
    }

    function setFoucusToHID() {
        hidWidget.setFocusToHID();
    }

    function reset() {
        normalKeyboard.setToDefault();
        numberKeyboard.setToDefault();
    }

    Component.onCompleted: {
        audioService.getAudioGuidance();
    }

    onStateChanged: root.reset()

    onWindowWidthChanged: {
        PluginProxy.resetPanelHeight();
    }

    onResolutionChanged: {
        if (resolution == "hd") {
            root.style = root.styleHd
            root.globalStyle = root.globalStyleHd
            hidWidget.globalStyle = root.globalStyleHd
        } else {
            root.style = root.styleFhd
            root.globalStyle = root.globalStyleFhd
            hidWidget.globalStyle = root.globalStyle
        }
    }

    onSetFocusFirstAfterEnabledChanged: {
        console.warn("onSetFocusAfterEnabledChanged : " + setFocusFirstAfterEnabled);
        if (setFocusFirstAfterEnabled){
            setDefaultFocusOnVirtualKeybaord();
            setFocusFirstAfterEnabled = false;
        }
    }

    // Normal Keyboard
    NormalKeyboard {
        id: normalKeyboard
        objectName: "normalKeyboard"
        contentType: root.contentType
        enterKeyType: root.enterKeyType
        width: style.keyboardDefaultWidth
        height: style.keyboardDefaultHeight
        anchors.horizontalCenter: parent.horizontalCenter
        enabled: false
        y: windowHeight

        // slots
        onKeyPressed: root.keyPressed(rawcode, shift, eventType)
        onKeysymPressed: root.keysymPressed(keysym, eventType)
        onTextKeyPressed: root.textKeyPressed(text)
        onChangeLanguage: {
            root.switchContext()
        }
        onClearAllPressed: root.clearAllPressed()
        onTtsService: ttsService.speakButton(text)

        onMeetTopBoundary: root.meetTopBoundary()
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
        onTtsService: ttsService.speakButton(text)
    }

    // HID Prediction
    HidPredictionWidget {
        id: hidWidget
        objectName: "hidWidget"
        width: style.keyboardDefaultWidth
        height: root.globalStyle.hidPrediction.height
        anchors.horizontalCenter: parent.horizontalCenter
        enabled: false
        y: windowHeight

        Keys.onPressed: onSendKey(event.key)
    }

    Service {
        id: lunaService
        appId: root.appId

        function showLanguageNotification(language) {
            var param = "";
            param += ("\"sourceId\":\"" + appId + "\"");
            param += (",\"message\":\"" + language + "\"");
            param += (",\"noactions\":\"true\"");
            call("palm://com.webos.notification", "/createToast", "{" + param + "}");
        }
    }
    /* Service : TTS Service Control */
    Service {
        id: ttsService
        property bool visible : PluginProxy.visible

        appId: root.appId
        service: "com.webos.service.tts"
        method: "speak"
        onResponse: console.warn("@@@ VKB TTS onResponse @@@")
        onError: console.warn("@@@ VKB TTS onError @@@")
        function speakButton(value) {
            console.warn("= = = = = = = = = = = = = = = @@@ VKB TTS @@@ t:" + value + ", a:" + audioGuidance + ",langCode:" + langCode + ", p:" + pointerVisible + ", visible : " + visible);
            console.warn("= = = = = = = = = = = = = = = @@@ VKB TTS @@@ translatorLocale : " +  PluginProxy.translatorLocale);
            var text =globalStringModel.getPronounceByChar(value);
            console.warn("= = = = = = = = = = = = = = = @@@ VKB TTS @@@ text : " + text);
            if (visible && pointerVisible === false &&  audioGuidance === "on") {
                if (setFocusFirstAfterEnabled == true) {
                    return;
                }
                callService({"text" : text, "clear" : true, "language" : (state === "Number-Keyboard") ? PluginProxy.translatorLocale : langCode})
            }
        }
    }

    /* Service : Audio Guidance Control */
    Service {
        id: audioService
        appId: root.appId
        service: "com.webos.settingsservice"
        method: "getSystemSettings"
        onResponse: {
            var jsonObject

            if (method.toString() && method.toString() === "getSystemSettings") {
                jsonObject = JSON.parse(payload);
                if (jsonObject && typeof jsonObject.settings !== 'undefined' && typeof jsonObject.settings.audioGuidance !== 'undefined') {
                    root.audioGuidance = jsonObject.settings.audioGuidance
                }
            }
        }
        function getAudioGuidance() {
            callService({"subscribe" : true, "keys" : ["audioGuidance"], "category" : "option"})
        }
    }

    Keys.onPressed: {
        if (CommonVariables.savedFocusItem && CommonVariables.savedFocusItem.visible) {
            CommonVariables.savedFocusItem.focus = true;
        }
        if (event.key === Qt.Key_Up) {
            hideRequested(true);
            event.accepted = true;
        }
    }

    onMeetTopBoundary: hideRequested(true);

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
                script: PluginProxy.resetPanelHeight();
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
                script: PluginProxy.setPanelHeight(numberKeyboard.height);
            }
        },
        State {
            name: "Hid-Prediction"; extend: "Active"
            when: inputSource === 0 && Prediction.list.length > 0 && (contentType !== Maliit.UrlContentType && contentType !== Maliit.EmailContentType)
            PropertyChanges {
                target: hidWidget
                enabled: true
                y: 0
                focus: true
            }
            StateChangeScript {
                script: PluginProxy.setPanelHeight(hidWidget.height);
            }
        },
        State {
            name: "Hide"
            when: inputSource === 0 && (Prediction.list.length === 0 || contentType === Maliit.UrlContentType || contentType === Maliit.EmailContentType)
            StateChangeScript {
                script: hideRequested(false)
            }
        }
    ]

    Connections {
        target: PluginProxy
        onLanguageChanged: {
            root.label = (langCode === "ko") ? "KOR" : label;
            root.langCode = langCode;

            normalKeyboard.setLanguage(language, label, langCode, data);
        }
        onShowLanguageNotification: {
            lunaService.showLanguageNotification(label)
        }

        onVisibleChanged: {
            if (!visible) {
                root.reset();
                if (state === "Normal-Keyboard")
                    normalKeyboard.setDefaultFocus();
                else if (state === "Number-Keyboard")
                    numberKeyboard.setDefaultFocus();
            } else {
                console.warn("At visible changed, State : " + state);
                setFocusFirstAfterEnabled = Qt.binding(function(){
                    return state === "Normal-Keyboard" ? normalKeyboard.enabled : numberKeyboard.enabled;
                })
            }
        }

        onLanguageCountChanged: {
            normalKeyboard.activateLanguageButton = (languageCount > 1) ? true : false
        }
        onForceFocusTo: {
            switch (label) {
            case "Enter":
                setFocusToEnter();
                break;
            case "HID":
                setFoucusToHID();
                break;
            default:
                break;
            }
        }
        onResetRequested: root.reset()
        onTranslatorChanged: {
            style.setFontForMenuLocale(PluginProxy.translatorLocale)
            if (speakLanguage == false) return;
            if (inputSource == 0 || visible == false) return; // because reading lang name through toast popup
            ttsService.speakButton(globalStringModel.getStringLangCode(langCode));
        }
        onCursorVisibleChanged: {
            console.warn("IMEManager cursor visible : " + cursorVisible);
            root.pointerVisible = cursorVisible;
            setDefaultFocusOnVirtualKeybaord();
       }
       onHidNavKeysPressed: {
            setDefaultFocusOnVirtualKeybaord();
       }
    }

    function setDefaultFocusOnVirtualKeybaord() {
        if (root.pointerVisible)
            CommonVariables.savedFocusItem.focus = false;
        else if (CommonVariables.savedFocusItem && CommonVariables.savedFocusItem.visible) {
            CommonVariables.savedFocusItem.focus = true;
            CommonVariables.savedFocusItem.releaseButton();
        }
        else if (state === "Normal-Keyboard")
            normalKeyboard.setDefaultFocus();
        else if (state === "Number-Keyboard")
            numberKeyboard.setDefaultFocus();
    }
}
