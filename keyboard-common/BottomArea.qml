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
import "commonvariables.js" as CommonVariables

Item {
    id: root
    signal sendKey(int keycode, bool shift, int eventType)
    signal ttsService(string text)

    /* Spacebar Button */
    ButtonBase {
        id: spaceButton
        objectName: "spaceButton"
        image: {
            if (style.keyboardDefaultWidth === 1920) {
                if (state == "Select") {
                    return "qrc:///images/spacebar-dark.png"
                } else {
                    return "qrc:///images/spacebar.png"
                }
            } else {
                if (state == "Select") {
                    return "qrc:///images-hd/spacebar-dark.png"
                } else {
                    return "qrc:///images-hd/spacebar.png"
                }
            }
        }

        onReleased: {
            sendKey(57, false, eventType);
        }
        onFocusChanged: if (focus) root.ttsService("Space")
        width: root.width
        height: root.height
    }

    onFocusChanged: focus ? spaceButton.focus = true : null

    Connections {
        target: PluginProxy
        onKeyReleased : {
            if (isReleased && (spaceButton.state === "Select"))
                spaceButton.state = "Focus";
        }
    }
}
