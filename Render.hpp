#ifndef ASTEROIDS_RENDER_HPP
#define ASTEROIDS_RENDER_HPP

#include <vector>
#include "Types.hpp"

namespace Asteroids
{
  class Render
  {
  public:
    Render(int screenWidth, int screenHeight);
  
    float width() const;
    float height() const;

    void setup();
    void release();

    void resize(int newWidth, int newHeight);

    enum Color
    {
      BLACK,
      WHITE,
      RED,
      GREEN,
      BLUE
    };

    void bind();
    void unbind();

    void clear(Color color);

    void drawLine(Color color, Point p1, Point p2);
    void drawTriangle(Color color, Point p1, Point p2, Point p3);
    void drawQuad(Color color, Point p1, Point p2, Point p3, Point p4);
  
    void drawNAngle(Color color, std::vector<Point> vertices);

    static const int screenSize = 120;

    Point fromScreenSpace(Point p) const;//Converts point from screen space ([0;width], [0;height]) to game space ((-screenSize, screenSize

  private:
    Point toGLSpace(Point p) const;

    void setVertex(Point point);

    int _width;
    int _height;

    struct _RGBColor
    {
      float r;
      float g;
      float b;
    };
  
    _RGBColor toRGB(Color color);
    void setColor(Color color);
  };
}
#endif
