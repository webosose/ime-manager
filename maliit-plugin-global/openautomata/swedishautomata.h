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

#ifndef SWEDISH_AUTOMATA_H
#define SWEDISH_AUTOMATA_H

#include "automatabase.h"
#include <QLocale>

class SwedishAutomata : public AutomataBase
{

public:
    SwedishAutomata()
    {
        m_accentSelect = false;

        m_accents.insert(QString(0x00B4));
        m_accents.insert(QString(0x0060));
        m_accents.insert(QString(0x007E));
        m_accents.insert(QString(0x00A8));
        m_accents.insert(QString(0x005E));

        addSymbolKeys();
        addNumberKeys();
        addShiftKeys();
        addNormalKeys();
        addAccentKeys();
        addAltKeysForHID();

        addAcuteAccentForHID();
        addGraveAccentKeysForHID();
        addTildeAccentKeysForHID();
        addDiaresisAccentForHID();
        addCircumflexAccentForHID();
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
        return new SwedishAutomata();
    }

private:
    void addSymbolKeys()
    {
        m_keymap.insert(0x21,QString(0x21));
        m_keymap.insert(0x22,QString(0xC4));
        m_keymap.insert(0x23,QString(0x23));
        m_keymap.insert(0x24,QString(0x24));
        m_keymap.insert(0x25,QString(0x25));
        m_keymap.insert(0x26,QString(0x26));
        m_keymap.insert(0x27,QString(0xE4));
        m_keymap.insert(0x28,QString(0x28));
        m_keymap.insert(0x29,QString(0x29));
        m_keymap.insert(0x2a,QString(0x2a));
        m_keymap.insert(0x2b,QString(0x60));
        m_keymap.insert(0x2c,QString(0x2c));
        m_keymap.insert(0x2d,QString(0x2B));
        m_keymap.insert(0x2e,QString(0x2e));
        m_keymap.insert(0x2f,QString(0x2D));
    }

    void addNumberKeys()
    {
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
    }

    void addShiftKeys()
    {
        m_keymap.insert(0x3A,QString(0xD6));
        m_keymap.insert(0x3B,QString(0xF6));
        m_keymap.insert(0x3c,QString(0x3B));
        m_keymap.insert(0x3d,QString(0xB4));
        m_keymap.insert(0x3e,QString(0x3A));
        m_keymap.insert(0x3f,QString(0x5f));
        m_keymap.insert(0x40,QString(0x40));
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
        m_keymap.insert(0x5b,QString(0xE5));
        m_keymap.insert(0x5c,QString(0x27));
        m_keymap.insert(0x5d,QString(0xA8));
        m_keymap.insert(0x5e,QString(0x5e));
        m_keymap.insert(0x5f,QString(0x3f));
        m_keymap.insert(0x7e,QString(0xBD));
    }

    void addNormalKeys()
    {
        m_keymap.insert(0x60,QString(0xA7));
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
        m_keymap.insert(0x7B,QString(0xC5));
        m_keymap.insert(0x7c,QString(0x2A));
        m_keymap.insert(0x7d,QString(0x5E));
        m_keymap.insert(0x20,QString(0x20));
    }

    void addAccentKeys()
    {
        m_keymap.insert(0xE2,QString(0xE2));
        m_keymap.insert(0xE3,QString(0xE3));
        m_keymap.insert(0xEB1,QString(0xEB));
        m_keymap.insert(0xEA,QString(0xEA));
        m_keymap.insert(0xEF,QString(0xEF));
        m_keymap.insert(0xEE,QString(0xEE));
        m_keymap.insert(0xF1,QString(0xF1));
        m_keymap.insert(0xF4,QString(0xF4));
        m_keymap.insert(0xF5,QString(0xF5));
        m_keymap.insert(0xFC,QString(0xFC));
        m_keymap.insert(0xFB,QString(0xFB));
        m_keymap.insert(0xFF,QString(0xFF));
        m_keymap.insert(0xC2,QString(0xC2));
        m_keymap.insert(0xC3,QString(0xC3));
        m_keymap.insert(0xCB1,QString(0xCB));
        m_keymap.insert(0xCA,QString(0xCA));
        m_keymap.insert(0xCF,QString(0xCF));
        m_keymap.insert(0xCE,QString(0xCE));
        m_keymap.insert(0xD1,QString(0xD1));
        m_keymap.insert(0xD4,QString(0xD4));
        m_keymap.insert(0xD5,QString(0xD5));
        m_keymap.insert(0xDC,QString(0xDC));
        m_keymap.insert(0xDB,QString(0xDB));
        m_keymap.insert(0x178,QString(0x178));
    }

    void addAltKeysForHID()
    {
        m_keymap.insert(0xA1,QString(0x0040));
        m_keymap.insert(0xA2,QString(0x00A3));
        m_keymap.insert(0xA3,QString(0x0024));
        m_keymap.insert(0xA4,QString(0x20AC));
        m_keymap.insert(0xA6,QString(0x007B));
        m_keymap.insert(0xA7,QString(0x005B));
        m_keymap.insert(0xA8,QString(0x005D));
        m_keymap.insert(0xA9,QString(0x007D));
        m_keymap.insert(0xAE,QString(0x20AC));
        m_keymap.insert(0xB7,QString(0x007E));
        m_keymap.insert(0xCB,QString(0x00B5));
        m_keymap.insert(0xAA,QString(0x005C));
    }

