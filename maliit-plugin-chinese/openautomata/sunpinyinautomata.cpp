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

#include "sunpinyinautomata.h"
#include "languages.h"
#include "chinesekeymap.h"

#include <dlfcn.h>

#define SUN_VK_PAGE_UP       0xff55
#define SUN_VK_PAGE_DOWN     0xff56
#define SUN_VK_BACK_SPACE    0xff08
#define SUN_VK_DELETE        0xffff

static const int MAX_PRE_EDIT_LENGTH = 16;
static const int CANDIDATE_WINDOW_LENGTH = 8;
static const int NUM_MAP[] = {0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39};
static const QString LIB_PATH = QString("%1%2").arg(IMEMANAGER_RESOURCE_PATH).arg("/libsunpinyin.so.3.0");

SunpinyinAutomata::SunpinyinAutomata()
{
    sunpinyin_lib_handle = dlopen (LIB_PATH.toStdString().c_str(),RTLD_LAZY);
    char *error;
    if (!sunpinyin_lib_handle) {
       fputs (error = dlerror(), stderr);
       qWarning() << "@@@@ Unable to load libsunpinyin.so " << error;
       exit(1);
    }

    init_factory = (INIT_FACTORY*)dlsym(sunpinyin_lib_handle,"initFactory");
    if ((error = dlerror()) != NULL)  {
        fputs(error, stderr);
        qWarning() << "@@@@ Unable to call init " << error;
        exit(1);
    }

    init_view = (INIT_VIEW*)dlsym(sunpinyin_lib_handle,"initCIMIView");
    if ((error = dlerror()) != NULL)  {
        fputs(error, stderr);
        qWarning() << "@@@@ Unable to call initCIMIView " << error;
        exit(1);
    }

    onKeyEvent = (ON_KEY_EVENT*)dlsym(sunpinyin_lib_handle,"onKeyEvent");
    if ((error = dlerror()) != NULL)  {
       fputs(error, stderr);
       qWarning() << "@@@@ Unable to call onKeyEvent " << error;
       exit(1);
    }

    preEdit = (PREEDIT*)dlsym(sunpinyin_lib_handle,"getPredit");
    if ((error = dlerror()) != NULL)  {
        fputs(error, stderr);
        qWarning() << "@@@@ Unable to call getPredit " << error;
        exit(1);
    }

    commit = (COMMIT*)dlsym(sunpinyin_lib_handle,"getCommit");
    if ((error = dlerror()) != NULL)  {
        fputs(error, stderr);
        qWarning() << "@@@@ Unable to call getCommit " << error;
        exit(1);
    }

    candiList = (CANDI_LIST*)dlsym(sunpinyin_lib_handle,"getCandidateList");
    if ((error = dlerror()) != NULL)  {
        fputs(error, stderr);
        qWarning() << "@@@@ Unable to call getCandidateList " << error;
        exit(1);
    }

    total = (TOTAL*)dlsym(sunpinyin_lib_handle,"total");
    if ((error = dlerror()) != NULL)  {
        fputs(error, stderr);
        qWarning() << "@@@@ Unable to call total " << error;
        exit(1);
    }

    size = (SIZE*)dlsym(sunpinyin_lib_handle,"size");
    if ((error = dlerror()) != NULL)  {
        fputs(error, stderr);
        qWarning() << "@@@@ Unable to call size " << error;
        exit(1);
    }

    first = (FIRST*)dlsym(sunpinyin_lib_handle,"first");
    if ((error = dlerror()) != NULL)  {
        fputs(error, stderr);
        qWarning() << "@@@@ Unable to call first " << error;
        exit(1);
    }

    throwBackKey = (THROW_BACK_KEY*)dlsym(sunpinyin_lib_handle,"throwBackKey");
    if ((error = dlerror()) != NULL)  {
        fputs(error, stderr);
        qWarning() << "@@@@ Unable to call throwBackKey " << error;
        exit(1);
    }

    resetCall = (RESET*)dlsym(sunpinyin_lib_handle,"resetSession");
    if ((error = dlerror()) != NULL)  {
        fputs(error, stderr);
        qWarning() << "@@@@ Unable to call resetSession " << error;
        exit(1);
    }

    close = (CLOSE_SESSION*)dlsym(sunpinyin_lib_handle,"closeSession");
    if ((error = dlerror()) != NULL)  {
        fputs(error, stderr);
        qWarning() << "@@@@ Unable to call close " << error;
        exit(1);
    }
    m_shift = false;
    init();
}

SunpinyinAutomata::~SunpinyinAutomata()
{
    close(factory,view);
    dlclose(sunpinyin_lib_handle);
}

