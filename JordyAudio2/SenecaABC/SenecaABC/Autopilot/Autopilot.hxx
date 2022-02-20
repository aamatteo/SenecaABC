/* ------------------------------------------------------------------   */
/*      item            : Autopilot.hxx
        made by         : jordy
	from template   : DusimeModuleTemplate.hxx
        template made by: Rene van Paassen
        date            : Sun Mar 22 10:58:09 2020
	category        : header file
        description     :
	changes         : Sun Mar 22 10:58:09 2020 first version
	template changes: 030401 RvP Added template creation comment
        language        : C++
        copyright       : (c) 2016 TUDelft-AE-C&S
*/

#ifndef Autopilot_hxx
#define Autopilot_hxx

// include the dusime header
#include <dusime.h>
USING_DUECA_NS;

// This includes headers for the objects that are sent over the channels
#include "comm-objects.h"
#include "StatesOutputs.h"
// include headers for functions/classes you need in the module
#include <map>
#include <initializer_list>

#include <Eigen/Dense>
using namespace Eigen;
using Eigen::MatrixXd;
/** A module.

    The instructions to create an module of this class from the Scheme
    script are:

    \verbinclude autopilot.scm
*/


class Autopilot: public SimulationModule
{
  /** self-define the module type, to ease writing the parameter table */
  typedef Autopilot _ThisModule_;

private: // simulation data
  // declare the data you need in your simulation

  MatrixXd STMvertical;
  MatrixXd STMlateral;

  Vector2d pos;
  Vector2d start;
  Vector2d finish;

  Vector2d vnv_start;
  Vector2d vnv_finish;
  Vector2d vnv_next_wp;

  int APstate;
  bool ap_disengaged;
  bool ap_on;
  bool fd_on;
  float t;
  float de;
  float da;
  float dr;

  float theta;
  float theta_ref;
  float theta_old;
  float theta_error;
  float theta_roll_addendum;
  float q;
  float q_ref;
  float q_old;
  float q_error;
  float q_int;
  float theta_ref_loop;
  float theta_ref_old;
  float theta_ref_command;
  float theta_ref_pit;

  float phi;
  float phi_old;
  float phi_ref;
  float phi_error;
  float p;
  float p_ref;
  float p_old;
  float p_error;
  float p_int;
  float phi_ref_loop;
  float phi_ref_old;
  float phi_ref_command;
  float phi_ref_rol;

  float beta;
  float beta_error;
  float r;
  float r_ref;
  float r_error;

  float Vtas;
  float VtasSBY;
  float alpha;
  float VSref;
  float VS;
  float VS_roll_addendum;
  float phi_abs;

  float alt;
  float alt_ref;
  float alt_old;
  float alt_error;

  int V_ref;
  float V_error;
  float V_old;

  float hdg;
  float hdg_error_old;
  float hdg_error;
  float hdg_select_old;
  float hdg_int;

  uint32_t msg;
  int curStateVertical;
  int prevStateVertical;
  int curStateLateral;
  int prevStateLateral;
  float alt_select_input;
  float alt_select;
  float hdg_select;
  bool Vswitched;
  bool Lswitched;
  bool changed_to_alt_captured;
  bool need_update;
  bool reset_hdg;

  float ap_flash_timer;
  float pit_flash_timer;
  float rol_flash_timer;
  bool ap_flash;
  bool pit_flash;
  bool rol_flash;

  float x;
  float y;
  float nav_d;
  float nav_R;
  float nav_beta;
  float nav_direct;
  float nav_total_radial;
  float nav_extension;
  float nav_p3x;
  float nav_p3y;
  float nav_alpha;
  float hdg_ref;
  float hdg_ref_old;
  int active_nav_source;
  float course;
  float nav_alpha_true;
  float needle_deviation;
  float dist_to_top;
  float dtk;

  float de_old;

  float crs_select;

  int active_leg;
  int active_vnv_leg;
  float gps_dist;
  bool update_hsi;

  float dx;
  float alt_v;
  int vnav_situation;
  int iter_wps;
  float distance_to_next_vnv;
  float time_to_bod;
  bool switch_to_vpth;
  float alt_v_until_switch;

  float theta_at_switch;
  float VS_at_switch;

  int alts_flash_state;
  int alt_flash_state;
  float alts_flash_timer;
  float alt_flash_timer;

  float timer;

  bool GPS_failure;
  bool VOR_failure;
  bool ADC_failure;
  bool PFD_failure;
  bool GMU_failure;
  bool HSI_failure;
  bool AFCS_pit;
  bool AFCS_rol;
  bool clogged_sp;
  bool clogged_pt;
  bool prev_PFD_failure;

  bool prev_clogged_pt;;
  float pressure_1;
  float pressure_2;
  float pressure_3;
  float pressure_4;
  float q1;
  float dp;

  bool prev_GPS_failure;
  float frozen_x;
  float frozen_y;
  float frozen_vs;

  bool prev_clogged_sp;
  float frozen_altitude;

  float ude;
  float ude_old;
  float uda;
  float uda_old;
  float da_old;
  float Tservo;

