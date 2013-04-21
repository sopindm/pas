#include "Random.hpp"
#include "Objects.hpp"

using namespace Asteroids;

const double PI = 3.14159;

Object::Object(): _lifeTime(-1),
		  _center(Point(0, 0)),
		  _radius(0),
		  _direction(0),
		  _speed(0)
{
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

double Object::radius() const
{
  return _radius;
}

void Object::setRadius(double radius)
{
  _radius = radius;
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

bool Object::intersect(const Object& object, const Timer& timer, bool continuous) const
{
  double range = (center() - object.center()).magnitude();

  double minRange = radius() + object.radius();
  if(continuous)
    minRange += speed() * timer.elapsed();

  return range <= minRange;
}

bool Object::update(const Timer& timer, int width, int height)
{
  if(_lifeTime >= 0)
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
  setLifeTime(-1);
  setCenter(Point(0, 1));
  setRadius(3);
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
}

Shoot::Shoot(const Ship& ship)
{
  setLifeTime(_lifeTime);
  setCenter(ship.nose());
  setRadius(1);
  setDirection(ship.direction());
  setSpeed(_speed);
}

void Shoot::draw(Render& render)
{
  render.drawLine(Render::RED, center(), center() + Vector(0, 1).rotate(direction()));
}

bool Shoot::intersect(const Asteroid& asteroid, const Timer& timer) const
{
  if(!Object::intersect(asteroid, timer, true))
    return false;

  Point nose = center() + (Vector(0, 1) * (1 + speed() * timer.elapsed())).rotate(direction());

  Line shoot(center(), nose);

  for(int i=0;i<asteroid.lines();i++)
  {
    if(shoot.intersect(asteroid.line(i)))
      return true;
  }

  return false;
}

Asteroid::Asteroid()
{
}

Asteroid::Asteroid(int width, int height)
{
  setLifeTime(5);

  generatePosition(width, height);
  generateSpeed();
  generateForm();
}

void Asteroid::generatePosition(int width, int height)
{
  //Generating new asteroid position. Leaving screen center empty (for the ship)

  Point center(Random::nextFloat(-width, width), Random::nextFloat(-height, height));

  if(center.magnitude() < 20)
    center = Point(center.x / center.magnitude() * 20, center.y / center.magnitude() * 20);

  setCenter(center);
}

void Asteroid::generateSpeed()
{
  setDirection(Random::nextFloat(2 * PI));
  setSpeed(Random::nextFloat(8, 10));
}

void Asteroid::generateForm()
{
  _points.clear();
  int n = Random::nextInt(7, 15);

  float radius = Random::nextFloat(5, 8);
  setRadius(radius);

  float dAngle = .25 / n * 2 * PI; //angle dispersion
  float dRadius = radius * 0.1; //radius dispersion

  for(int i=0;i<n;i++)
  {
    float angle = static_cast<float>(i) / n * 2 * PI;
    angle += Random::nextFloat(-dAngle, dAngle);

    _points.push_back(Point(0, radius + Random::nextFloat(-dRadius, dRadius)).rotate(angle));
  }
}

void Asteroid::draw(Render& render)
{
  std::vector<Point> points(_points);

  for(int i=0;i<points.size();i++)
    points[i] += center();

  render.drawNAngle(Render::GRAY, points);
}

int Asteroid::lines() const
{
  return _points.size();
}

Line Asteroid::line(int index) const
{
  Point start(center() + _points[index]);

  index++;
  if(index == _points.size())
    index = 0;

  Point finish(center() + _points[index]);

  return Line(start, finish);
}
