// Copyright (c) 2013-2019 LG Electronics, Inc.
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
class GlobalInputMethod;

class Keyboard : public QQuickView
{
    Q_OBJECT

    Q_ENUMS(InputSource)

    Q_PROPERTY(int contentType READ contentType NOTIFY contentTypeChanged)
    Q_PROPERTY(int enterKeyType READ enterKeyType NOTIFY enterKeyTypeChanged)
    Q_PROPERTY(int hiddenText READ hiddenText NOTIFY hiddenTextChanged)
    Q_PROPERTY(int inputSource READ inputSource NOTIFY inputSourceChanged)
    Q_PROPERTY(QString emptyString READ emptyString NOTIFY translatorChanged)
    Q_PROPERTY(QString translatorLocale READ translatorLocale)
    Q_PROPERTY(bool isReleased NOTIFY keyReleased)
    Q_PROPERTY(bool cursorVisible READ cursorVisible NOTIFY cursorVisibleChanged)
    Q_PROPERTY(QString maliitServiceId READ maliitServiceId CONSTANT)


public:
    enum InputSource {
        InputSourceHardware,
        InputSourceVirtual,
        InputSourceNone
    };

    Keyboard(GlobalInputMethod* im, Prediction* prediction);
    virtual ~Keyboard() {}

    int contentType();
    int enterKeyType();
    bool hiddenText();
    InputSource inputSource();
    void setInputSource(InputSource source);
    bool isPointerVisible();
    bool cursorVisible();
    QString emptyString();
    QString translatorLocale() {return translatorLangCode;}
    bool hidKeyPressEvent(Qt::Key keyCode, Qt::KeyboardModifiers modifiers);
    void setTranslator(QString locale, bool speakLanguage);
    void removeTranslator();
    void load();
    void onKeyReleased(Qt::Key keyCode, Qt::KeyboardModifiers modifiers, bool isReleased);
    int instanceId();
    QString maliitServiceId();

    Q_INVOKABLE void setPanelHeight(int height);
    Q_INVOKABLE void resetPanelHeight();

Q_SIGNALS:
    void contentTypeChanged(int type); // FIXME type should be MaliitEnums::ContentType type
    void enterKeyTypeChanged(int enterKeyType); // FIXME type should be MaliitEnums::EnterKeyType type
    void hiddenTextChanged(bool hidden);
    void inputSourceChanged(InputSource source);
    void translatorChanged(bool speakLanguage);
    void forceFocusTo(QString label);
    void keyPressed(quint32 nativeScanCode, Qt::KeyboardModifiers, int eventType);
    void switchContext(Maliit::SwitchDirection direction);
    void clearAllPressed();
    void textKeyPressed(QString text);
    void languageChanged(QString language, QString label, QString langCode, QVariant data);
    void countryChanged(QString country);
    void visibleChanged(bool visible, bool reset);
    void keysymPressed(quint32, int);
    void languageCountChanged(int languageCount);
    void showLanguageNotification(QString label);
    void resetRequested();
    void keyReleased(bool isReleased);
    void cursorVisibleChanged(bool cursorVisible);
    void moveCursorPosition(int direction, int eventType);

//#IF_COMMERCIAL
    void setDefaultFocus();
//#ELSE
//#END

public Q_SLOTS:
    void onKeyPressed(QString nativeScanCode, bool shift, int eventType);
    void onSwitchContext();
    void onShowRequested(bool reset);
    void onHideRequested(bool reset);
    void onKeysymPressed(QString keysym, int eventType);

private:
    GlobalInputMethod* m_im;
    WebOSInputManager* m_ime;
    QScopedPointer<WindowInformation> m_winInfo;
    InputSource m_inputSource;
    QScopedPointer<QTranslator> translator;
    QString translatorLangCode;
};

#endif //KEYBOARD_H
