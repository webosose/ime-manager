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

#ifndef TRIE_H
#define TRIE_H

#include <QString>
#include <QStringList>
#include <QScopedPointer>


class TrieNode;

class TrieFilter
{
public:
    virtual bool filter(const QString&) = 0;
};

class Trie
{
public:
    Trie();
    ~Trie();

    void add(const QString &key,const QString &val);
    QStringList& subStrings(const QString &prefix,QStringList &list);
    QStringList& subStrings(const QString &prefix,QStringList &list,TrieFilter &filter);

private:
   QScopedPointer<TrieNode> m_root;
};
#endif //TRIE_H
