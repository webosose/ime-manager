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
import "../keyboard-common"

Item {
    id: root
    objectName: "bottomArea"
    property QtObject chineseStyle: []
    property variant suggestionList: Suggestion.list
    property bool next: Suggestion.next
    property bool previous: Suggestion.previous
    property string preedit: Suggestion.preedit

    signal sendKey(int keycode, bool shift)
    signal meetLeftBoundary()
    signal meetRightBoundary()
    signal meetTopBoundary(int column)
    signal meetBottomBoundary()

    ButtonBase {
        id: preeditBox
        objectName: "preeditBox"
        state: "Disable"
        buttonStyle: root.chineseStyle.suggestionButton
        text: preedit
        width: preeditBox.contentWidth > root.chineseStyle.preeditBox.width ?
                    preeditBox.contentWidth : root.chineseStyle.preeditBox.width
        height: style.bottom.height
        onReleased: {
            spaceBar.focus = true;
            commitPreeditString()
        }
        anchors.left: parent.left
        Keys.onPressed: {
            if (event.key === Qt.Key_Right) {
                if(suggestionItemBar.enabled)
                    suggestionItemRepeater.itemAt(0).focus = true;
                else if(componentBar.enabled)
                    compoentRepeater.itemAt(0).focus = true;
                else
                    spaceBar.focus = true;
                event.accepted = true;
            } else if (event.key === Qt.Key_Up) {
                meetTopBoundary(0);
                event.accepted = true;
            }
        }
    }

    Row {
        id: suggestionBar
        objectName: "predictionRow"
        spacing: style.middle.cellSpace
        x: preeditBox.width + style.middle.leftMargin

        Row {
            id: suggestionItemBar
            objectName: "predictionBar"
            enabled: suggestionList.length > 0
            Repeater {
                id: suggestionItemRepeater
                objectName: "suggestionItemRepeater"
                model: suggestionList
                ButtonBase {
                    buttonStyle: root.chineseStyle.suggestionButton
                    text: modelData
                    height: style.bottom.height
                    width: contentWidth > root.chineseStyle.suggestion.cellWidth ? contentWidth : root.chineseStyle.suggestion.cellWidth
                    onReleased: {
                        spaceBar.focus = true;
                        Suggestion.onSelected(index)
                    }

                    KeyNavigation.right: suggestionItemRepeater.itemAt(index + 1)
                    KeyNavigation.left: suggestionItemRepeater.itemAt(index - 1)
                    Keys.onPressed: {
                        if (event.key === Qt.Key_Right && index === suggestionItemRepeater.count - 1) {
                            if (leftArrow.width > 0 && leftArrow.state !== "Disable")
                                leftArrow.focus = true;
                            else if (rightArrow.width > 0 && rightArrow.state!== "Disable")
                                rightArrow.focus = true;
                            else if (componentBar.enabled)
                                compoentRepeater.itemAt(0).focus = true;
                            else
                                spaceBar.focus = true;
                            event.accepted = true;
                        } else if (event.key === Qt.Key_Left && index === 0 && preeditBox.enabled) {
                            preeditBox.focus = true;
                        }
                    }
                }
                onItemRemoved: item.removed = true
            }
        }

        ButtonBase {
            id: leftArrow
            objectName: "leftArrow"
            enabled: previous || next
            visible: previous || next
            buttonStyle: root.chineseStyle.suggestionArrow
            state : Suggestion.previous ? "Normal" : "Disable"
            image: {
                if (style.keyboardDefaultWidth === 1920) {
                    if (state !== "Disable")
                        return "qrc:///images/arrow-left.png"
                    else
                        return "qrc:///images/arrow-left-dark.png"
                } else {
                    if (state !== "Disable")
                        return "qrc:///images-hd/arrow-left.png"
                    else
                        return "qrc:///images-hd/arrow-left-dark.png"
                }
            }
            height: root.chineseStyle.suggestion.arrowWidth
            width: (previous || next) ? root.chineseStyle.suggestion.arrowWidth : 0
            radius: width * 0.5
            onReleased: {
                Suggestion.onPrevious();
                if (previous) leftArrow.focus = true;
                else if (next) rightArrow.focus = true;
                else spaceBar.focus = true;
            }
            Keys.onPressed: {
                if (event.key === Qt.Key_Right) {
                    if (rightArrow.width > 0 && rightArrow.state !== "Disable")
                        rightArrow.focus = true;
                    else if (componentBar.enabled)
                        compoentRepeater.itemAt(0).focus = true;
                    else
                        spaceBar.focus = true;
                    event.accepted = true;
                }
            }
            KeyNavigation.left: suggestionItemRepeater.itemAt(suggestionItemRepeater.count-1)
        }

        ButtonBase {
            id: rightArrow
            objectName: "rightArrow"
            enabled: previous || next
            visible: previous || next
            buttonStyle: root.chineseStyle.suggestionArrow
            state : Suggestion.next ? "Normal" : "Disable"
            image: {
                if (style.keyboardDefaultWidth === 1920) {
                    if (state !== "Disable")
                        return "qrc:///images/arrow-right.png"
                    else
                        return "qrc:///images/arrow-right-dark.png"
                } else {
                    if (state !== "Disable")
                        return "qrc:///images-hd/arrow-right.png"
                    else
                        return "qrc:///images-hd/arrow-right-dark.png"
                }
            }
            height: root.chineseStyle.suggestion.arrowWidth
            width: (previous || next) ? root.chineseStyle.suggestion.arrowWidth : 0
            radius: width * 0.5
            onReleased: {
                Suggestion.onNext();
                if (next) rightArrow.focus = true;
                else if (previous) leftArrow.focus = true;
                else spaceBar.focus = true;
            }
            Keys.onPressed: {
                if (event.key === Qt.Key_Right) {
                    if (componentBar.enabled)
                        compoentRepeater.itemAt(0).focus = true;
                    else
                        spaceBar.focus = true;
                    event.accepted = true;
                } else if (event.key === Qt.Key_Left) {
                    if (leftArrow.width > 0 && leftArrow.state !== "Disable")
                        leftArrow.focus = true;
                    else
                        suggestionItemRepeater.itemAt(suggestionItemRepeater.count-1).focus = true;
                    event.accepted = true;
                }
            }
        }

        Row {
            id: componentBar
            objectName: "componentBar"
            enabled: StrokeComponent.list.length > 0
            Repeater {
                id: compoentRepeater
                objectName: "compoentRepeater"
                model: StrokeComponent.list
                ButtonBase {
                    buttonStyle: root.chineseStyle.componentButton
                    text: modelData
                    height: style.bottom.height
                    width: root.chineseStyle.component.cellWidth
                    onReleased: {
                        spaceBar.focus = true;
                        StrokeComponent.onSelected(index)
                    }
                    KeyNavigation.right: compoentRepeater.itemAt(index + 1)
                    KeyNavigation.left: compoentRepeater.itemAt(index - 1)
                    Keys.onPressed: {
                        if (event.key === Qt.Key_Right && index === compoentRepeater.count - 1) {
                            spaceBar.focus = true;
                            event.accepted = true;
                        }
                        else if (event.key === Qt.Key_Left && index === 0) {
                            if (rightArrow.width > 0 && rightArrow.state !== "Disable")
                                rightArrow.focus = true;
                            else if (leftArrow.width > 0 && leftArrow.state !== "Disable")
                                leftArrow.focus = true;
                            else if(suggestionItemBar.enabled)
                                suggestionItemRepeater.itemAt(suggestionItemRepeater.count-1).focus = true;
                            else
                                meetLeftBoundary();
                            event.accepted = true;
                        }
                    }
                }
                onItemRemoved: item.removed = true
            }
        }

        BottomArea {
            id: spaceBar
            objectName: "spaceBar"
            width: {
                var sumWidth = preeditBox.width;
                if (suggestionItemBar.enabled)
                    sumWidth += suggestionItemBar.width + suggestionBar.spacing;
                if (previous || next)
                    sumWidth += leftArrow.width + rightArrow.width + (style.middle.cellSpace*2);
                if (componentBar.enabled)
                    sumWidth += componentBar.width + suggestionBar.spacing;
                sumWidth += style.bottom.leftMargin;
                return root.width - sumWidth;
            }
            height: style.bottom.height
            onSendKey: root.sendKey(89,false)
            Keys.onPressed: {
                if (event.key === Qt.Key_Left) {
                    if (componentBar.enabled)
                        compoentRepeater.itemAt(compoentRepeater.count-1).focus = true;
                    else if (rightArrow.width > 0 && rightArrow.state !== "Disable")
                        rightArrow.focus = true;
                    else if (leftArrow.width > 0 && leftArrow.state !== "Disable")
                        leftArrow.focus = true;
                    else if (suggestionItemBar.enabled)
                       suggestionItemRepeater.itemAt(suggestionItemRepeater.count-1).focus = true;
                    else if (preeditBox.state === "Normal")
                        preeditBox.focus = true;
                    else
                        meetLeftBoundary();
                    event.accepted = true;
                }
            }
        }
    }

    onNextChanged: rightArrow.state = next ? "Normal" : "Disable"
    onPreviousChanged: leftArrow.state = previous ? "Normal" : "Disable"
    onPreeditChanged: checkPreeditState()

    function checkPreeditState() {
        if (preedit.length > 0)
            preeditBox.state = "Normal"
        else
            preeditBox.state = "Disable"
    }

    function commitPreeditString() {
        if (preedit.length > 0)
           Suggestion.onPreeditBoxPressed();
    }

    Keys.onPressed: {
        if (event.key === Qt.Key_Up) {
            meetTopBoundary(-1);
            event.accepted = true;
        } else if (event.key === Qt.Key_Down) {
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
       if (column === -1 && suggestionList.length > 0) {
          suggestionItemRepeater.itemAt(0).focus = true;
       } else {
          spaceBar.focus = true;
       }
    }

    Connections {
        target: PluginProxy
        onKeyReleased : {
            if (isReleased && leftArrow.visible && (leftArrow.state === "Select"))
                leftArrow.state = "Focus";
            if (isReleased && rightArrow.visible && (rightArrow.state === "Select"))
                rightArrow.state = "Focus";
        }
    }
}
