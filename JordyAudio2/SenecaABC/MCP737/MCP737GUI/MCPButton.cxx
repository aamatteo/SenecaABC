// MCPButton.cxx
//
// screen element that has on/off state and sends event on toggle
//
// Olaf Stroosma
// 25 JUN 2004

// class header
#include "MCPButton.hxx"

// DUECA headers
#include <SimTime.hxx>
#include <EventAccessToken.hxx>
USING_DUECA_NS;

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
MCPButton::MCPButton():
on(false)
{

}

/** destructor */
MCPButton::~MCPButton()
{

}

/** constructor with screen area, event token and on and off events */
MCPButton::MCPButton(float xl, float xu, float yl, float yu, 
		     DUECA_NS ::EventChannelWriteToken<MCP737Event> *ptoken, 
		     MCP737Event evt):
  MCPElement(xl, xu, yl, yu),
  on(false),
  x( (xl+xu)/2.0 ), y( (yl+yu)/2.0 ),
  ptoken(ptoken), evt(evt)
{
}

/** check if click is within screen area */
bool MCPButton::checkClick(float x, float y, int button)
{
  // is it in our area?
  if(MCPElement::checkClick(x,y,button)) {

    // debug
    D_MOD("Button hit, sending " << evt);

    // send out the corresponding event
    ptoken->sendEvent(new MCP737Event(evt), SimTime::now());
  
    return true;
  }
  else {
    return false;
  }
}

/** draw the element */
void MCPButton::draw()
{
  // debug
  //cout << "Button draw " << (on?"ON":"OFF") << " @ ( " << x << ", " << y << " )" << endl;

  // TODO
  if (on) {

    glColor3f(0.0, 1.0, 0.0);

    float width= xmax-xmin;
    float height=ymax-ymin;

    glBegin(GL_POLYGON);
    glVertex2f(xmin+0.40*width,ymin+0.38*height);
    glVertex2f(xmin+0.40*width,ymin+0.76*height);
    glVertex2f(xmin+0.55*width,ymin+0.76*height);
    glVertex2f(xmin+0.55*width,ymin+0.38*height);
    glEnd();  
    
  }
}

/** set the value of the element, probably in response to a hardware event */
void MCPButton::setValue(double d)
{
  D_MOD("Button received update from hardware: " << d);

  if(d >= 0.0) {
    on = true;
  }
  else {
    on = false;
  }
}
