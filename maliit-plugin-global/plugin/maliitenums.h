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

#ifndef MALIIT_ENUMS_H
#define MALIIT_ENUMS_H

#include <QObject>
#include <maliit/namespace.h>

//! \brief MaliitQuick exposes Maliit enums to QML-based input methods
class MaliitEnums : public QObject
{
    Q_OBJECT
    Q_ENUMS(ContentType)
    Q_ENUMS(EnterKeyType)

public:
    enum ContentType {
        FreeTextContentType = Maliit::FreeTextContentType,
        NumberContentType = Maliit::NumberContentType,
        PhoneNumberContentType = Maliit::PhoneNumberContentType,
        EmailContentType = Maliit::EmailContentType,
        UrlContentType = Maliit::UrlContentType,
        CustomContentType = Maliit::CustomContentType
    };

    enum EnterKeyType {
        DefaultEnterKeyType = Maliit::DefaultEnterKeyType,
        ReturnEnterKeyType = Maliit::ReturnEnterKeyType,
        DoneEnterKeyType = Maliit::DoneEnterKeyType,
        GoEnterKeyType = Maliit::GoEnterKeyType,
        SendEnterKeyType = Maliit::SendEnterKeyType,
        SearchEnterKeyType = Maliit::SearchEnterKeyType,
        NextEnterKeyType = Maliit::NextEnterKeyType,
        PreviousEnterKeyType = Maliit::PreviousEnterKeyType
    };
};

#endif // MALIIT_ENUMS_H
