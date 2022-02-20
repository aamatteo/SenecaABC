// MCPSwitch.cxx
//
// screen element that has on/off state and sends different event on toggle
//
// Olaf Stroosma
// 14 JUL 2004

// class header
#include "MCPSwitch.hxx"

// DUECA headers
#include <SimTime.hxx>

// OpenGL headers
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

// debug headers
#include <iostream>
using namespace std;
//#define D_MOD
#include <debug.h>

/** static variables */
ProjectUtilities MCPSwitch::utils;

/** default constructor */
MCPSwitch::MCPSwitch():
  on(false), tex_id(0)
{
}

/** destructor */
MCPSwitch::~MCPSwitch()
{

}

/** constructor with screen area, event token and on and off events */
MCPSwitch::MCPSwitch(float xl, float xu, float yl, float yu, 
		     EventChannelWriteToken<MCP737Event> *ptoken, 
		     MCP737Event on_evt, MCP737Event off_evt):
  MCPElement(xl, xu, yl, yu),
  on(false),
  x( (xl+xu)/2.0 ), y( (yl+yu)/2.0 ),
  ptoken(ptoken), on_evt(on_evt), off_evt(off_evt), tex_id(0)
{
}

/** check if click is within screen area */
bool MCPSwitch::checkClick(float x, float y, int button)
{
  // is it in our area?
  if(MCPElement::checkClick(x,y,button)) {
    //toggle
    on = !on;
    
    // send out the corresponding event
    if(on) {
      ptoken->sendEvent(new MCP737Event(on_evt), SimTime::now());
    }
    else {
      ptoken->sendEvent(new MCP737Event(off_evt), SimTime::now());
    }
  
    return true;
  }
  else {
    return false;
  }
}

/** draw the element */
void MCPSwitch::draw()
{
  if(tex_id <= 0)
    return;

  glPushMatrix();

  // texture
  glEnable (GL_TEXTURE_2D);
  glBindTexture (GL_TEXTURE_2D, tex_id);
  
  // switch
  glColor3f(1.0, 1.0, 1.0);

  glTranslatef(x,y,0.0);

  float offset = (on ? 0.0 : 0.5);

  glBegin(GL_QUADS);
  glTexCoord2f(0.0+offset, 1.0); // upper left corner of image
  glVertex2f(xmin-x, ymax-y);
  glTexCoord2f(0.5+offset, 1.0); // upper right corner of image
  glVertex2f(xmax-x, ymax-y);
  glTexCoord2f(0.5+offset, 0.0); // lower right corner of image
  glVertex2f(xmax-x, ymin-y);
  glTexCoord2f(0.0+offset, 0.0); // lower left corner of image
  glVertex2f(xmin-x, ymin-y);
  glEnd();

  glDisable (GL_TEXTURE_2D);

  /*  if (on) {

    glColor3f(0.0, 1.0, 0.0);

    float width= xmax-xmin;
    float height=ymax-ymin;

    glBegin(GL_POLYGON);
    glVertex2f(xmin+0.40*width,ymin+0.38*height);
    glVertex2f(xmin+0.40*width,ymin+0.76*height);
    glVertex2f(xmin+0.55*width,ymin+0.76*height);
    glVertex2f(xmin+0.55*width,ymin+0.38*height);
    glEnd();  
    
    }*/

  glPopMatrix();
}

/** set the value of the element, probably in response to a hardware event */
void MCPSwitch::setValue(double d)
{
  D_MOD("Switch received update from hardware: " << d);

  if(d >= 0.0) {
    on = true;
  }
  else {
    on = false;
  }
}

/** load the texture, on is left half, off is right */
bool MCPSwitch::loadTextureFile(char *s)
{
  // get the texture
  glGenTextures(1, &tex_id); 
  if(utils.loadTGA(s, tex_id) != 1) {
    // debug
    D_MOD("error loading " << s << " @ " << tex_id);
    return false;
  }
  else {
    D_MOD("success loading " << s <<  " @ " << tex_id);
    return true;
  }


}


