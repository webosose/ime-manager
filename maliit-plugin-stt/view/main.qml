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
import QtQuick.Window 2.2

import WebOSServices 1.0

Rectangle {
    id: main
    objectName: "main"
    color: sttStyle.main.color
    visible: true

    signal textKeyPressed(string text)
    signal backToKeyboardPressed()
    signal canShowSTTView()
    signal sigSendText(string text)
    signal sigSendWarningText(string text)

    property string resolution: (WindowInformation.windowHeight > 242) ? "fhd" : "hd"
    property variant resultTextArray
    property int resultNum: 0
    property int num: 0
    property bool isShow: false
    property string currentLanguage
    property string languageParam
    property string voiceLanguage // STT Language by settings -> General -> Language -> Voice Recognition Language
    property string selectedLanguage: ""
    property int remainSeconds: 30 //storing remain seconds. default sec is 30.

    //variables for master volume control
    property int masterVolume: 0
    property bool muted: false
    property int mediaVolume: 5

    property double timeToShow:0

    property bool isCursorOn: false;

    property bool isLanguagedChanged: false;

    property WebOSKeyExtension extKey: WebOSKeyExtension {
        id: extKey
    }

    property bool isActivated: false
    property string startSTT_state: ""

    /* Global variable: Fonts */
    property int fontNormal: Font.Normal
    property int fontDemiBold: Font.DemiBold
    property int fontBold: Font.Bold
    // Museo Sans
    property string museoSans_light_fontFamily : "Museo Sans"   // for 300, 500, LG display light
    property string museoSans_regular_fontFamily : "Museo Sans" // for 700,  LG display regular
    property int museo300_fontWeight : fontNormal               //"Moon Museo Sans Light"
    property int museo500_fontWeight : fontDemiBold             //"Moon Museo Sans Medium"
    property int museo700_fontWeight : fontBold                 //"Moon Museo Sans Bold"
    property bool museo700_fontItalic : true                    //"Moon Museo Sans Bold Italic"
    // Miso
    property string miso_light_fontFamily : "Miso"              // for miso-regular, LG display light
    property string miso_regular_fontFamily : "Miso"            // for miso-bold, LG display regular
    property int misoRegular_fontWeight : fontDemiBold          //"Moon Miso Medium"
    property int misoBold_fontWeight : fontBold                 //"Moon Miso Bold"

    // RTL case check variable QT.locale().textDirection -> LTR: 0, RTL: 1
    property bool isRTL: Qt.locale(selectedLanguage).textDirection ? true : false

    // DEBUG
    readonly property bool _DEBUG: true

    //for LayoutMirroring. QT.locale().textDirection -> LTR: 0, RTL: 1
    LayoutMirroring.enabled: isRTL

    // FOREGROUND APP ID
    property string cardTypeForegroundAppId: ""         // foreground appID of Card Type Window
    property string anyTypeForegroundAppId: ""          // foreground appID of Any Type Window

    SttStyle {
        id: sttStyle
        isFHD: resolution === "fhd"
    }

    StringSet { id: stringSet }

    TTSService{ id : ttsService
        Component.onCompleted: callGetSystemSettings(); // Enabled from webOS3.0 MR Major
    }
    /* C++ Instatance
                PluginProxy             - Class STTView
                WindowInformation       - Class WindowInformation
    */
    onIsShowChanged: {
        printLog("$$$$$$$$$$$$$$windowWidth: "+WindowInformation.windowWidth+", windowHeight: "+WindowInformation.windowHeight);
        printLog("====================== STATUS MONITOR ============================");
        printLog("main.resolution: " + main.resolution);
        printLog("main.isShow: " + main.isShow);
        printLog("main.state: " + main.state);
        printLog("startSTT state: " + startSTT_state); // sttResult, sessionEnd
        printLog("==================================================================");
        if (!main.isShow) {
            resultListButton1.text = "";
            resultListButton2.text = "";
            resultListButton3.text = "";
            guideText.text = "";
            resultTextArray = undefined;
            sayAgainButton.opacity = 0;
            checkingRemainingTimeTimer.stop();
            if(needCancelAPI())
            {
                printLog("nlp cancel is called.   startSTT_state: " + startSTT_state);
                sttCancelService.call("luna://com.webos.service.nlp","/cancel","{}");
                sttService.cancel();
            }

            //Volume Restored
            printLog("\r\nVolume Restored to 100");
            mediaVolumeController.call("luna://com.webos.audio/media", "/setVolume", "{\"volume\":100}");

            selectedLanguage = "";
            langSelectListModel.clear();
            isActivated = false;
            startSTT_state = "";
        } else {
            timeToShow = Date.now();
            main.state = 'init';
            masterVolumeController.call("luna://com.webos.audio", "/getVolume", "{\"subscribe\":false}");
            startSTTPlugin();
            printWarningLog("selectedLanguage: " + selectedLanguage);
        }
    }
    onCurrentLanguageChanged: {
        printLog("=== onCurrentLanguageChanged ===")
        printLog("currentLanguage: " + currentLanguage)
        var lang = currentLanguage.slice(0,2);
        var region = currentLanguage.slice(3);
        sttStyle.reloadFontFamily(lang, region) // do job to load font here
        updateGuideLangText();
    }
    onSelectedLanguageChanged: {
        printLog("=== onSelectedLanguageChanged ===")
        printLog("selectedLanguage: " + selectedLanguage)
    }
    onVoiceLanguageChanged: { // this is called only when STT plugin is activated
        printLog("voiceLanguage : " + voiceLanguage);
    }

    LocaleString {
        id: localeString
    }

    Timer {
        id: checkingRemainingTimeTimer
        interval: 1000; running: false; repeat: true
        onTriggered: {
            remainSeconds--;
            printLog("remainSeconds : " + remainSeconds);
            if(remainSeconds === 0) {
                running = false;
                backToKeyboardPressed();
            }
        }
    }

    Rectangle {
        anchors.fill: parent
        color: sttStyle.main.bgColor
    }

    /* RESULT LIST */
    Item {
        id: resultListBox
        objectName: "resultListBox"
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        height: sttStyle.resultListBox.height
        visible: false

        function focusInit () {
            printLog("=== resultListBox focusInit() ===");
            printLog("isCursorOn: " + isCursorOn)
            focusOut();
        }
        function focusOut() {
            if(ttsService.audioGuidanceEnable || !isCursorOn)
                resultListButton1.forceActiveFocus();
        }

        Rectangle {
            anchors.fill: parent
            color: sttStyle.resultListBox.bgColor
            opacity: sttStyle.resultListBox.bgOpacity
        }

        Text {
            id: resultTitle
            objectName: "resultTitle"
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.leftMargin: sttStyle.resultTitle.leftMargin
            anchors.topMargin: sttStyle.resultTitle.topMargin
            font.pixelSize: sttStyle.resultTitle.fontSize
            font.family: miso_light_fontFamily
            font.weight: misoRegular_fontWeight
            color: sttStyle.resultTitle.fontColor
            text: stringSet.strings["VOICE RECOGNITION RESULTS"]
            opacity: 0
            //for LayoutMirroring. QT.locale().textDirection -> LTR: 0, RTL: 1
            LayoutMirroring.enabled: isRTL
            property string textToSpeech : ""
            onVisibleChanged: {
                if(visible) {
                    var result = text;
                    result += ", " + resultListButton1.text;
                    if(resultListButton2.text)
                        result += ", " + resultListButton2.text;
                    if(resultListButton3.text)
                        result += ", " + resultListButton3.text;
                    textToSpeech = result;
                }
            }
        }

        Rectangle {
            id: resultTitleLine
            objectName: "resultTitleLine"
            anchors.top: resultTitle.bottom
            anchors.topMargin: sttStyle.resultTitle.lineTopMargin
            anchors.left: parent.left
            anchors.leftMargin: sttStyle.resultTitle.leftMargin
            anchors.right: parent.right
            anchors.rightMargin: sttStyle.resultTitle.rightMargin
            height: sttStyle.resultTitle.lineHeight
            color: sttStyle.resultTitle.lineColor

            //for LayoutMirroring. QT.locale().textDirection -> LTR: 0, RTL: 1
            LayoutMirroring.enabled: isRTL
        }

        ResultListButton {
            id: resultListButton1
            objectName: "resultListButton1"
            anchors.top: resultTitleLine.bottom
            anchors.left: parent.left
            anchors.topMargin: sttStyle.resultButton.lineMargin
            anchors.leftMargin: sttStyle.resultButton.leftMargin
            anchors.right: parent.right
            anchors.rightMargin: sttStyle.resultButton.rightMargin
            text: ""
            opacity:0
            onActiveFocusChanged: {
                if(activeFocus) {
                    if(resultTitle.textToSpeech) {
                        ttsService.speakByAudioGuidance(resultTitle.textToSpeech,currentLanguage);
                        resultTitle.textToSpeech = "";
                    } else
                        ttsService.speakByAudioGuidance(textToSpeech,currentLanguage);
                }
            }
            Keys.onReleased: {
                printLog("=== resultListButton1 Keys.onReleased: === " + event.key)
                switch(event.key){
                case extKey.key_up:     // UP
                    sayAgainButton.forceActiveFocus();
                    event.accepted = true;
                    break;
                case extKey.key_right:  // RIGHT -> LTR : sayAgainButton, RTL: OWN
                    if(!isRTL) // normal(LTR) case
                        sayAgainButton.forceActiveFocus();
                    event.accepted = true;
                    break;
                case extKey.key_down:   // DOWN -> resultListButton2
                    if(resultListButton2.opacity)
                        resultListButton2.forceActiveFocus();
                    event.accepted = true;
                    break;
                case extKey.key_left:   // LEFT -> LTR: OWN.  RTL: sayAgainButton
                    if(isRTL) // RTL case
                        sayAgainButton.forceActiveFocus();
                    event.accepted = true;
                    break;
                case extKey.key_return:
                    resultListButton1.onReleasedAction();
                    event.accepted = true;
                    break;
                }
            }
        }

        SeperateLine {
            id: seperateLine1
            objectName: "seperateLine1"
            anchors.top: resultListButton1.bottom
            anchors.horizontalCenter: resultListButton1.horizontalCenter
            opacity:0
            visible: false
        }

        ResultListButton {
            id: resultListButton2
            objectName: "resultListButton2"
            anchors.top: resultListButton1.bottom
            anchors.left: parent.left
            anchors.topMargin: sttStyle.resultButton.spacing
            anchors.leftMargin: sttStyle.resultButton.leftMargin
            anchors.right: parent.right
            anchors.rightMargin: sttStyle.resultButton.rightMargin
            text: ""
            opacity:0
            onActiveFocusChanged:if(activeFocus)ttsService.speakByAudioGuidance(textToSpeech,currentLanguage)
            Keys.onReleased: {
                printLog("=== resultListButton2 Keys.onReleased: === " + event.key)
                switch(event.key){
                case extKey.key_up:     // UP -> resultListButton1
                    resultListButton1.forceActiveFocus();
                    event.accepted = true;
                    break;
                case extKey.key_down:   // DOWN -> resultListButton3
                    if(resultListButton3.opacity)
                        resultListButton3.forceActiveFocus();
                    event.accepted = true;
                    break;
                case extKey.key_left:   // LEFT -> LTR: OWN, RTL: sayAgainButton
                    if(isRTL) // RTL case
                        sayAgainButton.forceActiveFocus();
                    event.accepted = true;
                    break;
                case extKey.key_right:  // RIGHT -> LTR : sayAgainButton, RTL: OWN
                    if(!isRTL) // normal(LTR) case
                        sayAgainButton.forceActiveFocus();
                    event.accepted = true;
                    break;
                case extKey.key_return:
                    onReleasedAction();
                    event.accepted = true;
                    break;
                }
            }
        }

        ResultListButton {
            id: resultListButton3
            objectName: "resultListButton3"
            anchors.top: resultListButton2.bottom
            anchors.left: parent.left
            anchors.topMargin: sttStyle.resultButton.spacing
            anchors.leftMargin: sttStyle.resultButton.leftMargin
            anchors.right: parent.right
            anchors.rightMargin: sttStyle.resultButton.rightMargin
            text: ""
            opacity:0
            onActiveFocusChanged:if(activeFocus)ttsService.speakByAudioGuidance(textToSpeech,currentLanguage)
            Keys.onReleased: {
                printLog("=== resultListButton3 Keys.onReleased: === " + event.key)
                switch(event.key){
                case extKey.key_up:     // UP -> resultListButton2
                    resultListButton2.forceActiveFocus();
                    event.accepted = true;
                    break;
                case extKey.key_left:   // LEFT -> LTR: OWN, RTL: sayAgainButton
                    if(isRTL) // RTL case
                        sayAgainButton.forceActiveFocus();
                    event.accepted = true;
                    break;
                case extKey.key_right:  // RIGHT -> LTR : sayAgainButton, RTL: OWN
                    if(!isRTL) // normal(LTR) case
                        sayAgainButton.forceActiveFocus();
                    event.accepted = true;
                    break;
                case extKey.key_down:   // DOWN -> resultListButton3
                    resultListButton3.forceActiveFocus();
                    event.accepted = true;
                    break;
                case extKey.key_return:
                    onReleasedAction();
                    event.accepted = true;
                    break;
                }
            }
        }

        SeperateLine {
            id: seperateLine3
            objectName: "seperateLine3"
            anchors.top: resultListButton3.bottom
            anchors.horizontalCenter: resultListButton3.horizontalCenter
            opacity:0
            visible: false
        }

        SayAgainButton {
            id: sayAgainButton
            objectName: "sayAgainButton"
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.topMargin: sttStyle.sayAgainButton.topMargin
            anchors.rightMargin: sttStyle.sayAgainButton.rightMargin
            opacity:0

            onActiveFocusChanged:if(activeFocus)ttsService.speakByAudioGuidance(textToSpeech,currentLanguage)

            Keys.onReleased: {
                printLog("=== sayAgainButton Keys.onReleased: === " + event.key)
                switch(event.key){
                case extKey.key_up:     // UP
                    forceActiveFocus()
                    event.accepted = true;
                    break;
                case extKey.key_down:   // DOWN
                    resultListButton1.forceActiveFocus();
                    event.accepted = true;
                    break;
                case extKey.key_left:   // LEFT -> LTR: resultListButton1. RTL -> OWN
                    if(!isRTL)
                        resultListButton1.forceActiveFocus();
                    event.accepted = true;
                    break;
                case extKey.key_right:  // RIGHT -> LTR: OWN, RTL: resultListButton1
                    if(isRTL)
                        resultListButton1.forceActiveFocus();
                    break;
                case extKey.key_return:
                    sayAgainButton.onReleasedAction();
                    event.accepted = true;
                    break;
                }
            }
        }
        Keys.onReleased: {
            printLog("=== resultBox Keys.onReleased: === " + event.key)
            switch(event.key){
            case extKey.key_up:
                sayAgainButton.forceActiveFocus()
                event.accepted = true;
                break;
            case extKey.key_right:
                if(isRTL) {
                    resultListButton1.forceActiveFocus();
                } else {
                    sayAgainButton.forceActiveFocus();
                }
                event.accepted = true;
                break;
            case extKey.key_down:
                resultListButton1.forceActiveFocus();
                event.accepted = true;
                break;
            case extKey.key_left:
                if(isRTL) {
                    sayAgainButton.forceActiveFocus();
                } else {
                    resultListButton1.forceActiveFocus();
                }
                event.accepted = true;
                break;
            }
        }
    }

    Rectangle {
        id: micBackground
        objectName: "micBackground"
        anchors.bottom: parent.bottom
        width: parent.width
        height: sttStyle.micBackground.height
        color: sttStyle.micBackground.bgColor
        opacity: 0.8
    }

    MicImage {
        id: micRec
        objectName: "micRec"
        anchors.centerIn: micBackground
        opacity:1
        property string textToSpeech : stringSet.strings["Speech to text"] + " " + stringSet.strings["button"]
        onEntered: {
            printLog("=== micRec's onEntered ===")
            if(main.state === "event_error") {
                micRec.forceActiveFocus()
            }
        }
        onExited: {
            printLog("=== micRec's onExited ===")
            main.forceActiveFocus()
        }
        onClicked: onClickedAction()
        onActiveFocusChanged: {
            if(micRec.activeFocus){
                remainSeconds = 30
                ttsService.speakByAudioGuidance(textToSpeech, currentLanguage)
            }
        }
        Keys.onReleased: {
            printLog("=== micRec Keys.onReleased: === " + event.key)
            switch(event.key){
            case extKey.key_up:
                guideRetryButton.forceActiveFocus()
                event.accepted = true;
                break;
            case extKey.key_left:
            case extKey.key_right:
            case extKey.key_down:
                forceActiveFocus();
                event.accepted = true;
                break;
            case extKey.key_return:
                micRec.onClickedAction();
                event.accepted = true;
                break;
            }
        }
        function onClickedAction() {
            printLog("=== micRec's onClickedAction ===")
            printLog("main.state: " + main.state)
            if(main.state === "event_error"){
                printLog("restart STT")
                main.forceActiveFocus();
                restartSttService();
            }
        }
    }

    Text {
        id: guideLangText
        objectName: "guideLangText"
        anchors.bottom: micBackground.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottomMargin: sttStyle.guideLangText.bottomMargin
        font.family: museoSans_light_fontFamily
        font.weight: museo500_fontWeight
        font.pixelSize: sttStyle.guideLangText.fontSize
        color: sttStyle.guideText.fontColor
        property string imgString: "<img src=\"images/stt_icon_keyhelp_red.png\">"
        property string spacing: ""
        property string imgStringName: stringSet.strings["Red Button"]
        text: stringSet.strings["Press %1%2 to change language."].arg(imgString).arg(spacing)
        property string textToSpeech: stringSet.strings["Press %1%2 to change language."].arg(imgStringName).arg("")
    }

    Image {
        id: guideImage
        objectName: "guideImage"
        anchors.right: guideText.left
        anchors.rightMargin: sttStyle.guideImage.rightMargin
        anchors.verticalCenter: guideText.verticalCenter
        source: "images/nlp_sequence_error_icon.png"
        visible: false
        LayoutMirroring.enabled: isRTL
    }

    Text {
        id: guideText
        objectName: "guideText"
        anchors {
            left: parent.left; leftMargin: sttStyle.guideText.leftMargin
            right: parent.right; rightMargin: sttStyle.guideText.rightMargin
            top: parent.top
            topMargin: {
                if(guideLangText.visible)
                    return sttStyle.guideText.topMarginReady
                else if (guideRetryButton.visible)
                    return (parent.height - (guideText.contentHeight + guideRetryButton.height + guideRetryButton.anchors.topMargin))/2
                else {
                    return sttStyle.guideText.topMarginInitError
                }
            }
        }
        horizontalAlignment: Text.AlignHCenter
        wrapMode: Text.Wrap
        font.pixelSize: sttStyle.guideText.fontSize
        font.family: museoSans_light_fontFamily
        font.weight: museo500_fontWeight
        color: sttStyle.guideText.fontColor
        text: ""
        property string textToSpeech: text
        onVisibleChanged: {
            if(visible) callTTS();
            else text = "";
        }
        onTextToSpeechChanged: callTTS();
        function callTTS() {
            if(!(text && visible)) return;
            if(!guideLangText.visible)
                ttsService.speakByAudioGuidance(textToSpeech, currentLanguage);

            if (main.state === "event_error") {
                guideRetryButton.clearPrevSpeech = false;
                guideRetryButton.forceActiveFocus();
            }
        }
    }

    // Button OK
    SayAgainButton {
        id: guideRetryButton
        objectName: "guideRetryButton"
        anchors.top: guideText.bottom
        anchors.topMargin: sttStyle.guideRetryButton.topMargin
        anchors.horizontalCenter: parent.horizontalCenter
        visible: false

        buttonLeftNormalImg : "images/stt_small_btn_n_l.png"
        buttonMidNormalImg : "images/stt_small_btn_n_m.png"
        buttonRightNormalImg : "images/stt_small_btn_n_r.png"
        buttonLeftFocusImg : "images/stt_small_btn_f_l.png"
        buttonMidFocusImg : "images/stt_small_btn_f_m.png"
        buttonRightFocusImg : "images/stt_small_btn_f_r.png"
        textFontColor : "#a6a6a6"
        textFontFocusColor : sttStyle.sayAgainButton.focusFontColor
        property bool clearPrevSpeech: true

        onActiveFocusChanged: {
            if (activeFocus) {
                ttsService.speakByAudioGuidance(textToSpeech,currentLanguage, clearPrevSpeech);
                clearPrevSpeech = true;
            }
        }

        Keys.onReleased: {
            printLog("=== guideRetryButton Keys.onReleased: === " + event.key)
            switch(event.key){
            case extKey.key_up:
            case extKey.key_left:
            case extKey.key_right:
            case extKey.key_down:
                forceActiveFocus()
                event.accepted = true;
                break;
            case extKey.key_return:
                sayAgainButton.onReleasedAction();
                event.accepted = true;
                break;
            }
        }
    }
    // LANGUAGE SELECT BOX
    Item {
        id: langSelectBox
        objectName: "langSelectBox"
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        height: sttStyle.langSelectBox.height
        visible: false

        property string textToSpeech : ""

        function focusInit () {
            printLog("=== langSelectBox focusInit() ===");
            focusOut();
        }
        function focusOut () {
            printLog("=== langSelectBox ===");
            forceActiveFocus();
            langSelectListView.initialize();
        }

        Rectangle {
            anchors.fill: parent
            color: sttStyle.langSelectBox.bgColor
        }

        //for LayoutMirroring. QT.locale().textDirection -> LTR: 0, RTL: 1
        LayoutMirroring.enabled: isRTL

        property real deltaContentY: 0

        onActiveFocusChanged: if(activeFocus)remainSeconds = 30;
        onVisibleChanged: {
            if(visible) {
                var result = langSelectTitle.text;
                for(var i=0; i<langSelectListModel.count; i++) {
                    if(langSelectListModel.get(i).isSelected)
                        result += " " + langSelectListModel.get(i).languageName + " " + stringSet.strings["checked"];
                }
                textToSpeech = result;
            }
        }

        Text {
            id: langSelectTitle
            objectName: "langSelectTitle"
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.topMargin: sttStyle.langSelectTitle.topMargin
            anchors.leftMargin: sttStyle.langSelectTitle.leftMargin
            anchors.rightMargin: sttStyle.langSelectTitle.rightMargin
            font.pixelSize: sttStyle.langSelectTitle.fontSize
            font.family: miso_light_fontFamily
            font.weight: misoRegular_fontWeight
            color: sttStyle.langSelectTitle.fontColor
            text: stringSet.strings["SELECT LANGUAGE"]

            //for LayoutMirroring. QT.locale().textDirection -> LTR: 0, RTL: 1
            LayoutMirroring.enabled: isRTL

        }

        Rectangle {
            id: langSelectTitleLine
            objectName: "langSelectTitleLine"
            anchors.top: langSelectTitle.bottom
            anchors.topMargin: sttStyle.langSelectTitle.lineTopMargin
            anchors.left: langSelectTitle.left
            anchors.right: langSelectTitle.right
            height: sttStyle.langSelectTitle.lineHeight
            color: sttStyle.langSelectTitle.lineColor

            //for LayoutMirroring. QT.locale().textDirection -> LTR: 0, RTL: 1
            LayoutMirroring.enabled: isRTL
        }
        ListView {
            id: langSelectListView
            objectName: "langSelectListView"
            anchors.top: langSelectTitleLine.top
            anchors.left: parent.left
            anchors.right: scrollBar.left
            anchors.topMargin: sttStyle.langSelectListView.topMargin
            anchors.leftMargin: sttStyle.langSelectListView.leftMargin
            anchors.rightMargin: sttStyle.langSelectListView.rightMargin
            height: sttStyle.langSelectListItem.height * 3 + sttStyle.langSelectListView.spacing * 2
            anchors.bottomMargin: sttStyle.langSelectListView.bottomMargin
            contentHeight: langSelectListModel.count*(sttStyle.langSelectListView.spacing + sttStyle.langSelectListItem.height)
            model: langSelectListModel
            currentIndex: _NOT_ON_THE_LIST
            spacing: sttStyle.langSelectListView.spacing
            highlightFollowsCurrentItem: true
            clip: true
            boundsBehavior: Flickable.StopAtBounds
            property variant targetScrollBar : scrollBar

            //for LayoutMirroring. QT.locale().textDirection -> LTR: 0, RTL: 1
            LayoutMirroring.enabled: isRTL
            LayoutMirroring.childrenInherit: isRTL

            readonly property int _NOT_ON_THE_LIST: -1

            function initialize() {
                currentIndex = _NOT_ON_THE_LIST;
                if(ttsService.audioGuidanceEnable || !isCursorOn) {
                    langSelectListView.focusToTopItem();
                    langSelectListView.forceActiveFocus();
                }
                scrollBar.updateAll();
            }
            function focusToTopItem(){
                printLog("=== langSelectListView focusToTopItem() ===");
                printLog("contentY: " + contentY);
                printLog("contentY + sttStyle.langSelectListItem.height/2 : " + contentY + sttStyle.langSelectListItem.height/2);
                var i;
                // find Item from top
                for(i = 1; i < langSelectListModel.count; i++) {
                    currentIndex = indexAt(0,contentY + (sttStyle.langSelectListItem.height/2) * i );
                    if(currentIndex != _NOT_ON_THE_LIST)
                        break;
                }
                positionViewAtIndex(currentIndex, ListView.Beginning);
                printLog("currentIndex = indexAt(0,contentY + (sttStyle.langSelectListItem.height/2) * i; " + currentIndex);
            }
            function focusToBottomItem(){
                printLog("=== langSelectListView focusToBottomItem() ===")
                // find Item from bottom
                var i;
                for(i = 1; i < langSelectListModel.count; i++) {
                    currentIndex = indexAt(0, contentY + height - (sttStyle.langSelectListItem.height/2) * i);
                    if(currentIndex != _NOT_ON_THE_LIST)
                        break;
                }
                printLog("currentIndex = indexAt(0, contentY + height - sttStyle.langSelectListItem.height/2); " + currentIndex)
                positionViewAtIndex(currentIndex, ListView.End);
            }
            onContentYChanged: {
                printLog("=== langSelectListView onContentYChanged ===")
                targetScrollBar.updateScrollButtons();
            }

            onCurrentIndexChanged: {
                printLog("=== onCurrentIndexChanged ===")
                printLog("langSelectListView.currentIndex: " + currentIndex)

            }

            delegate: Item {
                id: langSelectListItemUI // this is the LIST ITEM COMPONENT developer thinks. It has full width and check image
                objectName: "langSelectListItemUI"
                width: parent.width
                height: sttStyle.langSelectListItem.height
                property ListView parentListObject: langSelectListView
                property int itemIndex: index
                property real centerY : y + height/2
                property string textToSpeech : {
                    if(isSelected)
                        return langItemText.text + " " + stringSet.strings["checked"];
                    else
                        return langItemText.text + " " + stringSet.strings["unchecked"];
                }
                function checkedFocus(){
                    printLog("=== checkedFocus() index " + itemIndex + "===")

                    if(langSelectListView.currentIndex === itemIndex){
                        langSelectListItem.forceActiveFocus()
                        printLog("langSelectListItem.activeFocus " + langSelectListItem.activeFocus)

                    }
                }

                Component.onCompleted: {
                    langSelectListView.onCurrentIndexChanged.connect(checkedFocus)
                }
                Component.onDestruction: {
                    langSelectListView.onCurrentIndexChanged.disconnect(checkedFocus)
                }

                // UI object that has actual width and height
                Item {
                    id: langSelectListItemActualUI
                    objectName: "langSelectListItemActualUI"
                    anchors.left: parent.left
                    width: langSelectListItem.width + sttStyle.langSelectListItem.imgWidth + sttStyle.langSelectListItem.itemImgleftMargin*2
                    height: parent.height
                    Rectangle{
                        anchors.fill: parent
                        color: langSelectListItem.activeFocus? "#cf0652": "transparent"
                    }
                    // select image
                    Image {
                        id: langItemImg
                        objectName: "langItemImg"
                        anchors.left: parent.left
                        anchors.leftMargin: sttStyle.langSelectListItem.itemImgleftMargin
                        anchors.verticalCenter: parent.verticalCenter
                        source: "images/stt_check.png"
                        width:  sttStyle.langSelectListItem.imgWidth
                        opacity: isSelected? 1 : 0
                    }

                    MouseArea {
                        id: langSelectListItem // this is the LIST ITEM COMPONENT user thinks. It has only focusable area.
                        objectName: "langSelectListItem"
                        anchors.left: langItemImg.right
                        anchors.leftMargin: sttStyle.langSelectListItem.itemImgleftMargin
                        width: sttStyle.langSelectListItem.itemTextLeftMargin + langItemText.width + sttStyle.langSelectListItem.itemTextRightMargin
                        height: sttStyle.langSelectListItem.height
                        hoverEnabled: true
                        onEntered: {
                            printLog("=== langSelectListItem onEntered() ===")
                            if( (langSelectListItemUI.centerY >= langSelectListView.contentY) && (langSelectListItemUI.centerY <= langSelectListView.contentY + langSelectListView.height) ){
                                langSelectListView.currentIndex = itemIndex
                            }
                        }
                        onExited: {
                            langSelectListView.currentIndex = langSelectListView._NOT_ON_THE_LIST
                            langSelectBox.forceActiveFocus()
                        }
                        onClicked: {
                            onClickedAction()
                        }
                        onActiveFocusChanged:{
                            if(activeFocus){
                                if(langSelectBox.textToSpeech) {
                                    ttsService.speakByAudioGuidance(langSelectBox.textToSpeech, currentLanguage);
                                    langSelectBox.textToSpeech = "";
                                } else
                                    ttsService.speakByAudioGuidance(langSelectListItemUI.textToSpeech, currentLanguage);
                                remainSeconds = 30;
                            }
                        }
                        Text {
                            id: langItemText
                            objectName: "langItemText"
                            anchors.left: parent.left
                            anchors.leftMargin: sttStyle.langSelectListItem.itemTextLeftMargin
                            anchors.verticalCenter: parent.verticalCenter
                            color: sttStyle.langSelectListItem.fontColor
                            font.pixelSize: sttStyle.langSelectListItem.fontSize
                            font.family: museoSans_regular_fontFamily
                            font.weight: museo500_fontWeight
                            text: languageName // languageName : member variable of the item in langSelectListModel
                        }
                    }
                }
                function onClickedAction(){
                    langSelectListModel.setSelected(index)
                    ttsService.speakByAudioGuidance(langSelectListItemUI.textToSpeech,currentLanguage)
                }
                //                onIsSelectedChanged : ttsService.speakByAudioGuidance(langSelectListItemUI.textToSpeech,currentLanguage)

                Keys.onReleased: {
                    printLog("=== langSelectListView ITEM Keys.onReleased: === " + event.key)
                    switch(event.key){
                    case extKey.key_left:   // LEFT -> RTL: scrollUp or scrollDown
                        if(isRTL) {
                            parentListObject.currentIndex = parentListObject._NOT_ON_THE_LIST;
                            focusToOtherUI();
                        }
                        event.accepted = true;
                        break;
                    case extKey.key_right:  // RIGHT -> LTR: scrollUp or scrollDown
                        if(!isRTL) {
                            parentListObject.currentIndex = parentListObject._NOT_ON_THE_LIST;
                            focusToOtherUI();
                        }
                        event.accepted = true;
                        break;
                    case extKey.key_return:
                        onClickedAction();
                        event.accepted = true;
                        break;
                    }
                }
                function focusToOtherUI(){
                    parentListObject.currentIndex = parentListObject._NOT_ON_THE_LIST;
                    if( (y - langSelectListView.contentY) < langSelectListView.height/2) // Focus to scrollUp
                        if(scrollUp.isDimmed) // if scroll up is dimmed -> focus to scroll down.
                            if(scrollDown.isDimmed) // if scroll Down is dimmed -> focus to Cancel button(Cancel button is never dimmed)
                                langSelectButtonCancel.forceActiveFocus();
                            else
                                scrollDown.forceActiveFocus();

                        else // normal
                            scrollUp.forceActiveFocus();
                    else // Focus to scrollDown
                        if(scrollDown.isDimmed) // if scroll down is dimmed -> focus to scroll up.
                            if(scrollUp.isDimmed) // // if scroll Up is dimmed -> focus to Cancel button(Cancel button is never dimmed)
                                langSelectButtonCancel.forceActiveFocus();
                            else
                                scrollUp.forceActiveFocus();
                        else
                            scrollDown.forceActiveFocus();
                }
            }

            Keys.onReleased: {
                printLog("=== langSelectListView Keys.onReleased: === " + event.key)
                switch(event.key){
                case extKey.key_up:     // UP -> Upper Item
                    printLog("case extKey.key_up:     // UP -> Upper Item")
                    printLog("langSelectListView.currentIndex: " + langSelectListView.currentIndex)
                    if((langSelectListView.currentIndex - 1)  < 0) { // TOP OF THE LIST -> langSelectButtonCancel
                        langSelectListView.currentIndex = langSelectListView._NOT_ON_THE_LIST;
                        langSelectButtonCancel.forceActiveFocus();
                    }
                    else {// OTHERS
                        langSelectListView.decrementCurrentIndex()
                    }
                    event.accepted = true;
                    break;
                case extKey.key_down:   // DOWN -> Lower Item
                    if((langSelectListView.currentIndex + 1) < langSelectListModel.count){
                        langSelectListView.incrementCurrentIndex();
                    }
                    event.accepted = true;
                    break;
                case extKey.key_left:   // LEFT -> OWN
                    event.accepted = true;
                    break;
                }
            }
        }


        // Button OK
        MouseArea {
            id: langSelectButtonOk
            objectName: "langSelectButtonOk"
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.topMargin: sttStyle.langSelectButtonOk.topMargin
            anchors.rightMargin: sttStyle.langSelectButtonOk.rightMargin
            width: langSelectButtonOkImageLeft.paintedWidth + langSelectButtonOkText.contentWidth + langSelectButtonOkImageRight.paintedWidth
            height: sttStyle.langSelectButtonOk.height
            hoverEnabled: true
            property string textToSpeech : langSelectButtonOkText.text + " " + stringSet.strings["button"]
            //for LayoutMirroring. QT.locale().textDirection -> LTR: 0, RTL: 1
            LayoutMirroring.enabled: isRTL

            onEntered: langSelectButtonOk.forceActiveFocus()
            onExited: langSelectButtonOk.parent.forceActiveFocus()
            onClicked: onClickedAction()
            onActiveFocusChanged: {
                if(activeFocus){
                    ttsService.speakByAudioGuidance(textToSpeech,currentLanguage)
                    remainSeconds = 30;
                }
            }
            Image {
                id: langSelectButtonOkImageLeft
                objectName: "langSelectButtonOkImageLeft"
                anchors.left: parent.left
                width: sttStyle.langSelectButtonOk.sideImgWidth
                height: parent.height
                source: langSelectButtonOk.activeFocus ? "images/small_btn_f_l.png" : "images/small_btn_w_n_l.png"
            }
            Image {
                id: langSelectButtonOkImageMiddle
                objectName: "langSelectButtonOkImageMiddle"
                anchors.left: langSelectButtonOkImageLeft.right
                anchors.right: langSelectButtonOkImageRight.left
                height: parent.height
                source: langSelectButtonOk.activeFocus ? "images/small_btn_f_m.png" : "images/small_btn_w_n_m.png"
            }
            Image {
                id: langSelectButtonOkImageRight
                objectName: "langSelectButtonOkImageRight"
                anchors.right: parent.right
                width: sttStyle.langSelectButtonOk.sideImgWidth
                height: parent.height
                source: langSelectButtonOk.activeFocus ? "images/small_btn_f_r.png" : "images/small_btn_w_n_r.png"
            }
            Text {
                id: langSelectButtonOkText
                objectName: "langSelectButtonOkText"
                anchors.centerIn: parent
                text: stringSet.strings["OK"]
                font.pixelSize: sttStyle.sayAgainButton.fontSize
                font.family: miso_regular_fontFamily
                font.weight: misoBold_fontWeight
                font.capitalization: Font.AllUppercase
                color: langSelectButtonOk.activeFocus ? sttStyle.sayAgainButton.focusFontColor : sttStyle.sayAgainButton.fontColor
            }

            Keys.onReleased: {
                printLog("=== langSelectButtonOk Keys.onReleased: === " + event.key)
                switch(event.key){
                case extKey.key_up:     // UP -> OWN
                    forceActiveFocus();
                    event.accepted = true;
                    break;
                case extKey.key_down:   // DOWN -> scrollUp
                    if(scrollUp.isDimmed) // if scroll Up is dimmed -> focus to scroll Down
                        if(scrollDown.isDimmed) // if scroll Down is dimmed -> keep focus
                            forceActiveFocus();
                        else
                            scrollDown.forceActiveFocus();
                    else
                        scrollUp.forceActiveFocus();
                    event.accepted = true;
                    break;
                case extKey.key_left:   // LEFT -> LTR: langSelectButtonCancel, RTL: OWN
                    if(!isRTL)
                        langSelectButtonCancel.forceActiveFocus();
                    event.accepted = true;
                    break;
                case extKey.key_right:  // RIGHT -> LTR: OWN, RTL: langSelectButtonCancel
                    if(isRTL)
                        langSelectButtonCancel.forceActiveFocus();
                    event.accepted = true;
                    break;
                case extKey.key_return:
                    onClickedAction();
                    event.accepted = true;
                    break;
                }
            }
            function onClickedAction(){
                main.forceActiveFocus()
                loadLanguageText()
                selectedLanguage = langSelectListModel.getSelectedItem().code
                restartSttService()
            }
        }
        // Button Cancel
        MouseArea {
            id: langSelectButtonCancel
            objectName: "langSelectButtonCancel"
            anchors.top: parent.top
            anchors.right: langSelectButtonOk.left
            anchors.topMargin: sttStyle.langSelectButtonCancel.topMargin
            anchors.rightMargin: sttStyle.langSelectButtonCancel.rightMargin
            width: langSelectButtonCancelImageLeft.paintedWidth + langSelectButtonCancelText.contentWidth + langSelectButtonCancelImageRight.paintedWidth
            height: sttStyle.langSelectButtonCancel.height
            hoverEnabled: true
            property string textToSpeech : langSelectButtonCancelText.text + " " + stringSet.strings["button"]
            //for LayoutMirroring. QT.locale().textDirection -> LTR: 0, RTL: 1
            LayoutMirroring.enabled: isRTL

            onEntered: langSelectButtonCancel.forceActiveFocus()
            onExited: langSelectButtonCancel.parent.forceActiveFocus()
            onClicked: onClickedAction()
            onActiveFocusChanged:{
                if(activeFocus){
                    ttsService.speakByAudioGuidance(textToSpeech,currentLanguage)
                    remainSeconds = 30;
                }
            }
            Image {
                id: langSelectButtonCancelImageLeft
                objectName: "langSelectButtonCancelImageLeft"
                anchors.left: parent.left
                width: sttStyle.langSelectButtonCancel.sideImgWidth
                height: parent.height
                source: langSelectButtonCancel.activeFocus ? "images/small_btn_f_l.png" : "images/small_btn_w_n_l.png"
            }
            Image {
                id: langSelectButtonCancelImageMiddle
                objectName: "langSelectButtonCancelImageMiddle"
                anchors.left: langSelectButtonCancelImageLeft.right
                anchors.right: langSelectButtonCancelImageRight.left
                height: parent.height
                source: langSelectButtonCancel.activeFocus ? "images/small_btn_f_m.png" : "images/small_btn_w_n_m.png"
            }
            Image {
                id: langSelectButtonCancelImageRight
                objectName: "langSelectButtonCancelImageRight"
                anchors.right: parent.right
                width: sttStyle.langSelectButtonCancel.sideImgWidth
                height: parent.height
                source: langSelectButtonCancel.activeFocus ? "images/small_btn_f_r.png" : "images/small_btn_w_n_r.png"
            }
            Text {
                id: langSelectButtonCancelText
                objectName: "langSelectButtonCancelText"
                anchors.centerIn: parent
                text: stringSet.strings["CANCEL"]
                font.pixelSize: sttStyle.sayAgainButton.fontSize
                font.family: miso_regular_fontFamily
                font.weight: misoBold_fontWeight
                font.capitalization: Font.AllUppercase
                color: langSelectButtonCancel.activeFocus ? sttStyle.sayAgainButton.focusFontColor : sttStyle.sayAgainButton.fontColor
            }

            Keys.onReleased: {
                printLog("=== langSelectButtonCancel Keys.onReleased: === " + event.key)
                switch(event.key){
                case extKey.key_up:     // UP -> OWN
                    forceActiveFocus();
                    event.accepted = true;
                    break;
                case extKey.key_right:  // RIGHT -> LTR: langSelectButtonOk, RTL: langSelectListView
                    if(isRTL)
                        langSelectListView.focusToTopItem();
                    else {
                        langSelectButtonOk.forceActiveFocus();
                    }
                    event.accepted = true;
                    break;
                case extKey.key_down:   // DOWN -> scrollUp
                    if(scrollUp.isDimmed) // if scroll Up is dimmed -> focus to scroll Down
                        if(scrollDown.isDimmed) // if scroll Down is dimmed -> keep focus
                            forceActiveFocus();
                        else
                            scrollDown.forceActiveFocus();
                    else
                        scrollUp.forceActiveFocus();
                    event.accepted = true;
                    break;
                case extKey.key_left:   // LEFT -> LTR: langSelectListView, RTL: langSelectButtonOk
                    if(isRTL)
                        langSelectButtonOk.forceActiveFocus();
                    else
                        langSelectListView.focusToTopItem();
                    event.accepted = true;
                    break;
                case extKey.key_return:
                    onClickedAction();
                    event.accepted = true;
                    break;
                }
            }
            function onClickedAction() {
                main.forceActiveFocus();
                restartSttService();
            }
        }

        Item {
            id: scrollBar
            objectName: "scrollBar"
            anchors.top: langSelectTitle.bottom
            anchors.topMargin: sttStyle.langSelectListScrollBar.topMargin
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.bottomMargin: sttStyle.langSelectListScrollBar.bottomMargin
            anchors.rightMargin: sttStyle.langSelectListScrollBar.rightMargin
            width: sttStyle.langSelectListScrollBar.width

            //for LayoutMirroring. QT.locale().textDirection -> LTR: 0, RTL: 1
            LayoutMirroring.enabled: isRTL

            property ListView targetListView: langSelectListView


            function isAtTop() {
                return (targetListView.contentY === 0)? true : false;
            }
            function isAtBottom() {
                return (targetListView.contentY + targetListView.height === targetListView.contentHeight)? true : false
            }
            function needScroll() {
                return (targetListView.contentHeight <= targetListView.height) ? false : true;
            }
            function updateAll() {
                scrollUp.update()
                scrollDown.update()
                scrollMidBar.update()
            }
            function updateScrollButtons() {
                scrollUp.update()
                scrollDown.update()
            }

            MouseArea {
                id: scrollUp
                objectName: "scrollUp"
                anchors.top: parent.top
                anchors.topMargin: sttStyle.langSelectListScrollBar.topMargin
                width: parent.width
                height: sttStyle.langSelectListScrollBar.arrowHeight
                hoverEnabled: true
                opacity: scrollUp.isDimmed ? 0.3 : 1
                property string textToSpeech : stringSet.strings["scroll up"]
                property bool isDimmed: false

                function onClickedAction(){
                    printLog("=== scrollUp onClickedAction() ===");
                    // What is shorter? Select shorter item between
                    // 1. 2 item scrolling and
                    // 2. current view ~ first item
                    printLog("2 item scrolling : " + (sttStyle.langSelectListItem.height + langSelectListView.spacing)*2);
                    printLog("current view ~ first item : " + langSelectListView.contentY);
                    ttsService.speakByAudioGuidance(stringSet.strings["up"], currentLanguage);
                    langSelectBox.deltaContentY = - Math.min((sttStyle.langSelectListItem.height + langSelectListView.spacing)*2, langSelectListView.contentY);
                    printLog("langSelectBox.deltaContentY = - Math.min((sttStyle.langSelectListItem.height + langSelectListView.spacing)*2, langSelectListView.contentY); " + langSelectBox.deltaContentY);
                    moveContentYAni.start();
                }
                function update(){
                    printLog("=== scrollUp update ===")
                    if(!scrollBar.needScroll() || scrollBar.isAtTop()){  // if Listview is at top, dimm
                        scrollUp.isDimmed = true;
                        if(scrollUp.activeFocus) // if scroll Up has focus after ListView at top -> focus to top item
                            langSelectListView.focusToTopItem();
                    }
                    else
                        scrollUp.isDimmed = false;
                }

                onEntered: {
                    forceActiveFocus()
                }
                onExited: {
                    parent.forceActiveFocus()
                }
                onClicked: onClickedAction()
                onActiveFocusChanged: {
                    if(activeFocus){
                        if(!scrollUp.isDimmed)
                            ttsService.speakByAudioGuidance(textToSpeech,currentLanguage)
                        remainSeconds = 30;
                    }
                }
                Image {
                    anchors.fill: parent
                    source: {
                        if(scrollUp.isDimmed){
                            "qrc:///stt/images/stt_popup_scroll_arrow_up_n.png"
                        } else {
                            if(parent.activeFocus)
                                "qrc:///stt/images/stt_popup_scroll_arrow_up_f.png"
                            else
                                "qrc:///stt/images/stt_popup_scroll_arrow_up_n.png"
                        }
                    }
                }

                Keys.onReleased: {
                    printLog("=== scrollUp Keys.onReleased: === " + event.key)
                    switch(event.key){
                    case extKey.key_up:     // UP -> langSelectButtonOk
                        langSelectButtonOk.forceActiveFocus();
                        event.accepted = true;
                        break;
                    case extKey.key_right:  // RIGHT -> LTR: OWN, RTL: langSelectListView
                        if(isRTL)
                            langSelectListView.focusToTopItem();
                        event.accepted = true;
                        break;
                    case extKey.key_down:   // DOWN -> scrollDown
                        if(scrollDown.isDimmed) // if scroll down is dimmed, don't keep focus.
                            scrollUp.forceActiveFocus();
                        else // normal
                            scrollDown.forceActiveFocus();
                        event.accepted = true;
                        break;
                    case extKey.key_left:   // LEFT -> LTR: langSelectListView, RTL: OWN
                        if(!isRTL)
                            langSelectListView.focusToTopItem();
                        event.accepted = true;
                        break;
                    case extKey.key_return:
                        onClickedAction();
                        event.accepted = true;
                        break;
                    }
                }
            }

            MouseArea {
                id: scrollMidBar
                objectName: "scrollMidBar"
                anchors.top: scrollUp.bottom
                anchors.bottom: scrollDown.top
                anchors.topMargin: sttStyle.langSelectListScrollBar.barTopMargin
                anchors.bottomMargin: sttStyle.langSelectListScrollBar.barBottomMargin
                width: parent.width
                hoverEnabled: true
                opacity: scrollMidBar.isDimmed ? 0.3 : 1

                property bool isDimmed: false

                drag {
                    target: scrollMidBarImg
                    minimumY: 0
                    maximumY: (scrollMidBar.height - scrollMidBarImg.height)
                    axis: Drag.YAxis
                }
                onClicked: { langSelectListView.contentY = (mouse.y / scrollMidBar.height * (langSelectListView.contentHeight - langSelectListView.height)) }

                function update(){
                    printLog("=== scrollMidBar update ===");
                    if(!scrollBar.needScroll()) // is whole List height is equal to View height, there is no need to scroll
                        scrollMidBar.isDimmed = true;
                    else
                        scrollMidBar.isDimmed = false;
                }
                Item {
                    id: scrollMidBarImg
                    objectName: "scrollMidBarImg"
                    anchors.left: parent.left
                    anchors.right: parent.right

                    Image {
                        id: scrollMidBarImgTop
                        objectName: "scrollMidBarImgTop"
                        anchors.top: parent.top
                        width: parent.width
                        height: paintedHeight
                        source: "qrc:///stt/images/stt_popup_scroll_bar_top.png"
                    }
                    Image {
                        id: scrollMidBarImgMid
                        objectName: "scrollMidBarImgMid"
                        anchors.top: scrollMidBarImgTop.bottom
                        anchors.bottom: scrollMidBarImgBottom.top
                        width: parent.width
                        fillMode: Image.Stretch
                        source: "qrc:///stt/images/stt_popup_scroll_bar_middle.png"
                    }
                    Image {
                        id: scrollMidBarImgBottom
                        objectName: "scrollMidBarImgBottom"
                        anchors.bottom: parent.bottom
                        width: parent.width
                        height: paintedHeight
                        source: "qrc:///stt/images/stt_popup_scroll_bar_bottom.png"
                    }

                }


            }
            MouseArea {
                id: scrollDown
                objectName: "scrollDown"
                anchors.bottom: parent.bottom
                width: parent.width
                height: sttStyle.langSelectListScrollBar.arrowHeight
                hoverEnabled: true
                opacity: scrollDown.isDimmed ? 0.3 : 1
                property string textToSpeech: stringSet.strings["scroll down"]
                property bool isDimmed: false

                function onClickedAction(){
                    printLog("=== scrollDown onClickedAction() ===");
                    printLog("current view ~ last item :" + (langSelectListView.contentHeight - langSelectListView.height - langSelectListView.contentY));
                    printLog("2 item scrolling : " + (sttStyle.langSelectListItem.height + langSelectListView.spacing)*2 );
                    // What is shorter? Select shorter item between
                    // 1. 2 item scrolling and
                    // 2. current view ~ last item
                    ttsService.speakByAudioGuidance(stringSet.strings["down"], currentLanguage);
                    langSelectBox.deltaContentY = Math.min((sttStyle.langSelectListItem.height + langSelectListView.spacing)*2 , langSelectListView.contentHeight - langSelectListView.height - langSelectListView.contentY);
                    printLog("langSelectBox.deltaContentY = Math.min((sttStyle.langSelectListItem.height + langSelectListView.spacing)*2 , langSelectListView.contentHeight - langSelectListView.height - langSelectListView.contentY) " + langSelectBox.deltaContentY);
                    moveContentYAni.start();
                }
                function update(){
                    printLog("=== scrollDown update ===")
                    if(!scrollBar.needScroll() || scrollBar.isAtBottom()){ // if Listview is at bottom, dimm
                        isDimmed = true;
                        if(scrollDown.activeFocus) // if scroll Down has focus after ListView at bottom -> focus to bottom item
                            langSelectListView.focusToBottomItem()
                    }
                    else
                        isDimmed = false;
                }

                onEntered: {
                    forceActiveFocus()
                }
                onExited: {
                    parent.forceActiveFocus()
                }
                onClicked: onClickedAction()
                onActiveFocusChanged: {
                    if(activeFocus){
                        if(!scrollDown.isDimmed)
                            ttsService.speakByAudioGuidance(textToSpeech,currentLanguage)
                        remainSeconds = 30;
                    }
                }
                Image {
                    anchors.fill: parent
                    source: {
                        if(scrollDown.isDimmed){
                            "qrc:///stt/images/stt_popup_scroll_arrow_down_n.png"
                        } else {
                            if(scrollDown.activeFocus)
                                "qrc:///stt/images/stt_popup_scroll_arrow_down_f.png"
                            else
                                "qrc:///stt/images/stt_popup_scroll_arrow_down_n.png"
                        }
                    }
                }
                Keys.onReleased: {
                    printLog("=== scrollDown Keys.onReleased: === " + event.key)
                    switch(event.key){
                    case extKey.key_up:     // UP -> scrollUp
                        if(scrollUp.isDimmed) // if scroll up is dimmed, focus to Ok button
                            langSelectButtonOk.forceActiveFocus();
                        else // normal
                            scrollUp.forceActiveFocus();
                        event.accepted = true;
                        break;
                    case extKey.key_right:  // RIGHT -> LTR: OWN, RTL: langSelectListView
                        if(isRTL)
                            langSelectListView.focusToBottomItem();
                        break;
                    case extKey.key_down:   // DOWN -> OWN
                        printLog("case extKey.key_down:   // DOWN -> OWN")
                        printLog("scrollDown.forceActiveFocus();")
                        scrollDown.forceActiveFocus();
                        event.accepted = true;
                        break;
                    case extKey.key_left:   // LEFT -> LTR: langSelectListView, RTL: OWN
                        if(!isRTL)
                            langSelectListView.focusToBottomItem();
                        event.accepted = true;
                        break;
                    case extKey.key_return:
                        onClickedAction();
                        event.accepted = true;
                        break;
                    }
                }
            }

        }

        PropertyAnimation {
            id: moveContentYAni
            objectName: "moveContentYAni"
            target: langSelectListView
            property: "contentY"
            to: langSelectListView.contentY + langSelectBox.deltaContentY
            duration: 300
            easing.type: Easing.InOutQuad
            onRunningChanged: if(!running) {langSelectListView.returnToBounds()}
        }
        /*
          Key Focusable Object
          langSelectListView
          langSelectButtonOk
          langSelectButtonCancel
          scrollUp
          scrollDown
          */
        Keys.onReleased: {
            printLog("=== langSelectBox Keys.onReleased: === " + event.key)
            switch(event.key){
            case extKey.key_up:     // UP -> langSelectButtonCancel
                langSelectButtonCancel.forceActiveFocus();
                break;
            case extKey.key_right:  // RIGHT -> LTR: langSelectButtonCancel, RTL: langSelectListView
                if(isRTL)
                    langSelectListView.forceActiveFocus();
                else
                    langSelectButtonCancel.forceActiveFocus();

                event.accepted = true;
                break;
            case extKey.key_down:   // DOWN -> langSelectListView
                langSelectListView.focusToTopItem();
                break;
            case extKey.key_left:   // LEFT -> LTR: langSelectListView, RTL: langSelectButtonCancel
                if(isRTL)
                    langSelectButtonCancel.forceActiveFocus();
                else
                    langSelectListView.focusToTopItem();
                event.accepted = true;
                break;
            }
        }
    }

    Binding {
        target: scrollMidBarImg
        property: "y"
        value: langSelectListView.contentY * scrollMidBar.drag.maximumY / (langSelectListView.contentHeight - langSelectListView.height)
        when: (!scrollMidBar.drag.active)
    }

    Binding {
        target: langSelectListView
        property: "contentY"
        value: (scrollMidBarImg.y * (langSelectListView.contentHeight - langSelectListView.height) / scrollMidBar.drag.maximumY)
        when: (scrollMidBar.drag.active || scrollMidBar.pressed)
    }

    ListModel {
        id: langSelectListModel
        objectName: "langSelectListModel"
        function add(sttLanguage){
            // isInList
            for (var i =0; i < langSelectListModel.count; i++) {
                if(langSelectListModel.get(i).code === sttLanguage)
                    return;
            }

            // is valid locale language
            var localeText = localeString.printLocale(sttLanguage);
            printLog("var localeText = localeString.printLocale("+ sttLanguage +"); " + localeText)
            if(localeText === "")
                return;

            langSelectListModel.append({
                                           index: langSelectListModel.count,
                                           code: sttLanguage,
                                           languageName : localeText,
                                           isSelected: false
                                       });
        }
        function setSelectedByLangCode(langCode){
            for (var i = 0; i < langSelectListModel.count; i++){
                var item = langSelectListModel.get(i);
                if(item.code === langCode){
                    item.isSelected = true;
                } else {
                    item.isSelected = false;
                }
            }
        }

        function setSelected(index){
            for (var i = 0; i < langSelectListModel.count; i++){
                var item = langSelectListModel.get(i);
                if(i === index){
                    item.isSelected = true;
                } else {
                    item.isSelected = false;
                }
            }
        }
        function clearSelected(){
            for (var i = 0; i < langSelectListModel.count; i++){
                var item = langSelectListModel.get(i);
                item.isSelected = false;
            }

        }
        function restoreSelection(languageCode){
            for (var i = 0; i < langSelectListModel.count; i++){
                var item = langSelectListModel.get(i);
                item.isSelected = (item.code === languageCode);

            }
        }
        function getSelectedItem() {
            for (var i = 0; i < langSelectListModel.count; i++){
                var item = langSelectListModel.get(i);
                if(item.isSelected){
                    return item;
                }
            }
            return null;
        }
    }

    Service { id: getAppIdService
        appId: "com.webos.service.ime.stt"
        onResponse: {
            var jsonObject = JSON.parse(payload)
            if(!jsonObject.returnValue) { console.exception(payload); return; }
            printLog("getAppIdService", payload)
            if ( jsonObject.foregroundAppInfo !== undefined){
                cardTypeForegroundAppId = ""
                anyTypeForegroundAppId = ""
                var foregroundAppList = jsonObject.foregroundAppInfo
                for(var i = 0; i < foregroundAppList.length; i++) {
                    var object = foregroundAppList[i]
                    if(object.windowType === "_WEBOS_WINDOW_TYPE_CARD") { // always exist
                        // Only CARD TYPE App is returned using getForegroundInfo API without extraInfo.
                        // Thus, this is general foreground app.
                        cardTypeForegroundAppId = object.appId
                    }else{// if exist _WEBOS_WINDOW_TYPE_POPUP,_WEBOS_WINDOW_TYPE_OVERLAY => if not exist, anyTypeForegroundAppId === ""
                        anyTypeForegroundAppId  = object.appId
                    }
                    printLog("=== getAppIdService return == cardTypeForegroundAppId :" + cardTypeForegroundAppId + " : anyTypeForegroundAppId : " + anyTypeForegroundAppId)
                }
            }

            // START VOICE RECOGNITION
            //            canShowSTTView();
            //            guideText.text = qsTr("Speak to input text.")+qsTr(" (")+localeString.printLocale(selectedLanguage)+qsTr(")") + PluginProxy.emptyString; // i18n This sentence appears when user tries to input text by voice recognition.
            callSttService();
            isActivated = true;
        }

        onError: {
            printLog("onError():");
            console.trace();
        }
    }
    /* Service: Check MRCU connection status*/
    /* luna://com.webos.service.mrcu/getConnectionStatus '{"subscribe":true}'
       luna://com.webos.service.mrcu/getConnectionStatus '{}'
    1) disconnect
    {
        "connected": false,
        "returnValue": true
    }
    2) connect
    {
        "connected": true,
        "returnValue": true
    }
    */
    Service {
        id: checkMRCUPairService
        appId: "com.webos.service.ime.stt"
        onResponse: {
            printWarningLog("checkMRCUPairService Response : " + payload);
            var jsonObject = JSON.parse(payload);
            if(!jsonObject.returnValue) {
                printLog(jsonObject.errorCode + " " + jsonObject.errorText);
                goToInitialError();
                handleErrors("", stringSet.strings["You need to use LG Magic Remote to use voice recognition."]);
                return;
            }
            if(jsonObject.isFalseActive){
                goToInitialError();
		handleErrors("", stringSet.strings["To use voice recognition with the Magic Remote that you are currently using, please try again from the other TV."]);
                return;
            }
            if(jsonObject.connected) {
                callGetAppIdService();
            } else {
		goToInitialError();
		handleErrors("", stringSet.strings["You need to use LG Magic Remote to use voice recognition."]);
            }
            cancel()
        }
    }

    /* Service: Check Bluetooth Setting(atsc is always on) */
    /*
    luna-send -f -n 1 luna://com.webos.service.bluetooth/gap/getState '{}'
    {
        "state": true,
        "returnValue": true
    }
    */

    Service {
        id: checkBluetoothService
        appId: "com.webos.service.ime.stt"

        onResponse: {
            printWarningLog("checkBluetoothService Response : " + payload)
            var jsonObject = JSON.parse(payload)
            if(!jsonObject.returnValue){
                goToInitialError()
                handleErrors("", stringSet.strings["Turn on Bluetooth and then speak to Magic remote for voice recognition."]); // // only dvb has bluetooth setting
                return;
            }
            if(jsonObject.state)
                callCheckMRCUPairService();
            else {
                goToInitialError()
                handleErrors("", stringSet.strings["Turn on Bluetooth and then speak to Magic remote for voice recognition."]); // only dvb has bluetooth setting
            }
            cancel()
        }
    }

    /* Service: System sound */
    Service {
        id: systemSound
        appId: "com.webos.service.ime.stt"
        onResponse: {
            cancel();
            printLog("SystemSound called");
            debugText.text = "SystemSound called";
        }
        onError: {
            printLog("onError():");
            console.trace();
        }
    }

    /* Service : Media Volume Control */
    Service {
        id: mediaVolumeController
        appId: "com.webos.service.ime.stt"
        onResponse: cancel()
    }

    /* Service : Master Volume Control */
    Service {
        id: masterVolumeController
        appId: "com.webos.service.ime.stt"
        onResponse: {
            printLog("GetVolume.response:" + payload);
            if ( payload !== undefined){
                var jsonObject = JSON.parse(payload)
                if(!jsonObject.returnValue) {
                    console.exception(payload);
                } else if(jsonObject.volume !== undefined) {
                    masterVolume = jsonObject.volume;
                    if(masterVolume <= 0) masterVolume = 1;
                    mediaVolume = 500/masterVolume;
                    printLog("mediaVolume:"+mediaVolume);
                    muted = jsonObject.muted;
                }
                cancel();
            }
        }

        onError: {
            printLog("onError():");
            console.trace();
        }
    }

    Service {
        id: getNlpStatusService
        appId: "com.webos.service.ime.stt"
        onResponse: {
            printWarningLog("getNlpStatusService Response : " + payload)
            cancel();
            var jsonObject = JSON.parse(payload);
            if((jsonObject.returnValue !== undefined) && !jsonObject.returnValue) {
                main.state = 'initial_error';
                handleErrors(jsonObject.errorCode, jsonObject.errorText);
            } else {
                printLog("main.isActivated: " + main.isActivated);
                if(main.isActivated) {
                    /* Retry case */
                    callSttService();
                } else {
                    /* Activation case */
                    voiceLanguage = jsonObject.voiceLanguage;

                    // List set
                    setLangSelectList();

                    // set voice recognition language set on Settings app
                    if(voiceLanguage === "cmn-Hans-CN") voiceLanguage = "zh-Hans-CN";
                    else if(voiceLanguage === "yue-Hant-HK") voiceLanguage = "zh-Hant-HK";
                    else if(voiceLanguage === "cmn-Hant-TW") voiceLanguage = "zh-Hant-TW";

                    // set selected language on stt plugin
                    printLog("selectedLanguage: " + selectedLanguage);

                    // set selection to voiceLanguage
                    selectedLanguage = voiceLanguage;
                    currentLanguage = selectedLanguage;
                    langSelectListModel.setSelectedByLangCode(selectedLanguage);

                    printLangSelectList();

                    main.state = "init";
                    main.forceActiveFocus();
                    callCheckBluetoothService();
                }
            }
        }
    }


    Service {
        id: launchEULA
        appId: "com.webos.service.ime.stt"
        onResponse: cancel()
    }

    Service {
        id: sttService
        appId: "com.webos.service.ime.stt"
        onResponse: {
            printWarningLog("payload: " + payload)
            var jsonObject = JSON.parse(payload);
            debugText.text = jsonObject.event + ">>";
            if((jsonObject.returnValue !== undefined) && !jsonObject.returnValue) {
                printWarningLog("=========================================================== ERROR: " + jsonObject.errorCode)
                main.state = 'event_error';
                handleErrors(jsonObject.errorCode, jsonObject.errorText);
                debugText.text = debugText.text + jsonObject.errorCode + " not in Event ";
                cancel();
            } else {
                printWarningLog("=========================================================== EVENT: " + jsonObject.event)
                if(jsonObject.event === undefined)
                    startSTT_state = "undefined"
                else
                    startSTT_state = jsonObject['event']

                if (jsonObject.event === "error") {
                    main.state = 'event_error';
                    handleErrors(jsonObject.errorCode, jsonObject.errorText);
                    debugText.text = debugText.text + jsonObject.errorCode + " in Error Event";
                    return;
                } else if (jsonObject.event === "sttStart") {
                    main.forceActiveFocus();
                    debugText.text = "";
                    main.state = 'event_sttStart';
                    guideText.text = stringSet.strings["Speak to input text."] + stringSet.strings[" ("] + localeString.printLocale(selectedLanguage) + stringSet.strings[")"];
                    canShowSTTView();
                } else if (jsonObject.event === "micStart") {
                    main.state = 'event_micStart';
                    // Volume Down to 5
                    if(masterVolume > 5 && muted === false) {
                        printLog("\r\nVolume Down to 5");
                        mediaVolumeController.call("luna://com.webos.audio/media", "/setVolume", "{\"volume\":" + mediaVolume + "}");
                    }else
                        printLog("masterVolume:" + masterVolume + ", mute status: " + muted);
                    //AUI : commandable
                    systemSound.call("luna://com.webos.audio/systemsounds", "/playFeedback", "{\"name\":\"voicestart\",\"sink\":\"pfeedback\",\"play\":true}");
                    if(isLanguagedChanged)
                        stopSpinner();
                } else if (jsonObject.event === "energyLevel") {
                    main.state = 'event_energyLevel';
                    micRec.energyLevel = jsonObject.energyLevel;
                } else if (jsonObject.event === "sttConnecting") {
                    main.state = 'event_sttConnecting';
                    guideText.text = "";
                    //AUI : processing
                    systemSound.call("luna://com.webos.audio/systemsounds", "/playFeedback", "{\"name\":\"voiceconfirm\",\"sink\":\"pfeedback\",\"play\":true}");
                    //Volume Restored
                    printLog("\r\nVolume Restored to 100");
                    mediaVolumeController.call("luna://com.webos.audio/media", "/setVolume", "{\"volume\":100}");
                } else if (jsonObject.event === "sttResult") {
                    if (jsonObject.sttResult[0] !== undefined) {
                        var temp = jsonObject.sttResult;
                        resultTextArray = temp;
                    }
                    for (var i = 0; i < 3; i++) {
                        if (resultTextArray[i] !== undefined) {
                            if (i === 0)
                                resultListButton1.text = resultTextArray[i];
                            else if (i === 1)
                                resultListButton2.text = resultTextArray[i];
                            else if (i === 2)
                                resultListButton3.text = resultTextArray[i];
                        } else {
                            break;
                        }
                    }
                    if(i === 0) {
                        main.state = 'event_sessionEnd_0';
                        resultListBox.focusInit();
                    } else if (i === 1) {
                        main.state = 'event_sessionEnd_1';
                        resultListBox.focusInit();
                    } else if (i === 2) {
                        main.state = 'event_sessionEnd_2';
                        resultListBox.focusInit();
                        remainSeconds = 30;
                        checkingRemainingTimeTimer.start();
                    } else if (i === 3) {
                        main.state = 'event_sessionEnd_3';
                        resultListBox.focusInit();
                        remainSeconds = 30;
                        checkingRemainingTimeTimer.start();
                    } else{
                        main.state = 'event_error';
                    }
                } else if (jsonObject.event === "sessionEnd") {
                    cancel();
                    debugText.text = debugText.text + "[" + main.state + "]";
                    if(main.state === 'event_sessionEnd_1')
                        textKeyPressed(resultListButton1.text);
                }

            }
        }
        onError: console.warn("STT plugin Error")
    }

    Service {
        id: sttCancelService
        appId: "com.webos.service.ime.stt"
        onResponse: cancel()
    }

    Service {
        id: createAlertService
        appId: "com.webos.service.ime.stt"
        onResponse: cancel()
    }

    /* Key Handler */
    Keys.onReleased: {
        printLog("=== main Keys.onReleased: === " + event.key)
        printLog("event.key: " + event.key);
        var keyInterval = Date.now() - timeToShow;
        if( keyInterval > 0 && keyInterval <= 800 ){
            console.warn("========================================== interval:" + keyInterval + "Too fast key click!! returns!\r\n");
            return;
        }

        switch(event.key){
        case extKey.key_red:
            printLog("red key is Clicked")
            if(main.state === "event_micStart" || main.state === "event_sttStart" || main.state === "event_energyLevel"){
                main.state = "event_langSelect"
                langSelectBox.focusInit();
                checkingRemainingTimeTimer.restart();
                if(needCancelAPI())
                {
                    printLog("nlp cancel is called.   startSTT_state: " + startSTT_state);
                    sttCancelService.call("luna://com.webos.service.nlp","/cancel","{}");
                    sttService.cancel();
                }
            }
            break;
        case extKey.webOS_Voice:
            printLog("voice key is Clicked")
            // When user got multi results, if user press voice key then user can speak to use STT again.
            if(main.state === 'event_sessionEnd_2' || main.state === 'event_sessionEnd_3'||
                    main.state === 'event_error'|| main.state === 'event_langSelect') {
                playSpinner();
                restartSttService();
            } else {
                systemSound.call("luna://com.webos.audio/systemsounds", "/playFeedback", "{\"name\":\"voicecancel\",\"sink\":\"pfeedback\",\"play\":true}")
                backToKeyboardPressed();
            }

            break;
        case extKey.webOS_Back:
            printLog("back key is Clicked")
            debugText.text = "key Event ::Back" + event.key;
            if(main.state === 'event_sessionEnd_2' || main.state === 'event_sessionEnd_3'|| main.state === 'event_error' || main.state === "event_langSelect" ||
                    main.state === 'initial_error') {
                backToKeyboardPressed();
            } else {
                systemSound.call("luna://com.webos.audio/systemsounds", "/playFeedback", "{\"name\":\"voicecancel\",\"sink\":\"pfeedback\",\"play\":true}")
                backToKeyboardPressed();
            }
            break;
        case extKey.key_up:
        case extKey.key_down:
        case extKey.key_left:
        case extKey.key_right:
            if(guideRetryButton.visible)
                guideRetryButton.forceActiveFocus()
            break;
        default:
            // Do nothing
            debugText.text = "Default key Event ::Voice" + event.key;
            break;
        }
    }

    Spinner {
        id: spinner
        anchors.fill: parent
        //visible: false
        opacity: 0
    }

    Timer {
        id: spinnerTimer
        interval: 100
        onTriggered: {
            if(main.state === "event_micStart" || main.state === "event_sttStart" || main.state === "event_energyLevel" || main.state === "event_error" ||
                    main.state === "event_langSelect" || main.state === "sttConnecting") {
                printLog("stopSpinner();")
                stopSpinner();
            } else {
                restart();
            }
        }
    }

    /* Debug text */
    Text{
        visible: false
        id: debugText
        x: 30; y: 30
        text: currentLanguage
        color: sttStyle.seperateLine.boldColor
    }
    function goToInitialError(){
        main.state = "initial_error"
        main.forceActiveFocus();
    }
    function printLog(str){
        if(_DEBUG)
            sigSendText(str)
    }
    function printWarningLog(str){
        if(_DEBUG)
            sigSendWarningText(str)
    }
    function startSTTPlugin(){ // this is the start point to activate stt Plugin.
        callGetNlpStatueService();
    }
    function calculateHandleHeight() {

        if(langSelectListView != undefined) {
            if(langSelectListView.contentHeight === 0)
                return;
            if(langSelectListView.height < langSelectListView.contentHeight) {
                var heightRatio = langSelectListView.height / langSelectListView.contentHeight;
                scrollMidBarImg.height = Math.max (20, (heightRatio * scrollMidBar.height));
            } else {
                scrollMidBarImg.height = scrollMidBar.height;
            }
        }
    }
    function restartSttService() {
        main.state = "init";
        checkingRemainingTimeTimer.stop();
        currentLanguage = selectedLanguage;
        langSelectListModel.restoreSelection(selectedLanguage);
        isLanguagedChanged = false;
        getNlpStatusService.call("luna://com.webos.service.nlp","/getNlpStatus","{}");
    }


    /* Call Service Method */

    /* Call Service Method */
    function callGetAppIdService() {
        printWarningLog("callGetAppIdService()")
        getAppIdService.call("luna://com.webos.applicationManager","/getForegroundAppInfo","{\"extraInfo\": true}")
    }

    function callCheckBluetoothService() {
        printWarningLog("callCheckBluetoothService()")
        checkBluetoothService.call("luna://com.webos.service.bluetooth/gap", "/getState", "{}");
    }
    function callCheckMRCUPairService() {
        printWarningLog("callCheckMRCUPairService()")
        checkMRCUPairService.call("luna://com.webos.service.mrcu","/getConnectionStatus", "{}");
    }
    function callGetNlpStatueService() {
        printWarningLog("callGetNlpStatueService()")
        getNlpStatusService.call("luna://com.webos.service.nlp","/getNlpStatus","{}");
    }

    function callSttService() {
        printWarningLog("callSttService()")
        printLog("selectedLanguage: " + selectedLanguage);
        var targetSttLang;
        // call sttService as voiceLanguage of this item
        var dictationModeValue = false;
        if(anyTypeForegroundAppId === ""&& cardTypeForegroundAppId === "com.webos.app.browser"){ //only browser use dictationMode true
            dictationModeValue = true;
        }
        printLog("=== callSttService() === dictationModeValue:" + dictationModeValue);
        var param = {};

        if (selectedLanguage) {
            if(selectedLanguage == "zh-Hans-CN") targetSttLang = "cmn-Hans-CN";
            else if(selectedLanguage == "zh-Hant-HK") targetSttLang = "yue-Hant-HK";
            else if(selectedLanguage == "zh-Hant-TW") targetSttLang = "cmn-Hant-TW";
            else targetSttLang = selectedLanguage;

            param = {
                "subscribe": true,
                "micDevice": "motionRemote",
                "dictationMode": dictationModeValue,
                "sttLanguage": targetSttLang,
                "isImeStatus": true
            }
            param = JSON.stringify(param);

            sttService.call("luna://com.webos.service.nlp", "/startStt", param);
            PluginProxy.selectLanguage(selectedLanguage);
        } else {
            param = {
                "subscribe": true,
                "micDevice": "motionRemote",
                "dictationMode": dictationModeValue,
                "sttLanguage": "en-US",
                "isImeStatus": true
            }
            param = JSON.stringify(param);

            sttService.call("luna://com.webos.service.nlp", "/startStt", param);
        }
    }
    function launchEula() {
        launchEULA.call("luna://com.webos.applicationManager", "/launch", "{\"id\": \"com.webos.app.eula\", \"params\": {\"context\": \"voice\"}}")
    }

    function createAlert(title, message, buttons) {
        message = message.replace(/\"/g,"\\\"");
        title = title.replace(/\"/g,"\\\"");
        createAlertService.call("palm://com.webos.notification","/createAlert","{\"title\":\"" + title + "\",\"message\":\"" + message + "\",\"buttons\":" + buttons + "}");

    }
    function needCancelAPI() {
        if(startSTT_state === "undefined" || startSTT_state === "sttResult" || startSTT_state === "sessionEnd" ||
                startSTT_state === "error" || startSTT_state === "")
            return false;
        else
            return true;
    }

    function loadLanguageText() {
        printLog("=== loadLanguageText() ===");
        playSpinner();
    }
    function playSpinner() {
        spinner.opacity = 1;
        spinner.play(true);
        spinnerTimer.start();
    }
    function stopSpinner() {
        spinner.opacity = 0;
        spinner.stop();
    }

    function setLangSelectList() {
        printLog("=== setLangSelectList() ===");
        printLog("voiceLanguage: " + voiceLanguage);
        printLog("getLanguageName(voiceLanguage): " + getLanguageName(voiceLanguage));
        printLog("PluginProxy.vkbLanguage1: " + PluginProxy.vkbLanguage1);
        printLog("PluginProxy.vkbLanguage2: " + PluginProxy.vkbLanguage2);
        printLog("PluginProxy.vkbLanguage3: " + PluginProxy.vkbLanguage3);
        printLog("PluginProxy.vkbLanguage4: " + PluginProxy.vkbLanguage4);
        printLog("PluginProxy.vkbLanguage5: " + PluginProxy.vkbLanguage5);
        addSttLanguage(getLanguageName(voiceLanguage));
        addSttLanguage(PluginProxy.vkbLanguage1);
        addSttLanguage(PluginProxy.vkbLanguage2);
        addSttLanguage(PluginProxy.vkbLanguage3);
        addSttLanguage(PluginProxy.vkbLanguage4);
        addSttLanguage(PluginProxy.vkbLanguage5);

        calculateHandleHeight();

    }

    // voiceLanguage has country code and language name (ex. en-US)
    // vkbLanguage has only language name -> no need to call this function (ex. en, ko, es, ...)
    function getLanguageName(countryLangCode){
        printLog("=== getLanguageName ===");
        printLog("countryLangCode: " + countryLangCode);
        if(countryLangCode == "cmn-Hans-CN") return "zh-Hans";
        else if(countryLangCode == "yue-Hant-HK") return "zh-Hant";
        else if(countryLangCode == "cmn-Hant-TW") return "zh-Hant";
        else return countryLangCode.slice(0,2);
    }
    function addSttLanguage(vkbLanguage) {
        if(vkbLanguage === undefined || vkbLanguage === "")
            return;
        //TODO
        // uz-Latn(there is no one matched in STT Language List), zh-Hans, zh-Hant, ja( jp-JP in STT Language List)
        // may be it needs to changed to switch-case routine
        var sttLangList = localeString.getSTTLangList(vkbLanguage) // sttLangList is ListModel QML object
        for (var i = 0; i < sttLangList.count; i++) {
            var langCode = sttLangList.get(i).name;
            var lang, region;

            if(langCode === "zh-Hans-CN"){
                lang = "zh-Hans";
                region = "CN";
            } else if(langCode === "zh-Hant-TW") {
                lang = "zh-Hant";
                region = "TW";
            } else if(langCode === "zh-Hant-HK") {
                lang = "zh-Hant";
                region = "HK";
            } else {
                lang = langCode.slice(0,2);
                region = langCode.slice(3);
            }
            if(vkbLanguage === lang) {
                printLog("add this to LangSelectList : " + langCode);
                langSelectListModel.add(langCode);
            }
        }
    }
    function printLangSelectList() {
        for( var i = 0; i< langSelectListModel.count; i++){
            printLog("langSelectListModel.get(" + i + ").code : " + langSelectListModel.get(i).code);
            printLog("langSelectListModel.get(" + i + ").languageName : " + langSelectListModel.get(i).languageName);
            printLog("langSelectListModel.get(" + i + ").isSelected : " + langSelectListModel.get(i).isSelected);
        }
    }

    // check whether previous selected language is on the list or not.
    // on the list : return index
    // not on the list : return 0 (it means voice recognition language set on Settings App.
    function checkPrevSelectedLang(selectedLang) {
        for (var i = 0; i < langSelectListModel.count; i++) {
            var item = langSelectListModel.get(i);
            if(selectedLang === item.code) {
                return item.index;
            }
        }
        return -1;
    }

    function updateGuideLangText() {
        printLog("=== updateGuideLangText ===")
        printLog("guideLangText.spacing: \""+ guideLangText.spacing + "\"")
        printLog("guideLangText.imgString: " + guideLangText.imgString)
        if(currentLanguage === "ar-SA" || currentLanguage === "ar-AE" || currentLanguage === "ar-EG" ||
                currentLanguage === "he-IL"){
            guideLangText.spacing = ""
            // guideLangText.imgString = "&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; <img src=\"images/stt_icon_keyhelp_red.png\">"
            guideLangText.imgString = "&nbsp; &nbsp; \u202A <img src=\"images/stt_icon_keyhelp_red.png\"> \u202C"
            printLog("change guideLangText.spacing: \""+ guideLangText.spacing + "\"")
            printLog("change guideLangText.imgString: " + guideLangText.imgString)
        } else if (currentLanguage === "vi-VN") {
            guideLangText.spacing = "&nbsp;"
            guideLangText.imgString = "<img src=\"images/stt_icon_keyhelp_red.png\">"
            printLog("change guideLangText.spacing: \""+ guideLangText.spacing + "\"")
            printLog("change guideLangText.imgString: " + guideLangText.imgString)
        } else if (currentLanguage === "ko-KR") {
            guideLangText.spacing = "&nbsp; &nbsp; &nbsp;&nbsp;"
            guideLangText.imgString = "<img src=\"images/stt_icon_keyhelp_red.png\">"
            printLog("change guideLangText.spacing: \""+ guideLangText.spacing + "\"")
            printLog("change guideLangText.imgString: " + guideLangText.imgString)
        } else if (currentLanguage === "ja-JP") {
            guideLangText.spacing = "&nbsp; "
            guideLangText.imgString = "<img src=\"images/stt_icon_keyhelp_red.png\">"
            printLog("change guideLangText.spacing: \""+ guideLangText.spacing + "\"")
            printLog("change guideLangText.imgString: " + guideLangText.imgString)
        } else {
            guideLangText.spacing = "&nbsp;&nbsp;"
            guideLangText.imgString = "<img src=\"images/stt_icon_keyhelp_red.png\">"
            printLog("change guideLangText.spacing: \""+ guideLangText.spacing + "\"")
            printLog("change guideLangText.imgString: " + guideLangText.imgString)
        }
    }
    function handleErrors(errorCode, errorText) {
        printLog("=== handleErrors ===")
        var title;
        var message;
        var leftButton;
        var rightButton;
        var buttons;
        var onClick;
        var params;

        guideText.text = "";

        switch(errorCode) {
        case "6040" :
            guideText.text = stringSet.strings["Try again after update is complete."];
            break;
        case "6020" : // "STT Mic device connection fail"
            guideText.text = stringSet.strings["Mic connection is unstable."];
            break;
        case "6021" : // "STT Network server is not respoding"
        case "6023" : // "STT Network unreachable"
        case "6032" : // errorText: NLP service not initialized
            guideText.text = stringSet.strings["Network server is not Responding. Try again."];
            break;
        case "6022" : // "STT Voice recognition server is not responding"
            guideText.text = stringSet.strings["Voice recognition server is not responding. Try again."];
            break;
        case "6027" : // "STT No results"
            guideText.text = stringSet.strings["Voice is not recognized. Try again."];
            break;
        case "6045" : // errorText : "Voice is loudly"
            guideText.text = stringSet.strings["Voice is not recognized. Keep your distance from the remote control and speak again."];
            break;
        case "6034" : // errorText: Wired lan cable connection needed
        case "6035" : // errorText: Wireless connection unstable
        case "6036" : // errorText: Network configuration needed
            title = "";
            message = stringSet.strings["Do you want to go to \"Network Settings\" now to check the connection?"];
            leftButton = "{\"position\":\"left\",\"label\":\"" + stringSet.strings["NO"] + "\"}";
            rightButton = "{\"position\":\"left\",\"label\":\"" + stringSet.strings["YES"] + "\"," + "\"onclick\": " + "\"palm://com.webos.applicationManager/launch\"" + "," + "\"params\": " + "{\"id\":\"com.palm.app.settings\",\"params\":{\"target\":\"network\"}}" + "}";
            buttons = "[" + leftButton + "," + rightButton + "]";
            createAlert(title, message, buttons);
            break;
        case "6038" : // errorText: End-User license agreement needed
            launchEula();
            break;
        default :
            guideText.text = errorText;
            break;
        }

        if (0 < guideText.text.length){
            canShowSTTView();
        }

        remainSeconds = 30;
        checkingRemainingTimeTimer.restart();
    }

    /// SLOT ///
    function slotCursorOn() {
        printWarningLog("=== slotCursorOn() ===")
        isCursorOn = true;
        switch(state){
        case "event_error":
            main.forceActiveFocus();
            break;
        case "event_langSelect":
            langSelectBox.focusOut();
            break;
        case "event_sessionEnd_0":
        case "event_sessionEnd_2":
        case "event_sessionEnd_3":
            resultListBox.focusOut();
            break;
        default:
            printWarningLog("Cursor on state : " + state)
        }
    }
    function slotCursorOff() {
        printWarningLog("=== slotCursorOff() ===")
        isCursorOn = false;
        switch(state){
        case "event_error":
            main.forceActiveFocus();
            break;
        case "event_sessionEnd_0":
        case "event_sessionEnd_2":
        case "event_sessionEnd_3":
            resultListBox.focusInit();
            break;
        default:
            printWarningLog("Cursor on state : " + state)
        }
    }

    // FUNCTION called when language loading is completed
    function slotLanguageChanged() {
        printLog("=== slotLanguageChanged() ===")
        //        guideText.text = qsTr("Speak to input text.")+qsTr(" (")+localeString.printLocale(selectedLanguage)+qsTr(")") + PluginProxy.emptyString; // i18n This sentence appears when user tries to input text by voice recognition.
        if(main.state === "event_micStart" || main.state === "event_energyLevel" || main.state === "event_error" ||
                main.state === "sttConnecting") {
            printLog("stopSpinner();")
            stopSpinner();
        } else {
            isLanguagedChanged = true;
            spinnerTimer.restart();
        }
    }

    states: [
        State {
            name: "init"
            PropertyChanges { target: micRec; state: "off" }
            PropertyChanges { target: micBackground; visible: true}
            PropertyChanges { target: guideText; visible: false}
            PropertyChanges { target: guideLangText; visible: false}
        },
        State {
            name: "off"
            PropertyChanges { target: micRec; state: "off" }
            PropertyChanges { target: micBackground; visible: true}
            PropertyChanges { target: sayAgainButton; opacity: 0 }
            PropertyChanges { target: guideText; visible: true}
            PropertyChanges { target: guideLangText; visible: true}
            PropertyChanges { target: guideRetryButton; visible: false}
        },
        State {
            name: "initial_error"
            PropertyChanges { target: micRec; state: "error" }
            PropertyChanges { target: micBackground; visible: true}
            PropertyChanges { target: sayAgainButton; opacity: 1 }
            PropertyChanges { target: guideImage; visible: true }
            PropertyChanges { target: guideText; visible: true}
            PropertyChanges { target: guideRetryButton; visible: false}
            PropertyChanges { target: guideLangText; visible: false}
        },
        State {
            name: "event_error"
            PropertyChanges { target: micRec; state: "hide" }
            PropertyChanges { target: micBackground; visible: true}
            PropertyChanges { target: sayAgainButton; opacity: 1 }
            PropertyChanges { target: guideImage; visible: true }
            PropertyChanges { target: guideText; visible: true}
            PropertyChanges { target: guideRetryButton; visible: true}
            PropertyChanges { target: guideLangText; visible: false}
        },
        State {
            name: "event_sttStart"
            PropertyChanges { target: micRec; state: "ready" }
            PropertyChanges { target: micBackground; visible: true}
            PropertyChanges { target: sayAgainButton; opacity: 0}
            PropertyChanges { target: guideText; visible: true}
            PropertyChanges { target: guideLangText; visible: true}
        },
        State {
            name: "event_micStart"
            PropertyChanges { target: micRec; state: "ready" }
            PropertyChanges { target: micBackground; visible: true}
            PropertyChanges { target: sayAgainButton; opacity: 0}
            PropertyChanges { target: guideText; visible: true}
            PropertyChanges { target: guideLangText; visible: true}
        },
        State {
            name: "event_langSelect"
            PropertyChanges { target: micRec; state: "langSelect"; opacity: 0.0 }
            PropertyChanges { target: micBackground; visible: false}
            PropertyChanges { target: sayAgainButton; opacity: 0}
            PropertyChanges { target: guideText; visible: false}
            PropertyChanges { target: guideLangText; visible: false}
            PropertyChanges { target: langSelectBox; visible: true}

        },
        State {
            name: "event_energyLevel"
            PropertyChanges { target: micRec; state: "energyLevel" }
            PropertyChanges { target: micBackground; visible: true}
            PropertyChanges { target: sayAgainButton; opacity: 0}
            PropertyChanges { target: guideText; visible: true}
            PropertyChanges { target: guideLangText; visible: true}
        },
        State {
            name: "event_sttConnecting"
            PropertyChanges { target: micRec; state: "processing" }
            PropertyChanges { target: micBackground; visible: true}
            PropertyChanges { target: guideLangText; visible: false}
        },
        State {
            name: "event_sttResult"
            PropertyChanges { target: micRec; state: "hide" }
            PropertyChanges { target: micBackground; visible: false}
        },
        State {
            name: "event_sessionEnd_0"
            PropertyChanges { target: micRec; state: "error" }
            PropertyChanges { target: micBackground; visible: true}
            PropertyChanges { target: guideText; visible: true}
            PropertyChanges { target: guideLangText; visible: true}
            PropertyChanges { target: sayAgainButton; opacity: 1 }
        },
        State {
            name: "event_sessionEnd_1"
            PropertyChanges { target: resultListBox; visible: true }
            PropertyChanges { target: micRec; state: "hide" }
            PropertyChanges { target: micBackground; visible: false}
            PropertyChanges { target: guideText; visible: 0}
            PropertyChanges { target: guideLangText; visible: false}
            PropertyChanges { target: sayAgainButton; opacity: 1 }
        },
        State {
            name: "event_sessionEnd_2"
            PropertyChanges { target: resultListBox; visible: true }
            PropertyChanges { target: resultTitle; opacity: 1 }
            PropertyChanges { target: resultListButton1; opacity: 1 }
            PropertyChanges { target: resultListButton2; opacity: 1 }
            PropertyChanges { target: sayAgainButton; opacity: 1 }

            PropertyChanges { target: micRec; state: "hide" }
            PropertyChanges { target: micBackground; visible: false}
            PropertyChanges { target: guideText; visible: false}
            PropertyChanges { target: guideLangText; visible: false}
        },
        State {
            name: "event_sessionEnd_3"
            PropertyChanges { target: resultListBox; visible: true }
            PropertyChanges { target: resultTitle; opacity: 1 }
            PropertyChanges { target: resultListButton1; opacity: 1 }
            PropertyChanges { target: resultListButton2; opacity: 1 }
            PropertyChanges { target: resultListButton3; opacity: 1 }
            PropertyChanges { target: sayAgainButton; opacity: 1 }

            PropertyChanges { target: micRec; state: "hide" }
            PropertyChanges { target: micBackground; visible: false}
            PropertyChanges { target: guideText; visible: false}
            PropertyChanges { target: guideLangText; visible: false}

        }
    ]
    transitions: [
        Transition {
            to: "event_sttConnecting"
            ScriptAction {
                script: {
                    ttsService.speakByAudioGuidance(stringSet.strings["Loading"], currentLanguage);
                }
            }
        }
    ]
}
