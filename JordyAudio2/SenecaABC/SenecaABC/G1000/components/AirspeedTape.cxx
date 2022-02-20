/* ------------------------------------------------------------------   */
/*      item            : AirspeedTape.cxx
        made by         : jcomans
        from template   : hmigauge_component.cxx
        template made by: Joost Ellerbroek
        date            : 081013
        category        : body file
        description     :
        changes         : 081013 first version
        language        : C++
*/

#include "AirspeedTape.hxx"

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
  const float digit_text_size = 0.38f;

  ////////////////////////////////////////////////////////////
  // The background box
  ////////////////////////////////////////////////////////////
  const float box_width  =  90.0f;
  const float box_height = 340.0f;
  const GLRectangle airspeed_box(-box_height/2.0f, box_height/2.0f, 0.0f, box_width);

  ////////////////////////////////////////////////////////////
  // The Vtas box
  ////////////////////////////////////////////////////////////
  const float vtas_box_top    = -box_height/2.0f;
  const float vtas_box_bottom =  vtas_box_top - 23.0f;
  const float vtas_box_left   =  0.0f;
  const float vtas_box_right  =  box_width;

  const float vtas_box_center = vtas_box_left   + (vtas_box_right - vtas_box_left ) /2.0f;
  const float vtas_box_middle = vtas_box_bottom + (vtas_box_top - vtas_box_bottom ) /2.0f;

  const GLRectangle vtas_box(vtas_box_bottom,vtas_box_top,vtas_box_left,vtas_box_right);

  ////////////////////////////////////////////////////////////
  // The MCP Speed box
  ////////////////////////////////////////////////////////////
  const float mcp_box_bottom = box_height/2.0f  ;
  const float mcp_box_top    = mcp_box_bottom  + 25.0f;

  const float mcp_box_left   =  0.0f;
  const float mcp_box_right  =  box_width;

  const float mcp_box_center = mcp_box_left   + (mcp_box_right - mcp_box_left ) /2.0f;
  const float mcp_box_middle = mcp_box_bottom + (mcp_box_top - mcp_box_bottom ) /2.0f;

  const GLRectangle mcp_box(mcp_box_bottom,mcp_box_top,mcp_box_left,mcp_box_right);

  ////////////////////////////////////////////////////////////
  // The moving airspeed tape
  ////////////////////////////////////////////////////////////
  const float airspeed_range_kts    = 60.0f;
  const float large_tick_resolution = 10.0f;
  const float small_tick_resolution = large_tick_resolution / 2.0f;
  const float tape_pixel_resolution = box_height/airspeed_range_kts;

  const float large_tick_width = 20.0f;
  const float small_tick_width = 10.0f;

  // Declaration of the class that will render the tape label
  class AirspeedLabelPolicy
  {
  public:
      static void print_label(float airspeed, float x, float y);
  };
  // Convenience typdef
  typedef VerticalTape<AirspeedLabelPolicy> GLAirspeedTape;
  // The actual tape
  const GLAirspeedTape airspeed_tape( box_width, box_height,
				      GLAirspeedTape::right,
				      large_tick_resolution, small_tick_resolution,
				      tape_pixel_resolution,
				      large_tick_width, small_tick_width);

  ////////////////////////////////////////////////////////////
  // The speed target
  ////////////////////////////////////////////////////////////
  const float target_left   = box_width -15.0f;
  const float target_right  = box_width;
  const float target_top    =  15.0f;
  const float target_bottom = -15.0f;

  const float target_indent_left   =  box_width - 5.0f;
  const float target_indent_top    =  5.0f;
  const float target_indent_bottom = -5.0f;

  const GLRectangle target_rectangle(target_bottom , target_top,
                                     target_indent_left   , target_right);

  const GLQuad target_top_quad( target_indent_left , target_top,
                                target_left        , target_top,
                                target_left        , target_indent_top,
                                target_indent_left , 0.0f);

  const GLQuad target_bottom_quad( target_indent_left , target_bottom,
                                   target_left        , target_bottom,
                                   target_left        , target_indent_bottom,
                                   target_indent_left , 0.0f);

  ////////////////////////////////////////////////////////////
  // The airspeed ticker
  ////////////////////////////////////////////////////////////
  // The black background box consists of a triangle and two boxes
  const float triangle_right  = box_width -  5.0f;
  const float triangle_left   = box_width - 15.0f;
  const float triangle_top    =              5.0f;
  const float triangle_bottom =             -5.0f;

  const float ones_box_right  = box_width - 15.0f;
  const float ones_box_left   = box_width - 35.0f;
  const float ones_box_top    =             34.0f;
  const float ones_box_bottom =            -34.0f;

  const float tens_box_right  = box_width - 35.0f;
  const float tens_box_left   = box_width - 83.0f;
  const float tens_box_top    =             21.0f;
  const float tens_box_bottom =            -21.0f;

  const GLTriangle index_triangle( triangle_right , 0.0f ,
				   triangle_left  , triangle_top ,
				   triangle_left  , triangle_bottom );

  const GLRectangle ones_box( ones_box_bottom , ones_box_top,
			      ones_box_left   , ones_box_right );

  const GLRectangle tens_box( tens_box_bottom , tens_box_top,
			      tens_box_left   , tens_box_right );

  // The first digit on the right is a normal continuous rotary
  const float ones_label_resolution =  1.0f;
  const float ones_value_resolution =  1.0f;
  const float ones_min_label        =  0.0f;
  const float ones_max_label        =  9.0f;
  const float ones_stiction         =  0.0f;
  const float ones_spacing_px       = 35.0f;

  const float ones_bbox_width  = 20.0f;
  const float ones_bbox_height = ones_box_top - ones_box_bottom - 2.0f;
  const float ones_bbox_xpos   = ones_box_right - ones_bbox_width + 2.0f;
  const float ones_bbox_ypos   = 0.0f;
  const float ones_text_size   = digit_text_size;

  const size_t ones_field_width = 1;
  const size_t ones_fill_char   = ' ';

  const RotaryDigit ones_rotary( ones_label_resolution, ones_value_resolution,
				 ones_min_label, ones_max_label,
				 ones_stiction,
				 ones_spacing_px,
				 ones_bbox_width, ones_bbox_height,
				 ones_bbox_xpos, ones_bbox_ypos,
				 ones_text_size, ones_field_width, ones_fill_char );

  // The remaining digits give tens of airspeed with sticktion
  const float tens_label_resolution =  1.0f;
  const float tens_value_resolution = 10.0f;
  const float tens_min_label        =  0.0f;
  const float tens_max_label        = 40.0f;
  const float tens_stiction         =  9.0f;
  const float tens_spacing_px       = 35.0f;

  const float tens_bbox_width  = 40.0f;
  const float tens_bbox_height = tens_box_top - tens_box_bottom - 2.0f;
  const float tens_bbox_xpos   = tens_box_right - tens_bbox_width + 2.0f;
  const float tens_bbox_ypos   = 0.0f;
  const float tens_text_size   = digit_text_size;

  const size_t tens_field_width = 2;
  const size_t tens_fill_char   = ' ';

  const RotaryDigit tens_rotary( tens_label_resolution, tens_value_resolution,
				 tens_min_label, tens_max_label,
				 tens_stiction,
				 tens_spacing_px,
				 tens_bbox_width, tens_bbox_height,
				 tens_bbox_xpos, tens_bbox_ypos,
				 tens_text_size, tens_field_width, tens_fill_char );

  ////////////////////////////////////////////////////////////
  // Optimum climb angle
  ////////////////////////////////////////////////////////////
  const float speed_resolution = box_height / airspeed_range_kts;
  const float tick_width       = 20.0f;

  bool prev_clogged_pt = false;
  bool prev_clogged_sp = false;
  float V1_ias;
  float V1_tas;
  float dp;
  float p1;
  float p2;
  float p3;
  float p4;
  float q1;
  float q1_tas;
  float prevVias = 0;
  float Vias;
};

