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

#ifndef NEPALI_AUTOMATA_H
#define NEPALI_AUTOMATA_H

#include "automatabase.h"
#include <QLocale>

class NepaliAutomata : public AutomataBase
{

public:
    NepaliAutomata()
    {
        m_keymap.clear();
        addSymbolKeys();
        addNumberKeys();
        addShiftKeys();
        addNormalKeys();
        addAccentKeys();
        addAltKeysForHID();
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
        return new NepaliAutomata();
    }
private:
    void addSymbolKeys()
    {
        m_keymap.insert(0x21,QString(0x0967));
        m_keymap.insert(0x40,QString(0x0968));
        m_keymap.insert(0x23,QString(0x0969));
        m_keymap.insert(0x24,QString(0x096a));
        m_keymap.insert(0x25,QString(0x096b));
        m_keymap.insert(0x5E,QString(0x096c));
        m_keymap.insert(0x26,QString(0x096d));
        m_keymap.insert(0x2A,QString(0x096e));
        m_keymap.insert(0x28,QString(0x096f));
        m_keymap.insert(0x29,QString(0x0966));
        m_keymap.insert(0x5F,QString(0x0029));
        m_keymap.insert(0x2B,QString(0x0902));
        m_keymap.insert(0x2D,QString(0x28));
        m_keymap.insert(0x3D,QString(0x2E));
    }

    void addNumberKeys()
    {
        m_keymap.insert(0x30,QString(0x0923));
        m_keymap.insert(0x31,QString("\u091c\u094d\u091e"));
        m_keymap.insert(0x32,QString(0x0918));
        m_keymap.insert(0x33,QString(0x0919));
        m_keymap.insert(0x34,QString(0x091d));
        m_keymap.insert(0x35,QString(0x091b));
        m_keymap.insert(0x36,QString(0x091f));
        m_keymap.insert(0x37,QString(0x0920));
        m_keymap.insert(0x38,QString(0x0921));
        m_keymap.insert(0x39,QString(0x0922));
    }

    void addShiftKeys()
    {
        m_keymap.insert(0x51,QString(0x094b));
        m_keymap.insert(0x57,QString("\u0927\u094d"));
        m_keymap.insert(0x45,QString("\u092d\u094d"));
        m_keymap.insert(0x52,QString("\u091a\u094d"));
        m_keymap.insert(0x54,QString("\u0924\u094d"));
        m_keymap.insert(0x59,QString("\u0925\u094d"));
        m_keymap.insert(0x55,QString("\u0917\u094d"));
        m_keymap.insert(0x49,QString("\u0915\u094d\u0937"));
        m_keymap.insert(0x4F,QString(0x0907));
        m_keymap.insert(0x50,QString(0x090f));
        m_keymap.insert(0x7B,QString("\u0930\u094d"));
        m_keymap.insert(0x7D,QString(0x0948));
        m_keymap.insert(0x41,QString("\u092c\u094d"));
        m_keymap.insert(0x53,QString("\u0915\u094d"));
        m_keymap.insert(0x44,QString("\u092e\u094d"));
        m_keymap.insert(0x46,QString(0x0901));
        m_keymap.insert(0x47,QString("\u0928\u094d"));
        m_keymap.insert(0x48,QString("\u091c\u094d"));
        m_keymap.insert(0x4A,QString("\u0935\u094d"));
        m_keymap.insert(0x4B,QString("\u092a\u094d"));
        m_keymap.insert(0x4C,QString(0x0940));
        m_keymap.insert(0x3A,QString("\u0938\u094d"));
        m_keymap.insert(0x22,QString(0x0942));
        m_keymap.insert(0xFE,QString(0x094d)); //also in lower case
        m_keymap.insert(0x5A,QString("\u0936\u094d"));
        m_keymap.insert(0x58,QString("\u0939\u094d"));
        m_keymap.insert(0x43,QString(0x090b));
        m_keymap.insert(0x56,QString("\u0916\u094d"));
        m_keymap.insert(0x42,QString("\u0926\u094d"));
        m_keymap.insert(0x4E,QString("\u0932\u094d"));
        m_keymap.insert(0x4D,QString(0x0903));
        m_keymap.insert(0x3C,QString(0x003f));
        m_keymap.insert(0x3E,QString("\u0936\u094d\u0930"));
        m_keymap.insert(0x3F,QString("\u0930\u0942"));
    }

    void addNormalKeys()
    {
        m_keymap.insert(0x71,QString("\u0924\u094d\u0930"));
        m_keymap.insert(0x77,QString(0x0927));
        m_keymap.insert(0x65,QString(0x092D));
        m_keymap.insert(0x72,QString(0x091A));
        m_keymap.insert(0x74,QString(0x0924));
        m_keymap.insert(0x79,QString(0x0925));
        m_keymap.insert(0x75,QString(0x0917));
        m_keymap.insert(0x69,QString(0x0937));
        m_keymap.insert(0x6F,QString(0x092F));
        m_keymap.insert(0x70,QString(0x0909));
        m_keymap.insert(0x5B,QString(0x0943));
        m_keymap.insert(0x5D,QString(0x0947));
        m_keymap.insert(0x61,QString(0x092c));
        m_keymap.insert(0x73,QString(0x0915));
        m_keymap.insert(0x64,QString(0x092e));
        m_keymap.insert(0x66,QString(0x093e));
        m_keymap.insert(0x67,QString(0x0928));
        m_keymap.insert(0x68,QString(0x091c));
        m_keymap.insert(0x6A,QString(0x0935));
        m_keymap.insert(0x6B,QString(0x092a));
        m_keymap.insert(0x6C,QString(0x093f));
        m_keymap.insert(0x3B,QString(0x0938));
        m_keymap.insert(0x27,QString(0x0941));
        m_keymap.insert(0xC4,QString("\u094d\u0930"));
        m_keymap.insert(0x7A,QString(0x0936));
        m_keymap.insert(0x78,QString(0x0939));
        m_keymap.insert(0x63,QString(0x0905));
        m_keymap.insert(0x76,QString(0x0916));
        m_keymap.insert(0x62,QString(0x0926));
        m_keymap.insert(0x6E,QString(0x0932));
        m_keymap.insert(0x6D,QString(0x092b));
        m_keymap.insert(0x2C,QString(0x002c));
        m_keymap.insert(0x2E,QString(0x0964));
        m_keymap.insert(0x2F,QString(0x0930));
        m_keymap.insert(0x20,QString(0x20));
    }

     void addAccentKeys()
     {
		 //lower case
         m_keymap.insert(0x60,QString(0x091e));
                 //upper case
         m_keymap.insert(0x7E,QString("\u091e\u094d"));
     }

     void addAltKeysForHID()
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
         m_keymap.insert(0xAB,QString(0x2B));
         m_keymap.insert(0xB5,QString(0x090A));
         m_keymap.insert(0xB7,QString(0x0914));
         m_keymap.insert(0xC7,QString(0x0906));
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
         m_keymap.insert(0xE2,QString(0x27));
         m_keymap.insert(0xE3,QString(0x22));
         m_keymap.insert(0xE4,QString(0x5F));
         m_keymap.insert(0xE5,QString(0x2B));
         m_keymap.insert(0xE6,QString(0x094c));
         m_keymap.insert(0xEE,QString(0x0908));
         m_keymap.insert(0xEF,QString(0x0910));
         m_keymap.insert(0xF1,QString(0x0913));
     }

};
#endif // NEPALI_AUTOMATA_H

