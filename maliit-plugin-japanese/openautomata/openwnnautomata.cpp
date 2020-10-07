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

#include "openwnnautomata.h"

static const int MAX_PRE_EDIT_LENGTH = 16;
static const int CANDIDATE_WINDOW_LENGTH = 8;
static const QString LIB_PATH = "/usr/lib/maliit/plugins/libWnnJpn.so";

static const int KEY_ESC       = 0x01000012;
static const int KEY_LEFT      = 0x01000012;
static const int KEY_RIGHT     = 0x01000014;
static const int KEY_BACKSPACE = 0x01000003;
static const int KEY_SPACE     = 0x20;
static const int KEY_ENTER     = 0x01000005;
static const int KEY_RETURN    = 0x01000004;

OpenWnnAutomata::OpenWnnAutomata()
{
    openWnn_lib_handle = dlopen (LIB_PATH.toStdString().c_str(),RTLD_LAZY);
    char *error;
    if (!openWnn_lib_handle) {
        if((error = dlerror()) != NULL){
            fputs (error = dlerror(), stderr);
            qWarning() << "@@@@ Unable to load libWnnJpn.so " << error;
	}
        exit(1);
    }

    _initContext = (INIT_CONTEXT*)dlsym(openWnn_lib_handle,"initOpenwnn");
    if ((error = dlerror()) != NULL)  {
        fputs(error, stderr);
        qWarning() << "@@@@ Unable to call initOpenwnn " << error;
        exit(1);
    }

    _setInputMode = (SET_INPUT_MODE*)dlsym(openWnn_lib_handle,"setInputMode");
    if ((error = dlerror()) != NULL)  {
        fputs(error, stderr);
        qWarning() << "@@@@ Unable to call setInputMode " << error;
        exit(1);
    }

    _processKey = (PROCESS_KEY*)dlsym(openWnn_lib_handle,"processKey");
    if ((error = dlerror()) != NULL)  {
        fputs(error, stderr);
        qWarning() << "@@@@ Unable to call processKey " << error;
        exit(1);
    }

    _getPreEdit = (GET_PREEDIT*)dlsym(openWnn_lib_handle,"getPreedit");
    if ((error = dlerror()) != NULL)  {
        fputs(error, stderr);
        qWarning() << "@@@@ Unable to call getPreedit " << error;
        exit(1);
    }

    _getCommit = (GET_COMMIT*)dlsym(openWnn_lib_handle,"getCommit");
    if ((error = dlerror()) != NULL)  {
        fputs(error, stderr);
        qWarning() << "@@@@ Unable to call getCommit " << error;
        exit(1);
    }

    _candidateCount = (CANDIDATE_COUNT*)dlsym(openWnn_lib_handle,"candidateListItemCount");
    if ((error = dlerror()) != NULL)  {
        fputs(error, stderr);
        qWarning() << "@@@@ Unable to call candidateListItemCount " << error;
        exit(1);
    }

    _candidateSelect = (CANDATE_SELECT*)dlsym(openWnn_lib_handle,"candidateListItemSelected");
    if ((error = dlerror()) != NULL)  {
        fputs(error, stderr);
        qWarning() << "@@@@ Unable to call candidateListItemSelected " << error;
        exit(1);
    }

    _isComposing = (IS_COMPOSING*)dlsym(openWnn_lib_handle,"isComposing");
    if ((error = dlerror()) != NULL)  {
        fputs(error, stderr);
        qWarning() << "@@@@ Unable to call isComposing " << error;
        exit(1);
    }

    _getCandidateList = (GET_CANDIDATE_LIST*)dlsym(openWnn_lib_handle,"getCandidateList");
    if ((error = dlerror()) != NULL)  {
        fputs(error, stderr);
        qWarning() << "@@@@ Unable to call getCandidateList " << error;
        exit(1);
    }

    _reset = (RESET*)dlsym(openWnn_lib_handle,"reset");
    if ((error = dlerror()) != NULL)  {
        fputs(error, stderr);
        qWarning() << "@@@@ Unable to call reset " << error;
        exit(1);
    }

    _close = (CLOSE*)dlsym(openWnn_lib_handle,"close");
    if ((error = dlerror()) != NULL)  {
        fputs(error, stderr);
        qWarning() << "@@@@ Unable to call close " << error;
        exit(1);
    }
    init();
}

