#ifndef ASTEROIDS_OBJECTS_HPP
#define ASTEROIDS_OBJECTS_HPP

#include "Types.hpp"
#include "Render.hpp"

namespace Asteroids
{
  class Ship
  {
  public:
    Ship();

    Point center() const;

    double angle() const;
    void setAngle(double newAngle);

    void draw(Render& render);

  private:
    double _angle;
    
  };
}
#endif
