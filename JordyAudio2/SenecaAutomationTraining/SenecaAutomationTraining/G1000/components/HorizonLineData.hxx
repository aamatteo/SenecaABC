/* ------------------------------------------------------------------   */
/*      item            : HorizonLineData.hxx
        from template   : DataInterface.hxx
        template made by: Joost Ellerbroek
        category        : header file
        template changes: 081016 first version
        language        : C++
*/

#ifndef HorizonLineData_hxx
#define HorizonLineData_hxx
#include <Link.hxx>
using namespace hmi;

// Includes and/or defines for custom types


/// HorizonLineData DataInterface
class HorizonLineData
{
public:// Data elements
Link<float> pitch;
Link<float> roll;


public:
  /** Constructor */
  HorizonLineData();

  /** Destructor */
  ~HorizonLineData();
};

#endif
