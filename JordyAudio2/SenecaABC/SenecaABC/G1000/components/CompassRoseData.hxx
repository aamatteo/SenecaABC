/* ------------------------------------------------------------------   */
/*      item            : CompassRoseData.hxx
        from template   : DataInterface.hxx
        template made by: Joost Ellerbroek
        category        : header file
        template changes: 081016 first version
        language        : C++
*/

#ifndef CompassRoseData_hxx
#define CompassRoseData_hxx
#include <Link.hxx>
using namespace hmi;

// Includes and/or defines for custom types


/// CompassRoseData DataInterface
class CompassRoseData
{
public:// Data elements
Link<float> heading;
Link<float> track;
Link<float> hdg_bug;
Link<float> course;
Link<int> active_nav_source;
Link<float> turn_rate;
Link<bool> GMU_failure;


public:
  /** Constructor */
  CompassRoseData();

  /** Destructor */
  ~CompassRoseData();
};

#endif