void SunpinyinAutomata::init()
{
    factory = init_factory(DICTIONARY_PATH);
    view = init_view(factory);

    m_pinyinMap[Qt::Key_A]  = 0x0061;
    m_pinyinMap[Qt::Key_B]  = 0x0062;
    m_pinyinMap[Qt::Key_C]  = 0x0063;
    m_pinyinMap[Qt::Key_D]  = 0x0064;
    m_pinyinMap[Qt::Key_E]  = 0x0065;
    m_pinyinMap[Qt::Key_F]  = 0x0066;
    m_pinyinMap[Qt::Key_G]  = 0x0067;
    m_pinyinMap[Qt::Key_H]  = 0x0068;
    m_pinyinMap[Qt::Key_I]  = 0x0069;
    m_pinyinMap[Qt::Key_J]  = 0x006A;
    m_pinyinMap[Qt::Key_K]  = 0x006B;
    m_pinyinMap[Qt::Key_L]  = 0x006C;
    m_pinyinMap[Qt::Key_M]  = 0x006D;
    m_pinyinMap[Qt::Key_N]  = 0x006E;
    m_pinyinMap[Qt::Key_O]  = 0x006F;
    m_pinyinMap[Qt::Key_P]  = 0x0070;
    m_pinyinMap[Qt::Key_Q]  = 0x0071;
    m_pinyinMap[Qt::Key_R]  = 0x0072;
    m_pinyinMap[Qt::Key_S]  = 0x0073;
    m_pinyinMap[Qt::Key_T]  = 0x0074;
    m_pinyinMap[Qt::Key_U]  = 0x0075;
    m_pinyinMap[Qt::Key_V]  = 0x0076;
    m_pinyinMap[Qt::Key_W]  = 0x0077;
    m_pinyinMap[Qt::Key_X]  = 0x0078;
    m_pinyinMap[Qt::Key_Y]  = 0x0079;
    m_pinyinMap[Qt::Key_Z]  = 0x007A;
}

bool SunpinyinAutomata::isNextSuggestionsAvailable()
{
    // fix : PLAT-60252
    int _total = getPreedit() == "a" ? total() - 1 : total();
    return first() + CANDIDATE_WINDOW_LENGTH < _total;
}

bool SunpinyinAutomata::isPreviousSuggestionsAvailable()
{
    return first() > 0;
}

void SunpinyinAutomata::nextSuggestions()
{
    if (isNextSuggestionsAvailable()) {
        onKeyEvent(view,SUN_VK_PAGE_DOWN,0,0);
    }
}

void SunpinyinAutomata::previousSuggestions()
{
    if (isPreviousSuggestionsAvailable()) {
        onKeyEvent(view,SUN_VK_PAGE_UP,0,0);
    }
}

void SunpinyinAutomata::reset()
{
    resetCall(view);
}

bool SunpinyinAutomata::isComposing()
{
    return getPreedit().length() != 0;
}

QString SunpinyinAutomata::getCommit()
{
    const char *comit = commit();
    return QString(comit);
}

QString SunpinyinAutomata::getPreedit()
{
    const char *pre = preEdit();
    return QString(pre);
}

void SunpinyinAutomata::shifted(bool shift)
{
    m_shift = shift;
}

bool SunpinyinAutomata::isShifted()
{
    return m_shift;
}

bool SunpinyinAutomata::setLanguage(const QString &language)
{
    m_language = language;
    return true;
}

QString SunpinyinAutomata::getLanguage()
{
    return m_language;
}

void SunpinyinAutomata::suggestionSelected(int index)
{
    onKeyEvent(view,NUM_MAP[index],NUM_MAP[index],0);
}

void SunpinyinAutomata::strokeComponentSelected(int index)
{
    Q_UNUSED(index);
}

bool SunpinyinAutomata::isDirectInput(Qt::Key keycode)
{
    return isDirectInputKey(keycode);
}

quint32 SunpinyinAutomata::chineseSymbolKeyMapping(Qt::Key keycode)
{
    return chineseSymbolUnicodeKey(keycode);
}

bool SunpinyinAutomata::processKeyEvent(Qt::Key keycode, Qt::KeyboardModifiers modifiers)
{
    int key;
    Q_UNUSED(modifiers);
    switch(keycode) {
    case Qt::Key_Backspace:
        key = SUN_VK_BACK_SPACE;
        break;
    default:
        key = m_pinyinMap[keycode];
    }
    onKeyEvent(view,key,key,0);
    validateComposingState();

    int *keyArr = throwBackKey();
    if (keyArr[0] == key) return false;
    return true;
}

void SunpinyinAutomata::validateComposingState()
{
    QString preEdit = getPreedit();
    if (preEdit.length() > MAX_PRE_EDIT_LENGTH)
        processKeyEvent(Qt::Key_Backspace,Qt::NoModifier);
}

QStringList SunpinyinAutomata::getSuggestionList()
{
    QStringList suggestions;
    std::vector<std::string> *list = candiList();
    for (size_t i=0; i < list->size(); ++i) {
        suggestions << QString::fromUtf8(list->at(i).c_str());
    }
    return suggestions;
}

int SunpinyinAutomata::getCandidatesNum()
{
    return size();
}

int SunpinyinAutomata::getStrokeComponentCount()
{
    return 0;
}

QStringList SunpinyinAutomata::getStrokeComponentList()
{
    QStringList stroke;
    return stroke;
}
