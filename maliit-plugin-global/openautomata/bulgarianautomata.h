// Copyright (c) 2015-2018 LG Electronics, Inc.
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

#ifndef BULGARIAN_AUTOMATA_H
#define BULGARIAN_AUTOMATA_H

#include "automatabase.h"
#include <QLocale>

class BulgarianAutomata: public AutomataBase
{

public:
    BulgarianAutomata() {
        m_keymap.clear();
        m_keymap.insert(0x21,QString(0x21));
        m_keymap.insert(0x23,QString(0x2B));
        m_keymap.insert(0x24,QString(0x22));
        m_keymap.insert(0x25,QString(0x25));
        m_keymap.insert(0x26,QString(0x3A));
        m_keymap.insert(0x28,QString(0x5F));
        m_keymap.insert(0x29,QString(0x2116));
        m_keymap.insert(0x2A,QString(0x2F));
        m_keymap.insert(0x2B,QString(0x20Ac));
        m_keymap.insert(0x2D,QString(0x2D));
        m_keymap.insert(0x2f,QString(0x2E));
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
        m_keymap.insert(0x3D,QString(0x2E));
        m_keymap.insert(0x5C,QString(0x5C));
        m_keymap.insert(0x5D,QString(0x3B));
        m_keymap.insert(0x5E,QString(0x3D));
        m_keymap.insert(0x5F,QString(0x24));
        m_keymap.insert(0x60,QString(0x28));
        m_keymap.insert(0x7C,QString(0x7C));
        m_keymap.insert(0x7D,QString(0xA7));
        m_keymap.insert(0x7E,QString(0x29));
        m_keymap.insert(0x20,QString(0x20));
        //lower case letters
        m_keymap.insert(0x61,QString(0x44C));
        m_keymap.insert(0x62,QString(0x444));
        m_keymap.insert(0x63,QString(0x44A));
        m_keymap.insert(0x64,QString(0x430));
        m_keymap.insert(0x65,QString(0x435));
        m_keymap.insert(0x66,QString(0x43E));
        m_keymap.insert(0x67,QString(0x436));
        m_keymap.insert(0x68,QString(0x433));
        m_keymap.insert(0x69,QString(0x441));
        m_keymap.insert(0x6a,QString(0x442));
        m_keymap.insert(0x6b,QString(0x43D));
        m_keymap.insert(0x6c,QString(0x432));
        m_keymap.insert(0x6d,QString(0x43F));
        m_keymap.insert(0x6e,QString(0x445));
        m_keymap.insert(0x6f,QString(0x434));
        m_keymap.insert(0x70,QString(0x437));
        m_keymap.insert(0x71,QString(0x2C));
        m_keymap.insert(0x72,QString(0x438));
        m_keymap.insert(0x73,QString(0x44F));
        m_keymap.insert(0x74,QString(0x448));
        m_keymap.insert(0x75,QString(0x43A));
        m_keymap.insert(0x76,QString(0x44D));
        m_keymap.insert(0x77,QString(0x443));
        m_keymap.insert(0x78,QString(0x439));
        m_keymap.insert(0x79,QString(0x449));
        m_keymap.insert(0x7a,QString(0x44E));
        //lower case special keys
        m_keymap.insert(0x5B,QString(0x446));
        m_keymap.insert(0x40,QString(0x3F));
        m_keymap.insert(0x3B,QString(0x43C));
        m_keymap.insert(0x27,QString(0x447));
        m_keymap.insert(0x2C,QString(0x440));
        m_keymap.insert(0x2E,QString(0x43B));
        m_keymap.insert(0x2F,QString(0x431));
        //upper case letters
        m_keymap.insert(0x41,QString(0x42C));
        m_keymap.insert(0x42,QString(0x424));
        m_keymap.insert(0x43,QString(0x42A));
        m_keymap.insert(0x44,QString(0x410));
        m_keymap.insert(0x45,QString(0x415));
        m_keymap.insert(0x46,QString(0x41E));
        m_keymap.insert(0x47,QString(0x416));
        m_keymap.insert(0x48,QString(0x413));
        m_keymap.insert(0x49,QString(0x421));
        m_keymap.insert(0x4a,QString(0x422));
        m_keymap.insert(0x4b,QString(0x41D));
        m_keymap.insert(0x4c,QString(0x412));
        m_keymap.insert(0x4d,QString(0x41F));
        m_keymap.insert(0x4e,QString(0x425));
        m_keymap.insert(0x4f,QString(0x414));
        m_keymap.insert(0x50,QString(0x417));
        m_keymap.insert(0x51,QString(0x44B));
        m_keymap.insert(0x52,QString(0x418));
        m_keymap.insert(0x53,QString(0x42F));
        m_keymap.insert(0x54,QString(0x428));
        m_keymap.insert(0x55,QString(0x41A));
        m_keymap.insert(0x56,QString(0x42D));
        m_keymap.insert(0x57,QString(0x423));
        m_keymap.insert(0x58,QString(0x419));
        m_keymap.insert(0x59,QString(0x429));
        m_keymap.insert(0x5A,QString(0x42E));
        //HID  Shift special keys
        m_keymap.insert(0x06a3,QString(0x40));
        m_keymap.insert(0x7B,QString(0x426));
        m_keymap.insert(0x3A,QString(0x41C));
        m_keymap.insert(0x22,QString(0x427));
        m_keymap.insert(0x3C,QString(0x420));
        m_keymap.insert(0x3E,QString(0x41B));
        m_keymap.insert(0x3F,QString(0x411));
    }

    void setPreedit(const QString &preeditString, int cursorPos)
    {
        m_surroundingText = preeditString;
    }

    bool isPredictionSupported()
    {
        return true;
    }

    static AutomataBase* create()
    {
        return new BulgarianAutomata();
    }
};

#endif // BULGARIAN_AUTOMATA_H

