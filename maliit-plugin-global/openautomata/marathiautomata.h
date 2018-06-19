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

#ifndef MARATHI_AUTOMATA_H
#define MARATHI_AUTOMATA_H

#include "automatabase.h"
#include <QLocale>

class MarathiAutomata : public AutomataBase
{

public:
    MarathiAutomata()
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
        return new MarathiAutomata();
    }
private:
    void addSymbolKeys()
    {
        m_keymap.insert(0x21,QString(0x090D));
        m_keymap.insert(0x40,QString(0x0945));
        m_keymap.insert(0x23,QString("\u094D\u0930"));
        m_keymap.insert(0x24,QString("\u0930\u094D"));
        m_keymap.insert(0x25,QString("\u091C\u094D\u091E"));
        m_keymap.insert(0x5e,QString("\u0924\u094D\u0930"));
        m_keymap.insert(0x26,QString("\u0915\u094D\u0937"));
        m_keymap.insert(0x2a,QString("\u0936\u094D\u0930"));
        m_keymap.insert(0x28,QString(0x28));
        m_keymap.insert(0x29,QString(0x29));
        m_keymap.insert(0x5f,QString(0x0903));
        m_keymap.insert(0x2b,QString(0x090B));
    }

    void addNumberKeys()
    {
        m_keymap.insert(0x30,QString(0x0966));
        m_keymap.insert(0x31,QString(0x0967));
        m_keymap.insert(0x32,QString(0x0968));
        m_keymap.insert(0x33,QString(0x0969));
        m_keymap.insert(0x34,QString(0x096A));
        m_keymap.insert(0x35,QString(0x096B));
        m_keymap.insert(0x36,QString(0x096C));
        m_keymap.insert(0x37,QString(0x096D));
        m_keymap.insert(0x38,QString(0x096E));
        m_keymap.insert(0x39,QString(0x096F));
    }

    void addShiftKeys()
    {
        m_keymap.insert(0x51,QString(0x0914));
        m_keymap.insert(0x57,QString(0x0910));
        m_keymap.insert(0x45,QString(0x0906));
        m_keymap.insert(0x52,QString(0x0908));
        m_keymap.insert(0x54,QString(0x090A));
        m_keymap.insert(0x59,QString(0x092D));
        m_keymap.insert(0x55,QString(0x0919));
        m_keymap.insert(0x49,QString(0x0918));
        m_keymap.insert(0x4F,QString(0x0927));
        m_keymap.insert(0x50,QString(0x091D));
        m_keymap.insert(0x7B,QString(0x0922));
        m_keymap.insert(0x7D,QString(0x091E));
        m_keymap.insert(0x41,QString(0x0913));
        m_keymap.insert(0x53,QString(0x090F));
        m_keymap.insert(0x44,QString(0x0905));
        m_keymap.insert(0x46,QString(0x0907));
        m_keymap.insert(0x47,QString(0x0909));
        m_keymap.insert(0x48,QString(0x092B));
        m_keymap.insert(0x4A,QString(0x0931));
        m_keymap.insert(0x4b,QString(0x0916));
        m_keymap.insert(0x4c,QString(0x0925));
        m_keymap.insert(0x3a,QString(0x091B));
        m_keymap.insert(0x22,QString(0x0920));
        m_keymap.insert(0x7C,QString(0x0911));
        m_keymap.insert(0x58,QString(0x0901));
        m_keymap.insert(0x43,QString(0x0923));
        m_keymap.insert(0x4E,QString(0x0933));
        m_keymap.insert(0x4D,QString(0x0936));
        m_keymap.insert(0x3C,QString(0x0937));
        m_keymap.insert(0x3E,QString(0x0964));
        m_keymap.insert(0x3F,QString(0x095F));
    }

    void addNormalKeys()
    {
        m_keymap.insert(0x2d,QString(0x2d));
        m_keymap.insert(0x3D,QString(0x0943));
        m_keymap.insert(0x71,QString(0x094C));
        m_keymap.insert(0x77,QString(0x0948));
        m_keymap.insert(0x65,QString(0x093E));
        m_keymap.insert(0x72,QString(0x0940));
        m_keymap.insert(0x74,QString(0x0942));
        m_keymap.insert(0x79,QString(0x092C));
        m_keymap.insert(0x75,QString(0x0939));
        m_keymap.insert(0x69,QString(0x0917));
        m_keymap.insert(0x6f,QString(0x0926));
        m_keymap.insert(0x70,QString(0x091C));
        m_keymap.insert(0x5B,QString(0x0921));
        m_keymap.insert(0x5D,QString(0x093C));
        m_keymap.insert(0x61,QString(0x094B));
        m_keymap.insert(0x73,QString(0x0947));
        m_keymap.insert(0x64,QString(0x094D));
        m_keymap.insert(0x66,QString(0x093F));
        m_keymap.insert(0x67,QString(0x0941));
        m_keymap.insert(0x68,QString(0x092A));
        m_keymap.insert(0x6A,QString(0x0930));
        m_keymap.insert(0x6B,QString(0x0915));
        m_keymap.insert(0x6C,QString(0x0924));
        m_keymap.insert(0x3B,QString(0x091A));
        m_keymap.insert(0x27,QString(0x091F));
        m_keymap.insert(0x5C,QString(0x0949));
        m_keymap.insert(0x78,QString(0x0902));
        m_keymap.insert(0x63,QString(0x092E));
        m_keymap.insert(0x76,QString(0x0928));
        m_keymap.insert(0x62,QString(0x0935));
        m_keymap.insert(0x6E,QString(0x0932));
        m_keymap.insert(0x6D,QString(0x0938));
        m_keymap.insert(0x2C,QString(0x2C));
        m_keymap.insert(0x2E,QString(0x2E));
        m_keymap.insert(0x2F,QString(0x092F));
        m_keymap.insert(0x20,QString(0x20));
    }

     void addAltedKeys()
     {
         m_keymap.insert(0xA0,QString(0x31));
         m_keymap.insert(0xA1,QString(0x32));
         m_keymap.insert(0xA2,QString(0x33));
         m_keymap.insert(0xA3,QString(0x34));
         m_keymap.insert(0xA4,QString(0x35));
         m_keymap.insert(0xA5,QString(0x36));
         m_keymap.insert(0xA6,QString(0x37));
         m_keymap.insert(0xA7,QString(0x38));
         m_keymap.insert(0xA8,QString(0x39));
         m_keymap.insert(0xA9,QString(0x30));
         m_keymap.insert(0xAA,QString(0x2D));
         m_keymap.insert(0xAB,QString(0x3D));
         m_keymap.insert(0xC3,QString(0x60));
         m_keymap.insert(0xB6,QString(0x5B));
         m_keymap.insert(0xB7,QString(0x5D));
         m_keymap.insert(0xC1,QString(0x3B));
         m_keymap.insert(0xC2,QString(0x27));
         m_keymap.insert(0xC4,QString(0x5C));
         m_keymap.insert(0xCC,QString(0x2C));
         m_keymap.insert(0xCD,QString(0x2E));
         m_keymap.insert(0xCE,QString(0x2F));
     }

     void addAltShiftedKeys()
     {
         m_keymap.insert(0xDA,QString(0x21));
         m_keymap.insert(0xDB,QString(0x40));
         m_keymap.insert(0xDC,QString(0x23));
         m_keymap.insert(0xDD,QString(0x24));
         m_keymap.insert(0xDE,QString(0x25));
         m_keymap.insert(0xDF,QString(0x5E));
         m_keymap.insert(0xE0,QString(0x26));
         m_keymap.insert(0xE1,QString(0x2A));
         m_keymap.insert(0xE2,QString(0x28));
         m_keymap.insert(0xE3,QString(0x29));
         m_keymap.insert(0xE4,QString(0x5F));
         m_keymap.insert(0xE5,QString(0x2B));
         m_keymap.insert(0xFD,QString(0x7E));
         m_keymap.insert(0xF0,QString(0x7B));
         m_keymap.insert(0xF1,QString(0x7D));
         m_keymap.insert(0xFB,QString(0x3A));
         m_keymap.insert(0xFC,QString(0x22));
         m_keymap.insert(0xFE,QString(0x7C));
         m_keymap.insert(0x106,QString(0x3C));
         m_keymap.insert(0x107,QString(0x3E));
         m_keymap.insert(0x108,QString(0x3F));
         m_keymap.insert(0xFF,QString(0x093D));
         m_keymap.insert(0x100,QString(0x0950));
         m_keymap.insert(0x101,QString(0x20B9));
     }
};
#endif // MARATHI_AUTOMATA_H

