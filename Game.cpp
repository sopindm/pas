#include <cmath>
#include "Game.hpp"

using namespace Asteroids;

Game::Game()
{
}

void Game::tap(Point point)
{
  _ship.setDirection(point.angle(_ship.center()));
  _shoots.push_back(Shoot(_ship));
}

void Game::update(Timer& timer, int width, int height)
{
  for(int i=0;i<_shoots.size();i++)
  {
    if(!_shoots[i].update(timer, width, height))
    {
      _shoots[i] = _shoots[_shoots.size() - 1];
      _shoots.resize(_shoots.size() - 1);
      i--;
    }
  }
}

void Game::draw(Render& render)
{
  _ship.draw(render);

  for(int i=0;i<_shoots.size();i++)
    _shoots[i].draw(render);
}
