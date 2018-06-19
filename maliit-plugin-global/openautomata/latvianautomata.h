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

#ifndef LATVIAN_AUTOMATA_H
#define LATVIAN_AUTOMATA_H

#include "automatabase.h"
#include <QLocale>

class LatvianAutomata : public AutomataBase
{

public:
    LatvianAutomata()
    {
        m_accentSelect = false;
        m_accents.insert(QString(0x00B4));
        m_accents.insert(QString(0x02D9));
        m_accents.insert(QString(0x00A8));

        addAcuteAccentForHID();
        addDegreeAccentForHID();
        addDiaresisAccentForHID();

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
        return new LatvianAutomata();
    }
private:
    void addSymbolKeys()
    {
        m_keymap.insert(0x21,QString(0x21));
        m_keymap.insert(0x22,QString(0x22));
        m_keymap.insert(0x23,QString(0x23));
        m_keymap.insert(0x24,QString(0x24));
        m_keymap.insert(0x25,QString(0x25));
        m_keymap.insert(0x26,QString(0x26));
        m_keymap.insert(0x27,QString(0x27));
        m_keymap.insert(0x28,QString(0x28));
        m_keymap.insert(0x29,QString(0x29));
        m_keymap.insert(0x2a,QString(0x2a));
        m_keymap.insert(0x2b,QString(0x2b));
        m_keymap.insert(0x2c,QString(0x2c));
        m_keymap.insert(0x2d,QString(0x2d));
        m_keymap.insert(0x2e,QString(0x2e));
        m_keymap.insert(0x2f,QString(0x2f));
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
        m_keymap.insert(0x3a,QString(0x3a));
        m_keymap.insert(0x3b,QString(0x3b));
        m_keymap.insert(0x3c,QString(0x3c));
        m_keymap.insert(0x3d,QString(0x3d));
        m_keymap.insert(0x3e,QString(0x3e));
        m_keymap.insert(0x3f,QString(0x3f));
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
        m_keymap.insert(0x5e,QString(0x5e));
        m_keymap.insert(0x5f,QString(0x5f));
    }

    void addNormalKeys()
    {
        m_keymap.insert(0x5b,QString(0x5b));
        m_keymap.insert(0x5c,QString(0x02D9));
        m_keymap.insert(0x5d,QString(0x5d));
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
        m_keymap.insert(0x7b,QString(0x7b));
        m_keymap.insert(0x7c,QString(0x7c));
        m_keymap.insert(0x7d,QString(0x7d));
        m_keymap.insert(0x7e,QString(0x7e));
        m_keymap.insert(0x20,QString(0x20));
    }

    void addAccentKeys()
    {
        m_keymap.insert(0x03e0,QString(0x101));
        m_keymap.insert(0x1e8,QString(0x10D));
        m_keymap.insert(0x03ba,QString(0x113));
        m_keymap.insert(0x03bb,QString(0x123));
        m_keymap.insert(0x03ef,QString(0x12B));
        m_keymap.insert(0x03f3,QString(0x137));
        m_keymap.insert(0x03b6,QString(0x13C));
        m_keymap.insert(0x03f1,QString(0x146));
        m_keymap.insert(0x01b9,QString(0x161));
        m_keymap.insert(0x03fe,QString(0x16B));
        m_keymap.insert(0x01be,QString(0x17E));
        m_keymap.insert(0x03c0,QString(0x100));
        m_keymap.insert(0x01c8,QString(0x10C));
        m_keymap.insert(0x03aa,QString(0x112));
        m_keymap.insert(0x03ab,QString(0x122));
        m_keymap.insert(0x03cf,QString(0x12A));
        m_keymap.insert(0x03d3,QString(0x136));
        m_keymap.insert(0x03a6,QString(0x13B));
        m_keymap.insert(0x03d1,QString(0x145));
        m_keymap.insert(0x01a9,QString(0x160));
        m_keymap.insert(0x03de,QString(0x16A));
        m_keymap.insert(0x01ae,QString(0x17D));
    }

