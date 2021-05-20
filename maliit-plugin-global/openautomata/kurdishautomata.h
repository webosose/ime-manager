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

#ifndef KURDISH_AUTOMATA_H
#define KURDISH_AUTOMATA_H

#include "automatabase.h"
#include <QLocale>

class KurdishAutomata : public AutomataBase
{

public:
    KurdishAutomata()
    {
        m_keymap.clear();
        m_keymap.insert(0x21,QString(QChar(0x21)));
        m_keymap.insert(0x22,QString(QChar(0x22)));
        m_keymap.insert(0x23,QString(QChar(0x23)));
        m_keymap.insert(0x24,QString(QChar(0x24)));
        m_keymap.insert(0x25,QString(QChar(0x25)));
        m_keymap.insert(0x26,QString(QChar(0x26)));
        m_keymap.insert(0x27,QString(QChar(0x637)));
        m_keymap.insert(0x28,QString(QChar(0x28)));
        m_keymap.insert(0x29,QString(QChar(0x29)));
        m_keymap.insert(0x2a,QString(QChar(0x2a)));
        m_keymap.insert(0x2b,QString(QChar(0x2b)));
        m_keymap.insert(0x2c,QString(QChar(0x648)));
        m_keymap.insert(0x2d,QString(QChar(0x2d)));
        m_keymap.insert(0x2e,QString(QChar(0x632)));
        m_keymap.insert(0x2f,QString(QChar(0x638)));
        m_keymap.insert(0x30,QString(QChar(0x30)));
        m_keymap.insert(0x31,QString(QChar(0x31)));
        m_keymap.insert(0x32,QString(QChar(0x32)));
        m_keymap.insert(0x33,QString(QChar(0x33)));
        m_keymap.insert(0x34,QString(QChar(0x34)));
        m_keymap.insert(0x35,QString(QChar(0x35)));
        m_keymap.insert(0x36,QString(QChar(0x36)));
        m_keymap.insert(0x37,QString(QChar(0x37)));
        m_keymap.insert(0x38,QString(QChar(0x38)));
        m_keymap.insert(0x39,QString(QChar(0x39)));
        m_keymap.insert(0x3a,QString(QChar(0x3a)));
        m_keymap.insert(0x3b,QString(QChar(0x643)));
        m_keymap.insert(0x3c,QString(QChar(0x2C)));
        m_keymap.insert(0x3d,QString(QChar(0x3d)));
        m_keymap.insert(0x3e,QString(QChar(0x2e)));
        m_keymap.insert(0x3f,QString(QChar(0x61F)));
        m_keymap.insert(0x40,QString(QChar(0x40)));
        m_keymap.insert(0x41,QString(QChar(0x64D)));
        m_keymap.insert(0x42,QString(QChar(0xFEF5)));
        m_keymap.insert(0x43,QString(QChar(0x7D)));
        m_keymap.insert(0x44,QString(QChar(0x5D)));
        m_keymap.insert(0x45,QString(QChar(0x64F)));
        m_keymap.insert(0x46,QString(QChar(0x5B)));
        m_keymap.insert(0x47,QString(QChar(0xFEF7)));
        m_keymap.insert(0x48,QString(QChar(0x623)));
        m_keymap.insert(0x49,QString(QChar(0xF7)));
        m_keymap.insert(0x4a,QString(QChar(0x640)));
        m_keymap.insert(0x4b,QString(QChar(0x60C)));
        m_keymap.insert(0x4c,QString(QChar(0x2F)));
        m_keymap.insert(0x4d,QString(QChar(0x2019)));
        m_keymap.insert(0x4e,QString(QChar(0x622)));
        m_keymap.insert(0x4f,QString(QChar(0xD7)));
        m_keymap.insert(0x50,QString(QChar(0x61B)));
        m_keymap.insert(0x51,QString(QChar(0x64E)));
        m_keymap.insert(0x52,QString(QChar(0x64C)));
        m_keymap.insert(0x53,QString(QChar(0x650)));
        m_keymap.insert(0x54,QString(QChar(0xFEF9)));
        m_keymap.insert(0x55,QString(QChar(0x2018)));
        m_keymap.insert(0x56,QString(QChar(0x7B)));
        m_keymap.insert(0x57,QString(QChar(0x64B)));
        m_keymap.insert(0x58,QString(QChar(0x652)));
        m_keymap.insert(0x59,QString(QChar(0x625)));
        m_keymap.insert(0x5a,QString(QChar(0x7E)));
        m_keymap.insert(0x5b,QString(QChar(0x62C)));
        m_keymap.insert(0x5c,QString(QChar(0x5c)));
        m_keymap.insert(0x5d,QString(QChar(0x62F)));
        m_keymap.insert(0x5e,QString(QChar(0x5e)));
        m_keymap.insert(0x5f,QString(QChar(0x5f)));
        m_keymap.insert(0x60,QString(QChar(0x630)));
        m_keymap.insert(0x61,QString(QChar(0x634)));
        m_keymap.insert(0x62,QString(QChar(0xFEFB)));
        m_keymap.insert(0x63,QString(QChar(0x624)));
        m_keymap.insert(0x64,QString(QChar(0x64A)));
        m_keymap.insert(0x65,QString(QChar(0x62B)));
        m_keymap.insert(0x66,QString(QChar(0x628)));
        m_keymap.insert(0x67,QString(QChar(0x644)));
        m_keymap.insert(0x68,QString(QChar(0x627)));
        m_keymap.insert(0x69,QString(QChar(0x647)));
        m_keymap.insert(0x6a,QString(QChar(0x62A)));
        m_keymap.insert(0x6b,QString(QChar(0x646)));
        m_keymap.insert(0x6c,QString(QChar(0x645)));
        m_keymap.insert(0x6d,QString(QChar(0x629)));
        m_keymap.insert(0x6e,QString(QChar(0x649)));
        m_keymap.insert(0x6f,QString(QChar(0x62E)));
        m_keymap.insert(0x70,QString(QChar(0x62D)));
        m_keymap.insert(0x71,QString(QChar(0x636)));
        m_keymap.insert(0x72,QString(QChar(0x642)));
        m_keymap.insert(0x73,QString(QChar(0x633)));
        m_keymap.insert(0x74,QString(QChar(0x641)));
        m_keymap.insert(0x75,QString(QChar(0x639)));
        m_keymap.insert(0x76,QString(QChar(0x0631)));
        m_keymap.insert(0x77,QString(QChar(0x635)));
        m_keymap.insert(0x78,QString(QChar(0x621)));
        m_keymap.insert(0x79,QString(QChar(0x63A)));
        m_keymap.insert(0x7a,QString(QChar(0x626)));
        m_keymap.insert(0x7b,QString(QChar(0x3E)));
        m_keymap.insert(0x7c,QString(QChar(0x7c)));
        m_keymap.insert(0x7d,QString(QChar(0x3C)));
        m_keymap.insert(0x7e,QString(QChar(0x651)));
        m_keymap.insert(0x20,QString(QChar(0x20)));
        //numbers
        m_keymap.insert(0x1000661,QString(QChar(0x661)));
        m_keymap.insert(0x1000662,QString(QChar(0x662)));
        m_keymap.insert(0x1000663,QString(QChar(0x663)));
        m_keymap.insert(0x1000664,QString(QChar(0x664)));
        m_keymap.insert(0x1000665,QString(QChar(0x665)));
        m_keymap.insert(0x1000666,QString(QChar(0x666)));
        m_keymap.insert(0x1000667,QString(QChar(0x667)));
        m_keymap.insert(0x1000668,QString(QChar(0x668)));
        m_keymap.insert(0x1000669,QString(QChar(0x669)));
        m_keymap.insert(0x1000660,QString(QChar(0x660)));
        m_keymap.insert(0x003F11,QString(QChar(0x003F)));
    }

    void setPreedit(const QString &preeditString, int cursorPos)
    {
        Q_UNUSED(cursorPos);
        m_surroundingText = preeditString;
    }

    bool isPredictionSupported()
    {
        return false;
    }

    static AutomataBase* create()
    {
        return new KurdishAutomata();
    }
};

#endif // KURDISH_AUTOMATA_H
