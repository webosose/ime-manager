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

/*
keycode reference : qt-features-webos/include/qweboskeyextension.h
*/

QtObject {
    id: root

    readonly property int key_return:   36
    readonly property int key_red:      406
    readonly property int key_up:       111
    readonly property int key_left:     113
    readonly property int key_right:    114
    readonly property int key_down:     116

    readonly property int webOS_Exit:       0x01200001
    readonly property int webOS_Info:       0x01200002
    readonly property int webOS_Back:       420     //0x01200003
    readonly property int webOS_Settings:   0x01200004

    readonly property int webOS_Red:        0x01200011
    readonly property int webOS_Green:      0x01200012
    readonly property int webOS_Yellow:     0x01200013
    readonly property int webOS_Blue:       0x01200014

    readonly property int webOS_ChannelUp:      0x01200021
    readonly property int webOS_ChannelDown:    0x01200022
    readonly property int webOS_ChannelDash:    0x01200023
    readonly property int webOS_ChannelBack:    0x01200024
    readonly property int webOS_Favorite:       0x01200025
    readonly property int webOS_SetChannel:     0x01200026

    readonly property int webOS_3DMode:             0x01200031
    readonly property int webOS_ScreenRemote:       0x01200032
    readonly property int webOS_QMenu:              0x01200033
    readonly property int webOS_Voice:              436     //0x01200034
    readonly property int webOS_InputSource:        0x01200035
    readonly property int webOS_InputTV:            0x01200036
    readonly property int webOS_AspectRatio:        0x01200037
    readonly property int webOS_LiveTVMenu:         0x01200038
    readonly property int webOS_TVGuide:            0x01200039
    readonly property int webOS_AudioDescription:   0x01200040

    readonly property int webOS_Simplink:           0x01200053
    readonly property int webOS_InputTVRadio:       0x01200055

    readonly property int webOS_LocalUp:            0x01200061
    readonly property int webOS_LocalDown:          0x01200062
    readonly property int webOS_LocalLeft:          0x01200063
    readonly property int webOS_LocalRight:         0x01200064
    readonly property int webOS_LocalEnter:         0x01200065
    readonly property int webOS_LocalVolumeUp:      0x01200068
    readonly property int webOS_LocalVolumeDown:    0x01200069

    readonly property int webOS_CursorShow:         0x01200201
    readonly property int webOS_CursorHide:         0x01200202
    readonly property int webOS_CameraVoice:        0x01200203
    readonly property int webOS_FingerReadyCue:     0x01200204
    readonly property int webOS_FingerFocusOn:      0x01200205

    readonly property int webOS_FactoryPowerOnly:   0x01201001
    readonly property int webOS_FactoryInStart:     0x01201002
    readonly property int webOS_FactoryInStop:      0x01201003
    readonly property int webOS_FactoryAdjust:      0x01201004

    readonly property int webOS_FactoryTv:          0x01201010
    readonly property int webOS_FactoryVideo1:      0x01201011
    readonly property int webOS_FactoryVideo2:      0x01201012
    readonly property int webOS_FactoryComponent1:  0x01201013
    readonly property int webOS_FactoryHdmi1:       0x01201015
    readonly property int webOS_FactoryHdmi2:       0x01201016
    readonly property int webOS_FactoryHdmi3:       0x01201017
    readonly property int webOS_FactoryHdmi4:       0x01201018

    readonly property int webOS_FactoryEyeQ:        0x01201020
    readonly property int webOS_FactoryPictureMode: 0x01201021
    readonly property int webOS_FactorySoundMode:   0x01201022

    readonly property int webOS_FactoryMultiSoundSetting: 0x01201025
}
