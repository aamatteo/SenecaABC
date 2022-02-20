/* ------------------------------------------------------------------   */
/*      item            : BankIndicatorData.hxx
        from template   : DataInterface.hxx
        template made by: Joost Ellerbroek
        category        : header file
        template changes: 081016 first version
        language        : C++
*/

#ifndef BankIndicatorData_hxx
#define BankIndicatorData_hxx
#include <Link.hxx>
using namespace hmi;

// Includes and/or defines for custom types


/// BankIndicatorData DataInterface
class BankIndicatorData
{
public:// Data elements
Link<float> roll;
Link<float> Y_fycg;


public:
  /** Constructor */
  BankIndicatorData();

  /** Destructor */
  ~BankIndicatorData();
};

#endif
