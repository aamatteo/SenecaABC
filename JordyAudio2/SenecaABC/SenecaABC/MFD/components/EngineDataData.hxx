/* ------------------------------------------------------------------   */
/*      item            : EngineDataData.hxx
        from template   : DataInterface.hxx
        template made by: Joost Ellerbroek
        category        : header file
        template changes: 081016 first version
        language        : C++
*/

#ifndef EngineDataData_hxx
#define EngineDataData_hxx
#include <Link.hxx>
using namespace hmi;

// Includes and/or defines for custom types


/// EngineDataData DataInterface
class EngineDataData
{
public:// Data elements
Link<float> n1_left;
Link<float> n1_right;
Link<float> n2_left;
Link<float> n2_right;
Link<float> itt_left;
Link<float> itt_right;
Link<float> rpm_left;
Link<float> rpm_right;
Link<float> tl_left;
Link<float> tl_right;
Link<float> altitude;
Link<float> map_left;
Link<float> map_right;
Link<float> dt;
Link<int> lgear;
Link<int> ngear;
Link<int> rgear;


public:
  /** Constructor */
  EngineDataData();

  /** Destructor */
  ~EngineDataData();
};

#endif
