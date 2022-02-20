/* ------------------------------------------------------------------   */
/*      item            : CompassRose.cxx
        made by         : jcomans
        from template   : hmigauge_component.cxx
        template made by: Joost Ellerbroek
        date            : 081013
        category        : body file
        description     :
        changes         : 081013 first version
        language        : C++
*/

#include "CompassRose.hxx"

#include <hmi.hxx>

#include "ColorMap.hpp"
#include "GLTools.hxx"
#include "HMITools.hxx"
#include "Math.hxx"

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <cmath>
using namespace std;

namespace {
  const float rose_radius = 145.0f;
  const float large_tick_length = 18.0f;
  const float small_tick_length = large_tick_length / 2.0f;

  const float plane_length = 40.0f;

  const float gl_y_front           =  plane_length * 5.0f/9.0f;
  const float gl_y_nose            =  plane_length * 4.0f/9.0f;
  const float gl_y_wingtaper_begin =  plane_length * 2.0f/9.0f;
  const float gl_y_wingtaper_end   =  plane_length * 1.0f/9.0f;
  const float gl_y_wing_end        =  0.0f;
  const float gl_y_tailtaper_begin = -plane_length * 2.4f/9.0f;
  const float gl_y_tailtaper_end   = -plane_length * 3.2f/9.0f;
  const float gl_y_tail_end        = -plane_length * 4.0f/9.0f;

  const float gl_x_center  = 0.0f;
  const float gl_x_body    = plane_length * 1.0f/9.0f;
  const float gl_x_wingtip = plane_length * 4.0f/9.0f;
  const float gl_x_tailtip = plane_length * 2.0f/9.0f;


    // Target box
  const float box_width = 90;
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

  const GLRectangle info_box(0.0f,27.0f,0.0f,78.0f);

  bool prev_GMU_failure;
  float frozen_heading;

};

CompassRose::CompassRose() :
    GaugeComponent("CompassRose"),
  _gl_display_list_index(0),
  _font(0)
{
}

CompassRose::~CompassRose()
{
  glDeleteLists(_gl_display_list_index,1);
}

