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

#ifndef DANISH_AUTOMATA_H
#define DANISH_AUTOMATA_H

#include "automatabase.h"
#include <QLocale>

class DanishAutomata : public AutomataBase
{

public:
    DanishAutomata()
    {
        m_accentSelect = false;
        m_accents.insert(QString(QChar(0x00B4)));
        m_accents.insert(QString(QChar(0x0060)));
        m_accents.insert(QString(QChar(0x00A8)));
        m_accents.insert(QString(QChar(0x005E)));
        m_accents.insert(QString(QChar(0x007E)));

        addNumberKeys();
        addSymbolKeys();
        addNormalKeys();
        addShiftedKeys();
        addAltKeysForHID();
        addAcuteAccentForHID();
        addGraveAccentKeysForHID();
        addDiaeresisAccentForHID();
        addCircumFlexAccentKeysForHID();
        addTildeAccentKeysForHID();
        addAccentKeysForVKB();
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
        return new DanishAutomata();
    }

private:
    void addNumberKeys()
    {
        m_keymap.insert(0x30,QString(QChar(0x30)));
        m_keymap.insert(0x31,QString(QChar(0x31)));
        m_keymap.insert(0x32,QString(QChar(0x32)));
        m_keymap.insert(0x33,QString(QChar(0x33)));
        m_keymap.insert(0x34,QString(QChar(0x34)));
        m_keymap.insert(0x35,QString(QChar(0x35)));
        m_keymap.insert(0x36,QString(QChar(0x36)));
        m_keymap.insert(0x37,QString(QChar(0x37)));
        m_keymap.insert(0x38,QString(QChar(0x38)));
        m_keymap.insert(0x39,QString(QChar(0x39)));
    }

    void addSymbolKeys()
    {
        m_keymap.insert(0x60,QString(QChar(0xBD)));
        m_keymap.insert(0x3B,QString(QChar(0xE6)));
        m_keymap.insert(0x3A,QString(QChar(0xC6)));
        m_keymap.insert(0x27,QString(QChar(0xF8)));
        m_keymap.insert(0x22,QString(QChar(0xD8)));
        m_keymap.insert(0x5B,QString(QChar(0xE5)));
        m_keymap.insert(0x7B,QString(QChar(0xC5)));
        m_keymap.insert(0x7E,QString(QChar(0xA7)));
        m_keymap.insert(0x21,QString(QChar(0x21)));
        m_keymap.insert(0x40,QString(QChar(0x22)));
        m_keymap.insert(0x23,QString(QChar(0x23)));
        m_keymap.insert(0x24,QString(QChar(0xA4)));
        m_keymap.insert(0x25,QString(QChar(0x25)));
        m_keymap.insert(0x5E,QString(QChar(0x26)));
        m_keymap.insert(0x26,QString(QChar(0x2F)));
        m_keymap.insert(0x2A,QString(QChar(0x28)));
        m_keymap.insert(0x28,QString(QChar(0x29)));
        m_keymap.insert(0x29,QString(QChar(0x3D)));
        m_keymap.insert(0x5F,QString(QChar(0x3F)));
        m_keymap.insert(0x3D,QString(QChar(0xB4)));
        m_keymap.insert(0x2B,QString(QChar(0x60)));
        m_keymap.insert(0x5C,QString(QChar(0x27)));
        m_keymap.insert(0x7C,QString(QChar(0x2A)));
        m_keymap.insert(0x5D,QString(QChar(0xA8)));
        m_keymap.insert(0x7D,QString(QChar(0x5E)));
        m_keymap.insert(0x2C,QString(QChar(0x2C)));
        m_keymap.insert(0x3C,QString(QChar(0x3B)));
        m_keymap.insert(0x2E,QString(QChar(0x2E)));
        m_keymap.insert(0x3E,QString(QChar(0x3A)));
        m_keymap.insert(0x2F,QString(QChar(0x2D)));
        m_keymap.insert(0x3F,QString(QChar(0x5F)));
        m_keymap.insert(0x2D,QString(QChar(0x2B)));
    }

