/* ------------------------------------------------------------------   */
/*      item            : AltitudeTapeData.hxx
        from template   : DataInterface.hxx
        template made by: Joost Ellerbroek
        category        : header file
        template changes: 081016 first version
        language        : C++
*/

#ifndef AltitudeTapeData_hxx
#define AltitudeTapeData_hxx
#include <Link.hxx>
using namespace hmi;

// Includes and/or defines for custom types


/// AltitudeTapeData DataInterface
class AltitudeTapeData
{
public:// Data elements
Link<float> altitude;
Link<float> altitude_target;
Link<int> curVerticalState;
Link<float> altitude_target_vnav;
Link<float> nav_R;
Link<float> vnav_R;
Link<float> hdot;
Link<bool> ADC_failure;
Link<bool> clogged_sp;


public:
  /** Constructor */
  AltitudeTapeData();

  /** Destructor */
  ~AltitudeTapeData();
};

#endif
