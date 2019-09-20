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

#ifndef WINDOW_INFORMATION_H
#define WINDOW_INFORMATION_H

#include <QObject>

class WindowInformation : public QObject
{
    Q_OBJECT

public:
    WindowInformation();
    ~WindowInformation();

    int  windowWidth() const { return m_windowWidth; }
    int  windowHeight() const { return m_windowHeight; }
    int  screenWidth() const { return m_screenWidth; }
    int  screenHeight() const { return m_screenHeight; }

public slots:
    void screenGeometryChanged(const QRect &geometry);

private:
    int m_windowWidth;
    int m_windowHeight;
    int m_screenWidth;
    int m_screenHeight;
};

#endif //WINDOW_INFORMATION_H