    void addNormalKeys()
    {
        m_keymap.insert(0x71,QString(QChar(0x71)));
        m_keymap.insert(0x77,QString(QChar(0x77)));
        m_keymap.insert(0x65,QString(QChar(0x65)));
        m_keymap.insert(0x72,QString(QChar(0x72)));
        m_keymap.insert(0x74,QString(QChar(0x74)));
        m_keymap.insert(0x79,QString(QChar(0x79)));
        m_keymap.insert(0x75,QString(QChar(0x75)));
        m_keymap.insert(0x69,QString(QChar(0x69)));
        m_keymap.insert(0x6F,QString(QChar(0x6F)));
        m_keymap.insert(0x70,QString(QChar(0x70)));
        m_keymap.insert(0X61,QString(QChar(0X61)));
        m_keymap.insert(0x73,QString(QChar(0x73)));
        m_keymap.insert(0x64,QString(QChar(0x64)));
        m_keymap.insert(0x66,QString(QChar(0x66)));
        m_keymap.insert(0x67,QString(QChar(0x67)));
        m_keymap.insert(0x68,QString(QChar(0x68)));
        m_keymap.insert(0x6A,QString(QChar(0x6A)));
        m_keymap.insert(0x6B,QString(QChar(0x6B)));
        m_keymap.insert(0x6C,QString(QChar(0x6C)));
        m_keymap.insert(0x7A,QString(QChar(0x7A)));
        m_keymap.insert(0x78,QString(QChar(0x78)));
        m_keymap.insert(0x63,QString(QChar(0x63)));
        m_keymap.insert(0x76,QString(QChar(0x76)));
        m_keymap.insert(0x62,QString(QChar(0x62)));
        m_keymap.insert(0x6E,QString(QChar(0x6E)));
        m_keymap.insert(0x6D,QString(QChar(0x6D)));
        m_keymap.insert(0x20,QString(QChar(0x20)));
    }

    void addShiftedKeys()
    {
        m_keymap.insert(0x51,QString(QChar(0x51)));
        m_keymap.insert(0x57,QString(QChar(0x57)));
        m_keymap.insert(0x45,QString(QChar(0x45)));
        m_keymap.insert(0x52,QString(QChar(0x52)));
        m_keymap.insert(0x54,QString(QChar(0x54)));
        m_keymap.insert(0x59,QString(QChar(0x59)));
        m_keymap.insert(0x55,QString(QChar(0x55)));
        m_keymap.insert(0x49,QString(QChar(0x49)));
        m_keymap.insert(0x4F,QString(QChar(0x4F)));
        m_keymap.insert(0x50,QString(QChar(0x50)));
        m_keymap.insert(0x41,QString(QChar(0x41)));
        m_keymap.insert(0x53,QString(QChar(0x53)));
        m_keymap.insert(0x44,QString(QChar(0x44)));
        m_keymap.insert(0x46,QString(QChar(0x46)));
        m_keymap.insert(0x47,QString(QChar(0x47)));
        m_keymap.insert(0x48,QString(QChar(0x48)));
        m_keymap.insert(0x4A,QString(QChar(0x4A)));
        m_keymap.insert(0x4B,QString(QChar(0x4B)));
        m_keymap.insert(0x4C,QString(QChar(0x4C)));
        m_keymap.insert(0x5A,QString(QChar(0x5A)));
        m_keymap.insert(0x58,QString(QChar(0x58)));
        m_keymap.insert(0x43,QString(QChar(0x43)));
        m_keymap.insert(0x56,QString(QChar(0x56)));
        m_keymap.insert(0x42,QString(QChar(0x42)));
        m_keymap.insert(0x4E,QString(QChar(0x4E)));
        m_keymap.insert(0x4D,QString(QChar(0x4D)));
    }

    void addAltKeysForHID()
    {
        m_keymap.insert(0xA1,QString(QChar(0x0040)));
        m_keymap.insert(0xA2,QString(QChar(0x00A3)));
        m_keymap.insert(0xA3,QString(QChar(0x0024)));
        m_keymap.insert(0xA4,QString(QChar(0x20AC)));
        m_keymap.insert(0xA6,QString(QChar(0x007B)));
        m_keymap.insert(0xA7,QString(QChar(0x005B)));
        m_keymap.insert(0xA8,QString(QChar(0x005D)));
        m_keymap.insert(0xA9,QString(QChar(0x007D)));
        m_keymap.insert(0xAB,QString(QChar(0x007C)));
        m_keymap.insert(0xAE,QString(QChar(0x20AC)));
        m_keymap.insert(0xB7,QString(QChar(0x007E)));
        m_keymap.insert(0xCB,QString(QChar(0x00B5)));
    }

