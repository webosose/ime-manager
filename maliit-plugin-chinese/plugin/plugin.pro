# Copyright (c) 2013-2019 LG Electronics, Inc.
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
TARGET = $${CHINESE_PLUGIN_TARGET}
TEMPLATE = lib
DEFINES += MALIIT_DEFAULT_PROFILE=\\\"$$MALIIT_DEFAULT_PROFILE\\\"
DEFINES += 'IMEMANAGER_RESOURCE_PATH=\\"$${MALIIT_PLUGINS_DIR}\\"'
DEFINES += 'DICTIONARY_PATH=\\"/usr/lib/maliit/plugins/dict\\"'

QT = core gui quick qml gui-private


CONFIG += \
    plugin \

LIBS += -lwebos-platform-interface

HEADERS += \
    plugin.h \
    inputmethod.h \
    suggestion.h \
    keyboard.h \
    windowinformation.h \
    layoutloader.h \
    languages.h \
    strokecomponent.h \
    maliitenums.h \
    chinesekeymap.h \
    automata.h \
    chineseautomata.h \
    ../openautomata/trie.h \
    ../openautomata/sunpinyinautomata.h \
    ../openautomata/pyzyautomata.h \
    ../openautomata/cangjieautomata.h \
    ../openautomata/strokeautomata.h

SOURCES += \
    plugin.cpp \
    inputmethod.cpp \
    suggestion.cpp \
    keyboard.cpp \
    windowinformation.cpp \
    layoutloader.cpp \
    strokecomponent.cpp \
    chinesekeymap.cpp \
    chineseautomata.cpp \
    ../openautomata/trie.cpp \
    ../openautomata/sunpinyinautomata.cpp \
    ../openautomata/pyzyautomata.cpp \
	../openautomata/cangjieautomata.cpp \
    ../openautomata/strokeautomata.cpp

# qml & json
DEFINES += 'IMEMANAGER_RESOURCE_PATH=\\"$${MALIIT_PLUGINS_DIR}\\"'
RESOURCES += ../../keyboard-common/common.qrc
RESOURCES += ../../keyboard-common/common-images.qrc
RESOURCES += ../../keyboard-common/common-images-hd.qrc

RESOURCES += jsons/openjson.qrc

OTHER_FILES += ../view/*

qml.path = $${MALIIT_PLUGINS_DIR}/qml/view-chinese
qml.files = ../view/*

dict.path = $${MALIIT_PLUGINS_DIR}/dict
dict.files = ../openautomata/dict/*

target.path += $${MALIIT_PLUGINS_DIR}/CHN
INSTALLS += target qml dict
