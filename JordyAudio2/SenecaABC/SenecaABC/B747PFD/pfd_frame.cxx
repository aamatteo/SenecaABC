#include "pfd_frame.hxx"
#include <cmath>
#include <stdio.h>

pfd_frame::pfd_frame(): gl2DObject("pfd_frame"/*posx, posy*/)
{

}

pfd_frame::~pfd_frame()
{

}

void pfd_frame::init()
{
}

void pfd_frame::draw()
{
  // glColor3f(0.5625f, 0.47265f, 0.37109f);
  // glRectf(0.0,0.0,155.0,150.0);
  //
  // glLineWidth(1.5f);
  // glBegin(GL_LINES);
  // // Frame highlights
  // glColor3f( 0.4335f, 0.3398f, 0.25f);
  // glVertex2f(155.0f,0.0f);
  // glVertex2f(155.0f,150.0f);
  //
  // glVertex2f(0.0f, 150.0f);
  // glVertex2f(155.0f,150.0f);
  //
  // glColor3f(0.7462f, 0.5937f, 0.4375f);
  // glVertex2f(0.0f, 0.0f);
  // glVertex2f(155.0f,0.0f);
  //
  // glVertex2f(0.0, 150.0f);
  // glVertex2f(0.0f,0.0f);
  //
  // glEnd();
  glLineWidth(1.0f);

  // Draw the display background
  glColor3fv(Black);
  glBegin(GL_POLYGON);
  glVertex2f(5.0f, 10.0f);
  glVertex2f(5.0f, 140.0f);
  glVertex2f(10.0f, 145.0f);
  glVertex2f(145.0f, 145.0f);
  glVertex2f(150.0f, 140.0f);
  glVertex2f(150.0f, 10.0f);
  glVertex2f(145.0f, 5.0f);
  glVertex2f(10.0f, 5.0f);
  glEnd();

}