void OpenWnnAutomata::init()
{
    context = _initContext();
    m_kanaMap.reserve(60);
    m_kanaMap[1]  = Kana("","「","ろ","ロ");
    m_kanaMap[2]  = Kana("1","!","ぬ","ヌ");
    m_kanaMap[3]  = Kana("2","\"","ふ","フ");
    m_kanaMap[4]  = Kana("3","#","あ","ア");
    m_kanaMap[5]  = Kana("4","$","う","ウ");
    m_kanaMap[6]  = Kana("5","%","え","エ");
    m_kanaMap[7]  = Kana("6","&","お","オ");
    m_kanaMap[8]  = Kana("7","'","や","ヤ");
    m_kanaMap[9]  = Kana("8","(","ゆ","ユ");
    m_kanaMap[10] = Kana("9",")","よ","ヨ");
    m_kanaMap[11] = Kana("0","」","わ","ワ");
    m_kanaMap[12] = Kana("-","=","ほ","ホ");
    m_kanaMap[13] = Kana("^","~","へ","ヘ");
    m_kanaMap[13] = Kana("¥","|","へ","ヘ");
    m_kanaMap[16] = Kana("q","Q","た","タ");
    m_kanaMap[17] = Kana("w","W","て","テ");
    m_kanaMap[18] = Kana("e","E","い","イ");
    m_kanaMap[19] = Kana("r","R","す","ス");
    m_kanaMap[20] = Kana("t","T","か","カ");
    m_kanaMap[21] = Kana("y","Y","ん","ン");
    m_kanaMap[22] = Kana("u","U","な","ナ");
    m_kanaMap[23] = Kana("i","I","に","ニ");
    m_kanaMap[24] = Kana("o","O","ら","ラ");
    m_kanaMap[25] = Kana("p","P","せ","セ");
    m_kanaMap[26] = Kana("@","'","゛","゛");
    m_kanaMap[27] = Kana("[","{","゜","゜");
    m_kanaMap[28] = Kana("]","}","む","ム");
    m_kanaMap[30] = Kana("a","A","ち","チ");
    m_kanaMap[31] = Kana("s","S","と","ト");
    m_kanaMap[32] = Kana("d","D","し","シ");
    m_kanaMap[33] = Kana("f","F","は","ハ");
    m_kanaMap[34] = Kana("g","G","き","キ");
    m_kanaMap[35] = Kana("h","H","く","ク");
    m_kanaMap[36] = Kana("j","J","ま","マ");
    m_kanaMap[37] = Kana("k","K","の","ノ");
    m_kanaMap[38] = Kana("l","L","り","リ");
    m_kanaMap[39] = Kana(";","+","れ","レ");
    m_kanaMap[40] = Kana(":","*","け","ケ");
    m_kanaMap[43] = Kana("]","}","む","ム");
    m_kanaMap[44] = Kana("z","Z","つ","ツ");
    m_kanaMap[45] = Kana("x","X","さ","サ");
    m_kanaMap[46] = Kana("c","C","そ","ソ");
    m_kanaMap[47] = Kana("v","V","ひ","ヒ");
    m_kanaMap[48] = Kana("b","B","こ","コ");
    m_kanaMap[49] = Kana("n","N","み","ミ");
    m_kanaMap[50] = Kana("m","M","も","モ");
    m_kanaMap[51] = Kana(",","<","ね","ネ");
    m_kanaMap[52] = Kana(".",">","る","ル");
    m_kanaMap[53] = Kana("/","?","め","メ");

    m_dMap[0xE38080] = " ";
    m_dMap[0xEFBCA0] = "@";
    m_dMap[0xEFBC9F] = "?";
    m_dMap[0xEFBC8E] = ".";
    m_dMap[0xEFBC8C] = ",";

    m_inputMode = Hiragana;
    m_hidMode = ROMAN_HIRA;
}

