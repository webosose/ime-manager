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


#ifndef CHINESE_AUTOMATA_H
#define CHINESE_AUTOMATA_H

#include <QEvent>
#include <QObject>
#include <QString>
#include <QStringList>

#include "automata.h"
#include "../openautomata/sunpinyinautomata.h"
#include "../openautomata/pyzyautomata.h"
#include "../openautomata/cangjieautomata.h"
#include "../openautomata/strokeautomata.h"

class ChineseAutomata : public Automata
{

public:
    ChineseAutomata();
    ~ChineseAutomata();

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
     QScopedPointer<Automata> m_automata;
     bool m_shifted;
};
#endif //CHINESE_AUTOMATA_H
