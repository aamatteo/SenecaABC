/* ------------------------------------------------------------------   */
/*      item            : FlightPathVector.cxx
        made by         : jcomans
        from template   : hmigauge_component.cxx
        template made by: Joost Ellerbroek
        date            : 081013
        category        : body file 
        description     :
        changes         : 081013 first version
        language        : C++
*/

#include "FlightPathVector.hxx"

#include <hmi.hxx>

#include "ColorMap.hpp"
#include "GLTools.hxx"
#include "Math.hxx"

#include <iostream>
using namespace std;

namespace {
  const float half_vertical_fov  = deg2rad(20.0f);
  const float half_gauge_height  = 280.0f;

  //const float gl_pitch_scaling = half_gauge_height / half_vertical_fov;
  const float distance_to_projection = half_gauge_height / tan(half_vertical_fov);

  const float arc_radius = 12.0f;
  const float long_stem_length  = 15.0f;
  const float short_stem_length =  8.0f;
};

FlightPathVector::FlightPathVector() :
  hmi::GaugeComponent("FlightPathVector")
{

}

FlightPathVector::~FlightPathVector()
{

}

void FlightPathVector::Init()
{
}

void FlightPathVector::Render()
{
  const float pitch   = *GetData().pitch;
  const float roll    = *GetData().roll;
  const float heading = *GetData().heading;
  const float gamma   = *GetData().gamma;
  const float chi     = *GetData().chi;

  //cout << pitch << "\t" << gamma << "\t" << heading << "\t" << chi << endl;

  const float gl_x_translation = distance_to_projection * tan( chi - heading );
  const float gl_y_translation = distance_to_projection * tan( gamma - pitch );
  const float gl_z_rotation    = rad2deg(roll);

  {
    GLSaveMatrix current_matrix_state;
    GLLineWidth  line_width(2.0f);
    GLLineSmooth line_smooth;
    
    hmi::Colour::PaletteColour(cn_performance);

    glRotatef( gl_z_rotation , 0.0f, 0.0f, 1.0f);
    glTranslatef( gl_x_translation, gl_y_translation, 0.0f );

    {
      GLBegin line_loop(GL_LINE_LOOP);
      circlePoints( arc_radius, deg2rad(0.0f), deg2rad(360.0f), 18 );
    }

    {
      glRotatef( -gl_z_rotation, 0.0f, 0.0f, 1.0f);
      GLBegin lines(GL_LINES);
      glVertex2f( arc_radius                  , 0.0f );
      glVertex2f( arc_radius+long_stem_length , 0.0f );

      glVertex2f( -arc_radius                  , 0.0f );
      glVertex2f( -arc_radius-long_stem_length , 0.0f );

      glVertex2f( 0.0f , arc_radius );
      glVertex2f( 0.0f , arc_radius + short_stem_length );
    }
  }
}