    void addAcuteAccentForHID()
    {
        m_accentKeymap.insert(QString(0x00B4)+QString(0x65),QString(0x00E9));
        m_accentKeymap.insert(QString(0x00B4)+QString(0x6F),QString(0x00F3));
        m_accentKeymap.insert(QString(0x00B4)+QString(0x73),QString(0x015B));
        m_accentKeymap.insert(QString(0x00B4)+QString(0x7A),QString(0x017A));
        m_accentKeymap.insert(QString(0x00B4)+QString(0x63),QString(0x0107));
        m_accentKeymap.insert(QString(0x00B4)+QString(0x6E),QString(0x0144));
        m_accentKeymap.insert(QString(0x00B4)+QString(0x45),QString(0x00C9));
        m_accentKeymap.insert(QString(0x00B4)+QString(0x4F),QString(0x00D3));
        m_accentKeymap.insert(QString(0x00B4)+QString(0x53),QString(0x015A));
        m_accentKeymap.insert(QString(0x00B4)+QString(0x5A),QString(0x0179));
        m_accentKeymap.insert(QString(0x00B4)+QString(0x43),QString(0x0106));
        m_accentKeymap.insert(QString(0x00B4)+QString(0x4E),QString(0x0143));

    }

    void addDegreeAccentForHID()
    {
        m_accentKeymap.insert(QString(0x02D9)+QString(0x65),QString(0x0117));
        m_accentKeymap.insert(QString(0x02D9)+QString(0x61),QString(0x00E5));
        m_accentKeymap.insert(QString(0x02D9)+QString(0x67),QString(0x0121));
        m_accentKeymap.insert(QString(0x02D9)+QString(0x7A),QString(0x017C));
        m_accentKeymap.insert(QString(0x02D9)+QString(0x45),QString(0x0116));
        m_accentKeymap.insert(QString(0x02D9)+QString(0x41),QString(0x00C5));
        m_accentKeymap.insert(QString(0x02D9)+QString(0x5A),QString(0x017B));
    }

    void addDiaresisAccentForHID()
    {
        m_accentKeymap.insert(QString(0x00A8)+QString(0x61),QString(0x00E4));
        m_accentKeymap.insert(QString(0x00A8)+QString(0x6F),QString(0x00F6));
        m_accentKeymap.insert(QString(0x00A8)+QString(0x75),QString(0x00FC));
        m_accentKeymap.insert(QString(0x00A8)+QString(0x41),QString(0x00C4));
        m_accentKeymap.insert(QString(0x00A8)+QString(0x4F),QString(0x00D6));
        m_accentKeymap.insert(QString(0x00A8)+QString(0x55),QString(0x00DC));
    }

    void addAltKeysForHID()
    {
        m_keymap.insert(0xA1,QString(0x00AB));
        m_keymap.insert(0xA2,QString(0x00BB));
        m_keymap.insert(0xA3,QString(0x20AC));
        m_keymap.insert(0xA5,QString(0x2019));
        m_keymap.insert(0xAA,QString(0x2013));
        m_keymap.insert(0xAE,QString(0x0113));
        m_keymap.insert(0xAF,QString(0x0157));
        m_keymap.insert(0xB2,QString(0x016B));
        m_keymap.insert(0xB3,QString(0x012B));
        m_keymap.insert(0xB4,QString(0xF5));
        m_keymap.insert(0xB8,QString(0x0101));
        m_keymap.insert(0xB9,QString(0x0161));
        m_keymap.insert(0xBC,QString(0x0123));
        m_keymap.insert(0xBF,QString(0x0137));
        m_keymap.insert(0xC0,QString(0x013C));
        m_keymap.insert(0xC2,QString(0x00B4));
        m_keymap.insert(0xC4,QString(0x02D9));
        m_keymap.insert(0xC5,QString(0x017E));
        m_keymap.insert(0xC7,QString(0x010D));
        m_keymap.insert(0xCA,QString(0x0146));
    }

    void addShiftedAltKeysForHID()
    {
        m_keymap.insert(0xDD,QString(0xA7));
        m_keymap.insert(0xDE,QString(0xB0));
        m_keymap.insert(0xE0,QString(0xB1));
        m_keymap.insert(0xE1,QString(0xD7));
        m_keymap.insert(0xE4,QString(0x2014));
        m_keymap.insert(0xE8,QString(0x112));
        m_keymap.insert(0xE9,QString(0x156));
        m_keymap.insert(0xEC,QString(0x16A));
        m_keymap.insert(0xED,QString(0x12A));
        m_keymap.insert(0xEE,QString(0xD5));
        m_keymap.insert(0xF2,QString(0x100));
        m_keymap.insert(0xF3,QString(0x160));
        m_keymap.insert(0xF6,QString(0x122));
        m_keymap.insert(0xF9,QString(0x136));
        m_keymap.insert(0xFA,QString(0x13B));
        m_keymap.insert(0xFC,QString(0xA8));
        m_keymap.insert(0xFF,QString(0x17D));
        m_keymap.insert(0x101,QString(0x10C));
        m_keymap.insert(0x104,QString(0x145));
    }
};

#endif // LATVIAN_AUTOMATA_H
