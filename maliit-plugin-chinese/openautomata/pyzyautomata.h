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


#ifndef PYZY_AUTOMATA_H
#define PYZY_AUTOMATA_H

#include <QEvent>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QDebug>
#include <dlfcn.h>

#include "automata.h"

typedef void* (INIT_CONTEXT)(const std::string&, const std::string&);
typedef bool  (INSERT_CHAR)(void*,char);
typedef bool  (REMOVE_CHAR)(void*);
typedef bool  (HAS_CANDIDATE)(void*,int);
typedef bool  (SELECT_CANDIDATE)(void*,int);
typedef int   (GET_CANDIDATES_SIZE)(void*);

typedef const std::string& (GET_CANDIDATE)(void*, int);
typedef const std::string& (REST_TEXT)(void*);
typedef const std::string& (SELECTED_TEXT)(void*);
typedef const std::string& (CONVERSION_TEXT)(void*);
typedef const std::string& (AUXILIARY_TEXT)(void*);
typedef const std::string& (COMMIT_TEXT)(void*);

typedef void  (RESET_CONTEXT)(void*);
typedef void  (CLOSE)(void*);

class PyzyAutomata : public Automata
{
    Q_OBJECT

public:
    PyzyAutomata();
    ~PyzyAutomata();

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

    void *pyzy_lib_handle;
    void *context;

    INIT_CONTEXT        *initContext;
    INSERT_CHAR         *insertChar;
    REMOVE_CHAR         *removeChar;
    HAS_CANDIDATE       *hasCandidate;
    SELECT_CANDIDATE    *selectCandidate;
    GET_CANDIDATES_SIZE *getCandidatesSize;
    GET_CANDIDATE       *getCandidate;
    REST_TEXT           *restText;
    SELECTED_TEXT       *selectedText;
    CONVERSION_TEXT     *conversionText;
    AUXILIARY_TEXT      *auxiliaryText;
    COMMIT_TEXT         *commitText;
    RESET_CONTEXT       *resetContext;
    CLOSE               *close;

    bool m_shift;
    QString m_language;
    int m_cur_page;
};
#endif //PYZY_AUTOMATA_H
