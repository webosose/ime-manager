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

#ifndef SOMALI_AUTOMATA_H
#define SOMALI_AUTOMATA_H

#include "automatabase.h"
#include <QLocale>

class SomaliAutomata: public AutomataBase
{

public:
    SomaliAutomata()
    {
        addNumberKeys();
        addNormalKeys();
        addShiftedKeys();
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
        return new SomaliAutomata();
    }

private:
    void addNumberKeys()
    {
        m_keymap.insert(0x60,QString(0x60));
        m_keymap.insert(0x31,QString(0x04A1));
        m_keymap.insert(0x32,QString(0x04A2));
        m_keymap.insert(0x33,QString(0x04A3));
        m_keymap.insert(0x34,QString(0x04A4));
        m_keymap.insert(0x35,QString(0x04A5));
        m_keymap.insert(0x36,QString(0x04A6));
        m_keymap.insert(0x37,QString(0x04A7));
        m_keymap.insert(0x38,QString(0x04A8));
        m_keymap.insert(0x39,QString(0x04A9));
        m_keymap.insert(0x30,QString(0x04A0));
        m_keymap.insert(0x2D,QString(0x2D));
        m_keymap.insert(0x3D,QString(0x3D));
    }

    void addNormalKeys()
    {
        m_keymap.insert(0x71,QString(0x048E));
        m_keymap.insert(0x77,QString(0x0493));
        m_keymap.insert(0x65,QString(0x0497));
        m_keymap.insert(0x72,QString(0x0487));
        m_keymap.insert(0x74,QString(0x0482));
        m_keymap.insert(0x79,QString(0x0495));
        m_keymap.insert(0x75,QString(0x049A));
        m_keymap.insert(0x69,QString(0x0498));
        m_keymap.insert(0x6F,QString(0x0499));
        m_keymap.insert(0x70,QString(""));
        m_keymap.insert(0x5B,QString(0x5B));
        m_keymap.insert(0x5D,QString(0x5D));
        m_keymap.insert(0x5C,QString(0x5C));
        m_keymap.insert(0x61,QString(0x0496));
        m_keymap.insert(0x73,QString(0x0488));
        m_keymap.insert(0x64,QString(0x0486));
        m_keymap.insert(0x66,QString(0x048D));
        m_keymap.insert(0x67,QString(0x048C));
        m_keymap.insert(0x68,QString(0x0494));
        m_keymap.insert(0x6A,QString(0x0483));
        m_keymap.insert(0x6B,QString(0x048F));
        m_keymap.insert(0x6C,QString(0x0490));
        m_keymap.insert(0x3B,QString(0x3B));
        m_keymap.insert(0x27,QString(0x27));
        m_keymap.insert(0x7A,QString(0x0480));
        m_keymap.insert(0x78,QString(0x0484));
        m_keymap.insert(0x63,QString(0x048B));
        m_keymap.insert(0x76,QString(""));
        m_keymap.insert(0x62,QString(0x0481));
        m_keymap.insert(0x6E,QString(0x0492));
        m_keymap.insert(0x6D,QString(0x0491));
        m_keymap.insert(0x2C,QString(0x2C));
        m_keymap.insert(0x2E,QString(0x2E));
        m_keymap.insert(0x2F,QString(0x2F));
        m_keymap.insert(0x20,QString(0x20));
    }

    void addShiftedKeys()
    {
        m_keymap.insert(0x7E,QString(0x7E));
        m_keymap.insert(0x21,QString(0x0021));
        m_keymap.insert(0x40,QString(0x0040));
        m_keymap.insert(0x23,QString(0x0023));
        m_keymap.insert(0x24,QString(0x0024));
        m_keymap.insert(0x25,QString(0x0025));
        m_keymap.insert(0x5E,QString(0x005E));
        m_keymap.insert(0x26,QString(0x0026));
        m_keymap.insert(0x2A,QString(0x002A));
        m_keymap.insert(0x28,QString(0x0028));
        m_keymap.insert(0x29,QString(0x0029));
        m_keymap.insert(0x5F,QString(0x005F));
        m_keymap.insert(0x2B,QString(0x002B));
        m_keymap.insert(0x45,QString(0x049C));
        m_keymap.insert(0x4F,QString(0x049D));
        m_keymap.insert(0x7B,QString(0x7B));
        m_keymap.insert(0x7D,QString(0x7D));
        m_keymap.insert(0x7C,QString(0x7C));
        m_keymap.insert(0x41,QString(0x049B));
        m_keymap.insert(0x53,QString(0x0489));
        m_keymap.insert(0x44,QString(0x048A));
        m_keymap.insert(0x46,QString(""));
        m_keymap.insert(0x47,QString(""));
        m_keymap.insert(0x48,QString(""));
        m_keymap.insert(0x4A,QString(""));
        m_keymap.insert(0x4B,QString(0x0485));
        m_keymap.insert(0x3A,QString(0x3A));
        m_keymap.insert(0x22,QString(0x22));
        m_keymap.insert(0x58,QString(""));
        m_keymap.insert(0x43,QString(""));
        m_keymap.insert(0x56,QString(""));
        m_keymap.insert(0x4E,QString(""));
        m_keymap.insert(0x3C,QString(0x3C));
        m_keymap.insert(0x3E,QString(0x3E));
        m_keymap.insert(0x3F,QString(0x3F));
    }
};

#endif // SOMALI_AUTOMATA_H
