/* ------------------------------------------------------------------   */
/*      item            : VerticalSpeedTape.cxx
        made by         : jcomans
        from template   : hmigauge_component.cxx
        template made by: Joost Ellerbroek
        date            : 081013
        category        : body file
        description     :
        changes         : 081013 first version
        language        : C++
*/

#include "VerticalSpeedTape.hxx"

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
  float target_vs_gp = 0.0f;
  ////////////////////////////////////////////////////////////
  // The background boxes
  ////////////////////////////////////////////////////////////
  const float box_width           =  45.0f;
  const float box_height          = 160.0f;
  const float box_triangle_height =  30.0f;

  const GLQuad top_box( 0.0f      , 0.0f ,
			0.0f      , box_height,
			box_width , box_height ,
			box_width , box_triangle_height );

  const GLQuad bottom_box( 0.0f      ,  0.0f ,
			   0.0f      , -box_height,
			   box_width , -box_height ,
			   box_width , -box_triangle_height );

  const GLRectangle vertical_speed_box(-box_height, box_height, 0.0f, box_width);

  ////////////////////////////////////////////////////////////
  // The stationary VS tape
  ////////////////////////////////////////////////////////////
  //const float vertical_speed_range  = 2/70.
  const float large_tick_resolution = 1.0f;
  const float small_tick_resolution = large_tick_resolution / 2.0f;
  const float tape_pixel_resolution = 70.0f;
  //

  const float large_tick_width = 20.0f;
  const float small_tick_width = 10.0f;

  // Declaration of the class that will render the labels
  class VSLabelPolicy
  {
  public:
    static void print_label(float value, float x, float y);
  };
  // Convenience typdef
  typedef VerticalTape<VSLabelPolicy> GLVerticalSpeedTape;
  // The actual tape
  const GLVerticalSpeedTape vertical_speed_tape( box_width, 2*box_height,
						 GLVerticalSpeedTape::left,
						 large_tick_resolution, small_tick_resolution,
						 tape_pixel_resolution,
						 large_tick_width, small_tick_width );

   ////////////////////////////////////////////////////////////
   // The MCP Speed box
   ////////////////////////////////////////////////////////////
   const float mcp_box_bottom = 160;//box_height/2.0f  ;
   const float mcp_box_top    = 180;//mcp_box_bottom  + 25.0f;

   const float mcp_box_left   =  0.0f;
   const float mcp_box_right  =  box_width;

   const float mcp_box_center = mcp_box_left   + (mcp_box_right - mcp_box_left ) /2.0f;
   const float mcp_box_middle = mcp_box_bottom + (mcp_box_top - mcp_box_bottom ) /2.0f;

   const GLRectangle mcp_box(mcp_box_bottom,mcp_box_top,mcp_box_left,mcp_box_right);

   ////////////////////////////////////////////////////////////
   // The VS speed target
   ////////////////////////////////////////////////////////////
   const float target_left   = 0.0f;
   const float target_right  = 8.0f;
   const float target_top    =  10.0f;
   const float target_bottom = -10.0f;

   const float target_indent_left   =  2.0f;
   const float target_indent_top    =  6.0f;
   const float target_indent_bottom = -6.0f;

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
  // The moving indicator
  ////////////////////////////////////////////////////////////
  const float indicator_width          = 68.0f;
  const float indicator_triangle_width = 18.0f;
  const float indicator_height         = 22.0f;

  const float max_vs_movement     = 2100.0f;
  const float label_min_vs        = 100.0f;
  const float label_vs_resolution =  50.0f;

  GLTriangle indicator_tip( 0.0f , 0.0f,
			    indicator_triangle_width ,  indicator_height/2.0f,
			    indicator_triangle_width , -indicator_height/2.0f );

  GLRectangle indicator_rect( -indicator_height/2.0f, indicator_height/2.0f,
			 indicator_triangle_width, indicator_width );

  float prevVS;
  float VS;
};

VerticalSpeedTape::VerticalSpeedTape() :
    GaugeComponent("VerticalSpeedTape")
{

}

VerticalSpeedTape::~VerticalSpeedTape()
{

}

void VerticalSpeedTape::Init()
{
}

