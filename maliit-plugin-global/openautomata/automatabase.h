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

#ifndef AUTOMATABASE_H
#define AUTOMATABASE_H

#include <QString>
#include <QChar>
#include <QHash>
#include <QDebug>
#include <QSet>

class AutomataBase
{

public:

    AutomataBase();

    virtual ~AutomataBase();

    virtual void setPreedit(const QString &preeditString, int cursorPos) = 0;

    virtual QString getPreedit() {return m_preedit;}

    virtual QString getCommit() {return m_commit;}

    virtual bool processKeyEvent(quint32 nativeScanCode, Qt::KeyboardModifiers modifiers, bool isCapsLockOn, bool isNumLockOn);

    virtual bool processKeysym(quint32 keysym);

    virtual bool isPredictionSupported() = 0;

    virtual QString getWordForPrediction() {return m_surroundingText;}

    virtual void reset();

protected:
    QHash<quint32,QString> m_keymap;
    QHash<QString,QString> m_accentKeymap;
    QSet<QString> m_accents;
    QString m_accent;
    bool m_accentSelect;
    QString m_commit;
    QString m_preedit;
    QString m_surroundingText;
};

#endif // AUTOMATABASE_H
