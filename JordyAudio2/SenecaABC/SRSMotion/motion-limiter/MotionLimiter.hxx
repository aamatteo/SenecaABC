/* ------------------------------------------------------------------   */
/*      item            : MotionLimiter.hxx
        made by         : stroosma
        date            : 020325
	category        : header file
        description     :
	changes         : 020325 first version
                          020905 incorporated new Engine + improvements
                                 from FCS_Fault
        language        : C++
*/

#ifndef MotionLimiter_hxx
#define MotionLimiter_hxx

// include the dusime header
#include <dusime.h>
#include <StateGuard.hxx>
#include <CriticalActivity.hxx>

// ethercat motion connection
#ifdef HAVE_ETHERCAT
#include <MotionInterface.hxx>
#endif

// include headers for the objects that are sent over the channels
#include "comm-objects.h"
#include <SimStateRequest.hxx>

// include headers for functions/classes you need in the module
#include "GenericMotionFilter.hxx"
#include "MotionLimiterEngine.hxx"

#include "MotionSender.hxx"
#include "MotionReceiver.hxx"
#include <map>
#include <deque>
#include <vector>
#include <boost/scoped_ptr.hpp>
using std::map;
using std::deque;
using std::vector;


// defines for the status word
#define MOTION_TEST		0X01
#define JACK_BRAKE		0X02
#define JACK_MIN		0X04
#define JACK_MAX		0X08

// defines for the motion commands
// TODO: check with new ICD
#define CMD_SHUTDOWN		0
#define CMD_ERROR		1
#define CMD_DOWNANDLOCK		2
#define CMD_NEUTRAL		3
#define CMD_DITHER		4
#define CMD_CUE			5

// defines for the motion replies
// TODO: check with new ICD
#define MCC_LOCALCHECK		1
#define MCC_DOWNANDLOCK		2
#define MCC_MOVETONEUTRAL	3
#define MCC_NEUTRAL		4
#define MCC_DITHER		5
#define MCC_CUE			6
#define MCC_MOVETODOWNANDLOCK	7
#define MCC_SHUTDOWN		8
#define MCC_ERROR		9
#define MCC_EXPERIMENT		20

// depth of FIFO for setpoints, in milliseconds
// this determines how far back we look when comparing
// measured position data and commanded setpoints
#define SETPOINT_FIFO_DEPTH 120.0

// class to store the commanded positions, for assessing the
// tracking performance of the motion base
class CmdPos;

// class to store the commanded positions, for assessing the
// tracking performance of the motion base
class CmdPos
{
public:
  double x;
  double y;
  double z;
  double phi;
  double theta;
  double psi;

  CmdPos();
  CmdPos(double, double, double, double, double, double);
  ~CmdPos();
};

/** A hardware module. */
class MotionLimiter: public HardwareModule, public TriggerPuller
{
#ifdef HAVE_ETHERCAT
  /** Link to the ethercat interface */
  SingletonPointer<MotionInterface>  interface;
#endif

private: // simulation data
  // declare the data you need in your simulation
  // ptr to a GMF, doing the motion filtering
  // comes from Scheme
  GenericMotionFilter *mf;
  vector<GenericMotionFilter*> filters;
  // filter user data, to be filled by motion filter, sent to logger
  MotionFilterUserData fud;
  MotionFilterUserData fud_null;

  // object doing the actual work
  MotionLimiterEngine mle;
  // the simulator motion state
  // don't forget to update this from the engine!
  SimulatorMotionState sms;
  void updateSimulatorMotionState();
  // work variable holding the proposed (unsafe) acc. from motion filter
  // don't use this to fill the MCC output! use the mle query functions instead!
  SimulatorMotionAcceleration sma_unsafe;// in DERP, deprecated 09JUN2002
  SimulatorMotionAcceleration sma_unsafe_ug;// in center of upper gimbal
  // our periodic time-spec, to be passed on to motion filter
  PeriodicTimeSpec my_time_spec;

  // state: we're honoring a MotionRequest to go to Neutral
  bool neutral_requested;
  // name of module requesting a position
  vstring request_client_name;