  std::string fp_filename;
  std::string fp_prev_file_name;
  std::string fp_comment;
  int nr_of_wp;
  MatrixXd fp_location;
  std::vector<std::string> wp_names;
  std::string fp_wp;
  float fp_lat;
  float fp_lon;
  float fp_alt;
  std::string dummy_string;
  float nav_dtk;
  float delta_x;
  float delta_y;

  float vor1_x;
  float vor1_y;
  float vor2_x;
  float vor2_y;
  bool use_vor1;
  bool use_vor2;

  float curveRadius;

  float prev_nav_R;
  bool vor_flag_state;
  bool prev_vor_flag_state;

  float needleOffset;
  float prevNeedleOffset;
  float HSItimeConstant;
  float prevCourse;
  int prev_nav_source;
  bool switchToVor;
  float prev_crs_select;

  float fpa_req;
  float phi_rate1;



public:
  void update_G1000(int APstate, int ap_vertical, int ap_lateral,
        int ap_armed, float target_alt, float alt_hold, float target_speed,
        float hdg_bug, float target_vs, bool ap_flash, bool pit_flash,
        bool rol_flash,int active_nav_source, float course, int vnav_situation,
        float alt_v,int active_leg, int alts_flash_state, int alt_flash_state,
        bool vor_flag_state);

  float calc_p(float h);

  float getCurveRadius(Eigen::Vector2d A, Eigen::Vector2d B, Eigen::Vector2d C, float r);
  float getAngle(Eigen::Vector2d A, Eigen::Vector2d B, Eigen::Vector2d C);
  Eigen::Vector2d getMid(Eigen::Vector2d A, Eigen::Vector2d B, float abc, float r);



private: // trim calculation data
  // declare the trim calculation data needed for your simulation

private: // snapshot data
  // declare, if you need, the room for placing snapshot data

private: // channel access
  // declare access tokens for all the channels you read and write
  // examples:
  // ChannelReadToken    r_mytoken;
  // ChannelWriteToken   w_mytoken;
  StreamChannelReadToken<CitationOutput> in_token;
  StreamChannelWriteToken<AutopilotChannel> ap_token;
  EventChannelReadToken<GFC700Event> gfcr_token;
  EventChannelReadToken<FailureEvent> fail_token;
  EventChannelReadToken<APIncoEvent> apinco_token;
  EventChannelWriteToken<AP2G1000Channel> ap2g_token;
  StreamChannelReadToken<PrimarySwitches> *ps_token;

private: // activity allocation
  /** You might also need a clock. Don't mis-use this, because it is
      generally better to trigger on the incoming channels */
  PeriodicAlarm        myclock;

  /** Callback object for simulation calculation. */
  Callback<Autopilot>  cb1;

  /** Activity for simulation calculation. */
  ActivityCallback      do_calc;

public: // class name and trim/parameter tables
  /** Name of the module. */
  static const char* const           classname;

  /** Return the initial condition table. */
  static const IncoTable*            getMyIncoTable();

  /** Return the parameter table. */
  static const ParameterTable*       getMyParameterTable();

public: // construction and further specification
  /** Constructor. Is normally called from scheme/the creation script. */
  Autopilot(Entity* e, const char* part, const PrioritySpec& ts);

  /** Continued construction. This is called after all script
      parameters have been read and filled in, according to the
      parameter table. Your running environment, e.g. for OpenGL
      drawing, is also prepared. Any lengty initialisations (like
      reading the 4 GB of wind tables) should be done here.
      Return false if something in the parameters is wrong (by
      the way, it would help if you printed what!) May be deleted. */
  bool complete();

  /** Destructor. */
  ~Autopilot();

  // add here the member functions you want to be called with further
  // parameters. These are then also added in the parameter table
  // The most common one (addition of time spec) is given here.
  // Delete if not needed!

  /** Specify a time specification for the simulation activity. */
  bool setTimeSpec(const TimeSpec& ts);

  /** Request check on the timing. */
  bool checkTiming(const vector<int>& i);

  bool use_column;

public: // member functions for cooperation with DUECA
  /** indicate that everything is ready. */
  bool isPrepared();

  /** start responsiveness to input data. */
  void startModule(const TimeSpec &time);

  /** stop responsiveness to input data. */
  void stopModule(const TimeSpec &time);

public: // the member functions that are called for activities
  /** the method that implements the main calculation. */
  void doCalculation(const TimeSpec& ts);

public: // member functions for cooperation with DUSIME
  /** For the Snapshot capability, fill the snapshot "snap" with the
      data saved at a point in your simulation (if from_trim is false)
      or with the state data calculated in the trim calculation (if
      from_trim is true). */
  void fillSnapshot(const TimeSpec& ts,
		    Snapshot& snap, bool from_trim);

  /** Restoring the state of the simulation from a snapshot. */
  void loadSnapshot(const TimeSpec& t, const Snapshot& snap);

  /** Perform a trim calculation. Should NOT use current state
      uses event channels parallel to the stream data channels,
      calculates, based on the event channel input, the steady state
      output. */
  void trimCalculation(const TimeSpec& ts, const TrimMode& mode);
};

#endif
