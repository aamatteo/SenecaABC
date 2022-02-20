/* ------------------------------------------------------------------   */
/*      item            : HorizonFieldsData.hxx
        from template   : DataInterface.hxx
        template made by: Joost Ellerbroek
        category        : header file
        template changes: 081016 first version
        language        : C++
*/

#ifndef HorizonFieldsData_hxx
#define HorizonFieldsData_hxx
#include <Link.hxx>
using namespace hmi;

// Includes and/or defines for custom types


/// HorizonFieldsData DataInterface
class HorizonFieldsData
{
public:// Data elements
Link<float> pitch;
Link<float> roll;


public:
  /** Constructor */
  HorizonFieldsData();

  /** Destructor */
  ~HorizonFieldsData();
};

#endif
