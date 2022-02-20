#include "G1000GLWindow.hxx"

#include <GL/gl.h>

#include <RenderWindow.hxx>
#include <FTFont.hxx>

#include "G1000Gauge.hxx"

#include <ColorMap.hpp>

G1000GLWindow::G1000GLWindow(int width, int height):
  texture_id(0),
  DuecaGLWindow("G1000 - PFD"),
  _width(width),
  _height(height),
  _render_window(new hmi::RenderWindow(width,height)),
  _g1000_gauge(new G1000Gauge)
{
  setWindow(138,128,_width,_height);

  // The G1000Gauge is the main gauge for this window
  _render_window->AddGauge(_g1000_gauge);
}

G1000GLWindow::~G1000GLWindow()
{
  delete _render_window;     _render_window=0;
}

void G1000GLWindow::display()
{

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
  // glColor3f(1.0, 1.0, 1.0);
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
  //
  //
  // //////////////////////////////////////////////////////////////////
  // float xl = -1.0;
  // float xu = -1.0+195.0/1412.0*2.0;
  // float yl = -1.0;
  // float yu = 1.0;
  //
  // float xmin = xl;
  // float xmax = xu;
  // float ymin = yl;
  // float ymax = yu;
  //
  // float x = (xl+xu)/2.0;
  // float y = (yl+yu)/2.0;
  // float offset = 0.0;
  //
  // glPushMatrix();
  //
  // // texture
  // glEnable (GL_TEXTURE_2D);
  // glBindTexture (GL_TEXTURE_2D, texture_id);
  //
  // // switch
  // glColor3f(1.0, 1.0, 1.0);
  //
  // glTranslatef(x,y,0.0);
  //
  //
  // glBegin(GL_QUADS);
  // glTexCoord2f(0.0+offset, 1.0); // upper left corner of image
  // glVertex2f(xmin-x, ymax-y);
  // glTexCoord2f(0.5+offset, 1.0); // upper right corner of image
  // glVertex2f(xmax-x, ymax-y);
  // glTexCoord2f(0.5+offset, 0.0); // lower right corner of image
  // glVertex2f(xmax-x, ymin-y);
  // glTexCoord2f(0.0+offset, 0.0); // lower left corner of image
  // glVertex2f(xmin-x, ymin-y);
  // glEnd();
  //
  // glDisable (GL_TEXTURE_2D);
  //
  // glPopMatrix();
  ///////////////////////////////////////////////////////////////////////

  // Render the gauge
  _render_window->Display();
  swapBuffers();
}

void G1000GLWindow::reshape(int width, int height)
{
  _width  = width;
  _height = height;

  // glViewport (0, 0, (GLsizei) width, (GLsizei) height);
  //
  // glMatrixMode (GL_PROJECTION);
  // glLoadIdentity();
  // gluOrtho2D(-1.0 ,1.0, -1.0, 1.0);// fixed coordinate axes

  _render_window->Reshape(_width,_height);
}

void G1000GLWindow::mouse(int button, int state, int x, int y)
{

  if(button == GLUT_LEFT_BUTTON){
    _g1000_gauge->GetData().mouse_down = (state == GLUT_DOWN);
  }

  if( state == GLUT_DOWN && button == GLUT_LEFT_BUTTON) {
    // std::cout <<"G1000 left down @ ( " << x << ", " << y << " ) \n";
    _g1000_gauge->GetData().mouse_left = true;
    _g1000_gauge->GetData().mouse_x = x;
    _g1000_gauge->GetData().mouse_y = y;

  }
  //else if ( state == GLUT_DOWN && button == GLUT_RIGHT_BUTTON) {
  else{
    //_g1000_gauge->GetData().mouse_left = false;
    //std::cout<<"G1000 right down @ ( " << x << ", " << y << " ) \n";
  }
}

void G1000GLWindow::init()
{
  loadDefaultColorMap();

  // glGenTextures(1, &texture_id);
  // if(utils.loadTGA("ap.tga", texture_id) != 1) {
  //   // debug
  //   std::cout<<"error loading " << "bezel_left.tga" << " @ " << texture_id << "\n";
  // }else{
  //   std::cout<<"bezel correctly loaded ================================ \n";
  // }




  // Give the render window a chance to initialize
  _render_window->Init();
}

G1000GaugeData& G1000GLWindow::getG1000Data()
{
  return _g1000_gauge->GetData();
}
