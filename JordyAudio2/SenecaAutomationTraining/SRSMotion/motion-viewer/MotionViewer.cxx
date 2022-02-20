/*
 *	MOTIONVIEW.c main motion view program file
 *	
 *	AUTHOR:			O. Stroosma
 *	DATE:			28-1-99
 *	REVISION DATE:	26-7-01 DUECA
 *
 *	NOTE:			primary display axes are characterized as follows:
 *					origin: c.g. of upper base triangle in mid pos.
 *					x-axis: through apex of upper base triangle
 *							or nose of cabin, pointing fwd
 *					y-axis: pointing to the right
 *					z-axis:	pointing straight down
 *
 *	INPUT:			6 structures of hydr_cilinder composed of:
 *						x0, y0, z0: base position (hardcoded at the moment)
 *						x1, y1, z1: top position
 *						status from 0 to 100
 *
 */

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "MotionViewer.hxx"
#include "text.h"

#include <ostream>

// Constructor
MotionViewer::MotionViewer(void):
DuecaGLWindow("SIMONA Motion Viewer", true, true, true, false),
cabin_scale(0.428), x_offset(0.36)
{
  // viewing position (elevation angle, azimuth angle, distance)
  view_pos[0] = 110.0;
  view_pos[1] = 320.0;
  view_pos[2] = -7.5;
  
  // 24AUG2001 default status
  for(int ii=0;ii<6;++ii) legs[ii].status = 0;
}

MotionViewer::~MotionViewer()
{
  // apparently nothing
}	
	
	
// Initialisation cabin model geometry
void MotionViewer::init_cabin_model()
{
  // create cabin display list
  theCabin = glGenLists(1);
  
  // new display list
  glNewList(theCabin, GL_COMPILE);
  
  // polygon style 
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  
  // to get to real world coordinates
  glScalef(cabin_scale, cabin_scale, cabin_scale);
  
  // coordinate axes
  glColor4f(0.7f, 0.7f, 0.7f, 1.0);
  glBegin(GL_LINES);
  glVertex3f(0.0, 0.0, 0.0);
  glVertex3f(4.0, 0.0, 0.0);
  glVertex3f(0.0, 0.0, 0.0);
  glVertex3f(0.0, 4.0, 0.0);
  glVertex3f(0.0, 0.0, 0.0);
  glVertex3f(0.0, 0.0, 4.0);
  glEnd();
  
  glPushMatrix();
  glTranslatef(4.5f, 0.0, 0.0);
  glScalef(0.01f, 0.01f, 0.01f);
  glRotatef(180, 1.0, 0.0, 0.0);
  glutStrokeCharacter (GLUT_STROKE_ROMAN, 'x'); 
  glPopMatrix();
  
  glPushMatrix();
  glTranslatef(0.0, 4.5f, 0.0);
  glScalef(0.01f, 0.01f, 0.01f);
  glRotatef(180, 1.0, 0.0, 0.0);
  glutStrokeCharacter (GLUT_STROKE_ROMAN, 'y'); 
  glPopMatrix();
  
  glPushMatrix();
  glTranslatef(0.0, 0.0, 4.5f);
  glScalef(0.01f, 0.01f, 0.01f);
  glRotatef(180, 1.0, 0.0, 0.0);
  glutStrokeCharacter (GLUT_STROKE_ROMAN, 'z'); 
  glPopMatrix();
  
  // color and alpha value 
  glColor4f(0.3f,0.3f,0.3f,0.7f);
  
  // scale around front gimbal point to actual dimensions [ML]
  // scaling factor is 1600/1200 (new/old upper gimbal radius)
  glTranslatef(2.88f, 0.0, 0.0);
  glScalef(1.3333, 1.3333, 1.3333);
  glTranslatef(-2.88f, 0.0, 0.0);

  // right side
  glBegin(GL_POLYGON);
  glNormal3f(0.0, 1.0, 0.0);
  glVertex3f(-1.44f, 2.5, 0.0);
  glVertex3f(2.88f, 2.5, 0.0);
  glVertex3f(2.88f, 2.5, -1.5);
  glVertex3f(1.44f, 2.5, -2.5);
  glVertex3f(-1.44f, 2.5, -2.5);
  glEnd();
  
  // left side
  glBegin(GL_POLYGON);
  glNormal3f(0.0, -1.0, 0.0);
  glVertex3f(-1.44f, -2.5, 0.0);
  glVertex3f(-1.44f, -2.5, -2.5);
  glVertex3f(1.44f, -2.5, -2.5);
  glVertex3f(2.88f, -2.5, -1.5);
  glVertex3f(2.88f, -2.5, 0.0);
  glEnd();
  
  // front
  glColor4f(0.35f, 0.35f, 0.35f, 0.7f);
  glBegin(GL_POLYGON);
  glNormal3f(1.0, 0.0, 0.0);
  glVertex3f(2.88f, 2.5, 0.0);
  glVertex3f(2.88f, -2.5, 0.0);
  glVertex3f(2.88f, -2.5, -1.5);
  glVertex3f(2.88f, 2.5, -1.5);
  glEnd();
  
  // windscreen
  glColor4f(0.4f, 0.4f, 0.4f, 0.7f);
  glBegin(GL_POLYGON);
  glNormal3f(1.0, 0.0, -1.44f);
  glVertex3f(2.88f, 2.5, -1.5);
  glVertex3f(2.88f, -2.5, -1.5);
  glVertex3f(1.44f, -2.5, -2.5);
  glVertex3f(1.44f, 2.5, -2.5);
  glEnd();
  
  // roof
  glColor4f(0.25f, 0.25f, 0.25f, 0.7f);
  glBegin(GL_POLYGON);
  glNormal3f(0.0, 0.0, -1.0);
  glVertex3f(1.44f, 2.5, -2.5);
  glVertex3f(1.44f, -2.5, -2.5);
  glVertex3f(-1.44f, -2.5, -2.5);
  glVertex3f(-1.44f, 2.5, -2.5);
  glEnd();
  
  // back
  glColor4f(0.4f, 0.4f, 0.4f, 0.7f);
  glBegin(GL_POLYGON);
  glNormal3f(-1.0, 0.0, 0.0);
  glVertex3f(-1.44f, 2.5, 0.0);
  glVertex3f(-1.44f, 2.5, -2.5);
  glVertex3f(-1.44f, -2.5, -2.5);
  glVertex3f(-1.44f, -2.5, 0.0);
  glEnd();
  
  // bottom
  glBegin(GL_POLYGON);
  glNormal3f(0.0, 0.0, 1.0);
  glVertex3f(-1.44f, 2.5, 0.0);
  glVertex3f(-1.44f, -2.5, 0.0);
  glVertex3f(2.88f, -2.5, 0.0);
  glVertex3f(2.88f, 2.5, 0.0);
  glEnd();
  
  // end display list
  glEndList();
}

