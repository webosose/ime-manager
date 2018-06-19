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

#ifndef THAI_AUTOMATA_H
#define THAI_AUTOMATA_H

#include "automatabase.h"
#include <QLocale>

class ThaiAutomata : public AutomataBase
{

public:
    ThaiAutomata()
    {
        m_keymap.clear();
        m_keymap.insert(0x31,QString(0xE45));
        m_keymap.insert(0x32,QString(0x2F));
        m_keymap.insert(0x33,QString(0x2D));
        m_keymap.insert(0x34,QString(0xE20));
        m_keymap.insert(0x35,QString(0xE16));
        m_keymap.insert(0x36,QString(0xE38));
        m_keymap.insert(0x37,QString(0xE36));
        m_keymap.insert(0x38,QString(0xE04));
        m_keymap.insert(0x39,QString(0xE15));
        m_keymap.insert(0x30,QString(0xE08));
        m_keymap.insert(0x2D,QString(0xE02));
        m_keymap.insert(0x3D,QString(0xE0A));
        m_keymap.insert(0x71,QString(0xE46));
        m_keymap.insert(0x77,QString(0xE44));
        m_keymap.insert(0x65,QString(0xE33));
        m_keymap.insert(0x72,QString(0xE1E));
        m_keymap.insert(0x74,QString(0xE30));
        m_keymap.insert(0x79,QString(0xE31));
        m_keymap.insert(0x75,QString(0xE35));
        m_keymap.insert(0x69,QString(0xE23));
        m_keymap.insert(0x6F,QString(0xE19));
        m_keymap.insert(0x70,QString(0xE22));
        m_keymap.insert(0x5B,QString(0xE1A));
        m_keymap.insert(0x5D,QString(0xE25));
        m_keymap.insert(0x5C,QString(0xE03));
        m_keymap.insert(0X61,QString(0xE1F));
        m_keymap.insert(0x73,QString(0xE2B));
        m_keymap.insert(0x64,QString(0xE01));
        m_keymap.insert(0x66,QString(0xE14));
        m_keymap.insert(0x67,QString(0xE40));
        m_keymap.insert(0x68,QString(0xE49));
        m_keymap.insert(0x6A,QString(0xE48));
        m_keymap.insert(0x6B,QString(0xE32));
        m_keymap.insert(0x6C,QString(0xE2A));
        m_keymap.insert(0x3B,QString(0xE27));
        m_keymap.insert(0x27,QString(0xE07));
        m_keymap.insert(0x4D,QString(0x03F));
        m_keymap.insert(0x401,QString(0x040));
        m_keymap.insert(0x7A,QString(0xE1C));
        m_keymap.insert(0x78,QString(0xE1B));
        m_keymap.insert(0x63,QString(0xE41));
        m_keymap.insert(0x76,QString(0xE2D));
        m_keymap.insert(0x62,QString(0xE34));
        m_keymap.insert(0x6E,QString(0xE37));
        m_keymap.insert(0x6D,QString(0xE17));
        m_keymap.insert(0x2C,QString(0xE21));
        m_keymap.insert(0x2E,QString(0xE43));
        m_keymap.insert(0x2F,QString(0xE1D));
        m_keymap.insert(0x7D,QString(0x02C));
        m_keymap.insert(0x22,QString(0x02E));
        m_keymap.insert(0x82,QString(0x30));
        m_keymap.insert(0x85,QString(0x31));
        m_keymap.insert(0x80,QString(0x32));
        m_keymap.insert(0x81,QString(0x33));
        m_keymap.insert(0x86,QString(0x34));
        m_keymap.insert(0x87,QString(0x35));
        m_keymap.insert(0x88,QString(0x36));
        m_keymap.insert(0x89,QString(0x37));
        m_keymap.insert(0x90,QString(0x38));
        m_keymap.insert(0x91,QString(0x39));
        m_keymap.insert(0x5E,QString(0xE39));
        m_keymap.insert(0x26,QString(0xE3F));
        m_keymap.insert(0x57,QString(0x22));
        m_keymap.insert(0x45,QString(0xE0E));
        m_keymap.insert(0x52,QString(0xE11));
        m_keymap.insert(0x54,QString(0xE18));
        m_keymap.insert(0x59,QString(0xE4D));
        m_keymap.insert(0x55,QString(0xE4A));
        m_keymap.insert(0x49,QString(0xE13));
        m_keymap.insert(0x4F,QString(0xE2F));
        m_keymap.insert(0x50,QString(0xE0D));
        m_keymap.insert(0x7B,QString(0xE10));
        m_keymap.insert(0x7C,QString(0xE05));
        m_keymap.insert(0x41,QString(0xE24));
        m_keymap.insert(0x53,QString(0xE06));
        m_keymap.insert(0x44,QString(0xE0F));
        m_keymap.insert(0x46,QString(0xE42));
        m_keymap.insert(0x47,QString(0xE0C));
        m_keymap.insert(0x48,QString(0xE47));
        m_keymap.insert(0x4A,QString(0xE4B));
        m_keymap.insert(0x4B,QString(0xE29));
        m_keymap.insert(0x4C,QString(0xE28));
        m_keymap.insert(0x3A,QString(0xE0B));
        m_keymap.insert(0x5A,QString(0x28));
        m_keymap.insert(0x58,QString(0x29));
        m_keymap.insert(0x43,QString(0xE09));
        m_keymap.insert(0x56,QString(0xE2E));
        m_keymap.insert(0x42,QString(0xE3A));
        m_keymap.insert(0x4E,QString(0xE4C));
        m_keymap.insert(0x3C,QString(0xE12));
        m_keymap.insert(0x3E,QString(0xE2C));
        m_keymap.insert(0x3F,QString(0xE26));
        m_keymap.insert(0x7E,QString(0x25));
        m_keymap.insert(0x21,QString(0x2B));
        m_keymap.insert(0x40,QString(0xE51));
        m_keymap.insert(0x23,QString(0xE52));
        m_keymap.insert(0x24,QString(0xE53));
        m_keymap.insert(0x25,QString(0xE54));
        m_keymap.insert(0x5E,QString(0xE39));
        m_keymap.insert(0x2A,QString(0xE55));
        m_keymap.insert(0x28,QString(0xE56));
        m_keymap.insert(0x29,QString(0xE57));
        m_keymap.insert(0x5F,QString(0xE58));
        m_keymap.insert(0x2B,QString(0xE59));
        m_keymap.insert(0x51,QString(0xE50));
        m_keymap.insert(0x20,QString(0x20));
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
        return new ThaiAutomata();
    }
};

#endif // THAI_AUTOMATA_H
