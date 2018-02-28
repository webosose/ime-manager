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

#ifndef WORDPREDICT_H
#define WORDPREDICT_H

#include <QString>
#include <QStringList>

class WordCount;

class WordPredict
{
public:
    WordPredict();
    ~WordPredict();

    bool setLanguage(const QString &language);
    QStringList getPredictionList(const QString &prefix);
    void addWord(const QString &word);

private:
    bool init();
    bool contains(const QString &word);
    void storeUserWords();

    QString m_language;
    QList<WordCount> freqWordList;
    QList<WordCount> userWordList;
};
#endif //WORDPREDICT_H
