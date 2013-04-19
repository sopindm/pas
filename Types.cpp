#include <cmath>
#include "Types.hpp"

using namespace Asteroids;

Point Point::rotate(double angle)
{
  return Point(x * cos(angle) - y * sin(angle), y * cos(angle) + x * sin(angle));
}
