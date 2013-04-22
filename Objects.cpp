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

bool Ship::intersect(const Asteroid& asteroid, const Timer& timer) const
{
  if(!Object::intersect(asteroid, timer))
    return false;

  double deltaR = speed() * timer.elapsed();

  Point nose = center() + Vector(0, 3 + deltaR).rotate(direction());
  Point middleLeft = center() + Vector(-1, deltaR).rotate(direction());
  Point middleRight = center() + Vector(1, deltaR).rotate(direction());
  Point backLeft = center() + Vector(-1, -2).rotate(direction());
  Point backRight = center() + Vector(1, -2).rotate(direction());

  return asteroid.intersectLine(Line(nose, middleLeft)) ||
    asteroid.intersectLine(Line(nose, middleRight)) ||
    asteroid.intersectLine(Line(middleLeft, backLeft)) ||
    asteroid.intersectLine(Line(middleRight, backRight)) ||
    asteroid.intersectLine(Line(backLeft, backRight));
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

  Point nose = center() + Vector(0, 1 + speed() * timer.elapsed()).rotate(direction());

  Line shoot(center(), nose);

  return asteroid.intersectLine(shoot);
}

Asteroid::Asteroid(): _size(0)
{
}

Asteroid::Asteroid(int width, int height): _size(1)
{
  generatePosition(-width, width, -height, height);
  generateSpeed(defaultMinSpeed, defaultMaxSpeed, 0, 2 * PI);
  generateForm(defaultMinRadius, defaultMaxRadius);
}

void Asteroid::generatePosition(float minX, float maxX, float minY, float maxY, bool freeCenter)
{
  Point center(Random::nextFloat(minX, maxX), Random::nextFloat(minY, maxY));

  if(freeCenter && center.magnitude() < 20)
    center = center * (20.0 / center.magnitude());

  setCenter(center);
}

void Asteroid::generateSpeed(float minSpeed, float maxSpeed, float minAngle, float maxAngle)
{
  setDirection(Random::nextFloat(minAngle, maxAngle));
  setSpeed(Random::nextFloat(minSpeed, maxSpeed));
}

void Asteroid::generateForm(float minRadius, float maxRadius)
{
  _points.clear();
  int n = Random::nextInt(7, 15);

  float radius = Random::nextFloat(minRadius, maxRadius);
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
  std::vector<Point> points(0);

  for(int i=0;i<_points.size();i++)
    points.push_back(center() + _points[i]);

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

bool Asteroid::intersectLine(const Line& line) const
{
  for(int i=0;i<lines();i++)
  {
    if(line.intersect(this->line(i)))
      return true;
  }

  return false;
}

int Asteroid::size() const
{
  return _size;
}

void Asteroid::divide(std::vector<Asteroid>& collection)
{
  int pieces = Random::nextInt(divisionMinPieces, divisionMaxPieces);

  float startAngle = Random::nextFloat(0, 2 * PI);
  float dAngle = .25 / pieces * 2 * PI; //angle dispersion
  float dRadius = radius() * 0.03; //radius dispersion

  for(int i=0;i<pieces;i++)
  {
    float angle = static_cast<float>(i) / pieces * 2 * PI;
    angle += Random::nextFloat(-dAngle, dAngle);

    float radius = this->radius() * 0.3 * (1 + Random::nextFloat(-dRadius, dRadius));

    Asteroid newAsteroid;
    newAsteroid._size = _size - 1;

    Point position = center() + Vector(0, radius).rotate(angle);
    newAsteroid.generatePosition(position.x, position.x, position.y, position.y);
    newAsteroid.generateSpeed(defaultMinSpeed, defaultMaxSpeed, angle - dAngle, angle + dAngle);
    newAsteroid.generateForm(radius, radius);

    collection.push_back(newAsteroid);
  }


}
