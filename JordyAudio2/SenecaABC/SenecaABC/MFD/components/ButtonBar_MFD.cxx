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

#include "ButtonBar_MFD.hxx"

#include <iomanip>
#include <iostream>
#include <map>
#include <string>


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

  map<size_t,string> labelmap;
};

ButtonBar_MFD::ButtonBar_MFD() :
    GaugeComponent("ButtonBar")
{

}

ButtonBar_MFD::~ButtonBar_MFD()
{

}

void ButtonBar_MFD::Init()
{
  labelmap[0]  = "SYSTEM";
  labelmap[3]  = "MAP";
  labelmap[10] = "DCLTR";
}

void ButtonBar_MFD::Render()
{
  // The background
  hmi::Colour::PaletteColour(cn_background);
  GLRectangle(0.0f,button_bar_height,0.0f,button_bar_width).drawFill();

  // The top line
  hmi::Colour::PaletteColour(cn_foreground);
  {
    GLLineWidth width(2.0);
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
}
