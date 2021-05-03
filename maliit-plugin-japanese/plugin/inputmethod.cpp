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

#include "inputmethod.h"
#include <maliit/plugins/abstractinputmethodhost.h>
#include <maliit/plugins/updateevent.h>
#ifndef UBUNTU_DESKTOP_BUILD
#include <qpa/qwindowsysteminterface.h>
#include <linux/input.h>

#endif
#include <QDebug>
#include <QTimer>

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
    const char * const PredictionAttribute = "predictionEnabled";
    const char * const PreeditClickPosAttribute = "preeditClickPos";
    const char * const SurroundingTextAttribute = "surroundingText";
    const char * const ToolbarAttribute = "toolbar";
    const char * const ToolbarIdAttribute = "toolbarId";
    const char * const WinId = "winId";
}

template<typename T, typename U> bool isValidIndex(T i, U list){
    return 0 <= i && i < list.length();
}

static const QString JAPANESE_INPUT_METHOD_DEFAULT_LANGUAGE = QLocale::languageToString(QLocale::Japanese);
static const unsigned int KEY_BACKSPACE_VKB = 20;
static const unsigned int KEY_RETURN    = 40;
static const unsigned int KEY_CONVERT   = 100;
static const unsigned int KEY_ARROW     = 21;

static const quint32 EVDEV_OFFSET   = 8;
static const quint32 SCANCODE_OK         = 0;    // from Device: "OK" button of Magic-remote
static const quint32 SCANCODE_BACK       = 420;  // from Device: "Back" button of Magic-remote
static const quint32 SCANCODE_POINTERON  = 1206; // from Device: Device sends the keycode when the pointer appears
static const quint32 SCANCODE_POINTEROFF = 1207; // from Device: Device sends the keycode when the pointer disappears
static const quint32 SCANCODE_BACKSPACE  = 22;   // from VKB
static const quint32 SCANCODE_RETURN     = 36;   // from VKB
static const quint32 SCANCODE_TAB        = 23;   // from VKB
static const quint32 SCANCODE_RALT       = 108;  // from HID: Right Alt changes the language of the VKB
static const quint32 SCANCODE_KEYPAD_SLASH    = 106;
static const quint32 SCANCODE_KEYPAD_ASTERISK = 63;
static const quint32 SCANCODE_KEYPAD_MINUS    = 82;
static const quint32 SCANCODE_KEYPAD_PLUS     = 86;
static const quint32 SCANCODE_KEYPAD_ENTER    = 104;
static const quint32 SCANCODE_NUMKEY_3        = 12;
static const quint32 SCANCODE_NUMKEY_8        = 17;
static const quint32 SCANCODE_COLON           = 48;
static const quint32 SCANCODE_ZENKAKU_HANKAKU = 49; // from HID: Changes the language of the VKB
static const quint32 SCANCODE_UNKNOWN         = 0xffffffff;
static const quint32 SCANCODE_INIT            = 0xfffffffe;
static const quint32 SCANCODE_PLAY            = 0xD7;  // from Remote
static const quint32 SCANCODE_PAUSE           = 0x7F;  // from Remote
static const quint32 SCANCODE_STOP            = 0x88;  // from Remote
static const quint32 SCANCODE_REW             = 0xB0;  // from Remote
static const quint32 SCANCODE_FF              = 0xD8;  // from Remote
static const quint32 SCANCODE_BACKSKIP        = 0x335; // from Remote
static const quint32 SCANCODE_FORWARDSKIP     = 0x336; // from Remote
static const quint32 SCANCODE_REC             = 0xAF;  // from Remote
static const quint32 SCANCODE_BULE            = 0x199; // from Remote "Color key"
static const quint32 SCANCODE_RED             = 0x196; // from Remote "Color key"
static const quint32 SCANCODE_GREEN           = 0x197; // from Remote "Color key"
static const quint32 SCANCODE_YELLOW          = 0x198; // from Remote "Color key"
static const quint32 SCANCODE_TR              = 0x36F; // from Remote "Brodcast Change"
static const quint32 SCANCODE_BS              = 0x348; // from Remote "Brodcast Change"
static const quint32 SCANCODE_CS1             = 0x355; // from Remote "Brodcast Change"
static const quint32 SCANCODE_CS2             = 0x362; // from Remote "Brodcast Change"
static const quint32 SCANCODE_CHUP            = 0x19A; // from Remote "CH UP key"
static const quint32 SCANCODE_CHDOWN          = 0x19B; // from Remote "CH DOWN key"
static const quint32 SCANCODE_EPG             = 0x172; // from Remote "EPG key"
static const quint32 SCANCODE_3D              = 0x33D; // from Remote "3D key"
static const quint32 SCANCODE_PROGRAM_INFO    = 0x16E; // from Remote "Program info key"
static const quint32 SCANCODE_LIVEMENU        = 0x311; // from Remote "Live menu key"
static const quint32 SCANCODE_AUDIOCHANGE     = 0x326; // from Remote "Audio Change key"
static const quint32 SCANCODE_CAPTION         = 0x327; // from Remote "Caption key"
static const quint32 SCANCODE_TIMER           = 0x323; // from Remote "Timer key"
static const quint32 SCANCODE_3DIGEIT         = 0x37C; // from Remote "3DIGEIT key"
static const quint32 SCANCODE_CH_REGIST       = 0x3E7; // from Remote "CH regist key"
static const quint32 SCANCODE_D_DATA          = 0x37D; // from Remote "D data key"
static const quint32 SCANCODE_SIMPLINK        = 0x312; // from Remote "Simplink key"
static const quint32 SCANCODE_ECHO            = 0x389; // from Remote "Echo key"
static const quint32 SCANCODE_SCREEN_REMOTE   = 0x3EA; // from Remote "Screen remote key"
static const quint32 SCANCODE_VOICE_SEARCH    = 225; // from Remote "Voice Search key"
static const quint32 DIRECTION_LEFT    = 0;
static const quint32 DIRECTION_RIGHT   = 1;

