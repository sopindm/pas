#include <GL/glew.h>
#include <GL/glfw.h>
#include "Render.hpp"

using namespace Asteroids;

Render::Render(int width, int height): _width(width), _height(height)
{
}

void Render::setup()
{
  glewInit();
  glViewport(0, 0, _width, _height);

  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity ();

  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();

  glBlendFunc(GL_ZERO, GL_ONE);
}

void Render::release()
{
}

void Render::resize(int newWidth, int newHeight)
{
  _width = newWidth;
  _height = newHeight;

  glViewport(0, 0, _width, _height);
}

void Render::clear(Color color)
{
  _RGBColor rgb = toRGB(color);

  glClearColor(rgb.r, rgb.g, rgb.b, 1);
  glClear(GL_COLOR_BUFFER_BIT);
}

Render::_RGBColor Render::toRGB(Color color)
{
  _RGBColor ret = {0, 0, 0};

  switch(color)
  {
  case BLACK:
    return ret;
  case WHITE:
    ret.r = 1;
    ret.g = 1;
    ret.b = 1;
    return ret;
  case RED:
    ret.r = 1;
    return ret;
  case GREEN:
    ret.g = 1;
    return ret;
  case BLUE:
    ret.b = 1;
    return ret;
  }
}

void Render::setColor(Color color)
{
  _RGBColor rgb = toRGB(color);
  glColor3f(rgb.r, rgb.g, rgb.b);
}

void Render::bind()
{
}

void Render::unbind()
{
  glfwSwapBuffers();
}

Point Render::toScreenSpace(Point point)
{
  int size = std::min(_width, _height);

  float identity = static_cast<float>(size) / screenSize * 2;

  return Point(point.x * identity / _width, point.y * identity / _height);
}

void Render::setVertex(Point point)
{
  point = toScreenSpace(point);

  glVertex3f(point.x, point.y, -1);
}

void Render::drawLine(Color color, Point p1, Point p2)
{
  glBegin(GL_LINES);

  setColor(color);

  setVertex(p1);
  setVertex(p2);

  glEnd();
}

void Render::drawTriangle(Color color, Point p1, Point p2, Point p3)
{
  glBegin(GL_TRIANGLES);

  setColor(color);

  setVertex(p1);
  setVertex(p2);
  setVertex(p3);

  glEnd();
}

void Render::drawQuad(Color color, Point p1, Point p2, Point p3, Point p4)
{
  glBegin(GL_QUADS);

  setColor(color);

  setVertex(p1);
  setVertex(p2);
  setVertex(p3);
  setVertex(p4);

  glEnd();
}

void Render::drawNAngle(Color color, std::vector<Point> vertices)
{
  setColor(color);

  glBegin(GL_TRIANGLES);

  for(int i=0;i<vertices.size()-2;i++)
  {
    setVertex(vertices[0]);
    setVertex(vertices[i+1]);
    setVertex(vertices[i+2]);
  }

  glEnd();
}
