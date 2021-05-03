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

#ifndef SRILANKAN_AUTOMATA_H
#define SRILANKAN_AUTOMATA_H

#include "automatabase.h"
#include <QLocale>

class SrilankanAutomata: public AutomataBase
{

public:
    SrilankanAutomata() {
        m_accentSelect = false;

        addNumberKeys();
        addNormalKeys();
        addShiftedKeys();
        addSymbolKeys();
        addAccentKeys();
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
        return new SrilankanAutomata();
    }

private:
    void addSymbolKeys()
    {
        m_keymap.insert(0x60,QString("\u0DCA\u200D\u0DBB"));
        m_keymap.insert(0x7e,QString("\u0DBB\u0DCA\u200D"));
        m_keymap.insert(0x21,QString(QChar(0x0021)));
        m_keymap.insert(0x40,QString(QChar(0x0040)));
        m_keymap.insert(0x23,QString(QChar(0x0023)));
        m_keymap.insert(0x24,QString(QChar(0x0024)));
        m_keymap.insert(0x25,QString(QChar(0x0025)));
        m_keymap.insert(0x5e,QString(QChar(0x005E)));
        m_keymap.insert(0x26,QString(QChar(0x0026)));
        m_keymap.insert(0x2a,QString(QChar(0x002A)));
        m_keymap.insert(0x28,QString(QChar(0x0028)));
        m_keymap.insert(0x29,QString(QChar(0x0029)));
        m_keymap.insert(0x5f,QString(QChar(0x005F)));
        m_keymap.insert(0x2b,QString(QChar(0x002B)));
        m_keymap.insert(0x2d,QString(QChar(0x002D)));
        m_keymap.insert(0x3d,QString(QChar(0x003D)));
        m_keymap.insert(0x27,QString(QChar(0x002E)));
        m_keymap.insert(0x3b,QString(QChar(0x0DAD)));
        m_keymap.insert(0x3a,QString(QChar(0x0DAE)));
        m_keymap.insert(0x2c,QString(QChar(0x0DBD)));
        m_keymap.insert(0x22,QString(QChar(0x002C)));
        m_keymap.insert(0x5b,QString(QChar(0x0DA4)));
        m_keymap.insert(0x5c,QString(QChar(0x005C)));
        m_keymap.insert(0x5d,QString(QChar(0x003B)));
        m_keymap.insert(0x7b,QString(QChar(0x0DA5)));
        m_keymap.insert(0x7c,QString(QChar(0x007C)));
        m_keymap.insert(0x7d,QString(QChar(0x003A)));
        m_keymap.insert(0x2e,QString(QChar(0x0D9C)));
        m_keymap.insert(0x2f,QString(QChar(0x002F)));
        m_keymap.insert(0x3c,QString(QChar(0x0DC5)));
        m_keymap.insert(0x3e,QString(QChar(0x0D9D)));
        m_keymap.insert(0x3f,QString(QChar(0x003F)));
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

    void addShiftedKeys()
    {
        m_keymap.insert(0x41,QString(QChar(0x0DDF)));
        m_keymap.insert(0x42,QString(QChar(0x0D8A)));
        m_keymap.insert(0x43,QString(QChar(0x0DA3)));
        m_keymap.insert(0x44,QString(QChar(0x0DD8)));
        m_keymap.insert(0x45,QString(QChar(0x0DD1)));
        m_keymap.insert(0x46,QString(QChar(0x0DC6)));
        m_keymap.insert(0x47,QString(QChar(0x0DA8)));
        m_keymap.insert(0x48,QString("\u0DCA\u200D\u0DBA"));
        m_keymap.insert(0x49,QString(QChar(0x0DC2)));
        m_keymap.insert(0x4a,QString("\u0DC5\u0DD4"));
        m_keymap.insert(0x4b,QString(QChar(0x0DAB)));
        m_keymap.insert(0x4c,QString(QChar(0x0D9B)));
        m_keymap.insert(0x4d,QString(QChar(0x0DB5)));
        m_keymap.insert(0x4e,QString(QChar(0x0DB7)));
        m_keymap.insert(0x4f,QString(QChar(0x0DB0)));
        m_keymap.insert(0x50,QString(QChar(0x0DA1)));
        m_keymap.insert(0x51,QString(QChar(0x0DD6)));
        m_keymap.insert(0x52,QString(QChar(0x0D8D)));
        m_keymap.insert(0x53,QString(QChar(0x0DD3)));
        m_keymap.insert(0x54,QString(QChar(0x0D94)));
        m_keymap.insert(0x55,QString(QChar(0x0DB9)));
        m_keymap.insert(0x56,QString(QChar(0x0DAA)));
        m_keymap.insert(0x57,QString(QChar(0x0D8B)));
        m_keymap.insert(0x58,QString(QChar(0x0D83)));
        m_keymap.insert(0x59,QString(QChar(0x0DC1)));
        m_keymap.insert(0x5a,QString(QChar(0x0022)));
    }

    void addNormalKeys()
    {
        m_keymap.insert(0x61,QString(QChar(0x0DCA)));
        m_keymap.insert(0x62,QString(QChar(0x0D89)));
        m_keymap.insert(0x63,QString(QChar(0x0DA2)));
        m_keymap.insert(0x64,QString(QChar(0x0DCF)));
        m_keymap.insert(0x65,QString(QChar(0x0DD0)));
        m_keymap.insert(0x66,QString(QChar(0x0DD9)));
        m_keymap.insert(0x67,QString(QChar(0x0DA7)));
        m_keymap.insert(0x68,QString(QChar(0x0DBA)));
        m_keymap.insert(0x69,QString(QChar(0x0DC3)));
        m_keymap.insert(0x6a,QString(QChar(0x0DC0)));
        m_keymap.insert(0x6b,QString(QChar(0x0DB1)));
        m_keymap.insert(0x6c,QString(QChar(0x0D9A)));
        m_keymap.insert(0x6d,QString(QChar(0x0DB4)));
        m_keymap.insert(0x6e,QString(QChar(0x0DB6)));
        m_keymap.insert(0x6f,QString(QChar(0x0DAF)));
        m_keymap.insert(0x70,QString(QChar(0x0DA0)));
        m_keymap.insert(0x71,QString(QChar(0x0DD4)));
        m_keymap.insert(0x72,QString(QChar(0x0DBB)));
        m_keymap.insert(0x73,QString(QChar(0x0DD2)));
        m_keymap.insert(0x74,QString(QChar(0x0D92)));
        m_keymap.insert(0x75,QString(QChar(0x0DB8)));
        m_keymap.insert(0x76,QString(QChar(0x0DA9)));
        m_keymap.insert(0x77,QString(QChar(0x0D85)));
        m_keymap.insert(0x78,QString(QChar(0x0D82)));
        m_keymap.insert(0x79,QString(QChar(0x0DC4)));
        m_keymap.insert(0x7a,QString(QChar(0x0027)));
        m_keymap.insert(0x20,QString(QChar(0x0020)));
    }

    void addAccentKeys()
    {
        m_keymap.insert(0xAC,QString(QChar(0x0DDE)));
        m_keymap.insert(0xAD,QString(QChar(0x0DDC)));
        m_keymap.insert(0xAE,QString(QChar(0x0DDB)));
        m_keymap.insert(0xAF,QString(QChar(0x0DDA)));
        m_keymap.insert(0xB0,QString(QChar(0x0D91)));
        m_keymap.insert(0xB1,QString(QChar(0x0D8E)));
        m_keymap.insert(0xB4,QString(QChar(0x0DB3)));
        m_keymap.insert(0xB8,QString(QChar(0x0DF3)));
        m_keymap.insert(0xB9,QString(QChar(0x0DDD)));
        m_keymap.insert(0xBA,QString(QChar(0x0DF2)));
        m_keymap.insert(0xBB,QString(QChar(0x0D86)));
        m_keymap.insert(0xBC,QString(QChar(0x0D87)));
        m_keymap.insert(0xBD,QString(QChar(0x0D88)));
        m_keymap.insert(0xBF,QString(QChar(0x0D93)));
        m_keymap.insert(0xC0,QString(QChar(0x0D95)));
        m_keymap.insert(0xC1,QString(QChar(0x0D96)));
        m_keymap.insert(0xC2,QString(QChar(0x0DF4)));
        m_keymap.insert(0xC5,QString(QChar(0x0D8C)));
        m_keymap.insert(0xC6,QString(QChar(0x0D9E)));
        m_keymap.insert(0xC7,QString(QChar(0x0DA6)));
        m_keymap.insert(0xC8,QString(QChar(0x0DAC)));
        m_keymap.insert(0xC9,QString(QChar(0x0D90)));
        m_keymap.insert(0xCC,QString(QChar(0x0D8F)));
        m_keymap.insert(0xCD,QString(QChar(0x0D9F)));
    }
};
#endif //SRILANKAN_AUTOMATA_H

