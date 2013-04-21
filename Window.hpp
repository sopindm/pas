#ifndef ASTEROIDS_WINDOW_HPP
#define ASTEROIDS_WINDOW_HPP

#include <android_native_app_glue.h>
#include <android/sensor.h>
#include "Configuration.hpp"

namespace Asteroids
{
  class EventLoop;

  class Window
  {
  public:
    Window(android_app* app);

    void release();
    void setup(EventLoop* loop);

    int width() const;
    int height() const;

    bool handleEvent();

    void destroy();

  private:
    void* pack();
    static Window* unpack(void* data);

    void handleKey(AInputEvent* event);
    void handleTap(AInputEvent* event);
    void handleGravity(ASensorEvent* event);

  private:
    void activateGSensor();
    void deactivateGSensor();

    void activate();
    void deactivate();

    void processEvent(int32_t event);
    void processInput(AInputEvent* event);
    void processSensor();

    static void activityCallback(android_app* app, int32_t command);
    static int32_t inputCallback(android_app* app, AInputEvent* event);
    static void sensorCallback(android_app* app, android_poll_source* source);

  private:
    bool _enabled;
    bool _quit;

    EventLoop* _loop;
    android_app* _app;
 
    const ASensor* _sensor;
    ASensorManager* _sensorManager;
    ASensorEventQueue* _sensorEventQueue;
    android_poll_source _sensorPollSource;
    Configuration _configuration;
  };
}
#endif
