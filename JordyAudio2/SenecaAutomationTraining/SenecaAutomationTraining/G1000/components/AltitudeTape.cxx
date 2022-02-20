/* ------------------------------------------------------------------   */
/*      item            : AltitudeTape.cxx
        made by         : jcomans
        from template   : hmigauge_component.cxx
        template made by: Joost Ellerbroek
        date            : 081013
        category        : body file
        description     :
        changes         : 081013 first version
        language        : C++
*/

#include "AltitudeTape.hxx"

#include <iomanip>

#include <hmi.hxx>

#include "ColorMap.hpp"
#include "GLTools.hxx"
#include "HMITools.hxx"
#include "Math.hxx"

using std::setw;
using std::setfill;

// Variables and objects that determine the size and position of
// the elements.
namespace {
  ////////////////////////////////////////////////////////////
  // The background box
  ////////////////////////////////////////////////////////////
  const float box_width  = 105.0f;
  const float box_height = 340.0f;
  const GLRectangle altitude_box(-box_height/2.0f, box_height/2.0f, 0.0f, box_width);

  ////////////////////////////////////////////////////////////
  // The QNH box
  ////////////////////////////////////////////////////////////
  const float qnh_box_top    = -box_height/2.0f;
  const float qnh_box_bottom =  qnh_box_top - 25.0f;
  const float qnh_box_left   =  0.0f;
  const float qnh_box_right  =  box_width;

  const float qnh_box_center = qnh_box_left   + (qnh_box_right - qnh_box_left ) /2.0f;
  const float qnh_box_middle = qnh_box_bottom + (qnh_box_top - qnh_box_bottom ) /2.0f;

  const GLRectangle qnh_box(qnh_box_bottom,qnh_box_top,qnh_box_left,qnh_box_right);

  ////////////////////////////////////////////////////////////
  // The Glideslope box
  ////////////////////////////////////////////////////////////
  const float gsbox_height = 108.0f;
  const float gsbox_width = 21.0f;

  const GLRectangle gstop_box(0,gsbox_height,-gsbox_width,0.0f);
  const GLRectangle gsbottom_box(0,-gsbox_height,-gsbox_width,0.0f);
  const GLRectangle gsletter_box(gsbox_height+1,gsbox_height + 26.0f, -gsbox_width, 0.0f);

  const GLRectangle gs_diamond(2.0f, 13.0f, -13.0f, -2.0f);
  ////////////////////////////////////////////////////////////
  // The MCP Altitude box
  ////////////////////////////////////////////////////////////
  const float mcp_box_bottom = box_height/2.0f  ;
  const float mcp_box_top    = mcp_box_bottom  + 25.0f;

  const float mcp_box_left   =  0.0f;
  const float mcp_box_right  =  box_width;

  const float mcp_box_center = mcp_box_left   + (mcp_box_right - mcp_box_left ) /2.0f;
  const float mcp_box_middle = mcp_box_bottom + (mcp_box_top - mcp_box_bottom ) /2.0f;

  const GLRectangle mcp_box(mcp_box_bottom,mcp_box_top,mcp_box_left,mcp_box_right);

  const float altv_box_bottom = mcp_box_bottom + 25.0f/2;
  const float altv_box_top = altv_box_bottom + 25.0f;
  const float altv_box_left = mcp_box_right+2;
  const float altv_box_right = altv_box_left+box_width*0.75f;
  const float altv_box_center = altv_box_left + (altv_box_right - altv_box_left) /2.0f;
  const float altv_box_middle = altv_box_bottom + (altv_box_top - altv_box_bottom) /2.0f;

  const GLRectangle altv_box(altv_box_bottom,altv_box_top,altv_box_left,altv_box_right);

  ////////////////////////////////////////////////////////////
  // The moving altitude tape
  ////////////////////////////////////////////////////////////
  const float altitude_range_ft     = 600.f;
  const float large_tick_resolution = 100.0f;
  const float small_tick_resolution = large_tick_resolution / 5.0f;
  const float tape_pixel_resolution = box_height/altitude_range_ft;

  const float small_tick_width =   8.0f;
  const float large_tick_width  = 18.0f;

  const float altitude_resolution = box_height / altitude_range_ft;

