/* ------------------------------------------------------------------   */
/*      item            : PitchLadder.cxx
        made by         : jcomans
        from template   : hmigauge_component.cxx
        template made by: Joost Ellerbroek
        date            : 081013
        category        : body file 
        description     :
        changes         : 081013 first version
        language        : C++
*/

#include "PitchLadder.hxx"

#include <hmi.hxx>

#include "ColorMap.hpp"
#include "GLTools.hxx"
#include "Math.hxx"

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
using namespace std;

// Define local constants that can be used to tweak the rendering
namespace {
  const float half_vertical_fov  = deg2rad(20.0f);
  const float half_gauge_height  = 280.0f;

  const float gl_pitch_scaling = half_gauge_height / half_vertical_fov;

  const float distance_to_projection = half_gauge_height / tan( half_vertical_fov );

  const float half_large_tick_width = 55.0f;
  const float half_small_tick_width =  0.55f * half_large_tick_width;
  const float half_tiny_tick_width  =  0.55f * half_small_tick_width;

  const float text_padding = 5.0f;
};

PitchLadder::PitchLadder() :
  hmi::GaugeComponent("PitchLadder"),
  _gl_display_list_index(0),
  _font(0)
{

}

PitchLadder::~PitchLadder()
{
  glDeleteLists(_gl_display_list_index,1);
}

void PitchLadder::Init()
{
  // See if we can get a display list index
  _gl_display_list_index = glGenLists(1);

  if(!_gl_display_list_index) throw "Unable to get GL display list";

  // Initialize the font
  _font = hmi::FontManager::Get(0);
  if(!_font) throw "Unable to get the font!";
}

void PitchLadder::Render()
{
  // Define the data we will use for rendering
  const float& pitch = *GetData().pitch;
  const float& roll  = *GetData().roll;

  const float gl_z_rotation    =  rad2deg(roll);

  _font->SetSize(0.18,0.18); // No idea what the units are, magic number!
  _font->SetSmooth(true);

  // Create a scope for the matrix state
  {
    GLSaveMatrix original_state;

    {
      GLStencilMask stencil_mask(false);
      GLRectangle(0.0f, distance_to_projection* tan(deg2rad(-8.0f)), -190.0f, 190.0f ).drawFill();

      {
      	GLBegin triangle_fan(GL_TRIANGLE_FAN);

      	glVertex2f(0.0f,0.0f);
      	circlePoints(190.0, deg2rad(-90.0f), deg2rad(-30.0f), 6);
      	circlePoints(190.0, deg2rad( 30.0f), deg2rad( 90.0f), 6);
      }
      
      stencil_mask.finish();
      
      glRotatef( gl_z_rotation, 0.0f, 0.0f, 1.0f);
          
      hmi::Colour::PaletteColour(cn_foreground);
      GLLineSmooth line_smooth;
      GLLineWidth  line_width(1.5f);

      if( pitch > deg2rad(90.0f) || pitch < deg2rad(-90.0f) ) return;

      // 10 deg tick marks have a text label
      drawLadder( pitch, half_large_tick_width, deg2rad( 10.0f), deg2rad( 10.0f), 9 ,true  );
      drawLadder( pitch, half_large_tick_width, deg2rad(-10.0f), deg2rad(-10.0f), 9 ,true  );

      // 5 deg tick marks have a text label
      drawLadder( pitch, half_small_tick_width, deg2rad( 10.0f), deg2rad(  5.0f), 9 ,true );
      drawLadder( pitch, half_small_tick_width, deg2rad(-10.0f), deg2rad( -5.0f), 9 ,true );

      // 5 deg tick marks have a text label
      drawLadder( pitch, half_tiny_tick_width, deg2rad( 5.0f), deg2rad(  2.5f), 18 ,false );
      drawLadder( pitch, half_tiny_tick_width, deg2rad(-5.0f), deg2rad( -2.5f), 18 ,false );
    }

  }
}

void PitchLadder::drawLadder(float pitch,
			     float half_tick_width, float spacing,
			     float start_tick,  size_t n_ticks,
			     bool draw_labels)
{
  for(size_t current_tick_index=0 ; current_tick_index < n_ticks ; ++current_tick_index)
  {
    // Calculate current pitch and corresponding offset
    const float tick_pitch_angle = start_tick + current_tick_index * spacing;
    const float gl_y_translation = distance_to_projection*tan( -pitch + tick_pitch_angle);

    
    // For now, hardcode use of absolute pitch value for label
    stringstream ss;
    ss << fabs(rad2deg(tick_pitch_angle));
    const string tick_pitch_string = ss.str();
    {
      GLSaveMatrix current_matrix_state;

      glTranslatef( 0.0f, gl_y_translation, 0.0f );
      glBegin(GL_LINES);
      glVertex2f( -half_tick_width, 0.0f );
      glVertex2f(  half_tick_width, 0.0f );
      glEnd();

      if(draw_labels)
      {
	_font->Print( -(half_tick_width+text_padding) , 0.0, tick_pitch_string,
		      hmi::Font::RIGHT|hmi::Font::VCENTER);
	_font->Print(  (half_tick_width+text_padding) , 0.0, tick_pitch_string,
		       hmi::Font::LEFT|hmi::Font::VCENTER);
      }
    }
    
  }
}
