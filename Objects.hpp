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

    bool isPersistent() const;
    double lifeTime() const;

    Point center() const;
    //virtual double radius() const = 0;

    double direction() const;
    double speed() const;

    virtual bool update(const Timer& timer, int width, int height);

  protected:
    void setPersistent(bool value);
    void setLifeTime(double newLifeTime);

    void setCenter(Point newCenter);

    void setDirection(double newDirection);
    void setSpeed(double newSpeed);

  private:
    bool _isPersistent;
    double _lifeTime;

    Point _center;

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

  class Shoot: public Object
  {
  public:
    Shoot();
    Shoot(const Ship& ship);

    void draw(Render& render);

  private:
    static const float _lifeTime = 1;
    static const float _speed = 60;

  };
}
#endif
