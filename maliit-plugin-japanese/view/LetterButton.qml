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

ButtonBase {
    id: letterButton
    objectName: "letterButton"
    property string mode: "Hiragana"
    property string hiraganaChar    /* display character */
    property string katakanaChar
    property string fullWidthEnglishLowercaseChar
    property string fullWidthEnglishUppercaseChar
    property string symbolChar
    property string hiraganaRawcode        /* code sening to engine */
    property string katakanaRawcode
    property string fullWidthEnglishLowercaseRawcode
    property string fullWidthEnglishUppercaseRawcode
    property string symbolRawcode
    signal sendKey(string rawcode, bool shift, int eventType)

    text: getCurrentText()
    state: (text.length > 0) ? "Normal" : "Disable"

    onReleased: {
        switch (mode) {
        case "Hiragana":
            sendKey(hiraganaRawcode, false, eventType);
            break;
        case "Katakana":
            sendKey(katakanaRawcode, false, eventType);
            break;
        case "FullWidth-English":
            sendKey(fullWidthEnglishLowercaseRawcode, false, eventType);
            break;
        case "FullWidth-English-Shift":
        case "FullWidth-English-Shift-Lock":
            sendKey(fullWidthEnglishUppercaseRawcode, false, eventType);
            break;
        case "Symbol":
            sendKey(symbolRawcode, false, eventType);
        }
    }

    function getCurrentText() {
        var t;

        switch (mode) {
        case "Hiragana":
            t = hiraganaChar;
            break;
        case "Katakana":
            t = katakanaChar;
            break;
        case "FullWidth-English":
            t = fullWidthEnglishLowercaseChar;
            break;
        case "FullWidth-English-Shift":
        case "FullWidth-English-Shift-Lock":
            t = fullWidthEnglishUppercaseChar;
            break;
        case "Symbol":
            t = symbolChar;
            break;
        default:
            t = "";
        }

        return (t !== undefined) ? t : "";
    }
}
