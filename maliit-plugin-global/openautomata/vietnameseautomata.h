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
        m_keymap.insert(0x21,QString(QChar(0x102)));
        m_keymap.insert(0x22,QString(QChar(0x22)));
        m_keymap.insert(0x23,QString(QChar(0xCA)));
        m_keymap.insert(0x24,QString(QChar(0xD4)));
        m_keymap.insert(0x25,QString(QChar(0x300)));
        m_keymap.insert(0x26,QString(QChar(0x303)));
        m_keymap.insert(0x27,QString(QChar(0x27)));
        m_keymap.insert(0x28,QString(QChar(0x323)));
        m_keymap.insert(0x29,QString(QChar(0x110)));
        m_keymap.insert(0x2a,QString(QChar(0x301)));
        m_keymap.insert(0x2b,QString(QChar(0x2b)));
        m_keymap.insert(0x2c,QString(QChar(0x2c)));
        m_keymap.insert(0x2d,QString(QChar(0x2d)));
        m_keymap.insert(0x2e,QString(QChar(0x2e)));
        m_keymap.insert(0x2f,QString(QChar(0x2f)));
    }
    void addNumberKeys()
    {
        m_keymap.insert(0x30,QString(QChar(0x111)));
        m_keymap.insert(0x31,QString(QChar(0x103)));
        m_keymap.insert(0x32,QString(QChar(0xE2)));
        m_keymap.insert(0x33,QString(QChar(0xEA)));
        m_keymap.insert(0x34,QString(QChar(0xF4)));
        m_keymap.insert(0x35,QString(QChar(0x300)));
        m_keymap.insert(0x36,QString(QChar(0x309)));
        m_keymap.insert(0x37,QString(QChar(0x303)));
        m_keymap.insert(0x38,QString(QChar(0x301)));
        m_keymap.insert(0x39,QString(QChar(0x323)));
    }

    void addShiftKeys()
    {
        m_keymap.insert(0x3a,QString(QChar(0x3a)));
        m_keymap.insert(0x3b,QString(QChar(0x3b)));
        m_keymap.insert(0x3c,QString(QChar(0x3c)));
        m_keymap.insert(0x3d,QString(QChar(0x20AB)));
        m_keymap.insert(0x3e,QString(QChar(0x3e)));
        m_keymap.insert(0x3f,QString(QChar(0x3f)));
        m_keymap.insert(0x40,QString(QChar(0xC2)));
        m_keymap.insert(0x41,QString(QChar(0x41)));
        m_keymap.insert(0x42,QString(QChar(0x42)));
        m_keymap.insert(0x43,QString(QChar(0x43)));
        m_keymap.insert(0x44,QString(QChar(0x44)));
        m_keymap.insert(0x45,QString(QChar(0x45)));
        m_keymap.insert(0x46,QString(QChar(0x46)));
        m_keymap.insert(0x47,QString(QChar(0x47)));
        m_keymap.insert(0x48,QString(QChar(0x48)));
        m_keymap.insert(0x49,QString(QChar(0x49)));
        m_keymap.insert(0x4a,QString(QChar(0x4a)));
        m_keymap.insert(0x4b,QString(QChar(0x4b)));
        m_keymap.insert(0x4c,QString(QChar(0x4c)));
        m_keymap.insert(0x4d,QString(QChar(0x4d)));
        m_keymap.insert(0x4e,QString(QChar(0x4e)));
        m_keymap.insert(0x4f,QString(QChar(0x4f)));
        m_keymap.insert(0x50,QString(QChar(0x50)));
        m_keymap.insert(0x51,QString(QChar(0x51)));
        m_keymap.insert(0x52,QString(QChar(0x52)));
        m_keymap.insert(0x53,QString(QChar(0x53)));
        m_keymap.insert(0x54,QString(QChar(0x54)));
        m_keymap.insert(0x55,QString(QChar(0x55)));
        m_keymap.insert(0x56,QString(QChar(0x56)));
        m_keymap.insert(0x57,QString(QChar(0x57)));
        m_keymap.insert(0x58,QString(QChar(0x58)));
        m_keymap.insert(0x59,QString(QChar(0x59)));
        m_keymap.insert(0x5a,QString(QChar(0x5a)));
        m_keymap.insert(0x5b,QString(QChar(0x1B0)));
        m_keymap.insert(0x5c,QString(QChar(0x5c)));
        m_keymap.insert(0x5d,QString(QChar(0x1A1)));
        m_keymap.insert(0x5e,QString(QChar(0x309)));
        m_keymap.insert(0x5f,QString(QChar(0x5f)));
    }

    void addNormalKeys()
    {
        m_keymap.insert(0x60,QString(QChar(0x60)));
        m_keymap.insert(0x61,QString(QChar(0x61)));
        m_keymap.insert(0x62,QString(QChar(0x62)));
        m_keymap.insert(0x63,QString(QChar(0x63)));
        m_keymap.insert(0x64,QString(QChar(0x64)));
        m_keymap.insert(0x65,QString(QChar(0x65)));
        m_keymap.insert(0x66,QString(QChar(0x66)));
        m_keymap.insert(0x67,QString(QChar(0x67)));
        m_keymap.insert(0x68,QString(QChar(0x68)));
        m_keymap.insert(0x69,QString(QChar(0x69)));
        m_keymap.insert(0x6a,QString(QChar(0x6a)));
        m_keymap.insert(0x6b,QString(QChar(0x6b)));
        m_keymap.insert(0x6c,QString(QChar(0x6c)));
        m_keymap.insert(0x6d,QString(QChar(0x6d)));
        m_keymap.insert(0x6e,QString(QChar(0x6e)));
        m_keymap.insert(0x6f,QString(QChar(0x6f)));
        m_keymap.insert(0x70,QString(QChar(0x70)));
        m_keymap.insert(0x71,QString(QChar(0x71)));
        m_keymap.insert(0x72,QString(QChar(0x72)));
        m_keymap.insert(0x73,QString(QChar(0x73)));
        m_keymap.insert(0x74,QString(QChar(0x74)));
        m_keymap.insert(0x75,QString(QChar(0x75)));
        m_keymap.insert(0x76,QString(QChar(0x76)));
        m_keymap.insert(0x77,QString(QChar(0x77)));
        m_keymap.insert(0x78,QString(QChar(0x78)));
        m_keymap.insert(0x79,QString(QChar(0x79)));
        m_keymap.insert(0x7a,QString(QChar(0x7a)));
        m_keymap.insert(0x7b,QString(QChar(0x1AF)));
        m_keymap.insert(0x7c,QString(QChar(0x7c)));
        m_keymap.insert(0x7d,QString(QChar(0x1A0)));
        m_keymap.insert(0x7e,QString(QChar(0x7e)));
        m_keymap.insert(0x20,QString(QChar(0x20)));
    }

    void addAccentKeys()
    {
        m_keymap.insert(0x4011,QString(QChar(0x40)));
        m_keymap.insert(0x2d1,QString(QChar(0x2D)));
        m_keymap.insert(0x5f1,QString(QChar(0x20AB)));
        m_keymap.insert(0x82,QString(QChar(0x30)));
        m_keymap.insert(0x85,QString(QChar(0x31)));
        m_keymap.insert(0x80,QString(QChar(0x32)));
        m_keymap.insert(0x81,QString(QChar(0x33)));
        m_keymap.insert(0x86,QString(QChar(0x34)));
        m_keymap.insert(0x87,QString(QChar(0x35)));
        m_keymap.insert(0x88,QString(QChar(0x36)));
        m_keymap.insert(0x89,QString(QChar(0x37)));
        m_keymap.insert(0x90,QString(QChar(0x38)));
        m_keymap.insert(0x91,QString(QChar(0x39)));
        m_keymap.insert(0x1ea7,QString(QChar(0x1ea7)));
        m_keymap.insert(0x1ea5,QString(QChar(0x1ea5)));
        m_keymap.insert(0x1ead,QString(QChar(0x1ead)));
        m_keymap.insert(0x1ea9,QString(QChar(0x1ea9)));
        m_keymap.insert(0x1eab,QString(QChar(0x1eab)));
        m_keymap.insert(0x1eb1,QString(QChar(0x1eb1)));
        m_keymap.insert(0x1eaf,QString(QChar(0x1eaf)));
        m_keymap.insert(0x1eb7,QString(QChar(0x1eb7)));
        m_keymap.insert(0x1eb3,QString(QChar(0x1eb3)));
        m_keymap.insert(0x1eb5,QString(QChar(0x1eb5)));
        m_keymap.insert(0x1ec1,QString(QChar(0x1ec1)));
        m_keymap.insert(0x1ebf,QString(QChar(0x1ebf)));
        m_keymap.insert(0x1ec7,QString(QChar(0x1ec7)));
        m_keymap.insert(0x1ec3,QString(QChar(0x1ec3)));
        m_keymap.insert(0x1ec5,QString(QChar(0x1ec5)));
        m_keymap.insert(0x1ed3,QString(QChar(0x1ed3)));
        m_keymap.insert(0x1ed1,QString(QChar(0x1ed1)));
        m_keymap.insert(0x1ed9,QString(QChar(0x1ed9)));
        m_keymap.insert(0x1ed5,QString(QChar(0x1ed5)));
        m_keymap.insert(0x1ed7,QString(QChar(0x1ed7)));
        m_keymap.insert(0x1edd,QString(QChar(0x1edd)));
        m_keymap.insert(0x1edb,QString(QChar(0x1edb)));
        m_keymap.insert(0x1ee3,QString(QChar(0x1ee3)));
        m_keymap.insert(0x1edf,QString(QChar(0x1edf)));
        m_keymap.insert(0x1ee1,QString(QChar(0x1ee1)));
        m_keymap.insert(0x1eeb,QString(QChar(0x1eeb)));
        m_keymap.insert(0x1ee9,QString(QChar(0x1ee9)));
        m_keymap.insert(0x1ef1,QString(QChar(0x1ef1)));
        m_keymap.insert(0x1eed,QString(QChar(0x1eed)));
        m_keymap.insert(0x1eef,QString(QChar(0x1eef)));
        //Expand shift keys
        m_keymap.insert(0x1ea6,QString(QChar(0x1ea6)));
        m_keymap.insert(0x1ea4,QString(QChar(0x1ea4)));
        m_keymap.insert(0x1eac,QString(QChar(0x1eac)));
        m_keymap.insert(0x1ea8,QString(QChar(0x1ea8)));
        m_keymap.insert(0x1eaa,QString(QChar(0x1eaa)));
        m_keymap.insert(0x1eb0,QString(QChar(0x1eb0)));
        m_keymap.insert(0x1eae,QString(QChar(0x1eae)));
        m_keymap.insert(0x1eb6,QString(QChar(0x1eb6)));
        m_keymap.insert(0x1eb2,QString(QChar(0x1eb2)));
        m_keymap.insert(0x1eb4,QString(QChar(0x1eb4)));
        m_keymap.insert(0x1ec0,QString(QChar(0x1ec0)));
        m_keymap.insert(0x1ebe,QString(QChar(0x1ebe)));
        m_keymap.insert(0x1ec6,QString(QChar(0x1ec6)));
        m_keymap.insert(0x1ec2,QString(QChar(0x1ec2)));
        m_keymap.insert(0x1ec4,QString(QChar(0x1ec4)));
        m_keymap.insert(0x1ed2,QString(QChar(0x1ed2)));
        m_keymap.insert(0x1ed0,QString(QChar(0x1ed0)));
        m_keymap.insert(0x1ed8,QString(QChar(0x1ed8)));
        m_keymap.insert(0x1ed4,QString(QChar(0x1ed4)));
        m_keymap.insert(0x1ed6,QString(QChar(0x1ed6)));
        m_keymap.insert(0x1edc,QString(QChar(0x1edc)));
        m_keymap.insert(0x1eda,QString(QChar(0x1eda)));
        m_keymap.insert(0x1ee2,QString(QChar(0x1ee2)));
        m_keymap.insert(0x1ede,QString(QChar(0x1ede)));
        m_keymap.insert(0x1ee0,QString(QChar(0x1ee0)));
        m_keymap.insert(0x1eea,QString(QChar(0x1eea)));
        m_keymap.insert(0x1ee8,QString(QChar(0x1ee8)));
        m_keymap.insert(0x1ef0,QString(QChar(0x1ef0)));
        m_keymap.insert(0x1eec,QString(QChar(0x1eec)));
        m_keymap.insert(0x1eee,QString(QChar(0x1eee)));
    }

    void addAltKeysForHID()
    {
        m_keymap.insert(0xA0,QString(QChar(0x31)));
        m_keymap.insert(0xA1,QString(QChar(0x32)));
        m_keymap.insert(0xA2,QString(QChar(0x33)));
        m_keymap.insert(0xA3,QString(QChar(0x34)));
        m_keymap.insert(0xA4,QString(QChar(0x35)));
        m_keymap.insert(0xA5,QString(QChar(0x36)));
        m_keymap.insert(0xA6,QString(QChar(0x37)));
        m_keymap.insert(0xA7,QString(QChar(0x38)));
        m_keymap.insert(0xA8,QString(QChar(0x39)));
        m_keymap.insert(0xA9,QString(QChar(0x30)));
        m_keymap.insert(0xAA,QString(QChar(0x2D)));
        m_keymap.insert(0xAB,QString(QChar(0x3D)));
        m_keymap.insert(0xB6,QString(QChar(0x5B)));
        m_keymap.insert(0xB7,QString(QChar(0x5D)));
    }

    void addShiftedAltKeysForHID()
    {
        m_keymap.insert(0xFD,QString(QChar(0x7E)));
        m_keymap.insert(0xDA,QString(QChar(0x21)));
        m_keymap.insert(0xDB,QString(QChar(0x40)));
        m_keymap.insert(0xDC,QString(QChar(0x23)));
        m_keymap.insert(0xDD,QString(QChar(0x24)));
        m_keymap.insert(0xDE,QString(QChar(0x25)));
        m_keymap.insert(0xDF,QString(QChar(0x5E)));
        m_keymap.insert(0xE0,QString(QChar(0x26)));
        m_keymap.insert(0xE1,QString(QChar(0x2A)));
        m_keymap.insert(0xE2,QString(QChar(0x28)));
        m_keymap.insert(0xE3,QString(QChar(0x29)));
        m_keymap.insert(0xE4,QString(QChar(0x5F)));
        m_keymap.insert(0xE5,QString(QChar(0x2B)));
        m_keymap.insert(0xF0,QString(QChar(0x7B)));
        m_keymap.insert(0xF1,QString(QChar(0x7D)));
        m_keymap.insert(0xFB,QString(QChar(0x3A)));
        m_keymap.insert(0xFC,QString(QChar(0x22)));
        m_keymap.insert(0xFE,QString(QChar(0x7C)));
        m_keymap.insert(0x106,QString(QChar(0x3C)));
        m_keymap.insert(0x107,QString(QChar(0x3E)));
        m_keymap.insert(0x108,QString(QChar(0x3F)));
    }
};
#endif // VIETNAMESE_AUTOMATA_H
