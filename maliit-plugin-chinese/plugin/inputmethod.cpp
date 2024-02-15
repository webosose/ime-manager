// Copyright (c) 2017-2023 LG Electronics, Inc.
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

#include "inputmethod.h"
#include "chineseautomata.h"
#include "languages.h"

#include <maliit/plugins/abstractinputmethodhost.h>
#include <maliit/plugins/updateevent.h>
#ifndef UBUNTU_DESKTOP_BUILD
#include <qpa/qwindowsysteminterface.h>
#endif
#include <linux/input.h>

#include <QDebug>

namespace {
    // attribute names for propertiesChanged in updateEvent
    const char * const AnchorPositionAttribute = "anchorPosition";
    const char * const AutoCapitalizationAttribute = "autocapitalizationEnabled";
    const char * const ContentTypeAttribute = "contentType";
    const char * const EnterKeyTypeAttribute = "enterKeyType";
    const char * const CorrectionAttribute = "correctionEnabled";
    const char * const CursorPositionAttribute = "cursorPosition";
    const char * const CursorRectAttribute = "cursorRectangle";
    const char * const FocusStateAttribute = "focusState";
    const char * const HasSelectionAttribute = "hasSelection";
    const char * const HiddenTextAttribute = "hiddenText";
    const char * const InputMethodModeAttribute = "inputMethodMode";
    const char * const SuggestionAttribute = "suggestionEnabled";
    const char * const PreeditClickPosAttribute = "preeditClickPos";
    const char * const SurroundingTextAttribute = "surroundingText";
    const char * const ToolbarAttribute = "toolbar";
    const char * const ToolbarIdAttribute = "toolbarId";
    const char * const WinId = "winId";
}

static const quint32 EVDEV_OFFSET   = 8;
static const quint32 MAGIC_SCANCODE_OK   = 0;    // from Device: "OK" button of Magic-remote
static const quint32 REMOTE_SCANCODE_OK  = 36;   // from Device: "OK" button of Normal-remote
static const quint32 SCANCODE_BACK       = 420;  // from Device: "Back" button of Magic-remote
static const quint32 SCANCODE_POINTERON  = 1206; // from Device: Device sends the keycode when the pointer appears
static const quint32 SCANCODE_POINTEROFF = 1207; // from Device: Device sends the keycode when the pointer disappears
static const quint32 SCANCODE_RALT       = 108;  // from HID: Right Alt changes the language of the VKB
static const quint32 SCANCODE_PLAY       = 0xD7;  // from Remote
static const quint32 SCANCODE_PAUSE      = 0x7F;  // from Remote
static const quint32 SCANCODE_STOP       = 0x88;  // from Remote
static const quint32 SCANCODE_REW        = 0xB0;  // from Remote
static const quint32 SCANCODE_FF         = 0xD8;  // from Remote
static const quint32 SCANCODE_REC        = 0xAF;  // from Remote
static const quint32 SCANCODE_RED        = 406;  // from Remote
static const quint32 SCANCODE_GRN        = 407;  // from Remote
static const quint32 SCANCODE_YEL        = 408;  // from Remote
static const quint32 SCANCODE_BLU        = 409;  // from Remote
static const quint32 SCANCODE_UNKNOWN    = 0xffffffff;
static const unsigned int KEY_BACKSPACE_VKB = 20;
static const quint32 KEY_RETURN = 40;
static const unsigned int KEY_SPACE_VKB = 137;
static const unsigned int KEY_TAB_VKB = 21;
static const quint32 CHINESE_SPACE_KEYCODE = 0x3000;
static const QString SHIFTED_STATE = "Normal-Shift";
static const QString NORMAL_STATE = "Normal";
static const quint32 SCANCODE_LEFT_SHIFT   = 50;
static const quint32 SCANCODE_RIGHT_SHIFT  = 62;

static const quint32 DIRECTION_LEFT    = 0;
static const quint32 DIRECTION_RIGHT   = 1;

static const quint32 MOUSE_EVENT    = 1;
static const quint32 KEYBOARD_EVENT = 2;
static const quint32 TOUCH_EVENT    = 3;

enum {
    KEYSYM_ASTERISK = 0x002a,
    KEYSYM_PLUS,
    KEYSYM_COMMA,
    KEYSYM_MINUS,
    KEYSYM_PERIOD,
    KEYSYM_SLASH,
    KEYSYM_0,
    KEYSYM_1,
    KEYSYM_2,
    KEYSYM_3,
    KEYSYM_4,
    KEYSYM_5,
    KEYSYM_6,
    KEYSYM_7,
    KEYSYM_8,
    KEYSYM_9,
    KEYSYM_VOIDSYMBOL = 0xffffff
};

class ChineseInputMethodPrivate
{
    Q_DECLARE_PUBLIC(ChineseInputMethod)

public:
    ChineseInputMethod *const q_ptr;
    bool keyLocked;
    quint32 pressedScanCode;
    bool sendEnterKey;
    int dirCursorMoveKey;

    ChineseInputMethodPrivate(ChineseInputMethod *im)
        : q_ptr(im)
        , keyLocked(false)
        , pressedScanCode(SCANCODE_UNKNOWN)
        , sendEnterKey(false)
        , dirCursorMoveKey(-1)
    {}


