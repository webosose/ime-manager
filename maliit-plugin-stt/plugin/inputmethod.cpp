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

#include <maliit/plugins/abstractinputmethodhost.h>
#include <QDebug>
QString STTLanguage;
STTInputMethod::STTInputMethod(MAbstractInputMethodHost *host)
    : MAbstractInputMethod(host)
    , m_stt(new STTView(host))
{
    qDebug() << __PRETTY_FUNCTION__;
    connect(m_stt.data(), SIGNAL (textKeyPressed(QString)),
            this, SLOT (onTextKeyPressed(QString)));

    connect(m_stt.data(), SIGNAL (backToKeyboardPressed()),
            this, SLOT (onBackToKeyboardPressed()));

    QVariantMap attributes;
    accessoryEnabled.reset(inputMethodHost()->registerPluginSetting("accessoryenabled", QT_TR_NOOP("system locale info"), Maliit::BoolType, attributes));
    systemLocale.reset(inputMethodHost()->registerPluginSetting("localeInfo", QT_TR_NOOP("system locale info"), Maliit::StringType, attributes));
    connect(systemLocale.data(), SIGNAL (valueChanged()), this, SLOT (onSystemLocaleChanged()));
    currentLanguage.reset(inputMethodHost()->registerPluginSetting("currentLanguage", QT_TR_NOOP("current IME language"), Maliit::StringType, attributes));
}

STTInputMethod::~STTInputMethod()
{
    qDebug() << __PRETTY_FUNCTION__;
}

void STTInputMethod::show()
{
    qWarning() << __PRETTY_FUNCTION__;

    m_stt->initialize();

    QJsonObject objLocaleInfo = QJsonObject::fromVariantMap(systemLocale->value().toMap());
    QJsonArray arKeyboards;
    // get the keyboard language array from keyboard settings
    static const QString LOCALEINFO_KEYBOARDS_KEY = "keyboards";
    qWarning() << "systemLocale->value().toMap() : " << systemLocale->value().toMap();
    QJsonObject::const_iterator it = objLocaleInfo.find(LOCALEINFO_KEYBOARDS_KEY);
    if (it == objLocaleInfo.end())
        qWarning() << "cannot find key in locale setting: " << "localeInfo/" << LOCALEINFO_KEYBOARDS_KEY;
    else
        arKeyboards = it.value().toArray();

    m_stt->setVkbLanguageList(arKeyboards);
    m_stt->show(STTLanguage);
}

void STTInputMethod::hide()
{
    qDebug() << __PRETTY_FUNCTION__;
    m_stt->hide();
    m_stt->removeTranslator();
}

QList<MAbstractInputMethod::MInputMethodSubView>
STTInputMethod::subViews(Maliit::HandlerState state) const
{
    qWarning() << __PRETTY_FUNCTION__;
    Q_UNUSED(state);

    MAbstractInputMethod::MInputMethodSubView subView;
    subView.subViewId = "stt";
    subView.subViewTitle = "stt";
    QList<MAbstractInputMethod::MInputMethodSubView> subViews;
    subViews << subView;
    return subViews;
}

QString STTInputMethod::activeSubView(Maliit::HandlerState state) const
{
    qWarning() << __PRETTY_FUNCTION__;
    Q_UNUSED(state);
    return QString("");
}

void STTInputMethod::setState(const QSet<Maliit::HandlerState> &state)
{
    qDebug() << __PRETTY_FUNCTION__;
    MAbstractInputMethod::setState(state);
}

void STTInputMethod::handleClientChange()
{
    qDebug() << __PRETTY_FUNCTION__;
    MAbstractInputMethod::handleClientChange();
}

void STTInputMethod::handleVisualizationPriorityChange(bool inhibitShow)
{
    qDebug() << __PRETTY_FUNCTION__;
    MAbstractInputMethod::handleVisualizationPriorityChange(inhibitShow);
}

void STTInputMethod::handleAppOrientationAboutToChange(int angle)
{
    qDebug() << __PRETTY_FUNCTION__;
    // Rotate your input method UI here
    Q_UNUSED(angle);
}

void STTInputMethod::handleAppOrientationChanged(int angle)
{
    qDebug() << __PRETTY_FUNCTION__;
    // Can typically be forwarded to handleAppOrientationAboutToChange
    // as long as that method will not do anything when newAngle == previousAngle
    Q_UNUSED(angle);
}

