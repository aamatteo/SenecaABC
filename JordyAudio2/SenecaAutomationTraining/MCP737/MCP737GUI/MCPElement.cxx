// MCPElement.cxx
//
// base class for screen elements that can be clicked and/or drawn
//
// Olaf Stroosma
// 25 JUN 2004

#include "MCPElement.hxx"

/** default constructor */
MCPElement::MCPElement():
  xmin(0),xmax(0),ymin(0),ymax(0),
  enabled(true)
{
  //
}

/** constructor with non-zero screen area */
MCPElement::MCPElement(float xl, float xu, float yl, float yu ):
  xmin(xl),xmax(xu),ymin(yl),ymax(yu),
  enabled(true)
{
  //
}


/** destructor */
MCPElement::~MCPElement()
{

}

/** check if click is within screen area */
bool MCPElement::checkClick(float x, float y, int button)
{
  if(x > xmin && x < xmax && y > ymin && y < ymax) {
    return true;
  }
  else {
    return false;
  }
}

/** draw the element */
void MCPElement::draw()
{
  // nothing
}

/** set the value of the element, probably in response to a hardware event */
void MCPElement::setValue(double d)
{
  // nothing
}
