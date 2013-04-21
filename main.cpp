#include "Random.hpp"
#include "EventLoop.hpp"

int main ( int argc, char * argv[] )
{
  Asteroids::Random::setup();

  Asteroids::EventLoop loop;
  loop.setup();

  loop.run();

  return 0;
}

