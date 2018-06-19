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

#ifndef FRENCH_AUTOMATA_H
#define FRENCH_AUTOMATA_H

#include "automatabase.h"
#include <QLocale>

class FrenchAutomata : public AutomataBase
{

public:
    FrenchAutomata()
    {
        m_accents.insert(QString(0x005E));
        m_accents.insert(QString(0x0060));
        m_accents.insert(QString(0x00A8));
        m_accents.insert(QString(0x00AB));
        m_accents.insert(QString(0x007E));

        m_accentSelect = false;
        addSymbolKeys();
        addNumberKeys();
        addShiftKeys();
        addNormalKeys();
        addAccentKeys();
        addAltKeysForHID();

        addCircumflexAccentForHID();
        addGraveAccentForHID();
        addCedillaAccentForHID();
        addDiaresisAccentForHID();
        addTildeAccentForHID();
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
        return new FrenchAutomata();
    }

private:
    void addSymbolKeys()
    {
        m_keymap.insert(0x21,QString(0x31));
        m_keymap.insert(0x22,QString(0x25));
        m_keymap.insert(0x23,QString(0x33));
        m_keymap.insert(0x24,QString(0x34));
        m_keymap.insert(0x25,QString(0x35));
        m_keymap.insert(0x26,QString(0x37));
        m_keymap.insert(0x27,QString(0x00F9));
        m_keymap.insert(0x28,QString(0x39));
        m_keymap.insert(0x29,QString(0x30));
        m_keymap.insert(0x2a,QString(0x38));
        m_keymap.insert(0x2b,QString(0x2b));
        m_keymap.insert(0x2c,QString(0x3B));
        m_keymap.insert(0x2d,QString(0x29));
        m_keymap.insert(0x2e,QString(0x3A));
        m_keymap.insert(0x2f,QString(0x21));
    }

    void addNumberKeys()
    {
        m_keymap.insert(0x30,QString(0x00E0));
        m_keymap.insert(0x31,QString(0x26));
        m_keymap.insert(0x32,QString(0x00E9));
        m_keymap.insert(0x33,QString(0x22));
        m_keymap.insert(0x34,QString(0x27));
        m_keymap.insert(0x35,QString(0x28));
        m_keymap.insert(0x36,QString(0x2D));
        m_keymap.insert(0x37,QString(0x00E8));
        m_keymap.insert(0x38,QString(0x5F));
        m_keymap.insert(0x39,QString(0x00E7));
    }

    void addShiftKeys()
    {
        m_keymap.insert(0x3a,QString(0x4D));
        m_keymap.insert(0x3c,QString(0x2E));
        m_keymap.insert(0x3d,QString(0x3d));
        m_keymap.insert(0x3e,QString(0x2F));
        m_keymap.insert(0x3f,QString(0xA7));
        m_keymap.insert(0x40,QString(0x32));
        m_keymap.insert(0x41,QString(0x51));
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
        m_keymap.insert(0x4d,QString(0x3F));
        m_keymap.insert(0x4e,QString(0x4e));
        m_keymap.insert(0x4f,QString(0x4f));
        m_keymap.insert(0x50,QString(0x50));
        m_keymap.insert(0x51,QString(0x41));
        m_keymap.insert(0x52,QString(0x52));
        m_keymap.insert(0x53,QString(0x53));
        m_keymap.insert(0x54,QString(0x54));
        m_keymap.insert(0x55,QString(0x55));
        m_keymap.insert(0x56,QString(0x56));
        m_keymap.insert(0x57,QString(0x5A));
        m_keymap.insert(0x58,QString(0x58));
        m_keymap.insert(0x59,QString(0x59));
        m_keymap.insert(0x5a,QString(0x57));
        m_keymap.insert(0x5b,QString(0x005E));
        m_keymap.insert(0x5c,QString(0x2A));
        m_keymap.insert(0x5d,QString(0x24));
        m_keymap.insert(0x5e,QString(0x36));
        m_keymap.insert(0x5f,QString(0x00B0));
        m_keymap.insert(0x7a,QString(0x77));
        m_keymap.insert(0x7b,QString(0x00A8));
        m_keymap.insert(0x7c,QString(0xB5));
        m_keymap.insert(0x7d,QString(0x00A3));
        m_keymap.insert(0x7e,QString(0x7e));
    }