void CompassRose::Init()
{
  // See if we can get a display list index
  _gl_display_list_index = glGenLists(1);

  if(!_gl_display_list_index) throw "Unable to get GL display list";

  // Initialize the font
  _font = hmi::FontManager::Get(0);
  if(!_font) throw "Unable to get the font!";

  // Create the display list for the static part
  glNewList(_gl_display_list_index+0,GL_COMPILE);
  {
    // Blocking part of the DME box. This is not optimal: if the pitch becomes
    // too high, this should actually become sky color...
    {
      hmi::Colour::PaletteColour(cn_ground);
      GLBegin triangle_fan(GL_TRIANGLE_FAN);
      glVertex2f( 0.0f, 0.0f );
      circlePoints(rose_radius*1.165, deg2rad(270.0f), deg2rad(230.0f), 36);
    }

    // The compass background
    GLBlend blend;
    hmi::Colour::PaletteColour(cn_background, 0.3);
    {
      GLBegin triangle_fan(GL_TRIANGLE_FAN);
      glVertex2f( 0.0f, 0.0f );
      circlePoints(rose_radius, deg2rad(0.0f), deg2rad(360.0f), 36);
    }

    // The plane symbol
    hmi::Colour::PaletteColour(cn_foreground);
    {
      GLBegin triangle(GL_TRIANGLES);
      glVertex2f( gl_x_center,  gl_y_front           );
      glVertex2f( gl_x_body,    gl_y_nose            );
      glVertex2f( gl_x_center,  gl_y_nose            );
    }
    {
      GLBegin quad(GL_QUADS);
      glVertex2f( gl_x_center,  gl_y_nose            );
      glVertex2f( gl_x_body,    gl_y_nose            );
      glVertex2f( gl_x_body,    gl_y_wingtaper_begin );
      glVertex2f( gl_x_center,  gl_y_wingtaper_begin );
    }
    {
      GLBegin polygon(GL_POLYGON);
      glVertex2f( gl_x_center,  gl_y_wingtaper_begin );
      glVertex2f( gl_x_body,    gl_y_wingtaper_begin );
      glVertex2f( gl_x_wingtip, gl_y_wingtaper_end   );
      glVertex2f( gl_x_wingtip, gl_y_wing_end        );
      glVertex2f( gl_x_center,  gl_y_wing_end        );
    }
    {
      GLBegin quad(GL_QUADS);
      glVertex2f( gl_x_center,  gl_y_wing_end        );
      glVertex2f( gl_x_body,    gl_y_wing_end        );
      glVertex2f( gl_x_body,    gl_y_tailtaper_begin );
      glVertex2f( gl_x_center,  gl_y_tailtaper_begin );
    }
    {
      GLBegin polygon(GL_POLYGON);
      glVertex2f( gl_x_center,  gl_y_tailtaper_begin );
      glVertex2f( gl_x_body,    gl_y_tailtaper_begin );
      glVertex2f( gl_x_tailtip, gl_y_tailtaper_end   );
      glVertex2f( gl_x_tailtip, gl_y_tail_end        );
      glVertex2f( gl_x_center,  gl_y_tail_end);
    }

    // Left side
    {
      GLBegin triangle(GL_TRIANGLES);
      glVertex2f( -gl_x_center,  gl_y_front           );
      glVertex2f( -gl_x_body,    gl_y_nose            );
      glVertex2f( -gl_x_center,  gl_y_nose            );
    }
    {
      GLBegin quad(GL_QUADS);
      glVertex2f( -gl_x_center,  gl_y_nose            );
      glVertex2f( -gl_x_body,    gl_y_nose            );
      glVertex2f( -gl_x_body,    gl_y_wingtaper_begin );
      glVertex2f( -gl_x_center,  gl_y_wingtaper_begin );
    }
    {
      GLBegin polygon(GL_POLYGON);
      glVertex2f( -gl_x_center,  gl_y_wingtaper_begin );
      glVertex2f( -gl_x_body,    gl_y_wingtaper_begin );
      glVertex2f( -gl_x_wingtip, gl_y_wingtaper_end   );
      glVertex2f( -gl_x_wingtip, gl_y_wing_end        );
      glVertex2f( -gl_x_center,  gl_y_wing_end        );
    }
    {
      GLBegin quad(GL_QUADS);
      glVertex2f( -gl_x_center,  gl_y_wing_end        );
      glVertex2f( -gl_x_body,    gl_y_wing_end        );
      glVertex2f( -gl_x_body,    gl_y_tailtaper_begin );
      glVertex2f( -gl_x_center,  gl_y_tailtaper_begin );
    }
    {
      GLBegin polygon(GL_POLYGON);
      glVertex2f( -gl_x_center,  gl_y_tailtaper_begin );
      glVertex2f( -gl_x_body,    gl_y_tailtaper_begin );
      glVertex2f( -gl_x_tailtip, gl_y_tailtaper_end   );
      glVertex2f( -gl_x_tailtip, gl_y_tail_end        );
      glVertex2f( -gl_x_center,  gl_y_tail_end);
    }

    // The index triangle
    hmi::Colour::PaletteColour(cn_foreground);
    {
      GLSaveMatrix matrix_state;
      glTranslatef(0.0f,rose_radius,0.0f);
      GLTriangle(0.0f,-10.0f, -8.0f,10.0f, 8.0f,10.0f).drawFill();
    }

    // The text field
    hmi::Colour::PaletteColour(cn_background);
    {

      GLSaveMatrix matrix_state;
      glTranslatef(0.0f,rose_radius+10.0f,0.0f);
      GLRectangle(0.0f,30.0f,-35.0f,35.0f).drawFill();
      hmi::Colour::PaletteColour(cn_outline);
      GLRectangle(0.0f,30.0f,-35.0f,35.0f).drawOutline();

    }
    {
      GLSaveMatrix matrix_state;
      glTranslatef(-176.0f,rose_radius-10.0f,0.0f);
      hmi::Colour::PaletteColour(cn_background);
      info_box.drawFill();
      hmi::Colour::PaletteColour(cn_outline);
      info_box.drawOutline();
    }
    {
      hmi::Colour::PaletteColour(cn_background);
      GLSaveMatrix matrix_state;
      glTranslatef(98.0f,rose_radius-10.0f,0.0f);
      info_box.drawFill();
      hmi::Colour::PaletteColour(cn_outline);
      info_box.drawOutline();
    }

    // The fixed outside ticks
    hmi::Colour::PaletteColour(cn_foreground);
    {
      GLLineSmooth antialias;
      GLLineWidth line_width(3.0f);

      for(float angle = 45.0f; angle<170.0f; angle+=45.0f )
      {
	{
	  GLSaveMatrix matrix_state;
	  glRotatef(angle,0.0f,0.0f,1.0f);
	  glTranslatef(0.0f,rose_radius+2.0,0.0f);
	  GLBegin lines(GL_LINES);
	  glVertex2f(0.0f,0.0f);
	  glVertex2f(0.0f,large_tick_length);
	}
	{
	  GLSaveMatrix matrix_state;
	  glRotatef(-angle,0.0f,0.0f,1.0f);
	  glTranslatef(0.0f,rose_radius+2.0,0.0f);
	  GLBegin lines(GL_LINES);
	  glVertex2f(0.0f,0.0f);
	  glVertex2f(0.0f,large_tick_length);
	}
      }
    }

  // Fixed turnrate ticks
  {
    GLSaveMatrix matrix_state;
    GLLineSmooth antialias;
    GLLineWidth line_width(2.0f);
    GLBegin lines(GL_LINES);
    glVertex2f((rose_radius + 2.0f) * sin(deg2rad(20.0f)), (rose_radius + 2.0f) * cos(deg2rad(20.0f)));
    glVertex2f((rose_radius + 17.0f) * sin(deg2rad(20.0f)), (rose_radius + 17.0f) * cos(deg2rad(20.0f)));
  }
  {
    GLSaveMatrix matrix_state;
    GLLineSmooth antialias;
    GLLineWidth line_width(2.0f);
    GLBegin lines(GL_LINES);
    glVertex2f((rose_radius + 2.0f) * sin(deg2rad(-20.0f)), (rose_radius + 2.0f) * cos(deg2rad(-20.0f)));
    glVertex2f((rose_radius + 17.0f) * sin(deg2rad(-20.0f)), (rose_radius + 17.0f) * cos(deg2rad(-20.0f)));
  }
  {
    GLSaveMatrix matrix_state;
    GLLineSmooth antialias;
    GLLineWidth line_width(2.0f);
    GLBegin lines(GL_LINES);
    glVertex2f((rose_radius + 2.0f) * sin(deg2rad(10.0f)), (rose_radius + 2.0f) * cos(deg2rad(10.0f)));
    glVertex2f((rose_radius + 12.0f) * sin(deg2rad(10.0f)), (rose_radius + 12.0f) * cos(deg2rad(10.0f)));
  }
  {
    GLSaveMatrix matrix_state;
    GLLineSmooth antialias;
    GLLineWidth line_width(2.0f);
    GLBegin lines(GL_LINES);
    glVertex2f((rose_radius + 2.0f) * sin(deg2rad(-10.0f)), (rose_radius + 2.0f) * cos(deg2rad(-10.0f)));
    glVertex2f((rose_radius + 12.0f) * sin(deg2rad(-10.0f)), (rose_radius + 12.0f) * cos(deg2rad(-10.0f)));
  }

  }
  glEndList();
}

