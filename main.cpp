#include "EventLoop.hpp"

void android_main(android_app* app)
{
  Asteroids::EventLoop loop(app);
  loop.setup();

  loop.run();
}

