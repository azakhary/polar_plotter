/*
  Point.h - Point Utility for Polar plotter
  Created by Avetis Zakhayan, 2017
  Released into the public domain.
*/

#ifndef Point_h
#define Point_h

#include "Arduino.h"

class Point
{
public:
	double r;
	double a;

	Point(double x, double y);
	Point(Point* point);

	double getAngle();
	double getRadius();
	double getX();
	double getY();
	void setAngle(double alpha);
	double dot(Point* point);
	double len();
	Point* transform(double alphaBy);
};

#endif
