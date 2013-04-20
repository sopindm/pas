#include <GL/glfw.h>
#include <cmath>
#include "EventLoop.hpp"

using namespace Asteroids;

EventLoop* _loop;

EventLoop::EventLoop()
{
  _loop = this;
  _done = false;
}

EventLoop::~EventLoop()
{
  _render->release();
  glfwTerminate();
}

void EventLoop::setup()
{
  _window.setup(this);

  _render.reset(new Render(_window.width(), _window.height()));
  _render->setup();
}

void EventLoop::onClick(int x, int y)
{
  Point click(_render->fromScreenSpace(Point(x, y)));

  click.y = click.y - _ship.center().y;
  click.x = click.x - _ship.center().x;

  double angle = atan2(-click.x, click.y); //In default state we a rotated at 90 degrees, so we need to rotate 90 degrees back
  _ship.setAngle(angle);
}

void EventLoop::onPaint()
{
  _render->bind();

  _render->clear(Render::WHITE);
  
  _render->drawQuad(Render::BLACK, 
		    Point(-_render->width(), -_render->height()),
		    Point(-_render->width(), _render->height()),
		    Point(_render->width(), _render->height()), 
		    Point(_render->width(), -_render->height()));

  _ship.draw(*_render);
  _render->unbind();
}

void EventLoop::onExit()
{
  _done = true;
}

void EventLoop::run()
{
  while(!_done)
  {
    _window.handleEvent();
  }
}