  // Declaration of the class that will render the tape labels
  class AltitudeLabelPolicy
  {
  public:
    static void print_label(float altitude, float x, float y);
  };
  // Convenience typdef
  typedef VerticalTape<AltitudeLabelPolicy> GLAltitudeTape;
  // The actual tape
  const GLAltitudeTape altitude_tape( box_width, box_height,
				      GLAltitudeTape::left,
				      large_tick_resolution, small_tick_resolution,
				      tape_pixel_resolution,
				      large_tick_width, small_tick_width);

  ////////////////////////////////////////////////////////////
  // The altitude target
  ////////////////////////////////////////////////////////////
  const float target_left   = 0.0f;
  const float target_right  = 15.0f;
  const float target_top    =  15.0f;
  const float target_bottom = -15.0f;

  const float target_indent_left   =  5.0f;
  const float target_indent_top    =  5.0f;
  const float target_indent_bottom = -5.0f;

  const GLRectangle target_rectangle(target_bottom , target_top,
                                     target_left   , target_indent_left);

  const GLQuad target_top_quad( target_indent_left , target_top,
                                target_right       , target_top,
                                target_right       , target_indent_top,
                                target_indent_left , 0.0f);

  const GLQuad target_bottom_quad( target_indent_left , target_bottom,
                                   target_right       , target_bottom,
                                   target_right       , target_indent_bottom,
                                   target_indent_left , 0.0f);

  ////////////////////////////////////////////////////////////
  // The altitude ticker
  ////////////////////////////////////////////////////////////
  // The black background box consists of a triangle and two boxes
  const float triangle_left   =  5.0f;
  const float triangle_right  = 15.0f;
  const float triangle_top    =  5.0f;
  const float triangle_bottom = -5.0f;

  const float hundreds_box_left   =  15.0f;
  const float hundreds_box_right  =  68.0f;
  const float hundreds_box_top    =  21.0f;
  const float hundreds_box_bottom = -21.0f;

  const float twenties_box_left   =  68.0f;
  const float twenties_box_right  = 100.0f;
  const float twenties_box_top    =  34.0f;
  const float twenties_box_bottom = -34.0f;


  const GLTriangle  index_triangle( triangle_left  , 0.0f ,
				    triangle_right , triangle_top ,
				    triangle_right , triangle_bottom );

  const GLRectangle hundreds_box(  hundreds_box_bottom , hundreds_box_top,
				   hundreds_box_left   , hundreds_box_right );

  const GLRectangle twenties_box( twenties_box_bottom , twenties_box_top,
				  twenties_box_left   , twenties_box_right );

  // The rightmost rotary indicates the tens of altitude in a continous
  // rotary fashing. Altitudes are labeled in 20ft increments
  const float twenties_label_resolution = 20.0f;
  const float twenties_value_resolution = 20.0f;
  const float twenties_min_label        =  0.0f;
  const float twenties_max_label        = 80.0f;
  const float twenties_stiction         =  0.0f;
  const float twenties_spacing_px       = 30.0f;

  const float twenties_bbox_width  = 32.0f;
  const float twenties_bbox_height = twenties_box_top - twenties_box_bottom;
  const float twenties_bbox_xpos   = twenties_box_right - twenties_bbox_width + 2.0f;
  const float twenties_bbox_ypos   = 0.0f;
  const float twenties_text_size   = 0.28f;

  const size_t twenties_field_width = 2;
  const char   twenties_fill_char   = '0';

  const RotaryDigit twenties_rotary( twenties_label_resolution, twenties_value_resolution,
				     twenties_min_label, twenties_max_label,
				     twenties_stiction,
				     twenties_spacing_px,
				     twenties_bbox_width, twenties_bbox_height,
				     twenties_bbox_xpos, twenties_bbox_ypos,
				     twenties_text_size, twenties_field_width, twenties_fill_char );

  // The center rotary indicates the hundreds of altitude in a 'jumpy' fashion.
  // The digit doesn't move down until the difference to the next digit is
  // 20 ft. This is done by setting a stiction of 80 with a resolution of 100
  const float hundreds_label_resolution =   1.0f;
  const float hundreds_value_resolution = 100.0f;
  const float hundreds_min_label        =   0.0f;
  const float hundreds_max_label        =   9.0f;
  const float hundreds_stiction         =  80.0f;
  const float hundreds_spacing_px       =  30.0f;

