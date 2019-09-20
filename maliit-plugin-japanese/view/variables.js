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

var numbers = [
            "1", "2", "3", "4", "5", "6", "7", "8", "9", "0"
];

var numberSymbols = [
            ".", ",", "/", "#", "-", "+", "%", "(", ")", "*"
];

var HiraganaChars = [
            "あ", "か", "さ", "た", "な", "は", "ま", "や", "ら", "わ", "ぁ", "ゃ", "ー", "⊔",
            "い", "き", "し", "ち", "に", "ひ", "み", "ゆ", "り", "を", "ぃ", "ゅ", "「", "＠",
            "う", "く", "す", "つ", "ぬ", "ふ", "む", "よ", "る", "ん", "ぅ", "ょ", "」", "？",
            "え", "け", "せ", "て", "ね", "へ", "め", "゛", "れ", "、", "ぇ", "っ", "，", "．",
            "お", "こ", "そ", "と", "の", "ほ", "も", "゜", "ろ", "。", "ぉ", "ゎ", "", ""
]; // 14*5

var HiraganaRawcode = [
            "0xE38182", "0xE3818B", "0xE38195", "0xE3819F", "0xE381AA", "0xE381AF", "0xE381BE", "0xE38284", "0xE38289", "0xE3828F", "0xE38181", "0xE38283", "0xE383BC", "0xE38080",
            "0xE38184", "0xE3818D", "0xE38197", "0xE381A1", "0xE381AB", "0xE381B2", "0xE381BF", "0xE38286", "0xE3828A", "0xE38292", "0xE38183", "0xE38285", "0xE3808C", "0xEFBCA0",
            "0xE38186", "0xE3818F", "0xE38199", "0xE381A4", "0xE381AC", "0xE381B5", "0xE38280", "0xE38288", "0xE3828B", "0xE38293", "0xE38185", "0xE38287", "0xE3808D", "0xEFBC9F",
            "0xE38188", "0xE38191", "0xE3819B", "0xE381A6", "0xE381AD", "0xE381B8", "0xE38281", "0xE3829B", "0xE3828C", "0xE38081", "0xE38187", "0xE381A3", "0xEFBC8C", "0xEFBC8E",
            "0xE3818A", "0xE38193", "0xE3819D", "0xE381A8", "0xE381AE", "0xE381BB", "0xE38282", "0xE3829C", "0xE3828D", "0xE38082", "0xE38189", "0xE3828E", "", ""
]; // 14*5

var KatakanaChars = [
            "ア", "カ", "サ", "タ", "ナ", "ハ", "マ", "ヤ", "ラ", "ワ", "ァ", "ャ", "ー", "⊔",
            "イ", "キ", "シ", "チ", "ニ", "ヒ", "ミ", "ユ", "リ", "ヲ", "ィ", "ュ", "「", "＠",
            "ウ", "ク", "ス", "ツ", "ヌ", "フ", "ム", "ヨ", "ル", "ン", "ゥ", "ョ", "」", "？",
            "エ", "ケ", "セ", "テ", "ネ", "ヘ", "メ", "゛", "レ", "、", "ェ", "ッ", "，", "．",
            "オ", "コ", "ソ", "ト", "ノ", "ホ", "モ", "゜", "ロ", "。", "ォ", "ヮ",
]; // 14*5

var KatakanaRawcode = [
            "0xE382A2", "0xE382AB", "0xE382B5", "0xE382BF", "0xE3838A", "0xE3838F", "0xE3839E", "0xE383A4", "0xE383A9", "0xE383AF", "0xE382A1", "0xE383A3", "0xE383BC", "0xE38080",
            "0xE382A4", "0xE382AD", "0xE382B7", "0xE38381", "0xE3838B", "0xE38392", "0xE3839F", "0xE383A6", "0xE383AA", "0xE383B2", "0xE382A3", "0xE383A5", "0xE3808C", "0xEFBCA0",
            "0xE382A6", "0xE382AF", "0xE382B9", "0xE38384", "0xE3838C", "0xE38395", "0xE383A0", "0xE383A8", "0xE383AB", "0xE383B3", "0xE382A5", "0xE383A7", "0xE3808D", "0xEFBC9F",
            "0xE382A8", "0xE382B1", "0xE382BB", "0xE38386", "0xE3838D", "0xE38398", "0xE383A1", "0xE3829B", "0xE383AC", "0xE38081", "0xE382A7", "0xE38383", "0xEFBC8C", "0xEFBC8E",
            "0xE382AA", "0xE382B3", "0xE382BD", "0xE38388", "0xE3838E", "0xE3839B", "0xE383A2", "0xE3829C", "0xE383AD", "0xE38082", "0xE382A9", "0xE383AE",
]; // 14*5

var FullWidthEnglish_Lowercase_Chars = [
            "１", "２", "３", "４", "５", "６", "７", "８", "９", "０",
            "ｑ", "ｗ", "ｅ", "ｒ", "ｔ", "ｙ", "ｕ", "ｉ", "ｏ", "ｐ",
            "ａ", "ｓ", "ｄ", "ｆ", "ｇ", "ｈ", "ｊ", "ｋ", "ｌ", "？",
            "＠", "ｚ", "ｘ", "ｃ", "ｖ", "ｂ", "ｎ", "ｍ", "，", "．"
]; // 10*4

