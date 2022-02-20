/* ------------------------------------------------------------------   */
/*      item            : ClimbPerformance.cxx
        made by         : jcomans
        from template   : hmigauge_component.cxx
        template made by: Joost Ellerbroek
        date            : 081013
        category        : body file 
        description     :
        changes         : 081013 first version
        language        : C++
*/

#include "ClimbPerformance.hxx"

#include <hmi.hxx>

#include "ColorMap.hpp"
#include "GLTools.hxx"
#include "Math.hxx"

namespace
{
  const float half_vertical_fov  = deg2rad(20.0f);
  const float half_gauge_height  = 280.0f;

  const float distance_to_projection = half_gauge_height / tan(half_vertical_fov);

  const float current_bar_width = 30.0f;
  const float max_bar_width     = 50.0f;

  const float current_bar_x_begin = 27.0f;
  const float current_bar_x_end   = current_bar_x_begin + current_bar_width;


  
  const float max_bar_x_begin = current_bar_x_end;
  const float max_bar_x_end   = max_bar_x_begin + max_bar_width;

  
};

ClimbPerformance::ClimbPerformance() :
  hmi::GaugeComponent("ClimbPerformance")
{

}

ClimbPerformance::~ClimbPerformance()
{

}

void ClimbPerformance::Init()
{
}

void ClimbPerformance::Render()
{
  if(*GetData().performance_data_valid == false) return;
  
  const float pitch   = *GetData().pitch;
  const float roll    = *GetData().roll;

  const float gamma_max             = *GetData().gamma_max;
  const float gamma_max_full_thrust = *GetData().gamma_max_full_thrust;

  const float gl_y_current_translation = distance_to_projection * tan( gamma_max             - pitch );
  const float gl_y_max_translation     = distance_to_projection * tan( gamma_max_full_thrust - pitch );

  const float gl_z_rotation = rad2deg(roll);


  {
    GLSaveMatrix current_matrix_state;
    GLLineWidth  line_width(4.0f);
    GLLineSmooth line_smooth;
    
    hmi::Colour::PaletteColour(cn_performance);

    glRotatef( gl_z_rotation , 0.0f, 0.0f, 1.0f);

    // Draw the current max climb angle
    {
      GLSaveMatrix rotated_state;
      glTranslatef( 0.0f, gl_y_current_translation, 0.0f );
      {
	GLBegin lines(GL_LINES);
	glVertex2f(  current_bar_x_begin, 0.0f );
	glVertex2f(  current_bar_x_end  , 0.0f );

	glVertex2f( -current_bar_x_begin, 0.0f );
	glVertex2f( -current_bar_x_end  , 0.0f );
      }
    }

    // Draw the max climb angle at full power
    {
      GLSaveMatrix rotated_state;
      glTranslatef( 0.0f, gl_y_max_translation, 0.0f );
      {
	GLBegin lines(GL_LINES);
	glVertex2f(  max_bar_x_begin, 0.0f );
	glVertex2f(  max_bar_x_end  , 0.0f );

	glVertex2f( -max_bar_x_begin, 0.0f );
	glVertex2f( -max_bar_x_end  , 0.0f );
      }
    }
    
  }
}
