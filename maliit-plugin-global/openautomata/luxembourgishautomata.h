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

#ifndef LUXEMBOURGISH_AUTOMATA_H
#define LUXEMBOURGISH_AUTOMATA_H

#include "automatabase.h"
#include <QLocale>

class LuxembourgishAutomata : public AutomataBase
{

public:
    LuxembourgishAutomata()
    {
        m_accentSelect = false;

        addSymbolKeys();
        addNumberKeys();
        addShiftKeys();
        addNormalKeys();
        addAccentKeys();
        addAltKeysForHID();
    }

    void setPreedit(const QString &preeditString, int cursorPos)
    {
        Q_UNUSED(cursorPos);
        m_surroundingText = preeditString;
    }

    bool isPredictionSupported()
    {
        return true;
    }

    static AutomataBase* create()
    {
        return new LuxembourgishAutomata();
    }
private:
    void addSymbolKeys()
    {
        m_keymap.insert(0x21,QString(QChar(0x2B)));
        m_keymap.insert(0x40,QString(QChar(0x22)));
        m_keymap.insert(0x23,QString(QChar(0x2A)));
        m_keymap.insert(0x24,QString(QChar(0xe7)));
        m_keymap.insert(0x25,QString(QChar(0x25)));
        m_keymap.insert(0x5E,QString(QChar(0x26)));
        m_keymap.insert(0x26,QString(QChar(0x2F)));
        m_keymap.insert(0x2A,QString(QChar(0x28)));
        m_keymap.insert(0x28,QString(QChar(0x29)));
        m_keymap.insert(0x29,QString(QChar(0x3D)));
        m_keymap.insert(0x5F,QString(QChar(0x3F)));
        m_keymap.insert(0x2B,QString(QChar(0x60)));
        m_keymap.insert(0x2D,QString(QChar(0x27)));
        m_keymap.insert(0x3D,QString(QChar(0x5E)));
        m_keymap.insert(0x1A,QString(QChar(0x40)));
        m_keymap.insert(0x1B,QString(QChar(0x23)));
        m_keymap.insert(0x1C,QString(QChar(0x5E)));
        m_keymap.insert(0x1D,QString(QChar(0x26)));
        m_keymap.insert(0x1E,QString(QChar(0x2A)));
        m_keymap.insert(0x1F,QString(QChar(0x28)));
        m_keymap.insert(0xE7,QString(QChar(0x24)));
        m_keymap.insert(0x01AB,QString(QChar(0x29)));
        m_keymap.insert(0x02AB,QString(QChar(0x2D)));
        m_keymap.insert(0x03AB,QString(QChar(0x3D)));
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
        m_keymap.insert(0x51,QString(QChar(0x51)));
        m_keymap.insert(0x57,QString(QChar(0x57)));
        m_keymap.insert(0x45,QString(QChar(0x45)));
        m_keymap.insert(0x52,QString(QChar(0x52)));
        m_keymap.insert(0x54,QString(QChar(0x54)));
        m_keymap.insert(0x59,QString(QChar(0x5A)));
        m_keymap.insert(0x55,QString(QChar(0x55)));
        m_keymap.insert(0x49,QString(QChar(0x49)));
        m_keymap.insert(0x4F,QString(QChar(0x4F)));
        m_keymap.insert(0x50,QString(QChar(0x50)));
        m_keymap.insert(0x7B,QString(QChar(0xFC)));
        m_keymap.insert(0x7D,QString(QChar(0x21)));
        m_keymap.insert(0x41,QString(QChar(0x41)));
        m_keymap.insert(0x53,QString(QChar(0x53)));
        m_keymap.insert(0x44,QString(QChar(0x44)));
        m_keymap.insert(0x46,QString(QChar(0x46)));
        m_keymap.insert(0x47,QString(QChar(0x47)));
        m_keymap.insert(0x48,QString(QChar(0x48)));
        m_keymap.insert(0x4A,QString(QChar(0x4A)));
        m_keymap.insert(0x4B,QString(QChar(0x4B)));
        m_keymap.insert(0x4C,QString(QChar(0x4C)));
        m_keymap.insert(0x3A,QString(QChar(0xF6)));
        m_keymap.insert(0x22,QString(QChar(0xE4)));
        m_keymap.insert(0x5A,QString(QChar(0x59)));
        m_keymap.insert(0x58,QString(QChar(0x58)));
        m_keymap.insert(0x43,QString(QChar(0x43)));
        m_keymap.insert(0x56,QString(QChar(0x56)));
        m_keymap.insert(0x42,QString(QChar(0x42)));
        m_keymap.insert(0x4E,QString(QChar(0x4E)));
        m_keymap.insert(0x4D,QString(QChar(0x4D)));
        m_keymap.insert(0x3C,QString(QChar(0x3B)));
        m_keymap.insert(0x3E,QString(QChar(0x3A)));
        m_keymap.insert(0x3F,QString(QChar(0x5F)));
        m_keymap.insert(0x20,QString(QChar(0x20)));
    }

