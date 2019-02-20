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
import "../keyboard-common/commonvariables.js" as CommonVariables

Rectangle {
    id: middle
    objectName: "middleLayout"
    width: parent.width
    height: parent.height
    color: style.bgColor
    property string mode: "Normal"
    property Grid currGrid: middleGrid
    property Repeater currRepeater: letterRepeater
    signal sendKey(string rawcode, bool shift)
    signal sendText(string text)
    signal meetLeftBoundary(int row)
    signal meetRightBoundary(int row)
    signal meetTopBoundary(int column)
    signal meetBottomBoundary(int column)
    property int defaultFocus

    function checkNavigationKey(index, key) {
        var accepted = false;
        var rowIndex = Math.floor(index / currGrid.columns);
        var colIndex = index % currGrid.columns;

        if (key === Qt.Key_Up && rowIndex === 0) {
            meetTopBoundary(colIndex);
            accepted = true;
        } else if (key === Qt.Key_Down && rowIndex === currGrid.rows - 1) {
            meetBottomBoundary(colIndex);
            accepted = true;
        } else if (key === Qt.Key_Left && colIndex === 0) {
            meetLeftBoundary(rowIndex);
            accepted = true;
        } else if (key === Qt.Key_Right && validateRightBoundary(index,colIndex)) {
            meetRightBoundary(rowIndex);
            accepted = true;
        }
        return accepted;
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
                meetBottomBoundary(colIndex);
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
                meetRightBoundary(rowIndex);
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

    function validateRightBoundary(index,colIndex) {
        var nextItem = currRepeater.itemAt(index+1);
        if (nextItem && nextItem.state === "Disable") {
            if (index === 9 || index === 21 || index === 32 || index === 45)
                return true;
        }
        return colIndex === currGrid.columns - 1;
    }

    /* key buttons */
    Grid {
        id: middleGrid
        objectName: "middleGrid"
        anchors.fill: parent
        spacing: style.middle.cellSpace
        rows: 4

        Repeater {
            id: letterRepeater
            objectName: "letterRepeater"
            LetterButton {
                mode:middle.mode
                width: (style.middle.width + middleGrid.spacing) / middleGrid.columns - middleGrid.spacing
                height: style.middle.cellHeight

                mainChar: modelData.mainChar ? modelData.mainChar : ""
                shiftedChar: modelData.shiftedChar ? modelData.shiftedChar : ""
                symbolChar: modelData.symbolChar ? modelData.symbolChar : ""
                rawcode: modelData.rawcode ? modelData.rawcode : "-1"
                shiftRawcode: modelData.shiftRawcode ? modelData.shiftRawcode : "-1"
                onSendKey: middle.sendKey(rawcode, shift)
                onSendText: middle.sendText(text)

                KeyNavigation.down:  letterRepeater.itemAt(index + middleGrid.columns)
                KeyNavigation.up:    letterRepeater.itemAt(index - middleGrid.columns)
                KeyNavigation.left:  letterRepeater.itemAt(index - 1)
                KeyNavigation.right: letterRepeater.itemAt(index + 1)
                Keys.onPressed: event.accepted = processNavKey(index, event.key)
            }
            onItemRemoved: item.removed = true
        }
    }

    function setLayoutData(row, column, model) {
        middleGrid.columns = column;
        letterRepeater.model = model;
        defaultFocus = ( 2 * column ) + Math.round( column/2 ) - 1;
    }

    function setKeyNavigation(row, column) {
        if (column === -1) column = currGrid.columns - 1;
        if (row === -1) row = currGrid.rows - 1;
        while(currRepeater.itemAt(row * currGrid.columns + column).state === "Disable") column --;
        currRepeater.itemAt(row * currGrid.columns + column).focus = true;
    }

    function getMiddleItem() {
        if (!currRepeater.model)
            return null;

        var i = Math.floor(currGrid.rows / 2) * currGrid.columns + Math.floor(currGrid.columns / 2) - 1;
        //TODO: Check the visible and state
        return currRepeater.itemAt(i);
    }
}
