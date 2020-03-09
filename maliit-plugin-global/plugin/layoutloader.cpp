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

#include "layoutloader.h"

#include <stdio.h>
#include <QFile>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>
#include <QUrl>

StringHash LayoutLoader::s_hash;
static const QString EMPTY_STRING = QString("");

LayoutLoader::LayoutLoader()
{
    if (s_hash.isEmpty()) {
        initFileTable();
    }
}

LayoutLoader::LayoutLoader(const QString &language)
{
    if (s_hash.isEmpty()) {
        initFileTable();
    }

    if (!language.isNull() && !language.isEmpty())
        setLanguage(language);
}

LayoutLoader::LayoutLoader(const LayoutLoader &l)
    : QObject(0)
{
    if (s_hash.isEmpty()) {
        initFileTable();
    }
    m_language = QString(l.getLanguage());
    m_separator = QString(l.getSeparator());
    m_json = QJsonObject(l.getLayout());
}

LayoutLoader& LayoutLoader::operator=(const LayoutLoader &l)
{
    if (&l == this)
        return *this;

    if (s_hash.isEmpty()) {
        initFileTable();
    }
    m_language = QString(l.getLanguage());
    m_separator = QString(l.getSeparator());
    m_json = QJsonObject(l.getLayout());

    return *this;
}

LayoutLoader::~LayoutLoader()
{
}

