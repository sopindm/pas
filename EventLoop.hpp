#ifndef ASTEROIDS_MAINLOOP_HPP
#define ASTEROIDS_MAINLOOP_HPP

#include <android_native_app_glue.h>
#include "Render.hpp"
#include "Game.hpp"
#include "Window.hpp"
#include "Timer.hpp"

namespace Asteroids
{
  class EventLoop
  {
  public:
    EventLoop(android_app* app);
    ~EventLoop();

    void setup();
    void run();

  private:
    friend class Window;

    void onActivate();
    void onDeactivate();

    void onTap(int x, int y);
    void onGravity(float x, float y);
    void onPaint();

    void onExit();

    Window _window;
    Render _render;
    Ship _ship;

    Game _game;
    Timer _timer;
    bool _active;

  };
}
#endif
