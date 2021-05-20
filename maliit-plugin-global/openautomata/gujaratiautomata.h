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

#ifndef GUJARATI_AUTOMATA_H
#define GUJARATI_AUTOMATA_H

#include "automatabase.h"
#include <QLocale>

class GujaratiAutomata : public AutomataBase
{

public:
    GujaratiAutomata()
    {
        addSymbolKeys();
        addNumberKeys();
        addShiftKeys();
        addNormalKeys();
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
        return new GujaratiAutomata();
    }
private:
    void addSymbolKeys()
    {
        m_keymap.insert(0x21,QString(QChar(0x0A8D)));
        m_keymap.insert(0x40,QString(QChar(0x0AC5)));
        m_keymap.insert(0x23,QString("\u0ACD\u0AB0"));
        m_keymap.insert(0x24,QString("\u0AB0\u0ACD"));
        m_keymap.insert(0x25,QString("\u0A9C\u0ACD\u0A9E"));
        m_keymap.insert(0x5e,QString("\u0AA4\u0ACD\u0AB0"));
        m_keymap.insert(0x26,QString("\u0A95\u0ACD\u0AB7"));
        m_keymap.insert(0x2a,QString("\u0AB6\u0ACD\u0AB0"));
        m_keymap.insert(0x28,QString(QChar(0x28)));
        m_keymap.insert(0x29,QString(QChar(0x29)));
        m_keymap.insert(0x5f,QString(QChar(0x0A83)));
        m_keymap.insert(0x2b,QString(QChar(0x0A8B)));
    }

    void addNumberKeys()
    {
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
    }

    void addShiftKeys()
    {
        m_keymap.insert(0x51,QString(QChar(0x0A94)));
        m_keymap.insert(0x57,QString(QChar(0x0A90)));
        m_keymap.insert(0x45,QString(QChar(0x0A86)));
        m_keymap.insert(0x52,QString(QChar(0x0A88)));
        m_keymap.insert(0x54,QString(QChar(0x0A8A)));
        m_keymap.insert(0x59,QString(QChar(0x0AAD)));
        m_keymap.insert(0x55,QString(QChar(0x0A99)));
        m_keymap.insert(0x49,QString(QChar(0x0A98)));
        m_keymap.insert(0x4F,QString(QChar(0x0AA7)));
        m_keymap.insert(0x50,QString(QChar(0x0A9D)));
        m_keymap.insert(0x7B,QString(QChar(0x0AA2)));
        m_keymap.insert(0x7D,QString(QChar(0x0A9E)));
        m_keymap.insert(0x41,QString(QChar(0x0A93)));
        m_keymap.insert(0x53,QString(QChar(0x0A8F)));
        m_keymap.insert(0x44,QString(QChar(0x0A85)));
        m_keymap.insert(0x46,QString(QChar(0x0A87)));
        m_keymap.insert(0x47,QString(QChar(0x0A89)));
        m_keymap.insert(0x48,QString(QChar(0x0AAB)));
        m_keymap.insert(0x4b,QString(QChar(0x0A96)));
        m_keymap.insert(0x4c,QString(QChar(0x0AA5)));
        m_keymap.insert(0x3a,QString(QChar(0x0A9B)));
        m_keymap.insert(0x22,QString(QChar(0x0AA0)));
        m_keymap.insert(0x7C,QString(QChar(0x0A91)));
        m_keymap.insert(0x58,QString(QChar(0x0A81)));
        m_keymap.insert(0x43,QString(QChar(0x0AA3)));
        m_keymap.insert(0x4E,QString(QChar(0x0AB3)));
        m_keymap.insert(0x4D,QString(QChar(0x0AB6)));
        m_keymap.insert(0x3C,QString(QChar(0x0AB7)));
        m_keymap.insert(0x3E,QString(QChar(0x0964)));
    }

