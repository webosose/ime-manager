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

#ifndef INPUT_METHOD_H
#define INPUT_METHOD_H

#include <maliit/plugins/abstractinputmethod.h>
#include <maliit/plugins/abstractpluginsetting.h>

#include <QSet>

#include "keyboard.h"
#include "prediction.h"
#include "../openautomata/openwnnautomata.h"

class JapaneseInputMethodPrivate;

class JapaneseInputMethod
    : public MAbstractInputMethod
{
    Q_OBJECT

    Q_PROPERTY(bool hiddenText READ hiddenText NOTIFY hiddenTextChanged)

public:
    JapaneseInputMethod(MAbstractInputMethodHost *host);
    ~JapaneseInputMethod();

    //! \reimp
    /* Mandatory */
    virtual void show();
    virtual void hide();
    virtual void handleVisualizationPriorityChange(bool priority);
    virtual void handleClientChange();
    virtual void handleAppOrientationAboutToChange(int angle);
    virtual void handleAppOrientationChanged(int angle);
    virtual QList<MInputMethodSubView> subViews(Maliit::HandlerState state
                                                = Maliit::OnScreen) const;
    virtual void setActiveSubView(const QString &subViewId,
                                  Maliit::HandlerState state = Maliit::OnScreen);
    virtual QString activeSubView(Maliit::HandlerState state = Maliit::OnScreen) const;
    virtual void setState(const QSet<Maliit::HandlerState> &state);

    /* Optional, often used */
    virtual void update();
    virtual void reset();
    virtual void switchContext(Maliit::SwitchDirection direction, bool enableAnimation);
    virtual void handleFocusChange(bool focusIn);
    virtual void setPreedit(const QString &preeditString, int cursorPos);

    /* Optional, rarely used */
    virtual bool imExtensionEvent(MImExtensionEvent *event);
    virtual void showLanguageNotification();
    virtual void processKeyEvent(QEvent::Type keyType, Qt::Key keyCode,
                                 Qt::KeyboardModifiers modifiers, const QString &text,
                                 bool autoRepeat, int count, quint32 nativeScanCode,
                                 quint32 nativeModifiers, unsigned long time);
    virtual void setKeyOverrides(const QMap<QString, QSharedPointer<MKeyOverride> > &overrides);
    virtual void handleMouseClickOnPreedit(const QPoint &pos, const QRect &preeditRect);
    //! \reimp_end
    bool hiddenText();
    void clear();

public:
    bool isKanjiConvert() const { return m_isConvert; }
    void setHidModeFromHid(int hidMode);
    bool hasEnabledLanguages();

Q_SIGNALS:
    void hiddenTextChanged(bool isHidden);
    void showRequested(bool reset);

private:
    Q_DECLARE_PRIVATE(JapaneseInputMethod)

    const QScopedPointer<JapaneseInputMethodPrivate> d_ptr;

private Q_SLOTS:
    void onPredictionSelected(int index);
    void onVirtualKeyPressed(quint32 nativeScanCode, Qt::KeyboardModifiers, int eventType);
    void onSwitchContext(Maliit::SwitchDirection);
    void onActivateSTT();
    void onClearAllPressed();
    void onVisibleChanged(bool isVisible);
    void onSystemLocaleChanged();
    void onSetHidModeFromVkb(int hidMode);
    void onTextKeyPressed(QString text);
    void releaseKeyLock();
    void onSwitchSymbolMode(bool isSymbol);
    void onMoveCursorPosition(int direction, int eventType);
    void onVkbModeChanged(int mode);

protected:
    bool m_hiddenText;
    bool m_isSymbol;

private:
    bool processKeyEventCommon(Qt::Key keyCode, quint32 nativeScanCode, Qt::KeyboardModifiers, bool isCaps=false);
    bool processRemoteKeyEvent(Qt::Key keyCode, quint32 nativeScanCode, Qt::KeyboardModifiers modifiers);
    bool processHidKeyEvent(QEvent::Type keyType, Qt::Key keyCode,
                            Qt::KeyboardModifiers modifiers, const QString &text,
                            bool autoRepeat, int count, quint32 nativeScanCode,
                            quint32 nativeModifiers, unsigned long time);
    void doMoveCursorPosition(int direction);
    void commitPreedit();

private:
    QScopedPointer<OpenWnnAutomata> m_automata;
    int m_candIndex;
    bool m_isConvert;

    QScopedPointer<Maliit::Plugins::AbstractPluginSetting> m_systemLocale;
    QScopedPointer<Maliit::Plugins::AbstractPluginSetting> enableStt;
    bool m_isJapaneseEnabled;
    bool m_isActive;
    bool m_bNumberKey;
    bool m_bHoldSource;
    quint32 m_keySym;

    QScopedPointer<Prediction> m_prediction;
    QScopedPointer<Keyboard> m_keyboard;

    //! \reimp_end
};

#endif // INPUT_METHOD_H

