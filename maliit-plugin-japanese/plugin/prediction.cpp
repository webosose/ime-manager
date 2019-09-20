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

#include "prediction.h"

#include <stdio.h>
#include <QHash>
#include <QLocale>

Prediction::Prediction(MAbstractInputMethodHost* host)
    : m_host(host)
    , m_predictionIndex(0)
    , m_predictionList()
    , m_active(false)
{
}

void Prediction::setPredictionIndex(int index)
{
    m_predictionIndex = index;
    Q_EMIT predictionIndexChanged(index);
}

int Prediction::getPredictionIndex()
{
    return m_predictionIndex;
}

void Prediction::setPredictionList(QStringList predictionList)
{
    qDebug() << __PRETTY_FUNCTION__;
    m_predictionList = predictionList;
    setPredictionIndex(0);
    setActive(0 < m_predictionList.length());
    Q_EMIT predictionListChanged();
}

QVariant Prediction::getPredictionList()
{
    return QVariant::fromValue(m_predictionList);
}

void Prediction::clearPredictionList()
{
    m_predictionList.clear();
    Q_EMIT predictionListChanged();
    setActive(false);
}

void Prediction::onSelected(int index)
{
    Q_EMIT predictionSelected(index);
}

void Prediction::setActive(bool active)
{
    if (active != m_active) {
        m_active = active;
        Q_EMIT activeChanged(active);
    }
}
