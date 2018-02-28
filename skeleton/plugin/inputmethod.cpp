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

SkullInputMethod::SkullInputMethod(MAbstractInputMethodHost *host)
    : MAbstractInputMethod(host)
{
    qDebug() << __PRETTY_FUNCTION__;
}

SkullInputMethod::~SkullInputMethod()
{
    qDebug() << __PRETTY_FUNCTION__;
}

void SkullInputMethod::show()
{
    qDebug() << __PRETTY_FUNCTION__;
    MAbstractInputMethod::show();
}

void SkullInputMethod::hide()
{
    qDebug() << __PRETTY_FUNCTION__;
    MAbstractInputMethod::hide();
}

QList<MAbstractInputMethod::MInputMethodSubView>
SkullInputMethod::subViews(Maliit::HandlerState state) const
{
    qDebug() << __PRETTY_FUNCTION__;
    return MAbstractInputMethod::subViews(state);
}

QString SkullInputMethod::activeSubView(Maliit::HandlerState state) const
{
    qDebug() << __PRETTY_FUNCTION__;
    return MAbstractInputMethod::activeSubView(state);
}

void SkullInputMethod::setState(const QSet<Maliit::HandlerState> &state)
{
    qDebug() << __PRETTY_FUNCTION__;
    MAbstractInputMethod::setState(state);
}

void SkullInputMethod::handleClientChange()
{
    qDebug() << __PRETTY_FUNCTION__;
    MAbstractInputMethod::handleClientChange();
}

void SkullInputMethod::handleVisualizationPriorityChange(bool inhibitShow)
{
    qDebug() << __PRETTY_FUNCTION__;
    MAbstractInputMethod::handleVisualizationPriorityChange(inhibitShow);
}

void SkullInputMethod::handleAppOrientationAboutToChange(int angle)
{
    qDebug() << __PRETTY_FUNCTION__;
    // Rotate your input method UI here
    Q_UNUSED(angle);
}

void SkullInputMethod::handleAppOrientationChanged(int angle)
{
    qDebug() << __PRETTY_FUNCTION__;
    // Can typically be forwarded to handleAppOrientationAboutToChange
    // as long as that method will not do anything when newAngle == previousAngle
    Q_UNUSED(angle);
}

void SkullInputMethod::update()
{
    qDebug() << __PRETTY_FUNCTION__;
    // empty default implementation
    MAbstractInputMethod::update();
}

void SkullInputMethod::reset()
{
    qDebug() << __PRETTY_FUNCTION__;
    // empty default implementation
    MAbstractInputMethod::reset();
}

void SkullInputMethod::handleFocusChange(bool focusIn)
{
    qDebug() << __PRETTY_FUNCTION__;

    MAbstractInputMethod::handleFocusChange(focusIn);
}

void SkullInputMethod::switchContext(Maliit::SwitchDirection direction,
                                          bool enableAnimation)
{
    qDebug() << __PRETTY_FUNCTION__;

    MAbstractInputMethod::switchContext(direction, enableAnimation);
}

void SkullInputMethod::setPreedit(const QString &preeditString, int cursorPos)
{
    qDebug() << __PRETTY_FUNCTION__;

    MAbstractInputMethod::setPreedit(preeditString, cursorPos);
}

void SkullInputMethod::setActiveSubView(const QString &subViewId, Maliit::HandlerState state)
{
    qDebug() << __PRETTY_FUNCTION__;

    // Ignored as input method only support one subview
    MAbstractInputMethod::setActiveSubView(subViewId, state);
}

bool SkullInputMethod::imExtensionEvent(MImExtensionEvent *event)
{
    qDebug() << __PRETTY_FUNCTION__;
    return MAbstractInputMethod::imExtensionEvent(event);
}

void SkullInputMethod::showLanguageNotification()
{
    qDebug() << __PRETTY_FUNCTION__;
    MAbstractInputMethod::showLanguageNotification();
}

void SkullInputMethod::processKeyEvent(QEvent::Type keyType, Qt::Key keyCode,
                             Qt::KeyboardModifiers modifiers, const QString &text,
                             bool autoRepeat, int count, quint32 nativeScanCode,
                             quint32 nativeModifiers, unsigned long time)
{
    qDebug() << __PRETTY_FUNCTION__;
    MAbstractInputMethod::processKeyEvent(keyType, keyCode, modifiers,
            text, autoRepeat, count, nativeScanCode, nativeModifiers, time);
}

void SkullInputMethod::setKeyOverrides(const QMap<QString, QSharedPointer<MKeyOverride> > &overrides)
{
    qDebug() << __PRETTY_FUNCTION__;
    MAbstractInputMethod::setKeyOverrides(overrides);
}

void SkullInputMethod::handleMouseClickOnPreedit(const QPoint &pos, const QRect &preeditRect)
{
    qDebug() << __PRETTY_FUNCTION__;
    MAbstractInputMethod::handleMouseClickOnPreedit(pos, preeditRect);
}
