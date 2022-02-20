// SegmentDisplay.cxx
//
// draws a 7 segment display for numbers
//
// Olaf Stroosma
// 28 JUN 2004

#define SegmentDisplay_cxx

// class header
#include "SegmentDisplay.hxx"

// OpenGL headers
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

// debug
#include <iostream>
using namespace std;

/** static variables */
bool SegmentDisplay::first = true;
struct SegmentDisplay::bars SegmentDisplay::digit_bars[7];
GLuint SegmentDisplay::tex_id=0;
ProjectUtilities SegmentDisplay::utils;

/** default constructor */
SegmentDisplay::SegmentDisplay():
  red(1.0), green(1.0), blue(1.0)
{
  // bars are numbered as follows:
  //     0
  //    1 2
  //     3
  //    4 5
  //     6

  // coordinate origin is in lower left corner, range is [0,1] for x and [0,2] for y

  if(first) {
    // define bar #0
    digit_bars[0].x0 = 0.0;
    digit_bars[0].y0 = 2.0;
    digit_bars[0].x1 = 1.0;
    digit_bars[0].y1 = 2.0;
    digit_bars[0].color = 0.0;
    
    // define bar #1
    digit_bars[1].x0 = 0.0;
    digit_bars[1].y0 = 1.0;
    digit_bars[1].x1 = 0.0;
    digit_bars[1].y1 = 2.0;
    digit_bars[1].color = 0.0;
    
    // define bar #2 
    digit_bars[2].x0 = 1.0;
    digit_bars[2].y0 = 1.0;
    digit_bars[2].x1 = 1.0;
    digit_bars[2].y1 = 2.0;
    digit_bars[2].color = 0.0;
    
    // define bar #3
    digit_bars[3].x0 = 0.0;
    digit_bars[3].y0 = 1.0;
    digit_bars[3].x1 = 1.0;
    digit_bars[3].y1 = 1.0;
    digit_bars[3].color = 0.0;
    
    // define bar #4
    digit_bars[4].x0 = 0.0;
    digit_bars[4].y0 = 0.0;
    digit_bars[4].x1 = 0.0;
    digit_bars[4].y1 = 1.0;
    digit_bars[4].color = 0.0;
    
    // define bar #5
    digit_bars[5].x0 = 1.0;
    digit_bars[5].y0 = 0.0;
    digit_bars[5].x1 = 1.0;
    digit_bars[5].y1 = 1.0;
    digit_bars[5].color = 0.0;
    
    // define bar #6 
    digit_bars[6].x0 = 0.0;
    digit_bars[6].y0 = 0.0;
    digit_bars[6].x1 = 1.0;
    digit_bars[6].y1 = 0.0;
    digit_bars[6].color = 0.0;

    // get the texture
    glGenTextures(1, &tex_id); 
    if(!utils.loadTGA("digits.tga", tex_id)) {
      // debug
      // cout << "error loading digits.tga @ " << tex_id << endl;
    }
    else {
      //cout << "success loading digits.tga @ " << tex_id << endl;
    }

    first = false;
  }
  
  // nothing else
}
  
/** destructor */
SegmentDisplay::~SegmentDisplay()
{
  //
}


