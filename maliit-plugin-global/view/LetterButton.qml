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

import "../keyboard-common"

ButtonBase {
    id: letterButton
    objectName: "letterButton"
    property string mode: "Normal"
    property variant keyData
    property string mainChar: (keyData && keyData.mainChar) ? keyData.mainChar : ""     /* display character */
    property string shiftedChar: (keyData && keyData.shiftedChar) ? keyData.shiftedChar : ""
    property string expandChar: (keyData && keyData.expandChar) ? keyData.expandChar : ""
    property string expandShiftedChar: (keyData && keyData.expandShiftedChar) ? keyData.expandShiftedChar : ""
    property string rawcode: (keyData && keyData.rawcode) ? keyData.rawcode : "-1"        /* code sening to engine */
    property string shiftRawcode: (keyData && keyData.shiftRawcode) ? keyData.shiftRawcode : "-1"
    property string expandRawcode: (keyData && keyData.expandRawcode) ? keyData.expandRawcode : "-1"
    property string expandShiftRawcode: (keyData && keyData.expandShiftRawcode) ? keyData.expandShiftRawcode : "-1"
    property string normalKeysym: (keyData && keyData.normalKeysym) ? keyData.normalKeysym : "-1"
    property string shiftKeysym: (keyData && keyData.shiftKeysym) ? keyData.shiftKeysym : "-1"
    property string expandKeysym: (keyData && keyData.expandKeysym) ? keyData.expandKeysym : "-1"
    property string expandShiftKeysym: (keyData && keyData.expandShiftKeysym) ? keyData.expandShiftKeysym : "-1"
    property bool forceText : (keyData && keyData.forceText) ? keyData.forceText : false
    signal sendKey(string rawcode, bool shift)
    signal sendKeysym(string keysym)
    signal sendText(string text)

    function updateState(text) {
        if (text.length === 0)
            state = "Disable";
        else if (state === "Disable")
            state = "Normal";
    }

    text: {
        if (mode === "Normal")
            mainChar
        else if (mode === "Normal-Shift" || mode === "Normal-Shift-Lock")
            shiftedChar
        else if (mode === "Expand")
            expandChar
        else if (mode === "Expand-Shift" || mode === "Expand-Shift-Lock")
            expandShiftedChar
        else
            ""
    }

    onTextChanged: updateState(text)
    Component.onCompleted: updateState(text)

    onReleased: {
        if (forceText) {
            sendText(text);
            return;
        }

        switch (mode) {
        case "Normal":
            if (normalKeysym !== "-1")
                sendKeysym(normalKeysym);
            else
                sendKey(rawcode, false);
            break;
        case "Normal-Shift":
            if (shiftKeysym !== "-1")
                sendKeysym(shiftKeysym);
            else
                sendKey(shiftRawcode, true);
            break;
        case "Normal-Shift-Lock":
            if (shiftKeysym !== "-1")
                sendKeysym(shiftKeysym);
            else
                sendKey(shiftRawcode, true);
            break;
        case "Expand":
            if (expandKeysym !== "-1")
                sendKeysym(expandKeysym);
            else
                sendKey(expandRawcode, false);
            break;
        case "Expand-Shift":
            if (expandShiftKeysym !== "-1")
                sendKeysym(expandShiftKeysym);
            else
                sendKey(expandRawcode, false);
            break;
        case "Expand-Shift-Lock":
            if (expandShiftKeysym !== "-1")
                sendKeysym(expandShiftKeysym);
            else
                sendKey(expandRawcode, false);
            break;
        case "Symbol":
            sendText(text);
            break;
        default:
            console.log("Error! mode is " + mode);
        }
    }

    Connections {
        target: PluginProxy
        onKeyReleased : {
            if (isReleased && (state === "Select"))
                state = "Focus";
        }
    }
}
