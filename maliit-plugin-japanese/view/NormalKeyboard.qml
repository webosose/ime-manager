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
import com.meego.maliit 1.0

import "../keyboard-common"
import "variables.js" as Variables
import "japanesestyle.js" as JapaneseStyle
import "../keyboard-common/commonvariables.js" as CommonVariables

Rectangle {
    id: root
    objectName:"normalKeyboard"
    color: commonStyle.bgColor

    property alias mode: leftFunctionAreaJapanese.state
    property alias currLanguage: leftFunctionAreaJapanese.currLanguage
    property alias supportShiftMode: leftFunctionAreaJapanese.supportShiftMode
    property alias predictionNum: middleLayoutArea.predictionNum
    property alias predictionHead: middleLayoutArea.predictionHead
    property alias predictionMode: middleLayoutArea.predictionMode
    property alias currIndex: middleLayoutArea.currIndex
    property int contentType: 0
    property int enterKeyType: 0
    property real predictionPage: 0
    property bool showScreenKeyboard: true
    property bool showMore: false
    property int lastCloumn: 0
    property int lastFocusedArea: Variables.MiddleArea

    signal keyPressed(string rawcode, bool shift, int eventType)
    signal changeLanguage()
    signal clearAllPressed()
    signal activateSTT()
    signal reset()
    signal clickInputCharacterChangeButton(string mode)
    signal changeToSymbolMode()
    signal changeToHiraganaMode()
    signal meetTopBoundary()
    signal meetBottomBoundary()

    onEnabledChanged: {
        console.warn("@@@ enabled : " + enabled);
        setDefaultFocusOnVirtualKeybaord();
    }

    LeftFunctionAreaJapanese {
        id: leftFunctionAreaJapanese
        objectName: "leftFunctionAreaJapanese"
        anchors.top: parent.top
        anchors.topMargin: commonStyle.left.topMargin
        anchors.left: parent.left
        anchors.leftMargin: commonStyle.left.leftMargin
        width: commonStyle.left.width
        height: commonStyle.left.height

        onClickLanguageButton: root.changeLanguage()
        onClickInputCharacterChangeButton: {
            middleLayoutArea.clickInputCharacterChangeButton();
            root.clickInputCharacterChangeButton(root.mode);
        }

        onMeetRightBoundary: middleLayoutArea.setKeyNavigation(row, 0)
        onMeetBottomBoundary: {
            if (root.predictionMode)
                backButton.setKeyNavigation();
            else {
                bottom.setKeyNavigation(root.mode);
                bottom.checkMeetBottomBoundry();
                lastFocusedArea = Variables.LeftArea;
            }
        }
        onMeetLeftBoundary: row === JapaneseStyle.HiraganaKatakanaRows ? nextAndPreviousButton.setKeyNavigation() : rightFunctionArea.setKeyNavigation(row, "Left")
        onMeetTopBoundary: root.meetTopBoundary()
        onSetSymbolMode: {
            root.changeToSymbolMode();
        }
        onUnsetSymbolMode: {
            root.changeToHiraganaMode();
        }
    }

    MiddleLayout {
        id: middleLayoutArea
        objectName: "middleLayoutArea"
        mode: root.mode
        anchors.top: parent.top
        anchors.topMargin: commonStyle.middle.topMargin
        anchors.left: leftFunctionAreaJapanese.right
        anchors.leftMargin: root.mode === "Hiragana" || root.mode === "Katakana" ? JapaneseStyle.HiraganaKatakanaLeftRightMargin : commonStyle.middle.leftMargin
        width: commonStyle.middle.width + commonStyle.middle.cellSpace
        height: mode === "Hiragana" || mode === "Katakana" ? JapaneseStyle.JapaneseMiddleHeight : commonStyle.middle.height

        onSendKey: {
            root.keyPressed(rawcode, shift, eventType);
            if (root.mode === "FullWidth-English-Shift") {
                root.mode = "FullWidth-English";
                currRepeater.itemAt(currIndex).focus = true;
            }
        }
        onPressNextPrediction: root.drawPredictionLayout()
        onPredictionListSelected: setDefaultFocus();

        onMeetLeftBoundary: row === JapaneseStyle.HiraganaKatakanaRows ? backButton.setKeyNavigation() : leftFunctionAreaJapanese.setKeyNavigation(row)
        onMeetRightBoundary: row === JapaneseStyle.HiraganaKatakanaRows ? nextAndPreviousButton.setKeyNavigation() : rightFunctionArea.setKeyNavigation(row)
        onMeetBottomBoundary: {
            bottom.setKeyNavigation(root.mode);
            bottom.checkMeetBottomBoundry();
            root.lastCloumn = column;
            lastFocusedArea = Variables.MiddleArea;
        }
        onMeetTopBoundary: root.meetTopBoundary()
    }

    RightFunctionArea {
        id: rightFunctionArea
        objectName: "rightFunctionArea"
        anchors.right: parent.right
        anchors.rightMargin: commonStyle.right.rightMargin
        anchors.top: parent.top
        anchors.topMargin: commonStyle.right.topMargin
        width: commonStyle.right.width
        height: commonStyle.right.height
        enterText: {
            if(PluginProxy.unfixedStatus === true) {
                return Variables.EnterCaptionConfirm;
            } else {
                switch (enterKeyType) {
                    case Maliit.SearchEnterKeyType:
                        return Variables.EnterCaptionSearch;
                    case Maliit.DefaultEnterKeyType:
                        return Variables.EnterCaptionFnish;
                }
            }
        }

        Component.onCompleted: {
            clickClearAllButton.connect(clearAllPressed);
            sendKey.connect(keyPressed);
        }

        onMeetLeftBoundary: {
            if (!predictionMode) {
                if (mode === "Hiragana" && row === JapaneseStyle.HiraganaKatakanaRows - 1) {
                    middleLayoutArea.setKeyNavigationToConvert();
                } else if (mode === "Katakana" && row === JapaneseStyle.HiraganaKatakanaRows - 1) {
                    middleLayoutArea.setKeyNavigation(row, -1);
                } else {
                    if (row <= JapaneseStyle.SymbolEnglishRows - 1) middleLayoutArea.setKeyNavigation(row, -1);
                    else bottom.setKeyNavigation(root.mode);
                }
            } else {
                middleLayoutArea.setKeyNavigation(row, -1);
            }
        }
        onMeetRightBoundary: {
            if (row === JapaneseStyle.HiraganaKatakanaRows){
                return backButton.setKeyNavigation()
            } else if (row === 4 && root.mode !== "Hiragana" && root.mode !== "Katakana") {
                return bottom.setKeyNavigation(root.mode)
            } else {
                return leftFunctionAreaJapanese.setKeyNavigation(row)
            }
        }
        onMeetTopBoundary: root.meetTopBoundary()
        onMeetBottomBoundary: {
            if (predictionMode)
                nextAndPreviousButton.setKeyNavigation();
            else {
                bottom.setKeyNavigation(root.mode, true);
                bottom.checkMeetBottomBoundry(true)
                lastFocusedArea = Variables.RightArea;
            }
        }
    }

    NextAndPreviousButton {
        id: nextAndPreviousButton
        objectName: "nextAndPreviousButton"
        anchors.right: parent.right
        anchors.rightMargin: commonStyle.right.rightMargin
        anchors.top: rightFunctionArea.bottom
        anchors.topMargin: commonStyle.right.cellSpace
        width: commonStyle.right.width
        height: commonStyle.right.cellHeight
        text: predictionPageTxt
        visible: false
        showNextButton: predictionNum < Prediction.list.length
        showPreviousButton: predictionNum > (Variables.FullScreenPredictionRows * Variables.FullScreenPredictionColumns)
        onNextPrediction: {
            root.drawPredictionLayout();
            middleLayoutArea.predictionHead += Variables.FullScreenPredictionRows * Variables.FullScreenPredictionColumns;
        }
        onPreviousPrediction: {
            predictionNum -= Variables.FullScreenPredictionRows * Variables.FullScreenPredictionColumns * 2;
            root.drawPredictionLayout();
            middleLayoutArea.predictionHead -= Variables.FullScreenPredictionRows * Variables.FullScreenPredictionColumns;
        }

        onMeetRightBoundary : backButton.setKeyNavigation()
        onMeetTopBoundary: rightFunctionArea.setKeyNavigation(4)
        onMeetLeftBoundary: {
            if (!middleLayoutArea.setKeyNavigation(-1, -1)) {
                backButton.setKeyNavigation();
            }
        }
        onMeetBottomBoundary : root.meetBottomBoundary()

    }

    PredictiveBottom {
        id: bottom
        objectName: "bottom"
        anchors.left: root.left
        anchors.leftMargin: commonStyle.bottom.leftMargin
        anchors.right: rightFunctionArea.left
        anchors.rightMargin: root.mode === "Hiragana" || root.mode === "Katakana" ? JapaneseStyle.HiraganaKatakanaLeftRightMargin : commonStyle.bottom.rightMargin
        anchors.top: middleLayoutArea.bottom
        anchors.topMargin: commonStyle.middle.cellSpace

        height: commonStyle.bottom.height
        words: !predictionMode ? selectPredictionWords() : undefined
        showMoreButton: showMore
        showBackButton: predictionMode
        showSpaceBar: root.mode !== "Hiragana" && root.mode !== "Katakana"
        onSendKey: root.keyPressed(rawcode, shift, eventType)
        onSelectPredictionWord: {
            Prediction.onSelected(index);
            predictionMode = false;
            predictionNum = 0;
            predictionHead = 0;
            meetTopBoundary();
        }
        onPressMore: {
            root.drawPredictionLayout();
            nextAndPreviousButton.y = 0;
            nextAndPreviousButton.visible = true;
        }
        onPressBack: {
            setToDefault(true);
            showMore = true;
        }
        onMeetLeftBoundary: {
            if (root.mode !== "Hiragana" )
                rightFunctionArea.setKeyNavigation(-1)
        }
        onMeetRightBoundary: {
            if (root.mode !== "Hiragana" )
                rightFunctionArea.setKeyNavigation(-1)
        }
        onMeetTopBoundary: {
            if (lastFocusedArea === Variables.MiddleArea) {
                if (root.lastCloumn === Variables.ConvertKeyColumn)
                    middleLayoutArea.setKeyNavigationToConvert();
                else
                    middleLayoutArea.setKeyNavigation(-1, root.lastCloumn);
            }
            else if (lastFocusedArea === Variables.LeftArea && root.mode === "Symbol")
                leftFunctionAreaJapanese.setKeyNavigation(1);
            else if (lastFocusedArea === Variables.LeftArea && root.mode === "FullWidth-English")
                leftFunctionAreaJapanese.setKeyNavigation(3);
            else if (lastFocusedArea === Variables.RightArea)
                rightFunctionArea.setKeyNavigation(4);
        }
        onMeetBottomBoundary: root.meetBottomBoundary()
        onPredictionSelected: meetTopBoundary()//setDefaultFocus()
    }

    // back button at the prediction mode
    ButtonBase {
        id: backButton
        objectName: "backButton"
        anchors.left: root.left
        anchors.leftMargin: commonStyle.bottom.leftMargin
        anchors.top: middleLayoutArea.bottom
        anchors.topMargin: commonStyle.middle.cellSpace
        text: Variables.BackButton
        width: predictionMode ? commonStyle.left.width : 0
        height: commonStyle.bottom.height
        visible: predictionMode
        onReleased: {
            setToDefault(true);
            showMore = false;
        }

        Keys.onPressed: {
            if (event.key === Qt.Key_Up) {
                leftFunctionAreaJapanese.setKeyNavigation(2);
                event.accepted = true;
            } else if (event.key === Qt.Key_Right) {
                if (!middleLayoutArea.setKeyNavigation(-1, 0)) {
                    nextAndPreviousButton.setKeyNavigation();
                }
                event.accepted = true;
            } else if (event.key === Qt.Key_Left) {
                nextAndPreviousButton.setKeyNavigation("Back");
                event.accepted = true;
            } else if (event.key === Qt.Key_Down) {
                meetBottomBoundary()
                event.accepted = true;
            }
        }

        function setKeyNavigation() {
            backButton.focus = true;
        }
    }

    onModeChanged: {
        Prediction.clearPredictionList();
        showMore = false;
    }

    Connections {
        target: Prediction
        onActiveChanged: {
            if (!active) {
                root.predictionMode = false;
                root.predictionNum = 0;
                nextAndPreviousButton.visible = false;
                showMore = false;
            }
        }
    }

    function selectPredictionWords() {
        var bottomWidth = JapaneseStyle.windowWidth - commonStyle.left.leftMargin - commonStyle.right.rightMargin;
        var predictionWidth = 0;
        var words = [];
        var str = "";
        showMore = false;
        for (var i = 0; i < Prediction.list.length; i++) {
            str = Prediction.list[i];
            predictionWidth += (str.length * commonStyle.predictionButton.normal.fontSize)+8;

            if (bottomWidth < predictionWidth) {
                showMore = true;
                break;
            }

            predictionWidth += commonStyle.predictionBar.spacing;
            words.push(Prediction.list[i]);
        }
        return words;
    }

    function drawPredictionLayout() {
        var row = Variables.FullScreenPredictionRows;
        var column = Variables.FullScreenPredictionColumns;
        var model = [];
        for (var i = 0; i < row * column; i++) {
            if (Prediction.list[predictionNum] !== undefined) {
                model.push(Prediction.list[predictionNum]);
            } else {
                model.push('');
            }
            predictionNum++;
        }

        // set layout to grid
        predictionMode = true;
        middleLayoutArea.setPredictionLayoutData(row, column, model);
        showPageText();
        setDefaultFocus();
    }

    function setToDefault(visible) {
        predictionMode = false;
        predictionNum = 0;
        predictionHead = 0;
        mode = "Hiragana";
        middleLayoutArea.clickInputCharacterChangeButton();
        leftFunctionAreaJapanese.setToDefault();
        leftFunctionAreaJapanese.supportShiftMode = false;
        nextAndPreviousButton.visible = false;
        setDefaultFocus();
    }

    function setEnterKeyText (unfixedStatus) {
        if (unfixedStatus === true) {
            return Variables.EnterCaptionConfirm;
        } else {
            switch (enterKeyType) {
                case Maliit.SearchEnterKeyType:
                    return Variables.EnterCaptionSearch;
                case Maliit.DefaultEnterKeyType:
                    return Variables.EnterCaptionFnish;
            }
        }
    }

    function setDefaultFocus() {
        if( middleLayoutArea.defaultFocus !== undefined )
            middleLayoutArea.currRepeater.itemAt(middleLayoutArea.defaultFocus).focus = true;
    }

    function setFocusToEnter() {
        rightFunctionArea.setFocusTo("Enter");
    }

    function showPageText() {
        var currentPageNum = 0;
        var totalPgaeNum = 0;
        var currentPageTxt = "";
        var totalPgaeTxt = "";

        predictionPage = Prediction.list.length % (Variables.FullScreenPredictionRows * Variables.FullScreenPredictionColumns);
        if (predictionPage === 0) {
            currentPageNum = predictionNum / (Variables.FullScreenPredictionRows * Variables.FullScreenPredictionColumns);
            totalPgaeNum = Prediction.list.length / (Variables.FullScreenPredictionRows * Variables.FullScreenPredictionColumns);
        } else {
            currentPageNum = predictionNum / (Variables.FullScreenPredictionRows * Variables.FullScreenPredictionColumns);
            totalPgaeNum = Prediction.list.length / (Variables.FullScreenPredictionRows * Variables.FullScreenPredictionColumns) + 1;
        }

        currentPageTxt = parseInt(currentPageNum);;
        totalPgaeTxt = parseInt(totalPgaeNum);

        nextAndPreviousButton.predictionPageTxt = currentPageTxt + "/" + totalPgaeTxt;
        nextAndPreviousButton.text = nextAndPreviousButton.predictionPageTxt;
    }
}
