
//-----------------------------------------------------------------------------
//
// PFD_B747.cxx
//
// Copyright (C) 2000:  Delft University of Technology,
//			Fac. Aerospace Engineering,
//			Control & Simulation
//
// Description:This class draws an OpenGL B747-400 Primary Flight Display
//
// Created: by Z.C. Roza on 29-6-2002
// Updated: by <name> on <date>
//
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Include files
//------------------------------------------------------------------------------
#include "PFD_B747.h"
#include <cmath>
#include <stdio.h>
#include <iostream>
#include <algorithm>

using namespace std;

#define MS2KTS 1.94384449

//------------------------------------------------------------------------------
// Default Constructors
//------------------------------------------------------------------------------
PFD_B747::PFD_B747():WglClientAreaUser("PFD", false),
    _spd(false), _flch(false), _hdg(false), _vspd(false),
    _alt(false),_apMode(ALT),
    _spdBugOn(false), _altBugOn(false),
    _selectedVertSpd(0.0f),_selectedTas(0.0f), _selectedAlt(0.f),
    currentMach(0), trueAirspeed(0), currentAlt(0), currentRC(0),
    _selectedFlapAngle(0), _landingFlapAngle(25),_ILS_DME(0.0),
    _Vref(0.0f), _Vstall(0.0f), _Vplackard(0.0f), _Vmaneuver(0.0f), _V1(0.0f), _V2(0.0f), _FAS(0.0f),
    _altOffset(0), _curTimeSec(0.0), _speedsSet(0),
    _2dobjectroot(NULL)
{
}

PFD_B747::PFD_B747(const char *window_title, bool mouse_passive):
    WglClientAreaUser(window_title, mouse_passive),
    _spd(false), _flch(false), _hdg(false), _vspd(false),
    _alt(false),_apMode(ALT),
    _spdBugOn(false), _altBugOn(false),
    _selectedVertSpd(0.0f),_selectedTas(0.0f), _selectedAlt(0.f),
    currentMach(0), trueAirspeed(0), currentAlt(0), currentRC(0),
    _selectedFlapAngle(0), _landingFlapAngle(25),_ILS_DME(0.0),
    _Vref(0.0f), _Vstall(0.0f), _Vplackard(0.0f), _Vmaneuver(0.0f), _V1(0.0f), _V2(0.0f), _FAS(0.0f),
    _altOffset(0), _curTimeSec(0.0), _speedsSet(0),
    _2dobjectroot(NULL)
{
}

//------------------------------------------------------------------------------
// Destructor
//------------------------------------------------------------------------------
PFD_B747::~PFD_B747()
{

}

//------------------------------------------------------------------------------
// initialiseScene
//
// This function intialises the client area user by doing some setup rendering.
//------------------------------------------------------------------------------
void PFD_B747::initGL()
{
  glClearColor (0.0, 0.0, 0.0, 0.0);

  // clear display
  glClear(GL_COLOR_BUFFER_BIT);

  //	set Shade mode
  glShadeModel(GL_SMOOTH);

  // matrix mode
  glMatrixMode(GL_MODELVIEW);

  // call setup() for 2D object tree
  _2dobjectroot->setup();
}

//------------------------------------------------------------------------------
// renderScene
//
// This function renders the actual OpenGL scene
//------------------------------------------------------------------------------
void PFD_B747::display()
{
  glClear (GL_COLOR_BUFFER_BIT);

  glPushMatrix();
    // detemine the shortest side of the display window for scaling
    float min_size = 0.0;
    if( WglClientAreaUser::window_width > WglClientAreaUser::window_height )
      min_size = WglClientAreaUser::window_height;
    else
      min_size = WglClientAreaUser::window_width;

    // move display to the middle horizontally and to the top vertically
    float width_offset = 0.5*( WglClientAreaUser::window_width - min_size )+15.0f;
    float height_offset = WglClientAreaUser::window_height - min_size + 30.0f;
    glTranslatef( width_offset , height_offset, 0.0 );

    // scale the display to fit the window
    glScalef( min_size/155.0, min_size/150.0, 1.0);

    // draw the display
    glPushMatrix();
      renderPFD();
    glPopMatrix();
  glPopMatrix();

  swapBuffers();
}

