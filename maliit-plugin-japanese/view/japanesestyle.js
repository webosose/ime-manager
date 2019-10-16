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

var windowHeight = 384;
var windowHeightKatakanaAndEnglish = 324;
var JapaneseMiddleHeight = 284;
var HiraganaKatakanaColumns = 14;
var EnglishColumns = 10;
var SymbolColumns = 12;
var HiraganaKatakanaRows = 5;
var SymbolEnglishRows = 4;
var windowWidth = 1920;
var NextAndPreviousButtonHeight = 60;
var HiraganaKatakanaLeftRightMargin = 18;
var HiraganaKatakanaCellWidth = 100;
var ConvertButtonWidth = 206;

var hidPrediction = {
    height: 100,
    leftMargin: 20,
    rightMargin: 20,
    topMargin: 20,
    bottomMargin: 20,
    cellHeight: 60,
    cellWidth: 167,
    cellSpace: 6,
    cellCount: 10,
    moreWidth: 72,
    length: 9,
    maxLength: 12,
    indicatorWidth: 150
};

var hidPredictionBottomMargin = 20;

var hidPredictionButton = {
    fontFamily: "LG Display_JP",
    normal: {
        bgColor: "#282828",
        fgColor: "#eeeeee",
        subtitleColor: "#808080",
        borderColor: "#ffb80d",
        borderWidth: 0,
        fontSize: 28,
        subtitleSize: 20
    },
    focus: {
        bgColor: "#ff2f7d",
        fgColor: "#eeeeee",
        subtitleColor: "#808080",
        borderColor: "#ffb80d",
        borderWidth: 0,
        fontSize: 28,
        subtitleSize: 20
    },
    select: {
        bgColor: "#bcbcbc",
        fgColor: "#282828",
        subtitleColor: "#808080",
        borderColor: "#ff2f7d",
        borderWidth: 6,
        fontSize: 28,
        subtitleSize: 20
    },
    disable: {
        bgColor: "#383838",
        fgColor: "#282828",
        subtitleColor: "#282828",
        borderWidth: 0
    }
};

var button = {
    unavailable: {
        bgColor: "#383838",
        fgColor: "#282828"
    }
};
