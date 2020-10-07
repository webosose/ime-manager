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


#include "wordpredict.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QList>
#include <QMap>
#include <QMultiMap>
#include <QtAlgorithms>
#include <QDir>

class WordCount
{
public:
    WordCount(QString w, int f) : word(w), frequncy(f) {}
    QString word;
    int frequncy;
};

static const QString DIC_PATH = QString("%1%2").arg(IMEMANAGER_RESOURCE_PATH).arg("/dict/");
static const QString UDIC_PATH = QString("%1%2").arg(IMEMANAGER_USER_DICTIONARY_PATH).arg("/dict/");
static QString convertCase(QString word,const QString &prefix);
static bool caseSensitiveLessThan(const WordCount &w1, const WordCount &w2);
static bool caseInsensitiveLessThan(const WordCount &w1, const WordCount &w2);

WordPredict::WordPredict()
{
}

WordPredict::~WordPredict()
{
    storeUserWords();
}

bool WordPredict::init()
{
    freqWordList.clear();
    userWordList.clear();
    QFile file(DIC_PATH + m_language + ".dic");

    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Couldn't able to read the dictionary " << m_language << ".dic";
        file.close();
        return false;
    }

    QTextStream in (&file);
    in.setCodec("UTF-8");

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(" ");
        freqWordList.append(WordCount(fields[0],fields[1].toInt()));
    }
    file.close();

    QFile userWordFile(UDIC_PATH + m_language + "_user.dic");
    if (userWordFile.open(QIODevice::ReadOnly)) {
        QTextStream in (&userWordFile);
        in.setCodec("UTF-8");

        while(!in.atEnd()) {
            QString line = in.readLine();
            QStringList fields = line.split(" ");
            userWordList.append(WordCount(fields[0],fields[1].toInt()));
        }
    }
    userWordFile.close();
    return true;
}

bool WordPredict::contains(const QString &word)
{
    return freqWordList.end() != qBinaryFind(freqWordList.begin(), freqWordList.end(),
                                              WordCount(word,0), caseSensitiveLessThan);
}

void WordPredict::addWord(const QString &word)
{
    if (word.length() > 2 && !contains(word)) {
        WordCount wCount(word,1);
        QList<WordCount>::iterator it;
        it = qLowerBound(userWordList.begin(), userWordList.end(), wCount, caseSensitiveLessThan);
        if (it != userWordList.end() && it->word == word) {
            it->frequncy++;
        } else {
            userWordList.insert(it, wCount);
        }
    }
}

void WordPredict::storeUserWords()
{
    if (!userWordList.isEmpty()) {
        QDir().mkpath(UDIC_PATH);
        QFile userWordFile(UDIC_PATH + m_language + "_user.dic");
        bool openFlag = userWordFile.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text);
	if(openFlag) {
            QTextStream out (&userWordFile);
            out.setCodec("UTF-8");
            QList<WordCount>::iterator it = userWordList.begin();
            while (it != userWordList.end()) {
                out << it->word << " " << it->frequncy << endl;
                ++it;
            }
            userWordFile.close();
	}
    }
}

bool WordPredict::setLanguage(const QString &language)
{
    storeUserWords();
    m_language = language;
    return init();
}

QStringList WordPredict::getPredictionList(const QString &prefix)
{
    QStringList suggestionList;

    QMultiMap<int,QString> frequencyList;
    QMultiMap<int,QString> userFrequencyList;

    int prefixLimit = m_language == QLocale::languageToString(QLocale::Korean) ? 1 : 2;
    if (prefix.length() < prefixLimit)
        return suggestionList;

    WordCount wCount(prefix,0);
    bool caseSensitive = (m_language == QLocale::languageToString(QLocale::Russian) ||
                          m_language == QLocale::languageToString(QLocale::German)  ||
                          m_language == QLocale::languageToString(QLocale::Korean));

    QList<WordCount>::iterator it;
    it = qLowerBound(freqWordList.begin(), freqWordList.end(), wCount,
                     caseSensitive?caseSensitiveLessThan:caseInsensitiveLessThan);
    while (it != freqWordList.end()) {
        if (!it->word.startsWith(prefix, caseSensitive?Qt::CaseSensitive:Qt::CaseInsensitive)) break;
        if (it->word != prefix) {
            frequencyList.insert(it->frequncy,it->word);
        }
        ++it;
    }

    it = qLowerBound(userWordList.begin(), userWordList.end(), wCount,
                     caseSensitive?caseSensitiveLessThan:caseInsensitiveLessThan);
    while (it != userWordList.end()) {
        if (!it->word.startsWith(prefix,caseSensitive?Qt::CaseSensitive:Qt::CaseInsensitive)) {
            break;
        }
        if (it->word != prefix && it->frequncy > 2) {
            userFrequencyList.insert(it->frequncy,it->word);
        }
        ++it;
    }

    QMap<int,QString>::const_iterator i;
    for (i = frequencyList.constBegin(); i != frequencyList.constEnd(); ++i) {
        suggestionList.prepend(convertCase(i.value(),prefix));
    }
    for (i = userFrequencyList.constBegin(); i != userFrequencyList.constEnd(); ++i) {
        suggestionList.prepend(convertCase(i.value(),prefix));
    }

    return suggestionList;
}

static bool caseInsensitiveLessThan(const WordCount &w1, const WordCount &w2)
{
    return w1.word.compare(w2.word,Qt::CaseInsensitive) < 0;
}

static bool caseSensitiveLessThan(const WordCount &w1, const WordCount &w2)
{
    return w1.word.compare(w2.word,Qt::CaseSensitive) < 0;
}

static QString convertCase(QString word,const QString &prefix)
{
    int i=0;
    bool upper = true;
    for(;i<prefix.size(); ++i) {
        if (prefix[i].isUpper()) {
            word[i] = word[i].toUpper();
        } else {
            upper = false;
        }
    }
    if (upper) {
        for(;i<word.size(); ++i) {
            word[i] = word[i].toUpper();
        }
    }
    return word;
}
