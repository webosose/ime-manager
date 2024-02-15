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

#include "suggestion.h"

Suggestion::Suggestion()
    : m_suggestionList()
    , m_showNext(false)
    , m_showPrevious(false)
    , m_preedit("")
{
}

void Suggestion::setSuggestionList (QStringList suggestionList) {
    m_suggestionList = std::move(suggestionList);
    Q_EMIT suggestionListChanged();
}

void Suggestion::setPreedit(QString preedit) {
    m_preedit = preedit;
    Q_EMIT preeditChanged();
}

QVariant Suggestion::getSuggestionList() {
    return QVariant::fromValue(m_suggestionList);
}

void Suggestion::onSelected(int index) {
    Q_EMIT suggestionSelected(index);
}

void Suggestion::onNext() {
    Q_EMIT nextSuggestions();
}

void Suggestion::onPrevious() {
    Q_EMIT previousSuggestions();
}

void Suggestion::setNextAvailable(bool next) {
    m_showNext = next;
    Q_EMIT showNextChanged();
}

void Suggestion::setPreviousAvailable(bool previous) {
    m_showPrevious = previous;
    Q_EMIT showPreviousChanged();
}

void Suggestion::onModeButtonPressed() {
    Q_EMIT virtualModeButtonPressed();
}

void Suggestion::onPreeditBoxPressed() {
    Q_EMIT preeditBoxPressed(m_preedit);
}
