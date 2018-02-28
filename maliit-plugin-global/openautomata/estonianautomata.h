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

#ifndef ESTONIAN_AUTOMATA_H
#define ESTONIAN_AUTOMATA_H

#include "automatabase.h"
#include <QLocale>

class EstonianAutomata : public AutomataBase
{

public:
    EstonianAutomata()
    {
        m_accentSelect = false;
        m_accents.insert(QString(0x02C7));
        m_accents.insert(QString(0x00B4));
        m_accents.insert(QString(0x007E));
        m_accents.insert(QString(0x0060));
        m_accents.insert(QString(0x005E));

        addNumberKeys();
        addSymbolKeys();
        addNormalKeys();
        addShiftedKeys();
        addAltKeysForHID();
        addAltShiftedKeysForHID();
        addAccentKeys();

        addCaronAccentForHID();
        addAcuteAccentForHID();
        addGraveAccentKeysForHID();
        addCircumFlexAccentForHID();
        addTildeAccentForHID();
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
        return new EstonianAutomata();
    }

private:
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

    void addSymbolKeys()
    {
        m_keymap.insert(0x60,QString(0x02C7));
        m_keymap.insert(0x7E,QString(0x007E));
        m_keymap.insert(0x2D,QString(0x002B));
        m_keymap.insert(0x3D,QString(0x00B4));
        m_keymap.insert(0x2B,QString(0x0060));
        m_keymap.insert(0x5C,QString(0x0027));
        m_keymap.insert(0x7C,QString(0x002A));
        m_keymap.insert(0x21,QString(0x0021));
        m_keymap.insert(0x40,QString(0x0022));
        m_keymap.insert(0x23,QString(0x0023));
        m_keymap.insert(0x24,QString(0x00A4));
        m_keymap.insert(0x25,QString(0x0025));
        m_keymap.insert(0x5E,QString(0x0026));
        m_keymap.insert(0x26,QString(0x002F));
        m_keymap.insert(0x2A,QString(0x0028));
        m_keymap.insert(0x28,QString(0x0029));
        m_keymap.insert(0x29,QString(0x003D));
        m_keymap.insert(0x5F,QString(0x003F));
        m_keymap.insert(0x2C,QString(0x002C));
        m_keymap.insert(0x3C,QString(0x003B));
        m_keymap.insert(0x2E,QString(0x002E));
        m_keymap.insert(0x3E,QString(0x003A));
        m_keymap.insert(0x2F,QString(0x002D));
        m_keymap.insert(0x3F,QString(0x005F));
    }

    void addNormalKeys()
    {
        m_keymap.insert(0x71,QString(0x71));
        m_keymap.insert(0x77,QString(0x77));
        m_keymap.insert(0x65,QString(0x65));
        m_keymap.insert(0x72,QString(0x72));
        m_keymap.insert(0x74,QString(0x74));
        m_keymap.insert(0x79,QString(0x79));
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
        m_keymap.insert(0x7A,QString(0x7A));
        m_keymap.insert(0x78,QString(0x78));
        m_keymap.insert(0x63,QString(0x63));
        m_keymap.insert(0x76,QString(0x76));
        m_keymap.insert(0x62,QString(0x62));
        m_keymap.insert(0x6E,QString(0x6E));
        m_keymap.insert(0x6D,QString(0x6D));
        m_keymap.insert(0x20,QString(0x20));
    }

    void addShiftedKeys()
    {
        m_keymap.insert(0x51,QString(0x51));
        m_keymap.insert(0x57,QString(0x57));
        m_keymap.insert(0x45,QString(0x45));
        m_keymap.insert(0x52,QString(0x52));
        m_keymap.insert(0x54,QString(0x54));
        m_keymap.insert(0x59,QString(0x59));
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
        m_keymap.insert(0x5A,QString(0x5A));
        m_keymap.insert(0x58,QString(0x58));
        m_keymap.insert(0x43,QString(0x43));
        m_keymap.insert(0x56,QString(0x56));
        m_keymap.insert(0x42,QString(0x42));
        m_keymap.insert(0x4E,QString(0x4E));
        m_keymap.insert(0x4D,QString(0x4D));
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
        m_keymap.insert(0xAA,QString(0x005C));
        m_keymap.insert(0xC4,QString(0x00BD));
        m_keymap.insert(0xAE,QString(0x20AC));
        m_keymap.insert(0xB7,QString(0x00A7));
        m_keymap.insert(0xB9,QString(0x0161));
        m_keymap.insert(0xC2,QString(0x005E));
        m_keymap.insert(0xC5,QString(0x017E));
    }

    void addAltShiftedKeysForHID()
    {
        m_keymap.insert(0xF3,QString(0x0160));
        m_keymap.insert(0xFF,QString(0x017D));
        m_keymap.insert(0xFC,QString(0x005E));
    }