  bool changeKeyCodes(Qt::Key &keyCode, quint32 &nativeScanCode)
  {
    switch (keyCode) {
        case Qt::Key_Clear:
            keyCode = Qt::Key_Backspace;
            nativeScanCode = KEY_BACKSPACE + 8;
            return true;
        default:
            break;
    }
    return false;
  }
};

ChineseInputMethod::ChineseInputMethod(MAbstractInputMethodHost *host)
    : MAbstractInputMethod(host)
    , d_ptr(new ChineseInputMethodPrivate(this))
    , currentLanguageIndex(0)
    , m_automata(new ChineseAutomata)
    , m_suggestion(new Suggestion())
    , m_strokeComponent(new StrokeComponent())
    , m_keyboard(new Keyboard(host, m_suggestion.data(), m_strokeComponent.data()))
    , m_sendEnterKey(false)
    , dirCursorMoveKey(-1)
    , pressedScancode(SCANCODE_UNKNOWN)
    , m_bNumberKey(false)
    , m_keySym(0)
{
    currentLanguageIndex = -1;

    connect(m_suggestion.data(), SIGNAL (suggestionSelected(int)),
            this, SLOT (onSuggestionSelected(int)));

    connect(m_strokeComponent.data(), SIGNAL (strokeComponentSelected(int)),
            this, SLOT (onStrokeComponentSelected(int)));

    connect(m_keyboard.data(), SIGNAL (keyPressed(quint32, Qt::KeyboardModifiers, int)),
            this, SLOT (onVirtualKeyPressed(quint32, Qt::KeyboardModifiers, int)));

    connect(m_keyboard.data(), SIGNAL (switchContext(Maliit::SwitchDirection)),
            this, SLOT (onSwitchContext(Maliit::SwitchDirection)));

    connect(m_suggestion.data(), SIGNAL (nextSuggestions()),
            this, SLOT (onNextSuggestions()));

    connect(m_suggestion.data(), SIGNAL (previousSuggestions()),
            this, SLOT (onPreviousSuggestions()));

    connect(m_keyboard.data(), SIGNAL (shiftKeyPressed()),
            this, SLOT (onShiftKeyPressed()));

    connect(m_keyboard.data(), SIGNAL (symbolKeyPressed(QString)),
            this, SLOT (onSymbolKeyPressed(QString)));

    connect(m_keyboard.data(), SIGNAL (textKeyPressed(QString)),
            this, SLOT (onTextKeyPressed(QString)));

    connect(m_keyboard.data(), SIGNAL (clearAllPressed()),
            this, SLOT (onClearAllPressed()));

    connect(m_keyboard.data(), SIGNAL(visibleChanged(bool, bool)),
            this, SLOT  (onVisibleChanged(bool, bool)));

    connect(m_keyboard.data(),      SIGNAL(moveCursorPosition(int, int)),
            this, SLOT  (onMoveCursorPosition(int, int)));

    connect(m_suggestion.data(), SIGNAL (virtualModeButtonPressed()),
            this, SLOT (onToggleModeButton()));

    connect(m_suggestion.data(), SIGNAL (preeditBoxPressed(QString)),
            this, SLOT (onPreeditCommit(QString)));

    connect(this,                   SIGNAL(showRequested(bool)),
            m_keyboard.data(),      SLOT(onShowRequested(bool)));

    QVariantMap attributes;
    systemLocale.reset(inputMethodHost()->registerPluginSetting("localeInfo", QT_TR_NOOP("system locale info"), Maliit::StringType, attributes));
    connect(systemLocale.data(), SIGNAL (valueChanged()),
            this, SLOT (onSystemLocaleChanged()));

    // country info
    currentCountry.reset(inputMethodHost()->registerPluginSetting("country", QT_TR_NOOP("country info"), Maliit::StringType, attributes));
    connect(currentCountry.data(), SIGNAL(valueChanged()),
            this, SLOT(onSystemLocaleChanged()));

    m_suggestion->setPreviousAvailable(false);
    m_suggestion->setNextAvailable(false);
}

ChineseInputMethod::~ChineseInputMethod()
{
}

void ChineseInputMethod::insertLanguage(QString language)
{
    enabledLanguages.append(language);
    enabledLayouts.append(LayoutLoader(language));
}

void ChineseInputMethod::removeLanguage(QString language)
{
    enabledLanguages.removeAll(language);
    enabledLayouts.removeAll(language);
}

void ChineseInputMethod::clear()
{
    qWarning() << __PRETTY_FUNCTION__;
    m_automata->reset();
    m_suggestion->setSuggestionList(QStringList());
    m_strokeComponent->setStrokeComponentList(QStringList());
    m_suggestion->setPreviousAvailable(false);
    m_suggestion->setNextAvailable(false);
    dirCursorMoveKey = -1;
    setPreedit("");
}

void ChineseInputMethod::reset()
{
    qWarning() << __PRETTY_FUNCTION__;
    clear();
    m_keyboard->removeTranslator();
    // empty default implementation
    MAbstractInputMethod::reset();
}

void ChineseInputMethod::onPreviousSuggestions()
{
    m_automata->previousSuggestions();
    m_suggestion->setSuggestionList(m_automata->getSuggestionList());
    m_suggestion->setPreviousAvailable(m_automata->isPreviousSuggestionsAvailable());
    m_suggestion->setNextAvailable(m_automata->isNextSuggestionsAvailable());
}

