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
import "commonvariables.js" as CommonVariables
import com.meego.maliit 1.0

Item {
    id: root

    property alias enterText: enterButton.text
    property int idxLastFocusOnCursorBtn: CommonVariables.left
    property var lastFocusOnCursorBtn: idxLastFocusOnCursorBtn == CommonVariables.left ? moveCursorLeftButton : moveCursorRightButton
    signal ttsService(string text)
    signal clickClearAllButton()
    signal sendKey(int keycode, bool shift)
    signal meetLeftBoundary(int row)
    signal meetRightBoundary(int row)
    signal meetTopBoundary(int column)
    signal meetBottomBoundary(int column)

    Column {
        spacing: style.right.cellSpace
        /* Delete Button */
        ButtonBase {
            id: deleteButton
            objectName: "deleteButton"
            image: {
                if (style.keyboardDefaultWidth === 1920) {
                    if (state == "Select") {
                        return "qrc:///images/clear-dark.png"
                    } else {
                        return "qrc:///images/clear.png"
                    }
                } else {
                    if (state == "Select") {
                        return "qrc:///images-hd/clear-dark.png"
                    } else {
                        return "qrc:///images-hd/clear.png"
                    }
                }
            }
            width: root.width
            height: style.right.cellHeight
            onTtsService: root.ttsService(ttsStringBackspace)
            onReleased: sendKey(14, false)

            property int row: 0
            property string ttsStringBackspace: qsTr("Back Space") + (PluginProxy.emptyString !== undefined ? PluginProxy.emptyString : "")
            KeyNavigation.down: enterButton
        }

        /* Enter Button */
        ButtonBase {
            id: enterButton
            objectName: "enterButton"
            text: {
                switch (enterKeyType) {
                case Maliit.SearchEnterKeyType:
                    return qsTr("Search") + (PluginProxy.emptyString !== undefined ? PluginProxy.emptyString : "");
                default:
                    return qsTr("Enter") + (PluginProxy.emptyString !== undefined ? PluginProxy.emptyString : "");
                }
            }
            fontSizeMode: Text.Fit
            onTtsService: root.ttsService(text)
            onReleased: sendKey(28, false)

            width: root.width
            height: style.right.cellHeight * 2 + style.right.cellSpace * 1
            allowRepeat: false

            property int row: 1
            readonly property int initRow: 1
            property string ttsStringSearch: qsTr("Search") + (PluginProxy.emptyString !== undefined ? PluginProxy.emptyString : "") //i18n This string is a naun for a button on VKB. It means "searching an word user writes using the keyboard".
            KeyNavigation.up: deleteButton
            KeyNavigation.down: lastFocusOnCursorBtn;
        }

        Row {
            width : childrenRect.width
            height: childrenRect.height
            spacing: style.right.cellSpace

            ButtonBase {
                id: moveCursorLeftButton
                objectName: "moveCursorLeftButton"
                property int row: 3
                text: "\ufe64"
                onTtsService: root.ttsService(qsTr("Left"))
                height: style.right.cellHeight
                width: root.width/2 - style.right.cellSpace/2
                fontSizeMode: Text.Fit
                onReleased: {
                    console.warn("@@@ click cursor left");
                    moveCursorPosition(CommonVariables.left);
                }
                onFocusChanged : {
                    if (focus) {
                        root.idxLastFocusOnCursorBtn = CommonVariables.left
                    }
                }
                KeyNavigation.right: moveCursorRightButton
                KeyNavigation.down: clearAllButton
            }

            ButtonBase {
                id: moveCursorRightButton
                objectName: "moveCursorRightButton"
                property int row: 3
                text: "\ufe65"
                onTtsService: root.ttsService(qsTr("Right"))
                height: style.right.cellHeight
                width: root.width/2 - style.right.cellSpace/2
                fontSizeMode: Text.Fit
                onReleased: {
                    console.warn("@@@ click cursor right");
                    moveCursorPosition(CommonVariables.right);
                }
                onFocusChanged : {
                    if (focus) {
                        root.idxLastFocusOnCursorBtn = CommonVariables.right
                    }
                }
                KeyNavigation.down: clearAllButton
            }
        }

        /* Clear-All button */
        ButtonBase {
            id: clearAllButton
            objectName: "clearAllButton"
            text: qsTr("Clear all") + (PluginProxy.emptyString !== undefined ? PluginProxy.emptyString : "")
            fontSizeMode: Text.Fit
            onTtsService: root.ttsService(text)
            onReleased: clickClearAllButton()

            width: root.width
            height: style.right.cellHeight

            property int row: 4
            KeyNavigation.up: lastFocusOnCursorBtn
        }
    }

    Keys.onPressed: {
        if (event.key === Qt.Key_Up) {
            meetTopBoundary(0);
            event.accepted = true;
        } else if (event.key === Qt.Key_Down) {
            meetBottomBoundary(0);
            event.accepted = true;
        } else if (event.key === Qt.Key_Left) {
            meetLeftBoundary(CommonVariables.savedFocusItem.row);
            enterButton.row = enterButton.initRow;
            event.accepted = true;
        } else if (event.key === Qt.Key_Right) {
            meetRightBoundary(CommonVariables.savedFocusItem.row);
            event.accepted = true;
        }
    }

    Connections {
        target: PluginProxy
        onKeyReleased : {
            if (isReleased && (deleteButton.state === "Select"))
                deleteButton.state = "Focus";
            else if (isReleased && (enterButton.state === "Select"))
                enterButton.state = "Focus";
            else if (isReleased && (clearAllButton.state === "Select"))
                clearAllButton.state = "Focus";
            else if (isReleased && (moveCursorLeftButton.state === "Select"))
                moveCursorLeftButton.state = "Focus";
            else if (isReleased && (moveCursorRightButton.state === "Select"))
                moveCursorRightButton.state = "Focus";
        }
    }

    function setKeyNavigation(row) {
        if (row === 0) {
            deleteButton.focus = true;
        } else if (row === 1) {
            enterButton.focus = true;
            enterButton.row = row;
        } else if (row === 2) {
            enterButton.focus = true;
            enterButton.row = row;
        } else if (row === 3) {
            moveCursorLeftButton.focus = true;
        } else if (row === 4 || row === -1) {
            clearAllButton.focus = true;
        }
    }

    function setFocusTo(name) {
        if (name === "Enter")
            enterButton.focus = true;
    }
}
