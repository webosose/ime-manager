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

include(config.pri)
include(bno-resources/bno-resources.pri)

!isEmpty(HELP) {
    # Output help
    help_string = \
        Recognised CONFIG flags: \
        \\n\\t disable-maliit-plugin-global: Do not build the maliit-plugin-global \
        \\n\\t disable-tests: Do not build the tests \
        \\nExamples: \
        \\n\\t qmake \
        \\n\\t qmake CONFIG+=disable-maliit-plugin-global

    !build_pass:system(echo \"$$help_string\")
} else {
    config_string = Tip: Run qmake HELP=1 for a list of all supported build options

    !build_pass:system(echo \"$$config_string\")
}

CONFIG += ordered
TEMPLATE = subdirs

!disable-maliit-plugin-global:SUBDIRS += maliit-plugin-global

CONFIG += webos-service
WEBOS_SYSBUS_DIR = service
