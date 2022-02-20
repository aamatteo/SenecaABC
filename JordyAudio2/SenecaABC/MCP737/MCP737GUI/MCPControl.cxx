// MCPControl.cxx
//
// screen element that changes a numerical value and sends event on change
//
// Olaf Stroosma
// 25 JUN 2004

#include "MCPControl.hxx"

// OpenGL headers
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

// DUECA headers
#include <SimTime.hxx>

// debug
#include <iostream>
//#define D_MOD
#include <debug.h>

/** default constructor */
MCPControl::MCPControl()
{

}

/** constructor with screen area, increments for left & right button, initial value, token, event and link 
	to other MCPNumber screen element */
MCPControl::MCPControl(float xl, float xu, float yl, float yu, 
		       double inc1, double inc2, double val, 
		       EventChannelWriteToken<MCP737Event> *tok, MCP737Event evt, 
		       MCPNumber* num, bool wrap):
MCPElement(xl, xu, yl, yu),
incr1(inc1), incr2(inc2),
value(val),
wrap_around(wrap),
out_token(tok), chg_evt(evt),
number(num)
{
  // get in sync with the MCPNumber from the start
  value = num->getValue();
}


/** destructor */
MCPControl::~MCPControl()
{

}

/** check if click is within screen area */
bool MCPControl::checkClick(float x, float y, int button)
{
  if(enabled) {
    bool res = MCPElement::checkClick(x,y,button);
    
    if(res) {
      // update
      if(number) value = number->getValue();

    
      // handle buttons
      if(button == GLUT_LEFT_BUTTON)
	value += incr1;
      else if(button == GLUT_RIGHT_BUTTON)
	value += incr2;
    
      // do wrap around
      if(wrap_around) {
	if(value > 360.0)
	  value -= 360.0;
	else if(value < 0.0)
	  value += 360.0;
      }

      // sync display element
      if(number) number->setValue(value);
      
      // send event
      chg_evt.data = value;
      out_token->sendEvent(new MCP737Event(chg_evt), SimTime::now());
      D_MOD("Control sending event: " << chg_evt);
    }
    
    return res;
  }
  else return false;
}

/*void MCPControl::draw()
{

}
*/
