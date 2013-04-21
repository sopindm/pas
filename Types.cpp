#include <cmath>
#include "Types.hpp"

using namespace Asteroids;

Point Point::rotate(double angle, Point center) const
{
  Point point(x - center.x, y - center.y);

  return Point(center.x + point.x * cos(angle) - point.y * sin(angle), 
	       center.y + point.y * cos(angle) + point.x * sin(angle));
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

double Point::angle(Point base)
{
  Point point(*this - base);
  return atan2(-point.x, point.y);
}