void ChineseInputMethod::onNextSuggestions()
{
    m_automata->nextSuggestions();
    m_suggestion->setSuggestionList(m_automata->getSuggestionList());
    m_suggestion->setPreviousAvailable(m_automata->isPreviousSuggestionsAvailable());
    m_suggestion->setNextAvailable(m_automata->isNextSuggestionsAvailable());
}

void ChineseInputMethod::onSuggestionSelected(int index)
{
    m_automata->suggestionSelected(index);
    if (m_automata->isComposing()) {
        setPreedit(m_automata->getPreedit());
    } else {
        inputMethodHost()->sendCommitString(m_automata->getCommit());
        setPreedit("");
    }
    m_suggestion->setSuggestionList(m_automata->getSuggestionList());
    if (m_automata->isShifted())
        m_strokeComponent->setStrokeComponentList(m_automata->getStrokeComponentList());
    m_suggestion->setNextAvailable(m_automata->isNextSuggestionsAvailable());
    m_suggestion->setPreviousAvailable(m_automata->isPreviousSuggestionsAvailable());
}

void ChineseInputMethod::onStrokeComponentSelected(int index)
{
    m_automata->strokeComponentSelected(index);
    if (m_automata->isComposing()) {
        setPreedit(m_automata->getPreedit());
    } else {
        inputMethodHost()->sendCommitString(m_automata->getCommit());
        setPreedit("");
    }
    m_suggestion->setSuggestionList(m_automata->getSuggestionList());
    m_strokeComponent->setStrokeComponentList(m_automata->getStrokeComponentList());
    m_suggestion->setNextAvailable(m_automata->isNextSuggestionsAvailable());
    m_suggestion->setPreviousAvailable(m_automata->isPreviousSuggestionsAvailable());
}

void ChineseInputMethod::onPreeditCommit(QString text)
{
    qDebug() << __PRETTY_FUNCTION__;
    if (0 == text.length())
        return;
    inputMethodHost()->sendCommitString(text);
    clear();
}

void ChineseInputMethod::onTextKeyPressed(QString text)
{
    qWarning() << "text: " << text;
    if (0 == text.length())
        return;

    QString preedit(m_automata->getPreedit());
    if (0 < preedit.length()) {
        inputMethodHost()->sendCommitString(preedit);
    }
    inputMethodHost()->sendCommitString(text);
    clear();
}

void ChineseInputMethod::onClearAllPressed()
{
    QString surroundingText;
    int cursor;
    inputMethodHost()->surroundingText(surroundingText, cursor);
    inputMethodHost()->sendCommitString("", -cursor, UINT_MAX);
    clear();
}

void ChineseInputMethod::onMoveCursorPosition(int direction,int eventType)
{
    qWarning() << __PRETTY_FUNCTION__;
    if (eventType == MOUSE_EVENT || eventType == TOUCH_EVENT) {
        doMoveCursorPosition(direction);
        return;
    }
    dirCursorMoveKey = direction;
}

void ChineseInputMethod::doMoveCursorPosition(int direction)
{
    qDebug() << __PRETTY_FUNCTION__;

    int keyCode = (direction == DIRECTION_LEFT) ? 113 : 114;
    Qt::Key key = (direction == DIRECTION_LEFT) ? Qt::Key_Left : Qt::Key_Right;

    MAbstractInputMethod::processKeyEvent(QEvent::KeyPress, key, Qt::NoModifier, "", false, 0, keyCode, 0, 0);
    MAbstractInputMethod::processKeyEvent(QEvent::KeyRelease, key, Qt::NoModifier, "", false, 0, keyCode, 0, 0);

}

#define INDEX_IS_VALID(i,list) (0 <= (i) && (i) < (list).length())
void ChineseInputMethod::show()
{
    qWarning() << __PRETTY_FUNCTION__;

#ifndef UBUNTU_DESKTOP_BUILD
#if QT_VERSION >= QT_VERSION_CHECK(6, 7, 0)
    QWindowSystemInterface::handleFocusWindowChanged(m_keyboard.data());
#else
    QWindowSystemInterface::handleWindowActivated(m_keyboard.data());
#endif
#endif

    if (!INDEX_IS_VALID(currentLanguageIndex, enabledLanguages))
        switchContext(Maliit::SwitchUndefined, false);

    // check the content-type
    bool valid;
    int contentType = inputMethodHost()->contentType(valid);
    if (valid)
        m_keyboard->setContentType(contentType);

    // check the enterKey-type
    int enterKeyType = inputMethodHost()->enterKeyType(valid);
    if (valid)
        m_keyboard->setEnterKeyType(enterKeyType);

    bool hiddenText = inputMethodHost()->hiddenText(valid);
    if (valid)
        m_keyboard->setHiddenText(hiddenText);

    m_keyboard->setInputSource(Keyboard::InputSourceVirtual);
    m_keyboard->show();
}

void ChineseInputMethod::hide()
{
    qDebug() << __PRETTY_FUNCTION__;

    m_keyboard->hide();
    m_keyboard->setInputSource(Keyboard::InputSourceNone);
}

QList<MAbstractInputMethod::MInputMethodSubView>
ChineseInputMethod::subViews(Maliit::HandlerState state) const
{
    Q_UNUSED(state);

    MAbstractInputMethod::MInputMethodSubView sub_view;
    sub_view.subViewId = "chinese";
    sub_view.subViewTitle = "chinese";
    QList<MAbstractInputMethod::MInputMethodSubView> sub_views;
    sub_views << sub_view;
    return sub_views;
}

