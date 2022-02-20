// MCPNumber.hxx
//
// screen element that draws a numerical value that can optionally be changed directly 
// DEBUG: MCPEvent is replaced by string
//
// Olaf Stroosma
// 25 JUN 2004

#ifndef MCPNumber_hxx
#define MCPNumber_hxx

#include "MCPElement.hxx"
#include "SegmentDisplay.hxx"

#include <string>

#include "project_utilities.h"

class MCPNumber : public MCPElement  
{
public:
  /** default constructor */
  MCPNumber();
  
  /** constructor with screen area, initial value, increments for both mouse buttons,
      a format string for sprintf, an event token and an event to send on change */
  MCPNumber(float xl, float xu, float yl, float yu, 
	    double val, double incr1, double incr2, std::string form,
	    std::string tok, std::string evt);
  
  /** constructor with screen position, initial value and format string for sprintf */
  MCPNumber(float x, float y, double val, std::string form);
  
  /** destructor */
  virtual ~MCPNumber();
  
  /** check if click is within screen area */
  virtual bool checkClick(float x, float y, int button);
  
  /** draw the element */
  virtual void draw();
  
  /** accessor functions */
  inline void setValue(double d){value=d;}
  inline double getValue(){return value;}

  inline void setNumDigits(int i){num_digits=i;}
  inline int getNumDigits(){return num_digits;}
  
  inline void allowMinus(bool b){allow_minus=b;}
private:
  
  /** value to show */
  double value;
  
  /** format to show value in */
  std::string format;
  
  /** screen position */
  float x, y;
  
  /** optional increments for left and right buttons */
  double incr1, incr2;
  
  /** working buffer to print to */
  char buf[16];
  
  /** the event token to use */
  // debug
  std::string out_token;
  
  /** the event to send */
  // debug
  std::string chg_str;
  
  /** utilities for text drawing and textures */
  ProjectUtilities utils;

  /** segment display */
  SegmentDisplay seg;

  /** number of digits */
  int num_digits;

  /** allow negative numbers */
  bool allow_minus;
};

#endif 
