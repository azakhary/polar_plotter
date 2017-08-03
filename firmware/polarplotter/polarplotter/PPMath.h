/*
  Point.h - Polar Plotter Firmware
  Created by Avetis Zakhayan, 2017
  Released into the public domain.
*/

#ifndef PPMath_h
#define PPMath_h

#include "Arduino.h"
#include "Point.h"

class PPMath
{
public:

	int TURN_TABLE_CW = 6;
	int TURN_TABLE_CCW = 7;
	int TONE_ARM_CW = 8;
	int TONE_ARM_CCW = 9;

	double turnTableRotation;
	double toneArmRotation;
	double R;
	Point& currentPoint;

	double ttBuffer;
	double taBuffer;

	PPMath();

	void PPMath::setup();
	double moveTo(double xTo, double yTo);
	double getAlphaFromAB(Point* currA, Point* currB);
	void PPMath::moveTurntableBy(double steps);
	void PPMath::moveArmBy(double steps);
};

#endif
