// Copyright (c) 2016-2018 LG Electronics, Inc.
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

#ifndef PERSIAN_AUTOMATA_H
#define PERSIAN_AUTOMATA_H

#include "automatabase.h"
#include <QLocale>

class PersianAutomata : public AutomataBase
{

public:
    PersianAutomata()
    {
        m_keymap.clear();
        //Normal Keyboard
        //First Row - HW Keyboard
        m_keymap.insert(0x31,QString(QChar(0x31)));
        m_keymap.insert(0x32,QString(QChar(0x32)));
        m_keymap.insert(0x33,QString(QChar(0x33)));
        m_keymap.insert(0x34,QString(QChar(0x34)));
        m_keymap.insert(0x35,QString(QChar(0x35)));
        m_keymap.insert(0x36,QString(QChar(0x36)));
        m_keymap.insert(0x37,QString(QChar(0x37)));
        m_keymap.insert(0x38,QString(QChar(0x38)));
        m_keymap.insert(0x39,QString(QChar(0x39)));
        m_keymap.insert(0x30,QString(QChar(0x30)));
        m_keymap.insert(0x2D,QString(QChar(0x2D)));
        m_keymap.insert(0x3D,QString(QChar(0x3D)));
        //First Row - Virtual Keyboard
        m_keymap.insert(0x6F1,QString(QChar(0x6F1)));
        m_keymap.insert(0x6F2,QString(QChar(0x6F2)));
        m_keymap.insert(0x6F3,QString(QChar(0x6F3)));
        m_keymap.insert(0x6F4,QString(QChar(0x6F4)));
        m_keymap.insert(0x6F5,QString(QChar(0x6F5)));
        m_keymap.insert(0x6F6,QString(QChar(0x6F6)));
        m_keymap.insert(0x6F7,QString(QChar(0x6F7)));
        m_keymap.insert(0x6F8,QString(QChar(0x6F8)));
        m_keymap.insert(0x6F9,QString(QChar(0x6F9)));
        m_keymap.insert(0x6F0,QString(QChar(0x6F0)));
        //Second Row
        m_keymap.insert(0x71,QString(QChar(0x636)));
        m_keymap.insert(0x77,QString(QChar(0x635)));
        m_keymap.insert(0x65,QString(QChar(0x62B)));
        m_keymap.insert(0x72,QString(QChar(0x642)));
        m_keymap.insert(0x74,QString(QChar(0x641)));
        m_keymap.insert(0x79,QString(QChar(0x63A)));
        m_keymap.insert(0x75,QString(QChar(0x639)));
        m_keymap.insert(0x69,QString(QChar(0x647)));
        m_keymap.insert(0x6F,QString(QChar(0x62E)));
        m_keymap.insert(0x70,QString(QChar(0x62D)));
        m_keymap.insert(0x5B,QString(QChar(0x62C)));
        m_keymap.insert(0x5D,QString(QChar(0x686)));
        m_keymap.insert(0x5C,QString(QChar(0x67E)));
        //Third Row
        m_keymap.insert(0x61,QString(QChar(0x634)));
        m_keymap.insert(0x73,QString(QChar(0x633)));
        m_keymap.insert(0x64,QString(QChar(0x6CC)));
        m_keymap.insert(0x66,QString(QChar(0x628)));
        m_keymap.insert(0x67,QString(QChar(0x644)));
        m_keymap.insert(0x68,QString(QChar(0x627)));
        m_keymap.insert(0x6A,QString(QChar(0x62A)));
        m_keymap.insert(0x6B,QString(QChar(0x646)));
        m_keymap.insert(0x6C,QString(QChar(0x645)));
        m_keymap.insert(0x3B,QString(QChar(0x6A9)));
        m_keymap.insert(0x27,QString(QChar(0x6AF)));
        //Fourth Row
        m_keymap.insert(0x40,QString(QChar(0x40)));
        m_keymap.insert(0x7A,QString(QChar(0x638)));
        m_keymap.insert(0x78,QString(QChar(0x637)));
        m_keymap.insert(0x63,QString(QChar(0x632)));
        m_keymap.insert(0x76,QString(QChar(0x631)));
        m_keymap.insert(0x62,QString(QChar(0x630)));
        m_keymap.insert(0x6E,QString(QChar(0x62F)));
        m_keymap.insert(0x6D1,QString(QChar(0x67E)));
        m_keymap.insert(0x6D,QString(QChar(0x626)));
        m_keymap.insert(0x2C,QString(QChar(0x648)));
        m_keymap.insert(0x8C,QString(QChar(0x2C)));
        m_keymap.insert(0x2E,QString(QChar(0x2E)));
        m_keymap.insert(0x2F1,QString(QChar(0x3F)));
        m_keymap.insert(0x2F,QString(QChar(0x2F)));
        //Shift Keyboard
        //First Row - Virtual Keyboard
        m_keymap.insert(0x21,QString(QChar(0x21)));
        m_keymap.insert(0x648,QString(QChar(0x2C)));
        m_keymap.insert(0x40,QString(QChar(0x40)));
        m_keymap.insert(0xFDFC,QString(QChar(0xFDFC)));
        m_keymap.insert(0x25,QString(QChar(0x25)));
        m_keymap.insert(0x637,QString(QChar(0x78)));
        m_keymap.insert(0x60C,QString(QChar(0x60C)));
        m_keymap.insert(0x2A,QString(QChar(0x2A)));
        m_keymap.insert(0x29,QString(QChar(0x29)));
        m_keymap.insert(0x28,QString(QChar(0x28)));
        m_keymap.insert(0x5F,QString(QChar(0x5F)));
        m_keymap.insert(0x2B,QString(QChar(0x2B)));
        //First Row - Hardware Keyboard
        m_keymap.insert(0x23,QString(QChar(0x23)));
        m_keymap.insert(0x24,QString(QChar(0x24)));
        m_keymap.insert(0x5E,QString(QChar(0x5E)));
        m_keymap.insert(0x26,QString(QChar(0x26)));
        m_keymap.insert(0x2A,QString(QChar(0x2A)));
        //Second Row
        m_keymap.insert(0x511,QString(QChar(0x652)));
        m_keymap.insert(0x51,QString(QChar(0x64B)));
        m_keymap.insert(0x57,QString(QChar(0x64C)));
        m_keymap.insert(0x45,QString(QChar(0x64D)));
        m_keymap.insert(0x521,QString(QChar(0x64B)));
        m_keymap.insert(0x52,QString("\u0631\u06CC\u0627\u0644"));
        m_keymap.insert(0x541,QString(QChar(0x64F)));
        m_keymap.insert(0x54,QString(QChar(0x60C)));
        m_keymap.insert(0x591,QString(QChar(0x650)));
        m_keymap.insert(0x59,QString(QChar(0x61B)));
        m_keymap.insert(0x551,QString(QChar(0x64E)));
        m_keymap.insert(0x55,QString(QChar(0x2C)));
        m_keymap.insert(0x491,QString(QChar(0x651)));
        m_keymap.insert(0x49,QString(QChar(0x5D)));
        m_keymap.insert(0x4F1,QString(QChar(0x5D)));
        m_keymap.insert(0x4F,QString(QChar(0x5B)));
        m_keymap.insert(0x501,QString(QChar(0x5B)));
        m_keymap.insert(0x50,QString(QChar(0x5C)));
        m_keymap.insert(0x7B,QString(QChar(0x7D)));
        m_keymap.insert(0x7D,QString(QChar(0x7B)));
        m_keymap.insert(0x7C,QString(QChar(0x7C)));
        //Third Row
        m_keymap.insert(0x411,QString(QChar(0x624)));
        m_keymap.insert(0x41,QString(QChar(0x64E)));
        m_keymap.insert(0x531,QString(QChar(0x626)));
        m_keymap.insert(0x53,QString(QChar(0x64F)));
        m_keymap.insert(0x441,QString(QChar(0x64A)));
        m_keymap.insert(0x44,QString(QChar(0x650)));
        m_keymap.insert(0x461,QString(QChar(0x625)));
        m_keymap.insert(0x46,QString(QChar(0x651)));
        m_keymap.insert(0x471,QString(QChar(0x623)));
        m_keymap.insert(0x47,QString(QChar(0x6C0)));
        m_keymap.insert(0x48,QString(QChar(0x622)));
        m_keymap.insert(0x4A1,QString(QChar(0x629)));
        m_keymap.insert(0x4A,QString(QChar(0x640)));
        m_keymap.insert(0x4B,QString(QChar(0xAB)));
        m_keymap.insert(0x4C,QString(QChar(0xBB)));
        m_keymap.insert(0x3A,QString(QChar(0x3A)));
        m_keymap.insert(0x221,QString(QChar(0x61B)));
        m_keymap.insert(0x22,QString(QChar(0x22)));
        m_keymap.insert(0x3F,QString(QChar(0x61F)));
        //Fourth Row
        m_keymap.insert(0x40,QString(QChar(0x40)));
        m_keymap.insert(0x5A1,QString(QChar(0x653)));
        m_keymap.insert(0x5A,QString(QChar(0x629)));
        m_keymap.insert(0x581,QString(QChar(0x698)));
        m_keymap.insert(0x58,QString(QChar(0x64A)));
        m_keymap.insert(0x431,QString(QChar(0x670)));
        m_keymap.insert(0x43,QString(QChar(0x698)));
        m_keymap.insert(0x561,QString(QChar(0x654)));
        m_keymap.insert(0x56,QString(QChar(0x624)));
        m_keymap.insert(0x421,QString(QChar(0x655)));
        m_keymap.insert(0x42,QString(QChar(0x625)));
        m_keymap.insert(0x4E1,QString(QChar(0x621)));
        m_keymap.insert(0x4E,QString(QChar(0x623)));
        m_keymap.insert(0x4D1,QString(QChar(0x3C)));
        m_keymap.insert(0x4D,QString(QChar(0x621)));
        m_keymap.insert(0x3C1,QString(QChar(0x3E)));
        m_keymap.insert(0x3C,QString(QChar(0x3C)));
        m_keymap.insert(0x3E1,QString(QChar(0x2C)));
        m_keymap.insert(0x3E,QString(QChar(0x3E)));
        m_keymap.insert(0x8A,QString(QChar(0x2E)));
        m_keymap.insert(0x8B,QString(QChar(0x3F)));
        //Space Key
        m_keymap.insert(0x20,QString(QChar(0x20)));
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

    void reset() {}

    static AutomataBase* create()
    {
        return new PersianAutomata();
    }
};

#endif // PERSIAN_AUTOMATA_H
