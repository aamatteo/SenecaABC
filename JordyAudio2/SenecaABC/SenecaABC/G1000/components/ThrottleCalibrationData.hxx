/* ------------------------------------------------------------------   */
/*      item            : ThrottleCalibrationData.hxx
        from template   : DataInterface.hxx
        template made by: Joost Ellerbroek
        category        : header file
        template changes: 081016 first version
        language        : C++
*/

#ifndef ThrottleCalibrationData_hxx
#define ThrottleCalibrationData_hxx
#include <Link.hxx>
using namespace hmi;

// Includes and/or defines for custom types


/// ThrottleCalibrationData DataInterface
class ThrottleCalibrationData
{
public:// Data elements
Link<bool> enabled;
Link<float> tl_left;
Link<float> tl_right;
Link<int> gear;
Link<float> altitude;


public:
  /** Constructor */
  ThrottleCalibrationData();

  /** Destructor */
  ~ThrottleCalibrationData();
};

#endif
