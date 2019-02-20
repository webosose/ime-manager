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

#ifndef SUGGESTION_H
#define SUGGESTION_H

#include <QtQuick>

class Suggestion : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool next READ isNextAvailable NOTIFY showNextChanged)
    Q_PROPERTY(bool previous READ isPreviousAvailable NOTIFY showPreviousChanged)
    Q_PROPERTY(QVariant list READ getSuggestionList NOTIFY suggestionListChanged)
    Q_PROPERTY(QString preedit READ getPreedit NOTIFY preeditChanged)

public:
    Q_INVOKABLE void onSelected(int index);
    Q_INVOKABLE void onNext();
    Q_INVOKABLE void onPrevious();
    Q_INVOKABLE void onModeButtonPressed();
    Q_INVOKABLE void onPreeditBoxPressed();

    Suggestion();

    void setSuggestionList(QStringList suggestionList);
    void setPreedit(QString preedit);
    QVariant getSuggestionList();
    QString getPreedit() { return m_preedit; }

    bool isNextAvailable() { return m_showNext; }
    bool isPreviousAvailable() { return m_showPrevious; }
    void setNextAvailable(bool next);
    void setPreviousAvailable(bool previous);

Q_SIGNALS:
    void showNextChanged();
    void showPreviousChanged();
    void suggestionListChanged();
    void preeditChanged();
    void suggestionSelected(int index);
    void nextSuggestions();
    void previousSuggestions();
    void virtualModeButtonPressed();
    void preeditBoxPressed(QString preedit);

private:
    QStringList m_suggestionList;
    bool m_showNext;
    bool m_showPrevious;
    QString m_preedit;
};
#endif //SUGGESTION_H
