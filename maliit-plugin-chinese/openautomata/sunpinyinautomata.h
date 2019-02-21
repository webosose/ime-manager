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


#ifndef SUNPINYIN_AUTOMATA_H
#define SUNPINYIN_AUTOMATA_H

#include <QEvent>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QDebug>
#include <QMap>

#include "automata.h"

typedef void* (INIT_FACTORY)(const char*);
typedef void* (INIT_VIEW)(void*);
typedef void (ON_KEY_EVENT)(void*, unsigned, unsigned, unsigned);
typedef const char* (PREEDIT)();
typedef const char* (COMMIT)();
typedef std::vector<std::string>* (CANDI_LIST)();
typedef int (TOTAL)();
typedef int (SIZE)();
typedef int (FIRST)();
typedef int* (THROW_BACK_KEY)();
typedef void (RESET)(void*);
typedef void (CLOSE_SESSION)(void*,void*);

class SunpinyinAutomata : public Automata
{
    Q_OBJECT

public:
    SunpinyinAutomata();
    ~SunpinyinAutomata();

    bool setLanguage (const QString &language);
    QString getLanguage();
    void suggestionSelected(int index);
    void strokeComponentSelected(int index);
    QString getPreedit();
    QString getCommit();
    bool processKeyEvent(Qt::Key keycode, Qt::KeyboardModifiers modifiers);
    QStringList getSuggestionList();
    QStringList getStrokeComponentList();
    int getStrokeComponentCount();
    void shifted (bool shift);
    bool isShifted();
    bool isNextSuggestionsAvailable();
    bool isPreviousSuggestionsAvailable();
    void nextSuggestions();
    void previousSuggestions();
    void reset();
    bool isDirectInput(Qt::Key keycode);
    bool isComposing();
    int getCandidatesNum();
    quint32 chineseSymbolKeyMapping(Qt::Key keycode);

private:
    void init();
    void validateComposingState();

    void *sunpinyin_lib_handle;
    void *factory;
    void *view;
    INIT_FACTORY *init_factory;
    INIT_VIEW *init_view;
    ON_KEY_EVENT *onKeyEvent;
    PREEDIT *preEdit;
    COMMIT *commit;
    CANDI_LIST *candiList;
    TOTAL *total;
    SIZE *size;
    FIRST *first;
    THROW_BACK_KEY *throwBackKey;
    RESET *resetCall;
    CLOSE_SESSION *close;

    bool m_shift;
    QString m_language;
    QMap <Qt::Key,int> m_pinyinMap;

};
#endif //SUNPINYIN_AUTOMATA_H
