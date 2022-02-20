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

#include "Map.hxx"

// HMILib objects and functions
#include <hmi.hxx>

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <list>

#include "ColorMap.hpp"
#include "GLTools.hxx"
#include "HMITools.hxx"
#include "Math.hxx"
#include <tuple>

#include <GL/glut.h>


float getAngle(Eigen::Vector2d A, Eigen::Vector2d B, Eigen::Vector2d C){
  float ang = RAD2DEG * (atan2(C(1)-B(1), C(0)-B(0)) - atan2(A(1)-B(1), A(0)-B(0)));
  if(ang<0){
    return ang + 360;
  }
  else{
    return ang;
  }
}

std::tuple<Eigen::Vector2d, Eigen::Vector2d>  getCenter(Eigen::Vector2d A, Eigen::Vector2d B, float r){
  float x1 = A(0);
  float y1 = A(1);
  float x2 = B(0);
  float y2 = B(1);

  float xa = 0.5 * (x2-x1);
  float ya = 0.5 * (y2-y1);
  float x0 = x1 + xa;
  float y0 = y1 + ya;
  float a = pow(pow(xa,2)+pow(ya,2), 0.5);
  float b = pow(pow(r,2)-pow(a,2), 0.5);

  Eigen::Vector2d C(x0 + (b*ya)/a, y0 - (b*xa)/a);
  Eigen::Vector2d D(x0 - (b*ya)/a, y0 + (b*xa)/a);

  return std::make_tuple(C,D);
}

std::tuple<Eigen::Vector2d, float, float> getMid(Eigen::Vector2d A, Eigen::Vector2d B, float abc, float r){
  float AB = pow(pow(B(0)-A(0), 2)+pow(B(1)-A(1),2), 0.5);
  float EB = r/(tan(0.5*abc/RAD2DEG));
  float AE = AB - EB;

  Eigen::Vector2d E(0,0);

  float hab;

  if(A(1)<=B(1)){
    hab = asin((B(1)-A(1))/AB);
    E(1) = A(1)+AE*sin(hab);
  } else{
    hab = asin((A(1)-B(1))/AB);
    E(1) = A(1)-AE*sin(hab);
  }

  if(A(0)<=B(0)){
    E(0) = A(0)+AE*cos(hab);
  } else{
    E(0) = A(0)-AE*cos(hab);
  }

  return std::make_tuple(E, EB, hab);
}


std::tuple<Eigen::Vector2d, Eigen::Vector2d, Eigen::Vector2d, float, float> planIntersection(Eigen::Vector2d A, Eigen::Vector2d B, Eigen::Vector2d C, float r){
  float abc = getAngle(A, B, C);
  bool change_D = false;
  if(abc>180){
    change_D = true;
    abc = 360 - abc;
  }

  Eigen::Vector2d E(0,0);
  Eigen::Vector2d F(0,0);
  Eigen::Vector2d D(0,0);
  Eigen::Vector2d D1(0,0);
  Eigen::Vector2d D2(0,0);

  float EB, FB, hab, hcb, theta0, theta1;

  std::tie(E, EB, hab) = getMid(A, B, abc, r);
  std::tie(F, FB, hcb) = getMid(C, B, abc, r);

  float hed = 90/RAD2DEG-hab;

  std::tie(D1, D2) = getCenter(E, F, r);

  if(change_D){
    D = D2;
    theta1 = RAD2DEG * (atan2(F(1)-D(1), F(0)-D(0)));
    theta0 = theta1 - 180 + abc;
  }else{
    D = D1;
    theta0 = RAD2DEG * (atan2(F(1)-D(1), F(0)-D(0)));
    theta1 = theta0 + 180 - abc;
  }

  return std::make_tuple(E,F,D,theta0,theta1);
}

struct DigitBar
{ float x0,y0,x1,y1, color;};

namespace
{
  float map_width = 879.0f;

  const float map_height = 686.0f;

  GLRectangle map_block(1.0, 1.0, 1.0, 1.0);

  const float vor_height = 16.0f;
  const float vor_width = 20.0f;
  const float vor_corner = 6.0f;
  const GLRectangle vor_box(0.0f,vor_height,0.0f,vor_width);
  GLRectangle scale_box(1.0, 1.0, 1.0, 1.0);

  const float intersection_width = 7;
  const float intersection_height = 6;

  const float airport_box_width = 40.0f;
  const float airport_box_height = 18.0f;
  const GLRectangle airport_box(0.0f, airport_box_height, 0.0f, airport_box_width);

  const float rose_radius = 174;
  const float small_tick_length = 5;
  const float large_tick_length = 10;

  const float plane_length = 25.0f;

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

  const float fpbox_left = 599.0f - 145.0f;
  const float fpbox_right = 1015.0f - 145.0f;
  const float fpbox_bottom = 267.0f - 27.0f;
  const float fpbox_top = 604.0f - 27.0f;

  const GLRectangle fpbox(fpbox_bottom, fpbox_top, fpbox_left, fpbox_right);

