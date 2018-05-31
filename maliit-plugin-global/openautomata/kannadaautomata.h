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

#ifndef KANNADA_AUTOMATA_H
#define KANNADA_AUTOMATA_H

#include "automatabase.h"
#include <QLocale>

class KannadaAutomata : public AutomataBase
{

public:
    KannadaAutomata()
    {
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
        return false;
    }

    static AutomataBase* create()
    {
        return new KannadaAutomata();
    }
private:
    void addSymbolKeys()
    {
        m_keymap.insert(0x21,QString(0x0C92));
        m_keymap.insert(0x23,QString("\u0CCD\u0CB0"));
        m_keymap.insert(0x24,QString("\u0CB0\u0CCD"));
        m_keymap.insert(0x25,QString("\u0c9c\u0ccd\u0c9e"));
        m_keymap.insert(0x5e,QString("\u0ca4\u0ccd\u0cb0"));
        m_keymap.insert(0x26,QString("\u0c95\u0ccd\u0cb7"));
        m_keymap.insert(0x2a,QString("\u0cb6\u0ccd\u0cb0"));
        m_keymap.insert(0x28,QString(0x28));
        m_keymap.insert(0x29,QString(0x29));
        m_keymap.insert(0x5f,QString(0x0c83));
        m_keymap.insert(0x2b,QString(0x5E));

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
        m_keymap.insert(0x22,QString(0x0ca0));
        m_keymap.insert(0x3a,QString(0x0c9b));
        m_keymap.insert(0x3c,QString(0x0cb7));
        m_keymap.insert(0x3e,QString(0x007c));
        m_keymap.insert(0x3f,QString(0x0c8b));
        m_keymap.insert(0x41,QString(0x0c93));
        m_keymap.insert(0x43,QString(0x0ca3));
        m_keymap.insert(0x44,QString(0x0c85));
        m_keymap.insert(0x45,QString(0x0c86));
        m_keymap.insert(0x46,QString(0x0c87));
        m_keymap.insert(0x47,QString(0x0c89));
        m_keymap.insert(0x48,QString(0x0cab));
        m_keymap.insert(0x49,QString(0x0c98));
        m_keymap.insert(0x4a,QString(0x0cb1));
        m_keymap.insert(0x4b,QString(0x0c96));
        m_keymap.insert(0x4c,QString(0x0ca5));
        m_keymap.insert(0x4d,QString(0x0cb6));
        m_keymap.insert(0x4e,QString(0x0cb3));
        m_keymap.insert(0x4f,QString(0x0ca7));
        m_keymap.insert(0x50,QString(0x0c9d));
        m_keymap.insert(0x51,QString(0x0c94));
        m_keymap.insert(0x52,QString(0x0c88));
        m_keymap.insert(0x53,QString(0x0c8f));
        m_keymap.insert(0x54,QString(0x0c8a));
        m_keymap.insert(0x55,QString(0x0c99));
        m_keymap.insert(0x57,QString(0x0c90));
        m_keymap.insert(0x59,QString(0x0cad));
        m_keymap.insert(0x5a,QString(0x0c8e));
        m_keymap.insert(0x5c,QString(0x0C9E));
        m_keymap.insert(0x7b,QString(0x0ca2));
        m_keymap.insert(0x7D,QString(0x0c9e));
    }

