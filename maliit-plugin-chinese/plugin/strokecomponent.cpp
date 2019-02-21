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

#include "strokecomponent.h"

StrokeComponent::StrokeComponent()
    :m_strokeComponentList()
{
}

void StrokeComponent::setStrokeComponentList(QStringList strokeComponentList)
{
    m_strokeComponentList = strokeComponentList;
    Q_EMIT strokeComponentListChanged();
}

QVariant StrokeComponent::getStrokeComponentList()
{
    return QVariant::fromValue(m_strokeComponentList);
}

void StrokeComponent::onSelected(int index)
{
    Q_EMIT strokeComponentSelected(index);
}
