/* ------------------------------------------------------------------   */
/*      item            : InstructorParameters.cxx
        made by         : jcomans
        from template   : hmigauge_component.cxx
        template made by: Joost Ellerbroek
        date            : 081013
        category        : body file 
        description     :
        changes         : 081013 first version
        language        : C++
*/

#include "InstructorParameters.hxx"

// HMILib objects and functions
#include <hmi.hxx>

#include <iomanip>
#include <iostream>

#include "ColorMap.hpp"
#include "GLTools.hxx"
#include "HMITools.hxx"
#include "Math.hxx"

using namespace std;

namespace
{
  const float block_width  = 400.0f;
  const float block_height = 200.0f;

  const GLRectangle background(0.0f, block_height, 0.0f, block_width);
};

InstructorParameters::InstructorParameters() :
  GaugeComponent("InstructorParameters")
{

}

InstructorParameters::~InstructorParameters()
{

}

void InstructorParameters::Init()
{
}

void InstructorParameters::Render()
{
  const bool show_instructor = *data.show_instructor;

  const float height     = *data.height;
  const float min_height = *data.min_height;
  const float fuel_left  = *data.fuel_left;
  const float fuel_right = *data.fuel_right;

  const float liter_left  = fuel_left  / 6.02f * 3.78541f;
  const float liter_right = fuel_right / 6.02f * 3.78541f;

  const float height_ft     = height     / 0.305;
  const float min_height_ft = min_height / 0.305;


  if(!show_instructor) return;

  hmi::Colour::PaletteColour(cn_background);
  
  background.drawFill();

  hmi::Colour::PaletteColour(cn_foreground);

  HMIText fuel_label(hmi::FontManager::Get(0));
  fuel_label.left().top().size(0.20).position(0.0f,block_height).padding(10.0f,-5.0f);
  fuel_label << fixed << setprecision(1) << "Fuel - L:" << liter_left << " R:" << liter_right
	       << " T:" << liter_left+liter_right;
  fuel_label.draw();

  HMIText height_label(hmi::FontManager::Get(0));
  height_label.left().top().size(0.20).position(0.0f,block_height-30.0f).padding(10.0f,0.0f);
  height_label << fixed << setprecision(0) << "Height - Current: " << height_ft
	       << " Min: " << min_height_ft;
  height_label.draw();
}
