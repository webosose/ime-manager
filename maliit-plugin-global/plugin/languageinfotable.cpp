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

#include "languageinfotable.h"

#include <QHash>
#include <QLocale>

class LanguageInfoElement
{
public:
    LanguageInfoElement(QString iso2Code, QString iso1Code, QLocale::Script script, QString ownLanguage)
        : iso2Code(iso2Code)
        , iso1Code(iso1Code)
        , script(script)
        , ownLanguage(ownLanguage)
    {}

    QString iso2Code;   // ISO 639-2
    QString iso1Code;   // ISO 639-1
    QLocale::Script script;
    QString ownLanguage;
};

typedef QHash<QString, LanguageInfoElement> LanguageHash;


QScopedPointer<LanguageInfoTable> LanguageInfoTable::s_instance;      // used for singleton
static LanguageHash s_languageHash;


class LanguageInfoTablePrivate
{
    Q_DECLARE_PUBLIC(LanguageInfoTable)

public:
    LanguageInfoTable *const q_ptr;
    QString language;
    LanguageHash::const_iterator it;

    LanguageInfoTablePrivate(LanguageInfoTable *inst)
        : q_ptr(inst)
        , language("")
    {}

    LanguageHash::const_iterator getIterator(QString language)
    {
        if (this->language != language) {
            this->language = language;
            it = s_languageHash.find(language);
        }
        return it;
    }
};


LanguageInfoTable *LanguageInfoTable::getInstance()
{
    if (s_instance.isNull())
        s_instance.reset(new LanguageInfoTable());
    return s_instance.data();
}

LanguageInfoTable::LanguageInfoTable()
    : d_ptr(new LanguageInfoTablePrivate(this))
{
    if (s_languageHash.empty())
        initializeHashTable();
}

LanguageInfoTable::~LanguageInfoTable()
{
}

void LanguageInfoTable::releaseInstance()
{
    if (!s_instance.isNull())
        s_instance.reset();
}

QString LanguageInfoTable::getIso2Code(QString language)
{
    Q_D(LanguageInfoTable);
    LanguageHash::const_iterator it = d->getIterator(language);
    if (it != s_languageHash.end())
        return it.value().iso2Code;
    else
        return "";
}

QString LanguageInfoTable::getIso1Code(QString language)
{
    Q_D(LanguageInfoTable);
    LanguageHash::const_iterator it = d->getIterator(language);
    if (it != s_languageHash.end())
        return it.value().iso1Code;
    else
        return "";
}

QLocale::Script LanguageInfoTable::getScript(QString language)
{
    Q_D(LanguageInfoTable);
    LanguageHash::const_iterator it = d->getIterator(language);
    if (it != s_languageHash.end())
        return it.value().script;
    else
        return QLocale::AnyScript;
}

QString LanguageInfoTable::getOwnLanguage(QString language)
{
    Q_D(LanguageInfoTable);
    LanguageHash::const_iterator it = d->getIterator(language);
    if (it != s_languageHash.end())
        return it.value().ownLanguage;
    else
        return "";
}

