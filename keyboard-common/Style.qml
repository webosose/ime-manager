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

// standard in FHD, UHD
QtObject {
    id: root

    readonly property string _MuseoSans: "Museo SansNormal"
    readonly property string _LGDisplay: "LG Display-Regular"
    readonly property string _LGDisplayHK: "LG Display_HK-Regular"
    readonly property string _LGDisplayJP: "LG Display_JP"
    readonly property string _LGIndia: "LGIndia"
    readonly property string _NotoSansKhmer: "Noto Sans Khmer"

    property color bgColor: "#4b4b4b"
    property string defaultFontFamily: _MuseoSans
    property string fontForMenuLocale: _MuseoSans

    property string webosVariant: "standard"
    property int keyboardDefaultWidth: 1920
    property int keyboardDefaultHeight: 324

    property var left: QtObject {
        property int width: 174
        property int height: 226
        property int topMargin: 20
        property int leftMargin: 20
        property int cellWidth: 174
        property int cellHeight: 52 //60 is original. 52 is the tuned value
        property int cellSpace: 6
        property int fontSize: 28
    }

    property var right: QtObject {
        property int width: 192
        property int height: 284
        property int leftMargin: 20
        property int rightMargin: 20
        property int topMargin: 20
        property int cellHeight: 52 //60 is original value. 52 is the tuned value
        property int cellSpace: 6
    }

    property var middle: QtObject {
        property int width: 1474
        property int height: 226
        property int topMargin: 20
        property int leftMargin: 20
        property int cellHeight: 52
        property int cellSpace: 6
    }

    property var bottom: QtObject {
        property int width: 1668
        property int height: 52
        property int topMargin: 6
        property int leftMargin: 20
        property int rightMargin: 20
        property int bottomMargin: 20
        property int cellSpace: 6
        property int hideBtnWidth: 157
    }

    property var button: QtObject {
        property string fontFamily: defaultFontFamily
        property int minimumPixelSize: 12
        property double minimumMargin: 2
        property var normal: QtObject {
            property color bgColor: "#282828"
            property color fgColor: "#eeeeee"
            property color borderColor: "#ffb80d"
            property int borderWidth: 0
            property int fontSize: 28
        }
        property var focus: QtObject {
            property color bgColor: "#cf0652"
            property color fgColor: "#eeeeee"
            property color borderColor: "#ffb80d"
            property int borderWidth: 0
            property int fontSize: 28
        }
        property var select: QtObject {
            property color bgColor: "#bcbcbc"
            property color fgColor: "#282828"
            property color borderColor: "#cf0652"
            property int borderWidth: 6
            property int fontSize: 28
        }
        property var disable: QtObject {
            property color bgColor: "transparent"
            property color fgColor: "transparent"
            property color borderColor: "transparent"
            property int borderWidth: 0
            property int fontSize: 28
        }
        property var lockedNormal: QtObject {
            property color bgColor: "#282828"
            property color borderColor: "#bcbcbc"
            property int borderWidth: 6
        }
        property var lockedFocus: QtObject {
            property color bgColor: "#cf0652"
            property color borderColor: "#bcbcbc"
            property int borderWidth: 6
        }
        property var lockedSelect: QtObject {
            property color bgColor: "#bcbcbc"
            property color borderColor: "#cf0652"
            property int borderWidth: 6
        }
    }

    property var symbolButton: QtObject {
        property string fontFamily: _LGDisplay
        property int minimumPixelSize: 12
        property double minimumMargin: 2
        property var normal: QtObject {
            property color bgColor: "#282828"
            property color fgColor: "#eeeeee"
            property color borderColor: "#ffb80d"
            property int borderWidth: 0
            property int fontSize: 28
        }
        property var focus: QtObject {
            property color bgColor: "#cf0652"
            property color fgColor: "#eeeeee"
            property color borderColor: "#ffb80d"
            property int borderWidth: 0
            property int fontSize: 28
        }
        property var select: QtObject {
            property color bgColor: "#bcbcbc"
            property color fgColor: "#282828"
            property color borderColor: "#cf0652"
            property int borderWidth: 6
            property int fontSize: 28
        }
        property var disable: QtObject {
            property color bgColor: "transparent"
            property color fgColor: "transparent"
            property color borderColor: "transparent"
            property int borderWidth: 0
            property int fontSize: 28
        }
        property var lockedNormal: QtObject {
            property color bgColor: "#282828"
            property color borderColor: "#bcbcbc"
            property int borderWidth: 6
        }
        property var lockedFocus: QtObject {
            property color bgColor: "#cf0652"
            property color borderColor: "#bcbcbc"
            property int borderWidth: 6
        }
        property var lockedSelect: QtObject {
            property color bgColor: "#bcbcbc"
            property color borderColor: "#cf0652"
            property int borderWidth: 6
        }
    }

    property var languageButton: QtObject {
        property string fontFamily: defaultFontFamily
        property int minimumPixelSize: 12
        property double minimumMargin: 2
        property var normal: QtObject {
            property color bgColor: "#282828"
            property color fgColor: "#eeeeee"
            property color borderColor: "#ffb80d"
            property int borderWidth: 0
            property int fontSize: 28
        }
        property var focus: QtObject {
            property color bgColor: "#cf0652"
            property color fgColor: "#eeeeee"
            property color borderColor: "#ffb80d"
            property int borderWidth: 0
            property int fontSize: 28
        }
        property var select: QtObject {
            property color bgColor: "#bcbcbc"
            property color fgColor: "#282828"
            property color borderColor: "#cf0652"
            property int borderWidth: 6
            property int fontSize: 28
        }
        property var disable: QtObject {
            property color bgColor: "#4b4b4b"
            property color fgColor: "lightgray"
            property color borderColor: "#ffb80d"
            property int borderWidth: 0
            property int fontSize: 28
        }
    }

    property var predictionButton: QtObject {
        property var normal: QtObject {
            property color bgColor: "#eee"
            property color fgColor: "black"
            property color borderColor: "darkgray"
            property int borderWidth: 1
            property int fontSize: 28
        }
        property var focus: QtObject {
            property color bgColor: "#cf0652"
            property color fgColor: "#eee"
            property color borderColor: "#cf0652"
            property int borderWidth: 0
            property int fontSize: 28
        }
        property var select: QtObject {
            property color bgColor: "#bcbcbc"
            property color fgColor: "#282828"
            property color borderColor: "#cf0652"
            property int borderWidth: 6
            property int fontSize: 28
        }
        property var disable: QtObject {
            property color bgColor: "transparent"
            property color fgColor: "transparent"
            property color borderColor: "transparent"
            property int borderWidth: 0
            property int fontSize: 28
        }
    }

    property var predictionBar: QtObject {
        property int leftMargin: 20
        property int bottomMargin: 60
        property int height: 52
        property int listWidth: 800
        property int spacing: 30
        property int btnWidth: 52
        property int spacebarMargin: 60
        property int cellWidth: 120
    }

    property var predictionBarButton: QtObject {
        property var normal: QtObject {
            property color bgColor: "transparent"
            property color fgColor: "#eee"
            property color borderColor: "transparent"
            property int borderWidth: 0
            property int fontSize: 30
        }
        property var focus: QtObject {
            property color bgColor: "transparent"
            property color fgColor: "#cf0652"
            property color borderColor: "transparent"
            property int borderWidth: 0
            property int fontSize: 30
        }
        property var select: QtObject {
            property color bgColor: "transparent"
            property color fgColor: "#bcbcbc"
            property color borderColor: "transparent"
            property int borderWidth: 0
            property int fontSize: 30
        }
        property var disable: QtObject {
            property color bgColor: "transparent"
            property color fgColor: "transparent"
            property color borderColor: "transparent"
            property int borderWidth: 0
            property int fontSize: 30
        }
    }

    property var predictionMoreButton: QtObject {
        property var normal: QtObject {
            property color bgColor: "transparent"
            property color fgColor: "#eee"
            property color borderColor: "transparent"
            property int borderWidth: 0
            property int fontSize: 30
        }
        property var focus: QtObject {
            property color bgColor: "#cf0652"
            property color fgColor: "#eee"
            property color borderColor: "#cf0652"
            property int borderWidth: 0
            property int fontSize: 30
        }
        property var select: QtObject {
            property color bgColor: "#bcbcbc"
            property color fgColor: "#282828"
            property color borderColor: "#cf0652"
            property int borderWidth: 6
            property int fontSize: 30
        }
        property var disable: QtObject {
            property color bgColor: "transparent"
            property color fgColor: "transparent"
            property color borderColor: "transparent"
            property int borderWidth: 0
            property int fontSize: 30
        }
    }

    property var numberKeyboard: QtObject {
        property int width: 1920
        property int height: 100
        property int topMargin: 20
        property int bottomMargin: 20
        property int leftMargin: 20
        property int rightMargin: 20
        property int cellSpace: 6
        property int cellHeight: 60
        property int cellWidth: 136
        property int seperator: 20
        property int funcButtonWidth: 109
        property int enterButtonWidth: 192
    }

    property var numberButton: QtObject {
        property string fontFamily: _MuseoSans
        property int minimumPixelSize: 12
        property double minimumMargin: 2
        property var normal: QtObject {
            property color bgColor: "#282828"
            property color fgColor: "#eeeeee"
            property color borderColor: "#ffb80d"
            property int borderWidth: 0
            property int fontSize: 28
        }
        property var focus: QtObject {
            property color bgColor: "#cf0652"
            property color fgColor: "#eeeeee"
            property color borderColor: "#ffb80d"
            property int borderWidth: 0
            property int fontSize: 28
        }
        property var select: QtObject {
            property color bgColor: "#bcbcbc"
            property color fgColor: "#282828"
            property color borderColor: "#cf0652"
            property int borderWidth: 6
            property int fontSize: 28
        }
        property var disable: QtObject {
            property color bgColor: "transparent"
            property color fgColor: "transparent"
            property color borderColor: "transparent"
            property int borderWidth: 0
            property int fontSize: 28
        }
    }

    property var numericEnterButton: QtObject {
        property string fontFamily: fontForMenuLocale
        property int minimumPixelSize: 12
        property double minimumMargin: 2
        property var normal: QtObject {
            property color bgColor: "#282828"
            property color fgColor: "#eeeeee"
            property color borderColor: "#ffb80d"
            property int borderWidth: 0
            property int fontSize: 28
        }
        property var focus: QtObject {
            property color bgColor: "#cf0652"
            property color fgColor: "#eeeeee"
            property color borderColor: "#ffb80d"
            property int borderWidth: 0
            property int fontSize: 28
        }
        property var select: QtObject {
            property color bgColor: "#bcbcbc"
            property color fgColor: "#282828"
            property color borderColor: "#cf0652"
            property int borderWidth: 6
            property int fontSize: 28
        }
        property var disable: QtObject {
            property color bgColor: "transparent"
            property color fgColor: "transparent"
            property color borderColor: "transparent"
            property int borderWidth: 0
            property int fontSize: 28
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
