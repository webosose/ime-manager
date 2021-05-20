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

#ifndef UYGHUR_AUTOMATA_H
#define UYGHUR_AUTOMATA_H

#include "automatabase.h"
#include <QLocale>

class UyghurAutomata : public AutomataBase
{

public:
    UyghurAutomata()
    {
        addNumberKeys();
        addSymbolKeys();
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
        return new UyghurAutomata();
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
    }

    void addSymbolKeys()
    {
        m_keymap.insert(0x60,QString(QChar(0x60)));
        m_keymap.insert(0x7E,QString(QChar(0x7E)));
        m_keymap.insert(0x2D,QString(QChar(0x2D)));
        m_keymap.insert(0x3D,QString(QChar(0x3D)));
        m_keymap.insert(0x5C,QString(QChar(0x5C)));
        m_keymap.insert(0x7C,QString(QChar(0x7C)));
        m_keymap.insert(0x21,QString(QChar(0x21)));
        m_keymap.insert(0x40,QString(QChar(0x40)));
        m_keymap.insert(0x23,QString(QChar(0x23)));
        m_keymap.insert(0x24,QString(QChar(0x24)));
        m_keymap.insert(0x25,QString(QChar(0x25)));
        m_keymap.insert(0x5E,QString(QChar(0x5E)));
        m_keymap.insert(0x26,QString(QChar(0x26)));
        m_keymap.insert(0x2A,QString(QChar(0x2A)));
        m_keymap.insert(0x28,QString(QChar(0x29)));
        m_keymap.insert(0x29,QString(QChar(0x28)));
        m_keymap.insert(0x5F,QString(QChar(0x5F)));
        m_keymap.insert(0x2B,QString(QChar(0x2B)));
        m_keymap.insert(0x7B,QString(QChar(0xBB)));
        m_keymap.insert(0x7D,QString(QChar(0xAB)));
    }

    void addNormalKeys()
    {
        m_keymap.insert(0x71,QString(QChar(0x0686)));
        m_keymap.insert(0x77,QString(QChar(0x06CB)));
        m_keymap.insert(0x65,QString(QChar(0x06D0)));
        m_keymap.insert(0x72,QString(QChar(0x0631)));
        m_keymap.insert(0x74,QString(QChar(0x062A)));
        m_keymap.insert(0x79,QString(QChar(0x064A)));
        m_keymap.insert(0x75,QString(QChar(0x06C7)));
        m_keymap.insert(0x69,QString(QChar(0x06AD)));
        m_keymap.insert(0x6F,QString(QChar(0x0648)));
        m_keymap.insert(0x70,QString(QChar(0x067E)));
        m_keymap.insert(0x5B,QString(QChar(0x5D)));
        m_keymap.insert(0x5D,QString(QChar(0x5B)));
        m_keymap.insert(0x61,QString(QChar(0x06BE)));
        m_keymap.insert(0x73,QString(QChar(0x0633)));
        m_keymap.insert(0x64,QString(QChar(0x062F)));
        m_keymap.insert(0x66,QString(QChar(0x0627)));
        m_keymap.insert(0x67,QString(QChar(0x06D5)));
        m_keymap.insert(0x68,QString(QChar(0x0649)));
        m_keymap.insert(0x6A,QString(QChar(0x0642)));
        m_keymap.insert(0x6B,QString(QChar(0x0643)));
        m_keymap.insert(0x6C,QString(QChar(0x0644)));
        m_keymap.insert(0x3B,QString(QChar(0x061B)));
        m_keymap.insert(0x27,QString(QChar(0x27)));//
        m_keymap.insert(0x7A,QString(QChar(0x0632)));
        m_keymap.insert(0x78,QString(QChar(0x0634)));
        m_keymap.insert(0x63,QString(QChar(0x063A)));
        m_keymap.insert(0x76,QString(QChar(0x06C8)));
        m_keymap.insert(0x62,QString(QChar(0x0628)));
        m_keymap.insert(0x6E,QString(QChar(0x0646)));
        m_keymap.insert(0x6D,QString(QChar(0x0645)));
        m_keymap.insert(0x2C,QString(QChar(0x060C)));
        m_keymap.insert(0x2E,QString(QChar(0x2E)));
        m_keymap.insert(0x2F,QString(QChar(0x0626)));
        m_keymap.insert(0x20,QString(QChar(0x20)));
    }

    void addShiftedKeys()
    {
        m_keymap.insert(0x44,QString(QChar(0x0698)));
        m_keymap.insert(0x46,QString(QChar(0x0641)));
        m_keymap.insert(0x47,QString(QChar(0x06AF)));
        m_keymap.insert(0x48,QString(QChar(0x062E)));
        m_keymap.insert(0x4A,QString(QChar(0x062C)));
        m_keymap.insert(0x4B,QString(QChar(0x06C6)));
        m_keymap.insert(0x4C,QString("\u0644\u0627"));
        m_keymap.insert(0x3A,QString(QChar(0x3A)));
        m_keymap.insert(0x22,QString(QChar(0x22)));
        m_keymap.insert(0x3C,QString(QChar(0x3E)));
        m_keymap.insert(0x3E,QString(QChar(0x3C)));
        m_keymap.insert(0x3F,QString(QChar(0x061f)));
    }

};

#endif // UYGHUR_AUTOMATA_H
