// Copyright (c) 2017-2024 LG Electronics, Inc.
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

#include <QFile>
#include <QList>
#include "strokeautomata.h"
#include "languages.h"
#include "chinesekeymap.h"

static const QString DIC_PATH = QString("%1%2").arg(IMEMANAGER_RESOURCE_PATH).arg("/dict/");
static const int MAX_PRE_EDIT_LENGTH = 16;
static const int CANDIDATE_WINDOW_LENGTH = 8;

StrokeAutomata::StrokeAutomata()
{
    init();
}

bool StrokeAutomata::init()
{
    if (!loadStroke()) return false;
    if (!loadCompoList()) return false;
    if (!loadCompoSuggestion()) return false;
    if (!loadCompoAlpha()) return false;

    m_preMap[(Qt::Key)0x4E00]  = 'h';
    m_preMap[(Qt::Key)0x4E28]  = 's';
    m_preMap[(Qt::Key)0x4E3F]  = 'p';
    m_preMap[(Qt::Key)0x4E36]  = 'n';
    m_preMap[(Qt::Key)0x4E5B]  = 'z';

    m_shift = false;
    m_compoActive.clear();
    m_preedit.clear();
    m_preAlpha.clear();
    m_curPage = 0;
    m_curSuggestions.clear();
    m_totSuggestions.clear();
    m_preStack.clear();
    return true;
}

bool StrokeAutomata::loadStroke()
{
    QFile file(DIC_PATH +"stroke.dic");
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Couldn't able to read the dictionary " << "stroke.dic";
        file.close();
        return false;
    }
    QTextStream in (&file);
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    in.setCodec("UTF-8");
#endif
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(" ");
        m_trie.add(fields[0],fields[1]);
    }
    file.close();
    return true;
}

bool StrokeAutomata::loadCompoList()
{
    QFile file(DIC_PATH +"strokeCompoList.dic");
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Couldn't able to read the dictionary " << "strokeCompoList.dic";
        file.close();
        return false;
    }
    QTextStream in (&file);
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    in.setCodec("UTF-8");
#endif
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(" ");
        int len = fields[1].toInt();
        QStringList compoList;
        for (int i=0; i<len; ++i) {
            compoList.append(in.readLine());
        }
        m_compoMap[fields[0]] = compoList;
    }
    file.close();
    return true;
}

bool StrokeAutomata::loadCompoSuggestion()
{
    QFile file(DIC_PATH +"compoListSuggestion.dic");
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Couldn't able to read the dictionary " << "compoListSuggestion.dic";
        file.close();
        return false;
    }
    QTextStream in (&file);
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    in.setCodec("UTF-8");
#endif
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(" ");
        int len = fields[1].toInt();
        QSet<QString> suggSet;
        for (int i=0; i<len; ++i) {
            suggSet.insert(in.readLine());
        }
        m_compoSuggMap[fields[0]] = suggSet;
    }
    file.close();
    return true;
}

bool StrokeAutomata::loadCompoAlpha()
{
    QFile file(DIC_PATH +"commap.dic");
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Couldn't able to read the dictionary " << "commap.dic";
        file.close();
        return false;
    }
    QTextStream in (&file);
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    in.setCodec("UTF-8");
#endif
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(" ");
        m_compoAlphaMap[fields[0]] = fields[1];
    }
    file.close();
    return true;
}

StrokeAutomata::~StrokeAutomata()
{
   reset();
}

bool StrokeAutomata::isNextSuggestionsAvailable()
{
    int total = getCandidatesNum();
    int noOfSuggestions = getPreedit().length() > 8 ? 2 : CANDIDATE_WINDOW_LENGTH;
    return total > 0 && (m_curPage+1) * noOfSuggestions  <  total;
}

bool StrokeAutomata::isPreviousSuggestionsAvailable()
{
    return getCandidatesNum() > 0 && m_curPage != 0;
}

void StrokeAutomata::nextSuggestions()
{
    if (isNextSuggestionsAvailable()) {
        m_curPage++;
    }
}

void StrokeAutomata::previousSuggestions()
{
    if (isPreviousSuggestionsAvailable()) {
        m_curPage--;
    }
}

void StrokeAutomata::reset()
{
    m_preedit.clear();
    m_preAlpha.clear();
    m_commit.clear();
    m_compoActive.clear();
    m_totSuggestions.clear();
    m_curSuggestions.clear();
    m_preStack.clear();
    m_curPage = 0;
}

bool StrokeAutomata::isComposing()
{
    return m_preedit.size() > 0;
}