void LayoutLoader::initFileTable()
{
    s_hash.reserve(100);
    s_hash.insert(QLocale::languageToString(QLocale::English),   ":/jsons/en.json");
    s_hash.insert(QLocale::languageToString(QLocale::Korean),    ":/jsons/ko.json");
    s_hash.insert(QLocale::languageToString(QLocale::Russian),   ":/jsons/ru.json");
    s_hash.insert(QLocale::languageToString(QLocale::Finnish),   ":/jsons/fi.json");
    s_hash.insert(QLocale::languageToString(QLocale::Croatian),  ":/jsons/hr.json");
    s_hash.insert(QLocale::languageToString(QLocale::Danish),    ":/jsons/dk.json");
    s_hash.insert(QLocale::languageToString(QLocale::Norwegian), ":/jsons/no.json");
    s_hash.insert(QLocale::languageToString(QLocale::Bosnian),   ":/jsons/bs.json");
    s_hash.insert(QLocale::languageToString(QLocale::Bulgarian), ":/jsons/bg.json");
    s_hash.insert(QLocale::languageToString(QLocale::Greek),     ":/jsons/gr.json");
    s_hash.insert(QLocale::languageToString(QLocale::Hungarian), ":/jsons/hu.json");
    s_hash.insert(QLocale::languageToString(QLocale::Swedish),   ":/jsons/se.json");
    s_hash.insert(QLocale::languageToString(QLocale::Ukrainian), ":/jsons/ua.json");
    s_hash.insert(QLocale::languageToString(QLocale::Thai),      ":/jsons/th.json");
    s_hash.insert(QLocale::languageToString(QLocale::Turkish),   ":/jsons/tr.json");
    s_hash.insert(QLocale::languageToString(QLocale::Vietnamese),":/jsons/vn.json");
    s_hash.insert(QLocale::languageToString(QLocale::Hindi),     ":/jsons/hi.json");
    s_hash.insert(QLocale::languageToString(QLocale::Arabic),    ":/jsons/ar.json");
    s_hash.insert(QLocale::languageToString(QLocale::Lithuanian),":/jsons/lt.json");
    s_hash.insert(QLocale::languageToString(QLocale::Kazakh),    ":/jsons/kz.json");
    s_hash.insert(QLocale::languageToString(QLocale::Macedonian),":/jsons/mk.json");
    s_hash.insert(QLocale::languageToString(QLocale::Hebrew),    ":/jsons/he.json");
    s_hash.insert(QLocale::languageToString(QLocale::Kurdish),   ":/jsons/ku.json");
    s_hash.insert(QLocale::languageToString(QLocale::Persian),   ":/jsons/fa.json");
    s_hash.insert(QLocale::languageToString(QLocale::Romanian),  ":/jsons/ro.json");
    s_hash.insert(QLocale::languageToString(QLocale::Mongolian), ":/jsons/mn.json");
    s_hash.insert(QLocale::languageToString(QLocale::Serbian),   ":/jsons/rs.json");
    s_hash.insert(QLocale::languageToString(QLocale::Sinhala),   ":/jsons/si.json");
    s_hash.insert(QLocale::languageToString(QLocale::Slovak),    ":/jsons/sk.json");
    s_hash.insert(QLocale::languageToString(QLocale::Slovenian), ":/jsons/sl.json");
    s_hash.insert(QLocale::languageToString(QLocale::German),    ":/jsons/de.json");
    s_hash.insert(QLocale::languageToString(QLocale::Albanian),  ":/jsons/al.json");
    s_hash.insert(QLocale::languageToString(QLocale::Polish),    ":/jsons/pl.json");
    s_hash.insert(QLocale::languageToString(QLocale::Czech),     ":/jsons/cz.json");
    s_hash.insert(QLocale::languageToString(QLocale::French),    ":/jsons/fr.json");
    s_hash.insert(QLocale::languageToString(QLocale::Italian),   ":/jsons/it.json");
    s_hash.insert(QLocale::languageToString(QLocale::Dutch),     ":/jsons/nl.json");
    s_hash.insert(QLocale::languageToString(QLocale::Uzbek)
           + "-" + QLocale::scriptToString(QLocale::LatinScript),":/jsons/uz-latn.json");
    s_hash.insert(QLocale::languageToString(QLocale::Estonian),  ":/jsons/ee.json");
    s_hash.insert(QLocale::languageToString(QLocale::Portuguese),":/jsons/pt.json");
    s_hash.insert(QLocale::languageToString(QLocale::Khmer),     ":/jsons/km.json");
    s_hash.insert(QLocale::languageToString(QLocale::Sinhala),   ":/jsons/si.json");
    s_hash.insert(QLocale::languageToString(QLocale::Spanish),   ":/jsons/es.json");
    s_hash.insert(QLocale::languageToString(QLocale::Tamil),     ":/jsons/ta.json");
    s_hash.insert(QLocale::languageToString(QLocale::Kannada),":/jsons/kn.json");
    s_hash.insert(QLocale::languageToString(QLocale::Bengali),":/jsons/bn.json");
    s_hash.insert(QLocale::languageToString(QLocale::Swahili),":/jsons/sw.json");
    s_hash.insert(QLocale::languageToString(QLocale::Malayalam),":/jsons/ml.json");
    s_hash.insert(QLocale::languageToString(QLocale::Gujarati),":/jsons/gu.json");
    s_hash.insert(QLocale::languageToString(QLocale::Telugu),":/jsons/te.json");
    s_hash.insert(QLocale::languageToString(QLocale::Marathi),":/jsons/mr.json");
    s_hash.insert(QLocale::languageToString(QLocale::Assamese),":/jsons/as.json");
    s_hash.insert(QLocale::languageToString(QLocale::Punjabi),":/jsons/pa.json");
    s_hash.insert(QLocale::languageToString(QLocale::Oriya),":/jsons/or.json");
    s_hash.insert(QLocale::languageToString(QLocale::Urdu),":/jsons/ur.json");
    s_hash.insert(QLocale::languageToString(QLocale::Hausa),":/jsons/ha.json");
    s_hash.insert(QLocale::languageToString(QLocale::Azerbaijani),":/jsons/az.json");
    s_hash.insert(QLocale::languageToString(QLocale::Afrikaans),":/jsons/af.json");
    s_hash.insert(QLocale::languageToString(QLocale::Irish),     ":/jsons/ie.json");
    s_hash.insert(QLocale::languageToString(QLocale::Latvian),   ":/jsons/lv.json");
    s_hash.insert(QLocale::languageToString(QLocale::Maori),     ":/jsons/mi.json");
    // Uzbek cyril and latin should be treated differently.
    s_hash.insert(QLocale::languageToString(QLocale::Uzbek)
            + "-" + QLocale::scriptToString(QLocale::CyrillicScript), ":/jsons/uz-cyrl.json");
    s_hash.insert(QLocale::languageToString(QLocale::Indonesian),":/jsons/id.json");
    s_hash.insert(QLocale::languageToString(QLocale::Malay),     ":/jsons/ms.json");    
    s_hash.insert(QLocale::languageToString(QLocale::Armenian),":/jsons/hy.json");
    s_hash.insert(QLocale::languageToString(QLocale::Bashkir),":/jsons/ba.json");
    s_hash.insert(QLocale::languageToString(QLocale::Icelandic),   ":/jsons/is.json");
    s_hash.insert(QLocale::languageToString(QLocale::Belarusian),   ":/jsons/be.json");
    s_hash.insert(QLocale::languageToString(QLocale::Catalan),   ":/jsons/ca.json");
    s_hash.insert(QLocale::languageToString(QLocale::Igbo),   ":/jsons/ig.json");
    s_hash.insert(QLocale::languageToString(QLocale::Kirghiz),   ":/jsons/ky.json");
    s_hash.insert(QLocale::languageToString(QLocale::Luxembourgish),   ":/jsons/lb.json");
    s_hash.insert(QLocale::languageToString(QLocale::Maltese),   ":/jsons/mt.json");
    s_hash.insert(QLocale::languageToString(QLocale::Nepali),   ":/jsons/ne.json");
    s_hash.insert(QLocale::languageToString(QLocale::NorthernSotho),   ":/jsons/nso.json");
    s_hash.insert(QLocale::languageToString(QLocale::Tajik),   ":/jsons/tg.json");
    s_hash.insert(QLocale::languageToString(QLocale::Pashto),   ":/jsons/ps.json");
    s_hash.insert(QLocale::languageToString(QLocale::Tatar),   ":/jsons/tt.json");
    s_hash.insert(QLocale::languageToString(QLocale::Turkmen),   ":/jsons/tk.json");
    s_hash.insert(QLocale::languageToString(QLocale::Uighur),   ":/jsons/ug.json");
    s_hash.insert(QLocale::languageToString(QLocale::Wolof),   ":/jsons/wo.json");
    s_hash.insert(QLocale::languageToString(QLocale::Yoruba),   ":/jsons/yo.json");
    s_hash.insert(QLocale::languageToString(QLocale::Lao),   ":/jsons/lo.json");
    s_hash.insert(QLocale::languageToString(QLocale::Georgian),   ":/jsons/ka.json");
    s_hash.insert(QLocale::languageToString(QLocale::Burmese),   ":/jsons/my.json");
    s_hash.insert(QLocale::languageToString(QLocale::Welsh),   ":/jsons/cy.json");
    s_hash.insert(QLocale::languageToString(QLocale::Zulu),   ":/jsons/zu.json");
    s_hash.insert(QLocale::languageToString(QLocale::Somali),   ":/jsons/so.json");
}

