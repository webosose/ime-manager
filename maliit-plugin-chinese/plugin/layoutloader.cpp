// Copyright (c) 2017-2019 LG Electronics, Inc.
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
#include "languages.h"

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

LayoutLoader::LayoutLoader() {
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
    m_json = QJsonObject(l.getLayout());

    return *this;
}

LayoutLoader::~LayoutLoader()
{
}

void LayoutLoader::initFileTable() {
    s_hash.insert(LanguageConstants::SIMPLIFIED_CHINESE, ":/jsons/zh-Hans.json");
#ifdef ENABLE_OPEN_AUTOMATA
   s_hash.insert(LanguageConstants::TRADITIONAL_CHINESE, ":/jsons/open/zh-Hant.json");
#else
   s_hash.insert(LanguageConstants::TRADITIONAL_CHINESE, ":/jsons/zh-Hant.json");
#endif
    s_hash.insert(LanguageConstants::TRADITIONAL_CHINESE_TW,":/jsons/zh-Hant-tw.json");
    s_hash.squeeze();
}

const QString LayoutLoader::getFileName(QString language) {
    StringHash::const_iterator it = s_hash.find(language);
    if (it == s_hash.end())
        return "";
    else
        return it.value();
}

bool LayoutLoader::setLanguage(QString language) {
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

QJsonObject LayoutLoader::getLayout() const {
    return m_json;
}

void LayoutLoader::makeLayout(QJsonObject src) {
    int length, row, column;

    row    = src.value("Normal_keys").toObject().value("Row").toString().toInt();
    column = src.value("Normal_keys").toObject().value("Col").toString().toInt();
    length = row * column;

    QJsonArray normalKeys = src.value("Normal_keys").toObject().value("Key").toArray();
    QJsonArray::iterator itNormalKeys = normalKeys.begin();
    QJsonArray shiftKeys = src.value("Shift_keys").toObject().value("Key").toArray();
    QJsonArray::iterator itShiftKeys = shiftKeys.begin();
    QJsonArray symbolKeys = src.value("Symbol_keys").toObject().value("Key").toArray();
    QJsonArray::iterator itSymbolKeys = symbolKeys.begin();

    QJsonArray keys;
    QJsonObject obj;
    QJsonValue val;

    for (int i = 0; i < length; ++i) {
        obj = QJsonObject();

        /* from Normal_keys.Key[] */
        while(itNormalKeys != normalKeys.end()) {
            val = (*itNormalKeys).toObject().value("index");
            if (!val.isNull() && val.toString() != "-1") {
                break;
            }
            else
                ++itNormalKeys;
        }
        auto normalKeysObj = itNormalKeys != normalKeys.end() ? itNormalKeys->toObject() : QJsonObject();
        val = normalKeysObj.value("keylabel");
        obj.insert("mainChar",  val.isString() ? val : QJsonValue(EMPTY_STRING));
        val = normalKeysObj.value("rawcode");
        obj.insert("rawcode", val.isString() ? val : QJsonValue(-1));

        /* from Shift_keys.Key[] */
        while(itShiftKeys != shiftKeys.end()) {
            val = (*itShiftKeys).toObject().value("index");
            if (!val.isNull() && val.toString() != "-1")
                break;
            else
                ++itShiftKeys;
        }
        auto shiftKeysObj = itShiftKeys != shiftKeys.end() ? itShiftKeys->toObject() : QJsonObject();
        val = shiftKeysObj.value("keylabel");
        obj.insert("shiftedChar", val.isString() ? val : QJsonValue(EMPTY_STRING));
        val = shiftKeysObj.value("rawcode");
        obj.insert("shiftRawcode", val.isString() ? val : QJsonValue(-1));

        /* from Symbol_keys.Key[] */
        while(itSymbolKeys != symbolKeys.end()) {
            val = (*itSymbolKeys).toObject().value("index");
            if (!val.isNull() && val.toString() != "-1")
                break;
            else
                ++itSymbolKeys;
        }
        auto symbolKeysObj = itSymbolKeys != symbolKeys.end() ? itSymbolKeys->toObject() : QJsonObject();
        val = symbolKeysObj.value("keylabel");
        obj.insert("symbolChar", val.isString() ? val : QJsonValue(EMPTY_STRING));

        keys.push_back(QJsonValue(obj));

        if (itNormalKeys != normalKeys.end()) ++itNormalKeys;
        if (itShiftKeys != shiftKeys.end()) ++itShiftKeys;
        if (itSymbolKeys != symbolKeys.end()) ++itSymbolKeys;
    }

    /* make json object */
    QJsonObject dst;
    dst.insert(QString("language"), QJsonValue(m_language));
    dst.insert(QString("length"), QJsonValue(length));
    dst.insert(QString("row"),    QJsonValue(row));
    dst.insert(QString("column"), QJsonValue(column));
    dst.insert(QString("keys"),   QJsonValue(keys));

    m_json = dst;
}

QString LayoutLoader::getLanguage() const
{
    return m_language;
}

bool LayoutLoader::operator==(const LayoutLoader &l) const
{
    return (l.getLanguage() == m_language) ? true : false;
}
