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

#ifndef BURMESE_AUTOMATA_H
#define BURMESE_AUTOMATA_H

#include "automatabase.h"
#include <QLocale>

class BurmeseAutomata : public AutomataBase
{

public:
    BurmeseAutomata()
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
        return new BurmeseAutomata();
    }

private:
    void addNumberKeys()
    {
        m_keymap.insert(0x31,QString(QChar(0x1041)));
        m_keymap.insert(0x32,QString(QChar(0x1042)));
        m_keymap.insert(0x33,QString(QChar(0x1043)));
        m_keymap.insert(0x34,QString(QChar(0x1044)));
        m_keymap.insert(0x35,QString(QChar(0x1045)));
        m_keymap.insert(0x36,QString(QChar(0x1046)));
        m_keymap.insert(0x37,QString(QChar(0x1047)));
        m_keymap.insert(0x38,QString(QChar(0x1048)));
        m_keymap.insert(0x39,QString(QChar(0x1049)));
        m_keymap.insert(0x30,QString(QChar(0x1040)));
    }

    void addSymbolKeys()
    {
        m_keymap.insert(0x60,QString(QChar(0x1050)));
        m_keymap.insert(0x7E,QString(QChar(0x100E)));
        m_keymap.insert(0x2D,QString(QChar(0x2D)));
        m_keymap.insert(0x3D,QString(QChar(0x3D)));
        m_keymap.insert(0x5C,QString(QChar(0x104F)));
        m_keymap.insert(0x7C,QString(QChar(0x1051)));
        m_keymap.insert(0x21,QString(QChar(0x100D)));
        m_keymap.insert(0x40,QString(QChar(0x1052)));
        m_keymap.insert(0x23,QString(QChar(0x100B)));
        m_keymap.insert(0x24,QString(QChar(0x1053)));
        m_keymap.insert(0x25,QString(QChar(0x1054)));
        m_keymap.insert(0x5E,QString(QChar(0x1055)));
        m_keymap.insert(0x26,QString(QChar(0x101B)));
        m_keymap.insert(0x2A,QString(QChar(0x002A)));
        m_keymap.insert(0x28,QString(QChar(0x0028)));
        m_keymap.insert(0x29,QString(QChar(0x0029)));
        m_keymap.insert(0x5F,QString(QChar(0x5F)));
        m_keymap.insert(0x2B,QString(QChar(0x2B)));
        m_keymap.insert(0x7B,QString(QChar(0xBB)));
        m_keymap.insert(0x7D,QString(QChar(0xAB)));
    }

    void addNormalKeys()
    {
        m_keymap.insert(0x71,QString(QChar(0x1006)));
        m_keymap.insert(0x77,QString(QChar(0x1010)));
        m_keymap.insert(0x65,QString(QChar(0x1014)));
        m_keymap.insert(0x72,QString(QChar(0x1019)));
        m_keymap.insert(0x74,QString(QChar(0x1021)));
        m_keymap.insert(0x79,QString(QChar(0x1015)));
        m_keymap.insert(0x75,QString(QChar(0x1000)));
        m_keymap.insert(0x69,QString(QChar(0x1004)));
        m_keymap.insert(0x6F,QString(QChar(0x101E)));
        m_keymap.insert(0x70,QString(QChar(0x1005)));
        m_keymap.insert(0x5B,QString(QChar(0x101F)));
        m_keymap.insert(0x5D,QString(QChar(0x1029)));
        m_keymap.insert(0x61,QString(QChar(0x1031)));
        m_keymap.insert(0x73,QString(QChar(0x103B)));
        m_keymap.insert(0x64,QString(QChar(0x102D)));
        m_keymap.insert(0x66,QString(QChar(0x103A)));
        m_keymap.insert(0x67,QString(QChar(0x102B)));
        m_keymap.insert(0x68,QString(QChar(0x1037)));
        m_keymap.insert(0x6A,QString(QChar(0x103C)));
        m_keymap.insert(0x6B,QString(QChar(0x102F)));
        m_keymap.insert(0x6C,QString(QChar(0x1030)));
        m_keymap.insert(0x3B,QString(QChar(0x1038)));
        m_keymap.insert(0x27,QString(QChar(0x0027)));
        m_keymap.insert(0x7A,QString(QChar(0x1016)));
        m_keymap.insert(0x78,QString(QChar(0x1011)));
        m_keymap.insert(0x63,QString(QChar(0x1001)));
        m_keymap.insert(0x76,QString(QChar(0x101C)));
        m_keymap.insert(0x62,QString(QChar(0x1018)));
        m_keymap.insert(0x6E,QString(QChar(0x100A)));
        m_keymap.insert(0x6D,QString(QChar(0x102C)));
        m_keymap.insert(0x2C,QString(QChar(0x002C)));
        m_keymap.insert(0x2E,QString(QChar(0x002E)));
        m_keymap.insert(0x2F,QString(QChar(0x002F)));
        m_keymap.insert(0x20,QString(QChar(0x20)));
    }

    void addShiftedKeys()
    {
        m_keymap.insert(0x51,QString(QChar(0x1008)));
        m_keymap.insert(0x57,QString(QChar(0x101D)));
        m_keymap.insert(0x45,QString(QChar(0x1023)));
        m_keymap.insert(0x52,QString(QChar(0x104E)));
        m_keymap.insert(0x54,QString(QChar(0x1024)));
        m_keymap.insert(0x59,QString(QChar(0x104C)));
        m_keymap.insert(0x55,QString(QChar(0x1025)));
        m_keymap.insert(0x49,QString(QChar(0x104D)));
        m_keymap.insert(0x4F,QString(QChar(0x103F)));
        m_keymap.insert(0x50,QString(QChar(0x100F)));
        m_keymap.insert(0x7B,QString(QChar(0x1027)));
        m_keymap.insert(0x7D,QString(QChar(0x102A)));
        m_keymap.insert(0x41,QString(QChar(0x1017)));
        m_keymap.insert(0x53,QString(QChar(0x103E)));
        m_keymap.insert(0x44,QString(QChar(0x102E)));
        m_keymap.insert(0x46,QString(QChar(0x1039)));
        m_keymap.insert(0x47,QString(QChar(0x103D)));
        m_keymap.insert(0x48,QString(QChar(0x1036)));
        m_keymap.insert(0x4A,QString(QChar(0x1032)));
        m_keymap.insert(0x4B,QString(QChar(0x1012)));
        m_keymap.insert(0x4C,QString(QChar(0x1013)));
        m_keymap.insert(0x3A,QString(QChar(0x1002)));
        m_keymap.insert(0x22,QString(QChar(0x0022)));
        m_keymap.insert(0x5A,QString(QChar(0x1007)));
        m_keymap.insert(0x58,QString(QChar(0x100C)));
        m_keymap.insert(0x43,QString(QChar(0x1003)));
        m_keymap.insert(0x56,QString(QChar(0x1020)));
        m_keymap.insert(0x42,QString(QChar(0x101A)));
        m_keymap.insert(0x4E,QString(QChar(0x1009)));
        m_keymap.insert(0x4D,QString(QChar(0x1026)));
        m_keymap.insert(0x3C,QString(QChar(0x104A)));
        m_keymap.insert(0x3E,QString(QChar(0x104B)));
        m_keymap.insert(0x3F,QString(QChar(0x003F)));
    }

};

#endif // BURMESE_AUTOMATA_H
