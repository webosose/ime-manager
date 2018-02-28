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

#include "prediction.h"
#include "countryinfotable.h"

Prediction::Prediction(MAbstractInputMethodHost* host)
    : m_host(host)
    , m_predictionIndex(0)
    , m_predictionList()
    , m_active(false)
    , m_countryCode("us")
    , m_urlStrings(QString("http:// https:// www. .com .org /").split(" "))
    , m_emailStrings(QString(".com .org /").split(" "))
    , m_contentType(Maliit::FreeTextContentType)
{
}

void Prediction::setPredictionIndex(int index)
{
    m_predictionIndex = index;
    Q_EMIT predictionIndexChanged(index);
}

int Prediction::getPredictionIndex()
{
    return m_predictionIndex;
}

void Prediction::setPredictionList(QStringList predictionList)
{
    qDebug() << ":::> setPredictionList 1* c,p: " << m_contentType << predictionList;
    if (m_contentType == Maliit::UrlContentType || m_contentType == Maliit::EmailContentType)
        return;

    m_predictionList = predictionList;
    setPredictionIndex(0);
    setActive(0 < m_predictionList.length());
    Q_EMIT predictionListChanged();
}

QVariant Prediction::getPredictionList()
{
    return QVariant::fromValue(m_predictionList);
}

void Prediction::clearPredictionList()
{
    if (m_contentType != Maliit::UrlContentType && m_contentType != Maliit::EmailContentType) {
        m_predictionList.clear();
        Q_EMIT predictionListChanged();
        setActive(false);
    }
}

void Prediction::onSelected(QString selectedString)
{
    if (m_contentType == Maliit::UrlContentType || m_contentType == Maliit::EmailContentType)
        Q_EMIT predictionSelected(selectedString, false);
    else
        Q_EMIT predictionSelected(selectedString, true);
}

void Prediction::setActive(bool active)
{
    if (active != m_active) {
        m_active = active;
        Q_EMIT activeChanged(active);
    }
}

void Prediction::setCountry(QString country)
{
    // set the list for url and email
    m_urlStrings.clear();
    m_urlStrings << (CountryInfoTable::getInstance()->getUrlSuggestions(country));

    m_emailStrings.clear();
    m_emailStrings << (CountryInfoTable::getInstance()->getEmailSuggestions(country));

    if (m_contentType == Maliit::UrlContentType)
        m_predictionList = m_urlStrings;
    else if (m_contentType == Maliit::EmailContentType)
        m_predictionList = m_emailStrings;

    Q_EMIT predictionListChanged();
}

void Prediction::onHiddenTextChanged(bool hiddenText)
{
    Q_UNUSED(hiddenText);
    clearPredictionList();
}

void Prediction::onContentTypeChanged(int contentType)
{
    m_predictionList.clear();

    m_contentType = contentType;
    switch (contentType) {
        case Maliit::FreeTextContentType :
            setPredictionIndex(0);
            setActive(false);
            break;
        case Maliit::UrlContentType:
            m_predictionList = m_urlStrings;
            setPredictionIndex(0);
            setActive(false);
            break;
        case Maliit::EmailContentType:
            m_predictionList = m_emailStrings;
            setPredictionIndex(0);
            setActive(false);
            break;
        default:
            setActive(false);
    }
    Q_EMIT predictionListChanged();
}
