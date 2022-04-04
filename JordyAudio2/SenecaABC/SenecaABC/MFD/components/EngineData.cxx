/* ------------------------------------------------------------------   */
/*      item            : EngineData.cxx
        made by         : jcomans
        from template   : hmigauge_component.cxx
        template made by: Joost Ellerbroek
        date            : 081013
        category        : body file
        description     :
        changes         : 081013 first version
        language        : C++
*/

#include "EngineData.hxx"

// HMILib objects and functions
#include <hmi.hxx>

#include <iomanip>
#include <iostream>
#include <string>

#include "ColorMap.hpp"
#include "GLTools.hxx"
#include "HMITools.hxx"
#include "Math.hxx"

#include <GL/glut.h>

using namespace std;

struct DigitBar
{ float x0,y0,x1,y1, color;};

namespace
{

  const float block_width  = 145.0f;
  const float block_height = 706.0f;

  const GLRectangle engine_block(0.0f,-block_height,0.0f,block_width);

  float map_left = 0;
  float map_right = 0;
  float map_left_old = 0;
  float map_right_old = 0;

  const float Tdelay = 1.5;



};

EngineData::EngineData() :
    GaugeComponent("EngineData"){}

EngineData::~EngineData(){}

void EngineData::Init(){}

void EngineData::Render()
{
  // Get the data
  const float rpm_left = *data.rpm_left;
  const float rpm_right = *data.rpm_right;
  const float tl_left = *data.tl_left;
  const float tl_right = *data.tl_right;
  const float altitude = *data.altitude;

  const float u_map_l = tl_left*(1.225*pow(((288.15-0.0065*altitude)/288.15),(-9.81/(-0.0065*287)-1))*26.033-3.4993);
  const float u_map_r = tl_right*(1.225*pow(((288.15-0.0065*altitude)/288.15),(-9.81/(-0.0065*287)-1))*26.033-3.4993);

  const float dt = *data.dt;

  map_left = clipValue(map_left_old + dt*(-1/Tdelay * map_left_old + 1/Tdelay*u_map_l),10,35);
  map_right = clipValue(map_right_old + dt*(-1/Tdelay * map_right_old + 1/Tdelay*u_map_r),10,35);
  map_left_old= map_left;
  map_right_old= map_right;

  const float gauge_needle = 54;
  const float gauge_tick = 8;
  const float gauge_radius = 62;

  const float fflow_y = -338;
  const float cht_y = -400;
  const float temp_y = -462;
  const float pres_y = -524;
  const float amps_y = -586;// not actually used
  const float fuel_y = -586;// move up to make room for gear


  const GLTriangle triangle_l(-11.0f, 16.0f,
                              10.0f, 16.0f,
                              0.0f, 0.0f);
  const GLTriangle triangle_r(-11.0f, -16.0f,
                              10.0f, -16.0f,
                              0.0f, 0.0f);

  // index_triangle( triangle_left  , 0.0f ,
  //           triangle_right , triangle_top ,
  //           triangle_right , triangle_bottom );
  HMIText text(hmi::FontManager::Get(2));
  // const float itt_left  = *data.itt_left;
  // const float itt_right = *data.itt_right;

  // Draw the background box
  hmi::Colour::PaletteColour(cn_background);
  engine_block.drawFill();

  hmi::Colour::PaletteColour(cn_outline);
  engine_block.drawOutline();

  {
    GLSaveMatrix matrix_state;

    glTranslatef(0.0, -300.0, 0.0);
    glScalef(3.0f, 3.0f, 1.0f);

    //draw_fan_rpm(n1_left, n1_right);


  }

  {
    // RPM  dial
    GLSaveMatrix original_state;
    GLLineSmooth antialias;
    GLLineWidth  line_width(3.0f);
    hmi::Colour::PaletteColour(cn_foreground);
    glTranslatef( 73.0, -201.0f, 0.0f);
    hmi::FontManager::Get(1)->SetSize(0.13,0.13);
    hmi::FontManager::Get(1)->Print(-12,10, "RPM");
    hmi::FontManager::Get(1)->Print(-17,30, "3000");
    hmi::FontManager::Get(1)->Print(-37,-35, "0");
    hmi::FontManager::Get(1)->Print(27,-35, "0");

    text.clear().position(-40, -62).hcenter().vcenter().size(0.2);
    text << fixed << setw(4) << setfill(' ') << setprecision(0) << rpm_left;
    text.draw();

    text.clear().position(40, -62).hcenter().vcenter().size(0.2);
    text << fixed << setw(4) << setfill(' ') << setprecision(0) << rpm_right;
    text.draw();


    glBegin(GL_LINE_STRIP);
    circlePoints( gauge_radius, deg2rad(45.0f), deg2rad(135.0f), 60 );
    glEnd();
    glBegin(GL_LINE_STRIP);
    circlePoints( gauge_radius, deg2rad(-45.0f), deg2rad(-135.0f), 60 );
    glEnd();

    {
      GLLineWidth  line_width(2.0f);
      GLBegin lines(GL_LINES);
      for(float step=deg2rad(45.0f);step<deg2rad(136.0f);step+=deg2rad(15.0f))
      {
        if( fmod(step,10.0f) < 0.0001 ) continue;
        glVertex2f( gauge_radius*sin(step) , gauge_radius*cos(step) );
        glVertex2f( (gauge_radius-gauge_tick)*sin(step),
            (gauge_radius-gauge_tick)*cos(step) );
      }
    }
    {
      GLLineWidth  line_width(2.0f);
      GLBegin lines(GL_LINES);
      for(float step=deg2rad(225.0f);step<deg2rad(316.0f);step+=deg2rad(15.0f))
      {
        if( fmod(step,10.0f) < 0.0001 ) continue;
        glVertex2f( gauge_radius*sin(step) , gauge_radius*cos(step) );
        glVertex2f( (gauge_radius-gauge_tick)*sin(step),
            (gauge_radius-gauge_tick)*cos(step) );
      }
    }
    hmi::Colour::PaletteColour(cn_apmode);
    glBegin(GL_LINE_STRIP);
    circlePoints( gauge_radius, deg2rad(55.0f), deg2rad(105.0f), 60 );
    glEnd();
    glBegin(GL_LINE_STRIP);
    circlePoints( gauge_radius, deg2rad(-55.0f), deg2rad(-105.0f), 60 );
    glEnd();
    {
      GLLineWidth  line_width(3.0f);
      glColor3f(1.0, 0.0, 0.0);
      GLBegin lines(GL_LINES);
      glVertex2f( (gauge_radius+gauge_tick/2)*sin(deg2rad(50.0f)), (gauge_radius+gauge_tick/2)*cos(deg2rad(50.0f)) );
      glVertex2f( ((gauge_radius+gauge_tick/2)-gauge_tick)*sin(deg2rad(50.0f)), ((gauge_radius+gauge_tick/2)-gauge_tick)*cos(deg2rad(50.0f)) );
    }
    {
      GLLineWidth  line_width(3.0f);
      glColor3f(1.0, 0.0, 0.0);
      GLBegin lines(GL_LINES);
      glVertex2f( (gauge_radius+gauge_tick/2)*sin(deg2rad(-50.0f)), (gauge_radius+gauge_tick/2)*cos(deg2rad(-50.0f)) );
      glVertex2f( ((gauge_radius+gauge_tick/2)-gauge_tick)*sin(deg2rad(-50.0f)), ((gauge_radius+gauge_tick/2)-gauge_tick)*cos(deg2rad(-50.0f)) );
    }
    {
      hmi::Colour::PaletteColour(cn_foreground);
      GLBegin lines(GL_LINES);
      rpm_needle_left = rpm_left/3000.0f * 90.0f + 225.0f;
      glVertex2f( gauge_radius*sin(deg2rad(rpm_needle_left)) , gauge_radius*cos(deg2rad(rpm_needle_left)) );
      glVertex2f( (gauge_radius-gauge_needle)*sin(deg2rad(rpm_needle_left)), (gauge_radius-gauge_needle)*cos(deg2rad(rpm_needle_left)) );
    }
    {
      hmi::Colour::PaletteColour(cn_foreground);
      GLBegin lines(GL_LINES);
      rpm_needle_right = -rpm_right/3000.0f * 90.0f + 135.0f;
      glVertex2f( gauge_radius*sin(deg2rad(rpm_needle_right)) , gauge_radius*cos(deg2rad(rpm_needle_right)) );
      glVertex2f( (gauge_radius-gauge_needle)*sin(deg2rad(rpm_needle_right)), (gauge_radius-gauge_needle)*cos(deg2rad(rpm_needle_right)) );
    }



  }
  {
    // MAN dial
    GLSaveMatrix original_state;
    GLLineSmooth antialias;
    GLLineWidth  line_width(3.0f);
    hmi::Colour::PaletteColour(cn_foreground);
    glTranslatef( 73.0, -67.0f, 0.0f);

    hmi::FontManager::Get(1)->SetSize(0.13,0.13);
    hmi::FontManager::Get(1)->Print(-12,10, "MAN");
    hmi::FontManager::Get(1)->Print(-20,-20, "IN HG");
    hmi::FontManager::Get(1)->Print(-37,27, "35");
    hmi::FontManager::Get(1)->Print(22,27, "35");
    hmi::FontManager::Get(1)->Print(-37,-35, "10");
    hmi::FontManager::Get(1)->Print(22,-35, "10");

    text.clear().position(-40, -62).hcenter().vcenter().size(0.2);
    text << fixed << setprecision(1) << map_left;
    text.draw();

    text.clear().position(40, -62).hcenter().vcenter().size(0.2);
    text << fixed << setprecision(1) << map_right;
    text.draw();

    glBegin(GL_LINE_STRIP);
    circlePoints( gauge_radius, deg2rad(45.0f), deg2rad(135.0f), 60 );
    glEnd();
    glBegin(GL_LINE_STRIP);
    circlePoints( gauge_radius, deg2rad(-45.0f), deg2rad(-135.0f), 60 );
    glEnd();

    {
      hmi::Colour::PaletteColour(cn_foreground);
      GLBegin lines(GL_LINES);
      for(float step=deg2rad(45.0f);step<deg2rad(136.0f);step+=deg2rad(18.0f))
      {
        if( fmod(step,10.0f) < 0.0001 ) continue;
        glVertex2f( gauge_radius*sin(step) , gauge_radius*cos(step) );
        glVertex2f( (gauge_radius-gauge_tick)*sin(step),
            (gauge_radius-gauge_tick)*cos(step) );
      }
    }
    {
      GLBegin lines(GL_LINES);
      for(float step=deg2rad(225.0f);step<deg2rad(315.0f);step+=deg2rad(18.0f))
      {
        if( fmod(step,10.0f) < 0.0001 ) continue;
        glVertex2f( gauge_radius*sin(step) , gauge_radius*cos(step) );
        glVertex2f( (gauge_radius-gauge_tick)*sin(step),
            (gauge_radius-gauge_tick)*cos(step) );
      }
    }
    hmi::Colour::PaletteColour(cn_apmode);
    glBegin(GL_LINE_STRIP);
    circlePoints( gauge_radius, deg2rad(63.0f), deg2rad(135.0f), 60 );
    glEnd();
    glBegin(GL_LINE_STRIP);
    circlePoints( gauge_radius, deg2rad(-63.0f), deg2rad(-135.0f), 60 );
    glEnd();
    {
      hmi::Colour::PaletteColour(cn_foreground);
      GLBegin lines(GL_LINES);
      man_needle_left = (map_left-10.0f)/25.0f * 90.0f + 225.0f;
      glVertex2f( gauge_radius*sin(deg2rad(man_needle_left)) , gauge_radius*cos(deg2rad(man_needle_left)) );
      glVertex2f( (gauge_radius-gauge_needle)*sin(deg2rad(man_needle_left)), (gauge_radius-gauge_needle)*cos(deg2rad(man_needle_left)) );
    }
    {
      hmi::Colour::PaletteColour(cn_foreground);
      GLBegin lines(GL_LINES);
      man_needle_right = -(map_right-10.0f)/25.0f * 90.0f + 135.0f;
      glVertex2f( gauge_radius*sin(deg2rad(man_needle_right)) , gauge_radius*cos(deg2rad(man_needle_right)) );
      glVertex2f( (gauge_radius-gauge_needle)*sin(deg2rad(man_needle_right)), (gauge_radius-gauge_needle)*cos(deg2rad(man_needle_right)) );
    }
  }

  {
    std::string gph = "GPH";
    std::string cht = "CHT";
    std::string temp = "OIL TEMP";
    std::string pres = "OIL PRES";
    std::string fuel = "FUEL QTY GAL";
    draw_bar(fflow_y, gph, true, 0.12f, 0.92f, 0.92f, 1.0f, rpm_left/2800*0.6f+0.1f, rpm_right/2800*0.6f+0.1f);
    draw_bar(cht_y, cht, false, 0.45f, 0.92f, 0.92f, 1.0f, 0.7f, 0.55f);
    draw_bar(temp_y, temp, false, 0.4f, 0.9f, 0.f, 0.2f, 0.9f, 0.5f);
    draw_bar(pres_y, pres, false, 0.45f, 0.6f, 0.f, 0.1f, 0.5f, 0.47f);
    draw_bar(fuel_y, fuel, false, 0.18f, 1.0f, 0.f, 0.18f, 0.5f, 0.5f);

  }

  // landing gear
  {
    HMIText text(hmi::FontManager::Get(2));
    GLSaveMatrix matrix_state;
    GLLineSmooth antialias;
    GLLineWidth  line_width(2.0f);
    hmi::Colour::PaletteColour(cn_foreground);
    text.position(72, -648 + 25).hcenter().vcenter().size(0.13);
    text << "LANDING GEAR";
    text.draw();

    draw_gear(72.0-36.0, -648, *data.lgear);
    draw_gear(72.0     , -648, *data.ngear);
    draw_gear(72.0+36.0, -648, *data.rgear);
  }
}


