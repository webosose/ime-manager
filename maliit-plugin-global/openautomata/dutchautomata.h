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

#ifndef DUTCH_AUTOMATA_H
#define DUTCH_AUTOMATA_H

#include "automatabase.h"
#include <QLocale>

class DutchAutomata : public AutomataBase
{

public:
    DutchAutomata()
    {
        m_accentSelect = false;

        m_accents.insert(QString(QChar(0x00B4)));
        m_accents.insert(QString(QChar(0x0060)));
        m_accents.insert(QString(QChar(0x00A8)));
        m_accents.insert(QString(QChar(0x005E)));
        m_accents.insert(QString(QChar(0x007E)));
        m_accents.insert(QString(QChar(0x00B8)));

        addSymbolKeys();
        addNumberKeys();
        addShiftKeys();
        addNormalKeys();
        addAccentKeys();
        addAltKeysForHID();
        addShiftedAltKeysForHID();

        addAcuteAccentForHID();
        addGraveAccentForHID();
        addDiaresisAccentForHID();
        addCircumflexAccentForHID();
        addTildeAccentForHID();
        addCedillaAccentForHID();
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
        return new DutchAutomata();
    }
private:
    void addSymbolKeys()
    {
        m_keymap.insert(0x22,QString(QChar(0x60)));
        m_keymap.insert(0x21,QString(QChar(0x21)));
        m_keymap.insert(0x23,QString(QChar(0x23)));
        m_keymap.insert(0x24,QString(QChar(0x24)));
        m_keymap.insert(0x25,QString(QChar(0x25)));
        m_keymap.insert(0x26,QString(QChar(0x26)));
        m_keymap.insert(0x27,QString(QChar(0xB4)));
        m_keymap.insert(0x28,QString(QChar(0x28)));
        m_keymap.insert(0x29,QString(QChar(0x29)));
        m_keymap.insert(0x2a,QString(QChar(0x2a)));
        m_keymap.insert(0x2b,QString(QChar(0x7E)));
        m_keymap.insert(0x2c,QString(QChar(0x2c)));
        m_keymap.insert(0x2d,QString(QChar(0x2d)));
        m_keymap.insert(0x2e,QString(QChar(0x2e)));
        m_keymap.insert(0x2f,QString(QChar(0x2f)));
    }

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

    void addShiftKeys()
    {
        m_keymap.insert(0x3a,QString(QChar(0x3a)));
        m_keymap.insert(0x3b,QString(QChar(0x3b)));
        m_keymap.insert(0x3c,QString(QChar(0x3c)));
        m_keymap.insert(0x3d,QString(QChar(0x3d)));
        m_keymap.insert(0x3e,QString(QChar(0x3e)));
        m_keymap.insert(0x3f,QString(QChar(0x3f)));
        m_keymap.insert(0x40,QString(QChar(0x40)));
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
        m_keymap.insert(0x5b,QString(QChar(0xA8)));
        m_keymap.insert(0x5c,QString(QChar(0x5c)));
        m_keymap.insert(0x5d,QString(QChar(0x5d)));
        m_keymap.insert(0x5e,QString(QChar(0x5e)));
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
        m_keymap.insert(0x7b,QString(QChar(0x5E)));
        m_keymap.insert(0x7c,QString(QChar(0x7c)));
        m_keymap.insert(0x7d,QString(QChar(0x7d)));
        m_keymap.insert(0x7e,QString(QChar(0x7e)));
        m_keymap.insert(0x20,QString(QChar(0x20)));
    }

