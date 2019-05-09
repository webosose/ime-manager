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

#include "keyboard.h"
#include "suggestion.h"
#include "strokecomponent.h"
#include "languages.h"

#include <maliit/plugins/abstractinputmethodhost.h>
#include "maliitenums.h"

//#IF_COMMERCIAL
static QHash<QString, QString> s_languageHash;
//#ELSE
//#END

Keyboard::Keyboard(MAbstractInputMethodHost* host, Suggestion* suggestion, StrokeComponent* strokeComponent)
    : QQuickView()
    , m_host(host)
    , m_ime(WebOSPlatform::instance()->inputManager())
    , m_winInfo(new WindowInformation)
    , m_inputSource(InputSourceNone)
    , translator(new QTranslator(this))
    , m_contentType(Maliit::FreeTextContentType)
    , m_enterKeyType(Maliit::DefaultEnterKeyType)
    , m_hiddenText(false)
{
    // register enums and objects before loading qml
    qmlRegisterUncreatableType<MaliitEnums>("com.meego.maliit", 1, 0,
            "Maliit", "This is the class used to export Maliit Enums");

    QQmlContext *rootCtx = rootContext();
    rootCtx->setContextProperty("Keyboard", this);
    rootCtx->setContextProperty("PluginProxy", this);
    rootCtx->setContextProperty("Suggestion", suggestion);
    rootCtx->setContextProperty("StrokeComponent", strokeComponent);
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
    m_shifted = false;

    QString mainPath = QString("%1%2").arg(IMEMANAGER_RESOURCE_PATH).arg("/qml/view-chinese/main.qml");
    setSource(mainPath);

    QQuickItem *rootObj = rootObject();
    QObject::connect(rootObj, SIGNAL (keyPressed(QString, bool)),
            this, SLOT(onKeyPressed(QString, bool)));

    QObject::connect(rootObj, SIGNAL (switchContext()),
            this, SLOT(onSwitchContext()));

    QObject::connect(rootObj, SIGNAL (clearAllPressed()),
            this, SIGNAL(clearAllPressed()));

    QObject::connect(rootObj, SIGNAL (shiftPressed(QString)),
            this, SLOT(onShiftPressed(QString)));

    QObject::connect(rootObj, SIGNAL (symbolPressed(QString)),
            this, SIGNAL(symbolKeyPressed(QString)));

    QObject::connect(rootObj, SIGNAL (textKeyPressed(QString)),
            this, SIGNAL(textKeyPressed(QString)));

    QObject::connect(rootObj, SIGNAL (showRequested(bool)),
            this, SLOT(onShowRequested(bool)));

    QObject::connect(rootObj, SIGNAL (hideRequested(bool)),
            this, SLOT(onHideRequested(bool)));

    QObject::connect(rootObj, SIGNAL (keyReleased(bool)),
            this, SLOT(onKeyReleased(bool)));

    QObject::connect(rootObj, SIGNAL (moveCursorPosition(int)),
            this, SIGNAL(moveCursorPosition(int)));

    //#IF_COMMERCIAL
    initializeHashTable();
    //#ELSE
    //#END

    m_host->registerWindow(this, Maliit::PositionCenterBottom);

    QObject::connect(m_ime, SIGNAL(cursorVisibleChanged(bool)), this, SIGNAL(cursorVisibleChanged(bool)));
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
    Q_EMIT visibleChanged(true, reset);
}

void Keyboard::onHideRequested(bool reset)
{
    qDebug() << __PRETTY_FUNCTION__;

    hide();
    Q_EMIT visibleChanged(false, reset);
}

void Keyboard::onKeyPressed(QString nativeScanCode, bool shift)
{
    qDebug() << __PRETTY_FUNCTION__;

    Qt::KeyboardModifiers modifiers = Qt::NoModifier;
    if (shift) modifiers |= Qt::ShiftModifier;

    bool ok;
    int keyCode = nativeScanCode.toInt(&ok,16);
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
    qDebug() << __PRETTY_FUNCTION__;
    QScopedPointer<QKeyEvent> ev(new QKeyEvent(QEvent::KeyRelease, keyCode, modifiers));
    keyReleaseEvent(ev.data());
    Q_EMIT keyReleased(isReleased);
}

Keyboard::InputSource Keyboard::inputSource()
{
    qDebug() << __PRETTY_FUNCTION__;

    return m_inputSource;
}

void Keyboard::setInputSource(Keyboard::InputSource source)
{
    qDebug() << __PRETTY_FUNCTION__;

    m_inputSource = source;
    Q_EMIT inputSourceChanged(source);
}

bool Keyboard::cursorVisible()
{
    qDebug() << __PRETTY_FUNCTION__;

    return m_ime->getCursorVisible();
}

