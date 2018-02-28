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

QtObject {
    id: root

    property var hidPrediction: QtObject {
        property int height: 77
        property int predictionRowWidth: 1150
        property int leftMargin: 13
        property int rightMargin: 13
        property int topMargin: 13
        property int bottomMargin: 13
        property int cellHeight: 50
        property int cellWidth: 111
        property int cellSpace: 4
        property int cellCount: 10
        property int maxLengthChar: 72
        property int moreWidth: 48
    }

    property int hidPredictionBottomMargin: 13

    property var hidPredictionButton: QtObject {
        property string fontFamily: "MuseoSans"
        property var normal: QtObject {
            property color bgColor: "#282828"
            property color fgColor: "#eeeeee"
            property color subtitleColor: "#808080"
            property color borderColor: "#ffb80d"
            property int borderWidth: 0
            property int fontSize: 18
            property int subtitleSize: 14
        }
        property var focus: QtObject {
            property color bgColor: "#cf0652"
            property color fgColor: "#eeeeee"
            property color subtitleColor: "#808080"
            property color borderColor: "#ffb80d"
            property int borderWidth: 0
            property int fontSize: 18
            property int subtitleSize: 14
        }
        property var select: QtObject {
            property color bgColor: "#bcbcbc"
            property color fgColor: "#282828"
            property color subtitleColor: "#808080"
            property color borderColor: "#cf0652"
            property int borderWidth: 4
            property int fontSize: 18
            property int subtitleSize: 14
        }
        property var disable: QtObject {
            property color bgColor: "#383838"
            property color fgColor: "#282828"
            property color subtitleColor: "#282828"
            property int borderWidth: 0
        }
    }
}
