#include <cmath>
#include "Types.hpp"

using namespace Asteroids;

float Point::magnitude() const
{
  return sqrt(x * x + y * y);
}

Point Point::operator+(const Point& point) const
{
  return Point(x + point.x, y + point.y);
}

void Point::operator+=(const Point& point) 
{
  x += point.x;
  y += point.y;
}

void Point::operator-=(const Point& point) 
{
  x -= point.x;
  y -= point.y;
}

Point Point::operator-(const Point& point) const
{
  return Point(x - point.x, y - point.y);
}

Point Point::operator*(double value) const
{
  return Point(x * value, y * value);
}

double Point::angle()
{
  return atan2(-x, y);
}

double Point::angle(Point base)
{
  return (*this - base).angle();
}

Point Point::rotate(double angle) const
{
  return Point(x * cos(angle) - y * sin(angle), 
	       y * cos(angle) + x * sin(angle));
}

Point Point::rotate(double angle, Point center) const
{
  return (*this - center).rotate(angle);
}
