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

#ifndef LANGUAGE_INFO_TABLE_H
#define LANGUAGE_INFO_TABLE_H

#include <QObject>
#include <QString>
#include <QScopedPointer>
#include <QLocale>

class LanguageInfoTablePrivate;

class LanguageInfoTable
{
    // using singleton
private:
    static QScopedPointer<LanguageInfoTable> s_instance;
    LanguageInfoTable();

public:
    static LanguageInfoTable *getInstance();
    static void releaseInstance();

    virtual ~LanguageInfoTable();
    QString getIso2Code(QString language);
    QString getIso1Code(QString language);
    QLocale::Script getScript(QString language);
    QString getOwnLanguage(QString language);

protected:
    void initializeHashTable();

private:
    Q_DISABLE_COPY(LanguageInfoTable)
    Q_DECLARE_PRIVATE(LanguageInfoTable)

    const QScopedPointer<LanguageInfoTablePrivate> d_ptr;
};

#endif // COUNTRY_INFO_TABLE_H
