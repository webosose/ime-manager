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
        m_keymap.insert(0x21,QString(QChar(0x090D)));
        m_keymap.insert(0x40,QString(QChar(0x0945)));
        m_keymap.insert(0x23,QString("\u094D\u0930"));
        m_keymap.insert(0x24,QString("\u0930\u094D"));
        m_keymap.insert(0x25,QString("\u091C\u094D\u091E"));
        m_keymap.insert(0x5e,QString("\u0924\u094D\u0930"));
        m_keymap.insert(0x26,QString("\u0915\u094D\u0937"));
        m_keymap.insert(0x2a,QString("\u0936\u094D\u0930"));
        m_keymap.insert(0x28,QString(QChar(0x28)));
        m_keymap.insert(0x29,QString(QChar(0x29)));
        m_keymap.insert(0x5f,QString(QChar(0x0903)));
        m_keymap.insert(0x2b,QString(QChar(0x090B)));
    }

    void addNumberKeys()
    {
        m_keymap.insert(0x30,QString(QChar(0x0966)));
        m_keymap.insert(0x31,QString(QChar(0x0967)));
        m_keymap.insert(0x32,QString(QChar(0x0968)));
        m_keymap.insert(0x33,QString(QChar(0x0969)));
        m_keymap.insert(0x34,QString(QChar(0x096A)));
        m_keymap.insert(0x35,QString(QChar(0x096B)));
        m_keymap.insert(0x36,QString(QChar(0x096C)));
        m_keymap.insert(0x37,QString(QChar(0x096D)));
        m_keymap.insert(0x38,QString(QChar(0x096E)));
        m_keymap.insert(0x39,QString(QChar(0x096F)));
    }

    void addShiftKeys()
    {
        m_keymap.insert(0x51,QString(QChar(0x0914)));
        m_keymap.insert(0x57,QString(QChar(0x0910)));
        m_keymap.insert(0x45,QString(QChar(0x0906)));
        m_keymap.insert(0x52,QString(QChar(0x0908)));
        m_keymap.insert(0x54,QString(QChar(0x090A)));
        m_keymap.insert(0x59,QString(QChar(0x092D)));
        m_keymap.insert(0x55,QString(QChar(0x0919)));
        m_keymap.insert(0x49,QString(QChar(0x0918)));
        m_keymap.insert(0x4F,QString(QChar(0x0927)));
        m_keymap.insert(0x50,QString(QChar(0x091D)));
        m_keymap.insert(0x7B,QString(QChar(0x0922)));
        m_keymap.insert(0x7D,QString(QChar(0x091E)));
        m_keymap.insert(0x41,QString(QChar(0x0913)));
        m_keymap.insert(0x53,QString(QChar(0x090F)));
        m_keymap.insert(0x44,QString(QChar(0x0905)));
        m_keymap.insert(0x46,QString(QChar(0x0907)));
        m_keymap.insert(0x47,QString(QChar(0x0909)));
        m_keymap.insert(0x48,QString(QChar(0x092B)));
        m_keymap.insert(0x4A,QString(QChar(0x0931)));
        m_keymap.insert(0x4b,QString(QChar(0x0916)));
        m_keymap.insert(0x4c,QString(QChar(0x0925)));
        m_keymap.insert(0x3a,QString(QChar(0x091B)));
        m_keymap.insert(0x22,QString(QChar(0x0920)));
        m_keymap.insert(0x7C,QString(QChar(0x0911)));
        m_keymap.insert(0x58,QString(QChar(0x0901)));
        m_keymap.insert(0x43,QString(QChar(0x0923)));
        m_keymap.insert(0x4E,QString(QChar(0x0933)));
        m_keymap.insert(0x4D,QString(QChar(0x0936)));
        m_keymap.insert(0x3C,QString(QChar(0x0937)));
        m_keymap.insert(0x3E,QString(QChar(0x0964)));
        m_keymap.insert(0x3F,QString(QChar(0x095F)));
    }

    void addNormalKeys()
    {
        m_keymap.insert(0x2d,QString(QChar(0x2d)));
        m_keymap.insert(0x3D,QString(QChar(0x0943)));
        m_keymap.insert(0x71,QString(QChar(0x094C)));
        m_keymap.insert(0x77,QString(QChar(0x0948)));
        m_keymap.insert(0x65,QString(QChar(0x093E)));
        m_keymap.insert(0x72,QString(QChar(0x0940)));
        m_keymap.insert(0x74,QString(QChar(0x0942)));
        m_keymap.insert(0x79,QString(QChar(0x092C)));
        m_keymap.insert(0x75,QString(QChar(0x0939)));
        m_keymap.insert(0x69,QString(QChar(0x0917)));
        m_keymap.insert(0x6f,QString(QChar(0x0926)));
        m_keymap.insert(0x70,QString(QChar(0x091C)));
        m_keymap.insert(0x5B,QString(QChar(0x0921)));
        m_keymap.insert(0x5D,QString(QChar(0x093C)));
        m_keymap.insert(0x61,QString(QChar(0x094B)));
        m_keymap.insert(0x73,QString(QChar(0x0947)));
        m_keymap.insert(0x64,QString(QChar(0x094D)));
        m_keymap.insert(0x66,QString(QChar(0x093F)));
        m_keymap.insert(0x67,QString(QChar(0x0941)));
        m_keymap.insert(0x68,QString(QChar(0x092A)));
        m_keymap.insert(0x6A,QString(QChar(0x0930)));
        m_keymap.insert(0x6B,QString(QChar(0x0915)));
        m_keymap.insert(0x6C,QString(QChar(0x0924)));
        m_keymap.insert(0x3B,QString(QChar(0x091A)));
        m_keymap.insert(0x27,QString(QChar(0x091F)));
        m_keymap.insert(0x5C,QString(QChar(0x0949)));
        m_keymap.insert(0x78,QString(QChar(0x0902)));
        m_keymap.insert(0x63,QString(QChar(0x092E)));
        m_keymap.insert(0x76,QString(QChar(0x0928)));
        m_keymap.insert(0x62,QString(QChar(0x0935)));
        m_keymap.insert(0x6E,QString(QChar(0x0932)));
        m_keymap.insert(0x6D,QString(QChar(0x0938)));
        m_keymap.insert(0x2C,QString(QChar(0x2C)));
        m_keymap.insert(0x2E,QString(QChar(0x2E)));
        m_keymap.insert(0x2F,QString(QChar(0x092F)));
        m_keymap.insert(0x20,QString(QChar(0x20)));
    }

     void addAltedKeys()
     {
         m_keymap.insert(0xA0,QString(QChar(0x31)));
         m_keymap.insert(0xA1,QString(QChar(0x32)));
         m_keymap.insert(0xA2,QString(QChar(0x33)));
         m_keymap.insert(0xA3,QString(QChar(0x34)));
         m_keymap.insert(0xA4,QString(QChar(0x35)));
         m_keymap.insert(0xA5,QString(QChar(0x36)));
         m_keymap.insert(0xA6,QString(QChar(0x37)));
         m_keymap.insert(0xA7,QString(QChar(0x38)));
         m_keymap.insert(0xA8,QString(QChar(0x39)));
         m_keymap.insert(0xA9,QString(QChar(0x30)));
         m_keymap.insert(0xAA,QString(QChar(0x2D)));
         m_keymap.insert(0xAB,QString(QChar(0x3D)));
         m_keymap.insert(0xC3,QString(QChar(0x60)));
         m_keymap.insert(0xB6,QString(QChar(0x5B)));
         m_keymap.insert(0xB7,QString(QChar(0x5D)));
         m_keymap.insert(0xC1,QString(QChar(0x3B)));
         m_keymap.insert(0xC2,QString(QChar(0x27)));
         m_keymap.insert(0xC4,QString(QChar(0x5C)));
         m_keymap.insert(0xCC,QString(QChar(0x2C)));
         m_keymap.insert(0xCD,QString(QChar(0x2E)));
         m_keymap.insert(0xCE,QString(QChar(0x2F)));
     }

     void addAltShiftedKeys()
     {
         m_keymap.insert(0xDA,QString(QChar(0x21)));
         m_keymap.insert(0xDB,QString(QChar(0x40)));
         m_keymap.insert(0xDC,QString(QChar(0x23)));
         m_keymap.insert(0xDD,QString(QChar(0x24)));
         m_keymap.insert(0xDE,QString(QChar(0x25)));
         m_keymap.insert(0xDF,QString(QChar(0x5E)));
         m_keymap.insert(0xE0,QString(QChar(0x26)));
         m_keymap.insert(0xE1,QString(QChar(0x2A)));
         m_keymap.insert(0xE2,QString(QChar(0x28)));
         m_keymap.insert(0xE3,QString(QChar(0x29)));
         m_keymap.insert(0xE4,QString(QChar(0x5F)));
         m_keymap.insert(0xE5,QString(QChar(0x2B)));
         m_keymap.insert(0xFD,QString(QChar(0x7E)));
         m_keymap.insert(0xF0,QString(QChar(0x7B)));
         m_keymap.insert(0xF1,QString(QChar(0x7D)));
         m_keymap.insert(0xFB,QString(QChar(0x3A)));
         m_keymap.insert(0xFC,QString(QChar(0x22)));
         m_keymap.insert(0xFE,QString(QChar(0x7C)));
         m_keymap.insert(0x106,QString(QChar(0x3C)));
         m_keymap.insert(0x107,QString(QChar(0x3E)));
         m_keymap.insert(0x108,QString(QChar(0x3F)));
         m_keymap.insert(0xFF,QString(QChar(0x093D)));
         m_keymap.insert(0x100,QString(QChar(0x0950)));
         m_keymap.insert(0x101,QString(QChar(0x20B9)));
     }
};
#endif // MARATHI_AUTOMATA_H

