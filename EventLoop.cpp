//#include <cmath>
#include <unistd.h>
#include "Logger.hpp"
#include "EventLoop.hpp"

using namespace Asteroids;

EventLoop::EventLoop(android_app* app): _window(app), _render(app)
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

void EventLoop::onTap(int x, int y)
{
  Point click(_render.fromScreenSpace(Point(x, y)));

  click.y = click.y - _ship.center().y;
  click.x = click.x - _ship.center().x;

  double angle = atan2(-click.x, click.y); //In default state we a rotated at 90 degrees, so we need to rotate 90 degrees back
  _ship.setAngle(angle);
}

void EventLoop::onPaint()
{
  _render.bind();

  _render.clear(Render::WHITE);
  
  _render.drawQuad(Render::BLACK,
		    Point(-_render.width(), -_render.height()),
		    Point(-_render.width(), _render.height()),
		    Point(_render.width(), _render.height()),
		    Point(_render.width(), -_render.height()));

  _ship.draw(_render);
  _render.unbind();
}

void EventLoop::onActivate()
{
	_render.setup();
}

void EventLoop::onDeactivate()
{
	_render.release();
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
