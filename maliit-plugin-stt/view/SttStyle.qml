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
    property bool isFHD: true
    property real ratio: isFHD ? 1 : 2/3
    property var fontFamily: QtObject {
        property string museo300: "Museo SansNormal"
        property string museo500: "Museo SansDemiBold"
        property string miso_bold: "Moon Miso Bold"
    }

    property var main: QtObject {
        property color color: "transparent"
        property color bgColor: "#000000"
        property real opacity: 1.0
    }

    property var mic: QtObject {
        property int width: 293 * ratio
        property int height: 190 * ratio
        property color bgColor: "transparent"
        property color focusedColor: "#cf0652"
        property int micBorderWidth: 148 * ratio
        property int micImageHeight: 144 * ratio
        property int micErrorImageHeight: 190 * ratio
    }

    property var micBackground: QtObject {
        property int height: 190 * ratio
        property color bgColor: "#000000"
    }

    property var langSelectBox: QtObject {
        property int height: 380 * ratio
        property color bgColor: "#686868"
        property color fontColor: "#ffffff"
        property color lineColor: "#ffffff"
    }

    property var langSelectButtonOk: QtObject {
        property int height: 80 * ratio
        property int topMargin: 26 * ratio
        property int rightMargin: 25 * ratio
        property int sideImgWidth: 50 * ratio
    }

    property var langSelectButtonCancel: QtObject {
        property int height: 80 * ratio
        property int topMargin: 26 * ratio
        property int sideImgWidth: 50 * ratio
    }

    property var langSelectTitle: QtObject {
        property int topMargin: 25 * ratio
        property int leftMargin: 40 * ratio
        property int rightMargin: 40 * ratio
        property int fontSize: 73 * ratio
        property color fontColor: "#ffffff"
        property int lineTopMargin: 8 * ratio
        property int lineWidth: 1840 * ratio
        property int lineHeight: 2 * ratio
        property color lineColor: "#ffffff"
    }

    property var langSelectListView: QtObject {
        property int topMargin: 24 * ratio
        property int bottomMargin: 10 * ratio
        property int leftMargin: 30 * ratio
        property int rightMargin: 10 * ratio
        property int spacing: 18 * ratio
    }

    property var langSelectListItem: QtObject {
        property int itemImgleftMargin: 10 * ratio
        property int height: 55 * ratio
        property int itemTextLeftMargin: 10 * ratio
        property int itemTextRightMargin: 10 * ratio
        property int fontSize: 30 * ratio
        property color fontColor: "#ffffff"
        property int imgWidth: 20 * ratio
    }

    property var langSelectListScrollBar: QtObject {
        property int topMargin: 10 * ratio
        property int bottomMargin: 10 * ratio
        property int rightMargin: 40 * ratio
        property int width: 60 * ratio
        property int height: 228 * ratio
        property int arrowHeight: 60 * ratio
        property int barHeight: 108 * ratio
        property int barTopMargin: 10 * ratio
        property int barBottomMargin: 10 * ratio
    }

    property var guideImage: QtObject {
        property int rightMargin: 15 * ratio
    }

    property var guideText: QtObject {
        property int leftMargin: 15 * ratio
        property int rightMargin: 15 * ratio
        property int topMarginReady: 47 * ratio
        property int topMarginInitError: 70 * ratio
        property int bottomMargin: 5 * ratio
        property int fontSize: 32 * ratio
        property color fontColor: "#ffffff"
    }

    property var guideRetryButton: QtObject {
        property int topMargin: 24 * ratio
        property int rightMargin: 40 * ratio
    }
    property var guideLangText: QtObject {
        property int bottomMargin: 36 * ratio
        property int fontSize: 28 * ratio
        property color fontColor: "#ffffff"
        property int keyHelpImgLeftMargin: 10 * ratio
        property int keyHelpImgRightMargin: 15 * ratio
    }

    property var resultListBox: QtObject {
        property int height: 364 * ratio
        property color bgColor: "#686868"
        property real bgOpacity: 0.8
    }
    property var resultTitle: QtObject {
        property int topMargin: 25 * ratio
        property int leftMargin: 40 * ratio
        property int rightMargin: 40 * ratio
        property int fontSize: 73 * ratio
        property color fontColor: "#eeeeee"
        property int lineTopMargin: 8 * ratio
        property int lineHeight: 2 * ratio
        property color lineColor: "#ffffff"

    }
    property var resultButton: QtObject {
        property color bgColor: "transparent"
        property int lineMargin: 23 * ratio
        property int spacing: 9 * ratio
        property int width: 640 * ratio
        property int height: 58 * ratio
        property int leftMargin: 30 * ratio
        property int rightMargin: 30 * ratio
        property int fontSize: 30 * ratio
        property color fontColor: "#ffffff"
        property int textLeftMargin: 5 * ratio
        property int focusTextLeftMargin: 10 * ratio
        property int focusBorderWidth: 5 * ratio
        property color focusBorderColor: "#ff2f7d"
        property color exitColor: "transparent"
    }

    property var resultListButtonText: QtObject {
        property int leftMargin: 10 * ratio
    }

    property var sayAgainButton: QtObject {
        property color bgColor: "transparent"
        property int height: 80 * ratio
        property int rightMargin: 30 * ratio
        property int bottomMargin: 26 * ratio
        property int topMargin: 26 * ratio
        property int fontSize: 33 * ratio
        property color fontColor: "#686868"
        property color focusFontColor: "#ffffff"
        property int sideImgWidth: 50 * ratio
    }

    property var seperateLine: QtObject {
        property int initialLineTopMargin: 106 * ratio
        property int rightMargin: 60 * ratio
        property int width: 640 * ratio
        property int height: 1 * ratio
        property int boldHeight: 4 * ratio
        property color color: "#ffffff"
        property color boldColor: "#717171"
        property real opacity: 0.3
        property real boldOpacity: 1
    }

    property var spinner: QtObject {
        property int diameter: 73 * ratio
    }

    function reloadFontFamily(language, region) {
        switch(language) {
        // non-latin based //
        case "am":
            museoSans_light_fontFamily = "LG Display_Amharic";
            museoSans_regular_fontFamily = "LG Display_Amharic";
            museo300_fontWeight = fontDemiBold;
            museo500_fontWeight = fontDemiBold;
            museo700_fontWeight = fontDemiBold;
            museo700_fontItalic = false;
            miso_light_fontFamily = "LG Display_Amharic";
            miso_regular_fontFamily = "LG Display_Amharic";
            misoRegular_fontWeight = fontDemiBold;
            misoBold_fontWeight = fontDemiBold;
            break;
        case "ml": //Malayalam
            museoSans_light_fontFamily = "LG Display_ML";
            museoSans_regular_fontFamily = "LG Display_ML";
            museo300_fontWeight = fontDemiBold;
            museo500_fontWeight = fontDemiBold;
            museo700_fontWeight = fontDemiBold;
            museo700_fontItalic = false;
            miso_light_fontFamily = "LG Display_ML";
            miso_regular_fontFamily = "LG Display_ML";
            misoRegular_fontWeight = fontDemiBold;
            misoBold_fontWeight = fontDemiBold;
            break;
        case "or":
            museoSans_light_fontFamily = "LG Display_Oriya";
            museoSans_regular_fontFamily = "LG Display_Oriya";
            museo300_fontWeight = fontDemiBold;
            museo500_fontWeight = fontDemiBold;
            museo700_fontWeight = fontDemiBold;
            museo700_fontItalic = false;
            miso_light_fontFamily = "LG Display_Oriya";
            miso_regular_fontFamily = "LG Display_Oriya";
            misoRegular_fontWeight = fontDemiBold;
            misoBold_fontWeight = fontDemiBold;
            break;
        case "ur":
            museoSans_light_fontFamily = "LG Display_Urdu";
            museoSans_regular_fontFamily = "LG Display_Urdu";
            museo300_fontWeight = fontDemiBold;
            museo500_fontWeight = fontDemiBold;
            museo700_fontWeight = fontDemiBold;
            museo700_fontItalic = false;
            miso_light_fontFamily = "LG Display_Urdu";
            miso_regular_fontFamily = "LG Display_Urdu";
            misoRegular_fontWeight = fontDemiBold;
            misoBold_fontWeight = fontDemiBold;
            break;
        case "en":
            if(region === "JP") {
                museoSans_light_fontFamily = "LG Display_JP";
                museoSans_regular_fontFamily = "LG Display_JP";
                museo300_fontWeight = fontDemiBold;
                museo500_fontWeight = fontDemiBold;
                museo700_fontWeight = fontDemiBold;
                museo700_fontItalic = false;
                miso_light_fontFamily = "LG Display_JP";
                miso_regular_fontFamily = "LG Display_JP";
                misoRegular_fontWeight = fontDemiBold;
                misoBold_fontWeight = fontDemiBold;
            } else {    // latin
                museoSans_light_fontFamily = "Museo Sans";
                museoSans_regular_fontFamily = "Museo Sans";
                museo300_fontWeight = fontNormal;
                museo500_fontWeight = fontDemiBold;
                museo700_fontWeight = fontBold;
                museo700_fontItalic = true;
                miso_light_fontFamily = "Miso";
                miso_regular_fontFamily = "Miso";
                misoRegular_fontWeight = fontNormal;
                misoBold_fontWeight = fontBold;
            }
            break;
        case "ja": //Japanese
            museoSans_light_fontFamily = "LG Display_JP";
            museoSans_regular_fontFamily = "LG Display_JP";
            museo300_fontWeight = fontDemiBold;
            museo500_fontWeight = fontDemiBold;
            museo700_fontWeight = fontDemiBold;
            museo700_fontItalic = false;
            miso_light_fontFamily = "LG Display_JP";
            miso_regular_fontFamily = "LG Display_JP";
            misoRegular_fontWeight = fontDemiBold;
            misoBold_fontWeight = fontDemiBold;
            break;
        case "zh": //Chinese
            if(region === "HK" || region === "TW") {
                museoSans_light_fontFamily = "LG Display GP4_HK-Light";
                museoSans_regular_fontFamily = "LG Display GP4_HK-Regular";
                museo300_fontWeight = fontNormal;
                museo500_fontWeight = fontNormal;
                museo700_fontWeight = fontDemiBold;
                museo700_fontItalic = false;
                miso_light_fontFamily = "LG Display GP4_HK-Light";
                miso_regular_fontFamily = "LG Display GP4_HK-Regular";
                misoRegular_fontWeight = fontNormal;
                misoBold_fontWeight = fontDemiBold;
            } else {
                museoSans_light_fontFamily = "LG Display-Light";
                museoSans_regular_fontFamily = "LG Display-Regular";
                museo300_fontWeight = fontNormal;
                museo500_fontWeight = fontNormal;
                museo700_fontWeight = fontDemiBold;
                museo700_fontItalic = false;
                miso_light_fontFamily = "LG Display-Light";
                miso_regular_fontFamily = "LG Display-Regular";
                misoRegular_fontWeight = fontNormal;
                misoBold_fontWeight = fontDemiBold;
            }
            break;
        case "as": //Assamese
        case "bn": //Bengali
        case "gu": //Gujarati
        case "hi": //Hindi
        case "kn": //Kannada
        case "mr": //Marathi
        case "pa": //Panjabi
        case "ta": //Tamil
        case "te": //Telugu
            museoSans_light_fontFamily = "LGIndia";
            museoSans_regular_fontFamily = "LGIndia";
            museo300_fontWeight = fontDemiBold;
            museo500_fontWeight = fontDemiBold;
            museo700_fontWeight = fontDemiBold;
            museo700_fontItalic = false;
            miso_light_fontFamily = "LGIndia";
            miso_regular_fontFamily = "LGIndia";
            misoRegular_fontWeight = fontDemiBold;
            misoBold_fontWeight = fontDemiBold;
            break;
        // nonLatin //
        case "ar": //Arabic
        case "bg": //Bularian
        case "el": //Greek
        case "fa": //Farsi
        case "he": //Hebrew
        case "kk": //Kazakh
        case "ko": //Korean
        case "ku": //Kurdish
        case "mk": //Macedonian
        case "mn": //Mongolian
        case "ru": //Russian
        case "th": //Thai
        case "uk": //Ukranian
            museoSans_light_fontFamily = "LG Display-Light";
            museoSans_regular_fontFamily = "LG Display-Regular";
            museo300_fontWeight = fontNormal;
            museo500_fontWeight = fontNormal;
            museo700_fontWeight = fontDemiBold;
            museo700_fontItalic = false;
            miso_light_fontFamily = "LG Display-Light";
            miso_regular_fontFamily = "LG Display-Regular";
            misoRegular_fontWeight = fontNormal;
            misoBold_fontWeight = fontDemiBold;
            break;
        case "km": //Khmer
            museoSans_light_fontFamily = "Noto Sans Khmer";
            museoSans_regular_fontFamily = "Noto Sans Khmer";
            museo300_fontWeight = fontNormal;
            museo500_fontWeight = fontNormal;
            museo700_fontWeight = fontDemiBold;
            museo700_fontItalic = false;
            miso_light_fontFamily = "Noto Sans Khmer";
            miso_regular_fontFamily = "Noto Sans Khmer";
            misoRegular_fontWeight = fontNormal;
            misoBold_fontWeight = fontDemiBold;
            break;
        // latin based //
        default:
            museoSans_light_fontFamily = "Museo Sans";
            museoSans_regular_fontFamily = "Museo Sans";
            museo300_fontWeight = fontNormal;
            museo500_fontWeight = fontDemiBold;
            museo700_fontWeight = fontBold;
            museo700_fontItalic = true;
            miso_light_fontFamily = "Miso";
            miso_regular_fontFamily = "Miso";
            misoRegular_fontWeight = fontNormal;
            misoBold_fontWeight = fontBold;
            break;
        }
        console.log("reloadFontFamily: "+ language+", "+region);
        console.log("museoSans_light_fontFamily: "+ museoSans_light_fontFamily);
        console.log("museoSans_regular_fontFamily: "+ museoSans_regular_fontFamily);
        console.log("museo300_fontWeight: "+ museo300_fontWeight);
        console.log("museo500_fontWeight: "+ museo500_fontWeight);
        console.log("museo700_fontWeight: "+ museo700_fontWeight);
        console.log("museo700_fontItalic: "+ museo700_fontItalic);
        console.log("miso_light_fontFamily: "+ miso_light_fontFamily);
        console.log("miso_regular_fontFamily: "+ miso_regular_fontFamily);
        console.log("misoRegular_fontWeight: "+ misoRegular_fontWeight);
        console.log("misoBold_fontWeight: "+ misoBold_fontWeight);
    }
}

