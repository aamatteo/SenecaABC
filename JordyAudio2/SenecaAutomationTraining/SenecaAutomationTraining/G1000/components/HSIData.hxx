/* ------------------------------------------------------------------   */
/*      item            : HSIData.hxx
        from template   : DataInterface.hxx
        template made by: Joost Ellerbroek
        category        : header file
        template changes: 081016 first version
        language        : C++
*/

#ifndef HSIData_hxx
#define HSIData_hxx
#include <Link.hxx>
using namespace hmi;

// Includes and/or defines for custom types
#include <iostream>


/// HSIData DataInterface
class HSIData
{
public:// Data elements
Link<float> heading;
Link<float> dme;
Link<float> course;
Link<float> deviation;
Link<float> offset;
Link<float> needle_deviation;
Link<int> active_nav_source;
Link<bool> VOR_failure;
Link<bool> HSI_failure;
Link<bool> GMU_failure;
Link<bool> AFCS_rol;
Link<bool> vor_flag_state;
Link<std::string> fp_name;


public:
  /** Constructor */
  HSIData();

  /** Destructor */
  ~HSIData();
};

#endif