void EngineData::draw_gear(float x_value, float y_value, int state)
{
  glTranslatef(x_value, y_value, 0.0);
  
  switch (state) {
  default:
  case -1:
    {
      glColor3f(1.0, 0.0, 0.0);
      glBegin(GL_POLYGON);
      circlePoints(12.0, 0.0, 360.0, 60.0);
      glEnd();
      break;
    }
  case 0:
    {
      glColor3f(1.0, 1.0, 1.0);
      glBegin(GL_LINE_STRIP);
      circlePoints(12.0, 0.0, 360.0, 60.0);
      glEnd();
      break;
    }
  case 1:
    {
      glColor3f(0.0, 1.0, 0.0);
      glBegin(GL_POLYGON);
      circlePoints(12.0, 0.0, 360.0, 60.0);
      glEnd();
      break;
    }
  case 2:
    {
      glColor3f(1.0, 1.0, 1.0);
      glBegin(GL_LINE_LOOP);
      glVertex2f(-12.0,-12.0);
      glVertex2f(-12.0, 12.0);
      glVertex2f( 12.0, 12.0);
      glVertex2f( 12.0,-12.0);
      glEnd();
      glBegin(GL_LINES);
      glVertex2f(-12.0, 10.0);
      glVertex2f(-10.0, 12.0);
      glVertex2f(-12.0,  6.0);
      glVertex2f( -6.0, 12.0);
      glVertex2f(-12.0,  2.0);
      glVertex2f( -2.0, 12.0);
      glVertex2f(-12.0, -2.0);
      glVertex2f(  2.0, 12.0);
      glVertex2f(-12.0, -6.0);
      glVertex2f(  6.0, 12.0);
      glVertex2f(-12.0, -10.0);
      glVertex2f( 10.0, 12.0);
      glVertex2f(-10.0, -12.0);
      glVertex2f( 12.0, 10.0);
      glVertex2f(- 6.0, -12.0);
      glVertex2f( 12.0, 6.0);
      glVertex2f(- 2.0, -12.0);
      glVertex2f( 12.0, 2.0);
      glVertex2f( 2.0, -12.0);
      glVertex2f( 12.0, -2.0);
      glVertex2f( 6.0, -12.0);
      glVertex2f( 12.0, -6.0);
      glVertex2f( 10.0, -12.0);
      glVertex2f( 12.0, -10.0);
     glEnd();
	
      break;
    }

  } 

  glTranslatef(-x_value, -y_value, 0.0);
}

