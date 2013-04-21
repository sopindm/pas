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

  _center += (Vector(0, 1) * _speed * timer.elapsed()).rotate(_direction);

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

Ship::Ship(): Object()
{
  setPersistent(true);
  setLifeTime(-1);
  setCenter(Point(0, 1));
  setDirection(0);
  setSpeed(0);
}

Point Ship::nose() const
{
  return center() + Vector(0, 3).rotate(direction());
}

void Ship::setDirection(double direction)
{
  Object::setDirection(direction);
}

void Ship::setSpeed(double speed)
{
  Object::setSpeed(speed);
}

void Ship::draw(Render& render)
{
  render.drawQuad(Render::WHITE, 
		  center() + Vector(-1, -2).rotate(direction()),
		  center() + Vector(-1, 0).rotate(direction()),
		  center() + Vector(1, 0).rotate(direction()),
		  center() + Vector(1, -2).rotate(direction()));

  render.drawTriangle(Render::WHITE, 
		      center() + Vector(1, 0).rotate(direction()),
		      center() + Vector(0, 3).rotate(direction()),
		      center() + Vector(-1, 0).rotate(direction()));
}

Shoot::Shoot()
{
  setPersistent(false);
}

Shoot::Shoot(const Ship& ship)
{
  setPersistent(false);
  setLifeTime(_lifeTime);
  setCenter(ship.nose());
  setDirection(ship.direction());
  setSpeed(_speed);
}

void Shoot::draw(Render& render)
{
  render.drawLine(Render::RED, center(), center() + Vector(0, 1).rotate(direction()));
}


