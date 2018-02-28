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

#ifndef DUMMYSERVICE_H
#define DUMMYSERVICE_H

#include <QtQuick>

class DummyService : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString appId READ appId WRITE setAppId)
public:
    DummyService(QObject *parent = 0);

    Q_INVOKABLE void call(const QString& uri, const QString& method, const QString& param);

    QString appId() const;
    void setAppId(const QString& id);

private:
    QString m_appId;
};
#endif // DUMMYSERVICE_H