  // zero valued accelerations, to be fed to the MotionLimiterEngine when
  // we're braking and have no interest in the MotionFilter output
  SimulatorMotionAcceleration sma_null;
  // the MotionState the MotionLimiterEngine reports back to us.
  // if it reads IN_NEUTRAL, we've completed the transition from Advance to
  // Hold_Current
  MotionLimiterEngine::MotionState cur_MotionState;
  MotionLimiterEngine::MotionState old_MotionState;

  // the FIFO for the previous setpoints, to be compared to received measurements
  deque<CmdPos> setpointFIFO;

  // get the MLE results in the form of a MotionCommandedPosVelAcc
  MotionCommandedPosVelAcc getMCPVA();

  /// reference data for the down position
  const MotionCommandedPosVelAcc mcpva_down;

  /// reference data for the neutral position
  const MotionCommandedPosVelAcc mcpva_neutral;
  
  // get the MLE results in the form of a CmdPos
  CmdPos getCmdPos();

  int comm_errors;
  volatile bool commsOK; // watchdog signal on MCC replies
  bool downOK; // check if real motion base is down
  // flag a communication error, revert to safe mode if it happens too much
  void flagCommError(const TimeSpec&);
  // flag a motion error, revert to safe mode if it happens too much
  void flagMotionError(const TimeSpec&);
  // countdown to wait a while in Neutral before going down
  int neutral_countdown;

  // set the motion cueing data on the interface
  void writeMotion(const MotionCommandedPosVelAcc& cp, int cmd);

  // send all the data to be logged over our DUECA channels
  void sendLogData(const TimeSpec& ts, const SimulatorMotionAcceleration& mf_output, const int& status = 0);
  void sendLogData(const TimeSpec& ts, const SimulatorMotionAcceleration& mf_output, const MotionFilterUserData& usr_data, const int& status = 0);

  // waiting time before sending neutral to MCC after braking into neutral/hold_current
  double settling_time_counter;
  const double settling_time;
  bool settling_started;

  void preLimit(SimulatorMotionAcceleration &);
  double surge_pre_limit, sway_pre_limit, heave_pre_limit;
  double roll_pre_limit, pitch_pre_limit, yaw_pre_limit;

  // catching nasty input, returns true if there's a problem
  bool sanitizeInput(VehicleCabMotion& vcm);

  // catching nasty motion filter output, returns true if there's a problem
  bool sanitizeMFOutput(SimulatorMotionAcceleration& sma);

  // check sanity of motion limiter itself
  bool checkMLESanity();

  // estimated motion system delay
  // ML tries to get data for this many time ticks in the future
  // it can be negative, in which case you'll have behavior similar
  // to the old model_data_delay
  int motion_system_delay;

  // TimingCheck object to report anomalies to
  TimingCheck *myTimingCheck;

  // flag to fake io
  bool fake_io;
  
  // flag to feed zero motion to filter at all times
  // usefull for motion/no-motion experiments
  bool stay_still;

  // flag to employ less strict timing checks on input
  bool loose_timing;

  // more precise control over the amount of delay to be accepted 
  // in the input data during a run
  int delay_tolerance, old_data_tolerance;

  // reference position for SimulatorCabMotion (previously only DERP)
  double x_SCM_ref, y_SCM_ref, z_SCM_ref;

  // starting the EtherCAT device only once
  bool starting, started; 

private: // trim calculation data
  // declare the trim calculation data needed for your simulation

private: // snapshot data
  // declare, if you need, the room for placing snapshot data

private: // channel access
  StreamChannelReadToken<VehicleCabMotion> input_token;
  StreamChannelWriteToken<MotionActuatorLengths> length_token;
  StreamChannelWriteToken<MotionCommandedPosVelAcc> pva_token;
  StreamChannelWriteToken<MotionGimbalPositions> gimbal_token;
  StreamChannelWriteToken<SimulatorCabMotion> result_token;
  StreamChannelWriteToken<SimulatorMotionAcceleration> filter_output_token;
  StreamChannelWriteToken<MotionFilterUserData> filter_user_token;
  EventChannelReadToken<MotionRequest> request_token;
  EventChannelWriteToken<MotionConfirm> confirm_token;
  EventChannelReadToken<MotionConfiguration> conf_in_token;
  EventChannelWriteToken<MotionConfiguration> conf_out_token;
  EventChannelWriteToken<SimStateRequest> ssr_token;

