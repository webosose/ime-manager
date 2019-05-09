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

#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <maliit/plugins/abstractinputmethod.h>

#include <QtQuick>
#include <QTranslator>
#include "windowinformation.h"
#include <webosplatform.h>
#include <webosinputmanager.h>
#include <qpa/qplatformnativeinterface.h>
#include <QObject>

class Suggestion;
class StrokeComponent;

static const QString SHIFTED = "Normal-Shift";

class Keyboard : public QQuickView
{
    Q_OBJECT

    Q_ENUMS(InputSource)

    Q_PROPERTY(int contentType READ getContentType NOTIFY contentTypeChanged)
    Q_PROPERTY(int enterKeyType READ getEnterKeyType NOTIFY enterKeyTypeChanged)
    Q_PROPERTY(int hiddenText READ isHiddenText NOTIFY hiddenTextChanged)
    Q_PROPERTY(int inputSource READ inputSource NOTIFY inputSourceChanged)
    Q_PROPERTY(bool shifted READ isShifted NOTIFY shiftKeyPressed)
    Q_PROPERTY(QString languageLabel READ getLanguageLabel NOTIFY languageLabelChanged)
    Q_PROPERTY(QString shiftLabel READ getShiftLabel NOTIFY shiftLabelChanged)
    Q_PROPERTY(QString emptyString READ emptyString NOTIFY translatorChanged)
    Q_PROPERTY(QString numKeyEnterLabel READ getNumKeyEnterLabel NOTIFY numKeyEnterLabelChanged)
    Q_PROPERTY(bool isReleased NOTIFY keyReleased)
    Q_PROPERTY(bool cursorVisible READ cursorVisible NOTIFY cursorVisibleChanged)
    Q_PROPERTY(QString maliitServiceId READ maliitServiceId CONSTANT)


public:
    enum InputSource {
        InputSourceHardware,
        InputSourceVirtual,
        InputSourceNone
    };

    Keyboard(MAbstractInputMethodHost* host, Suggestion* suggestion, StrokeComponent* strokeComponent);

    int getContentType();
    int getEnterKeyType();
    bool isHiddenText();
    InputSource inputSource();
    void setInputSource(InputSource source);
    bool cursorVisible();
    bool hidKeyPressEvent(Qt::Key keyCode, Qt::KeyboardModifiers modifiers);
    bool isShifted() {return m_shifted;}
    bool isNumberMode();
    void setShift(bool shift);
    void setLanguage(QString language, QVariant data);
    void setTranslator();
    void setContentType(int contentType);
    void setEnterKeyType(int enterKeyType);
    void setHiddenText(bool hidenText);
    void removeTranslator();
    void setNumKeyEnterLabel(QString language);
    void onKeyReleased(Qt::Key keyCode, Qt::KeyboardModifiers modifiers, bool isReleased);
    QString getNumKeyEnterLabel() { return m_numKeyEnter;}
    QString getLanguageLabel();
    QString getShiftLabel();
    QString emptyString();
    int instanceId();
    QString maliitServiceId();

    Q_INVOKABLE void setPanelHeight(int height);
    Q_INVOKABLE void resetPanelHeight();

Q_SIGNALS:
    void inputSourceChanged(InputSource source);
    void keyPressed(quint32 nativeScanCode, Qt::KeyboardModifiers);
    void shiftKeyPressed();
    void symbolKeyPressed(QString state);
    void switchContext(Maliit::SwitchDirection direction);
    void clearAllPressed();
    void textKeyPressed(QString text);
    void languageChanged(QString language, QVariant data);
    void visibleChanged(bool visible,bool reset);
    void languageLabelChanged();
    void shiftLabelChanged();
    void translatorChanged();
    void contentTypeChanged(int contentType);
    void enterKeyTypeChanged(int enterKeyType);
    void numKeyEnterLabelChanged();
    void hiddenTextChanged(bool isHidden);
    void forceFocusTo(QString label);
    void keyReleased(bool isReleased);
    void cursorVisibleChanged(bool cursorVisible);
    void moveCursorPosition(int);

public Q_SLOTS:
    void onKeyPressed(QString nativeScanCode, bool shift);
    void onSwitchContext();
    void onShowRequested(bool reset);
    void onHideRequested(bool reset);
    void onShiftPressed(QString state);

//#IF_COMMERCIAL
protected:
    void initializeHashTable();
//#ELSE
//#END

private:
    MAbstractInputMethodHost* m_host;
    WebOSInputManager* m_ime;
    QScopedPointer<WindowInformation> m_winInfo;
    InputSource m_inputSource;
    bool m_shifted;
    QString m_language;
    QString m_numKeyEnter;
    QScopedPointer<QTranslator> translator;
    int m_contentType;
    int m_enterKeyType;
    bool m_hiddenText;
};

#endif //KEYBOARD_H
