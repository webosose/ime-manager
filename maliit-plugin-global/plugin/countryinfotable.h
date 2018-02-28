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

#ifndef COUNTRY_INFO_TABLE_H
#define COUNTRY_INFO_TABLE_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QScopedPointer>

class CountryInfoTable : public QObject
{
    Q_OBJECT

    // using singleton
private:
    static QScopedPointer<CountryInfoTable> s_instance;
    CountryInfoTable();

public:
    static CountryInfoTable *getInstance();
    static void releaseInstance();

    virtual ~CountryInfoTable();
    QString getCountryCode(QString country);
    QStringList getUrlSuggestions(QString country);
    QStringList getEmailSuggestions(QString country);
    QString conv3166ToCountryString(QString iso3166Code);
    int conv3166ToCountryLocale(QString iso3166Code);

protected:
    void init();
};

class CountryInfoElement
{
public:
    CountryInfoElement(QString code, QString urls, QString emails)
        : countryCode(code), urlSuggestions(urls), emailSuggestions(emails)
    {}

    QString countryCode;
    QString urlSuggestions;
    QString emailSuggestions;
};

#endif // COUNTRY_INFO_TABLE_H
