/* ------------------------------------------------------------------   */
/*      item            : AircraftReferenceData.hxx
        from template   : DataInterface.hxx
        template made by: Joost Ellerbroek
        category        : header file
        template changes: 081016 first version
        language        : C++
*/

#ifndef AircraftReferenceData_hxx
#define AircraftReferenceData_hxx
#include <Link.hxx>
using namespace hmi;

// Includes and/or defines for custom types


/// AircraftReferenceData DataInterface
class AircraftReferenceData
{
public:// Data elements
Link<int> dummy;
Link<float> pitch;
Link<float> roll;
Link<float> theta_ref;
Link<float> phi_ref;
Link<int> APstate;


public:
  /** Constructor */
  AircraftReferenceData();

  /** Destructor */
  ~AircraftReferenceData();
};

#endif
