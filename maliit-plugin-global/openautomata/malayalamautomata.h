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

#ifndef MALAYALAM_AUTOMATA_H
#define MALAYALAM_AUTOMATA_H

#include "automatabase.h"
#include <QLocale>

class MalayalamAutomata: public AutomataBase
{

public:
    MalayalamAutomata()
    {
        addNumberKeys();
        addNormalKeys();
        addShiftedKeys();
        addAltedKeys();
        addAltShiftedKeys();
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
        return new MalayalamAutomata();
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
        m_keymap.insert(0x3D,QString(QChar(0x0D43)));
    }

    void addNormalKeys()
    {
        m_keymap.insert(0x71,QString(QChar(0x0D4C)));
        m_keymap.insert(0x77,QString(QChar(0x0D48)));
        m_keymap.insert(0x65,QString(QChar(0x0D3E)));
        m_keymap.insert(0x72,QString(QChar(0x0D40)));
        m_keymap.insert(0x74,QString(QChar(0x0D42)));
        m_keymap.insert(0x79,QString(QChar(0x0D2C)));
        m_keymap.insert(0x75,QString(QChar(0x0D39)));
        m_keymap.insert(0x69,QString(QChar(0x0D17)));
        m_keymap.insert(0x6F,QString(QChar(0x0D26)));
        m_keymap.insert(0x70,QString(QChar(0x0D1C)));
        m_keymap.insert(0X5B,QString(QChar(0X0D21)));
        m_keymap.insert(0X5D,QString(QChar(0X0D7C)));
        m_keymap.insert(0X61,QString(QChar(0X0D4B)));
        m_keymap.insert(0x73,QString(QChar(0x0D47)));
        m_keymap.insert(0x64,QString(QChar(0x0D4D)));
        m_keymap.insert(0x66,QString(QChar(0x0D3F)));
        m_keymap.insert(0x67,QString(QChar(0x0D41)));
        m_keymap.insert(0x68,QString(QChar(0x0D2A)));
        m_keymap.insert(0x6A,QString(QChar(0x0D30)));
        m_keymap.insert(0x6B,QString(QChar(0x0D15)));
        m_keymap.insert(0x6C,QString(QChar(0x0D24)));
        m_keymap.insert(0x3B,QString(QChar(0x0D1A)));
        m_keymap.insert(0x27,QString(QChar(0x0D1F)));
        m_keymap.insert(0x60,QString(QChar(0x0D4A)));
        m_keymap.insert(0x7A,QString(QChar(0x0D46)));
        m_keymap.insert(0x78,QString(QChar(0x0D02)));
        m_keymap.insert(0x63,QString(QChar(0x0D2E)));
        m_keymap.insert(0x76,QString(QChar(0x0D28)));
        m_keymap.insert(0x62,QString(QChar(0x0D35)));
        m_keymap.insert(0x6E,QString(QChar(0x0D32)));
        m_keymap.insert(0x6D,QString(QChar(0x0D38)));
        m_keymap.insert(0x2C,QString(QChar(0x002C)));
        m_keymap.insert(0x2E,QString(QChar(0x002E)));
        m_keymap.insert(0x2F,QString(QChar(0x0D2F)));
        m_keymap.insert(0x20,QString(QChar(0x20)));
    }

