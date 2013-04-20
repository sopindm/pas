#ifndef ASTEROIDS_WINDOW_HPP
#define ASTEROIDS_WINDOW_HPP

#include <android_native_app_glue.h>

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

  private:
    void* pack();
    static Window* unpack(void* data);

    void handleTap(AInputEvent* event);
    void handleKey(int key);

  private:
    void activate();
    void deactivate();

    void processEvent(int32_t event);
    void processInput(AInputEvent* event);

    static void activityCallback(android_app* app, int32_t command);
    static int32_t inputCallback(android_app* app, AInputEvent* event);

  private:
    bool _enabled;
    bool _quit;

    EventLoop* _loop;
    android_app* _app;
  };
}
#endif
