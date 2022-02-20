// MCPButton.hxx
//
// screen element that has on/off state and sends event on toggle
//
// Olaf Stroosma
// 25 JUN 2004


#ifndef MCPButton_hxx
#define MCPButton_hxx

#include "MCPElement.hxx"

// get the DUECA stuff in here
#include "comm-objects.h"
#define DO_INSTANTIATE
#define INCLUDE_TEMPLATE_SOURCE
#include <EventAccessToken.hxx>
USING_DUECA_NS;

// debug
#include <string>

/** screen element that has on/off state and sends event on toggle */
class MCPButton : public MCPElement  
{
public:
  /** default constructor */
  MCPButton();
  
  /** constructor with screen area, event token and on and off events */
  //MCPButton(float xl, float xu, float yl, float yu, std::string token, std::string on_evt, std::string off_evt);
  MCPButton(float xl, float xu, float yl, float yu, 
	    EventChannelWriteToken<MCP737Event> *ptoken, 
	    MCP737Event evt);
  
  /** destructor */
  virtual ~MCPButton();

  /** check if click is within screen area */
  virtual bool checkClick(float x, float y, int button);
  
  /** draw the element */
  virtual void draw();
  
  /** set the value of the element, probably in response to a hardware event */
  virtual void setValue(double d);
  
private:
  /** on or off state */
  bool on;
  
  /** screen coordinates to draw button at, currently at center of screen area */
  float x,y;

  /** the token for sending events */
  // debug
  //std::string out_token;
  EventChannelWriteToken<MCP737Event> *ptoken;
  
  /** the events that will be sent */
  // debug
  //std::string on_str, off_str;
  MCP737Event evt;
};

#endif
