/* ------------------------------------------------------------------   */
/*      item            : BankIndicator.cxx
        made by         : jcomans
        from template   : hmigauge_component.cxx
        template made by: Joost Ellerbroek
        date            : 081013
        category        : body file
        description     :
        changes         : 081013 first version
        language        : C++
*/

#include "BankIndicator.hxx"

#include <hmi.hxx>

#include "ColorMap.hpp"
#include "GLTools.hxx"
#include "Math.hxx"

#include <boost/bind.hpp>
#include <algorithm>

namespace {
  const float Lambda = 0.5f;
  float Slip = 0.0f;
  float m_slip = 0.0f;

  const float arc_radius = 190.0f;

  const float triangle_height     = 22.0f;
  const float half_triangle_width = triangle_height / 2.0f;

  const float large_tick_length = triangle_height;
  const float small_tick_length = large_tick_length * 0.6f;

  const float large_tick_list[] = { -60.0f , -30.0f , 30.0f , 60.0f };
  const size_t n_large_ticks    = sizeof(large_tick_list) / sizeof(float);

  const float small_tick_list[] = { -45.0f , -20.0f , -10.0f , 10.0f , 20.0f , 45.0f };
  const size_t n_small_ticks    = sizeof(small_tick_list) / sizeof(float);

  void draw_tick(float angle_deg, float tick_length);
};

BankIndicator::BankIndicator() :
  GaugeComponent("BankIndicator"),
  _gl_display_list_index(0)
{
}

BankIndicator::~BankIndicator()
{
  glDeleteLists(_gl_display_list_index,1);
}

void BankIndicator::Init()
{
  // See if we can get a display list index
  _gl_display_list_index = glGenLists(1);

  if(!_gl_display_list_index) throw "Unable to get GL display list";


  ////////////////////////////////////////////////////////////
  // Compile the display list
  glNewList( _gl_display_list_index, GL_COMPILE);

  {
    GLLineSmooth line_smooth;
    GLLineWidth  line_width(2.0f);

    // Draw the ticks
    std::for_each( &large_tick_list[0],
		   &large_tick_list[n_large_ticks],
		   boost::bind(draw_tick, _1, large_tick_length ));

    std::for_each( &small_tick_list[0],
		   &small_tick_list[n_small_ticks],
		   boost::bind(draw_tick, _1, small_tick_length ));

    // Draw the triangle
    {
      GLSaveMatrix original_state;
      glTranslatef( 0.0f, arc_radius, 0.0f);

      glBegin(GL_TRIANGLES);
      glVertex2f( 0.0f , 0.0f );
      glVertex2f( -half_triangle_width , triangle_height );
      glVertex2f(  half_triangle_width , triangle_height );
      glEnd();
    }

    // Draw the circle
    glBegin(GL_LINE_STRIP);
    ///TODO: Properly deal with floating point limits
    circlePoints( arc_radius, deg2rad(-60.0f), deg2rad(60.0f), 60 );
    glEnd();
  }

  glEndList();
  ////////////////////////////////////////////////////////////
}

void BankIndicator::Render()
{
  const float& roll         = *GetData().roll;
  const float Y_fycg = *GetData().Y_fycg;
  const float gl_z_rotation =  rad2deg(roll);

  hmi::Colour::PaletteColour(cn_foreground);

  {
    GLSaveMatrix original_state;

    // Draw the static part first
    glTranslatef( 0.0f, arc_radius, 0.0f);

    glBegin(GL_TRIANGLES);
    glVertex2f( 0.0f , 0.0f );
    glVertex2f( -half_triangle_width , -triangle_height );
    glVertex2f(  half_triangle_width , -triangle_height );
    glEnd();
  }

  {
    GLSaveMatrix original_state;

    // Dynamic part
    glRotatef( gl_z_rotation, 0.0f, 0.0f, 1.0f);
    glCallList(_gl_display_list_index);
  }

  {
    Slip = (1.0f-Lambda)*Slip + Lambda * Y_fycg*-0.1;
    m_slip =  rad2deg(Slip) / 15.0f;
    GLBegin polygon(GL_POLYGON);
    glVertex2f(-13.0f + 100.0f * m_slip, arc_radius-triangle_height -5.0f);
    glVertex2f( 13.0f + 100.0f * m_slip, arc_radius-triangle_height -5.0f);
    glVertex2f( 12.0f + 100.0f * m_slip, arc_radius-triangle_height -2.0f);
    glVertex2f(-12.0f + 100.0f * m_slip, arc_radius-triangle_height -2.0f);
    //glEnd();

  }

}

namespace {
  void draw_tick(float angle_deg, float tick_length)
  {
    GLSaveMatrix original_state;

    glRotatef( angle_deg , 0.0f, 0.0f, 1.0f );
    glTranslatef( 0.0f, arc_radius, 0.0f);

    glBegin(GL_LINES);
    glVertex2f( 0.0f, 0.0f);
    glVertex2f( 0.0f, tick_length);
    glEnd();
  }
};