QString ChineseInputMethod::activeSubView(Maliit::HandlerState state) const
{
    Q_UNUSED(state);
    qDebug() << __PRETTY_FUNCTION__;
    return QString("chinese");
}

void ChineseInputMethod::setState(const QSet<Maliit::HandlerState> &state)
{
    qDebug() << __PRETTY_FUNCTION__;
    MAbstractInputMethod::setState(state);
}

void ChineseInputMethod::handleClientChange()
{
    qDebug() << __PRETTY_FUNCTION__;
    MAbstractInputMethod::handleClientChange();
}

void ChineseInputMethod::handleVisualizationPriorityChange(bool inhibitShow)
{
    qDebug() << __PRETTY_FUNCTION__;
    MAbstractInputMethod::handleVisualizationPriorityChange(inhibitShow);
}

void ChineseInputMethod::handleAppOrientationAboutToChange(int angle)
{
    qDebug() << __PRETTY_FUNCTION__;
    // Rotate your input method UI here
    Q_UNUSED(angle);
}

void ChineseInputMethod::handleAppOrientationChanged(int angle)
{
    qDebug() << __PRETTY_FUNCTION__;
    // Can typically be forwarded to handleAppOrientationAboutToChange
    // as long as that method will not do anything when newAngle == previousAngle
    Q_UNUSED(angle);
}

void ChineseInputMethod::update()
{
    qDebug() << __PRETTY_FUNCTION__;
    // empty default implementation
    MAbstractInputMethod::update();
}


void ChineseInputMethod::handleFocusChange(bool focusIn)
{
    qDebug() << __PRETTY_FUNCTION__;
    clear();
    // this is for hardware keyboard
    inputMethodHost()->setRedirectKeys(focusIn);
}

void ChineseInputMethod::switchContext(Maliit::SwitchDirection direction,
                                          bool enableAnimation)
{
    Q_UNUSED(enableAnimation);
    qDebug() << __PRETTY_FUNCTION__;
    // If index was out of bounds, it means the plugin wasn't active.
    if (!INDEX_IS_VALID(currentLanguageIndex, enabledLanguages)) {
        switch (direction) {
            case Maliit::SwitchForward:
                currentLanguageIndex = 0;
                break;
            case Maliit::SwitchBackward:
                currentLanguageIndex = enabledLanguages.length() - 1;
                break;
            case Maliit::SwitchUndefined:
                currentLanguageIndex = 0;
        }
    } else {
        if (direction == Maliit::SwitchForward)
            currentLanguageIndex++;
        else if (direction == Maliit::SwitchBackward)
            currentLanguageIndex--;
    }

    if (!INDEX_IS_VALID(currentLanguageIndex, enabledLanguages)) {
        clear();
        currentLanguageIndex = -1;
        m_keyboard->removeTranslator();
        inputMethodHost()->switchPlugin(direction);
        return;
    }

    m_keyboard->setShift(false);
    m_automata->setLanguage(enabledLanguages[currentLanguageIndex]);
    m_keyboard->setLanguage(enabledLanguages[currentLanguageIndex],
                    QVariant((enabledLayouts.at(currentLanguageIndex)).getLayout()));
    m_keyboard->setTranslator();

    QString preedit(m_automata->getPreedit());
    if (0 < preedit.length())
        inputMethodHost()->sendCommitString("");
    clear();
}

void ChineseInputMethod::onShiftKeyPressed()
{
    m_automata->shifted(m_keyboard->isShifted());
    clear();
}

void ChineseInputMethod::onSymbolKeyPressed(QString state)
{
    Q_UNUSED(state);
    clear();
}

void ChineseInputMethod::setPreedit(const QString &preeditString)
{
    qDebug() << __PRETTY_FUNCTION__;
    m_suggestion->setPreedit(preeditString);
}

void ChineseInputMethod::setActiveSubView(const QString &subViewId, Maliit::HandlerState state)
{
    qDebug() << __PRETTY_FUNCTION__;

    // Ignored as input method only support one subview
    MAbstractInputMethod::setActiveSubView(subViewId, state);
}

bool ChineseInputMethod::imExtensionEvent(MImExtensionEvent *event)
{
    qDebug() << __PRETTY_FUNCTION__;

    if (!event || event->type() != MImExtensionEvent::Update)
        return false;

    MImUpdateEvent *updateEvent(static_cast<MImUpdateEvent *>(event));

    const QStringList propertiesChanged(updateEvent->propertiesChanged());

    // contentType
    if (propertiesChanged.contains(ContentTypeAttribute)) {
        const int type(updateEvent->value(ContentTypeAttribute).toInt());
        if (type != m_keyboard->getContentType())
            m_keyboard->setContentType(type);
    }

    // EnterKeyType
    if (propertiesChanged.contains(EnterKeyTypeAttribute)) {
        const int type(updateEvent->value(EnterKeyTypeAttribute).toInt());
        if (type != m_keyboard->getEnterKeyType())
            m_keyboard->setEnterKeyType(type);
    }

    // hiddenText
    if (propertiesChanged.contains(HiddenTextAttribute)) {
        const bool hiddenText(updateEvent->value(HiddenTextAttribute).toBool());
        if (hiddenText != m_keyboard->isHiddenText()) {
           m_keyboard->setHiddenText(hiddenText);
        }
    }

    return true;
}

void ChineseInputMethod::showLanguageNotification()
{
    qDebug() << __PRETTY_FUNCTION__;
    MAbstractInputMethod::showLanguageNotification();
}

