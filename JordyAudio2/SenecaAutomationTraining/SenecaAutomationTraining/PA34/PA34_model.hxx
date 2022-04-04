/* ------------------------------------------------------------------   */
/*      item            : PA34_model.hxx
        generated by    : hkoolstra
	from template   : Simulink61Template.hxx
        template made by: Rene van Paassen
        date            : Tue Feb 25 10:44:23 2014
	category        : header file
        description     : Encapsulation of the Simulink/rtw model
	                  pa34model_dueca_8b
	changes         : Tue Feb 25 10:44:23 2014 first version
	template changes: 030326 RvP Centralised creation of models
	                         RvP delete and re-create strategy
			  050224 RvP Improved delete and re-create,
                                     handles MP machines.
			  060419 RvP version for rtw61
			  070116 RvP Call sequence for rtw64 is
                                 identical; code also doubles for rtw64
			  070125 RvP Call sequence for rtw65 is
                                 identical; code also doubles for rtw65
        language        : C++
*/
#ifndef PA34_model_hxx
#define PA34_model_hxx

// include the dusime header
#include <dusime.h>
USING_DUECA_NS;

//voor math functies
#include <math.h>

// This includes headers for the objects that are sent over the channels
#include "comm-objects.h"
#include <SimStateRequest.hxx>
// include headers for functions/classes you need in the module
extern "C" {
#define RTW_GENERATED_S_FUNCTION
#include "rtwtypes.h"
#include <simstruc.h>
#include "pa34model_dueca_8b.h"
}


#include "StatesOutputs.h"

// the pa34model_dueca_8b.h file defines the assert macro to be null. This is
// not wat we want, we need assert to check the dimensions of the
// model against those of the DUECA simulation. Therefore:
#undef assert


// calculate total number of states
// Of separaat definieren line numbers 81:86
#if defined(NCSTATES) && defined(NDSTATES)
# define NSTATES (NCSTATES + NDSTATES)
#elif defined(NCSTATES)
# define NSTATES NCSTATES
#elif defined(NDSTATES)
# define NSTATES NDSTATES
#else
# error "Neither NCSTATES nor NDSTATES defined"
#endif


/** A simulation module.

    The instructions to create an module of this class from the Scheme
    script are:

    \verbinclude pa-34_model.scm
 */
class PA34_model: public SimulationModule
{
private: // simulation data
  /** pointer to the real-time workshop model. */
  pa34model_dueca_8b_rtModel *S;

  /** pointer to a new, re-initialized  model, waiting */
  pa34model_dueca_8b_rtModel *Snew;

  /** pointer to a used, old model. */
  pa34model_dueca_8b_rtModel *Sold;

  /** The time step we are going to use. */
  double dt;

  /** initial (trimmed) pitch value */
  //double de0;

  /** elevator angle to detect trim changes in HC */
  double prev_de;

  /** flaps and gear */
  float flap_pos, flap_speed, flap_incr;
  float gear_pos, gear_time, gear_incr;
  bool flapsOK, gearOK, gear_fail;

  /** aileron rudder inter connect als percentage */
  double ARI;

  /** turbulence intensity and wind setting */
//  double turb_gain;
//  double turb_gains[8];
  float K_turb;
  float K_shear;
  float wind_vel;
  float wind_dir;
  float wind_vel_stepsize;
  int wind_vel_nsteps;
  float wind_dir_stepsize;
  int wind_dir_nsteps;

  /** turbulence file name */
//  vstring turb_file;

  /** turbulence data */
//  vector<float> turbulence;

  /** iterator to play back the turbulence data */
//  vector<float>::const_iterator turb_iter;

  /** conversion from cg to cabin variables */
  double xcab, ycab, zcab;
  double sf,cf,st,ct,sp,cp;// Euler gonio work variables

  /** elevator trim */
  //double trim_tab_pos;// rad -0.26 ... 0.26
  //double trim_speed;// rad/s
  //double trim_incr; // rad/step

  /** fixed terrain elevation */
  double terr_elevation;

  /** has inco been loaded? otherwise we send default trim inputs */
  bool inco_loaded;

  /** fade in parameter */
  float fade_in;

  float timesound; // to dampen out first second

  /** engine parameters */
  float power_left, power_right;
  float LEFT_RPM, RIGHT_RPM;
  float pla_stepsize_left, pla_stepsize_right;
  int pla_nsteps_left, pla_nsteps_right;

  /** mass parameters */
  bool asym_start;
  float asym_x, asym_y, asym_z, asym_mass;
  float old_x, old_y, old_z, old_mass;
  float dx, dy, dz, dmass;
  int mass_nsteps;

  /** control parameters */
  float aileron_power, rudder_power, rudder_bias, elevator_fix, rudder_offset, rudder_offset_time, eventgeardown; //eventgeardown

  /** comm event parameters and trigger */

  bool radioevent, check_gear_asym;// radioevent is the trigger, radiocomm is the parameter defined in CommEvent
  int radiocomm;

