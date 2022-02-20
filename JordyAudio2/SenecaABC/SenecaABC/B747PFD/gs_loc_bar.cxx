#include "gs_loc_bar.hxx"
#include <cmath>
#include <GL/gl.h>

int gs_loc_bar::m_glId = 0;

gs_loc_bar::gs_loc_bar(float x, float y, float phi, float maxangle, const char* name):
  gl2DObject(name, x, y, phi),
  m_angle(0.0f),
  m_maxangle(maxangle/180.0f*M_PI)
{
}

gs_loc_bar::~gs_loc_bar()
{
}

void gs_loc_bar::init()
{
  if (m_glId == 0) // init already done for previous object?
  {
 /*   // Glidescope and localizer dots
    m_glId = glGenLists(1);
    if (m_glId !=0)
    {
      glNewList(m_glId, GL_COMPILE);
      glColor3fv(White);
      // draw locator dots
      for (float x = -24.0; x <= 24.0; x += 12.0)
      {
        
        if (x != 0.0f)
        {
          glBegin(GL_LINE_LOOP);
          for (int angle = 0; angle < 360; angle += 30)
            glVertex2f( x + cos (angle * 0.017453f) * 1.5f, 0.0f + sin (angle * 0.017453f) * 1.5f);
        }
        else
        {
          glBegin(GL_LINES);
          glVertex2f(0.0f, -2.0f);
          glVertex2f(0.0f,  2.0f);
        }
        glEnd();
      }
      glEndList();
    }
*/
  }
}

void gs_loc_bar::draw()
{
/*
    glCallList(m_glId);  // draw scale stockscene
    glColor3fv(Magenta); // TODO turns amber when excessive deviation
    if (fabs(m_angle) > 1.0f) {
      glLineWidth(3.0);
      glBegin(GL_LINE_LOOP);
    }
    else {
      glBegin(GL_POLYGON);
    }
    glVertex2f(m_angle*24.0, 1.8f);
    glVertex2f(m_angle*24.0 +3.3, 0.0f);
    glVertex2f(m_angle*24.0, -1.8f);
    glVertex2f(m_angle*24.0 -3.3, 0.0f);
    glEnd();
    glLineWidth(1.0);
*/
}

void gs_loc_bar::angle(float a)
{
  /*
  localizer:  5 ticks, maximum +- 2.5 degrees
  glidescope: 5 ticks, maximum +- 0.7 degrees
  
  scale range such that localizer and glidescope min and max are at +- 1, and extend a 
  little beyond that range so that the needle stops beyond the last tick
  */
  m_angle = (a < 0.0f ? std::max(a, -1.15f * m_maxangle) : std::min(a, 1.15f * m_maxangle)) / m_maxangle;
}