static const quint32 MOUSE_EVENT    = 1;
static const quint32 KEYBOARD_EVENT = 2;
static const quint32 TOUCH_EVENT    = 3;

enum IlligalNativeScanCode {
    REMOTE_UNDEFINED = 1198,
    REMOTE_HOME = 1199
};

enum {
    KEYSYM_ASTERISK = 0x002a,
    KEYSYM_PLUS,
    KEYSYM_COMMA,
    KEYSYM_MINUS,
    KEYSYM_PERIOD,
    KEYSYM_SLASH,
    KEYSYM_0 = 0xEFBC98,
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

class JapaneseInputMethodPrivate
{
    Q_DECLARE_PUBLIC(JapaneseInputMethod)

public:
    JapaneseInputMethod *const q_ptr;
    bool keyLocked;
    quint32 pressedScanCode;
    bool sendEnterKey;
    int dirCursorMoveKey;

    JapaneseInputMethodPrivate(JapaneseInputMethod *im)
        : q_ptr(im)
        , keyLocked(false)
        , pressedScanCode(SCANCODE_UNKNOWN)
        , sendEnterKey(false)
        , dirCursorMoveKey(-1)
    {}

    quint32 convertToKeysym(quint32 scanCode)
    {
        if (scanCode == SCANCODE_KEYPAD_SLASH)
            return KEYSYM_SLASH;
        else if (scanCode == SCANCODE_KEYPAD_ASTERISK)
            return KEYSYM_ASTERISK;
        else if (scanCode == SCANCODE_KEYPAD_MINUS)
            return KEYSYM_MINUS;
        else if (scanCode == SCANCODE_KEYPAD_PLUS)
            return KEYSYM_PLUS;
        else
            return KEYSYM_VOIDSYMBOL;
    }

  void blockKeycodeDuring(quint32 ms)
    {
        keyLocked = true;
        QTimer::singleShot(ms, q_ptr, SLOT(releaseKeyLock()));
    }

