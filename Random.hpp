#ifndef ASTEROIDS_RANDOM_HPP
#define ASTEROIDS_RANDOM_HPP

namespace Asteroids
{
  class Random
  {
  public:
    static void setup();

    static int nextInt(int maxValue);
    static int nextInt(int minValue, int maxValue);

    static float nextFloat(float maxValue = 1.0);
    static float nextFloat(float minValue, float maxValue);

  };
}
#endif
