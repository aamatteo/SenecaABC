/* ------------------------------------------------------------------   */
/*      item            : RadioBlock.cxx
        made by         : jcomans
        from template   : hmigauge_component.cxx
        template made by: Joost Ellerbroek
        date            : 081013
        category        : body file
        description     :
        changes         : 081013 first version
        language        : C++
*/
#include "RadioBlock_MFD.hxx"

#include <iomanip>
#include <iostream>
#include <fstream>
#include <ctime>
#include <hmi.hxx>

#include "GLTools.hxx"
#include "HMITools.hxx"
#include "Math.hxx"


using namespace std;

namespace {
  const float radio_block_width   = 1024.0f;
  const float radio_block_height  =   55.0f;

  const GLRectangle radio_block(0.0f,radio_block_height, 0.0f, radio_block_width);

  const float ap_block_middle = 460.0f;

  const float frequency_box_width =  264.0f;

  const float nav_box_left   = 0.0f;
  const float nav_box_right  = frequency_box_width;
  const float nav_box_bottom = 0.0f;
  const float nav_box_top    = radio_block_height;
  const float nav_box_middle = radio_block_height / 2.0f;

  const GLRectangle nav_box(nav_box_bottom,nav_box_top,nav_box_left,nav_box_right);

  const float com_box_left   = radio_block_width - frequency_box_width;
  const float com_box_right  = radio_block_width;
  const float com_box_bottom = 0.0f;
  const float com_box_top    = radio_block_height;
  const float com_box_middle = radio_block_height / 2.0f;

  const GLRectangle com_box(com_box_bottom, com_box_top, com_box_left, com_box_right);

  const float gps_box_width = com_box_left - nav_box_right;

  const float wpt_box_left   = nav_box_right;
  const float wpt_box_right  = wpt_box_left + gps_box_width * 0.565f;
  const float wpt_box_bottom = radio_block_height/2.0f;
  const float wpt_box_top    = radio_block_height;
  const float wpt_box_vcenter = wpt_box_bottom + (wpt_box_top - wpt_box_bottom) / 2.0f;
  const float wpt_box_hcenter = wpt_box_left   + (wpt_box_right - wpt_box_left) / 2.0f;

  const GLRectangle wpt_box(wpt_box_bottom, wpt_box_top, wpt_box_left, wpt_box_right);

  const float dme_box_left   = wpt_box_right;
  const float dme_box_right  = com_box_left;
  const float dme_box_bottom = radio_block_height/2.0f;
  const float dme_box_top    = radio_block_height;
  const float dme_box_vcenter = dme_box_bottom + (dme_box_top - dme_box_bottom) / 2.0f;
  const float dme_box_hcenter = dme_box_left   + (dme_box_right - dme_box_left) / 2.0f;

  const GLRectangle dme_box(dme_box_bottom, dme_box_top, dme_box_left, dme_box_right);

  const float roll_box_left   = nav_box_right;
  const float roll_box_right  = roll_box_left + gps_box_width * 0.253f;
  const float roll_box_bottom = 0.0f;
  const float roll_box_top    = radio_block_height/2.0f;
  const float roll_box_vcenter = roll_box_bottom + (roll_box_top - roll_box_bottom) / 2.0f;
  const float roll_box_hcenter = roll_box_left   + (roll_box_right - roll_box_left) / 2.0f;

  const GLRectangle roll_box(roll_box_bottom, roll_box_top, roll_box_left, roll_box_right);

  const float ap_box_left   = roll_box_right;
  const float ap_box_right  = nav_box_right + gps_box_width * 0.435f;
  const float ap_box_bottom = 0.0f;
  const float ap_box_top    = radio_block_height/2.0f;
  const float ap_box_vcenter = ap_box_bottom + (ap_box_top - ap_box_bottom) / 2.0f;
  const float ap_box_hcenter = ap_box_left   + (ap_box_right - ap_box_left) / 2.0f;

  const GLRectangle ap_box(ap_box_bottom, ap_box_top, ap_box_left, ap_box_right);

  const float pitch_box_left   = ap_box_right;
  const float pitch_box_right  = com_box_left;
  const float pitch_box_bottom = 0.0f;
  const float pitch_box_top    = radio_block_height/2.0f;
  const float pitch_box_vcenter = pitch_box_bottom + (pitch_box_top - pitch_box_bottom) / 2.0f;
  const float pitch_box_hcenter = pitch_box_left   + (pitch_box_right - pitch_box_left) / 2.0f;

