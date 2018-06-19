// Copyright (c) 2016-2018 LG Electronics, Inc.
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

#ifndef PERSIAN_AUTOMATA_H
#define PERSIAN_AUTOMATA_H

#include "automatabase.h"
#include <QLocale>

class PersianAutomata : public AutomataBase
{

public:
    PersianAutomata()
    {
        m_keymap.clear();
        //Normal Keyboard
        //First Row - HW Keyboard
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
        //First Row - Virtual Keyboard
        m_keymap.insert(0x6F1,QString(0x6F1));
        m_keymap.insert(0x6F2,QString(0x6F2));
        m_keymap.insert(0x6F3,QString(0x6F3));
        m_keymap.insert(0x6F4,QString(0x6F4));
        m_keymap.insert(0x6F5,QString(0x6F5));
        m_keymap.insert(0x6F6,QString(0x6F6));
        m_keymap.insert(0x6F7,QString(0x6F7));
        m_keymap.insert(0x6F8,QString(0x6F8));
        m_keymap.insert(0x6F9,QString(0x6F9));
        m_keymap.insert(0x6F0,QString(0x6F0));
        //Second Row
        m_keymap.insert(0x71,QString(0x636));
        m_keymap.insert(0x77,QString(0x635));
        m_keymap.insert(0x65,QString(0x62B));
        m_keymap.insert(0x72,QString(0x642));
        m_keymap.insert(0x74,QString(0x641));
        m_keymap.insert(0x79,QString(0x63A));
        m_keymap.insert(0x75,QString(0x639));
        m_keymap.insert(0x69,QString(0x647));
        m_keymap.insert(0x6F,QString(0x62E));
        m_keymap.insert(0x70,QString(0x62D));
        m_keymap.insert(0x5B,QString(0x62C));
        m_keymap.insert(0x5D,QString(0x686));
        m_keymap.insert(0x5C,QString(0x67E));
        //Third Row
        m_keymap.insert(0x61,QString(0x634));
        m_keymap.insert(0x73,QString(0x633));
        m_keymap.insert(0x64,QString(0x6CC));
        m_keymap.insert(0x66,QString(0x628));
        m_keymap.insert(0x67,QString(0x644));
        m_keymap.insert(0x68,QString(0x627));
        m_keymap.insert(0x6A,QString(0x62A));
        m_keymap.insert(0x6B,QString(0x646));
        m_keymap.insert(0x6C,QString(0x645));
        m_keymap.insert(0x3B,QString(0x6A9));
        m_keymap.insert(0x27,QString(0x6AF));
        //Fourth Row
        m_keymap.insert(0x40,QString(0x40));
        m_keymap.insert(0x7A,QString(0x638));
        m_keymap.insert(0x78,QString(0x637));
        m_keymap.insert(0x63,QString(0x632));
        m_keymap.insert(0x76,QString(0x631));
        m_keymap.insert(0x62,QString(0x630));
        m_keymap.insert(0x6E,QString(0x62F));
        m_keymap.insert(0x6D1,QString(0x67E));
        m_keymap.insert(0x6D,QString(0x626));
        m_keymap.insert(0x2C,QString(0x648));
        m_keymap.insert(0x8C,QString(0x2C));
        m_keymap.insert(0x2E,QString(0x2E));
        m_keymap.insert(0x2F1,QString(0x3F));
        m_keymap.insert(0x2F,QString(0x2F));
        //Shift Keyboard
        //First Row - Virtual Keyboard
        m_keymap.insert(0x21,QString(0x21));
        m_keymap.insert(0x648,QString(0x2C));
        m_keymap.insert(0x40,QString(0x40));
        m_keymap.insert(0xFDFC,QString(0xFDFC));
        m_keymap.insert(0x25,QString(0x25));
        m_keymap.insert(0x637,QString(0x78));
        m_keymap.insert(0x60C,QString(0x60C));
        m_keymap.insert(0x2A,QString(0x2A));
        m_keymap.insert(0x29,QString(0x29));
        m_keymap.insert(0x28,QString(0x28));
        m_keymap.insert(0x5F,QString(0x5F));
        m_keymap.insert(0x2B,QString(0x2B));
        //First Row - Hardware Keyboard
        m_keymap.insert(0x23,QString(0x23));
        m_keymap.insert(0x24,QString(0x24));
        m_keymap.insert(0x5E,QString(0x5E));
        m_keymap.insert(0x26,QString(0x26));
        m_keymap.insert(0x2A,QString(0x2A));
        //Second Row
        m_keymap.insert(0x511,QString(0x652));
        m_keymap.insert(0x51,QString(0x64B));
        m_keymap.insert(0x57,QString(0x64C));
        m_keymap.insert(0x45,QString(0x64D));
        m_keymap.insert(0x521,QString(0x64B));
        m_keymap.insert(0x52,QString("\u0631\u06CC\u0627\u0644"));
        m_keymap.insert(0x541,QString(0x64F));
        m_keymap.insert(0x54,QString(0x60C));
        m_keymap.insert(0x591,QString(0x650));
        m_keymap.insert(0x59,QString(0x61B));
        m_keymap.insert(0x551,QString(0x64E));
        m_keymap.insert(0x55,QString(0x2C));
        m_keymap.insert(0x491,QString(0x651));
        m_keymap.insert(0x49,QString(0x5D));
        m_keymap.insert(0x4F1,QString(0x5D));
        m_keymap.insert(0x4F,QString(0x5B));
        m_keymap.insert(0x501,QString(0x5B));
        m_keymap.insert(0x50,QString(0x5C));
        m_keymap.insert(0x7B,QString(0x7D));
        m_keymap.insert(0x7D,QString(0x7B));
        m_keymap.insert(0x7C,QString(0x7C));
        //Third Row
        m_keymap.insert(0x411,QString(0x624));
        m_keymap.insert(0x41,QString(0x64E));
        m_keymap.insert(0x531,QString(0x626));
        m_keymap.insert(0x53,QString(0x64F));
        m_keymap.insert(0x441,QString(0x64A));
        m_keymap.insert(0x44,QString(0x650));
        m_keymap.insert(0x461,QString(0x625));
        m_keymap.insert(0x46,QString(0x651));
        m_keymap.insert(0x471,QString(0x623));
        m_keymap.insert(0x47,QString(0x6C0));
        m_keymap.insert(0x48,QString(0x622));
        m_keymap.insert(0x4A1,QString(0x629));
        m_keymap.insert(0x4A,QString(0x640));
        m_keymap.insert(0x4B,QString(0xAB));
        m_keymap.insert(0x4C,QString(0xBB));
        m_keymap.insert(0x3A,QString(0x3A));
        m_keymap.insert(0x221,QString(0x61B));
        m_keymap.insert(0x22,QString(0x22));
        m_keymap.insert(0x3F,QString(0x61F));
        //Fourth Row
        m_keymap.insert(0x40,QString(0x40));
        m_keymap.insert(0x5A1,QString(0x653));
        m_keymap.insert(0x5A,QString(0x629));
        m_keymap.insert(0x581,QString(0x698));
        m_keymap.insert(0x58,QString(0x64A));
        m_keymap.insert(0x431,QString(0x670));
        m_keymap.insert(0x43,QString(0x698));
        m_keymap.insert(0x561,QString(0x654));
        m_keymap.insert(0x56,QString(0x624));
        m_keymap.insert(0x421,QString(0x655));
        m_keymap.insert(0x42,QString(0x625));
        m_keymap.insert(0x4E1,QString(0x621));
        m_keymap.insert(0x4E,QString(0x623));
        m_keymap.insert(0x4D1,QString(0x3C));
        m_keymap.insert(0x4D,QString(0x621));
        m_keymap.insert(0x3C1,QString(0x3E));
        m_keymap.insert(0x3C,QString(0x3C));
        m_keymap.insert(0x3E1,QString(0x2C));
        m_keymap.insert(0x3E,QString(0x3E));
        m_keymap.insert(0x8A,QString(0x2E));
        m_keymap.insert(0x8B,QString(0x3F));
        //Space Key
        m_keymap.insert(0x20,QString(0x20));
    }

    void setPreedit(const QString &preeditString, int cursorPos)
    {
        Q_UNUSED(cursorPos);
        m_surroundingText = preeditString;
    }

    bool isPredictionSupported()
    {
        return true;
    }

    void reset() {}

    static AutomataBase* create()
    {
        return new PersianAutomata();
    }
};

#endif // PERSIAN_AUTOMATA_H
