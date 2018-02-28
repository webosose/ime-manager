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

#include "sttview.h"

#include <maliit/plugins/abstractinputmethodhost.h>

#ifndef UBUNTU_DESKTOP_BUILD
#include <qpa/qwindowsysteminterface.h>
#endif

STTView::STTView(MAbstractInputMethodHost* host)
    : m_host(host)
    , m_view(new STTQuickView())
    , m_winInfo(new WindowInformation)
    , translator(new QTranslator(this))
{
    m_view->rootContext()->setContextProperty("PluginProxy", this);
    m_view->rootContext()->setContextProperty("WindowInformation", m_winInfo.data());
    m_view->setSource(QUrl("qrc:///stt/main.qml"));

    QSurfaceFormat f = m_view->format();
    f.setAlphaBufferSize(8);
    f.setBlueBufferSize(8);
    f.setGreenBufferSize(8);
    f.setRedBufferSize(8);
    m_view->setFormat(f);

    m_view->setClearBeforeRendering(true);
    m_view->setColor(Qt::transparent);

    m_view->create();

    m_view->setY(QGuiApplication::primaryScreen()->availableSize().height());
    m_view->resize(m_winInfo->windowWidth(), m_winInfo->windowHeight());
    m_view->setResizeMode(QQuickView::SizeRootObjectToView);
    m_view->setFlags(m_view->flags() | Qt::FramelessWindowHint);

    QObject::connect(m_view->rootObject(), SIGNAL (textKeyPressed(QString)),
            this, SIGNAL(textKeyPressed(QString)));

    QObject::connect(m_view->rootObject(), SIGNAL (backToKeyboardPressed()),
            this, SIGNAL(backToKeyboardPressed()));

    QObject::connect(m_view->rootObject(), SIGNAL (canShowSTTView()),
            this, SLOT(onShowSTTView()));

    QObject::connect(m_view->rootObject(), SIGNAL(sigSendText(QString)),
            this, SLOT(slotPrintText(QString)));
    QObject::connect(m_view->rootObject(), SIGNAL(sigSendWarningText(QString)),
            this, SLOT(slotPrintWarningText(QString)));

    QObject::connect(this, SIGNAL(sigCursorOn()),
            m_view->rootObject(), SLOT(slotCursorOn()));
    QObject::connect(this, SIGNAL(sigCursorOff()),
            m_view->rootObject(), SLOT(slotCursorOff()));
    QObject::connect(this, SIGNAL(languageChanged()),
            m_view->rootObject(), SLOT(slotLanguageChanged()));
    m_host->registerWindow(m_view.data(), Maliit::PositionCenterBottom);
}

void STTView::onShowSTTView()
{
    qDebug() << __PRETTY_FUNCTION__;
    m_view->show();
}

void STTView::show(QString languageStr)
{
    qDebug() << __PRETTY_FUNCTION__;
    qDebug() << "languageStr: " << languageStr;
    if(languageStr == "cmn-Hans-CN") languageStr = "zh-Hans-CN";
    else if(languageStr == "yue-Hant-HK") languageStr = "zh-Hant-HK";
    else if(languageStr == "cmn-Hant-TW") languageStr = "zh-Hant-TW";

    selectLanguage(languageStr);
    m_view->rootObject()->setProperty("isShow", true);
}

void STTView::hide()
{
    m_view->rootObject()->setProperty("isShow", false);
    m_view->hide();
}

void STTView::keyPressed(QKeyEvent * keyEvent)
{
    m_view->keyPressed(keyEvent);
}

void STTView::keyReleased(QKeyEvent * keyEvent)
{
    m_view->keyReleased(keyEvent);
}

void STTView::selectLanguage(QString locale) {
    qWarning() << " -------------------- START OF LOAD MULTI-LANGUAGE ---------------------";
    if(translator) qApp->removeTranslator(translator.data());
    QString translationFilePath("/usr/share/qml/locales/imemanager");
    QString translationFileName("imemanager");

    QString tmpLocale = locale;
    tmpLocale.replace(QString("-"),QString("_"));
    if(translator->load(translationFileName + QString("_") + tmpLocale, translationFilePath)) {
        qWarning() <<"translation file loaded by fileName : " << translationFileName + QString("_") + tmpLocale;
    } else {
        translator->load(QLocale(locale), translationFileName, "_", translationFilePath);
        qWarning() <<"translation file loaded by fileSearch : " << translationFileName;
    }
    if(translator.isNull()) return;
    qApp->installTranslator(translator.data());
    qWarning() <<" -------------------- END OF LOAD MULTI-LANGUAGE ---------------------";
    Q_EMIT languageChanged();
}

QString STTView::getEmptyString() {
    return "";
}

void STTView::removeTranslator()
{
    if (translator)
        qApp->removeTranslator(translator.data());
}

void STTView::setVkbLanguageList(QJsonArray vkbLanguageArray){
    for(int i = 0; i < vkbLanguageArray.count(); i++) {
       vkbLanguageList.append(vkbLanguageArray[i].toString());
    }
}

QString STTView::getVkbLangauge1() {
    if(vkbLanguageList.count() >= 1){
        return (QString)vkbLanguageList.value(0);
    }
    return "";
}
QString STTView::getVkbLangauge2() {
    if(vkbLanguageList.count() >= 2){
        return (QString)vkbLanguageList.value(1);
    }
    return "";
}
QString STTView::getVkbLangauge3() {
    if(vkbLanguageList.count() >= 3){
        return (QString)vkbLanguageList.value(2);
    }
    return "";
}
QString STTView::getVkbLangauge4() {
    if(vkbLanguageList.count() >= 4){
        return (QString)vkbLanguageList.value(3);
    }
    return "";
}
QString STTView::getVkbLangauge5() {
    if(vkbLanguageList.count() >= 5){
        return (QString)vkbLanguageList.value(4);
    }
    return "";
}
void STTView::initialize() {
    vkbLanguageList.clear();
    handleWindowActivated();
}
void STTView::handleWindowActivated() {

#ifndef UBUNTU_DESKTOP_BUILD
    QWindowSystemInterface::handleWindowActivated(m_view.data());
#endif
}
void STTView::slotPrintText(QString text) {
    qDebug() << text;
}

void STTView::slotPrintWarningText(QString text) {
    qWarning() << text;
}
