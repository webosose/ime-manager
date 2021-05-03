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

#ifndef KAZAKH_AUTOMATA_H
#define KAZAKH_AUTOMATA_H

#include "automatabase.h"
#include <QLocale>

class KazakhAutomata : public AutomataBase
{

public:
    KazakhAutomata()
    {
        m_accentSelect = false;

        addSymbolKeys();
        addNumberKeys();
        addShiftKeys();
        addNormalKeys();
        addAccentKeys();
        addAltKeysForHID();
        addShiftAltKeysForHID();
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
        return new KazakhAutomata();
    }

    void addSymbolKeys()
    {
        m_keymap.insert(0x60,QString(QChar(0x28)));
        m_keymap.insert(0x5B,QString(QChar(0x445)));
        m_keymap.insert(0x5D,QString(QChar(0x44A)));
        m_keymap.insert(0x2D,QString(QChar(0x4E9)));
        m_keymap.insert(0x3D,QString(QChar(0x4BB)));
        m_keymap.insert(0x3B,QString(QChar(0x436)));
        m_keymap.insert(0x27,QString(QChar(0x44D)));
        m_keymap.insert(0x3F,QString(QChar(0x3F)));
        m_keymap.insert(0x99,QString(QChar(0x40)));
        m_keymap.insert(0x2C,QString(QChar(0x431)));
        m_keymap.insert(0x2E,QString(QChar(0x44E)));
        m_keymap.insert(0x2F,QString(QChar(0x2F)));
    }

    void addNumberKeys()
    {
        m_keymap.insert(0x31,QString(QChar(0x22)));
        m_keymap.insert(0x32,QString(QChar(0x4D9)));
        m_keymap.insert(0x33,QString(QChar(0x456)));
        m_keymap.insert(0x34,QString(QChar(0x4A3)));
        m_keymap.insert(0x35,QString(QChar(0x493)));
        m_keymap.insert(0x36,QString(QChar(0x2C)));
        m_keymap.insert(0x37,QString(QChar(0x2E)));
        m_keymap.insert(0x38,QString(QChar(0x4AF)));
        m_keymap.insert(0x39,QString(QChar(0x4B1)));
        m_keymap.insert(0x30,QString(QChar(0x49B)));
    }

    void addNormalKeys()
    {
        m_keymap.insert(0x71,QString(QChar(0x439)));
        m_keymap.insert(0x77,QString(QChar(0x446)));
        m_keymap.insert(0x65,QString(QChar(0x443)));
        m_keymap.insert(0x72,QString(QChar(0x43A)));
        m_keymap.insert(0x74,QString(QChar(0x435)));
        m_keymap.insert(0x79,QString(QChar(0x43D)));
        m_keymap.insert(0x75,QString(QChar(0x433)));
        m_keymap.insert(0x69,QString(QChar(0x448)));
        m_keymap.insert(0x6F,QString(QChar(0x449)));
        m_keymap.insert(0x70,QString(QChar(0x437)));
        m_keymap.insert(0x61,QString(QChar(0x444)));
        m_keymap.insert(0x73,QString(QChar(0x44B)));
        m_keymap.insert(0x64,QString(QChar(0x432)));
        m_keymap.insert(0x66,QString(QChar(0x430)));
        m_keymap.insert(0x67,QString(QChar(0x43F)));
        m_keymap.insert(0x68,QString(QChar(0x440)));
        m_keymap.insert(0x6A,QString(QChar(0x43E)));
        m_keymap.insert(0x6B,QString(QChar(0x43B)));
        m_keymap.insert(0x6C,QString(QChar(0x434)));
        m_keymap.insert(0x7A,QString(QChar(0x44F)));
        m_keymap.insert(0x78,QString(QChar(0x447)));
        m_keymap.insert(0x63,QString(QChar(0x441)));
        m_keymap.insert(0x76,QString(QChar(0x43C)));
        m_keymap.insert(0x62,QString(QChar(0x438)));
        m_keymap.insert(0x6E,QString(QChar(0x442)));
        m_keymap.insert(0x6D,QString(QChar(0x44C)));
        m_keymap.insert(0x20,QString(QChar(0x20)));
    }

