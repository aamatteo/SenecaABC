/* ------------------------------------------------------------------   */
/*      item            : ButtonBar.cxx
        made by         : jcomans
        from template   : hmigauge_component.cxx
        template made by: Joost Ellerbroek
        date            : 081013
        category        : body file
        description     :
        changes         : 081013 first version
        language        : C++
*/

#include "ButtonBar.hxx"

#include <iomanip>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <chrono>
#include <ctime>


#include <hmi.hxx>

#include "ColorMap.hpp"
#include "GLTools.hxx"
#include "HMITools.hxx"
#include "Math.hxx"

using namespace std;

namespace
{
  const float button_bar_width  = 1024.0f;
  const float button_bar_height =   25.0f;

  const size_t n_buttons    = 12;
  const float  button_width = button_bar_width/static_cast<float>(n_buttons);

  const float time_box_width = 128.0f;
  const float time_box_height = 25.0f;
  const GLRectangle time_box(0.0f,time_box_height,0.0f,time_box_width);

  const GLRectangle oat_box(0.0f,time_box_height,0.0f, 85.0f);

  const float dme_box_width = 81.0f;
  const float dme_box_height = 75.0f;
  const GLRectangle dme_box(0.0f, dme_box_height, 0.0f, dme_box_width);

  std::time_t end_time;
  std::string T;

  map<size_t,string> labelmap;

  std::string prev_file_name;
  std::string comment;
  float nav1_act;
  float nav2_act;
  float nav1_stby;
  float nav2_stby;
  float nav_freq;
  float dme_nm = 0;
  std::string dummy;
  int use_vor1 = 0;
  int use_vor2 = 0;

  float vor1_x = 0;
  float vor1_y = 0;
  float vor2_x = 0;
  float vor2_y = 0;

  float temperature;
};

ButtonBar::ButtonBar() :
    GaugeComponent("ButtonBar")
{

}

ButtonBar::~ButtonBar()
{

}

void ButtonBar::Init()
{
  labelmap[1]  = "INSET";
  labelmap[3]  = "PFD";
  labelmap[5]  = "CDI";
  labelmap[6]  = "DME";
  labelmap[7]  = "XPDR";
  labelmap[8]  = "IDENT";
  labelmap[9]  = "TMR/REF";
  labelmap[10] = "NRST";
  labelmap[11] = "ALERTS";
}

