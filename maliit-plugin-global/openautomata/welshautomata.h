// Copyright (c) 2017-2020 LG Electronics, Inc.
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

#ifndef WELSH_AUTOMATA_H
#define WELSH_AUTOMATA_H

#include "automatabase.h"
#include <QLocale>

class WelshAutomata : public AutomataBase
{

public:
    WelshAutomata()
    {
        addNumberKeys();
        addSymbolKeys();
        addNormalKeys();
        addShiftedKeys();
        addAltKeysForHID();
        addAltShiftedKeysForHID();
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
        return new WelshAutomata();
    }

private:
    void addNumberKeys()
    {
        m_keymap.insert(0x30,QString(0x30));
        m_keymap.insert(0x31,QString(0x31));
        m_keymap.insert(0x32,QString(0x32));
        m_keymap.insert(0x33,QString(0x33));
        m_keymap.insert(0x34,QString(0x34));
        m_keymap.insert(0x35,QString(0x35));
        m_keymap.insert(0x36,QString(0x36));
        m_keymap.insert(0x37,QString(0x37));
        m_keymap.insert(0x38,QString(0x38));
        m_keymap.insert(0x39,QString(0x39));
    }

    void addSymbolKeys()
    {
        m_keymap.insert(0x60,QString(0x0060));
        m_keymap.insert(0x7E,QString(0x007E));
        m_keymap.insert(0x2D,QString(0x002D));
        m_keymap.insert(0x3D,QString(0x003D));
        m_keymap.insert(0x2B,QString(0x002B));
        m_keymap.insert(0x5C,QString(0x005C));
        m_keymap.insert(0x7C,QString(0x007C));
        m_keymap.insert(0x21,QString(0x0021));
        m_keymap.insert(0x40,QString(0x0040));
        m_keymap.insert(0x23,QString(0x00A3));
        m_keymap.insert(0x24,QString(0x0024));
        m_keymap.insert(0x25,QString(0x0025));
        m_keymap.insert(0x5E,QString(0x005E));
        m_keymap.insert(0x26,QString(0x0026));
        m_keymap.insert(0x2A,QString(0x002A));
        m_keymap.insert(0x28,QString(0x0028));
        m_keymap.insert(0x29,QString(0x0029));
        m_keymap.insert(0x5F,QString(0x005F));
        m_keymap.insert(0x2C,QString(0x002C));
        m_keymap.insert(0x3C,QString(0x003C));
        m_keymap.insert(0x2E,QString(0x002E));
        m_keymap.insert(0x3E,QString(0x003E));
        m_keymap.insert(0x2F,QString(0x002F));
        m_keymap.insert(0x3F,QString(0x003F));
        m_keymap.insert(0x5B,QString(0x005B));
        m_keymap.insert(0x5D,QString(0x005D));
        m_keymap.insert(0x3B,QString(0x003B));
        m_keymap.insert(0x27,QString(0x0027));
        m_keymap.insert(0x7B,QString(0x007B));
        m_keymap.insert(0x7D,QString(0x007D));
        m_keymap.insert(0x3A,QString(0x003A));
        m_keymap.insert(0x22,QString(0x0022));
    }

    void addNormalKeys()
    {
        m_keymap.insert(0x71,QString(0x71));
        m_keymap.insert(0x77,QString(0x77));
        m_keymap.insert(0x65,QString(0x65));
        m_keymap.insert(0x72,QString(0x72));
        m_keymap.insert(0x74,QString(0x74));
        m_keymap.insert(0x79,QString(0x79));
        m_keymap.insert(0x75,QString(0x75));
        m_keymap.insert(0x69,QString(0x69));
        m_keymap.insert(0x6F,QString(0x6F));
        m_keymap.insert(0x70,QString(0x70));
        m_keymap.insert(0X61,QString(0X61));
        m_keymap.insert(0x73,QString(0x73));
        m_keymap.insert(0x64,QString(0x64));
        m_keymap.insert(0x66,QString(0x66));
        m_keymap.insert(0x67,QString(0x67));
        m_keymap.insert(0x68,QString(0x68));
        m_keymap.insert(0x6A,QString(0x6A));
        m_keymap.insert(0x6B,QString(0x6B));
        m_keymap.insert(0x6C,QString(0x6C));
        m_keymap.insert(0x7A,QString(0x7A));
        m_keymap.insert(0x78,QString(0x78));
        m_keymap.insert(0x63,QString(0x63));
        m_keymap.insert(0x76,QString(0x76));
        m_keymap.insert(0x62,QString(0x62));
        m_keymap.insert(0x6E,QString(0x6E));
        m_keymap.insert(0x6D,QString(0x6D));
        m_keymap.insert(0x20,QString(0x20));
    }