    void addAcuteAccentForHID()
    {
        m_accentKeymap.insert(QString(QChar(0x00B4))+QString(QChar(0x61)),QString(QChar(0x00E1)));
        m_accentKeymap.insert(QString(QChar(0x00B4))+QString(QChar(0x65)),QString(QChar(0x00E9)));
        m_accentKeymap.insert(QString(QChar(0x00B4))+QString(QChar(0x69)),QString(QChar(0x00ED)));
        m_accentKeymap.insert(QString(QChar(0x00B4))+QString(QChar(0x6F)),QString(QChar(0x00F3)));
        m_accentKeymap.insert(QString(QChar(0x00B4))+QString(QChar(0x75)),QString(QChar(0x00FA)));
        m_accentKeymap.insert(QString(QChar(0x00B4))+QString(QChar(0x79)),QString(QChar(0x00FD)));
        m_accentKeymap.insert(QString(QChar(0x00B4))+QString(QChar(0x41)),QString(QChar(0x00C1)));
        m_accentKeymap.insert(QString(QChar(0x00B4))+QString(QChar(0x45)),QString(QChar(0x00C9)));
        m_accentKeymap.insert(QString(QChar(0x00B4))+QString(QChar(0x49)),QString(QChar(0x00CD)));
        m_accentKeymap.insert(QString(QChar(0x00B4))+QString(QChar(0x4F)),QString(QChar(0x00D3)));
        m_accentKeymap.insert(QString(QChar(0x00B4))+QString(QChar(0x55)),QString(QChar(0x00DA)));
        m_accentKeymap.insert(QString(QChar(0x00B4))+QString(QChar(0x59)),QString(QChar(0x00DD)));
    }

    void addGraveAccentKeysForHID()
    {
        m_accentKeymap.insert(QString(QChar(0x60))+QString(QChar(0x61)),QString(QChar(0xE0)));
        m_accentKeymap.insert(QString(QChar(0x60))+QString(QChar(0x65)),QString(QChar(0xE8)));
        m_accentKeymap.insert(QString(QChar(0x60))+QString(QChar(0x69)),QString(QChar(0xEC)));
        m_accentKeymap.insert(QString(QChar(0x60))+QString(QChar(0x6F)),QString(QChar(0xF2)));
        m_accentKeymap.insert(QString(QChar(0x60))+QString(QChar(0x75)),QString(QChar(0xF9)));
        m_accentKeymap.insert(QString(QChar(0x60))+QString(QChar(0x41)),QString(QChar(0xC0)));
        m_accentKeymap.insert(QString(QChar(0x60))+QString(QChar(0x45)),QString(QChar(0xC8)));
        m_accentKeymap.insert(QString(QChar(0x60))+QString(QChar(0x49)),QString(QChar(0xCC)));
        m_accentKeymap.insert(QString(QChar(0x60))+QString(QChar(0x4F)),QString(QChar(0xD2)));
        m_accentKeymap.insert(QString(QChar(0x60))+QString(QChar(0x55)),QString(QChar(0xD9)));
    }

    void addDiaeresisAccentForHID()
    {
        m_accentKeymap.insert(QString(QChar(0x00A8))+QString(QChar(0x61)),QString(QChar(0x00E4)));
        m_accentKeymap.insert(QString(QChar(0x00A8))+QString(QChar(0x65)),QString(QChar(0x00EB)));
        m_accentKeymap.insert(QString(QChar(0x00A8))+QString(QChar(0x69)),QString(QChar(0x00EF)));
        m_accentKeymap.insert(QString(QChar(0x00A8))+QString(QChar(0x6F)),QString(QChar(0x00F6)));
        m_accentKeymap.insert(QString(QChar(0x00A8))+QString(QChar(0x75)),QString(QChar(0x00FC)));
        m_accentKeymap.insert(QString(QChar(0x00A8))+QString(QChar(0x79)),QString(QChar(0x00FF)));
        m_accentKeymap.insert(QString(QChar(0x00A8))+QString(QChar(0x41)),QString(QChar(0x00C4)));
        m_accentKeymap.insert(QString(QChar(0x00A8))+QString(QChar(0x45)),QString(QChar(0x00CB)));
        m_accentKeymap.insert(QString(QChar(0x00A8))+QString(QChar(0x49)),QString(QChar(0x00CF)));
        m_accentKeymap.insert(QString(QChar(0x00A8))+QString(QChar(0x4F)),QString(QChar(0x00D6)));
        m_accentKeymap.insert(QString(QChar(0x00A8))+QString(QChar(0x55)),QString(QChar(0x00DC)));
        m_accentKeymap.insert(QString(QChar(0x00A8))+QString(QChar(0x59)),QString(QChar(0x0178)));
    }

