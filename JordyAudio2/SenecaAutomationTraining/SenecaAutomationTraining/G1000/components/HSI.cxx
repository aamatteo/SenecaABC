/* ------------------------------------------------------------------   */
/*      item            : HSI.cxx
        made by         : jcomans
        from template   : hmigauge_component.cxx
        template made by: Joost Ellerbroek
        date            : 081013
        category        : body file
        description     :
        changes         : 081013 first version
        language        : C++
*/

#include "HSI.hxx"

#include <hmi.hxx>
#include <fstream>
#include "ColorMap.hpp"
#include "GLTools.hxx"
#include "HMITools.hxx"
#include "Math.hxx"

namespace
{
  const float max_deflection = 70.0f;
  const float max_offset = 10;
  bool prev_GMU_failure;
  float frozen_heading;

  int nr_of_wps;
  std::string prev_file_name;
  std::string comment;
};

HSI::HSI() :
    GaugeComponent("HSI")
{
}

HSI::~HSI()
{

}

void HSI::Init()
{
}

void HSI::Render()
{
  float heading = *GetData().heading;

  const float& course    =  *GetData().course;
  float offset    = *GetData().needle_deviation;

  const int& active_nav_source = *GetData().active_nav_source;

  const bool VOR_failure = *GetData().VOR_failure;
  const bool HSI_failure = *GetData().HSI_failure;
  const bool GMU_failure = *GetData().GMU_failure;
  const bool AFCS_rol = *GetData().AFCS_rol;
  bool vor_flag_state = *GetData().vor_flag_state;
  const std::string filename = *GetData().fp_name;

  if(filename != prev_file_name && filename.length()>0){
    std::ifstream myfile (filename);

    myfile >> comment >> comment >> comment;
    myfile >> comment >> comment;
    myfile >> comment >> comment >> comment;
    myfile >> comment >> comment;
    myfile >> comment >> comment >> comment;
    myfile >> comment >> comment >> comment;
    myfile >> comment >> comment >> comment;
    myfile >> comment >> nr_of_wps;

    myfile.close();
  }
  if(filename.length() < 3){
    nr_of_wps = 0;
  }

  if(nr_of_wps == 0 && active_nav_source == 0){
    offset = max_offset;
    vor_flag_state = true;
  }

  // const float max_offset = nm2m( 1.0f );


  if(GMU_failure && prev_GMU_failure == false){
    frozen_heading = heading;
  }
  if(GMU_failure){
    heading = frozen_heading;
  }
  prev_GMU_failure = GMU_failure;

  {
    GLSaveMatrix matrixstate;

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

    HMIText text(hmi::FontManager::Get(0));
    switch(active_nav_source){
      case 0:
        text.position(-24.0,24.0).right().bottom().size(0.20);
        text << "GPS";
        text.draw();

        text.clear();
        text.position(24.0,24.0).left().bottom().size(0.20);
        text << "ENR";
        text.draw();
        break;

      case 1:
        text.position(-24.0,24.0).right().bottom().size(0.20);
        text << "VOR1";
        text.draw();

        text.clear();
        text.position(24.0,24.0).left().bottom().size(0.20);
        text << "";
        text.draw();
        break;

      case 2:
        text.position(-24.0,24.0).right().bottom().size(0.20);
        text << "VOR2";
        text.draw();

        text.clear();
        text.position(24.0,24.0).left().bottom().size(0.20);
        text << "";
        text.draw();
      break;

    }



    {
      GLSaveMatrix state;
      GLLineWidth width(3.0f);
      GLLineSmooth antialias;

      glRotatef(  rad2deg(heading) , 0.0f, 0.0f, 1.0f);
      glRotatef( -course  , 0.0f, 0.0f, 1.0f);

      GLTriangle( 0.0f , 127.0f, -15.0f, 112.0f, 15.0f, 112.0f ).drawFill();

      if(active_nav_source>0){
        if(vor_flag_state){
          GLTriangle( 0.0f , 74.0f, -12.0f, 62.0f, 12.0f, 62.0f ).drawFill();
        }else{
          GLTriangle( 0.0f , -74.0f, -12.0f, -62.0f, 12.0f, -62.0f ).drawFill();
        }
      }

      switch(active_nav_source){
        case 0:
          glBegin(GL_LINES);
          glVertex2f( 0.0f ,  127.0f );
          glVertex2f( 0.0f ,   62.0f );

          glVertex2f( 0.0f ,  -62.0f );
          glVertex2f( 0.0f , -127.0f );
          glEnd();
        break;

        case 1:
          glBegin(GL_LINES);
          glVertex2f( 0.0f ,  127.0f );
          glVertex2f( 0.0f ,   62.0f );

          glVertex2f( 0.0f ,  -62.0f );
          glVertex2f( 0.0f , -127.0f );
          glEnd();
        break;

        case 2:
          glBegin(GL_LINES);
          glVertex2f( 3.0f ,  122.0f );
          glVertex2f( 3.0f ,   62.0f );

          glVertex2f( 3.0f ,  -62.0f );
          glVertex2f( 3.0f , -127.0f );
          glEnd();

          glBegin(GL_LINES);
          glVertex2f( -3.0f ,  122.0f );
          glVertex2f( -3.0f ,   62.0f );

          glVertex2f( -3.0f ,  -62.0f );
          glVertex2f( -3.0f , -127.0f );
          glEnd();
        break;
      }



    }

    hmi::Colour::PaletteColour(cn_foreground);

    {
      GLSaveMatrix state;
      glRotatef(  rad2deg(heading) , 0.0f, 0.0f, 1.0f);
      glRotatef( -course  , 0.0f, 0.0f, 1.0f);
      {
	GLSaveMatrix state;
	glTranslatef(max_deflection/2.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	circlePoints(5.0f, deg2rad(0.0f), deg2rad(360.0f), 12);
	glEnd();
      }

      {
	GLSaveMatrix state;
	glTranslatef(max_deflection, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	circlePoints(5.0f, deg2rad(0.0f), deg2rad(360.0f), 12);
	glEnd();
      }

      {
	GLSaveMatrix state;
	glTranslatef(-max_deflection/2.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	circlePoints(5.0f, deg2rad(0.0f), deg2rad(360.0f), 12);
	glEnd();
      }

      {
	GLSaveMatrix state;
	glTranslatef(-max_deflection, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	circlePoints(5.0f, deg2rad(0.0f), deg2rad(360.0f), 12);
	glEnd();
      }

      if(VOR_failure == false || active_nav_source == 0){
        GLLineWidth width(3.0f);
        GLLineSmooth antialias;

        if( offset < -max_offset )
  	       glTranslatef( -max_deflection , 0.0f, 0.0f );
        else if( offset > max_offset )
  	       glTranslatef(  max_deflection , 0.0f, 0.0f );
        else
  	       glTranslatef( max_deflection * offset/max_offset , 0.0f, 0.0f );

           switch(active_nav_source){
             case 0:
               hmi::Colour::PaletteColour(cn_nav);
               glBegin(GL_LINES);
               glVertex2f( 0.0f ,   58.0f );
               glVertex2f( 0.0f ,  -58.0f );
               glEnd();
             break;

             case 1:
               hmi::Colour::PaletteColour(cn_apmode);
               glBegin(GL_LINES);
               glVertex2f( 0.0f ,   58.0f );
               glVertex2f( 0.0f ,  -58.0f );
               glEnd();
             break;

             case 2:
               hmi::Colour::PaletteColour(cn_apmode);
               glBegin(GL_LINES);
               glVertex2f( 3.0f ,   58.0f );
               glVertex2f( 3.0f ,  -58.0f );
               glEnd();

               glBegin(GL_LINES);
               glVertex2f( -3.0f ,   58.0f );
               glVertex2f( -3.0f ,  -58.0f );
               glEnd();
             break;
           }

    }
    }
  }
}
