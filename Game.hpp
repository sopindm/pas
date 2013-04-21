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

    void update(Timer& timer, int width, int height);
    void draw(Render& render);

    void tap(Point point);
    void gravity(Vector gravity); 

  private:
    const static float shootDelay = 0.5;
    const static float moveDelay = 0.5;

    Ship _ship;
    std::vector<Shoot> _shoots;

    Timer _shootTimer;
    Timer _moveTimer;

  };
}
#endif