void PFD_B747::renderPFD()
{
  // [OS] anti-alias everything
  glEnable(GL_LINE_SMOOTH);

  // call display() for each 2D object in the object tree
  _2dobjectroot->display();
  //--------------------------------------------------------------------------
  // Draw Speed and Altitude indicator

  // [OS] scale both
  glPushMatrix();
  glScalef(1.0, 0.85, 1.0);

  // Draw Altitude and Speed Tape Background
  //glColor3f(0.0f,0.1875f,0.3125f);
  glColor3f(0.4,0.4,0.4);
  glRectf(115.0f,27.5f,133.0f, 127.5f);
  glRectf(8.0f,27.5f,23.0f, 127.5f);

  // Draw Altitude and Speed Tape Ground Background
  if((currentAlt + _altOffset) <= 512.0f)
  {
    glColor3f(0.9f,0.6f,0.0f);
    glRectf(115.0f,27.5f,133.0f, 28.5f + (512.0f - currentAlt + _altOffset) * 0.09615384f);
  }

  if(trueAirspeed <= 70.0f)
  {
    glColor3f(0.9f,0.6f,0.0f);
    glRectf(8.0f,27.5f,23.0f, 27.5f + (70.0f - trueAirspeed) * 0.7142857f);
  }

  // Draw Altitude and Speed Tapes
  double clip_top[4] = {0.0, -1.0, 0.0, 127.5};
  double clip_bottom[4] = {0.0, 1.0, 0.0, -27.5};
  glClipPlane(GL_CLIP_PLANE0, clip_top);
  glEnable(GL_CLIP_PLANE0);
  glClipPlane(GL_CLIP_PLANE1, clip_bottom);
  glEnable(GL_CLIP_PLANE1);


  // Draw speed and altitude bugs
  double deltaSpd = _selectedTas - trueAirspeed;
// extra variabele voor bar
  double deltaSpd2 = (_V1 - trueAirspeed) * 0.7142857f;
  double deltaAlt = _selectedAlt - currentAlt;

  if(deltaSpd < -70.0f) deltaSpd = -70.0f * 0.7142857f;
  else if(deltaSpd <70.0f) deltaSpd = deltaSpd * 0.7142857f;
  else deltaSpd = 70.0f * 0.7142857f;

  if(deltaAlt < -520.0f) deltaAlt = -52.0f * 0.9615384f;
  else if(deltaAlt <520.0f) deltaAlt = deltaAlt * 0.09615384f;
  else deltaAlt = 52.0f * 0.9615384f;

  glColor3f(1.0f,0.5f,0.0f);

    // Draw Altitude Scale and Numbers
  int		timeHun = (int)((currentAlt + _altOffset) / 100.0f);
  int		time5Hun= (int)((currentAlt + _altOffset)/ 500.0f);
  int		time2Hun= (int)((currentAlt + _altOffset)/ 200.0f);
  //int		time10Hun= (int)((currentAlt + _altOffset) / 1000.0f);
  double	rest1 = (currentAlt + _altOffset - (100.0f * timeHun))/100.0f;
  double	rest2 = (currentAlt + _altOffset - (500.0f * time5Hun))/500.0f;
  double	rest3 = (currentAlt + _altOffset - (200.0f * time2Hun))/200.0f;

  double dummy; //, dummy2;

  glColor3f(1.0f,1.0f,1.0f);
  glBegin(GL_LINES);
    for(int i=-8; i<9;i++)
    {
      dummy = (i - rest1) * 9.615384f;
      glVertex2f(115.0f,77.5 + dummy);
      glVertex2f(117.5f,77.5 + dummy);
    }
  glEnd();

  int value1, value2;
  for(int i=-3; i<5;i++)
  {
    dummy = (i - rest3) * 19.230769f;
    value1 = (int)(200.0f * (time2Hun + i))/1000;
    snprintf(_textString,255, "%2d", value1);
    strokeString(119.0f,76.0 + dummy,_textString,GLUT_STROKE_ROMAN, 0.035);

    value2 = (int)(200.0f * (time2Hun + i)) - 1000 * value1;
    if(value2 >=0)
    {
      snprintf(_textString,255, "%03d", value2);
    }
    else
    {
      snprintf(_textString,255, "%03d", abs(value2));
    }
    strokeString(125.5f,76.0f + dummy,_textString,GLUT_STROKE_ROMAN, 0.025);
  }

  // Draw Speed Scale and Numbers
  timeHun	= (int)(trueAirspeed / 10.0f);
  time5Hun= (int)(trueAirspeed / 20.0f);
  rest1	= (trueAirspeed - (10.0f * timeHun))/10.0f;
  rest2	= (trueAirspeed - (20.0f * time5Hun))/20.0f;

  glBegin(GL_LINES);
    for(int i=-8; i<9;i++)
    {
      dummy = (i - rest1) * 7.142857f;
      glVertex2f(23.0f,77.5 + dummy);
      glVertex2f(20.5f,77.5 + dummy);
    }
  glEnd();

  for(int i=-3; i<5;i++)
  {
    dummy = (i - rest2) * 14.285714f;
    snprintf(_textString,255, "%3d", (int)(20.0f * (time5Hun + i)));
    strokeString(11.0f,76.0 + dummy,_textString,GLUT_STROKE_ROMAN, 0.030);
  }

  renderSpeedLimits();


  glDisable(GL_CLIP_PLANE0);
  glDisable(GL_CLIP_PLANE1);

  // Draw speed and altitude indicator background
  glColor3f(0.0,0.0,0.0);
  glBegin(GL_TRIANGLES);
    glVertex2f(121.0f, 74.9f);
    glVertex2f(117.0f, 77.5f);
    glVertex2f(121.0f, 80.2f);

    glVertex2f(18.0f, 75.0f);
    glVertex2f(21.5f, 77.5f);
    glVertex2f(18.0f, 80.0f);
  glEnd();

  glRectf(7.0f,72.5f,18.0f,82.5f);
  glRectf(120.6f,72.5f,136.0f,82.5f);

  // Draw speed and altitude indicator outline
  glColor3f(1.0,1.0,1.0);
  glBegin(GL_LINE_LOOP);
    glVertex2f(136.0f, 72.5f);
    glVertex2f(120.5f, 72.5f);
    glVertex2f(120.5f, 75.0f);
    glVertex2f(117.0f, 77.5f);
    glVertex2f(120.5f, 80.0f);
    glVertex2f(120.5f, 82.5f);
    glVertex2f(136.0f, 82.5f);
  glEnd();

  glBegin(GL_LINE_LOOP);
    glVertex2f(7.0f,  72.5f);
    glVertex2f(18.0f, 72.5f);
    glVertex2f(18.0f, 75.0f);
    glVertex2f(21.5f, 77.5f);
    glVertex2f(18.0f, 80.0f);
    glVertex2f(18.0f, 82.5f);
    glVertex2f(7.0f,  82.5f);
  glEnd();

  // Draw textual values
  // glColor3f(1.0f,1.0f,1.0f);
  // snprintf(_textString,255, "%0.3f", (float)currentMach);
  // strokeString(10.0f,20.5f,_textString,GLUT_STROKE_ROMAN, 0.035);

  if((trueAirspeed - (int)trueAirspeed) >= 0.5)
    snprintf(_textString,255, "%03d", (int)trueAirspeed + 1);
  else	snprintf(_textString,255, "%03d", (int)trueAirspeed);
  strokeString(8.0f,76.0f,_textString,GLUT_STROKE_ROMAN, 0.035);

  // Render Altitude
  int curAlt, thousend, hund, tens;
  //if((currentAlt - (int)currentAlt) >= 0.05)
  //  curAlt = (int) (currentAlt + _altOffset -1);
  //else
  //  curAlt = (int) (currentAlt + _altOffset);
  // bug: 14999 should become 15000
  // 14995 should become 15000
  // 14990 should become 15000
  // 14989 should become 14980
  // 14985 should become 14980
  // 14981 should become 14980, so add 10
  double curAlt2 = currentAlt + 10.0;
  if ((curAlt2 - (int)curAlt2) >= 0.05)
    curAlt = (int) (curAlt2 + _altOffset -1);
  else
    curAlt = (int) (curAlt2 + _altOffset);

  thousend = (curAlt / 1000);
  snprintf(_textString,255, "%02d", thousend );
  strokeString(122.0f,76.0f,_textString,GLUT_STROKE_ROMAN, 0.035);
  hund = (curAlt - thousend * 1000)/100;
  snprintf(_textString,255, "%01d", hund);
  strokeString(128.0f,76.0f,_textString,GLUT_STROKE_ROMAN, 0.029);
  tens = (curAlt - thousend * 1000 - hund * 100)/20;
  snprintf(_textString,255, "%02d", tens * 20);
  strokeString(130.0f,76.0f,_textString,GLUT_STROKE_ROMAN, 0.029);

  if (_spdBugOn)
  {
    if (_selectedTas>0){
    glColor3f(1.0f,0.0f,1.0f);
    snprintf(_textString,255, "%03d", (int)_selectedTas);
    strokeString(12.0f,130.5f,_textString,GLUT_STROKE_ROMAN, 0.035);
    }
    else{
      glColor3f(1.0f,0.0f,1.0f);
      strokeString(12.0f,130.5f,"XXX",GLUT_STROKE_ROMAN, 0.035);
    }
  }

  if (_altBugOn)
  {
    snprintf(_textString,255, "%05d", (int)_selectedAlt + _altOffset);
    strokeString(118.0f,130.5f,_textString,GLUT_STROKE_ROMAN, 0.035);
  }

  glColor3f(0.0f,0.85f,0.0f);
  strokeString(118.0f,19.5f,"29.92in",GLUT_STROKE_ROMAN, 0.034);

  // ILS data
  /*** Show no ILS data
  glColor3f(1.0f,1.0f,1.0f);
  strokeString(30.0f,124.0f,"KAG",GLUT_STROKE_ROMAN, 0.034);
  snprintf(_textString, 255, "DME %.1f", _ILS_DME);
  strokeString(30.0f,119.0f,_textString,GLUT_STROKE_ROMAN, 0.034);
  strokeString(30.0f,30.0f,"CRS 059",GLUT_STROKE_ROMAN, 0.034);
  ***/


  //--------------------------------------------------------------------------
  // Draw Flap Cues
  //renderFlapCues();

  // render speed trendvector
  //enderSpeedTrend();

  //--------------------------------------------------------------------------
  // Draw Vertical Speed indicator

  // Draw current rate of climb in textual format
  // glColor3f(1.0f,1.0f,1.0f);
  // if(currentRC > 400.0)
  // {
  //   snprintf(_textString,255, "%04d", (int) abs(currentRC));
  //   strokeString(134.5f,120.0f,_textString, GLUT_STROKE_ROMAN, 0.031);
  // }
  // else if(currentRC < -400.0)
  // {
  //   snprintf(_textString,255, "%04d", (int) abs(currentRC));
  //   strokeString(134.5f,31.5f,_textString, GLUT_STROKE_ROMAN, 0.031);
  // }
  //
  // // Vertical Speed Indicator Background
  // //glColor3f(0.0f,0.1875f,0.3125f);
  // glColor3f(0.4f,0.4f,0.4f);
  // glBegin(GL_TRIANGLE_STRIP);
  //   glVertex2f(135.0f,37.5f);	//1
  //   glVertex2f(142.0f,37.5f);	//2
  //   glVertex2f(135.0f,66.5f);	//3
  //   glVertex2f(147.0f,57.5f);	//4
  //   glVertex2f(137.0f,71.5f);	//5
  //   glVertex2f(147.0f,97.5f);	//6
  //   glVertex2f(137.0f,83.5f);	//7
  //   glVertex2f(142.0f,117.5f);	//8
  //   glVertex2f(135.0f,88.5f);	//9
  //   glVertex2f(135.0f,117.5f);	//10
  // glEnd();
  //
  // glColor3f(1.0f,1.0f,1.0f);
  // glBegin(GL_LINES);
  //   double interval = 76.0/12.0;
  //   for(int j=0; j<13; j++)
  //   {
  //     glVertex2f(139.0f,39.5f + interval * j);
  //     glVertex2f(141.0f,39.5f + interval * j);
  //   }
  //
  //   glVertex2f(141.0f,77.5f);
  //   glVertex2f(143.0f,77.5f);
  // glEnd();
  //
  // strokeString(136.0f,113.5f,"6", GLUT_STROKE_ROMAN, 0.025);
  // strokeString(136.0f,100.1f,"2", GLUT_STROKE_ROMAN, 0.025);
  // strokeString(136.0f,87.83f,"1", GLUT_STROKE_ROMAN, 0.025);
  // strokeString(136.0f,64.50f,"1", GLUT_STROKE_ROMAN, 0.025);
  // strokeString(136.0f,52.16f,"2", GLUT_STROKE_ROMAN, 0.025);
  // strokeString(136.0f,39.5f, "6", GLUT_STROKE_ROMAN, 0.025);
  //
  // // Draw current rate of climb needle
  // double clip_right[4] = {-1.0, 0.0, 0.0,146.2f };
  // glColor3f(1.0f,1.0f,1.0f);
  // glLineWidth(2.0f);
  // glClipPlane(GL_CLIP_PLANE3, clip_right);
  // glEnable(GL_CLIP_PLANE3);
  //   glBegin(GL_LINES);
  //     glVertex2f(150.0f,77.5f);
  //     if(currentRC <= 2000.0f && currentRC >= -2000.0f)
  //     {
  //       glVertex2f(139.0f,(77.5 + currentRC * 1.2666666e-2));
  //     }
  //     else
  //     {	if(currentRC > 0.0)
  //       {
  //         if(currentRC > 6000.0f) currentRC = 6000.0f;
  //         glVertex2f(139.0f,(96.5 + currentRC * 3.1666666e-3));
  //       }
  //       else
  //       {
  //         if(currentRC < -6000.0f) currentRC = -6000.0f;
  //         glVertex2f(139.0f,(58.5 + currentRC * 3.1666666e-3));
  //       }
  //     }
  //   glEnd();
  // glDisable(GL_CLIP_PLANE3);
  // glLineWidth(1.0f);
  //
  // // Draw climb rate bug
  // if(_apMode == PFD_B747::VS)
  // {
  //   glColor3f(1.0f,0.0f,1.0f);
  //   glBegin(GL_LINE_LOOP);
  //   if(_selectedVertSpd <= 2000.0f && _selectedVertSpd >= -2000.0f)
  //   {
  //     glVertex2f(139.0f,(78.5 + _selectedVertSpd * 1.2666666e-2));
  //     glVertex2f(139.0f,(76.5 + _selectedVertSpd * 1.2666666e-2));
  //     glVertex2f(142.0f,(76.5 + _selectedVertSpd * 1.2666666e-2));
  //     glVertex2f(142.0f,(78.5 + _selectedVertSpd * 1.2666666e-2));
  //   }
  //   else
  //   {	if(_selectedVertSpd > 0.0)
  //     {
  //       if(_selectedVertSpd > 6000.0f)
  //       {
  //         glVertex2f(139.0f,116.5);
  //         glVertex2f(139.0f,114.5);
  //         glVertex2f(142.0f,114.5);
  //         glVertex2f(142.0f,116.5);
  //       }
  //       else
  //       {
  //         glVertex2f(139.0f,(97.5 + _selectedVertSpd * 3.1666666e-3));
  //         glVertex2f(139.0f,(95.5 + _selectedVertSpd * 3.1666666e-3));
  //         glVertex2f(142.0f,(95.5 + _selectedVertSpd * 3.1666666e-3));
  //         glVertex2f(142.0f,(97.5 + _selectedVertSpd * 3.1666666e-3));
  //       }
  //     }
  //     else
  //     {
  //       if(_selectedVertSpd < -6000.0f)
  //       {
  //         glVertex2f(139.0f,40.5);
  //         glVertex2f(139.0f,38.5);
  //         glVertex2f(142.0f,38.5);
  //         glVertex2f(142.0f,40.5);
  //       }
  //       else
  //       {
  //         glVertex2f(139.0f,(59.5 + _selectedVertSpd * 3.1666666e-3));
  //         glVertex2f(139.0f,(57.5 + _selectedVertSpd * 3.1666666e-3));
  //         glVertex2f(142.0f,(57.5 + _selectedVertSpd * 3.1666666e-3));
  //         glVertex2f(142.0f,(59.5 + _selectedVertSpd * 3.1666666e-3));
  //       }
  //     }
  //   }
  //   glEnd();
  // }

  // [OS] scale
  glPopMatrix();
}

