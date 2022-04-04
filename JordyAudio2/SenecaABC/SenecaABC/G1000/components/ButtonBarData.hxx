/* ------------------------------------------------------------------   */
/*      item            : ButtonBarData.hxx
        from template   : DataInterface.hxx
        template made by: Joost Ellerbroek
        category        : header file
        template changes: 081016 first version
        language        : C++
*/

#ifndef ButtonBarData_hxx
#define ButtonBarData_hxx
#include <Link.hxx>
using namespace hmi;

// Includes and/or defines for custom types
#include <iostream>


/// ButtonBarData DataInterface
class ButtonBarData
{
public:// Data elements
Link<float> x;
Link<float> y;
Link<float> dme_status;
Link<std::string> fp_name;
Link<float> altitude;
Link<bool> ADC_failure;


public:
  /** Constructor */
  ButtonBarData();

  /** Destructor */
  ~ButtonBarData();
};

#endif
