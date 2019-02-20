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

#include "chineseautomata.h"
#include "languages.h"
#include "chinesekeymap.h"
#include <QDebug>

ChineseAutomata::ChineseAutomata()
{
    m_automata.reset(new SunpinyinAutomata);
    m_shifted = false;
}

ChineseAutomata::~ChineseAutomata()
{
    m_automata.reset();
}

bool ChineseAutomata::isNextSuggestionsAvailable()
{
    return m_automata->isNextSuggestionsAvailable();
}

bool ChineseAutomata::isPreviousSuggestionsAvailable()
{
    return m_automata->isPreviousSuggestionsAvailable();
}

void ChineseAutomata::nextSuggestions()
{
    m_automata->nextSuggestions();
}

void ChineseAutomata::previousSuggestions()
{
   m_automata->previousSuggestions();
}

void ChineseAutomata::reset()
{
    if (!m_automata.isNull()) m_automata->reset();
}

bool ChineseAutomata::isComposing()
{
    return m_automata->isComposing();
}

QString ChineseAutomata::getCommit()
{
    return m_automata->getCommit();
}

QString ChineseAutomata::getPreedit()
{
    return m_automata->getPreedit();
}

void ChineseAutomata::shifted(bool shift)
{
    QString language = m_automata->getLanguage();
    if (language.length() == 0) return;
    if (language == LanguageConstants::SIMPLIFIED_CHINESE) {
        if (shift) {
            m_automata.reset(new StrokeAutomata);
        }  else {
            m_automata.reset(new SunpinyinAutomata);
        }
    } else {
        if (shift) {
            m_automata.reset(new PyzyAutomata);
        } else {
            m_automata.reset(new CangjieAutomata);
        }
    }
    m_shifted = shift;
    m_automata->setLanguage(language);
    m_automata->shifted(shift);
}

bool ChineseAutomata::isShifted()
{
    return m_shifted;
}

bool ChineseAutomata::setLanguage(const QString &language)
{
    if (language == LanguageConstants::SIMPLIFIED_CHINESE) {
        m_automata.reset(new SunpinyinAutomata);
    } else {
        m_automata.reset(new CangjieAutomata);
    }
    return m_automata->setLanguage(language);
}

QString ChineseAutomata::getLanguage()
{
    return m_automata->getLanguage();
}

void ChineseAutomata::suggestionSelected(int index)
{
    m_automata->suggestionSelected(index);
}

void ChineseAutomata::strokeComponentSelected(int index)
{
    m_automata->strokeComponentSelected(index);
}

bool ChineseAutomata::isDirectInput(Qt::Key keycode)
{
    return m_automata->isDirectInput(keycode);
}

quint32 ChineseAutomata::chineseSymbolKeyMapping(Qt::Key keycode)
{
    return m_automata->chineseSymbolKeyMapping(keycode);
}

bool ChineseAutomata::processKeyEvent(Qt::Key keycode, Qt::KeyboardModifiers modifiers)
{
   return m_automata->processKeyEvent(keycode,modifiers);
}

QStringList ChineseAutomata::getSuggestionList()
{
    return m_automata->getSuggestionList();
}

int ChineseAutomata::getCandidatesNum()
{
    return m_automata->getCandidatesNum();
}

int ChineseAutomata::getStrokeComponentCount()
{
    return m_automata->getStrokeComponentCount();
}

QStringList ChineseAutomata::getStrokeComponentList()
{
   return m_automata->getStrokeComponentList();
}
