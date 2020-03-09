# Copyright (c) 2013-2018 LG Electronics, Inc.
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
TARGET = $${GLOBAL_PLUGIN_TARGET}
TEMPLATE = lib
DEFINES += MALIIT_DEFAULT_PROFILE=\\\"$$MALIIT_DEFAULT_PROFILE\\\"

QT = core gui quick qml gui-private

CONFIG += \
    plugin \

LIBS += -lwebos-platform-interface

HEADERS += \
    plugin.h \
    inputmethod.h \
    automata.h \
    keyboard.h \
    windowinformation.h \
    prediction.h \
    maliitenums.h \
    layoutloader.h \
    countryinfotable.h \
    languageinfotable.h \
    globalautomata.h

SOURCES += \
    plugin.cpp \
    inputmethod.cpp \
    keyboard.cpp \
    windowinformation.cpp \
    prediction.cpp \
    layoutloader.cpp \
    countryinfotable.cpp \
    languageinfotable.cpp \
    globalautomata.cpp

# qml & json
DEFINES += 'IMEMANAGER_RESOURCE_PATH=\\"$${MALIIT_PLUGINS_DIR}\\"'
DEFINES += 'IMEMANAGER_USER_DICTIONARY_PATH=\\"/var/preferences/com.webos.imemanager\\"'
RESOURCES += ../../keyboard-common/common.qrc
RESOURCES += ../../keyboard-common/common-images.qrc
RESOURCES += ../../keyboard-common/common-images-hd.qrc

RESOURCES += jsons/json.qrc

OTHER_FILES += ../view/*

contains(DEFINES, UBUNTU_DESKTOP_BUILD) {
    HEADERS += dummyservice.h
    SOURCES += dummyservice.cpp
}

HEADERS += ../openautomata/wordpredict.h \
           ../openautomata/hangul.h \
           ../openautomata/openautomata.h \
           ../openautomata/automatabase.h \
           ../openautomata/automatautil.h \
           ../openautomata/englishautomata.h \
           ../openautomata/germanautomata.h \
           ../openautomata/dutchautomata.h \
           ../openautomata/italianautomata.h \
           ../openautomata/koreanautomata.h \
           ../openautomata/spanishautomata.h \
           ../openautomata/polishautomata.h \
           ../openautomata/frenchautomata.h \
           ../openautomata/portugueseautomata.h \
           ../openautomata/russianautomata.h \
           ../openautomata/latvianautomata.h \
           ../openautomata/finnishautomata.h \
           ../openautomata/croatianautomata.h \
           ../openautomata/danishautomata.h \
           ../openautomata/norwegianautomata.h \
           ../openautomata/czechautomata.h \
           ../openautomata/irishautomata.h \
           ../openautomata/albanianautomata.h \
           ../openautomata/bosnianautomata.h \
           ../openautomata/bulgarianautomata.h \
           ../openautomata/greekautomata.h \
           ../openautomata/estonianautomata.h \
           ../openautomata/hungarianautomata.h \
           ../openautomata/swedishautomata.h \
           ../openautomata/indonesianautomata.h \
           ../openautomata/ukrainianautomata.h \
           ../openautomata/thaiautomata.h \
           ../openautomata/turkishautomata.h \
           ../openautomata/vietnameseautomata.h \
           ../openautomata/hindiautomata.h \
           ../openautomata/arabicautomata.h \
           ../openautomata/arabicautomata.h \
           ../openautomata/malayautomata.h \
           ../openautomata/lithuanianautomata.h \
           ../openautomata/Kazakhautomata.h \
           ../openautomata/macedonianautomata.h \
           ../openautomata/hebrewautomata.h \
           ../openautomata/kurdishautomata.h \
           ../openautomata/persianautomata.h \
           ../openautomata/romanianautomata.h \
           ../openautomata/maoriautomata.h \
           ../openautomata/mongolianautomata.h \
           ../openautomata/serbianautomata.h \
           ../openautomata/slovakautomata.h \
           ../openautomata/slovenianautomata.h \
           ../openautomata/uzbeklatinautomdata.h \
           ../openautomata/cambodianautomata.h \
           ../openautomata/srilankanautomata.h \
           ../openautomata/tamilautomata.h \
           ../openautomata/kannadaautomata.h \
           ../openautomata/swahiliautomata.h \
           ../openautomata/malayalamautomata.h \
           ../openautomata/bengaliautomata.h \
           ../openautomata/gujaratiautomata.h \
           ../openautomata/teluguautomata.h \
           ../openautomata/marathiautomata.h \
           ../openautomata/assameseautomata.h \
           ../openautomata/punjabiautomata.h \
           ../openautomata/oriyaautomata.h \
           ../openautomata/urduautomata.h \
           ../openautomata/hausaautomata.h \
           ../openautomata/azerbaijaniautomata.h \
           ../openautomata/afrikaansautomata.h \
           ../openautomata/armenianautomata.h \
           ../openautomata/bashkirautomata.h \
           ../openautomata/icelandicautomata.h \
           ../openautomata/belarusianautomata.h \
           ../openautomata/catalanautomata.h \
           ../openautomata/igboautomata.h \
           ../openautomata/kyrgyzautomata.h \
           ../openautomata/luxembourgishautomata.h \
           ../openautomata/malteseautomata.h \
           ../openautomata/nepaliautomata.h \
           ../openautomata/northensothoautomata.h \
           ../openautomata/tajikautomata.h \
           ../openautomata/pashtoautomata.h \
           ../openautomata/tatarautomata.h \
           ../openautomata/turkmenautomata.h \
           ../openautomata/uyghurautomata.h \
           ../openautomata/wolofautomata.h \
           ../openautomata/yorubaautomata.h \
           ../openautomata/laoautomata.h \
           ../openautomata/georgianautomata.h \
           ../openautomata/burmeseautomata.h \
           ../openautomata/welshautomata.h \
           ../openautomata/zuluautomata.h \
           ../openautomata/somaliautomata.h

SOURCES += ../openautomata/wordpredict.cpp \
           ../openautomata/openautomata.cpp \
           ../openautomata/automatabase.cpp \
           ../openautomata/automatautil.cpp \
           ../openautomata/koreanautomata.cpp


isEmpty(MALIIT_PLUGIN_VERSION) {
    MALIIT_PLUGIN_VERSION = $$system("git describe --tags `git rev-list --tags --max-count=1`")
}

QMAKE_SUBSTITUTES += plugin.json.in
PRE_TARGETDEPS += plugin.json
QMAKE_DISTCLEAN += plugin.json

target.path += $${MALIIT_PLUGINS_DIR}
qml.path = $${MALIIT_PLUGINS_DIR}/qml/view-global
qml.files = ../view/*

common.path = $${MALIIT_PLUGINS_DIR}/qml/keyboard-common
common.files = ../../keyboard-common/*

dict.path = $${MALIIT_PLUGINS_DIR}/dict
dict.files = ../openautomata/dict/*

INSTALLS += target qml common dict
