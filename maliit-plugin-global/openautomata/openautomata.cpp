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

#include "openautomata.h"
#include "englishautomata.h"
#include "koreanautomata.h"
#include "germanautomata.h"
#include "dutchautomata.h"
#include "italianautomata.h"
#include "spanishautomata.h"
#include "polishautomata.h"
#include "frenchautomata.h"
#include "portugueseautomata.h"
#include "russianautomata.h"
#include "latvianautomata.h"
#include "finnishautomata.h"
#include "croatianautomata.h"
#include "danishautomata.h"
#include "norwegianautomata.h"
#include "czechautomata.h"
#include "irishautomata.h"
#include "albanianautomata.h"
#include "bosnianautomata.h"
#include "bulgarianautomata.h"
#include "greekautomata.h"
#include "estonianautomata.h"
#include "hungarianautomata.h"
#include "swedishautomata.h"
#include "indonesianautomata.h"
#include "ukrainianautomata.h"
#include "thaiautomata.h"
#include "turkishautomata.h"
#include "vietnameseautomata.h"
#include "hindiautomata.h"
#include "arabicautomata.h"
#include "malayautomata.h"
#include "lithuanianautomata.h"
#include "Kazakhautomata.h"
#include "macedonianautomata.h"
#include "hebrewautomata.h"
#include "kurdishautomata.h"
#include "persianautomata.h"
#include "romanianautomata.h"
#include "maoriautomata.h"
#include "mongolianautomata.h"
#include "serbianautomata.h"
#include "slovakautomata.h"
#include "slovenianAutomata.h"
#include "uzbeklatinautomata.h"
#include "cambodianautomata.h"
#include "srilankanautomata.h"
#include "tamilautomata.h"
#include "kannadaautomata.h"
#include "swahiliautomata.h"
#include "malayalamautomata.h"
#include "bengaliautomata.h"
#include "gujaratiautomata.h"
#include "teluguautomata.h"
#include "marathiautomata.h"
#include "assameseautomata.h"
#include "punjabiautomata.h"
#include "oriyaautomata.h"
#include "urduautomata.h"
#include "hausaautomata.h"
#include "azerbaijaniautomata.h"
#include "afrikaansautomata.h"
#include "armenianautomata.h"
#include "bashkirautomata.h"
#include "icelandicautomata.h"
#include "belarusianautomata.h"
#include "catalanautomata.h"
#include "igboautomata.h"
#include "kyrgyzautomata.h"
#include "luxembourgishautomata.h"
#include "malteseautomata.h"
#include "nepaliautomata.h"
#include "northensothoautomata.h"
#include "tajikautomata.h"
#include "pashtoautomata.h"
#include "tatarautomata.h"
#include "turkmenautomata.h"
#include "uyghurautomata.h"
#include "wolofautomata.h"
#include "yorubaautomata.h"
#include "laoautomata.h"
#include "georgianautomata.h"
#include "burmeseautomata.h"
#include "welshautomata.h"
#include "zuluautomata.h"
#include "somaliautomata.h"
#include <QDebug>

OpenAutomata::OpenAutomata()
{
    m_automataMap[QLocale::languageToString(QLocale::English)] = &EnglishAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Korean)]  = &KoreanAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::German)]  = &GermanAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Dutch)]   = &DutchAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Italian)] = &ItalianAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Spanish)] = &SpanishAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Polish)]  = &PolishnAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::French)]  = &FrenchAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Portuguese)] = &PortugueseAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Russian)] = &RussianAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Latvian)] = &LatvianAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Finnish)] = &FinnishAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Croatian)] = &CroatianAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Danish)] = &DanishAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Czech)] = &CzechAutomata::create;
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    m_automataMap[QLocale::languageToString(QLocale::NorwegianBokmal)] = &NorwegianAutomata::create;
#else
    m_automataMap[QLocale::languageToString(QLocale::Norwegian)] = &NorwegianAutomata::create;
