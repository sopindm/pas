#ifndef ASTEROIDS_TIMER_HPP
#define ASTEROIDS_TIMER_HPP

namespace Asteroids
{
  class Timer
  {
  public:
    Timer();

    void start();
    void stop();
    void reset();

    double elapsed() const;

    void pause();
    void resume();

    bool isPaused() const;
    bool isWorking() const;
    bool isStopped() const;

  private:
    static double _getTime();

    enum
    {
      STOPPED,
      WORKING,
      PAUSED
    } _state;

    double _startTime;
    double _pauseTime;

  };
}
#endif
