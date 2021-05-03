// Copyright (c) 2015-2018 LG Electronics, Inc.
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

#ifndef ITALIAN_AUTOMATA_H
#define ITALIAN_AUTOMATA_H

#include "automatabase.h"
#include <QLocale>

class ItalianAutomata : public AutomataBase
{

public:
    ItalianAutomata()
    {
        addSymbolKeys();
        addNumberKeys();
        addShiftKeys();
        addNormalKeys();
        addAccentKeys();
        addAltKeysForHID();
        addShiftedAltKeysForHID();

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
        return new ItalianAutomata();
    }
private:
    void addSymbolKeys()
    {
        m_keymap.insert(0x21,QString(QChar(0x21)));
        m_keymap.insert(0x23,QString(QChar(0xA3)));
        m_keymap.insert(0x24,QString(QChar(0x24)));
        m_keymap.insert(0x25,QString(QChar(0x25)));
        m_keymap.insert(0x26,QString(QChar(0x2F)));
        m_keymap.insert(0x27,QString(QChar(0x27)));
        m_keymap.insert(0x28,QString(QChar(0x29)));
        m_keymap.insert(0x29,QString(QChar(0x3D)));
        m_keymap.insert(0x2a,QString(QChar(0x28)));
        m_keymap.insert(0x2b,QString(QChar(0x5E)));
        m_keymap.insert(0x2c,QString(QChar(0x2c)));
        m_keymap.insert(0x2d,QString(QChar(0x27)));
        m_keymap.insert(0x2e,QString(QChar(0x2e)));
        m_keymap.insert(0x2f,QString(QChar(0x2D)));
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
        m_keymap.insert(0x3a,QString(QChar(0x3a)));
        m_keymap.insert(0x3b,QString(QChar(0x3b)));
        m_keymap.insert(0x3c,QString(QChar(0x3B)));
        m_keymap.insert(0x3e,QString(QChar(0x3A)));
        m_keymap.insert(0x3f,QString(QChar(0x5F)));
        m_keymap.insert(0x40,QString(QChar(0x22)));
        m_keymap.insert(0x41,QString(QChar(0x41)));
        m_keymap.insert(0x42,QString(QChar(0x42)));
        m_keymap.insert(0x43,QString(QChar(0x43)));
        m_keymap.insert(0x44,QString(QChar(0x44)));
        m_keymap.insert(0x45,QString(QChar(0x45)));
        m_keymap.insert(0x46,QString(QChar(0x46)));
        m_keymap.insert(0x47,QString(QChar(0x47)));
        m_keymap.insert(0x48,QString(QChar(0x48)));
        m_keymap.insert(0x49,QString(QChar(0x49)));
        m_keymap.insert(0x4a,QString(QChar(0x4a)));
        m_keymap.insert(0x4b,QString(QChar(0x4b)));
        m_keymap.insert(0x4c,QString(QChar(0x4c)));
        m_keymap.insert(0x4d,QString(QChar(0x4d)));
        m_keymap.insert(0x4e,QString(QChar(0x4e)));
        m_keymap.insert(0x4f,QString(QChar(0x4f)));
        m_keymap.insert(0x50,QString(QChar(0x50)));
        m_keymap.insert(0x51,QString(QChar(0x51)));
        m_keymap.insert(0x52,QString(QChar(0x52)));
        m_keymap.insert(0x53,QString(QChar(0x53)));
        m_keymap.insert(0x54,QString(QChar(0x54)));
        m_keymap.insert(0x55,QString(QChar(0x55)));
        m_keymap.insert(0x56,QString(QChar(0x56)));
        m_keymap.insert(0x57,QString(QChar(0x57)));
        m_keymap.insert(0x58,QString(QChar(0x58)));
        m_keymap.insert(0x59,QString(QChar(0x59)));
        m_keymap.insert(0x5a,QString(QChar(0x5a)));
        m_keymap.insert(0x5c,QString(QChar(0x5c)));
        m_keymap.insert(0x5d,QString(QChar(0x2B)));
        m_keymap.insert(0x5e,QString(QChar(0x26)));
        m_keymap.insert(0x5f,QString(QChar(0x3f)));
    }

