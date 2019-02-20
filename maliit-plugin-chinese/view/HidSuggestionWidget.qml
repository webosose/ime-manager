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

Rectangle {
    id: root
    objectName: "hidPredictionWidget"
    property QtObject chineseStyle: []
    property variant suggestionList: Suggestion.list
    property int head: 0
    property int length: 8
    property bool isNext: Suggestion.next
    property bool isPrevious: Suggestion.previous
    property string currentLanguage: ""
    property string preedit: Suggestion.preedit
    color: style.bgColor

    Row {
        id: suggestionItems
        objectName: "predictionRow"
        anchors.top: parent.top
        anchors.left: parent.left
        spacing: root.chineseStyle.hidSuggestion.cellSpace

        // Row frequently ignores the margin value of anchors.
        // So this item is used like the left margin.
        // And the items of the repeater will have the y value as top margin.
        Item {
            width: root.chineseStyle.hidSuggestion.leftMargin - parent.spacing
            height: parent.height
        }

         ButtonBase {
            id: preeditBox
            objectName: "preeditBox"
            y: root.chineseStyle.hidSuggestion.topMargin
            state: "Disable"
            buttonStyle: root.chineseStyle.preeditBox
            text: Suggestion.preedit
            width: preeditBox.contentWidth > root.chineseStyle.preeditBox.width ?
                        preeditBox.contentWidth : root.chineseStyle.preeditBox.width
            height: root.chineseStyle.hidSuggestion.cellHeight
            onReleased: commitPreeditString()
        }

        Repeater {
            model: suggestionList
            onItemRemoved: item.removed = true
            HidSuggestionItem {
                wordText: modelData
                y: root.chineseStyle.hidSuggestion.topMargin
                width: contentWidth > root.chineseStyle.hidSuggestion.cellWidth ? contentWidth :
                root.chineseStyle.hidSuggestion.cellWidth
                height: root.chineseStyle.hidSuggestion.cellHeight
                hotKeyText: "F" + (index + 1)
                chineseStyle: root.chineseStyle
                onReleased: selectSuggestion(index)
            }
        }
    }

    HidSuggestionItem {
        id: prevButton
        objectName: "prevButton"
        state: "Disable"
        anchors.top: parent.top
        anchors.topMargin: root.chineseStyle.hidSuggestion.topMargin
        anchors.right: nextButton.left
        anchors.rightMargin: root.chineseStyle.hidSuggestion.cellSpace
        width: root.chineseStyle.hidSuggestion.cellWidth
        height: root.chineseStyle.hidSuggestion.cellHeight
        wordText: "<"
        hotKeyText: "F10"
        chineseStyle: root.chineseStyle
        onReleased: showPrevSuggestion()
    }

    HidSuggestionItem {
        id: nextButton
        objectName: "nextButton"
        state: "Disable"
        anchors.top: parent.top
        anchors.topMargin: root.chineseStyle.hidSuggestion.topMargin
        anchors.right: modeButton.left
        anchors.rightMargin: root.chineseStyle.hidSuggestion.cellSpace
        width: root.chineseStyle.hidSuggestion.cellWidth
        height: root.chineseStyle.hidSuggestion.cellHeight
        wordText: ">"
        hotKeyText: "F11"
        chineseStyle: root.chineseStyle
        onReleased: showNextSuggestion()
    }

    HidSuggestionItem {
        id: modeButton
        objectName: "modeButton"
        anchors.top: parent.top
        anchors.topMargin: root.chineseStyle.hidSuggestion.topMargin
        anchors.right: parent.right
        anchors.rightMargin: root.chineseStyle.hidSuggestion.rightMargin
        width: root.chineseStyle.hidSuggestion.cellWidth
        height: root.chineseStyle.hidSuggestion.cellHeight
        wordText: getInputModeString()
        hotKeyText: "F12"
        chineseStyle: root.chineseStyle
        onReleased: modeButtonPressed()
    }

    onIsNextChanged: checkNextButtonState()
    onIsPreviousChanged: checkPreviousButtonState()
    onPreeditChanged: checkPreeditState()

    function showNextSuggestion() {
        Suggestion.onNext();
    }

    function showPrevSuggestion() {
        Suggestion.onPrevious();
    }

    function selectSuggestion(index) {
        if (index >= 0 && index < suggestionList.length) {
            Suggestion.onSelected(index);
            head = 0;
        }
    }

    function commitPreeditString() {
        if (preedit.length > 0)
           Suggestion.onPreeditBoxPressed();
    }

    function onSendKey(keycode) {

        if (keycode === Qt.Key_F12) {
            modeButtonPressed();
            return;
        }

        if (keycode < Qt.Key_F1 || Qt.Key_F12 < keycode)
            return;

        if (keycode === Qt.Key_F10)
            showPrevSuggestion();
        else if (keycode === Qt.Key_F11)
            showNextSuggestion();
        else {
            var selectedIndex = keycode - Qt.Key_F1;
            selectSuggestion(selectedIndex);
        }
    }

    function checkPreviousButtonState() {
        // prev button
        if (isPrevious)
            prevButton.state = "Normal";
        else
            prevButton.state = "Disable";
    }

    function checkNextButtonState() {
        // next button
        if (isNext)
            nextButton.state = "Normal";
        else
            nextButton.state = "Disable";
    }

    function modeButtonPressed() {
       Suggestion.onModeButtonPressed();
    }

    function setLanguage(language) {
        currentLanguage = language;
        if (language === Languages.SIMPLIFIED_CHINESE)
            modeButton.state = "Disable";
        else
            modeButton.state = "Normal";
    }

    function getInputModeString() {
        if (currentLanguage === Languages.SIMPLIFIED_CHINESE)
            return Languages.HID_PINYIN_INPUT_MODE;
        else if (currentLanguage === Languages.TRADITIONAL_CHINESE)
            return Keyboard.shifted ? Languages.HID_ZHUYIN_INPUT_MODE : Languages.HID_CANJIE_INPUT_MODE;
        else
            return Keyboard.shifted ? Languages.HID_CANJIE_INPUT_MODE : Languages.HID_ZHUYIN_INPUT_MODE;
    }

    function checkPreeditState() {
        if (preedit.length > 0)
            preeditBox.state = "Normal"
        else
            preeditBox.state = "Disable"
    }

    function commitPreeditText() {
        if (preedit.length > 0)
           Suggestion.onPreeditBoxPressed();
    }

}
