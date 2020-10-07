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

#include "pyzyautomata.h"
#include "languages.h"
#include "chinesekeymap.h"

static const int MAX_PRE_EDIT_LENGTH = 16;
static const int CANDIDATE_WINDOW_LENGTH = 8;
static const QString LIB_PATH = "/usr/lib/libpyzy-1.0.so.0";
static const QString DB_PATH  = "/usr/share/pyzy";

PyzyAutomata::PyzyAutomata()
{
    pyzy_lib_handle = dlopen (LIB_PATH.toStdString().c_str(),RTLD_LAZY);
    char *error;
    if (!pyzy_lib_handle) {
        if((error = dlerror()) != NULL){
            fputs (error = dlerror(), stderr);
            qWarning() << "Unable to load libpyzy.so " << error;
	}
        exit(1);
    }

    initContext = (INIT_CONTEXT*)dlsym(pyzy_lib_handle,"initContext");
    if ((error = dlerror()) != NULL)  {
        fputs(error, stderr);
        qWarning() << "Unable to create initContext handle " << error;
        exit(1);
    }

    insertChar = (INSERT_CHAR*)dlsym(pyzy_lib_handle,"insertChar");
    if ((error = dlerror()) != NULL)  {
        fputs(error, stderr);
        qWarning() << "Unable to create insertChar handle " << error;
        exit(1);
    }

    removeChar = (REMOVE_CHAR*)dlsym(pyzy_lib_handle,"removeChar");
    if ((error = dlerror()) != NULL)  {
        fputs(error, stderr);
        qWarning() << "Unable to create removeChar handle " << error;
        exit(1);
    }

    hasCandidate = (HAS_CANDIDATE*)dlsym(pyzy_lib_handle,"hasCandidate");
    if ((error = dlerror()) != NULL)  {
        fputs(error, stderr);
        qWarning() << "Unable to create hasCandidate handle " << error;
        exit(1);
    }

    selectCandidate = (SELECT_CANDIDATE*)dlsym(pyzy_lib_handle,"selectCandidate");
    if ((error = dlerror()) != NULL)  {
        fputs(error, stderr);
        qWarning() << "Unable to create selectCandidate handle " << error;
        exit(1);
    }

    getCandidatesSize = (GET_CANDIDATES_SIZE*)dlsym(pyzy_lib_handle,"getCandidatesSize");
    if ((error = dlerror()) != NULL)  {
        fputs(error, stderr);
        qWarning() << "Unable to create getCandidatesSize handle " << error;
        exit(1);
    }

    getCandidate = (GET_CANDIDATE*)dlsym(pyzy_lib_handle,"getCandidate");
    if ((error = dlerror()) != NULL)  {
        fputs(error, stderr);
        qWarning() << "Unable to create getCandidate handle " << error;
        exit(1);
    }

    restText = (REST_TEXT*)dlsym(pyzy_lib_handle,"restText");
    if ((error = dlerror()) != NULL)  {
        fputs(error, stderr);
        qWarning() << "Unable to create restText handle " << error;
        exit(1);
    }

    auxiliaryText = (AUXILIARY_TEXT*)dlsym(pyzy_lib_handle,"auxiliaryText");
    if ((error = dlerror()) != NULL)  {
        fputs(error, stderr);
        qWarning() << "Unable to create auxiliaryText handle " << error;
        exit(1);
    }

    selectedText = (SELECTED_TEXT*)dlsym(pyzy_lib_handle,"selectedText");
    if ((error = dlerror()) != NULL)  {
        fputs(error, stderr);
        qWarning() << "Unable to create selectedText handle " << error;
        exit(1);
    }

    conversionText = (CONVERSION_TEXT*)dlsym(pyzy_lib_handle,"conversionText");
    if ((error = dlerror()) != NULL)  {
        fputs(error, stderr);
        qWarning() << "Unable to create conversionText handle " << error;
        exit(1);
    }

    commitText = (COMMIT_TEXT*)dlsym(pyzy_lib_handle,"commitText");
    if ((error = dlerror()) != NULL)  {
        fputs(error, stderr);
        qWarning() << "Unable to create commitText handle " << error;
        exit(1);
    }

    resetContext = (RESET_CONTEXT*)dlsym(pyzy_lib_handle,"resetContext");
    if ((error = dlerror()) != NULL)  {
        fputs(error, stderr);
        qWarning() << "Unable to create resetContext handle " << error;
        exit(1);
    }

    close = (CLOSE*)dlsym(pyzy_lib_handle,"close");
    if ((error = dlerror()) != NULL)  {
        fputs(error, stderr);
        qWarning() << "Unable to create close handle " << error;
        exit(1);
    }
    init();
}