  const GLRectangle pitch_box(pitch_box_bottom, pitch_box_top, pitch_box_left, pitch_box_right);

  const GLRectangle ap_off_box(ap_box_bottom + 3, ap_box_top - 3, ap_box_left + 3, ap_box_left + 50);
  const GLRectangle pit_flash_box(ap_box_bottom + 3, ap_box_top - 3, pitch_box_left+3, pitch_box_left + 50);
  const GLRectangle rol_flash_box(ap_box_bottom + 3, ap_box_top - 3, roll_box_right - 50, roll_box_right - 3);

  const float title_box_left = nav_box_right;
  const float title_box_right = com_box_left;
  const float title_box_top = ap_box_top;
  const float title_box_bottom = ap_box_bottom;

  const GLRectangle title_box(title_box_bottom, title_box_top, title_box_left, title_box_right);

  enum nav_radio { nav1,nav2 };
  enum com_radio { com1,com2 };

  void draw_arrow(float x, float y);

  std::string prev_file_name;
  std::string comment;
  float nav1_act;
  float nav2_act;
  float nav1_stby;
  float nav2_stby;

  int nr_of_wps;
  int fpl_page;
  int fpl_page_old;

  std::string nav1Name;
  std::string nav2Name;

  float prev_x = 0;
  float prev_y = 0;
  float prev_gs = 0;
  float gs;
};

class LabelFlasher: public hmi::Animator
{
public:
  LabelFlasher():_active(true) {}

  bool active() const { return _active; }

  void Step(const double& t)
  {
    const double delta = t - start_time;

    const double decimal = delta - floor(delta);

    if(decimal < 0.5)
      _active = true;
    else
      _active = false;
  };

private:
  bool _active;
};

RadioBlock_MFD::RadioBlock_MFD() :
  hmi::GaugeComponent("RadioBlock"),
  _label_flasher(new LabelFlasher)
{
  AddAnimator(_label_flasher);
}

RadioBlock_MFD::~RadioBlock_MFD()
{

}

void RadioBlock_MFD::Init()
{
}

void RadioBlock_MFD::updateTransitions(bool current_altmode, bool current_hdgmode)
{

}

