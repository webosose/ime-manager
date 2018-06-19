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

#ifndef HUNGARIAN_AUTOMATA_H
#define HUNGARIAN_AUTOMATA_H

#include "automatabase.h"
#include <QLocale>

class HungarianAutomata : public AutomataBase
{

public:
    HungarianAutomata()
    {
        m_accentSelect = false;
        m_accents.insert(QString(0x02C7));
        m_accents.insert(QString(0x005E));
        m_accents.insert(QString(0x02D8));
        m_accents.insert(QString(0x02DA));
        m_accents.insert(QString(0x02DB));
        m_accents.insert(QString(0x02D9));
        m_accents.insert(QString(0x00B4));
        m_accents.insert(QString(0x02DD));
        m_accents.insert(QString(0x00A8));
        m_accents.insert(QString(0x00B8));

        addCaronAccentForHID();
        addCircumFlexAccentForHID();
        addBreveAccentForHID();
        addRingAboveAccentForHID();
        addOGONEKAccentForHID();
        addDotAboveAccentForHID();
        addAcuteAccentForHID();
        addDoubleAcuteAccentForHID();
        addDiaeresisAccentForHID();
        addCedillaAccentForHID();
        addAltKeysForHID();

        addSymbolKeys();
        addNumberKeys();
        addShiftKeys();
        addNormalKeys();
        addAccentKeys();
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
        return new HungarianAutomata();
    }

private:

    void addSymbolKeys()
    {
        m_keymap.insert(0x21,QString(0x27));
        m_keymap.insert(0x22,QString(0xC1));
        m_keymap.insert(0x23,QString(0x2B));
        m_keymap.insert(0x24,QString(0x21));
        m_keymap.insert(0x25,QString(0x25));
        m_keymap.insert(0x26,QString(0x3D));
        m_keymap.insert(0x27,QString(0xE1));
        m_keymap.insert(0x28,QString(0x29));
        m_keymap.insert(0x29,QString(0xD6));
        m_keymap.insert(0x2a,QString(0x28));
        m_keymap.insert(0x2b,QString(0xD3));
        m_keymap.insert(0x2c,QString(0x2c));
        m_keymap.insert(0x2d,QString(0xFc));
        m_keymap.insert(0x2e,QString(0x2e));
        m_keymap.insert(0x2f,QString(0x2D));
    }

    void addNumberKeys()
    {
        m_keymap.insert(0x30,QString(0xF6));
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
        m_keymap.insert(0x3a,QString(0xC9));
        m_keymap.insert(0x3b,QString(0xE9));
        m_keymap.insert(0x3c,QString(0x3F));
        m_keymap.insert(0x3d,QString(0xF3));
        m_keymap.insert(0x3e,QString(0x3A));
        m_keymap.insert(0x3f,QString(0x5F));
        m_keymap.insert(0x40,QString(0x22));
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
        m_keymap.insert(0x59,QString(0x5A));
        m_keymap.insert(0x5a,QString(0x59));
        m_keymap.insert(0x5b,QString(0x151));
        m_keymap.insert(0x5c,QString(0x171));
        m_keymap.insert(0x5d,QString(0xFA));
        m_keymap.insert(0x5e,QString(0x2F));
        m_keymap.insert(0x5f,QString(0xDC));
    }

    void addNormalKeys()
    {
        m_keymap.insert(0x60,QString(0x30));
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
        m_keymap.insert(0x79,QString(0x7A));
        m_keymap.insert(0x7a,QString(0x79));
        m_keymap.insert(0x7b,QString(0x150));
        m_keymap.insert(0x7c,QString(0x170));
        m_keymap.insert(0x7d,QString(0xDA));
        m_keymap.insert(0x7e,QString(0xA7));
        m_keymap.insert(0x20,QString(0x20));
    }

