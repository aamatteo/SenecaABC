/* ------------------------------------------------------------------   */
/*      item            : ThrottleCalibration.cxx
        made by         : jcomans
        from template   : hmigauge_component.cxx
        template made by: Joost Ellerbroek
        date            : 081013
        category        : body file
        description     :
        changes         : 081013 first version
        language        : C++
*/

#include "ThrottleCalibration.hxx"

// HMILib objects and functions
#include <hmi.hxx>

#include "ColorMap.hpp"
#include "GLTools.hxx"
#include "HMITools.hxx"

namespace
{
  // const float field_height =  25.0f;
  // const float field_width  = 150.0f;

  const float field_height =  768.0f;
  const float field_width  = 1024.0f;
  const float padding      =   0.0f;
};

ThrottleCalibration::ThrottleCalibration() :
  hmi::GaugeComponent("ThrottleCalibration")
{

}

ThrottleCalibration::~ThrottleCalibration()
{

}

void ThrottleCalibration::Init()
{
  // Initialize your display lists and fonts here
}

void ThrottleCalibration::Render()
{
  const bool enabled    = *data.enabled;
  const float tl_left = *data.tl_left;
  const float tl_right = *data.tl_right;
  const int gear = *data.gear;
  const float altitude = *data.altitude;

  if(enabled)
  {
    GLSaveMatrix original_state;

    hmi::Colour::PaletteColour(cn_background);


    //GLRectangle(0.0f,100.0f,0.0f,250.0f).drawFill();

    glTranslatef(150.0f, 150.0f, 0.0f );


    {
      HMIText text(hmi::FontManager::Get(2));
      text.clear().position(-120.0f,75.0f).left().size(0.20);
      text << "SIMULATION PAUSED";
      text.draw();
      text.clear().position(-120.0f,50.0f).left().size(0.15);
      text << "Throttle left: ";
      text.draw();

      text.clear().position(-120.0f,30.0f).left().size(0.15);
      text << "Throttle right: ";
      text.draw();

      text.clear().position(-120.0f,10.0f).left().size(0.15);
      text << "Gear: ";
      text.draw();
    }
    {
      HMIText text(hmi::FontManager::Get(1));
      text.position(30.0f,50.0f).hcenter().right().size(0.15);
      text.cleartext() << std::fixed << std::setprecision(0) << std::setw(3) << std::setfill(' ') << tl_left*100 <<"%";
      text.draw();

      text.position(30.0f,30.0f).hcenter().right().size(0.15);
      text.cleartext() << std::fixed << std::setprecision(0) << std::setw(3) << std::setfill(' ') << tl_right*100 <<"%";
      text.draw();

      if(gear){
        text.cleartext() << "UP";
      }else{
        text.cleartext() << "DOWN";
      }
      text.position(30.0f,10.0f).hcenter().right().size(0.15);
      text.draw();

      glColor3f(1.0f,0.0f,0.0f);
      text.clear().position(-120.0f,-20.0f).left().size(0.20);
      if(altitude<10 && tl_left>0.1 || altitude<10 && tl_right>0.1){
        text.cleartext() << "BRING THROTTLES";
        text.draw();
        text.clear().position(-120.0f,-40.0f).left().size(0.20);
        text.cleartext() << "TO IDLE";
      }else if(altitude>10 && tl_left<0.5 || altitude>10 && tl_right<0.5){
        text.cleartext() << "BRING THROTTLES";
        text.draw();
        text.clear().position(-120.0f,-40.0f).left().size(0.20);
        text.cleartext() << "TO CRUISE POWER";
      } else{
        text.cleartext();
      }
      text.draw();

      text.clear().position(-120.0f,-70.0f).left().size(0.20);
      if(altitude<100 && gear){
        text.cleartext() << "BRING GEAR DOWN";
        text.draw();
      }else if(altitude>100 && !gear){
        text.cleartext() << "BRING GEAR UP";
        text.draw();
      }



    }



  }
}
