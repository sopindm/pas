#ifndef ASTEROIDS_OBJECTS_HPP
#define ASTEROIDS_OBJECTS_HPP

#include "Types.hpp"
#include "Render.hpp"
#include "Timer.hpp"

namespace Asteroids
{
  class Object
  {
  public:
    Object();

    double lifeTime() const;

    Point center() const;
    double radius() const;

    double direction() const;
    double speed() const;

    virtual bool update(const Timer& timer, int width, int height);
    virtual bool intersect(const Object& object, const Timer& timer, bool continuous = false) const;

    virtual void draw(Render& render) = 0;

  protected:
    void setLifeTime(double newLifeTime);

    void setCenter(Point center);
    void setRadius(double radius);

    void setDirection(double newDirection);
    void setSpeed(double newSpeed);

  private:
    double _lifeTime;

    Point _center;
    double _radius;

    double _direction;
    double _speed;

  };

  class Ship: public Object
  {
  public:
    Ship();

    Point nose() const;

    void setDirection(double newDirection);
    void setSpeed(double newSpeed);

    void draw(Render& render);

  };

  class Asteroid: public Object
  {
  public:
    Asteroid();
    Asteroid(int width, int height);

    void draw(Render& render);

    int lines() const;
    Line line(int index) const;

  private:
    void generatePosition(int width, int height);
    void generateSpeed();
    void generateForm();

    std::vector<Point> _points;

  };

  class Shoot: public Object
  {
  public:
    Shoot();
    Shoot(const Ship& ship);

    void draw(Render& render);

    bool intersect(const Asteroid& asteroid, const Timer& timer) const;

  private:
    static const float _lifeTime = 1;
    static const float _speed = 60;

  };
}
#endif
