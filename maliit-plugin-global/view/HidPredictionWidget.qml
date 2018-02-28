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
import "../keyboard-common"

Rectangle {
    id: root
    objectName: "hidPredictionWidget"
    property QtObject globalStyle: GlobalStyle {}
    property variant predictions: Prediction.list
    property variant predictionSlice
    property int pageCnt: 1
    property int head: 0
    property int cnt: 0
    property int reminder: 0

    color: style.bgColor

    onPredictionsChanged: splitSlice()
    onHeadChanged: predictionSlice = predictions.slice(head, head+cnt)

    ListModel {
        id: cntArray
    }

    Row {
        id: predictionRow
        objectName: "predictionRow"
        anchors.top: parent.top
        anchors.left: parent.left
        spacing: root.globalStyle.hidPrediction.cellSpace
        width: root.globalStyle.hidPrediction.predictionRowWidth
        height: parent.height

        // Row frequently ignores the margin value of anchors.
        // So this Rectangle is used like the left margin.
        // And the Rectangles of the repeater will have the y value as top margin.
        Item {
            width: root.globalStyle.hidPrediction.leftMargin - root.globalStyle.hidPrediction.cellSpace
            height: parent.height
        }
        Repeater {
            id: predictionRepeater
            objectName: "predictionRepeater"
            model: predictionSlice
            onItemRemoved: item.removed = true
            HidPredictionItem {
                y: root.globalStyle.hidPrediction.topMargin
                width: cntArray && cntArray.get(pageCnt-1)
                       ? (
                             (((cntArray.get(pageCnt) && (cntArray.get(pageCnt).cnt === 0)) || pageCnt === cntArray.count) && cntArray.get(pageCnt-1).cnt !== 10)
                             ? (wordWidth + 2 * root.globalStyle.hidPrediction.leftMargin)
                             : (predictionRow.width + root.globalStyle.hidPrediction.cellSpace - root.globalStyle.hidPrediction.cellSpace * cntArray.get(pageCnt-1).cnt) * (predictionSlice[index].length + 2) / cntArray.get(pageCnt-1).lengthChar
                         )
                       : 0
                height: root.globalStyle.hidPrediction.cellHeight
                wordText: modelData
                hotKeyText: "F" + (index + 1)
                globalStyle: root.globalStyle
                onReleased: selectPrediction(wordText)
            }
        }
    }

    Row {
        id: prevNextRow
        objectName: "prevNextRow"
        anchors.top: parent.top
        anchors.topMargin: root.globalStyle.hidPrediction.topMargin
        anchors.right: parent.right
        anchors.rightMargin: root.globalStyle.hidPrediction.rightMargin
        spacing: root.globalStyle.hidPrediction.cellSpace

        HidPredictionItem {
            id: prevButton
            objectName: "prevButton"
            width: root.globalStyle.hidPrediction.moreWidth
            height: root.globalStyle.hidPrediction.cellHeight
            wordText: "<"   // FIXME: this should be replaced with image file.
            hotKeyText: "F11"
            globalStyle: root.globalStyle
            onReleased: showPrevPrediction()
        }
        HidPredictionItem {
            id: nextButton
            objectName: "nextButton"
            width: root.globalStyle.hidPrediction.moreWidth
            height: root.globalStyle.hidPrediction.cellHeight
            wordText: ">"   // FIXME: this should be replaced with image file.
            hotKeyText: "F12"
            globalStyle: root.globalStyle
            onReleased: showNextPrediction()
        }
    }

    function onSendKey(keycode) {
        if (keycode < Qt.Key_F1 || Qt.Key_F12 < keycode)
            return;

        if (keycode === Qt.Key_F11)
            showPrevPrediction();
        else if (keycode === Qt.Key_F12)
            showNextPrediction();
        else {
            var selectedIndex = keycode - Qt.Key_F1;
             if (selectedIndex < cntArray.get(pageCnt-1).cnt)
                 selectPrediction(Prediction.list[head + selectedIndex]);
        }
    }

    function selectPrediction(word) {
        if (word) {
            Prediction.onSelected(word);
            head = 0;
        }
    }

    function setFocusToHID() {
        root.focus = true;
    }

    function showPrevPrediction() {
        if (pageCnt > 1 && head - cntArray.get(pageCnt-2).cnt >= 0) {
            cnt = cntArray.get(pageCnt-2).cnt;
            head = head - cntArray.get(pageCnt-2).cnt;
            pageCnt -= 1;
            checkButtonState();
        }
    }

    function showNextPrediction() {
        if (cntArray.get(pageCnt) && cntArray.get(pageCnt).cnt && head + cntArray.get(pageCnt-1).cnt < Prediction.list.length) {
            cnt = cntArray.get(pageCnt).cnt;
            head = head + cntArray.get(pageCnt-1).cnt;
            pageCnt += 1;
            checkButtonState();
        }
    }

    function splitSlice() {
        pageCnt = 1;
        head = 0;
        var i;
        var indexArray =0;
        var cnt = 0;
        var lengthChar = 0;
        reminder = predictions.length;
        i = cntArray.count-1;
        while (i>=0) {
            cntArray.setProperty(i, "cnt", 0);
            cntArray.setProperty(i, "lengthChar", 0);
            i--;
        }
        for (i=0; i<predictions.length; i++) {
            cnt++;
            lengthChar += (predictions[i].length +2);
            if (lengthChar + cnt < root.globalStyle.hidPrediction.maxLengthChar && cnt < 10) {
                if (cnt !== reminder)
                    continue;
            } else if (lengthChar + cnt >= root.globalStyle.hidPrediction.maxLengthChar && cnt <= 10) {
                cnt--;
                lengthChar -= (predictions[i--].length +2);
                reminder -= cnt;
            } else if (cnt === 10) {
                reminder -= cnt;
            }
            if (cntArray.get(indexArray) && cntArray.get(indexArray).cnt === 0) {
                cntArray.setProperty(indexArray, "cnt", cnt);
                cntArray.setProperty(indexArray, "lengthChar", lengthChar);
            } else {
                cntArray.append({"cnt" : cnt, "lengthChar" : lengthChar});
            }
            indexArray++;
            lengthChar = 0;
            cnt = 0;
            continue;
        }
        if (cntArray.get(0)) {
            cnt = cntArray.get(0).cnt;
            predictionSlice = predictions.slice(head, cnt);
            checkButtonState();
        }
    }

    function checkButtonState() {
        // prev button
        if (pageCnt > 1 && head - cntArray.get(0).cnt >= 0)
            prevButton.state = "Normal";
        else
            prevButton.state = "Disable";

        // next button
        if (head + cntArray.get(pageCnt-1).cnt < predictions.length)
            nextButton.state = "Normal";
        else
            nextButton.state = "Disable";
    }
}
