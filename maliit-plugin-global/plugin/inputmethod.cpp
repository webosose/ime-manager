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

#include "inputmethod.h"
#include "globalautomata.h"
#include "languageinfotable.h"
#include "countryinfotable.h"

#include <maliit/plugins/abstractinputmethodhost.h>
#include <maliit/plugins/updateevent.h>
#include <linux/input.h>
#ifndef UBUNTU_DESKTOP_BUILD
#include <qpa/qwindowsysteminterface.h>
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

static const QString GLOBAL_INPUT_METHOD_DEFAULT_LANGUAGE = QLocale::languageToString(QLocale::English);

static const quint32 EVDEV_OFFSET   = 8;

static const quint32 SCANCODE_INIT       = 0xfffffffe;
static const quint32 SCANCODE_UNKNOWN    = 0xffffffff;
static const quint32 SCANCODE_OK         = 0;    // "OK" button of Magic-remote
static const quint32 SCANCODE_BACK       = 420;  // "Back" button of Magic-remote
static const quint32 SCANCODE_POINTERON  = 1206; // Device sends the keycode when the pointer appears
static const quint32 SCANCODE_POINTEROFF = 1207; // Device sends the keycode when the pointer disappears
static const quint32 SCANCODE_BACKSPACE  = 22;   // from VKB
static const quint32 SCANCODE_RETURN     = 36;   // from VKB
static const quint32 SCANCODE_TAB        = 23;   // from VKB
static const quint32 SCANCODE_SPACE      = 65;   // from VKB
static const quint32 SCANCODE_RALT       = 108;  // from HID: Right Alt changes the language of the VKB
static const quint32 SCANCODE_PLAY       = 0xD7;  // from Remote
static const quint32 SCANCODE_PAUSE      = 0x7F;  // from Remote
static const quint32 SCANCODE_STOP       = 0x88;  // from Remote
static const quint32 SCANCODE_REW        = 0xB0;  // from Remote
static const quint32 SCANCODE_FF         = 0xD8;  // from Remote
static const quint32 SCANCODE_REC        = 0xAF;  // from Remote
static const quint32 SCANCODE_KEYPAD_SLASH    = 106;
static const quint32 SCANCODE_KEYPAD_ASTERISK = 63;
static const quint32 SCANCODE_KEYPAD_MINUS    = 82;
static const quint32 SCANCODE_KEYPAD_PLUS     = 86;
static const quint32 SCANCODE_KEYPAD_ENTER    = 104;
static const quint32 SCANCODE_LEFT_SHIFT      = 50;
static const quint32 SCANCODE_RIGHT_SHIFT     = 62;

static const quint32 DIRECTION_LEFT    = 0;
static const quint32 DIRECTION_RIGHT   = 1;

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

class GlobalInputMethodPrivate
{
    Q_DECLARE_PUBLIC(GlobalInputMethod)

public:
    GlobalInputMethod *const q_ptr;
    QLocale::Country country;
    QString countryString;
    QString language;
    QString menuLanguage;
    bool keyLocked;
    QScopedPointer<QTimer> predictionDelayer;
    QScopedPointer<QTimer> switchingDelayer;

    QString surroundingText;
    int cursorPosition;
    bool focusIn;
    quint32 pressedScanCode;
    bool sendEnterKey;
    int dirCursorMoveKey;

    GlobalInputMethodPrivate(GlobalInputMethod *im)
        : q_ptr(im)
        , country(QLocale::AnyCountry)
        , countryString("")
        , language("")
        , menuLanguage("")
        , keyLocked(false)
        , predictionDelayer(new QTimer(q_ptr))
        , switchingDelayer(new QTimer(q_ptr))
        , cursorPosition(-1)
        , focusIn(false)
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

    void delayPredictionUpdate()
    {
        predictionDelayer->setSingleShot(true);
        predictionDelayer->start(400);
    }

    void stopDelayPredictionUpdate()
    {
        predictionDelayer->stop();
    }

    void delayLanguageSwitching()
    {
        switchingDelayer->setSingleShot(true);
        switchingDelayer->start(50);
    }

    void stopDelayLanguageSwitching()
    {
        switchingDelayer->stop();
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
        case SCANCODE_REC:
            bypass = true;
            break;
        }

