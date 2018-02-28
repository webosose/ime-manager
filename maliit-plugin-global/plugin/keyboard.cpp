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

#include "keyboard.h"
#include "prediction.h"
#include "inputmethod.h"

#include <maliit/plugins/abstractinputmethodhost.h>
#include "maliitenums.h"
#ifdef UBUNTU_DESKTOP_BUILD
#include "dummyservice.h"
#endif
#include <qpa/qplatformnativeinterface.h>

Keyboard::Keyboard(GlobalInputMethod* im, Prediction* prediction)
    : QQuickView()
    , m_im(im)
    , m_ime(WebOSPlatform::instance()->inputManager())
    , m_winInfo(new WindowInformation)
    , m_inputSource(InputSourceNone)
    , translator(new QTranslator(this))
    , translatorLangCode("")
{
    // register enums and objects before loading qml
    qmlRegisterUncreatableType<MaliitEnums>("com.meego.maliit", 1, 0,
            "Maliit", "This is the class used to export Maliit Enums");
#ifdef UBUNTU_DESKTOP_BUILD
    qmlRegisterType<DummyService>("WebOSServices", 1, 0, "Service");
#endif

    QQmlContext *rootCtx = rootContext();
    rootCtx->setContextProperty("PluginProxy", this);
    rootCtx->setContextProperty("Prediction", prediction);
    rootCtx->setContextProperty("WindowInformation", m_winInfo.data());

    QSurfaceFormat f = format();
    f.setAlphaBufferSize(8);
    f.setBlueBufferSize(8);
    f.setGreenBufferSize(8);
    f.setRedBufferSize(8);
    setFormat(f);

    create();

    setY(m_winInfo->screenHeight() - m_winInfo->windowHeight());
    resize(m_winInfo->windowWidth(), m_winInfo->windowHeight());
    setResizeMode(QQuickView::SizeRootObjectToView);
    setFlags(flags() | Qt::FramelessWindowHint);

    load();

    QObject::connect(m_ime, SIGNAL(cursorVisibleChanged(bool)), this, SIGNAL(cursorVisibleChanged(bool)));
}

void Keyboard::load()
{
    QString mainPath = QString("%1%2").arg(IMEMANAGER_RESOURCE_PATH).arg("/qml/view-global/main.qml");
    qWarning() << "### mainPath" << mainPath;

    setSource(mainPath);

    QQuickItem *rootObj = rootObject();
    QObject::connect(rootObj, SIGNAL (keyPressed(QString, bool)),
            this, SLOT(onKeyPressed(QString, bool)));

    QObject::connect(rootObj, SIGNAL (switchContext()),
            this, SLOT(onSwitchContext()));

    QObject::connect(rootObj, SIGNAL (activateSTT()),
            this, SIGNAL(activateSTT()));

    QObject::connect(rootObj, SIGNAL (clearAllPressed()),
            this, SIGNAL(clearAllPressed()));

    QObject::connect(rootObj, SIGNAL (textKeyPressed(QString)),
            this, SIGNAL(textKeyPressed(QString)));

    QObject::connect(rootObj, SIGNAL (showRequested(bool)),
            this, SLOT(onShowRequested(bool)));

    QObject::connect(rootObj, SIGNAL (hideRequested(bool)),
            this, SLOT(onHideRequested(bool)));

    QObject::connect(rootObj, SIGNAL (keysymPressed(QString)),
            this, SLOT(onKeysymPressed(QString)));

    QObject::connect(rootObj, SIGNAL (keyReleased(bool)),
            this, SLOT(onKeyReleased(bool)));

    QObject::connect(rootObj, SIGNAL (moveCursorPosition(int)),
            this, SIGNAL(moveCursorPosition(int)));

    m_im->inputMethodHost()->registerWindow(this, Maliit::PositionCenterBottom);
}

bool Keyboard::hidKeyPressEvent(Qt::Key keyCode, Qt::KeyboardModifiers modifiers)
{
    qDebug() << __PRETTY_FUNCTION__;

    if (!isVisible()) return false;

    QScopedPointer<QKeyEvent> ev(new QKeyEvent(QEvent::KeyPress, keyCode, modifiers));
    keyPressEvent(ev.data());

    return true;
}

void Keyboard::onShowRequested(bool reset)
{
    qDebug() << __PRETTY_FUNCTION__;

    show();
    update();
    Q_EMIT visibleChanged(true, reset);
}

void Keyboard::onHideRequested(bool reset)
{
    qDebug() << __PRETTY_FUNCTION__;

    hide();
    update();
    Q_EMIT visibleChanged(false, reset);
}

void Keyboard::onKeyPressed(QString nativeScanCode, bool shift)
{
    qDebug() << __PRETTY_FUNCTION__;
    Qt::KeyboardModifiers modifiers = Qt::NoModifier;
    if (shift) modifiers |= Qt::ShiftModifier;

    bool ok;
    int keyCode = nativeScanCode.toInt(&ok) + 8;
    if (!ok) {
        qWarning() << "nativeScanCode convert fail: " << nativeScanCode;
        return;
    }

    Q_EMIT keyPressed(keyCode, modifiers);
}

void Keyboard::onSwitchContext()
{
    qDebug() << __PRETTY_FUNCTION__;

    Q_EMIT switchContext(Maliit::SwitchForward);
}

void Keyboard::onKeyReleased(Qt::Key keyCode, Qt::KeyboardModifiers modifiers, bool isReleased)
{
    qWarning() << __PRETTY_FUNCTION__;
    QScopedPointer<QKeyEvent> ev(new QKeyEvent(QEvent::KeyRelease, keyCode, modifiers));
    keyReleaseEvent(ev.data());
    Q_EMIT keyReleased(isReleased);
}

int Keyboard::contentType()
{
    qDebug() << __PRETTY_FUNCTION__;

    return m_im->contentType();
}

int Keyboard::enterKeyType()
{
    qDebug() << __PRETTY_FUNCTION__;

    return m_im->enterKeyType();
}

bool Keyboard::hiddenText()
{
    return m_im->hiddenText();
}

Keyboard::InputSource Keyboard::inputSource()
{
    qDebug() << __PRETTY_FUNCTION__;

    return m_inputSource;
}

void Keyboard::setInputSource(Keyboard::InputSource source)
{
    qDebug() << __PRETTY_FUNCTION__;

    if (source != m_inputSource) {
        m_inputSource = source;
        Q_EMIT inputSourceChanged(source);
    }
}

bool Keyboard::cursorVisible()
{
    qDebug() << __PRETTY_FUNCTION__;

    return m_ime->getCursorVisible();
}

void Keyboard::setTranslator(QString locale, bool speakLanguage)
{
    if (locale == translatorLangCode)
        return;

    translatorLangCode = locale;
    qApp->removeTranslator(translator.data());
    translator->load(QString("imemanager_") + locale, "/usr/share/qml/locales/imemanager", QString("_"));
    qApp->installTranslator(translator.data());
    Q_EMIT translatorChanged(speakLanguage);
}

void Keyboard::removeTranslator()
{
    translatorLangCode.clear();
    qApp->removeTranslator(translator.data());
}

QString Keyboard::emptyString()
{
    return "";
}

void Keyboard::onKeysymPressed(QString keysym)
{
    // convert to quint32 and signal
    bool ok = false;
    Q_EMIT keysymPressed(keysym.toInt(&ok, 16));
}

void Keyboard::setPanelHeight(int height)
{
    resize(m_winInfo->windowWidth(), height);
    update();
}

void Keyboard::resetPanelHeight()
{
    resize(m_winInfo->windowWidth(), m_winInfo->windowHeight());
    update();
}
