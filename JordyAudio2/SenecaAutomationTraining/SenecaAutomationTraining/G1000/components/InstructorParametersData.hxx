/* ------------------------------------------------------------------   */
/*      item            : InstructorParametersData.hxx
        from template   : DataInterface.hxx
        template made by: Joost Ellerbroek
        category        : header file
        template changes: 081016 first version
        language        : C++
*/

#ifndef InstructorParametersData_hxx
#define InstructorParametersData_hxx
#include <Link.hxx>
using namespace hmi;

// Includes and/or defines for custom types


/// InstructorParametersData DataInterface
class InstructorParametersData
{
public:// Data elements
Link<bool> show_instructor;
Link<float> fuel_left;
Link<float> fuel_right;
Link<float> height;
Link<float> min_height;


public:
  /** Constructor */
  InstructorParametersData();

  /** Destructor */
  ~InstructorParametersData();
};

#endif
