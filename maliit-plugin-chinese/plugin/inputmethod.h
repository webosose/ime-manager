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

#ifndef CHINESE_INPUT_METHOD_H
#define CHINESE_INPUT_METHOD_H

#include <maliit/plugins/abstractinputmethod.h>
#include <maliit/plugins/abstractpluginsetting.h>

#include <QSet>
#include <QList>

#include "automata.h"
#include "keyboard.h"
#include "suggestion.h"
#include "strokecomponent.h"
#include "layoutloader.h"

class ChineseInputMethodPrivate;

class ChineseInputMethod
    : public MAbstractInputMethod
{
    Q_OBJECT

public:
    ChineseInputMethod(MAbstractInputMethodHost *host);
    ~ChineseInputMethod();

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
    virtual void update();
    virtual void reset();
    virtual void switchContext(Maliit::SwitchDirection direction, bool enableAnimation);
    virtual void handleFocusChange(bool focusIn);
    virtual void setPreedit(const QString &preeditString);
    virtual bool imExtensionEvent(MImExtensionEvent *event);
    virtual void showLanguageNotification();
    virtual void processKeyEvent(QEvent::Type keyType, Qt::Key keyCode,
                                 Qt::KeyboardModifiers modifiers, const QString &text,
                                 bool autoRepeat, int count, quint32 nativeScanCode,
                                 quint32 nativeModifiers, unsigned long time);
    bool processHidKeyEvent(QEvent::Type keyType, Qt::Key keyCode,
                            Qt::KeyboardModifiers modifiers, const QString &text,
                            bool autoRepeat, int count, quint32 nativeScanCode,
                            quint32 nativeModifiers, unsigned long time);
    virtual void setKeyOverrides(const QMap<QString, QSharedPointer<MKeyOverride> > &overrides);
    virtual void handleMouseClickOnPreedit(const QPoint &pos, const QRect &preeditRect);

    bool hasEnabledLanguages();
    bool handleCommitString(Qt::Key keyCode);
    void clear();

Q_SIGNALS:
    void showRequested(bool reset);

private:
    Q_DECLARE_PRIVATE(ChineseInputMethod)
    const QScopedPointer<ChineseInputMethodPrivate> d_ptr;

private Q_SLOTS:
    void onSuggestionSelected(int index);
    void onStrokeComponentSelected(int index);
    void onVirtualKeyPressed(quint32, Qt::KeyboardModifiers, int);
    void onNextSuggestions();
    void onPreviousSuggestions();
    void onSwitchContext(Maliit::SwitchDirection);
    void onVisibleChanged(bool visible, bool reset);
    void onSystemLocaleChanged();
    void onShiftKeyPressed();
    void onSymbolKeyPressed(QString);
    void onTextKeyPressed(QString);
    void onPreeditCommit(QString);
    void releaseKeyLock();
    void onClearAllPressed();
    void onToggleModeButton();
    void onMoveCursorPosition(int direction, int eventType);

protected:
    QScopedPointer<Maliit::Plugins::AbstractPluginSetting> systemLocale;
    QScopedPointer<Maliit::Plugins::AbstractPluginSetting> currentCountry;

    QStringList enabledLanguages;
    int currentLanguageIndex;
    QList<LayoutLoader> enabledLayouts;

    QScopedPointer<Automata> m_automata;
    QScopedPointer<Suggestion> m_suggestion;
    QScopedPointer<StrokeComponent> m_strokeComponent;
    QScopedPointer<Keyboard> m_keyboard;
    bool m_sendEnterKey;
    int dirCursorMoveKey;
    quint32 pressedScancode;

private:
    /*IF_COMMERCIAL*/
    bool isNumberOrEnterKey(Qt::Key keycode);
    /*ELSE*/
    /*END*/
    bool isNumKeyWithNumberKeyboard(Qt::Key keyCode);
    bool processKeyEventCommon(Qt::Key keyCode, Qt::KeyboardModifiers);
    bool processRemoteKeyEvent(Qt::Key keyCode, quint32 nativeScanCode, Qt::KeyboardModifiers modifiers);
    bool checkBypassKey(quint32 nativeScanCode);
    void insertLanguage(QString language);
    void removeLanguage(QString language);
    void doMoveCursorPosition(int direction);

    bool m_bNumberKey;
    quint32 m_keySym;
};
#endif // CHINESE_INPUT_METHOD_H
