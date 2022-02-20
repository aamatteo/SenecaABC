#include "MFDGLWindow.hxx"

#include <GL/gl.h>

#include <RenderWindow.hxx>
#include <FTFont.hxx>

#include "MFDGauge.hxx"

#include <ColorMap.hpp>

MFDGLWindow::MFDGLWindow(int width, int height):
  DuecaGLWindow("G1000 - MFD"),
  _width(width),
  _height(height),
  _render_window(new hmi::RenderWindow(width,height)),
  _g1000_gauge(new MFDGauge)
{
  setWindow(138,128,_width,_height);

  // The G1000Gauge is the main gauge for this window
  _render_window->AddGauge(_g1000_gauge);
}

MFDGLWindow::~MFDGLWindow()
{
  delete _render_window;     _render_window=0;
}

void MFDGLWindow::display()
{
  // Render the gauge
  _render_window->Display();

  swapBuffers();
}

void MFDGLWindow::reshape(int width, int height)
{
  _width  = width;
  _height = height;

  _render_window->Reshape(_width,_height);
}

void MFDGLWindow::mouse(int button, int state, int x, int y)
{

  // if(button == GLUT_LEFT_BUTTON){
  //   _g1000_gauge->GetData().mouse_down = (state == GLUT_DOWN);
  // }

  if( state == GLUT_DOWN && button == GLUT_LEFT_BUTTON) {
    // std::cout <<"G1000 left down @ ( " << x << ", " << y << " ) \n";
    _g1000_gauge->GetData().mouse_left = true;
    _g1000_gauge->GetData().mouse_x = x;
    _g1000_gauge->GetData().mouse_y = 912-y;

  }
  //else if ( state == GLUT_DOWN && button == GLUT_RIGHT_BUTTON) {
  else{
    //_g1000_gauge->GetData().mouse_left = false;
    //std::cout<<"G1000 right down @ ( " << x << ", " << y << " ) \n";
  }
}

void MFDGLWindow::init()
{
  loadDefaultColorMap();

  // Give the render window a chance to initialize
  _render_window->Init();
}

MFDGaugeData& MFDGLWindow::getG1000Data()
{
  return _g1000_gauge->GetData();
}