/** draw a digit */
bool SegmentDisplay::drawDigit(int n)
{
  // turn on the right bars
  switch(n) {
  case 0: {
    digit_bars[0].color=1.0;
    digit_bars[1].color=1.0;
    digit_bars[2].color=1.0;
    digit_bars[3].color=0.0;
    digit_bars[4].color=1.0;
    digit_bars[5].color=1.0;
    digit_bars[6].color=1.0;
    
    break;
  }
  case 1: {
    digit_bars[0].color=0.0;
    digit_bars[1].color=0.0;
    digit_bars[2].color=1.0;
    digit_bars[3].color=0.0;
    digit_bars[4].color=0.0;
    digit_bars[5].color=1.0;
    digit_bars[6].color=0.0;
    
    break;
  }
    
  case 2: {
    digit_bars[0].color=1.0;
    digit_bars[1].color=0.0;
    digit_bars[2].color=1.0;
    digit_bars[3].color=1.0;
    digit_bars[4].color=1.0;
    digit_bars[5].color=0.0;
    digit_bars[6].color=1.0;
    
    break;
  }
  case 3: {
    digit_bars[0].color=1.0;
    digit_bars[1].color=0.0;
    digit_bars[2].color=1.0;
    digit_bars[3].color=1.0;
    digit_bars[4].color=0.0;
    digit_bars[5].color=1.0;
    digit_bars[6].color=1.0;
    
    break;
  }
  case 4: {
    digit_bars[0].color=0.0;
    digit_bars[1].color=1.0;
    digit_bars[2].color=1.0;
    digit_bars[3].color=1.0;
    digit_bars[4].color=0.0;
    digit_bars[5].color=1.0;
    digit_bars[6].color=0.0;
    
    break;
  }
  case 5: {
    digit_bars[0].color=1.0;
    digit_bars[1].color=1.0;
    digit_bars[2].color=0.0;
    digit_bars[3].color=1.0;
    digit_bars[4].color=0.0;
    digit_bars[5].color=1.0;
    digit_bars[6].color=1.0;
    
    break;
  }
  case 6: {
    digit_bars[0].color=1.0;
    digit_bars[1].color=1.0;
    digit_bars[2].color=0.0;
    digit_bars[3].color=1.0;
    digit_bars[4].color=1.0;
    digit_bars[5].color=1.0;
    digit_bars[6].color=1.0;
    
    break;
  }
  case 7: {
    digit_bars[0].color=1.0;
    digit_bars[1].color=0.0;
    digit_bars[2].color=1.0;
    digit_bars[3].color=0.0;
    digit_bars[4].color=0.0;
    digit_bars[5].color=1.0;
    digit_bars[6].color=0.0;
    
    break;
  }
  case 8: {
    digit_bars[0].color=1.0;
    digit_bars[1].color=1.0;
    digit_bars[2].color=1.0;
    digit_bars[3].color=1.0;
    digit_bars[4].color=1.0;
    digit_bars[5].color=1.0;
    digit_bars[6].color=1.0;
	
    break;
  }
  case 9: {
    digit_bars[0].color=1.0;
    digit_bars[1].color=1.0;
    digit_bars[2].color=1.0;
    digit_bars[3].color=1.0;
    digit_bars[4].color=0.0;
    digit_bars[5].color=1.0;
    digit_bars[6].color=1.0;
    
    break;
  }
  default: {
    digit_bars[0].color=0.0;
    digit_bars[1].color=0.0;
    digit_bars[2].color=0.0;
    digit_bars[3].color=0.0;
    digit_bars[4].color=0.0;
    digit_bars[5].color=0.0;
    digit_bars[6].color=0.0;
  
    return false;
    break;
  }
  }

  // draw all the bars
  glLineWidth(2.0);
  
  for (int i=0;i<7;i++) {
    glColor3f(digit_bars[i].color*red,digit_bars[i].color*green,digit_bars[i].color*blue);
    glBegin(GL_LINES);
    glVertex2f(digit_bars[i].x0, digit_bars[i].y0);
    glVertex2f(digit_bars[i].x1, digit_bars[i].y1);
    glEnd();
  }

  glColor3f(1.0, 1.0, 1.0);
  glLineWidth(1.0);

  return true;
}	

/** draw a digit using texture */
bool SegmentDisplay::drawDigitTextured(int n)
{
  // texture
  glEnable (GL_TEXTURE_2D);
  glBindTexture (GL_TEXTURE_2D, tex_id);
  
  // minus sign 
  if(n < 0) n = 10;

  glColor3f(1.0, 1.0, 1.0);
  glBegin(GL_QUADS);
  glTexCoord2f (0.0909f*float(n),1.0f); 	// upper left corner of image
  //glTexCoord2f(0.0, 1.0);
  glVertex2f(0.0, 2.0);
  glTexCoord2f (0.0909f*float(n)+0.0909f,1.0f); 	// upper right corner of image
  //glTexCoord2f(1.0, 1.0);
  glVertex2f( 1.0, 2.0);
  glTexCoord2f (0.0909f*float(n)+0.0909f,0.0f);// lower right corner of image
  //glTexCoord2f(1.0, 0.0);
  glVertex2f(1.0, 0.0);
  glTexCoord2f (0.0909f*float(n),0.0);// lower left corner of image
  //glTexCoord2f(0.0, 0.0);
  glVertex2f(0.0, 0.0);
  glEnd();

  glDisable (GL_TEXTURE_2D);

  return true;
}

bool SegmentDisplay::setColor(float r, float g, float b)
{
  red = r;
  green = g;
  blue = b;

  return true; // no point really in testing, OpenGL does that already
}
