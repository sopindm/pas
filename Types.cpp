#include <cmath>
#include "Types.hpp"

using namespace Asteroids;

Point Point::rotate(double angle, Point center) const
{
  Point point(x - center.x, y - center.y);

  return Point(center.x + point.x * cos(angle) - point.y * sin(angle), 
	       center.y + point.y * cos(angle) + point.x * sin(angle));
}