struct RemoteKeysym {
    quint32 key;
    quint32 keysym;
};

static const struct RemoteKeysym RemoteNumericKeysymMap[] = {
    { KEY_NUMERIC_0, KEYSYM_0 },
    { KEY_NUMERIC_1, KEYSYM_1 },
    { KEY_NUMERIC_2, KEYSYM_2 },
    { KEY_NUMERIC_3, KEYSYM_3 },
    { KEY_NUMERIC_4, KEYSYM_4 },
    { KEY_NUMERIC_5, KEYSYM_5 },
    { KEY_NUMERIC_6, KEYSYM_6 },
    { KEY_NUMERIC_7, KEYSYM_7 },
    { KEY_NUMERIC_8, KEYSYM_8 },
    { KEY_NUMERIC_9, KEYSYM_9 }
};

static quint32 getRemoteNumericKeysym(quint32 key)
{
    for (quint32 i = 0; i < sizeof(RemoteNumericKeysymMap) / sizeof(RemoteKeysym); i++) {
        if (key == RemoteNumericKeysymMap[i].key)
            return RemoteNumericKeysymMap[i].keysym;
    }
    return KEYSYM_VOIDSYMBOL;
}

bool ChineseInputMethod::isNumKeyWithNumberKeyboard(Qt::Key keyCode)
{
    // check current mode and number
    qWarning() << __PRETTY_FUNCTION__;
    return (m_keyboard->isNumberMode() && keyCode >= Qt::Key_0 && keyCode <= Qt::Key_9);
}

bool ChineseInputMethod::processKeyEventCommon(Qt::Key keyCode, Qt::KeyboardModifiers modifiers)
{
    qWarning() << __PRETTY_FUNCTION__;

    QString preedit = m_automata->getPreedit();

    if ((keyCode == Qt::Key_Return ||  keyCode == Qt::Key_Enter) && preedit.length() > 0) {
        onPreeditCommit(preedit);
        return true;
    }

    if (keyCode == Qt::Key_Space) {
        if (m_automata->getCandidatesNum() > 0)
            onSuggestionSelected(0);
        else
            onTextKeyPressed(QString((QChar)CHINESE_SPACE_KEYCODE));
        return true;
    }

    if (!m_automata->processKeyEvent(keyCode, modifiers)) {
        return handleCommitString(keyCode);
    }

    m_suggestion->setSuggestionList(m_automata->getSuggestionList());
    m_suggestion->setNextAvailable(m_automata->isNextSuggestionsAvailable());
    m_suggestion->setPreviousAvailable(m_automata->isPreviousSuggestionsAvailable());

    if (m_automata->isShifted())
        m_strokeComponent->setStrokeComponentList(m_automata->getStrokeComponentList());

    if (keyCode == Qt::Key_Backspace && 0 == preedit.length())
        return false;

    if (keyCode == Qt::Key_Tab)
        return false;

    setPreedit(m_automata->getPreedit());
    return true;
}

bool ChineseInputMethod::checkBypassKey(quint32 nativeScanCode)
{
    switch (nativeScanCode) {
    case SCANCODE_PLAY:
    case SCANCODE_PAUSE:
    case SCANCODE_STOP:
    case SCANCODE_REW:
    case SCANCODE_FF:
    case SCANCODE_REC:
    case SCANCODE_RED:
    case SCANCODE_GRN:
    case SCANCODE_YEL:
    case SCANCODE_BLU:
        return true;
    }
    return false;
}

