#ifndef ASTEROIDS_RENDER_HPP
#define ASTEROIDS_RENDER_HPP

#include <vector>
#include <android_native_app_glue.h>
#include <EGL/egl.h>
#include "Geometry.hpp"

namespace Asteroids
{
  class Render
  {
  public:
    Render(android_app* app);
  
    float width() const;
    float height() const;

    void setup();
    void release();

    void resize(int newWidth, int newHeight);

    enum Color
    {
      BLACK,
      GRAY,
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
  
    void drawNAngle(Color color, const std::vector<Point>& vertices);

    static const int screenSize = 60;

    Point fromScreenSpace(Point p) const;//Converts point from screen space ([0;width], [0;height]) to game space ((-screenSize, screenSize

  private:
    void setupWindow();

    Point toGLSpace(Point p) const;

    void setVertex(Point point);

    void pushPoint(const Point& point, std::vector<float>& vertices);

    android_app* _app;

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

    EGLDisplay _display;
    EGLSurface _surface;
    EGLContext _context;

  };
}
#endif
