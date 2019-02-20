// Copyright (c) 2017-2019 LG Electronics, Inc.
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

#include "chinesekeymap.h"

bool isDirectInputKey(Qt::Key keycode) {

    /* Qt::Key_Space(0x20) to Qt::Key_ydiaeresis(0x0ff) is the range Qt::Key has provided for the Text keys
       which can be directly commited as string this is needed to avoid the other function key
       to commit as string which may give strange behavior */

    if (keycode >= Qt::Key_Space && keycode <= Qt::Key_ydiaeresis)
        return true;

    switch ((int)keycode) {
    case 0xff01:
    case 0xff1a:
    case 0x3001:
    case 0x2026:
    case 0xff08:
    case 0xff09:
    case 0xff0c:
    case 0x3002:
    case 0xff1f:
    case 0xff5e:
        return true;
    default:
        return false;
    }
}

quint32 chineseSymbolUnicodeKey(Qt::Key keycode)
{
    switch (keycode) {
    case Qt::Key_QuoteLeft:
        return 0x00b7;
    case Qt::Key_BracketLeft:
        return 0x3010;
    case Qt::Key_BracketRight:
        return 0x3011;
    case Qt::Key_Backslash:
        return 0x3001;
    case Qt::Key_Apostrophe:
        return 0x2018;
    case Qt::Key_Period:
        return 0x3002;
    case Qt::Key_Slash:
        return 0x2019;
    case Qt::Key_Dollar:
        return 0x00a5;
    case Qt::Key_Bar:
        return 0x201D;
    case Qt::Key_QuoteDbl:
        return 0x201C;
    case Qt::Key_Less:
        return 0x300A;
    case Qt::Key_Greater:
        return 0x300B;
    case Qt::Key_Underscore:
        return 0x2014;
    case Qt::Key_ParenLeft:
        return 0xFF08;
    case Qt::Key_ParenRight:
        return 0xFF09;
    case Qt::Key_Colon:
        return 0xFF1A;
    case Qt::Key_Semicolon:
        return 0xFF1B;
    case Qt::Key_Exclam:
        return 0xFF01;
    default:
        return 0;
    }
}

quint32 bopomofoInputkey(Qt::Key keycode) {
    if (keycode >= Qt::Key_A && keycode <= Qt::Key_Z) {
        return keycode + 32;
    }
    return keycode;
}
