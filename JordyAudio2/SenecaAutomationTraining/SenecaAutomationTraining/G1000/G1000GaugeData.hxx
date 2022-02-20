/* ------------------------------------------------------------------   */
/*      item            : G1000GaugeData.hxx
        from template   : DataInterface.hxx
        template made by: Joost Ellerbroek
        category        : header file
        template changes: 081016 first version
        language        : C++
*/

#ifndef G1000GaugeData_hxx
#define G1000GaugeData_hxx
#include <Link.hxx>
using namespace hmi;

// Includes and/or defines for custom types
#include <iostream>


/// G1000GaugeData DataInterface
class G1000GaugeData
{
public:// Data elements
  /// The pitch angle in radians
  DataHolder<float> pitch;
  /// The roll angle in radians
  DataHolder<float> roll;
  /// The heading angle in radians
  DataHolder<float> heading;
  /// The flight path angle in radians
  DataHolder<float> gamma;
  /// The track angle in radians
  DataHolder<float> chi;
  /// The altitude in m
  DataHolder<float> altitude;
  /// The rate of climb in m/s
  DataHolder<float> hdot;
  /// The indicated airspeed in m/s
  DataHolder<float> Vias;
  /// The true airspeed in m/s
  DataHolder<float> Vtas;
DataHolder<float> Y_fycg;
DataHolder<float> vtasdot;
DataHolder<float> x;
DataHolder<float> y;
  /// Some engine data
  DataHolder<float> n1_left;
DataHolder<float> n1_right;
DataHolder<float> n2_left;
DataHolder<float> n2_right;
DataHolder<float> itt_left;
DataHolder<float> itt_right;
DataHolder<float> rpm_left;
DataHolder<float> rpm_right;
DataHolder<float> tl_left;
DataHolder<float> tl_right;
DataHolder<int> gear;
  /// AP Targets
  DataHolder<float> altitude_target;
DataHolder<float> speed_target;
DataHolder<float> Vmin;
DataHolder<float> Vmax;
  /// Performance data
  DataHolder<bool> performance_data_valid;
DataHolder<float> Vc_gamma_max;
DataHolder<float> gamma_max;
DataHolder<float> gamma_max_full_thrust;
  /// Nav radio data
  DataHolder<float> dme;
DataHolder<float> course;
DataHolder<float> trueCourse;
DataHolder<float> deviation;
DataHolder<float> offset;
DataHolder<int> dme_status;
  /// Trim throttle calibration
  DataHolder<bool> trim_enabled;
  /// A trim value [-1,0,1]
  DataHolder<int> trim;
  /// Auto pilot data
  DataHolder<bool> ap_hdghold_mode;
DataHolder<bool> ap_althold_mode;
DataHolder<bool> ap_hdghold_transition;
DataHolder<bool> ap_althold_transition;
DataHolder<bool> crashed;
DataHolder<bool> fullscreen;
  /// Instructor data
  DataHolder<bool> show_instructor;
DataHolder<float> height;
DataHolder<float> min_height;
  /// Autopilot states
  DataHolder<int> curVerticalState;
DataHolder<int> curLateralState;
DataHolder<int> ap_armed;
DataHolder<int> APstate;
DataHolder<float> hdg_bug;
DataHolder<float> target_vs;
DataHolder<float> target_speed;
DataHolder<float> alt_hold;
DataHolder<bool> ap_flash;
DataHolder<bool> pit_flash;
DataHolder<bool> rol_flash;
DataHolder<float> theta_ref;
DataHolder<float> phi_ref;
DataHolder<int> active_nav_source;
DataHolder<float> needle_deviation;
DataHolder<int> vnav_situation;
DataHolder<float> brg;
DataHolder<float> altitude_target_vnav;
DataHolder<float> nav_R;
DataHolder<float> vnav_R;
DataHolder<float> turn_rate;
DataHolder<int> alts_flash_state;
DataHolder<int> alt_flash_state;
DataHolder<bool> vor_flag_state;
  /// Failure modes
  DataHolder<bool> GPS_failure;
DataHolder<bool> VOR_failure;
DataHolder<bool> ADC_failure;
DataHolder<bool> PFD_failure;
DataHolder<bool> GMU_failure;
DataHolder<bool> HSI_failure;
DataHolder<bool> AFCS_pit;
DataHolder<bool> AFCS_rol;
DataHolder<bool> clogged_sp;
DataHolder<bool> clogged_pt;
DataHolder<float> map_left;
DataHolder<float> map_right;
DataHolder<std::string> fp_name;
DataHolder<bool> mouse_left;
DataHolder<bool> mouse_down;
DataHolder<int> GFC_msg;
DataHolder<int> mouse_x;
DataHolder<int> mouse_y;
DataHolder<float> dt;
DataHolder<bool> dme_animation;
DataHolder<bool> sync_animation;
DataHolder<int> active_leg;


public:
  /** Constructor */
  G1000GaugeData();

  /** Destructor */
  ~G1000GaugeData();
};

#endif
