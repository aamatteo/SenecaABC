// MCPControl.hxx
//
// screen element that changes a numerical value and sends event on change
//
// Olaf Stroosma
// 25 JUN 2004

#ifndef MCPControl_hxx
#define MCPControl_hxx

#include "MCPElement.hxx"
#include "MCPNumber.hxx"

// get the DUECA stuff in here
#include "comm-objects.h"
#include <EventAccessToken.hxx>
USING_DUECA_NS;

// debug
#include <string>
using namespace std;


/** screen element that changes a numerical value and sends event on change */
class MCPControl : public MCPElement  
{
public:
  /** default constructor */
  MCPControl();
  
  /** constructor with screen area, increments for left & right button, initial value, token, event and link 
      to other MCPNumber screen element */
  MCPControl(float xl, float xu, float yl, float yu, 
	     double inc1, double inc2, double val, 
	     EventChannelWriteToken<MCP737Event> *tok, MCP737Event evt, 
	     MCPNumber* num, bool wrap=false);
  
  /** destructor */
  virtual ~MCPControl();
  
  /** check if click is within screen area */
  virtual bool checkClick(float x, float y, int button);

  //virtual void draw();
  
private:
  /** increments for left button and right button */
  double incr1, incr2;
  
  /** local copy of the value to be controlled, retrieved from the associated MCPNumber */
  double value;
  
  /** flag to indicate a wrap-around at 360 */
  bool wrap_around;

  /** token to send the event out on */
  EventChannelWriteToken<MCP737Event> *out_token;
  
  /** event to send on change in value */
  MCP737Event chg_evt;	
  
  /** screen element that remains in sync with the controlled value */
  MCPNumber *number;
};

#endif

