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

#ifndef TAJIK_AUTOMATA_H
#define TAJIK_AUTOMATA_H

#include "automatabase.h"
#include <QLocale>

class TajikAutomata: public AutomataBase
{

public:
    TajikAutomata()
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
        return new TajikAutomata();
    }

private:
    void addNumberKeys()
    {
        m_keymap.insert(0x60,QString(QChar(0x0451)));
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
        m_keymap.insert(0x2D,QString(QChar(0x0493)));
        m_keymap.insert(0x3D,QString(QChar(0x4EF)));
    }

    void addNormalKeys()
    {
        m_keymap.insert(0x71,QString(QChar(0x0439)));
        m_keymap.insert(0x77,QString(QChar(0x049B)));
        m_keymap.insert(0x65,QString(QChar(0x0443)));
        m_keymap.insert(0x72,QString(QChar(0x043A)));
        m_keymap.insert(0x74,QString(QChar(0x0435)));
        m_keymap.insert(0x79,QString(QChar(0x043D)));
        m_keymap.insert(0x75,QString(QChar(0x0433)));
        m_keymap.insert(0x69,QString(QChar(0x0448)));
        m_keymap.insert(0x6F,QString(QChar(0x04B3)));
        m_keymap.insert(0x70,QString(QChar(0x0437)));
        m_keymap.insert(0X5B,QString(QChar(0X0445)));
        m_keymap.insert(0X5D,QString(QChar(0X044a)));
        m_keymap.insert(0x021C,QString(QChar(0X005C)));
        m_keymap.insert(0X61,QString(QChar(0X0444)));
        m_keymap.insert(0x73,QString(QChar(0x04B7)));
        m_keymap.insert(0x64,QString(QChar(0x0432)));
        m_keymap.insert(0x66,QString(QChar(0x0430)));
        m_keymap.insert(0x67,QString(QChar(0x043F)));
        m_keymap.insert(0x68,QString(QChar(0x0440)));
        m_keymap.insert(0x6A,QString(QChar(0x043E)));
        m_keymap.insert(0x6B,QString(QChar(0x043B)));
        m_keymap.insert(0x6C,QString(QChar(0x0434)));
        m_keymap.insert(0x3B,QString(QChar(0x0436)));
        m_keymap.insert(0x27,QString(QChar(0x044D)));
        m_keymap.insert(0x7A,QString(QChar(0x044F)));
        m_keymap.insert(0x78,QString(QChar(0x0447)));
        m_keymap.insert(0x63,QString(QChar(0x0441)));
        m_keymap.insert(0x76,QString(QChar(0x043C)));
        m_keymap.insert(0x62,QString(QChar(0x0438)));
        m_keymap.insert(0x6E,QString(QChar(0x0442)));
        m_keymap.insert(0x6D,QString(QChar(0x04E3)));
        m_keymap.insert(0x2C,QString(QChar(0x0431)));
        m_keymap.insert(0x2E,QString(QChar(0x044E)));
        m_keymap.insert(0x2F,QString(QChar(0x002E)));
        m_keymap.insert(0x021B,QString(QChar(0x002F)));
        m_keymap.insert(0x021A,QString(QChar(0x002e)));
        m_keymap.insert(0x20,QString(QChar(0x20)));
    }

    void addShiftedKeys()
    {
        m_keymap.insert(0x7E,QString(QChar(0x0401)));
        m_keymap.insert(0x21,QString(QChar(0x0021)));
        m_keymap.insert(0x40,QString(QChar(0x0022)));
        m_keymap.insert(0x23,QString(QChar(0x2116)));
        m_keymap.insert(0x24,QString(QChar(0x003B)));
        m_keymap.insert(0x25,QString(QChar(0x0025)));
        m_keymap.insert(0x5E,QString(QChar(0x003A)));
        m_keymap.insert(0x26,QString(QChar(0x003F)));
        m_keymap.insert(0x2A,QString(QChar(0x002A)));
        m_keymap.insert(0x28,QString(QChar(0x0028)));
        m_keymap.insert(0x29,QString(QChar(0x0029)));
        m_keymap.insert(0x5F,QString(QChar(0x0492)));
        m_keymap.insert(0x2B,QString(QChar(0x04EE)));
        m_keymap.insert(0x51,QString(QChar(0x0419)));
        m_keymap.insert(0x57,QString(QChar(0x049A)));
        m_keymap.insert(0x45,QString(QChar(0x0423)));
        m_keymap.insert(0x52,QString(QChar(0x041A)));
        m_keymap.insert(0x54,QString(QChar(0x0415)));
        m_keymap.insert(0x59,QString(QChar(0x041D)));
        m_keymap.insert(0x55,QString(QChar(0x0413)));
        m_keymap.insert(0x49,QString(QChar(0x0428)));
        m_keymap.insert(0x4F,QString(QChar(0x04B2)));
        m_keymap.insert(0x50,QString(QChar(0x0417)));
        m_keymap.insert(0x7B,QString(QChar(0x0425)));
        m_keymap.insert(0x7D,QString(QChar(0x042a)));
        m_keymap.insert(0x41,QString(QChar(0x0424)));
        m_keymap.insert(0x53,QString(QChar(0x04B6)));
        m_keymap.insert(0x44,QString(QChar(0x0412)));
        m_keymap.insert(0x46,QString(QChar(0x0410)));
        m_keymap.insert(0x47,QString(QChar(0x041F)));
        m_keymap.insert(0x48,QString(QChar(0x0420)));
        m_keymap.insert(0x4A,QString(QChar(0x041E)));
        m_keymap.insert(0x4B,QString(QChar(0x041B)));
        m_keymap.insert(0x4C,QString(QChar(0x0414)));
        m_keymap.insert(0x3A,QString(QChar(0x0416)));
        m_keymap.insert(0x22,QString(QChar(0x042D)));
        m_keymap.insert(0x5A,QString(QChar(0x042F)));
        m_keymap.insert(0x58,QString(QChar(0x0427)));
        m_keymap.insert(0x43,QString(QChar(0x0421)));
        m_keymap.insert(0x56,QString(QChar(0x041C)));
        m_keymap.insert(0x42,QString(QChar(0x0418)));
        m_keymap.insert(0x4E,QString(QChar(0x0422)));
        m_keymap.insert(0x4D,QString(QChar(0x04E2)));
        m_keymap.insert(0x3C,QString(QChar(0x0411)));
        m_keymap.insert(0x3E,QString(QChar(0x042E)));
        m_keymap.insert(0x3F,QString(QChar(0x002C)));
        m_keymap.insert(0x021D,QString(QChar(0x0040)));
        m_keymap.insert(0x01ba,QString(QChar(0x0023)));
        m_keymap.insert(0x01bb,QString(QChar(0x0024)));
        m_keymap.insert(0x01bc,QString(QChar(0x005e)));
        m_keymap.insert(0x01bd,QString(QChar(0x0026)));
    }
};

#endif // TAJIK_AUTOMATA_H
