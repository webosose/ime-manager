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

#include "globalautomata.h"
#include "../openautomata/wordpredict.h"
#include "../openautomata/openautomata.h"

#include <QDebug>

typedef enum {
    PREDICTION_METHOD_FREQUENCY,
    PREDICTION_METHOD_NONE
} PredictionMethod;

class GlobalAutomataPrivate
{
    Q_DECLARE_PUBLIC(GlobalAutomata)

public:
    GlobalAutomata * const q_ptr;

    QScopedPointer<WordPredict> predictor;
    QScopedPointer<OpenAutomata> automata;

    QString language;
    PredictionMethod predictionMethod;

    GlobalAutomataPrivate(GlobalAutomata *automata)
        : q_ptr(automata)
        , predictor(new WordPredict)
        , automata(new OpenAutomata)
        , predictionMethod(PREDICTION_METHOD_NONE)
    {}
};

GlobalAutomata::GlobalAutomata()
    : d_ptr(new GlobalAutomataPrivate(this))
{

}

GlobalAutomata::~GlobalAutomata()
{
}

bool GlobalAutomata::setLanguage(const QString &language)
{
    Q_D(GlobalAutomata);
    d->language = language;

    if (d->predictor->setLanguage(language)) {
        d->predictionMethod = PREDICTION_METHOD_FREQUENCY;
    }
    return d->automata->setLanguage(language);
}

bool GlobalAutomata::isSupportedLanguage(const QString &language)
{
    Q_D(GlobalAutomata);
    return d->automata->isSupportedLanguage(language);
}

QString GlobalAutomata::getAutomataLanguageString(const QString &language)
{
    Q_D(GlobalAutomata);
    return d->automata->getAutomataLanguageString(language);
}

void GlobalAutomata::reset()
{
    Q_D(GlobalAutomata);
    d->automata->reset();
}

QString GlobalAutomata::getPreedit()
{
    Q_D(GlobalAutomata);
    return d->automata->getPreedit();
}

void GlobalAutomata::setPreedit(const QString &preedit, int cursorPos)
{
    Q_D(GlobalAutomata);
    d->automata->setPreedit(preedit, cursorPos);
}

QString GlobalAutomata::getCommit()
{
    Q_D(GlobalAutomata);
    return d->automata->getCommit();
}

bool GlobalAutomata::processKeyEvent(quint32 nativeScanCode, Qt::KeyboardModifiers modifiers, bool isCapsLockOn, bool isNumLockOn)
{
    Q_D(GlobalAutomata);
    return d->automata->processKeyEvent(nativeScanCode, modifiers, isCapsLockOn, isNumLockOn);
}

bool GlobalAutomata::processKeysym(quint32 keysym)
{
    Q_D(GlobalAutomata);
    return d->automata->processKeysym(keysym);
}

bool GlobalAutomata::isPredictionSupported()
{
    Q_D(GlobalAutomata);
    if (d->predictionMethod == PREDICTION_METHOD_NONE)
        return false;
    else
        return true;
}

QString GlobalAutomata::getWordForPrediction()
{
    Q_D(GlobalAutomata);
    return d->automata->getWordForPrediction();
}

QStringList GlobalAutomata::getPredictionList(const QString &language)
{
    Q_D(GlobalAutomata);
    switch (d->predictionMethod) {
    case PREDICTION_METHOD_FREQUENCY:
        return d->predictor->getPredictionList(getWordForPrediction());
        break;
    default:
        return QStringList();
    }
}

void GlobalAutomata::addWord(const QString &word)
{
    Q_D(GlobalAutomata);
    d->predictor->addWord(word);
}