  const GLRectangle fppage_box(0.0f, map_height ,map_width/2.0f, map_width);
  const float fpboxLine_top = 692.0f - 27.0f;
  const float fpboxLine_bottom = fpbox_top;
  const float fpboxLine_left = fpbox_left;
  const float fpboxLine_right = fpbox_right;
  const float fpboxLine_x1 = 611.0f - 145.0f;
  const float fpboxLine_x2 = 778.0f - 145.0f;
  const float fpboxLine_y1 = 682.0f - 27.0f;

  const float vnvboxLine_top = 234.0f - 27.0f;
  const float vnvboxLine_bottom = 103.0f - 27.0f;
  const float vnvboxLine_left = fpbox_left;
  const float vnvboxLine_right = fpbox_right;
  const float vnvboxLine_x1 = fpboxLine_x1;
  const float vnvboxLine_x2 = fpboxLine_x2;
  const float vnvboxLine_y1 = 224.0f - 27.0f;

  const float dtkcolumn_x = 656.0f;
  const float dtkcolumn_y = fpbox_top + 4.0f;
  const float discolumn_x = 740.0f;
  const float discolumn_y = dtkcolumn_y;
  const float altcolumn_x = 816.0f;
  const  float altcolumn_y = dtkcolumn_y;


  float vor1_x;
  float vor1_y;
  float vor2_x;
  float vor2_y;
  int use_vor1;
  int use_vor2;

  float frozen_x;
  float frozen_y;
  bool prev_GPS_failure;

  float load_wp = true;

  std::string wp;
  std::string comment;
  float lat;
  float lon;
  float alt;
  int nr_wps = 0;
  int nr_of_map_items = 0;

  Eigen::MatrixXd fp_location(1,3);
  Eigen::MatrixXd map_items(1,3);
  std::vector<std::string> wp_names;
  std::vector<std::string> item_names;
  std::string prev_file_name;
  int nr_of_wp;
  std::string dummy_string;

  float dx;
  float dy;
  float dtk;

  float fpl_page_old;

  float iter_wps;
  float alt_v;

  float time_to_top;
  int is_vnav_descending = 0;

  bool fpl_page = false;

  float frozen_heading;

  float Vtas_demped;
  float prevVtas;
};

Map::Map() :
    GaugeComponent("Map"),
    _gl_display_list_index(0)
{
}
Map::~Map(){
  glDeleteLists(_gl_display_list_index,1);
}

void Map::Init(){
  _gl_display_list_index = glGenLists(1);

  if(!_gl_display_list_index) throw "Unable to get GL display list";
  glNewList( _gl_display_list_index+0, GL_COMPILE);

  hmi::Colour::PaletteColour(cn_foreground);
  GLLineSmooth antialias;
  GLLineWidth line_width(2.0f);
  {
    GLSaveMatrix matrix_state;
    glTranslatef(map_width/2,map_height/2,0.0f);
    {
      glBegin(GL_LINE_STRIP);
      ///TODO: Properly deal with floating point limits
      circlePoints( rose_radius, deg2rad(0.0f), deg2rad(360.0f), 60 );
      glEnd();
    }

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
        GLBegin lines(GL_LINES);
        glVertex2f( rose_radius*sin(step) , rose_radius*cos(step) );
        glVertex2f( (rose_radius-large_tick_length)*sin(step),
            (rose_radius-large_tick_length)*cos(step) );
      }
    }
  }
  glEndList();
}

