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

// lite in HD
QtObject {
    id: root

    readonly property string _MuseoSans: "Museo SansDemiBold"
    readonly property string _MuseoSans300: "Museo SansNormal"
    readonly property string _MuseoSans700: "Museo SansBold"
    readonly property string _MuseoSans900: "Museo SansBlack"

    readonly property string _LGDisplay: "LG Display-Regular"
    readonly property string _LGDisplayHK: "LG Display_HK-Regular"
    readonly property string _LGDisplayJP: "LG Display_JP"
    readonly property string _LGIndia: "LGIndia"
    readonly property string _NotoSansKhmer: "Noto Sans Khmer"

    property color bgColor: "#4b4b4b"
    property string defaultFontFamily: _MuseoSans
    property string fontForMenuLocale: _MuseoSans

    property string webosVariant: "standard"
    property int keyboardDefaultWidth: 1280
    property int keyboardDefaultHeight: 217

    property var left: QtObject {
        property int width: 114
        property int height: 152
        property int topMargin: 13
        property int leftMargin: 13
        property int cellWidth: 114
        property int cellHeight: 35
        property int cellSpace: 4
        property int fontSize: 19
    }

    property var right: QtObject {
        property int width: 128
        property int height: 191
        property int topMargin: 13
        property int leftMargin: 13
        property int rightMargin: 13
        property int cellHeight: 35
        property int cellSpace: 4
    }

    property var middle: QtObject {
        property int width: 986
        property int height: 152
        property int topMargin: 13
        property int leftMargin: 13
        property int cellHeight: 35
        property int cellSpace: 4
    }

    property var bottom: QtObject {
        property int width: 1049
        property int height: 35
        property int topMargin: 4
        property int leftMargin: 13
        property int rightMargin: 13
        property int bottomMargin: 13
        property int cellSpace: 4
        property int hideBtnWidth: 70
    }

    property var button: QtObject {
        property string fontFamily: defaultFontFamily
        property int minimumPixelSize: 8
        property double minimumMargin: 2
        property var normal: QtObject {
            property color bgColor: "#282828"
            property color fgColor: "#eeeeee"
            property color borderColor: "#ffb80d"
            property int borderWidth: 0
            property int fontSize: 19
        }
        property var focus: QtObject {
            property color bgColor: "#cf0652"
            property color fgColor: "#ffffff"
            property color borderColor: "#ffb80d"
            property int borderWidth: 0
            property int fontSize: 19
        }
        property var select: QtObject {
            property color bgColor: "#bcbcbc"
            property color fgColor: "#282828"
            property color borderColor: "#cf0652"
            property int borderWidth: 4
            property int fontSize: 19
        }
        property var disable: QtObject {
            property color bgColor: "transparent"
            property color fgColor: "transparent"
            property color borderColor: "transparent"
            property int borderWidth: 0
            property int fontSize: 19
        }
        property var lockedNormal: QtObject {
            property color bgColor: "#282828"
            property color borderColor: "#eeeeee"
            property int borderWidth: 4
        }
        property var lockedFocus: QtObject {
            property color bgColor: "#cf0652"
            property color borderColor: "#eeeeee"
            property int borderWidth: 4
        }
        property var lockedSelect: QtObject {
            property color bgColor: "#eeeeee"
            property color borderColor: "#cf0652"
            property int borderWidth: 4
        }
    }

    property var symbolButton: QtObject {
        property string fontFamily: _LGDisplay
        property int minimumPixelSize: 8
        property double minimumMargin: 2
        property var normal: QtObject {
            property color bgColor: "#282828"
            property color fgColor: "#eeeeee"
            property color borderColor: "#ffb80d"
            property int borderWidth: 0
            property int fontSize: 19
        }
        property var focus: QtObject {
            property color bgColor: "#cf0652"
            property color fgColor: "#ffffff"
            property color borderColor: "#ffb80d"
            property int borderWidth: 0
            property int fontSize: 19
        }
        property var select: QtObject {
            property color bgColor: "#bcbcbc"
            property color fgColor: "#282828"
            property color borderColor: "#cf0652"
            property int borderWidth: 4
            property int fontSize: 19
        }
        property var disable: QtObject {
            property color bgColor: "transparent"
            property color fgColor: "transparent"
            property color borderColor: "transparent"
            property int borderWidth: 0
            property int fontSize: 19
        }
        property var lockedNormal: QtObject {
            property color bgColor: "#282828"
            property color borderColor: "#eeeeee"
            property int borderWidth: 4
        }
        property var lockedFocus: QtObject {
            property color bgColor: "#cf0652"
            property color borderColor: "#eeeeee"
            property int borderWidth: 4
        }
        property var lockedSelect: QtObject {
            property color bgColor: "#eeeeee"
            property color borderColor: "#cf0652"
            property int borderWidth: 4
        }
    }

    property var languageButton: QtObject {
        property string fontFamily: defaultFontFamily
        property int minimumPixelSize: 8
        property double minimumMargin: 2
        property var normal: QtObject {
            property color bgColor: "#282828"
            property color fgColor: "#eeeeee"
            property color borderColor: "#ffb80d"
            property int borderWidth: 0
            property int fontSize: 19
        }
        property var focus: QtObject {
            property color bgColor: "#cf0652"
            property color fgColor: "#ffffff"
            property color borderColor: "#ffb80d"
            property int borderWidth: 0
            property int fontSize: 19
        }
        property var select: QtObject {
            property color bgColor: "#bcbcbc"
            property color fgColor: "#282828"
            property color borderColor: "#cf0652"
            property int borderWidth: 4
            property int fontSize: 19
        }
        property var disable: QtObject {
            property color bgColor: "#4b4b4b"
            property color fgColor: "lightgray"
            property color borderColor: "#ffb80d"
            property int borderWidth: 0
            property int fontSize: 19
        }
    }

    property var predictionButton: QtObject {
        property var normal: QtObject {
            property color bgColor: "#eee"
            property color fgColor: "black"
            property color borderColor: "darkgray"
            property int borderWidth: 1
            property int fontSize: 19
        }
        property var focus: QtObject {
            property color bgColor: "#cf0652"
            property color fgColor: "#eeeeee"
            property color borderColor: "#cf0652"
            property int borderWidth: 0
            property int fontSize: 19
        }
        property var select: QtObject {
            property color bgColor: "#bcbcbc"
            property color fgColor: "#282828"
            property color borderColor: "#ff2f7d"
            property int borderWidth: 4
            property int fontSize: 19
        }
        property var disable: QtObject {
            property color bgColor: "transparent"
            property color fgColor: "transparent"
            property color borderColor: "transparent"
            property int borderWidth: 0
            property int fontSize: 19
        }
    }

    property var predictionBar: QtObject {
        property int leftMargin: 13
        property int bottomMargin: 13
        property int height: 35
        property int listWidth: 582
        property int spacing: 20
        property int btnWidth: 34
        property int spacebarMargin: 35
        property int cellWidth: 80
    }

    property var predictionBarButton: QtObject {
        property var normal: QtObject {
            property color bgColor: "transparent"
            property color fgColor: "#eeeeee"
            property color borderColor: "transparent"
            property int borderWidth: 0
            property int fontSize: 20
        }
        property var focus: QtObject {
            property color bgColor: "transparent"
            property color fgColor: "#cf0652"
            property color borderColor: "transparent"
            property int borderWidth: 0
            property int fontSize: 20
        }
        property var select: QtObject {
            property color bgColor: "transparent"
            property color fgColor: "#bcbcbc"
            property color borderColor: "transparent"
            property int borderWidth: 0
            property int fontSize: 20
        }
        property var disable: QtObject {
            property color bgColor: "transparent"
            property color fgColor: "transparent"
            property color borderColor: "transparent"
            property int borderWidth: 0
            property int fontSize: 20
        }
    }

    property var predictionMoreButton: QtObject {
        property var normal: QtObject {
            property color bgColor: "transparent"
            property color fgColor: "#eeeeee"
            property color borderColor: "transparent"
            property int borderWidth: 0
            property int fontSize: 20
        }
        property var focus: QtObject {
            property color bgColor: "#cf0652"
            property color fgColor: "#eeeeee"
            property color borderColor: "#cf0652"
            property int borderWidth: 0
            property int fontSize: 20
        }
        property var select: QtObject {
            property color bgColor: "#bcbcbc"
            property color fgColor: "#282828"
            property color borderColor: "#cf0652"
            property int borderWidth: 4
            property int fontSize: 20
        }
        property var disable: QtObject {
            property color bgColor: "transparent"
            property color fgColor: "transparent"
            property color borderColor: "transparent"
            property int borderWidth: 0
            property int fontSize: 20
        }
    }

    property var numberKeyboard: QtObject {
        property int width: 1280
        property int height: 76
        property int topMargin: 13
        property int bottomMargin: 13
        property int leftMargin: 13
        property int rightMargin: 13
        property int cellSpace: 4
        property int cellHeight: 50
        property int cellWidth: 90
        property int seperator: 13
        property int funcButtonWidth: 75
        property int enterButtonWidth: 128
    }

    property var numberButton: QtObject {
        property string fontFamily: _MuseoSans
        property int minimumPixelSize: 8
        property double minimumMargin: 2
        property var normal: QtObject {
            property color bgColor: "#282828"
            property color fgColor: "#eeeeee"
            property color borderColor: "#ffb80d"
            property int borderWidth: 0
            property int fontSize: 19
        }
        property var focus: QtObject {
            property color bgColor: "#cf0652"
            property color fgColor: "#ffffff"
            property color borderColor: "#ffb80d"
            property int borderWidth: 0
            property int fontSize: 19
        }
        property var select: QtObject {
            property color bgColor: "#bcbcbc"
            property color fgColor: "#282828"
            property color borderColor: "#cf0652"
            property int borderWidth: 4
            property int fontSize: 19
        }
        property var disable: QtObject {
            property color bgColor: "transparent"
            property color fgColor: "transparent"
            property color borderColor: "transparent"
            property int borderWidth: 0
            property int fontSize: 19
        }
    }

    property var numericEnterButton: QtObject {
        property string fontFamily: fontForMenuLocale
        property int minimumPixelSize: 8
        property double minimumMargin: 2
        property var normal: QtObject {
            property color bgColor: "#282828"
            property color fgColor: "#eeeeee"
            property color borderColor: "#ffb80d"
            property int borderWidth: 0
            property int fontSize: 19
        }
        property var focus: QtObject {
            property color bgColor: "#cf0652"
            property color fgColor: "#eeeeee"
            property color borderColor: "#ffb80d"
            property int borderWidth: 0
            property int fontSize: 19
        }
        property var select: QtObject {
            property color bgColor: "#bcbcbc"
            property color fgColor: "#282828"
            property color borderColor: "#cf0652"
            property int borderWidth: 4
            property int fontSize: 19
        }
        property var disable: QtObject {
            property color bgColor: "transparent"
            property color fgColor: "transparent"
            property color borderColor: "transparent"
            property int borderWidth: 0
            property int fontSize: 19
        }
    }

    function setDefaultFont(langCode) {
        root.defaultFontFamily = getFontForLanguage(langCode);
    }

    function setFontForMenuLocale(localeCode) {
        root.fontForMenuLocale = getFontForLanguage(localeCode);
    }

    function getFontForLanguage(langCode) {
        switch (langCode) {
        case "ja":
            return _LGDisplayJP;
        case "zh-Hant":
            return _LGDisplayHK;
        case "zh-Hans":
        case "ar":
        case "bg":
        case "cs":
        case "el":
        case "fa":
        case "he":
        case "kk":
        case "ko":
        case "ku":
        case "mk":
        case "mn":
        case "ru":
        case "th":
        case "uk":
        case "uz-Cyrl":
            return _LGDisplay;
        case "hi":
            return _LGIndia;
        case "km":
            return _NotoSansKhmer;
        default:
            return _MuseoSans;
        }
    }
}
