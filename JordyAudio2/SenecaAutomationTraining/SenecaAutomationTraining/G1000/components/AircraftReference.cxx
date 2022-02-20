/* ------------------------------------------------------------------   */
/*      item            : AircraftReference.cxx
        made by         : jcomans
        from template   : hmigauge_component.cxx
        template made by: Joost Ellerbroek
        date            : 081013
        category        : body file
        description     :
        changes         : 081013 first version
        language        : C++
*/

#include "AircraftReference.hxx"
#include <hmi.hxx>
#include "ColorMap.hpp"
#include "GLTools.hxx"
#include "Math.hxx"

// Define local constants that can be used to tweak the rendering
namespace {

  float height;
  float old_height;
  float max_movement = 5.0f;

  const float half_reference_width         = 85.0f;
  const float reference_thickness          = 40.0f;
  const float reference_unshaded_pct       =  0.60f;

  const float reference_height = 30.0f;

  const float reference_outside = half_reference_width;
  const float reference_middle  = reference_outside - reference_thickness * reference_unshaded_pct;
  const float reference_inside  = reference_outside - reference_thickness;


  //const float reference_tip_height         = 30.0f;
  //const float reference_unshaded_thickness = 25.0f;


  const float bar_width          =  75.0f;
  const float half_bar_thickness =  10.0f / 2.0f;
  const float bar_tip_width      =   2.0f * half_bar_thickness;
  const float bar_x_offset       = 125.0f;

  const GLTriangle fd_left_upper( 0.0f, 0.0f,
    		                          -(half_reference_width + 5), -reference_thickness,
  		                            -(half_reference_width + 20), -(reference_thickness - 8));
  const GLTriangle fd_left_lower( -(half_reference_width + 5), -reference_thickness,
                                  -(half_reference_width + 20), -(reference_thickness - 8),
                                  -(half_reference_width + 20), -reference_thickness);
  const GLTriangle fd_right_upper( 0.0f, 0.0f,
    		                          half_reference_width + 5, -reference_thickness,
  		                            half_reference_width + 20, -(reference_thickness - 8));
  const GLTriangle fd_right_lower( half_reference_width + 5, -reference_thickness,
                                  half_reference_width + 20, -(reference_thickness - 8),
                                  half_reference_width + 20, -reference_thickness);

  const float half_vertical_fov  = deg2rad(20.0f);
  const float half_gauge_height  = 280.0f;
  const float distance_to_projection = half_gauge_height / tan( half_vertical_fov );

};

AircraftReference::AircraftReference() :
  hmi::GaugeComponent("AircraftReference"),
  _gl_display_list_index(0)
{
}

AircraftReference::~AircraftReference()
{
  glDeleteLists(_gl_display_list_index,1);
}

