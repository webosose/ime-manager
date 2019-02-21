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

#ifndef LAYOUTLOADER_H
#define LAYOUTLOADER_H

#include <QObject>
#include <QString>
#include <QHash>
#include <QJsonObject>

class LayoutLoader : public QObject
{
    Q_OBJECT

public:
    typedef QHash<QString, QString> StringHash;

private:
    static StringHash s_hash;
    static void initFileTable();

public:
    LayoutLoader();
    LayoutLoader(const QString& language);
    LayoutLoader(const LayoutLoader& l);
    ~LayoutLoader();

    QJsonObject getLayout() const;
    bool setLanguage(QString language);
    QString getLanguage() const;
    bool operator==(const LayoutLoader &l) const;
    LayoutLoader& operator=(const LayoutLoader&);

private:
    const QString getFileName(QString language);
    void makeLayout(QJsonObject src);

private:
    QString m_language;
    QJsonObject m_json;
};

typedef LayoutLoader::StringHash StringHash;

#endif //LAYOUTLOADER_H