    void addCircumFlexAccentKeysForHID()
    {
        m_accentKeymap.insert(QString(QChar(0x5E))+QString(QChar(0x61)),QString(QChar(0xE2)));
        m_accentKeymap.insert(QString(QChar(0x5E))+QString(QChar(0x65)),QString(QChar(0xEA)));
        m_accentKeymap.insert(QString(QChar(0x5E))+QString(QChar(0x69)),QString(QChar(0xEE)));
        m_accentKeymap.insert(QString(QChar(0x5E))+QString(QChar(0x6F)),QString(QChar(0xF4)));
        m_accentKeymap.insert(QString(QChar(0x5E))+QString(QChar(0x75)),QString(QChar(0xFB)));
        m_accentKeymap.insert(QString(QChar(0x5E))+QString(QChar(0x41)),QString(QChar(0xC2)));
        m_accentKeymap.insert(QString(QChar(0x5E))+QString(QChar(0x45)),QString(QChar(0xCA)));
        m_accentKeymap.insert(QString(QChar(0x5E))+QString(QChar(0x49)),QString(QChar(0xCE)));
        m_accentKeymap.insert(QString(QChar(0x5E))+QString(QChar(0x4F)),QString(QChar(0xD4)));
        m_accentKeymap.insert(QString(QChar(0x5E))+QString(QChar(0x55)),QString(QChar(0xDB)));
    }

    void addTildeAccentKeysForHID()
    {
        m_accentKeymap.insert(QString(QChar(0x007E))+QString(QChar(0x61)),QString(QChar(0x00E3)));
        m_accentKeymap.insert(QString(QChar(0x007E))+QString(QChar(0x6E)),QString(QChar(0x00F1)));
        m_accentKeymap.insert(QString(QChar(0x007E))+QString(QChar(0x6F)),QString(QChar(0x00F5)));
        m_accentKeymap.insert(QString(QChar(0x007E))+QString(QChar(0x41)),QString(QChar(0x00C3)));
        m_accentKeymap.insert(QString(QChar(0x007E))+QString(QChar(0x4E)),QString(QChar(0x00D1)));
        m_accentKeymap.insert(QString(QChar(0x007E))+QString(QChar(0x4F)),QString(QChar(0x00D5)));
    }

    void addAccentKeysForVKB()
    {
        m_keymap.insert(0xe2,QString(QChar(0xE2)));
        m_keymap.insert(0xe3,QString(QChar(0xe3)));
        m_keymap.insert(0xeb,QString(QChar(0xeb)));
        m_keymap.insert(0xea,QString(QChar(0xea)));
        m_keymap.insert(0xef,QString(QChar(0xef)));
        m_keymap.insert(0xee,QString(QChar(0xee)));
        m_keymap.insert(0xf1,QString(QChar(0xf1)));
        m_keymap.insert(0xf4,QString(QChar(0xf4)));
        m_keymap.insert(0xf5,QString(QChar(0xf5)));
        m_keymap.insert(0xfc,QString(QChar(0xfc)));
        m_keymap.insert(0xfb,QString(QChar(0xfb)));
        m_keymap.insert(0xff,QString(QChar(0xff)));
        m_keymap.insert(0xc2,QString(QChar(0xc2)));
        m_keymap.insert(0xc3,QString(QChar(0xc3)));
        m_keymap.insert(0xb5,QString(QChar(0xcb)));
        m_keymap.insert(0xca,QString(QChar(0xca)));
        m_keymap.insert(0xcf,QString(QChar(0xcf)));
        m_keymap.insert(0xce,QString(QChar(0xce)));
        m_keymap.insert(0xd1,QString(QChar(0xd1)));
        m_keymap.insert(0xd4,QString(QChar(0xd4)));
        m_keymap.insert(0xd5,QString(QChar(0xd5)));
        m_keymap.insert(0xdc,QString(QChar(0xdc)));
        m_keymap.insert(0xdb,QString(QChar(0xdb)));
        m_keymap.insert(0x13be,QString(QChar(0x178)));
    }
};

#endif // DANISH_AUTOMATA_H

