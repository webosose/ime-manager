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
import "japanesestyle.js" as JapaneseStyle

Rectangle {
    id: btn
    objectName: "nextAndPreviousBtn"

    property alias text: txt.text
    property bool showNextButton
    property bool showPreviousButton
    property string predictionPageTxt: ""

    signal nextPrediction()
    signal previousPrediction()
    signal meetLeftBoundary()
    signal meetRightBoundary()
    signal meetTopBoundary()
    signal meetBottomBoundary()

    color: commonStyle.button.normal.bgColor
    border.color: commonStyle.button.normal.borderColor
    border.width: commonStyle.button.normal.borderWidth

    ButtonBase {
        id: previousButton
        objectName: "previousButton"
        anchors.left: parent.left
        anchors.leftMargin: commonStyle.left.cellSpace
        image: (state === "Select") ? "qrc:///japanese/images/arrow-left-dark.png" : "qrc:///japanese/images/arrow-left.png"
        buttonStyle: commonStyle.predictionMoreButton
        width: showPreviousButton ? commonStyle.right.cellHeight : 0
        height: width
        radius: width * 0.5 // for circle
        visible: showPreviousButton
        onReleased: previousPrediction()

        Keys.onPressed: {
            if (event.key === Qt.Key_Right && showNextButton) {
                nextButton.focus = true;
                event.accepted = true;
            }
        }
    }

    Text {
        id: txt
        objectName: "txt"
        anchors.fill: parent
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.family: commonStyle.button.fontFamily ? commonStyle.button.fontFamily : commonStyle.defaultFontFamily
        text: predictionPageTxt
        color: commonStyle.button.normal.fgColor
        font.pixelSize: commonStyle.button.normal.fontSize
    }

    ButtonBase {
        id: nextButton
        objectName: "nextButton"
        anchors.right: parent.right
        anchors.rightMargin: commonStyle.right.cellSpace
        image: (state === "Select") ? "qrc:///images/arrow-right-dark.png" : "qrc:///images/arrow-right.png"
        buttonStyle: commonStyle.predictionMoreButton
        width: showNextButton ? commonStyle.right.cellHeight : 0
        height: width
        radius: width * 0.5 // for circle
        visible: showNextButton
        onReleased: nextPrediction()

        Keys.onPressed: {
            if (event.key === Qt.Key_Left && showPreviousButton) {
                previousButton.focus = true;
                event.accepted = true;
            }
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

    function setKeyNavigation(from) {
        var priorArray =  (from === "Back") ? [nextButton, previousButton] : [previousButton, nextButton];
        for (var i=0; i < priorArray.length; i++) {
            if (priorArray[i].visible){
                priorArray[i].focus = true;
                break;
            }
        }
    }
}