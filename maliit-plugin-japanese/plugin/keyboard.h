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

#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <maliit/plugins/abstractinputmethod.h>

#include <QtQuick>
#include <QTranslator>
#include "windowinformation.h"
#include <webosplatform.h>
#include <webosinputmanager.h>
#include <QObject>

class Prediction;
class JapaneseInputMethod;

class Keyboard : public QQuickView
{
    Q_OBJECT

    Q_ENUMS(InputSource)

    Q_PROPERTY(int contentType READ getContentType NOTIFY contentTypeChanged)
    Q_PROPERTY(int enterKeyType READ getEnterKeyType NOTIFY enterKeyTypeChanged)
    Q_PROPERTY(int hiddenText READ hiddenText NOTIFY hiddenTextChanged)
    Q_PROPERTY(int inputSource READ inputSource NOTIFY inputSourceChanged)
    Q_PROPERTY(int hidMode READ hidMode NOTIFY hidModeChanged)
    Q_PROPERTY(QString emptyString READ emptyString NOTIFY translatorChanged)
    Q_PROPERTY(bool unfixedStatus READ isUnfixedStatus  NOTIFY unfixedStatusChanged)
//#IF_COMMERCIAL
    Q_PROPERTY(QString numKeyEnterLabel READ getNumKeyEnterLabel NOTIFY numKeyEnterLabelChanged)
//#ELSE
//#END
    Q_PROPERTY(bool isReleased NOTIFY keyReleased)
    Q_PROPERTY(bool cursorVisible READ cursorVisible NOTIFY cursorVisibleChanged)
    Q_PROPERTY(QString maliitServiceId READ maliitServiceId CONSTANT)


public:
    enum InputSource {
        InputSourceHardware,
        InputSourceVirtual,
        InputSourceNone
    };
    enum VkbMode {
        VkbModeHiragana,
        VkbModeKatakana,
        VkbModeEnglish,
        VkbModeSymbol
    };

    Keyboard(JapaneseInputMethod* im, Prediction* prediction);
    virtual ~Keyboard() {}

    int getContentType();
    int getEnterKeyType();
    void setContentType(int contentType);
    void setEnterKeyType(int enterKeyType);
    void setHiddenText(bool isHidden);
//#IF_COMMERCIAL
    void setNumKeyEnterLabel(QString language);
    QString getNumKeyEnterLabel() { return m_numKeyEnter;}
//#ELSE
//#END
    bool hiddenText();
    InputSource inputSource();
    void setInputSource(InputSource source);
    bool cursorVisible();
    VkbMode vkbMode() const;
    int hidMode();
    void setHidModeFromHid(int hidMode);
    QString emptyString();
    bool hidKeyPressEvent(Qt::Key keyCode, Qt::KeyboardModifiers modifiers);
    void setTranslator(QString langCode);
    void removeTranslator();
    bool isUnfixedStatus();
    void setUnfixedStatus(bool unfixedStatus);
    void onKeyReleased(Qt::Key keyCode, Qt::KeyboardModifiers modifiers, bool isReleased);
    int instanceId();
    QString maliitServiceId();

    Q_INVOKABLE void setPanelHeight(int height);
    Q_INVOKABLE void resetPanelHeight();

Q_SIGNALS:
    void inputSourceChanged(InputSource source);
    void keyPressed(quint32 nativeScanCode, Qt::KeyboardModifiers, int eventType);
    void switchContext(Maliit::SwitchDirection direction);
    void languageChanged();
    void clearAllPressed();
    void activateSTT();
    void hidModeChanged(int hidMode);
    void setHidModeFromVkb(int hidMode);
    void visibleChanged(bool visible, bool reset);
//#IF_COMMERCIAL
    void numKeyEnterLabelChanged();
//#ELSE
//#END
    void translatorChanged();
    void unfixedStatusChanged(bool unfixedStatus);
    void contentTypeChanged(int contentType);
    void enterKeyTypeChanged(int enterKeyType);
    void hiddenTextChanged(bool hidden);
    void textKeyPressed(QString text);
    void forceFocusTo(QString label);
    void switchSymbolMode(bool isSymbol);
    void keyReleased(bool isReleased);
    void cursorVisibleChanged(bool cursorVisible);
    void moveCursorPosition(int direction, int eventType);
    void vkbModeChanged(int mode);

public Q_SLOTS:
    void onKeyPressed(QString nativeScanCode, bool shift, int eventType);
    void onSwitchContext();
    void onClickInputCharacterChangeButton(QString vkbMode);
    void onShowRequested(bool reset);
    void onHideRequested(bool reset);
    void onSwitchSymbolMode(bool isSymbol);

//#IF_COMMERCIAL
protected:
    void initializeHashTable();
//#ELSE
//#END

private:
    JapaneseInputMethod* m_im;
    WebOSInputManager* m_ime;
    InputSource m_inputSource;
    WindowInformation m_winInfo;
    VkbMode m_vkbMode;
//#IF_COMMERCIAL
    QString m_numKeyEnter;
//#ELSE
//#END
    int m_hidMode;
    bool m_unfixedStatus;
    QScopedPointer<QTranslator> translator;
    int m_contentType;
    int m_enterKeyType;
    bool m_hiddenText;
};

#endif //KEYBOARD_H
