// MCPLight.hxx
//
// screen element that has on/off state
//
// Olaf Stroosma
// 14 JUL 2004

#ifndef MCPLight_hxx
#define MCPLight_hxx

#include "MCPElement.hxx"


/** screen element that has on/off state and sends event on toggle */
class MCPLight : public MCPElement  
{
public:
  /** default constructor */
  MCPLight();
  
  /** constructor with screen area, event token and on and off events */
  MCPLight(float xl, float xu, float yl, float yu); 
  
  /** destructor */
  virtual ~MCPLight();

  /** check if click is within screen area */
  virtual bool checkClick(float x, float y, int button);
  
  /** draw the element */
  virtual void draw();
  
  /** set the value of the element, probably in response to a hardware event */
  virtual void setValue(double d);
  
  /** set the color */
  inline void setColor(float r, float g, float b){red=r;green=g;blue=b;};
  
private:
  /** color state */
  double color;
  float red, green, blue;
  
  /** screen coordinates to draw button at, currently at center of screen area */
  float x,y;
};

#endif
