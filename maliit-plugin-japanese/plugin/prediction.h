// Copyright (c) 2019 LG Electronics, Inc.
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

#ifndef PREDICTION_H
#define PREDICTION_H

#include <maliit/plugins/abstractinputmethodhost.h>
#include <QtQuick>
#include <QStringList>

class Prediction : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool active READ isActive NOTIFY activeChanged)
    Q_PROPERTY(int index READ getPredictionIndex NOTIFY predictionIndexChanged)
    Q_PROPERTY(QVariant list READ getPredictionList NOTIFY predictionListChanged)

public:
    Q_INVOKABLE void onSelected(int index);
    Q_INVOKABLE void clearPredictionList();

    Prediction(MAbstractInputMethodHost* host);

    void setPredictionIndex(int index);
    int getPredictionIndex();

    void setPredictionList(QStringList predictionList);
    QVariant getPredictionList();

    bool isActive() { return m_active; }
    void setActive(bool active);

Q_SIGNALS:
    void predictionListChanged();
    void predictionSelected(int index);
    void predictionIndexChanged(int index);
    void activeChanged(bool active);

private:
    MAbstractInputMethodHost* m_host;

    int m_predictionIndex;
    QStringList m_predictionList;
    bool m_active;
};

#endif //PREDICTION_H
