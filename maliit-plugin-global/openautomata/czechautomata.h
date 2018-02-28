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

#ifndef CZECH_AUTOMATA_H
#define CZECH_AUTOMATA_H

#include "automatabase.h"
#include <QLocale>

class CzechAutomata : public AutomataBase
{

public:
    CzechAutomata()
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
        addNormalKeys();
        addNumberKeys();
        addShiftedKeys();
        addAccentKeys();
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
        return new CzechAutomata();
    }

private:
    void addSymbolKeys()
    {
        m_keymap.insert(0x60,QString(0x003B));
        m_keymap.insert(0x31,QString(0x002B));
        m_keymap.insert(0x32,QString(0x011B));
        m_keymap.insert(0x33,QString(0x0161));
        m_keymap.insert(0x34,QString(0x010D));
        m_keymap.insert(0x35,QString(0x0159));
        m_keymap.insert(0x36,QString(0x017E));
        m_keymap.insert(0x37,QString(0x00FD));
        m_keymap.insert(0x38,QString(0x00E1));
        m_keymap.insert(0x39,QString(0x00ED));
        m_keymap.insert(0x30,QString(0x00E9));
        m_keymap.insert(0x2D,QString(0x003D));
        m_keymap.insert(0x3D,QString(0x00B4));
        m_keymap.insert(0x5C,QString(0x00A8));
        m_keymap.insert(0x5B,QString(0x00FA));
        m_keymap.insert(0x5D,QString(0x0029));
        m_keymap.insert(0x3B,QString(0x016F));
        m_keymap.insert(0x27,QString(0x00A7));
        // Shifted Symbols
        m_keymap.insert(0x7E,QString(0x02DA));
        m_keymap.insert(0x5F,QString(0x0025));
        m_keymap.insert(0x2B,QString(0x02C7));
        m_keymap.insert(0x7B,QString(0x002F));
        m_keymap.insert(0x7D,QString(0x0028));
        m_keymap.insert(0x3A,QString(0x0022));
        m_keymap.insert(0x22,QString(0x0021));
        m_keymap.insert(0x3C,QString(0x003F));
        m_keymap.insert(0x3E,QString(0x003A));
        m_keymap.insert(0x3F,QString(0x005F));
    }

    void addNormalKeys()
    {
        m_keymap.insert(0x71,QString(0x71));
        m_keymap.insert(0x77,QString(0x77));
        m_keymap.insert(0x65,QString(0x65));
        m_keymap.insert(0x72,QString(0x72));
        m_keymap.insert(0x74,QString(0x74));
        m_keymap.insert(0x79,QString(0x7A));
        m_keymap.insert(0x75,QString(0x75));
        m_keymap.insert(0x69,QString(0x69));
        m_keymap.insert(0x6F,QString(0x6F));
        m_keymap.insert(0x70,QString(0x70));
        m_keymap.insert(0X61,QString(0X61));
        m_keymap.insert(0x73,QString(0x73));
        m_keymap.insert(0x64,QString(0x64));
        m_keymap.insert(0x66,QString(0x66));
        m_keymap.insert(0x67,QString(0x67));
        m_keymap.insert(0x68,QString(0x68));
        m_keymap.insert(0x6A,QString(0x6A));
        m_keymap.insert(0x6B,QString(0x6B));
        m_keymap.insert(0x6C,QString(0x6C));
        m_keymap.insert(0x7A,QString(0x79));
        m_keymap.insert(0x78,QString(0x78));
        m_keymap.insert(0x63,QString(0x63));
        m_keymap.insert(0x76,QString(0x76));
        m_keymap.insert(0x62,QString(0x62));
        m_keymap.insert(0x6E,QString(0x6E));
        m_keymap.insert(0x6D,QString(0x6D));
        m_keymap.insert(0x2C,QString(0x2C));
        m_keymap.insert(0x2E,QString(0x2E));
        m_keymap.insert(0x2F,QString(0x2D));
        m_keymap.insert(0x20,QString(0x20));
    }

    void addNumberKeys()
    {
        m_keymap.insert(0x21,QString(0x0031));
        m_keymap.insert(0x40,QString(0x0032));
        m_keymap.insert(0x23,QString(0x0033));
        m_keymap.insert(0x24,QString(0x0034));
        m_keymap.insert(0x25,QString(0x0035));
        m_keymap.insert(0x5E,QString(0x0036));
        m_keymap.insert(0x26,QString(0x0037));
        m_keymap.insert(0x2A,QString(0x0038));
        m_keymap.insert(0x28,QString(0x0039));
        m_keymap.insert(0x29,QString(0x0030));
    }

    void addShiftedKeys()
    {
        m_keymap.insert(0x51,QString(0x51));
        m_keymap.insert(0x57,QString(0x57));
        m_keymap.insert(0x45,QString(0x45));
        m_keymap.insert(0x52,QString(0x52));
        m_keymap.insert(0x54,QString(0x54));
        m_keymap.insert(0x59,QString(0x5A));
        m_keymap.insert(0x55,QString(0x55));
        m_keymap.insert(0x49,QString(0x49));
        m_keymap.insert(0x4F,QString(0x4F));
        m_keymap.insert(0x50,QString(0x50));
        m_keymap.insert(0x41,QString(0x41));
        m_keymap.insert(0x53,QString(0x53));
        m_keymap.insert(0x44,QString(0x44));
        m_keymap.insert(0x46,QString(0x46));
        m_keymap.insert(0x47,QString(0x47));
        m_keymap.insert(0x48,QString(0x48));
        m_keymap.insert(0x4A,QString(0x4A));
        m_keymap.insert(0x4B,QString(0x4B));
        m_keymap.insert(0x4C,QString(0x4C));
        m_keymap.insert(0x5A,QString(0x59));
        m_keymap.insert(0x58,QString(0x58));
        m_keymap.insert(0x43,QString(0x43));
        m_keymap.insert(0x56,QString(0x56));
        m_keymap.insert(0x42,QString(0x42));
        m_keymap.insert(0x4E,QString(0x4E));
        m_keymap.insert(0x4D,QString(0x4D));
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
        m_accentKeymap.insert(QString(0x00A8)+QString(0x69),QString(0x00EF));
        m_accentKeymap.insert(QString(0x00A8)+QString(0x49),QString(0x00CF));
        m_accentKeymap.insert(QString(0x00A8)+QString(0x79),QString(0x00FF));
        m_accentKeymap.insert(QString(0x00A8)+QString(0x59),QString(0x0178));
    }

    void addCedillaAccentForHID()
    {
        m_accentKeymap.insert(QString(0x00B8)+QString(0x74),QString(0x0163));
        m_accentKeymap.insert(QString(0x00B8)+QString(0x54),QString(0x0162));
        m_accentKeymap.insert(QString(0x00B8)+QString(0x73),QString(0x015F));
        m_accentKeymap.insert(QString(0x00B8)+QString(0x53),QString(0x015E));
        m_accentKeymap.insert(QString(0x00B8)+QString(0x63),QString(0x00E7));
        m_accentKeymap.insert(QString(0x00B8)+QString(0x43),QString(0x00C7));
        m_accentKeymap.insert(QString(0x00B8)+QString(0x6E),QString(0x0146));
        m_accentKeymap.insert(QString(0x00B8)+QString(0x4E),QString(0x0145));
        m_accentKeymap.insert(QString(0x00B8)+QString(0x72),QString(0x0157));
        m_accentKeymap.insert(QString(0x00B8)+QString(0x52),QString(0x0156));
        m_accentKeymap.insert(QString(0x00B8)+QString(0x67),QString(0x0123));
        m_accentKeymap.insert(QString(0x00B8)+QString(0x47),QString(0x0122));
        m_accentKeymap.insert(QString(0x00B8)+QString(0x6B),QString(0x0137));
        m_accentKeymap.insert(QString(0x00B8)+QString(0x4B),QString(0x0136));
        m_accentKeymap.insert(QString(0x00B8)+QString(0x6C),QString(0x013C));
        m_accentKeymap.insert(QString(0x00B8)+QString(0x4C),QString(0x013B));
    }

    void addAccentKeys()
    {
        m_keymap.insert(0xe1,QString(0xe1));
        m_keymap.insert(0x1e8,QString(0x10D));
        m_keymap.insert(0x1ef,QString(0x10F));
        m_keymap.insert(0xe9,QString(0xe9));
        m_keymap.insert(0x1ec,QString(0x11B));
        m_keymap.insert(0xed,QString(0xed));
        m_keymap.insert(0x1f2,QString(0x148));
        m_keymap.insert(0xf3,QString(0xf3));
        m_keymap.insert(0x1f8,QString(0x159));
        m_keymap.insert(0x1b9,QString(0x161));
        m_keymap.insert(0x1bb,QString(0x165));
        m_keymap.insert(0xfd,QString(0xfd));
        m_keymap.insert(0x1be,QString(0x17E));
        m_keymap.insert(0xDF,QString(0xc1));
        m_keymap.insert(0x1c8,QString(0x10C));
        m_keymap.insert(0x1cf,QString(0x10E));
        m_keymap.insert(0x0111,QString(0xc9));
        m_keymap.insert(0x1cc,QString(0x11A));
        m_keymap.insert(0x110,QString(0xcd));
        m_keymap.insert(0x1d2,QString(0x147));
        m_keymap.insert(0xd3,QString(0xd3));
        m_keymap.insert(0x1d8,QString(0x158));
        m_keymap.insert(0x1a9,QString(0x160));
        m_keymap.insert(0x1ab,QString(0x164));
        m_keymap.insert(0xdd,QString(0xdd));
        m_keymap.insert(0x1ae,QString(0x17D));
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
        m_keymap.insert(0xAE,QString(0x20AC));
        m_keymap.insert(0xB6,QString(0x00F7));
        m_keymap.insert(0xB7,QString(0x00D7));
        m_keymap.insert(0xB9,QString(0x0111));
        m_keymap.insert(0xBA,QString(0x0110));
        m_keymap.insert(0xBB,QString(0x005B));
        m_keymap.insert(0xBC,QString(0x005D));
        m_keymap.insert(0xBF,QString(0x0142));
        m_keymap.insert(0xC0,QString(0x0141));
        m_keymap.insert(0xC1,QString(0x0024));
        m_keymap.insert(0xC2,QString(0x00DF));
        m_keymap.insert(0xC6,QString(0x0023));
        m_keymap.insert(0xC7,QString(0x0026));
        m_keymap.insert(0xC8,QString(0x0040));
        m_keymap.insert(0xC9,QString(0x007B));
        m_keymap.insert(0xCA,QString(0x007D));
        m_keymap.insert(0xCC,QString(0x003C));
        m_keymap.insert(0xCD,QString(0x003E));
        m_keymap.insert(0xCE,QString(0x002A));
    }
};
#endif // CZECH_AUTOMATA_H

