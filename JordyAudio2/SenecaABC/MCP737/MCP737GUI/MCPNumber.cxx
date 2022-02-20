// MCPNumber.cxx
//
// screen element that draws a numerical value that can optionally be changed directly 
// DEBUG: MCPEvent is replaced by string
//
// Olaf Stroosma
// 25 JUN 2004

#include "MCPNumber.hxx"

// debug
#include <iostream>
using namespace std;

/** default constructor */
MCPNumber::MCPNumber()
{

}

/** constructor with screen area, initial value, increments for both mouse buttons,
	a format string for sprintf, an event token and an event to send on change */
MCPNumber::MCPNumber(float xl, float xu, float yl, float yu, 
					 double val, double incr1, double incr2, string form,
					 string tok, string evt):
MCPElement(xl, xu, yl, yu),
value(val),
format(form),
x( (xl+xu)/2.0 ), y( (yl+yu)/2.0 ),
incr1(incr1), incr2(incr2),
out_token(tok), chg_str(evt),
num_digits(3), allow_minus(false)
{
}


/** constructor with screen position, initial value and format string for sprintf */
MCPNumber::MCPNumber(float x, float y, double val, string form):
MCPElement(), value(val), format(form), x(x), y(y),
incr1(0.0), incr2(0.0), num_digits(3), allow_minus(false)
{
}

/** destructor */
MCPNumber::~MCPNumber()
{

}

/** check if click is within screen area */
bool MCPNumber::checkClick(float x, float y, int button)
{
  if(enabled) {
    bool res = MCPElement::checkClick(x,y,button);
    
    if(res && button == 1)
      value += incr1;
    else if(res && button == 2)
      value += incr2;
    
    // TODO: how are we going to sync this with our associated control????
    // SOLVED: an MCPControl needs to sync itself before changing anything, because
    // there may be two (increment & decrement) controls working the same number.
    
    /*if(res)
      cout << "Number clicked: " << chg_str << " for " << value << endl;
    */
    return res;
  }
  else return false;
}
  
  
/** draw the element */
void MCPNumber::draw()
{
  if (enabled) {
    // compose the string
    //sprintf(buf, format.c_str(), value);
    int val;

    if(fabs(value) < 1.0) val = (int)(100.0 * value + 0.5);
    else val = (int)value;
    
    // draw it
    //cout << "MCPNumber drawing @ ( " << x << ", " << y << " ): " << buf << endl;
    glColor3f(1.0, 1.0, 1.0);
    
    // debug: change aspect and stroke string it
    /*	glPushMatrix();
	glTranslatef(x, y, 0.0);
	glScalef(1.0, 524.0/94.0, 1.0);
	utils.strokeString(0, 0, buf, GLUT_STROKE_ROMAN, 0.0003);
	glPopMatrix();*/
    
    // minus signs
    bool minus = (val < 0);
    if (minus) {
      if (allow_minus) val *= -1;
      else {
	val = 0; value = 0.0;
	minus = false;
      }
    }
    
    // segment it
    int digits[num_digits];
    
    for (int i = 0; i < num_digits; i++) {
      
      digits[i] = ( val % (int (pow(10.0, i+1))) ) / int(pow(10.0, i));
      
      for (int j = 0; j < i; j++) {
	digits[i] -= int(digits[j]*pow(10.0,j)) / int(pow(10.0, i));
      }
    }
    
    glPushMatrix();
    glTranslatef(x, y, 0.0);
    glScalef(0.030, 0.11, 1.0);
    seg.setColor(1.0, 0.0, 0.0);
    
    // minus sign
    if(allow_minus) {
      if(minus) seg.drawDigitTextured(-1);
      glTranslatef(1.0, 0.0, 0.0);
    }
    
    for (int i = num_digits;i--;) {
      //cout << "Digit #" << i << " is " << digits[i] << endl;
      seg.drawDigitTextured(digits[i]);
      glTranslatef(1.0, 0.0, 0.0);
    }
    
    glPopMatrix();
  }
}