    void addNormalKeys()
    {
        m_keymap.insert(0x2d,QString(QChar(0x2d)));
        m_keymap.insert(0x3D,QString(QChar(0x0AC3)));
        m_keymap.insert(0x71,QString(QChar(0x0ACC)));
        m_keymap.insert(0x77,QString(QChar(0x0AC8)));
        m_keymap.insert(0x65,QString(QChar(0x0ABE)));
        m_keymap.insert(0x72,QString(QChar(0x0AC0)));
        m_keymap.insert(0x74,QString(QChar(0x0AC2)));
        m_keymap.insert(0x79,QString(QChar(0x0AAC)));
        m_keymap.insert(0x75,QString(QChar(0x0AB9)));
        m_keymap.insert(0x69,QString(QChar(0x0A97)));
        m_keymap.insert(0x6f,QString(QChar(0x0AA6)));
        m_keymap.insert(0x70,QString(QChar(0x0A9C)));
        m_keymap.insert(0x5B,QString(QChar(0x0AA1)));
        m_keymap.insert(0x5D,QString(QChar(0x0ABC)));
        m_keymap.insert(0x61,QString(QChar(0x0ACB)));
        m_keymap.insert(0x73,QString(QChar(0x0AC7)));
        m_keymap.insert(0x64,QString(QChar(0x0ACD)));
        m_keymap.insert(0x66,QString(QChar(0x0ABF)));
        m_keymap.insert(0x67,QString(QChar(0x0AC1)));
        m_keymap.insert(0x68,QString(QChar(0x0AAA)));
        m_keymap.insert(0x6A,QString(QChar(0x0AB0)));
        m_keymap.insert(0x6B,QString(QChar(0x0A95)));
        m_keymap.insert(0x6C,QString(QChar(0x0AA4)));
        m_keymap.insert(0x3B,QString(QChar(0x0A9A)));
        m_keymap.insert(0x27,QString(QChar(0x0A9F)));
        m_keymap.insert(0x5C,QString(QChar(0x0AC9)));
        m_keymap.insert(0x78,QString(QChar(0x0A82)));
        m_keymap.insert(0x63,QString(QChar(0x0AAE)));
        m_keymap.insert(0x76,QString(QChar(0x0AA8)));
        m_keymap.insert(0x62,QString(QChar(0x0AB5)));
        m_keymap.insert(0x6E,QString(QChar(0x0AB2)));
        m_keymap.insert(0x6D,QString(QChar(0x0AB8)));
        m_keymap.insert(0x2C,QString(QChar(0x2C)));
        m_keymap.insert(0x2E,QString(QChar(0x2E)));
        m_keymap.insert(0x2F,QString(QChar(0x0AAF)));
        m_keymap.insert(0x20,QString(QChar(0x20)));
    }

     void addAltedKeys()
     {
         m_keymap.insert(0xA0,QString(QChar(0x0AE7)));
         m_keymap.insert(0xA1,QString(QChar(0x0AE8)));
         m_keymap.insert(0xA2,QString(QChar(0x0AE9)));
         m_keymap.insert(0xA3,QString(QChar(0x0AEA)));
         m_keymap.insert(0xA4,QString(QChar(0x0AEB)));
         m_keymap.insert(0xA5,QString(QChar(0x0AEC)));
         m_keymap.insert(0xA6,QString(QChar(0x0AED)));
         m_keymap.insert(0xA7,QString(QChar(0x0AEE)));
         m_keymap.insert(0xA8,QString(QChar(0x0AEF)));
         m_keymap.insert(0xA9,QString(QChar(0x0AE6)));
         m_keymap.insert(0xAB,QString(QChar(0x0AC4)));
         m_keymap.insert(0xCD,QString(QChar(0x0965)));
     }

     void addAltShiftedKeys()
     {
         m_keymap.insert(0xE5,QString(QChar(0x0AE0)));
         m_keymap.insert(0xFF,QString(QChar(0x0AD0)));
         m_keymap.insert(0x106,QString(QChar(0x0ABD)));
     }
};
#endif // GUJARATI_AUTOMATA_H

