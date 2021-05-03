// Copyright (c) 2015-2018 LG Electronics, Inc.
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

#ifndef HINDI_AUTOMATA_H
#define HINDI_AUTOMATA_H

#include "automatabase.h"
#include <QLocale>

class HindiAutomata : public AutomataBase
{

public:
    HindiAutomata()
    {
        m_keymap.clear();
        m_keymap.insert(0x21,QString(QChar(0x90d)));
        m_keymap.insert(0x22,QString(QChar(0x920)));
        m_keymap.insert(0x23,QString("\u094d\u0930"));
        m_keymap.insert(0x24,QString("\u0930\u094D"));
        m_keymap.insert(0x25,QString("\u091c\u094D\u091E"));
        m_keymap.insert(0x26,QString("\u0915\u094D\u0937"));
        m_keymap.insert(0x27,QString(QChar(0x91f)));
        m_keymap.insert(0x28,QString(QChar(0x28)));
        m_keymap.insert(0x29,QString(QChar(0x29)));
        m_keymap.insert(0x2a,QString("\u0936\u094D\u0930"));
        m_keymap.insert(0x2b,QString(QChar(0x90B)));
        m_keymap.insert(0x2c,QString(QChar(0x2c)));
        m_keymap.insert(0x2d,QString(QChar(0x2d)));
        m_keymap.insert(0x2e,QString(QChar(0x2e)));
        m_keymap.insert(0x2f,QString(QChar(0x92f)));
        m_keymap.insert(0x30,QString(QChar(0x966)));
        m_keymap.insert(0x31,QString(QChar(0x967)));
        m_keymap.insert(0x32,QString(QChar(0x968)));
        m_keymap.insert(0x33,QString(QChar(0x969)));
        m_keymap.insert(0x34,QString(QChar(0x96A)));
        m_keymap.insert(0x35,QString(QChar(0x96B)));
        m_keymap.insert(0x36,QString(QChar(0x96C)));
        m_keymap.insert(0x37,QString(QChar(0x96D)));
        m_keymap.insert(0x38,QString(QChar(0x96E)));
        m_keymap.insert(0x39,QString(QChar(0x96F)));
        m_keymap.insert(0x3a,QString(QChar(0x91b)));
        m_keymap.insert(0x3b,QString(QChar(0x91A)));
        m_keymap.insert(0x3c,QString(QChar(0x937)));
        m_keymap.insert(0x3d,QString(QChar(0x943)));
        m_keymap.insert(0x3e,QString(QChar(0x964)));
        m_keymap.insert(0x3f,QString(QChar(0x95f)));
        m_keymap.insert(0x40,QString(QChar(0x945)));
        m_keymap.insert(0x41,QString(QChar(0x913)));
        m_keymap.insert(0x42,QString(QChar(0x934)));
        m_keymap.insert(0x43,QString(QChar(0x923)));
        m_keymap.insert(0x44,QString(QChar(0x905)));
        m_keymap.insert(0x45,QString(QChar(0x906)));
        m_keymap.insert(0x46,QString(QChar(0x907)));
        m_keymap.insert(0x47,QString(QChar(0x909)));
        m_keymap.insert(0x48,QString(QChar(0x92B)));
        m_keymap.insert(0x49,QString(QChar(0x918)));
        m_keymap.insert(0x4a,QString(QChar(0x931)));
        m_keymap.insert(0x4b,QString(QChar(0x916)));
        m_keymap.insert(0x4c,QString(QChar(0x925)));
        m_keymap.insert(0x4d,QString(QChar(0x936)));
        m_keymap.insert(0x4e,QString(QChar(0x933)));
        m_keymap.insert(0x4f,QString(QChar(0x927)));
        m_keymap.insert(0x50,QString(QChar(0x91d)));
        m_keymap.insert(0x51,QString(QChar(0x914)));
        m_keymap.insert(0x52,QString(QChar(0x908)));
        m_keymap.insert(0x53,QString(QChar(0x90f)));
        m_keymap.insert(0x54,QString(QChar(0x90A)));
        m_keymap.insert(0x55,QString(QChar(0x919)));
        m_keymap.insert(0x56,QString(QChar(0x929)));
        m_keymap.insert(0x57,QString(QChar(0x910)));
        m_keymap.insert(0x58,QString(QChar(0x901)));
        m_keymap.insert(0x59,QString(QChar(0x92D)));
        m_keymap.insert(0x5a,QString(QChar(0x90E)));
        m_keymap.insert(0x5b,QString(QChar(0x921)));
        m_keymap.insert(0x5c,QString(QChar(0x949)));
        m_keymap.insert(0x5d,QString(QChar(0x93C)));
        m_keymap.insert(0x5e,QString("\u0924\u094D\u0930"));
        m_keymap.insert(0x5f,QString(QChar(0x903)));
        m_keymap.insert(0x60,QString(QChar(0x94A)));
        m_keymap.insert(0x61,QString(QChar(0x94B)));
        m_keymap.insert(0x62,QString(QChar(0x935)));
        m_keymap.insert(0x63,QString(QChar(0x92e)));
        m_keymap.insert(0x64,QString(QChar(0x94D)));
        m_keymap.insert(0x65,QString(QChar(0x93E)));
        m_keymap.insert(0x66,QString(QChar(0x93f)));
        m_keymap.insert(0x67,QString(QChar(0x941)));
        m_keymap.insert(0x68,QString(QChar(0x92A)));
        m_keymap.insert(0x69,QString(QChar(0x917)));
        m_keymap.insert(0x6a,QString(QChar(0x930)));
        m_keymap.insert(0x6b,QString(QChar(0x915)));
        m_keymap.insert(0x6c,QString(QChar(0x924)));
        m_keymap.insert(0x6d,QString(QChar(0x938)));
        m_keymap.insert(0x6e,QString(QChar(0x932)));
        m_keymap.insert(0x6f,QString(QChar(0x926)));
        m_keymap.insert(0x70,QString(QChar(0x91C)));
        m_keymap.insert(0x71,QString(QChar(0x94C)));
        m_keymap.insert(0x72,QString(QChar(0x940)));
        m_keymap.insert(0x73,QString(QChar(0x947)));
        m_keymap.insert(0x74,QString(QChar(0x942)));
        m_keymap.insert(0x75,QString(QChar(0x939)));
        m_keymap.insert(0x76,QString(QChar(0x928)));
        m_keymap.insert(0x77,QString(QChar(0x948)));
        m_keymap.insert(0x78,QString(QChar(0x902)));
        m_keymap.insert(0x79,QString(QChar(0x92C)));
        m_keymap.insert(0x7a,QString(QChar(0x946)));
        m_keymap.insert(0x7b,QString(QChar(0x922)));
        m_keymap.insert(0x7c,QString(QChar(0x911)));
        m_keymap.insert(0x7d,QString(QChar(0x91E)));
        m_keymap.insert(0x7e,QString(QChar(0x912)));
        m_keymap.insert(0x20,QString(QChar(0x20)));
        m_keymap.insert(0x401,QString(QChar(0x40)));
        m_keymap.insert(0x3f1,QString(QChar(0x3f)));
    }

    void setPreedit(const QString &preeditString, int cursorPos)
    {
        Q_UNUSED(cursorPos);
        m_surroundingText = preeditString;
    }

    bool isPredictionSupported()
    {
        return true;
    }

    static AutomataBase* create()
    {
        return new HindiAutomata();
    }
};

#endif // HINDI_AUTOMATA_H