void STTInputMethod::update()
{
    qDebug() << __PRETTY_FUNCTION__;
    // empty default implementation
    MAbstractInputMethod::update();
}

void STTInputMethod::reset()
{
    qDebug() << __PRETTY_FUNCTION__;
    // empty default implementation
    MAbstractInputMethod::reset();
}

void STTInputMethod::handleFocusChange(bool focusIn)
{
    qDebug() << __PRETTY_FUNCTION__;

    MAbstractInputMethod::handleFocusChange(focusIn);
}

void STTInputMethod::switchContext(Maliit::SwitchDirection direction,
                                          bool enableAnimation)
{
    qDebug() << __PRETTY_FUNCTION__;

    MAbstractInputMethod::switchContext(direction, enableAnimation);
}

void STTInputMethod::setPreedit(const QString &preeditString, int cursorPos)
{
    qDebug() << __PRETTY_FUNCTION__;

    MAbstractInputMethod::setPreedit(preeditString, cursorPos);
}

void STTInputMethod::setActiveSubView(const QString &subViewId, Maliit::HandlerState state)
{
    qDebug() << __PRETTY_FUNCTION__;

    // Ignored as input method only support one subview
    MAbstractInputMethod::setActiveSubView(subViewId, state);
}

bool STTInputMethod::imExtensionEvent(MImExtensionEvent *event)
{
    qDebug() << __PRETTY_FUNCTION__;
    return MAbstractInputMethod::imExtensionEvent(event);
}

void STTInputMethod::showLanguageNotification()
{
    qDebug() << __PRETTY_FUNCTION__;
    MAbstractInputMethod::showLanguageNotification();
}

void STTInputMethod::processKeyEvent(QEvent::Type keyType, Qt::Key keyCode,
                             Qt::KeyboardModifiers modifiers, const QString &text,
                             bool autoRepeat, int count, quint32 nativeScanCode,
                             quint32 nativeModifiers, unsigned long time)
{
    qDebug() << __PRETTY_FUNCTION__;
    Q_UNUSED(keyCode);
    Q_UNUSED(text);
    Q_UNUSED(autoRepeat);
    Q_UNUSED(count);
    Q_UNUSED(nativeModifiers);
    Q_UNUSED(time);
    qDebug() << "keyType : " << keyType;
    if ( keyType == QEvent::KeyPress) {
        QScopedPointer<QKeyEvent> ev(new QKeyEvent(keyType, nativeScanCode, modifiers));
        qDebug() << "ev->key(): " << ev->key();
        if(ev->key() == 1206) // 1206 means Cursor on
            m_stt->sigCursorOn();
        else if(ev->key() == 1207) // 1207 means Curson out
            m_stt->sigCursorOff();
    }
    else if ( keyType == QEvent::KeyRelease ){
        QScopedPointer<QKeyEvent> ev(new QKeyEvent(keyType, nativeScanCode, modifiers));
        qDebug() << "ev->key(): " << ev->key();
        m_stt->keyReleased(ev.data());
    }
}

void STTInputMethod::onSystemLocaleChanged()
{
    QJsonObject objLocaleInfo = QJsonObject::fromVariantMap(systemLocale->value().toMap());
    QJsonValue value = objLocaleInfo.value(QString("locales"));

    QJsonObject subObject = value.toObject();
    QJsonValue subValue = subObject.value(QString("STT"));

    STTLanguage = subValue.toString();
    qDebug() << "STT Plug-In language:" << STTLanguage;
}

void STTInputMethod::setKeyOverrides(const QMap<QString, QSharedPointer<MKeyOverride> > &overrides)
{
    qDebug() << __PRETTY_FUNCTION__;
    MAbstractInputMethod::setKeyOverrides(overrides);
}

void STTInputMethod::handleMouseClickOnPreedit(const QPoint &pos, const QRect &preeditRect)
{
    qDebug() << __PRETTY_FUNCTION__;
    MAbstractInputMethod::handleMouseClickOnPreedit(pos, preeditRect);
}

void STTInputMethod::backToKeyboard()
{
    accessoryEnabled->set(false);
    reset();
}

void STTInputMethod::onBackToKeyboardPressed()
{
    backToKeyboard();
}

void STTInputMethod::onTextKeyPressed(QString text)
{
    if (0 == text.length())
        return;

    inputMethodHost()->sendCommitString(text);

    backToKeyboard();
}
