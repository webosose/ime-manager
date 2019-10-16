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

import "japanesestyle.js" as JapaneseStyle
import "variables.js" as Variables

Rectangle {
    id: root
    objectName: "hidPredictionWidget"
    property variant predictionList: Prediction.list
    property variant predictionListSlice: Prediction.list.slice(head, head + JapaneseStyle.hidPrediction.length)
    property int head: 0
    property int length: JapaneseStyle.hidPrediction.length
    property int mode: Variables.HidModeRomanHira
    signal setHidModeFromVkb(int mode)

    color: commonStyle.bgColor

    Row {
        anchors.top: parent.top
        anchors.left: parent.left
        spacing: JapaneseStyle.hidPrediction.cellSpace

        Item {
            width: JapaneseStyle.hidPrediction.leftMargin - parent.spacing
            height: parent.height
        }

        Repeater {
            model: predictionListSlice
            onItemRemoved: item.removed = true
            HidPredictionItem {
                y: JapaneseStyle.hidPrediction.topMargin
                width: JapaneseStyle.hidPrediction.cellWidth
                height: JapaneseStyle.hidPrediction.cellHeight
                wordText: modelData
                hotKeyText: "F" + (index + 1)
                onReleased: selectPrediction(head + index)
            }
        }
    }

    Row {
        anchors.top: parent.top
        anchors.topMargin: JapaneseStyle.hidPrediction.topMargin
        anchors.right: parent.right
        anchors.rightMargin: JapaneseStyle.hidPrediction.rightMargin
        spacing: JapaneseStyle.hidPrediction.cellSpace
        HidPredictionItem {
            id: prevButton
            objectName: "prevButton"
            width: JapaneseStyle.hidPrediction.moreWidth
            height: JapaneseStyle.hidPrediction.cellHeight
            wordText: "<"   // FIXME: this should be replaced with image file.
            hotKeyText: "F10"
            onReleased: showPrevPrediction()
        }
        HidPredictionItem {
            id: nextButton
            objectName: "nextButton"
            width: JapaneseStyle.hidPrediction.moreWidth
            height: JapaneseStyle.hidPrediction.cellHeight
            wordText: ">"   // FIXME: this should be replaced with image file.
            hotKeyText: "F11"
            onReleased: showNextPrediction()
        }
        HidPredictionItem {
            id: indicator
            objectName: "indicator"
            width: JapaneseStyle.hidPrediction.indicatorWidth
            height: JapaneseStyle.hidPrediction.cellHeight
            wordText: Variables.HidModeCaption[root.mode]
            hotKeyText: "F12"
            onReleased: nextHidMode()
        }
    }
    onPredictionListSliceChanged: checkButtonState()
    onPredictionListChanged: head=0

    function onSendKey(keycode) {
        if (keycode < Qt.Key_F1 || Qt.Key_F12 < keycode)
            return;

        if (keycode === Qt.Key_F10)
            showPrevPrediction();
        else if (keycode === Qt.Key_F11)
            showNextPrediction();
        else if (keycode === Qt.Key_F12)
            nextHidMode();
        else {
            var selectedIndex = keycode - Qt.Key_F1;
            selectPrediction(head + selectedIndex);
        }
    }

    function selectPrediction(index) {
        if (index >= 0 && index < Prediction.list.length) {
            Prediction.onSelected(index);
            head = 0;
        }
    }

    function showPrevPrediction() {
        if (head - length >= 0)
            head -= length;
        checkButtonState();
    }

    function showNextPrediction() {
        if (head + length < Prediction.list.length)
            head = head + length;
        checkButtonState();
    }

    function checkButtonState() {
        // prev button
        if (head - length >= 0)
            prevButton.state = "Normal";
        else
            prevButton.state = "Disable";

        // next button
        if (head + length < Prediction.list.length)
            nextButton.state = "Normal";
        else
            nextButton.state = "Disable";
    }

    function setHidModeFromHid(hidMode) {
        mode = hidMode;
    }

    function setFocusToHID() {
        root.focus = true;
    }

    function nextHidMode() {
        mode++;
        if (Variables.HidModeKanaKata < mode)
            mode = Variables.HidModeRomanHira;
        setHidModeFromVkb(mode);
    }

    function setHidModeforNumberContent() {
        setHidModeFromVkb(Variables.HidModeHalfWidthEnglish);
    }
}