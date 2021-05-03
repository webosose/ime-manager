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

#ifndef ORIYA_AUTOMATA_H
#define ORIYA_AUTOMATA_H

#include "automatabase.h"
#include <QLocale>

class OriyaAutomata : public AutomataBase
{

public:
    OriyaAutomata()
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
        return new OriyaAutomata();
    }
private:
    void addSymbolKeys()
    {
        m_keymap.insert(0x23,QString("\u0B4D\u0B30"));
        m_keymap.insert(0x24,QString("\u0B30\u0B4D"));
        m_keymap.insert(0x25,QString("\u0B1C\u0B4D\u0B1E"));
        m_keymap.insert(0x5e,QString("\u0B24\u0B4D\u0B30"));
        m_keymap.insert(0x26,QString("\u0B15\u0B4D\u0B37"));
        m_keymap.insert(0x2a,QString("\u0B36\u0B4D\u0B30"));
        m_keymap.insert(0x28,QString(QChar(0x28)));
        m_keymap.insert(0x29,QString(QChar(0x29)));
        m_keymap.insert(0x5f,QString(QChar(0x0B03)));
        m_keymap.insert(0x2b,QString(QChar(0x0B0B)));
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
        m_keymap.insert(0x51,QString(QChar(0x0B14)));
        m_keymap.insert(0x57,QString(QChar(0x0B10)));
        m_keymap.insert(0x45,QString(QChar(0x0B06)));
        m_keymap.insert(0x52,QString(QChar(0x0B08)));
        m_keymap.insert(0x54,QString(QChar(0x0B0A)));
        m_keymap.insert(0x59,QString(QChar(0x0B2D)));
        m_keymap.insert(0x55,QString(QChar(0x0B19)));
        m_keymap.insert(0x49,QString(QChar(0x0B18)));
        m_keymap.insert(0x4F,QString(QChar(0x0B27)));
        m_keymap.insert(0x50,QString(QChar(0x0B1D)));
        m_keymap.insert(0x7B,QString(QChar(0x0B22)));
        m_keymap.insert(0x7D,QString(QChar(0x0B1E)));
        m_keymap.insert(0x41,QString(QChar(0x0B13)));
        m_keymap.insert(0x53,QString(QChar(0x0B0F)));
        m_keymap.insert(0x44,QString(QChar(0x0B05)));
        m_keymap.insert(0x46,QString(QChar(0x0B07)));
        m_keymap.insert(0x47,QString(QChar(0x0B09)));
        m_keymap.insert(0x48,QString(QChar(0x0B2B)));
        m_keymap.insert(0x4B,QString(QChar(0x0B16)));
        m_keymap.insert(0x4C,QString(QChar(0x0B25)));
        m_keymap.insert(0x3A,QString(QChar(0x0B1B)));
        m_keymap.insert(0x22,QString(QChar(0x0B20)));
        m_keymap.insert(0x5A,QString(QChar(0x0B71)));
        m_keymap.insert(0x58,QString(QChar(0x0B01)));
        m_keymap.insert(0x43,QString(QChar(0x0B23)));
        m_keymap.insert(0x4E,QString(QChar(0x0B33)));
        m_keymap.insert(0x4D,QString(QChar(0x0B36)));
        m_keymap.insert(0x3C,QString(QChar(0x0B37)));
        m_keymap.insert(0x3E,QString(QChar(0x0964)));
        m_keymap.insert(0x3F,QString(QChar(0x0B2F)));
    }

    void addNormalKeys()
    {
        m_keymap.insert(0x2d,QString(QChar(0x2d)));
        m_keymap.insert(0x3D,QString(QChar(0x0B43)));
        m_keymap.insert(0x71,QString(QChar(0x0B4C)));
        m_keymap.insert(0x77,QString(QChar(0x0B48)));
        m_keymap.insert(0x65,QString(QChar(0x0B3E)));
        m_keymap.insert(0x72,QString(QChar(0x0B40)));
        m_keymap.insert(0x74,QString(QChar(0x0B42)));
        m_keymap.insert(0x79,QString(QChar(0x0B2C)));
        m_keymap.insert(0x75,QString(QChar(0x0B39)));
        m_keymap.insert(0x69,QString(QChar(0x0B17)));
        m_keymap.insert(0x6f,QString(QChar(0x0B26)));
        m_keymap.insert(0x70,QString(QChar(0x0B1C)));
        m_keymap.insert(0x5B,QString(QChar(0x0B21)));
        m_keymap.insert(0x5D,QString(QChar(0x0B3C)));
        m_keymap.insert(0x61,QString(QChar(0x0B4B)));
        m_keymap.insert(0x73,QString(QChar(0x0B47)));
        m_keymap.insert(0x64,QString(QChar(0x0B4D)));
        m_keymap.insert(0x66,QString(QChar(0x0B3F)));
        m_keymap.insert(0x67,QString(QChar(0x0B41)));
        m_keymap.insert(0x68,QString(QChar(0x0B2A)));
        m_keymap.insert(0x6A,QString(QChar(0x0B30)));
        m_keymap.insert(0x6B,QString(QChar(0x0B15)));
        m_keymap.insert(0x6C,QString(QChar(0x0B24)));
        m_keymap.insert(0x3B,QString(QChar(0x0B1A)));
        m_keymap.insert(0x27,QString(QChar(0x0B1F)));
        m_keymap.insert(0x7A,QString(QChar(0x0B5F)));
        m_keymap.insert(0x78,QString(QChar(0x0B02)));
        m_keymap.insert(0x63,QString(QChar(0x0B2E)));
        m_keymap.insert(0x76,QString(QChar(0x0B28)));
        m_keymap.insert(0x62,QString(QChar(0x0B71)));
	m_keymap.insert(0x6E,QString(QChar(0x0B32)));
        m_keymap.insert(0x6D,QString(QChar(0x0B38)));
        m_keymap.insert(0x2C,QString(QChar(0x2C)));
        m_keymap.insert(0x2E,QString(QChar(0x2E)));
        m_keymap.insert(0x2F,QString(QChar(0x0B5F)));
        m_keymap.insert(0x20,QString(QChar(0x20)));
    }

     void addAltedKeys()
     {
         m_keymap.insert(0xA0,QString(QChar(0x0B67)));
         m_keymap.insert(0xA1,QString(QChar(0x0B68)));
         m_keymap.insert(0xA2,QString(QChar(0x0B69)));
         m_keymap.insert(0xA3,QString(QChar(0x0B6A)));
         m_keymap.insert(0xA4,QString(QChar(0x0B6B)));
         m_keymap.insert(0xA5,QString(QChar(0x0B6C)));
         m_keymap.insert(0xA6,QString(QChar(0x0B6D)));
         m_keymap.insert(0xA7,QString(QChar(0x0B6E)));
         m_keymap.insert(0xA8,QString(QChar(0x0B6F)));
         m_keymap.insert(0xA9,QString(QChar(0x0B66)));
         m_keymap.insert(0xAA,QString(QChar(0x20B9)));
         m_keymap.insert(0xAB,QString(QChar(0x0B44)));
         m_keymap.insert(0xAF,QString(QChar(0x0B63)));
         m_keymap.insert(0xB6,QString(QChar(0x0B5C)));
         m_keymap.insert(0xBB,QString(QChar(0x0B62)));
         m_keymap.insert(0xC5,QString(QChar(0x0B70)));
         m_keymap.insert(0xC8,QString(QChar(0x0B35)));
         m_keymap.insert(0xCC,QString(QChar(0x0965)));
     }

     void addAltShiftedKeys()
     {
         m_keymap.insert(0xE5,QString(QChar(0x0B60)));
         m_keymap.insert(0xE9,QString(QChar(0x0B61)));
         m_keymap.insert(0xF0,QString(QChar(0x0B5D)));
         m_keymap.insert(0xF5,QString(QChar(0x0B0C)));
         m_keymap.insert(0x106,QString(QChar(0x0B3D)));
     }
};
#endif // ORIYA_AUTOMATA_H

