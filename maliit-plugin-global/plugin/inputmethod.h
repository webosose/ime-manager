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

#ifndef GLOBAL_INPUT_METHOD_H
#define GLOBAL_INPUT_METHOD_H

#include <maliit/plugins/abstractinputmethod.h>
#include <maliit/plugins/abstractpluginsetting.h>

#include <QSet>
#include <QList>

#include "automata.h"
#include "keyboard.h"
#include "prediction.h"
#include "layoutloader.h"

class GlobalInputMethodPrivate;

class GlobalInputMethod
    : public MAbstractInputMethod
{
    Q_OBJECT

    Q_PROPERTY(int contentType READ contentType NOTIFY contentTypeChanged)
    Q_PROPERTY(int enterKeyType READ enterKeyType NOTIFY enterKeyTypeChanged)
    Q_PROPERTY(bool hiddenText READ hiddenText NOTIFY hiddenTextChanged)

    Q_PROPERTY(QString surroundingText READ surroundingText NOTIFY surroundingTextChanged)
    Q_PROPERTY(int cursorPosition READ cursorPosition NOTIFY cursorPositionChanged)

public:
    GlobalInputMethod(MAbstractInputMethodHost *host);
    ~GlobalInputMethod();

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

    int contentType();
    int enterKeyType();
    bool hiddenText();
    void clear();

    QString surroundingText();
    int cursorPosition();

Q_SIGNALS:
    void contentTypeChanged(int contentType);
    void enterKeyTypeChanged(int enterKeyType);
    void hiddenTextChanged(bool isHidden);
    void surroundingTextChanged();
    void cursorPositionChanged();
    void languageCountChanged(int languageCount);
    void showRequested(bool reset);
//#IF_COMMERCIAL
    void setDefaultFocus();
//#ELSE
//#END

private:
    Q_DISABLE_COPY(GlobalInputMethod)
    Q_DECLARE_PRIVATE(GlobalInputMethod)

    const QScopedPointer<GlobalInputMethodPrivate> d_ptr;

private Q_SLOTS:
    void onPredictionSelected(QString selectedString, bool replace);
    void onVirtualKeyPressed(quint32 nativeScanCode, Qt::KeyboardModifiers, int eventType);
    void onClearAllPressed();
    void onTextKeyPressed(QString text);
    void onVisibleChanged(bool visible, bool reset);
    void onSystemLocaleChanged();
    void onCountryChanged();
    void onKeysymPressed(quint32 keysym, int eventType);
    void releaseKeyLock();
    void onSurroundingTextChanged();
    void onCursorPositionChanged();
    void onContentTypeChanged(int contentType);
    void onEnterKeyTypeChanged(int enterKeyType);
    void onDelayPredictionUpdate();
    void onDelaySwitchingLanguage();
    void onMoveCursorPosition(int direction, int eventType);
    void onSwitchContext(Maliit::SwitchDirection direction);

protected:
    int m_contentType;
    int m_enterKeyType;
    bool m_hiddenText;
    bool m_stopHidCharInput;

    QScopedPointer<Maliit::Plugins::AbstractPluginSetting> systemLocale;
    QScopedPointer<Maliit::Plugins::AbstractPluginSetting> currentLanguage;
    QScopedPointer<Maliit::Plugins::AbstractPluginSetting> defaultLanguage;
    QScopedPointer<Maliit::Plugins::AbstractPluginSetting> currentCountry;

    QStringList enabledLanguages;
    int currentLanguageIndex;
    QList<LayoutLoader> enabledLayouts;

    QScopedPointer<Automata> m_automata;
    QScopedPointer<Prediction> m_prediction;
    QScopedPointer<Keyboard> m_keyboard;

private:
    bool processKeyEventCommon(Qt::Key keyCode, quint32 nativeScanCode, Qt::KeyboardModifiers, QString text = "");
    bool processRemoteKeyEvent(Qt::Key keyCode, quint32 nativeScanCode, Qt::KeyboardModifiers modifiers);
    bool processHidKeyEvent(QEvent::Type keyType, Qt::Key keyCode,
                            Qt::KeyboardModifiers modifiers, const QString &text,
                            bool autoRepeat, int count, quint32 nativeScanCode,
                            quint32 nativeModifiers, unsigned long time);
    void insertLanguage(QString language);
    void removeLanguage(QString language);
    QString getMenuLanguageString(QLocale locale, QString langCode = "");
    void updatePredictionList();
    void appendPredictionSeed();
    void updateTranslator();
    void updateTranslator(bool speakLanguage);
    void doMoveCursorPosition(int direction);
    bool m_wasLocaleSetup;
};

#endif // GLOBAL_INPUT_METHOD_H
