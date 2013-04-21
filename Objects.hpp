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

  class Asteroid: public Object
  {
  public:
    Asteroid();
    Asteroid(int width, int height);

    void draw(Render& render);

    bool intersectLine(const Line& line) const;

    int size() const;//if size = 0 - asteroid destroyed completely, else it divides into pieces
    void divide(std::vector<Asteroid>& collection);

  private:
    int lines() const;
    Line line(int index) const;

    const static float defaultMinSpeed = 8;
    const static float defaultMaxSpeed = 10;

    const static float defaultMinRadius = 5;
    const static float defaultMaxRadius = 8;

    const static int divisionMinPieces = 3;
    const static int divisionMaxPieces = 5;

    void generatePosition(float minX, float maxX, float minY, float maxY, bool freeCenter = true);
    void generateSpeed(float minSpeed, float maxSpeed, float minAngle, float maxAngle);
    void generateForm(float minRadius, float maxRadius);

    int _size;
    std::vector<Point> _points;

  };

  class Ship: public Object
  {
  public:
    Ship();

    Point nose() const;

    void setDirection(double newDirection);
    void setSpeed(double newSpeed);

    void draw(Render& render);
    bool intersect(const Asteroid& asteroid, const Timer& timer) const;

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
