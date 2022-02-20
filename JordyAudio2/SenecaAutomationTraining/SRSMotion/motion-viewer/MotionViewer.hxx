/* ------------------------------------------------------------------   */
/*      item            : MotionViewer.hxx
        made by         : Olaf Stroosma
        date            : 010726
	category        : header file 
        description     : OpenGL motion visualization
	changes         : 010726 first version
        language        : C++
*/

#ifndef Motionviewer_hxx
#define Motionviewer_hxx

#include <DuecaGLWindow.hxx>
#include <GL/glut.h>

#ifdef DUECA_NS_ON
using dueca::DuecaGLWindow;
#endif

#include <stringoptions.h>

class MotionViewer: public DuecaGLWindow
{
public:
	MotionViewer();
	~MotionViewer();
	
	// Begin inherited funtions from DuecaGLWindow	
  /** \group Prototypes for interation handling. 
      This class adheres to -- as much as is practical -- the calling
      conventions for Glut. */

  /** This is called if the size of the window is changed. You might
      need to update the image set-up for a different screen
      format. */
  void reshape(int x, int y);

  /** Called when a key is pressed. */
  void keyboard(unsigned char key, int x, int y);

  /** Called when a function key is pressed.
      \todo Does not currently work under gtk. */
	// OS: not used in Motion Viewer
  //void special(int key, int x, int y);
  
  /** This is called whenever the display needs to be redrawn. When
      called, the appropriate window has been made current. */
  void display();

  /** This is called when the window is ready, for first-time
      set-up. */
  void initGL();

  /** This is called whenever a mouse button event comes in */
  void mouse(int button, int state, int x, int y);

  /** This is called whenever a mouse motion event comes in. */
  void motion(int x, int y);

  // End inherited funtions from DuecaGLWindow  
  
  // data structure for a hydraulic jack, status coding:
  // 0:	OK, white
  // 100:	WARNING, red
  // 0-100: CAUTION, between white and red
  struct hydr_cilinder { float x0, y0, z0, x1, y1, z1, length; int status;} legs[6];
  
  // text to be displayed
  vstring display_text;
		
  // position and orientation of cabin
  struct cab { float x, y, z, phi, theta, psi;} cabin;

private:
	// data structure for 3 corners of the cabin
	// defined as midpoint between 2 meeting jacks
	struct { float x, y, z;} corners[3];
	
	// viewing position (elevation angle, azimuth angle, distance)
	float view_pos[3]; // = {110.0, 40.0, -7.5};
	
	// define the true scale of the coordinate system
	// in relation to cabin definition system
	const float cabin_scale;// = 0.428f;
	
	// cabin display list ID
	GLuint theCabin;
	
	// mouse state for moving of viewpoint 
	enum {ST_STATIC, ST_MOVING} mouse_state;
	
	// Initialisation cabin model geometry
	void init_cabin_model();
	
	// convert the leg data to corner data for the cabin
	void convert_data(void);
	
	// Draw one of the legs
	void draw_leg( int leg_nr, struct hydr_cilinder *leg);

  // drawing offset for cabin, due to scaling and funny reference point
  const float x_offset;
};
#endif