OpenWnnAutomata::~OpenWnnAutomata()
{
    _close(context);
    dlclose(openWnn_lib_handle);
}

void OpenWnnAutomata::setInputMode(int mode)
{
    m_inputMode = (OpenWnnMode)mode;
    _setInputMode(context,m_inputMode);
}

void OpenWnnAutomata::setHidMode(int mode)
{
    m_hidMode = (HIDMode)mode;
    switch (m_hidMode)
    {
    case HANKAKU:
        setInputMode(Direct);
        break;
    case ZENKAKU:
        setInputMode(zenkaku);
        break;
    case ROMAN_HIRA:
        setInputMode(Hiragana);
        break;
    case ROMAN_KATA:
        setInputMode(Katakana);
        break;
    default:
        break;
    }
}

QString OpenWnnAutomata::convHexToStr(unsigned int inChar)
{
    QByteArray dst;
    for (int i = 0; i < 4; i++) {
        unsigned char tmp = (inChar >> (8 * (3 - i))) & 0xff;
        if (tmp != 0) {
            dst.append(tmp);
        }
    }
    return QString::fromUtf8(dst.constData(), dst.size());
}

bool OpenWnnAutomata::processHIDKeyEvent(Qt::Key keycode,quint32 nativeScanCode, Qt::KeyboardModifiers modifiers, bool isCaps=false)
{
    QString input;
    switch (m_hidMode) {
        case ROMAN_HIRA:
        case ROMAN_KATA:
            input =  (modifiers & Qt::ShiftModifier) ? m_kanaMap[nativeScanCode].latin_shifted : m_kanaMap[nativeScanCode].latin;
            break;
        case HANKAKU:
        case ZENKAKU:
            if (modifiers & Qt::ShiftModifier) {
                input = isCaps ? m_kanaMap[nativeScanCode].latin : m_kanaMap[nativeScanCode].latin_shifted;
            } else {
                input = isCaps ? m_kanaMap[nativeScanCode].latin_shifted : m_kanaMap[nativeScanCode].latin;
            }
            break;
        case KANA_HIRA:
            input = m_kanaMap[nativeScanCode].hira;
            break;
        case KANA_KATA:
            input = m_kanaMap[nativeScanCode].kata;
            break;
    }
    return _processKey(context,keycode,input.toStdWString());
}

bool OpenWnnAutomata::processKeyEvent(Qt::Key keycode,quint32 nativeScanCode, Qt::KeyboardModifiers modifiers)
{
    if (nativeScanCode == 0x64) {
        keycode = Qt::Key_Space;
    }
    QString scanTxt = m_dMap[nativeScanCode];
    if (scanTxt.length() == 0)
        scanTxt = convHexToStr(nativeScanCode);
    return _processKey(context,keycode,scanTxt.toStdWString());
}

QString OpenWnnAutomata::getPreedit()
{
    return QString::fromStdWString(_getPreEdit(context));
}

QString OpenWnnAutomata::getCommit()
{
    return QString::fromStdWString(_getCommit(context));
}

int OpenWnnAutomata::candidateListItemCount()
{
    return _candidateCount(context);
}

void OpenWnnAutomata::candidateListItemSelected(int index)
{
    _candidateSelect(context,index);
}

QStringList OpenWnnAutomata::getCandidateList()
{
    QStringList suggestions;
    std::vector<std::wstring> *list = _getCandidateList(context);
    for (size_t i=0; i<list->size(); ++i) {
        suggestions << QString::fromStdWString(list->at(i));
    }
    return suggestions;
}

bool OpenWnnAutomata::isComposing()
{
    return _isComposing(context);
}

void OpenWnnAutomata::reset()
{
    _reset(context);
}
