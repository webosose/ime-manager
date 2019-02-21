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


#ifndef CANGJIE_AUTOMATA_H
#define CANGJIE_AUTOMATA_H

#include <QEvent>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QDebug>
#include <QMap>
#include <QMultiMap>

#include "automata.h"
#include "trie.h"

class CangjieAutomata : public Automata
{
    Q_OBJECT

public:
    CangjieAutomata();
    ~CangjieAutomata();

    bool setLanguage (const QString &language);
    QString getLanguage();
    void suggestionSelected(int index);
    QString getPreedit();
    QString getCommit();
    bool processKeyEvent(Qt::Key keycode, Qt::KeyboardModifiers modifiers);
    QStringList getSuggestionList();
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

    void strokeComponentSelected(int index);
    QStringList getStrokeComponentList();
    int getStrokeComponentCount();

private:
    bool init();

    bool m_shift;
    QString m_language;
    QString m_preedit;
    QString m_preAlpha;
    QString m_commit;
    QMap <Qt::Key,QString> m_preMap;
    QMultiMap<QString,QString> m_cangjieMap;
    Trie m_trie;
    int m_curPage;
    QStringList m_totSuggestions;
    QStringList m_curSuggestions;
};
#endif //CANGJIE_AUTOMATA_H
