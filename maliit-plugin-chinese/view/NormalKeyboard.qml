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
import "../keyboard-common" as Common
import "languages.js" as Languages
import "../keyboard-common/commonvariables.js" as CommonVariables

Rectangle {
    id: main
    objectName: "normalKeyboard"
    color: style.bgColor

    property alias mode: leftFunctionArea.state
    property alias currLanguage: leftFunctionArea.currLanguage
    property int enterKeyType: 0
    property QtObject chineseStyle: []

    signal keyPressed(string rawcode, bool shift)
    signal switchContext()
    signal shiftPressed(string state)
    signal textKeyPressed(string text)
    signal symbolPressed(string state)
    signal clearAllPressed()

    onEnabledChanged: {
        if (enabled) {
           CommonVariables.savedFocusItem = getMiddleItem();
        }
    }
    LeftFunctionArea {
        id: leftFunctionArea
        objectName: "leftFunctionArea"
        anchors.top: parent.top
        anchors.topMargin: style.left.topMargin
        anchors.left: parent.left
        anchors.leftMargin: style.left.leftMargin
        width: style.left.width
        height: style.left.height
        enabled: true

        Component.onCompleted: {
            languageButtonPressed.connect(switchContext);
            shiftClicked.connect(shiftPressed);
            symbolClicked.connect(symbolPressed);
        }

        onMeetRightBoundary: {
            if (strokeLayoutArea.enabled) {
                if (row == 2) row = 1
                strokeLayoutArea.setKeyNavigation(row,0)
            }
            else
                middleLayoutArea.setKeyNavigation(row, 0)
        }
        onMeetBottomBoundary: bottomArea.setKeyNavigation()
        onMeetLeftBoundary: rightFunctionArea.setKeyNavigation(row, "Left")
        onMeetTopBoundary: root.meetTopBoundary()
    }

    MiddleLayout {
        id: middleLayoutArea
        objectName: "middleLayoutArea"
        mode: main.mode
        anchors.top: parent.top
        anchors.topMargin: style.middle.topMargin
        anchors.left: leftFunctionArea.right
        anchors.leftMargin: style.middle.leftMargin
        width: style.middle.width + style.middle.cellSpace
        height: style.middle.height
        enabled: true
        z:1
        onSendKey: main.keyPressed(rawcode, shift)
        onSendText: main.textKeyPressed(text)
        onMeetLeftBoundary: leftFunctionArea.setKeyNavigation(row)
        onMeetRightBoundary: rightFunctionArea.setKeyNavigation(row)
        onMeetBottomBoundary: bottomArea.setKeyNavigation()
        onMeetTopBoundary: root.meetTopBoundary()
    }

    StrokeLayout {
        id: strokeLayoutArea
        objectName: "strokeLayoutArea"
        mode: main.mode
        anchors.top: parent.top
        anchors.topMargin: style.middle.topMargin
        anchors.left: leftFunctionArea.right
        anchors.leftMargin: style.middle.leftMargin
        width: style.middle.width + style.middle.cellSpace
        height: style.middle.height
        enabled: false
        onSendKey: main.keyPressed(rawcode, shift)
        onSendText: main.textKeyPressed(text)
        onMeetLeftBoundary: leftFunctionArea.setKeyNavigation(row)
        onMeetRightBoundary: {
            if(row === 2) row = 3;
            rightFunctionArea.setKeyNavigation(row)
        }
        onMeetBottomBoundary: bottomArea.setKeyNavigation()
        onMeetTopBoundary: root.meetTopBoundary()
    }

    Common.RightFunctionArea {
        id: rightFunctionArea
        objectName: "rightFunctionArea"
        anchors.right: parent.right
        anchors.rightMargin: style.right.rightMargin
        anchors.top: parent.top
        anchors.topMargin: style.right.topMargin
        width: style.right.width
        height: style.right.height

        Component.onCompleted: {
            clickClearAllButton.connect(clearAllPressed);
            sendKey.connect(keyPressed);
        }
        onMeetLeftBoundary: {
            if (row > 3) bottomArea.setKeyNavigation();
            else if(strokeLayoutArea.enabled)
                strokeLayoutArea.setKeyNavigation(row,-1)
            else
                middleLayoutArea.setKeyNavigation(row, -1)
        }
        onMeetRightBoundary: {
            if (row < 4) {
                leftFunctionArea.setKeyNavigation(row)
            } else {
                bottomArea.setKeyNavigation(-1);
            }
        }
        onMeetTopBoundary: root.meetTopBoundary()
        onMeetBottomBoundary: root.meetBottomBoundary()
    }

    BottomArea {
        id: bottomArea
        objectName: "bottomArea"
        anchors.top: leftFunctionArea.bottom
        anchors.topMargin: style.bottom.topMargin
        anchors.left: parent.left
        anchors.leftMargin: style.bottom.leftMargin
        anchors.right: rightFunctionArea.left
        anchors.rightMargin: style.bottom.rightMargin
        height: style.bottom.height
        chineseStyle: root.chineseStyle

        Component.onCompleted: {
            sendKey.connect(keyPressed);
        }
        onMeetLeftBoundary: rightFunctionArea.setKeyNavigation(-1)
        onMeetRightBoundary: rightFunctionArea.setKeyNavigation(-1)
        onMeetTopBoundary: {
            if (column === 0)
                leftFunctionArea.setKeyNavigation(2);
            else if(strokeLayoutArea.enabled)
                strokeLayoutArea.setKeyNavigation(2,4);
            else
                middleLayoutArea.setKeyNavigation(-1, 5);
        }
        onMeetBottomBoundary: root.meetBottomBoundary()
    }

    function setLanguage(language, data) {
        currLanguage = language;
        drawLayout(language, data);
        if (language === Languages.SIMPLIFIED_CHINESE)
            drawStrokeLayout(language,data);
        mode = "Normal";
        gc();
    }

    function drawLayout(language, data) {

        var length = data.length;
        var column = data.column;
        var row = data.row;

        // set layout to grid
        middleLayoutArea.setLayoutData(row, column, data.keys);
    }

    function drawStrokeLayout(language, data) {
        var length = data.length;
        var column = data.column;
        var row = data.row;
        var strokeColumn = 5;

        state = "Normal-Shift";

        var numModel = [];
        for (var i = 0; i < column; i++) {
            numModel[i] = data.keys[i];
        }
        strokeLayoutArea.setNumGridData(column,numModel);

        var strokeModel = [];
        var sCount = strokeColumn + column;
        for (var j = 0; i < sCount; i++,j++) {
            strokeModel[j] = data.keys[i];
        }
        strokeLayoutArea.setStrokeGridData(strokeColumn,strokeModel);

        var xCharModel = [];
        var unUsedKeys = 5;
        var xCount = column + strokeColumn + column + unUsedKeys;
        i += unUsedKeys;
        for (var k = 0; i < xCount; i++,k++) {
            xCharModel[k] = data.keys[i];
        }
        strokeLayoutArea.setXcharGridData(column,xCharModel);
    }

    Keys.onPressed: {
        if (event.key === Qt.Key_Up || event.key === Qt.Key_Down)
            Keyboard.onHideRequested(false);
    }

    function setDefaultFocus() {
        if( middleLayoutArea.defaultFocus !== undefined ){
            CommonVariables.savedFocusItem.focus = false;
            CommonVariables.savedFocusItem = getMiddleItem();
        }
    }

    function setFocusToEnter() {
        rightFunctionArea.setFocusTo("Enter");
    }

    function getMiddleItem() {
        return strokeLayoutArea.enabled ? strokeLayoutArea.getMiddleItem() : middleLayoutArea.getMiddleItem();
    }

    onModeChanged: {
        if (currLanguage === Languages.SIMPLIFIED_CHINESE && mode === "Normal-Shift") {
            strokeLayoutArea.enabled = true;
            middleLayoutArea.enabled = false;
            strokeLayoutArea.z = 1;
            middleLayoutArea.z = 0;
            CommonVariables.savedFocusItem = strokeLayoutArea.getMiddleItem()
        } else {
            middleLayoutArea.enabled = true;
            strokeLayoutArea.enabled = false;
            middleLayoutArea.z = 1;
            strokeLayoutArea.z = 0;
            CommonVariables.savedFocusItem = middleLayoutArea.getMiddleItem()
        }
    }
}
