
//-----------------------------------------------------------------------------
//
// OglClientAreaUser.h
//
// Copyright (C) 2000:  Delft University of Technology,
//						Fac. Aerospace Engineering, 
//						Control & Simulation 
//
// Description:<Description> 
//
// Created: by <name> on <date>
// Updated: by <name> on <date>
//
//------------------------------------------------------------------------------


#ifndef WglClientAreaUser_H
#define WglClientAreaUser_H

//------------------------------------------------------------------------------
// Include files 
//------------------------------------------------------------------------------

// dueca GLWindow headers
#include <DuecaGLWindow.hxx>

// OpenGL Headers
#ifndef GLUT_H
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif

//------------------------------------------------------------------------------
// Types & Enums
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Forward declarations
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// OglClientAreaUser Class Declaration
//------------------------------------------------------------------------------
class WglClientAreaUser: public DUECA_NS::DuecaGLWindow
{
public:

	//--------------------------------------------------------------------------
	// Types & Enums
	//--------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	// Methods
	//--------------------------------------------------------------------------
	// Empty CONSTRUCTOR
  WglClientAreaUser();
  // Overloaded CONSTRUCTOR with options from DuecaGLWindow
  WglClientAreaUser(const char *window_title, bool mouse_passive=false);
	// DESTRUCTOR
	virtual ~WglClientAreaUser();

  // inherited from DuecaGLWindow
  virtual void reshape (int wClientArea, int hwClientArea);
  //virtual void keyboard (unsigned char key, int x, int y);
  //virtual void special (int key, int x, int y);
  //virtual void display () = 0;
  //virtual void initGL () = 0;
  	

	//--------------------------------------------------------------------------
	// Public Member Data
	//--------------------------------------------------------------------------
  int window_width, window_height; // use these public variable to get the size of the current window

protected:

	//--------------------------------------------------------------------------
	// Protected Member Data
	//--------------------------------------------------------------------------


	//--------------------------------------------------------------------------
	// Methods
	//--------------------------------------------------------------------------

	// Functions for rendering vector and bitmap fonts in OpenGL
	void strokeString(float x, float y, const char *string, void *font, double size);
	void bitmapString(float x, float y, const char *string, void *font = GLUT_BITMAP_TIMES_ROMAN_24);



private:
	
	//--------------------------------------------------------------------------
	// Private Member Data
	//--------------------------------------------------------------------------
	
	
	//--------------------------------------------------------------------------
	// Methods
	//--------------------------------------------------------------------------
						

};	// End OglClientAreaUser class

#endif // OglClientAreaUser_H
