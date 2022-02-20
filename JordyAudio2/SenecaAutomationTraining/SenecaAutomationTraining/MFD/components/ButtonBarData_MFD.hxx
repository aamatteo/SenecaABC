/* ------------------------------------------------------------------   */
/*      item            : ButtonBarData_MFD.hxx
        from template   : DataInterface.hxx
        template made by: Joost Ellerbroek
        category        : header file
        template changes: 081016 first version
        language        : C++
*/

#ifndef ButtonBarData_MFD_hxx
#define ButtonBarData_MFD_hxx
#include <Link.hxx>
using namespace hmi;

// Includes and/or defines for custom types


/// ButtonBarData_MFD DataInterface
class ButtonBarData_MFD
{
public:// Data elements
Link<int> example_var;


public:
  /** Constructor */
  ButtonBarData_MFD();

  /** Destructor */
  ~ButtonBarData_MFD();
};

#endif
