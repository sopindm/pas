#include <GL/glfw.h>
#include "EventLoop.hpp"
#include "Window.hpp"

using namespace Asteroids;

const int width = 800;
const int height = 300;

Window* _window;

Window::Window()
{
  _window = this;
}

int Window::width() const
{
  return ::width;
}

int Window::height() const
{
  return ::height;
}

void Window::setup(EventLoop* loop)
{
  _loop = loop;

  glfwInit();
  glfwOpenWindow(::width, ::height, 16, 0, 0, 0, 0, 0, GLFW_WINDOW);

  glfwSetMouseButtonCallback(mouseHandler);
  glfwSetKeyCallback(keyboardHandler);
}

void Window::handleTap(int x, int y)
{
  GLFWvidmode vidMode;
  glfwGetDesktopMode( &vidMode );

  y = vidMode.Height - y;
  _loop->onClick(x, y);
}

void Window::handleKey(int key)
{
  if(key == GLFW_KEY_ESC)
    _loop->onExit();
}

void Asteroids::mouseHandler(int button, int state)
{
  int x, y;
  glfwGetMousePos(&x, &y);
 
  if ( state )
  {
    _window->handleTap(x, y);
  }
}
 
void Asteroids::keyboardHandler(int key, int action)
{
  if(action == GLFW_PRESS)
    _window->handleKey(key);
}