    void addAccentKeys()
    {
        m_keymap.insert(0x00e1,QString(0xE1));
        m_keymap.insert(0x00e9,QString(0xe9));
        m_keymap.insert(0x00ed,QString(0xed));
        m_keymap.insert(0x00f3,QString(0xf3));
        m_keymap.insert(0x00f5,QString(0xf5));
        m_keymap.insert(0x00f6,QString(0xf6));
        m_keymap.insert(0x01f5,QString(0x151));
        m_keymap.insert(0x00fa,QString(0xfa));
        m_keymap.insert(0x00fc,QString(0xfc));
        m_keymap.insert(0x01fb,QString(0x171));
        m_keymap.insert(0x01c1,QString(0xc1));
        m_keymap.insert(0x003a,QString(0xc9));
        m_keymap.insert(0x00B3,QString(0xcd));
        m_keymap.insert(0x00d3,QString(0xd3));
        m_keymap.insert(0x00d5,QString(0xd5));
        m_keymap.insert(0x00d6,QString(0xd6));
        m_keymap.insert(0x01d5,QString(0x150));
        m_keymap.insert(0x00da,QString(0xda));
        m_keymap.insert(0x00dc,QString(0xdc));
        m_keymap.insert(0x01db,QString(0x170));
        m_keymap.insert(0x003F1,QString(0x3F));
        m_keymap.insert(0x00401,QString(0x40));
    }

    void addCaronAccentForHID()
    {
        m_accentKeymap.insert(QString(0x02C7)+QString(0x65),QString(0x011B));
        m_accentKeymap.insert(QString(0x02C7)+QString(0x45),QString(0x011A));
        m_accentKeymap.insert(QString(0x02C7)+QString(0x72),QString(0x0159));
        m_accentKeymap.insert(QString(0x02C7)+QString(0x52),QString(0x0158));
        m_accentKeymap.insert(QString(0x02C7)+QString(0x74),QString(0x0165));
        m_accentKeymap.insert(QString(0x02C7)+QString(0x54),QString(0x0164));
        m_accentKeymap.insert(QString(0x02C7)+QString(0x7A),QString(0x017E));
        m_accentKeymap.insert(QString(0x02C7)+QString(0x5A),QString(0x017D));
        m_accentKeymap.insert(QString(0x02C7)+QString(0x73),QString(0x0161));
        m_accentKeymap.insert(QString(0x02C7)+QString(0x53),QString(0x0160));
        m_accentKeymap.insert(QString(0x02C7)+QString(0x64),QString(0x010F));
        m_accentKeymap.insert(QString(0x02C7)+QString(0x44),QString(0x010E));
        m_accentKeymap.insert(QString(0x02C7)+QString(0x63),QString(0x010D));
        m_accentKeymap.insert(QString(0x02C7)+QString(0x43),QString(0x010C));
        m_accentKeymap.insert(QString(0x02C7)+QString(0x6E),QString(0x0148));
        m_accentKeymap.insert(QString(0x02C7)+QString(0x4E),QString(0x0147));
    }

    void addCircumFlexAccentForHID()
    {
        m_accentKeymap.insert(QString(0x005E)+QString(0x69),QString(0x00EE));
        m_accentKeymap.insert(QString(0x005E)+QString(0x49),QString(0x00CE));
        m_accentKeymap.insert(QString(0x005E)+QString(0x6F),QString(0x00F4));
        m_accentKeymap.insert(QString(0x005E)+QString(0x4F),QString(0x00D4));
        m_accentKeymap.insert(QString(0x005E)+QString(0x61),QString(0x00E2));
        m_accentKeymap.insert(QString(0x005E)+QString(0x41),QString(0x00C2));
    }

    void addBreveAccentForHID()
    {
        m_accentKeymap.insert(QString(0x02D8)+QString(0x61),QString(0x0103));
        m_accentKeymap.insert(QString(0x02D8)+QString(0x41),QString(0x0102));
    }

    void addRingAboveAccentForHID()
    {
        m_accentKeymap.insert(QString(0x02DA)+QString(0x75),QString(0x016F));
        m_accentKeymap.insert(QString(0x02DA)+QString(0x55),QString(0x016E));
    }

