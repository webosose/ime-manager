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

#include "koreanautomata.h"
#include "automatautil.h"
#include <dlfcn.h>
#include <iconv.h>

#ifdef WORDS_BIGENDIAN
#define UCS4 "UCS-4BE"
#else
#define UCS4 "UCS-4LE"
#endif

#ifndef ICONV_CONST
#define ICONV_CONST
#endif

static const QString LIB_PATH = QString("%1%2").arg(IMEMANAGER_RESOURCE_PATH).arg("/libhangul.so");
static const quint32 SCANCODE_BACKSPACE  = 14;
static const quint32 SCANCODE_SPACE  = 57;
static const char* BUL_LAYOUT_KEYBOARD = "2";

void ucs4_to_utf8(char *buf, const ucschar *ucs4, size_t bufsize)
{
    size_t n;
    ICONV_CONST char*  inbuf;
    size_t inbytesleft;
    char*  outbuf;
    size_t outbytesleft;
    iconv_t cd;

    for (n = 0; ucs4[n] != 0; n++)
    continue;

    if (n == 0) {
    buf[0] = '\0';
    return;
    }

    cd = iconv_open("UTF-8", UCS4);
    if (cd == (iconv_t)(-1))
    return;

    inbuf = (char*)ucs4;
    inbytesleft = n * 4;
    outbuf = buf;
    outbytesleft = bufsize;
    iconv(cd, &inbuf, &inbytesleft, &outbuf, &outbytesleft);

    iconv_close(cd);

    if (outbytesleft > 0)
    *outbuf = '\0';
    else
    buf[bufsize - 1] = '\0';
}

KoreanAutomata::KoreanAutomata()
{
    hungle_lib_handle = dlopen (LIB_PATH.toStdString().c_str(),RTLD_LAZY);
    char *error;
    if (!hungle_lib_handle) {
        if((error = dlerror()) != NULL){
            fputs (error = dlerror(), stderr);
            qWarning() << "Unable to load libhangul.so " << error;
	}
        exit(1);
    }

    hangul_ic_new = (HANGUL_IC_NEW_FPTR*)dlsym(hungle_lib_handle,"hangul_ic_new");
    if ((error = dlerror()) != NULL)  {
        fputs(error, stderr);
        qWarning() << "Unable to call hangul_ic_new " << error;
        exit(1);
    }

    hic = hangul_ic_new(BUL_LAYOUT_KEYBOARD);

    hangul_ic_set_option = (HANGUL_IC_SET_OPTION*)dlsym(hungle_lib_handle,"hangul_ic_set_option");
    if ((error = dlerror()) != NULL)  {
        fputs(error, stderr);
        qWarning() << "Unable to call hangul_ic_set_option " << error;
        exit(1);
    }

    hangul_ic_set_option(hic, HANGUL_IC_OPTION_AUTO_REORDER, false);
    hangul_ic_set_option(hic, HANGUL_IC_OPTION_COMBI_ON_DOUBLE_STROKE, false);
    hangul_ic_set_option(hic, HANGUL_IC_OPTION_NON_CHOSEONG_COMBI, true);

    hangul_ic_process = (HANGUL_IC_PROCESS_FTR*)dlsym(hungle_lib_handle,"hangul_ic_process");
    if ((error = dlerror()) != NULL)  {
        fputs(error, stderr);
        qWarning() << "Unale to call hangul_ic_process " << error;
        exit(1);
    }

    hangul_ic_get_preedit_string = (HANGUL_IC_GET_PREEDIT_STRING*)dlsym(hungle_lib_handle,"hangul_ic_get_preedit_string");
    if ((error = dlerror()) != NULL)  {
        fputs(error, stderr);
        qWarning() << "Unale to call hangul_ic_get_preedit_string " << error;
        exit(1);
    }

    hangul_ic_get_commit_string = (HANGUL_IC_GET_COMMIT_STRING*)dlsym(hungle_lib_handle,"hangul_ic_get_commit_string");
    if ((error = dlerror()) != NULL)  {
        fputs(error, stderr);
        qWarning() << "Unale to call hangul_ic_get_commit_string  " << error;
        exit(1);
    }

    hangul_ic_backspace = (HANGUL_IC_BACK_SPACE*)dlsym(hungle_lib_handle,"hangul_ic_backspace");
    if ((error = dlerror()) != NULL)  {
        fputs(error, stderr);
        qWarning() << "Unale to call hangul_ic_backspace  " << error;
        exit(1);
    }

    hangul_ic_delete = (HANGUL_IC_DELETE*)dlsym(hungle_lib_handle,"hangul_ic_delete");
    if ((error = dlerror()) != NULL)  {
        fputs(error, stderr);
        qWarning() << "Unale to call hangul_ic_backspace  " << error;
        exit(1);
    }

    hangul_ic_reset = (HANGUL_IC_RESET*)dlsym(hungle_lib_handle,"hangul_ic_reset");
    if ((error = dlerror()) != NULL)  {
        fputs(error, stderr);
        qWarning() << "Unale to call hangul_ic_reset  " << error;
        exit(1);
    }

    hangul_ic_flush = (HANGUL_IC_FLUSH*)dlsym(hungle_lib_handle,"hangul_ic_flush");
    if ((error = dlerror()) != NULL)  {
        fputs(error, stderr);
        qWarning() << "Unale to call hangul_ic_flush  " << error;
        exit(1);
    }

    hangul_ic_is_empty = (HANGUL_IC_EMPTY*)dlsym(hungle_lib_handle,"hangul_ic_is_empty");
    if ((error = dlerror()) != NULL)  {
        fputs(error, stderr);
        qWarning() << "Unale to call hangul_ic_is_empty  " << error;
        exit(1);
    }

    hangul_ic_is_transliteration = (HANGUL_IC_TRANSLITERATION*)dlsym(hungle_lib_handle,"hangul_ic_is_transliteration");
    if ((error = dlerror()) != NULL)  {
        fputs(error, stderr);
        qWarning() << "Unale to call hangul_ic_is_transliteration  " << error;
        exit(1);
    }
}