PyzyAutomata::~PyzyAutomata()
{
    reset();
    close(context);
    dlclose(pyzy_lib_handle);
}

void PyzyAutomata::init()
{
    m_language = "";
    m_shift = false;
    m_cur_page = 0;
    std::string path = DB_PATH.toStdString();
    context = initContext(path,path);
}


bool PyzyAutomata::isNextSuggestionsAvailable()
{
    int total = getCandidatesNum();
    int noOfSuggestions = getPreedit().length() > 8 ? 2 : CANDIDATE_WINDOW_LENGTH;
    return total > 0 && (m_cur_page+1) * noOfSuggestions  <  total;
}

bool PyzyAutomata::isPreviousSuggestionsAvailable()
{
    return getCandidatesSize(context) > 0 && m_cur_page != 0;
}

void PyzyAutomata::nextSuggestions()
{
    if (isNextSuggestionsAvailable()) {
        m_cur_page++;
    }
}

void PyzyAutomata::previousSuggestions()
{
    if (isPreviousSuggestionsAvailable()) {
        m_cur_page--;
    }
}

void PyzyAutomata::reset()
{
    m_cur_page = 0;
    resetContext(context);
}

bool PyzyAutomata::isComposing()
{
    return getPreedit().length() != 0;
}

QString PyzyAutomata::getCommit()
{
    return  QString::fromStdString(commitText(context));
}

QString PyzyAutomata::getPreedit()
{
    QString preedit = QString::fromStdString(selectedText(context)+auxiliaryText(context));
    if (preedit.length() == 0)
        return QString::fromStdString(conversionText(context));
    return preedit;
}

void PyzyAutomata::shifted(bool shift)
{
    m_shift = shift;
}

bool PyzyAutomata::isShifted()
{
    return m_shift;
}

bool PyzyAutomata::setLanguage(const QString &language)
{
    init();
    m_language = language;
    return true;
}

QString PyzyAutomata::getLanguage()
{
    return m_language;
}

void PyzyAutomata::suggestionSelected(int index)
{
    int noOfSuggestions = getPreedit().length() > 8 ? 2 : CANDIDATE_WINDOW_LENGTH;
    selectCandidate(context, (m_cur_page * noOfSuggestions) + index);
    m_cur_page = 0;
}

void PyzyAutomata::strokeComponentSelected(int index)
{
    Q_UNUSED(index);
}

bool PyzyAutomata::isDirectInput(Qt::Key keycode)
{
    return isDirectInputKey(keycode);
}

quint32 PyzyAutomata::chineseSymbolKeyMapping(Qt::Key keycode)
{
    return chineseSymbolUnicodeKey(keycode);
}

bool PyzyAutomata::processKeyEvent(Qt::Key keycode, Qt::KeyboardModifiers modifiers)
{
    Q_UNUSED(modifiers);
    m_cur_page = 0;
    if (keycode == Qt::Key_Backspace) {
        return removeChar(context);
    }
    if (getPreedit().length() < MAX_PRE_EDIT_LENGTH) {
        int key = bopomofoInputkey(keycode);
        return insertChar(context,key);
    }
    return true;
}

QStringList PyzyAutomata::getSuggestionList()
{
    int totalSize = getCandidatesSize(context);

    QStringList suggestions;
    if (totalSize == 0)
        return suggestions;

    int noOfSuggestions = getPreedit().length() > 8 ? 2 : CANDIDATE_WINDOW_LENGTH;
    int start  = m_cur_page * noOfSuggestions;
    int end    =  start + noOfSuggestions < totalSize ? start + noOfSuggestions : start + (totalSize - start);

    for (int i=start; i<end; ++i) {
        suggestions << QString::fromStdString(getCandidate(context,i));
    }
    return suggestions;
}

int PyzyAutomata::getCandidatesNum()
{
    return getCandidatesSize(context);
}

int PyzyAutomata::getStrokeComponentCount()
{
    return 0;
}

QStringList PyzyAutomata::getStrokeComponentList()
{
    QStringList stroke;
    return stroke;
}

