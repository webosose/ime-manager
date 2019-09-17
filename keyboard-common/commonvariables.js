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

.pragma library

// set this as a default focus for 5-way remote
var defaultFocusItem = undefined;

// This will save the previous focused item. we can use it
var savedFocusItem = undefined;

var left = 0;

var right = 1;

var MouseEvent = 1
var KeyBoardEvent = 2
var TouchEvent = 3
