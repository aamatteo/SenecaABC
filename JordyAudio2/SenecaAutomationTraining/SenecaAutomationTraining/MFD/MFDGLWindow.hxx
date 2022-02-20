#ifndef _MFDGLWINDOW_H_
#define _MFDGLWINDOW_H_

#include <DuecaGLWindow.hxx>
#include "../../MCP737/MCP737GUI/project_utilities.h"

// Forward declarations to avoid #includes
namespace hmi { class RenderWindow; };
class MFDGauge;
class MFDGaugeData;

class MFDGLWindow: public dueca::DuecaGLWindow
{
public:
  MFDGLWindow(int width=1024, int height=768);
  virtual ~MFDGLWindow();

private:
  // Copy and assignment doesn't make any sense
  MFDGLWindow(const MFDGLWindow& dummy);
  MFDGLWindow& operator=(const MFDGLWindow& dummy);

public:
  // Initialize our display
  void init();

  // Update and render the display
  void display();

  virtual void mouse(int button, int state, int x, int y);

  // Acess the data struct used to communicate with the gauges
  MFDGaugeData& getG1000Data();

public:
  // An overload called when the window changes size. It gives the
  // gauges a chance to deal with resizes
  void reshape(int width, int height);

private:
  int _width;
  int _height;

  hmi::RenderWindow* _render_window;
  MFDGauge*        _g1000_gauge;
};

#endif /* _G1000GLWINDOW_H_ */