    void addOGONEKAccentForHID()
    {
        m_accentKeymap.insert(QString(0x02DB)+QString(0x61),QString(0x0105));
        m_accentKeymap.insert(QString(0x02DB)+QString(0x41),QString(0x0104));
        m_accentKeymap.insert(QString(0x02DB)+QString(0x65),QString(0x0119));
        m_accentKeymap.insert(QString(0x02DB)+QString(0x45),QString(0x0118));
    }

    void addDotAboveAccentForHID()
    {
        m_accentKeymap.insert(QString(0x02D9)+QString(0x7A),QString(0x017C));
        m_accentKeymap.insert(QString(0x02D9)+QString(0x5A),QString(0x017B));
    }

    void addAcuteAccentForHID()
    {
        m_accentKeymap.insert(QString(0x00B4)+QString(0x65),QString(0x00E9));
        m_accentKeymap.insert(QString(0x00B4)+QString(0x45),QString(0x00C9));
        m_accentKeymap.insert(QString(0x00B4)+QString(0x72),QString(0x0155));
        m_accentKeymap.insert(QString(0x00B4)+QString(0x52),QString(0x0154));
        m_accentKeymap.insert(QString(0x00B4)+QString(0x7A),QString(0x017A));
        m_accentKeymap.insert(QString(0x00B4)+QString(0x5A),QString(0x0179));
        m_accentKeymap.insert(QString(0x00B4)+QString(0x75),QString(0x00FA));
        m_accentKeymap.insert(QString(0x00B4)+QString(0x55),QString(0x00DA));
        m_accentKeymap.insert(QString(0x00B4)+QString(0x69),QString(0x00ED));
        m_accentKeymap.insert(QString(0x00B4)+QString(0x49),QString(0x00CD));
        m_accentKeymap.insert(QString(0x00B4)+QString(0x6F),QString(0x00F3));
        m_accentKeymap.insert(QString(0x00B4)+QString(0x4F),QString(0x00D3));
        m_accentKeymap.insert(QString(0x00B4)+QString(0x61),QString(0x00E1));
        m_accentKeymap.insert(QString(0x00B4)+QString(0x41),QString(0x00C1));
        m_accentKeymap.insert(QString(0x00B4)+QString(0x73),QString(0x015B));
        m_accentKeymap.insert(QString(0x00B4)+QString(0x53),QString(0x015A));
        m_accentKeymap.insert(QString(0x00B4)+QString(0x6C),QString(0x013A));
        m_accentKeymap.insert(QString(0x00B4)+QString(0x4C),QString(0x0139));
        m_accentKeymap.insert(QString(0x00B4)+QString(0x79),QString(0x00FD));
        m_accentKeymap.insert(QString(0x00B4)+QString(0x59),QString(0x00DD));
        m_accentKeymap.insert(QString(0x00B4)+QString(0x63),QString(0x0107));
        m_accentKeymap.insert(QString(0x00B4)+QString(0x43),QString(0x0106));
        m_accentKeymap.insert(QString(0x00B4)+QString(0x6E),QString(0x0144));
        m_accentKeymap.insert(QString(0x00B4)+QString(0x4E),QString(0x0143));
    }

    void addDoubleAcuteAccentForHID()
    {
        m_accentKeymap.insert(QString(0x02DD)+QString(0x75),QString(0x0171));
        m_accentKeymap.insert(QString(0x02DD)+QString(0x55),QString(0x0170));
        m_accentKeymap.insert(QString(0x02DD)+QString(0x6F),QString(0x0151));
        m_accentKeymap.insert(QString(0x02DD)+QString(0x4F),QString(0x0150));
    }

