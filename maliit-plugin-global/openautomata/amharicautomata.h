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

#ifndef AMHARIC_AUTOMATA_H
#define AMHARIC_AUTOMATA_H

#include "automatabase.h"
#include <QLocale>

class AmharicAutomata  : public AutomataBase
{

public:
    AmharicAutomata ()
    {
        addSymbolKeys();
        addNumberKeys();
        addShiftKeys();
        addNormalKeys();
    }

    void setPreedit(const QString &preeditString, int cursorPos)
    {
        m_surroundingText = preeditString;
    }

    bool isPredictionSupported()
    {
        return false;
    }

    static AutomataBase* create()
    {
        return new AmharicAutomata ();
    }
private:
    void addSymbolKeys()
    {
        m_keymap.insert(0x7E,QString(0x7E));
        m_keymap.insert(0x60,QString(0x60));
        m_keymap.insert(0x21,QString(0x21));
        m_keymap.insert(0x40,QString(0x22));
        m_keymap.insert(0x23,QString(0x2166));
        m_keymap.insert(0x24,QString(0x3B));
        m_keymap.insert(0x25,QString(0x25));
        m_keymap.insert(0x5e,QString(0x3A));
        m_keymap.insert(0x26,QString(0x3F));
        m_keymap.insert(0x2a,QString(0x2A));
        m_keymap.insert(0x28,QString(0x28));
        m_keymap.insert(0x29,QString(0x29));
        m_keymap.insert(0x5f,QString(0x5f));
        m_keymap.insert(0x2b,QString(0x2b));
    }

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

    void addShiftKeys()
    {
        m_keymap.insert(0x51,QString(0x51));
        m_keymap.insert(0x57,QString(0x0DC));
        m_keymap.insert(0x45,QString(0x45));
        m_keymap.insert(0x52,QString(0x52));
        m_keymap.insert(0x54,QString(0x54));
        m_keymap.insert(0x59,QString(0x59));
        m_keymap.insert(0x55,QString(0x55));
        m_keymap.insert(0x49,QString(0x0130));
        m_keymap.insert(0x4F,QString(0x4F));
        m_keymap.insert(0x50,QString(0x50));
        m_keymap.insert(0x7B,QString(0xD6));
        m_keymap.insert(0x7D,QString(0x011E));
        m_keymap.insert(0x41,QString(0x41));
        m_keymap.insert(0x53,QString(0x53));
        m_keymap.insert(0x44,QString(0x44));
        m_keymap.insert(0x46,QString(0x46));
        m_keymap.insert(0x47,QString(0x47));
        m_keymap.insert(0x48,QString(0x48));
        m_keymap.insert(0x4A,QString(0x4A));
        m_keymap.insert(0x4B,QString(0x4B));
        m_keymap.insert(0x4C,QString(0x4C));
        m_keymap.insert(0x3A,QString(0x49));
        m_keymap.insert(0x22,QString(0x018F));
        m_keymap.insert(0x7C,QString(0x2F));
        m_keymap.insert(0x5A,QString(0x5A));
        m_keymap.insert(0x58,QString(0x58));
        m_keymap.insert(0x43,QString(0x43));
        m_keymap.insert(0x56,QString(0x56));
        m_keymap.insert(0x42,QString(0x42));
        m_keymap.insert(0x4E,QString(0x4E));
        m_keymap.insert(0x4D,QString(0x4D));
        m_keymap.insert(0x3C,QString(0xC7));
        m_keymap.insert(0x3E,QString(0x015E));
        m_keymap.insert(0x3F,QString(0x2C));
    }

    void addNormalKeys()
    {
        m_keymap.insert(0x2d,QString(0x2d));
        m_keymap.insert(0x3D,QString(0x3D));
        m_keymap.insert(0x71,QString(0x71));
        m_keymap.insert(0x77,QString(0xFC));
        m_keymap.insert(0x65,QString(0x65));
        m_keymap.insert(0x72,QString(0x72));
        m_keymap.insert(0x74,QString(0x74));
        m_keymap.insert(0x79,QString(0x79));
        m_keymap.insert(0x75,QString(0x75));
        m_keymap.insert(0x69,QString(0x69));
        m_keymap.insert(0x6f,QString(0x6f));
        m_keymap.insert(0x70,QString(0x70));
        m_keymap.insert(0x5B,QString(0xF6));
        m_keymap.insert(0x5D,QString(0x011F));
        m_keymap.insert(0x61,QString(0x61));
        m_keymap.insert(0x73,QString(0x73));
        m_keymap.insert(0x64,QString(0x64));
        m_keymap.insert(0x66,QString(0x66));
        m_keymap.insert(0x67,QString(0x67));
        m_keymap.insert(0x68,QString(0x68));
        m_keymap.insert(0x6A,QString(0x6A));
        m_keymap.insert(0x6B,QString(0x6B));
        m_keymap.insert(0x6C,QString(0x6C));
        m_keymap.insert(0x3B,QString(0x0131));
        m_keymap.insert(0x27,QString(0x0259));
        m_keymap.insert(0x5C,QString(0x5C));
        m_keymap.insert(0x7A,QString(0x7A));
        m_keymap.insert(0x78,QString(0x78));
        m_keymap.insert(0x63,QString(0x63));
        m_keymap.insert(0x76,QString(0x76));
        m_keymap.insert(0x62,QString(0x62));
        m_keymap.insert(0x6E,QString(0x6E));
        m_keymap.insert(0x6D,QString(0x6D));
        m_keymap.insert(0x2C,QString(0xE7));
        m_keymap.insert(0x2E,QString(0x015F));
        m_keymap.insert(0x2F,QString(0x2E));
        m_keymap.insert(0x20,QString(0x20));
    }
};
#endif // AMHARIC_AUTOMATA_H

