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

#include "keyboard.h"
#include "prediction.h"
#include "inputmethod.h"

#include <maliit/plugins/abstractinputmethodhost.h>
#include "maliitenums.h"
#include <webosshell.h>
#include <webosshellsurface.h>

Keyboard::Keyboard(JapaneseInputMethod* im, Prediction* prediction)
    : QQuickView()
    , m_im(im)
    , m_ime(WebOSPlatform::instance()->inputManager())
    , m_inputSource(InputSourceNone)
    , m_vkbMode(VkbModeHiragana)
    , m_hidMode(0)
    , translator(new QTranslator(this))
    , m_contentType(Maliit::FreeTextContentType)
    , m_enterKeyType(Maliit::DefaultEnterKeyType)
    , m_hiddenText(false)
{
    // register enums and objects before loading qml
    qmlRegisterUncreatableType<MaliitEnums>("com.meego.maliit", 1, 0,
            "Maliit", "This is the class used to export Maliit Enums");

    QQmlContext *rootCtx = rootContext();
    rootCtx->setContextProperty("PluginProxy", this);
    rootCtx->setContextProperty("Prediction", prediction);

    QSurfaceFormat f = format();
    f.setAlphaBufferSize(8);
    f.setBlueBufferSize(8);
    f.setGreenBufferSize(8);
    f.setRedBufferSize(8);
    setFormat(f);

    create();

    WebOSShell *shell = WebOSPlatform::instance()->shell();
    WebOSShellSurface* shellSurface = shell ? shell->shellSurfaceFor(this) : nullptr;
    if (shellSurface)
        shellSurface->setProperty(QStringLiteral("displayAffinity"), QString("%1").arg(instanceId()));

    setY(m_winInfo.screenHeight() - m_winInfo.windowHeight());
    resize(m_winInfo.windowWidth(), m_winInfo.windowHeight());
    setResizeMode(QQuickView::SizeRootObjectToView);
    setFlags(flags() | Qt::FramelessWindowHint);

    QString mainPath = QString("%1%2").arg(IMEMANAGER_RESOURCE_PATH).arg("/qml/view-japanese/main.qml");
    setSource(mainPath);

    QQuickItem *rootObj = rootObject();
    QObject::connect(rootObj, SIGNAL (keyPressed(QString, bool, int)),
            this, SLOT(onKeyPressed(QString, bool, int)));

    QObject::connect(rootObj, SIGNAL (switchContext()),
            this, SLOT(onSwitchContext()));

    QObject::connect(rootObj, SIGNAL (clearAllPressed()),
            this, SIGNAL(clearAllPressed()));

    QObject::connect(rootObj, SIGNAL (showRequested(bool)),
            this, SLOT(onShowRequested(bool)));

    QObject::connect(rootObj, SIGNAL (hideRequested(bool)),
            this, SLOT(onHideRequested(bool)));

    QObject::connect(rootObj, SIGNAL (clickInputCharacterChangeButton(QString)),
            this, SLOT(onClickInputCharacterChangeButton(QString)));

    QObject::connect(rootObj, SIGNAL (setHidModeFromVkb(int)),
            this, SIGNAL(setHidModeFromVkb(int)));

    QObject::connect(rootObj, SIGNAL (textKeyPressed(QString)),
            this, SIGNAL(textKeyPressed(QString)));

    QObject::connect(rootObj, SIGNAL (activateSTT()),
            this, SIGNAL(activateSTT()));

    QObject::connect(rootObj, SIGNAL (switchSymbolMode(bool)),
            this, SLOT(onSwitchSymbolMode(bool)));

    QObject::connect(rootObj, SIGNAL (keyReleased(bool)),
            this, SLOT(onKeyReleased(bool)));

    QObject::connect(rootObj, SIGNAL (moveCursorPosition(int, int)),
            this, SIGNAL(moveCursorPosition(int, int)));

//#IF_COMMERCIAL
    initializeHashTable();
//#ELSE
//#END

    m_im->inputMethodHost()->registerWindow(this, Maliit::PositionCenterBottom);
    m_unfixedStatus = false;
    QObject::connect(m_ime, SIGNAL(cursorVisibleChanged(bool)), this, SIGNAL(cursorVisibleChanged(bool)));
}

