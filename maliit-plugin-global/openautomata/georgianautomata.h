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

#ifndef GEORGIAN_AUTOMATA_H
#define GEORGIAN_AUTOMATA_H

#include "automatabase.h"
#include <QLocale>

class GeorgianAutomata: public AutomataBase
{

public:
    GeorgianAutomata()
    {
        addNumberKeys();
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
        return new GeorgianAutomata();
    }

private:
    void addNumberKeys()
    {
        m_keymap.insert(0x60,QString(0x201E));
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
        m_keymap.insert(0x3D,QString(0x3D));
    }

    void addNormalKeys()
    {
        m_keymap.insert(0x71,QString(0x10E5));
        m_keymap.insert(0x77,QString(0x10EC));
        m_keymap.insert(0x65,QString(0x10D4));
        m_keymap.insert(0x72,QString(0x10E0));
        m_keymap.insert(0x74,QString(0x10E2));
        m_keymap.insert(0x79,QString(0x10E7));
        m_keymap.insert(0x75,QString(0x10E3));
        m_keymap.insert(0x69,QString(0x10D8));
        m_keymap.insert(0x6F,QString(0x10DD));
        m_keymap.insert(0x70,QString(0x10DE));
        m_keymap.insert(0x5B,QString(0x5B));
        m_keymap.insert(0x5D,QString(0x5D));
        m_keymap.insert(0x5C,QString(0x7E));
        m_keymap.insert(0x61,QString(0x10D0));
        m_keymap.insert(0x73,QString(0x10E1));
        m_keymap.insert(0x64,QString(0x10D3));
        m_keymap.insert(0x66,QString(0x10E4));
        m_keymap.insert(0x67,QString(0x10D2));
        m_keymap.insert(0x68,QString(0x10F0));
        m_keymap.insert(0x6A,QString(0x10EF));
        m_keymap.insert(0x6B,QString(0x10D9));
        m_keymap.insert(0x6C,QString(0x10DA));
        m_keymap.insert(0x3B,QString(0x3B));
        m_keymap.insert(0x27,QString(0x27));
        m_keymap.insert(0x7A,QString(0x10D6));
        m_keymap.insert(0x78,QString(0x10EE));
        m_keymap.insert(0x63,QString(0x10EA));
        m_keymap.insert(0x76,QString(0x10D5));
        m_keymap.insert(0x62,QString(0x10D1));
        m_keymap.insert(0x6E,QString(0x10DC));
        m_keymap.insert(0x6D,QString(0x10DB));
        m_keymap.insert(0x2C,QString(0x2C));
        m_keymap.insert(0x2E,QString(0x2E));
        m_keymap.insert(0x2F,QString(0x2F));
        m_keymap.insert(0x20,QString(0x20));
    }

    void addShiftedKeys()
    {
        m_keymap.insert(0x7E,QString(0x201C));
        m_keymap.insert(0x21,QString(0x21));
        m_keymap.insert(0x40,QString(0x40));
        m_keymap.insert(0x23,QString(0x23));
        m_keymap.insert(0x24,QString(0x24));
        m_keymap.insert(0x25,QString(0x25));
        m_keymap.insert(0x5E,QString(0x5E));
        m_keymap.insert(0x26,QString(0x26));
        m_keymap.insert(0x2A,QString(0x2A));
        m_keymap.insert(0x28,QString(0x28));
        m_keymap.insert(0x29,QString(0x29));
        m_keymap.insert(0x5F,QString(0x5F));
        m_keymap.insert(0x2B,QString(0x2B));
        m_keymap.insert(0x57,QString(0x10ED));
        m_keymap.insert(0x52,QString(0x10E6));
        m_keymap.insert(0x54,QString(0x10D7));
        m_keymap.insert(0x7B,QString(0x7B));
        m_keymap.insert(0x7D,QString(0x7D));
        m_keymap.insert(0x7C,QString(0x7C));
        m_keymap.insert(0x53,QString(0x10E8));
        m_keymap.insert(0x4A,QString(0x10DF));
        m_keymap.insert(0x4C,QString(0x20BE));
        m_keymap.insert(0x3A,QString(0x3A));
        m_keymap.insert(0x22,QString(0x22));
        m_keymap.insert(0x5A,QString(0x10EB));
        m_keymap.insert(0x43,QString(0x10E9));
        m_keymap.insert(0x4E,QString(0x4E));
        m_keymap.insert(0x3C,QString(0x3C));
        m_keymap.insert(0x3E,QString(0x3E));
        m_keymap.insert(0x3F,QString(0x3F));
        m_keymap.insert(0x58,QString(""));
        m_keymap.insert(0x56,QString(""));
    }

    void addAltKeysForHID()
    {
      m_keymap.insert(0xA1,QString(0x201E));
      m_keymap.insert(0xA2,QString(0x201C));
      m_keymap.insert(0xA4,QString(0x20AC));
      m_keymap.insert(0xA7,QString(0xB0));
      m_keymap.insert(0xAA,QString(0x2014));
      m_keymap.insert(0xAB,QString(0x2013));
      m_keymap.insert(0xAE,QString(0x10F1));
      m_keymap.insert(0xAF,QString(0xAE));
      m_keymap.insert(0xB1,QString(0x10F8));
      m_keymap.insert(0xB3,QString(0x10F2));
      m_keymap.insert(0xB8,QString(0x10FA));
      m_keymap.insert(0xBB,QString(0x10F6));
      m_keymap.insert(0xBC,QString(0x10F9));
      m_keymap.insert(0xBD,QString(0x10F5));
      m_keymap.insert(0xBE,QString(0x10F7));
      m_keymap.insert(0xC6,QString(0x10F4));
      m_keymap.insert(0xC7,QString(0xA9));
      m_keymap.insert(0xC8,QString(0x10F3));
      m_keymap.insert(0xCA,QString(0x10FC));
      m_keymap.insert(0xCC,QString(0xAB));
      m_keymap.insert(0xCD,QString(0xBB));
      m_keymap.insert(0xCE,QString(0x10FB));
    }
};

#endif // GEORGIAN_AUTOMATA_H
