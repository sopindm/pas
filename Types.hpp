#ifndef ASTEROIDS_TYPES_HPP
#define ASTEROIDS_TYPES_HPP

namespace Asteroids
{
  struct Point
  {
    Point(float pX, float pY): x(pX), y(pY) {};

    Point rotate(double angle);

    float x;
    float y;
  };
}
#endif