KoreanAutomata::~KoreanAutomata()
{
    hangul_ic_delete(hic);
    dlclose(hungle_lib_handle);
}

void KoreanAutomata::setPreedit(const QString &preeditString, int cursorPos) {
    Q_UNUSED(cursorPos);
    m_surroundingText = preeditString;
    m_predictonSeed = m_surroundingText + m_preedit;
}

bool KoreanAutomata::processKeyEvent(quint32 nativeScanCode, Qt::KeyboardModifiers modifiers, bool isCapsLockOn, bool isNumLockOn)
{
    bool ret;
    char commit[32]  = {'\0', };
    char preedit[32] = {'\0', };

    if (nativeScanCode == SCANCODE_BACKSPACE) {
         ret =  hangul_ic_backspace(hic);
         ucs4_to_utf8(preedit, hangul_ic_get_preedit_string(hic), sizeof(preedit));
         ucs4_to_utf8(commit, hangul_ic_get_commit_string(hic), sizeof(commit));
         m_preedit = QString(preedit);
         m_commit = QString(commit);
         m_predictonSeed = (m_surroundingText.length() > 0 ? m_surroundingText: m_commit) + m_preedit;
         return ret;
    }

    quint32 ascii = nativeCodeToAscii(nativeScanCode,modifiers,isCapsLockOn,isNumLockOn);

    if (ascii == 0) return false;

    ret = hangul_ic_process(hic, ascii);
    bool isSpace = nativeScanCode == SCANCODE_SPACE;
    if (ret || isSpace) {
        ucs4_to_utf8(preedit, hangul_ic_get_preedit_string(hic), sizeof(preedit));
        ucs4_to_utf8(commit, hangul_ic_get_commit_string(hic), sizeof(commit));
        m_preedit = QString(preedit);
        m_commit = isSpace ? QString(commit) + " ": QString(commit);
        m_predictonSeed = (m_surroundingText.length() > 0 ? m_surroundingText: m_commit) + m_preedit;
    }
    return ret || isSpace;
}

bool KoreanAutomata::processKeysym(quint32 keysym)
{
    bool ret;
    char commit[32]  = {'\0', };
    char preedit[32] = {'\0', };

    if (keysym == SCANCODE_BACKSPACE) {
        ret =  hangul_ic_backspace(hic);
        ucs4_to_utf8(preedit, hangul_ic_get_preedit_string(hic), sizeof(preedit));
        ucs4_to_utf8(commit, hangul_ic_get_commit_string(hic), sizeof(commit));
        m_preedit = QString(preedit);
        m_commit = QString(commit);
        m_predictonSeed = (m_surroundingText.length() > 0 ? m_surroundingText: m_commit) + m_preedit;
        return ret;
    }

    ret = hangul_ic_process(hic, keysym);
    if (ret) {
        ucs4_to_utf8(preedit, hangul_ic_get_preedit_string(hic), sizeof(preedit));
        ucs4_to_utf8(commit, hangul_ic_get_commit_string(hic), sizeof(commit));
        m_preedit = QString(preedit);
        m_commit = QString(commit);
        m_predictonSeed = (m_surroundingText.length() > 0 ? m_surroundingText: m_commit) + m_preedit;
    }
    return ret;
}

void KoreanAutomata::reset()
{
    hangul_ic_reset(hic);
    AutomataBase::reset();
}