void Keyboard::setPanelHeight(int height)
{
    qDebug() << __PRETTY_FUNCTION__;

    resize(m_winInfo->windowWidth(), height);
}

void Keyboard::resetPanelHeight()
{
    qDebug() << __PRETTY_FUNCTION__;

    resize(m_winInfo->windowWidth(), m_winInfo->windowHeight());
}

void Keyboard::onShiftPressed(QString state)
{
    qDebug() << __PRETTY_FUNCTION__;

    setShift(SHIFTED == state);
}

void Keyboard::setShift(bool shift)
{
    qDebug() << __PRETTY_FUNCTION__;

    m_shifted = shift;
    Q_EMIT shiftKeyPressed();
    Q_EMIT shiftLabelChanged();
}

void Keyboard::setLanguage(QString language, QVariant data)
{
    qDebug() << __PRETTY_FUNCTION__;

    m_language = language;
    Q_EMIT languageChanged(language,data);
    Q_EMIT languageLabelChanged();
    Q_EMIT shiftLabelChanged();
}

void Keyboard::setTranslator()
{
    qDebug() << __PRETTY_FUNCTION__;

    removeTranslator();
    QString langCode = (m_language == LanguageConstants::SIMPLIFIED_CHINESE)
                       ? "zh_Hans_CN" : "zh_Hant_TW";
    translator->load(QString("imemanager_") + langCode, "/usr/share/qml/locales/imemanager", "_");
    qApp->installTranslator(translator.data());
    Q_EMIT translatorChanged();
}

void Keyboard::removeTranslator()
{
    qDebug() << __PRETTY_FUNCTION__;

    qApp->removeTranslator(translator.data());
}

QString Keyboard::emptyString()
{
    return "";
}

QString Keyboard::getLanguageLabel()
{
    qDebug() << __PRETTY_FUNCTION__;

    return m_language != LanguageConstants::SIMPLIFIED_CHINESE
            ? LanguageConstants::TRADITIONAL_CHINESE
            : LanguageConstants::SIMPLIFIED_CHINESE;
}

QString Keyboard::getShiftLabel()
{
    qDebug() << __PRETTY_FUNCTION__;

    if (!isShifted()) {
        if (m_language == LanguageConstants::SIMPLIFIED_CHINESE)
            return LanguageConstants::PINYIN;
        if (m_language == LanguageConstants::TRADITIONAL_CHINESE)
            return LanguageConstants::CANGJIE;
        return LanguageConstants::ZHUYIN;
    } else {
        if (m_language == LanguageConstants::SIMPLIFIED_CHINESE)
            return LanguageConstants::STROKE;
        if (m_language == LanguageConstants::TRADITIONAL_CHINESE)
            return LanguageConstants::ZHUYIN;
        return LanguageConstants::CANGJIE;
    }
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

void Keyboard::setEnterKeyType(int enterKeyType)
{
    qDebug() << __PRETTY_FUNCTION__;

    m_enterKeyType = enterKeyType;
    Q_EMIT enterKeyTypeChanged(enterKeyType);
}


void Keyboard::setContentType(int contentType)
{
    qDebug() << __PRETTY_FUNCTION__;

    m_contentType = contentType;
    Q_EMIT contentTypeChanged(contentType);
}

bool Keyboard::isHiddenText()
{
    qDebug() << __PRETTY_FUNCTION__;

    return m_hiddenText;
}

void Keyboard::setHiddenText(bool hidenText)
{
    qDebug() << __PRETTY_FUNCTION__;

    m_hiddenText = hidenText;
    Q_EMIT hiddenTextChanged(hidenText);
}

void Keyboard::setNumKeyEnterLabel(QString language)
{
    qDebug() << __PRETTY_FUNCTION__;
//#IF_COMMERCIAL
    m_numKeyEnter = s_languageHash.contains(language) ? s_languageHash.value(language) : "Enter";
//#ELSE
/*
    m_numKeyEnter = language.startsWith("zh-Hant") ? "輸入" : (language.startsWith("zh-Hans") ? "输入" : "Enter");
*/
//#END
    Q_EMIT numKeyEnterLabelChanged();
}

bool Keyboard::isNumberMode()
{
    return m_inputSource == Keyboard::InputSourceVirtual && (m_contentType == Maliit::NumberContentType || m_contentType == Maliit::PhoneNumberContentType);
}

//#IF_COMMERCIAL
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

int Keyboard::instanceId()
{
    qDebug() << __PRETTY_FUNCTION__;
    return m_host->instanceId();
}

QString Keyboard::maliitServiceId()
{
    qDebug() << __PRETTY_FUNCTION__;

    return m_host->serviceName();
}