    void addShiftedKeys()
    {
        m_keymap.insert(0x23,QString("\u0D4D\u0D30"));
        m_keymap.insert(0x5E,QString(QChar(0x0D7F)));
        m_keymap.insert(0x26,QString("\u0D15\u0D4D\u0D37"));
        m_keymap.insert(0x2A,QString(QChar(0x0D7E)));
        m_keymap.insert(0x28,QString(QChar(0x0028)));
        m_keymap.insert(0x29,QString(QChar(0x0029)));
        m_keymap.insert(0x5F,QString(QChar(0x0D03)));
        m_keymap.insert(0x2B,QString(QChar(0x0D0B)));
        m_keymap.insert(0x51,QString(QChar(0x0D14)));
        m_keymap.insert(0x57,QString(QChar(0x0D10)));
        m_keymap.insert(0x45,QString(QChar(0x0D06)));
        m_keymap.insert(0x52,QString(QChar(0x0D08)));
        m_keymap.insert(0x54,QString(QChar(0x0D0A)));
        m_keymap.insert(0x59,QString(QChar(0x0D2D)));
        m_keymap.insert(0x55,QString(QChar(0x0D19)));
        m_keymap.insert(0x49,QString(QChar(0x0D18)));
        m_keymap.insert(0x4F,QString(QChar(0x0D27)));
        m_keymap.insert(0x50,QString(QChar(0x0D1D)));
        m_keymap.insert(0x7B,QString(QChar(0x0D22)));
        m_keymap.insert(0x7D,QString(QChar(0x0D1E)));
        m_keymap.insert(0x41,QString(QChar(0x0D13)));
        m_keymap.insert(0x53,QString(QChar(0x0D0F)));
        m_keymap.insert(0x44,QString(QChar(0x0D05)));
        m_keymap.insert(0x46,QString(QChar(0x0D07)));
        m_keymap.insert(0x47,QString(QChar(0x0D09)));
        m_keymap.insert(0x48,QString(QChar(0x0D2B)));
        m_keymap.insert(0x4A,QString(QChar(0x0D31)));
        m_keymap.insert(0x4B,QString(QChar(0x0D16)));
        m_keymap.insert(0x4C,QString(QChar(0x0D25)));
        m_keymap.insert(0x3A,QString(QChar(0x0D1B)));
        m_keymap.insert(0x22,QString(QChar(0x0D20)));
        m_keymap.insert(0x7E,QString(QChar(0x0D12)));
        m_keymap.insert(0x5A,QString(QChar(0x0D0E)));
        m_keymap.insert(0x58,QString(QChar(0x0D7A)));
        m_keymap.insert(0x43,QString(QChar(0x0D23)));
        m_keymap.insert(0x56,QString(QChar(0x0D7B)));
        m_keymap.insert(0x42,QString(QChar(0x0D34)));
        m_keymap.insert(0x4E,QString(QChar(0x0D33)));
        m_keymap.insert(0x4D,QString(QChar(0x0D36)));
        m_keymap.insert(0x7C,QString(QChar(0x0D37)));
        m_keymap.insert(0x3C,QString(QChar(0x0D7D)));
    }

    void addAltedKeys()
    {
        m_keymap.insert(0xA0,QString(QChar(0x0D67)));
        m_keymap.insert(0xA1,QString(QChar(0x0D68)));
        m_keymap.insert(0xA2,QString(QChar(0x0D69)));
        m_keymap.insert(0xA3,QString(QChar(0x0D6A)));
        m_keymap.insert(0xA4,QString(QChar(0x0D6B)));
        m_keymap.insert(0xA5,QString(QChar(0x0D6C)));
        m_keymap.insert(0xA6,QString(QChar(0x0D6D)));
        m_keymap.insert(0xA7,QString(QChar(0x0D6E)));
        m_keymap.insert(0xA8,QString(QChar(0x0D6F)));
        m_keymap.insert(0xA9,QString(QChar(0x0D66)));
        m_keymap.insert(0xAC,QString(QChar(0x0D57)));
    }

    void addAltShiftedKeys()
    {
        m_keymap.insert(0xDA,QString(QChar(0x0D70)));
        m_keymap.insert(0xDB,QString(QChar(0x0D71)));
        m_keymap.insert(0xDC,QString(QChar(0x0D72)));
        m_keymap.insert(0xE5,QString(QChar(0x0D60)));
        m_keymap.insert(0xE8,QString(QChar(0x0D61)));
        m_keymap.insert(0xF4,QString(QChar(0x0D0C)));
        m_keymap.insert(0x101,QString(QChar(0x0D79)));
    }
};

#endif // MALAYALAM_AUTOMATA_H

