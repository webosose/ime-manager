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
import "../keyboard-common/commonvariables.js" as CommonVariables

Item {
    id: middle
    objectName: "middleLayout"
    width: parent.width
    height: parent.height
    property string mode: "Normal"
    property Grid currGrid: letterGrid
    property Repeater currRepeater: letterRepeater
    property var letterModel: []
    property var symbolModel: []
    property int symbolColumns: symbolGrid.columns
    property bool predictionMode: false
    property int predictionIndex: 0
    property int defaultFocus
    property bool changeColumn: false

    signal ttsService(string text)
    signal sendKey(string rawcode, bool shift)
    signal sendKeysym(string keysym)
    signal sendText(string text)
    signal pressNextPrediction()
    signal meetLeftBoundary(int row)
    signal meetRightBoundary(int row)
    signal meetTopBoundary(int column)
    signal meetBottomBoundary(int column)
    signal modelChanged()

    function setKeyNavigation(row, column, direction) {
        if (row < 0 || row >= currGrid.rows)
            row = currGrid.rows - 1;

        if (column === "defaultIndex")
            column = Math.floor(currGrid.columns / 2);
        else if (column < 0 || column >= currGrid.columns)
            column = currGrid.columns - 1;

        var bHit = false;
        var i = row;
        var j = column;
        var item;

        switch (direction) {
        case "Right":
            for (j = column; j < currGrid.columns; ++j) {
                for (i = row; i >= 0 ; --i) {
                    item = getEnabledItemAt(i, j);
                    if (item) {
                        bHit = true;
                        break;
                    }
                }
                if (!bHit) {
                    for (i = row + 1; i < currGrid.rows; ++i) {
                        item = getEnabledItemAt(i, j);
                        if (item) {
                            bHit = true;
                            break;
                        }
                    }
                }
                if (bHit)
                    break;
            }
            if (bHit)
                item.focus = true;
            else
                meetRightBoundary(row);
            break;
        case "Left":
            if ((i === currGrid.rows - 1) && predictionMode && nextButton.state !== "Disable") {
                nextButton.focus = true;
                break;
            }
            for (j = column; j >=0; --j) {
                for (i = row; i >= 0 ; --i) {
                    item = getEnabledItemAt(i, j);
                    if (item) {
                        bHit = true;
                        break;
                    }
                }
                if (!bHit) {
                    for (i = row + 1; i < currGrid.rows; ++i) {
                        item = getEnabledItemAt(i, j);
                        if (item) {
                            bHit = true;
                            break;
                        }
                    }
                }
                if (bHit)
                    break;
            }
            if (bHit)
                item.focus = true;
            else
                meetLeftBoundary(row);
            break;
        case "Up":
            if ((j === currGrid.columns - 1) && predictionMode && nextButton.state !== "Disable") {
                nextButton.focus = true;
                break;
            }
            for (i = row; i >= 0; --i) {
                item = getEnabledItemAt(i, j);
                if (item)
                    break;
            }
            if (i >= 0)
                item.focus = true;

            for (i = row; i >= 0; --i) {
                for (j = column; j >=0; --j) {
                    item = getEnabledItemAt(i, j);
                    if (item) {
                        bHit = true;
                        break;
                    }
                }
                if (!bHit) {
                    for (j = column + 1; j < currGrid.columns; ++j) {
                        item = getEnabledItemAt(i, j);
                        if (item) {
                            bHit = true;
                            break;
                        }
                    }
                }
                if (bHit)
                    break;;
            }
            if (bHit)
                item.focus = true;
            // if this emit meetTopBoundary(), VKB will disappear.
            break;
        }
    }

    function processNavKey(index, key) {
        var accepted = false;
        var rowIndex = Math.floor(index / currGrid.columns);
        var colIndex = index % currGrid.columns;
        var i;

        switch (key) {
        case Qt.Key_Up:
            for (i = rowIndex - 1; i >= 0; --i) {
                if (getEnabledItemAt(i, colIndex))
                    break;
            }
            if (i < 0) {
                meetTopBoundary(colIndex);
                accepted = true;
            }
            break;
        case Qt.Key_Down:
            for (i = rowIndex + 1; i < currGrid.rows; ++i) {
                if (getEnabledItemAt(i, colIndex))
                    break;
            }
            if (i === currGrid.rows) {
                if (!predictionMode || nextButton.state === "Disable") meetBottomBoundary(colIndex);
                accepted = true;
            }
            break;
        case Qt.Key_Left:
            for (i = colIndex - 1; i >= 0; --i) {
                if (getEnabledItemAt(rowIndex, i))
                    break;
            }
            if (i < 0) {
                meetLeftBoundary(rowIndex);
                accepted = true;
            }
            break;
        case Qt.Key_Right:
            for (i = colIndex + 1; i < currGrid.columns; ++i) {
                if (getEnabledItemAt(rowIndex, i))
                    break;
            }
            if (i === currGrid.columns) {
                if (!predictionMode || nextButton.state === "Disable") meetRightBoundary(rowIndex);
                accepted = true;
            }
            break;
        }

        return accepted;
    }

    function getIndex(rowIndex, colIndex) {
        return (rowIndex * currGrid.columns + colIndex);
    }

    function getEnabledItemAt(rowIndex, colIndex) {
        var item = currRepeater.itemAt(getIndex(rowIndex, colIndex));
        return (item && item.enabled) ? item : null;
    }

    function getMiddleItem() {
        if (!currRepeater.model)
            return null;

        var row = currGrid.rows / 2;
        if(langCode === "nl") row = 1;

        var i = Math.floor(row) * currGrid.columns + Math.floor(currGrid.columns / 2) - 1;
        //TODO: Check the visible and state
        return currRepeater.itemAt(i);
    }

    function getTailItem() {
        if (!currRepeater.model)
            return null;

        return currRepeater.itemAt(currRepeater.count - 1);
    }

    onModeChanged: {
        if (mode === "Symbol") {
            currGrid     = symbolGrid;
            currRepeater = symRepeater;
        } else {
            currGrid     = letterGrid;
            currRepeater = letterRepeater;
        }
    }

    onPredictionModeChanged: {
        if (predictionMode) {
            currGrid = predictionGrid;
            currRepeater = predictionRepeater;
        } else {
            currRepeater.model = 0;
            modeChanged();
        }
    }

    onPredictionIndexChanged: {
        if (!predictionMode) {
            nextButton.state = "Disable";
        } else if (Prediction.list.length <= predictionIndex) {
            nextButton.focus = false;
            nextButton.state = "Disable";
        } else if (predictionIndex > 0 && nextButton.state === "Disable"){
            nextButton.state = "Normal";
        }
    }

    /* key buttons */
    Grid {
        id: letterGrid
        objectName: "letterGrid"
        x: 0
        y: (!predictionMode && mode !== "Symbol") ? 0 : 1000
        rows: 4
        spacing: style.middle.cellSpace

        property real cellWidth: 0
        property int cellHeight: style.middle.cellHeight

        Repeater {
            id: letterRepeater
            objectName: "letterRepeater"
            model: 60
            LetterButton {
                mode: middle.mode

                width: letterGrid.cellWidth
                height: letterGrid.cellHeight

                keyData: letterModel[index]
                visible: keyData ? true : false

                onSendKey: middle.sendKey(rawcode, shift)
                onSendText: middle.sendText(text)
                onSendKeysym: middle.sendKeysym(keysym)
                onTtsService: {
                    if (inputSource == 0 && changeColumn) changeColumn = false
                    else middle.ttsService(text)
                }

                KeyNavigation.down:  letterRepeater.itemAt(index + letterGrid.columns)
                KeyNavigation.up:    letterRepeater.itemAt(index - letterGrid.columns)
                KeyNavigation.left:  letterRepeater.itemAt(index - 1)
                KeyNavigation.right: letterRepeater.itemAt(index + 1)
                Keys.onPressed: event.accepted = processNavKey(index, event.key)
            }
            onItemRemoved: item.removed = true
        }
    }

    /* symbol buttons */
    Grid {
        id: symbolGrid
        objectName: "symbolGrid"
        x: 0; y: (!predictionMode && mode === "Symbol") ? 0 : 1000
        rows: 4; spacing: style.middle.cellSpace

        property real cellWidth: 0
        property int cellHeight: style.middle.cellHeight

        Repeater {
            id: symRepeater
            objectName: "symRepeater"
            model: 48
            SymbolButton {
                width: symbolGrid.cellWidth
                height: symbolGrid.cellHeight
                text: symbolModel[index] || ""
                buttonStyle: style.symbolButton
                visible: text !== ""

                onSendText: middle.sendText(text)
                onTtsService: middle.ttsService(text)

                KeyNavigation.down:  symRepeater.itemAt(index + symbolGrid.columns)
                KeyNavigation.up:    symRepeater.itemAt(index - symbolGrid.columns)
                KeyNavigation.left:  symRepeater.itemAt(index - 1)
                KeyNavigation.right: symRepeater.itemAt(index + 1)
                Keys.onPressed: event.accepted = processNavKey(index, event.key)
            }
            onItemRemoved: item.removed = true
        }
    }

    /* predicted word list */
    Grid {
        id: predictionGrid
        objectName: "predictionGrid"
        x: 0; y: predictionMode ? 0 : 1000
        spacing: style.middle.cellSpace

        Repeater {
            id: predictionRepeater
            objectName: "predictionRepeater"
            onModelChanged: middle.modelChanged()
            ButtonBase {
                objectName: "predictionGridButton"
                property bool bExecuted: false

                width: (style.middle.width + predictionGrid.spacing) / predictionGrid.columns - predictionGrid.spacing
                height: style.middle.cellHeight
                text: modelData
                state: (modelData === undefined || modelData === "") ? "Disable" : ""
                onReleased: {
                    if (bExecuted) {
                        var i = Math.floor(letterGrid.rows / 2) * letterGrid.columns + Math.floor(letterGrid.columns / 2) - 1;
                        var item = letterRepeater.itemAt(i);
                        if (item && item.enabled)
                            item.focus = true;
                        bExecuted = false;
                    }
                    Prediction.onSelected(text);
                    predictionMode = false;
                    predictionIndex = 0;
                }
                onExecuted: {
                    bExecuted = true;
                }
                onTtsService: middle.ttsService(text)

                KeyNavigation.down:  predictionRepeater.itemAt(index + predictionGrid.columns)
                KeyNavigation.up:    predictionRepeater.itemAt(index - predictionGrid.columns)
                KeyNavigation.left:  predictionRepeater.itemAt(index - 1)
                KeyNavigation.right: predictionRepeater.itemAt(index + 1)
                Keys.onPressed: {
                    event.accepted = processNavKey(index, event.key);
                    var rowIndex = Math.floor(index / predictionGrid.columns);
                    var colIndex = index % predictionGrid.columns;

                    if (event.key === Qt.Key_Up && rowIndex === 0) {
                        meetTopBoundary(colIndex);
                        event.accepted = true;
                    } else if (event.key === Qt.Key_Down) {
                        if (rowIndex === predictionGrid.rows - 1) {
                            meetBottomBoundary(colIndex);
                            event.accepted = true;
                        } else if (rowIndex === predictionGrid.rows - 2 && colIndex === predictionGrid.columns - 1) {
                            nextButton.state !== "Disable" ? (nextButton.focus = true) : meetBottomBoundary(colIndex);
                            event.accepted = true;
                        }
                    } else if (event.key === Qt.Key_Left && colIndex === 0) {
                        meetLeftBoundary(rowIndex);
                        event.accepted = true;
                    } else if (event.key === Qt.Key_Right) {
                        if (colIndex === predictionGrid.columns - 1) {
                            meetRightBoundary(rowIndex);
                            event.accepted = true;
                        } else if (rowIndex === predictionGrid.rows - 1 && colIndex === predictionGrid.columns - 2) {
                            nextButton.state !== "Disable" ? (nextButton.focus = true) : meetRightBoundary(rowIndex);
                            event.accepted = true;
                        }
                    }
                }
            }
            onItemRemoved: item.removed = true
        }
        ButtonBase {
            id: nextButton
            objectName: "nextButton"
            property string ttsStringNextlist: qsTr("Additional Recommendations") + (PluginProxy.emptyString !== undefined ? PluginProxy.emptyString : "")
            width: (style.middle.width + predictionGrid.spacing) / predictionGrid.columns - predictionGrid.spacing
            height: style.middle.cellHeight
            text: "..."
            enterPriority: releaseBeforeExecute
            onReleased: {
                pressNextPrediction();
                if (predictionIndex >= Prediction.list.length) {
                    var item = getTailItem();
                    if (item && item.enabled)
                        CommonVariables.savedFocusItem = item;
                }
            }
            onExecuted: {
                // this is called after onReleased(). so predictionIndex is already increased to next head.
                if (predictionIndex >= Prediction.list.length) {
                    var item = getTailItem();
                    if (item && item.enabled)
                        item.focus = true;
                }
            }

            onTtsService: middle.ttsService(ttsStringNextlist)

            KeyNavigation.up: {
                if (predictionRepeater.model)
                    return predictionRepeater.itemAt(predictionRepeater.model.length - predictionGrid.columns);
                else
                    return null;
            }
            KeyNavigation.left: {
                if (predictionRepeater.model)
                    return predictionRepeater.itemAt(predictionRepeater.model.length - 1);
                else
                    return null;
            }
            Keys.onPressed: {
                if (event.key === Qt.Key_Execute && state !== "Disable") {
                    state = "Select";
                } else if (event.key === Qt.Key_Down) {
                    meetBottomBoundary(predictionGrid.columns - 1);
                    event.accepted = true;
                } else if (event.key === Qt.Key_Right) {
                    meetRightBoundary(predictionGrid.rows - 1);
                    event.accepted = true;
                }
            }
            Connections {
                target: PluginProxy
                onKeyReleased : {
                    if (isReleased && predictionMode && (nextButton.state === "Select"))
                        nextButton.state = "Focus";
                }
            }
        }
    }

    function setLayoutData(row, column, model) {
        if (letterGrid.columns !== column) {
            changeColumn = true;
            letterGrid.columns = column;
            letterGrid.cellWidth = (style.middle.width + letterGrid.spacing) / letterGrid.columns - letterGrid.spacing;
        }
        letterModel = model;
        modelChanged();
    }

    function setSymbolLayoutData(row, column, model) {
        symbolGrid.columns = column;
        symbolGrid.cellWidth = (style.middle.width + symbolGrid.spacing) / symbolGrid.columns - symbolGrid.spacing;
        symbolModel = model;
    }

    function setPredictionLayoutData(row, column, model) {
        predictionGrid.columns = column;
        predictionGrid.rows = row;
        predictionRepeater.model = model;
    }
}