void EngineData::draw_bar(float y_value, std::string &txt, bool draw_ticks,
                          float green_l, float green_r, float red_l,
                          float red_r, float x_l, float x_r)
{
  const float bar_l = 6;
  const float bar_w = 132;
  const float bar_r = bar_l + bar_w;
  const GLTriangle triangle_l(-11.0f, 16.0f,
                              10.0f, 16.0f,
                              0.0f, 0.0f);
  const GLTriangle triangle_r(-11.0f, -16.0f,
                              10.0f, -16.0f,
                              0.0f, 0.0f);


  HMIText text(hmi::FontManager::Get(2));
  GLSaveMatrix matrix_state;
  GLLineSmooth antialias;
  GLLineWidth  line_width(2.0f);
  hmi::Colour::PaletteColour(cn_foreground);
  text.clear().position(72, y_value + 25).hcenter().vcenter().size(0.13);
  text << txt;
  text.draw();
  {
    GLBegin lines(GL_LINES);
    glVertex2f(bar_l, y_value);
    glVertex2f(bar_r, y_value);
  }
  {
    if(draw_ticks){
      GLBegin lines(GL_LINES);
      for(float step=0; step<1.01f; step+=0.1f)
      {
        if( fmod(step,10.0f) < 0.0001 ) continue;
        glVertex2f( bar_l + step*bar_w, y_value + 8 );
        glVertex2f( bar_l + step*bar_w, y_value - 9 );
      }
    }
  }
  {
    hmi::Colour::PaletteColour(cn_apmode);
    GLBegin lines(GL_LINES);
    glVertex2f(bar_l + green_l*bar_w, y_value);
    glVertex2f(bar_l + green_r*bar_w, y_value);
  }
  {
    glColor3f(1.0, 0.0, 0.0);
    GLBegin lines(GL_LINES);
    glVertex2f(bar_l + red_l*bar_w, y_value);
    glVertex2f(bar_l + red_r*bar_w, y_value);
  }
  {
    hmi::Colour::PaletteColour(cn_foreground);
    GLBegin lines(GL_LINES);
    glVertex2f(bar_l, y_value+14);
    glVertex2f(bar_l, y_value-15);
  }
  {
    hmi::Colour::PaletteColour(cn_foreground);
    GLBegin lines(GL_LINES);
    glVertex2f(bar_r, y_value+14);
    glVertex2f(bar_r, y_value-15);
  }
  {
    hmi::Colour::PaletteColour(cn_foreground);
    glTranslatef(bar_l+bar_w*x_l, y_value, 0.0f);
    {
      triangle_l.drawFill();
      hmi::Colour::PaletteColour(cn_background);
      text.clear().position(-1, 10).hcenter().vcenter().size(0.14);
      text << "L";
      text.draw();
    }
    glTranslatef(-(bar_l+bar_w*x_l), (-y_value), 0.0f);
  }
  {
    hmi::Colour::PaletteColour(cn_foreground);
    glTranslatef(bar_l+bar_w*x_r, y_value, 0.0f);
    {
      triangle_r.drawFill();
      hmi::Colour::PaletteColour(cn_background);
      text.clear().position(-1, -10).hcenter().vcenter().size(0.14);
      text << "R";
      text.draw();
    }
    glTranslatef(-(bar_l+bar_w*x_r), -y_value, 0.0f);
  }
}
namespace
{}
