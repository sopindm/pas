#include <time.h>
#include <stdlib.h>
#include "Random.hpp"

using namespace Asteroids;

void Random::setup()
{
  srand(time(NULL));
}

int Random::nextInt(int maxValue)
{
  return rand() % maxValue;
}

int Random::nextInt(int minValue, int maxValue)
{
  if(maxValue <= minValue)
    return minValue;

  return minValue + nextInt(maxValue - minValue);
}

float Random::nextFloat(float maxValue)
{
  return static_cast<float>(rand()) / RAND_MAX * maxValue;
}

float Random::nextFloat(float minValue, float maxValue)
{
  if(maxValue <= minValue)
    return minValue;

  return minValue + nextFloat(maxValue - minValue);
}
