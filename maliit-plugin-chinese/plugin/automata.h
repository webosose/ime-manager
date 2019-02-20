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


#ifndef AUTOMATA_H
#define AUTOMATA_H

#include <QEvent>
#include <QObject>
#include <QString>
#include <QStringList>

class Automata : public QObject
{
    Q_OBJECT

public:
    virtual bool setLanguage (const QString &language) = 0;
    virtual QString getLanguage() = 0;
    virtual void suggestionSelected(int index) = 0;
    virtual void strokeComponentSelected(int index) = 0;
    virtual QString getPreedit() = 0;
    virtual QString getCommit() = 0;
    virtual bool processKeyEvent(Qt::Key keycode, Qt::KeyboardModifiers modifiers) = 0;
    virtual QStringList getSuggestionList() = 0;
    virtual QStringList getStrokeComponentList() = 0;
    virtual int getStrokeComponentCount() = 0;
    virtual void shifted (bool shift) = 0;
    virtual bool isShifted() = 0;
    virtual bool isNextSuggestionsAvailable() = 0;
    virtual bool isPreviousSuggestionsAvailable() = 0;
    virtual void nextSuggestions() = 0;
    virtual void previousSuggestions() = 0;
    virtual void reset() = 0;
    virtual bool isDirectInput(Qt::Key keycode) = 0;
    virtual bool isComposing() = 0;
    virtual int getCandidatesNum() = 0;
    virtual quint32 chineseSymbolKeyMapping(Qt::Key keycode) = 0;
};
#endif //AUTOMATA_H
