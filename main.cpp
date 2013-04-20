#include "EventLoop.hpp"

#include <iostream>

int main ( int argc, char * argv[] )
{
  Asteroids::EventLoop loop;
  loop.setup();

  loop.run();

  return 0;
}