  bool checkBypassKey(quint32 nativeScanCode)
  {
      bool bypass = false;

      switch (nativeScanCode) {
      case SCANCODE_PLAY:
      case SCANCODE_PAUSE:
      case SCANCODE_STOP:
      case SCANCODE_REW:
      case SCANCODE_FF:
      case SCANCODE_BACKSKIP:
      case SCANCODE_FORWARDSKIP:
      case SCANCODE_REC:
      case SCANCODE_BULE:
      case SCANCODE_RED:
      case SCANCODE_GREEN:
      case SCANCODE_YELLOW:
      case SCANCODE_TR:
      case SCANCODE_BS:
      case SCANCODE_CS1:
      case SCANCODE_CS2:
      case SCANCODE_CHUP:
      case SCANCODE_CHDOWN:
      case SCANCODE_EPG:
      case SCANCODE_3D:
      case SCANCODE_PROGRAM_INFO:
      case SCANCODE_LIVEMENU:
      case SCANCODE_AUDIOCHANGE:
      case SCANCODE_CAPTION:
      case SCANCODE_TIMER:
      case SCANCODE_3DIGEIT:
      case SCANCODE_CH_REGIST:
      case SCANCODE_D_DATA:
      case SCANCODE_SIMPLINK:
      case SCANCODE_ECHO:
      case SCANCODE_SCREEN_REMOTE:
      case SCANCODE_VOICE_SEARCH:
          bypass = true;
          break;
      }

      return bypass;
  }

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

JapaneseInputMethod::JapaneseInputMethod(MAbstractInputMethodHost* host)
    : MAbstractInputMethod(host)
    , d_ptr(new JapaneseInputMethodPrivate(this))
    , m_hiddenText(false)
    , m_isSymbol(false)
    , m_candIndex(0)
    , m_isConvert(false)
    , m_isJapaneseEnabled(false)
    , m_isActive(false)
    , m_bNumberKey(false)
    , m_bHoldSource(false)
    , m_keySym(0)
    , m_prediction(new Prediction(host))
    , m_keyboard(new Keyboard(this, m_prediction.data()))
{
    qDebug() << __PRETTY_FUNCTION__;

    connect(m_prediction.data(), SIGNAL (predictionSelected(int)),
            this, SLOT (onPredictionSelected(int)));

    connect(m_keyboard.data(), SIGNAL (keyPressed(quint32, Qt::KeyboardModifiers, int)),
            this, SLOT (onVirtualKeyPressed(quint32, Qt::KeyboardModifiers, int)));

    connect(m_keyboard.data(), SIGNAL (switchContext(Maliit::SwitchDirection)),
            this, SLOT (onSwitchContext(Maliit::SwitchDirection)));

    connect(m_keyboard.data(), SIGNAL(activateSTT()),
            this, SLOT (onActivateSTT()));

    connect(m_keyboard.data(), SIGNAL (clearAllPressed()),
            this, SLOT (onClearAllPressed()));

    connect(m_keyboard.data(), SIGNAL (visibleChanged(bool)),
            this, SLOT (onVisibleChanged(bool)));

    connect(m_keyboard.data(), SIGNAL (setHidModeFromVkb(int)),
            this, SLOT (onSetHidModeFromVkb(int)));

    connect(m_keyboard.data(), SIGNAL(textKeyPressed(QString)),
            this,SLOT  (onTextKeyPressed(QString)));

    connect(m_keyboard.data(),      SIGNAL(moveCursorPosition(int, int)),
            this,                   SLOT  (onMoveCursorPosition(int, int)));

    connect(this, SIGNAL (hiddenTextChanged(bool)),
            m_keyboard.data(), SIGNAL (hiddenTextChanged(bool)));

    connect(m_keyboard.data(), SIGNAL (switchSymbolMode(bool)),
            this, SLOT (onSwitchSymbolMode(bool)));

    connect(m_keyboard.data(), SIGNAL (vkbModeChanged(int)),
            this, SLOT (onVkbModeChanged(int)));

    connect(this,                   SIGNAL(showRequested(bool)),
            m_keyboard.data(),      SLOT(onShowRequested(bool)));

    QVariantMap attributes;
    m_systemLocale.reset(inputMethodHost()->registerPluginSetting("localeInfo", QT_TR_NOOP("system locale info"), Maliit::StringType, attributes));

    connect(m_systemLocale.data(), SIGNAL (valueChanged()),
            this, SLOT (onSystemLocaleChanged()));

// Flag to enable STT
    enableStt.reset(inputMethodHost()->registerPluginSetting("accessoryenabled", QT_TR_NOOP("Flag to enable STT"), Maliit::BoolType, attributes));

    m_automata.reset(new OpenWnnAutomata);
    m_automata->setInputMode(0);
}

JapaneseInputMethod::~JapaneseInputMethod()
{
    qDebug() << __PRETTY_FUNCTION__;
}

void JapaneseInputMethod::show()
{
    qDebug() << __PRETTY_FUNCTION__;
    Q_D(JapaneseInputMethod);

    m_keyboard->setInputSource(Keyboard::InputSourceVirtual);

    // check the content-type
    bool valid;
    int contentType = inputMethodHost()->contentType(valid);
    if (valid)
        m_keyboard->setContentType(contentType);

    int enterKeyType = inputMethodHost()->enterKeyType(valid);
    if (valid)
        m_keyboard->setEnterKeyType(enterKeyType);

    bool hiddenText = inputMethodHost()->hiddenText(valid);
    if (valid) {
        m_hiddenText = hiddenText;
        m_keyboard->setHiddenText(hiddenText);
    }

    if (!m_isJapaneseEnabled)
        switchContext(Maliit::SwitchUndefined, false);
    else {
#ifndef UBUNTU_DESKTOP_BUILD
        QWindowSystemInterface::handleWindowActivated(m_keyboard.data());
#endif

        m_isActive = true;
        m_keyboard->languageChanged();
        m_keyboard->setInputSource(Keyboard::InputSourceVirtual);
        m_keyboard->setUnfixedStatus(false);
        m_keyboard->setTranslator(QString("ja"));
        Q_EMIT showRequested(false);
    }
    d->pressedScanCode = SCANCODE_INIT;
    d->sendEnterKey = false;
}

void JapaneseInputMethod::hide()
{
    qDebug() << __PRETTY_FUNCTION__;
    m_prediction->clearPredictionList();
    m_keyboard->setInputSource(Keyboard::InputSourceNone);
    m_keyboard->hide();
}

QList<MAbstractInputMethod::MInputMethodSubView>
JapaneseInputMethod::subViews(Maliit::HandlerState state) const
{
    qDebug() << __PRETTY_FUNCTION__;
    Q_UNUSED(state);

    MAbstractInputMethod::MInputMethodSubView subView;
    subView.subViewId = "japanese";
    subView.subViewTitle = "japanese";
    QList<MAbstractInputMethod::MInputMethodSubView> subViews;
    subViews << subView;
    return subViews;
}

QString JapaneseInputMethod::activeSubView(Maliit::HandlerState state) const
{
    Q_UNUSED(state);
    qWarning() << __PRETTY_FUNCTION__;
    return QString("japanese");
}

void JapaneseInputMethod::setState(const QSet<Maliit::HandlerState>& state)
{
    qWarning() << __PRETTY_FUNCTION__;
    MAbstractInputMethod::setState(state);
}

void JapaneseInputMethod::handleClientChange()
{
    qWarning() << __PRETTY_FUNCTION__;
    MAbstractInputMethod::handleClientChange();
}

void JapaneseInputMethod::handleVisualizationPriorityChange(bool inhibitShow)
{
    qWarning() << __PRETTY_FUNCTION__;
    MAbstractInputMethod::handleVisualizationPriorityChange(inhibitShow);
}

void JapaneseInputMethod::handleAppOrientationAboutToChange(int angle)
{
    qDebug() << __PRETTY_FUNCTION__;
    // Rotate your input method UI here
    Q_UNUSED(angle);
}

void JapaneseInputMethod::handleAppOrientationChanged(int angle)
{
    qWarning() << __PRETTY_FUNCTION__;
    // Can typically be forwarded to handleAppOrientationAboutToChange
    // as long as that method will not do anything when newAngle == previousAngle
    Q_UNUSED(angle);
}

void JapaneseInputMethod::update()
{
    qWarning() << __PRETTY_FUNCTION__;
    // empty default implementation
    MAbstractInputMethod::update();
}

void JapaneseInputMethod::clear()
{
    qDebug() << __PRETTY_FUNCTION__;
    Q_D(JapaneseInputMethod);

    bool unfixed = false;
    m_automata->reset();
    m_prediction->clearPredictionList();
    d->dirCursorMoveKey = -1;
    m_keyboard->setUnfixedStatus(unfixed);
}

void JapaneseInputMethod::reset()
{
    qWarning() << __PRETTY_FUNCTION__;
    clear();
    m_keyboard->removeTranslator();
    // empty default implementation
    MAbstractInputMethod::reset();
}

void JapaneseInputMethod::handleFocusChange(bool focusIn)
{
    qWarning() << __PRETTY_FUNCTION__;

    inputMethodHost()->setRedirectKeys(focusIn);
}

void JapaneseInputMethod::switchContext(Maliit::SwitchDirection direction,
                                          bool enableAnimation)
{
    Q_UNUSED(enableAnimation);
    qDebug() << __PRETTY_FUNCTION__;

    if (m_automata->isComposing()) {
        commitPreedit();
    }

    if (m_isActive) {
        m_isActive = false;
        clear();
        m_keyboard->removeTranslator();
        inputMethodHost()->switchPlugin(direction);
    }
}

void JapaneseInputMethod::setPreedit(const QString &preeditString, int cursorPos)
{
    qDebug() << __PRETTY_FUNCTION__;

    MAbstractInputMethod::setPreedit(preeditString, cursorPos);
}

void JapaneseInputMethod::setActiveSubView(const QString &subViewId, Maliit::HandlerState state)
{
    qWarning() << __PRETTY_FUNCTION__;

    // Ignored as input method only support one subview
    MAbstractInputMethod::setActiveSubView(subViewId, state);
}

bool JapaneseInputMethod::imExtensionEvent(MImExtensionEvent *event)
{
    qWarning() << __PRETTY_FUNCTION__;

    if (!event || event->type() != MImExtensionEvent::Update)
        return false;

    MImUpdateEvent *updateEvent(static_cast<MImUpdateEvent *>(event));

    const QStringList propertiesChanged(updateEvent->propertiesChanged());

    qWarning() << " = = = > propertiesChanged: " << propertiesChanged;

    // contentType
    if (propertiesChanged.contains(ContentTypeAttribute)) {
        const int type(updateEvent->value(ContentTypeAttribute).toInt());
        if (type != m_keyboard->getContentType())
            m_keyboard->setContentType(type);
    }

    // enterKeyType
    if (propertiesChanged.contains(EnterKeyTypeAttribute)) {
        const int type(updateEvent->value(EnterKeyTypeAttribute).toInt());
        if (type != m_keyboard->getEnterKeyType())
            m_keyboard->setEnterKeyType(type);
    }

    // hiddenText
    if (propertiesChanged.contains(HiddenTextAttribute)) {
        const bool hiddenText(updateEvent->value(HiddenTextAttribute).toBool());
        qWarning() << "hiddenText in jp: " << hiddenText;
        if (hiddenText != m_hiddenText) {
            m_hiddenText = hiddenText;
            m_keyboard->setHiddenText(hiddenText);

        }
    }
    return true;
}

void JapaneseInputMethod::showLanguageNotification()
{
    qDebug() << __PRETTY_FUNCTION__;
    MAbstractInputMethod::showLanguageNotification();
}

void JapaneseInputMethod::processKeyEvent(QEvent::Type keyType, Qt::Key keyCode,
                             Qt::KeyboardModifiers modifiers, const QString &text,
                             bool autoRepeat, int count, quint32 nativeScanCode,
                             quint32 nativeModifiers, unsigned long time)
{

    qDebug() << __PRETTY_FUNCTION__;
    qWarning() << "k: " << keyCode << ", n: " << nativeScanCode << ", t: " << keyType << ", modifiers" << QString::number((int)modifiers, 16);
    Q_D(JapaneseInputMethod);


    if(d->dirCursorMoveKey >= 0 && (keyCode == Qt::Key_Return || keyCode == Qt::Key_Enter)) {
        doMoveCursorPosition(d->dirCursorMoveKey);
    }

    switch (nativeScanCode) {
    case REMOTE_UNDEFINED:
    case REMOTE_HOME:
        return;
    }

    if (keyType == QEvent::KeyRelease) {
        d->dirCursorMoveKey = -1;
        // Keys to change language in hardware keyboard
        if ((keyCode == Qt::Key_Hangul && modifiers == Qt::NoModifier)
            || (nativeScanCode == SCANCODE_RALT && nativeModifiers == 0)
            || (keyCode == Qt::Key_Space && modifiers.testFlag(Qt::ControlModifier))) {
            switchContext(Maliit::SwitchForward, false);
        }
        else if (!d->sendEnterKey  && (keyCode == Qt::Key_Enter
                   || keyCode == Qt::Key_Return
                   || nativeScanCode == SCANCODE_OK
                   || nativeScanCode == SCANCODE_RETURN)) {
            if (!m_keyboard->isVisible())
                MAbstractInputMethod::processKeyEvent(keyType, keyCode, modifiers, text, autoRepeat, count, nativeScanCode, nativeModifiers, time);
            m_keyboard->onKeyReleased(keyCode, modifiers, true);
        } else if (d->sendEnterKey  && (keyCode == Qt::Key_Enter || keyCode == Qt::Key_Return)) {
             /* patch for [MFTEVENTFT-59640][MFTEVENTFT-59641] */
            d->sendEnterKey = false;
            inputMethodHost()->sendKeyEvent(QKeyEvent(QEvent::KeyPress,   Qt::Key_Return, Qt::NoModifier, "", false, 0));
            inputMethodHost()->sendKeyEvent(QKeyEvent(QEvent::KeyRelease, Qt::Key_Return, Qt::NoModifier, "", false, 0));
        } else if (d->pressedScanCode != SCANCODE_UNKNOWN && d->pressedScanCode == nativeScanCode) {
            MAbstractInputMethod::processKeyEvent(keyType, keyCode, modifiers,
                text, autoRepeat, count, nativeScanCode, nativeModifiers, time);
        }
        d->pressedScanCode = SCANCODE_UNKNOWN;
        return;
    }

    if (d->checkBypassKey(nativeScanCode)) {
        releaseKeyLock();
        d->pressedScanCode = nativeScanCode;
        MAbstractInputMethod::processKeyEvent(keyType, keyCode, modifiers,
            text, autoRepeat, count, nativeScanCode, nativeModifiers, time);
        return;
    }

    if (processHidKeyEvent(keyType, keyCode, modifiers, text, autoRepeat, count, nativeScanCode, nativeModifiers, time)) {
        releaseKeyLock();
        return;
    }

    // check if it is handled by VKB: 5-way remote
    if (processRemoteKeyEvent(keyCode, nativeScanCode, modifiers))
        return;

    // some key codes should be changed the other key code.
    d->changeKeyCodes(keyCode, nativeScanCode);

    // send to automata
    if ((nativeScanCode != SCANCODE_POINTERON && nativeScanCode != SCANCODE_POINTEROFF)
        && processKeyEventCommon(keyCode, nativeScanCode, modifiers))
        return;

    d->pressedScanCode = nativeScanCode;
    MAbstractInputMethod::processKeyEvent(keyType, keyCode, modifiers,
                                          text, autoRepeat, count, nativeScanCode, nativeModifiers, time);
}

bool JapaneseInputMethod::processHidKeyEvent(QEvent::Type keyType, Qt::Key keyCode,
                       Qt::KeyboardModifiers modifiers, const QString &text,
                       bool autoRepeat, int count, quint32 nativeScanCode,
                       quint32 nativeModifiers, unsigned long time)
{
    qWarning() << __PRETTY_FUNCTION__;
    Q_D(JapaneseInputMethod);

    // Keys to change language in hardware keyboard
    if ((keyCode == Qt::Key_Hangul)
        || (nativeScanCode == SCANCODE_RALT && nativeModifiers == 0)
        || (keyCode == Qt::Key_Space && modifiers.testFlag(Qt::ControlModifier))) {
        // Handle only for the KeyRelease event
        return true;
    }
    bool isCapsLockOn = false;

    // detect CapsLock
    if (Qt::Key_A <= keyCode && keyCode <= Qt::Key_Z) {
        if (modifiers & Qt::ShiftModifier) {
            if (0 < text.length() && 'a' <= text[0] && text[0] <= 'z')
                isCapsLockOn = true;
        } else {
            if (0 < text.length() && 'A' <= text[0] && text[0] <= 'Z')
                isCapsLockOn = true;
        }
    }

    if (nativeScanCode > 0x7F)
        return false;

    if (!m_keyboard->isVisible() && (keyCode == Qt::Key_Up || keyCode == Qt::Key_Down)) {
        m_keyboard->setInputSource(Keyboard::InputSourceHardware);
    }

    if (m_keyboard->inputSource() == Keyboard::InputSourceVirtual) {
        if (keyCode == Qt::Key_Return
            || keyCode == Qt::Key_Enter
            || keyCode == Qt::Key_Escape
            || keyCode == Qt::Key_Tab
            || keyCode == Qt::Key_Up || keyCode == Qt::Key_Down || keyCode == Qt::Key_Left || keyCode == Qt::Key_Right)
            return false;
    } else if (m_keyboard->inputSource() == Keyboard::InputSourceHardware) {
        if (Qt::Key_F1 <= keyCode && keyCode <= Qt::Key_F12) {
            m_keyboard->forceFocusTo("HID");
            if (m_keyboard->hidKeyPressEvent(keyCode, modifiers))
                return true;
        }
    }

    if (nativeScanCode == KEY_CONVERT)
        keyCode = Qt::Key_Henkan;

    m_bHoldSource = (
             (keyCode == Qt::Key_NumLock)
             || (keyCode == Qt::Key_CapsLock)
             || (keyCode == Qt::Key_ScrollLock));

    if (!m_bHoldSource)
        m_keyboard->setInputSource(Keyboard::InputSourceHardware); // set input source as HID
    else
        return true;

    // send to automata
    if (processKeyEventCommon(keyCode, nativeScanCode, modifiers, isCapsLockOn))
        return true;

    d->pressedScanCode = nativeScanCode;
    MAbstractInputMethod::processKeyEvent(keyType, keyCode, modifiers,
        text, autoRepeat, count, nativeScanCode, nativeModifiers, time);

    return true;
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

void JapaneseInputMethod::commitPreedit()
{
    m_automata->processKeyEvent(Qt::Key_Enter,0,Qt::NoModifier);
    QString commit(m_automata->getCommit());
    if (!commit.isEmpty()) {
        inputMethodHost()->sendCommitString(commit);
    }
}

bool JapaneseInputMethod::processKeyEventCommon(Qt::Key keyCode, quint32 nativeScanCode, Qt::KeyboardModifiers modifiers, bool isCaps)
{
    qWarning() << __PRETTY_FUNCTION__;

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
            return false;
    }
    nativeScanCode = nativeScanCode -8;

    bool result = true;

    if (m_keyboard->inputSource() == Keyboard::InputSourceVirtual) {
        if (m_keyboard->vkbMode() == Keyboard::VkbModeEnglish ||
            m_keyboard->vkbMode() == Keyboard::VkbModeSymbol) {
                if (keyCode == Qt::Key_Backspace || keyCode == Qt::Key_Return) return false;
                QString commit = m_automata->convHexToStr(nativeScanCode);
                inputMethodHost()->sendCommitString(commit);
                return true;
        }

        if (!m_automata->processKeyEvent(keyCode,nativeScanCode,modifiers)) {
            result = false;
        }
    }

    if (m_keyboard->inputSource() == Keyboard::InputSourceHardware) {

        if (keyCode == Qt::Key_Left || keyCode == Qt::Key_Right) {
            if (m_automata->isComposing()) {
                commitPreedit();
                m_prediction->setPredictionList(m_automata->getCandidateList());
                return true;
            }
            return false;
        }

        int cantCount = m_automata->candidateListItemCount();
        if (!m_automata->processHIDKeyEvent(keyCode,nativeScanCode,modifiers,isCaps)) {
            result = false;
        }

        if (keyCode == Qt::Key_Space) {
            if (!m_automata->isComposing()) {
                inputMethodHost()->sendCommitString("\u3000");
                return true;
            } else
            if (cantCount == 1) {
                commitPreedit();
                m_prediction->setPredictionList(m_automata->getCandidateList());
                return true;
            }
        }
    }

    QString commit(m_automata->getCommit());
    if (!commit.isEmpty()) {
        inputMethodHost()->sendCommitString(commit);
    }

    QString postPreedit(m_automata->getPreedit());
    QList<Maliit::PreeditTextFormat> formatList;
    formatList.append(Maliit::PreeditTextFormat(0, postPreedit.length(), Maliit::PreeditKeyPress));
    inputMethodHost()->sendPreeditString(postPreedit, formatList);
    m_prediction->setPredictionList(m_automata->getCandidateList());
    m_keyboard->setUnfixedStatus(m_automata->isComposing());

    return result;
}

void JapaneseInputMethod::setKeyOverrides(const QMap<QString, QSharedPointer<MKeyOverride> >& overrides)
{
    qDebug() << __PRETTY_FUNCTION__;
    MAbstractInputMethod::setKeyOverrides(overrides);
}

void JapaneseInputMethod::handleMouseClickOnPreedit(const QPoint& pos, const QRect& preeditRect)
{
    qWarning() << __PRETTY_FUNCTION__;
    MAbstractInputMethod::handleMouseClickOnPreedit(pos, preeditRect);
}

void JapaneseInputMethod::onPredictionSelected(int index)
{
    qDebug() << __PRETTY_FUNCTION__;
    m_automata->candidateListItemSelected(index);

    QString commit(m_automata->getCommit());
    if (!commit.isEmpty()) {
        inputMethodHost()->sendCommitString(commit);
    }

    QString postPreedit(m_automata->getPreedit());
    QList<Maliit::PreeditTextFormat> formatList;
    formatList.append(Maliit::PreeditTextFormat(0, postPreedit.length(), Maliit::PreeditKeyPress));
    inputMethodHost()->sendPreeditString(postPreedit, formatList);

    m_candIndex = 0;
    m_prediction->clearPredictionList();
    if (!m_automata->isComposing())
        m_isConvert = false;
    m_prediction->setPredictionList(m_automata->getCandidateList());
    m_keyboard->setUnfixedStatus(false);
}

void JapaneseInputMethod::onVirtualKeyPressed(quint32 nativeScanCode, Qt::KeyboardModifiers modifiers, int eventType)
{
    qDebug() << __PRETTY_FUNCTION__;
    Q_D(JapaneseInputMethod);

    Qt::Key keyCode = Qt::Key_unknown;
    switch (nativeScanCode) {
    case KEY_BACKSPACE_VKB:
        keyCode = Qt::Key_Backspace;
        break;
    case KEY_RETURN:
        keyCode = Qt::Key_Return;
        break;
    case KEY_CONVERT:
        keyCode = Qt::Key_Henkan;
        break;
    case KEY_ARROW:
        if (modifiers & Qt::ShiftModifier)
            keyCode = Qt::Key_Left;
        else
            keyCode = Qt::Key_Right;
        break;
    }

    m_keyboard->setInputSource(Keyboard::InputSourceVirtual);

    if (!processKeyEventCommon(keyCode, nativeScanCode + 8, modifiers)) {
        if (eventType == MOUSE_EVENT || eventType == TOUCH_EVENT || keyCode != Qt::Key_Return) {
            /* [MFTEVENTFT-62257][MFTEVENTFT-62377][MFTEVENTFT-62395]
             * Send "Enter" key with MRCU "OK"button.
             */
            inputMethodHost()->sendKeyEvent(QKeyEvent(QEvent::KeyPress, keyCode, modifiers, "", false, 0));
            inputMethodHost()->sendKeyEvent(QKeyEvent(QEvent::KeyRelease, keyCode, modifiers, "", false, 0));
        } else {
            /* [MFTEVENTFT-59640][MFTEVENTFT-59641]
             * The real key event from the user/client is processed in the processKeyEvent() function.
             * VKB is deactivated when the user click the "Enter" button in the VKB. If the user clicks/presses
             * this "Enter" button by pressing the NRCU's ok-key or HID keyboard's enter-key, VKB generates
             * the KeyPress event and KeyRelease event then sends it to the client/app. Then the client/app
             * deactivates VKB. VKB is dismissed. BUT there is still real "KeyRelease" event. So it is sent
             * to the app. In turn, the app will receive the key-event by following sequence:
             *   (Virtual-)Enter-KeyPress, (Virtual-)Enter-KeyRelease, (Real-)OK-KeyRelease.
             * The keycodes of the enter-key and ok-key are same.
             * APP receives the KeyRelease event TWICE. It can make some unexpected result.
             * So this change fixes this issue. "Enter" key event is sent at the real keyRelease event.
             */
            d->sendEnterKey = true;
        }
    }
    d->pressedScanCode = SCANCODE_UNKNOWN;
}

void JapaneseInputMethod::onSwitchContext(Maliit::SwitchDirection direction)
{
    qDebug() << __PRETTY_FUNCTION__;
    switchContext(direction, false);
}

void JapaneseInputMethod::onActivateSTT()
{
    qDebug() << __PRETTY_FUNCTION__;
    enableStt->set(true);
}

void JapaneseInputMethod::onClearAllPressed()
{
    qDebug() << __PRETTY_FUNCTION__;
    QString surroundingText;
    int cursor;
    inputMethodHost()->surroundingText(surroundingText, cursor);
    inputMethodHost()->sendCommitString("", -cursor, UINT_MAX);
    m_keyboard->setUnfixedStatus(false);
    m_isConvert = false;
    clear();
}

void JapaneseInputMethod::onMoveCursorPosition(int direction, int eventType)
{
    qWarning() << __PRETTY_FUNCTION__;
    Q_D(JapaneseInputMethod);
    if (eventType == MOUSE_EVENT || eventType == TOUCH_EVENT) {
        doMoveCursorPosition(direction);
        return;
    }
    d->dirCursorMoveKey = direction;
}
void JapaneseInputMethod::doMoveCursorPosition(int direction)
{
    qDebug() << __PRETTY_FUNCTION__;

    if (m_automata->isComposing()) {
        commitPreedit();
        m_prediction->setPredictionList(m_automata->getCandidateList());
        return;
    }

    int keyCode = (direction == DIRECTION_LEFT) ? 113 : 114;
    Qt::Key key = (direction == DIRECTION_LEFT) ? Qt::Key_Left : Qt::Key_Right;

    MAbstractInputMethod::processKeyEvent(QEvent::KeyPress, key, Qt::NoModifier, "", false, 0, keyCode, 0, 0);
    MAbstractInputMethod::processKeyEvent(QEvent::KeyRelease, key, Qt::NoModifier, "", false, 0, keyCode, 0, 0);
}

void JapaneseInputMethod::onTextKeyPressed(QString text)
{
    qDebug() << __PRETTY_FUNCTION__;
    if (0 == text.length())
        return;

    if (m_automata->isComposing()) {
        commitPreedit();
        m_prediction->setPredictionList(m_automata->getCandidateList());
    }

    inputMethodHost()->sendCommitString(text);
    clear();
}

void JapaneseInputMethod::onVisibleChanged(bool isVisible)
{
    qDebug() << __PRETTY_FUNCTION__;
    if (!isVisible)
        clear();
}

void JapaneseInputMethod::onSystemLocaleChanged()
{
    qDebug() << __PRETTY_FUNCTION__;

    QJsonObject objLocaleInfo = QJsonObject::fromVariantMap(m_systemLocale->value().toMap());

    // get the keyboard language array from keyboard settings
    QString LOCALEINFO_KEYBOARDS_KEY = "keyboards";
    QJsonObject::const_iterator it = objLocaleInfo.find(LOCALEINFO_KEYBOARDS_KEY);
    if (it == objLocaleInfo.end()) {
        qWarning() << "cannot find key in locale setting: " << "localeInfo/" << LOCALEINFO_KEYBOARDS_KEY;
        return;
    }

    QJsonArray arKeyboards = it.value().toArray();
    QScopedPointer<QLocale> loc;
    bool isJapaneseEnabled = false;
    for (int i = 0; i < arKeyboards.count(); ++i) {
        if (arKeyboards[i].isString()) {
            loc.reset(new QLocale(arKeyboards[i].toString()));
            if (loc->language() == QLocale::Japanese) {
                isJapaneseEnabled = true;
                break;
            }
        }
    }

    m_isJapaneseEnabled = isJapaneseEnabled;

    //#IF_COMMERCIAL
    static const QString LOCALEINFO_LOCALE_KEY = "locales";
    static const QString LOCALEINFO_LOCALE_UI_KEY = "UI";
    it = objLocaleInfo.find(LOCALEINFO_LOCALE_KEY);
    if (it == objLocaleInfo.end()) {
        qDebug() << "cannot find key in the locale setting: " << LOCALEINFO_LOCALE_KEY;
        return;
    }

    objLocaleInfo = it.value().toObject();
    it = objLocaleInfo.find(LOCALEINFO_LOCALE_UI_KEY);
    if (it == objLocaleInfo.end()) {
        qDebug() << "cannot find key in the locale setting: " << LOCALEINFO_LOCALE_KEY << "/" << LOCALEINFO_LOCALE_UI_KEY;
        return;
    }
    m_keyboard->setNumKeyEnterLabel(it.value().toString());
    //#ELSE
    //#END

    if (!isJapaneseEnabled)
        switchContext(Maliit::SwitchForward, false);
}

void JapaneseInputMethod::setHidModeFromHid(int hidMode)
{
    qDebug() << __PRETTY_FUNCTION__;
    m_keyboard->setHidModeFromHid(hidMode);
}

void JapaneseInputMethod::onSetHidModeFromVkb(int hidMode)
{
    qDebug() << __PRETTY_FUNCTION__;

    if (m_automata->isComposing()) {
        commitPreedit();
    }
    m_automata->setHidMode(hidMode);
    m_prediction->clearPredictionList();
}

void JapaneseInputMethod::onVkbModeChanged(int mode)
{
    qWarning() << __PRETTY_FUNCTION__;
    if (m_automata->isComposing()) {
        commitPreedit();
        m_prediction->setPredictionList(m_automata->getCandidateList());
    }
    switch(mode) {
        case Keyboard::VkbModeHiragana:
        case Keyboard::VkbModeKatakana:
            m_automata->setInputMode(mode);
            break;
        case Keyboard::VkbModeEnglish:
            m_automata->setInputMode(2);
            break;
        case Keyboard::VkbModeSymbol:
            m_automata->setInputMode(3);
            break;
    }
}

bool JapaneseInputMethod::hiddenText()
{
    return m_hiddenText;
}

bool JapaneseInputMethod::hasEnabledLanguages()
{
    return m_isJapaneseEnabled;
}

void JapaneseInputMethod::releaseKeyLock()
{
    qWarning() << __PRETTY_FUNCTION__;
    Q_D(JapaneseInputMethod);
    d->keyLocked = false;
}

bool JapaneseInputMethod::processRemoteKeyEvent(Qt::Key keyCode, quint32 nativeScanCode, Qt::KeyboardModifiers modifiers)
{
    qWarning() << __PRETTY_FUNCTION__;
    Q_D(JapaneseInputMethod);

    if (nativeScanCode == SCANCODE_POINTERON) {
        return false;
    } else if (nativeScanCode == SCANCODE_POINTEROFF) {
        d->blockKeycodeDuring(160);
        return false;
    }

    // Back key should work on pressing
    if (nativeScanCode == SCANCODE_BACK || keyCode == Qt::Key_Escape)
        releaseKeyLock();

    // IR Numeric key: convert to keysym
    m_keySym = getRemoteNumericKeysym(nativeScanCode - EVDEV_OFFSET);
    if (m_keySym != KEYSYM_VOIDSYMBOL) {
        m_bNumberKey = true;
        onTextKeyPressed(QString::number(m_keySym-KEYSYM_0));
        releaseKeyLock();

        // Move the focus to "Enter" button of the VKB: Requirement from HQ QE
        if (m_keyboard->inputSource() == Keyboard::InputSourceVirtual) {
            m_keyboard->forceFocusTo("Enter");
        }
        return true;
    }

    if (d->keyLocked)
        return true;

    bool accepted = false;

    // Replace key code of Remote: keyCode is Qt::Key_Unknown for some remote buttons
    if (nativeScanCode == SCANCODE_OK)         // "OK" button
        keyCode = Qt::Key_Execute;              // FIXME: This is temporary
    else if (nativeScanCode == SCANCODE_BACK)   // "Back" button
        keyCode = Qt::Key_Cancel;               // FIXME: This is temporary
    else if (nativeScanCode == SCANCODE_RETURN) // "OK" button of the 5-way remote
        keyCode = Qt::Key_Execute;              //      will be ignored when VKB is hided
    else if (nativeScanCode == SCANCODE_KEYPAD_ENTER)
        keyCode = Qt::Key_Execute;

    if (keyCode == Qt::Key_Escape)
        keyCode = Qt::Key_Cancel;

    // Extract Remote-Key
    switch (keyCode) {
    case Qt::Key_Up:
    case Qt::Key_Down:
    case Qt::Key_Left:
    case Qt::Key_Right:
    case Qt::Key_Execute:
        accepted = m_keyboard->hidKeyPressEvent(keyCode, modifiers);
        break;
    case Qt::Key_Cancel:
        if (m_keyboard->isVisible()) {
            accepted = true;
            m_keyboard->onHideRequested(false);
        } else {
            accepted = false;
        }
        break;
    default:
        ;
    }

    if (!accepted && nativeScanCode == SCANCODE_RETURN) {
        Q_EMIT showRequested(false);
        accepted = true;
    }
    return accepted;
}

void JapaneseInputMethod::onSwitchSymbolMode(bool isSymbol)
{
    m_isSymbol = isSymbol;

    if (m_isSymbol == true) {
        m_keyboard->setUnfixedStatus(false);
    }
}
