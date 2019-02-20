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

QtObject {
    id: root

    property var suggestion : QtObject {
        property int cellWidth: 63
        property int arrowWidth: 40
    }

    property var component : QtObject {
        property int cellWidth: 46
    }

    property var suggestionButton : QtObject {
        property var normal: QtObject{
            property color bgColor: "transparent"
            property color fgColor: "#999999"
            property color borderColor: "transparent"
            property int borderWidth: 0
            property int fontSize: 20
        }
        property var focus : QtObject {
            property color bgColor: "#cf0652"
            property color fgColor: "#ffffff"
            property color borderColor: "#ffb80d"
            property int borderWidth: 0
            property int fontSize: 20
        }
        property var select : QtObject {
            property color bgColor: "transparent"
            property color fgColor: "#bcbcbc"
            property color borderColor: "transparent"
            property int borderWidth: 0
            property int fontSize: 20
        }
        property var disable : QtObject {
            property color bgColor: "transparent"
            property color fgColor: "transparent"
            property color borderColor: "transparent"
            property int borderWidth: 0
            property int fontSize: 20
        }
    }

    property var suggestionArrow : QtObject {
        property var normal : QtObject {
            property color bgColor: "transparent"
            property color fgColor: "#999999"
            property color borderColor: "transparent"
            property int borderWidth: 0
            property int fontSize: 20
        }
        property var focus : QtObject {
            property color bgColor: "#cf0652"
            property color fgColor: "#999999"
            property color borderColor: "#cf0652"
            property int borderWidth: 0
            property int fontSize: 20
        }
        property var select : QtObject {
            property color bgColor: "transparent"
            property color fgColor: "#bcbcbc"
            property color borderColor: "transparent"
            property int borderWidth: 0
            property int fontSize: 20
        }
        property var disable : QtObject {
            property color bgColor: "transparent"
            property color fgColor: "transparent"
            property color borderColor: "transparent"
            property int borderWidth: 0
            property int fontSize: 20
        }
    }

    property var componentButton : QtObject {
        property string fontFamily: "Museo SansBlack"
        property int fontWeight: 50
        property var normal : QtObject {
            property color bgColor: "transparent"
            property color fgColor: "#ffffff"
            property color borderColor: "transparent"
            property int borderWidth: 0
            property int fontSize: 20
        }
        property var focus : QtObject {
            property color bgColor: "#cf0652"
            property color fgColor: "#ffffff"
            property color borderColor: "#cf0652"
            property int borderWidth: 0
            property int fontSize: 20
        }
        property var select : QtObject {
            property color bgColor: "transparent"
            property color fgColor: "#bcbcbc"
            property color borderColor: "transparent"
            property int borderWidth: 0
            property int fontSize: 20
        }
        property var disable : QtObject {
            property color bgColor: "transparent"
            property color fgColor: "transparent"
            property color borderColor: "transparent"
            property int borderWidth: 0
            property int fontSize: 20
        }
    }

    property var preeditBox : QtObject {
        property int width: 114
        property int height: 40
        property int textMargin: 2
        property var normal : QtObject {
            property color bgColor: "#282828"
            property color fgColor: "#eeeeee"
            property color borderColor: "#ffb80d"
            property int borderWidth: 0
            property int fontSize: 20
        }
        property var focus : QtObject {
            property color bgColor: "#cf0652"
            property color fgColor: "#999999"
            property color borderColor: "#cf0652"
            property int borderWidth: 0
            property int fontSize: 20
        }
        property var select : QtObject {
            property color bgColor: "#bcbcbc"
            property color fgColor: "#282828"
            property color borderColor: "#cf0652"
            property int borderWidth: 0
            property int fontSize: 20
        }
        property var disable : QtObject {
            property color bgColor: "#383838"
            property color fgColor: "#282828"
            property color borderColor: "transparent"
            property int borderWidth: 0
            property int fontSize: 20
        }
    }

    property var hidSuggestion : QtObject {
        property int height: 77
        property int leftMargin: 13
        property int rightMargin: 13
        property int bottomMargin: 13
        property int topMargin: 13
        property int cellHeight: 50
        property int cellWidth: 58
        property int cellSpace: 4
        property int moreWidth: 58
    }

    property var hidSuggestionButton : QtObject {
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
        property var focus : QtObject {
            property color bgColor: "#cf0652"
            property color fgColor: "#eeeeee"
            property color subtitleColor: "#808080"
            property color borderColor: "#ffb80d"
            property int borderWidth: 0
            property int fontSize: 18
            property int subtitleSize: 14
        }
        property var select : QtObject {
            property color bgColor: "#bcbcbc"
            property color fgColor: "#282828"
            property color subtitleColor: "#808080"
            property color borderColor: "#cf0652"
            property int borderWidth: 4
            property int fontSize: 18
            property int subtitleSize: 14
        }
        property var disable : QtObject {
            property color bgColor: "#383838"
            property color fgColor: "#282828"
            property color subtitleColor: "#282828"
            property int borderWidth: 0
        }
    }
}
