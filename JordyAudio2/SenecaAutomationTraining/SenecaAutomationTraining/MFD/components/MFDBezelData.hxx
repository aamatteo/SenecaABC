/* ------------------------------------------------------------------   */
/*      item            : MFDBezelData.hxx
        from template   : DataInterface.hxx
        template made by: Joost Ellerbroek
        category        : header file
        template changes: 081016 first version
        language        : C++
*/

#ifndef MFDBezelData_hxx
#define MFDBezelData_hxx
#include <Link.hxx>
using namespace hmi;

// Includes and/or defines for custom types


/// MFDBezelData DataInterface
class MFDBezelData
{
public:// Data elements
Link<bool> dummy;


public:
  /** Constructor */
  MFDBezelData();

  /** Destructor */
  ~MFDBezelData();
};

#endif