bool Keyboard::hidKeyPressEvent(Qt::Key keyCode, Qt::KeyboardModifiers modifiers)
{
    qWarning() << __PRETTY_FUNCTION__;
    if (!isVisible()) return false;
    QScopedPointer<QKeyEvent> ev(new QKeyEvent(QEvent::KeyPress, keyCode, modifiers));
    keyPressEvent(ev.data());
    return true;
}

void Keyboard::onShowRequested(bool reset)
{
    qDebug() << __PRETTY_FUNCTION__;

    show();
    Q_EMIT visibleChanged(true, reset);
}

void Keyboard::onHideRequested(bool reset)
{
    qDebug() << __PRETTY_FUNCTION__;

    hide();
    Q_EMIT visibleChanged(false, reset);
}

void Keyboard::onKeyPressed(QString nativeScanCode, bool shift, int eventType)
{
    Qt::KeyboardModifiers modifiers = Qt::NoModifier;
    if (shift) modifiers |= Qt::ShiftModifier;

    bool ok;
    int keyCode = nativeScanCode.toInt(&ok, 16);
    if (!ok) {
        qWarning() << "nativeScanCode convert fail: " << nativeScanCode;
        return;
    }

    Q_EMIT keyPressed(keyCode, modifiers, eventType);
}

void Keyboard::onSwitchContext()
{
    Q_EMIT switchContext(Maliit::SwitchForward);
}

void Keyboard::onKeyReleased(Qt::Key keyCode, Qt::KeyboardModifiers modifiers, bool isReleased)
{
    QScopedPointer<QKeyEvent> ev(new QKeyEvent(QEvent::KeyRelease, keyCode, modifiers));
    keyReleaseEvent(ev.data());
    Q_EMIT keyReleased(isReleased);
}

Keyboard::InputSource Keyboard::inputSource()
{
    return m_inputSource;
}

void Keyboard::setInputSource(Keyboard::InputSource source)
{
    if(source != m_inputSource){
        m_inputSource = source;
        Q_EMIT inputSourceChanged(source);
    }
}

bool Keyboard::cursorVisible()
{
    qDebug() << __PRETTY_FUNCTION__;

    return m_ime->getCursorVisible();
}

bool Keyboard::hiddenText()
{
    qDebug() << __PRETTY_FUNCTION__;
    return  m_hiddenText;
}

void Keyboard::onClickInputCharacterChangeButton(QString vkbMode)
{
    if (vkbMode == "Hiragana")
        m_vkbMode = VkbModeHiragana;
    else if (vkbMode == "Katakana")
        m_vkbMode = VkbModeKatakana;
    else if (vkbMode == "Symbol")
        m_vkbMode = VkbModeSymbol;
    else
        m_vkbMode = VkbModeEnglish;

    Q_EMIT vkbModeChanged(m_vkbMode);
}

Keyboard::VkbMode Keyboard::vkbMode() const
{
    return m_vkbMode;
}

int Keyboard::hidMode()
{
    return m_hidMode;
}

void Keyboard::setHidModeFromHid(int hidMode)
{
    m_hidMode = hidMode;

    Q_EMIT hidModeChanged(hidMode);
}

void Keyboard::setPanelHeight(int height)
{
    setY(m_winInfo.screenHeight() - height);
    resize(m_winInfo.windowWidth(), height);
}

void Keyboard::resetPanelHeight()
{
    setY(m_winInfo.screenHeight() - m_winInfo.windowHeight());
    resize(m_winInfo.windowWidth(), m_winInfo.windowHeight());
}

void Keyboard::setTranslator(QString langCode)
{
    removeTranslator();
    translator->load(QString("imemanager_") + langCode, "/usr/share/qml/locales/imemanager", "-");
    qApp->installTranslator(translator.data());
    Q_EMIT translatorChanged();
}

