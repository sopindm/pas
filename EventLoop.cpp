#include "Logger.hpp"
#include "EventLoop.hpp"

using namespace Asteroids;

EventLoop::EventLoop(android_app* app): _window(app), _render(app), _active(false)
{
}

EventLoop::~EventLoop()
{
  _render.release();
  _window.release();
}

void EventLoop::setup()
{
  _window.setup(this);
}

void EventLoop::onExit()
{
  _window.destroy();
}

void EventLoop::onTap(int x, int y)
{
  Point tap(_render.fromScreenSpace(Point(x, y)));
  _game.tap(tap);
}

void EventLoop::onGravity(float x, float y)
{
  _game.gravity(Vector(x, y));
}

void EventLoop::onPaint()
{
  _render.bind();

  if(_active && _timer.elapsed() >= 0.012)
  {
    _render.clear(Render::BLACK);

    _game.update(_timer, _render.width(), _render.height());
    _game.draw(_render);

    _timer.reset();
  }

  _render.unbind();
}

void EventLoop::onActivate()
{
	_game.setup(_render->width(), _render->height());

	_render.setup();
	
	if(_timer.isPaused())
	  _timer.resume();
	else _timer.reset();

	_active = true;	
}

void EventLoop::onDeactivate()
{
	_active = false;
	_render.release();
	_timer.pause();
}

void EventLoop::run()
{
	app_dummy();

	while(true)
	{
		if(_window.handleEvent())
			break;
	}
}
