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

    property string currLanguage: "English"
    property string languageLabel: "ENG"
    property bool supportShiftMode: true
    property bool supportExpandMode: false
    property bool supportExpandShiftMode: false
    property bool supportPageButton: false
    property bool activateLanguageButton: false
    property int rowIndex: 0

    signal ttsService(string text)
    signal clickLanguageButton()
    signal meetLeftBoundary(int row)
    signal meetRightBoundary(int row)
    signal meetTopBoundary(int column)
    signal meetBottomBoundary(int column)

    function setToDefault() {
        shiftButton.locked = false;
        if (shiftButton.state === "Disable")
            return;
        else if (shiftButton.focus)
            shiftButton.state = "Focus"
        else
            shiftButton.state = "Normal";
    }

    function setKeyNavigation(row) {
        if (row === 0 && languageChangeButton.state !== "Disable")
            languageChangeButton.focus = true;
        else if (row === 0 && languageChangeButton.state === "Disable")
            symbolButton.focus = true;
        else if (row === 1)
            symbolButton.focus = true;
        else if (row === 2 && accentButton.state !== "Disable")
            accentButton.focus = true;
        else if (row === 2 && accentButton.state === "Disable")
            symbolButton.focus = true;
        else if (row === 3 && shiftButton.state !== "Disable")
            shiftButton.focus = true;
        else if (row === 3 && shiftButton.state === "Disable" && accentButton.state !== "Disable")
            accentButton.focus = true;
        else if (row === 3 && shiftButton.state === "Disable" && accentButton.state === "Disable")
            symbolButton.focus = true;
    }

    state: "Normal"
    onStateChanged: {
        if ((state === "Expand" && !supportExpandShiftMode) || (state === "Symbol")) shiftButton.state = "Disable";
        else if (supportShiftMode && shiftButton.focus) shiftButton.state = "Focus";
        else if (supportShiftMode && !shiftButton.focus) shiftButton.state = "Normal";
    }
    onSupportExpandModeChanged: accentButton.state = supportExpandMode ? "Normal" : "Disable"
    onSupportShiftModeChanged: shiftButton.state = supportShiftMode ? "Normal" : "Disable"

    Keys.onPressed: {
        if (event.key === Qt.Key_Up) {
            meetTopBoundary(0);
            event.accepted = true;
        } else if (event.key === Qt.Key_Down) {
            meetBottomBoundary(-1); //focus to the first column of the bottom region
            event.accepted = true;
        } else if (event.key === Qt.Key_Left) {
            meetLeftBoundary(rowIndex);
            event.accepted = true;
        } else if (event.key === Qt.Key_Right) {
            meetRightBoundary(rowIndex);
            event.accepted = true;
        }
    }

    Column {
        spacing: style.left.cellSpace
        property bool activateLanguageButton : root.activateLanguageButton
        onActivateLanguageButtonChanged: {
            languageChangeButton.state = activateLanguageButton ? "Normal" : "Disable";
        }
        /* Language Button */
        ButtonBase {
            id: languageChangeButton
            state: activateLanguageButton ? "Normal" : "Disable"
            objectName: "languageChangeButton"
            property string ttsString: qsTr("Change Language") + (PluginProxy.emptyString !== undefined ? PluginProxy.emptyString : "")
            property int row: 0

            buttonStyle: style.languageButton
            text: (languageLabel !== undefined && languageLabel !== "") ? languageLabel : currLanguage
            width: root.width
            height: style.left.cellHeight
            fontSizeMode: Text.Fit
            allowRepeat: false

            onReleased: {
                shiftButton.state = "Normal";
                clickLanguageButton();
            }

            onTtsService: {
                root.ttsService(ttsString + " " + globalStringModel.getStringLangCode(langCode));
            }

            onStateChanged: if (state === "Focus") rowIndex = row
            KeyNavigation.down: symbolButton
        }

        /* Symbol Button */
        ButtonBase {
            id: symbolButton
            objectName: "symbolButton"

            property int row: 1
            property string ttsStringSymbol: qsTr("Text to Symbols") + (PluginProxy.emptyString !== undefined ? PluginProxy.emptyString : "")
            property string ttsStringText: qsTr("Symbols to Text") + (PluginProxy.emptyString !== undefined ? PluginProxy.emptyString : "")

            text: (root.state === "Symbol") ? qsTr("ABC") + (PluginProxy.emptyString !== undefined ? PluginProxy.emptyString : "")
                                            : "+ = [ ]"
            fontfamily: (root.state === "Symbol") ? "" : style._LGDisplay
            width: root.width
            height: style.left.cellHeight
            allowRepeat: false
            onReleased: {
                switch (root.state) {
                case "Normal":
                case "Normal-Shift":
                case "Normal-Shift-Lock":
                case "Expand":
                case "Expand-Shift":
                case "Expand-Shift-Lock":
                    root.state = "Symbol";
                    break;
                case "Symbol":
                    root.state = "Normal";
                    break;
                default:
                    break;
                }
                shiftButton.locked = false;
                if (focus && root.state === "Normal" || root.state === "Expand" || root.state === "Normal-Shift" || root.state === "Normal-Shift-Lock")
                    root.ttsService(ttsStringSymbol)
                else if (focus && root.state === "Symbol")
                    root.ttsService(ttsStringText)
            }
            onTtsService: {
                if (root.state === "Normal" || root.state === "Expand" || root.state === "Normal-Shift" || root.state === "Normal-Shift-Lock")
                    root.ttsService(ttsStringSymbol)
                else if (root.state === "Symbol")
                    root.ttsService(ttsStringText)
            }
            onStateChanged: if (state === "Focus") rowIndex = row
            KeyNavigation.up: languageChangeButton
            Keys.onPressed: {
                if (event.key === Qt.Key_Down) {
                    if (accentButton.state === "Disable") {
                        if (shiftButton.state === "Disable") {
                            meetBottomBoundary(-1);
                        } else {
                            shiftButton.focus = true;
                        }
                    } else {
                        accentButton.focus = true;
                    }
                    event.accepted = true;
                }
            }
        }

        /* Accent Button */
        ButtonBase {
            id: accentButton
            objectName: "accentButton"

            property int row: 2
            property string ttsStringUmlautOn: qsTr("Umlaut on") + (PluginProxy.emptyString !== undefined ? PluginProxy.emptyString : "")
            property string ttsStringUmlautOff: qsTr("Umlaut off") + (PluginProxy.emptyString !== undefined ? PluginProxy.emptyString : "")

            text: (root.state === "Expand" || root.state === "Expand-Shift" || root.state === "Expand-Shift-Lock") ? "ABC" : "Àà"
            width: root.width
            height: style.left.cellHeight
            state: supportExpandMode ? "Normal" : "Disable"
            allowRepeat: false
            onReleased: {
                switch (root.state) {
                case "Normal":
                case "Normal-Shift":
                case "Normal-Shift-Lock":
                    if (supportExpandMode)
                        root.state = "Expand";
                    break;
                case "Expand":
                case "Expand-Shift":
                case "Expand-Shift-Lock":
                    root.state = "Normal";
                    break;
                case "Symbol":
                    if (supportExpandMode)
                        root.state = "Expand";
                    break;
                default:
                    break;
                }
                shiftButton.locked = false;
                if (focus && root.state === "Symbol" || root.state === "Normal" || root.state === "Normal-Shift" || root.state === "Normal-Shift-Lock")
                    root.ttsService(ttsStringUmlautOn)
                else if (focus && root.state === "Expand")
                    root.ttsService(ttsStringUmlautOff)
            }
            onTtsService: {
                if (root.state === "Symbol" || root.state === "Normal" || root.state === "Normal-Shift" || root.state === "Normal-Shift-Lock")
                    root.ttsService(ttsStringUmlautOn)
                else if (root.state === "Expand")
                    root.ttsService(ttsStringUmlautOff)
            }
            onStateChanged: if (state === "Focus") rowIndex = row
            KeyNavigation.up: symbolButton

            Keys.onPressed: {
                if (event.key === Qt.Key_Down) {
                    if (shiftButton.state == "Disable") {
                        meetBottomBoundary(-1);
                    } else {
                        shiftButton.focus = true;
                    }
                    event.accepted = true;
                }
            }
        }

        /* Shift Button */
        ButtonBase {
            id: shiftButton
            objectName: "shiftButton"

            property int row: 3
            property url iconOff:  (style.keyboardDefaultWidth === 1920) ? "qrc:///images/shift.png" : "qrc:///images-hd/shift.png"
            property url iconDown: (style.keyboardDefaultWidth === 1920) ? "qrc:///images/shift-dark.png" : "qrc:///images-hd/shift-dark.png"
            property url iconOn:   (style.keyboardDefaultWidth === 1920) ? "qrc:///images/shift-on.png" : "qrc:///images-hd/shift-on.png"
            property url iconOnFocus: (style.keyboardDefaultWidth === 1920) ? "qrc:///images/shift-on-focused.png" : "qrc:///images-hd/shift-on-focused.png"
            property string ttsStringCaps: qsTr("Caps") + (PluginProxy.emptyString !== undefined ? PluginProxy.emptyString : "")
            property string ttsStringCapsLock: qsTr("Caps Lock") + (PluginProxy.emptyString !== undefined ? PluginProxy.emptyString : "")
            property string ttsStringOff: qsTr("off") + (PluginProxy.emptyString !== undefined ? PluginProxy.emptyString : "")
            property string ttsStringLowerCase: qsTr("Lower case") + (PluginProxy.emptyString !== undefined ? PluginProxy.emptyString : "")

            image : {
                if (supportPageButton)
                    return "";

                var icon = iconOff;
                switch (state) {
                case "":
                case "Normal":
                    if (root.state === "Normal-Shift" || root.state === "Expand-Shift" || root.state === "Normal-Shift-Lock" || root.state === "Expand-Shift-Lock")
                        icon = iconOn;
                    break;
                case "Focus":
                    if (root.state === "Normal-Shift" || root.state === "Expand-Shift" || root.state === "Normal-Shift-Lock" || root.state === "Expand-Shift-Lock")
                        icon = iconOnFocus;
                    break;
                case "Select":
                    icon = iconDown;
                    break;
                case "Disable":
                    icon = "";
                    break;
                default:
                    icon = iconOff;
                }
                return icon;
            }

            text: (!supportPageButton) ? "" : ((root.state === "Normal-Shift") ? "2/2" : "1/2")
            width: root.width
            height: style.left.cellHeight
            allowRepeat: false
            onReleased: {
                if (!supportShiftMode)
                    return;

                switch (root.state) {
                case "Normal":
                    root.state = "Normal-Shift";
                    break;
                case "Normal-Shift":
                    if (supportPageButton) {
                        root.state = "Normal";
                    }
                    else {
                        root.state = "Normal-Shift-Lock";
                        shiftButton.locked = true;
                    }
                    break;
                case "Normal-Shift-Lock":
                    root.state = "Normal";
                    shiftButton.locked = false;
                    break;
                case "Expand":
                    if (supportExpandShiftMode)
                        root.state = "Expand-Shift";
                    break;
                case "Expand-Shift":
                    root.state = "Expand-Shift-Lock";
                    shiftButton.locked = true;
                    break;
                case "Expand-Shift-Lock":
                    root.state = "Expand";
                    shiftButton.locked = false;
                    break;
                case "Symbol":
                default:
                    break;
                }
                if (focus && root.state === "Normal")
                    root.ttsService(ttsStringCaps)
                else if (focus && root.state === "Normal-Shift")
                    root.ttsService(ttsStringCapsLock)
                else if (focus && root.state === "Normal-Shift-Lock")
                    root.ttsService(ttsStringCapsLock + " " + ttsStringOff)
            }
            onTtsService: {
                if (root.state === "Normal")
                    root.ttsService(ttsStringCaps)
                else if (root.state === "Normal-Shift")
                    root.ttsService(ttsStringCapsLock)
                else if (root.state === "Normal-Shift-Lock")
                    root.ttsService(ttsStringCapsLock + " " + ttsStringOff)
            }
            onStateChanged: if (state === "Focus") rowIndex = row
            KeyNavigation.up: (accentButton.state !== "Disable") ? accentButton : symbolButton
        }
    }

    states: [
        State { name: "Normal"; StateChangeScript { script: setToDefault() } },
        State { name: "Normal-Shift" },
        State { name: "Normal-Shift-Lock" },
        State { name: "Expand" },
        State { name: "Expand-Shift" },
        State { name: "Expand-Shift-Lock" },
        State { name: "Symbol" }
    ]

    Connections {
        target: PluginProxy
        onKeyReleased : {
            if (isReleased && (languageChangeButton.state === "Select"))
                languageChangeButton.state = "Focus";
            else if (isReleased && (symbolButton.state === "Select"))
                symbolButton.state = "Focus";
            else if (isReleased && (accentButton.state === "Select"))
                accentButton.state = "Focus";
            else if (isReleased && (shiftButton.state === "Select"))
                shiftButton.state = "Focus";
        }
    }
}
