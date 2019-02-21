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
        property int cellWidth: 123
        property int arrowWidth: 60
    }

    property var component : QtObject {
        property int cellWidth: 68
    }

    property var suggestionButton : QtObject {
        property var normal: QtObject{
            property color bgColor: "transparent"
            property color fgColor: "#999999"
            property color borderColor: "transparent"
            property int borderWidth: 0
            property int fontSize: 30
        }
        property var focus : QtObject {
            property color bgColor: "#cf0652"
            property color fgColor: "#ffffff"
            property color borderColor: "#ffb80d"
            property int borderWidth: 0
            property int fontSize: 30
        }
        property var select : QtObject {
            property color bgColor: "transparent"
            property color fgColor: "#bcbcbc"
            property color borderColor: "transparent"
            property int borderWidth: 0
            property int fontSize: 30
        }
        property var disable : QtObject {
            property color bgColor: "transparent"
            property color fgColor: "transparent"
            property color borderColor: "transparent"
            property int borderWidth: 0
            property int fontSize: 30
        }
    }

    property var suggestionArrow : QtObject {
        property var normal : QtObject {
            property color bgColor: "transparent"
            property color fgColor: "#999999"
            property color borderColor: "transparent"
            property int borderWidth: 0
            property int fontSize: 30
        }
        property var focus : QtObject {
            property color bgColor: "#cf0652"
            property color fgColor: "#999999"
            property color borderColor: "#cf0652"
            property int borderWidth: 0
            property int fontSize: 30
        }
        property var select : QtObject {
            property color bgColor: "transparent"
            property color fgColor: "#bcbcbc"
            property color borderColor: "transparent"
            property int borderWidth: 0
            property int fontSize: 30
        }
        property var disable : QtObject {
            property color bgColor: "transparent"
            property color fgColor: "transparent"
            property color borderColor: "transparent"
            property int borderWidth: 0
            property int fontSize: 30
        }
    }

    property var componentButton : QtObject {
        property string fontFamily: "Museo"
        property int fontWeight: 75  // Font.Bold = 75
        property var normal : QtObject {
            property color bgColor: "transparent"
            property color fgColor: "#ffffff"
            property color borderColor: "transparent"
            property int borderWidth: 0
            property int fontSize: 30
        }
        property var focus : QtObject {
            property color bgColor: "#cf0652"
            property color fgColor: "#ffffff"
            property color borderColor: "#cf0652"
            property int borderWidth: 0
            property int fontSize: 30
        }
        property var select : QtObject {
            property color bgColor: "transparent"
            property color fgColor: "#bcbcbc"
            property color borderColor: "transparent"
            property int borderWidth: 0
            property int fontSize: 30
        }
        property var disable : QtObject {
            property color bgColor: "transparent"
            property color fgColor: "transparent"
            property color borderColor: "transparent"
            property int borderWidth: 0
            property int fontSize: 30
        }
    }

    property var preeditBox : QtObject {
        property int width: 174
        property int height: 70
        property int textMargin: 2
        property var normal : QtObject {
            property color bgColor: "#282828"
            property color fgColor: "#eeeeee"
            property color borderColor: "#ffb80d"
            property int borderWidth: 0
            property int fontSize: 30
        }
        property var focus : QtObject {
            property color bgColor: "#cf0652"
            property color fgColor: "#999999"
            property color borderColor: "#cf0652"
            property int borderWidth: 0
            property int fontSize: 30
        }
        property var select : QtObject {
            property color bgColor: "#bcbcbc"
            property color fgColor: "#282828"
            property color borderColor: "#cf0652"
            property int borderWidth: 0
            property int fontSize: 30
        }
        property var disable : QtObject {
            property color bgColor: "#383838"
            property color fgColor: "#282828"
            property color borderColor: "transparent"
            property int borderWidth: 0
            property int fontSize: 30
        }
    }

    property var hidSuggestion : QtObject {
        property int height: 100
        property int leftMargin: 20
        property int rightMargin: 20
        property int bottomMargin: 20
        property int topMargin: 20
        property int cellHeight: 60
        property int cellWidth: 86
        property int cellSpace: 6
        property int moreWidth: 86
    }

    property var hidSuggestionButton : QtObject {
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
        property var focus : QtObject {
            property color bgColor: "#cf0652"
            property color fgColor: "#eeeeee"
            property color subtitleColor: "#808080"
            property color borderColor: "#ffb80d"
            property int borderWidth: 0
            property int fontSize: 28
            property int subtitleSize: 20
        }
        property var select : QtObject {
            property color bgColor: "#bcbcbc"
            property color fgColor: "#282828"
            property color subtitleColor: "#808080"
            property color borderColor: "#cf0652"
            property int borderWidth: 6
            property int fontSize: 28
            property int subtitleSize: 20
        }
        property var disable : QtObject {
            property color bgColor: "#383838"
            property color fgColor: "#282828"
            property color subtitleColor: "#282828"
            property int borderWidth: 0
        }
    }
}
