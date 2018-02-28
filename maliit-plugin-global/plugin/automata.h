// Copyright (c) 2013-2018 LG Electronics, Inc.
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
    // create with static method. global singleton expected.
    //static Automata* get();

    virtual bool setLanguage(const QString &language) = 0;
    virtual bool isSupportedLanguage(const QString &language) = 0;

    virtual QString getAutomataLanguageString(const QString &language) = 0;

    // reset automata. TODO: will this reset language too?
    virtual void reset() = 0;

    virtual void setPreedit(const QString &preeditString, int cursorPos) = 0;
    virtual QString getPreedit() = 0;

    virtual QString getCommit() = 0;

    // Key process may fail for special keys.
    virtual bool processKeyEvent(quint32 nativeScanCode, Qt::KeyboardModifiers modifiers, bool isCapsLockOn = false, bool isNumLockOn = false) = 0;

    virtual bool processKeysym(quint32 keysym) = 0;

    virtual bool isPredictionSupported() = 0;

    // returns the partial word currently used for generating suggestion list
    virtual QString getWordForPrediction() = 0;

    virtual QStringList getPredictionList(const QString &language) = 0;

    virtual void addWord(const QString &word) {}
};

#endif //AUTOMATA_H