    void addAccentKeys()
    {
        m_keymap.insert(0xe11,QString(QChar(0xe1)));
        m_keymap.insert(0xe01,QString(QChar(0xe0)));
        m_keymap.insert(0xe41,QString(QChar(0xe4)));
        m_keymap.insert(0xe21,QString(QChar(0xe2)));
        m_keymap.insert(0xe31,QString(QChar(0xe3)));
        m_keymap.insert(0xe71,QString(QChar(0xe7)));
        m_keymap.insert(0xe91,QString(QChar(0xe9)));
        m_keymap.insert(0xe81,QString(QChar(0xe8)));
        m_keymap.insert(0xeb1,QString(QChar(0xeb)));
        m_keymap.insert(0xea1,QString(QChar(0xea)));
        m_keymap.insert(0xed1,QString(QChar(0xed)));
        m_keymap.insert(0xec1,QString(QChar(0xec)));
        m_keymap.insert(0xef1,QString(QChar(0xef)));
        m_keymap.insert(0xee1,QString(QChar(0xee)));
        m_keymap.insert(0xf11,QString(QChar(0xf1)));
        m_keymap.insert(0xf31,QString(QChar(0xf3)));
        m_keymap.insert(0xf21,QString(QChar(0xf2)));
        m_keymap.insert(0xf61,QString(QChar(0xf6)));
        m_keymap.insert(0xf41,QString(QChar(0xf4)));
        m_keymap.insert(0xf51,QString(QChar(0xf5)));
        m_keymap.insert(0xfa1,QString(QChar(0xfa)));
        m_keymap.insert(0xf91,QString(QChar(0xf9)));
        m_keymap.insert(0xfc1,QString(QChar(0xfc)));
        m_keymap.insert(0xfb1,QString(QChar(0xfb)));
        m_keymap.insert(0xc11,QString(QChar(0xc1)));
        m_keymap.insert(0xc01,QString(QChar(0xc0)));
        m_keymap.insert(0xc41,QString(QChar(0xc4)));
        m_keymap.insert(0xc21,QString(QChar(0xc2)));
        m_keymap.insert(0xc31,QString(QChar(0xc3)));
        m_keymap.insert(0xc71,QString(QChar(0xc7)));
        m_keymap.insert(0xc91,QString(QChar(0xc9)));
        m_keymap.insert(0xc81,QString(QChar(0xc8)));
        m_keymap.insert(0xcb1,QString(QChar(0xcb)));
        m_keymap.insert(0xca1,QString(QChar(0xca)));
        m_keymap.insert(0xcd1,QString(QChar(0xcd)));
        m_keymap.insert(0xcc1,QString(QChar(0xcc)));
        m_keymap.insert(0xcf1,QString(QChar(0xcf)));
        m_keymap.insert(0xce1,QString(QChar(0xce)));
        m_keymap.insert(0xd11,QString(QChar(0xd1)));
        m_keymap.insert(0xd31,QString(QChar(0xd3)));
        m_keymap.insert(0xd21,QString(QChar(0xd2)));
        m_keymap.insert(0xd61,QString(QChar(0xd6)));
        m_keymap.insert(0xd41,QString(QChar(0xd4)));
        m_keymap.insert(0xd51,QString(QChar(0xd5)));
        m_keymap.insert(0xda1,QString(QChar(0xda)));
        m_keymap.insert(0xd91,QString(QChar(0xd9)));
        m_keymap.insert(0xdc1,QString(QChar(0xdc)));
        m_keymap.insert(0xdb1,QString(QChar(0xdb)));
        m_keymap.insert(0x201,QString(QChar(0x20)));
    }

    void addAcuteAccentForHID()
    {
        m_accentKeymap.insert(QString(QChar(0x00B4))+QString(QChar(0x61)),QString(QChar(0x00E1)));
        m_accentKeymap.insert(QString(QChar(0x00B4))+QString(QChar(0x65)),QString(QChar(0x00E9)));
        m_accentKeymap.insert(QString(QChar(0x00B4))+QString(QChar(0x79)),QString(QChar(0x00FD)));
        m_accentKeymap.insert(QString(QChar(0x00B4))+QString(QChar(0x75)),QString(QChar(0x00FA)));
        m_accentKeymap.insert(QString(QChar(0x00B4))+QString(QChar(0x69)),QString(QChar(0x00ED)));
        m_accentKeymap.insert(QString(QChar(0x00B4))+QString(QChar(0x6F)),QString(QChar(0x00F3)));
        m_accentKeymap.insert(QString(QChar(0x00B4))+QString(QChar(0x41)),QString(QChar(0x00C1)));
        m_accentKeymap.insert(QString(QChar(0x00B4))+QString(QChar(0x45)),QString(QChar(0x00C9)));
        m_accentKeymap.insert(QString(QChar(0x00B4))+QString(QChar(0x59)),QString(QChar(0x00DD)));
        m_accentKeymap.insert(QString(QChar(0x00B4))+QString(QChar(0x55)),QString(QChar(0x00DA)));
        m_accentKeymap.insert(QString(QChar(0x00B4))+QString(QChar(0x49)),QString(QChar(0x00CD)));
        m_accentKeymap.insert(QString(QChar(0x00B4))+QString(QChar(0x4F)),QString(QChar(0x00D3)));
    }