// Initialisation function for viewer
// formerly known as init_viewer()
void MotionViewer::initGL(void)
{
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glShadeModel(GL_FLAT);
  
  glEnable(GL_DEPTH_TEST);
  
  // set up cabin model display list 
  init_cabin_model();
  
  // define fixed basepoints of cilinders
  // real values
  legs[0].z0 = legs[1].z0 = legs[2].z0 = 2.39;
  legs[3].z0 = legs[4].z0 = legs[5].z0 = 2.39;
  
  legs[0].x0 = 0.671031484f;
  legs[0].y0 = 0.994845087f;

  legs[1].x0 = 0.526045376f;
  legs[1].y0 = 1.07855286f;

  legs[2].x0 = -1.19707686f;
  legs[2].y0 = 0.0837077685f;
  
  legs[3].x0 = -1.19707686f;
  legs[3].y0 = -0.0837077685f;
  
  legs[4].x0 = 0.526045376f;
  legs[4].y0 = -1.07855286f;
  
  legs[5].x0 = 0.671031484f;
  legs[5].y0 = -0.994845087f;
  
  // define initial positions of gimbals
  // real values 
  legs[0].x1 = 1.19707686f;
  legs[0].y1 = 0.0837077642f;
  legs[0].z1 = 2.67399807E-05f;
  
  legs[1].x1 = -0.526045376f;
  legs[1].y1 = 1.0785528f;
  legs[1].z1 = 0.000344537706f;
  
  legs[2].x1 = -0.671031484f;
  legs[2].y1 = 0.994845036f;
  legs[2].z1 = 0.000317797726f;
  
  legs[3].x1 = -0.671031484f;
  legs[3].y1 = -0.994845036f;
  legs[3].z1 = -0.000317797726f;
  
  legs[4].x1 = -0.526045376f;
  legs[4].y1 = -1.0785528f;
  legs[4].z1 = -0.000344537706f;
  
  legs[5].x1 = 1.19707686f;
  legs[5].y1 = -0.0837077642f;
  legs[5].z1 = -2.67399807E-05f;
}

// convert the leg data to corner data for the cabin
void MotionViewer::convert_data(void)
{
  // define corners as average of two gimbal positions
  corners[0].x = 0.5*( legs[3].x1 + legs[4].x1);
  corners[0].y = 0.5*( legs[3].y1 + legs[4].y1);
  corners[0].z = 0.5*( legs[3].z1 + legs[4].z1);
  
  corners[1].x = 0.5*( legs[1].x1 + legs[2].x1);
  corners[1].y = 0.5*( legs[1].y1 + legs[2].y1);
  corners[1].z = 0.5*( legs[1].z1 + legs[2].z1);
  
  corners[2].x = 0.5*( legs[0].x1 + legs[5].x1);
  corners[2].y = 0.5*( legs[0].y1 + legs[5].y1);
  corners[2].z = 0.5*( legs[0].z1 + legs[5].z1);
  
  //glutPostRedisplay();
}

