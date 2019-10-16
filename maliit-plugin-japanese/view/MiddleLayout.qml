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
import "../keyboard-common"
import "variables.js" as Variables
import "japanesestyle.js" as JapaneseStyle
import "../keyboard-common/commonvariables.js" as CommonVariables

Rectangle {
    id: middle
    objectName: "middleLayout"
    width: parent.width
    height: parent.height
    color: commonStyle.bgColor
    property int columns: JapaneseStyle.HiraganaKatakanaColumns
    property int rows: JapaneseStyle.HiraganaKatakanaRows
    property string mode: "Hiragana"
    property Repeater currRepeater: letterRepeater
    property bool predictionMode: false
    property int predictionNum: 0
    property int predictionHead: 0
    property var hiraganaModel: []
    property var katakanaModel: []
    property var fullWidthEnglishLowercaseModel: []
    property var fullWidthEnglishUppercaseModel: []
    property var symbolModel: []
    property int defaultFocus
    property int currIndex: 0

    signal sendKey(string rawcode, bool shift, int eventType)
    signal sendCurrIndex(int index)
    signal pressNextPrediction()
    signal meetLeftBoundary(int row)
    signal meetRightBoundary(int row)
    signal meetTopBoundary(int column)
    signal meetBottomBoundary(int column)
    signal predictionListSelected()

    function checkNavigationKey(index, key) {
        var accepted = false;
        var rowIndex = Math.floor(index / middle.columns);
        var colIndex = index % middle.columns;

        if (!predictionMode) {
            if (key === Qt.Key_Up && rowIndex === 0) {
                meetTopBoundary(colIndex);
                accepted = true;
            } else if (key === Qt.Key_Down ) {
                if (mode === "Hiragana" && (colIndex === middle.columns - 1 || colIndex === middle.columns - 2) && rowIndex === middle.rows - 2) {
                   convertButton.focus = true;
                    accepted = true;
                } else if (rowIndex === middle.rows - 1) {
                    meetBottomBoundary(colIndex);
                    accepted = true;
                }
            } else if (key === Qt.Key_Left && colIndex === 0) {
                meetLeftBoundary(rowIndex);
                accepted = true;
            } else if (key === Qt.Key_Right) {
                if (mode === "Hiragana" && colIndex === middle.columns - 3 && rowIndex === middle.rows - 1) {
                    convertButton.focus = true;
                    accepted = true;
                } else if (mode === "Katakana" && colIndex === middle.columns - 3 && rowIndex === middle.rows - 1) {
                    meetRightBoundary(rowIndex);
                    accepted = true;
                } else if (colIndex === middle.columns - 1){
                    meetRightBoundary(rowIndex);
                    accepted = true;
                }
            }
        }
        return accepted;
    }

    onModeChanged: {
        if (mode === "Hiragana" || mode === "Katakana") {
            middle.columns = JapaneseStyle.HiraganaKatakanaColumns;
            middle.rows = JapaneseStyle.HiraganaKatakanaRows;
            currRepeater = letterRepeater;
        } else if (mode === "Symbol") {
            middle.columns = JapaneseStyle.SymbolColumns;
            middle.rows = JapaneseStyle.SymbolEnglishRows;
            currRepeater = letterRepeater;
        } else {
            middle.columns = JapaneseStyle.EnglishColumns;
            middle.rows = JapaneseStyle.SymbolEnglishRows;
            currRepeater = letterRepeater;
        }
    }

    onPredictionModeChanged: {
        if (predictionMode) {
            middle.columns = predictionGrid.columns;
            middle.rows = predictionGrid.rows;
            currRepeater = predictionRepeater;
        } else {
            modeChanged();
        }
    }

    onSendCurrIndex: {
        currIndex = index;
    }

    /* key buttons */
    Grid {
        id: middleGrid
        objectName: "middleGrid"
        rows: (mode === "Hiragana" || mode === "Katakana") ? 5 : 4
        x: 0
        y: (!predictionMode) ? 0 : 1000
        spacing: commonStyle.middle.cellSpace

        Repeater {
            id: letterRepeater
            objectName: "letterRepeater"
            LetterButton {
                mode: middle.mode
                height: commonStyle.middle.cellHeight
                width: {
                    if (mode === "Hiragana" || mode === "Katakana")
                        JapaneseStyle.HiraganaKatakanaCellWidth
                    else if (mode === "Symbol")
                        (commonStyle.middle.width + commonStyle.middle.cellSpace)/JapaneseStyle.SymbolColumns - commonStyle.middle.cellSpace
                    else
                        (commonStyle.middle.width + commonStyle.middle.cellSpace)/JapaneseStyle.EnglishColumns - commonStyle.middle.cellSpace
                }

                hiraganaChar: modelData.hiraganaChar ? modelData.hiraganaChar : ""
                katakanaChar: modelData.katakanaChar ? modelData.katakanaChar : ""
                fullWidthEnglishLowercaseChar: modelData.fullWidthEnglishLowercaseChar ? modelData.fullWidthEnglishLowercaseChar : ""
                fullWidthEnglishUppercaseChar: modelData.fullWidthEnglishUppercaseChar ? modelData.fullWidthEnglishUppercaseChar : ""
                symbolChar: modelData.symbolChar ? modelData.symbolChar : ""
                hiraganaRawcode: modelData.hiraganaRawcode ? modelData.hiraganaRawcode : "-1"
                katakanaRawcode: modelData.katakanaRawcode ? modelData.katakanaRawcode : "-1"
                fullWidthEnglishLowercaseRawcode: modelData.fullWidthEnglishLowercaseRawcode ? modelData.fullWidthEnglishLowercaseRawcode : "-1"
                fullWidthEnglishUppercaseRawcode: modelData.fullWidthEnglishUppercaseRawcode ? modelData.fullWidthEnglishUppercaseRawcode : "-1"
                symbolRawcode: modelData.symbolRawcode ? modelData.symbolRawcode : "-1"
                image: ""

                onSendKey: {
                    middle.sendCurrIndex(index);
                    middle.sendKey(rawcode, shift, eventType);
                }

                KeyNavigation.down: letterRepeater.itemAt(index + middle.columns)
                KeyNavigation.up: letterRepeater.itemAt(index - middle.columns)
                KeyNavigation.left: letterRepeater.itemAt(index - 1)
                KeyNavigation.right: letterRepeater.itemAt(index + 1)
                Keys.onPressed: {
                    event.accepted = checkNavigationKey(index, event.key)
                    if ((mode === "Hiragana" || mode === "Katakana") && letterRepeater.itemAt(Variables.HiraganaKatakanaSpaceButtonIndex).state === "Select") {
                        letterRepeater.itemAt(Variables.HiraganaKatakanaSpaceButtonIndex).image = "qrc:///images/spacebar-dark.png";
                    }
                }

                Connections {
                    target: PluginProxy
                    onKeyReleased : {
                        if (isReleased && currRepeater.itemAt(currIndex).focus)
                            currRepeater.itemAt(currIndex).state = "Focus";
                        if ((mode === "Hiragana" || mode === "Katakana") && letterRepeater.itemAt(Variables.HiraganaKatakanaSpaceButtonIndex).state !== "Select") {
                            letterRepeater.itemAt(Variables.HiraganaKatakanaSpaceButtonIndex).image = "qrc:///images/spacebar.png";
                        }
                    }
                }
            }
        }

        ButtonBase {
            id: convertButton
            objectName: "convertButton"
            width: JapaneseStyle.HiraganaKatakanaCellWidth
            height: commonStyle.middle.cellHeight
            visible: middle.mode === "Hiragana" ? true : false
            text: Variables.ConvertKeyCaption
            onReleased: sendKey(Variables.ConvertRawCode, false, eventType)

            Keys.onPressed: {
                if (event.key === Qt.Key_Up) {
                    setKeyNavigation(middle.rows - 2, middle.columns - 2);
                    event.accepted = true;
                } else if (event.key === Qt.Key_Down) {
                    meetBottomBoundary(middle.columns - 2);
                    event.accepted = true;
                } else if (event.key === Qt.Key_Right) {
                    meetRightBoundary(middle.rows - 1);
                    event.accepted = true;
                } else if (event.key === Qt.Key_Left) {
                    setKeyNavigation(middle.rows - 1, middle.columns - 3);
                    event.accepted = true;
                }
            }

            Connections {
                target: PluginProxy
                onKeyReleased : {
                    if (isReleased && (convertButton.state === "Select"))
                        convertButton.state = "Focus";
                }
            }
        }
    }

    /* predicted word list */
    Grid {
        id: predictionGrid
        objectName: "predictionGrid"
        spacing: commonStyle.middle.cellSpace
        x: 0; y: predictionMode ? 0 : 1000

        Repeater {
            id: predictionRepeater
            objectName: "predictionRepeater"
            ButtonBase {
                width: (commonStyle.middle.width + predictionGrid.spacing)/predictionGrid.columns - predictionGrid.spacing
                height: commonStyle.middle.cellHeight
                text: modelData
                visible: modelData !== undefined && modelData !== ""
                onReleased: {
                    Prediction.onSelected(predictionHead + index);
                    predictionMode = false;
                    predictionNum = 0;
                    predictionHead = 0;
                    predictionListSelected();
                }

                KeyNavigation.down: predictionRepeater.itemAt(index + predictionGrid.columns)
                KeyNavigation.up: predictionRepeater.itemAt(index - predictionGrid.columns)
                KeyNavigation.left: predictionRepeater.itemAt(index - 1)
                KeyNavigation.right: predictionRepeater.itemAt(index + 1)
                Keys.onPressed: {
                    event.accepted = checkNavigationKey(index, event.key);
                    var rowIndex = Math.floor(index / middle.columns);
                    var colIndex = index % middle.columns;

                    if (event.key === Qt.Key_Up && rowIndex === 0) {
                        meetTopBoundary(colIndex);
                        event.accepted = true;
                    } else if (event.key === Qt.Key_Down) {
                        if (rowIndex === middle.rows - 1) {
                            meetBottomBoundary(colIndex);
                            event.accepted = true;
                        }
                    } else if (event.key === Qt.Key_Left && colIndex === 0) {
                        meetLeftBoundary(rowIndex);
                        event.accepted = true;
                    } else if (event.key === Qt.Key_Right) {
                        if (colIndex === middle.columns - 1 || predictionHead + index === Prediction.list.length - 1) {
                            meetRightBoundary(rowIndex);
                            event.accepted = true;
                        }
                    }
                }
            }
        }
    }

    Component.onCompleted: drawInitialLayout()

    function drawInitialLayout() {
        var key;

        for (var i = 0; i < Variables.HiraganaKeyNum; i++) {
            key = new Object;
            key.hiraganaChar = Variables.HiraganaChars[i];
            key.hiraganaRawcode = Variables.HiraganaRawcode[i];
            hiraganaModel.push(key);
        }
        for (i = 0; i < Variables.KatakanaKeyNum; i++) {
            key = new Object;
            key.katakanaChar = Variables.KatakanaChars[i];
            key.katakanaRawcode = Variables.KatakanaRawcode[i];
            katakanaModel.push(key);
        }
        for (i = 0; i < Variables.FullWidthEnglishKeyNum; i++) {
            key = new Object;
            key.fullWidthEnglishLowercaseChar = Variables.FullWidthEnglish_Lowercase_Chars[i];
            key.fullWidthEnglishLowercaseRawcode = Variables.FullWidthEnglish_Lowercase_Rawcode[i];
            fullWidthEnglishLowercaseModel.push(key);
        }
        for (i = 0; i < Variables.FullWidthEnglishKeyNum; i++) {
            key = new Object;
            key.fullWidthEnglishUppercaseChar = Variables.FullWidthEnglish_Uppercase_Chars[i];
            key.fullWidthEnglishUppercaseRawcode = Variables.FullWidthEnglish_Uppercase_Rawcode[i];
            fullWidthEnglishUppercaseModel.push(key);
        }
        for (i = 0; i < Variables.SymbolKeyNum; i++) {
            key = new Object;
            key.symbolChar = Variables.FullWidthSymbol_Chars[i];
            key.symbolRawcode = Variables.FullWidthSymbol_Rawcode[i];
            symbolModel.push(key);
        }

        letterRepeater.model = hiraganaModel;
        letterRepeater.itemAt(Variables.HiraganaKatakanaSpaceButtonIndex).image = "qrc:///images/spacebar.png";
        letterRepeater.itemAt(Variables.HiraganaKatakanaSpaceButtonIndex).text = " ";

        this.defaultFocus = Math.floor(middle.rows / 2) * middle.columns + Math.floor(middle.columns / 2) - 1;
    }

    function clickInputCharacterChangeButton() {
        switch (mode) {
        case "Hiragana":
            letterRepeater.model = hiraganaModel;
            letterRepeater.itemAt(Variables.HiraganaKatakanaSpaceButtonIndex).image = "qrc:///images/spacebar.png";
            letterRepeater.itemAt(Variables.HiraganaKatakanaSpaceButtonIndex).text = " ";
            break;
        case "Katakana":
            letterRepeater.model = katakanaModel;
            letterRepeater.itemAt(Variables.HiraganaKatakanaSpaceButtonIndex).image = "qrc:///images/spacebar.png";
            letterRepeater.itemAt(Variables.HiraganaKatakanaSpaceButtonIndex).text = " ";
            break;
        case "FullWidth-English":
            letterRepeater.model = fullWidthEnglishLowercaseModel;
            break;
        case "FullWidth-English-Shift":
        case "FullWidth-English-Shift-Lock":
            letterRepeater.model = fullWidthEnglishUppercaseModel;
            break;
        case "Symbol":
            letterRepeater.model = symbolModel;
            break;
        }
        modeChanged();
    }

    onCurrRepeaterChanged: {
        if (currRepeater === predictionRepeater)
            this.defaultFocus = 0;
        else
            this.defaultFocus = Math.floor(middle.rows / 2) * middle.columns + Math.floor(middle.columns / 2) - 1;
    }

    function setPredictionLayoutData(row, column, model) {
        predictionGrid.columns = column;
        predictionGrid.rows = row;
        predictionRepeater.model = model;
        predictionModeChanged();
    }

    function setKeyNavigation(row, column) {
        if (mode === "Katakana" && column === -1 && (row === middle.rows - 1 || row === -1)) {
            column = middle.columns - 3;
        } else if (column === -1) column = middle.columns - 1;
        if (row === -1) row = middle.rows - 1;
        var tagetButton = currRepeater.itemAt(row * middle.columns + column);
        if (tagetButton && tagetButton.visible){
            currRepeater.itemAt(row * middle.columns + column).focus = true;
            return true;
        }
        return false;
    }

    function setKeyNavigationToConvert() {
        convertButton.focus = true;
    }
}
