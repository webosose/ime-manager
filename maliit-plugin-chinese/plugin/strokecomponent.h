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

#ifndef STROKE_COMPONENT_H
#define STROKE_COMPONENT_H

#include <QtQuick>

class StrokeComponent : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QVariant list READ getStrokeComponentList NOTIFY strokeComponentListChanged)

public:
    Q_INVOKABLE void onSelected(int index);

    StrokeComponent();

    void setStrokeComponentList(QStringList strokeComponentList);
    QVariant getStrokeComponentList();

Q_SIGNALS:
    void strokeComponentListChanged();
    void strokeComponentSelected(int index);

private:
    QStringList m_strokeComponentList;
};
#endif // STROKE_COMPONENT_H
