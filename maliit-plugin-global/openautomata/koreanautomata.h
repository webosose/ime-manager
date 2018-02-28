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

#ifndef KOREAN_AUTOMATA_H
#define KOREAN_AUTOMATA_H

#include "automatabase.h"
#include "hangul.h"
#include <QLocale>
#include <QDebug>

typedef HangulInputContext* (HANGUL_IC_NEW_FPTR)(const char*);
typedef bool (HANGUL_IC_PROCESS_FTR)(HangulInputContext *hic, int ascii);
typedef ucschar* (HANGUL_IC_GET_PREEDIT_STRING)(HangulInputContext *hic);
typedef ucschar* (HANGUL_IC_GET_COMMIT_STRING)(HangulInputContext *hic);
typedef ucschar* (HANGUL_IC_BACK_SPACE)(HangulInputContext *hic);
typedef ucschar* (HANGUL_IC_DELETE)(HangulInputContext *hic);
typedef ucschar* (HANGUL_IC_RESET)(HangulInputContext *hic);
typedef ucschar* (HANGUL_IC_FLUSH)(HangulInputContext *hic);
typedef ucschar* (HANGUL_IC_EMPTY)(HangulInputContext *hic);
typedef ucschar* (HANGUL_IC_TRANSLITERATION)(HangulInputContext *hic);
typedef void* (HANGUL_IC_SET_OPTION)(HangulInputContext *hic, int option, bool value);

class KoreanAutomata : public AutomataBase
{

public:
    KoreanAutomata();
    ~KoreanAutomata();

    void setPreedit(const QString &preeditString, int cursorPos) ;

    bool isPredictionSupported() {return true;}

    bool processKeyEvent(quint32 nativeScanCode, Qt::KeyboardModifiers modifiers, bool isCapsLockOn, bool isNumLockOn);

    bool processKeysym(quint32 keysym);

    QString getWordForPrediction() {return m_predictonSeed;}

    void reset();

    static AutomataBase* create()
    {
        return new KoreanAutomata();
    }

private:
    void *hungle_lib_handle;
    HangulInputContext *hic;
    HANGUL_IC_NEW_FPTR *hangul_ic_new;
    HANGUL_IC_PROCESS_FTR *hangul_ic_process;
    HANGUL_IC_GET_PREEDIT_STRING *hangul_ic_get_preedit_string;
    HANGUL_IC_GET_COMMIT_STRING *hangul_ic_get_commit_string;
    HANGUL_IC_BACK_SPACE *hangul_ic_backspace;
    HANGUL_IC_DELETE *hangul_ic_delete;
    HANGUL_IC_RESET *hangul_ic_reset;
    HANGUL_IC_FLUSH *hangul_ic_flush;
    HANGUL_IC_EMPTY *hangul_ic_is_empty;
    HANGUL_IC_TRANSLITERATION *hangul_ic_is_transliteration;
    HANGUL_IC_SET_OPTION *hangul_ic_set_option;

    QString m_predictonSeed;
};

#endif // ENGLISH_AUTOMATA_H