QString StrokeAutomata::getCommit()
{
    return m_commit;
}

QString StrokeAutomata::getPreedit()
{
    return m_preedit;
}

void StrokeAutomata::shifted(bool shift)
{
    m_shift = shift;
}

bool StrokeAutomata::isShifted()
{
    return m_shift;
}

bool StrokeAutomata::setLanguage(const QString &language)
{
    m_language = language;
    return true;
}

QString StrokeAutomata::getLanguage()
{
    return m_language;
}

void StrokeAutomata::suggestionSelected(int index)
{
    m_commit = m_curSuggestions[index];
    m_curPage = 0;
    m_compoActive.clear();
    m_preedit.clear();
    m_preAlpha.clear();
    m_totSuggestions.clear();
    m_curSuggestions.clear();
    m_preStack.clear();
}

bool StrokeAutomata::isDirectInput(Qt::Key keycode)
{
    return isDirectInputKey(keycode);
}

quint32 StrokeAutomata::chineseSymbolKeyMapping(Qt::Key keycode)
{
    return chineseSymbolUnicodeKey(keycode);
}

bool StrokeAutomata::filter(const QString &c)
{
    return m_compoActive.isEmpty()? true : m_compoSuggMap[m_compoActive].contains(c);
}

bool StrokeAutomata::processKeyEvent(Qt::Key keycode, Qt::KeyboardModifiers modifiers)
{
    Q_UNUSED(modifiers);

    if (keycode != Qt::Key_Backspace && !m_preMap.contains(keycode)) return false;

    if (keycode == Qt::Key_Backspace) {
        if (m_preAlpha == m_compoAlphaMap[m_compoActive]) {
            m_compoActive.clear();
        }
        QPair<QString,QString> pair = getFromStack();
        m_preedit = pair.first;
        m_preAlpha = pair.second;
    } else if (m_preedit.length() < MAX_PRE_EDIT_LENGTH) {
        addToStack(m_preedit,m_preAlpha);
        m_preedit += QChar((char16_t)keycode);
        m_preAlpha += m_preMap[keycode];
    }

    m_curPage = 0;
    m_totSuggestions.clear();
    m_curSuggestions.clear();
    m_trie.subStrings(m_preAlpha,m_totSuggestions,*this);
    return true;
}

QStringList StrokeAutomata::getSuggestionList()
{
    m_curSuggestions.clear();

    int totalSize = getCandidatesNum();

    if (totalSize == 0)
        return m_curSuggestions;

    int noOfSuggestions = getPreedit().length() > 8 ? 2 : CANDIDATE_WINDOW_LENGTH;
    int start  = m_curPage * noOfSuggestions;
    int end    =  start + noOfSuggestions < totalSize ? start + noOfSuggestions : start + (totalSize - start);

    for (int i=start; i<end; ++i) {
        m_curSuggestions << m_totSuggestions[i];
    }
    return m_curSuggestions;
}

int StrokeAutomata::getCandidatesNum()
{
    return m_totSuggestions.size();
}

int StrokeAutomata::getStrokeComponentCount()
{
    return m_compoMap[m_preedit].size();
}

void StrokeAutomata::strokeComponentSelected(int index)
{
    QStringList compoList = getStrokeComponentList();
    QSet<QString> compoSuggSet = m_compoSuggMap[compoList[index]];
    m_curPage = 0;
    QStringList tmpTotSugg;
    for (int i=0; i<m_totSuggestions.size(); ++i) {
        if (compoSuggSet.contains(m_totSuggestions[i])) {
            tmpTotSugg << m_totSuggestions[i];
        }
    }
    m_totSuggestions.clear();
    for (int i=0; i<tmpTotSugg.size(); ++i) {
        m_totSuggestions << tmpTotSugg[i];
    }
    m_commit.clear();
    m_compoActive = compoList[index];
    addToStack(m_preedit,m_preAlpha);
    m_preedit = m_compoActive;
    m_preAlpha = m_compoAlphaMap[m_compoActive];
}

void StrokeAutomata::addToStack(QString preedit, QString preAlpha)
{
    if (preedit.size() == 0) return;
    QPair<QString, QString> pair;
    pair.first = preedit;
    pair.second = preAlpha;
    m_preStack.push(pair);
}

QPair<QString,QString> StrokeAutomata::getFromStack()
{
    if (m_preStack.isEmpty()) {
        QPair<QString, QString> pair;
        return pair;
    }
    return m_preStack.pop();
}

QStringList StrokeAutomata::getStrokeComponentList()
{
    return m_compoMap[m_preedit];
}

