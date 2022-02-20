#include "compass.hxx"
#include <cmath>
#include <stdio.h>
#include <iostream>

// Because the column obstructed the view on the compass, 
// the compass was moved above the attutude indicator. 
// Moving this item up was done by: -35.0f+105.f
compass::compass(): gl2DObject("compass", 69.0f, -35.0f),
  m_stockId(0),
  m_currentHeading(0.0f), m_trackAngle(0.0f), m_selectedHeading(0.0f),
  _draw_heading_bug(false)
{
  
}

compass::~compass()
{
  
}

void compass::init()
{
  m_stockId = glGenLists(1);
  if(m_stockId !=0)
  {
    glNewList(m_stockId, GL_COMPILE);
    double  origin_x      = 0;
    double  origin_y      = 0;
    double  radius        = 60;
    bool    big           = true;   //flag to check whether to draw a big or a small tick-mark
    int     heading_count = 90;	    //zero degrees angle is 90 degrees heading

    // Draw compass background
    glColor3fv(Grey);
    glPushMatrix();
    glScalef(60.0f, 60.0f, 0.0f);
    circle(0.0f, 0.0f, 1.0f, true);
    glPopMatrix();

    glColor3fv(White);
	// Draw tick-marks
    for (int angle=0; angle<360; angle = angle + 5)
    {

      glPushMatrix();
      glRotatef(angle,0,0,1);
      glBegin(GL_LINES);
      glVertex2f(origin_x, origin_y + radius);
      if (big)
      {
        glVertex2f(origin_x, origin_y + radius - 4.0);
        big = false;
      }
      else
      {
        glVertex2f(origin_x, origin_y + radius - 2.0);
        big = true;
      }
      glEnd();
      glPopMatrix();
    }

	// Draw digits
    for (int angle=0; angle<360; angle = angle + 10)
    {
      if (heading_count<=0)
        heading_count=360;

      char buf[255];
      glPushMatrix();
      glRotatef(-90 + angle,0.0,0.0,1.0);
      snprintf(buf,255, "%02d", heading_count/10);
      strokeString(buf, origin_x - 2.5,origin_y + radius - 8.0, 3.4);
      glPopMatrix();

      heading_count = heading_count - 10;
    }
    glEndList();
  }
}

void compass::draw()
{
  selectClippingArea(0.0f, 70.0f, 140.0f, 58.0f);
  glPushMatrix();
  
  // Draw compass
  glRotatef(m_currentHeading,0,0,1);
  glCallList(m_stockId);

  // Draw track selected indicator
  glColor3fv(White);
  glPushMatrix();
  glRotatef(-m_trackAngle,0,0,1);
  glBegin(GL_LINES);
  glVertex2f(0.0f,0.0f);
  glVertex2f(0.0f,60.0f);
  glVertex2f(4.0f,48.0f);
  glVertex2f(-4.0f,48.0f);
  glEnd();
  glPopMatrix();

  // Draw heading selected indicator
  if (_draw_heading_bug)
  {
    glColor3fv(Magenta);
    glPushMatrix();
    glRotatef(- m_selectedHeading,0,0,1);
    glBegin(GL_LINE_LOOP);
    glVertex2f(0.0f, 62.5f);
    glVertex2f(0.4f, 60.0f);
    glVertex2f(3.0f, 60.0f);
    glVertex2f(3.0f, 63.0f);
    glVertex2f(-3.0f, 63.0f);
    glVertex2f(-3.0f, 60.0f);
    glVertex2f(-0.4f, 60.0f);
    glEnd();
    glPopMatrix();
  }
  glPopMatrix();
  deselectClippingArea();

  // Draw heading and magnetic text into compass
  glColor3f(0.90f,0.0f,0.90f);
  char buf[255];
  snprintf(buf,255, "%03dH", (int)m_selectedHeading);
  strokeString(buf, -22.0f,42.0f, 3.0f);
  glColor3fv(Green);
  strokeString("MAG", 13.0f, 42.0f, 3.0f);
  
  // Pointer
  glColor3fv(White);
  glBegin(GL_TRIANGLES);
  glVertex2f( 0.0f,60.0f);
  glVertex2f(-2.5f,65.0f);
  glVertex2f( 2.5f,65.0f);
  glEnd();
}

void compass::selectedHeading(float Heading)
{
  m_selectedHeading = WRAP(Heading);
}

void compass::currentHeading(float Heading)
{
  m_currentHeading = WRAP(Heading);
}

void compass::trackAngle(float angle)
{
  m_trackAngle = WRAP(angle);
}
