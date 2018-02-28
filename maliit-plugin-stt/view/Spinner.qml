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

import QtQuick 2.0

Rectangle {
    id: spin
    objectName: "spinner"
    anchors.centerIn: parent
    color: "transparent"

    property int waitBeforePlay: 100 //Wait to ckeck if app is already started
    opacity: 0
    property variant style
    property bool needScrim: false
    property bool playing: false
    property bool activated: true

    property int spinnerDiameter: sttStyle.spinner.diameter

    signal timeout()

    property var settings: ({})

    onSettingsChanged: {
        // Need to check this as the first assinment will trigger the signal
        if (settings.launcher === undefined)
            return;

        timeoutTimer.interval = settings.launcher.splashTimer;
        spin.activated = settings.globalActionsLaunchIndicator;
    }

    // Hide this from the public
    QtObject {
        id: d
        property int spinnerRadius: spinnerDiameter/2
        property int ballRadius: spinnerRadius/5
        property int ballDiameter: 2*ballRadius
        property int diffRadius: spinnerRadius-ballRadius
        property int nmbSteps: 10
        property real ballAngleRad: 2 * Math.atan(ballRadius/diffRadius)
        property real stepSize: (2*Math.PI - 2*ballAngleRad) / nmbSteps
        property real posAngle1: 1.5*ballAngleRad
        property real posAngle2: .5*ballAngleRad
        property real posAngle3: 2*Math.PI-.5*ballAngleRad

        property point center1: Qt.point(0,0)
        property point center2: Qt.point(0,0)
        property point center3: Qt.point(0,0)
        property var currBall1Angle
        property var currBall2Angle
        property var currBall3Angle
        property int currStep: 0
        property int currBall: 1
        property bool firstHit: false

        function animateSpinner() {
            setInitialPos();
            spin.opacity = 1;
            playing = true;
            ballTimer.start();
            timeoutTimer.start();
        }

        function setInitialPos() {
            currStep = 0;
            currBall = 1;
            firstHit = false;

            currBall1Angle = posAngle1;
            currBall2Angle = posAngle2;
            currBall3Angle = posAngle3;

            calculateBallsPositions();
        }

        function calculateBallCenter(angle, point) {
            var x = diffRadius * Math.cos(angle);
            var y = diffRadius * Math.sin(angle);
            point.x = diffRadius - y;
            point.y = diffRadius + x
        }

        function calculateBallsPositions() {
            calculateBallCenter(currBall1Angle, center1);
            calculateBallCenter(currBall2Angle, center2);
            calculateBallCenter(currBall3Angle, center3);
        }

        function showKinetic() {
            if (!firstHit)
                return;

            switch (currBall) {
            case 1:
                switch (currStep) {
                case 1:
                    currBall3Angle = currBall3Angle + ballAngleRad / 4;
                    calculateBallCenter(currBall3Angle, center3);
                    currBall2Angle = currBall2Angle + ballAngleRad / 2;
                    calculateBallCenter(currBall2Angle, center2);
                    break;
                case 2:
                    currBall3Angle = currBall3Angle + ballAngleRad / 8;
                    calculateBallCenter(currBall3Angle, center3);
                    currBall2Angle = currBall2Angle + ballAngleRad / 2;
                    calculateBallCenter(currBall2Angle, center2);
                    break;
                case 3:
                    currBall3Angle = currBall3Angle + ballAngleRad / 8;
                    calculateBallCenter(currBall3Angle, center3);
                    currBall2Angle = currBall2Angle - ballAngleRad / 4;
                    calculateBallCenter(currBall2Angle, center2);
                    break;
                case 4:
                    currBall2Angle = currBall2Angle - ballAngleRad / 8;
                    calculateBallCenter(currBall2Angle, center2);
                    break;
                case 5:
                    currBall2Angle = currBall2Angle - ballAngleRad / 8;
                    calculateBallCenter(currBall2Angle, center2);
                    break;
                }
                break;
            case 2:
                switch (currStep) {
                case 1:
                    currBall1Angle = currBall1Angle + ballAngleRad / 4;
                    calculateBallCenter(currBall1Angle, center1);
                    currBall3Angle = currBall3Angle + ballAngleRad / 2;
                    calculateBallCenter(currBall3Angle, center3);
                    break;
                case 2:
                    currBall1Angle = currBall1Angle + ballAngleRad / 8;
                    calculateBallCenter(currBall1Angle, center1);
                    currBall3Angle = currBall3Angle + ballAngleRad / 2;
                    calculateBallCenter(currBall3Angle, center3);
                    break;
                case 3:
                    currBall1Angle = currBall1Angle + ballAngleRad / 8;
                    calculateBallCenter(currBall1Angle, center1);
                    currBall3Angle = currBall3Angle - ballAngleRad / 4;
                    calculateBallCenter(currBall3Angle, center3);
                    break;
                case 4:
                    currBall3Angle = currBall3Angle - ballAngleRad / 8;
                    calculateBallCenter(currBall3Angle, center3);
                    break;
                case 5:
                    currBall3Angle = currBall3Angle - ballAngleRad / 8;
                    calculateBallCenter(currBall3Angle, center3);
                    break;
                }
                break;
            case 3:
                switch (currStep) {
                case 1:
                    currBall2Angle = currBall2Angle + ballAngleRad / 4;
                    calculateBallCenter(currBall2Angle, center2);
                    currBall1Angle = currBall1Angle + ballAngleRad / 2;
                    calculateBallCenter(currBall1Angle, center1);
                    break;
                case 2:
                    currBall2Angle = currBall2Angle + ballAngleRad / 8;
                    calculateBallCenter(currBall2Angle, center2);
                    currBall1Angle = currBall1Angle + ballAngleRad / 2;
                    calculateBallCenter(currBall1Angle, center1);
                    break;
                case 3:
                    currBall2Angle = currBall2Angle + ballAngleRad / 8;
                    calculateBallCenter(currBall2Angle, center2);
                    currBall1Angle = currBall1Angle - ballAngleRad / 4;
                    calculateBallCenter(currBall1Angle, center1);
                    break;
                case 4:
                    currBall1Angle = currBall1Angle - ballAngleRad / 8;
                    calculateBallCenter(currBall1Angle, center1);
                    break;
                case 5:
                    currBall1Angle = currBall1Angle - ballAngleRad / 8;
                    calculateBallCenter(currBall1Angle, center1);
                    break;
                }
                break;
            }
        }

        function changeBallPosition() {
            var currBallAngle;
            switch (currBall) {
            case 1:
                currBallAngle = currBall1Angle + currStep * stepSize;
                calculateBallCenter(currBallAngle, center1);
                break;
            case 2:
                currBallAngle = currBall2Angle + currStep * stepSize;
                calculateBallCenter(currBallAngle, center2);
                break;
            case 3:
                currBallAngle = currBall3Angle + currStep * stepSize;
                calculateBallCenter(currBallAngle, center3);
                break;
            }
            showKinetic();
        }

        function pushBalls() {
            switch (currBall) {
            case 1:
                currBall1Angle = posAngle3 - ballAngleRad / 2;
                currBall2Angle = posAngle1;
                currBall3Angle = posAngle2 - ballAngleRad / 2;
                currBall = 2;
                break;
            case 2:
                currBall1Angle = posAngle2 - ballAngleRad / 2;
                currBall2Angle = posAngle3 - ballAngleRad / 2;
                currBall3Angle = posAngle1;
                currBall = 3;
                break;
            case 3:
                currBall1Angle = posAngle1;
                currBall2Angle = posAngle2 - ballAngleRad / 2;
                currBall3Angle = posAngle3 - ballAngleRad / 2;
                currBall = 1;
                break;
            }

            calculateBallsPositions();
        }
    }

    Timer {
        id: ballTimer
        interval: 60
        onTriggered: {
            if (d.currStep == d.nmbSteps - 2) {
                d.pushBalls();
                d.currStep = 0;
                d.firstHit = true;
                restart();
                return;
            }

            d.currStep++;
            d.changeBallPosition();
            restart();
        }
    }

    Timer {
        id: waitTimer
        interval: waitBeforePlay
        onTriggered: {
            d.animateSpinner();
        }
        running: false
        repeat: false
    }

    Timer {
        id: timeoutTimer
        interval: 20000 // overwritten by settings
        onTriggered: {
            spin.timeout();
            spin.stop();
        }
        running: false
        repeat: false
    }



    Rectangle {
        id: scrim
	objectName: "scrim"
        color: "#000000"
        opacity: needScrim? 1.0 : 0.0
        anchors.fill: parent
    }

    Image {
        id: spinnerBg
        objectName: "spinnerBg"
        anchors.centerIn: parent
        visible: false
        source: "images/small_spinner_bg.png"
        sourceSize.height: spinnerDiameter
    }

    Rectangle {
        anchors.centerIn: parent
        color: "transparent"


        Item {
            id: plate
            objectName: "plate"
            width: spinnerDiameter
            height: spinnerDiameter
            anchors.centerIn: parent
        }

        Rectangle {
            id: ball1
            objectName: "ball1"
            anchors.left: plate.left
            anchors.top: plate.top
            antialiasing: true
            color: "#ff4a4a" //red
            width: d.ballDiameter
            height: d.ballDiameter
            radius: d.ballRadius
            anchors.leftMargin: d.center1.x
            anchors.topMargin: d.center1.y
        }
        Rectangle {
            id: ball2
            objectName: "ball2"
            anchors.left: plate.left
            anchors.top: plate.top
            antialiasing: true
            color: "#ffb80d" //orange
            width: d.ballDiameter
            height: d.ballDiameter
            radius: d.ballRadius
            anchors.leftMargin: d.center2.x
            anchors.topMargin: d.center2.y
        }
        Rectangle {
            id: ball3
            objectName: "ball3"
            anchors.left: plate.left
            anchors.top: plate.top
            antialiasing: true
            color: "#69cdff" //light blue
            width: d.ballDiameter
            height: d.ballDiameter
            radius: d.ballRadius
            anchors.leftMargin: d.center3.x
            anchors.topMargin: d.center3.y
        }
    }

    function play(showScrim) {
        if (!spin.activated) {
            console.log("spinner was disabled by settings");
            return;
        }
        needScrim = showScrim;
        if (waitBeforePlay > 0)
            waitTimer.start();
        else {
            spin.opacity = 1;
            d.animateSpinner();
        }
    }

    function stop() {
        needScrim = false;
        timeoutTimer.stop();
        ballTimer.stop();
        waitTimer.stop();
        spin.opacity = 0;
        playing = false;
    }
}
