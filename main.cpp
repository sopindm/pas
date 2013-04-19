#include <stdio.h>
#include <cmath>
#include "Render.hpp"
#include <GL/glfw.h>

const int width = 1024;
const int height = 1024;

using namespace Asteroids;

double angle = 0;

void drawCube(Render& render)
{
  render.clear(Render::WHITE);

  render.drawQuad(Render::BLACK, Point(-40, -40), Point(-40, 40), Point(40, 40), Point(40, -40));

  render.drawQuad(Render::WHITE, 
		  Point(-1, -1).rotate(angle), 
		  Point(-1, 1).rotate(angle), 
		  Point(1, 1).rotate(angle), 
		  Point(1, -1).rotate(angle));

  render.drawTriangle(Render::WHITE, 
		      Point(1, 1).rotate(angle), 
		      Point(0, 4).rotate(angle), 
		      Point(-1, 1).rotate(angle));
}
 
void paintGL(Render& render)
{
  render.clear(Render::WHITE);
  drawCube(render);
}
 
/*!
  Processes 'mouse move' event.
*/
void MouseMoveHandler ( int x, int y )
{
}
 
/*!
  Processes 'mouse down' event.
*/
void MouseDownHandler ( int button, int state )
{
  int x, y;

  glfwGetMousePos ( &x, &y );
 
  if ( state )
  {
    y = height / 2 + 5 - y;
    x = x - width / 2;

    angle = atan2(-x, y); //In default state we a rotated at 90 degrees, so we need to rotate 90 degrees back
  }
  else
  {
  }
}
 
 /*!
   Processes 'key down' event.
  */
void KeyButton ( int key, int state )
{
  if ( state )
  {
  }
  else
  {
  }
}
 
 //===============================================================================
 // Entry point.
 //===============================================================================
 
 int main ( int argc, char * argv[] )
 {
   /* Try to init GLFW and open window */
   glfwInit();
   
   if ( !glfwOpenWindow ( width, height, 16, 0, 0, 0, 0, 0, GLFW_WINDOW ) )
   {
     glfwTerminate ( );
     return -1;
   }

   /* Set mouse and keyboard event handlers */
   
   glfwSetMouseButtonCallback ( MouseDownHandler );
   glfwSetKeyCallback ( KeyButton );
   
   Render render(width, height);
   render.setup();
   
   char caption [100];
     
   GLint frames = 0;
     
   GLfloat start = glfwGetTime ( );
   
   //-----------------------------------------------------------------------------
   
   /* Start rendering loop */
   
   while ( GL_TRUE )
   {
    /* Print current FPS */
    
    GLfloat time = glfwGetTime ( );
    
    if ( time > start + 1 )
    {
      sprintf ( caption,
		"Framebuffer Test - %.1f FPS",
		frames / ( time - start ) );

      glfwSetWindowTitle ( caption );

      start = time; frames = 0;
    }
    
    frames++;
    
    /* Draw OpenGL scene  */

    render.bind();
    paintGL(render);
    render.unbind();

    /* Check exit criteria */
    
    if ( glfwGetKey ( GLFW_KEY_ESC ) )
    {
      break;
    }
  }
  
  //-----------------------------------------------------------------------------
   
  /* Release all OpenGL resources */
   
   render.release();
   
  glfwTerminate ( );
   
  return 0;
}