var FullWidthEnglish_Lowercase_Rawcode = [
            "0xEFBC91", "0xEFBC92", "0xEFBC93", "0xEFBC94", "0xEFBC95", "0xEFBC96", "0xEFBC97", "0xEFBC98", "0xEFBC99", "0xEFBC90",
            "0xEFBD91", "0xEFBD97", "0xEFBD85", "0xEFBD92", "0xEFBD94", "0xEFBD99", "0xEFBD95", "0xEFBD89", "0xEFBD8F", "0xEFBD90",
            "0xEFBD81", "0xEFBD93", "0xEFBD84", "0xEFBD86", "0xEFBD87", "0xEFBD88", "0xEFBD8a", "0xEFBD8b", "0xEFBD8c", "0xEFBC9F",
            "0xEFBCA0", "0xEFBD9A", "0xEFBD98", "0xEFBD83", "0xEFBD96", "0xEFBD82", "0xEFBD8E", "0xEFBD8D", "0xEFBC8C", "0xEFBC8E"
]; // 10*4

var FullWidthEnglish_Uppercase_Chars = [
            "１", "２", "３", "４", "５", "６", "７", "８", "９", "０",
            "Ｑ", "Ｗ", "Ｅ", "Ｒ", "Ｔ", "Ｙ", "Ｕ", "Ｉ", "Ｏ", "Ｐ",
            "Ａ", "Ｓ", "Ｄ", "Ｆ", "Ｇ", "Ｈ", "Ｊ", "Ｋ", "Ｌ", "？",
            "＠", "Ｚ", "Ｘ", "Ｃ", "Ｖ", "Ｂ", "Ｎ", "Ｍ", "，", "．"
]; // 10*4

var FullWidthEnglish_Uppercase_Rawcode = [
            "0xEFBC91", "0xEFBC92", "0xEFBC93", "0xEFBC94", "0xEFBC95", "0xEFBC96", "0xEFBC97", "0xEFBC98", "0xEFBC99", "0xEFBC90",
            "0xEFBCB1", "0xEFBCB7", "0xEFBCA5", "0xEFBCB2", "0xEFBCB4", "0xEFBCB9", "0xEFBCB5", "0xEFBCA9", "0xEFBCAF", "0xEFBCB0",
            "0xEFBCA1", "0xEFBCB3", "0xEFBCA4", "0xEFBCA6", "0xEFBCA7", "0xEFBCA8", "0xEFBCAA", "0xEFBCAB", "0xEFBCAC", "0xEFBC9F",
            "0xEFBCA0", "0xEFBCBA", "0xEFBCB8", "0xEFBCA3", "0xEFBCB6", "0xEFBCA2", "0xEFBCAE", "0xEFBCAD", "0xEFBC8C", "0xEFBC8E"
]; // 10*4

var FullWidthSymbol_Chars = [
            "１", "２", "３", "４", "５", "６", "７", "８", "９", "０", "ー", "＝",
            "＾", "～", "？", "！", "’", "”", "（", "）", "：", "；", "＋", "＆",
            "％", "＊", "＜", "＞", "［", "］", "｛", "｝", "，", "§", "＃", "｀",
            "／", "¿", "¡", "￡", "＄", "￥", "＼", "｜", "．", "＠", "＿", "￠"
]; // 12*4

var FullWidthSymbol_Rawcode = [
            "0xEFBC91", "0xEFBC92", "0xEFBC93", "0xEFBC94", "0xEFBC95", "0xEFBC96", "0xEFBC97", "0xEFBC98", "0xEFBC99", "0xEFBC90", "0xE383BC", "0xEFBC9D",
            "0xEFBCBE", "0xE3809C", "0xEFBC9F", "0xEFBC81", "0xE28099", "0xE2809D", "0xEFBC88", "0xEFBC89", "0xEFBC9A", "0xEFBC9B", "0xEFBC8B", "0xEFBC86",
            "0xEFBC85", "0xEFBC8A", "0xEFBC9C", "0xEFBC9E", "0xEFBCBB", "0xEFBCBD", "0xEFBD9B", "0xEFBD9D", "0xEFBC8C", "0xC2A7", "0xEFBC83", "0xEFBD80",
            "0xEFBC8F", "0xC2BF", "0xC2A1", "0xC2A3", "0xEFBC84", "0xEFBFA5", "0xEFBCBC", "0xEFBD9C", "0xEFBC8E", "0xEFBCA0", "0xEFBCBF", "0xC2A2"
]; // 12*4

var HiraganaCaption = "ひらがな";
var KatakanaCaption = "カタカナ";
var FullWidthEnglishCaption = "全角英数";
var FullWidthSymbolCaption = "+ = [ ]";
var ConvertKeyCaption = "変換";
var HiraganaKeyNum = 68;
var KatakanaKeyNum = 70;
var FullWidthEnglishKeyNum = 40;
var SymbolKeyNum = 48;
var FullScreenPredictionRows = 6;
var FullScreenPredictionColumns = 5;
var GridHideMoveValue = 1000;
var HiraganaKatakanaSpaceButtonIndex = 13;
var ConvertRawCode = "0x64";
var FullWidthSpaceRawCode = "0xE38080";
var HidModeCaption = ["ローマ平", "ローマ片", "半角英数", "全角英数", "かな平", "かな片"];
var HidModeRomanHira = 0;
var HidModeRomanKata = 1;
var HidModeHalfWidthEnglish = 2;
var HidModeFullWidthEnglish = 3;
var HidModeKanaHira = 4;
var HidModeKanaKata = 5;
var EnterCaptionSearch = "検索";
var EnterCaptionFnish = "完了";
var EnterCaptionConfirm = "確定";
var BackButton = "戻る";
var LeftArea = 0;
var MiddleArea = 1;
var RightArea = 2;
var ConvertKeyColumn = 12;
