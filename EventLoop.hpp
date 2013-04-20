#ifndef ASTEROIDS_MAINLOOP_HPP
#define ASTEROIDS_MAINLOOP_HPP

#include <memory>
#include "Render.hpp"
#include "Objects.hpp"
#include "Window.hpp"

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

    void onClick(int x, int y);
    void onPaint();
    void onExit();

    Window _window;
    std::auto_ptr<Render> _render;
    Ship _ship;

    bool _done;

  };
}
#endif
