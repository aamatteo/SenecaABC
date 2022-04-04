/* ------------------------------------------------------------------   */
/*      item            : CitationLogger.hxx
        made by         : stroosma
	from template   : DusimeModuleTemplate.hxx
        template made by: Rene van Paassen
        date            : Thu Jan 13 13:48:31 2005
	category        : header file
        description     :
	changes         : Thu Jan 13 13:48:31 2005 first version
	template changes: 030401 RvP Added template creation comment
        language        : C++
*/

#ifndef CitationLogger_hxx
#define CitationLogger_hxx

#ifdef CitationLogger_cxx
static const char h_id[] =
"$Id: CitationLogger.hxx,v 1.1.1.1 2022/02/17 15:04:28 matteopiras Exp $";
#endif

// include the dusime header
#include <dusime.h>

// This includes headers for the objects that are sent over the channels
#include "comm-objects.h"

// include headers for functions/classes you need in the module
#include <fstream>
// headers for file juggling
#include <dirent.h>

/** A module.

    The instructions to create an module of this class from the Scheme
    script are:

    \verbinclude citation-logger.scm
*/
class CitationLogger: public SimulationModule
{
private: // simulation data
  // declare the data you need in your simulation


  ofstream out;
  int next_file_number;
  SimulationState prev_state;
  //vstring log_dir;

  TimeSpec run_start;

  // copies of incoming data
  /*PrimaryControls _pc;
  SecondaryControls _sc;
  PrimarySwitches _ps;
  SecondarySwitches _ss;
  CitationPilotInput _cpi;*/
  //
  // from CitationOutput
  CitationOutput _co;
  //
  int eventID;
  bool turbulence, wind_shear;
  float turb_int, wind_vel, wind_dir;
  vstring inco_file;
  vstring notes;

  int curVerticalState;
  int curLateralState;
  int APstate;
  float target_alt;
  float target_speed;
  float hdg_bug;
  float target_vs;
  float alt_hold;
  int active_nav_source;
  float course;
  float altitude_target_vnav;
  int active_leg;

  float theta_ref;
  float phi_ref;
  float ap_de;
  float ap_da;
  float ap_dr;
  float needle_deviation;
  float dme;
  float brg;
  float nav_R;

  uint32_t msg;
  float alt_select;
  float hdg_select;
  float crs_select;

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






private: // trim calculation data
  // declare the trim calculation data needed for your simulation

private: // snapshot data
  // declare, if you need, the room for placing snapshot data

private: // channel access
  // declare StreamChannelReadToken<Type>, StreamChannelWriteToken<Type>
  // EventChannelReadToken<Type>, EventChannelWriteToken<Type>
  // access tokens for all the channels you read and write
  // example
  // StreamChannelReadToken<MyData>  my_token;
  /*StreamChannelReadToken<PrimaryControls> pc_token;
  StreamChannelReadToken<SecondaryControls> sc_token;
  StreamChannelReadToken<PrimarySwitches> ps_token;
  StreamChannelReadToken<SecondarySwitches> ss_token;
  StreamChannelReadToken<CitationPilotInput> cpi_token;*/
  StreamChannelReadToken<CitationOutput> out_token;
  EventChannelReadToken<INCOSelect> inco_sel_token;
  EventChannelReadToken<WindEvent> turb_token;
  StreamChannelReadToken<AutopilotChannel> ap_token;
  EventChannelReadToken<AP2G1000Channel> ap2g_token;
  EventChannelReadToken<GFC700Event> gfcr_token;
  EventChannelReadToken<FailureEvent> fail_token;
  // optional channel
  //StreamChannelReadToken<Vc_Channel> *Vc_token;

private: // activity allocation
  /** Callback object for simulation calculation. */
  Callback<CitationLogger>  cb1;

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
  CitationLogger(Entity* e, const char* part, const PrioritySpec& ts);

  /** Continued construction. This is called after all script
      parameters have been read and filled in, according to the
      parameter table. Your running environment, e.g. for OpenGL
      drawing, is also prepared. Any lengty initialisations (like
      reading the 4 GB of wind tables) should be done here.
      Return false if something in the parameters is wrong (by
      the way, it would help if you printed what!) May be deleted. */
  bool complete();

  /** Destructor. */
  ~CitationLogger();

  // add here the member functions you want to be called with further
  // parameters. These are then also added in the parameter table
  // The most common one (addition of time spec) is given here.
  // Delete if not needed!

  /** Specify a time specification for the simulation activity. */
  bool setTimeSpec(const TimeSpec& ts);

  /** Request check on the timing. */
  bool checkTiming(const vector<int>& i);

  /** Expect input from cv-calculation module over Vc_Channel channel. */
  //bool readCv(const bool& b);

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
  // the compare function to filter .log files out of the directory
  static int is_log_file(const struct dirent* entry);
}

#endif