void ButtonBar::Render()
{
  const float x = *data.y;
  const float y = *data.x;
  const int dme_status = *data.dme_status;
  const std::string filename = *GetData().fp_name;
  const float altitude = *GetData().altitude;
  const bool ADC_failure = *GetData().ADC_failure;


  if(filename != prev_file_name && filename.length()>0){
    std::ifstream myfile (filename.c_str());

    myfile >> comment >> nav1_act >> dummy;
    myfile >> comment >> dummy;
    myfile >> comment >> nav2_act >> dummy;
    myfile >> comment >> dummy;
    myfile >> comment >> use_vor1 >> use_vor2;
    myfile >> comment >> vor1_x >> vor1_y;
    myfile >> comment >> vor2_x >> vor2_y;

    myfile.close();
  }

  prev_file_name = filename;

  if(use_vor1 == 0 || filename.length() < 3){
    nav1_act = 117.95;
    dme_nm = 0.0;
    use_vor1 = 0;
  }
  if(use_vor2 == 0 || filename.length() < 3){
    nav2_act = 117.95;
    dme_nm = 0.0;
    use_vor2 = 0;
  }

  switch(dme_status){
    case 0:
      break;

    case 1:
      nav_freq = nav1_act;
      if(use_vor1){
        dme_nm = sqrt(pow(sqrt(pow((vor1_x-x),2)+pow((vor1_y-y),2)),2)+pow(altitude,2))/1852.0;
      }
      break;

    case 2:
      nav_freq = nav2_act;
      if(use_vor2){
        dme_nm = sqrt(pow(sqrt(pow((vor2_x-x),2)+pow((vor2_y-y),2)),2)+pow(altitude,2))/1852.0;
      }
      break;
  }

  // The background
  hmi::Colour::PaletteColour(cn_background);
  GLRectangle(0.0f,button_bar_height,0.0f,button_bar_width).drawFill();

  // The top line
  hmi::Colour::PaletteColour(cn_foreground);
  {
    GLBegin lines(GL_LINES);
    glVertex2f(0.0f,button_bar_height);
    glVertex2f(button_bar_width,button_bar_height);
  }

  // The divisions
  {
    GLLineWidth width(1.0);
    GLBegin lines(GL_LINES);

    for(size_t n=1; n<n_buttons; ++n)
    {
      const float x_pos = static_cast<float>(n) * button_width;
      glVertex2f( x_pos ,0.0f);
      glVertex2f( x_pos ,button_bar_height);
    }
  }

  // The labels
  hmi::Colour::PaletteColour(cn_foreground);
  HMIText text(hmi::FontManager::Get(2));

  text.vcenter().hcenter().size(0.16);

  map<size_t,string>::iterator I;
  for(I=labelmap.begin();I!=labelmap.end();++I)
  {
    const string label = I->second;
    const float button_number = static_cast<float>(I->first);
    const float box_center = button_number * button_width + button_width/2.0f;
    text.position(box_center,button_bar_height/2.0f).cleartext();
    text << label;
    text.draw();
  }

  if(dme_status!=0)
  {
    HMIText text(hmi::FontManager::Get(1));
    GLSaveMatrix matrix_state;
    GLLineSmooth antialias;
    GLLineWidth line_width(1.5f);
    glTranslatef(235.0f, 101.0f, 0.0f);
    hmi::Colour::PaletteColour(cn_background);
    dme_box.drawFill();
    hmi::Colour::PaletteColour(cn_outline);
    dme_box.drawOutline();
    {
      GLSaveMatrix matrix_state;
      glTranslatef(460.0f-235.0f, 180.0f-101.0f, 0.0f);
      glBegin(GL_LINE_STRIP);
      circlePoints( 145.0f*1.17, deg2rad(268.5f), deg2rad(242.5f), 36 );
      glEnd();
    }
    hmi::Colour::PaletteColour(cn_foreground);
    text.clear().position(2.0f, dme_box_height-11.0f).left().vcenter().size(0.15);
    text << "DME";
    text.draw();
    hmi::Colour::PaletteColour(cn_active);
    text.position(2.0f, dme_box_height-29.0f).left().vcenter().size(0.15);
    text.cleartext() << "NAV" << dme_status;
    text.draw();
    text.position(2.0f, dme_box_height-47.0f).left().vcenter().size(0.15);
    text.cleartext() << std::fixed << std::setprecision(2) << nav_freq;
    text.draw();

    hmi::Colour::PaletteColour(cn_foreground);
    text.position(2.0f, dme_box_height-65.0f).left().vcenter().size(0.16);
    if(dme_status == 1 && use_vor1 || dme_status == 2 && use_vor2){
      text.cleartext() << std::fixed << std::setw(4) << std::setfill(' ') << std::setprecision(1) << dme_nm;
    }else{
      text.cleartext() << "-.--";
    }
    text.draw();
    text.position(45.0f, dme_box_height-65.0f).left().vcenter().size(0.16);
    text.cleartext() << "NM";
    text.draw();


  }

  {
    GLSaveMatrix matrix_state;
    GLLineSmooth antialias;
    glTranslatef(button_bar_width-time_box_width+1, button_bar_height, 0.0f);
    GLLineWidth line_width(1.0f);
    hmi::Colour::PaletteColour(cn_background);
    time_box.drawFill();
    hmi::Colour::PaletteColour(cn_foreground);
    time_box.drawOutline();

    hmi::Colour::PaletteColour(cn_foreground);
    text.clear().position(5.0f, time_box_height/2-2.0f).left().vcenter().size(0.15);
    text << "LCL";
    text.draw();

    auto end = std::chrono::system_clock::now();
    end_time = std::chrono::system_clock::to_time_t(end);
    T = std::string(std::ctime(&end_time)).substr(11,8);

    text.clear().position(time_box_width-5.0f, time_box_height/2).right().vcenter().size(0.17);
    text << T;
    text.draw();
  }

  if (!ADC_failure)
  {
    GLSaveMatrix matrix_state;
    GLLineSmooth antialias;
    glTranslatef(0.0f, button_bar_height, 0.0f);
    GLLineWidth line_width(1.0f);
    hmi::Colour::PaletteColour(cn_background);
    oat_box.drawFill();
    hmi::Colour::PaletteColour(cn_foreground);
    oat_box.drawOutline();

    text.clear().position(3.0f, time_box_height/2).left().vcenter().size(0.15);
    text << "OAT";
    text.draw();

    temperature = floor(15.04 - 0.00649 * altitude);
    text.clear().position(68.0f, time_box_height/2).right().vcenter().size(0.15);
    text << temperature;
    text.draw();

    text.clear().position(72.0f, time_box_height/2).left().vcenter().size(0.15);
    text << "C";
    text.draw();

  } else
  {
    glTranslatef(0.0f, button_bar_height, 0.0f);
    glColor4f(0.255, 0.2, 0.2, 0.8);
    oat_box.drawFill();

    glColor3f(1.0, 0.0, 0.0);
    GLLineSmooth antialias;
    GLLineWidth line_width(2.0f);
    {
      GLBegin lines(GL_LINES);
      glVertex2f(0.0f, time_box_height);
      glVertex2f(85.0f, 0.0f);
    }
    {
      GLBegin lines(GL_LINES);
      glVertex2f(85.0f, time_box_height);
      glVertex2f(0.0f, 0.0f);
    }
    hmi::Colour::PaletteColour(cn_outline);
    oat_box.drawOutline();
  }
}
