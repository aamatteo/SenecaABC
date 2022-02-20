/* ------------------------------------------------------------------   */
/*      item            : RadioBlockData.hxx
        from template   : DataInterface.hxx
        template made by: Joost Ellerbroek
        category        : header file
        template changes: 081016 first version
        language        : C++
*/

#ifndef RadioBlockData_hxx
#define RadioBlockData_hxx
#include <Link.hxx>
using namespace hmi;

// Includes and/or defines for custom types
#include <iostream>


/// RadioBlockData DataInterface
class RadioBlockData
{
public:// Data elements
Link<bool> ap_hdghold_mode;
Link<bool> ap_althold_mode;
Link<bool> ap_hdghold_transition;
Link<bool> ap_althold_transition;
Link<float> dme;
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
Link<int> active_nav_source;
Link<int> vnav_situation;
Link<float> brg;
Link<int> alts_flash_state;
Link<int> alt_flash_state;
Link<bool> ADC_failure;
Link<bool> VOR_failure;
Link<bool> PFD_failure;
Link<std::string> fp_name;
Link<int> active_leg;


public:
  /** Constructor */
  RadioBlockData();

  /** Destructor */
  ~RadioBlockData();
};

#endif