//-----------------------------------------------------------------------------
// render speed trend vector
//-----------------------------------------------------------------------------

void PFD_B747::renderSpeedTrend()
{
  static double V_old = 0.0;
  static double t_old = 0.0;
  static double dt = 0.0;
  static double length = 0.0;
  double a, dV;



  dt +=  (_curTimeSec - t_old);

  if (_curTimeSec < 1.0){
    dt = 0.0;
    t_old = 0.0;
  }

  if ( dt > .1){
    dV = trueAirspeed - V_old;
    a = dV / dt;



    length = 10 * a * 0.7142857f;

    // limit length of trend vector
    if (length>46) {length=46;}
    if (length<-46) {length=-46;}

    V_old = trueAirspeed;
    dt = 0.0;
  }

  t_old = _curTimeSec;

  // draw the trend vector
  if (fabs(length) > 4.0){
    glColor3f(0.0f, 0.85f, 0.0f); // Green
    glBegin(GL_LINES);
       glVertex2f(21.0f, 77.5f );
       glVertex2f(21.0f, 77.5f + length);
    glEnd();
  }

  // draw the triangle
  if (length > 4.0){
    glBegin(GL_POLYGON);
      glVertex2f(20.0f , 74.5f + length);
      glVertex2f(22.0f , 74.5f + length);
      glVertex2f(21.0f , 77.5f + length);
    glEnd();
  }

  if (length < -4.0){
    glBegin(GL_POLYGON);
       glVertex2f(20.0f , 80.5f + length);
       glVertex2f(22.0f , 80.5f + length);
       glVertex2f(21.0f , 77.5f + length);
    glEnd();
  }
}


