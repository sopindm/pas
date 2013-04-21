#ifndef ASTEROIDS_MAINLOOP_HPP
#define ASTEROIDS_MAINLOOP_HPP

#include <memory>
#include "Render.hpp"
#include "Game.hpp"
#include "Window.hpp"
#include "Timer.hpp"

namespace Asteroids
{
  class EventLoop
  {
  public:
    EventLoop();
    ~EventLoop();

    void setup();
    void run();

  private:
    friend class Window;

    void onTap(int x, int y);
    void onGravity(float x, float y);
    void onPaint();

    void onActivation();
    void onDeactivation();

    void onExit();

    Window _window;
    std::auto_ptr<Render> _render;

    Game _game;

    Timer _timer;

    bool _active;
    bool _done;

  };
}
#endif
