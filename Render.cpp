#include <GLES/gl.h>
#include <GLES/glext.h>
#include <algorithm>
#include "Render.hpp"

using namespace Asteroids;

Render::Render(android_app* app):
		_app(app),
		_width(0),
		_height(0),
		_display(EGL_NO_DISPLAY),
		_context(EGL_NO_CONTEXT),
		_surface(EGL_NO_SURFACE)
{
}

float Render::width() const
{
  Point max(fromScreenSpace(Point(_width, _height)));

  return max.x;
}

float Render::height() const
{
  Point max(fromScreenSpace(Point(_width, _height)));

  return max.y;
}

void Render::setupWindow()
{
	if(_display != EGL_NO_DISPLAY)
		return;

	const EGLint attributes[] = {EGL_RENDERABLE_TYPE,
				                 EGL_OPENGL_ES_BIT,
				                 EGL_BLUE_SIZE, 5,
				                 EGL_GREEN_SIZE, 6,
				                 EGL_RED_SIZE, 5,
				                 EGL_SURFACE_TYPE,
				                 EGL_WINDOW_BIT,
				                 EGL_NONE};

	_display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
	eglInitialize(_display, NULL, NULL);

	EGLConfig config;
	EGLint numConfigs;
	eglChooseConfig(_display, attributes, &config, 1, &numConfigs);

	EGLint format;
	eglGetConfigAttrib(_display, config, EGL_NATIVE_VISUAL_ID, &format);
	ANativeWindow_setBuffersGeometry(_app->window, 0, 0, format);

	_surface = eglCreateWindowSurface(_display, config, _app->window, NULL);
	_context = eglCreateContext(_display, config, EGL_NO_CONTEXT, NULL);

	eglMakeCurrent(_display, _surface, _surface, _context);
	eglQuerySurface(_display, _surface, EGL_WIDTH, &_width);
	eglQuerySurface(_display, _surface, EGL_HEIGHT, &_height);
}

void Render::setup()
{
	setupWindow();

  glViewport(0, 0, _width, _height);

  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity ();

  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();

  glBlendFunc(GL_ZERO, GL_ONE);

  glEnableClientState(GL_VERTEX_ARRAY);
}

void Render::release()
{
	if(_display == EGL_NO_DISPLAY)
		return;

	eglMakeCurrent(_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);

	if(_context != EGL_NO_CONTEXT)
	{
		eglDestroyContext(_display, _context);
		_context = EGL_NO_CONTEXT;
	}

	if(_surface != EGL_NO_SURFACE)
	{
		eglDestroySurface(_display, _surface);
		_surface = EGL_NO_SURFACE;
	}

	eglTerminate(_display);
	_display = EGL_NO_DISPLAY;
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
  case GRAY:
    ret.r = 0.6;
    ret.g = 0.6;
    ret.b = 0.6;
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
  glColor4f(rgb.r, rgb.g, rgb.b, 1);
}

void Render::bind()
{
}

void Render::unbind()
{
  eglSwapBuffers(_display, _surface);
}

Point Render::toGLSpace(Point point) const
{
  float size = static_cast<float>(std::min(_width, _height));

  float identity = size / screenSize * 2;

  return Point(point.x * identity / _width, point.y * identity / _height);
}

Point Render::fromScreenSpace(Point point) const
{
  float xSize = static_cast<float>(_width);
  float ySize = static_cast<float>(_height);

  float size = std::min(xSize, ySize);

  float identity = size / screenSize;

  return Point((point.x - xSize / 2) / identity,
	       (point.y - ySize /2) / identity);
}

void drawBuffer(GLenum mode, void* buffer, size_t size)
{
	glVertexPointer(3, GL_FLOAT, 0, buffer);
	//glEnableVertexAttribArray(0);
	glDrawArrays(mode, 0, size);
}

void Render::drawLine(Color color, Point p1, Point p2)
{
  setColor(color);

  p1 = toGLSpace(p1);
  p2 = toGLSpace(p2);

  GLfloat vertices[] = {p1.x, p1.y, -1, p2.x, p2.y, -1};
  drawBuffer(GL_LINES, vertices, 2);
}

void Render::drawTriangle(Color color, Point p1, Point p2, Point p3)
{
  setColor(color);

  p1 = toGLSpace(p1);
  p2 = toGLSpace(p2);
  p3 = toGLSpace(p3);

  GLfloat vertices[] = {p1.x, p1.y, -1, p2.x, p2.y, -1, p3.x, p3.y, -1};
  drawBuffer(GL_TRIANGLES, vertices, 3);
}

void Render::drawQuad(Color color, Point p1, Point p2, Point p3, Point p4)
{
  drawTriangle(color, p1, p2, p3);
  drawTriangle(color, p1, p3, p4);
}

void Render::pushPoint(const Point& point, std::vector<float>& vertices)
{
	Point screenPoint = toGLSpace(point);
	vertices.push_back(screenPoint.x);
	vertices.push_back(screenPoint.y);
	vertices.push_back(-1);
}

void Render::drawNAngle(Color color, const std::vector<Point>& vertices)
{
  setColor(color);

  std::vector<float> screenVertices;
  for(int i=1;i<vertices.size()-1;i++)
  {
	pushPoint(vertices[0], screenVertices);
	pushPoint(vertices[i], screenVertices);
	pushPoint(vertices[i+1], screenVertices);
  }

  drawBuffer(GL_TRIANGLES, &screenVertices[0], (vertices.size() - 2) * 3);
}