  // communication between receive activity and main activity
  // note that this link is not guaranteed in Safe mode, but
  // we're running open loop then, so it doesn't matter
  // dynamically create these channels if not fake_io
  boost::scoped_ptr<StreamChannelWriteToken<MotionBaseResultData> >
  reply_out_token;

private: // activity allocation
  /// Callback object for simulation calculation
  Callback<MotionLimiter>  cb_ml_safe, cb_ml_work;

  /// Activity for simulation calculation
  CriticalActivity      do_calc;

public: // class name and trim/parameter tables
  /// Name of the module.
  static const char* const           classname;

  /// Return the initial condition table
  static const IncoTable*            getMyIncoTable();

  /// Return the parameter table
  static const ParameterTable*       getMyParameterTable();

public: // construction and further specification
  /** Constructor. Is normally called from scheme/the creation script. */
  MotionLimiter(Entity* e, const char* part, const PrioritySpec& ts);

  /** Continued construction. This is called after all script
      parameters have been read and filled in, according to the
      parameter table. Your running environment, e.g. for OpenGL
      drawing, is also prepared. Any lengty initialisations (like
      reading the 4 GB of wind tables) should be done here.
      Return false if something in the parameters is wrong (by
      the way, it would help if you printed what!) May be deleted. */
  bool complete();

  /** Destructor. */
  ~MotionLimiter();

  // add here the member functions you want to be called with further
  // parameters. These are then also added in the parameter table
  // The most common one (addition of time spec) is given here.
  // Delete if not needed!

  /** Specify a time specification for the simulation activity. */
  bool setTimeSpec(const TimeSpec& ts);

  /** Request check on the timing. */
  bool checkTiming(const vector<int>& i);

  // this receives a ptr to a GenericMotionFilter from Scheme
  // it should check this of course (see PackerSet)
  // OS 24JAN03 retained for backward compatibility, use setMotionFilters and selectMotionFilter
  // bool setMotionFilter(const SCM& mf);
  bool setMotionFilter(ScriptCreatable& mf, bool in);

  // this adds a Sceme motion filter to our list, selectable through selectMotionFilter
  //bool addMotionFilter(const SCM& mfnew);
  bool addMotionFilter(ScriptCreatable& mf, bool in);

  // this selects the active motion filter by index (order in which they were added)
  bool selectMotionFilter(const int& i);

  // set the estimate of the motion system delay. 
  // ML gets its data this far in the future
  bool setMotionSystemDelay(const double & d);

  /** Select a reference point for SimulatorCabMotion channel w.r.t. UGP. 
      0: UGP
      1: DERP (old default)
      2: OMCT (35 cm below DERP)
   */
  bool setSCMRefPoint(const int& i);

public: // member functions for cooperation with DUECA

  /// indicate that, at least for initial start-up, everything is ready
  bool isInitialPrepared();

  /// indicate that everything is ready
  bool isPrepared();

  /// initial start, go into safe mode
  void initialStartModule(const TimeSpec &ts);

  /// start responsiveness to input data
  void startModule(const TimeSpec &time);

  /// stop responsiveness to input data
  void stopModule(const TimeSpec &time);

  /// also stop the safe mode
  void finalStopModule(const TimeSpec& time);

public: // the member functions that are called for activities
  /// the method that implements the main calculation
  void doWork(const TimeSpec& ts);

  /// the method that implements the safety strategy
  void doSafe(const TimeSpec& ts);

  /// the method that does the receiving from the motion base
  void doRx(const TimeSpec& ts);

public: // member functions for cooperation with DUSIME
  /// For the Snapshot capability, fill the snapshot "snap" with the
  /// data saved at a point in your simulation (if from_trim is false)
  /// or with the state data calculated in the trim calculation (if
  /// from_trim is true)
  void fillSnapshot(const TimeSpec& ts,
		    Snapshot& snap, bool from_trim);

  /// Restoring the state of the simulation from a snapshot
  void loadSnapshot(const TimeSpec& t, const Snapshot& snap);

  /** Perform a trim calculation. Should NOT use current state
      uses event channels parallel to the stream data channels,
      calculates, based on the event channel input, the steady state
      output. */
  void trimCalculation(const TimeSpec& ts, const IncoMode& mode);
};


#endif
