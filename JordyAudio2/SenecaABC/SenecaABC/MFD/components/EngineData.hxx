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

#ifndef EngineData_hxx
#define EngineData_hxx

#include <GaugeComponent.hxx>
#include "EngineDataData.hxx"
#include <iostream>
#include <string>

// All the hmilib classes are defined in the hmi namespace
using namespace hmi;

/** hmiGauge GL display Gauge component
*/
class EngineData: public GaugeComponent
{
private:// Member data
  // Data interface object (defined in EngineDataData.if)
  EngineDataData data;
  float rpm_needle_left;
  float rpm_needle_right;
  float man_needle_left;
  float man_needle_right;

  void draw_bar(float y_value, std::string &txt, bool draw_ticks, float green_l, float green_r, float red_l, float red_r, float x_l, float x_r);

  // Your other member data here

public:// Construction / Destruction
  /// Constructor
  EngineData();

  /// Destructor
  ~EngineData();

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
  EngineDataData& GetData() {return data;}

};

#endif