//-----------------------------------------------------------------------------
// render Maximum/minimum speed
//-----------------------------------------------------------------------------

void PFD_B747::renderSpeedLimits()
{
  //Only draw these limits when in flight, so IAS > 25 kts
  if (trueAirspeed < 25.0f) {
    return;
  }

  // Draw MaxSpeed Barberpole ===================================================
  float deltaSpd = (_Vplackard - trueAirspeed)* 0.7142857f;
  glColor3f(1.0f, 0.0f, 0.0f); //red
  glLineWidth(1.5f);
  for (int ii = 0; deltaSpd + (float)ii < 52.0f; ii += 6){
    glBegin(GL_LINE_STRIP);
       glVertex2f(23.0f, 77.5f + deltaSpd + (float)ii);
       glVertex2f(25.0f, 77.5f + deltaSpd + (float)ii);
       glVertex2f(25.0f, 79.5f + deltaSpd + (float)ii);
       glVertex2f(23.0f, 79.5f + deltaSpd + (float)ii);
       glVertex2f(23.0f, 77.5f + deltaSpd + (float)ii);
    glEnd();
 }


  // Draw Stallspeed Barberpole and MinManSpeed =================================
  deltaSpd = (_Vstall - trueAirspeed)* 0.7142857f;


  glColor3f(1.0f, 1.0f, 0.0f); //yellow
  glBegin(GL_LINE_STRIP);
     glVertex2f(23.0f, 77.5f + deltaSpd +5);
     glVertex2f(25.0f, 77.5f + deltaSpd +5);
     glVertex2f(25.0f, 77.5f + deltaSpd);
  glEnd();

  glColor3f(1.0f, 0.0f, 0.0f); //red

  for (int ii = 0; deltaSpd - (float)ii > -52.0f; ii += 6){
    glBegin(GL_LINE_STRIP);
       glVertex2f(23.0f, 77.5f + deltaSpd - (float)ii);
       glVertex2f(25.0f, 77.5f + deltaSpd - (float)ii);
       glVertex2f(25.0f, 75.5f + deltaSpd - (float)ii);
       glVertex2f(23.0f, 75.5f + deltaSpd - (float)ii);
       glVertex2f(23.0f, 77.5f + deltaSpd - (float)ii);
    glEnd();
  }

  // Draw Min Flap Maneuver Speed for flaps < 30 ================================
  // if (_Vmaneuver > _Vref+0.1) {
  //   deltaSpd = (_Vmaneuver - trueAirspeed)* 0.7142857f;
  //
  //   glColor3f(0.0f, 0.85f, 0.0f); // Green
  //   glBegin(GL_LINES);
  //      glVertex2f(23.0f, 77.5f + deltaSpd);
  //      glVertex2f(25.0f, 77.5f + deltaSpd);
  //   glEnd();
  //   if (_selectedFlapAngle == 0) {
  //     strokeString(25.5f, 76.5f+deltaSpd, "UP", GLUT_STROKE_ROMAN, 0.025);
  //   } else {
  //     snprintf(_textString,255,"%i", _selectedFlapAngle);
  //     strokeString(25.5f, 76.5f+deltaSpd, _textString, GLUT_STROKE_ROMAN, 0.025);
  //   }
  // }

  // Draw V_ref =================================================================
  // deltaSpd = (_Vref - trueAirspeed)* 0.7142857f;
  // glColor3f(0.0f, 0.85f, 0.0f); // Green
  // glBegin(GL_LINES);
  //    glVertex2f(23.0f, 77.5f + deltaSpd);
  //    glVertex2f(25.0f, 77.5f + deltaSpd);
  // glEnd();
  // strokeString(25.5f, 76.5f + deltaSpd,"REF", GLUT_STROKE_ROMAN, 0.020);
  // glLineWidth(1.0f);
}

