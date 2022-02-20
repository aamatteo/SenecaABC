/* ------------------------------------------------------------------   */
/*      item            : FlightPathVectorData.hxx
        from template   : DataInterface.hxx
        template made by: Joost Ellerbroek
        category        : header file
        template changes: 081016 first version
        language        : C++
*/

#ifndef FlightPathVectorData_hxx
#define FlightPathVectorData_hxx
#include <Link.hxx>
using namespace hmi;

// Includes and/or defines for custom types


/// FlightPathVectorData DataInterface
class FlightPathVectorData
{
public:// Data elements
Link<float> pitch;
Link<float> roll;
Link<float> heading;
Link<float> gamma;
Link<float> chi;


public:
  /** Constructor */
  FlightPathVectorData();

  /** Destructor */
  ~FlightPathVectorData();
};

#endif
