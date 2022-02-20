/* ------------------------------------------------------------------   */
/*      item            : MFDBezel.cxx
        made by         : jkvanleeuwen
        from template   : hmigauge_component.cxx
        template made by: Joost Ellerbroek
        date            : 081013
        category        : body file
        description     :
        changes         : 081013 first version
        language        : C++
*/

#include "MFDBezel.hxx"

#include <iomanip>
#include <map>
#include <string>


#include <hmi.hxx>

#include "ColorMap.hpp"
#include "GLTools.hxx"
#include "HMITools.hxx"
#include "Math.hxx"
#include <map>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>


using namespace std;

namespace
{
  const float left_bar_width  = 195.0f;
  const float left_bar_height =   912.0f;

  const float right_bar_width = 195.0f;
  const float bottom_bar_height = 95.0f;
  const float top_bar_height = 49.0f;
  const float bottom_bar_width = 1414.0f;



  const float window_edge_radius = 30.0f;


  const float button_width = 49.0f;
  const float button_height = 29.0f;
  const GLRectangle button(0.0f, button_height, 0.0f, button_width);
  const GLRectangle button_shade(-2.0f, 31.0f, -2.0f, 51.0f);

  const float skbutton_horizontal_sep = 85.0f;
  const float apbutton_vertical_sep = 50.0f;
  const float apbutton_horizontal_sep = 72.0f;

  // const size_t = 6;
  map<int, string> aplabelsleft;
  map<int, string> aplabelsright;
  map<int, string> fplabels;


  const float apbuttons_left_column1 = 27.0f;
  const float apbuttons_left_column2 = apbuttons_left_column1+apbutton_horizontal_sep;
  const float apbuttons_bottom = 165.0f;

  const float fdbuttons_left_column1 = 0.0f;
  const float fdbuttons_left_column2 = 0.0f;
  const float fdbuttons_bottom = 0.0f;


  int index_apc;
  int index_apr;


};

MFDBezel::MFDBezel() :
    GaugeComponent("MFDBezel")
{

}

MFDBezel::~MFDBezel()
{

}

void MFDBezel::Init()
{
  {
    aplabelsleft[0]  = "FLC";
    aplabelsleft[1]  = "VS";
    aplabelsleft[2]  = "APR";
    aplabelsleft[3]  = "NAV";
    aplabelsleft[4]  = "HDG";
    aplabelsleft[5]  = "AP";
  }
  {
    aplabelsright[0]  = "FD";
    aplabelsright[1]  = "ALT";
    aplabelsright[2]  = "VNV";
    aplabelsright[3]  = "BC";
    aplabelsright[4]  = "UP";
    aplabelsright[5]  = "DN";
  }
  {
    fplabels[0]  = "CLR";
    fplabels[1]  = "FPL";
    fplabels[2]  = "D";
    fplabels[3]  = "MENU";
    fplabels[4]  = "PROC";
    fplabels[5]  = "ENT";
  }
}

