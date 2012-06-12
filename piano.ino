/*
 * Copyright (c) Clinton Freeman 2012
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
 * NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#include <Servo.h>

Servo servoA;
Servo servoB;
Servo servoC;

// Assumed IR sensor wired to anaolog pin 0.
int IRIn = 0;


int servoAStart = 10;
int servoAEnd = 100;
int servoAAng = 0; // Change the "Ang" values for the starting angle of the servo.
float servoASwing = 180.0; // Change the "swing" values for the maximum arc of the servo.

int servoBStart = 101;
int servoBEnd = 200;
int servoBAng = 0;
float servoBSwing = 180.0;

int servoCStart = 201;
int servoCEnd = 300;
int servoCAng = 0;
int servoCSwing = 180.0;

int crazyZone = 301; 

// Starting position for each of the servos.
int servoAPos = servoAAng;
int servoBPos = servoBAng;
int servoCPos = servoCAng;

void setup() {
  // Assumed servo controls are wired to digital pins 2, 3 & 4.
  servoA.attach(2);
  servoB.attach(3);
  servoC.attach(4);  

  // Move the servos to a starting point.
  servoA.write(servoAPos);
  servoB.write(servoBPos);
  servoC.write(servoCPos);

  // Init random number generator.
  randomSeed(analogRead(0));
}

int determineServoPos(int IRValue, int IRStart, int IREnd, int servoAng, float servoSwing) {
  float movement = ((IRValue - IRStart) / (float) (IREnd - IRStart));
  return ((int) (movement * servoSwing)) + servoAng;
}

int clampValue(int value, int minV, int maxV) {
  int result = max(value, minV);
  result = min(value, maxV);

  return result;
}

void loop () {
  int IRValue = analogRead(IRIn);
  Serial.println(IRValue);

  if (IRValue > servoAStart && IRValue < servoAEnd) {
    servoAPos = determineServoPos(IRValue, servoAStart, servoAEnd, servoAAng, servoASwing);
    servoA.write(servoAPos);
  } 
  
  if (IRValue > servoBStart && IRValue < servoBEnd) {
    servoBPos = determineServoPos(IRValue, servoBStart, servoBEnd, servoBAng, servoBSwing);
    servoB.write(servoBPos);
  } 

  if (IRValue > servoCStart && IRValue < servoCEnd) {
    servoCPos = determineServoPos(IRValue, servoCStart, servoCEnd, servoCAng, servoCSwing);
    servoC.write(servoCPos);
  }

  if (IRValue > crazyZone) {
    // generate random number between -5 and 5.
    long randNumber = random(10) - 5;
    // Move servoA by a random amount.
    servoAPos += randNumber;
    
    servoAPos = clampValue(servoAPos, servoAAng, (servoAAng + servoASwing));
    servoA.write(servoAPos);
    
    // Move servoB by a random amount.
    randNumber = random(10) - 5;
    servoBPos += randNumber;
    servoBPos = clampValue(servoBPos, servoBAng, (servoBAng + servoBSwing));
    servoB.write(servoBPos);

    // Move servoC by a random amount.
    randNumber = random(10) - 5;
    servoCPos += randNumber;
    servoCPos = clampValue(servoCPos, servoCAng, (servoCAng + servoCSwing));
    servoC.write(servoCPos);
  }
}
