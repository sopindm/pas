#include <cmath>
#include "Game.hpp"

using namespace Asteroids;

Game::Game()
{
  _shootTimer.reset();
  _moveTimer.reset();
}

void Game::tap(Point point)
{
  if(_shootTimer.elapsed() < shootDelay)
    return;

  _ship.setDirection(point.angle(_ship.center()));
  _ship.setSpeed(0);
  _shoots.push_back(Shoot(_ship));

  _moveTimer.reset();
  _shootTimer.reset();
}

void Game::gravity(Vector g)
{
  if(_moveTimer.elapsed() < moveDelay)
    return;

  float speed = 10 * g.magnitude();

  if(speed > 1)
  {
    _ship.setDirection(g.angle());
    _ship.setSpeed(speed);
  }
  else
    _ship.setSpeed(0);

  _moveTimer.reset();
} 

void Game::update(Timer& timer, int width, int height)
{
  _ship.update(timer, width, height);

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
