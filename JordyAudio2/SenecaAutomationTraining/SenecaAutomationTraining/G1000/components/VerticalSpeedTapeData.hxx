/* ------------------------------------------------------------------   */
/*      item            : VerticalSpeedTapeData.hxx
        from template   : DataInterface.hxx
        template made by: Joost Ellerbroek
        category        : header file
        template changes: 081016 first version
        language        : C++
*/

#ifndef VerticalSpeedTapeData_hxx
#define VerticalSpeedTapeData_hxx
#include <Link.hxx>
using namespace hmi;

// Includes and/or defines for custom types


/// VerticalSpeedTapeData DataInterface
class VerticalSpeedTapeData
{
public:// Data elements
Link<float> hdot;
Link<float> target_vs;
Link<int> curVerticalState;
Link<float> Vtas;
Link<bool> ADC_failure;
Link<bool> clogged_sp;
Link<float> dt;


public:
  /** Constructor */
  VerticalSpeedTapeData();

  /** Destructor */
  ~VerticalSpeedTapeData();
};

#endif
