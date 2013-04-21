#include <time.h>
#include "Timer.hpp"

using namespace Asteroids;

Timer::Timer():_state(STOPPED)
{
}

void Timer::start()
{
  _state = WORKING;
  _startTime = _getTime();
}

void Timer::stop()
{
  _state = STOPPED;
}

void Timer::reset()
{
  stop();
  start();
}

bool Timer::isWorking() const
{
   return _state == WORKING;
}

bool Timer::isStopped() const
{
   return _state == STOPPED;
}

bool Timer::isPaused() const
{
   return _state == PAUSED;
}

double Timer::elapsed() const
{
  if(_state != WORKING)
    return 0;

  return _getTime() - _startTime;
}

double Timer::_getTime()
{
  timespec spec;
  clock_gettime(CLOCK_MONOTONIC, &spec);

  return spec.tv_sec + spec.tv_nsec * 1e-9;
}

void Timer::pause()
{
  if(_state != WORKING)
    return;

  _state = PAUSED;
  _pauseTime = _getTime();
}

void Timer::resume()
{
  if(_state != PAUSED)
    return;

  _state = WORKING;
  _startTime += _getTime() - _pauseTime;
}
