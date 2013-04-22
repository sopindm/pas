#include <cmath>
#include "Game.hpp"

using namespace Asteroids;

Game::Game()
{
  _shootTimer.reset();
  _moveTimer.reset();
  _isActive = false;
}

void Game::setup(int width, int height)
{
  reset(width, height, 0);
  _isActive = true;
}

bool Game::isActive() const
{
  return _isActive;
}

void Game::reset(int width, int height, int level)
{
  setupAsteroids(width, height, level);
  _shoots.clear();
  _ship = Ship();

  _level = 0;
}

void Game::setupAsteroids(int width, int height, int level)
{
  int count = 10 + level * 5;

  _asteroids.clear();

  for(int i=0; i<count;i++)
    _asteroids.push_back(Asteroid(width, height));
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

  if(speed > 3)
  {
    _ship.setDirection(g.angle());
    _ship.setSpeed(speed);
  }
  else
    _ship.setSpeed(0);

  _moveTimer.reset();
} 

void Game::removeShoot(int index)
{
  _shoots[index] = _shoots[_shoots.size() - 1];
  _shoots.resize(_shoots.size() - 1);
}

void Game::removeAsteroid(int index)
{
  Asteroid asteroid = _asteroids[index];

  _asteroids[index] = _asteroids[_asteroids.size() - 1];
  _asteroids.resize(_asteroids.size() - 1);

  if(asteroid.size() > 0)
    asteroid.divide(_asteroids);
}

void Game::update(Timer& timer, int width, int height)
{
  if(_asteroids.size() == 0)
  {
    reset(width, height, _level + 1);
    return;
  }

  updateAsteroids(timer, width, height);
  collideShoots(timer);
  updateShoots(timer, width, height);

  if(!updateShip(timer, width, height))
    reset(width, height);
}

void Game::updateAsteroids(Timer& timer, int width, int height)
{
  for(int i=0;i<_asteroids.size();i++)
  {
    _asteroids[i].update(timer, width, height);
  }
}

bool Game::updateShip(Timer& timer, int width, int height)
{
  for(int i=0;i<_asteroids.size();i++)
    if(_ship.intersect(_asteroids[i], timer))
      return false;

  _ship.update(timer, width, height);
  return true;
}

void Game::collideShoots(Timer& timer)
{
  for(int i=0;i<_shoots.size();i++)
    for(int j=0;j<_asteroids.size();j++)
      if(_shoots[i].intersect(_asteroids[j], timer))
      {
	removeShoot(i);
	removeAsteroid(j);
	i--;
	break;
      }
}

void Game::updateShoots(Timer& timer, int width, int height)
{
  for(int i=0;i<_shoots.size();i++)
  {
    if(!_shoots[i].update(timer, width, height))
    {
      removeShoot(i);
      i--;
    }
  }
}

void Game::draw(Render& render)
{
  _ship.draw(render);

  for(int i=0;i<_asteroids.size();i++)
    _asteroids[i].draw(render);

  for(int i=0;i<_shoots.size();i++)
    _shoots[i].draw(render);
}
