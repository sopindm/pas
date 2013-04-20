#include "Objects.hpp"

using namespace Asteroids;

Ship::Ship(): _angle(0)
{
}

Point Ship::center() const
{
  return Point(0,1);
}

void Ship::setAngle(double newAngle)
{
  _angle = newAngle;
}

void Ship::draw(Render& render)
{
  render.drawQuad(Render::WHITE, 
		  Point(-1, -1).rotate(_angle, center()), 
		  Point(-1, 1).rotate(_angle, center()), 
		  Point(1, 1).rotate(_angle, center()), 
		  Point(1, -1).rotate(_angle, center()));

  render.drawTriangle(Render::WHITE, 
		      Point(1, 1).rotate(_angle, center()), 
		      Point(0, 4).rotate(_angle, center()), 
		      Point(-1, 1).rotate(_angle, center()));
}