// Draw one of the legs
void MotionViewer::draw_leg( int leg_nr, struct hydr_cilinder *leg)
{
  float rot_axis[3];
  float rot_angle;
  float rel_pos1[3];
  // tentative max. and min. lengths for status display
  /* float max_length = 3.281-0.05;
     float min_length = 2.131+0.05;
     float buffer_length = 0.05; */
  
  glColor3f(1.0, 1.0, 1.0);
  
  // calculate rotation axis, based on gimbal pos and leg length
  // use the cross product between current x-axis and leg end position
  // (normalization done by GL) and the in-product for the rotation angle
  
  // calculate the relative vector of gimbal to base
  rel_pos1[0] = leg->x1 - leg->x0;
  rel_pos1[1] = leg->y1 - leg->y0;
  rel_pos1[2] = leg->z1 - leg->z0;
  
  // calculate the length of the leg (may eventually be supplied separately)
  leg->length = sqrt(rel_pos1[0]*rel_pos1[0] + 
		     rel_pos1[1]*rel_pos1[1] + 
		     rel_pos1[2]*rel_pos1[2]);
  
  // color based on status: 0 = pure white, 100 = pure red
  if (leg->status != 0) glColor3f(1.0, 1-0.01*leg->status, 1- 0.01*leg->status);
  
  // calulate cross product of x-axis and relative positive vector
  rot_axis[0] = 0.0;
  rot_axis[1] = -rel_pos1[2];
  rot_axis[2] = rel_pos1[1];
  
  // calulate rotation angle
  rot_angle =  90-180/3.14*asin(rel_pos1[0]/leg->length);
  if (rot_angle <0) rot_angle += 180;
  
  glPushMatrix();
  
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  glTranslatef(leg->x0, leg->y0, leg->z0); // to get to base position
  
  // rotate
  glRotatef(rot_angle, rot_axis[0], rot_axis[1], rot_axis[2]);
  
  // Scale the x-axis, draw a box, ...
  glTranslatef(leg->length/2.0, 0.0, 0.0);
  glScalef (leg->length, 0.1f, 0.1f);
  glutSolidCube (1.0);
  
  glPopMatrix(); // return to fixed origin
  
}

