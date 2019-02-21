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
import com.meego.maliit 1.0

import "../keyboard-common"
import "../keyboard-common/commonvariables.js" as CommonVariables
import "variables.js" as Variables

Rectangle {
    id: root
    objectName: "normalKeyboard"
    color: style.bgColor

    property alias mode: leftFunctionArea.state
    property alias currLanguage: leftFunctionArea.currLanguage
    property alias languageLabel: leftFunctionArea.languageLabel
    property alias supportShiftMode: leftFunctionArea.supportShiftMode
    property alias supportExpandMode: leftFunctionArea.supportExpandMode
    property alias supportExpandShiftMode: leftFunctionArea.supportExpandShiftMode
    property alias predictionIndex: middleLayoutArea.predictionIndex
    property alias predictionMode: middleLayoutArea.predictionMode
    property alias supportPageButton: leftFunctionArea.supportPageButton
    property int contentType: 0
    property int enterKeyType: 0
    property bool showScreenKeyboard: true
    property bool activateLanguageButton : false

    signal ttsService(string text)
    signal keyPressed(string rawcode, bool shift)
    signal keysymPressed(string keysym)
    signal textKeyPressed(string text)
    signal changeLanguage()
    signal clearAllPressed()
    signal meetTopBoundary()

    onFocusChanged: if (focus) CommonVariables.savedFocusItem = middleLayoutArea.getMiddleItem()

    LeftFunctionArea {
        id: leftFunctionArea
        objectName: "leftFunctionArea"
        anchors.top: parent.top
        anchors.topMargin: style.left.topMargin
        anchors.left: parent.left
        anchors.leftMargin: style.left.leftMargin
        width: style.left.width
        height: style.left.height
        activateLanguageButton: root.activateLanguageButton

        onClickLanguageButton: root.changeLanguage()
        onTtsService: root.ttsService(text)

        onMeetRightBoundary: middleLayoutArea.setKeyNavigation(row, 0, "Right")
        onMeetBottomBoundary: bottom.setKeyNavigation(-1)
        onMeetLeftBoundary: { /* Do Nothing */ }
        onMeetTopBoundary: root.meetTopBoundary()
    }

    MiddleLayout {
        id: middleLayoutArea
        objectName: "middleLayoutArea"

        function checkShift(mode) {
            if (mode === "Normal-Shift" && !root.supportPageButton)
                return "Normal";
            else if (mode === "Expand-Shift")
                return "Expand";
            else
                return mode;
        }

        mode: root.mode
        anchors.top: parent.top
        anchors.topMargin: style.middle.topMargin
        anchors.left: leftFunctionArea.right
        anchors.leftMargin: style.middle.leftMargin
        width: style.middle.width + style.middle.cellSpace
        height: style.middle.height

        onCurrRepeaterChanged: CommonVariables.savedFocusItem = middleLayoutArea.getMiddleItem()
        onModelChanged: CommonVariables.savedFocusItem = middleLayoutArea.getMiddleItem()

        onSendKey: {
            root.keyPressed(rawcode, shift);
            root.mode = checkShift(root.mode);
        }

        onSendKeysym: {
            root.keysymPressed(keysym);
            root.mode = checkShift(root.mode);
        }

        onSendText: {
            root.textKeyPressed(text)
            root.mode = checkShift(root.mode);
        }
        onPressNextPrediction: {
            if (contentType !== Maliit.EmailContentType && contentType !== Maliit.UrlContentType)
                root.drawPredictionLayout();
        }
        onTtsService: root.ttsService(text)

        onMeetLeftBoundary: leftFunctionArea.setKeyNavigation(row)
        onMeetRightBoundary: rightFunctionArea.setKeyNavigation(row)
        onMeetBottomBoundary: bottom.setKeyNavigation(column)
        onMeetTopBoundary: root.meetTopBoundary()
    }

    RightFunctionArea {
        id: rightFunctionArea
        objectName:"rightFunctionArea"
        anchors.right: parent.right
        anchors.rightMargin: style.right.rightMargin
        anchors.top: parent.top
        anchors.topMargin: style.right.topMargin
        width: style.right.width
        height: style.right.height

        onTtsService: root.ttsService(text)
        Component.onCompleted: {
            clickClearAllButton.connect(clearAllPressed);
            sendKey.connect(keyPressed);
        }

        onMeetLeftBoundary: {
            if (row < 4) middleLayoutArea.setKeyNavigation(row, -1, "Left");
            else bottom.setKeyNavigation("defaultIndex"); //preColumn
        }
        onMeetRightBoundary: { /* Do Nothing */ }
        onMeetTopBoundary: root.meetTopBoundary()
        onMeetBottomBoundary: { /* Do Nothing */ }
    }

    PredictiveBottom {
        id: bottom
        objectName: "bottom"
        anchors.left: root.left
        anchors.leftMargin: style.bottom.leftMargin
        anchors.right: rightFunctionArea.left
        anchors.rightMargin: style.bottom.rightMargin
        anchors.bottom: parent.bottom
        anchors.bottomMargin: style.bottom.bottomMargin

        height: style.bottom.height
        constantPrediction: (contentType === Maliit.UrlContentType) || (contentType === Maliit.EmailContentType)
        words: !predictionMode ? Prediction.list.slice(0, bottom.maxLength) : undefined
        showMoreButton: (!predictionMode) && (maxLength < Prediction.list.length)
        showBackButton: predictionMode
        onSendKey: root.keyPressed(keycode, shift)
        onSelectPredictionWord: {
            Prediction.onSelected(word);
            predictionMode = false;
            predictionIndex = 0;
        }
        onPressMore: {
            if (contentType !== Maliit.EmailContentType && contentType !== Maliit.UrlContentType)
                root.drawPredictionLayout();
        }
        onPressBack: setToDefault(true)
        onTtsService: root.ttsService(text)

        onMeetLeftBoundary: { /* Do Nothing */ }
        onMeetRightBoundary: rightFunctionArea.setKeyNavigation(-1)
        onMeetTopBoundary: {
            if (column === -1)
                leftFunctionArea.setKeyNavigation(3);
            else
                middleLayoutArea.setKeyNavigation(-1, column, "Up");
        }
        onMeetBottomBoundary: { /* Do Nothing */ }
    }

    Keys.onPressed: {
        if (event.key === Qt.Key_Up)
            PluginProxy.onHideRequested(true);
    }

    onModeChanged: {
        if (predictionMode)
            setToDefault()
        CommonVariables.savedFocusItem = middleLayoutArea.getMiddleItem();
    }

    Connections {
        target: Prediction
        onActiveChanged: {
            if (!active) {
                root.predictionMode = false;
                root.predictionIndex = 0;
            }
        }
        onPredictionListChanged: {
            if (predictionMode) {
                root.predictionIndex = 0;
                root.drawPredictionLayout();
            }
        }
    }

    function setDefaultFocus() {
        if( middleLayoutArea.defaultFocus !== undefined ) {
            CommonVariables.savedFocusItem.focus = false;
            CommonVariables.savedFocusItem = middleLayoutArea.currRepeater.itemAt(middleLayoutArea.defaultFocus);
        }
    }

    function setLanguage(language, label, langCode, data) {
        currLanguage = language;
        languageLabel = label;
        style.setDefaultFont(langCode);
        mode = "Normal";

        if ( currLanguage === 'Arabic' || currLanguage === 'Kurdish' || currLanguage === 'Hindi')
            root.supportPageButton = true;
        else
            root.supportPageButton = false;
        if (currLanguage === 'Hebrew')
            root.supportShiftMode = false;
        else
            root.supportShiftMode = true;

        drawLayout(data);
    }

    function drawLayout(data) {
        supportExpandMode = data.supportAccent;
        supportExpandShiftMode = data.supportAccentEx;

        // set language grid
        middleLayoutArea.setLayoutData(data.row, data.column, data.keys);

        // set symbol grid
        var symbolColumnLength = (data.column < 12) ? 10 : 12;
        if (middleLayoutArea.symbolColumns !== symbolColumnLength) {
            middleLayoutArea.setSymbolLayoutData(
                        4, symbolColumnLength,
                        (symbolColumnLength === 10) ? Variables.symbolSet10x4 : Variables.symbolSet12x4);
        }

        middleLayoutArea.defaultFocus = ( 2 * data.column ) + Math.round( data.column/2 ) - 1;
    }

    function drawPredictionLayout() {
        var row = 4;
        var column = 5;
        var i = 0;

        var model = [];
        for (i = 0; i < row * column - 1; i++) {    // 1 cell is reserved for the [...] button
            if (Prediction.list[predictionIndex + i] !== undefined)
                model.push(Prediction.list[predictionIndex + i]);
            else
                break;
        }

        // set layout to grid
        middleLayoutArea.setPredictionLayoutData(row, column, model);
        predictionMode = true;
        predictionIndex += i;
    }

    function setToDefault() {
        predictionMode = false;
        predictionIndex = 0;
        mode = "Normal";
    }

    function setFocusToEnter() {
        rightFunctionArea.setFocusTo("Enter");
    }
}