    void addDiaeresisAccentForHID()
    {
        m_accentKeymap.insert(QString(0x00A8)+QString(0x65),QString(0x00EB));
        m_accentKeymap.insert(QString(0x00A8)+QString(0x45),QString(0x00CB));
        m_accentKeymap.insert(QString(0x00A8)+QString(0x75),QString(0x00FC));
        m_accentKeymap.insert(QString(0x00A8)+QString(0x55),QString(0x00DC));
        m_accentKeymap.insert(QString(0x00A8)+QString(0x6F),QString(0x00F6));
        m_accentKeymap.insert(QString(0x00A8)+QString(0x4F),QString(0x00D6));
        m_accentKeymap.insert(QString(0x00A8)+QString(0x61),QString(0x00E4));
        m_accentKeymap.insert(QString(0x00A8)+QString(0x41),QString(0x00C4));
    }

    void addCedillaAccentForHID()
    {
        m_accentKeymap.insert(QString(0x00B8)+QString(0x74),QString(0x0163));
        m_accentKeymap.insert(QString(0x00B8)+QString(0x54),QString(0x0162));
        m_accentKeymap.insert(QString(0x00B8)+QString(0x73),QString(0x015F));
        m_accentKeymap.insert(QString(0x00B8)+QString(0x53),QString(0x015E));
        m_accentKeymap.insert(QString(0x00B8)+QString(0x63),QString(0x00E7));
        m_accentKeymap.insert(QString(0x00B8)+QString(0x43),QString(0x00C7));
    }

    void addAltKeysForHID()
    {
        m_keymap.insert(0xA0,QString(0x007E));
        m_keymap.insert(0xA1,QString(0x02C7));
        m_keymap.insert(0xA2,QString(0x005E));
        m_keymap.insert(0xA3,QString(0x02D8));
        m_keymap.insert(0xA4,QString(0x02DA));
        m_keymap.insert(0xA5,QString(0x02DB));
        m_keymap.insert(0xA6,QString(0x0060));
        m_keymap.insert(0xA7,QString(0x02D9));
        m_keymap.insert(0xA8,QString(0x00B4));
        m_keymap.insert(0xA9,QString(0x02DD));
        m_keymap.insert(0xAA,QString(0x00A8));
        m_keymap.insert(0xAB,QString(0x00B8));
        m_keymap.insert(0xC4,QString(0x00A4));
        m_keymap.insert(0xAC,QString(0x005C));
        m_keymap.insert(0xAD,QString(0x007C));
        m_keymap.insert(0xAE,QString(0x00C4));
        m_keymap.insert(0xB2,QString(0x20AC));
        m_keymap.insert(0xB3,QString(0x00CD));
        m_keymap.insert(0xB6,QString(0x00F7));
        m_keymap.insert(0xB7,QString(0x00D7));
        m_keymap.insert(0xB8,QString(0x00E4));
        m_keymap.insert(0xB9,QString(0x0111));
        m_keymap.insert(0xBA,QString(0x0110));
        m_keymap.insert(0xBB,QString(0x005B));
        m_keymap.insert(0xBC,QString(0x005D));
        m_keymap.insert(0xBE,QString(0x00ED));
        m_keymap.insert(0xBF,QString(0x0142));
        m_keymap.insert(0xC0,QString(0x0141));
        m_keymap.insert(0xC1,QString(0x0024));
        m_keymap.insert(0xC2,QString(0x00DF));
        m_keymap.insert(0xC5,QString(0x003E));
        m_keymap.insert(0xC6,QString(0x0023));
        m_keymap.insert(0xC7,QString(0x0026));
        m_keymap.insert(0xC8,QString(0x0040));
        m_keymap.insert(0xC9,QString(0x007B));
        m_keymap.insert(0xCA,QString(0x007D));
        m_keymap.insert(0xCB,QString(0x003C));
        m_keymap.insert(0xCC,QString(0x003B));
        m_keymap.insert(0xCD,QString(0x003E));
        m_keymap.insert(0xCE,QString(0x002A));
    }
};

#endif // HUNGARIAN_AUTOMATA_H