    void addNormalKeys()
    {
        m_keymap.insert(0x27,QString(0x0c9f));
        m_keymap.insert(0x2c,QString(0x0cca));
        m_keymap.insert(0x2d,QString(0x2d));
        m_keymap.insert(0x2e,QString(0x0cc3));
        m_keymap.insert(0x2f,QString(0x0caf));
        m_keymap.insert(0x3b,QString(0x0c9a));
        m_keymap.insert(0x61,QString(0x0ccb));
        m_keymap.insert(0x62,QString(0x0cb5));
        m_keymap.insert(0x63,QString(0x0cae));
        m_keymap.insert(0x64,QString(0x0ccd));
        m_keymap.insert(0x65,QString(0x0cbe));
        m_keymap.insert(0x66,QString(0x0cbf));
        m_keymap.insert(0x67,QString(0x0cc1));
        m_keymap.insert(0x68,QString(0x0caa));
        m_keymap.insert(0x69,QString(0x0c97));
        m_keymap.insert(0x6a,QString(0x0cb0));
        m_keymap.insert(0x6b,QString(0x0c95));
        m_keymap.insert(0x6c,QString(0x0ca4));
        m_keymap.insert(0x6d,QString(0x0cb8));
        m_keymap.insert(0x6e,QString(0x0cb2));
        m_keymap.insert(0x6f,QString(0x0ca6));
        m_keymap.insert(0x70,QString(0x0c9c));
        m_keymap.insert(0x71,QString(0x0CCC));
        m_keymap.insert(0x72,QString(0x0cc0));
        m_keymap.insert(0x73,QString(0x0cc7));
        m_keymap.insert(0x74,QString(0x0cc2));
        m_keymap.insert(0x75,QString(0x0cb9));
        m_keymap.insert(0x76,QString(0x0ca8));
        m_keymap.insert(0x77,QString(0x0CC8));
        m_keymap.insert(0x78,QString(0x0c82));
        m_keymap.insert(0x79,QString(0x0cac));
        m_keymap.insert(0x7a,QString(0x0cc6));
        m_keymap.insert(0x5B,QString(0x0CA1));
        m_keymap.insert(0x7e,QString(0x7C));
        m_keymap.insert(0x20,QString(0x20));
    }

     void addAccentKeys()
     {
         m_keymap.insert(0xE1,QString(0x0ce7));
         m_keymap.insert(0xE2,QString(0x0ce8));
         m_keymap.insert(0xE3,QString(0x0ce9));
         m_keymap.insert(0xE4,QString(0x0cea));
         m_keymap.insert(0xE5,QString(0x0ceb));
         m_keymap.insert(0xE6,QString(0x0cec));
         m_keymap.insert(0xE7,QString(0x0ced));
         m_keymap.insert(0xE8,QString(0x0cee));
         m_keymap.insert(0xE9,QString(0x0cef));
         m_keymap.insert(0xEA,QString(0x0ce6));
         m_keymap.insert(0xEB,QString(0x0cc4));
         m_keymap.insert(0xED,QString(0x0cd6));
         m_keymap.insert(0xEF,QString(0x0ce1));
         m_keymap.insert(0xF01,QString(0x0cd5));
         m_keymap.insert(0xF11,QString(0x0c8c));
         m_keymap.insert(0xF2,QString(0x0cde));
         m_keymap.insert(0xF3,QString(0x0ce0));
         }

     void addAltKeysForHID()
     {
         m_keymap.insert(0xA0,QString(0x0ce7));
         m_keymap.insert(0xA1,QString(0x0ce8));
         m_keymap.insert(0xA2,QString(0x0ce9));
         m_keymap.insert(0xA3,QString(0x0cea));
         m_keymap.insert(0xA4,QString(0x0ceb));
         m_keymap.insert(0xA5,QString(0x0cec));
         m_keymap.insert(0xA6,QString(0x0ced));
         m_keymap.insert(0xA7,QString(0x0cee));
         m_keymap.insert(0xA8,QString(0x0cef));
         m_keymap.insert(0xA9,QString(0x0ce6));
         m_keymap.insert(0xAA,QString(0x0cc4));
         m_keymap.insert(0xAD,QString(0x0cd6));
         m_keymap.insert(0xAF,QString(0x0ce1));
         m_keymap.insert(0xB9,QString(0x0cd5));
         m_keymap.insert(0xBB,QString(0x0c8c));
         m_keymap.insert(0xBD,QString(0x0cde));
         m_keymap.insert(0xC1,QString(0x0ce0));
      }
};
#endif // KANNADA_AUTOMATA_H

