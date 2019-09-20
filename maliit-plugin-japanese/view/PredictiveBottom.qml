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

Item {
    id: root
    objectName: "predictiveBottom"
    property variant words
    property bool showMoreButton
    property bool showBackButton
    property bool showSpaceBar
    signal sendKey(string rawcode, bool shift, int eventType)
    signal selectPredictionWord(int index)
    signal pressMore()
    signal pressBack()
    signal meetLeftBoundary()
    signal meetRightBoundary()
    signal meetTopBoundary()
    signal meetBottomBoundary()
    signal predictionSelected()

    Row {
        id: row
        objectName: "predictionRow"
        spacing: showBackButton ? commonStyle.middle.leftMargin : commonStyle.predictionBar.spacing

        // prediction words
        Row {
            id: predictionBar
            objectName: "predictionBar"
            spacing: commonStyle.predictionBar.spacing
            Repeater {
                id: predictionRepeater
                objectName: "predictionRepeater"
                model: words
                ButtonBase {
                    buttonStyle: commonStyle.predictionBarButton
                    text: modelData
                    height: commonStyle.bottom.height
                    width: contentWidth

                    onExecuted: predictionSelected()
                    onReleased: selectPredictionWord(index)

                    KeyNavigation.right: {
                        if (index == words.length-1){
                            return showMoreButton ? moreButton : predictionRepeater.itemAt(0)
                        } else {
                            return predictionRepeater.itemAt(index + 1)
                        }
                    }
                    KeyNavigation.left: {
                        if (index == 0){
                            return showMoreButton ? moreButton : predictionRepeater.itemAt(words.length-1)
                        } else {
                            return predictionRepeater.itemAt(index - 1)
                        }

                    }

                    Keys.onPressed: {
                        if (event.key === Qt.Key_Right && index === predictionRepeater.count - 1) {
                            if (moreButton.visible) {
                                moreButton.focus = true;
                                event.accepted = true;
                            }
                        }
                    }
                }
                onItemRemoved: item.removed = true
            }
        }

        // more button
        ButtonBase {
            id: moreButton
            objectName: "moreButton"
            image: (state === "Select") ? "qrc:///images/arrow-right-dark.png" : "qrc:///images/arrow-right.png"
            buttonStyle: commonStyle.predictionMoreButton
            width: showMoreButton ? commonStyle.predictionBar.height : 0
            height: width
            radius: width * 0.5 // for circle
            visible: showMoreButton
            onReleased: pressMore()

            Keys.onPressed: {
                if (event.key === Qt.Key_Left && predictionRepeater.count > 0) {
                    predictionRepeater.itemAt(predictionRepeater.count - 1).focus = true;
                    event.accepted = true;
                }
            }
        }

        // spaceBar & hide button
        BottomArea {
            id: spaceBar
            height: commonStyle.bottom.height
            visible: showSpaceBar
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
            onSendKey: root.sendKey(Variables.FullWidthSpaceRawCode, shift, eventType)
        }
    }

    Keys.onPressed: {
        if (event.key === Qt.Key_Up) {
            meetTopBoundary();
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

    function setKeyNavigation(mode, fromRightArea) {
        if (mode === "Hiragana") {
            if (predictionRepeater.count)
                predictionRepeater.itemAt(0).focus = true;
        } else if (mode !== "Katakana" && !fromRightArea) {
            spaceBar.focus = true;
        }
    }

    function checkMeetBottomBoundry(fromRightArea) {
        if (mode === "Hiragana" && predictionRepeater.count === 0) {
            meetBottomBoundary()
        } else if (mode === "Katakana") {
            meetBottomBoundary()
        } else if (fromRightArea){
            meetBottomBoundary()
        } else {
            // There is space bar on Latin Alphabet
        }
    }
}
