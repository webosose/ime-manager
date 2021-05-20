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

#ifndef PUNJABI_AUTOMATA_H
#define PUNJABI_AUTOMATA_H

#include "automatabase.h"
#include <QLocale>

class PunjabiAutomata: public AutomataBase
{

public:
    PunjabiAutomata()
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
        return false;
    }

    static AutomataBase* create()
    {
        return new PunjabiAutomata();
    }

private:
    void addNumberKeys()
    {
        m_keymap.insert(0x31,QString(QChar(0x31)));
        m_keymap.insert(0x32,QString(QChar(0x32)));
        m_keymap.insert(0x33,QString(QChar(0x33)));
        m_keymap.insert(0x34,QString(QChar(0x34)));
        m_keymap.insert(0x35,QString(QChar(0x35)));
        m_keymap.insert(0x36,QString(QChar(0x36)));
        m_keymap.insert(0x37,QString(QChar(0x37)));
        m_keymap.insert(0x38,QString(QChar(0x38)));
        m_keymap.insert(0x39,QString(QChar(0x39)));
        m_keymap.insert(0x30,QString(QChar(0x30)));
        m_keymap.insert(0x2D,QString(QChar(0x002D)));
    }

    void addNormalKeys()
    {
        m_keymap.insert(0x71,QString(QChar(0x0A4C)));
        m_keymap.insert(0x77,QString(QChar(0x0A48)));
        m_keymap.insert(0x65,QString(QChar(0x0A3E)));
        m_keymap.insert(0x72,QString(QChar(0x0A40)));
        m_keymap.insert(0x74,QString(QChar(0x0A42)));
        m_keymap.insert(0x79,QString(QChar(0x0A2C)));
        m_keymap.insert(0x75,QString(QChar(0x0A39)));
        m_keymap.insert(0x69,QString(QChar(0x0A17)));
        m_keymap.insert(0x6F,QString(QChar(0x0A26)));
        m_keymap.insert(0x70,QString(QChar(0x0A1C)));
        m_keymap.insert(0X5B,QString(QChar(0X0A21)));
        m_keymap.insert(0X5D,QString(QChar(0X0A3C)));
        m_keymap.insert(0X61,QString(QChar(0X0A4B)));
        m_keymap.insert(0x73,QString(QChar(0x0A47)));
        m_keymap.insert(0x64,QString(QChar(0x0A4D)));
        m_keymap.insert(0x66,QString(QChar(0x0A3F)));
        m_keymap.insert(0x67,QString(QChar(0x0A41)));
        m_keymap.insert(0x68,QString(QChar(0x0A2A)));
        m_keymap.insert(0x6A,QString(QChar(0x0A30)));
        m_keymap.insert(0x6B,QString(QChar(0x0A15)));
        m_keymap.insert(0x6C,QString(QChar(0x0A24)));
        m_keymap.insert(0x3B,QString(QChar(0x0A1A)));
        m_keymap.insert(0x27,QString(QChar(0x0A1F)));
        m_keymap.insert(0x78,QString(QChar(0x0A70)));
        m_keymap.insert(0x63,QString(QChar(0x0A2E)));
        m_keymap.insert(0x76,QString(QChar(0x0A28)));
        m_keymap.insert(0x62,QString(QChar(0x0A35)));
        m_keymap.insert(0x6E,QString(QChar(0x0A32)));
        m_keymap.insert(0x6D,QString(QChar(0x0A38)));
        m_keymap.insert(0x2C,QString(QChar(0x002C)));
        m_keymap.insert(0x2E,QString(QChar(0x002E)));
        m_keymap.insert(0x2F,QString(QChar(0x0A2F)));
        m_keymap.insert(0x20,QString(QChar(0x20)));
    }

    void addShiftedKeys()
    {
        m_keymap.insert(0x21,QString("\u0A4D\u0A35"));
        m_keymap.insert(0x40,QString("\u0A4D\u0A2F"));
        m_keymap.insert(0x23,QString("\u0A4D\u0A30"));
        m_keymap.insert(0x24,QString(QChar(0x0A71)));
        m_keymap.insert(0x28,QString(QChar(0x0028)));
        m_keymap.insert(0x29,QString(QChar(0x0029)));
        m_keymap.insert(0x51,QString(QChar(0x0A14)));
        m_keymap.insert(0x57,QString(QChar(0x0A10)));
        m_keymap.insert(0x45,QString(QChar(0x0A06)));
        m_keymap.insert(0x52,QString(QChar(0x0A08)));
        m_keymap.insert(0x54,QString(QChar(0x0A0A)));
        m_keymap.insert(0x59,QString(QChar(0x0A2D)));
        m_keymap.insert(0x55,QString(QChar(0x0A19)));
        m_keymap.insert(0x49,QString(QChar(0x0A18)));
        m_keymap.insert(0x4F,QString(QChar(0x0A27)));
        m_keymap.insert(0x50,QString(QChar(0x0A1D)));
        m_keymap.insert(0x7B,QString(QChar(0x0A22)));
        m_keymap.insert(0x7D,QString(QChar(0x0A1E)));
        m_keymap.insert(0x41,QString(QChar(0x0A13)));
        m_keymap.insert(0x53,QString(QChar(0x0A0F)));
        m_keymap.insert(0x44,QString(QChar(0x0A05)));
        m_keymap.insert(0x46,QString(QChar(0x0A07)));
        m_keymap.insert(0x47,QString(QChar(0x0A09)));
        m_keymap.insert(0x48,QString(QChar(0x0A2B)));
        m_keymap.insert(0x4A,QString(QChar(0x0A5C)));
        m_keymap.insert(0x4B,QString(QChar(0x0A16)));
        m_keymap.insert(0x4C,QString(QChar(0x0A25)));
        m_keymap.insert(0x3A,QString(QChar(0x0A1B)));
        m_keymap.insert(0x22,QString(QChar(0x0A20)));
        m_keymap.insert(0x7E,QString("\u0A4D\u0A39"));
        m_keymap.insert(0x58,QString(QChar(0x0A02)));
        m_keymap.insert(0x43,QString(QChar(0x0A23)));
        m_keymap.insert(0x42,QString(QChar(0x0A72)));
        m_keymap.insert(0x4E,QString(QChar(0x0A33)));
        m_keymap.insert(0x4D,QString(QChar(0x0A36)));
        m_keymap.insert(0x3E,QString(QChar(0x0964)));
    }

    void addAltedKeys()
    {
        m_keymap.insert(0xA0,QString(QChar(0x0A67)));
        m_keymap.insert(0xA1,QString(QChar(0x0A68)));
        m_keymap.insert(0xA2,QString(QChar(0x0A69)));
        m_keymap.insert(0xA3,QString(QChar(0x0A6A)));
        m_keymap.insert(0xA4,QString(QChar(0x0A6B)));
        m_keymap.insert(0xA5,QString(QChar(0x0A6C)));
        m_keymap.insert(0xA6,QString(QChar(0x0A6D)));
        m_keymap.insert(0xA7,QString(QChar(0x0A6E)));
        m_keymap.insert(0xA8,QString(QChar(0x0A6F)));
        m_keymap.insert(0xA9,QString(QChar(0x0A66)));
        m_keymap.insert(0xAF,QString(QChar(0x20B9)));
        m_keymap.insert(0xB3,QString(QChar(0x0A5A)));
        m_keymap.insert(0xB5,QString(QChar(0x0A5B)));
        m_keymap.insert(0xB6,QString(QChar(0x0A5C)));
        m_keymap.insert(0xBB,QString(QChar(0x0A72)));
        m_keymap.insert(0xBC,QString(QChar(0x0A73)));
        m_keymap.insert(0xBD,QString(QChar(0x0A5E)));
        m_keymap.insert(0xBF,QString(QChar(0x0A59)));
        m_keymap.insert(0xC6,QString(QChar(0x0A74)));
        m_keymap.insert(0xC9,QString(QChar(0x0A73)));
        m_keymap.insert(0xCD,QString(QChar(0x0965)));
    }
};

#endif // PUNJABI_AUTOMATA_H