    void addGraveAccentForHID()
    {
        m_accentKeymap.insert(QString(QChar(0x0060))+QString(QChar(0x61)),QString(QChar(0x00E0)));
        m_accentKeymap.insert(QString(QChar(0x0060))+QString(QChar(0x65)),QString(QChar(0x00E8)));
        m_accentKeymap.insert(QString(QChar(0x0060))+QString(QChar(0x75)),QString(QChar(0x00F9)));
        m_accentKeymap.insert(QString(QChar(0x0060))+QString(QChar(0x69)),QString(QChar(0x00EC)));
        m_accentKeymap.insert(QString(QChar(0x0060))+QString(QChar(0x6F)),QString(QChar(0x00F2)));
        m_accentKeymap.insert(QString(QChar(0x0060))+QString(QChar(0x41)),QString(QChar(0x00C0)));
        m_accentKeymap.insert(QString(QChar(0x0060))+QString(QChar(0x45)),QString(QChar(0x00C8)));
        m_accentKeymap.insert(QString(QChar(0x0060))+QString(QChar(0x55)),QString(QChar(0x00D9)));
        m_accentKeymap.insert(QString(QChar(0x0060))+QString(QChar(0x49)),QString(QChar(0x00CC)));
        m_accentKeymap.insert(QString(QChar(0x0060))+QString(QChar(0x4F)),QString(QChar(0x00D2)));
    }

    void addDiaresisAccentForHID()
    {
        m_accentKeymap.insert(QString(QChar(0x00A8))+QString(QChar(0x61)),QString(QChar(0x00E4)));
        m_accentKeymap.insert(QString(QChar(0x00A8))+QString(QChar(0x65)),QString(QChar(0x00EB)));
        m_accentKeymap.insert(QString(QChar(0x00A8))+QString(QChar(0x79)),QString(QChar(0x00FF)));
        m_accentKeymap.insert(QString(QChar(0x00A8))+QString(QChar(0x75)),QString(QChar(0x00FC)));
        m_accentKeymap.insert(QString(QChar(0x00A8))+QString(QChar(0x69)),QString(QChar(0x00EF)));
        m_accentKeymap.insert(QString(QChar(0x00A8))+QString(QChar(0x6F)),QString(QChar(0x00F6)));
        m_accentKeymap.insert(QString(QChar(0x00A8))+QString(QChar(0x41)),QString(QChar(0x00C4)));
        m_accentKeymap.insert(QString(QChar(0x00A8))+QString(QChar(0x45)),QString(QChar(0x00CB)));
        m_accentKeymap.insert(QString(QChar(0x00A8))+QString(QChar(0x55)),QString(QChar(0x00DC)));
        m_accentKeymap.insert(QString(QChar(0x00A8))+QString(QChar(0x49)),QString(QChar(0x00CF)));
        m_accentKeymap.insert(QString(QChar(0x00A8))+QString(QChar(0x4F)),QString(QChar(0x00D6)));
    }

