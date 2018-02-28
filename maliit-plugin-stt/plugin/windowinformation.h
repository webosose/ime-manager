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

#ifndef WINDOW_INFORMATION_H
#define WINDOW_INFORMATION_H

#include <QObject>

class WindowInformation : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int screenWidth  READ screenWidth  NOTIFY screenWidthChanged)
    Q_PROPERTY(int screenHeight READ screenHeight NOTIFY screenHeightChanged)
    Q_PROPERTY(int windowWidth  READ windowWidth  NOTIFY windowWidthChanged)
    Q_PROPERTY(int windowHeight READ windowHeight NOTIFY windowHeightChanged)

public:
    WindowInformation();
    ~WindowInformation();

    int  windowWidth()  const { return m_windowWidth; }
    int  windowHeight() const { return m_windowHeight; }
    int  screenWidth()  const { return m_screenWidth; }
    int  screenHeight() const { return m_screenHeight; }

Q_SIGNALS:
    void screenWidthChanged(int width);
    void screenHeightChanged(int height);
    void windowWidthChanged(int width);
    void windowHeightChanged(int height);

public slots:
    void screenGeometryChanged(const QRect &geometry);

protected:
    int m_windowWidth;
    int m_windowHeight;
    int m_screenWidth;
    int m_screenHeight;
};

#endif //WINDOW_INFORMATION_H