void RadioBlock_MFD::Render()
{
  // const bool hdghold_active = *GetData().ap_hdghold_mode;
  // const bool althold_active = *GetData().ap_althold_mode;
  //
  // const bool hdghold_transition = *GetData().ap_hdghold_transition;
  // const bool althold_transition = *GetData().ap_althold_transition;
  //
  const float dme    = *GetData().dme;
  const float trk =  *GetData().trk;
  const float brg =  *GetData().brg;
  const float dtk =  *GetData().dtk;
  const float Vtas =  *GetData().Vtas;
  const float y =  *GetData().x;
  const float x =  *GetData().y;

  const int curVerticalState = *GetData().curVerticalState;
  const int curLateralState = *GetData().curLateralState;
  const int APstate = *GetData().APstate;

  const float target_vs = *data.target_vs;
  const float altitude_target = *data.altitude_target;
  const float hdg_bug = *data.hdg_bug;
  const int ap_armed = *data.ap_armed;
  const float target_speed = *data.target_speed;
  const float alt_hold = *data.alt_hold;

  const bool ap_flash = *data.ap_flash;
  const bool pit_flash = *data.pit_flash;
  const bool rol_flash = *data.rol_flash;

  const bool VOR_failure = *GetData().VOR_failure;
  const int msg = *GetData().msg;

  const float dt = *GetData().dt;

  gs = sqrt(pow(x-prev_x,2)+pow(y-prev_y,2))/dt;
  prev_x = x;
  prev_y = y;
  if (gs>300 || isnan(gs)){
    gs = prev_gs;
  }
  if (gs==0 && Vtas > 10)
  {
    gs = Vtas;
  }
  prev_gs = gs;
  //std::cout << "Groundspeed:" << gs << std::endl;

  if(msg == 14){
    fpl_page = !fpl_page;
  }

  const float com1_act  = 118.000;
  const float com2_act  = 118.000;
  const float com1_stby = 136.975;
  const float com2_stby = 136.975;

  const com_radio active_com = com1;
  const nav_radio active_nav = nav1;

  const std::string filename = *GetData().fp_name;

  const int active_nav_source = *GetData().active_nav_source;

  // read the flight plan if a new one becomes available
  if(filename != prev_file_name && filename.length()>0){
    std::ifstream myfile (filename);

    myfile >> comment >> nav1_stby >> nav1Name;
    myfile >> comment >> nav1_act;
    myfile >> comment >> nav2_stby >> nav2Name;
    myfile >> comment >> nav2_act;
    myfile >> comment >> comment >> comment;
    myfile >> comment >> comment >> comment;
    myfile >> comment >> comment >> comment;
    myfile >> comment >> nr_of_wps;

    myfile.close();
  }

  if (nav1Name.length() != 3 || filename.length()<3){
    nav1Name = "";
  }
  if (nav2Name.length() != 3 || filename.length()<3){
    nav2Name = "";
  }
  prev_file_name = filename;

  if (filename.length()<3){
    nr_of_wps = 0;
    nav1_act = 108.00;
    nav2_act = 108.00;
    nav1_stby = 108.00;
    nav2_stby = 108.00;

  }


  ////////////////////////////////////////////////////////////
  // Draw the background boxes
  ////////////////////////////////////////////////////////////
  {
    hmi::Colour::PaletteColour(cn_background);

    radio_block.drawFill();
    nav_box.drawFill();
    com_box.drawFill();
    wpt_box.drawFill();
    dme_box.drawFill();
    roll_box.drawFill();
    ap_box.drawFill();
    pitch_box.drawFill();
    title_box.drawFill();

    hmi::Colour::PaletteColour(cn_outline);
    radio_block.drawOutline();
    nav_box.drawOutline();
    com_box.drawOutline();
    title_box.drawOutline();
    //wpt_box.drawOutline();
    //dme_box.drawOutline();
    //roll_box.drawOutline();
    //ap_box.drawOutline();
    //pitch_box.drawOutline();
  }

  ////////////////////////////////////////////////////////////
  // Draw the static text
  ////////////////////////////////////////////////////////////
  hmi::Colour::PaletteColour(cn_foreground);
  HMIText text(hmi::FontManager::Get(2));

  text.padding(-5.0,5.0).bottom().right().size(0.14);

  text.position( nav_box_right, nav_box_middle );
  text << nav1Name;
  text.draw();

  text.position( nav_box_right, nav_box_bottom );
  text.cleartext() << nav2Name;
  text.draw();

  text.clear().padding(5.0,5.0).bottom().left().size(0.14);

  text.position( com_box_left , com_box_middle );
  text.cleartext() << "COM1";
  text.draw();

  text.position( com_box_left , com_box_bottom );
  text.cleartext() << "COM2";
  text.draw();

  if(VOR_failure){
    GLBlend blend;
    glColor4f(0.255, 0.2, 0.2, 0.8);
    nav_box.drawFill();

    glColor3f(1.0, 0.0, 0.0);
    GLLineSmooth antialias;
    GLLineWidth line_width(2.0f);
    {
      GLBegin lines(GL_LINES);
      glVertex2f(nav_box_left, nav_box_middle);
      glVertex2f(nav_box_right, nav_box_bottom);
    }
    {
      GLBegin lines(GL_LINES);
      glVertex2f(nav_box_right, nav_box_middle);
      glVertex2f(nav_box_left, nav_box_bottom);
    }
    {
      GLBegin lines(GL_LINES);
      glVertex2f(nav_box_left, nav_box_middle);
      glVertex2f(nav_box_right, nav_box_top);
    }
    {
      GLBegin lines(GL_LINES);
      glVertex2f(nav_box_right, nav_box_middle);
      glVertex2f(nav_box_left, nav_box_top);
    }


    hmi::Colour::PaletteColour(cn_outline);
    nav_box.drawOutline();
  }

  ////////////////////////////////////////////////////////////
  // Draw dynamic text
  ////////////////////////////////////////////////////////////
  // The nav radios
  // The nav radios
  if(VOR_failure == false){
    text.clear().padding(5.0,5.0).left().bottom().size(0.14);

    if( active_nav == nav1 ) hmi::Colour::PaletteColour(cn_active);
    else hmi::Colour::PaletteColour(cn_foreground);

    hmi::Colour::PaletteColour(cn_foreground);
    text.position( nav_box_left , nav_box_middle );
    text.cleartext() << fixed << setprecision(2) << nav1_act;
    hmi::BoundingBox bb_nav_1 = text.draw();


    hmi::Colour::PaletteColour(cn_active);
    if( active_nav == nav1 ) draw_arrow( bb_nav_1.x + bb_nav_1.w/2.0f + 15.0f , bb_nav_1.y+2.0f );

    if( active_nav == nav2 ) hmi::Colour::PaletteColour(cn_active);
    else hmi::Colour::PaletteColour(cn_foreground);

    text.position( nav_box_left , nav_box_bottom );
    text.cleartext() << fixed << setprecision(2) << nav2_act;
    hmi::BoundingBox bb_nav_2 = text.draw();

    if( active_nav == nav2 ) draw_arrow( bb_nav_2.x + bb_nav_2.w/2.0f + 15.0f , bb_nav_2.y+2.0f );

    hmi::Colour::PaletteColour(cn_foreground);


    if(active_nav_source == 1){
      hmi::Colour::PaletteColour(cn_apmode);
    }
    else{
      hmi::Colour::PaletteColour(cn_foreground);
    }
    text.position( bb_nav_1.x+bb_nav_1.w/2.0 , nav_box_middle ).padding( 50.0,5.0).size(0.18);
    text.cleartext() << fixed << setprecision(2) << nav1_stby;
    text.draw();


    if(active_nav_source == 2){
      hmi::Colour::PaletteColour(cn_apmode);
    }
    else{
      hmi::Colour::PaletteColour(cn_foreground);
    }
    text.position( bb_nav_2.x+bb_nav_2.w/2.0 , nav_box_bottom ).padding( 50.0,5.0).size(0.18);
    text.cleartext() << fixed << setprecision(2) << nav2_stby;
    text.draw();
  }

  // The com radios
  text.clear().padding(-5.0,5.0).right().bottom().size(0.14);

  if( active_com == com1 ) hmi::Colour::PaletteColour(cn_active);
  else hmi::Colour::PaletteColour(cn_foreground);

  hmi::Colour::PaletteColour(cn_foreground);
  text.position( com_box_right , com_box_middle );
  text.cleartext() << fixed << setprecision(3) << com1_act;
  hmi::BoundingBox bb_com_1 = text.draw();

  hmi::Colour::PaletteColour(cn_active);
  if( active_com == com1 ) draw_arrow( bb_com_1.x - bb_com_1.w/2.0f - 35.0f , bb_com_1.y + 2.0f );

  if( active_com == com2 ) hmi::Colour::PaletteColour(cn_active);
  else hmi::Colour::PaletteColour(cn_foreground);

  text.position( com_box_right , com_box_bottom );
  text.cleartext() << fixed << setprecision(3) << com2_act;
  hmi::BoundingBox bb_com_2 = text.draw();

  if( active_com == com2 ) draw_arrow( bb_com_2.x - bb_com_2.w/2.0f - 35.0f , bb_com_2.y + 2.0f );

  hmi::Colour::PaletteColour(cn_foreground);

  text.position( bb_com_1.x-bb_com_1.w/2.0 , com_box_middle ).padding( -50.0,5.0).size(0.18);
  text.cleartext() << fixed << setprecision(3) << com1_stby;
  text.draw();

  text.position( bb_com_2.x-bb_com_2.w/2.0 , com_box_bottom ).padding( -50.0,5.0).size(0.18);
  text.cleartext() << fixed << setprecision(3) << com2_stby;
  text.draw();

  // The AP Modes
  if(fpl_page){
    hmi::Colour::PaletteColour(cn_active);
    text.clear().position(ap_box_hcenter+50.0f, ap_box_bottom).hcenter().bottom().padding(0.0f,7.0f).size(0.18);
    text << "FPL - ACTIVE FLIGHT PLAN";
    text.draw();
  }else{
    hmi::Colour::PaletteColour(cn_active);
    text.clear().position(ap_box_hcenter+50.0f, ap_box_bottom).hcenter().bottom().padding(0.0f,7.0f).size(0.18);
    text << "NAV - DEFAULT NAV";
    text.draw();
  }

  // The GPS info
  hmi::Colour::PaletteColour(cn_foreground);
  text.clear().position(wpt_box_left,wpt_box_bottom).left().bottom().padding(10.0f,7.0f).size(0.14);
  text << "GS";
  text.draw();

  text.clear().position(wpt_box_hcenter,wpt_box_bottom).left().bottom().padding(10.0f,7.0f).size(0.14);
  text << "DTK";
  text.draw();

  hmi::Colour::PaletteColour(cn_foreground);
  text.clear().position(dme_box_left,dme_box_bottom).left().bottom().padding(10.0f,7.0f).size(0.14);
  text << "TRK";
  hmi::BoundingBox disbox = text.draw();

  text.clear().position(dme_box_hcenter,dme_box_bottom).left().bottom().padding(10.0f,7.0f).size(0.14);
  text << "ETE";
  hmi::BoundingBox brgbox = text.draw();

  hmi::Colour::PaletteColour(cn_nav);

  text.clear().position(wpt_box_left+30,wpt_box_bottom).left().bottom();
  text.padding(10.0f,7.0f).size(0.18);
  text << fixed << setw(3) << setfill(' ') << setprecision(0) << round(gs*3.6/1.852);
  text.draw();

  text.clear().position(wpt_box_hcenter+32,wpt_box_bottom).left().bottom();
  if(nr_of_wps>0){
    //int integer_dtk = static_cast<int>(dtk);
    //if(integer_dtk == 0) integer_dtk = 360;
    text.padding(10.0f,7.0f).size(0.18);
    //text << fixed << setw(3) << setfill('0') << setprecision(0) << (integer_dtk% 360 + 360) %360;
    text << fixed << setw(3) << setfill('0') << setprecision(0) << dtk;
  }else{
    text.padding(10.0f,7.0f).size(0.18);
    text.cleartext() << "___";
  }
  text.draw();

  text.clear().position( wpt_box_hcenter + 32 + 36, dme_box_bottom + 8).left().bottom().padding(10.0f,7.0f).size(0.12);
  text << "o";
  text.draw();


  int integer_trk = static_cast<int>(rad2deg(trk));
  text.clear().position(dme_box_left + 32, dme_box_bottom).left().bottom();
  text.padding(10.0f,7.0f).size(0.18);
  text << fixed << setw(3) << setfill('0') << setprecision(0) << (integer_trk  % 360 + 360) %360;
  text.draw();

  text.clear().position( dme_box_left + 32 + 36, dme_box_bottom + 8).left().bottom().padding(10.0f,7.0f).size(0.12);
  text << "o";
  text.draw();

  float time_s;
  if(gs>20){
    time_s = dme*1852/gs;
  }else{
    time_s = 0;
  }

  text.clear().position( brgbox.x + brgbox.w/2.0 , dme_box_bottom).left().bottom();
  text.padding(10.0f,7.0f).size(0.18);
  if(nr_of_wps>0){
    int time_s_integer = static_cast<int>( time_s);
    text << floor(time_s/60) << ":" << fixed << setw(2) << setfill('0') << time_s_integer%60;

  }else{
    text.cleartext() << "_:__";
  }
  text.draw();


  text.clear().position( wpt_box_left + 30 + 36, dme_box_bottom).left().bottom().padding(10.0f,7.0f).size(0.14);
  text << "KTS";
  text.draw();


}

namespace
{
  void draw_arrow(float x, float y)
  {
    const float tipsize = 5.0f;
    const float arrowsize = 20.0f;

    GLLineWidth thick(2.0);

    {
      GLBegin lines(GL_LINES);
      glVertex2f(x,y);
      glVertex2f(x+20.0f,y);
    }

    GLLineWidth thicker(3.0);


    {
      GLBegin lines(GL_LINES);
      glVertex2f(x,y);
      glVertex2f(x+tipsize,y+tipsize);

      glVertex2f(x,y);
      glVertex2f(x+tipsize,y-tipsize);

      glVertex2f(x+arrowsize,y);
      glVertex2f(x+arrowsize-tipsize,y+tipsize);

      glVertex2f(x+arrowsize,y);
      glVertex2f(x+arrowsize-tipsize,y-tipsize);
    }
  }
};
