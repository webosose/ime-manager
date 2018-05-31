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

#ifndef TAMIL_AUTOMATA_H
#define TAMIL_AUTOMATA_H

#include "automatabase.h"
#include <QLocale>

class TamilAutomata: public AutomataBase
{

public:
    TamilAutomata()
    {
        addNumberKeys();
        addNormalKeys();
        addShiftedKeys();
        addAltedKeys();
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
        return new TamilAutomata();
    }

private:
    void addNumberKeys()
    {
        m_keymap.insert(0x31,QString(0x31));
        m_keymap.insert(0x32,QString(0x32));
        m_keymap.insert(0x33,QString(0x33));
        m_keymap.insert(0x34,QString(0x34));
        m_keymap.insert(0x35,QString(0x35));
        m_keymap.insert(0x36,QString(0x36));
        m_keymap.insert(0x37,QString(0x37));
        m_keymap.insert(0x38,QString(0x38));
        m_keymap.insert(0x39,QString(0x39));
        m_keymap.insert(0x30,QString(0x30));
        m_keymap.insert(0x2D,QString(0x2D));
    }

    void addNormalKeys()
    {
        m_keymap.insert(0x71,QString(0x0BCC));
        m_keymap.insert(0x77,QString(0x0BC8));
        m_keymap.insert(0x65,QString(0x0BBE));
        m_keymap.insert(0x72,QString(0x0BC0));
        m_keymap.insert(0x74,QString(0x0BC2));
        m_keymap.insert(0x79,QString(0x0BAA));
        m_keymap.insert(0x75,QString(0x0BB9));
        m_keymap.insert(0x69,QString(0x0B95));
        m_keymap.insert(0x6F,QString(0x0BA4));
        m_keymap.insert(0x70,QString(0x0B9C));
        m_keymap.insert(0X5B,QString(0X0B9F));
        m_keymap.insert(0X61,QString(0X0BCB));
        m_keymap.insert(0x73,QString(0x0BC7));
        m_keymap.insert(0x64,QString(0x0BCD));
        m_keymap.insert(0x66,QString(0x0BBF));
        m_keymap.insert(0x67,QString(0x0BC1));
        m_keymap.insert(0x68,QString(0x0BAA));
        m_keymap.insert(0x6A,QString(0x0BB0));
        m_keymap.insert(0x6B,QString(0x0B95));
        m_keymap.insert(0x6C,QString(0x0BA4));
        m_keymap.insert(0x3B,QString(0x0B9A));
        m_keymap.insert(0x27,QString(0x0B9E));
        m_keymap.insert(0x7A,QString(0x0BC6));
        m_keymap.insert(0x63,QString(0x0BAE));
        m_keymap.insert(0x76,QString(0x0BA8));
        m_keymap.insert(0x62,QString(0x0BB5));
        m_keymap.insert(0x6E,QString(0x0BB2));
        m_keymap.insert(0x6D,QString(0x0BB8));
        m_keymap.insert(0x2C,QString(0x002C));
        m_keymap.insert(0x2E,QString(0x002E));
        m_keymap.insert(0x2F,QString(0x0BAF));
        m_keymap.insert(0x60,QString(0x0BCA));
        m_keymap.insert(0x20,QString(0x20));
    }

    void addShiftedKeys()
    {
        m_keymap.insert(0x5E,QString("\u0BA4\u0BCD\u0BB0"));
        m_keymap.insert(0x26,QString("\u0B95\u0BCD\u0BB7"));
        m_keymap.insert(0x2A,QString("\u0BB7\u0BCD\u0BB0"));
        m_keymap.insert(0x29,QString(0x0BF0));
        m_keymap.insert(0x5F,QString(0x0B83));
        m_keymap.insert(0x51,QString(0x0B94));
        m_keymap.insert(0x57,QString(0x0B90));
        m_keymap.insert(0x45,QString(0x0B86));
        m_keymap.insert(0x52,QString(0x0B88));
        m_keymap.insert(0x54,QString(0x0B8A));
        m_keymap.insert(0x59,QString(0x0BAA));
        m_keymap.insert(0x55,QString(0x0B99));
        m_keymap.insert(0x49,QString(0x0B95));
        m_keymap.insert(0x4F,QString(0x0BA4));
        m_keymap.insert(0x50,QString(0x0B9A));
        m_keymap.insert(0x7B,QString(0x0B9F));
        m_keymap.insert(0x41,QString(0x0B93));
        m_keymap.insert(0x53,QString(0x0B8F));
        m_keymap.insert(0x44,QString(0x0B85));
        m_keymap.insert(0x46,QString(0x0B87));
        m_keymap.insert(0x47,QString(0x0B89));
        m_keymap.insert(0x48,QString(0x0BAA));
        m_keymap.insert(0x4A,QString(0x0BB1));
        m_keymap.insert(0x4B,QString(0x0B95));
        m_keymap.insert(0x4C,QString(0x0BA4));
        m_keymap.insert(0x3A,QString(0x0B9A));
        m_keymap.insert(0x22,QString(0x0B9E));
        m_keymap.insert(0x5A,QString(0x0B8E));
        m_keymap.insert(0x58,QString(0x0BD0));
        m_keymap.insert(0x43,QString(0x0BA3));
        m_keymap.insert(0x56,QString(0x0BA9));
        m_keymap.insert(0x42,QString(0x0BB4));
        m_keymap.insert(0x4E,QString(0x0BB3));
        m_keymap.insert(0x4D,QString(0x0BB6));
        m_keymap.insert(0x3C,QString(0x0BB7));
        m_keymap.insert(0x3E,QString("\u0BB6\u0BCD\u0BB0\u0BC0"));
        m_keymap.insert(0x3F,QString(0x0BAF));
        m_keymap.insert(0x7E,QString(0x0B92));
    }

    void addAltedKeys()
    {
        m_keymap.insert(0xA0,QString(0x0BE7));
        m_keymap.insert(0xA1,QString(0x0BE8));
        m_keymap.insert(0xA2,QString(0x0BE9));
        m_keymap.insert(0xA3,QString(0x0BEA));
        m_keymap.insert(0xA4,QString(0x0BEB));
        m_keymap.insert(0xA5,QString(0x0BEC));
        m_keymap.insert(0xA6,QString(0x0BED));
        m_keymap.insert(0xA7,QString(0x0BEE));
        m_keymap.insert(0xA8,QString(0x0BEF));
        m_keymap.insert(0xA9,QString(0x0BF0));
        m_keymap.insert(0xAA,QString(0x0BF1));
        m_keymap.insert(0xAB,QString(0x0BF2));
        //Extra Expanded Keys
        m_keymap.insert(0xAC,QString(0x0BF9));
        m_keymap.insert(0xAD,QString(0x0BFA));
        m_keymap.insert(0xAE,QString(0x0BF4));
        m_keymap.insert(0xAF,QString(0x0BF3));
        m_keymap.insert(0xB0,QString(0x0BF5));
        m_keymap.insert(0xB1,QString(0x0BF8));
        m_keymap.insert(0xB2,QString(0x0BF7));
        m_keymap.insert(0xB3,QString(0x0BF6));
        m_keymap.insert(0xB4,QString(0x20B9));
    }
};

#endif // TAMIL_AUTOMATA_H

