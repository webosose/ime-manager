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

MouseArea {
    id: sayAgainButtonRec
    objectName: "sayAgainButtonRec"
    property string textToSpeech : sayAgainButtonText.text + " " + qsTr("button") + PluginProxy.emptyString

    LayoutMirroring.enabled: main.isRTL
    width: sayAgainButtonImageLeft.paintedWidth + sayAgainButtonImageMiddle.paintedWidth+ sayAgainButtonImageRight.paintedWidth
    height: sttStyle.sayAgainButton.height
    hoverEnabled: true

    onEntered: sayAgainButtonRec.forceActiveFocus()

    onExited: sayAgainButtonRec.parent.forceActiveFocus()

    onReleased: onReleasedAction()

    onActiveFocusChanged: if(activeFocus) remainSeconds = 30

    // UI VARIABLES. PARENT CAN CHANGE UI USING THESE VARIABLES
    property string buttonLeftNormalImg : "images/small_btn_w_n_l.png"
    property string buttonMidNormalImg : "images/small_btn_w_n_m.png"
    property string buttonRightNormalImg : "images/small_btn_w_n_r.png"
    property string buttonLeftFocusImg : "images/small_btn_f_l.png"
    property string buttonMidFocusImg : "images/small_btn_f_m.png"
    property string buttonRightFocusImg : "images/small_btn_f_r.png"
    property string textFontColor : sttStyle.sayAgainButton.fontColor
    property string textFontFocusColor : sttStyle.sayAgainButton.focusFontColor

    onOpacityChanged: {
        if(opacity === 1)
            update()
    }
    onVisibleChanged: {
        if(visible)
            update()
    }

    Image {
        id: sayAgainButtonImageLeft
        objectName: "sayAgainButtonImageLeft"
        anchors.left: parent.left
        width: sttStyle.sayAgainButton.sideImgWidth
        height: parent.height
        source: sayAgainButtonRec.activeFocus ? buttonLeftFocusImg : buttonLeftNormalImg
    }
    Image {
        id: sayAgainButtonImageMiddle
        objectName: "sayAgainButtonImageMiddle"
        anchors.left: sayAgainButtonImageLeft.right
        height: parent.height
        source: sayAgainButtonRec.activeFocus ? buttonMidFocusImg : buttonMidNormalImg
    }
    Image {
        id: sayAgainButtonImageRight
        objectName: "sayAgainButtonImageRight"
        anchors.left: sayAgainButtonImageMiddle.right
        width: sttStyle.sayAgainButton.sideImgWidth
        height: parent.height
        source: sayAgainButtonRec.activeFocus ? buttonRightFocusImg : buttonRightNormalImg
    }

    Text {
        id: sayAgainButtonText
        objectName: "sayAgainButtonText"
        anchors.centerIn: parent
        text: qsTr("RETRY") + PluginProxy.emptyString // i18n Button text means retrying voice recognition.
        font.pixelSize: sttStyle.sayAgainButton.fontSize
        font.family: miso_regular_fontFamily
        font.weight: misoBold_fontWeight
        font.capitalization: Font.AllUppercase
        color: sayAgainButtonRec.activeFocus ? textFontFocusColor : textFontColor
    }
    function update() {
        if(sayAgainButtonImageLeft.width + sayAgainButtonText.width + sayAgainButtonImageRight.width < 180) {
            sayAgainButtonRec.width = 180;
            sayAgainButtonImageMiddle.width = 180 - (sayAgainButtonImageLeft.width + sayAgainButtonImageRight.width);
        } else {
            sayAgainButtonImageMiddle.width = sayAgainButtonText.contentWidth;
            sayAgainButtonRec.width = sayAgainButtonImageLeft.width + sayAgainButtonImageMiddle.width + sayAgainButtonImageRight.width;
        }
    }

    function onReleasedAction() {
        resultListButton1.text = "";
        resultListButton2.text = "";
        resultListButton3.text = "";
        resultTextArray = undefined;
        main.forceActiveFocus();
        main.restartSttService();
    }
}