    void addCircumflexAccentForHID()
    {
        m_accentKeymap.insert(QString(QChar(0x005E))+QString(QChar(0x61)),QString(QChar(0x00E2)));
        m_accentKeymap.insert(QString(QChar(0x005E))+QString(QChar(0x65)),QString(QChar(0x00EA)));
        m_accentKeymap.insert(QString(QChar(0x005E))+QString(QChar(0x75)),QString(QChar(0x00FB)));
        m_accentKeymap.insert(QString(QChar(0x005E))+QString(QChar(0x69)),QString(QChar(0x00EE)));
        m_accentKeymap.insert(QString(QChar(0x005E))+QString(QChar(0x6F)),QString(QChar(0x00F4)));
        m_accentKeymap.insert(QString(QChar(0x005E))+QString(QChar(0x41)),QString(QChar(0x00C2)));
        m_accentKeymap.insert(QString(QChar(0x005E))+QString(QChar(0x45)),QString(QChar(0x00CA)));
        m_accentKeymap.insert(QString(QChar(0x005E))+QString(QChar(0x55)),QString(QChar(0x00DB)));
        m_accentKeymap.insert(QString(QChar(0x005E))+QString(QChar(0x49)),QString(QChar(0x00CE)));
        m_accentKeymap.insert(QString(QChar(0x005E))+QString(QChar(0x4F)),QString(QChar(0x00D4)));
    }

    void addTildeAccentForHID()
    {
        m_accentKeymap.insert(QString(QChar(0x007E))+QString(QChar(0x61)),QString(QChar(0x00E3)));
        m_accentKeymap.insert(QString(QChar(0x007E))+QString(QChar(0x6F)),QString(QChar(0x00F5)));
        m_accentKeymap.insert(QString(QChar(0x007E))+QString(QChar(0x6E)),QString(QChar(0x00F1)));
        m_accentKeymap.insert(QString(QChar(0x007E))+QString(QChar(0x41)),QString(QChar(0x00C3)));
        m_accentKeymap.insert(QString(QChar(0x007E))+QString(QChar(0x4F)),QString(QChar(0x00D5)));
        m_accentKeymap.insert(QString(QChar(0x007E))+QString(QChar(0x4E)),QString(QChar(0x00D1)));
    }

    void addCedillaAccentForHID()
    {
        m_accentKeymap.insert(QString(QChar(0x00B8))+QString(QChar(0x63)),QString(QChar(0x00E7)));
        m_accentKeymap.insert(QString(QChar(0x00B8))+QString(QChar(0x43)),QString(QChar(0x00C7)));
    }

    void addAltKeysForHID()
    {
        m_keymap.insert(0xC3,QString(QChar(0x00AC)));
        m_keymap.insert(0xA0,QString(QChar(0x00B9)));
        m_keymap.insert(0xA1,QString(QChar(0x00B2)));
        m_keymap.insert(0xA2,QString(QChar(0x00B3)));
        m_keymap.insert(0xA3,QString(QChar(0x00BC)));
        m_keymap.insert(0xA4,QString(QChar(0x00BD)));
        m_keymap.insert(0xA5,QString(QChar(0x00BE)));
        m_keymap.insert(0xA6,QString(QChar(0x00A3)));
        m_keymap.insert(0xA7,QString(QChar(0x007B)));
        m_keymap.insert(0xA8,QString(QChar(0x007D)));
        m_keymap.insert(0xAA,QString(QChar(0x005C)));
        m_keymap.insert(0xAB,QString(QChar(0x00B8)));
        m_keymap.insert(0xAE,QString(QChar(0x20AC)));
        m_keymap.insert(0xAF,QString(QChar(0x00B6)));
        m_keymap.insert(0xB9,QString(QChar(0x00DF)));
        m_keymap.insert(0xC5,QString(QChar(0x00AB)));
        m_keymap.insert(0xC6,QString(QChar(0x00BB)));
        m_keymap.insert(0xC7,QString(QChar(0x00A2)));
        m_keymap.insert(0xCB,QString(QChar(0x00B5)));
        m_keymap.insert(0xCD,QString(QChar(0x00B7)));
    }

    void addShiftedAltKeysForHID()
    {
        m_keymap.insert(0xF3,QString("SS"));
        m_keymap.insert(0x105,QString(QChar(0x4D)));
    }
};

#endif // DUTCH_AUTOMATA_H