void CompassRose::Render()
{
  float heading = *GetData().heading;
  const float hdg_bug = *GetData().hdg_bug;
  const float course = *GetData().course;
  const int active_nav_source = *GetData().active_nav_source;
  const float turn_rate = *GetData().turn_rate;
  const float GMU_failure = *GetData().GMU_failure;

  if(GMU_failure && prev_GMU_failure == false){
    frozen_heading = heading;
  }
  if(GMU_failure){
    heading = frozen_heading;
  }
  prev_GMU_failure = GMU_failure;

  // Turn turn_rate
  hmi::Colour::PaletteColour(cn_nav);
  {
    GLLineSmooth antialias;
    GLLineWidth line_width(3.0f);
    glBegin(GL_LINE_STRIP);
    circlePoints( rose_radius+3.0f, 0.0f, deg2rad(turn_rate/3.0f*20.0f), 60 );
    glEnd();
  }


  glCallList( _gl_display_list_index + 0 );

  {
    GLSaveMatrix state;
    glRotatef( rad2deg(heading) , 0.0f, 0.0f, 1.0f);
    ////////////////////////////////////////////////////////////
    // Draw the dynamic parts
    ////////////////////////////////////////////////////////////
    {
      hmi::Colour::PaletteColour(cn_foreground);
      GLLineSmooth antialias;
      GLLineWidth line_width(1.5f);
      // Short ticks first
      {
	GLBegin lines(GL_LINES);
	for(float step=0.0;step<deg2rad(360.0f);step+=deg2rad(5.0f))
	{
	  if( fmod(step,10.0f) < 0.0001 ) continue;
	  glVertex2f( rose_radius*sin(step) , rose_radius*cos(step) );
	  glVertex2f( (rose_radius-small_tick_length)*sin(step),
		      (rose_radius-small_tick_length)*cos(step) );
	}
      }
      // Long ticks next
      {

	for(float step=0.0;step<deg2rad(360.0f);step+=deg2rad(10.0f))
	{
	  addText(step);

	  GLBegin lines(GL_LINES);
	  glVertex2f( rose_radius*sin(step) , rose_radius*cos(step) );
	  glVertex2f( (rose_radius-large_tick_length)*sin(step),
		      (rose_radius-large_tick_length)*cos(step) );
	}
      }

    GLSaveMatrix matrix_state;
    glRotatef( -90.0f-hdg_bug , 0.0f, 0.0f, 1.0f);
    {
    glTranslatef(-1.5*rose_radius-1, 0.0f, 0.0f);

    hmi::Colour::PaletteColour(cn_active);
    target_rectangle.drawFill();
    target_bottom_quad.drawFill();
    target_top_quad.drawFill();
    }
    }
  }



  // Put the heading in the textbox
  hmi::Colour::PaletteColour(cn_foreground);
  int integer_course = static_cast<int>( course);

  HMIText text(_font);

  if(GMU_failure == false){
    int integer_heading = static_cast<int>( ::round(rad2deg(heading)));
    if(integer_heading == 0) integer_heading = 360;

    text.position(-5.0,rose_radius+26).hcenter().vcenter().size(0.30);
    text << setw(3) << setfill('0') << (integer_heading % 360 + 360) %360;
    text.draw();

    HMIText text(hmi::FontManager::Get(2));
    text.position(26.0,rose_radius+32).hcenter().vcenter().size(0.15);
    text.cleartext() << "o";
    text.draw();

  } else{
    {
      GLSaveMatrix matrix_state;
      glColor4f(0.255, 0.2, 0.2, 1.0);
      GLRectangle(10.0f+rose_radius,40.0f+rose_radius,-35.0f,35.0f).drawFill(); //0.0f,30.0f,-35.0f,35.0f

      glColor3f(1.0, 0.0, 0.0);
      GLLineSmooth antialias;
      GLLineWidth line_width(2.0f);
      {
        GLBegin lines(GL_LINES);
        glVertex2f(-34.0f, 39.0f+rose_radius);
        glVertex2f(34.0f, 11.0f+rose_radius);
      }
      {
        GLBegin lines(GL_LINES);
        glVertex2f(-34.0f, 11.0f+rose_radius);
        glVertex2f(34.0f, 39.0f+rose_radius);
      }

      {
        GLLineWidth line_width(1.0f);
        hmi::Colour::PaletteColour(cn_outline);
        GLRectangle(10.0f+rose_radius,40.0f+rose_radius,-35.0f,35.0f).drawOutline();
      }
      text.position(26.0,rose_radius+32).hcenter().vcenter().size(0.15);
    }
  }

  {
   hmi::Colour::PaletteColour(cn_foreground);
   text.position(-158.0f, rose_radius + 4 ).vcenter().left().size(0.16);
   text.cleartext() << "HDG";
   text.draw();

   text.position(114.0f, rose_radius + 4).vcenter().left().size(0.16);
   text.cleartext() << "CRS";
   text.draw();

   hmi::Colour::PaletteColour(cn_active);
   text.position(-126.0f, rose_radius + 4 ).vcenter().left().size(0.20);
   text.cleartext() << setw(3) << setfill('0') << hdg_bug;
   text.draw();

   switch(active_nav_source){
   case 0:
      hmi::Colour::PaletteColour(cn_nav);
      break;
   case 1:
      hmi::Colour::PaletteColour(cn_apmode);
      break;
   case 2:
      hmi::Colour::PaletteColour(cn_apmode);
      break;
   }

   text.position(148.0f, rose_radius + 4 ).vcenter().left().size(0.20);
   text.cleartext() << std::fixed << std::setprecision(0) << std::setw(3) << std::setfill('0') << course;
   text.draw();

   hmi::Colour::PaletteColour(cn_foreground);
   HMIText text(hmi::FontManager::Get(2));

   hmi::Colour::PaletteColour(cn_active);
   text.position(-108.0f, rose_radius + 8 ).vcenter().left().size(0.13);
   text.cleartext() << "o";
   text.draw();

   switch(active_nav_source){
     case 0:
      hmi::Colour::PaletteColour(cn_nav);
      break;
    case 1:
      hmi::Colour::PaletteColour(cn_apmode);
      break;
    case 2:
      hmi::Colour::PaletteColour(cn_apmode);
      break;
   }
   text.position(166.0f, rose_radius + 8 ).vcenter().left().size(0.13);
   text.cleartext() << "o";
   text.draw();
  }

}

void CompassRose::addText(float heading)
{
  const int value = static_cast<int>( ::round(rad2deg(heading) / 10.0f));

  stringstream label;

  switch(value)
  {
  case 0:
  case 360:
    label << 'N';
    break;
  case 9:
    label << 'E';
    break;
  case 18:
    label << 'S';
    break;
  case 27:
    label << 'W';
    break;
  default:
    if( value%3 != 0 ) return;
    label << value;
    break;
  }

  HMIText text(_font);
  text.position(0.0f, rose_radius-large_tick_length).padding(0.0f,-5.0f).hcenter().top().size(0.30);
  text << label.str();
  GLSaveMatrix push_matrix;
  glRotatef(rad2deg(-heading),0.0f,0.0f,1.0f);
  text.draw();
}
