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

  private:
    Ship _ship;
    std::vector<Shoot> _shoots;

  };
}
#endif
