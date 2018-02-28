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

#ifndef BENGALI_AUTOMATA_H
#define BENGALI_AUTOMATA_H

#include "automatabase.h"
#include <QLocale>

class BengaliAutomata : public AutomataBase
{

public:
    BengaliAutomata()
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
        m_surroundingText = preeditString;
    }

    bool isPredictionSupported()
    {
        return false;
    }

    static AutomataBase* create()
    {
        return new BengaliAutomata();
    }
private:
    void addSymbolKeys()
    {
        m_keymap.insert(0x21,QString("\u0985\u09CD\u09AF\u09Be"));
        m_keymap.insert(0x23,QString("\u09CD\u09B0"));
        m_keymap.insert(0x24,QString("\u09B0\u09CD"));
        m_keymap.insert(0x25,QString("\u099C\u09CD\u09B0"));
        m_keymap.insert(0x5e,QString("\u09A4\u09CD\u09B7"));
        m_keymap.insert(0x26,QString("\u0995\u09CD\u09B0"));
        m_keymap.insert(0x2a,QString("\u09B6\u09CD\u09B0"));
        m_keymap.insert(0x28,QString(0x28));
        m_keymap.insert(0x29,QString(0x29));
        m_keymap.insert(0x5f,QString(0x0983));
        m_keymap.insert(0x2b,QString(0x098B));
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
        m_keymap.insert(0x51,QString(0x0994));
        m_keymap.insert(0x57,QString(0x0990));
        m_keymap.insert(0x45,QString(0x0986));
        m_keymap.insert(0x52,QString(0x0988));
        m_keymap.insert(0x54,QString(0x098A));
        m_keymap.insert(0x59,QString(0x09AD));
        m_keymap.insert(0x55,QString(0x0999));
        m_keymap.insert(0x49,QString(0x0998));
        m_keymap.insert(0x4F,QString(0x09A7));
        m_keymap.insert(0x50,QString(0x099D));
        m_keymap.insert(0x7B,QString(0x09A2));
        m_keymap.insert(0x7D,QString(0x099E));
        m_keymap.insert(0x41,QString(0x0993));
        m_keymap.insert(0x53,QString(0x098F));
        m_keymap.insert(0x44,QString(0x0985));
        m_keymap.insert(0x46,QString(0x0987));
        m_keymap.insert(0x47,QString(0x0989));
        m_keymap.insert(0x48,QString(0x09AB));
        m_keymap.insert(0x4b,QString(0x0996));
        m_keymap.insert(0x4c,QString(0x09A5));
        m_keymap.insert(0x3a,QString(0x099B));
        m_keymap.insert(0x22,QString(0x09A0));
        m_keymap.insert(0x58,QString(0x0981));
        m_keymap.insert(0x43,QString(0x09A3));
        m_keymap.insert(0x4d,QString(0x09B6));
        m_keymap.insert(0x3C,QString(0x09B7));
        m_keymap.insert(0x3E,QString(0x007B));
        m_keymap.insert(0x3f,QString(0x09DF));
    }

    void addNormalKeys()
    {
        m_keymap.insert(0x2d,QString(0x2d));
        m_keymap.insert(0x3D,QString(0x09C3));
        m_keymap.insert(0x71,QString(0x09CC));
        m_keymap.insert(0x77,QString(0x09C8));
        m_keymap.insert(0x65,QString(0x09BE));
        m_keymap.insert(0x72,QString(0x09C0));
        m_keymap.insert(0x74,QString(0x09C2));
        m_keymap.insert(0x79,QString(0x09AC));
        m_keymap.insert(0x75,QString(0x09B9));
        m_keymap.insert(0x69,QString(0x0997));
        m_keymap.insert(0x6f,QString(0x09A6));
        m_keymap.insert(0x70,QString(0x0099C));
        m_keymap.insert(0x5B,QString(0x09A1));
        m_keymap.insert(0x5D,QString(0x009BC));
        m_keymap.insert(0x61,QString(0x09CB));
        m_keymap.insert(0x73,QString(0x09C7));
        m_keymap.insert(0x64,QString(0x09CD));
        m_keymap.insert(0x66,QString(0x09BF));
        m_keymap.insert(0x67,QString(0x09C1));
        m_keymap.insert(0x68,QString(0x09AA));
        m_keymap.insert(0x6A,QString(0x09B0));
        m_keymap.insert(0x6B,QString(0x0995));
        m_keymap.insert(0x6C,QString(0x09A4));
        m_keymap.insert(0x3B,QString(0x099A));
        m_keymap.insert(0x27,QString(0x099F));
        m_keymap.insert(0x78,QString(0x0982));
        m_keymap.insert(0x63,QString(0x09AE));
        m_keymap.insert(0x76,QString(0x09A8));
        m_keymap.insert(0x62,QString(0x09AC));
        m_keymap.insert(0x6E,QString(0x09B2));
        m_keymap.insert(0x6D,QString(0x09B8));
        m_keymap.insert(0x2C,QString(0x2C));
        m_keymap.insert(0x2E,QString(0x2E));
        m_keymap.insert(0x2F,QString(0x09AF));
        m_keymap.insert(0x20,QString(0x20));
    }

     void addAltedKeys()
     {
         m_keymap.insert(0xA0,QString(0x09E7));
         m_keymap.insert(0xA1,QString(0x09e8));
         m_keymap.insert(0xA2,QString(0x09e9));
         m_keymap.insert(0xA3,QString(0x09ea));
         m_keymap.insert(0xA4,QString(0x09eb));
         m_keymap.insert(0xA5,QString(0x09ec));
         m_keymap.insert(0xA6,QString(0x09ed));
         m_keymap.insert(0xA7,QString(0x09ee));
         m_keymap.insert(0xA8,QString(0x09ef));
         m_keymap.insert(0xA9,QString(0x09E6));
         m_keymap.insert(0xAB,QString(0x09E2));
         m_keymap.insert(0xAC,QString(0x09D7));
         m_keymap.insert(0xAF,QString(0x09E3));
         m_keymap.insert(0xB3,QString(0x09CE));
         m_keymap.insert(0xB6,QString(0x09DC));
         m_keymap.insert(0xB8,QString(0x09F4));
         m_keymap.insert(0xB9,QString(0x09F6));
         m_keymap.insert(0xBA,QString(0x09F8));
         m_keymap.insert(0xBB,QString(0x09E2));
         m_keymap.insert(0xBE,QString(0x09F0));
         m_keymap.insert(0xC6,QString(0x09FA));
     }

     void addAltShiftedKeys()
     {
         m_keymap.insert(0xE5,QString(0x09E0));
         m_keymap.insert(0xE9,QString(0x09E1));
         m_keymap.insert(0xF0,QString(0x09DD));
         m_keymap.insert(0xF2,QString(0x09F5));
         m_keymap.insert(0xF3,QString(0x09F7));
         m_keymap.insert(0xF4,QString(0x09F9));
         m_keymap.insert(0xF5,QString(0x098C));
         m_keymap.insert(0xF8,QString(0x09F1));
     }
};
#endif // BENGALI_AUTOMATA_H