void ChineseInputMethod::processKeyEvent(QEvent::Type keyType, Qt::Key keyCode,
                            Qt::KeyboardModifiers modifiers, const QString &text,
                            bool autoRepeat, int count, quint32 nativeScanCode,
                            quint32 nativeModifiers, unsigned long time)
{

    qWarning() << "keyCode: " << keyCode << ", naviveScanCode: " << nativeScanCode <<", keyType : " <<keyType;

    if(dirCursorMoveKey >= 0 && (keyCode == Qt::Key_Return || keyCode == Qt::Key_Enter)) {
        doMoveCursorPosition(dirCursorMoveKey);
    }

    if (keyType == QEvent::KeyRelease) {
        dirCursorMoveKey = -1;
        if (nativeScanCode == SCANCODE_LEFT_SHIFT || nativeScanCode == SCANCODE_RIGHT_SHIFT) {
            // Sending Long shift key release event back to Maliit
            MAbstractInputMethod::processKeyEvent(keyType, keyCode, modifiers,
                text, autoRepeat, count, nativeScanCode, nativeModifiers, time);
        } else // Keys to change language in hardware keyboard
        if ((keyCode == Qt::Key_Hangul && modifiers == Qt::NoModifier)
                || (nativeScanCode == SCANCODE_RALT && nativeModifiers == 0)
                || (modifiers == Qt::ControlModifier && keyCode == Qt::Key_Space)) {
             // Switch to virtual keyboard before switching the input method,
             // so that user will know the current input method.
             m_keyboard->setInputSource(Keyboard::InputSourceVirtual);
             switchContext(Maliit::SwitchForward, false);
        } else if (m_sendEnterKey && (keyCode == Qt::Key_Return || keyCode == Qt::Key_Enter)) {
            m_keyboard->onKeyReleased(keyCode, modifiers, true);
            m_sendEnterKey = false;
            inputMethodHost()->sendKeyEvent(QKeyEvent(QEvent::KeyPress,   Qt::Key_Return, Qt::NoModifier, "", false, 0));
            inputMethodHost()->sendKeyEvent(QKeyEvent(QEvent::KeyRelease, Qt::Key_Return, Qt::NoModifier, "", false, 0));
        } else if (!m_sendEnterKey
                  && (keyCode == Qt::Key_Return || keyCode == Qt::Key_Enter
                      || nativeScanCode == MAGIC_SCANCODE_OK || nativeScanCode == REMOTE_SCANCODE_OK)) {
            if (!m_keyboard->isVisible())
                MAbstractInputMethod::processKeyEvent(keyType, keyCode, modifiers, text, autoRepeat, count, nativeScanCode, nativeModifiers, time);
            m_keyboard->onKeyReleased(keyCode, modifiers, true);
        } else if (pressedScancode != SCANCODE_UNKNOWN &&
                        (pressedScancode == nativeScanCode || pressedScancode == SCANCODE_BACK)) {
            MAbstractInputMethod::processKeyEvent(keyType, keyCode, modifiers,
            text, autoRepeat, count, nativeScanCode, nativeModifiers, time);
        }
        qDebug() << "Pressed Scancode : " << pressedScancode << " nativeScanCode : " << nativeScanCode;
        pressedScancode = SCANCODE_UNKNOWN;
        return;
    }

    if (checkBypassKey(nativeScanCode)) {
        MAbstractInputMethod::processKeyEvent(keyType, keyCode, modifiers,
            text, autoRepeat, count, nativeScanCode, nativeModifiers, time);
        return;
    }

    if (keyCode == Qt::Key_Control) return;

    if (processHidKeyEvent(keyType, keyCode, modifiers, text, autoRepeat, count, nativeScanCode, nativeModifiers, time)) {
        return;
    }

    // check if it is handled by VKB: 5-way remote
    if(processRemoteKeyEvent(keyCode, nativeScanCode, modifiers)) {
        return;
    }

    // some key codes should be changed the other key code.
    if (keyCode == Qt::Key_Clear) {
        keyCode = Qt::Key_Backspace;
        nativeScanCode = KEY_BACKSPACE + 8;
    }

    if (enabledLanguages[currentLanguageIndex] == LanguageConstants::SIMPLIFIED_CHINESE && isNumberOrEnterKey(keyCode) == false) {
        if (m_keyboard->isShifted() || (keyCode == Qt::Key_F12)){
            if (!m_keyboard->isVisible()) {
                MAbstractInputMethod::processKeyEvent(keyType, keyCode, modifiers, text, autoRepeat, count, nativeScanCode, nativeModifiers, time);
            }
            return;
        }
    }

    if (nativeScanCode == SCANCODE_BACK || !processKeyEventCommon(keyCode, modifiers)) {
//#IF_COMMERCIAL
        if (keyCode == Qt::Key_Return || keyCode == Qt::Key_Enter){
            m_sendEnterKey = true;
            return;
        }
//#ELSE
/*
        if (keyCode == Qt::Key_Return || keyCode == Qt::Key_Enter)
            m_sendEnterKey = true;
*/
//#END
        pressedScancode = nativeScanCode;
        MAbstractInputMethod::processKeyEvent(keyType, keyCode, modifiers,
            text, autoRepeat, count, nativeScanCode, nativeModifiers, time);
    }
}

bool ChineseInputMethod::processHidKeyEvent(QEvent::Type keyType, Qt::Key keyCode,
                       Qt::KeyboardModifiers modifiers, const QString &text,
                       bool autoRepeat, int count, quint32 nativeScanCode,
                       quint32 nativeModifiers, unsigned long time)
{
    qDebug() << __PRETTY_FUNCTION__;

    // Keys to change language in hardware keyboard
    if ((keyCode == Qt::Key_Hangul)
        || (nativeScanCode == SCANCODE_RALT && nativeModifiers == 0)
        || (keyCode == Qt::Key_Space && modifiers.testFlag(Qt::ControlModifier))) {
        return true;
    }
    // escape ctrl + space since it's being used as hot key for keyboard switching.
    if (keyCode == Qt::Key_Space && modifiers == Qt::ControlModifier)
        return true;

    if (keyCode == Qt::Key_Alt || keyCode == Qt::Key_Shift || keyCode == Qt::Key_Control
        || keyCode == Qt::Key_NumLock || keyCode == Qt::Key_CapsLock)
        return false;

    if (nativeScanCode > 0x7F)
        return false;

    if (m_keyboard->inputSource() == Keyboard::InputSourceVirtual) {
        if (keyCode == Qt::Key_Return
            || keyCode == Qt::Key_Enter
            || keyCode == Qt::Key_Escape
            || keyCode == Qt::Key_Tab
            || keyCode == Qt::Key_Up || keyCode == Qt::Key_Down || keyCode == Qt::Key_Left || keyCode == Qt::Key_Right)
            return false;
    } else if (m_keyboard->inputSource() == Keyboard::InputSourceHardware) {
        switch (keyCode) {
        case Qt::Key_F1:    // F1 ~ F12 is used as the hotkey for hid predictive widget
        case Qt::Key_F2:
        case Qt::Key_F3:
        case Qt::Key_F4:
        case Qt::Key_F5:
        case Qt::Key_F6:
        case Qt::Key_F7:
        case Qt::Key_F8:
        case Qt::Key_F9:
        case Qt::Key_F10:
        case Qt::Key_F11:
        case Qt::Key_F12:
            if (m_keyboard->hidKeyPressEvent(keyCode, modifiers))
                return true;
            break;
        default:
            ;
        }
    }

    bool bHoldSource = (
             (keyCode == Qt::Key_NumLock)
             || (keyCode == Qt::Key_CapsLock)
             || (keyCode == Qt::Key_ScrollLock));
    if (!bHoldSource)
        m_keyboard->setInputSource(Keyboard::InputSourceHardware); // set input source as HID

    // send to automata
    if (processKeyEventCommon(keyCode, modifiers))
        return true;

    pressedScancode = nativeScanCode;
    MAbstractInputMethod::processKeyEvent(keyType, keyCode, modifiers,
        text, autoRepeat, count, nativeScanCode, nativeModifiers, time);

    return true;
}

