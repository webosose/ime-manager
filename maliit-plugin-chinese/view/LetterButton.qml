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
import "../keyboard-common"

ButtonBase {
    id: letterButton
    objectName: "letterButton"
    property string mode: "Normal"
    property string mainChar    /* display character */
    property string shiftedChar
    property string symbolChar
    property string rawcode        /* code sening to engine */
    property string shiftRawcode
    signal sendKey(string rawcode, bool shift)
    signal sendText(string text)

    function checkState(text) {
        return (text.length > 0) ? "Normal" : "Disable";
    }

    text: getCurrentText(mode)
    state: checkState(text)
    onTextChanged: state = checkState(text)

    onReleased: {
        switch (mode) {
        case "Normal":
            sendKey(rawcode, false);
            break;
        case "Normal-Shift":
            sendKey(shiftRawcode, true);
            break;
        case "Symbol":
            sendText(text);
            break;
        default:
            console.warn("Error! main.mode is " + main.mode);
        }
    }

    function getCurrentText(mode) {
        var t;

        switch (mode) {
        case "Normal":
            t = mainChar;
            break;
        case "Normal-Shift":
            t = shiftedChar;
            break;
        case "Symbol":
            t = symbolChar;
            break;
        default:
            t = "";
        }

        return (t !== undefined) ? t : "";
    }

    Connections {
        target: PluginProxy
        onKeyReleased : {
            if (isReleased && (letterButton.state === "Select"))
                letterButton.state = "Focus";
        }
    }
}
