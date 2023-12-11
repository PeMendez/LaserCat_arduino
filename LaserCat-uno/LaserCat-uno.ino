// Include Libraries
#include "Arduino.h"
#include "VarSpeedServo.h"
#include <SoftwareSerial.h>

// Pin Definitions
#define LASER_PIN_S	2
#define SERVO9G1_PIN_SIG	3
#define SERVO9G2_PIN_SIG	4

// Global variables and defines
// object initialization
VarSpeedServo servo9g1;
VarSpeedServo servo9g2;
SoftwareSerial arduino_softSerial (10,11); //TX, RX

bool laserState = 0;
bool autoplayState = 0;

const int servoSpeed = 30;
const int seqIntervalDelta = 50;
const int manualyServoMinStep = 5;
const int manualyServoMaxStep = 10;
const int minimalRangeSize = 10;

// Change these parameters to define the rectangular play area
int servo1Min = 60;
int servo1Max = 130;
int servo2Min = 10;
int servo2Max = 50;

int servo1pos = (servo1Min + servo1Max) / 2;
int servo2pos = (servo2Min + servo2Max) / 2;
int delayVal = 500;
int maxDelayVal = 10000;
int minDelayVal = seqIntervalDelta;


// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup()
{
  // Setup Serial which is useful for debugging
  // Use the Serial Monitor to view printed messages
  Serial.begin(115200);
  while (!Serial) ; // wait for serial port to connect. Needed for native USB
  Serial.println("start");

  arduino_softSerial.begin(9600);
  Serial.println("Softserial On....");

  servo9g1.attach(SERVO9G1_PIN_SIG);         // 1. attach the servo to correct pin to control it.
  servo9g2.attach(SERVO9G2_PIN_SIG);         // 1. attach the servo to correct pin to control it.
  pinMode(LASER_PIN_S, OUTPUT);
  // start with laser off
  digitalWrite(LASER_PIN_S, laserState);
  servo9g2.write(servo2pos , servoSpeed);
  servo9g1.write(servo1pos , servoSpeed);
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop()
{
  // TODO: cambiar por softserial para que tome los comandos de nodemcu
  if (arduino_softSerial.available() > 0) {
    String command = arduino_softSerial.readStringUntil('\n');
    Serial.print("Comando recibido:\t");
    Serial.println(command);

  // Settings
  // Turn laser On/Off
  if (command.indexOf("Laser On/Off") != -1) {
    laserState = !laserState;
    digitalWrite(LASER_PIN_S, laserState);
    Serial.print("Laser: ");
    Serial.println(laserState);
  }
  // decrease the delay between random points in Autoplay mode
  else if (command.indexOf("Speed Up") != -1) {
    delayVal -= seqIntervalDelta;
    delayVal = constrain(delayVal, minDelayVal, maxDelayVal);
    Serial.print("delay: ");
    Serial.println(delayVal);
  }
  // increase the delay between random points in Autoplay mode
  else if (command.indexOf("Speed Down") != -1) {
    delayVal += seqIntervalDelta;
    delayVal = constrain(delayVal, minDelayVal, maxDelayVal);
    Serial.print("delay: ");
    Serial.println(delayVal);
  }
  // Enable Autoplay - random points
  else if (command.indexOf("Autoplay") != -1) {
    autoplayState = !autoplayState;
    Serial.print("AutoPlay: ");
    Serial.println(autoplayState);
  }
  // Widen the servo margins
  else if (command.indexOf("Area +") != -1) {
    servo1Min -= 5;
    servo1Max += 5;
    servo2Min -= 5;
    servo2Max += 5;

    servo1Min  = constrain(servo1Min, 0, servo1Max);
    servo1Max  = constrain(servo1Max, servo1Min, 180);
    servo2Min  = constrain(servo2Min, 0, servo2Max);
    servo2Max  = constrain(servo2Max, servo2Min, 180);
    Serial.print("Area +: ");
    char buf[20];
    sprintf(buf, "%d,%d,%d,%d", servo1Min, servo1Max, servo2Min, servo2Max);
    Serial.println(buf);
  }
  // tighten the servo margins
  else if (command.indexOf("Area -") != -1) {
    if (servo1Max - servo1Min > minimalRangeSize) {
      servo1Min += 5;
      servo1Max -= 5;
    }
    if (servo2Max - servo2Min > minimalRangeSize) {
      servo2Min += 5;
      servo2Max -= 5;
    }
    Serial.print("Area -: ");
    char buf[20];
    sprintf(buf, "%d,%d,%d,%d", servo1Min, servo1Max, servo2Min, servo2Max);
    Serial.println(buf);
  }


  // Functionality
  if (autoplayState || (command.indexOf("Random Position") != -1)) {
    laserState = 1;
    digitalWrite(LASER_PIN_S, laserState);
    while(autoplayState){
      servo9g2.write(random(servo2Min, servo2Max), servoSpeed);
      servo9g1.write(random(servo1Min, servo1Max), servoSpeed);
      // waits until servos reaches destination
      servo9g2.wait();
      servo9g1.wait();
      delay(delayVal);
      if (arduino_softSerial.available() > 0) {
        // if a new command exists, set autoplay false and break the loop
        autoplayState=false;
        return;
      }
    }
  }
  else {
    // Move the laser manually in random size steps from 5 - 20 deg
    if (command.indexOf("Up") != -1) {
      servo2pos += random(manualyServoMinStep, manualyServoMaxStep);
      servo2pos = constrain(servo2pos, servo2Min, servo2Max);
      servo9g2.write(servo2pos, servoSpeed);
      // waits until servo reaches destination
      servo9g2.wait();
      Serial.println(servo2pos);
    }
    else if (command.indexOf("Down") != -1) {
      servo2pos -= random(manualyServoMinStep, manualyServoMaxStep);
      servo2pos = constrain(servo2pos, servo2Min, servo2Max);
      servo9g2.write(servo2pos, servoSpeed);
      // waits until servo reaches destination
      servo9g2.wait();
      Serial.println(servo2pos);
    }
    else if (command.indexOf("Left") != -1) {
      servo1pos += random(manualyServoMinStep, manualyServoMaxStep);
      servo1pos = constrain(servo1pos, servo1Min, servo1Max);
      servo9g1.write(servo1pos, servoSpeed);
      // waits until servo reaches destination
      servo9g1.wait();
      Serial.println(servo1pos);
    }
    else if (command.indexOf("Right") != -1) {
      servo1pos -= random(manualyServoMinStep, manualyServoMaxStep);
      servo1pos = constrain(servo1pos, servo1Min, servo1Max);
      servo9g1.write(servo1pos, servoSpeed);
      // waits until servo reaches destination
      servo9g1.wait();
      Serial.println(servo1pos);
    }
    else if (command.indexOf("Corners") != -1){
      const int speed = servoSpeed/2;
      laserState = 1;
      digitalWrite(LASER_PIN_S, laserState);
      //left dwown corner
      servo9g1.write(servo1Min, speed);
      servo9g2.write(servo2Min, speed);
      servo9g1.wait();
      servo9g1.wait();
      Serial.println("Left down");
      delay(2000);
      //left up corner
      servo9g1.write(servo1Min, speed);
      servo9g2.write(servo2Max, speed);
      servo9g1.wait();
      servo9g1.wait();
      Serial.println("Left down");
      delay(2000);
      //right up corner
      servo9g1.write(servo1Max, speed);
      servo9g2.write(servo2Max, speed);
      servo9g1.wait();
      servo9g1.wait();
      Serial.println("Right up");
      delay(2000);
      //right down corner
      servo9g1.write(servo1Max, speed);
      servo9g2.write(servo2Min, speed);
      servo9g1.wait();
      servo9g1.wait();
      Serial.println("Right down");
      delay(2000);
      //left dwown corner again
      servo9g1.write(servo1Min, speed);
      servo9g2.write(servo2Min, speed);
      servo9g1.wait();
      servo9g1.wait();
      Serial.println("Finish");
      delay(2000);
      // center
      servo9g1.write(servo1pos, speed);
      servo9g2.write(servo2pos, speed);
      servo9g1.wait();
      servo9g1.wait();
      Serial.println("Center");
      delay(2000);
      // end
      laserState = 0;
      digitalWrite(LASER_PIN_S, laserState);
    }
  }
  }
}




/*******************************************************

     Circuito.io is an automatic generator of schematics and code for off
     the shelf hardware combinations.

     Copyright (C) 2016 Roboplan Technologies Ltd.

     This program is free software: you can redistribute it and/or modify
     it under the terms of the GNU General Public License as published by
     the Free Software Foundation, either version 3 of the License, or
     (at your option) any later version.

     This program is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
     GNU General Public License for more details.

     You should have received a copy of the GNU General Public License
     along with this program.  If not, see <http://www.gnu.org/licenses/>.

     In addition, and without limitation, to the disclaimers of warranties
     stated above and in the GNU General Public License version 3 (or any
     later version), Roboplan Technologies Ltd. ("Roboplan") offers this
     program subject to the following warranty disclaimers and by using
     this program you acknowledge and agree to the following:
     THIS PROGRAM IS PROVIDED ON AN "AS IS" AND "AS AVAILABLE" BASIS, AND
     WITHOUT WARRANTIES OF ANY KIND EITHER EXPRESS OR IMPLIED.  ROBOPLAN
     HEREBY DISCLAIMS ALL WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT
     NOT LIMITED TO IMPLIED WARRANTIES OF MERCHANTABILITY, TITLE, FITNESS
     FOR A PARTICULAR PURPOSE, NON-INFRINGEMENT, AND THOSE ARISING BY
     STATUTE OR FROM A COURSE OF DEALING OR USAGE OF TRADE.
     YOUR RELIANCE ON, OR USE OF THIS PROGRAM IS AT YOUR SOLE RISK.
     ROBOPLAN DOES NOT GUARANTEE THAT THE PROGRAM WILL BE FREE OF, OR NOT
     SUSCEPTIBLE TO, BUGS, SECURITY BREACHES, OR VIRUSES. ROBOPLAN DOES
     NOT WARRANT THAT YOUR USE OF THE PROGRAM, INCLUDING PURSUANT TO
     SCHEMATICS, INSTRUCTIONS OR RECOMMENDATIONS OF ROBOPLAN, WILL BE SAFE
     FOR PERSONAL USE OR FOR PRODUCTION OR COMMERCIAL USE, WILL NOT
     VIOLATE ANY THIRD PARTY RIGHTS, WILL PROVIDE THE INTENDED OR DESIRED
     RESULTS, OR OPERATE AS YOU INTENDED OR AS MAY BE INDICATED BY ROBOPLAN.
     YOU HEREBY WAIVE, AGREE NOT TO ASSERT AGAINST, AND RELEASE ROBOPLAN,
     ITS LICENSORS AND AFFILIATES FROM, ANY CLAIMS IN CONNECTION WITH ANY OF
     THE ABOVE.
********************************************************/
