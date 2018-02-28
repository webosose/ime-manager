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

    property var hidPrediction:  QtObject {
        property int height: 99
        property int predictionRowWidth: 1724
        property int leftMargin: 20
        property int rightMargin: 20
        property int topMargin: 20
        property int bottomMargin: 20
        property int cellHeight: 60
        property int cellWidth: 167
        property int cellSpace: 6
        property int cellCount: 10
        property int maxLengthChar: 108
        property int moreWidth: 72
    }

    property int hidPredictionBottomMargin: 20

    property var hidPredictionButton: QtObject {
        property string fontFamily: "MuseoSans"
        property var normal: QtObject {
            property color bgColor: "#282828"
            property color fgColor: "#eeeeee"
            property color subtitleColor: "#808080"
            property color borderColor: "#ffb80d"
            property int borderWidth: 0
            property int fontSize: 28
            property int subtitleSize: 20
        }
        property var focus: QtObject {
            property color bgColor: "#ff2f7d"
            property color fgColor: "#eeeeee"
            property color subtitleColor: "#808080"
            property color borderColor: "#ffb80d"
            property int borderWidth: 0
            property int fontSize: 28
            property int subtitleSize: 20
        }
        property var select: QtObject {
            property color bgColor: "#bcbcbc"
            property color fgColor: "#282828"
            property color subtitleColor: "#808080"
            property color borderColor: "#ff2f7d"
            property int borderWidth: 6
            property int fontSize: 28
            property int subtitleSize: 20
        }
        property var disable: QtObject {
            property color bgColor: "#383838"
            property color fgColor: "#282828"
            property color subtitleColor: "#282828"
            property int borderWidth: 0
        }
    }

    // languages (ttsStrings)
    property string _Albanian: qsTr("Albanian") + PluginProxy.emptyString
    property string _Arabic: qsTr("Arabic") + PluginProxy.emptyString
    property string _Bosnian: qsTr("Bosnian") + PluginProxy.emptyString
    property string _Bulgarian: qsTr("Bulgarian") + PluginProxy.emptyString
    property string _Croatian: qsTr("Croatian") + PluginProxy.emptyString
    property string _Czech: qsTr("Czech") + PluginProxy.emptyString
    property string _Danish: qsTr("Danish") + PluginProxy.emptyString
    property string _Dutch: qsTr("Dutch") + PluginProxy.emptyString
    property string _English: qsTr("English") + PluginProxy.emptyString
    property string _Estonian: qsTr("Estonian") + PluginProxy.emptyString
    property string _Finnish: qsTr("Finnish") + PluginProxy.emptyString
    property string _French: qsTr("French") + PluginProxy.emptyString
    property string _Gaelic: qsTr("Gaelic") + PluginProxy.emptyString
    property string _German: qsTr("German") + PluginProxy.emptyString
    property string _Greek: qsTr("Greek") + PluginProxy.emptyString
    property string _Hebrew: qsTr("Hebrew") + PluginProxy.emptyString
    property string _Hindi: qsTr("Hindi") + PluginProxy.emptyString
    property string _Hungarian: qsTr("Hungarian") + PluginProxy.emptyString
    property string _Indonesian: qsTr("Indonesian") + PluginProxy.emptyString
    property string _Irish: qsTr("Irish") + PluginProxy.emptyString
    property string _Italian: qsTr("Italian") + PluginProxy.emptyString
    property string _Kazakh: qsTr("Kazakh") + PluginProxy.emptyString
    property string _Korean: qsTr("Korean") + PluginProxy.emptyString
    property string _Kurdish: qsTr("Kurdish") + PluginProxy.emptyString
    property string _Latvian: qsTr("Latvian") + PluginProxy.emptyString
    property string _Lithuanian: qsTr("Lithuanian") + PluginProxy.emptyString
    property string _Macedonian: qsTr("Macedonian") + PluginProxy.emptyString
    property string _Malay: qsTr("Malay") + PluginProxy.emptyString
    property string _Maori: qsTr("Maori") + PluginProxy.emptyString
    property string _Mongolian: qsTr("Mongolian") + PluginProxy.emptyString
    property string _Norwegian: qsTr("Norwegian") + PluginProxy.emptyString
    property string _Persian: qsTr("Persian") + PluginProxy.emptyString
    property string _Polish: qsTr("Polish") + PluginProxy.emptyString
    property string _Portuguese: qsTr("Portuguese") + PluginProxy.emptyString
    property string _Romanian: qsTr("Romanian") + PluginProxy.emptyString
    property string _Russian: qsTr("Russian") + PluginProxy.emptyString
    property string _Serbian: qsTr("Serbian") + PluginProxy.emptyString
    property string _Slovak: qsTr("Slovak") + PluginProxy.emptyString
    property string _Slovenian: qsTr("Slovenian") + PluginProxy.emptyString
    property string _Spanish: qsTr("Spanish") + PluginProxy.emptyString
    property string _Swedish: qsTr("Swedish") + PluginProxy.emptyString
    property string _Thai: qsTr("Thai") + PluginProxy.emptyString
    property string _Turkish: qsTr("Turkish") + PluginProxy.emptyString
    property string _Ukrainian: qsTr("Ukrainian") + PluginProxy.emptyString
    property string _Uzbek: qsTr("Uzbek") + PluginProxy.emptyString
    property string _Vietnamese: qsTr("Vietnamese") + PluginProxy.emptyString
}