    void addNormalKeys()
    {
        m_keymap.insert(0x60,QString(QChar(0x5C)));
        m_keymap.insert(0x61,QString(QChar(0x61)));
        m_keymap.insert(0x62,QString(QChar(0x62)));
        m_keymap.insert(0x63,QString(QChar(0x63)));
        m_keymap.insert(0x64,QString(QChar(0x64)));
        m_keymap.insert(0x65,QString(QChar(0x65)));
        m_keymap.insert(0x66,QString(QChar(0x66)));
        m_keymap.insert(0x67,QString(QChar(0x67)));
        m_keymap.insert(0x68,QString(QChar(0x68)));
        m_keymap.insert(0x69,QString(QChar(0x69)));
        m_keymap.insert(0x6a,QString(QChar(0x6a)));
        m_keymap.insert(0x6b,QString(QChar(0x6b)));
        m_keymap.insert(0x6c,QString(QChar(0x6c)));
        m_keymap.insert(0x6d,QString(QChar(0x6d)));
        m_keymap.insert(0x6e,QString(QChar(0x6e)));
        m_keymap.insert(0x6f,QString(QChar(0x6f)));
        m_keymap.insert(0x70,QString(QChar(0x70)));
        m_keymap.insert(0x71,QString(QChar(0x71)));
        m_keymap.insert(0x72,QString(QChar(0x72)));
        m_keymap.insert(0x73,QString(QChar(0x73)));
        m_keymap.insert(0x74,QString(QChar(0x74)));
        m_keymap.insert(0x75,QString(QChar(0x75)));
        m_keymap.insert(0x76,QString(QChar(0x76)));
        m_keymap.insert(0x77,QString(QChar(0x77)));
        m_keymap.insert(0x78,QString(QChar(0x78)));
        m_keymap.insert(0x79,QString(QChar(0x79)));
        m_keymap.insert(0x7a,QString(QChar(0x7a)));
        m_keymap.insert(0x7d,QString(QChar(0x2A)));
        m_keymap.insert(0x7e,QString(QChar(0x7C)));
        m_keymap.insert(0x20,QString(QChar(0x20)));
    }

     void addAccentKeys()
     {
         m_keymap.insert(0x5b,QString(QChar(0xe8)));
         m_keymap.insert(0x3b,QString(QChar(0xf2)));
         m_keymap.insert(0x27,QString(QChar(0xe0)));
         m_keymap.insert(0x5c,QString(QChar(0xf9)));
         m_keymap.insert(0x7b,QString(QChar(0xe9)));
         m_keymap.insert(0x3a,QString(QChar(0xe7)));
         m_keymap.insert(0x3d,QString(QChar(0xEC)));
         m_keymap.insert(0x22,QString(QChar(0xB0)));
         m_keymap.insert(0x7c,QString(QChar(0xA7)));

        //These accent keys donot have a HID mapping
         m_keymap.insert(0xed,QString(QChar(0xed)));
         m_keymap.insert(0xee,QString(QChar(0xee)));
         m_keymap.insert(0xf3,QString(QChar(0xf3)));
         m_keymap.insert(0xfa,QString(QChar(0xfa)));
         m_keymap.insert(0xc0,QString(QChar(0xc0)));
         m_keymap.insert(0xc8,QString(QChar(0xc8)));
         m_keymap.insert(0xc9,QString(QChar(0xc9)));
         m_keymap.insert(0xcc,QString(QChar(0xcc)));
         m_keymap.insert(0xcd,QString(QChar(0xcd)));
         m_keymap.insert(0xce,QString(QChar(0xce)));
         m_keymap.insert(0xd2,QString(QChar(0xd2)));
         m_keymap.insert(0xd3,QString(QChar(0xd3)));
         m_keymap.insert(0xd9,QString(QChar(0xd9)));
         m_keymap.insert(0xda,QString(QChar(0xda)));
         m_keymap.insert(0x401,QString(QChar(0x40)));
     }

     void addAltKeysForHID()
     {
         m_keymap.insert(0xA4,QString(QChar(0x20AC)));
         m_keymap.insert(0xAE,QString(QChar(0x20AC)));
         m_keymap.insert(0xB6,QString(QChar(0x5B)));
         m_keymap.insert(0xB7,QString(QChar(0x5D)));
         m_keymap.insert(0xC2,QString(QChar(0x23)));
         m_keymap.insert(0xC1,QString(QChar(0x40)));
      }

     void addShiftedAltKeysForHID()
     {
         m_keymap.insert(0xF0,QString(QChar(0x7B)));
         m_keymap.insert(0xF1,QString(QChar(0x7D)));
     }
};
#endif // ITALIAN_AUTOMATA_H

