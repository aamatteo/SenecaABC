/* ------------------------------------------------------------------   */
/*      item            : LeftBarData.hxx
        from template   : DataInterface.hxx
        template made by: Joost Ellerbroek
        category        : header file
        template changes: 081016 first version
        language        : C++
*/

#ifndef LeftBarData_hxx
#define LeftBarData_hxx
#include <Link.hxx>
using namespace hmi;

// Includes and/or defines for custom types


/// LeftBarData DataInterface
class LeftBarData
{
public:// Data elements
Link<bool> mouse_left;
Link<int> mouse_x;
Link<int> mouse_y;
Link<int> GFC_msg;
Link<bool> dme_animation;
Link<bool> sync_animation;


public:
  /** Constructor */
  LeftBarData();

  /** Destructor */
  ~LeftBarData();
};

#endif