void Map::Render()
{

  float heading = rad2deg(*GetData().heading);
  const int active_leg = *GetData().active_leg;
  const int active_vnv_leg = *GetData().active_vnv_leg;
  const int curVerticalState = *GetData().curVerticalState;
  const float Vtas = *GetData().Vtas;
  const float dist_to_top = *GetData().dist_to_top;
  float time_to_bod = *GetData().time_to_bod;
  const bool GPS_failure = *GetData().GPS_failure;
  const std::string filename = *GetData().fp_name;
  const int msg = *GetData().msg;
  const int scale = *GetData().range;
  const float altitude = *GetData().altitude;
  const float fpa_req = *GetData().fpa_req;
  const float dt = *GetData().dt;

  Vtas_demped = prevVtas + dt/1.0*(Vtas - prevVtas);
  prevVtas = Vtas_demped;

  if(msg == 14){
    fpl_page = !fpl_page;
  }
  float x = *GetData().x;
  float y = *GetData().y;

  time_to_top = dist_to_top/(Vtas);

  GLSaveMatrix matrix_state;
  HMIText text(hmi::FontManager::Get(1));

  if(fpl_page){
    map_width = 440.0f;
  }
  else{
    map_width = 879.0f;
  }

  if (fpl_page != fpl_page_old){
    Map::Init();
  }
  fpl_page_old = fpl_page;


  map_block = GLRectangle(0.0f,map_height,0.0f,map_width);
  scale_box = GLRectangle(474.0f, 493.0f, 522.0f-879.0f/2 + map_width/2, 569.0f-879.0f/2 + map_width/2);

  // read the flight plan if a new one becomes available
  if(filename != prev_file_name){
    std::cout << "Filename received: " << filename << "\n";
    nr_of_wp = 0;
    nr_of_map_items = 0;
  }
  if(filename != prev_file_name && filename.length()>0){
    std::ifstream myfile (filename);
    is_vnav_descending = 0;

    myfile >> comment >> dummy_string >> dummy_string;
    myfile >> comment >> dummy_string;
    myfile >> comment >> dummy_string >> dummy_string;
    myfile >> comment >> dummy_string;

    myfile >> comment >> use_vor1 >> use_vor2;
    myfile >> comment >> vor1_x >> vor1_y;
    myfile >> comment >> vor2_x >> vor2_y;

    myfile >> comment >> nr_of_wp;
    fp_location.resize(nr_of_wp, 5);
    wp_names.clear();
    for(int i=0; i<nr_of_wp; i++){
      myfile >> wp >> lat >> lon >> alt;
      wp_names.push_back(wp);
      fp_location(i,0) = lat;
      fp_location(i,1) = lon;
      fp_location(i,2) = alt;
    }
    if(nr_of_wp>0){
      fp_location(0,3) = 0;
      fp_location(0,4) = 0;
    }
    for(int i=1; i<nr_of_wp; i++){
      dx = fp_location(i,0)-fp_location(i-1,0);
      dy = fp_location(i,1)-fp_location(i-1,1);
      dtk = rad2deg(atan2(dx, dy));
      if(dtk<0){
        dtk +=360;
      }
      fp_location(i,3) = dtk;
      fp_location(i,4) = sqrt(dx*dx+dy*dy)/1852.0f;
    }

    myfile >> comment >> nr_of_map_items;
    map_items.resize(nr_of_map_items, 3);
    item_names.clear();
    for(int i=0; i<nr_of_map_items; i++){
      myfile >> wp >> lat >> lon >> alt;
      item_names.push_back(wp);
      map_items(i,0) = lat;
      map_items(i,1) = lon;
      map_items(i,2) = alt;
    }

    myfile.close();
    load_wp = false;
  }
  prev_file_name = filename;

  if(GPS_failure && prev_GPS_failure == false){
    frozen_x = x;
    frozen_y = y;
    frozen_heading = heading;
  }
  if(GPS_failure){
    x = frozen_x;
    y = frozen_y;
    heading = frozen_heading;
  }
  prev_GPS_failure = GPS_failure;


  // const float itt_left  = *data.itt_left;
  // const float itt_right = *data.itt_right;

  // Draw the background box
  //hmi::Colour::PaletteColour(cn_background);
  glColor3f(0.49f, 0.61f, 0.15f);
  map_block.drawFill();





  glCallList(_gl_display_list_index);
  hmi::FontManager::Get(1)->SetSize(0.16,0.16);


  if(use_vor1)
  {
    hmi::Colour::PaletteColour(cn_foreground);
    GLSaveMatrix matrix_state;
    glTranslatef(map_width/2 - vor_width/2 + (vor1_x - x)*(rose_radius/(scale*1852)),
                 map_height/2 - vor_height/2 + (vor1_y - y)*(rose_radius/(scale*1852)),
                 0.0f);

    vor_box.drawOutline();
    {
      GLBegin lines(GL_LINES);
      glVertex2f(0,vor_height/2.0f);
      glVertex2f(vor_corner,vor_height);
      glVertex2f(vor_width-vor_corner,vor_height);
      glVertex2f(vor_width,vor_height/2.0f);
    }
    {
      GLBegin lines(GL_LINES);
      glVertex2f(vor_width,vor_height/2.0f);
      glVertex2f(vor_width-vor_corner,0);
      glVertex2f(vor_corner,0);
      glVertex2f(0,vor_height/2.0f);
    }
    {
      glTranslatef(vor_width/2.0f, vor_height/2.0f, 0.0f);
      GLLineWidth line_width(2.0f);
      glBegin(GL_LINE_STRIP);
      circlePoints( 1, deg2rad(0.0f), deg2rad(360.0f), 60 );
      glEnd();
      glTranslatef(-vor_width/2.0f, -vor_height/2.0f, 0.0f);
    }



  }
  if(use_vor2)
  {
    hmi::Colour::PaletteColour(cn_foreground);
    GLSaveMatrix matrix_state;
    glTranslatef(map_width/2 - vor_width/2 + (vor2_x - x)*(rose_radius/(scale*1852)),
                 map_height/2 - vor_height/2 + (vor2_y - y)*(rose_radius/(scale*1852)),
                 0.0f);

   vor_box.drawOutline();
   {
     GLBegin lines(GL_LINES);
     glVertex2f(0,vor_height/2.0f);
     glVertex2f(vor_corner,vor_height);
     glVertex2f(vor_width-vor_corner,vor_height);
     glVertex2f(vor_width,vor_height/2.0f);
   }
   {
     GLBegin lines(GL_LINES);
     glVertex2f(vor_width,vor_height/2.0f);
     glVertex2f(vor_width-vor_corner,0);
     glVertex2f(vor_corner,0);
     glVertex2f(0,vor_height/2.0f);
   }
   {
     glTranslatef(vor_width/2.0f, vor_height/2.0f, 0.0f);
     GLLineWidth line_width(2.0f);
     glBegin(GL_LINE_STRIP);
     circlePoints( 1, deg2rad(0.0f), deg2rad(360.0f), 60 );
     glEnd();
     glTranslatef(-vor_width/2.0f, -vor_height/2.0f, 0.0f);
   }
  }

  // Draw intersections
  if(filename.length()>0){
    for(int i=0;i<nr_of_wp;i++){
      GLSaveMatrix matrix_state;
      HMIText text(hmi::FontManager::Get(1));

      glTranslatef(map_width/2 - intersection_width/2 + (fp_location(i,0) - x)*(rose_radius/(scale*1852)),
                   map_height/2 - intersection_height/2 + (fp_location(i,1) - y)*(rose_radius/(scale*1852)),
                   0.0f);
       if (wp_names.at(i).length() == 5){
         {
           GLBegin triangle(GL_TRIANGLES);
           glVertex2f( 0.0f, 0.0f);
           glVertex2f( intersection_width, 0.0f);
           glVertex2f( intersection_width/2.0f, intersection_height);
         }
         text.clear().position(3.0f, intersection_height+1).bottom().left().size(0.14);
         text << wp_names.at(i);
         text.draw();
       } else if(wp_names.at(i).length() == 3){
         text.clear().position(3.0f, vor_height+1).bottom().left().size(0.14);
         text << wp_names.at(i);
         text.draw();
       }
    }
    for(int i=0;i<nr_of_map_items;i++){
      GLSaveMatrix matrix_state;
      HMIText text(hmi::FontManager::Get(1));

      glTranslatef(map_width/2 - intersection_width/2 + (map_items(i,0) - x)*(rose_radius/(scale*1852)),
                   map_height/2 - intersection_height/2 + (map_items(i,1) - y)*(rose_radius/(scale*1852)),
                   0.0f);
       if (item_names.at(i).length() == 5){
         {
           GLBegin triangle(GL_TRIANGLES);
           glVertex2f( 0.0f, 0.0f);
           glVertex2f( intersection_width, 0.0f);
           glVertex2f( intersection_width/2.0f, intersection_height);
         }
         text.clear().position(3.0f, intersection_height+1).bottom().left().size(0.14);
         text << item_names.at(i);
         text.draw();
       } else if(item_names.at(i).length() == 3){
         text.clear().position(3.0f, vor_height+1).bottom().left().size(0.14);
         text << item_names.at(i);
         text.draw();
       }
    }
  }


  ////////////////////////////////////////////////////////////////////////////
  // Draw Flight Plan
  ////////////////////////////////////////////////////////////////////////////
  if(nr_of_wp>0)
  {
    hmi::Colour::PaletteColour(cn_nav);
    GLSaveMatrix matrix_state;
    GLLineSmooth antialias;
    GLLineWidth line_width(2.0f);

    glTranslatef(map_width/2, map_height/2, 0.0f);
    // above here nothing is changed

    Eigen::MatrixXf fp_straight(nr_of_wp-1, 4);
    Eigen::MatrixXf fp_curved(nr_of_wp-2,4);

    fp_straight(0,0) = fp_location(0,0);
    fp_straight(0,1) = fp_location(0,1);
    fp_straight(nr_of_wp-2,2) = fp_location(nr_of_wp-1,0);
    fp_straight(nr_of_wp-2,3) = fp_location(nr_of_wp-1,1);

    Eigen::Vector2d A(0, 0);
    Eigen::Vector2d B(0, 0);
    Eigen::Vector2d C(0, 0);
    Eigen::Vector2d D(0, 0);
    Eigen::Vector2d E(0, 0);
    Eigen::Vector2d F(0, 0);

    float theta0,theta1;
    float r = Vtas*Vtas/(9.81*0.364);

    for(int i=0; i<nr_of_wp-2; i++){
      A = {fp_location(i,0), fp_location(i,1)};
      B = {fp_location(i+1,0), fp_location(i+1,1)};
      C = {fp_location(i+2,0), fp_location(i+2,1)};

      std::tie(E, F, D, theta0, theta1) = planIntersection(A, B, C, r);

      fp_straight(i,2) = E(0);
      fp_straight(i,3) = E(1);
      fp_straight(i+1,0) = F(0);
      fp_straight(i+1,1) = F(1);

      fp_curved(i,0) = D(0);
      fp_curved(i,1) = D(1);
      fp_curved(i,2) = theta0;
      fp_curved(i,3) = theta1;
    }

    for(int j=active_leg; j<fp_straight.rows(); j++){
      float start_x = fp_straight(j,0);
      float start_y = fp_straight(j,1);
      float end_x = fp_straight(j,2);
      float end_y = fp_straight(j,3);

      if(j==active_leg){
        hmi::Colour::PaletteColour(cn_nav);
      }else{
        hmi::Colour::PaletteColour(cn_foreground);
      }

      GLBegin lines(GL_LINES);
      glVertex2f((start_x-x)*(rose_radius/(scale*1852)), (start_y-y)*(rose_radius/(scale*1852)));
      glVertex2f((end_x-x)*(rose_radius/(scale*1852)), (end_y-y)*(rose_radius/(scale*1852)));
      hmi::Colour::PaletteColour(cn_nav);
    }

    for(int k=active_vnv_leg; k<fp_curved.rows(); k++){

      float center_x = fp_curved(k,0);
      float center_y = fp_curved(k,1);
      float theta0 = -fp_curved(k,2)+90;
      float theta1 = -fp_curved(k,3)+90;
      {
        GLSaveMatrix matrix_state;
        glTranslatef((center_x-x)*(rose_radius/(scale*1852)), (center_y-y)*(rose_radius/(scale*1852)),0.0f);
        if(k==active_leg){
          hmi::Colour::PaletteColour(cn_nav);
        }else{
          hmi::Colour::PaletteColour(cn_foreground);
        }
        {
          glBegin(GL_LINE_STRIP);
          circlePoints( r*(rose_radius/(scale*1852)), deg2rad(theta0), deg2rad(theta1), 60 );
          glEnd();
        }
      }

    }

    // below here nothing is changed but everything is commented
    // for(int wp_index=1; wp_index<nr_of_wp; wp_index++){
    //   int start_x = fp_location(wp_index-1,0);
    //   int start_y = fp_location(wp_index-1,1);
    //   int end_x = fp_location(wp_index,0);
    //   int end_y = fp_location(wp_index,1);
    //
    //   GLBegin lines(GL_LINES);
    //   glVertex2f((start_x-x)*(rose_radius/(scale*1852)), (start_y-y)*(rose_radius/(scale*1852)));
    //   glVertex2f((end_x-x)*(rose_radius/(scale*1852)), (end_y-y)*(rose_radius/(scale*1852)));
    // }
  }
  {
    if(filename.length()>0){
      for(int i=0;i<abs(nr_of_wp);i++){
        GLSaveMatrix matrix_state;
        GLLineSmooth antialias;
        glTranslatef(map_width/2 + (fp_location(i,0) - x)*(rose_radius/(scale*1852)),
                     map_height/2 + (fp_location(i,1) - y)*(rose_radius/(scale*1852)),
                     0.0f);
        if(wp_names.at(i).length() == 4){
          {
            hmi::Colour::PaletteColour(cn_nav);
            GLLineWidth line_width(11.5f);
            glBegin(GL_LINE_STRIP);
            circlePoints( 6, deg2rad(0.0f), deg2rad(360.0f), 60 );
            glEnd();
            GLBegin triangle(GL_TRIANGLES);
            glVertex2f( -8.0f, -8.0f);
            glVertex2f( 8.0f, -8.0f);
            glVertex2f( 0.0f, 8.0f);
          }
          {
            hmi::Colour::PaletteColour(cn_background);
            GLLineWidth line_width(2.0f);
            glBegin(GL_LINE_STRIP);
            circlePoints( 10, deg2rad(0.0f), deg2rad(360.0f), 60 );
            glEnd();
          }
          glTranslatef(-airport_box_width/2, 12.0f, 0.0f);
          airport_box.drawFill();
          hmi::Colour::PaletteColour(cn_foreground);
          airport_box.drawOutline();
          hmi::Colour::PaletteColour(cn_nav);
          text.clear().position(airport_box_width/2, airport_box_height/2).hcenter().vcenter().size(0.14);
          text << wp_names.at(i);
          text.draw();
        }
      }
      for(int i=0;i<abs(nr_of_map_items);i++){
        GLSaveMatrix matrix_state;
        GLLineSmooth antialias;
        glTranslatef(map_width/2 + (map_items(i,0) - x)*(rose_radius/(scale*1852)),
                     map_height/2 + (map_items(i,1) - y)*(rose_radius/(scale*1852)),
                     0.0f);
        if(item_names.at(i).length() == 4){
          {
            hmi::Colour::PaletteColour(cn_nav);
            GLLineWidth line_width(11.5f);
            glBegin(GL_LINE_STRIP);
            circlePoints( 6, deg2rad(0.0f), deg2rad(360.0f), 60 );
            glEnd();
            GLBegin triangle(GL_TRIANGLES);
            glVertex2f( -8.0f, -8.0f);
            glVertex2f( 8.0f, -8.0f);
            glVertex2f( 0.0f, 8.0f);
          }
          {
            hmi::Colour::PaletteColour(cn_background);
            GLLineWidth line_width(2.0f);
            glBegin(GL_LINE_STRIP);
            circlePoints( 10, deg2rad(0.0f), deg2rad(360.0f), 60 );
            glEnd();
          }
          glTranslatef(-airport_box_width/2, 12.0f, 0.0f);
          airport_box.drawFill();
          hmi::Colour::PaletteColour(cn_foreground);
          airport_box.drawOutline();
          hmi::Colour::PaletteColour(cn_nav);
          text.clear().position(airport_box_width/2, airport_box_height/2).hcenter().vcenter().size(0.14);
          text << item_names.at(i);
          text.draw();
        }
      }
    }
  }

  {
    hmi::Colour::PaletteColour(cn_foreground);
    GLSaveMatrix matrix_state;
    glTranslatef(map_width/2,map_height/2,0.0f);
    glRotatef(-heading,0.0f,0.0f,1.0f);
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
  }

  // hmi::Colour::PaletteColour(cn_outline);
  // map_block.drawOutline();

  hmi::Colour::PaletteColour(cn_background);
  scale_box.drawFill();
  hmi::Colour::PaletteColour(cn_foreground);
  scale_box.drawOutline();

  text.clear().padding(-5.0,5.0).bottom().right().size(0.14);
  text.position(572.0f-879.0f/2 + map_width/2, 472.0f );
  text << "NM";
  text.draw();

  text.clear().position(543.0f-879.0f/2 + map_width/2, 478.0f).bottom().right().size(0.15);
  text << std::fixed << std::setw(2) << std::setfill(' ') << scale;
  text.draw();

  hmi::FontManager::Get(1)->SetSize(0.16,0.16);
  hmi::FontManager::Get(1)->Print(map_width/2 - 5, map_height/2+rose_radius-24, "N");
  hmi::FontManager::Get(1)->Print(map_width/2 - 5, map_height/2-rose_radius+15, "S");
  hmi::FontManager::Get(1)->Print(map_width/2+rose_radius - 24,map_height/2 - 5, "E");
  hmi::FontManager::Get(1)->Print(map_width/2-rose_radius + 15,map_height/2 - 5, "W");

  //////////////////////////////////////////////////////////////////////////////
  // Draw Flight Plan page
  //////////////////////////////////////////////////////////////////////////////
  if(fpl_page){

    map_width = 439.0f;

    hmi::Colour::PaletteColour(cn_background);
    fppage_box.drawFill();
    hmi::Colour::PaletteColour(cn_outline);
    fpbox.drawOutline();


    GLSaveMatrix matrix_state;
    HMIText text(hmi::FontManager::Get(1));
    GLLineSmooth antialias;
    GLLineWidth line_width(2.0f);
    // Draw the top part of the Flight Plan box
    {
      GLBegin lines(GL_LINES);
      glVertex2f(fpboxLine_left, fpboxLine_bottom);
      glVertex2f(fpboxLine_left, fpboxLine_top);
    }
    {
      GLBegin lines(GL_LINES);
      glVertex2f(fpboxLine_left, fpboxLine_top);
      glVertex2f(fpboxLine_x1, fpboxLine_top);
    }
    {
      GLBegin lines(GL_LINES);
      glVertex2f(fpboxLine_x1, fpboxLine_top);
      glVertex2f(fpboxLine_x1, fpboxLine_y1);
    }
    {
      GLBegin lines(GL_LINES);
      glVertex2f(fpboxLine_x1, fpboxLine_y1);
      glVertex2f(fpboxLine_x2, fpboxLine_y1);
    }
    {
      GLBegin lines(GL_LINES);
      glVertex2f(fpboxLine_x2, fpboxLine_y1);
      glVertex2f(fpboxLine_x2, fpboxLine_top);
    }
    {
      GLBegin lines(GL_LINES);
      glVertex2f(fpboxLine_x2, fpboxLine_top);
      glVertex2f(fpboxLine_right, fpboxLine_top);
    }
    {
      GLBegin lines(GL_LINES);
      glVertex2f(fpboxLine_x2, fpboxLine_top);
      glVertex2f(fpboxLine_right, fpboxLine_top);
    }
    {
      GLBegin lines(GL_LINES);
      glVertex2f(fpboxLine_right, fpboxLine_top);
      glVertex2f(fpboxLine_right, fpboxLine_bottom);
    }
    // Draw the entire VNV box
    {
      GLBegin lines(GL_LINES);
      glVertex2f(vnvboxLine_left, vnvboxLine_bottom);
      glVertex2f(vnvboxLine_left, vnvboxLine_top);
    }
    {
      GLBegin lines(GL_LINES);
      glVertex2f(vnvboxLine_left, vnvboxLine_top);
      glVertex2f(vnvboxLine_x1, vnvboxLine_top);
    }
    {
      GLBegin lines(GL_LINES);
      glVertex2f(vnvboxLine_x1, vnvboxLine_top);
      glVertex2f(vnvboxLine_x1, vnvboxLine_y1);
    }
    {
      GLBegin lines(GL_LINES);
      glVertex2f(vnvboxLine_x1, vnvboxLine_y1);
      glVertex2f(vnvboxLine_x2, vnvboxLine_y1);
    }
    {
      GLBegin lines(GL_LINES);
      glVertex2f(vnvboxLine_x2, vnvboxLine_y1);
      glVertex2f(vnvboxLine_x2, vnvboxLine_top);
    }
    {
      GLBegin lines(GL_LINES);
      glVertex2f(vnvboxLine_x2, vnvboxLine_top);
      glVertex2f(vnvboxLine_right, vnvboxLine_top);
    }
    {
      GLBegin lines(GL_LINES);
      glVertex2f(vnvboxLine_x2, vnvboxLine_top);
      glVertex2f(vnvboxLine_right, vnvboxLine_top);
    }
    {
      GLBegin lines(GL_LINES);
      glVertex2f(vnvboxLine_right, vnvboxLine_top);
      glVertex2f(vnvboxLine_right, vnvboxLine_bottom);
    }
    {
      GLBegin lines(GL_LINES);
      glVertex2f(vnvboxLine_right, vnvboxLine_bottom);
      glVertex2f(vnvboxLine_left, vnvboxLine_bottom);
    }

    hmi::Colour::PaletteColour(cn_foreground);
    text.clear().position(fpboxLine_x1, fpboxLine_y1).padding(5.0,5.0).bottom().left().size(0.14);
    text << "ACTIVE FLIGHT PLAN";
    text.draw();

    text.clear().position(vnvboxLine_x1, vnvboxLine_y1).padding(5.0,5.0).bottom().left().size(0.14);
    text << "CURRENT VNV PROFILE";
    text.draw();

    text.clear().position(dtkcolumn_x, dtkcolumn_y).bottom().left().size(0.14);
    text << "DTK";
    text.draw();
    text.clear().position(discolumn_x, discolumn_y).bottom().left().size(0.14);
    text << "DIS";
    text.draw();
    text.clear().position(altcolumn_x, altcolumn_y).bottom().left().size(0.14);
    text << "ALT";
    text.draw();

    text.clear().position(vnvboxLine_left+5.0f, vnvboxLine_top-30.0f).bottom().left().size(0.14);
    text << "ACTIVE VNV WPT";
    text.draw();
    text.clear().position(vnvboxLine_left+5.0f, vnvboxLine_top-30.0f-30.0f).bottom().left().size(0.14);
    text << "VS TGT";
    text.draw();
    text.clear().position(vnvboxLine_left+5.0f, vnvboxLine_top-30.0f-60.0f).bottom().left().size(0.14);
    text << "VS REQ";
    text.draw();
    text.clear().position(vnvboxLine_left+5.0f, vnvboxLine_top-30.0f-90.0f).bottom().left().size(0.14);
    text << "V DEV";
    text.draw();

    text.clear().position(vnvboxLine_x2+20.0f, vnvboxLine_top-30.0f-30.0f).bottom().left().size(0.14);
    text << "FPA";
    text.draw();


    

    if(curVerticalState == 4 && alt_v != -1){
      hmi::Colour::PaletteColour(cn_active);
      text.clear().position(vnvboxLine_left+140.0f, vnvboxLine_top-30.0f-30.0f).bottom().right().size(0.18);
      text << std::fixed << std::setprecision(0) << sin(deg2rad(-2.5f))*Vtas_demped*196.9f;
      text.draw();

      text.clear().position(vnvboxLine_left+145.0f, vnvboxLine_top-30.0f-30.0f).bottom().left().size(0.14);
      text << "FPM";
      text.draw();

      if((time_to_top<60 && !is_vnav_descending) || is_vnav_descending){
        text.clear().position(vnvboxLine_left+140.0f, vnvboxLine_top-30.0f-60.0f).bottom().right().size(0.18);
        text << std::fixed << std::setprecision(0) << -sin(fpa_req)*Vtas_demped*196.9f;
        text.draw();

        text.clear().position(vnvboxLine_left+140.0f, vnvboxLine_top-30.0f-90.0f).bottom().right().size(0.18);
        text << std::fixed << std::setprecision(0) << (alt_v-altitude/.3041);
        text.draw();

        text.clear().position(vnvboxLine_left+145.0f, vnvboxLine_top-30.0f-60.0f).bottom().left().size(0.14);
        text << "FPM";
        text.draw();

        text.clear().position(vnvboxLine_left+145.0f, vnvboxLine_top-30.0f-90.0f).bottom().left().size(0.14);
        text << "FT";
        text.draw();
      }


      hmi::Colour::PaletteColour(cn_foreground);
      switch(is_vnav_descending){
        case 0:
          text.clear().position(vnvboxLine_x2+20.0f, vnvboxLine_top-30.0f-60.0f).bottom().left().size(0.14);
          text << "TIME TO TOD";
          text.draw();

          if(time_to_top<0){
            is_vnav_descending = 1;
            hmi::Colour::PaletteColour(cn_active);
            text.clear().position(vnvboxLine_x2+150.0f, vnvboxLine_top-30.0f-60.0f).bottom().left().size(0.18);
            text << "0:00";
            text.draw();
          }else{
            hmi::Colour::PaletteColour(cn_active);
            text.clear().position(vnvboxLine_x2+150.0f, vnvboxLine_top-30.0f-60.0f).bottom().left().size(0.18);
            text << floor(time_to_top/60) << ":" << std::fixed << std::setw(2) << std::setfill('0') << (int)time_to_top%60;
            text.draw();
          }
        break;

        case 1:
          text.clear().position(vnvboxLine_x2+20.0f, vnvboxLine_top-30.0f-60.0f).bottom().left().size(0.14);
          text << "TIME TO BOD";
          text.draw();

          if(time_to_top>0){
            is_vnav_descending = 0;
            hmi::Colour::PaletteColour(cn_active);
            text.clear().position(vnvboxLine_x2+150.0f, vnvboxLine_top-30.0f-60.0f).bottom().left().size(0.18);
            text << "0:00";
            text.draw();
          }else{
            hmi::Colour::PaletteColour(cn_active);
            text.clear().position(vnvboxLine_x2+150.0f, vnvboxLine_top-30.0f-60.0f).bottom().left().size(0.18);
            text << floor(time_to_bod/60) << ":" << std::fixed << std::setw(2) << std::setfill('0') << (int)time_to_bod%60;
            text.draw();
          }
        break;
      }
    }else{
      text.clear().position(vnvboxLine_x2+20.0f, vnvboxLine_top-30.0f-60.0f).bottom().left().size(0.14);
      text << "TIME TO BOD";
      text.draw();
    }

    if(nr_of_wp>0 && active_vnv_leg+1<nr_of_wp){
      alt_v = fp_location(active_vnv_leg+1,2);
      iter_wps = 1;
      while(alt_v == -1 && active_vnv_leg+1+iter_wps<nr_of_wp){
        alt_v = fp_location(active_vnv_leg+1+iter_wps,2);
        iter_wps += 1;
      }
      if(curVerticalState == 4 && alt_v != -1){
        hmi::Colour::PaletteColour(cn_active);
        text.clear().position(vnvboxLine_x2-25.0f, vnvboxLine_top-32.0f).bottom().left().size(0.18);
        text << std::fixed << std::setprecision(0) << alt_v;
        text.draw();

        text.clear().position(vnvboxLine_x2+20.0f, vnvboxLine_top-32.0f).bottom().left().size(0.14);
        text << "FT at";
        text.draw();

        text.clear().position(vnvboxLine_x2+75.0f, vnvboxLine_top-32.0f).bottom().left().size(0.18);
        text << wp_names.at(active_vnv_leg+iter_wps);
        text.draw();

        text.clear().position(vnvboxLine_x2+150.0f, vnvboxLine_top-30.0f-30.0f).bottom().left().size(0.18);
        text << "-2.5";
        text.draw();
      }

      {
        hmi::Colour::PaletteColour(cn_nav);
        GLLineSmooth antialias;
        GLLineWidth line_width(2.0f);
        {
          GLBegin lines(GL_LINES);
          glVertex2f(fpbox_left+35, fpbox_top-26.0f-35.0f*active_leg);
          glVertex2f(fpbox_left+20, fpbox_top-26.0f-35.0f*active_leg);
        }
        {
          GLBegin lines(GL_LINES);
          glVertex2f(fpbox_left+20, fpbox_top-26.0f-35.0f*active_leg);
          glVertex2f(fpbox_left+20, fpbox_top-26.0f-35.0f*active_leg-35.0f);
        }
        {
          GLBegin lines(GL_LINES);
          glVertex2f(fpbox_left+20, fpbox_top-26.0f-35.0f*active_leg-35.0f);
          glVertex2f(fpbox_left+35, fpbox_top-26.0f-35.0f*active_leg-35.0f);
        }
        {
          GLBegin lines(GL_LINES);
          glVertex2f(fpbox_left+30, fpbox_top-21.0f-35.0f*active_leg-35.0f);
          glVertex2f(fpbox_left+35, fpbox_top-26.0f-35.0f*active_leg-35.0f);
        }
        {
          GLBegin lines(GL_LINES);
          glVertex2f(fpbox_left+30, fpbox_top-31.0f-35.0f*active_leg-35.0f);
          glVertex2f(fpbox_left+35, fpbox_top-26.0f-35.0f*active_leg-35.0f);
        }
      }

      hmi::Colour::PaletteColour(cn_active);
      for(int i; i<nr_of_wp; i++){
        if(wp_names.at(i) != "D"){
          text.clear().position(fpbox_left+45.0f, fpbox_top-20.0f-35.0f*i).top().left().size(0.18);
          text << wp_names.at(i);
          text.draw();
        }

        if(i>0){
          text.clear().position(dtkcolumn_x-10.0f, fpbox_top-20.0f-35.0f*i).top().left().size(0.18);
          text << std::fixed << std::setprecision(0) << std::setw(3) << std::setfill('0') << fp_location(i,3);
          text.draw();
          text.clear().position(dtkcolumn_x+23.0f, fpbox_top-18.0f-35.0f*i).top().left().size(0.12);
          text << "o";
          text.draw();

          text.clear().position(discolumn_x+30.0f, fpbox_top-20.0f-35.0f*i).top().right().size(0.18);
          text << std::fixed << std::setprecision(1) << fp_location(i,4) <<"NM";
          text.draw();

          if(fp_location(i,2) != -1){
            text.clear().position(altcolumn_x+35.0f, fpbox_top-20.0f-35.0f*i).top().right().size(0.18);
            text << std::fixed << std::setprecision(0) << fp_location(i,2) <<"FT";
            text.draw();
          }else{
            text.clear().position(altcolumn_x+35.0f, fpbox_top-20.0f-35.0f*i).top().right().size(0.18);
            text << "____FT";
            text.draw();
          }
        }
      }
    }




  }

}


namespace
{}
