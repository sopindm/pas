#include "Logger.hpp"
#include "EventLoop.hpp"
#include "Window.hpp"

using namespace Asteroids;

Window::Window(android_app* app): _app(app),
							      _enabled(false),
							      _quit(false)
{
	_app->onAppCmd = activityCallback;
	_app->onInputEvent = inputCallback;
	_app->userData = pack();
}

void Window::release()
{
}

void* Window::pack()
{
	return this;
}

Window* Window::unpack(void* data)
{
	return reinterpret_cast<Window*>(data);
}

int Window::width() const
{
  return ANativeWindow_getWidth(_app->window);
}

int Window::height() const
{
  return ANativeWindow_getHeight(_app->window);
}

void Window::setup(EventLoop* loop)
{
  _loop = loop;
}

void Window::handleTap(AInputEvent* event)
{
	if(AMotionEvent_getAction(event) != AMOTION_EVENT_ACTION_DOWN)
		return;

	int x = AMotionEvent_getX(event, 0);
	int y = height() - AMotionEvent_getY(event, 0);

	return _loop->onTap(x, y);
}

void Window::handleKey(int key)
{
}

bool Window::handleEvent()
{
	int32_t result;
	int32_t events;
	android_poll_source* source;

	while(ALooper_pollAll(_enabled ? 0 : -1, NULL, &events, (void**)&source) >= 0)
	{
		if(source != NULL)
		{
			source->process(_app, source);
		}
		if(_app->destroyRequested)
		{
			return true;
		}
	}

	if(_enabled)
	{
		_loop->onPaint();
	}

	return false;
}

void Window::activate()
{
	if(!_enabled && _app->window != NULL)
	{
		_enabled = true;
		_loop->onActivate();
	}
}

void Window::deactivate()
{
	if(_enabled)
	{
		_enabled = false;
		_loop->onDeactivate();
	}
}

void Window::processEvent(int32_t event)
{
	switch(event)
	{
	case APP_CMD_CONFIG_CHANGED:
		_loop->onConfigChanged();
		break;
	case APP_CMD_INIT_WINDOW:
		_loop->onCreateWindow();
		break;
	case APP_CMD_DESTROY:
		_loop->onDestroy();
		break;
	case APP_CMD_GAINED_FOCUS:
		activate();
		_loop->onGainFocus();
		break;
	case APP_CMD_LOST_FOCUS:
		_loop->onLostFocus();
		deactivate();
		break;
	case APP_CMD_LOW_MEMORY:
		_loop->onLowMemory();
		break;
	case APP_CMD_PAUSE:
		_loop->onPause();
		deactivate();
		break;
	case APP_CMD_RESUME:
		activate();
		_loop->onResume();
		break;
	case APP_CMD_SAVE_STATE:
		_loop->onSaveState(&_app->savedState, &_app->savedStateSize);
		break;
	case APP_CMD_START:
		_loop->onStart();
		break;
	case APP_CMD_STOP:
		_loop->onStop();
		break;
	case APP_CMD_TERM_WINDOW:
		_loop->onDestroyWindow();
		deactivate();
		break;
	}
}

void Window::processInput(AInputEvent* event)
{
	if(AInputEvent_getType(event) != AINPUT_EVENT_TYPE_MOTION)
		return;

	if(AInputEvent_getSource(event) != AINPUT_SOURCE_TOUCHSCREEN)
		return;

	handleTap(event);
}

void Window::activityCallback(android_app* app, int32_t command)
{
	Window* window(Window::unpack(app->userData));
	window->processEvent(command);
}

int32_t Window::inputCallback(android_app* app, AInputEvent* event)
{
	Window* window = Window::unpack(app->userData);
	window->processInput(event);

	return 0;
}