void VerticalSpeedTape::Render()
{
  float hdot_ftmin = m2ft(*data.hdot)*60.0f;
  const int curVerticalState = *data.curVerticalState;
  const float target_vs = *data.target_vs;
  const float Vtas = *data.Vtas;
  const bool ADC_failure = *data.ADC_failure;
  const bool clogged_sp = *data.clogged_sp;
  const float dt = *data.dt;

  if(clogged_sp){
    hdot_ftmin = prevVS;
  }


  VS = prevVS + dt/1.0*(hdot_ftmin - prevVS);
  hdot_ftmin = VS;
  prevVS = VS;


  ////////////////////////////////////////////////////////////
  // Draw the background boxes
  ////////////////////////////////////////////////////////////
  if(ADC_failure == false){

  {
    GLBlend blend;

    hmi::Colour::PaletteColour(cn_background, 0.3);
    top_box.drawFill();
    bottom_box.drawFill();

	  hmi::Colour::PaletteColour(cn_outline);
    top_box.drawOutline();
    bottom_box.drawOutline();
  }

  ////////////////////////////////////////////////////////////
  // Draw the stationary vertical speed tape
  ////////////////////////////////////////////////////////////
  {
    hmi::Colour::PaletteColour(cn_foreground);
    GLLineWidth(2.0);

    vertical_speed_tape.render();
  }

  ////////////////////////////////////////////////////////////
  // Draw the target vertical speed bars
  ////////////////////////////////////////////////////////////

  if(curVerticalState == 4){
    target_vs_gp = sin(deg2rad(-2.5f))*Vtas*196.9f;
    {
      hmi::Colour::PaletteColour(cn_nav);
      GLLineWidth line_width(3.0f);
      GLBegin lines(GL_LINES);
      glVertex2f(2.0f, target_vs_gp*70.0f/1000.0f);
      glVertex2f(sin(deg2rad(55.0f))*15, target_vs_gp*70.0f/1000.0f -cos(deg2rad(55.0f))*15);
    }
    {
      hmi::Colour::PaletteColour(cn_nav);
      GLLineWidth line_width(3.0f);
      GLBegin lines(GL_LINES);
      glVertex2f(2.0f, target_vs_gp*70.0f/1000.0f);
      glVertex2f(sin(deg2rad(55.0f))*15, target_vs_gp*70.0f/1000.0f + cos(deg2rad(55.0f))*15);
    }
  }

  if(curVerticalState == 2){
    // {
    //   hmi::Colour::PaletteColour(cn_active);
    //   GLLineWidth line_width(3.0f);
    //   GLBegin lines(GL_LINES);
    //   glVertex2f(2.0f, target_vs*70.0f/1000.0f);
    //   glVertex2f(sin(deg2rad(55.0f))*15, target_vs*70.0f/1000.0f -cos(deg2rad(55.0f))*15);
    // }
    // {
    //   hmi::Colour::PaletteColour(cn_active);
    //   GLLineWidth line_width(3.0f);
    //   GLBegin lines(GL_LINES);
    //   glVertex2f(2.0f, target_vs*70.0f/1000.0f);
    //   glVertex2f(sin(deg2rad(55.0f))*15, target_vs*70.0f/1000.0f + cos(deg2rad(55.0f))*15);
    // }
    GLSaveMatrix matrix_state;

    glTranslatef(0.0f, target_vs*70.0f/1000.0f, 0.0f);

    hmi::Colour::PaletteColour(cn_active);
    target_rectangle.drawFill();
    target_bottom_quad.drawFill();
    target_top_quad.drawFill();
  }


  ////////////////////////////////////////////////////////////
  // Draw the moving indicator
  ////////////////////////////////////////////////////////////
  {
    hmi::Colour::PaletteColour(cn_background);

    float gl_y_shift = 0.0f;
    if( fabs(hdot_ftmin) < max_vs_movement )
      gl_y_shift = hdot_ftmin * tape_pixel_resolution / 1000.0f;
    else
      gl_y_shift = SIGN(hdot_ftmin) * max_vs_movement * tape_pixel_resolution / 1000.0f;

    GLSaveMatrix matrix_state;
    glTranslatef(0.0f, gl_y_shift, 0.0f);
    indicator_tip.drawFill();
    indicator_rect.drawFill();

    if( fabs(hdot_ftmin) > label_min_vs )
    {
      hmi::Colour::PaletteColour(cn_foreground);
      HMIText text(hmi::FontManager::Get(2));
      text.position( indicator_width, 0.0f).padding(-2.0,0.0).right().vcenter().size(0.15);
      text <<  (int)(hdot_ftmin+25)/50*50;
      text.draw();
    }
  }

  ////////////////////////////////////////////////////////////
  // Display the target vertical speed in the box
  ////////////////////////////////////////////////////////////
  if(curVerticalState==2){
    GLSaveMatrix matrix_state;
    hmi::Colour::PaletteColour(cn_background);
    mcp_box.drawFill();

    hmi::Colour::PaletteColour(cn_outline);
    mcp_box.drawOutline();

    hmi::Colour::PaletteColour(cn_active);
    HMIText text(hmi::FontManager::Get(2));
    text.position( 20, 170 ).vcenter().hcenter().size(0.16);
    text << static_cast<int>(target_vs);
    text.draw();
  }



}else{
  GLBlend blend;
  glColor4f(0.255, 0.2, 0.2, 0.8);
  vertical_speed_box.drawFill();

  glColor3f(1.0, 0.0, 0.0);
  GLLineSmooth antialias;
  GLLineWidth line_width(2.0f);
  {
    GLBegin lines(GL_LINES);
    glVertex2f(0.0f, box_height);
    glVertex2f(box_width, -box_height);
  }
  {
    GLBegin lines(GL_LINES);
    glVertex2f(box_width, box_height);
    glVertex2f(0.0f, -box_height);
  }


  hmi::Colour::PaletteColour(cn_outline);
  top_box.drawOutline();
  bottom_box.drawOutline();
}
}
namespace {
  void VSLabelPolicy::print_label(float val, float x, float y)
  {
    const float value = fabs(val);

    if(value < 0.00001) return;

    HMIText text(hmi::FontManager::Get(0));
    text.position(x,y).padding(5.0,0.0).left().vcenter().size(0.28);
    text << setw(1) << value;
    text.draw();
  }
};
