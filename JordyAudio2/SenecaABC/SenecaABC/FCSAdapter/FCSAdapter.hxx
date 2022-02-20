/* ------------------------------------------------------------------   */
/*      item            : FCSAdapter.hxx
        made by         : simona
	from template   : HardwareModuleTemplate.hxx
        template made by: Rene van Paassen
        date            : Fri Apr 27 16:40:29 2012
	category        : header file
        description     :
	changes         : Fri Apr 27 16:40:29 2012 first version
	template changes: 030401 RvP Added template creation comment
        language        : C++
*/

#ifndef FCSAdapter_hxx
#define FCSAdapter_hxx

// include the dusime header
#include <dusime.h>
#include <CriticalActivity.hxx>
#include <HardwareModule.hxx>
USING_DUECA_NS;

// This includes headers for the objects that are sent over the channels
#include "comm-objects.h"

// Seneca model data
#include "StatesOutputs.h"


// include headers for functions/classes you need in the module

/** A hardware module.

    The instructions to create an module of this class from the Scheme
    script are:

    \verbinclude fcs-adapter.scm
 */
class FCSAdapter: public HardwareModule
{
private: // simulation data
  /** The time step we are going to use. */
  double dt;

  // output to the model
  CitationPilotInput myCPI;

  // configuration, determines how myCPI is filled
  PilotControlConfig myPCC;

  // low-level configuration, expect input from column/sidestick/ECI
  bool read_column, read_sidestick, read_config;

  // use qfeel or old method of column pitch trim
  bool use_qfeel;

  // use position offset to do column pitch trim
  // if false, use force offset
  bool use_qfeel_pos;

  // QFeel output
  QFeel myQF;

  // column parameters to invert de_trim to force offset
  double column_gain_y; // from rad column pos -> rad de
  double column_stiffness_y; // from rad column pos -> N column force

  // gains on sidestick inputs deg stick pos -> cit input
  float uxgain, uygain;

  // triggers for the two activities
  ConditionAnd h2s_trigger, s2h_trigger;

  // pitch trim stuff
  // default and sidestick behaviour adds de0 + trim_tab_pos to CPI.de
  // column calculates qfeel force from de0 + trim_tab_pos with column_gain
  // and column_stiffness.
  double de0; // baseline elevator deflection, set from model init
  double trim_tab_pos; // pilot-modified additional elevator deflection
  double trim_speed; // speed to adjust trim_tab_pos rad/s
  double trim_incr; // speed to adjust trim_tab_pos in rad/step
  double vtas; //
  double altitude; // aircraft altitude
  double q; // dynamic pressure

  /** A flag to remember that the safety activity approves of transition to
      working state. */
  bool hardware_ok;

  bool ap_on;
  float ap_de;
  float ap_da;
  float ap_dr;

  float ap_da_old;
  float ap_dr_old;

private: // channel access
  // declare StreamChannelReadToken<Type>, StreamChannelWriteToken<Type>
  // EventChannelReadToken<Type>, EventChannelWriteToken<Type>
  // access tokens for all the channels you read and write
  // example
  // StreamChannelReadToken<MyData>  my_token;

  // default input from joystick/midconsole
  StreamChannelReadToken<PrimaryControls> pc_token;
  StreamChannelReadToken<SecondaryControls> sc_token;
  StreamChannelReadToken<PrimarySwitches> ps_token;
  StreamChannelReadToken<SecondarySwitches> ss_token;
  StreamChannelReadToken<CitationOutput> in_token;

  // optional input from column
  StreamChannelReadToken<PrimaryControls>* pc_cpt_token;
  StreamChannelReadToken<PrimarySwitches>* ps_cpt_token;

  // optional input from sidestick
  StreamChannelReadToken<SideStickOutput>* sso_token;
  StreamChannelReadToken<StickSwitches>* ss_fo_token;

  // output to model
  StreamChannelWriteToken<CitationPilotInput> cpi_token;

  // optional output to column (for trimming and slaving)
  StreamChannelWriteToken<QFeel>* qf_token;

  // optional output to sidestick (for trimming and slaving)
  StreamChannelWriteToken<SideStickInput> *ssi_token;

  // input and output to change our configuration
  EventChannelReadToken<PilotControlConfig>* pcc_cmd_token;
  StreamChannelWriteToken<PilotControlConfig> pcc_token;

  // trimmed inputs from model
  EventChannelReadToken<CitationPilotInput> cpi_trim_token;

  // autopilot settings
  StreamChannelReadToken<AutopilotChannel> ap_token;
  EventChannelReadToken<APIncoEvent> apinco_token;

private: // activity allocation
  /** Callback objects for sim2hardware calculation. */
  Callback<FCSAdapter>  s2h_cb1, s2h_cb2;

  /** Activity for sim2hardware calculation. */
  CriticalActivity do_sim2hw;

  /** Callback object for hardware2sim calculation. */
  Callback<FCSAdapter> h2s_cb;

  /** Activity for hardware2sim calculation. */
  ActivityCallback do_hw2sim;

  /** Clock to drive activity. */
  PeriodicAlarm my_clock;

public: // class name and trim/parameter tables
  /** Name of the module. */
  static const char* const           classname;

  /** Return the initial condition table. */
  static const IncoTable*            getMyIncoTable();

  /** Return the parameter table */
  static const ParameterTable*       getMyParameterTable();

public: // construction and further specification
  /** Constructor. Is normally called from scheme/the creation script. */
  FCSAdapter(Entity* e, const char* part, const PrioritySpec& ts);

  /** Continued construction. This is called after all script
      parameters have been read and filled in, according to the
      parameter table. Your running environment, e.g. for OpenGL
      drawing, is also prepared. Any lengty initialisations (like
      reading the 4 GB of wind tables) should be done here.
      Return false if something in the parameters is wrong (by
      the way, it would help if you printed what!) May be deleted. */
  bool complete();

  /** Destructor. */
  ~FCSAdapter();

  // add here the member functions you want to be called with further
  // parameters. These are then also added in the parameter table
  // The most common one (addition of time spec) is given here.
  // Delete if not needed!

  /** Specify a time specification for the simulation activity. */
  bool setTimeSpec(const TimeSpec& ts);

  /** Request check on the timing. */
  bool checkTiming(const vector<int>& i);

  /** Expect input from column and drive it. */
  bool useColumn(const bool& b);

  /** Expect input from sidestick and drive it. */
  bool useSidestick(const bool& b);

  /** Expect configuration changing channel. */
  bool readConfig(const bool& b);

public: // member functions for cooperation with DUECA

  /** indicate that, at least for initial start-up, everything is ready */
  bool isInitialPrepared();

  /** indicate that everything is ready. */
  bool isPrepared();

  /** initial start, go into safe mode. */
  void initialStartModule(const TimeSpec &ts);

  /** start responsiveness to input data. */
  void startModule(const TimeSpec &time);

  /** stop responsiveness to input data. */
  void stopModule(const TimeSpec &time);

  /** also stop the safe mode. */
  void finalStopModule(const TimeSpec& time);

public: // the member functions that are called for activities
  /** the method that implements the main calculation for Sim->HW. */
  void doSim2HW(const TimeSpec& ts);

  /** the method that implements the safety strategy for Sim->HW. */
  void doSafeSim2HW(const TimeSpec& ts);

  /** the method that implements the main calculation for HW->Sim. */
  void doHW2Sim(const TimeSpec& ts);

public: // member functions for cooperation with DUSIME
  /** For the Snapshot capability, fill the snapshot "snap" with the
      state saved at a point in your simulation (if from_trim is false)
      or with the state data calculated in the trim calculation (if
      from_trim is true. */
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
