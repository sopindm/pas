#ifndef ASTEROIDS_TYPES_HPP
#define ASTEROIDS_TYPES_HPP

namespace Asteroids
{
  struct Point
  {
    Point(): x(0), y(0) {};
    Point(float pX, float pY): x(pX), y(pY) {};

    float magnitude() const;

    Point operator+(const Point& point) const;
    void operator+=(const Point& point);

    Point operator-(const Point& point) const;
    void operator-=(const Point& point);

    Point operator*(double x) const;

    Point rotate(double angle) const;
    Point rotate(double angle, Point center) const;

    double angle(); //Angle to Y axis
    double angle(Point base); 

    float x;
    float y;
  };

  typedef Point Vector;

  class Line
  {
  public:
    Line();
    Line(Point p1, Point p2);
    
    bool intersect(const Line& line) const;

  private:
    Point _start;
    Point _finish;

  };
}
#endif
