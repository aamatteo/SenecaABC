// SegmentDisplay.hxx
//
// draws a 7 segment display for numbers
//
// Olaf Stroosma
// 28 JUN 2004

#ifndef SegmentDisplay_hxx
#define SegmentDisplay_hxx

#include "project_utilities.h"

class SegmentDisplay 
{
public:
  /** default constructor */
  SegmentDisplay();

  /** destructor */
  virtual ~SegmentDisplay();

  /** draw a digit using stroke bars*/
  bool drawDigit(int n);

  /** draw a digit using texture */
  bool drawDigitTextured(int n);

  /** set the color, OpenGL style RGB (0.0 ... 1.0) */
  bool setColor(float r, float g, float b);

private:
  /**  mapping of digit to bars/segments */
  static struct bars{float x0,y0,x1,y1, color;} digit_bars[7];

  /** first instance populates the struct */
  static bool first;

  /** colors of the digits */
  float red, green, blue;

  /** texture for the bars */
  static GLuint tex_id;

  /** utilities */
  static ProjectUtilities utils;
};

#endif