    void addAccentKeys()
    {
        m_keymap.insert(0x027,QString(0x0E4));
        m_keymap.insert(0x05D,QString(0x0F5));
        m_keymap.insert(0x03B,QString(0x0F6));
        m_keymap.insert(0x0B9,QString(0x161));
        m_keymap.insert(0x05B,QString(0x0FC));
        m_keymap.insert(0x0C5,QString(0x17E));
        m_keymap.insert(0x022,QString(0x0C4));
        m_keymap.insert(0x07D,QString(0x0D5));
        m_keymap.insert(0x03A,QString(0x0D6));
        m_keymap.insert(0x0F3,QString(0x160));
        m_keymap.insert(0x07B,QString(0x0DC));
        m_keymap.insert(0x0FF,QString(0x17D));
    }

    void addCaronAccentForHID()
    {
        m_accentKeymap.insert(QString(0x02C7)+QString(0x73),QString(0x0161));
        m_accentKeymap.insert(QString(0x02C7)+QString(0x53),QString(0x0160));
        m_accentKeymap.insert(QString(0x02C7)+QString(0x7A),QString(0x017E));
        m_accentKeymap.insert(QString(0x02C7)+QString(0x5A),QString(0x017D));
        m_accentKeymap.insert(QString(0x02C7)+QString(0x63),QString(0x010D));
        m_accentKeymap.insert(QString(0x02C7)+QString(0x43),QString(0x010C));
    }

    void addAcuteAccentForHID()
    {
        m_accentKeymap.insert(QString(0x00B4)+QString(0x65),QString(0x00E9));
        m_accentKeymap.insert(QString(0x00B4)+QString(0x45),QString(0x00C9));
        m_accentKeymap.insert(QString(0x00B4)+QString(0x6F),QString(0x00F3));
        m_accentKeymap.insert(QString(0x00B4)+QString(0x4F),QString(0x00D3));
        m_accentKeymap.insert(QString(0x00B4)+QString(0x73),QString(0x015B));
        m_accentKeymap.insert(QString(0x00B4)+QString(0x53),QString(0x015A));
        m_accentKeymap.insert(QString(0x00B4)+QString(0x7A),QString(0x017A));
        m_accentKeymap.insert(QString(0x00B4)+QString(0x5A),QString(0x0179));
        m_accentKeymap.insert(QString(0x00B4)+QString(0x63),QString(0x0107));
        m_accentKeymap.insert(QString(0x00B4)+QString(0x43),QString(0x0106));
        m_accentKeymap.insert(QString(0x00B4)+QString(0x6E),QString(0x0144));
        m_accentKeymap.insert(QString(0x00B4)+QString(0x4E),QString(0x0143));
    }

    void addGraveAccentKeysForHID()
    {
        m_accentKeymap.insert(QString(0x60)+QString(0x65),QString(0xE8));
        m_accentKeymap.insert(QString(0x60)+QString(0x45),QString(0xC8));
        m_accentKeymap.insert(QString(0x60)+QString(0x75),QString(0xF9));
        m_accentKeymap.insert(QString(0x60)+QString(0x55),QString(0xD9));
        m_accentKeymap.insert(QString(0x60)+QString(0x6F),QString(0xF2));
        m_accentKeymap.insert(QString(0x60)+QString(0x4F),QString(0xD2));
        m_accentKeymap.insert(QString(0x60)+QString(0x61),QString(0xE0));
        m_accentKeymap.insert(QString(0x60)+QString(0x41),QString(0xC0));
    }

    void addCircumFlexAccentForHID()
    {
        m_accentKeymap.insert(QString(0x5E)+QString(0x61),QString(0x0E2));
        m_accentKeymap.insert(QString(0x5E)+QString(0x41),QString(0x0C2));
        m_accentKeymap.insert(QString(0x5E)+QString(0x65),QString(0x0EA));
        m_accentKeymap.insert(QString(0x5E)+QString(0x45),QString(0x0CA));
        m_accentKeymap.insert(QString(0x5E)+QString(0x69),QString(0x0EE));
        m_accentKeymap.insert(QString(0x5E)+QString(0x49),QString(0x0CE));
        m_accentKeymap.insert(QString(0x5E)+QString(0x67),QString(0x11D));
        m_accentKeymap.insert(QString(0x5E)+QString(0x47),QString(0x11C));
    }

    void addTildeAccentForHID()
    {
        m_accentKeymap.insert(QString(0x7E)+QString(0x6F),QString(0x0F5));
        m_accentKeymap.insert(QString(0x7E)+QString(0x4F),QString(0x0D5));
    }
};

#endif // ESTONIAN_AUTOMATA_H
