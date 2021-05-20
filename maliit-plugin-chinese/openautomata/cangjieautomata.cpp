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

#include <QFile>
#include <QList>
#include "cangjieautomata.h"
#include "languages.h"
#include "chinesekeymap.h"

static const QString DIC_PATH = QString("%1%2").arg(IMEMANAGER_RESOURCE_PATH).arg("/dict/");
static const int MAX_PRE_EDIT_LENGTH = 16;
static const int CANDIDATE_WINDOW_LENGTH = 8;

CangjieAutomata::CangjieAutomata()
{
    init();
}

bool CangjieAutomata::init()
{
    QFile file(DIC_PATH +"cangjie.dic");
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Couldn't able to read the dictionary " << "cangjie.dic";
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

    m_preMap[Qt::Key_Q] = "手";
    m_preMap[Qt::Key_W] = "田";
    m_preMap[Qt::Key_E] = "水";
    m_preMap[Qt::Key_R] = "口";
    m_preMap[Qt::Key_T] = "廿";
    m_preMap[Qt::Key_Y] = "卜";
    m_preMap[Qt::Key_U] = "山";
    m_preMap[Qt::Key_I] = "戈";
    m_preMap[Qt::Key_O] = "人";
    m_preMap[Qt::Key_P] = "心";
    m_preMap[Qt::Key_A] = "日";
    m_preMap[Qt::Key_S] = "尸";
    m_preMap[Qt::Key_D] = "木";
    m_preMap[Qt::Key_F] = "火";
    m_preMap[Qt::Key_G] = "土";
    m_preMap[Qt::Key_H] = "竹";
    m_preMap[Qt::Key_J] = "十";
    m_preMap[Qt::Key_K] = "大";
    m_preMap[Qt::Key_L] = "中";
    m_preMap[Qt::Key_Z] = "重";
    m_preMap[Qt::Key_X] = "難";
    m_preMap[Qt::Key_C] = "金";
    m_preMap[Qt::Key_V] = "女";
    m_preMap[Qt::Key_B] = "月";
    m_preMap[Qt::Key_N] = "弓";
    m_preMap[Qt::Key_M] = "一";

    m_shift = false;
    m_preedit.clear();
    m_preAlpha.clear();
    m_curPage = 0;
    m_curSuggestions.clear();
    m_totSuggestions.clear();
    return true;
}

CangjieAutomata::~CangjieAutomata()
{
   reset();
}

bool CangjieAutomata::isNextSuggestionsAvailable()
{
    int total = getCandidatesNum();
    int noOfSuggestions = getPreedit().length() > 8 ? 2 : CANDIDATE_WINDOW_LENGTH;
    return total > 0 && (m_curPage+1) * noOfSuggestions  <  total;
}

bool CangjieAutomata::isPreviousSuggestionsAvailable()
{
    return getCandidatesNum() > 0 && m_curPage != 0;
}

void CangjieAutomata::nextSuggestions()
{
    if (isNextSuggestionsAvailable()) {
        m_curPage++;
    }
}

void CangjieAutomata::previousSuggestions()
{
    if (isPreviousSuggestionsAvailable()) {
        m_curPage--;
    }
}

void CangjieAutomata::reset()
{
    m_preedit.clear();
    m_preAlpha.clear();
    m_commit.clear();
    m_totSuggestions.clear();
    m_curSuggestions.clear();
    m_curPage = 0;
}

bool CangjieAutomata::isComposing()
{
    return false;
}

QString CangjieAutomata::getCommit()
{
    return m_commit;
}

QString CangjieAutomata::getPreedit()
{
    return m_preedit;
}

void CangjieAutomata::shifted(bool shift)
{
    m_shift = shift;
}

bool CangjieAutomata::isShifted()
{
    return m_shift;
}

bool CangjieAutomata::setLanguage(const QString &language)
{
    m_language = language;
    return true;
}

QString CangjieAutomata::getLanguage()
{
    return m_language;
}

void CangjieAutomata::suggestionSelected(int index)
{
    m_commit = m_curSuggestions[index];
    m_curPage = 0;
    m_preedit.clear();
    m_preAlpha.clear();
    m_totSuggestions.clear();
    m_curSuggestions.clear();
}

bool CangjieAutomata::isDirectInput(Qt::Key keycode)
{
    return isDirectInputKey(keycode);
}

quint32 CangjieAutomata::chineseSymbolKeyMapping(Qt::Key keycode)
{
    return chineseSymbolUnicodeKey(keycode);
}

bool CangjieAutomata::processKeyEvent(Qt::Key keycode, Qt::KeyboardModifiers modifiers)
{
    Q_UNUSED(modifiers);

    if (!((keycode >= Qt::Key_A && keycode <= Qt::Key_Z) || (keycode == Qt::Key_Backspace))) {
         return false;
    }

    if (keycode == Qt::Key_Backspace) {
        m_preedit.chop(1);
        m_preAlpha.chop(1);
    } else if (m_preedit.length() < MAX_PRE_EDIT_LENGTH) {
        m_preedit += m_preMap[keycode];
        m_preAlpha += QChar(keycode);
    }

    m_curPage = 0;
    m_totSuggestions.clear();
    m_curSuggestions.clear();
    m_trie.subStrings(m_preAlpha,m_totSuggestions);
    return true;
}

QStringList CangjieAutomata::getSuggestionList()
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

int CangjieAutomata::getCandidatesNum()
{
    return m_totSuggestions.size();
}

int CangjieAutomata::getStrokeComponentCount()
{
    return 0;
}

void CangjieAutomata::strokeComponentSelected(int index)
{
    Q_UNUSED(index);
}

QStringList CangjieAutomata::getStrokeComponentList()
{
    QStringList stroke;
    return stroke;
}

