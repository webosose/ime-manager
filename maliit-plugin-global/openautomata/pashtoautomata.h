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

#ifndef PASHTO_AUTOMATA_H
#define PASHTO_AUTOMATA_H

#include "automatabase.h"
#include <QLocale>

class PashtoAutomata : public AutomataBase
{

public:
    PashtoAutomata()
    {
        addNumberKeys();
        addSymbolKeys();
        addNormalKeys();
        addShiftedKeys();
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
        return new PashtoAutomata();
    }

private:
    void addNumberKeys()
    {
        m_keymap.insert(0x31,QString(QChar(0x06f1)));
        m_keymap.insert(0x32,QString(QChar(0x06f2)));
        m_keymap.insert(0x33,QString(QChar(0x06f3)));
        m_keymap.insert(0x34,QString(QChar(0x06f4)));
        m_keymap.insert(0x35,QString(QChar(0x06f5)));
        m_keymap.insert(0x36,QString(QChar(0x06f6)));
        m_keymap.insert(0x37,QString(QChar(0x06f7)));
        m_keymap.insert(0x38,QString(QChar(0x06f8)));
        m_keymap.insert(0x39,QString(QChar(0x06f9)));
        m_keymap.insert(0x30,QString(QChar(0x06f0)));
    }

    void addSymbolKeys()
    {
        m_keymap.insert(0x60,QString(QChar(0x200D)));
        m_keymap.insert(0x7E,QString(QChar(0x0654)));
        m_keymap.insert(0xC3,QString(QChar(0x0060)));
        m_keymap.insert(0x2D,QString(QChar(0x002D)));
        m_keymap.insert(0x3D,QString(QChar(0x003D)));
        m_keymap.insert(0x5C,QString(QChar(0x005C)));
        m_keymap.insert(0x7C,QString(QChar(0x007C)));
        m_keymap.insert(0x2F,QString(QChar(0x002F)));
        m_keymap.insert(0x7B,QString(QChar(0x005d)));
        m_keymap.insert(0x7D,QString(QChar(0x005b)));
        m_keymap.insert(0x3A,QString(QChar(0x003A)));
        m_keymap.insert(0x21,QString(QChar(0x0021)));
        m_keymap.insert(0x40,QString(QChar(0x066c)));
        m_keymap.insert(0x23,QString(QChar(0x066b)));
        m_keymap.insert(0x24,QString(QChar(0x060b)));
        m_keymap.insert(0x25,QString(QChar(0x066a)));
        m_keymap.insert(0x5E,QString(QChar(0x00d7)));
        m_keymap.insert(0x26,QString(QChar(0x00bb)));
        m_keymap.insert(0x2A,QString(QChar(0x00ab)));
        m_keymap.insert(0x28,QString(QChar(0x0029)));
        m_keymap.insert(0x29,QString(QChar(0x0028)));
        m_keymap.insert(0x5F,QString(QChar(0x0640)));
        m_keymap.insert(0x2B,QString(QChar(0x002b)));
    }

    void addNormalKeys()
    {
        m_keymap.insert(0x71,QString(QChar(0x0636)));
        m_keymap.insert(0x77,QString(QChar(0x0635)));
        m_keymap.insert(0x65,QString(QChar(0x062b)));
        m_keymap.insert(0x72,QString(QChar(0x0642)));
        m_keymap.insert(0x74,QString(QChar(0x0641)));
        m_keymap.insert(0x79,QString(QChar(0x063a)));
        m_keymap.insert(0x75,QString(QChar(0x0639)));
        m_keymap.insert(0x69,QString(QChar(0x0647)));
        m_keymap.insert(0x6F,QString(QChar(0x062e)));
        m_keymap.insert(0x70,QString(QChar(0x062d)));
        m_keymap.insert(0x5B,QString(QChar(0x062c)));
        m_keymap.insert(0x5D,QString(QChar(0x0686)));
        m_keymap.insert(0x61,QString(QChar(0x0634)));
        m_keymap.insert(0x73,QString(QChar(0x0633)));
        m_keymap.insert(0x64,QString(QChar(0x06cc)));
        m_keymap.insert(0x66,QString(QChar(0x0628)));
        m_keymap.insert(0x67,QString(QChar(0x0644)));
        m_keymap.insert(0x68,QString(QChar(0x0627)));
        m_keymap.insert(0x6A,QString(QChar(0x062a)));
        m_keymap.insert(0x6B,QString(QChar(0x0646)));
        m_keymap.insert(0x6C,QString(QChar(0x0645)));
        m_keymap.insert(0x3B,QString(QChar(0x06a9)));
        m_keymap.insert(0x27,QString(QChar(0x06ab)));
        m_keymap.insert(0x7A,QString(QChar(0x0638)));
        m_keymap.insert(0x78,QString(QChar(0x0637)));
        m_keymap.insert(0x63,QString(QChar(0x0632)));
        m_keymap.insert(0x76,QString(QChar(0x0631)));
        m_keymap.insert(0x62,QString(QChar(0x0630)));
        m_keymap.insert(0x6E,QString(QChar(0x062f)));
        m_keymap.insert(0x6D,QString(QChar(0x0693)));
        m_keymap.insert(0x2C,QString(QChar(0x0648)));
        m_keymap.insert(0x2E,QString(QChar(0x0696)));
        m_keymap.insert(0x20,QString(QChar(0x20)));
    }

