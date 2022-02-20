/* ------------------------------------------------------------------   */
/*      item            : ECI.hxx
        made by         : Peter van Oorschot
	from template   : DusimeModuleTemplate.hxx
        template made by: Rene van Paassen
        date            : Tue Feb 28 14:58:16 2017
	category        : header file
        description     :
	changes         : Tue Feb 28 14:58:16 2017 first version
	template changes: 030401 RvP Added template creation comment
        language        : C++
        copyright       : (c) 2016 TUDelft-AE-C&S
*/

#ifndef ECI_hxx
#define ECI_hxx

#define SET_LABEL_TEXT(IN,OUT) sprintf(tmp_txt,"%3.1f",IN); gtk_label_set_text( GTK_LABEL(OUT), tmp_txt );
#define SET_LABEL_TEXT_2(IN,OUT) sprintf(tmp_txt,"%3.2f",IN); gtk_label_set_text( GTK_LABEL(OUT), tmp_txt );
#define SET_LABEL_TEXT_ROUND(IN,OUT) sprintf(tmp_txt,"%3.0f",IN); gtk_label_set_text( GTK_LABEL(OUT), tmp_txt );
#define GET_SCENARIO_SETTING(TYPE,VAR) else if (var==#VAR) VAR = boost::lexical_cast<TYPE>(value);
//TODO #define GET_SCENARIO_TRIGGER(TYPE,VAR,NAME) else if (var==#NAME) VAR = boost::lexical_cast<TYPE>(value);
#define ACTIVATE_SCENARIO_SETTING(VAR,NAME) else if (var==#NAME) VAR = true;

// include the dusime header
#include <dusime.h>
USING_DUECA_NS;

// This includes headers for the objects that are sent over the channels
#include "comm-objects.h"

// Seneca model data
#include "StatesOutputs.h"

// include headers for functions/classes you need in the module
#include <GtkGladeWindow.hxx>

// STD strings.
#include <string>


/** A module.

    The instructions to create an module of this class from the Scheme
    script are:

    \verbinclude eci.scm
*/
class ECI: public SimulationModule
{
  /** self-define the module type, to ease writing the parameter table */
  typedef ECI _ThisModule_;

private: // simulation data
	// declare the data you need in your simulation
	SimulationState prev_state;
	double dt, stopwatch;
	TimeTickType run_start;
	float pa34_v, pa34_h, pa34_gear; // model states

  // GUI
  GtkGladeWindow winglade;
  GtkWidget *g_sce_file_names;
  GtkWidget *g_scenario_id;
  GtkWidget *g_inco_file;
  GtkWidget *g_sce_notes;
  GtkWidget *g_send_button;
  GtkWidget *g_reset_button;
  GtkWidget *g_scetime;
  GtkWidget *g_automationfailure;
  GtkWidget *g_event_text;
  GtkWidget *g_shift_x;
  GtkWidget *g_shift_y;
  GtkWidget *g_shift_z;
  GtkWidget *g_shift_mass;
  GtkWidget *g_shift_time;
  GtkWidget *g_power_left;
  GtkWidget *g_power_right;
  GtkWidget *g_max_rpm_left;
  GtkWidget *g_max_rpm_right;
  GtkWidget *g_engine_time_left;
  GtkWidget *g_engine_time_right;
  GtkWidget *g_aileron_power;
  GtkWidget *g_rudder_power;
  GtkWidget *g_rudder_bias;
  GtkWidget *g_ARI;
  GtkWidget *g_turb_int;
  GtkWidget *g_wind_vel;
  GtkWidget *g_wind_dir;
  GtkWidget *g_wind_shear;
  // display
  GtkWidget *g_frozen_v;
  GtkWidget *g_frozen_h;
  GtkWidget *g_offset_v_value;
  GtkWidget *g_offset_v_time;
  GtkWidget *g_offset_h_value;
  GtkWidget *g_offset_h_time;
  char tmp_txt[50];

