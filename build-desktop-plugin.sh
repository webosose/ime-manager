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

DESKTOP_CONFIG=""
DESKTOP_CONFIG+="CONFIG+=ubuntu-desktop-build "
#DESKTOP_CONFIG+="CONFIG+=disable-maliit-plugin-global "
#DESKTOP_CONFIG+="CONFIG+=enable-maliit-plugin-japanese "
#DESKTOP_CONFIG+="CONFIG+=enable-maliit-plugin-chinese "
DESKTOP_CONFIG+="CONFIG+=disable-tests "
DESKTOP_CONFIG+="CONFIG+=debug "

qmake PREFIX=$HOME/maliit ${DESKTOP_CONFIG}
make && make install

MALIIT_CONFIG_DIR="${HOME}/.config/maliit.org"
MALIIT_CONFIG_FILE="${MALIIT_CONFIG_DIR}/server.conf"
mkdir -p ${MALIIT_CONFIG_DIR}
echo "[maliit]" > ${MALIIT_CONFIG_FILE}
echo "onscreen\\enabled=libplugin-global.so:, libplugin-japanese.so:japanese, libplugin-chinese.so:chinese" >> ${MALIIT_CONFIG_FILE}
echo "onscreen\\active=libplugin-global.so:" >> ${MALIIT_CONFIG_FILE}
echo "onscreen\\currentlanguage=en" >> ${MALIIT_CONFIG_FILE}

