/* ------------------------------------------------------------------   */
/*      item            : AirspeedTapeData.hxx
        from template   : DataInterface.hxx
        template made by: Joost Ellerbroek
        category        : header file
        template changes: 081016 first version
        language        : C++
*/

#ifndef AirspeedTapeData_hxx
#define AirspeedTapeData_hxx
#include <Link.hxx>
using namespace hmi;

// Includes and/or defines for custom types


/// AirspeedTapeData DataInterface
class AirspeedTapeData
{
public:// Data elements
Link<float> Vias;
Link<float> Vtas;
Link<float> Vc_gamma_max;
Link<float> speed_target;
Link<float> Vmin;
Link<float> Vmax;
Link<int> curVerticalState;
Link<float> vtasdot;
Link<bool> clogged_pt;
Link<bool> clogged_sp;
Link<bool> ADC_failure;
Link<float> altitude;
Link<float> dt;


public:
  /** Constructor */
  AirspeedTapeData();

  /** Destructor */
  ~AirspeedTapeData();
};

#endif