    void addNormalKeys()
    {
        m_keymap.insert(0x71,QString(QChar(0x71)));
        m_keymap.insert(0x77,QString(QChar(0x77)));
        m_keymap.insert(0x65,QString(QChar(0x65)));
        m_keymap.insert(0x72,QString(QChar(0x72)));
        m_keymap.insert(0x74,QString(QChar(0x74)));
        m_keymap.insert(0x79,QString(QChar(0x7A)));
        m_keymap.insert(0x75,QString(QChar(0x75)));
        m_keymap.insert(0x69,QString(QChar(0x69)));
        m_keymap.insert(0x6F,QString(QChar(0x6F)));
        m_keymap.insert(0x70,QString(QChar(0x70)));
        m_keymap.insert(0x5B,QString(QChar(0xE8)));
        m_keymap.insert(0x5D,QString(QChar(0xA8)));
        m_keymap.insert(0x61,QString(QChar(0x61)));
        m_keymap.insert(0x73,QString(QChar(0x73)));
        m_keymap.insert(0x64,QString(QChar(0x64)));
        m_keymap.insert(0x66,QString(QChar(0x66)));
        m_keymap.insert(0x67,QString(QChar(0x67)));
        m_keymap.insert(0x68,QString(QChar(0x68)));
        m_keymap.insert(0x6A,QString(QChar(0x6A)));
        m_keymap.insert(0x6B,QString(QChar(0x6B)));
        m_keymap.insert(0x6C,QString(QChar(0x6C)));
        m_keymap.insert(0x3B,QString(QChar(0xE9)));
        m_keymap.insert(0x27,QString(QChar(0xE0)));
        m_keymap.insert(0x7A,QString(QChar(0x79)));
        m_keymap.insert(0x78,QString(QChar(0x78)));
        m_keymap.insert(0x63,QString(QChar(0x63)));
        m_keymap.insert(0x76,QString(QChar(0x76)));
        m_keymap.insert(0x62,QString(QChar(0x62)));
        m_keymap.insert(0x6E,QString(QChar(0x6E)));
        m_keymap.insert(0x6D,QString(QChar(0x6D)));
        m_keymap.insert(0x2C,QString(QChar(0x2C)));
        m_keymap.insert(0x2E,QString(QChar(0x2E)));
        m_keymap.insert(0x2F,QString(QChar(0x2D)));
    }

     void addAccentKeys()
     {
         //lower case
        m_keymap.insert(0x60,QString(QChar(0xA7)));
         //upper case
        m_keymap.insert(0x7E,QString(QChar(0xB0)));
     }

     void addAltKeysForHID()
     {
       m_keymap.insert(0xA0,QString(QChar(0x00a6)));
       m_keymap.insert(0xA1,QString(QChar(0x0040)));
       m_keymap.insert(0xA2,QString(QChar(0x0023)));
       m_keymap.insert(0xA3,QString(QChar(0x00A3)));
       m_keymap.insert(0xA4,QString(QChar(0x00a7)));
       m_keymap.insert(0xA5,QString(QChar(0x00ac)));
       m_keymap.insert(0xA6,QString(QChar(0x007c)));
       m_keymap.insert(0xA7,QString(QChar(0x00a2)));
       m_keymap.insert(0xAA,QString(QChar(0x00b4)));
       m_keymap.insert(0xAB,QString(QChar(0x007e)));
       m_keymap.insert(0xAE,QString(QChar(0x20ac)));
       m_keymap.insert(0xB6,QString(QChar(0x005b)));
       m_keymap.insert(0xB7,QString(QChar(0x005d)));
       m_keymap.insert(0xC2,QString(QChar(0x007b)));
     }
};
#endif // LUXEMBOURGISH_AUTOMATA_H