  const float hundreds_bbox_width  = twenties_bbox_width/2.0f;
  const float hundreds_bbox_height = hundreds_box_top - hundreds_box_bottom - 2.0f;
  const float hundreds_bbox_xpos   = hundreds_box_right - hundreds_bbox_width + 2.0f;
  const float hundreds_bbox_ypos   = twenties_bbox_ypos;
  const float hundreds_text_size   = twenties_text_size;

  const size_t hundreds_field_width = 1;
  const char   hundreds_fill_char   = ' ';

  const RotaryDigit hundreds_rotary( hundreds_label_resolution, hundreds_value_resolution,
				     hundreds_min_label, hundreds_max_label,
				     hundreds_stiction,
				     hundreds_spacing_px,
				     hundreds_bbox_width, hundreds_bbox_height,
				     hundreds_bbox_xpos, hundreds_bbox_ypos,
				     hundreds_text_size, hundreds_field_width, hundreds_fill_char );

  // The left rotary indicates the thousands of altitude in 'jumpy' fashion as above
  const float thousands_label_resolution =    1.0f;
  const float thousands_value_resolution = 1000.0f;
  const float thousands_min_label        =    0.0f;
  const float thousands_max_label        =  120.0f;
  const float thousands_stiction         =  980.0f;
  const float thousands_spacing_px       =   35.0f;

  const float thousands_bbox_width  = 40.0f;
  const float thousands_bbox_height = hundreds_bbox_height;
  const float thousands_bbox_xpos   = hundreds_bbox_xpos - thousands_bbox_width + 2.0f;
  const float thousands_bbox_ypos   = twenties_bbox_ypos;
  const float thousands_text_size   = 0.38f;

  const size_t thousands_field_width = 2;
  const char   thousands_fill_char   = ' ';

  const RotaryDigit thousands_rotary( thousands_label_resolution, thousands_value_resolution,
				      thousands_min_label, thousands_max_label,
				      thousands_stiction,
				      thousands_spacing_px,
				      thousands_bbox_width, thousands_bbox_height,
				      thousands_bbox_xpos, thousands_bbox_ypos,
				      thousands_text_size, thousands_field_width, thousands_fill_char );

  bool prev_clogged_sp;
  float frozen_altitude;
};



AltitudeTape::AltitudeTape() :
  hmi::GaugeComponent("AltitudeTape")
{
}

AltitudeTape::~AltitudeTape()
{
}

void AltitudeTape::Init()
{
}

