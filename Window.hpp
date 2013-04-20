#ifndef ASTEROIDS_WINDOW_HPP
#define ASTEROIDS_WINDOW_HPP

namespace Asteroids
{
  class EventLoop;

  class Window
  {
  public:
    Window();
    void setup(EventLoop* loop);

    int width() const;
    int height() const;

  private:
    void handleTap(int x, int y);
    void handleKey(int key);

    friend void mouseHandler(int button, int state);
    friend void keyboardHandler(int button, int state);

    EventLoop* _loop;

  };

  void mouseHandler(int button, int state);
  void keyboardHandler(int key, int state);
}
#endif
