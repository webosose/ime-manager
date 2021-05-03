// Copyright (c) 2017-2020 LG Electronics, Inc.
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

#ifndef ICELANDIC_AUTOMATA_H
#define ICELANDIC_AUTOMATA_H

#include "automatabase.h"
#include <QLocale>

class IcelandicAutomata: public AutomataBase
{

public:
    IcelandicAutomata() {
        m_accentSelect = false;

        m_accents.insert(QString(QChar(0x00A8)));
        m_accents.insert(QString(QChar(0x00B0)));
        m_accents.insert(QString(QChar(0x00B4)));
        m_accents.insert(QString(QChar(0x005E)));

        addNumberKeys();
        addNormalKeys();
        addShiftedKeys();
        addAltKeysForHID();
        addSymbolKeys();
        addAcuteAccenForUI();
        addAcuteAccentForHID();
        addCircumFlexAccentForHID();
        addDiacriticAccentForHID();
        addDiaeresisAccentForHID();

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
        return new IcelandicAutomata();
    }

private:
    void addSymbolKeys()
    {
        m_keymap.insert(0x60,QString(QChar(0x00B0)));
        m_keymap.insert(0x7e,QString(QChar(0x00A8)));
        m_keymap.insert(0x21,QString(QChar(0x21)));
        m_keymap.insert(0x40,QString(QChar(0x22)));
        m_keymap.insert(0x23,QString(QChar(0x23)));
        m_keymap.insert(0x24,QString(QChar(0x24)));
        m_keymap.insert(0x25,QString(QChar(0x25)));
        m_keymap.insert(0x5e,QString(QChar(0x0026)));
        m_keymap.insert(0x26,QString(QChar(0x002F)));
        m_keymap.insert(0x2a,QString(QChar(0x0028)));
        m_keymap.insert(0x28,QString(QChar(0x0029)));
        m_keymap.insert(0x29,QString(QChar(0x003D)));
        m_keymap.insert(0x5f,QString(QChar(0x00D6)));
        m_keymap.insert(0x2b,QString(QChar(0x005F)));
        m_keymap.insert(0x2d,QString(QChar(0x00F6)));
        m_keymap.insert(0x3d,QString(QChar(0x002D)));
        m_keymap.insert(0x27,QString(QChar(0x00B4)));
        m_keymap.insert(0x3b,QString(QChar(0x00E6)));
        m_keymap.insert(0x3a,QString(QChar(0x00C6)));
        m_keymap.insert(0x2c,QString(QChar(0x2c)));
        m_keymap.insert(0x22,QString(QChar(0x0027)));
        m_keymap.insert(0x5b,QString(QChar(0x00F0)));
        m_keymap.insert(0x5c,QString(QChar(0x5c)));
        m_keymap.insert(0x5d,QString(QChar(0x0027)));
        m_keymap.insert(0x7b,QString(QChar(0x00D0)));
        m_keymap.insert(0x7c,QString(QChar(0x7c)));
        m_keymap.insert(0x7d,QString(QChar(0x003F)));
        m_keymap.insert(0x2e,QString(QChar(0x2e)));
        m_keymap.insert(0x2f,QString(QChar(0x00FE)));
        m_keymap.insert(0x3c,QString(QChar(0x003B)));
        m_keymap.insert(0x3e,QString(QChar(0x003A)));
        m_keymap.insert(0x3f,QString(QChar(0x00DE)));
        //CircumFlexAccent 0x005E
        m_keymap.insert(0xC2,QString(QChar(0x005E)));
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

    void addShiftedKeys()
    {
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
    }

    void addAltKeysForHID()
    {
        m_keymap.insert(0xC3,QString(QChar(0x00B0)));
        m_keymap.insert(0xA4,QString(QChar(0x20AC)));
        m_keymap.insert(0xA6,QString(QChar(0x007B)));

        m_keymap.insert(0xA7,QString(QChar(0x005B)));
        m_keymap.insert(0xA8,QString(QChar(0x005D)));
        m_keymap.insert(0xA9,QString(QChar(0x007D)));

        m_keymap.insert(0xAA,QString(QChar(0x005C)));
        m_keymap.insert(0xAC,QString(QChar(0x0040)));
        m_keymap.insert(0xAE,QString(QChar(0x20AC)));

        m_keymap.insert(0xB7,QString(QChar(0x007E)));
        m_keymap.insert(0xC2,QString(QChar(0x005E)));
        m_keymap.insert(0xCB,QString(QChar(0x00B5)));
    }

    void addNormalKeys()
    {
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
        m_keymap.insert(0x20,QString(QChar(0x20)));
    }

    void addAcuteAccenForUI()
    {
        m_keymap.insert(0x00e1, QString(QChar(0x00e1)));
        m_keymap.insert(0x00e9, QString(QChar(0x00e9)));
        m_keymap.insert(0x00ed, QString(QChar(0x00ed)));
        m_keymap.insert(0x00f3, QString(QChar(0x00f3)));
        m_keymap.insert(0x00f6, QString(QChar(0x00f6)));
        m_keymap.insert(0x00fa, QString(QChar(0x00fa)));
        m_keymap.insert(0x00fd, QString(QChar(0x00fd)));
        m_keymap.insert(0x00c1, QString(QChar(0x00c1)));
        m_keymap.insert(0x00c9, QString(QChar(0x00c9)));
        m_keymap.insert(0x00cd, QString(QChar(0x00cd)));
        m_keymap.insert(0x00d3, QString(QChar(0x00d3)));
        m_keymap.insert(0x00d6, QString(QChar(0x00d6)));
        m_keymap.insert(0x00da, QString(QChar(0x00da)));
        m_keymap.insert(0x00dd, QString(QChar(0x00dd)));
    }

    void addAcuteAccentForHID()
    {
        m_accentKeymap.insert(QString(QChar(0x00B4))+QString(QChar(0x61)),QString(QChar(0x00E1))); // a
        m_accentKeymap.insert(QString(QChar(0x00B4))+QString(QChar(0x41)),QString(QChar(0x00C1)));
        m_accentKeymap.insert(QString(QChar(0x00B4))+QString(QChar(0x65)),QString(QChar(0x00E9))); // e
        m_accentKeymap.insert(QString(QChar(0x00B4))+QString(QChar(0x45)),QString(QChar(0x00C9)));
        m_accentKeymap.insert(QString(QChar(0x00B4))+QString(QChar(0x69)),QString(QChar(0x00ED))); // i
        m_accentKeymap.insert(QString(QChar(0x00B4))+QString(QChar(0x49)),QString(QChar(0x00CD)));
        m_accentKeymap.insert(QString(QChar(0x00B4))+QString(QChar(0x6F)),QString(QChar(0x00F3))); // o
        m_accentKeymap.insert(QString(QChar(0x00B4))+QString(QChar(0x4F)),QString(QChar(0x00D3)));
        m_accentKeymap.insert(QString(QChar(0x00B4))+QString(QChar(0x75)),QString(QChar(0x00FA))); // u
        m_accentKeymap.insert(QString(QChar(0x00B4))+QString(QChar(0x55)),QString(QChar(0x00DA)));
        m_accentKeymap.insert(QString(QChar(0x00B4))+QString(QChar(0x79)),QString(QChar(0x00FD))); // y
        m_accentKeymap.insert(QString(QChar(0x00B4))+QString(QChar(0x59)),QString(QChar(0x00DD)));
    }

    void addCircumFlexAccentForHID()
    {
        m_accentKeymap.insert(QString(QChar(0x005E))+QString(QChar(0x61)),QString(QChar(0x00E2))); // a
        m_accentKeymap.insert(QString(QChar(0x005E))+QString(QChar(0x41)),QString(QChar(0x00C2)));
        m_accentKeymap.insert(QString(QChar(0x005E))+QString(QChar(0x65)),QString(QChar(0x00EA))); // e
        m_accentKeymap.insert(QString(QChar(0x005E))+QString(QChar(0x45)),QString(QChar(0x00CA)));
        m_accentKeymap.insert(QString(QChar(0x005E))+QString(QChar(0x69)),QString(QChar(0x00EE))); // i
        m_accentKeymap.insert(QString(QChar(0x005E))+QString(QChar(0x49)),QString(QChar(0x00CE)));
        m_accentKeymap.insert(QString(QChar(0x005E))+QString(QChar(0x6F)),QString(QChar(0x00F4))); // o
        m_accentKeymap.insert(QString(QChar(0x005E))+QString(QChar(0x4F)),QString(QChar(0x00D4)));
        m_accentKeymap.insert(QString(QChar(0x005E))+QString(QChar(0x75)),QString(QChar(0x00FB))); // u
        m_accentKeymap.insert(QString(QChar(0x005E))+QString(QChar(0x55)),QString(QChar(0x00DB)));
    }

    void addDiacriticAccentForHID()
    {
        m_accentKeymap.insert(QString(QChar(0x00B0))+QString(QChar(0x61)),QString(QChar(0x00E5))); // a
        m_accentKeymap.insert(QString(QChar(0x00B0))+QString(QChar(0x41)),QString(QChar(0x00C5)));
        m_accentKeymap.insert(QString(QChar(0x00B0))+QString(QChar(0x75)),QString(QChar(0x016F))); // u
        m_accentKeymap.insert(QString(QChar(0x00B0))+QString(QChar(0x55)),QString(QChar(0x016E)));
    }

    void addDiaeresisAccentForHID()
    {
        m_accentKeymap.insert(QString(QChar(0x00A8))+QString(QChar(0x61)),QString(QChar(0x00E4))); // a
        m_accentKeymap.insert(QString(QChar(0x00A8))+QString(QChar(0x41)),QString(QChar(0x00C4)));
        m_accentKeymap.insert(QString(QChar(0x00A8))+QString(QChar(0x65)),QString(QChar(0x00EB))); // e
        m_accentKeymap.insert(QString(QChar(0x00A8))+QString(QChar(0x45)),QString(QChar(0x00CB)));
        m_accentKeymap.insert(QString(QChar(0x00A8))+QString(QChar(0x69)),QString(QChar(0x00EF))); // i
        m_accentKeymap.insert(QString(QChar(0x00A8))+QString(QChar(0x49)),QString(QChar(0x00CF)));
        m_accentKeymap.insert(QString(QChar(0x00A8))+QString(QChar(0x6F)),QString(QChar(0x00F6))); // o
        m_accentKeymap.insert(QString(QChar(0x00A8))+QString(QChar(0x4F)),QString(QChar(0x00D6)));
        m_accentKeymap.insert(QString(QChar(0x00A8))+QString(QChar(0x75)),QString(QChar(0x00FC))); // u
        m_accentKeymap.insert(QString(QChar(0x00A8))+QString(QChar(0x55)),QString(QChar(0x00DC)));
        m_accentKeymap.insert(QString(QChar(0x00A8))+QString(QChar(0x79)),QString(QChar(0x00FF))); // y
    }
};
#endif //ICELANDIC_AUTOMATA_H