    void addShiftedKeys()
    {
        m_keymap.insert(0x51,QString(QChar(0x0652)));
        m_keymap.insert(0x57,QString(QChar(0x064c)));
        m_keymap.insert(0x45,QString(QChar(0x064d)));
        m_keymap.insert(0x52,QString(QChar(0x064b)));
        m_keymap.insert(0x54,QString(QChar(0x064f)));
        m_keymap.insert(0x59,QString(QChar(0x0650)));
        m_keymap.insert(0x55,QString(QChar(0x064e)));
        m_keymap.insert(0x49,QString(QChar(0x0651)));
        m_keymap.insert(0x4F,QString(QChar(0x0681)));
        m_keymap.insert(0x50,QString(QChar(0x0685)));
        m_keymap.insert(0x41,QString(QChar(0x069a)));
        m_keymap.insert(0x53,QString(QChar(0x06cd)));
        m_keymap.insert(0x44,QString(QChar(0x064a)));
        m_keymap.insert(0x46,QString(QChar(0x067e)));
        m_keymap.insert(0x47,QString(QChar(0x0623)));
        m_keymap.insert(0x48,QString(QChar(0x0622)));
        m_keymap.insert(0x4A,QString(QChar(0x067c)));
        m_keymap.insert(0x4B,QString(QChar(0x06bc)));
        m_keymap.insert(0x4C,QString(QChar(0x0629)));
        m_keymap.insert(0x22,QString(QChar(0x061b)));
        m_keymap.insert(0x5A,QString(QChar(0x0626)));
        m_keymap.insert(0x58,QString(QChar(0x06d0)));
        m_keymap.insert(0x43,QString(QChar(0x0698)));
        m_keymap.insert(0x56,QString(QChar(0x0621)));
        m_keymap.insert(0x42,QString(QChar(0x200C)));
        m_keymap.insert(0x4E,QString(QChar(0x0689)));
        m_keymap.insert(0x4D,QString(QChar(0x0624)));
        m_keymap.insert(0x3C,QString(QChar(0x060c)));
        m_keymap.insert(0x3E,QString(QChar(0x002e)));
        m_keymap.insert(0x3F,QString(QChar(0x061f)));
    }

    void addAltKeysForHID()
    {
        m_keymap.insert(0xA0,QString(QChar(0x007e)));
        m_keymap.insert(0xA1,QString(QChar(0x0040)));
        m_keymap.insert(0xA2,QString(QChar(0x0023)));
        m_keymap.insert(0xA3,QString(QChar(0x0024)));
        m_keymap.insert(0xA4,QString(QChar(0x0025)));
        m_keymap.insert(0xA5,QString(QChar(0x005e)));
        m_keymap.insert(0xA6,QString(QChar(0x0026)));
        m_keymap.insert(0xA7,QString(QChar(0x066d)));
        m_keymap.insert(0xA8,QString(QChar(0x2022)));
        m_keymap.insert(0xA9,QString(QChar(0x00b0)));
        m_keymap.insert(0xAA,QString(QChar(0x005f)));
        m_keymap.insert(0xAB,QString(QChar(0x00f7)));
        m_keymap.insert(0xAC,QString(QChar(0x20ac)));
        m_keymap.insert(0xAD,QString(QChar(0x0671)));
        m_keymap.insert(0xAE,QString(QChar(0x0649)));
        m_keymap.insert(0xAF,QString(QChar(0x200e)));
        m_keymap.insert(0xB0,QString(QChar(0x200f)));
        m_keymap.insert(0xB1,QString(QChar(0x0653)));
        m_keymap.insert(0xB2,QString(QChar(0x0659)));
        m_keymap.insert(0xB3,QString(QChar(0x0670)));
        m_keymap.insert(0xB4,QString(QChar(0x0027)));
        m_keymap.insert(0xB5,QString(QChar(0x0022)));
        m_keymap.insert(0xB6,QString(QChar(0x007d)));
        m_keymap.insert(0xB7,QString(QChar(0x007b)));
        m_keymap.insert(0xBA,QString(QChar(0x06d2)));
        m_keymap.insert(0xBB,QString(QChar(0x06ba)));
        m_keymap.insert(0xBC,QString(QChar(0x06b7)));
        m_keymap.insert(0xBD,QString(QChar(0x0625)));
        m_keymap.insert(0xBE,QString(QChar(0x0679)));
        m_keymap.insert(0xBF,QString(QChar(0x003e)));
        m_keymap.insert(0xC0,QString(QChar(0x003c)));
        m_keymap.insert(0xC1,QString(QChar(0x0643)));
        m_keymap.insert(0xC2,QString(QChar(0x06af)));
        m_keymap.insert(0xC5,QString(QChar(0x003f)));
        m_keymap.insert(0xC6,QString(QChar(0x003b)));
        m_keymap.insert(0xCA,QString(QChar(0x0688)));
        m_keymap.insert(0xCB,QString(QChar(0x0691)));
        m_keymap.insert(0xCC,QString(QChar(0x002c)));
        m_keymap.insert(0xCD,QString(QChar(0x06c7)));
        m_keymap.insert(0xCE,QString(QChar(0x06c9)));
    }

};

#endif // PASHTO_AUTOMATA_H
