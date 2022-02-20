/* ------------------------------------------------------------------   */
/*      item            : InstructorParameters.hxx
        made by         : jcomans
        from template   : hmigauge.hxx
        template made by: Joost Ellerbroek
        date            : 081013
        category        : header file
        description     : 
        changes         : 081013 first version
        language        : C++
*/

#ifndef InstructorParameters_hxx
#define InstructorParameters_hxx

#include <GaugeComponent.hxx>
#include "InstructorParametersData.hxx"

// All the hmilib classes are defined in the hmi namespace
using namespace hmi;

/** hmiGauge GL display Gauge component
*/
class InstructorParameters: public GaugeComponent
{
private:// Member data
  // Data interface object (defined in InstructorParametersData.if)
  InstructorParametersData data;

  // Your other member data here

public:// Construction / Destruction
  /// Constructor
  InstructorParameters();

  /// Destructor
  ~InstructorParameters();

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
  InstructorParametersData& GetData() {return data;}

  

};

#endif
