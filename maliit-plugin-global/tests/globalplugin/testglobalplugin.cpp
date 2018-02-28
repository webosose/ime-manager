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

#include "testglobalplugin.h"

#include <QString>
#include <QtTest>
#include <qdebug.h>

TestGlobalPlugin::TestGlobalPlugin()
    :plugin(new GlobalPlugin())
{
}

void TestGlobalPlugin::initTestCase()
{
}

void TestGlobalPlugin::testGetPluginName()
{
    QString plugName = plugin->name();
    QCOMPARE(plugName, QString("GlobalPlugin"));
}

void TestGlobalPlugin::testGetSupportedStates()
{
    QSet<Maliit::HandlerState> allowedStates = plugin->supportedStates();
    int size = allowedStates.size();

    if(size == 0)
        QFAIL("global plugin supportedstates size is 0");
}

void TestGlobalPlugin::cleanupTestCase()
{
}

QTEST_APPLESS_MAIN(TestGlobalPlugin)
