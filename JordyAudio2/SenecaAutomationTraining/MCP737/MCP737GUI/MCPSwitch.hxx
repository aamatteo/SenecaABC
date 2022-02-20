// MCPSwitch.hxx
//
// screen element that has on/off state and sends different event on toggle
//
// Olaf Stroosma
// 25 JUN 2004


#ifndef MCPSwitch_hxx
#define MCPSwitch_hxx

#include "MCPElement.hxx"
#include "project_utilities.h"

#include <string>

// get the DUECA stuff in here
#include "comm-objects.h"
#include <EventAccessToken.hxx>
USING_DUECA_NS;

/** screen element that has on/off state and sends event on toggle */
class MCPSwitch : public MCPElement  
{
public:
  /** default constructor */
  MCPSwitch();
  
  /** constructor with screen area, event token and on and off events */
  //MCPSwitch(float xl, float xu, float yl, float yu, std::string token, std::string on_evt, std::string off_evt);
  MCPSwitch(float xl, float xu, float yl, float yu, 
	    EventChannelWriteToken<MCP737Event> *ptoken, 
	    MCP737Event on_evt, MCP737Event off_evt);
  
  /** destructor */
  virtual ~MCPSwitch();

  /** check if click is within screen area */
  virtual bool checkClick(float x, float y, int button);
  
  /** draw the element */
  virtual void draw();
  
  /** set the value of the element, probably in response to a hardware event */
  virtual void setValue(double d);

  /** load the texture, on is left half, off is right */
  bool loadTextureFile(char* s);
  
private:
  /** on or off state */
  bool on;
  
  /** screen coordinates to draw button at, currently at center of screen area */
  float x,y;

  /** the token for sending events */
  EventChannelWriteToken<MCP737Event> *ptoken;
  
  /** the events that will be sent */
  MCP737Event on_evt, off_evt;

  /** texture for the switch */
  GLuint tex_id;

  /** utilities */
  static ProjectUtilities utils;
};

#endif