  /** bool to signal end of fligh*/
  bool flying;

  int APstate;
  float ap_de;
  float ap_da;
  float ap_dr;

  bool autopilotdisco_notplaying;
  uint32_t msg;

private: // trim calculation data
  /** pointer to a second copy of this real-time workshop model, for
      trim condition calculation. */
  pa34model_dueca_8b_rtModel *i_S;

private: // snapshot data
  /** Copy of the model state for snapshot sending. */
  double s_x[NSTATES];

private: // channel access
  // declare StreamChannelReadToken<Type>, StreamChannelWriteToken<Type>
  // EventChannelReadToken<Type>, EventChannelWriteToken<Type>
  // access tokens for all the channels you read and write
  // example
  // StreamChannelReadToken<MyData>  my_token;
  //StreamChannelReadToken<PrimaryControls> pc_token;
  //StreamChannelReadToken<SecondaryControls> sc_token;
  //StreamChannelReadToken<PrimarySwitches> ps_token;
  //StreamChannelReadToken<SecondarySwitches> ss_token;
  StreamChannelReadToken<CitationPilotInput> cpi_token;

//  EventChannelWriteToken<TurbulenceConfiguration> turb_token;
  EventChannelReadToken<WindEvent> turb_token;
  EventChannelReadToken<SnapshotRequest> sr_token;
  EventChannelReadToken<Reposition> repos_token;
  EventChannelReadToken<Trim_inco> trim_inco_token;

  // malfunction events
  EventChannelReadToken<MassEvent> mass_token;
  EventChannelReadToken<EngineEvent> engine_token;
  EventChannelReadToken<ControlEvent> control_token;

  // communication events

  EventChannelReadToken<CommEvent> comm_token;

  // autopilot settings
  StreamChannelReadToken<AutopilotChannel> ap_token;
  EventChannelReadToken<GFC700Event> gfcr_token;
  EventChannelReadToken<AP2G1000Channel> ap2g1000_token;


  // malfunction status update
  EventChannelWriteToken<MassEvent> mass_feedback_token;
  EventChannelWriteToken<EngineEvent> engine_feedback_token;

  // output streams
  StreamChannelWriteToken<CitationOutput> out_token;
  StreamChannelWriteToken<ManifoldChannel> ma_token;
  StreamChannelWriteToken<VehicleCabPosition> vcp_token;
  StreamChannelWriteToken<VehicleCabMotion> vcm_token;
  StreamChannelWriteToken<PropSoundData> snd_token;

  // output events
  //EventChannelWriteToken<SimStateRequest> hold_request;
  EventChannelWriteToken<Snapshot> snap_token;
  EventChannelWriteToken<CitationPilotInput> cpi_trim_token;

  // output sound
  ChannelWriteToken w_observer;
  ChannelWriteToken w_gearup;
  ChannelWriteToken w_geardown;
  ChannelWriteToken w_flaps;
  ChannelWriteToken w_sndwind;
  ChannelWriteToken w_sndstall;
  ChannelWriteToken w_sndmass;
  ChannelWriteToken w_sndspeed;
  ChannelWriteToken w_sndwheel;
  ChannelWriteToken w_sndtd;
  ChannelWriteToken w_gearalert;
  ChannelWriteToken w_autopilotdisco;
  ChannelWriteToken w_apbutton;
  //ChannelWriteToken w_comm; // added by Matteo Piras

private: // activity allocation
  /** Callback object for simulation calculation. */
  Callback<PA34_model>  cb1;

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
  PA34_model(Entity* e, const char* part, const PrioritySpec& ts);

  /** Continued construction. This is called after all script
      parameters have been read and filled in, according to the
      parameter table. Your running environment, e.g. for OpenGL
      drawing, is also prepared. Any lengty initialisations (like
      reading the 4 GB of wind tables) should be done here.
      Return false if something in the parameters is wrong (by
      the way, it would help if you printed what!) May be deleted. */
  bool complete();

  /** Destructor. */
  ~PA34_model();

  // add here the member functions you want to be called with further
  // parameters. These are then also added in the parameter table
  // The most common one (addition of time spec) is given here.
  // Delete if not needed!

  /** Specify a time specification for the simulation activity. */
  bool setTimeSpec(const TimeSpec& ts);

  /** Request check on the timing. */
  bool checkTiming(const vector<int>& i);

  /** Gain to apply on incoming turbulence */
  bool setTurbulenceGains(const vector<double>& i);

  /** Allow external TurbulenceConfiguration events to alter the turbulence */
  bool useTurbulenceConfiguration(const bool& b);

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
  void trimCalculation(const TimeSpec& ts, const IncoMode& mode);

private:
  /** Create and initialise a model. */
  pa34model_dueca_8b_rtModel *createAndInitialiseModel();

  /** Destroy it again. */
  void destroyModel(pa34model_dueca_8b_rtModel *dS);
};

#endif