void LanguageInfoTable::initializeHashTable()
{
    // initialize table
    s_languageHash.reserve(100);

    s_languageHash.insert(QLocale::languageToString(QLocale::Albanian),
                          LanguageInfoElement(QString("sqi"), QString("sq"),   QLocale::LatinScript,   QString("shqipe")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Arabic),
                          LanguageInfoElement(QString("ara"), QString("ar"),   QLocale::ArabicScript,  QString("العربية")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Bosnian),
                          LanguageInfoElement(QString("bos"), QString("bs"),   QLocale::LatinScript,   QString("bosanski")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Bulgarian),
                          LanguageInfoElement(QString("bul"), QString("bg"),   QLocale::CyrillicScript,QString("български")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Croatian),
                          LanguageInfoElement(QString("hrv"), QString("hr"),   QLocale::LatinScript,   QString("hrvatski")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Czech),
                          LanguageInfoElement(QString("ces"), QString("cs"),   QLocale::LatinScript,   QString("čeština")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Danish),
                          LanguageInfoElement(QString("dan"), QString("da"),   QLocale::LatinScript,   QString("dansk")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Dutch),
                          LanguageInfoElement(QString("nld"), QString("nl"),   QLocale::LatinScript,   QString("Nederlands")));
    s_languageHash.insert(QLocale::languageToString(QLocale::English),
                          LanguageInfoElement(QString("eng"), QString("en"),   QLocale::LatinScript,   QString("English")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Estonian),
                          LanguageInfoElement(QString("est"), QString("et"),   QLocale::LatinScript,   QString("eesti keel")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Finnish),
                          LanguageInfoElement(QString("fin"), QString("fi"),   QLocale::LatinScript,   QString("suomi")));
    s_languageHash.insert(QLocale::languageToString(QLocale::French),
                          LanguageInfoElement(QString("fra"), QString("fr"),   QLocale::LatinScript,   QString("français")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Gaelic),
                          LanguageInfoElement(QString("gla"), QString("ga"),   QLocale::LatinScript,   QString("Gaeilge")));
    s_languageHash.insert(QLocale::languageToString(QLocale::German),
                          LanguageInfoElement(QString("deu"), QString("de"),   QLocale::LatinScript,   QString("Deutsch")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Greek),
                          LanguageInfoElement(QString("ell"), QString("el"),   QLocale::LatinScript,   QString("ελληνική γλώσσα")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Hebrew),
                          LanguageInfoElement(QString("heb"), QString("he"),   QLocale::HebrewScript,  QString("עברית")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Hindi),
                          LanguageInfoElement(QString("hin"), QString("hi"),   QLocale::DevanagariScript, QString("हिन्दी")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Hungarian),
                          LanguageInfoElement(QString("hun"), QString("hu"),   QLocale::LatinScript,   QString("magyar")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Indonesian),
                          LanguageInfoElement(QString("ind"), QString("id"),   QLocale::LatinScript,   QString("bahasa Indonesia")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Irish),
                          LanguageInfoElement(QString("gle"), QString("ga"),   QLocale::LatinScript,   QString("Gaeilge"))); // TODO:Check own language
    s_languageHash.insert(QLocale::languageToString(QLocale::Italian),
                          LanguageInfoElement(QString("ita"), QString("it"),   QLocale::LatinScript,   QString("italiano")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Kazakh),
                          LanguageInfoElement(QString("kaz"), QString("kk"),   QLocale::CyrillicScript,QString("қазақ тілі")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Korean),
                          LanguageInfoElement(QString("kor"), QString("ko"),   QLocale::KoreanScript,  QString("한국어")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Khmer),
                          LanguageInfoElement(QString("khm"), QString("km"), QLocale::KhmerScript, QString("ខ្មែរ")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Kurdish),
                          LanguageInfoElement(QString("kur"), QString("ku"),   QLocale::ArabicScript,  QString("کوردی")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Latvian),
                          LanguageInfoElement(QString("lav"), QString("lv"),   QLocale::LatinScript,   QString("latviešu valoda")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Lithuanian),
                          LanguageInfoElement(QString("lit"), QString("lt"),   QLocale::LatinScript,   QString("lietuvių kalba")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Macedonian),
                          LanguageInfoElement(QString("mkd"), QString("mk"),   QLocale::CyrillicScript,QString("македонски")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Malay),
                          LanguageInfoElement(QString("msa"), QString("ms"),   QLocale::LatinScript,   QString("bahasa Melayu")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Maori),
                          LanguageInfoElement(QString("mri"), QString("mi"),   QLocale::LatinScript,   QString("Māori")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Mongolian),
                          LanguageInfoElement(QString("mon"), QString("mn"),   QLocale::CyrillicScript,QString("Монгол хэл")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Norwegian),
                          LanguageInfoElement(QString("nor"), QString("nb"),   QLocale::LatinScript,   QString("norsk")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Persian),
                          LanguageInfoElement(QString("fas"), QString("fa"),   QLocale::ArabicScript,  QString("فارسی")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Polish),
                          LanguageInfoElement(QString("pol"), QString("pl"),   QLocale::LatinScript,   QString("język polski")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Portuguese),
                          LanguageInfoElement(QString("por"), QString("pt"),   QLocale::LatinScript,   QString("português")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Romanian),
                          LanguageInfoElement(QString("ron"), QString("ro"),   QLocale::LatinScript,   QString("română")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Russian),
                          LanguageInfoElement(QString("rus"), QString("ru"),   QLocale::CyrillicScript,QString("Русский")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Serbian),
                          LanguageInfoElement(QString("srp"), QString("sr"),   QLocale::LatinScript,   QString("srpski")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Slovak),
                          LanguageInfoElement(QString("slk"), QString("sk"),   QLocale::LatinScript,   QString("slovenský jazyk")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Slovenian),
                          LanguageInfoElement(QString("slv"), QString("sl"),   QLocale::LatinScript,   QString("slovenski jezik")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Spanish),
                          LanguageInfoElement(QString("spa"), QString("es"),   QLocale::LatinScript,   QString("español")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Swedish),
                          LanguageInfoElement(QString("swe"), QString("sv"),   QLocale::LatinScript,   QString("svenska")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Tamil),
                          LanguageInfoElement(QString("tam"), QString("ta"),   QLocale::TamilScript,    QString("தமிழ்")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Thai),
                          LanguageInfoElement(QString("tha"), QString("th"),   QLocale::ThaiScript,    QString("ภาษาไทย")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Turkish),
                          LanguageInfoElement(QString("tur"), QString("tr"),   QLocale::LatinScript,   QString("Türkçe")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Ukrainian),
                          LanguageInfoElement(QString("ukr"), QString("uk"),   QLocale::CyrillicScript,QString("Українська")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Uzbek) + "-" + QLocale::scriptToString(QLocale::CyrillicScript),
                          LanguageInfoElement(QString("uzb"), QString("uz_Cyrl"),   QLocale::CyrillicScript, QString("Ўзбек")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Uzbek) + "-" + QLocale::scriptToString(QLocale::LatinScript),
                          LanguageInfoElement(QString("uzb"), QString("uz_Latn"),   QLocale::LatinScript,   QString("Oʻzbek")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Vietnamese),
                          LanguageInfoElement(QString("vie"), QString("vi"),   QLocale::LatinScript,   QString("Tiếng Việt")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Kannada),
                          LanguageInfoElement(QString("kan"), QString("kn"),   QLocale::KannadaScript, QString("ಕನ್ನಡ")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Bengali),
                          LanguageInfoElement(QString("ban"), QString("bn"),   QLocale::BengaliScript, QString("বাংলা")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Sinhala),
                          LanguageInfoElement(QString("sin"), QString("si"),   QLocale::SinhalaScript,  QString("සිංහල")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Swahili),
                          LanguageInfoElement(QString("swa"), QString("sw"),   QLocale::LatinScript,  QString("Swahili")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Malayalam),
                          LanguageInfoElement(QString("MAL"), QString("ml"),   QLocale::MalayalamScript,  QString("മലയാളം")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Gujarati),
                          LanguageInfoElement(QString("guj"), QString("gu"),   QLocale::GujaratiScript, QString("ગુજરાતી")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Telugu),
                          LanguageInfoElement(QString("tel"), QString("te"),   QLocale::TeluguScript, QString("తెలుగు")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Marathi),
                          LanguageInfoElement(QString("mar"), QString("mr"),   QLocale::DevanagariScript, QString("मराठी")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Assamese),
                          LanguageInfoElement(QString("asm"), QString("as"),   QLocale::DevanagariScript, QString("অসমীয়া")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Punjabi),
                          LanguageInfoElement(QString("pan"), QString("pa"),   QLocale::GurmukhiScript, QString("ਪੰਜਾਬੀ")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Oriya),
                          LanguageInfoElement(QString("ori"), QString("or"),   QLocale::OriyaScript, QString("ଓଡ଼ିଆ")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Urdu),
                          LanguageInfoElement(QString("urd"), QString("ur"),   QLocale::OldPersianScript, QString("اردو")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Hausa),
                          LanguageInfoElement(QString("hau"), QString("ha"),   QLocale::LatinScript, QString("Hausa")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Azerbaijani),
                          LanguageInfoElement(QString("aze"), QString("az"),   QLocale::LatinScript, QString("Azerbaijani")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Afrikaans),
                          LanguageInfoElement(QString("afr"), QString("af"),   QLocale::LatinScript, QString("Afrikaans")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Japanese),
                          LanguageInfoElement(QString("jpn"), QString("ja"),   QLocale::JapaneseScript,QString("日本語")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Chinese) + "-" + QLocale::scriptToString(QLocale::SimplifiedChineseScript),
                          LanguageInfoElement(QString("zho"), QString("zh_Hans"), QLocale::SimplifiedChineseScript, QString("中文")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Chinese) + "-" + QLocale::scriptToString(QLocale::TraditionalChineseScript),
                          LanguageInfoElement(QString("zho"), QString("zh_Hant"), QLocale::TraditionalChineseScript, QString("中文")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Armenian),
                          LanguageInfoElement(QString("hye"), QString("hy"),   QLocale::ArmenianScript, QString("հայերեն")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Bashkir),
                          LanguageInfoElement(QString("bak"), QString("ba"),   QLocale::CyrillicScript,QString("Башҡорттар")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Icelandic),
                          LanguageInfoElement(QString("isl"), QString("is"),   QLocale::LatinScript,   QString("Icelandic")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Belarusian),
                          LanguageInfoElement(QString("bel"), QString("be"),   QLocale::CyrillicScript,   QString("беларускі")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Catalan),
                          LanguageInfoElement(QString("cat"), QString("ca"),   QLocale::LatinScript,   QString("Català")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Igbo),
                          LanguageInfoElement(QString("ibo"), QString("ig"),   QLocale::LatinScript,   QString("Igbo")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Kirghiz),
                          LanguageInfoElement(QString("kir"), QString("ky"),   QLocale::CyrillicScript,   QString("Кыргызча")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Luxembourgish),
                          LanguageInfoElement(QString("ltz"), QString("lb"),   QLocale::LatinScript,   QString("Lëtzebuergesch")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Maltese),
                          LanguageInfoElement(QString("mlt"), QString("mt"),   QLocale::LatinScript,   QString("Malti")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Nepali),
                          LanguageInfoElement(QString("nep"), QString("ne"),   QLocale::DevanagariScript,   QString("नेपाली")));
    s_languageHash.insert(QLocale::languageToString(QLocale::NorthernSotho),
                          LanguageInfoElement(QString("nso"), QString("nso"),   QLocale::LatinScript,   QString("Sesotho sa Leboa")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Tajik),
                          LanguageInfoElement(QString("tgk"), QString("tg"),   QLocale::CyrillicScript,   QString("тоҷикӣ")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Pashto),
                          LanguageInfoElement(QString("pus"), QString("ps"),   QLocale::ArabicScript,   QString("پښتو")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Tatar),
                          LanguageInfoElement(QString("tat"), QString("tt"),   QLocale::CyrillicScript,   QString("татар теле")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Turkmen),
                          LanguageInfoElement(QString("tuk"), QString("tk"),   QLocale::LatinScript,   QString("Türkmen")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Uighur),
                          LanguageInfoElement(QString("uig"), QString("ug"),   QLocale::ArabicScript,   QString("ئۇيغۇرچە")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Wolof),
                          LanguageInfoElement(QString("wol"), QString("wo"),   QLocale::LatinScript,   QString("Wollof")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Yoruba),
                          LanguageInfoElement(QString("yor"), QString("yo"),   QLocale::LatinScript,   QString("Yorùbá")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Lao),
                          LanguageInfoElement(QString("lao"), QString("lo"),   QLocale::LaoScript,   QString("ພາສາລາວ")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Georgian),
                          LanguageInfoElement(QString("kat"), QString("ka"),   QLocale::GeorgianScript,   QString("ქართული")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Burmese),
                          LanguageInfoElement(QString("mya"), QString("my"),   QLocale::LaoScript,   QString("ဗမာစာ")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Welsh),
                          LanguageInfoElement(QString("cym"), QString("cy"),   QLocale::LatinScript,   QString("Cymraeg")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Zulu),
                          LanguageInfoElement(QString("zul"), QString("zu"),   QLocale::LatinScript,   QString("isiZulu")));
    s_languageHash.insert(QLocale::languageToString(QLocale::Somali),
                          LanguageInfoElement(QString("som"), QString("so"),   QLocale::CyrillicScript,   QString("af Soomaali")));
}