    void addNormalKeys()
    {
        m_keymap.insert(0x3b,QString(0x6D));
        m_keymap.insert(0x60,QString(0x00B2));
        m_keymap.insert(0x61,QString(0x71));
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
        m_keymap.insert(0x6d,QString(0x2C));
        m_keymap.insert(0x6e,QString(0x6e));
        m_keymap.insert(0x6f,QString(0x6f));
        m_keymap.insert(0x70,QString(0x70));
        m_keymap.insert(0x71,QString(0x61));
        m_keymap.insert(0x72,QString(0x72));
        m_keymap.insert(0x73,QString(0x73));
        m_keymap.insert(0x74,QString(0x74));
        m_keymap.insert(0x75,QString(0x75));
        m_keymap.insert(0x76,QString(0x76));
        m_keymap.insert(0x77,QString(0x7A));
        m_keymap.insert(0x78,QString(0x78));
        m_keymap.insert(0x79,QString(0x79));
        m_keymap.insert(0x20,QString(0x20));
    }

    void addAccentKeys()
    {
        m_keymap.insert(0xe2,QString(0xe2));
        m_keymap.insert(0xe0,QString(0xe0));
        m_keymap.insert(0xe6,QString(0xe6));
        m_keymap.insert(0xe7,QString(0xe7));
        m_keymap.insert(0xe8,QString(0xe8));
        m_keymap.insert(0xea,QString(0xea));
        m_keymap.insert(0xe9,QString(0xe9));
        m_keymap.insert(0xeb,QString(0xeb));
        m_keymap.insert(0xee,QString(0xee));
        m_keymap.insert(0xef,QString(0xef));
        m_keymap.insert(0xf4,QString(0xf4));
        m_keymap.insert(0x13bd,QString(0x153));
        m_keymap.insert(0xf9,QString(0xf9));
        m_keymap.insert(0xfb,QString(0xfb));
        m_keymap.insert(0xc2,QString(0xc2));
        m_keymap.insert(0xc0,QString(0xc0));
        m_keymap.insert(0xc6,QString(0xc6));
        m_keymap.insert(0xc7,QString(0xc7));
        m_keymap.insert(0xc8,QString(0xc8));
        m_keymap.insert(0xca,QString(0xca));
        m_keymap.insert(0xc9,QString(0xc9));
        m_keymap.insert(0xcb,QString(0xcb));
        m_keymap.insert(0xce,QString(0xce));
        m_keymap.insert(0xcf,QString(0xcf));
        m_keymap.insert(0xd4,QString(0xd4));
        m_keymap.insert(0x13bc,QString(0x152));
        m_keymap.insert(0xd9,QString(0xd9));
        m_keymap.insert(0xdb,QString(0xdb));
    }

    void addCircumflexAccentForHID()
    {
        m_accentKeymap.insert(QString(0x005E)+QString(0x61),QString(0x00E2));
        m_accentKeymap.insert(QString(0x005E)+QString(0x65),QString(0x00EA));
        m_accentKeymap.insert(QString(0x005E)+QString(0x75),QString(0x00FB));
        m_accentKeymap.insert(QString(0x005E)+QString(0x69),QString(0x00EE));
        m_accentKeymap.insert(QString(0x005E)+QString(0x6F),QString(0x00F4));
        m_accentKeymap.insert(QString(0x005E)+QString(0x41),QString(0x00C2));
        m_accentKeymap.insert(QString(0x005E)+QString(0x45),QString(0x00CA));
        m_accentKeymap.insert(QString(0x005E)+QString(0x55),QString(0x00DB));
        m_accentKeymap.insert(QString(0x005E)+QString(0x49),QString(0x00CE));
        m_accentKeymap.insert(QString(0x005E)+QString(0x4F),QString(0x00D4));
    }