#endif
    m_automataMap[QLocale::languageToString(QLocale::Irish)] = &IrishAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Albanian)] = &AlbanianAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Bosnian)] = &BosnianAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Bulgarian)] = &BulgarianAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Greek)] = &GreekAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Estonian)] = &EstonianAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Hungarian)] = &HungarianAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Swedish)] = &SwedishAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Indonesian)] = &IndonesianAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Ukrainian)] = &UkrainianAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Thai)] = &ThaiAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Turkish)] = &TurkishAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Vietnamese)] = &VietnameseAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Hindi)] = &HindiAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Arabic)] = &ArabicAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Malay)] = &MalayAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Lithuanian)] = &LithuanianAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Kazakh)] = &KazakhAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Macedonian)] = &MacedonianAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Hebrew)] = &HebrewAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Kurdish)] = &KurdishAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Persian)] = &PersianAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Romanian)] = &RomanianAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Maori)] = &MaoriAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Mongolian)] = &MongolianAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Serbian)] = &SerbianAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Slovak)] = &SlovakAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Slovenian)] = &SlovenianAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Uzbek)
            + "-" + QLocale::scriptToString(QLocale::LatinScript)] = &UzbekLatinAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Khmer)] = &CambodianAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Sinhala)] = &SrilankanAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Tamil)] = &TamilAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Kannada)] = &KannadaAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Swahili)] = &SwahiliAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Malayalam)] = &MalayalamAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Bengali)] = &BengaliAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Gujarati)] = &GujaratiAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Telugu)] = &TeluguAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Marathi)] = &MarathiAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Assamese)] = &AssameseAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Punjabi)] = &PunjabiAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Oriya)] = &OriyaAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Urdu)] = &UrduAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Hausa)] = &HausaAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Azerbaijani)] = &AzerbaijaniAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Afrikaans)] = &AfrikaansAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Armenian)] = &ArmenianAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Bashkir)] = &BashkirAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Icelandic)] = &IcelandicAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Belarusian)] = &BelarusianAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Catalan)] = &CatalanAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Igbo)] = &IgboAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Kirghiz)] = &KyrgyzAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Luxembourgish)] = &LuxembourgishAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Maltese)] = &MalteseAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Nepali)] = &NepaliAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::NorthernSotho)] = &NorthernSothoAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Tajik)] = &TajikAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Pashto)] = &PashtoAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Tatar)] = &TatarAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Turkmen)] = &TurkmenAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Uighur)] = &UyghurAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Wolof)] = &WolofAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Yoruba)] = &YorubaAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Lao)] = &LaoAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Georgian)] = &GeorgianAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Burmese)] = &BurmeseAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Welsh)] = &WelshAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Zulu)] = &ZuluAutomata::create;
    m_automataMap[QLocale::languageToString(QLocale::Somali)] = &SomaliAutomata::create;
    m_automata.reset(m_automataMap[QLocale::languageToString(QLocale::English)]());
}

OpenAutomata::~OpenAutomata()
{

}

bool OpenAutomata::setLanguage(const QString &language)
{
    m_automata.reset(m_automataMap[language]());
    return true;
}

bool OpenAutomata::isSupportedLanguage(const QString &language)
{
    return m_automataMap.contains(language);
}

QString OpenAutomata::getAutomataLanguageString(const QString &language)
{
    if (m_automataMap.contains(language))
        return language;
    else
        return QString("NotSupported");
}

void OpenAutomata::reset()
{
    m_automata->reset();
}

void OpenAutomata::setPreedit(const QString &preedit, int cursorPos)
{
    m_automata->setPreedit(preedit,cursorPos);
}

QString OpenAutomata::getPreedit()
{
    return m_automata->getPreedit();
}

QString OpenAutomata::getCommit()
{
    return m_automata->getCommit();
}

bool OpenAutomata::processKeyEvent(quint32 nativeScanCode, Qt::KeyboardModifiers modifiers, bool isCapsLockOn, bool isNumLockOn)
{
   return m_automata->processKeyEvent(nativeScanCode,modifiers,isCapsLockOn,isNumLockOn);
}

bool OpenAutomata::processKeysym(quint32 keysym)
{
    return m_automata->processKeysym(keysym);
}

bool OpenAutomata::isPredictionSupported()
{
    return m_automata->isPredictionSupported();
}

QString OpenAutomata::getWordForPrediction()
{
    return m_automata->getWordForPrediction();
}

QStringList OpenAutomata::getPredictionList(const QString &language)
{
    Q_UNUSED(language);
    return QStringList();
}
