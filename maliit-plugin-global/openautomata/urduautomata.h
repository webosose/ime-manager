// Copyright (c) 2017-2018 LG Electronics, Inc.
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

#ifndef URDU_AUTOMATA_H
#define URDU_AUTOMATA_H

#include "automatabase.h"
#include <QLocale>

class UrduAutomata: public AutomataBase
{

public:
    UrduAutomata()
    {
        addNumberKeys();
        addNormalKeys();
        addShiftedKeys();
        addAltedKeys();
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
        return new UrduAutomata();
    }

private:
    void addNumberKeys()
    {
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
    }

    void addNormalKeys()
    {
        m_keymap.insert(0x71,QString(QChar(0x0637)));
        m_keymap.insert(0x77,QString(QChar(0x0635)));
        m_keymap.insert(0x65,QString(QChar(0x06BE)));
        m_keymap.insert(0x72,QString(QChar(0x062F)));
        m_keymap.insert(0x74,QString(QChar(0x0679)));
        m_keymap.insert(0x79,QString(QChar(0x067E)));
        m_keymap.insert(0x75,QString(QChar(0x062A)));
        m_keymap.insert(0x69,QString(QChar(0x0628)));
        m_keymap.insert(0x6F,QString(QChar(0x062C)));
        m_keymap.insert(0x70,QString(QChar(0x062D)));
        m_keymap.insert(0X5B,QString(QChar(0X005D)));
        m_keymap.insert(0X5D,QString(QChar(0X005B)));
        m_keymap.insert(0X61,QString(QChar(0X0645)));
        m_keymap.insert(0x73,QString(QChar(0x0648)));
        m_keymap.insert(0x64,QString(QChar(0x0631)));
        m_keymap.insert(0x66,QString(QChar(0x0646)));
        m_keymap.insert(0x67,QString(QChar(0x0644)));
        m_keymap.insert(0x68,QString(QChar(0x06C1)));
        m_keymap.insert(0x6A,QString(QChar(0x0627)));
        m_keymap.insert(0x6B,QString(QChar(0x06A9)));
        m_keymap.insert(0x6C,QString(QChar(0x06CC)));
        m_keymap.insert(0x3B,QString(QChar(0x061B)));
        m_keymap.insert(0x27,QString(QChar(0x0027)));
        m_keymap.insert(0x5C,QString(QChar(0x005C)));
        m_keymap.insert(0x7A,QString(QChar(0x0642)));
        m_keymap.insert(0x78,QString(QChar(0x0641)));
        m_keymap.insert(0x63,QString(QChar(0x06D2)));
        m_keymap.insert(0x76,QString(QChar(0x0633)));
        m_keymap.insert(0x62,QString(QChar(0x0634)));
        m_keymap.insert(0x6E,QString(QChar(0x063A)));
        m_keymap.insert(0x6D,QString(QChar(0x0639)));
        m_keymap.insert(0x2C,QString(QChar(0x060C)));
        m_keymap.insert(0x2E,QString(QChar(0x06D4)));
        m_keymap.insert(0x2F,QString(QChar(0x002F)));
        m_keymap.insert(0x60,QString(QChar(0x0060)));
        m_keymap.insert(0x20,QString(QChar(0x20)));
    }

    void addShiftedKeys()
    {
        m_keymap.insert(0x21,QString(QChar(0x0021)));
        m_keymap.insert(0x40,QString(QChar(0x0040)));
        m_keymap.insert(0x23,QString(QChar(0x0023)));
        m_keymap.insert(0x24,QString(QChar(0x0024)));
        m_keymap.insert(0x25,QString(QChar(0x066A)));
        m_keymap.insert(0x5E,QString(QChar(0x005E)));
        m_keymap.insert(0x26,QString(QChar(0x06D6)));
        m_keymap.insert(0x2A,QString(QChar(0x066D)));
        m_keymap.insert(0x28,QString(QChar(0x0029)));
        m_keymap.insert(0x29,QString(QChar(0x0028)));
        m_keymap.insert(0x5F,QString(QChar(0x005F)));
        m_keymap.insert(0x2B,QString(QChar(0x002B)));
        m_keymap.insert(0x51,QString(QChar(0x0638)));
        m_keymap.insert(0x57,QString(QChar(0x0636)));
        m_keymap.insert(0x45,QString(QChar(0x0630)));
        m_keymap.insert(0x52,QString(QChar(0x0688)));
        m_keymap.insert(0x54,QString(QChar(0x062B)));
        m_keymap.insert(0x59,QString(QChar(0x0651)));
        m_keymap.insert(0x55,QString(QChar(0x06C3)));
        m_keymap.insert(0x49,QString(QChar(0x0640)));
        m_keymap.insert(0x4F,QString(QChar(0x0686)));
        m_keymap.insert(0x50,QString(QChar(0x062E)));
        m_keymap.insert(0x7B,QString(QChar(0x007D)));
        m_keymap.insert(0x7D,QString(QChar(0x007B)));
        m_keymap.insert(0x41,QString(QChar(0x0698)));
        m_keymap.insert(0x53,QString(QChar(0x0632)));
        m_keymap.insert(0x44,QString(QChar(0x0691)));
        m_keymap.insert(0x46,QString(QChar(0x06BA)));
        m_keymap.insert(0x47,QString(QChar(0x06C2)));
        m_keymap.insert(0x48,QString(QChar(0x0621)));
        m_keymap.insert(0x4A,QString(QChar(0x0622)));
        m_keymap.insert(0x4B,QString(QChar(0x06AF)));
        m_keymap.insert(0x4C,QString(QChar(0x064A)));
        m_keymap.insert(0x3A,QString(QChar(0x003A)));
        m_keymap.insert(0x22,QString(QChar(0x0022)));
        m_keymap.insert(0x7E,QString(QChar(0x007E)));
        m_keymap.insert(0x7C,QString(QChar(0x007C)));
        m_keymap.insert(0x43,QString(QChar(0x06D3)));
        m_keymap.insert(0x42,QString(QChar(0x0624)));
        m_keymap.insert(0x4E,QString(QChar(0x0626)));
        m_keymap.insert(0x3C,QString(QChar(0x003E)));
        m_keymap.insert(0x3E,QString(QChar(0x003C)));
        m_keymap.insert(0x3F,QString(QChar(0x061F)));
    }

    void addAltedKeys()
    {
        m_keymap.insert(0xA0,QString(QChar(0xFEF2)));
        m_keymap.insert(0xA6,QString(QChar(0x06D9)));
        m_keymap.insert(0xAC,QString(QChar(0x064B)));
        m_keymap.insert(0xAD,QString(QChar(0x064D)));
        m_keymap.insert(0xAE,QString(QChar(0x064C)));
        m_keymap.insert(0xB2,QString(QChar(0x064F)));
        m_keymap.insert(0xB3,QString(QChar(0x0650)));
        m_keymap.insert(0xB5,QString(QChar(0x0652)));
        m_keymap.insert(0xB8,QString(QChar(0x06E2)));
        m_keymap.insert(0xBD,QString(QChar(0x0623)));
        m_keymap.insert(0xBE,QString(QChar(0x0625)));
    }
};

#endif // URDU_AUTOMATA_H

