// Copyright (c) 2019 LG Electronics, Inc.
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

#ifndef __OPENWNNAUTOMATA_H__
#define __OPENWNNAUTOMATA_H__

#include <QEvent>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QDebug>
#include <QHash>
#include <vector>
#include <string>
#include <dlfcn.h>

typedef void*           (INIT_CONTEXT)();
typedef void            (SET_INPUT_MODE)(void*,int);
typedef bool            (PROCESS_KEY)(void*,int,std::wstring);
typedef std::wstring    (GET_PREEDIT)(void*);
typedef std::wstring    (GET_COMMIT)(void*);
typedef int             (CANDIDATE_COUNT)(void*);
typedef void            (CANDATE_SELECT)(void*,int);
typedef bool            (IS_COMPOSING)(void*);
typedef void            (RESET)(void*);
typedef void            (CLOSE)(void*);

typedef std::vector<std::wstring>* (GET_CANDIDATE_LIST)(void*);

class OpenWnnAutomata
{
public:

    enum OpenWnnMode {
        Hiragana = 0,
        Katakana,
        zenkaku,
        Direct
    };

    enum HIDMode {
        ROMAN_HIRA,
        ROMAN_KATA,
        HANKAKU,
        ZENKAKU,
        KANA_HIRA,
        KANA_KATA
    };

    class Kana {
    public:
        QString latin;
        QString latin_shifted;
        QString hira;
        QString kata;
        Kana(QString l, QString ls, QString h, QString k):latin(l), latin_shifted(ls), hira(h), kata(k) {}
        Kana() {}
    };

    OpenWnnAutomata();
    ~OpenWnnAutomata();

    void setInputMode(int mode);
    void setHidMode(int mode);
    bool processKeyEvent(Qt::Key keycode,quint32 nativeScanCode, Qt::KeyboardModifiers modifiers);
    bool processHIDKeyEvent(Qt::Key keycode,quint32 nativeScanCode, Qt::KeyboardModifiers modifiers, bool isCaps);

    QString getPreedit();
    QString getCommit();
    int candidateListItemCount();
    void candidateListItemSelected(int index);
    QStringList getCandidateList();
    bool isComposing();
    void reset();
    QString convHexToStr(unsigned int inChar);

private:

    void init();
    void *openWnn_lib_handle;
    void *context;
    OpenWnnMode m_inputMode;
    HIDMode m_hidMode;

    INIT_CONTEXT        *_initContext;
    SET_INPUT_MODE  *_setInputMode;
    PROCESS_KEY *_processKey;
    GET_PREEDIT *_getPreEdit;
    GET_COMMIT  *_getCommit;
    CANDIDATE_COUNT *_candidateCount;
    CANDATE_SELECT *_candidateSelect;
    IS_COMPOSING *_isComposing;
    RESET *_reset;
    CLOSE *_close;
    GET_CANDIDATE_LIST *_getCandidateList;

    QHash<quint32,Kana> m_kanaMap;
    QHash<quint32,QString> m_dMap;
};
#endif //__OPENWNNAUTOMATA_H__