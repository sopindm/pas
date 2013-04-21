#include "Random.hpp"
#include "EventLoop.hpp"

void android_main(android_app* app)
{
  Asteroids::Random::setup();

  Asteroids::EventLoop loop(app);
  loop.setup();

  loop.run();
}