    void addAcuteAccentForHID()
    {
        m_accentKeymap.insert(QString(0x00B4)+QString(0x61),QString(0x00E1));
        m_accentKeymap.insert(QString(0x00B4)+QString(0x65),QString(0x00E9));
        m_accentKeymap.insert(QString(0x00B4)+QString(0x69),QString(0x00ED));
        m_accentKeymap.insert(QString(0x00B4)+QString(0x6F),QString(0x00F3));
        m_accentKeymap.insert(QString(0x00B4)+QString(0x75),QString(0x00FA));
        m_accentKeymap.insert(QString(0x00B4)+QString(0x79),QString(0x00FD));

        m_accentKeymap.insert(QString(0x00B4)+QString(0x41),QString(0x00C1));
        m_accentKeymap.insert(QString(0x00B4)+QString(0x45),QString(0x00C9));
        m_accentKeymap.insert(QString(0x00B4)+QString(0x49),QString(0x00CD));
        m_accentKeymap.insert(QString(0x00B4)+QString(0x4F),QString(0x00D3));
        m_accentKeymap.insert(QString(0x00B4)+QString(0x55),QString(0x00DA));
        m_accentKeymap.insert(QString(0x00B4)+QString(0x59),QString(0x00DD));
    }

    void addGraveAccentKeysForHID()
    {
        m_accentKeymap.insert(QString(0x60)+QString(0x61),QString(0xE0));
        m_accentKeymap.insert(QString(0x60)+QString(0x65),QString(0xE8));
        m_accentKeymap.insert(QString(0x60)+QString(0x69),QString(0xEC));
        m_accentKeymap.insert(QString(0x60)+QString(0x6F),QString(0xF2));
        m_accentKeymap.insert(QString(0x60)+QString(0x75),QString(0xF9));
        m_accentKeymap.insert(QString(0x60)+QString(0x41),QString(0xC0));
        m_accentKeymap.insert(QString(0x60)+QString(0x45),QString(0xC8));
        m_accentKeymap.insert(QString(0x60)+QString(0x49),QString(0xCC));
        m_accentKeymap.insert(QString(0x60)+QString(0x4F),QString(0xD2));
        m_accentKeymap.insert(QString(0x60)+QString(0x55),QString(0xD9));
    }

    void addTildeAccentKeysForHID()
    {
        m_accentKeymap.insert(QString(0x007E)+QString(0x61),QString(0x00E3));
        m_accentKeymap.insert(QString(0x007E)+QString(0x6E),QString(0x00F1));
        m_accentKeymap.insert(QString(0x007E)+QString(0x6F),QString(0x00F5));
        m_accentKeymap.insert(QString(0x007E)+QString(0x41),QString(0x00C3));
        m_accentKeymap.insert(QString(0x007E)+QString(0x4E),QString(0x00D1));
        m_accentKeymap.insert(QString(0x007E)+QString(0x4F),QString(0x00D5));
    }

    void addDiaresisAccentForHID()
    {
        m_accentKeymap.insert(QString(0x00A8)+QString(0x61),QString(0x00E4));
        m_accentKeymap.insert(QString(0x00A8)+QString(0x65),QString(0x00EB));
        m_accentKeymap.insert(QString(0x00A8)+QString(0x69),QString(0x00EF));
        m_accentKeymap.insert(QString(0x00A8)+QString(0x6F),QString(0x00F6));
        m_accentKeymap.insert(QString(0x00A8)+QString(0x75),QString(0x00FC));
        m_accentKeymap.insert(QString(0x00A8)+QString(0x79),QString(0x00FF));
        m_accentKeymap.insert(QString(0x00A8)+QString(0x41),QString(0x00C4));
        m_accentKeymap.insert(QString(0x00A8)+QString(0x45),QString(0x00CB));
        m_accentKeymap.insert(QString(0x00A8)+QString(0x49),QString(0x00CF));
        m_accentKeymap.insert(QString(0x00A8)+QString(0x4F),QString(0x00D6));
        m_accentKeymap.insert(QString(0x00A8)+QString(0x55),QString(0x00DC));
        m_accentKeymap.insert(QString(0x00A8)+QString(0x59),QString(0x0178));
    }

    void addCircumflexAccentForHID()
    {
        m_accentKeymap.insert(QString(0x5E)+QString(0x61),QString(0xE2));
        m_accentKeymap.insert(QString(0x5E)+QString(0x65),QString(0xEA));
        m_accentKeymap.insert(QString(0x5E)+QString(0x69),QString(0xEE));
        m_accentKeymap.insert(QString(0x5E)+QString(0x6F),QString(0xF4));
        m_accentKeymap.insert(QString(0x5E)+QString(0x75),QString(0xFB));
        m_accentKeymap.insert(QString(0x5E)+QString(0x41),QString(0xC2));
        m_accentKeymap.insert(QString(0x5E)+QString(0x45),QString(0xCA));
        m_accentKeymap.insert(QString(0x5E)+QString(0x49),QString(0xCE));
        m_accentKeymap.insert(QString(0x5E)+QString(0x4F),QString(0xD4));
        m_accentKeymap.insert(QString(0x5E)+QString(0x55),QString(0xDB));
    }
};
#endif // SWEDISH_AUTOMATA_H
