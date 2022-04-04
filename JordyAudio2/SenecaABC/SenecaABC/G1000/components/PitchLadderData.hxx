/* ------------------------------------------------------------------   */
/*      item            : PitchLadderData.hxx
        from template   : DataInterface.hxx
        template made by: Joost Ellerbroek
        category        : header file
        template changes: 081016 first version
        language        : C++
*/

#ifndef PitchLadderData_hxx
#define PitchLadderData_hxx
#include <Link.hxx>
using namespace hmi;

// Includes and/or defines for custom types


/// PitchLadderData DataInterface
class PitchLadderData
{
public:// Data elements
Link<float> pitch;
Link<float> roll;
Link<float> dummy;


public:
  /** Constructor */
  PitchLadderData();

  /** Destructor */
  ~PitchLadderData();
};

#endif
