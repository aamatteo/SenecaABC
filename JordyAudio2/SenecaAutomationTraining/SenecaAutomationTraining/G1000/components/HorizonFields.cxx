/* ------------------------------------------------------------------   */
/*      item            : HorizonFields.cxx
        made by         : jcomans
        from template   : hmigauge_component.cxx
        template made by: Joost Ellerbroek
        date            : 081013
        category        : body file
        description     :
        changes         : 081013 first version
        language        : C++
*/

#include "HorizonFields.hxx"

#include <hmi.hxx>

#include "ColorMap.hpp"
#include "GLTools.hxx"
#include "Math.hxx"

// Define local constants that can be used to tweak the rendering
namespace {
  const float half_vertical_fov   = deg2rad(20.0f);
  const float half_gauge_height   = 280.0f;

  const float half_horizon_width  = 1000.0f;
  const float half_horizon_height = 1000.0f;
};

HorizonFields::HorizonFields() :
  hmi::GaugeComponent("HorizonFields"),
  _gl_display_list_index(0)
{
}

HorizonFields::~HorizonFields()
{
  glDeleteLists(_gl_display_list_index,1);
}

void HorizonFields::Init()
{
  // See if we can get a display list index
  _gl_display_list_index = glGenLists(1);

  if(!_gl_display_list_index) throw "Unable to get GL display list";

  ////////////////////////////////////////////////////////////
  // Compile the display list
  glNewList( _gl_display_list_index, GL_COMPILE);

  hmi::Colour::PaletteColour(cn_sky);
  glBegin(GL_TRIANGLE_STRIP);
  glVertex2f( -half_horizon_width , half_horizon_height );
  glVertex2f( -half_horizon_width , 0.0f                );
  glVertex2f(  half_horizon_width , half_horizon_height );
  glVertex2f(  half_horizon_width , 0.0f                );
  glEnd();

  hmi::Colour::PaletteColour(cn_ground);
  glBegin(GL_TRIANGLE_STRIP);
  glVertex2f( -half_horizon_width , -half_horizon_height );
  glVertex2f( -half_horizon_width ,  0.0f                );
  glVertex2f(  half_horizon_width , -half_horizon_height );
  glVertex2f(  half_horizon_width ,  0.0f                );
  glEnd();

  glEndList();
  ////////////////////////////////////////////////////////////
}

void HorizonFields::Render()
{
    // Define the data we will use for rendering
  const float& pitch = *GetData().pitch;
  const float& roll  = *GetData().roll;

  //const float gl_y_translation = -pitch * half_gauge_height / half_vertical_fov;

  const float distance_to_projection = half_gauge_height / tan(half_vertical_fov);

  const float gl_y_translation = - distance_to_projection * tan( pitch );

  const float gl_z_rotation    =  rad2deg(roll);

  // Create a scope for the matrix state
  {
    GLSaveMatrix original_state;

    glRotatef( gl_z_rotation, 0.0f, 0.0f, 1.0f);
    glTranslatef( 0.0f, gl_y_translation, 0.0f);

    glCallList(_gl_display_list_index);
  }
}