void Keyboard::removeTranslator()
{
    qApp->removeTranslator(translator.data());
}

bool Keyboard::isUnfixedStatus()
{
    return m_unfixedStatus;
}

void Keyboard::setUnfixedStatus(bool unfixedStatus)
{
    m_unfixedStatus = unfixedStatus;
    Q_EMIT unfixedStatusChanged(unfixedStatus);
}

QString Keyboard::emptyString()
{
    return "";
}

int Keyboard::getContentType()
{
    qDebug() << __PRETTY_FUNCTION__;

    return m_contentType;
}

int Keyboard::getEnterKeyType()
{
    qDebug() << __PRETTY_FUNCTION__;

    return m_enterKeyType;
}

void Keyboard::setContentType(int contentType)
{
    qDebug() << __PRETTY_FUNCTION__;

    m_contentType = contentType;
    Q_EMIT contentTypeChanged(contentType);
}

void Keyboard::setEnterKeyType(int enterKeyType)
{
    qDebug() << __PRETTY_FUNCTION__;

    m_enterKeyType = enterKeyType;
    Q_EMIT enterKeyTypeChanged(enterKeyType);
}

void Keyboard::setHiddenText(bool isHidden)
{
    qDebug() << __PRETTY_FUNCTION__;

    m_hiddenText = isHidden;
    Q_EMIT hiddenTextChanged(isHidden);
}

//#IF_COMMERCIAL
static QHash<QString, QString> s_languageHash;
void Keyboard::setNumKeyEnterLabel(QString language)
{
    qDebug() << __PRETTY_FUNCTION__;

    m_numKeyEnter = s_languageHash.contains(language) ? s_languageHash.value(language) : "Enter";
    Q_EMIT numKeyEnterLabelChanged();
}

void Keyboard::initializeHashTable()
{
    // initialize table
    s_languageHash.reserve(19);

    s_languageHash.insert(QString("cs-CZ"), QString("Zadat"));
    s_languageHash.insert(QString("da-DK"), QString("Indtast"));
    s_languageHash.insert(QString("de-DE"), QString("Eingabetaste"));
    s_languageHash.insert(QString("es-ES"), QString("Intro"));
    s_languageHash.insert(QString("el-GR"), QString("Enter"));
    s_languageHash.insert(QString("fr-FR"), QString("Entrer"));
    s_languageHash.insert(QString("it-IT"), QString("Invio"));
    s_languageHash.insert(QString("nl-NL"), QString("Invoeren"));
    s_languageHash.insert(QString("nb-NO"), QString("OK"));
    s_languageHash.insert(QString("pt-PT"), QString("Entrer"));
    s_languageHash.insert(QString("pt-BR"), QString("Entrer"));
    s_languageHash.insert(QString("ru-RU"), QString("Ввести"));
    s_languageHash.insert(QString("fi-FI"), QString("Syötä"));
    s_languageHash.insert(QString("sv-SE"), QString("OK"));
    s_languageHash.insert(QString("ko-KR"), QString("입력"));
    s_languageHash.insert(QString("zh-Hans-CN"), QString("输入"));
    s_languageHash.insert(QString("ja-JP"), QString("入力"));
    s_languageHash.insert(QString("zh-Hant-HK"), QString("輸入"));
    s_languageHash.insert(QString("ar-SA"), QString("ﺇﺪﺧﺎﻟ"));
}
//#ELSE
//#END

void Keyboard::onSwitchSymbolMode(bool isSymbol)
{
    Q_EMIT switchSymbolMode(isSymbol);
}

int Keyboard::instanceId()
{
    qDebug() << __PRETTY_FUNCTION__;
    return m_im->inputMethodHost()->instanceId();
}

QString Keyboard::maliitServiceId()
{
    qDebug() << __PRETTY_FUNCTION__;

    return m_im->inputMethodHost()->serviceName();
}
