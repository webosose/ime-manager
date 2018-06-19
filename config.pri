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

# Linker optimization for release build
QMAKE_LFLAGS_RELEASE+=-Wl,--as-needed
# Compiler warnings are error if the build type is debug.
# Except when we pass a CONFIG+=no-werror as a workaround for QTBUG-18092
no-werror {
    QMAKE_CXXFLAGS_DEBUG+=-O0
} else {
    QMAKE_CXXFLAGS_DEBUG+=-Werror -O0
}

# Enable Qt message log context
DEFINES += QT_MESSAGELOGCONTEXT

# This flag define to use QtQuickCompiler during compilation
# if current Qt build support it.
# If QtQuickCompiler is not present in current build
# this flag will be ignored by Qt
CONFIG += qtquickcompiler

# The feature maliit-defines initializes some variables related for MALIIT, such as installation paths
# here have to load it early, to start using the defines immediately
!load(maliit-defines) {
    #NOTE This should be error if we don't have global-keyboard
    #error(Cannot find $$[QT_INSTALL_DATA]/mkspecs/features/maliit-defines.prf. Probably Maliit framework not installed)
    warning(Cannot find $$[QT_INSTALL_DATA]/mkspecs/features/maliit-defines.prf. Probably Maliit framework not installed)
}
# This enables the maliit library for C++ code
CONFIG += maliit-plugins qt

isEmpty(PREFIX) {
    PREFIX = $$MALIIT_PREFIX
}

isEmpty(LIBDIR) {
    LIBDIR = $$PREFIX/lib
}

isEmpty(MALIIT_DEFAULT_PROFILE) {
    MALIIT_DEFAULT_PROFILE = nokia-n9
}

contains(QT_CONFIG, embedded) {
    CONFIG += qws
}

INSTALL_BIN = $$PREFIX/bin
INSTALL_LIBS = $$LIBDIR
INSTALL_HEADERS = $$PREFIX/include
INSTALL_DOCS = $$PREFIX/share/doc

enable-opengl {
    QT += opengl
    DEFINES += MALIIT_KEYBOARD_HAVE_OPENGL
}

MALIIT_PACKAGENAME = maliit-plugins
#MALIIT_VERSION = $$system(cat $$PWD/VERSION)

ubuntu-desktop-build {
    DEFINES += UBUNTU_DESKTOP_BUILD
}
