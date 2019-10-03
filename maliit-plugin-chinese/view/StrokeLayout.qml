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

Rectangle {
    id: stroke
    objectName: "stroke"
    color: style.bgColor
    property string mode: "Normal-Shift"
    signal sendKey(string rawcode, bool shift, int eventType)
    signal sendText(string text)
    signal meetLeftBoundary(int row)
    signal meetRightBoundary(int row)
    signal meetTopBoundary(int column)
    signal meetBottomBoundary(int column)

    /* Number Grid */
    Grid {
        id: numberGrid
        objectName: "numberGrid"
        anchors.top: parent.top
        anchors.left: parent.left
        spacing: style.middle.cellSpace
        rows : 1

        Repeater {
            id: numberRowRepeater
            objectName: "numberRowRepeater"
            LetterButton {
                mode:stroke.mode
                width: (style.middle.width + numberGrid.spacing) / numberGrid.columns - numberGrid.spacing
                height: style.middle.cellHeight
                shiftedChar: modelData.shiftedChar ? modelData.shiftedChar : ""
                shiftRawcode: modelData.shiftRawcode ? modelData.shiftRawcode : "-1"
                onSendKey: stroke.sendKey(rawcode, shift, eventType)
                onSendText: stroke.sendText(text)
                KeyNavigation.left: numberRowRepeater.itemAt(index - 1)
                KeyNavigation.right: numberRowRepeater.itemAt(index + 1)
                Keys.onPressed: {
                    if (event.key === Qt.Key_Up) {
                        meetTopBoundary(0);
                        event.accepted = true;
                    } else if (event.key === Qt.Key_Left && index == 0) {
                        meetLeftBoundary(0);
                        event.accepted = true;
                    } else if (event.key === Qt.Key_Right && index == numberGrid.columns-1) {
                        meetRightBoundary(0);
                        event.accepted = true;
                    }
                }
            }
            onItemRemoved: item.removed = true
        }
    }

    /* Stroke Grid */
    Grid {
        id: strokeGrid
        objectName: "strokeGrid"
        y: numberGrid.height + style.middle.cellSpace
        anchors.left: parent.left
        spacing: style.middle.cellSpace
        rows : 1

        Repeater {
            id: strokeRowRepeater
            objectName: "strokeRowRepeater"
            LetterButton {
                mode:stroke.mode
                width: (style.middle.width + strokeGrid.spacing) / strokeGrid.columns - strokeGrid.spacing
                height: (style.middle.cellHeight * 2) + strokeGrid.spacing
                shiftedChar: modelData.shiftedChar ? modelData.shiftedChar : ""
                shiftRawcode: modelData.shiftRawcode ? modelData.shiftRawcode : "-1"
                onSendKey: stroke.sendKey(rawcode, shift, eventType)
                onSendText: stroke.sendText(text)
                KeyNavigation.up:    numberRowRepeater.itemAt(index * 2)
                KeyNavigation.left:  strokeRowRepeater.itemAt(index - 1)
                KeyNavigation.right: strokeRowRepeater.itemAt(index + 1)
                Keys.onPressed: {
                    if (event.key === Qt.Key_Left && index == 0) {
                        meetLeftBoundary(1);
                        event.accepted = true;
                    } else if (event.key === Qt.Key_Right && index == strokeGrid.columns-1) {
                        meetRightBoundary(1);
                        event.accepted = true;
                    }
                }
            }
            onItemAdded: {
                numberRowRepeater.itemAt(index*2).KeyNavigation.down = item;
                numberRowRepeater.itemAt((index*2)+1).KeyNavigation.down = item;
            }
            onItemRemoved: item.removed = true
        }
    }

    /* Extra Character Grid */
    Grid {
        id: xcharGrid
        objectName: "xcharGrid"
        y: strokeGrid.height + numberGrid.height + (style.middle.cellSpace * 2)
        anchors.left: parent.left
        spacing: style.middle.cellSpace
        rows : 1

        Repeater {
            id:xcharRowRepeater
            objectName: "xcharRowRepeater"
            LetterButton {
                mode:stroke.mode
                width: (style.middle.width + xcharGrid.spacing) / xcharGrid.columns - xcharGrid.spacing
                height: style.middle.cellHeight
                shiftedChar: modelData.shiftedChar ? modelData.shiftedChar : ""
                shiftRawcode: modelData.shiftRawcode ? modelData.shiftRawcode : "-1"
                onSendKey: stroke.sendKey(rawcode, shift, eventType)
                onSendText: stroke.sendText(text)
                KeyNavigation.left:  xcharRowRepeater.itemAt(index - 1)
                KeyNavigation.right: xcharRowRepeater.itemAt(index + 1)
                Keys.onPressed: {
                    if (event.key === Qt.Key_Down) {
                        meetBottomBoundary(0);
                        event.accepted = true;
                    } else if (event.key === Qt.Key_Left && index == 0) {
                        meetLeftBoundary(2);
                        event.accepted = true;
                    } else if (event.key === Qt.Key_Right && index == xcharGrid.columns-1) {
                        meetRightBoundary(2);
                        event.accepted = true;
                    }
                }
            }
            onItemAdded: {
                if (index % 2 === 0)
                    strokeRowRepeater.itemAt(Math.floor(index / 2)).KeyNavigation.down = item;
                item.KeyNavigation.up = strokeRowRepeater.itemAt(Math.floor(index / 2));
            }
            onItemRemoved: item.removed = true
        }
    }

    function setNumGridData(column, model) {
        numberGrid.columns = column;
        numberRowRepeater.model = model;
    }

    function setStrokeGridData(column, model) {
        strokeGrid.columns = column;
        strokeRowRepeater.model = model;
    }

    function setXcharGridData(column, model) {
        xcharGrid.columns = column;
        xcharRowRepeater.model = model;
    }

    function setKeyNavigation(row, column) {
        switch(row) {
        case 0:
            if (column === -1) column = numberGrid.columns - 1;
            numberRowRepeater.itemAt(column).focus = true;
            break;
        case 1:
            if (column === -1) column = strokeGrid.columns - 1;
            strokeRowRepeater.itemAt(column).focus = true;
            break;
        case 2:
        case 3:
            if (column === -1) column = xcharGrid.columns - 1;
            xcharRowRepeater.itemAt(column).focus = true;
            break;
        }
    }

    function getMiddleItem() {
        if (!strokeRowRepeater.model)
            return null;
        return strokeRowRepeater.itemAt(2);
    }
}
