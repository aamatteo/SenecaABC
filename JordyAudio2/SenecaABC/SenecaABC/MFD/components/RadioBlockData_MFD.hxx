/* ------------------------------------------------------------------   */
/*      item            : RadioBlockData_MFD.hxx
        from template   : DataInterface.hxx
        template made by: Joost Ellerbroek
        category        : header file
        template changes: 081016 first version
        language        : C++
*/

#ifndef RadioBlockData_MFD_hxx
#define RadioBlockData_MFD_hxx
#include <Link.hxx>
using namespace hmi;

// Includes and/or defines for custom types
#include <iostream>


/// RadioBlockData_MFD DataInterface
class RadioBlockData_MFD
{
public:// Data elements
Link<bool> ap_hdghold_mode;
Link<bool> ap_althold_mode;
Link<bool> ap_hdghold_transition;
Link<bool> ap_althold_transition;
Link<float> course;
Link<int> curVerticalState;
Link<int> curLateralState;
Link<int> APstate;
Link<float> altitude_target;
Link<float> target_vs;
Link<float> hdg_bug;
Link<int> ap_armed;
Link<float> target_speed;
Link<float> alt_hold;
Link<bool> ap_flash;
Link<bool> pit_flash;
Link<bool> rol_flash;
Link<float> brg;
Link<float> trk;
Link<float> dtk;
Link<float> dme;
Link<float> Vtas;
Link<float> x;
Link<float> y;
Link<int> active_nav_source;
Link<bool> VOR_failure;
Link<std::string> fp_name;
Link<bool> fpl_page;
Link<int> msg;
Link<float> dt;


public:
  /** Constructor */
  RadioBlockData_MFD();

  /** Destructor */
  ~RadioBlockData_MFD();
};

#endif
