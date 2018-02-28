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
import WebOSServices 1.0

Item {
    property string german_Germany: qsTr("German - Germany") + PluginProxy.emptyString // i18n This needs to be translated only into German uses in Germany
    property string english_UK: qsTr("English - United Kingdom") + PluginProxy.emptyString // i18n This needs to be translated only into English uses in United Kingdom
    property string english_US: qsTr("English - United States") + PluginProxy.emptyString // i18n This needs to be translated only into English uses in United States
    property string english_Canada: qsTr("English - Canada") + PluginProxy.emptyString // i18n This needs to be translated only into English uses in Canada
    property string spanish_Spain: qsTr("Spanish - Spain") + PluginProxy.emptyString // i18n This needs to be translated only into Spanish uses in Spanin
    property string spanish_Mexico: qsTr("Spanish - Mexico") + PluginProxy.emptyString // i18n This needs to be translated only into Spanish uses in Mexico
    property string french_Canada: qsTr("French - Canada") + PluginProxy.emptyString // i18n This needs to be translated only into French uses in Canada
    property string french_France: qsTr("French - France") + PluginProxy.emptyString // i18n This needs to be translated only into French uses in France
    property string italian_Italy: qsTr("Italian - Italy") + PluginProxy.emptyString // i18n This needs to be translated only into Italian uses in Italy
    property string korean_Korea: qsTr("Korean - Korea") + PluginProxy.emptyString // i18n This needs to be translated only into Korean uses in Korea
    property string swedish_Sweden: qsTr("Swedish - Sweden") + PluginProxy.emptyString // i18n This needs to be translated only into Swedish uses in Sweden
    property string norwegian_Norway: qsTr("Norwegian - Norway") + PluginProxy.emptyString // i18n This needs to be translated only into Norwegian uses in Norway
    property string dutch_Netherlands: qsTr("Dutch - Netherlands") + PluginProxy.emptyString // i18n This needs to be translated only into Dutch uses in Netherlands
    property string russian_RussianFederation: qsTr("Russian - Russian Federation") + PluginProxy.emptyString // i18n This needs to be translated only into Russian uses in Russian Federation
    property string english_Australia: qsTr("English - Australia") + PluginProxy.emptyString // i18n This needs to be translated only into English uses in Australia
    property string chineseMandarinWithSimplifiedScript_China: qsTr("Chinese Mandarin with Simplified Script - China") + PluginProxy.emptyString // i18n This needs to be translated only into Chinese Mandarin with Simplified Script uses in China
    property string portuguese_Brazil: qsTr("Portuguese - Brazil") + PluginProxy.emptyString // i18n This needs to be translated only into Portuguese uses in Brazil
    property string portuguese_Portugal: qsTr("Portuguese - Portugal") + PluginProxy.emptyString // i18n This needs to be translated only into Portuguese uses in Portugal
    property string danish_Denmark: qsTr("Danish - Denmark") + PluginProxy.emptyString // i18n This needs to be translated only into Danish uses in Denmark
    property string finnish_Finland: qsTr("Finnish - Finland") + PluginProxy.emptyString // i18n This needs to be translated only into Finnish uses in Finland
    property string czech_CzechRepublic: qsTr("Czech - Czech Republic") + PluginProxy.emptyString // i18n This needs to be translated only into Czech uses in Czech Republic
    property string greek_Greece: qsTr("Greek - Greece") + PluginProxy.emptyString // i18n This needs to be translated only into Greek uses in Greece
    property string polish_Poland: qsTr("Polish - Poland") + PluginProxy.emptyString // i18n This needs to be translated only into Polish uses in Poland
    property string turkish_Turkey: qsTr("Turkish - Turkey") + PluginProxy.emptyString // i18n This needs to be translated only into Turkish uses in Turkey
    property string arabic_UnitedArabEmirates: qsTr("Arabic - United Arab Emirates") + PluginProxy.emptyString // i18n This needs to be translated only into Arabic uses in United Arab Emirates
    property string arabic_SaudiArabia: qsTr("Arabic - Saudi Arabia") + PluginProxy.emptyString // i18n This needs to be translated only into Arabic uses in Saudi Arabia
    property string arabic_Egypt: qsTr("Arabic - Egypt") + PluginProxy.emptyString // i18n This needs to be translated only into Arabic uses in Egypt
    property string ukrainian_Ukraine: qsTr("Ukrainian - Ukraine") + PluginProxy.emptyString // i18n This needs to be translated only into Ukrainian uses in Ukraine
    property string thai_Thailand: qsTr("Thai - Thailand") + PluginProxy.emptyString // i18n This needs to be translated only into Thai uses in Thailand
    property string vietnamese_Vietnam: qsTr("Vietnamese - Vietnam") + PluginProxy.emptyString // i18n This needs to be translated only into Vietnamese uses in Vietnam
    property string indonesian_Indonesia: qsTr("Indonesian - Indonesia") + PluginProxy.emptyString // i18n This needs to be translated only into Indonesian uses in Indonesia
    property string malay_Malaysia: qsTr("Malay - Malaysia") + PluginProxy.emptyString // i18n This needs to be translated only into Malay uses in Malaysia
    property string chineseMandarinWithTraditionalScript_Thiwain: qsTr("Chinese Mandarin with Traditional Script - Taiwain") + PluginProxy.emptyString // i18n This needs to be translated only into Chinese Mandarin with Traditional Script uses in Taiwain
    property string chineseCantoneseWithSimplifiedScript_HongKong: qsTr("Chinese Cantonese with Simplified Script - Hong Kong") + PluginProxy.emptyString // i18n This needs to be translated only into Chinese Cantonese with Simplified Script uses in Hong Kong
    property string japanese_Japan: qsTr("Japanese - Japan") + PluginProxy.emptyString // i18n This needs to be translated only into Japanese uses in Japan
    property string hebrew_Israel: qsTr("Hebrew - Israel") + PluginProxy.emptyString // i18n This needs to be translated only into Hebrew uses in Israel
    property string hungarian_Hungary: qsTr("Hungarian - Hungary") + PluginProxy.emptyString // i18n This needs to be translated only into Hungarian uses in Hungary
    property string romanian_Romania: qsTr("Romanian - Romania") + PluginProxy.emptyString // i18n This needs to be translated only into Romanian uses in Romania
    property string slovakian_Slovakia: qsTr("Slovak - Slovakia") + PluginProxy.emptyString // i18n This needs to be translated only into Slovak uses in Slovakia
    property string croatian_Croatia: qsTr("Croatian - Croatia") + PluginProxy.emptyString // i18n This needs to be translated only into Croatian uses in Croatia

    Component.onCompleted: {
        printLog("=== LocaleString onCompleted ===")
        printLog("=== LocaleString CALLE getLocaleLanguage ===")
        getLocaleLanguage()
    }

    function getSTTLangList(){
        return sttLangList
    }

    function printLocale(localeInfo) {
        var result

        switch(localeInfo) {
        case "de-DE":
            result = german_Germany
            break;
        case "en-GB":
            result = english_UK
            break;
        case "en-US":
            result = english_US
            break;
        case "en-CA":
            result = english_Canada
            break;
        case "es-ES":
            result = spanish_Spain
            break;
        case "es-MX":
            result = spanish_Mexico
            break;
        case "fr-CA":
            result = french_Canada
            break;
        case "fr-FR":
            result = french_France
            break;
        case "it-IT":
            result = italian_Italy
            break;
        case "ko-KR":
            result = korean_Korea
            break;
        case "sv-SE":
            result = swedish_Sweden
            break;
        case "nb-NO":
            result = norwegian_Norway
            break;
        case "nl-NL":
            result = dutch_Netherlands
            break;
        case "ru-RU":
            result = russian_RussianFederation
            break;
        case "en-AU":
            result = english_Australia
            break;
        case "zh-Hans-CN":
            result = chineseMandarinWithSimplifiedScript_China
            break;
        case "pt-BR":
            result = portuguese_Brazil
            break;
        case "pt-PT":
            result = portuguese_Portugal
            break;
        case "da-DK":
            result = danish_Denmark
            break;
        case "fi-FI":
            result = finnish_Finland
            break;
        case "cs-CZ":
            result = czech_CzechRepublic
            break;
        case "el-GR":
            result = greek_Greece
            break;
        case "pl-PL":
            result = polish_Poland
            break;
        case "tr-TR":
            result = turkish_Turkey
            break;
        case "ar-AE":
            result = arabic_UnitedArabEmirates
            break;
        case "ar-SA":
            result = arabic_SaudiArabia
            break;
        case "ar-EG":
            result = arabic_Egypt
            break;
        case "uk-UA":
            result = ukrainian_Ukraine
            break;
        case "th-TH":
            result = thai_Thailand
            break;
        case "vi-VN":
            result = vietnamese_Vietnam
            break;
        case "id-ID":
            result = indonesian_Indonesia
            break;
        case "ms-MY":
            result = malay_Malaysia
            break;
        case "zh-Hant-TW":
            result = chineseMandarinWithTraditionalScript_Thiwain
            break;
        case "zh-Hant-HK":
            result = chineseCantoneseWithSimplifiedScript_HongKong
            break;
        case "ja-JP":
            result = japanese_Japan
            break;
        case "he-IL":
            result = hebrew_Israel
            break;
        case "hu-HU":
            result = hungarian_Hungary
            break;
        case "ro-RO":
            result = romanian_Romania
            break;
        case "sk-SK":
            result = slovakian_Slovakia
            break;
        case "hr-HR":
            result = croatian_Croatia
            break;
        default:
            result = ""
            break;
        }

        return result;
    }
    function getLocaleLanguage() {
        getLocaleString.call("luna://com.webos.settingsservice", "/getSystemSettingValues" , "{\"key\":\"locale\"}")
    }

    ListModel {
        id: sttLangList
        ListElement {
            name: "de-DE"
        }
        ListElement {
            name: "en-US"
        }
        ListElement {
            name: "en-CA"
        }
        ListElement {
            name: "en-GB"
        }
        ListElement {
            name: "en-AU"
        }
        ListElement {
            name: "es-ES"
        }
        ListElement {
            name: "es-MX"
        }
        ListElement {
            name: "fr-FR"
        }
        ListElement {
            name: "fr-CA"
        }
        ListElement {
            name: "it-IT"
        }
        ListElement {
            name: "ko-KR"
        }
        ListElement {
            name: "sv-SE"
        }
        ListElement {
            name: "nb-NO"
        }
        ListElement {
            name: "nl-NL"
        }
        ListElement {
            name: "ru-RU"
        }
        ListElement {
            name: "pt-PT"
        }
        ListElement {
            name: "pt-BR"
        }
        ListElement {
            name: "da-DK"
        }
        ListElement {
            name: "fi-FI"
        }
        ListElement {
            name: "cs-CZ"
        }
        ListElement {
            name: "el-GR"
        }
        ListElement {
            name: "pl-PL"
        }
        ListElement {
            name: "tr-TR"
        }
        ListElement {
            name: "ar-AE"
        }
        ListElement {
            name: "ar-SA"
        }
        ListElement {
            name: "ar-EG"
        }
        ListElement {
            name: "uk-UA"
        }
        ListElement {
            name: "th-TH"
        }
        ListElement {
            name: "vi-VN"
        }
        ListElement {
            name: "id-ID"
        }
        ListElement {
            name: "ms-MY"
        }
        ListElement {
            name: "zh-Hans-CN"
        }
        ListElement {
            name: "zh-Hant-TW"
        }
        ListElement {
            name: "zh-Hant-HK"
        }
        ListElement {
            name: "ja-JP"
        }
        ListElement {
            name: "he-IL"
        }
        ListElement {
            name: "hu-HU"
        }
        ListElement {
            name: "ro-RO"
        }
        ListElement {
            name: "sk-SK"
        }
        ListElement {
            name: "hr-HR"
        }
    }

    Service {
        id: getLocaleString
        appId: "com.webos.service.ime.stt"
        onResponse: {
            printLog("=== getLocaleString onResponse ===");
            printLog("payload : " + payload);
            var jsonObject = JSON.parse(payload);
            var sttLocaleList = jsonObject.stt;

            printLog("for(var i = 0; i < sttLocaleList.length; i++){");
            for(var i = 0; i < sttLocaleList.length; i++){
                var langElement = sttLocaleList[i];
                printLog("langElement.languageCode : " + langElement.languageCode);
                printLog("langElement.name : " + langElement.name);
                var languageName = langElement.name;

                printLog("for(var j = 0; j < langElement.countries.length; j++ ) {");
                for(var j = 0; j < langElement.countries.length; j++ ) {
                    var country = langElement.countries[j];
                    printLog("country.spec: " + country.spec);
                    printLog("country.name: " + country.name);
                    var langCode;
                    if(country.spec == "cmn-Hans-CN") langCode = "zh-Hans-CN";
                    else if(country.spec == "yue-Hant-HK") langCode = "zh-Hant-HK";
                    else if(country.spec == "cmn-Hant-TW") langCode = "zh-Hant-TW";
                    else langCode = country.spec;

                    printLog("var langCode = country.spec; " + langCode);
                    var languageString = country.name + " - " +languageName;
                    printLog("var languageString = country.name" + "-" +"languageName; " + languageString);

                    setLocaleString(langCode, languageString)
                }
            }

        }
        function setLocaleString(localeCode, localeText){
            printLog("=== setLocaleString ===");
            printLog("localeCode: " + localeCode);
            printLog("localeText: " + localeText);
            switch(localeCode) {
            case "de-DE":
                german_Germany = localeText
                break;
            case "en-GB":
                english_UK = localeText
                break;
            case "en-US":
                english_US = localeText
                break;
            case "en-CA":
                english_Canada = localeText
                break;
            case "es-ES":
                spanish_Spain = localeText
                break;
            case "es-MX":
                spanish_Mexico = localeText
                break;
            case "fr-CA":
                french_Canada = localeText
                break;
            case "fr-FR":
                french_France = localeText
                break;
            case "it-IT":
                italian_Italy = localeText
                break;
            case "ko-KR":
                korean_Korea = localeText
                break;
            case "sv-SE":
                swedish_Sweden = localeText
                break;
            case "nb-NO":
                norwegian_Norway = localeText
                break;
            case "nl-NL":
                dutch_Netherlands = localeText
                break;
            case "ru-RU":
                russian_RussianFederation = localeText
                break;
            case "en-AU":
                english_Australia = localeText
                break;
            case "zh-Hans-CN":
                chineseMandarinWithSimplifiedScript_China = localeText
                break;
            case "pt-BR":
                portuguese_Brazil = localeText
                break;
            case "pt-PT":
                portuguese_Portugal = localeText
                break;
            case "da-DK":
                danish_Denmark = localeText
                break;
            case "fi-FI":
                finnish_Finland = localeText
                break;
            case "cs-CZ":
                czech_CzechRepublic = localeText
                break;
            case "el-GR":
                greek_Greece = localeText
                break;
            case "pl-PL":
                polish_Poland = localeText
                break;
            case "tr-TR":
                turkish_Turkey = localeText
                break;
            case "ar-AE":
                arabic_UnitedArabEmirates = localeText
                break;
            case "ar-SA":
                arabic_SaudiArabia = localeText
                break;
            case "ar-EG":
                arabic_Egypt = localeText
                break;
            case "uk-UA":
                ukrainian_Ukraine = localeText
                break;
            case "th-TH":
                thai_Thailand = localeText
                break;
            case "vi-VN":
                vietnamese_Vietnam = localeText
                break;
            case "id-ID":
                indonesian_Indonesia = localeText
                break;
            case "ms-MY":
                malay_Malaysia = localeText
                break;
            case "zh-Hant-TW":
                chineseMandarinWithTraditionalScript_Thiwain = localeText
                break;
            case "zh-Hant-HK":
                chineseCantoneseWithSimplifiedScript_HongKong = localeText
                break;
            case "ja-JP":
                japanese_Japan = localeText
                break;
            case "he-IL":
                hebrew_Israel = localeText
                break;
            case "hu-HU":
                hungarian_Hungary = localeText
                break;
            case "ro-RO":
                romanian_Romania = localeText
                break;
            case "sk-SK":
                slovakian_Slovakia = localeText
                break;
            case "hr-HR":
                croatian_Croatia = localeText
                break;
            default:
                result = ""
                break;
            }
        }
    }
}
