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

#ifndef TELUGU_AUTOMATA_H
#define TELUGU_AUTOMATA_H

#include "automatabase.h"
#include <QLocale>

class TeluguAutomata : public AutomataBase
{

public:
    TeluguAutomata()
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
        return new TeluguAutomata();
    }
private:
    void addSymbolKeys()
    {
        m_keymap.insert(0x7E,QString(0x0C12));
        m_keymap.insert(0x23,QString("\u0C4D\u0C30"));
        m_keymap.insert(0x25,QString("\u0C1C\u0C4D\u0C1E"));
        m_keymap.insert(0x5e,QString("\u0C24\u0C4D\u0C30"));
        m_keymap.insert(0x26,QString("\u0C15\u0C4D\u0C37"));
        m_keymap.insert(0x2a,QString("\u0C36\u0C4D\u0C30"));
        m_keymap.insert(0x28,QString(0x28));
        m_keymap.insert(0x29,QString(0x29));
        m_keymap.insert(0x5f,QString(0x0C03));
        m_keymap.insert(0x2b,QString(0x0C0B));
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
        m_keymap.insert(0x51,QString(0x0C14));
        m_keymap.insert(0x57,QString(0x0C10));
        m_keymap.insert(0x45,QString(0x0C06));
        m_keymap.insert(0x52,QString(0x0C08));
        m_keymap.insert(0x54,QString(0x0C0A));
        m_keymap.insert(0x59,QString(0x0C2D));
        m_keymap.insert(0x55,QString(0x0C19));
        m_keymap.insert(0x49,QString(0x0C18));
        m_keymap.insert(0x4F,QString(0x0C27));
        m_keymap.insert(0x50,QString(0x0C1D));
        m_keymap.insert(0x7B,QString(0x0C22));
        m_keymap.insert(0x7D,QString(0x0C1E));
        m_keymap.insert(0x41,QString(0x0C13));
        m_keymap.insert(0x53,QString(0x0C0F));
        m_keymap.insert(0x44,QString(0x0C05));
        m_keymap.insert(0x46,QString(0x0C07));
        m_keymap.insert(0x47,QString(0x0C09));
        m_keymap.insert(0x48,QString(0x0C2B));
        m_keymap.insert(0x4A,QString(0x0C31));
        m_keymap.insert(0x4b,QString(0x0C16));
        m_keymap.insert(0x4c,QString(0x0C25));
        m_keymap.insert(0x3a,QString(0x0C1B));
        m_keymap.insert(0x22,QString(0x0C20));
        m_keymap.insert(0x5A,QString(0x0C0E));
        m_keymap.insert(0x58,QString(0x0C01));
        m_keymap.insert(0x43,QString(0x0C23));
        m_keymap.insert(0x56,QString(0x0C28));
        m_keymap.insert(0x4E,QString(0x0C33));
        m_keymap.insert(0x4D,QString(0x0C36));
        m_keymap.insert(0x3C,QString(0x0C37));
    }

    void addNormalKeys()
    {
        m_keymap.insert(0x2d,QString(0x2d));
        m_keymap.insert(0x3D,QString(0x0C43));
        m_keymap.insert(0x71,QString(0x0C4C));
        m_keymap.insert(0x77,QString(0x0C48));
        m_keymap.insert(0x65,QString(0x0C3E));
        m_keymap.insert(0x72,QString(0x0C40));
        m_keymap.insert(0x74,QString(0x0C42));
        m_keymap.insert(0x79,QString(0x0C2C));
        m_keymap.insert(0x75,QString(0x0C39));
        m_keymap.insert(0x69,QString(0x0C17));
        m_keymap.insert(0x6f,QString(0x0C26));
        m_keymap.insert(0x70,QString(0x0C1C));
        m_keymap.insert(0x5B,QString(0x0C21));
        m_keymap.insert(0x61,QString(0x0C4B));
        m_keymap.insert(0x73,QString(0x0C47));
        m_keymap.insert(0x64,QString(0x0C4D));
        m_keymap.insert(0x66,QString(0x0C3F));
        m_keymap.insert(0x67,QString(0x0C41));
        m_keymap.insert(0x68,QString(0x0C2A));
        m_keymap.insert(0x6A,QString(0x0C30));
        m_keymap.insert(0x6B,QString(0x0C15));
        m_keymap.insert(0x6C,QString(0x0C24));
        m_keymap.insert(0x3B,QString(0x0C1A));
        m_keymap.insert(0x27,QString(0x0C1F));
        m_keymap.insert(0x7A,QString(0x0C46));
        m_keymap.insert(0x78,QString(0x0C02));
        m_keymap.insert(0x63,QString(0x0C2E));
        m_keymap.insert(0x76,QString(0x0C28));
        m_keymap.insert(0x62,QString(0x0C35));
        m_keymap.insert(0x6E,QString(0x0C32));
        m_keymap.insert(0x6D,QString(0x0C38));
        m_keymap.insert(0x2C,QString(0x2C));
        m_keymap.insert(0x2E,QString(0x2E));
        m_keymap.insert(0x2F,QString(0x0C2F));
        m_keymap.insert(0x60,QString(0x0C4A));
        m_keymap.insert(0x20,QString(0x20));
    }

     void addAltedKeys()
     {
         m_keymap.insert(0xA0,QString(0x0C67));
         m_keymap.insert(0xA1,QString(0x0C68));
         m_keymap.insert(0xA2,QString(0x0C69));
         m_keymap.insert(0xA3,QString(0x0C6A));
         m_keymap.insert(0xA4,QString(0x0C6B));
         m_keymap.insert(0xA5,QString(0x0C6C));
         m_keymap.insert(0xA6,QString(0x0C6D));
         m_keymap.insert(0xA7,QString(0x0C6E));
         m_keymap.insert(0xA8,QString(0x0C6F));
         m_keymap.insert(0xA9,QString(0x0C66));
         m_keymap.insert(0xAA,QString(0x20B9));
         m_keymap.insert(0xAB,QString(0x0C44));
         m_keymap.insert(0xAD,QString(0x0C56));
         m_keymap.insert(0xB5,QString(0x0C59));
         m_keymap.insert(0xB9,QString(0x0C55));
         m_keymap.insert(0xC1,QString(0x0C58));
     }

     void addAltShiftedKeys()
     {
         m_keymap.insert(0xE5,QString(0x0C60));
         m_keymap.insert(0xE9,QString(0x0C61));
         m_keymap.insert(0xF5,QString(0x0C0C));
     }
};
#endif // TELUGU_AUTOMATA_H

