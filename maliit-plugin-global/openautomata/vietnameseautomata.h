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

#ifndef VIETNAMESE_AUTOMATA_H
#define VIETNAMESE_AUTOMATA_H

#include "automatabase.h"
#include <QLocale>

class VietnameseAutomata : public AutomataBase
{

public:
    VietnameseAutomata()
    {
        m_accentSelect = false;

        addSymbolKeys();
        addNumberKeys();
        addShiftKeys();
        addNormalKeys();
        addAccentKeys();
        addAltKeysForHID();
        addShiftedAltKeysForHID();
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

    static AutomataBase* create()
    {
        return new VietnameseAutomata();
    }
private:

    void addSymbolKeys()
    {
        m_keymap.insert(0x21,QString(0x102));
        m_keymap.insert(0x22,QString(0x22));
        m_keymap.insert(0x23,QString(0xCA));
        m_keymap.insert(0x24,QString(0xD4));
        m_keymap.insert(0x25,QString(0x300));
        m_keymap.insert(0x26,QString(0x303));
        m_keymap.insert(0x27,QString(0x27));
        m_keymap.insert(0x28,QString(0x323));
        m_keymap.insert(0x29,QString(0x110));
        m_keymap.insert(0x2a,QString(0x301));
        m_keymap.insert(0x2b,QString(0x2b));
        m_keymap.insert(0x2c,QString(0x2c));
        m_keymap.insert(0x2d,QString(0x2d));
        m_keymap.insert(0x2e,QString(0x2e));
        m_keymap.insert(0x2f,QString(0x2f));
    }
    void addNumberKeys()
    {
        m_keymap.insert(0x30,QString(0x111));
        m_keymap.insert(0x31,QString(0x103));
        m_keymap.insert(0x32,QString(0xE2));
        m_keymap.insert(0x33,QString(0xEA));
        m_keymap.insert(0x34,QString(0xF4));
        m_keymap.insert(0x35,QString(0x300));
        m_keymap.insert(0x36,QString(0x309));
        m_keymap.insert(0x37,QString(0x303));
        m_keymap.insert(0x38,QString(0x301));
        m_keymap.insert(0x39,QString(0x323));
    }

    void addShiftKeys()
    {
        m_keymap.insert(0x3a,QString(0x3a));
        m_keymap.insert(0x3b,QString(0x3b));
        m_keymap.insert(0x3c,QString(0x3c));
        m_keymap.insert(0x3d,QString(0x20AB));
        m_keymap.insert(0x3e,QString(0x3e));
        m_keymap.insert(0x3f,QString(0x3f));
        m_keymap.insert(0x40,QString(0xC2));
        m_keymap.insert(0x41,QString(0x41));
        m_keymap.insert(0x42,QString(0x42));
        m_keymap.insert(0x43,QString(0x43));
        m_keymap.insert(0x44,QString(0x44));
        m_keymap.insert(0x45,QString(0x45));
        m_keymap.insert(0x46,QString(0x46));
        m_keymap.insert(0x47,QString(0x47));
        m_keymap.insert(0x48,QString(0x48));
        m_keymap.insert(0x49,QString(0x49));
        m_keymap.insert(0x4a,QString(0x4a));
        m_keymap.insert(0x4b,QString(0x4b));
        m_keymap.insert(0x4c,QString(0x4c));
        m_keymap.insert(0x4d,QString(0x4d));
        m_keymap.insert(0x4e,QString(0x4e));
        m_keymap.insert(0x4f,QString(0x4f));
        m_keymap.insert(0x50,QString(0x50));
        m_keymap.insert(0x51,QString(0x51));
        m_keymap.insert(0x52,QString(0x52));
        m_keymap.insert(0x53,QString(0x53));
        m_keymap.insert(0x54,QString(0x54));
        m_keymap.insert(0x55,QString(0x55));
        m_keymap.insert(0x56,QString(0x56));
        m_keymap.insert(0x57,QString(0x57));
        m_keymap.insert(0x58,QString(0x58));
        m_keymap.insert(0x59,QString(0x59));
        m_keymap.insert(0x5a,QString(0x5a));
        m_keymap.insert(0x5b,QString(0x1B0));
        m_keymap.insert(0x5c,QString(0x5c));
        m_keymap.insert(0x5d,QString(0x1A1));
        m_keymap.insert(0x5e,QString(0x309));
        m_keymap.insert(0x5f,QString(0x5f));
    }

    void addNormalKeys()
    {
        m_keymap.insert(0x60,QString(0x60));
        m_keymap.insert(0x61,QString(0x61));
        m_keymap.insert(0x62,QString(0x62));
        m_keymap.insert(0x63,QString(0x63));
        m_keymap.insert(0x64,QString(0x64));
        m_keymap.insert(0x65,QString(0x65));
        m_keymap.insert(0x66,QString(0x66));
        m_keymap.insert(0x67,QString(0x67));
        m_keymap.insert(0x68,QString(0x68));
        m_keymap.insert(0x69,QString(0x69));
        m_keymap.insert(0x6a,QString(0x6a));
        m_keymap.insert(0x6b,QString(0x6b));
        m_keymap.insert(0x6c,QString(0x6c));
        m_keymap.insert(0x6d,QString(0x6d));
        m_keymap.insert(0x6e,QString(0x6e));
        m_keymap.insert(0x6f,QString(0x6f));
        m_keymap.insert(0x70,QString(0x70));
        m_keymap.insert(0x71,QString(0x71));
        m_keymap.insert(0x72,QString(0x72));
        m_keymap.insert(0x73,QString(0x73));
        m_keymap.insert(0x74,QString(0x74));
        m_keymap.insert(0x75,QString(0x75));
        m_keymap.insert(0x76,QString(0x76));
        m_keymap.insert(0x77,QString(0x77));
        m_keymap.insert(0x78,QString(0x78));
        m_keymap.insert(0x79,QString(0x79));
        m_keymap.insert(0x7a,QString(0x7a));
        m_keymap.insert(0x7b,QString(0x1AF));
        m_keymap.insert(0x7c,QString(0x7c));
        m_keymap.insert(0x7d,QString(0x1A0));
        m_keymap.insert(0x7e,QString(0x7e));
        m_keymap.insert(0x20,QString(0x20));
    }

    void addAccentKeys()
    {
        m_keymap.insert(0x4011,QString(0x40));
        m_keymap.insert(0x2d1,QString(0x2D));
        m_keymap.insert(0x5f1,QString(0x20AB));
        m_keymap.insert(0x82,QString(0x30));
        m_keymap.insert(0x85,QString(0x31));
        m_keymap.insert(0x80,QString(0x32));
        m_keymap.insert(0x81,QString(0x33));
        m_keymap.insert(0x86,QString(0x34));
        m_keymap.insert(0x87,QString(0x35));
        m_keymap.insert(0x88,QString(0x36));
        m_keymap.insert(0x89,QString(0x37));
        m_keymap.insert(0x90,QString(0x38));
        m_keymap.insert(0x91,QString(0x39));
        m_keymap.insert(0x1ea7,QString(0x1ea7));
        m_keymap.insert(0x1ea5,QString(0x1ea5));
        m_keymap.insert(0x1ead,QString(0x1ead));
        m_keymap.insert(0x1ea9,QString(0x1ea9));
        m_keymap.insert(0x1eab,QString(0x1eab));
        m_keymap.insert(0x1eb1,QString(0x1eb1));
        m_keymap.insert(0x1eaf,QString(0x1eaf));
        m_keymap.insert(0x1eb7,QString(0x1eb7));
        m_keymap.insert(0x1eb3,QString(0x1eb3));
        m_keymap.insert(0x1eb5,QString(0x1eb5));
        m_keymap.insert(0x1ec1,QString(0x1ec1));
        m_keymap.insert(0x1ebf,QString(0x1ebf));
        m_keymap.insert(0x1ec7,QString(0x1ec7));
        m_keymap.insert(0x1ec3,QString(0x1ec3));
        m_keymap.insert(0x1ec5,QString(0x1ec5));
        m_keymap.insert(0x1ed3,QString(0x1ed3));
        m_keymap.insert(0x1ed1,QString(0x1ed1));
        m_keymap.insert(0x1ed9,QString(0x1ed9));
        m_keymap.insert(0x1ed5,QString(0x1ed5));
        m_keymap.insert(0x1ed7,QString(0x1ed7));
        m_keymap.insert(0x1edd,QString(0x1edd));
        m_keymap.insert(0x1edb,QString(0x1edb));
        m_keymap.insert(0x1ee3,QString(0x1ee3));
        m_keymap.insert(0x1edf,QString(0x1edf));
        m_keymap.insert(0x1ee1,QString(0x1ee1));
        m_keymap.insert(0x1eeb,QString(0x1eeb));
        m_keymap.insert(0x1ee9,QString(0x1ee9));
        m_keymap.insert(0x1ef1,QString(0x1ef1));
        m_keymap.insert(0x1eed,QString(0x1eed));
        m_keymap.insert(0x1eef,QString(0x1eef));
        //Expand shift keys
        m_keymap.insert(0x1ea6,QString(0x1ea6));
        m_keymap.insert(0x1ea4,QString(0x1ea4));
        m_keymap.insert(0x1eac,QString(0x1eac));
        m_keymap.insert(0x1ea8,QString(0x1ea8));
        m_keymap.insert(0x1eaa,QString(0x1eaa));
        m_keymap.insert(0x1eb0,QString(0x1eb0));
        m_keymap.insert(0x1eae,QString(0x1eae));
        m_keymap.insert(0x1eb6,QString(0x1eb6));
        m_keymap.insert(0x1eb2,QString(0x1eb2));
        m_keymap.insert(0x1eb4,QString(0x1eb4));
        m_keymap.insert(0x1ec0,QString(0x1ec0));
        m_keymap.insert(0x1ebe,QString(0x1ebe));
        m_keymap.insert(0x1ec6,QString(0x1ec6));
        m_keymap.insert(0x1ec2,QString(0x1ec2));
        m_keymap.insert(0x1ec4,QString(0x1ec4));
        m_keymap.insert(0x1ed2,QString(0x1ed2));
        m_keymap.insert(0x1ed0,QString(0x1ed0));
        m_keymap.insert(0x1ed8,QString(0x1ed8));
        m_keymap.insert(0x1ed4,QString(0x1ed4));
        m_keymap.insert(0x1ed6,QString(0x1ed6));
        m_keymap.insert(0x1edc,QString(0x1edc));
        m_keymap.insert(0x1eda,QString(0x1eda));
        m_keymap.insert(0x1ee2,QString(0x1ee2));
        m_keymap.insert(0x1ede,QString(0x1ede));
        m_keymap.insert(0x1ee0,QString(0x1ee0));
        m_keymap.insert(0x1eea,QString(0x1eea));
        m_keymap.insert(0x1ee8,QString(0x1ee8));
        m_keymap.insert(0x1ef0,QString(0x1ef0));
        m_keymap.insert(0x1eec,QString(0x1eec));
        m_keymap.insert(0x1eee,QString(0x1eee));
    }

    void addAltKeysForHID()
    {
        m_keymap.insert(0xA0,QString(0x31));
        m_keymap.insert(0xA1,QString(0x32));
        m_keymap.insert(0xA2,QString(0x33));
        m_keymap.insert(0xA3,QString(0x34));
        m_keymap.insert(0xA4,QString(0x35));
        m_keymap.insert(0xA5,QString(0x36));
        m_keymap.insert(0xA6,QString(0x37));
        m_keymap.insert(0xA7,QString(0x38));
        m_keymap.insert(0xA8,QString(0x39));
        m_keymap.insert(0xA9,QString(0x30));
        m_keymap.insert(0xAA,QString(0x2D));
        m_keymap.insert(0xAB,QString(0x3D));
        m_keymap.insert(0xB6,QString(0x5B));
        m_keymap.insert(0xB7,QString(0x5D));
    }

    void addShiftedAltKeysForHID()
    {
        m_keymap.insert(0xFD,QString(0x7E));
        m_keymap.insert(0xDA,QString(0x21));
        m_keymap.insert(0xDB,QString(0x40));
        m_keymap.insert(0xDC,QString(0x23));
        m_keymap.insert(0xDD,QString(0x24));
        m_keymap.insert(0xDE,QString(0x25));
        m_keymap.insert(0xDF,QString(0x5E));
        m_keymap.insert(0xE0,QString(0x26));
        m_keymap.insert(0xE1,QString(0x2A));
        m_keymap.insert(0xE2,QString(0x28));
        m_keymap.insert(0xE3,QString(0x29));
        m_keymap.insert(0xE4,QString(0x5F));
        m_keymap.insert(0xE5,QString(0x2B));
        m_keymap.insert(0xF0,QString(0x7B));
        m_keymap.insert(0xF1,QString(0x7D));
        m_keymap.insert(0xFB,QString(0x3A));
        m_keymap.insert(0xFC,QString(0x22));
        m_keymap.insert(0xFE,QString(0x7C));
        m_keymap.insert(0x106,QString(0x3C));
        m_keymap.insert(0x107,QString(0x3E));
        m_keymap.insert(0x108,QString(0x3F));
    }
};
#endif // VIETNAMESE_AUTOMATA_H