    void addGraveAccentForHID()
    {
        m_accentKeymap.insert(QString(0x0060)+QString(0x61),QString(0x00E0));
        m_accentKeymap.insert(QString(0x0060)+QString(0x65),QString(0x00E8));
        m_accentKeymap.insert(QString(0x0060)+QString(0x75),QString(0x00F9));
        m_accentKeymap.insert(QString(0x0060)+QString(0x69),QString(0x00EC));
        m_accentKeymap.insert(QString(0x0060)+QString(0x6F),QString(0x00F2));
        m_accentKeymap.insert(QString(0x0060)+QString(0x41),QString(0x00C0));
        m_accentKeymap.insert(QString(0x0060)+QString(0x45),QString(0x00C8));
        m_accentKeymap.insert(QString(0x0060)+QString(0x55),QString(0x00D9));
        m_accentKeymap.insert(QString(0x0060)+QString(0x49),QString(0x00CC));
        m_accentKeymap.insert(QString(0x0060)+QString(0x4F),QString(0x00D2));
    }

    void addCedillaAccentForHID()
    {
        m_accentKeymap.insert(QString(0x00AB)+QString(0x63),QString(0x00E7));
        m_accentKeymap.insert(QString(0x00AB)+QString(0x43),QString(0x00C7));
    }

    void addDiaresisAccentForHID()
    {
        m_accentKeymap.insert(QString(0x00A8)+QString(0x61),QString(0x00E4));
        m_accentKeymap.insert(QString(0x00A8)+QString(0x65),QString(0x00EB));
        m_accentKeymap.insert(QString(0x00A8)+QString(0x79),QString(0x00FF));
        m_accentKeymap.insert(QString(0x00A8)+QString(0x75),QString(0x00FC));
        m_accentKeymap.insert(QString(0x00A8)+QString(0x69),QString(0x00EF));
        m_accentKeymap.insert(QString(0x00A8)+QString(0x6F),QString(0x00F6));
        m_accentKeymap.insert(QString(0x00A8)+QString(0x41),QString(0x00C4));
        m_accentKeymap.insert(QString(0x00A8)+QString(0x45),QString(0x00CB));
        m_accentKeymap.insert(QString(0x00A8)+QString(0x55),QString(0x00DC));
        m_accentKeymap.insert(QString(0x00A8)+QString(0x49),QString(0x00CF));
        m_accentKeymap.insert(QString(0x00A8)+QString(0x4F),QString(0x00D6));
    }

    void addTildeAccentForHID()
    {
        m_accentKeymap.insert(QString(0x007E)+QString(0x61),QString(0x00E3));
        m_accentKeymap.insert(QString(0x007E)+QString(0x6F),QString(0x00F5));
        m_accentKeymap.insert(QString(0x007E)+QString(0x6E),QString(0x00F1));
        m_accentKeymap.insert(QString(0x007E)+QString(0x41),QString(0x00C3));
        m_accentKeymap.insert(QString(0x007E)+QString(0x4F),QString(0x00D5));
        m_accentKeymap.insert(QString(0x007E)+QString(0x4E),QString(0x00D1));
    }

    void addAltKeysForHID()
    {
        m_keymap.insert(0xAB,QString(0x00AB));
        m_keymap.insert(0xB8,QString(0x00E6));
        m_keymap.insert(0xB7,QString(0x00A4));
        m_keymap.insert(0xA1,QString(0x007E));
        m_keymap.insert(0xA2,QString(0x23));
        m_keymap.insert(0xA3,QString(0x7B));
        m_keymap.insert(0xA4,QString(0x5B));
        m_keymap.insert(0xA5,QString(0x7C));
        m_keymap.insert(0xA6,QString(0x0060));
        m_keymap.insert(0xA7,QString(0x5C));
        m_keymap.insert(0xA8,QString(0x5E));
        m_keymap.insert(0xA9,QString(0x40));
        m_keymap.insert(0xAA,QString(0x5D));
        m_keymap.insert(0xAB,QString(0x7D));
        m_keymap.insert(0xAE,QString(0x20AC));
        m_keymap.insert(0xF2,QString(0x00C6));
    }
};

#endif // FRENCH_AUTOMATA_H