	// selected sce file
	vstring inco_file;
	vstring sce_name;
	// general
	int scenario_id;
	float eventtime, eventspeed, eventaltitude, eventgear;
	long fpos; // position in file
	bool send_events;
	// events
	bool do_engineEvent, do_massEvent, do_controlEvent, do_displayEvent, do_windEvent, do_failureEvent;
	// engines
	float power_left, power_right;
	float max_rpm_left, max_rpm_right;
	float engine_time_left, engine_time_right;
	// mass shift
	float shift_x, shift_y, shift_z, shift_mass, shift_time;
	// controls
	float aileron_power, rudder_power, rudder_bias, ARI, elevator_fix;
	// display
	bool frozen_v, frozen_h;
	float offset_v_value, offset_v_time, offset_h_value, offset_h_time;
	// wind (incl. turb)
	bool enable_turb, enable_windshear;
	float turb_int, wind_vel, wind_dir;
	// addition to windEvent: FlightGear weather
	int fg_visibility;
	int fg_cloud0_alt, fg_cloud1_alt, fg_cloud2_alt;

  bool GPS_failure;
  bool VOR_failure;
  bool ADC_failure;
  bool PFD_failure;
  bool GMU_failure;
  bool AFCS_pit;
  bool AFCS_rol;
  bool clogged_sp;
  bool clogged_pt;

  int APstate;
  int verticalFDstate;
  int lateralFDstate;
  std::string fp_name;

  float lat_zero;
  float lon_zero;
  float alt_zero;
  float psi_zero;

  int active_nav_source;

  // std::string fp_comment;
  // std::string dummy_string;
  // float repos_x;
  // float repos_y;

  // utility functions
  void sendEngineEvent();
  void sendMassEvent();
  void sendControlEvent();
  void sendDisplayEvent();
  void sendWindEvent();
  void sendFailureEvent();
  void readScenarioFileHeader(const vstring& name);
  void readScenarioFileNext(const vstring& name);
  void resetParameters();
  void sendAllEvents();
  void fullGUIupdate();

public: // GTK callbacks
  // Process button clicks
  void onSendButtonClicked(GtkButton *button, gpointer user_data);
  void onResetButtonClicked(GtkButton *button, gpointer user_data);

  // Interface to the position and size of the window
  bool setWindowPositionSize(const vector< int >& p_vector);

private: // trim calculation data
  // declare the trim calculation data needed for your simulation

private: // snapshot data
  // declare, if you need, the room for placing snapshot data

private: // channel access
  // declare access tokens for all the channels you read and write
  // examples:
  // ChannelReadToken    r_mytoken;
  // ChannelWriteToken   w_mytoken;
  //using the old way for compatibility reasons: SIMONA still runs v0
  EventChannelWriteToken<MassEvent> mass_token;
  EventChannelWriteToken<EngineEvent> engine_token;
  EventChannelWriteToken<ControlEvent> control_token;
  EventChannelWriteToken<DisplayEvent> display_token;
  EventChannelWriteToken<WindEvent> turb_token;
  EventChannelWriteToken<FailureEvent> fail_token;
  EventChannelWriteToken<INCOSelect> inco_token;
  EventChannelWriteToken<APIncoEvent> apinco_token;
  EventChannelWriteToken<FGIncoEvent> fginco_token;
  // EventChannelWriteToken<Reposition> repos_token;
  StreamChannelReadToken<CitationOutput> pa34_token;

private: // activity allocation
  /** You might also need a clock. Don't mis-use this, because it is
      generally better to trigger on the incoming channels */
  PeriodicAlarm        myclock;

  /** Callback object for simulation calculation. */
  Callback<ECI>  cb1;

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
  ECI(Entity* e, const char* part, const PrioritySpec& ts);

  /** Continued construction. This is called after all script
      parameters have been read and filled in, according to the
      parameter table. Your running environment, e.g. for OpenGL
      drawing, is also prepared. Any lengty initialisations (like
      reading the 4 GB of wind tables) should be done here.
      Return false if something in the parameters is wrong (by
      the way, it would help if you printed what!) May be deleted. */
  bool complete();

  /** Destructor. */
  ~ECI();

  // add here the member functions you want to be called with further
  // parameters. These are then also added in the parameter table
  // The most common one (addition of time spec) is given here.
  // Delete if not needed!

  /** Specify a time specification for the simulation activity. */
  bool setTimeSpec(const TimeSpec& ts);

  /** Request check on the timing. */
  bool checkTiming(const vector<int>& i);

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

extern "C" {
  // the compare function to filter .sce files out of the directory
  static int is_sce_file(const struct dirent* entry);
}

#endif