        return bypass;
    }

    bool isAmericas(QLocale::Country c)
    {
        switch (c) {
        case QLocale::UnitedStates:
        case QLocale::Canada:
        case QLocale::Mexico:
        case QLocale::Honduras:
        case QLocale::Brazil:
        case QLocale::Chile:
        case QLocale::Peru:
        case QLocale::Argentina:
        case QLocale::Ecuador:
        case QLocale::Colombia:
        case QLocale::Panama:
            return true;
        default:
            return false;
        }
        return false;
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

GlobalInputMethod::GlobalInputMethod(MAbstractInputMethodHost *host)
    : MAbstractInputMethod(host)
    , d_ptr(new GlobalInputMethodPrivate(this))
    , m_contentType(Maliit::FreeTextContentType)
    , m_enterKeyType(Maliit::DefaultEnterKeyType)
    , m_hiddenText(false)
    , currentLanguageIndex(0)
    , m_automata(new GlobalAutomata)
    , m_prediction(new Prediction(host))
    , m_keyboard(new Keyboard(this, m_prediction.data()))
    , m_wasLocaleSetup(false)
{
    Q_D(GlobalInputMethod);

    qDebug() << __PRETTY_FUNCTION__;

    // TODO: Define default language set. Maybe English only?
#ifdef UBUNTU_DESKTOP_BUILD
    insertLanguage(QLocale::languageToString(QLocale::Korean));
#endif
    insertLanguage(GLOBAL_INPUT_METHOD_DEFAULT_LANGUAGE);

//#IF_COMMERCIAL
    connect(this,                   SIGNAL(setDefaultFocus()),
            m_keyboard.data(),      SIGNAL(setDefaultFocus()));
//#ELSE
//#END

    // connect button press
    connect(m_prediction.data(),    SIGNAL(predictionSelected(QString, bool)),
            this,                   SLOT  (onPredictionSelected(QString, bool)));

    connect(m_keyboard.data(),      SIGNAL(keyPressed(quint32, Qt::KeyboardModifiers)),
            this,                   SLOT  (onVirtualKeyPressed(quint32, Qt::KeyboardModifiers)));

    connect(m_keyboard.data(),      SIGNAL(keysymPressed(quint32)),
            this,                   SLOT  (onKeysymPressed(quint32)));

    connect(m_keyboard.data(),      SIGNAL(switchContext(Maliit::SwitchDirection)),
            this,                   SLOT  (onSwitchContext(Maliit::SwitchDirection)));

    connect(m_keyboard.data(),      SIGNAL(clearAllPressed()),
            this,                   SLOT  (onClearAllPressed()));

    connect(m_keyboard.data(),      SIGNAL(visibleChanged(bool, bool)),
            this,                   SLOT  (onVisibleChanged(bool, bool)));

    connect(m_keyboard.data(),      SIGNAL(textKeyPressed(QString)),
            this,                   SLOT  (onTextKeyPressed(QString)));

    connect(m_keyboard.data(),      SIGNAL(moveCursorPosition(int)),
            this,                   SLOT  (onMoveCursorPosition(int)));

    // connect update signal
    connect(this,                   SIGNAL(hiddenTextChanged(bool)),
            m_prediction.data(),    SLOT  (onHiddenTextChanged(bool)));

    connect(this,                   SIGNAL(hiddenTextChanged(bool)),
            m_keyboard.data(),      SIGNAL(hiddenTextChanged(bool)));

    connect(this,                   SIGNAL(contentTypeChanged(int)),
            this,                   SLOT  (onContentTypeChanged(int)));

    connect(this,                   SIGNAL(contentTypeChanged(int)),
            m_prediction.data(),    SLOT  (onContentTypeChanged(int)));

    connect(this,                   SIGNAL(contentTypeChanged(int)),
            m_keyboard.data(),      SIGNAL(contentTypeChanged(int)));

    connect(this,                   SIGNAL(enterKeyTypeChanged(int)),
            this,                   SLOT  (onEnterKeyTypeChanged(int)));

    connect(this,                   SIGNAL(enterKeyTypeChanged(int)),
            m_keyboard.data(),      SIGNAL(enterKeyTypeChanged(int)));

    connect(this,                   SIGNAL(surroundingTextChanged()),
            SLOT(onSurroundingTextChanged()));

    connect(this,                   SIGNAL(cursorPositionChanged()),
            SLOT(onCursorPositionChanged()));

    connect(d->predictionDelayer.data(),   SIGNAL(timeout()),
            this,                   SLOT  (onDelayPredictionUpdate()));

    connect(d->switchingDelayer.data(),    SIGNAL(timeout()),
            this,                   SLOT  (onDelaySwitchingLanguage()));

    connect(this,                   SIGNAL(languageCountChanged(int)),
            m_keyboard.data(),      SIGNAL(languageCountChanged(int)));

    connect(this,                   SIGNAL(showRequested(bool)),
            m_keyboard.data(),      SLOT(onShowRequested(bool)));

    QVariantMap attributes;

    // locale info
    systemLocale.reset(inputMethodHost()->registerPluginSetting("localeInfo", QT_TR_NOOP("system locale info"), Maliit::StringType, attributes));
    connect(systemLocale.data(), SIGNAL (valueChanged()),
            this, SLOT (onSystemLocaleChanged()));

    // ime language info
    currentLanguage.reset(inputMethodHost()->registerPluginSetting("currentLanguage", QT_TR_NOOP("current IME language"), Maliit::StringType, attributes));
    defaultLanguage.reset(inputMethodHost()->registerPluginSetting("defaultLanguage", QT_TR_NOOP("default IME language"), Maliit::StringType, attributes));
    if (currentLanguage->value().toString().isEmpty())
        defaultLanguage->set("");

    // country info
    currentCountry.reset(inputMethodHost()->registerPluginSetting("country", QT_TR_NOOP("country info"), Maliit::StringType, attributes));
    connect(currentCountry.data(), SIGNAL(valueChanged()), this, SLOT(onCountryChanged()));

    d->language = getMenuLanguageString(QLocale(currentLanguage->value().toString()), currentLanguage->value().toString());
    if (d->language.length() == 0 || !m_automata->isSupportedLanguage(d->language))
        d->language = GLOBAL_INPUT_METHOD_DEFAULT_LANGUAGE;

    if (d->language != GLOBAL_INPUT_METHOD_DEFAULT_LANGUAGE) {
        insertLanguage(d->language);
        currentLanguageIndex = 1;
        Q_EMIT languageCountChanged(enabledLanguages.count());
    }

    switchContext(Maliit::SwitchUndefined, false);
}

GlobalInputMethod::~GlobalInputMethod()
{
}

void GlobalInputMethod::insertLanguage(QString language)
{
    enabledLanguages.append(language);
    enabledLayouts.append(LayoutLoader(language));
}

void GlobalInputMethod::removeLanguage(QString language)
{
    enabledLanguages.removeAll(language);
    enabledLayouts.removeAll(language);
}

void GlobalInputMethod::onPredictionSelected(QString selectedString, bool replace)
{
    int preeditLength = m_automata->getPreedit().length();
    if (replace) {
        int replaceLength = m_automata->getWordForPrediction().length() - preeditLength;
        selectedString += enabledLayouts.at(currentLanguageIndex).getSeparator();
        inputMethodHost()->sendCommitString(selectedString, -replaceLength, replaceLength);
    } else {
        if (m_contentType == Maliit::UrlContentType && preeditLength > 0) {
            inputMethodHost()->sendCommitString(m_automata->getPreedit());
        }
        inputMethodHost()->sendCommitString(selectedString);
    }
    m_automata->addWord(selectedString);
    // clear automata and clear prediction list
    clear();
}

#define INDEX_IS_VALID(i,list) (0 <= (i) && (i) < (list).length())
void GlobalInputMethod::show()
{
    qWarning() << __PRETTY_FUNCTION__;
    Q_D(GlobalInputMethod);

#ifndef UBUNTU_DESKTOP_BUILD
    QWindowSystemInterface::handleWindowActivated(m_keyboard.data());
#endif

    if (!INDEX_IS_VALID(currentLanguageIndex, enabledLanguages))
        switchContext(Maliit::SwitchUndefined, false);

    m_keyboard->setInputSource(Keyboard::InputSourceVirtual);

    // check the content-type
    bool valid;
    int contentType = inputMethodHost()->contentType(valid);
    if (valid) {
        m_contentType = contentType;
        Q_EMIT contentTypeChanged(contentType);
    }

    int enterKeyType = inputMethodHost()->enterKeyType(valid);
    if (valid) {
        m_enterKeyType = enterKeyType;
        Q_EMIT enterKeyTypeChanged(enterKeyType);
    }

    bool hiddenText = inputMethodHost()->hiddenText(valid);
    if (valid) {
        m_hiddenText = hiddenText;
        Q_EMIT hiddenTextChanged(hiddenText);
    }

    m_keyboard->show();

    // set the initial mouse pointer to visible.
    d->pressedScanCode = SCANCODE_INIT;

    d->sendEnterKey = false;
    appendPredictionSeed();
}

void GlobalInputMethod::hide()
{
    qDebug() << __PRETTY_FUNCTION__;
    Q_D(GlobalInputMethod);
    d->stopDelayPredictionUpdate();
    m_prediction->clearPredictionList();
    m_keyboard->hide();
    m_keyboard->setInputSource(Keyboard::InputSourceNone);
}

QList<MAbstractInputMethod::MInputMethodSubView>
GlobalInputMethod::subViews(Maliit::HandlerState state) const
{
    Q_UNUSED(state);

    MAbstractInputMethod::MInputMethodSubView sub_view;
    sub_view.subViewId = "";
    sub_view.subViewTitle = "";
    QList<MAbstractInputMethod::MInputMethodSubView> sub_views;
    sub_views << sub_view;

    return sub_views;
}

QString GlobalInputMethod::activeSubView(Maliit::HandlerState state) const
{
    Q_UNUSED(state);

    qDebug() << __PRETTY_FUNCTION__;
    return QString("");
}

void GlobalInputMethod::setState(const QSet<Maliit::HandlerState> &state)
{
    qDebug() << __PRETTY_FUNCTION__;
    MAbstractInputMethod::setState(state);
}

void GlobalInputMethod::handleClientChange()
{
    qDebug() << __PRETTY_FUNCTION__;
    MAbstractInputMethod::handleClientChange();
}

void GlobalInputMethod::handleVisualizationPriorityChange(bool inhibitShow)
{
    qDebug() << __PRETTY_FUNCTION__;
    MAbstractInputMethod::handleVisualizationPriorityChange(inhibitShow);
}

void GlobalInputMethod::handleAppOrientationAboutToChange(int angle)
{
    qDebug() << __PRETTY_FUNCTION__;
    // Rotate your input method UI here
    Q_UNUSED(angle);
}

void GlobalInputMethod::handleAppOrientationChanged(int angle)
{
    qDebug() << __PRETTY_FUNCTION__;
    // Can typically be forwarded to handleAppOrientationAboutToChange
    // as long as that method will not do anything when newAngle == previousAngle
    Q_UNUSED(angle);
}

void GlobalInputMethod::update()
{
    qWarning() << __PRETTY_FUNCTION__;
    // empty default implementation
    MAbstractInputMethod::update();
}

void GlobalInputMethod::clear()
{
    qDebug() << __PRETTY_FUNCTION__;
    Q_D(GlobalInputMethod);
    d->stopDelayPredictionUpdate();
    d->surroundingText.clear();
    d->cursorPosition = 0;
    d->dirCursorMoveKey = -1;
    m_automata->reset();
    m_prediction->clearPredictionList();
}

void GlobalInputMethod::reset()
{
    qWarning() << __PRETTY_FUNCTION__;
    clear();
    m_keyboard->removeTranslator();
    // empty default implementation
    MAbstractInputMethod::reset();
}

void GlobalInputMethod::handleFocusChange(bool focusIn)
{
    qWarning() << "focusIn: " << focusIn;
    Q_D(GlobalInputMethod);

    clear();
    Q_EMIT m_keyboard->resetRequested();

    // this is for hardware keyboard
    inputMethodHost()->setRedirectKeys(focusIn);

    d->focusIn = focusIn;
}

void GlobalInputMethod::switchContext(Maliit::SwitchDirection direction, bool enableAnimation)
{
    qWarning() << __PRETTY_FUNCTION__;
    Q_UNUSED(enableAnimation);
    Q_D(GlobalInputMethod);

    if (d->switchingDelayer->isActive())
        d->switchingDelayer->stop();

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

    LanguageInfoTable *langInfo = LanguageInfoTable::getInstance();

    if (!INDEX_IS_VALID(currentLanguageIndex, enabledLanguages)) {
        currentLanguageIndex = -1;
        d->language = enabledLanguages.isEmpty() ? GLOBAL_INPUT_METHOD_DEFAULT_LANGUAGE : enabledLanguages.at(0);
        currentLanguage->set(langInfo->getIso1Code(d->language));
        m_keyboard->removeTranslator();
        inputMethodHost()->switchPlugin(direction);
        // complete changing languages
        m_stopHidCharInput = false;
        return;
    }

    QString preedit(m_automata->getPreedit());
    if (0 < preedit.length())
        inputMethodHost()->sendCommitString(preedit);

    d->language = enabledLanguages.at(currentLanguageIndex);
    m_automata->setLanguage(d->language);
    inputMethodHost()->setLanguage(d->language);

    QString iso1Code = langInfo->getIso1Code(d->language);
    currentLanguage->set(iso1Code);

    QString label = (langInfo->getScript(d->language) == QLocale::LatinScript)
                    ? langInfo->getIso2Code(d->language).toUpper()
                    : langInfo->getOwnLanguage(d->language);

    Q_EMIT m_keyboard->languageChanged(d->language, label, iso1Code, QVariant((enabledLayouts.at(currentLanguageIndex)).getLayout()));
    updateTranslator(true);

    if(m_wasLocaleSetup)
        clear();

    // complete changing languages
    m_stopHidCharInput = false;
}

void GlobalInputMethod::setPreedit(const QString &preeditString, int cursorPos)
{
    qDebug() << __PRETTY_FUNCTION__;

    m_automata->setPreedit(preeditString, cursorPos);
}

void GlobalInputMethod::setActiveSubView(const QString &subViewId, Maliit::HandlerState state)
{
    qDebug() << __PRETTY_FUNCTION__;

    // Ignored as input method only support one subview
    MAbstractInputMethod::setActiveSubView(subViewId, state);
}

bool GlobalInputMethod::imExtensionEvent(MImExtensionEvent *event)
{
    qDebug() << __PRETTY_FUNCTION__;

    if (!event || event->type() != MImExtensionEvent::Update)
        return false;

    Q_D(GlobalInputMethod);

    MImUpdateEvent *updateEvent(static_cast<MImUpdateEvent *>(event));

    const QStringList propertiesChanged(updateEvent->propertiesChanged());

    qWarning() << " = = = > propertiesChanged: " << propertiesChanged;

    // contentType
    if (propertiesChanged.contains(ContentTypeAttribute)) {
        const int type(updateEvent->value(ContentTypeAttribute).toInt());
        if (type != m_contentType) {
            m_contentType = type;
            Q_EMIT contentTypeChanged(type);
            if (m_contentType == Maliit::FreeTextContentType)
                appendPredictionSeed();
        }
    }

    // enterKeyType
    if (propertiesChanged.contains(EnterKeyTypeAttribute)) {
        const int type(updateEvent->value(EnterKeyTypeAttribute).toInt());
        if (type != m_enterKeyType) {
            m_enterKeyType = type;
            Q_EMIT enterKeyTypeChanged(type);
        }
    }

    // hiddenText
    if (propertiesChanged.contains(HiddenTextAttribute)) {
        const bool hiddenText(updateEvent->value(HiddenTextAttribute).toBool());
        qWarning() << "hiddenText: " << hiddenText;
        if (hiddenText != m_hiddenText) {
            m_hiddenText = hiddenText;
            Q_EMIT hiddenTextChanged(hiddenText);
        }
    }

    // surroundingText
    if (propertiesChanged.contains(SurroundingTextAttribute)) {
        const QString surroundingText(updateEvent->value(SurroundingTextAttribute).toString());
        qWarning() << " = = = > surroundingText: " << surroundingText;
        if (surroundingText != d->surroundingText) {
            d->surroundingText = surroundingText;
            Q_EMIT surroundingTextChanged();
        }
    }

    // cursorPosition
    if (propertiesChanged.contains(CursorPositionAttribute)) {
        const int cursorPosition(updateEvent->value(CursorPositionAttribute).toInt());
        qWarning() << " = = = > cursorPosition: " << cursorPosition;
        if (cursorPosition != d->cursorPosition) {
            d->cursorPosition = cursorPosition;
            Q_EMIT cursorPositionChanged();
        }
    }

    return true;
}

void GlobalInputMethod::showLanguageNotification()
{
    qDebug() << __PRETTY_FUNCTION__;
    MAbstractInputMethod::showLanguageNotification();
}

bool GlobalInputMethod::processKeyEventCommon(Qt::Key keyCode, quint32 nativeScanCode, Qt::KeyboardModifiers modifiers, QString text)
{
    qWarning() << "keyCode: " << keyCode << ", naviveScanCode: " << nativeScanCode;
    Q_D(GlobalInputMethod);

    if (keyCode == Qt::Key_Space || keyCode == Qt::Key_Return || keyCode == Qt::Key_Enter) {
        m_automata->addWord(m_automata->getWordForPrediction());
    }

    QString preedit(m_automata->getPreedit());

    //* Changing language, user can't input character.
    if (m_stopHidCharInput == true) return true;

    if (keyCode == Qt::Key_Return || keyCode == Qt::Key_Enter) {
        if (0 < preedit.length()) {
            inputMethodHost()->sendCommitString(preedit);
        }
        clear();
        return false;
    }

    // detect CapsLock
    bool isCapsLockOn = false;
    if (Qt::Key_A <= keyCode && keyCode <= Qt::Key_Z) {
        if (modifiers & Qt::ShiftModifier) {
            if (0 < text.length() && 'a' <= text[0] && text[0] <= 'z')
                isCapsLockOn = true;
        } else {
            if (0 < text.length() && 'A' <= text[0] && text[0] <= 'Z')
                isCapsLockOn = true;
        }
    }
    // detect NumLock
    bool isNumLockOn = false;
    if (modifiers & Qt::KeypadModifier) {
        if (Qt::Key_0 <= keyCode && keyCode <= Qt::Key_9)
            isNumLockOn = true;
        else if (Qt::Key_Period == keyCode)
            isNumLockOn = true;
    }

    // stop HID input while changing languages
    if (!m_stopHidCharInput) {
        if (!m_automata->processKeyEvent(nativeScanCode - 8, modifiers, isCapsLockOn, isNumLockOn)) {
            if (keyCode == Qt::Key_Delete && 0 < preedit.length()) {
                setPreedit(m_automata->getWordForPrediction(), 0);
                inputMethodHost()->sendCommitString(preedit);
                updatePredictionList();
            }
            return false;
        }
    }

    d->delayPredictionUpdate();

    if (keyCode == Qt::Key_Backspace && 0 == preedit.length())
        return false;

    QString commit(m_automata->getCommit());
    if (!commit.isEmpty()) {
        inputMethodHost()->sendCommitString(commit);
    }

    QString postPreedit(m_automata->getPreedit());
    QList<Maliit::PreeditTextFormat> formatList;
    formatList.append(Maliit::PreeditTextFormat(0, postPreedit.length(), Maliit::PreeditKeyPress));
    inputMethodHost()->sendPreeditString(postPreedit, formatList);

    qWarning() << "text " << postPreedit
        << "length " << postPreedit.length()
        << "(" << strlen(postPreedit.toUtf8().data()) << ")";

    return true;
}

void GlobalInputMethod::processKeyEvent(QEvent::Type keyType, Qt::Key keyCode,
                             Qt::KeyboardModifiers modifiers, const QString &text,
                             bool autoRepeat, int count, quint32 nativeScanCode,
                             quint32 nativeModifiers, unsigned long time)
{
    qWarning() << "k: " << keyCode << ", n: " << nativeScanCode << ", t: " << keyType << ", modifiers" << QString::number((int)modifiers, 16);

    Q_D(GlobalInputMethod);

    if(d->dirCursorMoveKey >= 0 && (keyCode == Qt::Key_Return || keyCode == Qt::Key_Enter)) {
        doMoveCursorPosition(d->dirCursorMoveKey);
    }

    // Client requests the keyRelease event
    if (keyType == QEvent::KeyRelease) {
        d->dirCursorMoveKey = -1;
        /* The "OK" key in the MRCU and the NRCU sends the Qt::Key_Return.
         * The "Enter" key in the HID keyboard   sends the Qt::Key_Return.
         * The "Enter" key in the HID keypad     sends the Qt::Key_Enter.
         */
        if (nativeScanCode == SCANCODE_LEFT_SHIFT || nativeScanCode == SCANCODE_RIGHT_SHIFT) {
            // Sending Long shift key release event back to Maliit
            MAbstractInputMethod::processKeyEvent(keyType, keyCode, modifiers,
                text, autoRepeat, count, nativeScanCode, nativeModifiers, time);
        } else
        if ((keyCode == Qt::Key_Hangul)
            || (nativeScanCode == SCANCODE_RALT && nativeModifiers == 0)
            || (keyCode == Qt::Key_Space && modifiers.testFlag(Qt::ControlModifier))) {
            // Handle only for the KeyRelease event
            // stop HID input while changing languages
            if (!m_stopHidCharInput)
                m_stopHidCharInput = true;
            // switch language
            d->delayLanguageSwitching();
        } else if (d->sendEnterKey && (keyCode == Qt::Key_Return || keyCode == Qt::Key_Enter)) {
            /* patch for [BHV-12081] */
            d->sendEnterKey = false;
            m_keyboard->onKeyReleased(keyCode, modifiers, true);
            inputMethodHost()->sendKeyEvent(QKeyEvent(QEvent::KeyPress,   Qt::Key_Return, Qt::NoModifier, "", false, 0));
            inputMethodHost()->sendKeyEvent(QKeyEvent(QEvent::KeyRelease, Qt::Key_Return, Qt::NoModifier, "", false, 0));
        } else if (!d->sendEnterKey
                   && (keyCode == Qt::Key_Return || keyCode == Qt::Key_Enter
                       || nativeScanCode == SCANCODE_OK || nativeScanCode == SCANCODE_RETURN)) {
            if (!m_keyboard->isVisible())
                MAbstractInputMethod::processKeyEvent(keyType, keyCode, modifiers, text, autoRepeat, count, nativeScanCode, nativeModifiers, time);
            m_keyboard->onKeyReleased(keyCode, modifiers, true);
        } else if (m_keyboard->isVisible()
            && (keyCode == Qt::Key_Escape || keyCode == Qt::Key_Cancel || keyCode == Qt::Key_Back || nativeScanCode == SCANCODE_BACK)) {
            m_keyboard->onHideRequested(false);
        } else if (((d->pressedScanCode != SCANCODE_UNKNOWN) && (d->pressedScanCode == nativeScanCode)) ||
                    (keyCode == Qt::Key_Control)) {
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
    if (processKeyEventCommon(keyCode, nativeScanCode, modifiers, text))
        return;

    d->pressedScanCode = nativeScanCode;
    MAbstractInputMethod::processKeyEvent(keyType, keyCode, modifiers,
        text, autoRepeat, count, nativeScanCode, nativeModifiers, time);
}

bool GlobalInputMethod::processHidKeyEvent(QEvent::Type keyType, Qt::Key keyCode,
                       Qt::KeyboardModifiers modifiers, const QString &text,
                       bool autoRepeat, int count, quint32 nativeScanCode,
                       quint32 nativeModifiers, unsigned long time)
{
    qDebug() << __PRETTY_FUNCTION__;
    Q_D(GlobalInputMethod);

    // Keys to change language in hardware keyboard
    if ((keyCode == Qt::Key_Hangul)
        || (nativeScanCode == SCANCODE_RALT && nativeModifiers == 0)
        || (keyCode == Qt::Key_Space && modifiers.testFlag(Qt::ControlModifier))) {
        return true;
    }

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
             m_keyboard->forceFocusTo("HID");
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

    // check if it should be handled by using keysym
    quint32 keysym = d->convertToKeysym(nativeScanCode);
    if (keysym != KEYSYM_VOIDSYMBOL) {
        onKeysymPressed(keysym);
        return true;
    }

    // send to automata
    if (processKeyEventCommon(keyCode, nativeScanCode, modifiers, text))
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

bool GlobalInputMethod::processRemoteKeyEvent(Qt::Key keyCode, quint32 nativeScanCode, Qt::KeyboardModifiers modifiers)
{
    qWarning() << "keyCode: " << keyCode << ", naviveScanCode: " << nativeScanCode;
    Q_D(GlobalInputMethod);

    if (nativeScanCode == SCANCODE_POINTERON) {
        return false;   // send to the client
    }
    else if (nativeScanCode == SCANCODE_POINTEROFF) {
        d->blockKeycodeDuring(160);
        return false;   // send to the client
    }

    // Back key should work on pressing
    if (nativeScanCode == SCANCODE_BACK || keyCode == Qt::Key_Escape)
        releaseKeyLock();

    // IR Numeric key: convert to keysym
    quint32 keysym = getRemoteNumericKeysym(nativeScanCode - EVDEV_OFFSET);
    if (keysym != KEYSYM_VOIDSYMBOL) {
        releaseKeyLock();
        onTextKeyPressed(QString::number(keysym-KEYSYM_0));

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
    if (nativeScanCode == SCANCODE_OK)         // "OK" button of the Magic remote
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
        if (!m_keyboard->isVisible())
            break;
        if (m_keyboard->cursorVisible()) {
            accepted = m_keyboard->isVisible();
        } else {
            accepted = m_keyboard->hidKeyPressEvent(keyCode, modifiers);
        }
        break;
    case Qt::Key_Cancel:
        if (m_keyboard->isVisible()) {
            accepted = true;
        } else {
            accepted = false;
        }
        break;
    default:
        ;
    }

    if (!accepted && nativeScanCode == SCANCODE_RETURN) {
        Q_EMIT showRequested(false);
        appendPredictionSeed();
        accepted = true;
    }

    return accepted;
}

void GlobalInputMethod::setKeyOverrides(const QMap<QString, QSharedPointer<MKeyOverride> > &overrides)
{
    qDebug() << __PRETTY_FUNCTION__;
    MAbstractInputMethod::setKeyOverrides(overrides);
}

void GlobalInputMethod::handleMouseClickOnPreedit(const QPoint &pos, const QRect &preeditRect)
{
    qDebug() << __PRETTY_FUNCTION__;
    // FIXME: reset?
    MAbstractInputMethod::handleMouseClickOnPreedit(pos, preeditRect);
}

void GlobalInputMethod::onVirtualKeyPressed(quint32 nativeScanCode, Qt::KeyboardModifiers modifiers)
{
    qWarning() << "naviveScanCode: " << nativeScanCode;
    Q_D(GlobalInputMethod);

    //FIXME: this should not happen here. move to keyboard proxy.
    Qt::Key keyCode = Qt::Key_unknown;
    if (nativeScanCode == SCANCODE_BACKSPACE)
        keyCode = Qt::Key_Backspace;
    else if (nativeScanCode == SCANCODE_RETURN)
        keyCode = Qt::Key_Return;
    else if (nativeScanCode == SCANCODE_TAB)
        keyCode = Qt::Key_Tab;
    else if (nativeScanCode == SCANCODE_SPACE)
        keyCode = Qt::Key_Space;

    if (keyCode == Qt::Key_unknown)
        return;

    m_keyboard->setInputSource(Keyboard::InputSourceVirtual);

    if (!processKeyEventCommon(keyCode, nativeScanCode, modifiers)) {
        if (m_keyboard->cursorVisible() || keyCode != Qt::Key_Return) {
            inputMethodHost()->sendKeyEvent(QKeyEvent(QEvent::KeyPress,   keyCode, modifiers, "", false, 0));
            inputMethodHost()->sendKeyEvent(QKeyEvent(QEvent::KeyRelease, keyCode, modifiers, "", false, 0));
        } else {
            /* [BHV-12081]
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

void GlobalInputMethod::onClearAllPressed()
{
    qDebug() << __PRETTY_FUNCTION__;

    QString surroundingText;
    int cursor = inputMethodHost()->surroundingText(surroundingText, cursor) ? cursor : 0;
    inputMethodHost()->sendCommitString("", -cursor, UINT_MAX);
    clear();
}

void GlobalInputMethod::onMoveCursorPosition(int direction)
{
    qWarning() << __PRETTY_FUNCTION__;
    Q_D(GlobalInputMethod);
    if (m_keyboard->cursorVisible()) {
        doMoveCursorPosition(direction);
        return;
    }
    d->dirCursorMoveKey = direction;
}

void GlobalInputMethod::doMoveCursorPosition(int direction)
{
    qDebug() << __PRETTY_FUNCTION__;

    int keyCode = (direction == DIRECTION_LEFT) ? 113 : 114;
    Qt::Key key = (direction == DIRECTION_LEFT) ? Qt::Key_Left : Qt::Key_Right;

    MAbstractInputMethod::processKeyEvent(QEvent::KeyPress, key, NULL, "", false, 0, keyCode, 0, 0);
    MAbstractInputMethod::processKeyEvent(QEvent::KeyRelease, key, NULL, "", false, 0, keyCode, 0, 0);
}

void GlobalInputMethod::onTextKeyPressed(QString text)
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

void GlobalInputMethod::onVisibleChanged(bool visible, bool reset)
{
    qDebug() << __PRETTY_FUNCTION__ << visible;

    if (reset)
        this->clear();
}

void GlobalInputMethod::onSystemLocaleChanged()
{
    qDebug() << __PRETTY_FUNCTION__;
    Q_D(GlobalInputMethod);

    QJsonObject objLocaleInfo = QJsonObject::fromVariantMap(systemLocale->value().toMap());

    // get the keyboard language array from keyboard settings
    static const QString LOCALEINFO_KEYBOARDS_KEY = "keyboards";
    QJsonObject::const_iterator it = objLocaleInfo.find(LOCALEINFO_KEYBOARDS_KEY);
    if (it == objLocaleInfo.end()) {
        qWarning() << "cannot find key in locale setting: " << "localeInfo/" << LOCALEINFO_KEYBOARDS_KEY;
        return;
    }
    QJsonArray arKeyboards = it.value().toArray();
    if (arKeyboards.isEmpty() || arKeyboards.contains("None")) { // keep the previous or default languages if "keyboards" is empty
        qWarning() << "There is no value at keyboards in locale setting";
        return;
    }

    QStringList keyboards;
    QScopedPointer<QLocale> loc;
    QString lang;
    for (int i = 0; i < arKeyboards.count(); ++i) {
        if (arKeyboards[i].isString()) {
            qWarning() << "arKeyboards[i].toString()" << arKeyboards[i].toString();
            loc.reset(new QLocale(arKeyboards[i].toString()));
            lang = getMenuLanguageString(*loc, arKeyboards[i].toString());
            if (m_automata->isSupportedLanguage(lang))
                keyboards.append(lang);
        }
    }

    if (keyboards.count() > 0 && keyboards != enabledLanguages) {
        // generate language/layout set
        enabledLayouts.clear();
        enabledLanguages.clear();
        for (int i = 0; i < keyboards.count(); ++i)
            insertLanguage(keyboards.at(i));

        if (defaultLanguage->value().toString() != keyboards[0]
                && keyboards[0] == QLocale::languageToString(QLocale::Estonian)) {
            /* http://hlm.lge.com/qi/browse/MFTEVENTFT-2149
             * The task for broad certification requested this change for the Digilev of Estonia.
             * It requires Estonian keyboard as default.
             * If FirstUse app adds the "et" as the first string of the localeInfo.keyboards
             * in the locale setting stage, VKB changes the default keyboard to Estonian.
             */
            defaultLanguage->set(keyboards[0]);
            currentLanguageIndex = 0;
        } else {
            /* Set the default keyboard to English and set index into latest language
             */
            defaultLanguage->set(GLOBAL_INPUT_METHOD_DEFAULT_LANGUAGE);
            currentLanguageIndex = enabledLanguages.indexOf(d->language);
        }

        switchContext(Maliit::SwitchUndefined, false);
        keyboards.clear();
    }

    Q_EMIT languageCountChanged(arKeyboards.count());

    m_wasLocaleSetup = true;

    // get the Menu language
    static const QString LOCALEINFO_LOCALE_KEY = "locales";
    static const QString LOCALEINFO_LOCALE_UI_KEY = "UI";

    it = objLocaleInfo.find(LOCALEINFO_LOCALE_KEY);
    if (it == objLocaleInfo.end()) {
        qDebug() << "cannot find key in the locale setting: " << LOCALEINFO_LOCALE_KEY;
        return;
    }
    QJsonObject objLocales = it.value().toObject();
    it = objLocales.find(LOCALEINFO_LOCALE_UI_KEY);
    if (it == objLocales.end()) {
        qDebug() << "cannot find key in the locale setting: " << LOCALEINFO_LOCALE_KEY << "/" << LOCALEINFO_LOCALE_UI_KEY;
        return;
    }

    QString langCode = it.value().toString(); //ex) en-US
    loc.reset(new QLocale(langCode));
    lang = getMenuLanguageString(*loc, langCode);
    if (lang != d->menuLanguage) {
        d->menuLanguage = lang;
        updateTranslator(true);
    }
}

void GlobalInputMethod::onCountryChanged()
{
    qDebug() << __PRETTY_FUNCTION__;
    Q_D(GlobalInputMethod);

    QLocale::Country country = (QLocale::Country)(CountryInfoTable::getInstance()->conv3166ToCountryLocale(currentCountry->value().toString()));
    if (d->country != country) {
        d->country = country;
        d->countryString = QLocale::countryToString(country);
        m_prediction->setCountry(d->countryString);
        Q_EMIT m_keyboard->countryChanged(d->countryString);
    }
}

// This will most likely process letter keys only
void GlobalInputMethod::onKeysymPressed(quint32 keysym)
{
    if (!m_automata->processKeysym(keysym))
        return;

    QString commit(m_automata->getCommit());

    if (!commit.isEmpty())
        inputMethodHost()->sendCommitString(commit);

    updatePredictionList();

    QString postPreedit(m_automata->getPreedit());
    QList<Maliit::PreeditTextFormat> formatList;
    formatList.append(Maliit::PreeditTextFormat(0, postPreedit.length(), Maliit::PreeditKeyPress));
    inputMethodHost()->sendPreeditString(postPreedit, formatList);
}

QString GlobalInputMethod::getMenuLanguageString(QLocale locale, QString langCode)
{
    qDebug() << __PRETTY_FUNCTION__;

    if (locale == QLocale::c()) {
        if (langCode == "ku")
            return QLocale::languageToString(QLocale::Kurdish);
        else if (langCode == "mi")
            return QLocale::languageToString(QLocale::Maori);
        else if (langCode == "mn")
            return QLocale::languageToString(QLocale::Mongolian);
        else
            return "";
    }

    QString language = QLocale::languageToString(locale.language());

    switch (locale.language()) {
    case QLocale::Uzbek:
    case QLocale::Chinese:
        language += "-" + QLocale::scriptToString(locale.script());
        break;
    default:
        ;
    }

    return language;
}

void GlobalInputMethod::updatePredictionList()
{
    Q_D(GlobalInputMethod);
    if (d->predictionDelayer->isActive())
        d->predictionDelayer->stop();
    if (!hiddenText()) {
        switch (contentType()) {
        case Maliit::UrlContentType:
        case Maliit::EmailContentType:
        case Maliit::PhoneNumberContentType:
        case Maliit::NumberContentType:
            break;
        default:
            m_prediction->setPredictionList(m_automata->getPredictionList(d->language));
        }
    }
}

bool GlobalInputMethod::hiddenText()
{
    return m_hiddenText;
}

int GlobalInputMethod::contentType()
{
    return m_contentType;
}

int GlobalInputMethod::enterKeyType()
{
    return m_enterKeyType;
}

QString GlobalInputMethod::surroundingText()
{
    int position;
    QString text = inputMethodHost()->surroundingText(text, position) ? text : "";
    return text;
}

int GlobalInputMethod::cursorPosition()
{
    QString text;
    int position = inputMethodHost()->surroundingText(text, position) ? position : 0;
    return position;
}

void GlobalInputMethod::releaseKeyLock()
{
    qDebug() << __PRETTY_FUNCTION__;
    Q_D(GlobalInputMethod);
    d->keyLocked = false;
}

void GlobalInputMethod::onSurroundingTextChanged()
{
    appendPredictionSeed();
}

void GlobalInputMethod::onCursorPositionChanged()
{
    appendPredictionSeed();
}

void GlobalInputMethod::onContentTypeChanged(int contentType)
{
    Q_UNUSED(contentType);
    updateTranslator(false);
}

void GlobalInputMethod::onEnterKeyTypeChanged(int enterKeyType)
{
    Q_UNUSED(enterKeyType);
}

void GlobalInputMethod::onDelayPredictionUpdate()
{
    qDebug() << __PRETTY_FUNCTION__;
    updatePredictionList();
}

void GlobalInputMethod::onSwitchContext(Maliit::SwitchDirection direction)
{
    qDebug() << __PRETTY_FUNCTION__;
    switchContext(direction, false);
}

void GlobalInputMethod::onDelaySwitchingLanguage()
{

    Q_D(GlobalInputMethod);

    switchContext(Maliit::SwitchForward, false);

    // show the notification for the language change if HID mode
    switch (d->country) {
    case QLocale::China:
    case QLocale::HongKong:
    case QLocale::Taiwan:
    case QLocale::Japan:
        // UX decides that the Device for these countries doesn't show the notification because of plugin structure
        break;
    default:
        if (d->focusIn
            && (m_keyboard->inputSource() == Keyboard::InputSourceHardware || !m_keyboard->isVisible())) {
            m_keyboard->showLanguageNotification(LanguageInfoTable::getInstance()->getOwnLanguage(d->language));
        }
    }

//    /* [WEBOSLCD13-78727] No focus after switching language using the language key of the HID keyboard
//     * : When switching language, letter buttons of the grid become invalid. So It needs to
//     *   set a middle button as the default focus item.
//     */
//    if (d->focusIn) {
//        Q_EMIT setDefaultFocus();
//    }
}

void GlobalInputMethod::appendPredictionSeed()
{
    Q_D(GlobalInputMethod);
    QString surroundingText;
    int cursor;
    bool valid;
    bool hasSelection = inputMethodHost()->hasSelection(valid);
    bool validText = inputMethodHost()->surroundingText(surroundingText, cursor);

    if (!valid || !validText || hasSelection)
        return;
    if (!m_automata->isPredictionSupported())
        return;

    if (m_automata->getPreedit().length() == 0) {
        QString predictString;
        if (cursor < 1) {
            predictString = "";
        } else if (surroundingText.at(cursor - 1) == ' ') {
            predictString = "";
        } else {
            int begin = surroundingText.lastIndexOf(QRegExp("\\s"), cursor - 1);
            if (begin < 0)
                begin = 0;
            else
                begin++;
            if (cursor <= begin)
                predictString = "";
            else
                predictString = surroundingText.mid(begin, cursor - begin);

        }
        setPreedit(predictString, cursor);

        if (m_keyboard->inputSource() == Keyboard::InputSourceVirtual)
            updatePredictionList();
        else if (m_keyboard->inputSource() == Keyboard::InputSourceHardware)
            d->delayPredictionUpdate();
    }
}

void GlobalInputMethod::updateTranslator(bool speakLanguage)
{
    Q_D(GlobalInputMethod);

    QString langCode;
    if (m_contentType == Maliit::NumberContentType || m_contentType == Maliit::PhoneNumberContentType)
        langCode = LanguageInfoTable::getInstance()->getIso1Code(d->menuLanguage);
    else
        langCode = LanguageInfoTable::getInstance()->getIso1Code(d->language);

    QString localeCode = langCode;

    if (langCode == "es" && !d->isAmericas(d->country))
        localeCode += "_ES";
    else if (langCode == "fr" && d->isAmericas(d->country))
        localeCode += "_CA";

    m_keyboard->setTranslator(localeCode, speakLanguage);
}