AirspeedTape::AirspeedTape() :
  hmi::GaugeComponent("AirspeedTape")
{

}

AirspeedTape::~AirspeedTape()
{

}

void AirspeedTape::Init()
{
}

void AirspeedTape::Render()
{

  float Vias_kts = ms2kts(*data.Vias);
  float Vtas_kts = round( ms2kts(*data.Vtas) );
  const float altitude = *data.altitude;
  const float dt = *data.dt;

  const float Vc_gamma_max_kts = ms2kts( *data.Vc_gamma_max );

  const float speed_target = *data.speed_target;

  const float Vmin_kts = 63;//ms2kts(*data.Vmin);
  const float Vmax_kts = 163;//ms2kts(*data.Vmax);
  const int curVerticalState = *data.curVerticalState;
  const float vtasdot = *data.vtasdot;

  const bool clogged_sp = *data.clogged_sp;
  const bool clogged_pt = *data.clogged_pt;
  const bool ADC_failure = *data.ADC_failure;

  if (abs(Vias_kts-Vias)<5){
    Vias = prevVias + dt/1.0*(Vias_kts - prevVias);
    Vias_kts = Vias;
  } else{
    Vias = Vias_kts;
  }
  prevVias = Vias;


  if(prev_clogged_pt == false && clogged_pt == true){
    V1_ias = Vias_kts/1.944;
    V1_tas = Vtas_kts/1.944;
    p1 = calc_p(altitude);
    q1 = 0.5*1.225*V1_ias*V1_ias;
    q1_tas = 0.5*1.225*V1_tas*V1_tas;
  }
  if(clogged_pt){
    p2 = calc_p(altitude);
    dp = p1-p2;
    Vias_kts = sqrt((2*(dp+q1))/1.225)*1.944;
    Vtas_kts = sqrt((2*(dp+q1_tas))/1.225)*1.944;
  }
  prev_clogged_pt = clogged_pt;


  if(prev_clogged_sp == false && clogged_sp == true){
    p3 = calc_p(altitude);

  }
  if(clogged_sp){
    p4 = calc_p(altitude);
    dp = p4-p3;
    Vias_kts = sqrt((2*(dp+(0.5*1.225*Vias_kts/1.944*Vias_kts/1.944)))/1.225)*1.944;
    Vtas_kts = sqrt((2*(dp+(0.5*1.225*Vtas_kts/1.944*Vtas_kts/1.944)))/1.225)*1.944;
  }
  prev_clogged_sp = clogged_sp;


  ////////////////////////////////////////////////////////////
  // Draw the background box
  ////////////////////////////////////////////////////////////
  if(ADC_failure == false){

  {
    GLBlend blend;

    hmi::Colour::PaletteColour(cn_background, 0.3);
    airspeed_box.drawFill();

    hmi::Colour::PaletteColour(cn_outline);
    airspeed_box.drawOutline();
  }

  ////////////////////////////////////////////////////////////
  // Draw the speed limits
  ////////////////////////////////////////////////////////////
  {
    const float limits_right = box_width;
    const float limits_left  = limits_right - 7.0f;
    const float limits_left_f = limits_right - 4.0f;

    const float limits_bottom = -Vias_kts*speed_resolution;
    const float limits_gmin   = (63  - Vias_kts) * speed_resolution;
    const float limits_gmax   = (163 - Vias_kts) * speed_resolution;
    const float limits_rmin   = (195 - Vias_kts) * speed_resolution;
    const float limits_fmin   = (61  - Vias_kts) * speed_resolution;
    const float limits_fmax   = (107 - Vias_kts) * speed_resolution;
    const float limits_top    = 300;

    const GLRectangle limits_vmin_rect(limits_bottom, limits_gmin,
                                       limits_left, limits_right);

    const GLRectangle limits_vnorm_rect(limits_gmin, limits_gmax,
                                        limits_left, limits_right);
    const GLRectangle limits_vyellow_rect(limits_gmax, limits_rmin,
                                        limits_left, limits_right);

    const GLRectangle limits_vmax_rect(limits_rmin, limits_top,
                                       limits_left, limits_right);


    const GLRectangle limits_flaps_rect(limits_fmin, limits_fmax,
                                        limits_left_f, limits_right);
    GLStencilMask box_mask;
    airspeed_box.drawFill();
    box_mask.finish();

    hmi::Colour::PaletteColour(cn_normal);
    limits_vnorm_rect.drawFill();

    hmi::Colour::PaletteColour(cn_refbar);
    limits_vyellow_rect.drawFill();

    hmi::Colour::PaletteColour(cn_danger);
    limits_vmin_rect.drawFill();
    limits_vmax_rect.drawFill();

    hmi::Colour::PaletteColour(cn_foreground);
    limits_flaps_rect.drawFill();
  }

  ////////////////////////////////////////////////////////////
  // Draw the airspeed tape
  ////////////////////////////////////////////////////////////
  {
    hmi::Colour::PaletteColour(cn_foreground);
    GLLineWidth(2.0f);

    airspeed_tape.render(Vias_kts);

  }

  ////////////////////////////////////////////////////////////
  // Draw the ticker
  ////////////////////////////////////////////////////////////
  {
    if (Vias_kts <195){
      hmi::Colour::PaletteColour(cn_background);
    } else{
      hmi::Colour::PaletteColour(cn_danger);
    }

    index_triangle.drawFill();
    ones_box.drawFill();
    tens_box.drawFill();

    hmi::Colour::PaletteColour(cn_foreground);
    ones_rotary.render( fmod(Vias_kts, 10.0f) );
    tens_rotary.render( Vias_kts );
  }
  ////////////////////////////////////////////////////////////
  // Draw the trend vector
  ////////////////////////////////////////////////////////////
  if(Vtas_kts>40)
  {
    hmi::Colour::PaletteColour(cn_nav);
    GLLineWidth line_width(2.0f);
    GLBegin lines(GL_LINES);
    glVertex2f(box_width-1.0f, 0.0f);
    glVertex2f(box_width-1.0f, clipValue((vtasdot*1.9438f *6.0f)*speed_resolution,-box_height/2,box_height/2));
  }

  ////////////////////////////////////////////////////////////
  // Draw the optimal climb speed tick
  ////////////////////////////////////////////////////////////
  {
    GLSaveMatrix state;
    GLBlend blend;
    GLLineWidth width(2.0f);

    const float block_height = tick_width * 0.75f;
    const float block_width  = block_height;

    const float gl_x_left   = box_width;
    const float gl_x_middle = gl_x_left + tick_width*0.25f;
    const float gl_x_right  = gl_x_left + tick_width;

    const float gl_y = clipValue( (89 - Vias_kts) * speed_resolution,
				  -box_height/2, box_height/2 );

    const float gl_y_top      = gl_y + block_height / 2.0f;
    const float gl_y_bottom   = gl_y - block_height / 2.0f;

    const float text_x = gl_x_middle + block_width/2.0f;
    const float text_y = gl_y;

    hmi::Colour::PaletteColour(cn_background);

    GLTriangle indicator( gl_x_left   , gl_y,
			  gl_x_middle , gl_y_top,
			  gl_x_middle , gl_y_bottom );

    GLQuad block( gl_x_middle , gl_y_bottom,
		  gl_x_right  , gl_y_bottom,
		  gl_x_right  , gl_y_top,
		  gl_x_middle , gl_y_top );

    indicator.drawFill();
    block.drawFill();

    hmi::Colour::PaletteColour(cn_active);

    HMIText text(hmi::FontManager::Get(0));
    text.position(text_x,text_y).hcenter().vcenter().size(0.2);
    text << "x";
    text.draw();
  }

  ////////////////////////////////////////////////////////////
  // Draw the speed target
  ////////////////////////////////////////////////////////////

  if(curVerticalState==5)
  {
    const float y_coord = clipValue( (speed_target - Vias_kts) * speed_resolution,
                                     -box_height/2, box_height/2);

    GLSaveMatrix matrix_state;

    glTranslatef(0.0f, y_coord, 0.0f);

    hmi::Colour::PaletteColour(cn_active);
    target_rectangle.drawFill();
    target_bottom_quad.drawFill();
    target_top_quad.drawFill();
  }

  ////////////////////////////////////////////////////////////
  // Draw the qnh box
  ////////////////////////////////////////////////////////////
  {
    GLSaveMatrix matrix_state;
    hmi::Colour::PaletteColour(cn_background);
    vtas_box.drawFill();

    hmi::Colour::PaletteColour(cn_outline);
    vtas_box.drawOutline();

    hmi::Colour::PaletteColour(cn_foreground);
    HMIText text(hmi::FontManager::Get(2));

    text.position( vtas_box_left,vtas_box_middle ).padding(2.0,0.0).vcenter().left().size(0.165);
    text << "TAS " << std::fixed << std::setprecision(0) << setw(3) << setfill(' ') << Vtas_kts;
    text.draw();

    text.clear().position(vtas_box_right,vtas_box_bottom).padding(-2.0,5.0).bottom().right().size(0.14);
    text << "KT";
    text.draw();
  }

  ////////////////////////////////////////////////////////////
  // Draw the mcp box
  ////////////////////////////////////////////////////////////
  if(curVerticalState==5)
  {
    GLSaveMatrix matrix_state;
    hmi::Colour::PaletteColour(cn_background);
    mcp_box.drawFill();

    hmi::Colour::PaletteColour(cn_outline);
    mcp_box.drawOutline();

    hmi::Colour::PaletteColour(cn_active);
    HMIText text(hmi::FontManager::Get(2));
    text.position( mcp_box_center,mcp_box_middle ).vcenter().hcenter().size(0.18);
    text << static_cast<int>(speed_target);
    text.draw();

    text.clear().position( mcp_box_center+28,mcp_box_middle-1 ).vcenter().hcenter().size(0.14);
    text << "KT";
    text.draw();
  }
}else{
  GLBlend blend;
  glColor4f(0.255, 0.2, 0.2, 0.8);
  airspeed_box.drawFill();

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
  airspeed_box.drawOutline();
}
}

namespace {
  void AirspeedLabelPolicy::print_label(float airspeed, float x, float y)
  {
    if( airspeed < 0.0f ) return;

    HMIText text(hmi::FontManager::Get(0));
    text.position(x,y).padding(-5.0,0.0).right().vcenter().size(0.3);
    text << setw(3) << setfill(' ') << airspeed;
    text.draw();
  }
};

float AirspeedTape::calc_p(float h){
    const float p0 = 101325;
    const float T0 = 288.15;
    const float g = 9.80665;
    const float R = 287;
    const float a = -0.0065;

    return p0 * pow(((T0 + a * h)/T0),-(g/(a*R)));
}
