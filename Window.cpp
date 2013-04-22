#include "EventLoop.hpp"
#include "Window.hpp"

using namespace Asteroids;

Window::Window(android_app* app): _app(app),
			          _enabled(false),
				  _quit(false),
				  _sensor(NULL),
				  _sensorPollSource(),
				  _sensorManager(NULL),
				  _sensorEventQueue(NULL),
				  _configuration(app)
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

void Window::handleKey(AInputEvent* event)
{
  if(AKeyEvent_getAction(event) != AKEY_EVENT_ACTION_DOWN)
    return;

  if(AKeyEvent_getKeyCode(event) != AKEYCODE_BACK)
    return;

  _loop->onExit();
}

void Window::handleTap(AInputEvent* event)
{
  if(AMotionEvent_getAction(event) != AMOTION_EVENT_ACTION_DOWN)
    return;

  int x = AMotionEvent_getX(event, 0);
  int y = height() - AMotionEvent_getY(event, 0);

  return _loop->onTap(x, y);
}

void Window::handleGravity(ASensorEvent* event)
{
  const float gravity = ASENSOR_STANDARD_GRAVITY / 2.0;
  const float minX = -1;
  const float maxX = 1;
  const float minY = -1;
  const float maxY = 1;
	
  const float centerX = (minX + maxX) / 2;
  const float centerY = (minY + maxY) / 2;

  float rawX = event->vector.x / gravity;
  if(rawX > maxX)
    rawX = maxX;
  else if (rawX < minX)
    rawX = minX;

  float rawY = event->vector.y / gravity;
  if(rawY > maxY)
    rawY = maxY;
  else if (rawY < minY)
    rawY = minY;

  float x = rawX;
  float y = rawY;
  switch(_configuration.rotation())
  {
  case Configuration::ROTATION_0:
    break;
  case Configuration::ROTATION_90:
    x = -rawY;
    y = rawX;
    break;
  case Configuration::ROTATION_180:
    x = -rawX;
    y = - rawY;
    break;
  case Configuration::ROTATION_270:
    x = rawY;
    y = -rawX;
    break;
  }

  _loop->onGravity(centerX - x, centerY - y);
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

void Window::destroy()
{
  deactivate();
  ANativeActivity_finish(_app->activity);
}

void Window::activateGSensor()
{
  _sensorPollSource.id = LOOPER_ID_USER;
  _sensorPollSource.app = _app;
  _sensorPollSource.process = sensorCallback;
		
  _sensorManager = ASensorManager_getInstance();

  if(_sensorManager != NULL)
  {
    _sensorEventQueue = ASensorManager_createEventQueue(_sensorManager, 
							_app->looper, 
							LOOPER_ID_USER, 
							NULL, 	
							&_sensorPollSource);
  }

  _sensor = ASensorManager_getDefaultSensor(_sensorManager, ASENSOR_TYPE_ACCELEROMETER);
  if(_sensor != NULL)
  {
    ASensorEventQueue_enableSensor(_sensorEventQueue, _sensor);
  }

  int32_t minDelay = ASensor_getMinDelay(_sensor);
  ASensorEventQueue_setEventRate(_sensorEventQueue, _sensor, minDelay);
}

void Window::activate()
{
  if(!_enabled && _app->window != NULL)
  {
    activateGSensor();
    _enabled = true;
    _loop->onActivate();
  }
}

void Window::deactivateGSensor()
{
  if(_sensor != NULL)
  {
    ASensorEventQueue_disableSensor(_sensorEventQueue, _sensor);
    _sensor = NULL;
  }

  if(_sensorEventQueue != NULL)
  {
    ASensorManager_destroyEventQueue(_sensorManager, _sensorEventQueue);
    _sensorEventQueue = NULL;
  }
  _sensorManager = NULL;
}

void Window::deactivate()
{
  if(_enabled)
  {
    deactivateGSensor();

    _enabled = false;
    _loop->onDeactivate();
  }
}

void Window::processEvent(int32_t event)
{
  switch(event)
  {
  case APP_CMD_GAINED_FOCUS:
    activate();
    break;
  case APP_CMD_LOST_FOCUS:
    deactivate();
    break;
  case APP_CMD_PAUSE:
    deactivate();
    break;
  case APP_CMD_RESUME:
    activate();
    break;
  case APP_CMD_TERM_WINDOW:
    deactivate();
    break;
  }
}

void Window::processInput(AInputEvent* event)
{
  switch(AInputEvent_getType(event))
  {
  case AINPUT_EVENT_TYPE_MOTION:	
    if(AInputEvent_getSource(event) != AINPUT_SOURCE_TOUCHSCREEN)
      return;
    handleTap(event);
    break;
  case AINPUT_EVENT_TYPE_KEY:
    handleKey(event);
    break;
  }
}

void Window::processSensor()
{
  ASensorEvent event;
  while(ASensorEventQueue_getEvents(_sensorEventQueue, &event, 1) > 0)
  {
    if(event.type != ASENSOR_TYPE_ACCELEROMETER)
      continue;
	
    handleGravity(&event);
    break;
  }
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

void Window::sensorCallback(android_app* app, android_poll_source* source)
{
  Window* window = Window::unpack(app->userData);
  window->processSensor();
}



