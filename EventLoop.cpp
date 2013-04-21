#include <GL/glfw.h>
#include "EventLoop.hpp"

using namespace Asteroids;

EventLoop::EventLoop()
{
  _active = true;
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

  _game.setup(_render->width(), _render->height());

  _timer.start();
}

void EventLoop::onDeactivation()
{
  _timer.pause();
  _active = false;
}

void EventLoop::onActivation()
{
  _timer.resume();
  _active = true;
}

void EventLoop::onTap(int x, int y)
{
  Point tap(_render->fromScreenSpace(Point(x, y)));
  _game.tap(tap);
}

void EventLoop::onGravity(float x, float y)
{
  _game.gravity(Vector(x, y));
}

void EventLoop::onPaint()
{
  _render->bind();

  if(_active && _timer.elapsed() >= 0.012)
  {
    _render->clear(Render::BLACK);

    _game.update(_timer, _render->width(), _render->height());
    _game.draw(*_render);

    _timer.reset();
  }

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
