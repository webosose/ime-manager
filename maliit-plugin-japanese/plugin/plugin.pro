# Copyright (c) 2019 LG Electronics, Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# SPDX-License-Identifier: Apache-2.0

include(../config.pri)
include(../config-plugin.pri)

TOP_BUILDDIR = $${OUT_PWD}/../..
TARGET = $${JAPANESE_PLUGIN_TARGET}
TEMPLATE = lib
DEFINES += MALIIT_DEFAULT_PROFILE=\\\"$$MALIIT_DEFAULT_PROFILE\\\"

QT = core gui quick qml gui-private

CONFIG += \
    plugin

LIBS += -lwebos-platform-interface

HEADERS += \
    plugin.h \
    inputmethod.h \
    keyboard.h \
    prediction.h \
    windowinformation.h \
    maliitenums.h \
    ../openautomata/openwnnautomata.h

SOURCES += \
    plugin.cpp \
    inputmethod.cpp \
    keyboard.cpp \
    prediction.cpp \
    windowinformation.cpp \
    ../openautomata/openwnnautomata.cpp

RESOURCES += \
    ../../keyboard-common/common.qrc \
    ../../keyboard-common/common-images.qrc \
    ../view/japanese-images.qrc

DEFINES += 'IMEMANAGER_RESOURCE_PATH=\\"$${MALIIT_PLUGINS_DIR}\\"'

OTHER_FILES += ../view/*

qml.path = $${MALIIT_PLUGINS_DIR}/qml/view-japanese
qml.files = ../view/*

target.path += $${MALIIT_PLUGINS_DIR}/JPN
INSTALLS += target qml
