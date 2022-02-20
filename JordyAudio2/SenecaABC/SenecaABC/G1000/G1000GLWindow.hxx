#ifndef _G1000GLWINDOW_H_
#define _G1000GLWINDOW_H_

#include <DuecaGLWindow.hxx>
#include "../../MCP737/MCP737GUI/project_utilities.h"

// Forward declarations to avoid #includes
namespace hmi { class RenderWindow; };
class G1000Gauge;
class G1000GaugeData;

class G1000GLWindow: public dueca::DuecaGLWindow
{
public:
  G1000GLWindow(int width=1024, int height=768);
  virtual ~G1000GLWindow();

private:
  // Copy and assignment doesn't make any sense
  G1000GLWindow(const G1000GLWindow& dummy);
  G1000GLWindow& operator=(const G1000GLWindow& dummy);

public:
  // Initialize our display
  void init();

  // Update and render the display
  void display();

  virtual void mouse(int button, int state, int x, int y);

  // Acess the data struct used to communicate with the gauges
  G1000GaugeData& getG1000Data();

public:
  // An overload called when the window changes size. It gives the
  // gauges a chance to deal with resizes
  void reshape(int width, int height);

private:
  ProjectUtilities utils;
  GLuint texture_id;

  int _width;
  int _height;

  hmi::RenderWindow* _render_window;
  G1000Gauge*        _g1000_gauge;
};

#endif /* _G1000GLWINDOW_H_ */