void AircraftReference::Init()
{
  // See if we can get a display list index
  _gl_display_list_index = glGenLists(1);

  if(!_gl_display_list_index) throw "Unable to get GL display list";

  ////////////////////////////////////////////////////////////
  // Compile the display list
  glNewList( _gl_display_list_index, GL_COMPILE);

  {
    GLPolygonSmooth polygon_smooth; // Not working at the time!
    GLLineSmooth line_smooth;

    GLLineWidth line_width(1.5);

    // Bottom part of the reference, gray/yellow
    hmi::Colour::PaletteColour(cn_refbar_dark);

    GLTriangle( 0.0f, 0.0f,
		-reference_middle , -reference_thickness,
		-reference_inside , -reference_thickness ).drawFill();

    GLTriangle( 0.0f, 0.0f,
		reference_middle , -reference_thickness,
		reference_inside , -reference_thickness ).drawFill();



    // Top part of the reference, bright yellow
    hmi::Colour::PaletteColour(cn_refbar);

    GLTriangle( 0.0f, 0.0f,
		-reference_outside , -reference_thickness,
		-reference_middle  , -reference_thickness ).drawFill();

    GLTriangle( 0.0f, 0.0f,
		reference_outside , -reference_thickness,
		reference_middle  , -reference_thickness ).drawFill();

    // Outline in black
    hmi::Colour::PaletteColour(cn_background);
    GLTriangle( 0.0f, 0.0f,
		-reference_outside , -reference_thickness,
		-reference_inside  , -reference_thickness ).drawOutline();

    GLTriangle( 0.0f, 0.0f,
		reference_outside , -reference_thickness,
		reference_inside  , -reference_thickness ).drawOutline();


    {
      // Draw the right horizontal bar
      GLSaveMatrix matrixstate;
      glTranslatef( bar_x_offset, 0.0f, 0.0f );

      // Top part bright yellow
      hmi::Colour::PaletteColour(cn_refbar);
      glBegin(GL_TRIANGLE_STRIP);
      glVertex2f(  0.0f, 0.0f );
      glVertex2f(  bar_tip_width ,  half_bar_thickness );
      glVertex2f(  bar_tip_width ,  0.0f               );
      glVertex2f(  bar_width     ,  half_bar_thickness );
      glVertex2f(  bar_width     ,  0.0f               );
      glEnd();

      // Bottom part gray/yellow
      hmi::Colour::PaletteColour(cn_refbar_dark);
      glBegin(GL_TRIANGLE_STRIP);
      glVertex2f(  0.0f, 0.0f );
      glVertex2f(  bar_tip_width , -half_bar_thickness );
      glVertex2f(  bar_tip_width ,  0.0f               );
      glVertex2f(  bar_width     , -half_bar_thickness );
      glVertex2f(  bar_width     ,  0.0f               );
      glEnd();
    }

    {
      // Draw the left horizontal bar
      GLSaveMatrix matrixstate;

      glTranslatef( -bar_x_offset, 0.0f, 0.0f );


      // Top part bright yellow
      hmi::Colour::PaletteColour(cn_refbar);
      glBegin(GL_TRIANGLE_STRIP);
      glVertex2f(  0.0f, 0.0f );
      glVertex2f( -bar_tip_width ,  half_bar_thickness );
      glVertex2f( -bar_tip_width ,  0.0f               );
      glVertex2f( -bar_width     ,  half_bar_thickness );
      glVertex2f( -bar_width     ,  0.0f               );
      glEnd();

      // Bottom part gary/yellow
      hmi::Colour::PaletteColour(cn_refbar_dark);
      glBegin(GL_TRIANGLE_STRIP);
      glVertex2f(  0.0f, 0.0f );
      glVertex2f( -bar_tip_width , -half_bar_thickness );
      glVertex2f( -bar_tip_width ,  0.0f               );
      glVertex2f( -bar_width     , -half_bar_thickness );
      glVertex2f( -bar_width     ,  0.0f               );
      glEnd();
    }
  }

  glEndList();
  ////////////////////////////////////////////////////////////
}

void AircraftReference::Render()
{
  const float pitch = rad2deg(*data.pitch);
  const float roll = rad2deg(*data.roll);
  const float theta_ref = *data.theta_ref;
  const float phi_ref = *data.phi_ref;
  const int APstate = *data.APstate;

  if(APstate !=0){
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
      
      glRotatef(- phi_ref + roll, 0.0f, 0.0f, 1.0f);
      {
        height = height = distance_to_projection * tan(deg2rad(theta_ref - pitch));
        old_height = drawFD(pitch, theta_ref, distance_to_projection, fd_left_upper, fd_right_upper, fd_left_lower, fd_right_lower, height, old_height);
        // old_height = height;
      }

    }
  }
  glCallList(_gl_display_list_index);
}

float AircraftReference::drawFD(float pitch, float theta_ref, float distance_to_projection, GLTriangle fd_left_upper, GLTriangle fd_right_upper, GLTriangle fd_left_lower, GLTriangle fd_right_lower, float height, float old_height){

  {
  GLSaveMatrix current_matrix_state;

  //std::cout<< fabs(height-old_height) << "\n";

  // if(fabs(height-old_height) < max_movement)
  // {
  //   glTranslatef( 0.0f, distance_to_projection * tan(deg2rad(theta_ref - pitch)), 0.0f );
  //   old_height = height;
  // } else{
  //   glTranslatef( 0.0f, old_height + SIGN(height)*max_movement, 0.0f );
  //   old_height = old_height + SIGN(height)*max_movement;
  //   //std::cout<<"slowing down FD";
  // }

  glTranslatef( 0.0f, distance_to_projection * tan(deg2rad(theta_ref - pitch)), 0.0f );



  hmi::Colour::PaletteColour(cn_nav);
  fd_left_upper.drawFill();
  fd_left_lower.drawFill();
  fd_right_upper.drawFill();
  fd_right_lower.drawFill();

  hmi::Colour::PaletteColour(cn_background);
  fd_left_upper.drawOutline();
  fd_left_lower.drawOutline();
  fd_right_upper.drawOutline();
  fd_right_lower.drawOutline();

  return 1.0;
  }
}
