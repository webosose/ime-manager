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

#include "windowinformation.h"
#include <QGuiApplication>
#include <QScreen>

WindowInformation::WindowInformation()
{
    connect(QGuiApplication::primaryScreen(), SIGNAL(geometryChanged(QRect)),
            this, SLOT(screenGeometryChanged(QRect)));

    //initialising screen and window properties through SLOT function itself.
    screenGeometryChanged(QGuiApplication::primaryScreen()->geometry());
}

void WindowInformation::screenGeometryChanged(const QRect &geometry) {
    QSize screenSize = geometry.size();
    m_screenWidth = screenSize.width();
    m_screenHeight = screenSize.height();
    m_windowWidth = screenSize.width();
    //Handling checks for both landscape and portrait conditions. Condition used to assign windowheight based on FULLHD/HD
    m_windowHeight = ((m_screenWidth >= 1920 && m_screenHeight >= 1080) || (m_screenWidth >= 1080 && m_screenHeight >= 1920))? 324:217;
}

WindowInformation::~WindowInformation()
{
}