    void addShiftedKeys()
    {
        m_keymap.insert(0x51,QString(0x51));
        m_keymap.insert(0x57,QString(0x57));
        m_keymap.insert(0x45,QString(0x45));
        m_keymap.insert(0x52,QString(0x52));
        m_keymap.insert(0x54,QString(0x54));
        m_keymap.insert(0x59,QString(0x59));
        m_keymap.insert(0x55,QString(0x55));
        m_keymap.insert(0x49,QString(0x49));
        m_keymap.insert(0x4F,QString(0x4F));
        m_keymap.insert(0x50,QString(0x50));
        m_keymap.insert(0x41,QString(0x41));
        m_keymap.insert(0x53,QString(0x53));
        m_keymap.insert(0x44,QString(0x44));
        m_keymap.insert(0x46,QString(0x46));
        m_keymap.insert(0x47,QString(0x47));
        m_keymap.insert(0x48,QString(0x48));
        m_keymap.insert(0x4A,QString(0x4A));
        m_keymap.insert(0x4B,QString(0x4B));
        m_keymap.insert(0x4C,QString(0x4C));
        m_keymap.insert(0x5A,QString(0x5A));
        m_keymap.insert(0x58,QString(0x58));
        m_keymap.insert(0x43,QString(0x43));
        m_keymap.insert(0x56,QString(0x56));
        m_keymap.insert(0x42,QString(0x42));
        m_keymap.insert(0x4E,QString(0x4E));
        m_keymap.insert(0x4D,QString(0x4D));
    }

    void addAltKeysForHID()
    {
        m_keymap.insert(0xA0,QString(0x00A1));
        m_keymap.insert(0xA1,QString(0x20AC));
        m_keymap.insert(0xA2,QString(0x0023));
        m_keymap.insert(0xA3,QString(0x00A2));
        m_keymap.insert(0xA4,QString(0x00A7));
        m_keymap.insert(0xA5,QString(0x02C6));
        m_keymap.insert(0xA6,QString(0x00B4));
        m_keymap.insert(0xA7,QString(0x00A8));
        m_keymap.insert(0xA8,QString(0x00B6));
        m_keymap.insert(0xA9,QString(0x00AF));
        m_keymap.insert(0xAA,QString(0x2013));
        m_keymap.insert(0xAB,QString(0x2260));
        m_keymap.insert(0xC3,QString(0x0060));
        m_keymap.insert(0xAC,QString(0x0153));
        m_keymap.insert(0xAD,QString(0x0175));
        m_keymap.insert(0xAE,QString(0x00EA));
        m_keymap.insert(0xAF,QString(0x00AE));
        m_keymap.insert(0xB0,QString(0x00FE));
        m_keymap.insert(0xB1,QString(0x0177));
        m_keymap.insert(0xB2,QString(0x00FB));
        m_keymap.insert(0xB3,QString(0x00EE));
        m_keymap.insert(0xB4,QString(0x00F4));
        m_keymap.insert(0xB5,QString(0x002C));
        m_keymap.insert(0xB6,QString(0x201C));
        m_keymap.insert(0xB7,QString(0x2018));
        m_keymap.insert(0xC4,QString(0x00AB));
        m_keymap.insert(0xB8,QString(0x00E2));
        m_keymap.insert(0xB9,QString(0x00DF));
        m_keymap.insert(0xBA,QString(0x00F0));
        m_keymap.insert(0xBB,QString(0x0192));
        m_keymap.insert(0xBC,QString(0x00A9));
        m_keymap.insert(0xBD,QString(0x02CD));
        m_keymap.insert(0xBE,QString(0x02DD));
        m_keymap.insert(0xBF,QString(0x02DA));
        m_keymap.insert(0xC0,QString(0x002D));
        m_keymap.insert(0xC1,QString(0x2026));
        m_keymap.insert(0xC2,QString(0x00E6));
        m_keymap.insert(0xC5,QString(0x02C0));
        m_keymap.insert(0xC6,QString(0x002E));
        m_keymap.insert(0xC7,QString(0x00B8));
        m_keymap.insert(0xC8,QString(0x02C7));
        m_keymap.insert(0xC9,QString(0x02D8));
        m_keymap.insert(0xCA,QString(0x02DC));
        m_keymap.insert(0xCB,QString(0x02DB));
        m_keymap.insert(0xCC,QString(0x2264));
        m_keymap.insert(0xCD,QString(0x2265));
        m_keymap.insert(0xCE,QString(0x00F7));
    }