void MFDBezel::Render()
{

  // Four rectangles to cover the entire bezel
  glColor3f(0.255, 0.255, 0.255);
  GLRectangle(0.0f,left_bar_height,0.0f,left_bar_width).drawFill();
  GLRectangle(0.0f,bottom_bar_height,0.0f,bottom_bar_width).drawFill();
  GLRectangle(left_bar_height-top_bar_height, left_bar_height,0.0f,bottom_bar_width).drawFill();
  GLRectangle(0.0f,left_bar_height,bottom_bar_width-left_bar_width,bottom_bar_width).drawFill();


  // Drawing the rounded bezel edges
  hmi::Colour::PaletteColour(cn_background);
  GLRectangle(0.0f, window_edge_radius, 0.0f, window_edge_radius).drawFill();
  GLRectangle(0.0f, window_edge_radius, bottom_bar_width-window_edge_radius, bottom_bar_width).drawFill();
  GLRectangle(left_bar_height-window_edge_radius, left_bar_height, bottom_bar_width-window_edge_radius, bottom_bar_width).drawFill();
  GLRectangle(left_bar_height-window_edge_radius, left_bar_height, 0.0f, window_edge_radius).drawFill();
  glColor3f(0.255, 0.255, 0.255);
  {
    GLSaveMatrix matrix_state;
    GLLineSmooth antialias;
    glTranslatef(window_edge_radius,window_edge_radius,0.0f);
    GLBegin triangle_fan(GL_TRIANGLE_FAN);
    glVertex2f( 0.0f, 0.0f );
    circlePoints(window_edge_radius, deg2rad(0.0f), deg2rad(360.0f), 36);
  }
  {
    GLSaveMatrix matrix_state;
    GLLineSmooth antialias;
    glTranslatef(bottom_bar_width-window_edge_radius,window_edge_radius,0.0f);
    GLBegin triangle_fan(GL_TRIANGLE_FAN);
    glVertex2f( 0.0f, 0.0f );
    circlePoints(window_edge_radius, deg2rad(0.0f), deg2rad(360.0f), 36);
  }
  {
    GLSaveMatrix matrix_state;
    GLLineSmooth antialias;
    glTranslatef(bottom_bar_width-window_edge_radius, left_bar_height-window_edge_radius,0.0f);
    GLBegin triangle_fan(GL_TRIANGLE_FAN);
    glVertex2f( 0.0f, 0.0f );
    circlePoints(window_edge_radius, deg2rad(0.0f), deg2rad(360.0f), 36);
  }
  {
    GLSaveMatrix matrix_state;
    GLLineSmooth antialias;
    glTranslatef(window_edge_radius, left_bar_height-window_edge_radius,0.0f);
    GLBegin triangle_fan(GL_TRIANGLE_FAN);
    glVertex2f( 0.0f, 0.0f );
    circlePoints(window_edge_radius, deg2rad(0.0f), deg2rad(360.0f), 36);
  }


  // drawing the two thick vertical lines
  {
    GLSaveMatrix matrix_state;
    GLLineSmooth antialias;
    GLLineWidth line_width(5.0f);
    glColor3f(0.125,0.125,0.125);
    {
      GLBegin lines(GL_LINES);
      glVertex2f(left_bar_width-20.0f, 0.0f);
      glVertex2f(left_bar_width-20.0f, left_bar_height);
    }
    {
      GLBegin lines(GL_LINES);
      glVertex2f(bottom_bar_width-left_bar_width+20.0f, 0.0f);
      glVertex2f(bottom_bar_width-left_bar_width+20.0f, left_bar_height);
    }
  }

  // drawing the two thin horizontal lines
  {
    GLSaveMatrix matrix_state;
    GLLineSmooth antialias;
    GLLineWidth line_width(2.0f);
    {
      GLBegin lines(GL_LINES);
      glVertex2f(left_bar_width-5.0f, bottom_bar_height-5.0f);
      glVertex2f(bottom_bar_width-left_bar_width+5.0f, bottom_bar_height-5.0f);
    }
    {
      GLBegin lines(GL_LINES);
      glVertex2f(left_bar_width-5.0f, left_bar_height - top_bar_height + 5.0f);
      glVertex2f(bottom_bar_width-left_bar_width+5.0f, left_bar_height - top_bar_height + 5.0f);
    }
  }


  // Drawing Softkey buttons
  {
    GLSaveMatrix matrix_state;
    GLLineSmooth antialias;
    glTranslatef(212.0f, 35.0f, 0.0f);
    GLLineWidth line_width(4.0f);
    for(int i=0; i<12; i++){
      glColor3f(0.125, 0.125, 0.125);
      button_shade.drawFill();
      {
        GLBegin lines(GL_LINES);
        glVertex2f(24.0f, 29.0f);
        glVertex2f(24.0f, bottom_bar_height-40.0f);
      }
      glColor3f(0.31, 0.31, 0.31);
      button.drawFill();
      {
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_TRIANGLES);
        glVertex2f(14.0f, 10.0f);
        glVertex2f(36.0f, 10.0f);
        glVertex2f(25.0f, 21.0f);
        glEnd();
      }
      glTranslatef(skbutton_horizontal_sep, 0.0f, 0.0f);
    }
  }


  // Drawing AP buttons
  HMIText text(hmi::FontManager::Get(2));
  // {
  //   GLSaveMatrix matrix_state;
  //   GLLineSmooth antialias;
  //   glTranslatef(apbuttons_left_column1, apbuttons_bottom, 0.0f);
  //
  //   for(int i=0; i<6; i++){
  //     glColor3f(0.125, 0.125, 0.125);
  //     button_shade.drawFill();
  //     glColor3f(0.31, 0.31, 0.31);
  //     button.drawFill();
  //
  //     hmi::Colour::PaletteColour(cn_foreground);
  //     text.clear().position(25.0f, 14.0f).hcenter().vcenter().size(0.18);
  //     text << aplabelsleft.at(i);;
  //     text.draw();
  //
  //     glTranslatef(0.0f, apbutton_vertical_sep, 0.0f);
  //   }
  //
  //   glTranslatef(apbutton_horizontal_sep, -apbutton_vertical_sep, 0.0f);
  //   for(int i=0; i<6; i++){
  //     glColor3f(0.125, 0.125, 0.125);
  //     button_shade.drawFill();
  //     glColor3f(0.31, 0.31, 0.31);
  //     button.drawFill();
  //
  //     hmi::Colour::PaletteColour(cn_foreground);
  //     text.clear().position(25.0f, 14.0f).hcenter().vcenter().size(0.18);
  //     text << aplabelsright.at(i);;
  //     text.draw();
  //
  //     glTranslatef(0.0f, -apbutton_vertical_sep, 0.0f);
  //   }
  // }

  // Drawing FP buttons
  {
    GLSaveMatrix matrix_state;
    GLLineSmooth antialias;
    glTranslatef(1261.0f, 161.0f, 0.0f);

    for(int i=0; i<3; i++){
      glColor3f(0.125, 0.125, 0.125);
      button_shade.drawFill();
      glColor3f(0.31, 0.31, 0.31);
      button.drawFill();

      hmi::Colour::PaletteColour(cn_foreground);
      text.clear().position(25.0f, 14.0f).hcenter().vcenter().size(0.15);
      text << fplabels.at(i);;
      text.draw();

      glTranslatef(0.0f, apbutton_vertical_sep, 0.0f);
    }

    glTranslatef(apbutton_horizontal_sep, -apbutton_vertical_sep, 0.0f);
    for(int i=0; i<3; i++){
      glColor3f(0.125, 0.125, 0.125);
      button_shade.drawFill();
      glColor3f(0.31, 0.31, 0.31);
      button.drawFill();

      hmi::Colour::PaletteColour(cn_foreground);
      text.clear().position(25.0f, 14.0f).hcenter().vcenter().size(0.15);
      text << fplabels.at(i+3);;
      text.draw();

      glTranslatef(0.0f, -apbutton_vertical_sep, 0.0f);
    }
  }

  {
    GLSaveMatrix matrix_state;
    GLLineSmooth antialias;
    hmi::Colour::PaletteColour(cn_foreground);
    text.clear().position(bottom_bar_width/2.0f, left_bar_height-top_bar_height/2.5f).hcenter().vcenter().size(0.22);
    text << "G1000";
    text.draw();
  }

  // ALT button
  {
    GLSaveMatrix matrix_state;
    GLLineSmooth antialias;
    glTranslatef(85.0f, 85.0f, 0.0f);
    hmi::Colour::PaletteColour(cn_foreground);
    text.clear().position(0.0f, 53.0f).hcenter().vcenter().size(0.22);
    text << "ALT";
    text.draw();
    {
      glColor3f(0.125, 0.125, 0.125);
      GLBegin triangle_fan(GL_TRIANGLE_FAN);
      glVertex2f( 0.0f, 0.0f );
      circlePoints(39, deg2rad(0.0f), deg2rad(360.0f), 36);
    }
    {
      glColor3f(0.31, 0.31, 0.31);
      GLBegin triangle_fan(GL_TRIANGLE_FAN);
      glVertex2f( 0.0f, 0.0f );
      circlePoints(35, deg2rad(0.0f), deg2rad(360.0f), 36);
    }
    {
      glColor3f(0.125, 0.125, 0.125);
      GLBegin triangle_fan(GL_TRIANGLE_FAN);
      glVertex2f( 0.0f, 0.0f );
      circlePoints(23, deg2rad(0.0f), deg2rad(360.0f), 36);
    }
    {
      glColor3f(0.31, 0.31, 0.31);
      GLBegin triangle_fan(GL_TRIANGLE_FAN);
      glVertex2f( 0.0f, 0.0f );
      circlePoints(21, deg2rad(0.0f), deg2rad(360.0f), 36);
    }
  }

  // FMS button
  {
    GLSaveMatrix matrix_state;
    GLLineSmooth antialias;
    glTranslatef(bottom_bar_width-85.0f, 85.0f, 0.0f);
    hmi::Colour::PaletteColour(cn_foreground);
    text.clear().position(0.0f, 53.0f).hcenter().vcenter().size(0.22);
    text << "FMS";
    text.draw();
    {
      glColor3f(0.125, 0.125, 0.125);
      GLBegin triangle_fan(GL_TRIANGLE_FAN);
      glVertex2f( 0.0f, 0.0f );
      circlePoints(39, deg2rad(0.0f), deg2rad(360.0f), 36);
    }
    {
      glColor3f(0.31, 0.31, 0.31);
      GLBegin triangle_fan(GL_TRIANGLE_FAN);
      glVertex2f( 0.0f, 0.0f );
      circlePoints(35, deg2rad(0.0f), deg2rad(360.0f), 36);
    }
    {
      glColor3f(0.125, 0.125, 0.125);
      GLBegin triangle_fan(GL_TRIANGLE_FAN);
      glVertex2f( 0.0f, 0.0f );
      circlePoints(23, deg2rad(0.0f), deg2rad(360.0f), 36);
    }
    {
      glColor3f(0.31, 0.31, 0.31);
      GLBegin triangle_fan(GL_TRIANGLE_FAN);
      glVertex2f( 0.0f, 0.0f );
      circlePoints(21, deg2rad(0.0f), deg2rad(360.0f), 36);
    }
  }


  // NAV button
  {
    GLSaveMatrix matrix_state;
    GLLineSmooth antialias;
    glTranslatef(85.0f, 702.0f, 0.0f);
    hmi::Colour::PaletteColour(cn_foreground);
    text.clear().position(0.0f, 53.0f).hcenter().vcenter().size(0.22);
    text << "NAV";
    text.draw();
    {
      glColor3f(0.125, 0.125, 0.125);
      GLBegin triangle_fan(GL_TRIANGLE_FAN);
      glVertex2f( 0.0f, 0.0f );
      circlePoints(39, deg2rad(0.0f), deg2rad(360.0f), 36);
    }
    {
      glColor3f(0.31, 0.31, 0.31);
      GLBegin triangle_fan(GL_TRIANGLE_FAN);
      glVertex2f( 0.0f, 0.0f );
      circlePoints(35, deg2rad(0.0f), deg2rad(360.0f), 36);
    }
    {
      glColor3f(0.125, 0.125, 0.125);
      GLBegin triangle_fan(GL_TRIANGLE_FAN);
      glVertex2f( 0.0f, 0.0f );
      circlePoints(23, deg2rad(0.0f), deg2rad(360.0f), 36);
    }
    {
      glColor3f(0.31, 0.31, 0.31);
      GLBegin triangle_fan(GL_TRIANGLE_FAN);
      glVertex2f( 0.0f, 0.0f );
      circlePoints(21, deg2rad(0.0f), deg2rad(360.0f), 36);
    }
  }

  // COM button
  {
    GLSaveMatrix matrix_state;
    GLLineSmooth antialias;
    glTranslatef(bottom_bar_width-85.0f, 702.0f, 0.0f);
    hmi::Colour::PaletteColour(cn_foreground);
    text.clear().position(0.0f, 53.0f).hcenter().vcenter().size(0.22);
    text << "COM";
    text.draw();
    {
      glColor3f(0.125, 0.125, 0.125);
      GLBegin triangle_fan(GL_TRIANGLE_FAN);
      glVertex2f( 0.0f, 0.0f );
      circlePoints(39, deg2rad(0.0f), deg2rad(360.0f), 36);
    }
    {
      glColor3f(0.31, 0.31, 0.31);
      GLBegin triangle_fan(GL_TRIANGLE_FAN);
      glVertex2f( 0.0f, 0.0f );
      circlePoints(35, deg2rad(0.0f), deg2rad(360.0f), 36);
    }
    {
      glColor3f(0.125, 0.125, 0.125);
      GLBegin triangle_fan(GL_TRIANGLE_FAN);
      glVertex2f( 0.0f, 0.0f );
      circlePoints(23, deg2rad(0.0f), deg2rad(360.0f), 36);
    }
    {
      glColor3f(0.31, 0.31, 0.31);
      GLBegin triangle_fan(GL_TRIANGLE_FAN);
      glVertex2f( 0.0f, 0.0f );
      circlePoints(21, deg2rad(0.0f), deg2rad(360.0f), 36);
    }
  }

  // HDG button
  {
    GLSaveMatrix matrix_state;
    GLLineSmooth antialias;
    glTranslatef(85.0f, 580.0f, 0.0f);
    hmi::Colour::PaletteColour(cn_foreground);
    text.clear().position(0.0f, 53.0f).hcenter().vcenter().size(0.22);
    text << "HDG";
    text.draw();
    {
      glColor3f(0.125, 0.125, 0.125);
      GLBegin triangle_fan(GL_TRIANGLE_FAN);
      glVertex2f( 0.0f, 0.0f );
      circlePoints(39, deg2rad(0.0f), deg2rad(360.0f), 36);
    }
    {
      glColor3f(0.31, 0.31, 0.31);
      GLBegin triangle_fan(GL_TRIANGLE_FAN);
      glVertex2f( 0.0f, 0.0f );
      circlePoints(35, deg2rad(0.0f), deg2rad(360.0f), 36);
    }
  }

  // CRS button
  {
    GLSaveMatrix matrix_state;
    GLLineSmooth antialias;
    glTranslatef(bottom_bar_width-85.0f, 580.0f, 0.0f);
    hmi::Colour::PaletteColour(cn_foreground);
    text.clear().position(0.0f, 53.0f).hcenter().vcenter().size(0.22);
    text << "CRS";
    text.draw();
    {
      glColor3f(0.125, 0.125, 0.125);
      GLBegin triangle_fan(GL_TRIANGLE_FAN);
      glVertex2f( 0.0f, 0.0f );
      circlePoints(39, deg2rad(0.0f), deg2rad(360.0f), 36);
    }
    {
      glColor3f(0.31, 0.31, 0.31);
      GLBegin triangle_fan(GL_TRIANGLE_FAN);
      glVertex2f( 0.0f, 0.0f );
      circlePoints(35, deg2rad(0.0f), deg2rad(360.0f), 36);
    }
  }

  // Volume button left
  {
    GLSaveMatrix matrix_state;
    GLLineSmooth antialias;
    glTranslatef(85.0f, left_bar_height-85.0f, 0.0f);
    {
      glColor3f(0.125, 0.125, 0.125);
      GLBegin triangle_fan(GL_TRIANGLE_FAN);
      glVertex2f( 0.0f, 0.0f );
      circlePoints(23, deg2rad(0.0f), deg2rad(360.0f), 36);
    }
    {
      glColor3f(0.31, 0.31, 0.31);
      GLBegin triangle_fan(GL_TRIANGLE_FAN);
      glVertex2f( 0.0f, 0.0f );
      circlePoints(21, deg2rad(0.0f), deg2rad(360.0f), 36);
    }
  }
  // Volume button right
  {
    GLSaveMatrix matrix_state;
    GLLineSmooth antialias;
    glTranslatef(bottom_bar_width-85.0f, left_bar_height-85.0f, 0.0f);
    {
      glColor3f(0.125, 0.125, 0.125);
      GLBegin triangle_fan(GL_TRIANGLE_FAN);
      glVertex2f( 0.0f, 0.0f );
      circlePoints(23, deg2rad(0.0f), deg2rad(360.0f), 36);
    }
    {
      glColor3f(0.31, 0.31, 0.31);
      GLBegin triangle_fan(GL_TRIANGLE_FAN);
      glVertex2f( 0.0f, 0.0f );
      circlePoints(21, deg2rad(0.0f), deg2rad(360.0f), 36);
    }
  }

  // NAV radio switch
  {
    GLSaveMatrix matrix_state;
    GLLineSmooth antialias;
    glTranslatef(106.0f, 771.0f, 0.0f);
    glColor3f(0.125, 0.125, 0.125);
    button_shade.drawFill();
    glColor3f(0.31, 0.31, 0.31);
    button.drawFill();
    GLLineWidth line_width(3.0f);
    glColor3f(1.0, 1.0, 1.0);
    {
      GLBegin lines(GL_LINES);
      glVertex2f(8.0f, 14.0f);
      glVertex2f(41.0f, 14.0f);
    }
    {
      glBegin(GL_TRIANGLES);
      glVertex2f(6.0f, 14.0f);
      glVertex2f(17.0f, 23.0f);
      glVertex2f(17.0f, 5.0f);
      glEnd();
    }
    {
      glBegin(GL_TRIANGLES);
      glVertex2f(43.0f, 14.0f);
      glVertex2f(32.0f, 23.0f);
      glVertex2f(32.0f, 5.0f);
      glEnd();
    }
  }

  // COM radio switch
  {
    GLSaveMatrix matrix_state;
    GLLineSmooth antialias;
    glTranslatef(1260.0f, 771.0f, 0.0f);
    glColor3f(0.125, 0.125, 0.125);
    button_shade.drawFill();
    glColor3f(0.31, 0.31, 0.31);
    button.drawFill();
    GLLineWidth line_width(3.0f);
    glColor3f(1.0, 1.0, 1.0);
    {
      GLBegin lines(GL_LINES);
      glVertex2f(8.0f, 14.0f);
      glVertex2f(41.0f, 14.0f);
    }
    {
      glBegin(GL_TRIANGLES);
      glVertex2f(6.0f, 14.0f);
      glVertex2f(17.0f, 23.0f);
      glVertex2f(17.0f, 5.0f);
      glEnd();
    }
    {
      glBegin(GL_TRIANGLES);
      glVertex2f(43.0f, 14.0f);
      glVertex2f(32.0f, 23.0f);
      glVertex2f(32.0f, 5.0f);
      glEnd();
    }
  }


  // glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //
  // // viewing matrix
  // glMatrixMode(GL_MODELVIEW);
  // glLoadIdentity();
  //
  // // texture
  // glEnable (GL_TEXTURE_2D);
  // glBindTexture (GL_TEXTURE_2D, texture_id);
  //
  // //glColor3f(1.0, 1.0, 1.0);
  // glBegin(GL_QUADS);
  // glTexCoord2f (0.0f,1.0f); 	// upper left corner of image
  // glVertex2f(-1.0, 1.0);
  // glTexCoord2f (1.0f,1.0f); 	// upper right corner of image
  // glVertex2f( 1.0, 1.0);
  // glTexCoord2f (1.0f,0.0f);// lower right corner of image
  // glVertex2f(1.0,-1.0);
  // glTexCoord2f (0.0f,0.0);// lower left corner of image
  // glVertex2f(-1.0,-1.0);
  // glEnd();
  //
  // glDisable (GL_TEXTURE_2D);



}
