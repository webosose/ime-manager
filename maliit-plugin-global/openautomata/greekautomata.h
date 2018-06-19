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

#ifndef GREEK_AUTOMATA_H
#define GREEK_AUTOMATA_H

#include "automatabase.h"
#include <QLocale>

class GreekAutomata: public AutomataBase
{

public:
    GreekAutomata() {
        m_accentSelect = false;

        m_accents.insert(QString(0x385));
        m_accents.insert(QString(0x384));
        m_accents.insert(QString(0x0A8));

        addNumberKeys();
        addNormalKeys();
        addShiftedKeys();
        addSymbolKeys();
        addAltedKeys();
        addAccentKeys();

        addGrekTonorAccentForHID();
        addDiaeresisAccentForHID();
        addGreekDialytikaAccentForHID();
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
        return new GreekAutomata();
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

    void addShiftedKeys()
    {
        m_keymap.insert(0x3a,QString(0x0A8));
        m_keymap.insert(0x3b,QString(0x0384));
        m_keymap.insert(0x3c,QString(0x3c));
        m_keymap.insert(0x3d,QString(0x3d));
        m_keymap.insert(0x3e,QString(0x3e));
        m_keymap.insert(0x3f,QString(0x3f));
        m_keymap.insert(0x40,QString(0x40));
        m_keymap.insert(0x41,QString(0x391));
        m_keymap.insert(0x42,QString(0x392));
        m_keymap.insert(0x43,QString(0x3A8));
        m_keymap.insert(0x44,QString(0x394));
        m_keymap.insert(0x45,QString(0x395));
        m_keymap.insert(0x46,QString(0x3A6));
        m_keymap.insert(0x47,QString(0x393));
        m_keymap.insert(0x48,QString(0x397));
        m_keymap.insert(0x49,QString(0x399));
        m_keymap.insert(0x4a,QString(0x39E));
        m_keymap.insert(0x4b,QString(0x39A));
        m_keymap.insert(0x4c,QString(0x39B));
        m_keymap.insert(0x4d,QString(0x39C));
        m_keymap.insert(0x4e,QString(0x39D));
        m_keymap.insert(0x4f,QString(0x39F));
        m_keymap.insert(0x50,QString(0x3A0));
        m_keymap.insert(0x51,QString(0x3A));
        m_keymap.insert(0x52,QString(0x3A1));
        m_keymap.insert(0x53,QString(0x3A3));
        m_keymap.insert(0x54,QString(0x3A4));
        m_keymap.insert(0x55,QString(0x398));
        m_keymap.insert(0x56,QString(0x3A9));
        m_keymap.insert(0x571,QString(0x03DA));
        m_keymap.insert(0x57,QString(0x385));
        m_keymap.insert(0x58,QString(0x3A7));
        m_keymap.insert(0x59,QString(0x3A5));
        m_keymap.insert(0x5a,QString(0x396));
        m_keymap.insert(0x5b,QString(0x5b));
        m_keymap.insert(0x5c,QString(0x5c));
        m_keymap.insert(0x5d,QString(0x5d));
        m_keymap.insert(0x5e,QString(0x5e));
        m_keymap.insert(0x5f,QString(0x5f));
        m_keymap.insert(0x60,QString(0x60));
    }

    void addNormalKeys()
    {
        m_keymap.insert(0x61,QString(0x3B1));
        m_keymap.insert(0x62,QString(0x3B2));
        m_keymap.insert(0x63,QString(0x3C8));
        m_keymap.insert(0x64,QString(0x3B4));
        m_keymap.insert(0x65,QString(0x3B5));
        m_keymap.insert(0x66,QString(0x3C6));
        m_keymap.insert(0x67,QString(0x3B3));
        m_keymap.insert(0x68,QString(0x3B7));
        m_keymap.insert(0x69,QString(0x3B9));
        m_keymap.insert(0x6a,QString(0x3BE));
        m_keymap.insert(0x6b,QString(0x3BA));
        m_keymap.insert(0x6c,QString(0x3BB));
        m_keymap.insert(0x6d,QString(0x3BC));
        m_keymap.insert(0x6e,QString(0x3BD));
        m_keymap.insert(0x6f,QString(0x3BF));
        m_keymap.insert(0x70,QString(0x3C0));
        m_keymap.insert(0x71,QString(0x3B));
        m_keymap.insert(0x72,QString(0x3C1));
        m_keymap.insert(0x73,QString(0x3C3));
        m_keymap.insert(0x74,QString(0x3C4));
        m_keymap.insert(0x75,QString(0x3B8));
        m_keymap.insert(0x76,QString(0x3C9));
        m_keymap.insert(0x77,QString(0x3C2));
        m_keymap.insert(0x78,QString(0x3C7));
        m_keymap.insert(0x79,QString(0x3C5));
        m_keymap.insert(0x7a,QString(0x3B6));
        m_keymap.insert(0x7b,QString(0x7b));
        m_keymap.insert(0x7c,QString(0x7c));
        m_keymap.insert(0x7d,QString(0x7d));
        m_keymap.insert(0x7e,QString(0x7e));
        m_keymap.insert(0x20,QString(0x20));
    }

    void addAccentKeys()
    {
        m_keymap.insert(0x07b1,QString(0x3AC));
        m_keymap.insert(0x07b2,QString(0x3AD));
        m_keymap.insert(0x07b3,QString(0x3AE));
        m_keymap.insert(0x07b4,QString(0x3AF));
        m_keymap.insert(0x07b5,QString(0x3CA));
        m_keymap.insert(0x07b6,QString(0x390));
        m_keymap.insert(0x07b7,QString(0x3CC));
        m_keymap.insert(0x07b8,QString(0x3CD));
        m_keymap.insert(0x07b9,QString(0x3CB));
        m_keymap.insert(0x07ba,QString(0x3B0));
        m_keymap.insert(0x07bb,QString(0x3CE));
        m_keymap.insert(0x07a1,QString(0x386));
        m_keymap.insert(0x07a2,QString(0x388));
        m_keymap.insert(0x07a3,QString(0x389));
        m_keymap.insert(0x07a4,QString(0x38A));
        m_keymap.insert(0x07a5,QString(0x3AA));
        m_keymap.insert(0x07a7,QString(0x38C));
        m_keymap.insert(0x07a8,QString(0x38E));
        m_keymap.insert(0x07a9,QString(0x3AB));
        m_keymap.insert(0x07ab,QString(0x38F));
    }

    void addAltedKeys()
    {
        m_keymap.insert(0xC1,QString(0x0385));
        m_keymap.insert(0xA1,QString(0x00B2));
        m_keymap.insert(0xA2,QString(0x00B3));
        m_keymap.insert(0xA3,QString(0x00A3));
        m_keymap.insert(0xA4,QString(0x00A7));
        m_keymap.insert(0xA5,QString(0x00B6));
        m_keymap.insert(0xA7,QString(0x00A4));
        m_keymap.insert(0xA8,QString(0x00B0));
        m_keymap.insert(0xA9,QString(0x00A6));
        m_keymap.insert(0xAA,QString(0x00B1));
        m_keymap.insert(0xAB,QString(0x00BD));
        m_keymap.insert(0xC4,QString(0x00AC));
        m_keymap.insert(0xAE,QString(0x20AC));
        m_keymap.insert(0xAF,QString(0x00AE));
        m_keymap.insert(0xB1,QString(0x00A5));
        m_keymap.insert(0xB6,QString(0x00AB));
        m_keymap.insert(0xB7,QString(0x00BB));
        m_keymap.insert(0xC7,QString(0x00A9));
    }

    void addGrekTonorAccentForHID()
    {
        m_accentKeymap.insert(QString(0x0384)+QString(0x03B1),QString(0x03AC));
        m_accentKeymap.insert(QString(0x0384)+QString(0x03B5),QString(0x03AD));
        m_accentKeymap.insert(QString(0x0384)+QString(0x03B7),QString(0x03AE));
        m_accentKeymap.insert(QString(0x0384)+QString(0x03B9),QString(0x03AF));
        m_accentKeymap.insert(QString(0x0384)+QString(0x03BF),QString(0x03CC));
        m_accentKeymap.insert(QString(0x0384)+QString(0x03C5),QString(0x03CD));
        m_accentKeymap.insert(QString(0x0384)+QString(0x03C9),QString(0x03CE));
        m_accentKeymap.insert(QString(0x0384)+QString(0x0391),QString(0x0386));
        m_accentKeymap.insert(QString(0x0384)+QString(0x0395),QString(0x0388));
        m_accentKeymap.insert(QString(0x0384)+QString(0x0397),QString(0x0389));
        m_accentKeymap.insert(QString(0x0384)+QString(0x0399),QString(0x038A));
        m_accentKeymap.insert(QString(0x0384)+QString(0x039F),QString(0x038C));
        m_accentKeymap.insert(QString(0x0384)+QString(0x03A5),QString(0x038E));
        m_accentKeymap.insert(QString(0x0384)+QString(0x03A9),QString(0x038F));
    }

    void addDiaeresisAccentForHID()
    {
        m_accentKeymap.insert(QString(0x00A8)+QString(0x03C5),QString(0x00FC));
        m_accentKeymap.insert(QString(0x00A8)+QString(0x03B9),QString(0x00EF));
        m_accentKeymap.insert(QString(0x00A8)+QString(0x03A5),QString(0x00DC));
        m_accentKeymap.insert(QString(0x00A8)+QString(0x0399),QString(0x00CF));
    }

    void addGreekDialytikaAccentForHID()
    {
        m_accentKeymap.insert(QString(0x0385)+QString(0x03C5),QString(0x03B0));
        m_accentKeymap.insert(QString(0x0385)+QString(0x03B9),QString(0x0390));
    }
};

#endif // GREEK_AUTOMATA_H

