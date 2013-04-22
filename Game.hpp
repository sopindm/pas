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

    bool isActive() const;

    void update(Timer& timer, int width, int height);
    void draw(Render& render);

    void tap(Point point);
    void gravity(Vector gravity); 

  private:
    void reset(int width, int height, int level = 0);
    int _level;

    void setupAsteroids(int width, int height, int level);

    void removeShoot(int index);
    void removeAsteroid(int index);

    void updateAsteroids(Timer& timer, int width, int height);
    void updateShoots(Timer& timer, int width, int height);
    bool updateShip(Timer& timer, int width, int height);

    void collideShoots(Timer& timer);

    const static float shootDelay = 0.3;
    const static float moveDelay = 0.5;

    bool _isActive;

    Ship _ship;
    std::vector<Shoot> _shoots;
    std::vector<Asteroid> _asteroids;

    Timer _shootTimer;
    Timer _moveTimer;

  };
}
#endif
