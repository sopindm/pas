#ifndef ASTEROIDS_GAME_HPP
#define ASTEROIDS_GAME_HPP

#include <vector>
#include "Objects.hpp"

namespace Asteroids
{
  class Game
  {
  public:
    Game();

    void setup(int width, int height);

    void update(Timer& timer, int width, int height);
    void draw(Render& render);

    void tap(Point point);
    void gravity(Vector gravity); 

  private:
    void setupAsteroids(int width, int height);

    void removeShoot(int index);
    void removeAsteroid(int index);

    void updateAsteroids(Timer& timer, int width, int height);
    void updateShoots(Timer& timer, int width, int height);

    void collideShoots(Timer& timer);

    const static float shootDelay = 0.01;
    const static float moveDelay = 0.5;

    Ship _ship;
    std::vector<Shoot> _shoots;
    std::vector<Asteroid> _asteroids;

    Timer _shootTimer;
    Timer _moveTimer;

  };
}
#endif
