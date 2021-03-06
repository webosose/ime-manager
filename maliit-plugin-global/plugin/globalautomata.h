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

#ifndef GLOBAL_AUTOMATA_H
#define GLOBAL_AUTOMATA_H

#include "automata.h"

#include <QHash>

class GlobalAutomataPrivate;

class GlobalAutomata : public Automata
{
public:
    GlobalAutomata();
    ~GlobalAutomata();

    virtual bool setLanguage(const QString &language);
    virtual bool isSupportedLanguage(const QString &language);
    virtual QString getAutomataLanguageString(const QString &language);
    virtual void reset();
    virtual QString getPreedit();
    virtual void setPreedit(const QString &preedit, int cursorPos);
    virtual QString getCommit();
    virtual bool processKeyEvent(quint32 nativeScanCode, Qt::KeyboardModifiers modifiers, bool isCapsLockOn = false, bool isNumLockOn = false);
    virtual bool processKeysym(quint32 keysym);
    virtual bool isPredictionSupported();
    virtual QString getWordForPrediction();
    virtual QStringList getPredictionList(const QString &language);
    virtual void addWord(const QString &word);

protected:
    const QScopedPointer<GlobalAutomataPrivate> d_ptr;

private:
    Q_DISABLE_COPY(GlobalAutomata)
    Q_DECLARE_PRIVATE(GlobalAutomata)
};

#endif //GLOBAL_AUTOMATA_H