//------------------------------------------------------------------------------
// Modifier Methods
//------------------------------------------------------------------------------

void PFD_B747::selectedVertSpeed(float Vspd)
{
	_selectedVertSpd = Vspd; //	* 196.850;		// [ft/min]

}

void PFD_B747::selectedTas(float Tas)
{
	// this piece of code works with Tas which actually contains Ias
	_selectedTas = Tas;
}

void PFD_B747::selectedAlt(float Alt)
{
	_selectedAlt = Alt;
}

void PFD_B747::set2DObjectRoot(gl2DObject* obj)
{
  _2dobjectroot = obj;
}

void PFD_B747::setAircraftState(float ias, float mach, float rc, float alt)
{
  currentMach         = mach;
  trueAirspeed        = ias;
  currentAlt          = alt;
  currentRC	          = rc;
}

void PFD_B747::setApModeIndication(bool spd, bool flch, bool hdg, bool vspd, bool alt,  apMode curMode)
{
	_spd = spd; _flch = flch; _hdg = hdg; _vspd = vspd; _alt = alt; _apMode  = curMode;
}

void PFD_B747::setAltitudeOffset(int altOffset)
{
	_altOffset = altOffset;
}

void PFD_B747::disableSpdBug(void)
{
	_spdBugOn=false;
	//else {_spdBugOn=true;}
}

void PFD_B747::enableSpdBug(void)
{
	_spdBugOn=true;

}

void PFD_B747::disableAltBug(void)
{
	_altBugOn=false;
}

void PFD_B747::enableAltBug(void)
{
	_altBugOn=true;

}

void PFD_B747::setCurrentTime(double sec)
{
  _curTimeSec = sec;
}

void PFD_B747::updateReferenceData( int selectedFlapAngle, int landingFlapAngle, float Vref, float Vstall,
                                    float Vplackard, float Vmaneuver, float V1, float V2, float FAS)
{
  _selectedFlapAngle  = selectedFlapAngle;
  _landingFlapAngle   = landingFlapAngle;
  _Vref               = Vref * MS2KTS;
  _Vstall             = Vstall * MS2KTS;
  _Vplackard          = Vplackard * MS2KTS;
  _Vmaneuver          = Vmaneuver * MS2KTS;
  _V1                 = V1 * MS2KTS;
  _V2                 = V2 * MS2KTS;
  _FAS                = FAS * MS2KTS;
}
