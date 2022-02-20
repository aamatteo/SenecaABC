
//-----------------------------------------------------------------------------
//
// WglClientAreaUser.cxx
//
// Copyright (C) 2000:  Delft University of Technology,
//						Fac. Aerospace Engineering, 
//						Control & Simulation 
//
// Description: Super class for drawing OpenGL windows. Use this as the base class for all common drawing
//              operations in your simulation 
//
// Created: by Manfred Roza on 2002?
// Updated: by Mark Mulder on 24/01/2007
//
//
// Update descriptions----------------------------------------------------------
// 24/01/2007 - added the virtual reshape function to redefine the viewport with new size of window
// 23/01/2007 - made the WglClientAreaUser class subclass of DuecaGLWindow

//------------------------------------------------------------------------------
// Include files 
//------------------------------------------------------------------------------
#include "WglClientAreaUser.h"
#include "string.h"


//------------------------------------------------------------------------------
// Default Constructors
//------------------------------------------------------------------------------
WglClientAreaUser::WglClientAreaUser():
  DuecaGLWindow("B747 Displays", false)
{

}

WglClientAreaUser::WglClientAreaUser(const char *window_title, bool mouse_passive):
  DuecaGLWindow (window_title, mouse_passive)
{

}

//------------------------------------------------------------------------------
// Destructor
//------------------------------------------------------------------------------
WglClientAreaUser::~WglClientAreaUser()
{

}


void WglClientAreaUser::reshape(int wClientArea, int hwClientArea)
{
  // define the origin of the Viewport to be in the lower left corner of the window
  glViewport (0, 0, (GLsizei)wClientArea, (GLsizei)hwClientArea);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  // clip everything outside the window
  gluOrtho2D(0.0, (GLdouble)wClientArea, 0.0, (GLdouble) hwClientArea);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  // store the window size
  window_width = wClientArea;
  window_height = hwClientArea;

  redraw();
}


//------------------------------------------------------------------------------
// strokeString
//
// Function for rendering string fonts in OpenGL. Function uses the GLUT library
// glutStrokeCharacter function which allows arbitrary scaling (vectors). This 
// function is slower compared to the bitmapString function. Available fonts:
//
// GLUT_STROKE_ROMAN
// GLUT_STROKE_MONO_ROMAN
//
// Other font types could be created using display lists
//------------------------------------------------------------------------------
void WglClientAreaUser::strokeString(float x, float y, const char *string, void *font, double size)
{
	glPushMatrix();
		glTranslatef(x, y, 0);
		glScalef(size, size, size);
		while (*string) 
		{
			glutStrokeCharacter(font, *string);
			++string;
		}
	glPopMatrix();
}


//------------------------------------------------------------------------------
// bitmapString
//
// Function for rendering string fonts in OpenGL. Function uses the GLUT library
// glutBitmapCharacter function which doesn't allow arbitrary scaling. This 
// function is faster compared to the strokeString function. Available fonts:
//
// GLUT_BITMAP_TIMES_ROMAN_10
// GLUT_BITMAP_TIMES_ROMAN_24
// GLUT_BITMAP_HELVETICA_10
// GLUT_BITMAP_HELVETICA_12
// GLUT_BITMAP_HELVETICA_18
// GLUT_BITMAP_8_BY_13
// GLUT_BITMAP_9_BY_15
//
// Other font types could be created using display lists of bitmap characters.
//------------------------------------------------------------------------------
void WglClientAreaUser::bitmapString(float x, float y, const char *string, void *font)
{
	int len, i;

	glRasterPos2f(x, y);
	len = (int) strlen(string);
	for (i = 0; i < len; ++i) 
	{
		glutBitmapCharacter(font, string[i]);
	}
}

