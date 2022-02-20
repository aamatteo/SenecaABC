/* ------------------------------------------------------------------   */
/*      item            : ClimbPerformanceData.hxx
        from template   : DataInterface.hxx
        template made by: Joost Ellerbroek
        category        : header file
        template changes: 081016 first version
        language        : C++
*/

#ifndef ClimbPerformanceData_hxx
#define ClimbPerformanceData_hxx
#include <Link.hxx>
using namespace hmi;

// Includes and/or defines for custom types


/// ClimbPerformanceData DataInterface
class ClimbPerformanceData
{
public:// Data elements
Link<float> pitch;
Link<float> roll;
Link<bool> performance_data_valid;
Link<float> gamma_max;
Link<float> gamma_max_full_thrust;


public:
  /** Constructor */
  ClimbPerformanceData();

  /** Destructor */
  ~ClimbPerformanceData();
};

#endif