// Display function
// formerly known as display_viewer()
void MotionViewer::display(void)
{
  int i;

#ifdef OLD_TRANSFORMS
  float mid_12[3], x_new[3], rot_axis1[3], y_new[3];
  float x_new_length, y_new_length1, y_new_length2;
  float rot_angle1, rot_angle2;
#endif

  // convert the leg data to cabin data
  // Is this the right place???
  convert_data();
  
  // clear display
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  glColor3f(1.0, 1.0, 1.0);
  
  // display name of motion pattern
  glMatrixMode (GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  gluOrtho2D(100.0, 100.0, -100.0, 100.0);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();
  glTranslatef(-0.9, 0.8, 0.0);
  strokeString(0,0, display_text.c_str(), GLUT_STROKE_ROMAN, 0.0005);
  glPopMatrix();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  
  // setup general viewing position
  glLoadIdentity();
  glTranslatef(0.0, 0.0, view_pos[2]);
  glRotatef(view_pos[0],1.0, 0.0, 0.0);
  glRotatef(view_pos[1],0.0, 0.0, 1.0);
  
  // manipulate transparancy
  glEnable(GL_BLEND);
  glEnable(GL_ALPHA_TEST);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
  
  // draw ground
  glColor4f(0.2f, 0.25f, 0.2f, 0.9f);
  glBegin(GL_POLYGON);
  glVertex3f(-3.0, -3.0, 2.39);
  glVertex3f(-3.0, 3.0, 2.39);
  glVertex3f(3.0, 3.0, 2.39);
  glVertex3f(3.0, -3.0, 2.39);
  glEnd();
  
  // draw ground frame
  glColor4f(0.1f, 0.1f, 1.0, 1.0);
  glLineWidth(6);
  glBegin(GL_LINES);
  glVertex3f(legs[1].x0, legs[1].y0, 2.35);
  glVertex3f(legs[2].x0, legs[2].y0, 2.35);
  glVertex3f(legs[3].x0, legs[3].y0, 2.35);
  glVertex3f(legs[4].x0, legs[4].y0, 2.35);
  glVertex3f(legs[5].x0, legs[5].y0, 2.35);
  glVertex3f(legs[0].x0, legs[0].y0, 2.35);
  glEnd();
  glLineWidth(1);
  
  // draw legs [OS] 03FEB03 moved here
  for (i = 0; i<6; i++)
    {
      draw_leg(i, &legs[i]);
    }
  
  // manipulate modelview to setup cabin ( to be checked )

#ifdef OLD_TRANSFORMS
  glTranslatef(corners[2].x, corners[2].y, corners[2].z); // to get to front gimbal
  // rotate coord system
  // first for new x-axis
  // calulate mid point between corner 0 and 1
  mid_12[0] = 0.5*(corners[0].x+corners[1].x);
  mid_12[1] = 0.5*(corners[0].y+corners[1].y);
  mid_12[2] = 0.5*(corners[0].z+corners[1].z);
  // calculate new x-axis
  x_new[0] = (corners[2].x - mid_12[0]);
  x_new[1] = (corners[2].y - mid_12[1]);
  x_new[2] = (corners[2].z - mid_12[2]);
  x_new_length = sqrt(x_new[0]*x_new[0] + x_new[1]*x_new[1] + x_new[2]*x_new[2]);
  // calulate rotation axis from x_old to x_new
  rot_axis1[0] = 0.0;
  rot_axis1[1] = -x_new[2];
  rot_axis1[2] = x_new[1];
  // calulate rotation angle
  rot_angle1 = 90 - 180/3.14*asin(x_new[0]/x_new_length);
  // rotate
  glRotatef(rot_angle1, rot_axis1[0], rot_axis1[1], rot_axis1[2]);
  
  // now for new y-axis 
  // calculate new y-axis
  y_new[0] = (corners[0].x - corners[1].x);
  y_new[1] = (corners[0].y - corners[1].y);
  y_new[2] = (corners[0].z - corners[1].z);
  // length of actual y-axis vector
  y_new_length1 = sqrt(y_new[0]*y_new[0] + y_new[1]*y_new[1] + y_new[2]*y_new[2]);
  // length of projection of y-axis vector on horizontal plane
  y_new_length2 = sqrt(y_new[0]*y_new[0] + y_new[1]*y_new[1]);
  // calulate rotation angle
  rot_angle2 = 90 - 180/3.14*asin((y_new[0]*y_new[0]+y_new[1]*y_new[1])
				  /y_new_length1/y_new_length2);
  // patch to correctly turn left
  if (corners[0].z > corners[1].z) rot_angle2 = -rot_angle2;
  // rotate
  glRotatef(rot_angle2, 1.0, 0.0, 0.0);
  
  glTranslatef(cabin_scale*-2.88f, 0.0, 0.0); // to get to cabin origin
  
#else
  glTranslatef(cabin.x, cabin.y, cabin.z);
  glRotatef(cabin.psi, 0.0, 0.0, 1.0);
  glRotatef(cabin.theta, 0.0, 1.0, 0.0);
  glRotatef(cabin.phi, 1.0, 0.0, 0.0);
  glTranslatef(x_offset, 0.0, 0.0);
#endif

  // draw cabin model display list
  glCallList(theCabin);	
  glDisable(GL_BLEND);
  glDisable(GL_ALPHA_TEST);
  
  swapBuffers();
}

// reshape function
void MotionViewer::reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(65.0, (GLfloat) w/(GLfloat) h, 1.0, 50.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

// Keyboard function
// formerly known as handle_keyboard
void MotionViewer::keyboard(unsigned char key, int x, int y)
{
  switch(key) 
    {
    case '2':
    case 'a':
      view_pos[0] -=10;
      break;
    case '8':
    case 'A':
      view_pos[0] +=10;
      break;
    case '4':
    case 'b':
      view_pos[1] -=10;
      break;
    case '6':
    case 'B':
      view_pos[1] +=10;
      break;
    case '3':
    case 'c':
      view_pos[2] -=0.5;
      break;
    case '9':
    case 'C':
      view_pos[2] +=0.5;
      break;
    }

  // notify DuecaGLWindow that a redraw is needed
  redraw();
}

// function to handle mouse button presses
// formerly known as handle_mouse_press
void MotionViewer::mouse(int button, int state, int x, int y)
{
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN 
      && mouse_state == ST_STATIC) mouse_state = ST_MOVING;
  else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP
	   && mouse_state == ST_MOVING) mouse_state = ST_STATIC;
}

// function to handle mouse motion
// formerly known as handle_mouse_move
void MotionViewer::motion(int x, int y)
{
  static int old_x = 0, old_y = 0;
  
  if ( mouse_state == ST_MOVING) {
    
    if ( x < old_x ) view_pos[1] += 3;
    if ( x > old_x ) view_pos[1] -= 3;
    
    // include a vertical threshold (3 pixels) to avoid wild movement
    if ( y < old_y - 3 ) view_pos[0] += 3;
    if ( y > old_y + 3 ) view_pos[0] -= 3;
    
    old_x = x;
    old_y = y;
  }
}
