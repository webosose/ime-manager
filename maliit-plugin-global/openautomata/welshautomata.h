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

    void addSymbolKeys()
    {
        m_keymap.insert(0x60,QString(QChar(0x0060)));
        m_keymap.insert(0x7E,QString(QChar(0x007E)));
        m_keymap.insert(0x2D,QString(QChar(0x002D)));
        m_keymap.insert(0x3D,QString(QChar(0x003D)));
        m_keymap.insert(0x2B,QString(QChar(0x002B)));
        m_keymap.insert(0x5C,QString(QChar(0x005C)));
        m_keymap.insert(0x7C,QString(QChar(0x007C)));
        m_keymap.insert(0x21,QString(QChar(0x0021)));
        m_keymap.insert(0x40,QString(QChar(0x0040)));
        m_keymap.insert(0x23,QString(QChar(0x00A3)));
        m_keymap.insert(0x24,QString(QChar(0x0024)));
        m_keymap.insert(0x25,QString(QChar(0x0025)));
        m_keymap.insert(0x5E,QString(QChar(0x005E)));
        m_keymap.insert(0x26,QString(QChar(0x0026)));
        m_keymap.insert(0x2A,QString(QChar(0x002A)));
        m_keymap.insert(0x28,QString(QChar(0x0028)));
        m_keymap.insert(0x29,QString(QChar(0x0029)));
        m_keymap.insert(0x5F,QString(QChar(0x005F)));
        m_keymap.insert(0x2C,QString(QChar(0x002C)));
        m_keymap.insert(0x3C,QString(QChar(0x003C)));
        m_keymap.insert(0x2E,QString(QChar(0x002E)));
        m_keymap.insert(0x3E,QString(QChar(0x003E)));
        m_keymap.insert(0x2F,QString(QChar(0x002F)));
        m_keymap.insert(0x3F,QString(QChar(0x003F)));
        m_keymap.insert(0x5B,QString(QChar(0x005B)));
        m_keymap.insert(0x5D,QString(QChar(0x005D)));
        m_keymap.insert(0x3B,QString(QChar(0x003B)));
        m_keymap.insert(0x27,QString(QChar(0x0027)));
        m_keymap.insert(0x7B,QString(QChar(0x007B)));
        m_keymap.insert(0x7D,QString(QChar(0x007D)));
        m_keymap.insert(0x3A,QString(QChar(0x003A)));
        m_keymap.insert(0x22,QString(QChar(0x0022)));
    }

    void addNormalKeys()
    {
        m_keymap.insert(0x71,QString(QChar(0x71)));
        m_keymap.insert(0x77,QString(QChar(0x77)));
        m_keymap.insert(0x65,QString(QChar(0x65)));
        m_keymap.insert(0x72,QString(QChar(0x72)));
        m_keymap.insert(0x74,QString(QChar(0x74)));
        m_keymap.insert(0x79,QString(QChar(0x79)));
        m_keymap.insert(0x75,QString(QChar(0x75)));
        m_keymap.insert(0x69,QString(QChar(0x69)));
        m_keymap.insert(0x6F,QString(QChar(0x6F)));
        m_keymap.insert(0x70,QString(QChar(0x70)));
        m_keymap.insert(0X61,QString(QChar(0X61)));
        m_keymap.insert(0x73,QString(QChar(0x73)));
        m_keymap.insert(0x64,QString(QChar(0x64)));
        m_keymap.insert(0x66,QString(QChar(0x66)));
        m_keymap.insert(0x67,QString(QChar(0x67)));
        m_keymap.insert(0x68,QString(QChar(0x68)));
        m_keymap.insert(0x6A,QString(QChar(0x6A)));
        m_keymap.insert(0x6B,QString(QChar(0x6B)));
        m_keymap.insert(0x6C,QString(QChar(0x6C)));
        m_keymap.insert(0x7A,QString(QChar(0x7A)));
        m_keymap.insert(0x78,QString(QChar(0x78)));
        m_keymap.insert(0x63,QString(QChar(0x63)));
        m_keymap.insert(0x76,QString(QChar(0x76)));
        m_keymap.insert(0x62,QString(QChar(0x62)));
        m_keymap.insert(0x6E,QString(QChar(0x6E)));
        m_keymap.insert(0x6D,QString(QChar(0x6D)));
        m_keymap.insert(0x20,QString(QChar(0x20)));
    }

    void addShiftedKeys()
    {
        m_keymap.insert(0x51,QString(QChar(0x51)));
        m_keymap.insert(0x57,QString(QChar(0x57)));
        m_keymap.insert(0x45,QString(QChar(0x45)));
        m_keymap.insert(0x52,QString(QChar(0x52)));
        m_keymap.insert(0x54,QString(QChar(0x54)));
        m_keymap.insert(0x59,QString(QChar(0x59)));
        m_keymap.insert(0x55,QString(QChar(0x55)));
        m_keymap.insert(0x49,QString(QChar(0x49)));
        m_keymap.insert(0x4F,QString(QChar(0x4F)));
        m_keymap.insert(0x50,QString(QChar(0x50)));
        m_keymap.insert(0x41,QString(QChar(0x41)));
        m_keymap.insert(0x53,QString(QChar(0x53)));
        m_keymap.insert(0x44,QString(QChar(0x44)));
        m_keymap.insert(0x46,QString(QChar(0x46)));
        m_keymap.insert(0x47,QString(QChar(0x47)));
        m_keymap.insert(0x48,QString(QChar(0x48)));
        m_keymap.insert(0x4A,QString(QChar(0x4A)));
        m_keymap.insert(0x4B,QString(QChar(0x4B)));
        m_keymap.insert(0x4C,QString(QChar(0x4C)));
        m_keymap.insert(0x5A,QString(QChar(0x5A)));
        m_keymap.insert(0x58,QString(QChar(0x58)));
        m_keymap.insert(0x43,QString(QChar(0x43)));
        m_keymap.insert(0x56,QString(QChar(0x56)));
        m_keymap.insert(0x42,QString(QChar(0x42)));
        m_keymap.insert(0x4E,QString(QChar(0x4E)));
        m_keymap.insert(0x4D,QString(QChar(0x4D)));
    }

    void addAltKeysForHID()
    {
        m_keymap.insert(0xA0,QString(QChar(0x00A1)));
        m_keymap.insert(0xA1,QString(QChar(0x20AC)));
        m_keymap.insert(0xA2,QString(QChar(0x0023)));
        m_keymap.insert(0xA3,QString(QChar(0x00A2)));
        m_keymap.insert(0xA4,QString(QChar(0x00A7)));
        m_keymap.insert(0xA5,QString(QChar(0x02C6)));
        m_keymap.insert(0xA6,QString(QChar(0x00B4)));
        m_keymap.insert(0xA7,QString(QChar(0x00A8)));
        m_keymap.insert(0xA8,QString(QChar(0x00B6)));
        m_keymap.insert(0xA9,QString(QChar(0x00AF)));
        m_keymap.insert(0xAA,QString(QChar(0x2013)));
        m_keymap.insert(0xAB,QString(QChar(0x2260)));
        m_keymap.insert(0xC3,QString(QChar(0x0060)));
        m_keymap.insert(0xAC,QString(QChar(0x0153)));
        m_keymap.insert(0xAD,QString(QChar(0x0175)));
        m_keymap.insert(0xAE,QString(QChar(0x00EA)));
        m_keymap.insert(0xAF,QString(QChar(0x00AE)));
        m_keymap.insert(0xB0,QString(QChar(0x00FE)));
        m_keymap.insert(0xB1,QString(QChar(0x0177)));
        m_keymap.insert(0xB2,QString(QChar(0x00FB)));
        m_keymap.insert(0xB3,QString(QChar(0x00EE)));
        m_keymap.insert(0xB4,QString(QChar(0x00F4)));
        m_keymap.insert(0xB5,QString(QChar(0x002C)));
        m_keymap.insert(0xB6,QString(QChar(0x201C)));
        m_keymap.insert(0xB7,QString(QChar(0x2018)));
        m_keymap.insert(0xC4,QString(QChar(0x00AB)));
        m_keymap.insert(0xB8,QString(QChar(0x00E2)));
        m_keymap.insert(0xB9,QString(QChar(0x00DF)));
        m_keymap.insert(0xBA,QString(QChar(0x00F0)));
        m_keymap.insert(0xBB,QString(QChar(0x0192)));
        m_keymap.insert(0xBC,QString(QChar(0x00A9)));
        m_keymap.insert(0xBD,QString(QChar(0x02CD)));
        m_keymap.insert(0xBE,QString(QChar(0x02DD)));
        m_keymap.insert(0xBF,QString(QChar(0x02DA)));
        m_keymap.insert(0xC0,QString(QChar(0x002D)));
        m_keymap.insert(0xC1,QString(QChar(0x2026)));
        m_keymap.insert(0xC2,QString(QChar(0x00E6)));
        m_keymap.insert(0xC5,QString(QChar(0x02C0)));
        m_keymap.insert(0xC6,QString(QChar(0x002E)));
        m_keymap.insert(0xC7,QString(QChar(0x00B8)));
        m_keymap.insert(0xC8,QString(QChar(0x02C7)));
        m_keymap.insert(0xC9,QString(QChar(0x02D8)));
        m_keymap.insert(0xCA,QString(QChar(0x02DC)));
        m_keymap.insert(0xCB,QString(QChar(0x02DB)));
        m_keymap.insert(0xCC,QString(QChar(0x2264)));
        m_keymap.insert(0xCD,QString(QChar(0x2265)));
        m_keymap.insert(0xCE,QString(QChar(0x00F7)));
    }

    void addAltShiftedKeysForHID()
    {
        m_keymap.insert(0xFD,QString(QChar(0x0300)));
        m_keymap.insert(0xDA,QString(QChar(0x2044)));
        m_keymap.insert(0xDB,QString(QChar(0x2122)));
        m_keymap.insert(0xDC,QString(QChar(0x2039)));
        m_keymap.insert(0xDD,QString(QChar(0x203A)));
        m_keymap.insert(0xDE,QString(QChar(0x2020)));
        m_keymap.insert(0xDF,QString(QChar(0x0302)));
        m_keymap.insert(0xE0,QString(QChar(0x0301)));
        m_keymap.insert(0xE1,QString(QChar(0x2022)));
        m_keymap.insert(0xE2,QString(QChar(0x02D9)));
        m_keymap.insert(0xE3,QString(QChar(0x0304)));
        m_keymap.insert(0xE4,QString(QChar(0x2014)));
        m_keymap.insert(0xE5,QString(QChar(0x00B1)));
        m_keymap.insert(0xE6,QString(QChar(0x0152)));
        m_keymap.insert(0xE7,QString(QChar(0x0174)));
        m_keymap.insert(0xE8,QString(QChar(0x00CA)));
        m_keymap.insert(0xE9,QString(QChar(0x2030)));
        m_keymap.insert(0xEA,QString(QChar(0x00DE)));
        m_keymap.insert(0xEB,QString(QChar(0x0176)));
        m_keymap.insert(0xEC,QString(QChar(0x00DB)));
        m_keymap.insert(0xED,QString(QChar(0x00CE)));
        m_keymap.insert(0xEE,QString(QChar(0x00D4)));
        m_keymap.insert(0xEF,QString(QChar(0x0326)));
        m_keymap.insert(0xF0,QString(QChar(0x201D)));
        m_keymap.insert(0xF1,QString(QChar(0x2019)));
        m_keymap.insert(0xFE,QString(QChar(0x00BB)));
        m_keymap.insert(0xF2,QString(QChar(0x00C2)));
        m_keymap.insert(0xF3,QString(QChar(0x00B7)));
        m_keymap.insert(0xF4,QString(QChar(0x00D0)));
        m_keymap.insert(0xF5,QString(QChar(0x0330)));
        m_keymap.insert(0xF6,QString(QChar(0x2038)));
        m_keymap.insert(0xF7,QString(QChar(0x0331)));
        m_keymap.insert(0xF8,QString(QChar(0x030B)));
        m_keymap.insert(0xF9,QString(QChar(0x030A)));
        m_keymap.insert(0xFA,QString(QChar(0x0335)));
        m_keymap.insert(0xFB,QString(QChar(0x2116)));
        m_keymap.insert(0xFC,QString(QChar(0x00C6)));
        m_keymap.insert(0xFF,QString(QChar(0x0309)));
        m_keymap.insert(0x100,QString(QChar(0x0323)));
        m_keymap.insert(0x101,QString(QChar(0x0327)));
        m_keymap.insert(0x102,QString(QChar(0x030C)));
        m_keymap.insert(0x103,QString(QChar(0x0306)));
        m_keymap.insert(0x104,QString(QChar(0x0303)));
        m_keymap.insert(0x105,QString(QChar(0x0328)));
        m_keymap.insert(0x106,QString(QChar(0x02BC)));
        m_keymap.insert(0x107,QString(QChar(0x0294)));
        m_keymap.insert(0x108,QString(QChar(0x00BF)));
    }
};

#endif // WELSH_AUTOMATA_H
