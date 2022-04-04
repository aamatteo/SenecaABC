/* ------------------------------------------------------------------   */
/*      item            : MapData.hxx
        from template   : DataInterface.hxx
        template made by: Joost Ellerbroek
        category        : header file
        template changes: 081016 first version
        language        : C++
*/

#ifndef MapData_hxx
#define MapData_hxx
#include <Link.hxx>
using namespace hmi;

// Includes and/or defines for custom types
#include <iostream>


/// MapData DataInterface
class MapData
{
public:// Data elements
Link<float> x;
Link<float> y;
Link<float> lat;
Link<float> lon;
Link<float> heading;
Link<int> active_leg;
Link<int> active_vnv_leg;
Link<bool> GPS_failure;
Link<std::string> fp_name;
Link<bool> fpl_page;
Link<float> Vtas;
Link<float> dist_to_top;
Link<float> time_to_bod;
Link<int> curVerticalState;
Link<int> msg;
Link<int> range;
Link<float> altitude;
Link<float> fpa_req;
Link<float> dt;


public:
  /** Constructor */
  MapData();

  /** Destructor */
  ~MapData();
};

#endif
