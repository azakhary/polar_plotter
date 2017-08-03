/*
  Point.cpp - Point Utility for Polar plotter
  Created by Avetis Zakhayan, 2017
  Released into the public domain.
*/

#include "Arduino.h"
#include "Point.h"

Point::Point(double x, double y)
{
    this->r = sqrt(x*x+y*y);
    this->a = atan2(y, x);
}

Point::Point(Point* point)
{
    this->r = point->r;
    this->a = point->a;
}

double Point::getAngle() 
{
  return a;
}

double Point::getRadius() 
{
	return r;
}

double Point::getX() 
{
  return cos(a)*r;
}

double Point::getY() 
{
  return sin(a)*r;
}

void Point::setAngle(double alpha)
{
	a = alpha;
}

double Point::dot(Point* point)
{
	return r * point->r * cos(a - point->a);
}

double Point::len()
{
	return r;
}

Point* Point::transform(double alphaBy)
{
	a += alphaBy;
  return this;
}