    void addAltShiftedKeysForHID()
    {
        m_keymap.insert(0xFD,QString(0x0300));
        m_keymap.insert(0xDA,QString(0x2044));
        m_keymap.insert(0xDB,QString(0x2122));
        m_keymap.insert(0xDC,QString(0x2039));
        m_keymap.insert(0xDD,QString(0x203A));
        m_keymap.insert(0xDE,QString(0x2020));
        m_keymap.insert(0xDF,QString(0x0302));
        m_keymap.insert(0xE0,QString(0x0301));
        m_keymap.insert(0xE1,QString(0x2022));
        m_keymap.insert(0xE2,QString(0x02D9));
        m_keymap.insert(0xE3,QString(0x0304));
        m_keymap.insert(0xE4,QString(0x2014));
        m_keymap.insert(0xE5,QString(0x00B1));
        m_keymap.insert(0xE6,QString(0x0152));
        m_keymap.insert(0xE7,QString(0x0174));
        m_keymap.insert(0xE8,QString(0x00CA));
        m_keymap.insert(0xE9,QString(0x2030));
        m_keymap.insert(0xEA,QString(0x00DE));
        m_keymap.insert(0xEB,QString(0x0176));
        m_keymap.insert(0xEC,QString(0x00DB));
        m_keymap.insert(0xED,QString(0x00CE));
        m_keymap.insert(0xEE,QString(0x00D4));
        m_keymap.insert(0xEF,QString(0x0326));
        m_keymap.insert(0xF0,QString(0x201D));
        m_keymap.insert(0xF1,QString(0x2019));
        m_keymap.insert(0xFE,QString(0x00BB));
        m_keymap.insert(0xF2,QString(0x00C2));
        m_keymap.insert(0xF3,QString(0x00B7));
        m_keymap.insert(0xF4,QString(0x00D0));
        m_keymap.insert(0xF5,QString(0x0330));
        m_keymap.insert(0xF6,QString(0x2038));
        m_keymap.insert(0xF7,QString(0x0331));
        m_keymap.insert(0xF8,QString(0x030B));
        m_keymap.insert(0xF9,QString(0x030A));
        m_keymap.insert(0xFA,QString(0x0335));
        m_keymap.insert(0xFB,QString(0x2116));
        m_keymap.insert(0xFC,QString(0x00C6));
        m_keymap.insert(0xFF,QString(0x0309));
        m_keymap.insert(0x100,QString(0x0323));
        m_keymap.insert(0x101,QString(0x0327));
        m_keymap.insert(0x102,QString(0x030C));
        m_keymap.insert(0x103,QString(0x0306));
        m_keymap.insert(0x104,QString(0x0303));
        m_keymap.insert(0x105,QString(0x0328));
        m_keymap.insert(0x106,QString(0x02BC));
        m_keymap.insert(0x107,QString(0x0294));
        m_keymap.insert(0x108,QString(0x00BF));
    }
};

#endif // WELSH_AUTOMATA_H