void ChineseInputMethod::releaseKeyLock()
{
    qDebug() << __PRETTY_FUNCTION__;
    Q_D(ChineseInputMethod);
    d->keyLocked = false;
}

bool ChineseInputMethod::processRemoteKeyEvent(Qt::Key keyCode, quint32 nativeScanCode, Qt::KeyboardModifiers modifiers)
{
    qWarning() << __PRETTY_FUNCTION__;

    if (nativeScanCode == SCANCODE_POINTERON) {
        return false;
    }
    else if (nativeScanCode == SCANCODE_POINTEROFF) {
        return false;
    }

    // Replace key code of Remote: keyCode is Qt::Key_Unknown for some remote buttons
    if (nativeScanCode == MAGIC_SCANCODE_OK || nativeScanCode == REMOTE_SCANCODE_OK) // "OK" button
        keyCode = Qt::Key_Execute;              // FIXME: This is temporary
    else if (nativeScanCode == SCANCODE_BACK)   // "Back" button
        keyCode = Qt::Key_Cancel;               // FIXME: This is temporary

    // IR Numeric key: convert to keysym
    m_keySym = getRemoteNumericKeysym(nativeScanCode - EVDEV_OFFSET);
    if (m_keySym != KEYSYM_VOIDSYMBOL) {
        m_bNumberKey = true;
        releaseKeyLock();
        onTextKeyPressed(QString::number(m_keySym-KEYSYM_0));

        // Move the focus to "Enter" button of the VKB: Requirement from HQ QE
        if (m_keyboard->inputSource() == Keyboard::InputSourceVirtual) {
            m_keyboard->forceFocusTo("Enter");
        }
        return true;
    }

    bool accepted = false;

    // Extract Remote-Key
    switch (keyCode) {
    case Qt::Key_Up:
    case Qt::Key_Down:
    case Qt::Key_Left:
    case Qt::Key_Right:
    case Qt::Key_Execute:
	if (!m_keyboard->isVisible())
            break;
        if (m_keyboard->cursorVisible()) {
            accepted = m_keyboard->isVisible();
        } else {
            accepted = m_keyboard->hidKeyPressEvent(keyCode, modifiers);
            // Sets focus back to last focused item or default key in VKB when navigation keys are used after touch event.
            // This fixes the issue reported in WRO-10152.
            m_keyboard->hidNavKeysPressed();
        }
        break;	
    case Qt::Key_Cancel:
        if (m_keyboard->isVisible()){
            m_keyboard->onHideRequested(false);
            accepted = true;
        } else {
            pressedScancode = nativeScanCode;
            accepted = false;
        }
        break;
        default:
            break;
    }
    if (!accepted && nativeScanCode == REMOTE_SCANCODE_OK) {
        Q_EMIT showRequested(false);
        accepted = true;
    }

    if (isNumKeyWithNumberKeyboard(keyCode)) {
        handleCommitString(keyCode);
        m_keyboard->forceFocusTo("Enter");
        accepted = true;
    }
    return accepted;
}

bool ChineseInputMethod::handleCommitString(Qt::Key keyCode)
{
    if (!m_automata->isDirectInput(keyCode))
        return false;

    if ((m_keyboard->inputSource() == Keyboard::InputSourceHardware)) {
        if (keyCode == Qt::Key_AsciiCircum) {
            QString tripleDot = "...";
            onTextKeyPressed(tripleDot);
            return true;
        } else {
            quint32 chineseSymbol = m_automata->chineseSymbolKeyMapping(keyCode);
            if (chineseSymbol != 0)
                onTextKeyPressed(QString((QChar)chineseSymbol));
            else
                onTextKeyPressed(QString((QChar)keyCode));
            return true;
        }
    } else {
        onTextKeyPressed(QString((QChar)keyCode));
        return true;
    }
}

void ChineseInputMethod::onToggleModeButton()
{
    if (enabledLanguages[currentLanguageIndex] != LanguageConstants::SIMPLIFIED_CHINESE)
        m_keyboard->setShift(!m_keyboard->isShifted());
}

void ChineseInputMethod::setKeyOverrides(const QMap<QString, QSharedPointer<MKeyOverride> > &overrides)
{
    qDebug() << __PRETTY_FUNCTION__;
    MAbstractInputMethod::setKeyOverrides(overrides);
}

void ChineseInputMethod::handleMouseClickOnPreedit(const QPoint &pos, const QRect &preeditRect)
{
    Q_UNUSED(pos);
    Q_UNUSED(preeditRect);
    qDebug() << __PRETTY_FUNCTION__;
}

