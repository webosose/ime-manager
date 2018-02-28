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
    id: resultListButton
    objectName: "resultListButton"

    LayoutMirroring.enabled: Qt.locale(voiceLanguage).textDirection ? true : false
    LayoutMirroring.childrenInherit: Qt.locale(voiceLanguage).textDirection ? true : false
    width: sttStyle.resultButton.width
    height: sttStyle.resultButton.height
    hoverEnabled: true
    property alias text: resultListButtonText.text
    property string textToSpeech : resultListButtonText.text
    onEntered: {
        resultListButton.forceActiveFocus()
    }

    onExited: {
        resultListButton.parent.forceActiveFocus()
    }

    onReleased: {
        onReleasedAction()
    }

    onActiveFocusChanged: {
        if(activeFocus) {
            resultListButtonTextRec.myElide = Text.ElideNone;
            if(resultListButtonTextRec.myContentWidth > resultListButtonTextRec.width)
                textAni.restart();
            remainSeconds = 30;
        } else {
            textAni.stop();
            resultListButtonTextRec.myX = 0;
            resultListButtonTextRec.myElide = Text.ElideRight;
        }
    }

    Rectangle {
        anchors.fill: parent
        color: resultListButton.activeFocus? "#cf0652" : "transparent"
    }

    Rectangle {
        id: resultListButtonTextRec
        objectName: "resultListButtonTextRec"
        anchors.left: parent.left
        anchors.leftMargin: sttStyle.resultListButtonText.leftMargin
        width: parent.width - sttStyle.resultListButtonText.leftMargin * 2
        height: parent.height
        color: sttStyle.resultButton.bgColor
        clip: true

        property alias myX: resultListButtonText.x
        property alias myContentWidth: resultListButtonText.contentWidth
        property alias myElide: resultListButtonText.elide

        Text {
            id: resultListButtonText
            objectName: "resultListButtonText"
            anchors.verticalCenter: parent.verticalCenter
            width: parent.width
            text: ""
            font.pixelSize: sttStyle.resultButton.fontSize
            font.family: museoSans_light_fontFamily
            font.weight: museo300_fontWeight
            color: sttStyle.resultButton.fontColor
            elide: Text.ElideRight
        }
    }

    SequentialAnimation {
        id: textAni
        objectName: "textAni"
        loops: Animation.Infinite
        PropertyAction { target: resultListButtonTextRec; property: "myX"; value: 0 }
        PauseAnimation { duration: 500 }
        PropertyAnimation {
            target: resultListButtonTextRec
            property: "myX"
            to: -resultListButtonTextRec.myContentWidth+resultListButtonTextRec.width
            duration: resultListButtonTextRec.myContentWidth - resultListButtonTextRec.width < 0 ? 0 : ((resultListButtonTextRec.myContentWidth - resultListButtonTextRec.width) * 10)
        }
        PauseAnimation { duration: 500 }
    }

    function onReleasedAction() {
        textKeyPressed(resultListButton.text);
        main.state = 'init';
    }
}
