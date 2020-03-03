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

#ifndef ARMENIAN_AUTOMATA_H
#define ARMENIAN_AUTOMATA_H

#include "automatabase.h"
#include <QLocale>

class ArmenianAutomata: public AutomataBase
{

public:
    ArmenianAutomata()
    {
        addNumberKeys();
        addNormalKeys();
        addShiftedKeys();
        addAccentKeys();
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
        return new ArmenianAutomata();
    }

private:
    void addNumberKeys()
    {
        m_keymap.insert(0x60,QString(0x055D));
        m_keymap.insert(0x31,QString(0x0589));
        m_keymap.insert(0x32,QString(0x0571));
        m_keymap.insert(0x33,QString(0x0575));
        m_keymap.insert(0x34,QString(0x055B));
        m_keymap.insert(0x35,QString(0x2C));
        m_keymap.insert(0x36,QString(0x2D));
        m_keymap.insert(0x37,QString(0x2E));
        m_keymap.insert(0x38,QString(0xAB));
        m_keymap.insert(0x39,QString(0xBB));
        m_keymap.insert(0x30,QString(0x0585));
        m_keymap.insert(0x2D,QString(0x057C));
        m_keymap.insert(0x3D,QString(0x056A));
    }

    void addNormalKeys()
    {
        m_keymap.insert(0x71,QString(0x056D));
        m_keymap.insert(0x77,QString(0x057E));
        m_keymap.insert(0x65,QString(0x0567));
        m_keymap.insert(0x72,QString(0x0580));
        m_keymap.insert(0x74,QString(0x0564));
        m_keymap.insert(0x79,QString(0x0565));
        m_keymap.insert(0x75,QString(0x0568));
        m_keymap.insert(0x69,QString(0x056B));
        m_keymap.insert(0x6F,QString(0x0578));
        m_keymap.insert(0x70,QString(0x0562));
        m_keymap.insert(0X5B,QString(0X0579));
        m_keymap.insert(0X5D,QString(0X057B));
        m_keymap.insert(0X5C,QString(0X055A));
        m_keymap.insert(0X61,QString(0X0561));
        m_keymap.insert(0x73,QString(0x057D));
        m_keymap.insert(0x64,QString(0x057F));
        m_keymap.insert(0x66,QString(0x0586));
        m_keymap.insert(0x67,QString(0x056F));
        m_keymap.insert(0x68,QString(0x0570));
        m_keymap.insert(0x6A,QString(0x0573));
        m_keymap.insert(0x6B,QString(0x0584));
        m_keymap.insert(0x6C,QString(0x056C));
        m_keymap.insert(0x3B,QString(0x0569));
        m_keymap.insert(0x27,QString(0x0583));
        m_keymap.insert(0x7A,QString(0x0566));
        m_keymap.insert(0x78,QString(0x0581));
        m_keymap.insert(0x63,QString(0x0563));
        m_keymap.insert(0x76,QString(0x0582));
        m_keymap.insert(0x62,QString(0x057A));
        m_keymap.insert(0x6E,QString(0x0576));
        m_keymap.insert(0x6D,QString(0x0574));
        m_keymap.insert(0x2C,QString(0x0577));
        m_keymap.insert(0x2E,QString(0x0572));
        m_keymap.insert(0x2F,QString(0x056E));
        m_keymap.insert(0x20,QString(0x20));
    }

    void addShiftedKeys()
    {
        m_keymap.insert(0x7E,QString(0x055C));
        m_keymap.insert(0x21,QString(0x2026));
        m_keymap.insert(0x40,QString(0x0541));
        m_keymap.insert(0x23,QString(0x0545));
        m_keymap.insert(0x24,QString(0x2605));
        m_keymap.insert(0x25,QString(0x2013));
        m_keymap.insert(0x5E,QString(0x2014));
        m_keymap.insert(0x26,QString(0x0587));
        m_keymap.insert(0x2A,QString(0x28));
        m_keymap.insert(0x28,QString(0x29));
        m_keymap.insert(0x29,QString(0x0555));
        m_keymap.insert(0x5F,QString(0x054C));
        m_keymap.insert(0x2B,QString(0x053A));
        m_keymap.insert(0x51,QString(0x053D));
        m_keymap.insert(0x57,QString(0x054E));
        m_keymap.insert(0x45,QString(0x0537));
        m_keymap.insert(0x52,QString(0x0550));
        m_keymap.insert(0x54,QString(0x0534));
        m_keymap.insert(0x59,QString(0x0535));
        m_keymap.insert(0x55,QString(0x0538));
        m_keymap.insert(0x49,QString(0x053B));
        m_keymap.insert(0x4F,QString(0x0548));
        m_keymap.insert(0x50,QString(0x0532));
        m_keymap.insert(0x7B,QString(0x0549));
        m_keymap.insert(0x7D,QString(0x054B));
        m_keymap.insert(0x7C,QString(0x055E));
        m_keymap.insert(0x41,QString(0x0531));
        m_keymap.insert(0x53,QString(0x054D));
        m_keymap.insert(0x44,QString(0x054F));
        m_keymap.insert(0x46,QString(0x0556));
        m_keymap.insert(0x47,QString(0x053F));
        m_keymap.insert(0x48,QString(0x0540));
        m_keymap.insert(0x4A,QString(0x0543));
        m_keymap.insert(0x4B,QString(0x0554));
        m_keymap.insert(0x4C,QString(0x053C));
        m_keymap.insert(0x3A,QString(0x0539));
        m_keymap.insert(0x22,QString(0x0553));
        m_keymap.insert(0x5A,QString(0x0536));
        m_keymap.insert(0x58,QString(0x0551));
        m_keymap.insert(0x43,QString(0x0533));
        m_keymap.insert(0x56,QString(0x0552));
        m_keymap.insert(0x42,QString(0x054A));
        m_keymap.insert(0x4E,QString(0x0546));
        m_keymap.insert(0x4D,QString(0x0544));
        m_keymap.insert(0x3C,QString(0x0547));
        m_keymap.insert(0x3E,QString(0x0542));
        m_keymap.insert(0x3F,QString(0x053E));
    }

    void addAccentKeys()
    {
        m_keymap.insert(0x0587,QString(0x0587));
        m_keymap.insert(0xAE,QString(0xAE));
        m_keymap.insert(0x2122,QString(0x2122));
        m_keymap.insert(0x0192,QString(0x0192));
        m_keymap.insert(0xA9,QString(0xA9));
        m_keymap.insert(0x055F,QString(0x055F));
        m_keymap.insert(0x058A,QString(0x058A));
        m_keymap.insert(0x055C,QString(0x055C));
        m_keymap.insert(0xB6,QString(0xB6));
        m_keymap.insert(0x2116,QString(0x2116));
    }
};

#endif // ARMENIAN_AUTOMATA_H