void ChineseInputMethod::onVirtualKeyPressed(quint32 nativeScanCode, Qt::KeyboardModifiers modifiers, int eventType)
{
    qDebug() << __PRETTY_FUNCTION__;

    Qt::Key keyCode = Qt::Key_unknown;
    switch (nativeScanCode) {
    case KEY_SPACE_VKB:
        keyCode = Qt::Key_Space;
        break;
    case KEY_BACKSPACE_VKB:
        keyCode = Qt::Key_Backspace;
        break;
    case KEY_RETURN:
        keyCode = Qt::Key_Return;
        break;
    case KEY_TAB_VKB:
        keyCode = Qt::Key_Tab;
        break;
    default:
        keyCode = (Qt::Key)nativeScanCode;
        break;
    }

    m_keyboard->setInputSource(Keyboard::InputSourceVirtual);
    if (!processKeyEventCommon(keyCode, modifiers)) {
        if (eventType == MOUSE_EVENT || eventType == TOUCH_EVENT || keyCode != Qt::Key_Return) {
            inputMethodHost()->sendKeyEvent(QKeyEvent(QEvent::KeyPress, keyCode, modifiers, "", false, 0));
            inputMethodHost()->sendKeyEvent(QKeyEvent(QEvent::KeyRelease, keyCode, modifiers, "", false, 0));
        } else {
            m_sendEnterKey = true;
        }
    }

    m_suggestion->setNextAvailable(m_automata->isNextSuggestionsAvailable());
    m_suggestion->setPreviousAvailable(m_automata->isPreviousSuggestionsAvailable());
}

void ChineseInputMethod::onSwitchContext(Maliit::SwitchDirection direction)
{
    qDebug() << __PRETTY_FUNCTION__;
    switchContext(direction, false);
}

void ChineseInputMethod::onVisibleChanged(bool visible, bool reset)
{
    Q_UNUSED(visible);

    if (reset)
        this->clear();
}

void ChineseInputMethod::onSystemLocaleChanged()
{
    QString LOCALEINFO_KEYBOARDS_KEY = "keyboards";
    QJsonObject localeJson = QJsonObject::fromVariantMap(systemLocale->value().toMap());
    QJsonObject::const_iterator it = localeJson.find(LOCALEINFO_KEYBOARDS_KEY);
    if (it == localeJson.end()) {
        qWarning() << "cannot find key in locale setting: " << "localeInfo/" << LOCALEINFO_KEYBOARDS_KEY;
        return;
    }
    QJsonArray keyboards = it.value().toArray();

    QList<QString> languages;
    QList<LayoutLoader> layouts;
    QScopedPointer<QLocale> locale;
    for (int i = 0; i < keyboards.count(); ++i) {
        if (keyboards[i].isString()) {
            locale.reset(new QLocale(keyboards[i].toString()));
            if (locale->script() == QLocale::SimplifiedHanScript) {
                languages.append(LanguageConstants::SIMPLIFIED_CHINESE);
                layouts.append(LayoutLoader(LanguageConstants::SIMPLIFIED_CHINESE));
            } else if (locale->script() == QLocale::TraditionalHanScript) {
                if (currentCountry->value().toString() == LanguageConstants::TAIWAN_ISO3166_CODE) {
                   languages.append(LanguageConstants::TRADITIONAL_CHINESE_TW);
                   layouts.append(LayoutLoader(LanguageConstants::TRADITIONAL_CHINESE_TW));
                } else {
                   languages.append(LanguageConstants::TRADITIONAL_CHINESE);
                   layouts.append(LayoutLoader(LanguageConstants::TRADITIONAL_CHINESE));
                }
            }
        }
    }

    enabledLanguages.clear();
    enabledLayouts.clear();

    if (languages.isEmpty()) {
        currentLanguageIndex = -1;
        m_keyboard->removeTranslator();
        inputMethodHost()->switchPlugin(Maliit::SwitchForward);
    } else {
        enabledLanguages = std::move(languages);
        enabledLayouts = layouts;
        if (currentLanguageIndex != -1)
            switchContext(Maliit::SwitchUndefined, false);
    }

    // get the Menu language
    static const QString LOCALEINFO_LOCALE_KEY = "locales";
    static const QString LOCALEINFO_LOCALE_UI_KEY = "UI";

    it = localeJson.find(LOCALEINFO_LOCALE_KEY);
    if (it == localeJson.end()) {
        qDebug() << "cannot find key in the locale setting: " << LOCALEINFO_LOCALE_KEY;
        return;
    }
    localeJson = it.value().toObject();
    it = localeJson.find(LOCALEINFO_LOCALE_UI_KEY);
    if (it == localeJson.end()) {
        qDebug() << "cannot find key in the locale setting: " << LOCALEINFO_LOCALE_KEY << "/" << LOCALEINFO_LOCALE_UI_KEY;
        return;
    }
    m_keyboard->setNumKeyEnterLabel(it.value().toString());
}

//#IF_COMMERCIAL
bool ChineseInputMethod::isNumberOrEnterKey(Qt::Key keyCode) {
    qDebug() << __PRETTY_FUNCTION__;

    if(keyCode >= Qt::Key_0 && keyCode <= Qt::Key_9) return true;

    if (keyCode == Qt::Key_Return || keyCode == Qt::Key_Enter) return true;

    return false;
}
//#ELSE
//#END

bool ChineseInputMethod::hasEnabledLanguages()
{
    return !enabledLanguages.isEmpty();
}
