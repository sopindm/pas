#include "Objects.hpp"

using namespace Asteroids;

Object::Object(): _isPersistent(true), 
		  _lifeTime(-1),
		  _center(Point(0, 0)),
		  _direction(0),
		  _speed(0)
{
}

bool Object::isPersistent() const
{
  return _isPersistent;
}

void Object::setPersistent(bool value)
{
  _isPersistent = value;
}

double Object::lifeTime() const
{
  return _lifeTime;
}

void Object::setLifeTime(double lifeTime)
{
  _lifeTime = lifeTime;
}

Point Object::center() const
{
  return _center;
}

void Object::setCenter(Point center)
{
  _center = center;
}

double Object::direction() const
{
  return _direction;
}

void Object::setDirection(double direction)
{
  _direction = direction;
}

double Object::speed() const
{
  return _speed;
}

void Object::setSpeed(double speed)
{
  _speed = speed;
}

bool Object::update(const Timer& timer, int width, int height)
{
  if(!_isPersistent)
    _lifeTime -= timer.elapsed();

  _center += (Vector(0, 1) * _speed * timer.elapsed()).rotate(_direction, Point(0, 0));

  if(_center.x > width)
    _center.x = -width + (_center.x - width);
  if(_center.x < -width)
    _center.x = width + (_center.x + width);

  if(_center.y > height)
    _center.y = -height + (_center.y - height);
  if(_center.y < -height)
    _center.y = height + (_center.y + height);

  return _lifeTime >= 0;
}

Ship::Ship(): _direction(0)
{
}

Point Ship::center() const
{
  return Point(0,1);
}

Point Ship::nose() const
{
  return Point(0, 4).rotate(_direction, center());
}

double Ship::direction() const
{
  return _direction;
}

void Ship::setDirection(double direction)
{
  _direction = direction;
}

void Ship::draw(Render& render)
{
  render.drawQuad(Render::WHITE, 
		  Point(-1, -1).rotate(_direction, center()), 
		  Point(-1, 1).rotate(_direction, center()), 
		  Point(1, 1).rotate(_direction, center()), 
		  Point(1, -1).rotate(_direction, center()));

  render.drawTriangle(Render::WHITE, 
		      Point(1, 1).rotate(_direction, center()), 
		      Point(0, 4).rotate(_direction, center()), 
		      Point(-1, 1).rotate(_direction, center()));
}

Shoot::Shoot()
{
  setPersistent(false);
}

Shoot::Shoot(const Ship& ship)
{
  setPersistent(false);
  setLifeTime(1);
  setCenter(ship.nose());
  setDirection(ship.direction());
  setSpeed(60);
}

void Shoot::draw(Render& render)
{
  render.drawLine(Render::RED, center(), center() + Vector(0, 1).rotate(direction(), Point(0, 0)));
}

/*
void Shoot::update(const Timer& timer, int width, int height)
{
  Object::update(timer, width, height);

  _lifeTime -= timer.elapsed();
  _point = _point + (Vector(0, 60) * timer.elapsed()).rotate(_direction, Point(0, 0));

  if(_point.x > width)
    _point.x = -width + (_point.x - width);
  if(_point.x < -width)
    _point.x = width + (_point.x + width);

  if(_point.y > height)
    _point.y = -height + (_point.y - height);
  if(_point.y < -height)
    _point.y = height + (_point.y + height);
}
*/

