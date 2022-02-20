/* ------------------------------------------------------------------   */
/*      item            : EngineData.hxx
        made by         : jcomans
        from template   : hmigauge.hxx
        template made by: Joost Ellerbroek
        date            : 081013
        category        : header file
        description     :
        changes         : 081013 first version
        language        : C++
*/

#ifndef Map_hxx
#define Map_hxx

#include <GaugeComponent.hxx>
#include "MapData.hxx"
#include <iostream>
#include <string>
#include <Eigen/Dense>

// All the hmilib classes are defined in the hmi namespace
using namespace hmi;

/** hmiGauge GL display Gauge component
*/
class Map: public GaugeComponent
{
private:// Member data
  // Data interface object (defined in EngineDataData.if)
  MapData data;

  GLuint _gl_display_list_index;

  Eigen::MatrixXd get_fp(std::string filename);


  // Your other member data here

public:// Construction / Destruction
  /// Constructor
  Map();

  /// Destructor
  ~Map();

public:// Functions implemented from hmiGaugeComponent
  /// Initialize your data / GL display lists here
  void Init();

  /// Render your gauge component
  void Render();

  /* ===================================================== */
  /* Implement the following three functions if you want to
     use mouse events in your component. */

  /// Check if coordinate (x, y) is inside this component
  // bool CoordinateInComponent(double x, double y) const;

  /// This is called whenever a mouse button event comes in.
  // void MouseButton(int button, int state, double x, double y);

  /// This is called whenever a mouse motion event comes in.
  // void MouseMotion(double x, double y);

  /* ===================================================== */

public:// Custom functions
  // Your functions here

public:// Data access
  /// Access this components data interface
  MapData& GetData() {return data;}

};

#endif
