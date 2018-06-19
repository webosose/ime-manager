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
        m_keymap.insert(0x28,QString(0x28));
        m_keymap.insert(0x29,QString(0x29));
        m_keymap.insert(0x5f,QString(0x0B03));
        m_keymap.insert(0x2b,QString(0x0B0B));
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
        m_keymap.insert(0x51,QString(0x0B14));
        m_keymap.insert(0x57,QString(0x0B10));
        m_keymap.insert(0x45,QString(0x0B06));
        m_keymap.insert(0x52,QString(0x0B08));
        m_keymap.insert(0x54,QString(0x0B0A));
        m_keymap.insert(0x59,QString(0x0B2D));
        m_keymap.insert(0x55,QString(0x0B19));
        m_keymap.insert(0x49,QString(0x0B18));
        m_keymap.insert(0x4F,QString(0x0B27));
        m_keymap.insert(0x50,QString(0x0B1D));
        m_keymap.insert(0x7B,QString(0x0B22));
        m_keymap.insert(0x7D,QString(0x0B1E));
        m_keymap.insert(0x41,QString(0x0B13));
        m_keymap.insert(0x53,QString(0x0B0F));
        m_keymap.insert(0x44,QString(0x0B05));
        m_keymap.insert(0x46,QString(0x0B07));
        m_keymap.insert(0x47,QString(0x0B09));
        m_keymap.insert(0x48,QString(0x0B2B));
        m_keymap.insert(0x4B,QString(0x0B16));
        m_keymap.insert(0x4C,QString(0x0B25));
        m_keymap.insert(0x3A,QString(0x0B1B));
        m_keymap.insert(0x22,QString(0x0B20));
        m_keymap.insert(0x5A,QString(0x0B71));
        m_keymap.insert(0x58,QString(0x0B01));
        m_keymap.insert(0x43,QString(0x0B23));
        m_keymap.insert(0x4E,QString(0x0B33));
        m_keymap.insert(0x4D,QString(0x0B36));
        m_keymap.insert(0x3C,QString(0x0B37));
        m_keymap.insert(0x3E,QString(0x0964));
        m_keymap.insert(0x3F,QString(0x0B2F));
    }

    void addNormalKeys()
    {
        m_keymap.insert(0x2d,QString(0x2d));
        m_keymap.insert(0x3D,QString(0x0B43));
        m_keymap.insert(0x71,QString(0x0B4C));
        m_keymap.insert(0x77,QString(0x0B48));
        m_keymap.insert(0x65,QString(0x0B3E));
        m_keymap.insert(0x72,QString(0x0B40));
        m_keymap.insert(0x74,QString(0x0B42));
        m_keymap.insert(0x79,QString(0x0B2C));
        m_keymap.insert(0x75,QString(0x0B39));
        m_keymap.insert(0x69,QString(0x0B17));
        m_keymap.insert(0x6f,QString(0x0B26));
        m_keymap.insert(0x70,QString(0x0B1C));
        m_keymap.insert(0x5B,QString(0x0B21));
        m_keymap.insert(0x5D,QString(0x0B3C));
        m_keymap.insert(0x61,QString(0x0B4B));
        m_keymap.insert(0x73,QString(0x0B47));
        m_keymap.insert(0x64,QString(0x0B4D));
        m_keymap.insert(0x66,QString(0x0B3F));
        m_keymap.insert(0x67,QString(0x0B41));
        m_keymap.insert(0x68,QString(0x0B2A));
        m_keymap.insert(0x6A,QString(0x0B30));
        m_keymap.insert(0x6B,QString(0x0B15));
        m_keymap.insert(0x6C,QString(0x0B24));
        m_keymap.insert(0x3B,QString(0x0B1A));
        m_keymap.insert(0x27,QString(0x0B1F));
        m_keymap.insert(0x7A,QString(0x0B5F));
        m_keymap.insert(0x78,QString(0x0B02));
        m_keymap.insert(0x63,QString(0x0B2E));
        m_keymap.insert(0x76,QString(0x0B28));
        m_keymap.insert(0x62,QString(0x0B71));
	m_keymap.insert(0x6E,QString(0x0B32));
        m_keymap.insert(0x6D,QString(0x0B38));
        m_keymap.insert(0x2C,QString(0x2C));
        m_keymap.insert(0x2E,QString(0x2E));
        m_keymap.insert(0x2F,QString(0x0B5F));
        m_keymap.insert(0x20,QString(0x20));
    }

     void addAltedKeys()
     {
         m_keymap.insert(0xA0,QString(0x0B67));
         m_keymap.insert(0xA1,QString(0x0B68));
         m_keymap.insert(0xA2,QString(0x0B69));
         m_keymap.insert(0xA3,QString(0x0B6A));
         m_keymap.insert(0xA4,QString(0x0B6B));
         m_keymap.insert(0xA5,QString(0x0B6C));
         m_keymap.insert(0xA6,QString(0x0B6D));
         m_keymap.insert(0xA7,QString(0x0B6E));
         m_keymap.insert(0xA8,QString(0x0B6F));
         m_keymap.insert(0xA9,QString(0x0B66));
         m_keymap.insert(0xAA,QString(0x20B9));
         m_keymap.insert(0xAB,QString(0x0B44));
         m_keymap.insert(0xAF,QString(0x0B63));
         m_keymap.insert(0xB6,QString(0x0B5C));
         m_keymap.insert(0xBB,QString(0x0B62));
         m_keymap.insert(0xC5,QString(0x0B70));
         m_keymap.insert(0xC8,QString(0x0B35));
         m_keymap.insert(0xCC,QString(0x0965));
     }

     void addAltShiftedKeys()
     {
         m_keymap.insert(0xE5,QString(0x0B60));
         m_keymap.insert(0xE9,QString(0x0B61));
         m_keymap.insert(0xF0,QString(0x0B5D));
         m_keymap.insert(0xF5,QString(0x0B0C));
         m_keymap.insert(0x106,QString(0x0B3D));
     }
};
#endif // ORIYA_AUTOMATA_H