const QString LayoutLoader::getFileName(QString language)
{
    StringHash::const_iterator it = s_hash.find(language);
    if (it == s_hash.end())
        return "";
    else
        return it.value();
}

bool LayoutLoader::setLanguage(QString language)
{
    if (language == m_language)
        return true;

    /* read json file */
    QFile file;
    QJsonDocument doc;
    QString fileName = getFileName(language);
    file.setFileName(fileName);

    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qWarning() << "@@@@ cannot open json file: " << fileName;
    }

    doc = QJsonDocument::fromJson(file.readAll());
    file.close();

    if (doc.isNull()) {
        qWarning() << "@@@@ json file is invalid: " << fileName;
        return false;
    }

    /* convert to json-object */
    QJsonObject obj = doc.object();
    if (obj.isEmpty()) {
        qWarning() << "@@@@ json object is invalid: " << fileName;
        return false;
    }

    m_language = language;

    //TODO: convert to our structure. Now QML converts it. Move it here!
    makeLayout(obj);
    return true;
}

QJsonObject LayoutLoader::getLayout() const
{
    return m_json;
}

void LayoutLoader::makeLayout(QJsonObject src)
{
    int length, row, column;

    row    = src.find("Normal_keys").value().toObject().find("Row").value().toString().toInt();
    column = src.find("Normal_keys").value().toObject().find("Col").value().toString().toInt();
    length = row * column;

    QJsonArray normalKeys = src.find("Normal_keys").value().toObject().find("Key").value().toArray();
    QJsonArray::iterator itNormalKeys = normalKeys.begin();
    QJsonArray shiftKeys = src.find("Shift_keys").value().toObject().find("Key").value().toArray();
    QJsonArray::iterator itShiftKeys = shiftKeys.begin();
    QJsonArray expandKeys = src.find("Expand_keys").value().toObject().find("Key").value().toArray();
    QJsonArray::iterator itExpandKeys = expandKeys.begin();
    QJsonArray expandShiftKeys = src.find("Expand_shift_keys").value().toObject().find("Key").value().toArray();
    QJsonArray::iterator itExpandShiftKeys = expandShiftKeys.begin();

    QJsonArray keys;
    QJsonObject obj;
    QJsonValue val;
    int cntExpandKey = 0, cntExpandShiftKey = 0;

    for (int i = 0; i < length; ++i) {
        obj = QJsonObject();

        /* from Normal_keys.Key[] */
        // if (index == -1) ignore
        while(itNormalKeys != normalKeys.end()) {
            val = (*itNormalKeys).toObject().find("index").value();
            if (!val.isNull() && val.toString() != "-1") {
                break;
            }
            else
                ++itNormalKeys;
        }
        val = (*itNormalKeys).toObject().find("keylabel").value();
        obj.insert("mainChar",  val.isString() ? val : QJsonValue(EMPTY_STRING));
        val = (*itNormalKeys).toObject().find("rawcode").value();
        obj.insert("rawcode", val.isString() ? val : QJsonValue(-1));
        val = (*itNormalKeys).toObject().find("forcetext").value();
        obj.insert("forceText",     val.isBool() ? val : QJsonValue(false));
        val = (*itNormalKeys).toObject().find("keysym").value();
        obj.insert("normalKeysym", val.isString() ? val : QJsonValue(-1));

        /* from Shift_keys.Key[] */
        while(itShiftKeys != shiftKeys.end()) {
            val = (*itShiftKeys).toObject().find("index").value();
            if (!val.isNull() && val.toString() != "-1")
                break;
            else
                ++itShiftKeys;
        }
        val = (*itShiftKeys).toObject().find("keylabel").value();
        obj.insert("shiftedChar", val.isString() ? val : QJsonValue(EMPTY_STRING));
        val = (*itShiftKeys).toObject().find("rawcode").value();
        obj.insert("shiftRawcode", val.isString() ? val : QJsonValue(-1));
        val = (*itShiftKeys).toObject().find("keysym").value();
        obj.insert("shiftKeysym", val.isString() ? val : QJsonValue(-1));

        /* from Expand_keys.Key[] */
        while(itExpandKeys != expandKeys.end()) {
            val = (*itExpandKeys).toObject().find("index").value();
            if (!val.isNull() && val.toString() != "-1")
                break;
            else
                ++itExpandKeys;
        }
        if (itExpandKeys != expandKeys.end()) {
            val = (*itExpandKeys).toObject().find("keylabel").value();
            if (val.isString() && (val.toString() != EMPTY_STRING)) {
                obj.insert("expandChar", val.isString() ? val : QJsonValue(EMPTY_STRING));
                val = (*itExpandKeys).toObject().find("keycode").value();
                obj.insert("expandRawcode", val.isString() ? val : QJsonValue(-1));
                val = (*itExpandKeys).toObject().find("keysym").value();
                obj.insert("expandKeysym", val.isString() ? val : QJsonValue(-1));
                ++cntExpandKey;
            }
        }

        /* from Expand_shift_keys.Key[] */
        while(itExpandShiftKeys != expandShiftKeys.end()) {
            val = (*itExpandShiftKeys).toObject().find("index").value();
            if (!val.isNull() && val.toString() != "-1")
                break;
            else
                ++itExpandShiftKeys;
        }
        if (itExpandShiftKeys != expandKeys.end()) {
            val = (*itExpandShiftKeys).toObject().find("keylabel").value();
            if (val.isString() && (val.toString() != EMPTY_STRING)) {
                obj.insert("expandShiftedChar", val.isString() ? val : QJsonValue(EMPTY_STRING));
                val = (*itExpandShiftKeys).toObject().find("keycode").value();
                obj.insert("expandShiftRawcode", (!val.isNull() && val.isString()) ? val : QJsonValue(-1));
                val = (*itExpandShiftKeys).toObject().find("keysym").value();
                obj.insert("expandShiftKeysym", val.isString() ? val : QJsonValue(-1));
                ++cntExpandShiftKey;
            }
        }

        keys.push_back(QJsonValue(obj));

        ++itNormalKeys;
        ++itShiftKeys;
        ++itExpandKeys;
        ++itExpandShiftKeys;
    }

    /* make json object */
    QJsonObject dst;
    dst.insert(QString("language"), QJsonValue(m_language));
    dst.insert(QString("length"), QJsonValue(length));
    dst.insert(QString("row"),    QJsonValue(row));
    dst.insert(QString("column"), QJsonValue(column));
    dst.insert(QString("keys"),   QJsonValue(keys));

    if (cntExpandKey > 0)
        dst.insert(QString("supportAccent"), QJsonValue(true));
    else
        dst.insert(QString("supportAccent"), QJsonValue(false));

    if (cntExpandShiftKey > 0)
        dst.insert(QString("supportAccentEx"), QJsonValue(true));
    else
        dst.insert(QString("supportAccentEx"), QJsonValue(false));

    m_json = dst;

    QJsonObject::iterator itSep = src.find("suggestion_separator");
    if (itSep == src.end())
        m_separator = QString(" ");
    else
        m_separator = itSep.value().toString();
}

QString LayoutLoader::getLanguage() const
{
    return m_language;
}

QString LayoutLoader::getSeparator() const
{
    return m_separator;
}

bool LayoutLoader::operator==(const LayoutLoader &l) const
{
    return (l.getLanguage() == m_language) ? true : false;
}