void AltitudeTape::Render()
{
  float altitude_ft     = *data.altitude/0.3048;
  const float altitude_target = *data.altitude_target;
  const float altitude_target_vnav = *data.altitude_target_vnav;
  const int curVerticalState = *data.curVerticalState;
  const float nav_R = *data.nav_R;
  const float vnav_R = *data.vnav_R;
  const float hdot = *data.hdot;
  const bool ADC_failure = *data.ADC_failure;
  const bool clogged_sp = *data.clogged_sp;
  ////////////////////////////////////////////////////////////
  // Draw the altitude tape box
  ////////////////////////////////////////////////////////////
  if(prev_clogged_sp == false && clogged_sp){
    frozen_altitude = altitude_ft;
  }
  if(clogged_sp){
    altitude_ft = frozen_altitude;
  }
  prev_clogged_sp = clogged_sp;

  if(ADC_failure == false){
  {

    GLBlend blend;

    hmi::Colour::PaletteColour(cn_background, 0.3);
    altitude_box.drawFill();

    hmi::Colour::PaletteColour(cn_outline);
    altitude_box.drawOutline();
  }

  ////////////////////////////////////////////////////////////
  // Draw the altitude tape itself
  ////////////////////////////////////////////////////////////
  {
    hmi::Colour::PaletteColour(cn_foreground);
    GLLineWidth(2.0f);

    altitude_tape.render(altitude_ft);
  }

  ////////////////////////////////////////////////////////////
  // Draw the ticker
  ////////////////////////////////////////////////////////////
  {
    hmi::Colour::PaletteColour(cn_background);

    index_triangle.drawFill();

    hundreds_box.drawFill();
    twenties_box.drawFill();

    hmi::Colour::PaletteColour(cn_foreground);
    twenties_rotary.render(  fmod(altitude_ft,100.0f) );
    hundreds_rotary.render(  fmod(altitude_ft,1000.0f) );
    thousands_rotary.render( altitude_ft );
  }

  ////////////////////////////////////////////////////////////
  // Draw the trend vector
  ////////////////////////////////////////////////////////////
  {
    hmi::Colour::PaletteColour(cn_nav);
    GLLineWidth line_width(2.0f);
    GLBegin lines(GL_LINES);
    glVertex2f(1.0f, 0.0f);
    glVertex2f(1.0f, clipValue((hdot/0.3048f*6.0f)*altitude_resolution,-box_height/2, box_height/2));
  }

  ////////////////////////////////////////////////////////////
  // Draw the altitude target
  ////////////////////////////////////////////////////////////
  {
    const float y_coord = clipValue( (altitude_target - altitude_ft) * altitude_resolution,
                                     -box_height/2, box_height/2);

    GLSaveMatrix matrix_state;

    glTranslatef(0.0f, y_coord, 0.0f);

    hmi::Colour::PaletteColour(cn_active);
    target_rectangle.drawFill();
    target_bottom_quad.drawFill();
    target_top_quad.drawFill();
  }

  if(curVerticalState == 4){
    if(altitude_target_vnav != -1){
      GLSaveMatrix matrix_state;
      hmi::Colour::PaletteColour(cn_background);
      altv_box.drawFill();

      hmi::Colour::PaletteColour(cn_outline);
      altv_box.drawOutline();

      hmi::Colour::PaletteColour(cn_nav);
      HMIText text(hmi::FontManager::Get(2));
      text.position( altv_box_center,altv_box_middle ).vcenter().hcenter().size(0.16);
      text << altitude_target_vnav;
      text.draw();
    }
  {
    GLSaveMatrix matrix_state;
    hmi::Colour::PaletteColour(cn_background);
    gsletter_box.drawFill();



    hmi::Colour::PaletteColour(cn_outline);
    gstop_box.drawOutline();
    gsbottom_box.drawOutline();
    gsletter_box.drawOutline();

    {
      GLBlend blend;
      hmi::Colour::PaletteColour(cn_background, 0.3);
      gstop_box.drawFill();
      gsbottom_box.drawFill();
    }

    hmi::Colour::PaletteColour(cn_nav);
    HMIText text(hmi::FontManager::Get(2));
    text.position( altv_box_center-162.0f,altv_box_middle-74.0f ).vcenter().size(0.16);
    text << "V";
    text.draw();

    }

  {
  GLSaveMatrix matrix_state;

    hmi::Colour::PaletteColour(cn_foreground);
    {
    glTranslatef( -11.0f, 86.0f, 0.0f);
    glBegin(GL_LINE_STRIP);
    circlePoints( 4, deg2rad(0.0f), deg2rad(360.0f), 60 );
    glEnd();
    }
    {
    glTranslatef( 0.0f, -41.0f, 0.0f);
    glBegin(GL_LINE_STRIP);
    circlePoints( 4, deg2rad(0.0f), deg2rad(360.0f), 60 );
    glEnd();
    }
    {
    glTranslatef( 0.0f, -86.0f, 0.0f);
    glBegin(GL_LINE_STRIP);
    circlePoints( 4, deg2rad(0.0f), deg2rad(360.0f), 60 );
    glEnd();
    }
    {
    glTranslatef( 0.0f, -41.0f, 0.0f);
    glBegin(GL_LINE_STRIP);
    circlePoints( 4, deg2rad(0.0f), deg2rad(360.0f), 60 );
    glEnd();
    }
  }
  {
    GLSaveMatrix matrix_state;

    float diamond_location = (altitude_target_vnav + (vnav_R)*tan(deg2rad(2.5))/0.3048 -altitude_ft)/1000.0f*87.0f;//(altitude_target_vnav + tan(deg2rad(2.5f))*nav_R/0.3048f-altitude_ft)/1000.0f*87.0f;
    // if(diamond_location<gsbox_height-11 && diamond_location > -gsbox_height + 11){
    //   glTranslatef(0.0f, diamond_location, 0.0f);
    //   hmi::Colour::PaletteColour(cn_nav);
    //   glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
    //   gs_diamond.drawFill();
    // }
    if(diamond_location<gsbox_height-11 && diamond_location > -gsbox_height + 11){
      {
        hmi::Colour::PaletteColour(cn_nav);
        GLLineWidth line_width(4.0f);
        GLBegin lines(GL_LINES);
        glVertex2f(-18.0f, diamond_location);
        glVertex2f(-18.0f+sin(deg2rad(55.0f))*15.0f, diamond_location -cos(deg2rad(55.0f))*15.0f);
      }
      {
        hmi::Colour::PaletteColour(cn_nav);
        GLLineWidth line_width(4.0f);
        GLBegin lines(GL_LINES);
        glVertex2f(-18.0f, diamond_location);
        glVertex2f(-18.0f+sin(deg2rad(55.0f))*15.0f, diamond_location + cos(deg2rad(55.0f))*15.0f);
      }
    }
  }
  }

  ////////////////////////////////////////////////////////////
  // Draw the qnh box
  ////////////////////////////////////////////////////////////
  {
    GLSaveMatrix matrix_state;
    hmi::Colour::PaletteColour(cn_background);
    qnh_box.drawFill();

    hmi::Colour::PaletteColour(cn_outline);
    qnh_box.drawOutline();

    hmi::Colour::PaletteColour(cn_active);
    HMIText text(hmi::FontManager::Get(2));
    text.position( qnh_box_center,qnh_box_middle ).vcenter().hcenter().size(0.18);
    text << "29.92IN";
    text.draw();
  }

  ////////////////////////////////////////////////////////////
  // Draw the mcp box
  ////////////////////////////////////////////////////////////
  {
    GLSaveMatrix matrix_state;
    hmi::Colour::PaletteColour(cn_background);
    mcp_box.drawFill();

    hmi::Colour::PaletteColour(cn_outline);
    mcp_box.drawOutline();

    hmi::Colour::PaletteColour(cn_active);
    HMIText text(hmi::FontManager::Get(2));
    text.position( mcp_box_center,mcp_box_middle ).vcenter().hcenter().size(0.18);
    text << altitude_target;
    text.draw();
  }

}else{
  {
    GLBlend blend;
    glColor4f(0.255, 0.2, 0.2, 0.8);
    altitude_box.drawFill();

    glColor3f(1.0, 0.0, 0.0);
    GLLineSmooth antialias;
    GLLineWidth line_width(2.0f);
    {
      GLBegin lines(GL_LINES);
      glVertex2f(0.0f, box_height/2.0f);
      glVertex2f(box_width, -box_height/2.0f);
    }
    {
      GLBegin lines(GL_LINES);
      glVertex2f(box_width, box_height/2.0f);
      glVertex2f(0.0f, -box_height/2.0f);
    }
    hmi::Colour::PaletteColour(cn_outline);
    altitude_box.drawOutline();
  }
}
}

namespace {
  void AltitudeLabelPolicy::print_label(float altitude, float x, float y)
  {
    const float remainder = fmod(altitude,1000.0f);
    const float thousands = ( altitude - remainder) / 1000.0f;

    if(fabs(thousands) > 0.000001f )
    {
      HMIText text(hmi::FontManager::Get(2));
      text.position(x,y).padding(5.0,0.0).left().vcenter().size(0.26).smooth();
      text << fabs(thousands);
      BoundingBox bb = text.draw();

      const double xx = bb.x+bb.w;
      const double yy = bb.y-bb.h/2.0;

      text.clear().position(xx,yy).padding(-3.0,0.0).left().bottom().size(0.18).smooth();
      text << setw(3) << setfill('0') << fabs(remainder);
      text.draw();
    }
    else
    {
      HMIText text(hmi::FontManager::Get(2));
      text.position(x,y).padding(5.0,0.0).left().vcenter().size(0.18).smooth();
      text << remainder;
      text.draw();
    }

  }
};
