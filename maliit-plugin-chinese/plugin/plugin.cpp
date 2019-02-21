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

#include "plugin.h"
#include "inputmethod.h"

#include <QtPlugin>

ChinesePlugin::ChinesePlugin()
    : m_inputMethod(0)
{
    allowedStates << Maliit::Hardware << Maliit::OnScreen;
}

QString ChinesePlugin::name() const
{
    return QString("ChinesePlugin");
}

MAbstractInputMethod *ChinesePlugin::createInputMethod(MAbstractInputMethodHost *host)
{
    if (!m_inputMethod)
        m_inputMethod = new ChineseInputMethod(host);
    return m_inputMethod;
    //return new ChineseInputMethod(host);
}

QSet<Maliit::HandlerState> ChinesePlugin::supportedStates() const
{
    if (m_inputMethod && !m_inputMethod->hasEnabledLanguages())
        return QSet<Maliit::HandlerState>();

    return allowedStates;
}
