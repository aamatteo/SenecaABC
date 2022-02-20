/* ------------------------------------------------------------------   */
/*      item            : MFDGaugeData.hxx
        from template   : DataInterface.hxx
        template made by: Joost Ellerbroek
        category        : header file
        template changes: 081016 first version
        language        : C++
*/

#ifndef MFDGaugeData_hxx
#define MFDGaugeData_hxx
#include <Link.hxx>
using namespace hmi;

// Includes and/or defines for custom types
#include <iostream>


/// MFDGaugeData DataInterface
class MFDGaugeData
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
DataHolder<float> deviation;
DataHolder<float> offset;
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
DataHolder<float> x;
DataHolder<float> y;
DataHolder<int> active_nav_source;
DataHolder<float> brg;
DataHolder<float> dtk;
DataHolder<int> active_leg;
DataHolder<int> active_vnv_leg;
DataHolder<float> dist_to_top;
DataHolder<float> time_to_bod;
DataHolder<bool> GPS_failure;
DataHolder<bool> VOR_failure;
DataHolder<float> map_left;
DataHolder<float> map_right;
DataHolder<float> dt;
DataHolder<std::string> fp_name;
DataHolder<bool> mouse_left;
DataHolder<int> mouse_x;
DataHolder<int> mouse_y;
DataHolder<bool> fpl_page;
DataHolder<int> msg;
DataHolder<int> range;
DataHolder<float> fpa_req;


public:
  /** Constructor */
  MFDGaugeData();

  /** Destructor */
  ~MFDGaugeData();
};

#endif
