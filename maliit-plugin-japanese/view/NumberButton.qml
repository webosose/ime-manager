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
    id: numberButton
    objectName: "numberButton"
    property string mainChar
    property string symbolChar
    signal textKeyPressed(string text)

    buttonStyle: commonStyle.numberButton
    text: getCurrentText()

    onReleased: {
        textKeyPressed(text);
    }

    function getCurrentText() {
        var t;

        switch (numberKeyboard.mode) {
        case "Normal":
            t = mainChar;
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
            if (isReleased && (numberButton.state === "Select"))
                numberButton.state = "Focus";
        }
    }
}
