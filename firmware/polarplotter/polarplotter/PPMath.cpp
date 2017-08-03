/*
  PPMath.cpp - Polar Plotter Firmware
  Created by Avetis Zakhayan, 2017
  Released into the public domain.
*/

#include "Arduino.h"
#include "PPMath.h"
#include "Point.h"

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <Servo.h> 

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_StepperMotor *turntable = AFMS.getStepper(200, 2);
Adafruit_StepperMotor *tonearm = AFMS.getStepper(200, 1);

PPMath::PPMath()
{
  turnTableRotation = 0;
  toneArmRotation = 0;
  R = 62.0; //mm
  currentPoint = Point(0, 0);
  ttBuffer = 0;
  taBuffer = 0;
}

void PPMath::setup() {
    AFMS.begin();
    turntable->release();
    tonearm->release();
}

double PPMath::moveTo(double xTo, double yTo)
{
  Point originalA = Point(currentPoint);
  Point currA = Point(originalA);

  Point originalB = *Point(xTo, yTo).transform(turnTableRotation);
  Point currB = Point(originalB);
  
  
  double lenB = originalB.len();
  double bTargetX = -(lenB * lenB) / (2.0 * R);
  double bTargetY = lenB * sqrt(1.0 - (lenB * lenB) / (4.0 * R * R));
  Point targetB = Point(bTargetX, bTargetY);
  double deltaAngle = targetB.getAngle() - originalB.getAngle();
  double currAngle = currentPoint.getAngle();
  currAngle = 0;

  double angleStep = 1.8 * DEG_TO_RAD / 16.0;   


  for(double i = currAngle; i < currAngle+deltaAngle; i+=angleStep) {
      moveTurntableBy(angleStep/angleStep);
      currentPoint.transform(angleStep);
      turnTableRotation += angleStep;
      // now when this is down update A and B
      currA.transform(angleStep);
      currB.transform(angleStep);

      double alpha = getAlphaFromAB(&currA, &currB); // This is the NEW angle of tonearm calculated from A & B

      Serial.println(alpha);
      double deltaTonearm = alpha - toneArmRotation;
      //Serial.println(deltaTonearm);
      moveArmBy(deltaTonearm/angleStep);
      toneArmRotation += deltaTonearm;
  }
  
}

void PPMath::moveTurntableBy(double steps) {
  ttBuffer+=steps;
  if(abs(ttBuffer) >= 1) {
    steps = (int)ttBuffer;
    ttBuffer -= steps;
  }

  if(abs(steps) >= 1) {
    for(int i = 0; i < abs(steps); i++) {
      int dir = 1;
      if(steps < 0) dir = -1;
      turntable->onestep(1 * dir, MICROSTEP);
    }
  }
}

void PPMath::moveArmBy(double steps) {
  taBuffer+=steps;
  if(abs(taBuffer) >= 1) {
    steps = (int)taBuffer;
    taBuffer -= steps;
  }

  if(abs(steps) >= 1) {
    for(int i = 0; i < abs(steps); i++) {
      int dir = -1;
      if(steps < 0) dir = 1;
      tonearm->onestep(dir, MICROSTEP);
    }
  }
}

double PPMath::getAlphaFromAB(Point* currA, Point* currB) 
{
    double underPart = sqrt((currA->getX() - currB->getX()) * (currA->getX() - currB->getX()) + (currA->getY() - currB->getY()) * (currA->getY() - currB->getY()));
    Point normal = Point((currA->getY() - currB->getY())/underPart, (currB->getX() - currA->getX())/underPart);
    double d = normal.dot(currB); //mm I guess?
    if(d < 0) d *= -1;
    double cosAlpha = d/R + cos(normal.getAngle());
    double alpha = normal.getAngle() - acos(cosAlpha); // This is the angle of tonearm

    if(alpha < 0) alpha = 6.28319 + alpha;
    if(alpha > 6.28319) alpha = alpha - 6.28319;

    return alpha;
}
