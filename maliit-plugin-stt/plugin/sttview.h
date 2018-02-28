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

#ifndef STTVIEW_H
#define STTVIEW_H

#include <maliit/plugins/abstractinputmethod.h>

#include <QtQuick>
#include <QJsonArray>
#include "windowinformation.h"
class STTQuickView : public QQuickView
{
    public:
        STTQuickView():QQuickView(){
            qDebug() << "STTQuickView is Created";
        }

        void keyPressed(QKeyEvent * ke){
            keyPressEvent(ke);
        }
        void keyReleased(QKeyEvent * ke){
            keyReleaseEvent(ke);
        }
};

class STTView : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString emptyString READ getEmptyString NOTIFY languageChanged)
    Q_PROPERTY(QString vkbLanguage1 READ getVkbLangauge1)
    Q_PROPERTY(QString vkbLanguage2 READ getVkbLangauge2)
    Q_PROPERTY(QString vkbLanguage3 READ getVkbLangauge3)
    Q_PROPERTY(QString vkbLanguage4 READ getVkbLangauge4)
    Q_PROPERTY(QString vkbLanguage5 READ getVkbLangauge5)

public:
    STTView(MAbstractInputMethodHost* host);
    void show(QString language);
    void hide();
    void keyPressed(QKeyEvent * keyEvent);
    void keyReleased(QKeyEvent * keyEvent);
    Q_INVOKABLE void selectLanguage(QString locale);
    QString getEmptyString();
    QString getVkbLangauge1();
    QString getVkbLangauge2();
    QString getVkbLangauge3();
    QString getVkbLangauge4();
    QString getVkbLangauge5();
    void removeTranslator();
    void setVkbLanguageList(QJsonArray);
    void initialize();
    void handleWindowActivated();

Q_SIGNALS:
    void textKeyPressed(QString text);
    void backToKeyboardPressed();
    void visibleChanged(bool visible);
    void languageChanged();
    void sigCursorOn();
    void sigCursorOff();

public Q_SLOTS:
    void onShowSTTView();
    void slotPrintText(QString text);
    void slotPrintWarningText(QString text);

private:
    MAbstractInputMethodHost* m_host;
    QScopedPointer<STTQuickView> m_view;
    QScopedPointer<WindowInformation> m_winInfo;
    QScopedPointer<QTranslator> translator;
    QList<QString> vkbLanguageList;
};

#endif //STTVIEW_H
