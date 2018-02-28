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

#include "automatabase.h"
#include "automatautil.h"

AutomataBase::AutomataBase()
{
    m_accentSelect = false;
}

AutomataBase::~AutomataBase()
{
   m_keymap.clear();
}

bool AutomataBase::processKeyEvent(quint32 nativeScanCode, Qt::KeyboardModifiers modifiers, bool isCapsLockOn, bool isNumLockOn)
{
    quint32 ascii = nativeCodeToAscii(nativeScanCode,modifiers,isCapsLockOn,isNumLockOn);
    QString value = m_keymap.value(ascii,"NULL");
    if (value == "NULL") return false;

    if (value[0] == '\\' && value.size() > 1 ) {
        m_accentSelect = false;
        m_accent = "";
        m_commit = value.right(value.size() - 1);
        return true;
    }

    if (m_accents.contains(value)) {
        m_accentSelect = true;
        m_accent = value;
        m_commit = "";
        return true;
    }

    if (m_accentSelect) {
        m_accentSelect = false;
        QString accentValue = m_accentKeymap.value(m_accent + value,"NULL");
        m_commit = (accentValue != "NULL") ? accentValue : m_accent + value;
        return true;
    }
    m_commit = value;
    return true;
}

bool AutomataBase::processKeysym(quint32 keysym)
{
    QString value = m_keymap.value(keysym,"NULL");
    if (value == "NULL") return false;
    m_commit = value;
    return true;
}

void AutomataBase::reset()
{
    m_preedit = "";
    m_commit = "";
    m_surroundingText = "";
    m_accent = "";
    m_accentSelect = false;
}