    void addShiftKeys()
    {
        m_keymap.insert(0x7E,QString(QChar(0x29)));
        m_keymap.insert(0x21,QString(QChar(0x21)));
        m_keymap.insert(0x40,QString(QChar(0x4D8)));
        m_keymap.insert(0x23,QString(QChar(0x406)));
        m_keymap.insert(0x24,QString(QChar(0x4A2)));
        m_keymap.insert(0x25,QString(QChar(0x492)));
        m_keymap.insert(0x5E,QString(QChar(0x3B)));
        m_keymap.insert(0x26,QString(QChar(0x3A)));
        m_keymap.insert(0x2A,QString(QChar(0x4AE)));
        m_keymap.insert(0x28,QString(QChar(0x4B0)));
        m_keymap.insert(0x29,QString(QChar(0x49A)));
        m_keymap.insert(0x5F,QString(QChar(0x4E8)));
        m_keymap.insert(0x2B,QString(QChar(0x4BA)));
        m_keymap.insert(0x51,QString(QChar(0x419)));
        m_keymap.insert(0x57,QString(QChar(0x426)));
        m_keymap.insert(0x45,QString(QChar(0x423)));
        m_keymap.insert(0x52,QString(QChar(0x41A)));
        m_keymap.insert(0x54,QString(QChar(0x415)));
        m_keymap.insert(0x59,QString(QChar(0x41D)));
        m_keymap.insert(0x55,QString(QChar(0x413)));
        m_keymap.insert(0x49,QString(QChar(0x428)));
        m_keymap.insert(0x4F,QString(QChar(0x429)));
        m_keymap.insert(0x50,QString(QChar(0x417)));
        m_keymap.insert(0x7B,QString(QChar(0x425)));
        m_keymap.insert(0x7D,QString(QChar(0x42A)));
        m_keymap.insert(0x41,QString(QChar(0x424)));
        m_keymap.insert(0x53,QString(QChar(0x42B)));
        m_keymap.insert(0x44,QString(QChar(0x412)));
        m_keymap.insert(0x46,QString(QChar(0x410)));
        m_keymap.insert(0x47,QString(QChar(0x41F)));
        m_keymap.insert(0x48,QString(QChar(0x420)));
        m_keymap.insert(0x4A,QString(QChar(0x41E)));
        m_keymap.insert(0x4B,QString(QChar(0x41B)));
        m_keymap.insert(0x4C,QString(QChar(0x414)));
        m_keymap.insert(0x3A,QString(QChar(0x416)));
        m_keymap.insert(0x22,QString(QChar(0x42D)));
        m_keymap.insert(0x5A,QString(QChar(0x42F)));
        m_keymap.insert(0x58,QString(QChar(0x427)));
        m_keymap.insert(0x43,QString(QChar(0x421)));
        m_keymap.insert(0x56,QString(QChar(0x41C)));
        m_keymap.insert(0x42,QString(QChar(0x418)));
        m_keymap.insert(0x4E,QString(QChar(0x422)));
        m_keymap.insert(0x4D,QString(QChar(0x42C)));
        m_keymap.insert(0x3C,QString(QChar(0x411)));
        m_keymap.insert(0x3E,QString(QChar(0x42E)));
    }

    void addAccentKeys()
    {
        m_keymap.insert(0xEB,QString(QChar(0x451)));
        m_keymap.insert(0xCB,QString(QChar(0x401)));
    }

    void addAltKeysForHID()
    {
        m_keymap.insert(0xC3,QString(QChar(0x0451)));

    }

    void addShiftAltKeysForHID()
    {
        m_keymap.insert(0xFD,QString(QChar(0x0401)));

    }

};

#endif // KAZAKH_AUTOMATA_H
