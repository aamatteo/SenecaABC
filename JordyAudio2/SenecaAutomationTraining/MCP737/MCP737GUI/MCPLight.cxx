// MCPLight.cxx
//
// screen element that has on/off state
//
// Olaf Stroosma
// 14 JUL 2004

// class header
#include "MCPLight.hxx"

// OpenGL headers
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

// debug headers
#include <iostream>
using namespace std;
//#define D_MOD
#include <debug.h>


/** default constructor */
MCPLight::MCPLight():
color(0.0)
{

}

/** destructor */
MCPLight::~MCPLight()
{

}

/** constructor with screen area, event token and on and off events */
MCPLight::MCPLight(float xl, float xu, float yl, float yu):
  MCPElement(xl, xu, yl, yu),
  color(0.0),
  x( (xl+xu)/2.0 ), y( (yl+yu)/2.0 )
{
}

/** check if click is within screen area */
bool MCPLight::checkClick(float x, float y, int button)
{
  return false;
}

/** draw the element */
void MCPLight::draw()
{
  glColor3f(color*red, color*green, color*blue);
  
  glBegin(GL_POLYGON);
  glVertex2f(xmin,ymin);
  glVertex2f(xmin,ymax);
  glVertex2f(xmax,ymax);
  glVertex2f(xmax,ymin);
  glEnd();  
  
}

/** set the value of the element, probably in response to a hardware event */
void MCPLight::setValue(double d)
{
  D_MOD("Light received update from hardware: " << d);

  color = d;
}
