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

  class Ship
  {
  public:
    Ship();

    Point center() const;
    Point nose() const;

    double direction() const;
    void setDirection(double newAngle);

    void draw(Render& render);

  private:
    double _direction;
    
  };

  class Shoot: public Object
  {
  public:
    Shoot();
    Shoot(const Ship& ship);

    //void update(const Timer& timer, int width, int height);
    void draw(Render& render);

  };
}
#endif
