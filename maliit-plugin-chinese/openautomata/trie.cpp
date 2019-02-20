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

#include "trie.h"

#include <QMap>
#include <QScopedPointer>
#include <QSharedPointer>
#include <QChar>
#include <QStack>
#include <QList>
#include <QSet>

class TrieNode {

public:
    TrieNode(bool end)
    {
       this->end = end;
    }

    void add(QChar &c, bool end)
    {
        if (!m_kids.contains(c)) {
            m_kids.insert(c,QSharedPointer<TrieNode>(new TrieNode(end)));
        }
    }

    void addValue(const QString &val)
    {
        m_values << val;
    }

    const QStringList& getValues()
    {
        return m_values;
    }

    TrieNode* get(const QChar &c)
    {
        return m_kids[c].data();
    }

    bool contains(QChar &c)
    {
        return m_kids.contains(c);
    }

    QList<QChar> keys()
    {
        return m_kids.keys();
    }

    bool isEnd() {
        return end;
    }

private:
    QMap<QChar,QSharedPointer<TrieNode>> m_kids;
    QStringList m_values;
    bool end;
};

Trie::Trie()
{
    m_root.reset(new TrieNode(false));
}

Trie::~Trie()
{

}

void Trie::add(const QString &key,const QString &val)
{
    TrieNode *current = m_root.data();
    int length = key.size();
    for (int i=0; i<length; ++i) {
        QChar c = key[i];
        current->add(c,(i + 1 == length));
        current = current->get(c);
    }
    current->addValue(val);
}

QStringList& Trie::subStrings(const QString &prefix, QStringList &substrings)
{
    class defFilter: public TrieFilter {
         bool filter(const QString&) { return true;}
    } df;
    return subStrings(prefix,substrings,df);
}

QStringList& Trie::subStrings(const QString &prefix, QStringList &substrings, TrieFilter &filter)
{
    int length = prefix.size();
    if (length == 0) return substrings;

    TrieNode *current = m_root.data();
    for (int i=0; i<length; ++i) {
        QChar c = prefix[i];
        if (current->contains(c)) {
            current = current->get(c);
        } else {
            return substrings;
        }
    }

    if (current->isEnd()) {
        const QStringList& list = current->getValues();
        for (int i=0; i<list.size(); ++i) {
            if (filter.filter(list[i])) {
                substrings << list[i];
            }
        }
    }

    QStack<TrieNode*> st;
    QListIterator<QChar> iter(current->keys());
    while(iter.hasNext()) {
        st.push(current->get(iter.next()));
    }

    QSet<TrieNode*> visited;
    while(!st.empty()) {
        current = st.pop();
        visited.insert(current);
        if (current->isEnd()) {
            const QStringList& list = current->getValues();
            for (int i=0; i<list.size(); ++i) {
                if (filter.filter(list[i])) {
                    substrings << list[i];
                }
            }
        }
        iter = current->keys();
        while(iter.hasNext()) {
            TrieNode* tn = current->get(iter.next());
            if (!visited.contains(tn)) {
                st.push(tn);
            }
        }
    }
    return substrings;
}
