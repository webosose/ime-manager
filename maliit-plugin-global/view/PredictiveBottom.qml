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

Item {
    id: root
    objectName: "predictiveBottom"
    property variant words
    property variant preColumn: "defaultIndex"
    property int maxLength: constantPrediction ? 6 : 5
    property bool constantPrediction: false
    property bool showMoreButton
    property bool showBackButton
    signal ttsService(string text)
    signal sendKey(int keycode, bool shift, int eventType)
    signal selectPredictionWord(string word)
    signal pressMore()
    signal pressBack()
    signal meetLeftBoundary()
    signal meetRightBoundary()
    signal meetTopBoundary(variant column)
    signal meetBottomBoundary()

    property bool focusMonitor : false
    property bool focusCheckedByWords : false

    onFocusMonitorChanged: {
        if (focusMonitor) focusCheckedByWords = Qt.binding(function(){
            return words == undefined || words.length <=0;
        })
    }

    onFocusCheckedByWordsChanged :{
        if (focusCheckedByWords) {
            spaceBar.focus = true;
            focusCheckedByWords = false;
            focusMonitor = false;
        }
    }

    Row {
        id: row
        objectName: "predictionRow"
        spacing: constantPrediction ? style.middle.cellSpace
                                    : (showBackButton ? style.middle.leftMargin : style.predictionBar.spacing)
        // back button at the prediction mode
        ButtonBase {
            id: backButton
            objectName: "backButton"
            text: qsTr("Back") + (PluginProxy.emptyString !== undefined ? PluginProxy.emptyString : "")
            width: showBackButton ? style.left.width : 0
            height: style.bottom.height
            visible: showBackButton
            onReleased: pressBack()
            onExecuted: spaceBar.focus = true
            onTtsService: root.ttsService(text)

            KeyNavigation.right: spaceBar

            Keys.onPressed: {
                if (event.key === Qt.Key_Down || event.key === Qt.Key_Left){
                    return;
                } else if (event.key === Qt.Key_Up) {
                    meetTopBoundary(-1);
                    event.accepted = true;
                } else if (event.key === Qt.Key_Right) {
                    root.preColumn = "defaultIndex";
                }
                state = "Normal"
            }
        }

        // prediction words
        Row {
            id: predictionBar
            objectName: "predictionBar"
            property int predictionIndex: -1
            spacing: constantPrediction ? style.middle.cellSpace : style.predictionBar.spacing

            Repeater {
                id: predictionRepeater
                objectName: "predictionRepeater"
                model: words
                ButtonBase {
                    buttonStyle: constantPrediction ? style.button : style.predictionBarButton
                    text: modelData
                    height: style.bottom.height
                    width: constantPrediction ? style.predictionBar.cellWidth : contentWidth
                    fontfamily: constantPrediction ? style._MuseoSans : ""
                    onExecuted: if (!constantPrediction) spaceBar.focus = true
                    onReleased: selectPredictionWord(text)
                    onFocusChanged: {
                        root.focusMonitor = focus;
                    }
                    onTtsService: {
                        var t;
                        if (constantPrediction) {
                            switch (text) {
                            case "http://":
                                t = qsTr("http colon slash slash") + (PluginProxy.emptyString !== undefined ? PluginProxy.emptyString : "")
                                root.ttsService(t)
                                break;
                            case "https://":
                                t = qsTr("https colon slash slash") + (PluginProxy.emptyString !== undefined ? PluginProxy.emptyString : "")
                                root.ttsService(t)
                                break;
                            case "www.":
                                t = qsTr("www dot") + (PluginProxy.emptyString !== undefined ? PluginProxy.emptyString : "")
                                root.ttsService(t)
                                break;
                            case ".org":
                                t = ". o r g"
                                root.ttsService(t)
                                break;
                            default:
                                root.ttsService(text)
                            }
                        } else root.ttsService(text)

                    }

                    KeyNavigation.right: predictionRepeater.itemAt(index + 1)
                    KeyNavigation.left: predictionRepeater.itemAt(index - 1)

                    Keys.onPressed: {
                        predictionBar.predictionIndex = index;
                        if (event.key === Qt.Key_Down) {
                            return;
                        } else if (event.key === Qt.Key_Left) {
                            root.preColumn = -1;
                            if (index === 0) {
                                return;
                            }
                        } else if (event.key === Qt.Key_Right && index === predictionRepeater.count - 1) {
                            moreButton.visible ? moreButton.focus = true : spaceBar.focus = true;
                            root.preColumn = "defaultIndex";
                            event.accepted = true;
                        } else if (event.key === Qt.Key_Up) {
                            meetTopBoundary(root.preColumn);
                            event.accepted = true;
                        }
                        if (!constantPrediction) state = "Normal";
                    }
                }
                onItemRemoved: item.removed = true
            }
            Connections {
                target: PluginProxy
                onKeyReleased : {
                    if (isReleased && constantPrediction && predictionBar.predictionIndex !== -1 && (predictionRepeater.itemAt(predictionBar.predictionIndex).state === "Select")) {
                        predictionRepeater.itemAt(predictionBar.predictionIndex).state = "Focus";
                        predictionBar.predictionIndex = -1;
                    }
                }
            }
        }

        // more button
        ButtonBase {
            id: moreButton
            objectName: "moreButton"
            property string ttsStringSeeMore: qsTr("See More") + (PluginProxy.emptyString !== undefined ? PluginProxy.emptyString : "")
            onFocusChanged: {
                root.focusMonitor = focus;
            }
            image: {
                if (style.keyboardDefaultWidth === 1920) {
                    if (state == "Select") {
                        return "qrc:///images/arrow-right-dark.png"
                    } else {
                        return "qrc:///images/arrow-right.png"
                    }
                } else {
                    if (state == "Select") {
                        return "qrc:///images-hd/arrow-right-dark.png"
                    } else {
                        return "qrc:///images-hd/arrow-right.png"
                    }
                }
            }
            buttonStyle: style.predictionMoreButton
            width: showMoreButton ? style.predictionBar.height : 0
            height: width
            radius: width * 0.5 // for circle
            visible: showMoreButton
            onReleased: pressMore()
            onExecuted: spaceBar.focus = true
            onTtsService: root.ttsService(ttsStringSeeMore)

            KeyNavigation.right: spaceBar
            Keys.onPressed: {
                if (event.key === Qt.Key_Down) {
                    return;
                } else if (event.key === Qt.Key_Left && predictionRepeater.count > 0) {
                    predictionRepeater.itemAt(predictionRepeater.count - 1).focus = true;
                    root.preColumn = -1;
                    event.accepted = true;
                } else if (event.key === Qt.Key_Up) {
                    meetTopBoundary(2); //focus to fix nearest button
                    event.accepted = true;
                }
                state = "Normal"
            }
        }

        // spaceBar
        BottomArea {
            id: spaceBar
            objectName: "spaceBar"
            property string ttsStringSpacebar: qsTr("Space") + (PluginProxy.emptyString !== undefined ? PluginProxy.emptyString : "")
            height: style.bottom.height
            width: {
                var sumWidth = predictionBar.width + moreButton.width + backButton.width;
                var space = 0;
                if (moreButton.visible)
                    space += row.spacing;
                if (words !== undefined && words.length > 0)
                    space += row.spacing;
                if (backButton.visible)
                    space += row.spacing;

                return root.width - sumWidth - space;
            }
            onSendKey: root.sendKey(keycode, shift, eventType)
            onTtsService: root.ttsService(ttsStringSpacebar)

            Keys.onPressed: {
                if (event.key === Qt.Key_Left) {
                    if (moreButton.visible) {
                        moreButton.focus = true;
                        event.accepted = true;
                    } else if (predictionRepeater.count > 0) {
                        predictionRepeater.itemAt(predictionRepeater.count - 1).focus = true;
                        event.accepted = true;
                    } else if (backButton.visible) {
                        backButton.focus = true;
                        event.accepted = true;
                    } else {
                        return;
                    }
                    root.preColumn = "defaultIndex";
                }
                else if (event.key === Qt.Key_Right) {
                    root.preColumn = "defaultIndex";
                }
                else if (event.key === Qt.Key_Up) {
                    meetTopBoundary(root.preColumn);
                    event.accepted = true;
                }
            }
        }
    }

    Keys.onPressed: {
        if (event.key === Qt.Key_Down) {
            meetBottomBoundary();
            event.accepted = true;
        } else if (event.key === Qt.Key_Left) {
            meetLeftBoundary();
            event.accepted = true;
        } else if (event.key === Qt.Key_Right) {
            meetRightBoundary();
            event.accepted = true;
        }
    }

    function setKeyNavigation(column) {
        //TODO: check the direction
        if (column === -1 && backButton.visible)
            backButton.focus = true;
        else if (column === -1 && words.length > 0)
            predictionRepeater.itemAt(0).focus = true;
        else
            spaceBar.focus = true;
        root.preColumn = column;
    }
}
