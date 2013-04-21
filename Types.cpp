#include <cmath>
#include <algorithm>
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

Line::Line(): _start(0, 0), 
	      _finish(0,0)
{
}

Line::Line(Point p1, Point p2): _start(p1), _finish(p2)
{
}

bool Line::intersect(const Line& line) const
{
  Vector v1 = _finish - _start;
  Vector v2 = line._start - line._finish;

  Point start1 = _start;
  Point start2 = line._start;

  float d = v1.x * v2.y - v1.y * v2.x;

  if(fabs(d) < 1e-2)
    return false;

  double d1 = ((start2.x - start1.x) * v2.y  - v2.x * (start2.y - start1.y)) / d;
  if(d1 < -1e-2 || d1 > 1 + 1e-2)
    return false;

  double d2 = (v1.x * (start2.y - start1.y) - v1.y * (start2.x - start1.x)) / d;
  if(d2 < -1e-2 || d2 > 1 + 1e-2)
    return false;

  return true;
}

