/* ------------------------------------------------------------------   */
/*      item            : MotionLimiter.cxx
        made by         : stroosma
        date            : 020325
	category        : body file
        description     :
	changes         : 020325 first version
			  020905 incorporated new Engine + improvements
                                 from FCS_Fault
        language        : C++
*/

static const char c_id[] =
"$Id: MotionLimiter.cxx,v 1.51 2019/04/08 15:40:42 ostroosma Exp $";

#define MotionLimiter_cxx
// include the definition of the module class
#include "MotionLimiter.hxx"
// OS 10AUG2001 needed to refer to our entity (setMotionLimiter())
#include <Entity.hxx>

// include additional files needed for your calculation here
#define SIGN(A) ( (A < 0.0) ? -1.0 : 1.0 )
#include <errno.h>
#include <signal.h>

#define D_MOD
#define I_MOD
#define W_MOD
#define E_MOD
#include <debug.h>

// the standard package for DUSIME, including template source
#define DO_INSTANTIATE
#include <dusime.h>

// shouldn't be necessary
#include <Ticker.hxx>
#include <MemberCall2Way.hxx>

template<class T>
inline const T limit1(const T& i)
{
  if (i >  1.0) return  1.0;
  if (i < -1.0) return -1.0;
  return i;
}

void MLsignalhandler(int i)
{
   cout << "MotionLimiter caught a signal: " << i << endl;
}

// class/module name
const char* const MotionLimiter::classname = "motion-limiter";

// initial condition/trim table
const IncoTable* MotionLimiter::getMyIncoTable()
{
  static IncoTable inco_table[] = {
    // always close off with:
    { NULL, NULL} };
  
  return inco_table;
}

// parameters to be inserted
const ParameterTable* MotionLimiter::getMyParameterTable()
{
  static const ParameterTable parameter_table[] = {
    { "set-timing",
      new MemberCall<MotionLimiter,TimeSpec>
        (&MotionLimiter::setTimeSpec), "set timing of main activity"},

    { "check-timing",
      new MemberCall<MotionLimiter,vector<int> >
      (&MotionLimiter::checkTiming), "set checks on timing of main activity"},

    { "set-motion-filter",
      new MemberCall2Way<MotionLimiter, ScriptCreatable >
      (&MotionLimiter::setMotionFilter), "set the single motion filter"},

    { "add-motion-filter",
      new MemberCall2Way<MotionLimiter, ScriptCreatable >
      (&MotionLimiter::addMotionFilter), "add a motion filter to the list"},

    { "select-motion-filter",
      new MemberCall<MotionLimiter, int>
      (&MotionLimiter::selectMotionFilter), "select the motion filter by index"},

    { "surge-limit",
      new VarProbe<MotionLimiter,double>
        (&MotionLimiter::surge_pre_limit), "pre-limit on surge, m/s2"},
    { "sway-limit",
      new VarProbe<MotionLimiter,double>
        (&MotionLimiter::sway_pre_limit), "pre-limit on sway, m/s2"},
    { "heave-limit",
      new VarProbe<MotionLimiter,double>
        (&MotionLimiter::heave_pre_limit), "pre-limit on heave, m/s2"},

    { "roll-limit",
      new VarProbe<MotionLimiter,double>
        (&MotionLimiter::roll_pre_limit), "pre-limit on roll, rad/s2"},
    { "pitch-limit",
      new VarProbe<MotionLimiter,double>
        (&MotionLimiter::pitch_pre_limit), "pre-limit on pitch, rad/s2"},
    { "yaw-limit",
      new VarProbe<MotionLimiter,double>
        (&MotionLimiter::yaw_pre_limit), "pre-limit on yaw, rad/s2"},

    { "motion-delay",
      new MemberCall<MotionLimiter,double>
        (&MotionLimiter::setMotionSystemDelay), "estimated delay of motion system for early cueing"},

    { "fake-io",
      new VarProbe<MotionLimiter,bool>
        (&MotionLimiter::fake_io), "do not send anything to the motion base"},

    { "stay-still",
      new VarProbe<MotionLimiter,bool>
        (&MotionLimiter::stay_still), "send constant neutral position to the motion base" },

    { "loose-timing",
      new VarProbe<MotionLimiter,bool>
      (&MotionLimiter::loose_timing), 
      "be less strict in timing check on input" },
    
    { "delay-tolerance",
      new VarProbe<MotionLimiter,int>
      (&MotionLimiter::delay_tolerance),
      "amount of delayed input to accept" },

    { "scm-reference-point",
      new MemberCall<MotionLimiter,int>
        (&MotionLimiter::setSCMRefPoint), "preset reference point for SCM channel, 0:UGP, 1:DERP, 2:OMCT"},
    { "scm-reference-point-x",
      new VarProbe<MotionLimiter,double>
        (&MotionLimiter::x_SCM_ref), "custom reference point for SCM channel, x forward"},
    { "scm-reference-point-y",
      new VarProbe<MotionLimiter,double>
        (&MotionLimiter::y_SCM_ref), "custom reference point for SCM channel, y right"},
    { "scm-reference-point-z",
      new VarProbe<MotionLimiter,double>
        (&MotionLimiter::z_SCM_ref), "custom reference point for SCM channel, z down"},

   // always close off with:
    { NULL, NULL} };

  return parameter_table;
}

// constructor
MotionLimiter::MotionLimiter(Entity* e, const char* part, const
		       PrioritySpec& ps) :
  HardwareModule(e, classname, part, getMyIncoTable(), 0),

  // initialize the data you need in your simulation
  mf(NULL),
  // SIMONA geometry data
  mle( 2.131+0.02,// min. jack length  +2        OS, new limits 21MAR2003
       3.281-0.02,// max. jack length  -2        OS, new limits 21MAR2003
       10.0,	 // max. jack acc.    /2        OS, new limits 21MAR2003
       5.0,      // max. jack acc. for braking [OS], added 12AUG2004
       1.600,	 // upper gimbal radius
       1.650,	 // lower gimbal radius
       2*asin(1.0/16.0), // upper gimbal spacing
       2*asin(3.0/16.5), // lower gimbal spacing
       2.39,     // 2.345, // neutral height OS 05JUL2004, same as MCC
       0.05+0.02, // hard buffer length, needed to drive through the hard buffer into down&lock
       1.0/100.0, // default timestep
       1),       // number of integration sub-steps
  sms(0.0, 0.0, 0.0, 
      0.0, 0.0, 0.0, 0.0, 
      0.0, 0.0, 0.0, 
      0.0, 0.0, 0.0, 
      0.0, 0.0, 0.0),
  my_time_spec(0, int(0.01/Ticker::single()->getTimeGranule())), // default 100 Hz
  
  // neutral request handling
  neutral_requested(false),
  request_client_name(),
  // zero accelerations
  sma_null(0.0, 0.0, 0.0, 0.0, 0.0, 0.0),
  // output from MotionLimiterEngine
  cur_MotionState(MotionLimiterEngine::DOWN),
  old_MotionState(MotionLimiterEngine::DOWN),
  mcpva_down(0,
  	   0.0, 0.0, -0.69, 0.0, 0.0, 0.0,
  	   0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
  	   0.0, 0.0, 0.0, 0.0, 0.0, 0.0),
  mcpva_neutral(0,
  	      0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
  	      0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
  	      0.0, 0.0, 0.0, 0.0, 0.0, 0.0),
  comm_errors(0),
  commsOK(false),
  downOK(false),
  neutral_countdown(0),
  
  // waiting time before sending neutral to MCC after braking into neutral/hold_current
  settling_time_counter(100), // just a first guess, reset in Calibrate
  settling_time(5.0), // seconds, 20JUN2002 was 2.0
  settling_started(false),
  
  // translational pre limiting limits
  surge_pre_limit(10.0), sway_pre_limit(10.0), heave_pre_limit(15.0),
  // rotatational pre limiting limits
  // loosely based on 1g at gimbals
  roll_pre_limit(15.0), pitch_pre_limit(15.0), yaw_pre_limit(15.0),
  
  // [OS] 08APR2003 default leading to old behavior
  // of taking the data for the previous time step,
  // IF we're on 100Hz update rate and 2000Hz ticker
  motion_system_delay(-20),
  
  myTimingCheck(NULL),

  fake_io(false),
  stay_still(false),
  loose_timing(false),
  delay_tolerance(0), old_data_tolerance(0),
  x_SCM_ref(0.0), y_SCM_ref(0.0), z_SCM_ref(-1.2075), // defaults to old behaviour (DERP)
  starting(false), started(false),

  // initialize the data you need for the trim calculation

  // initialize the channel access tokens
  input_token(getId(), NameSet(getEntity(), "VehicleCabMotion", part), 101),
  length_token(getId(), NameSet(getEntity(), "MotionActuatorLengths", part), 101),
  pva_token(getId(), NameSet(getEntity(), "MotionCommandedPosVelAcc", part), 101),
  gimbal_token(getId(), NameSet(getEntity(), "MotionGimbalPositions", part)),
  result_token(getId(), NameSet(getEntity(), "SimulatorCabMotion", part), 101),
  filter_output_token(getId(), NameSet(getEntity(), "SimulatorMotionAcceleration", part), 101),
  filter_user_token(getId(), NameSet(getEntity(), "MotionFilterUserData", part),101),
  request_token(getId(), NameSet(getEntity(), "MotionRequest", part)),
  confirm_token(getId(), NameSet(getEntity(), "MotionConfirm", part)),
  conf_in_token(getId(), NameSet(getEntity(), "MotionConfiguration", part)),
  conf_out_token(getId(), NameSet(getEntity(), "MotionConfiguration", part),
  	       ChannelDistribution::JOIN_MASTER),
  ssr_token(getId(), NameSet("dusime", "SimStateRequest", ""),
  	  ChannelDistribution::NO_OPINION),
  
  reply_out_token(),

  // activity initialization
  cb_ml_safe(this, &MotionLimiter::doSafe),
  cb_ml_work(this, &MotionLimiter::doWork),
  do_calc(this /* used to be getId()*/, "MotionLimiter main calculation", &cb_ml_work, &cb_ml_safe, ps)
{
  // do the actions you need for the simulation
  for(int i=6;i--;)
    fud_null.data[i] = 0.0;
  fud = fud_null;

  // connect the triggers for simulation
  do_calc.setTrigger(*Ticker::single());
}

bool MotionLimiter::complete()
{
  /* All your parameters have been set. You may do extended
     initialisation here. Return false if something is wrong. */
  if (!fake_io) {
    
    // if we're talking to real motion base, send that data out to DUECA
    reply_out_token.reset
      (new StreamChannelWriteToken<MotionBaseResultData>
       (getId(), NameSet(getEntity(), "MotionBaseResultData", getPart()), 101));

  }
	
  // reset old data tolerance 
  old_data_tolerance = delay_tolerance;

  return true;
}

// destructor
MotionLimiter::~MotionLimiter()
{
  //
}

// as an example, the setTimeSpec function
bool MotionLimiter::setTimeSpec(const TimeSpec& ts)
{
  // a time span of 0 is not acceptable
  if (ts.getValiditySpan() == 0) return false;

  // specify the timespec to the activity
  do_calc.setTimeSpec(ts);

  // apply it to our MotionFilter(s) if we already have one/them
  if (mf)
  mf->set_dt(ts.getDtInSeconds());

  if(filters.size()>0){
    for(vector<GenericMotionFilter*>::const_iterator iter = filters.begin();
	iter != filters.end();iter++){
      (*iter)->set_dt(ts.getDtInSeconds());
    }
  }

  // apply to the engine as well
  mle.setDt(ts.getDtInSeconds());

  // remember my timespec in case we have to pass it on later
  // to a motion filter
  my_time_spec = ts;

  // return true if everything is acceptable
  return true;
}

// get a motion filter from script
bool MotionLimiter::setMotionFilter(ScriptCreatable& mfin, bool in)
{
  // should only be incoming
  if(!in) return false;

  // try a dynamic cast, all filters inherit from GenericMotionFilter
  GenericMotionFilter *f = dynamic_cast<GenericMotionFilter*> (&mfin);

  // failed
  if(f==NULL) {
    E_MOD(classname << " set-motion-filter received something else than a GenericMotionFilter! ");
    return false;
  }
  
  // use it as our motion filter
  mf = f;
  
  // if we already received a main time-spec, pass it on
  mf->set_dt(my_time_spec.getDtInSeconds());

  return true;
}

// add a new motion filter from script to our list
bool MotionLimiter::addMotionFilter(ScriptCreatable& mfin, bool in)
{
  // should only be incoming
  if(!in) return false;

  // try a dynamic cast, all filters inherit from GenericMotionFilter
  GenericMotionFilter *f = dynamic_cast<GenericMotionFilter*> (&mfin);

  // failed
  if(f==NULL) {
    E_MOD(classname << " add-motion-filter received something else than a GenericMotionFilter! ");
    return false;
  }
  
  // put it in the list
  filters.push_back( f );

  // if we already received a main time-spec, pass it on
  filters.back()->set_dt(my_time_spec.getDtInSeconds());

  return true;
}
    
// select a motion filter from our list, can be overriden through MotionConfiguraiton event
bool MotionLimiter::selectMotionFilter(const int& i)
{
  if( i >= 0 && i < (int)filters.size()){
    mf = filters[i];
    mf->reset();// just to be sure
    return true;
  }
  else if (mf != NULL && filters.size() == 0 && i == 0) { // we have only 1 motion filter, also OK
    return true;
  }
  else {
    return false;
  }

}

// set the estimated time delay of the motion system.
bool MotionLimiter::setMotionSystemDelay(const double& d)
{
  // motion_system_delay is in ticks, while d is in seconds
  motion_system_delay = (int)(d / Ticker::single()->getTimeGranule());

  D_MOD(classname << " using motion system delay of " << motion_system_delay << " ticks, with time granule of "
	<< Ticker::single()->getTimeGranule());
  return true;
}

// and the checkTiming function
bool MotionLimiter::checkTiming(const vector<int>& i)
{
  if (i.size() == 3) {
    myTimingCheck = new TimingCheck(do_calc, i[0], i[1], i[2]);
  }
  else if (i.size() == 2) {
    myTimingCheck = new TimingCheck(do_calc, i[0], i[1]);
  }
  else {
    return false;
  }
  return true;
}

// set reference point for the SimulatorCabMotion channel
bool MotionLimiter::setSCMRefPoint(const int& i)
{
  switch(i) {
  case 0: { // UGP 
    x_SCM_ref = 0.0;
    y_SCM_ref = 0.0;
    z_SCM_ref = 0.0;
    break;
  }
  case 1: { // DERP
    x_SCM_ref = 0.0;
    y_SCM_ref = 0.0;
    z_SCM_ref = -1.2075;
    break;
  }
  case 2: { // OMCT
    x_SCM_ref = 0.0;
    y_SCM_ref = 0.0;
    z_SCM_ref = -1.2075 + 0.35;
    break;
  }
  default: {
    W_MOD(classname << " unknown SCM reference point " << i);
    return false;
  }
  }    
    
  return true;
}

// tell DUECA you are prepared to start your safety work
bool MotionLimiter::isInitialPrepared()
{
  bool res = true;

  // do whatever preparation is necessary
  CHECK_CONDITION(mf);
  CHECK_CONDITION(cur_MotionState == MotionLimiterEngine::DOWN);
  CHECK_TOKEN(input_token);
  CHECK_TOKEN(length_token);
  CHECK_TOKEN(pva_token);
  CHECK_TOKEN(gimbal_token);
  CHECK_TOKEN(filter_output_token);
  CHECK_TOKEN(filter_user_token);
  CHECK_TOKEN(confirm_token);
  CHECK_TOKEN(result_token);
  if (reply_out_token) CHECK_TOKEN(*reply_out_token);
  
  I_MOD("MotionLimiter " << ( res? "is " : "is not ") << "initial prepared");

  return res;
}

// tell DUECA you are prepared
bool MotionLimiter::isPrepared()
{
  bool res = true;

  // do whatever calculations you need to prepare the model. Return
  // with false if something is wrong
  CHECK_CONDITION(cur_MotionState == MotionLimiterEngine::DOWN);

  if(!fake_io) {

#ifdef HAVE_ETHERCAT
    CHECK_CONDITION(interface->isOperational());
#endif
    
    CHECK_CONDITION(commsOK);
    CHECK_CONDITION(downOK);
  }

  I_MOD("MotionLimiter " << ( res? "is " : "is not ") << "prepared");

  // only return true if the hardware you are handling responds OK
  // and the model stuff is also OK, e.g. all tokens are valid
  return res;
}

// start the module
void MotionLimiter::initialStartModule(const TimeSpec &time)
{
  do_calc.switchOn(time);
  do_calc.switchSafe(time);

  // reset receive activity state
  commsOK = false;

  // starting
  starting = true;

  D_MOD(classname << " initial start @ " << time);

  /*
#ifdef HAVE_ETHERCAT
  D_MOD(classname << " opening EtherCAT device");
  interface->open(my_time_spec.getDtInSeconds());
#endif
  */
}

// start the module
void MotionLimiter::startModule(const TimeSpec &time)
{
  do_calc.switchWork(time);
}

// stop the module work
void MotionLimiter::stopModule(const TimeSpec &time)
{
  do_calc.switchSafe(time);
}

// also stop the safe mode
void MotionLimiter::finalStopModule(const TimeSpec& time)
{
  D_MOD(classname << " final stop @ " << time);

  // stopping, not starting
  starting = false;

  /*
  if(!fake_io)  {
    // squeeze off a final cmdShutDown command to the MCC

#ifdef HAVE_ETHERCAT
    interface->dueca_tick = time.getValidityStart();
    interface->host_command = MotionInterface::CmdShutdown;
    interface->write();
    
    interface->close();
#endif
  }
  */

  do_calc.switchOff(time);
}

// fill a snapshot with state data. You may remove this method (and the
// declaration) if you specified to the SimulationModule that the size of
// state snapshots is zero
void MotionLimiter::fillSnapshot(const TimeSpec& ts,
                              Snapshot& snap, bool from_trim)
{
  // The most efficient way of filling a snapshot is with an AmorphStore
  // object.
  AmorphStore s(snap.accessData(), snap.getDataSize());

  if (from_trim) {
    // use packData(s, trim_state_variable1); ... to pack your state into
    // the snapshot
  }
  else {
    // this is a snapshot from the running simulation. Dusime takes care
    // that no other snapshot is taken at the same time, so you can safely
    // pack the data you copied into (or left into) the snapshot state
    // variables in here
    // use packData(s, snapshot_state_variable1); ...
  }
}

// reload from a snapshot. You may remove this method (and the
// declaration) if you specified to the SimulationModule that the size of
// state snapshots is zero
void MotionLimiter::loadSnapshot(const TimeSpec& t, const Snapshot& snap)
{
  // access the data in the snapshot with an AmorphReStore object
  AmorphReStore s(snap.data, snap.data_size);

  // use unPackData(s, real_state_variable1 ); ... to unpack the data
  // from the snapshot.
  // You can safely do this, while snapshot loading is going on the
  // simulation is in HoldCurrent or the activity is stopped.
}

// bring our representation of the simulator motion state up-to-date
// with the one of the engine, because he's the one who really knows
// this is called before giving the motion-filter our state and
// possibly (16AUG2001) before we use sms to fill our output MCPVA
void MotionLimiter::updateSimulatorMotionState()
{
  sms.x =  mle.getPlatformPosition(1);
  sms.y =  mle.getPlatformPosition(2);
  sms.z =  mle.getPlatformPosition(3);
  sms.q0 = mle.getPlatformAttitude(4);
  sms.q1 = mle.getPlatformAttitude(1);
  sms.q2 = mle.getPlatformAttitude(2);
  sms.q3 = mle.getPlatformAttitude(3);
  sms.xdot = mle.getPlatformVelocity(1);
  sms.ydot = mle.getPlatformVelocity(2);
  sms.zdot = mle.getPlatformVelocity(3);
  sms.p = mle.getPlatformRotation(1);
  sms.q = mle.getPlatformRotation(2);
  sms.r = mle.getPlatformRotation(3);
  sms.theta = asin(2.0*sms.q2*sms.q0-2.0*sms.q1*sms.q3);
  sms.psi = acos( limit1((sms.q0*sms.q0+sms.q1*sms.q1-sms.q2*sms.q2-sms.q3*sms.q3)/cos(sms.theta)) ) *
    SIGN(sms.q1*sms.q2+sms.q0*sms.q3);
  sms.phi = acos( limit1((sms.q0*sms.q0-sms.q1*sms.q1-sms.q2*sms.q2+sms.q3*sms.q3)/cos(sms.theta)) ) *
    SIGN(sms.q2*sms.q3+sms.q0*sms.q1);
  
}

// tally a communication error, revert to safe mode if it's too soon after the previous one
void MotionLimiter::flagCommError(const TimeSpec& ts)
{
  static TimeSpec previous_error = 0;
  const int timeout = 2;

  // if the last error occurred too short ago, panic
  if( (ts.getValidityStart()-previous_error.getValidityStart()) < timeout*my_time_spec.getValiditySpan()) {
    commsOK = false;
    
    if(do_calc.isWorking(ts)) {
#ifndef IGNORE_COMMS_ERRORS
      do_calc.criticalErrorNodeWide();
      E_MOD("MotionLimiter got too many communication errors, reverting to safe mode");
#else //IGNORE_COMMS_ERRORS
      E_MOD("MotionLimiter got too many communication errors, we would normally revert to safe mode (IGNORE_COMMS_ERRORS is defined)");
      if(myTimingCheck != NULL) myTimingCheck->userReportsAnomaly();
#endif //IGNORE_COMMS_ERRORS
    }
    
  }

  previous_error = ts;
}

// tally a motion error, revert to safe mode if it's too soon after the previous one
void MotionLimiter::flagMotionError(const TimeSpec& ts)
{
  static TimeSpec previous_error = 0;
  const int timeout = 2;

  // if the last error occurred too short ago, panic
  if( (ts.getValidityStart()-previous_error.getValidityStart()) < timeout*my_time_spec.getValiditySpan())  {
    if(do_calc.isWorking(ts)) {
#ifndef IGNORE_MOTION_ERRORS
      do_calc.criticalErrorNodeWide();
      E_MOD("MotionLimiter got too many motion errors, reverting to safe mode");
#else //IGNORE_MOTION_ERRORS
      E_MOD("MotionLimiter got too many motion errors, we would normally revert to safe mode (IGNORE_MOTION_ERRORS is defined)");
#endif //IGNORE_MOTION_ERRORS
    }
  }
  
  previous_error = ts;
}

void MotionLimiter::writeMotion(const MotionCommandedPosVelAcc& commanded, 
				int cmd)
{
  if(checkMLESanity()) {

#ifdef HAVE_ETHERCAT
    // send it to the motion base
    interface->host_setpoints.X = commanded.x;
    interface->host_setpoints.Y = commanded.y;
    interface->host_setpoints.Z = commanded.z;
    interface->host_setpoints.phi = commanded.phi;
    interface->host_setpoints.theta = commanded.theta;
    interface->host_setpoints.psi = commanded.psi;
    interface->host_setpoints.Xdot = commanded.xdot;
    interface->host_setpoints.Ydot = commanded.ydot;
    interface->host_setpoints.Zdot = commanded.zdot;
    interface->host_setpoints.p = commanded.p;
    interface->host_setpoints.q = commanded.q;
    interface->host_setpoints.r = commanded.r;
    interface->host_setpoints.Xddot = commanded.xdotdot;
    interface->host_setpoints.Yddot = commanded.ydotdot;
    interface->host_setpoints.Zddot = commanded.zdotdot;
    interface->host_setpoints.pdot = commanded.pdot;
    interface->host_setpoints.qdot = commanded.qdot;
    interface->host_setpoints.rdot = commanded.rdot;

    switch(cmd) {
    case CMD_SHUTDOWN: {
      interface->host_command = MotionInterface::CmdShutdown;
      break;
    }
    case CMD_ERROR: {
      interface->host_command = MotionInterface::CmdError;
      break;
    }
    case CMD_DOWNANDLOCK: {
      interface->host_command = MotionInterface::CmdDownLock;
      break;
    }
    case CMD_NEUTRAL: {
      interface->host_command = MotionInterface::CmdNeutral;
      break;
    }
    case CMD_DITHER: {
      interface->host_command = MotionInterface::CmdDither;
      break;
    }
    case CMD_CUE: {
      interface->host_command = MotionInterface::CmdCue;
      break;
    }
    default: {
      interface->host_command = MotionInterface::CmdCue;
      break;
    }
    }
#endif
    
  } else {
      E_MOD(classname << " MLE is severely confused, stopping motion");

#ifdef HAVE_ETHERCAT
      interface->host_command = MotionInterface::CmdError;
#endif
    }
}  

// put an extra limit on the input to the MLE
void MotionLimiter::preLimit(SimulatorMotionAcceleration &sma)
{
  if (sma.xdotdot > surge_pre_limit) 
  {
    sma.xdotdot = surge_pre_limit;
    W_MOD("MotionLimiter limiting surge to " << surge_pre_limit << " m/s2");
  }
  if (sma.xdotdot < -surge_pre_limit) 
  {
    sma.xdotdot = -surge_pre_limit;
    W_MOD("MotionLimiter limiting surge to " << -surge_pre_limit << " m/s2");
  }

  if (sma.ydotdot > sway_pre_limit) 
  {
    sma.ydotdot = sway_pre_limit;
    W_MOD("MotionLimiter limiting sway to " << sway_pre_limit << " m/s2");
  }
  if (sma.ydotdot < -sway_pre_limit) 
  {
    sma.ydotdot = -sway_pre_limit;
    W_MOD("MotionLimiter limiting sway to " << -sway_pre_limit << " m/s2");
  }
  
  if (sma.zdotdot > heave_pre_limit) 
  { 
    sma.zdotdot = heave_pre_limit;
    W_MOD("MotionLimiter limiting heave to " << heave_pre_limit << " m/s2");
  }
  if (sma.zdotdot < -heave_pre_limit) 
  {
    sma.zdotdot = -heave_pre_limit;
    W_MOD("MotionLimiter limiting heave to " << -heave_pre_limit << " m/s2");
  }

  if (sma.pdot > roll_pre_limit) 
  {
    sma.pdot = roll_pre_limit;
    W_MOD("MotionLimiter limiting roll to " << roll_pre_limit << " rad/s2");
  }
  if (sma.pdot < -roll_pre_limit) 
  {
    sma.pdot = -roll_pre_limit;
    W_MOD("MotionLimiter limiting roll to " << -roll_pre_limit << " rad/s2");
  }

  if (sma.qdot > pitch_pre_limit) 
  {
    sma.qdot = pitch_pre_limit;
    W_MOD("MotionLimiter limiting pitch to " << pitch_pre_limit << " rad/s2");
  }
  if (sma.qdot < -pitch_pre_limit) 
  {
    sma.qdot = -pitch_pre_limit;
    W_MOD("MotionLimiter limiting pitch to " << -pitch_pre_limit << " rad/s2");
  }
  
  if (sma.rdot > yaw_pre_limit) 
  { 
    sma.rdot = yaw_pre_limit;
    W_MOD("MotionLimiter limiting yaw to " << yaw_pre_limit << " rad/s2");
  }
  if (sma.rdot < -yaw_pre_limit) 
  {
    sma.rdot = -yaw_pre_limit;
    W_MOD("MotionLimiter limiting yaw to " << -yaw_pre_limit << " rad/s2");
  }
}

// catching nasty input, returns true if there's a problem
bool MotionLimiter::sanitizeInput(VehicleCabMotion& vcm)
{
  bool nasty = false;

  if(!finite(vcm.xdotdot)) {
    nasty = true;
    vcm.xdotdot = 0.0;
  }

  if(!finite(vcm.ydotdot)) {
    nasty = true;
    vcm.ydotdot = 0.0;
  }

  if(!finite(vcm.zdotdot)) {
    nasty = true;
    vcm.zdotdot = 0.0;
  }

  if(!finite(vcm.fx)) {
    nasty = true;
    vcm.fx = 0.0;
  }

  if(!finite(vcm.fy)) {
    nasty = true;
    vcm.fy = 0.0;
  }

  if(!finite(vcm.fz)) {
    nasty = true;
    vcm.fz = - 9.81;
  }

  if(!finite(vcm.xdot)) {
    nasty = true;
    vcm.xdot = 0.0;
  }

  if(!finite(vcm.ydot)) {
    nasty = true;
    vcm.ydot = 0.0;
  }

  if(!finite(vcm.zdot)) {
    nasty = true;
    vcm.zdot = 0.0;
  }

  if(!finite(vcm.pdot)) {
    nasty = true;
    vcm.pdot = 0.0;
  }

  if(!finite(vcm.qdot)) {
    nasty = true;
    vcm.qdot = 0.0;
  }

  if(!finite(vcm.rdot)) {
    nasty = true;
    vcm.rdot = 0.0;
  }

  if(!finite(vcm.p)) {
    nasty = true;
    vcm.p = 0.0;
  }

  if(!finite(vcm.q)) {
    nasty = true;
    vcm.q = 0.0;
  }

  if(!finite(vcm.r)) {
    nasty = true;
    vcm.r = 0.0;
  }

  return nasty;
}

// catching nasty output from motion filter, returns true if there's a problem
bool MotionLimiter::sanitizeMFOutput(SimulatorMotionAcceleration& sma)
{
  bool nasty = false;

  if(!finite(sma.xdotdot)) {
    nasty = true;
    sma.xdotdot = 0.0;
  }
  if(!finite(sma.ydotdot)) {
    nasty = true;
    sma.ydotdot = 0.0;
  }
  if(!finite(sma.zdotdot)) {
    nasty = true;
    sma.zdotdot = 0.0;
  }
  if(!finite(sma.pdot)) {
    nasty = true;
    sma.pdot = 0.0;
  }
  if(!finite(sma.qdot)) {
    nasty = true;
    sma.qdot = 0.0;
  }
  if(!finite(sma.rdot)) {
    nasty = true;
    sma.rdot = 0.0;
  }

  return nasty;
}

// check sanity of motion limiter itself
bool MotionLimiter::checkMLESanity()
{
  bool mle_ok = true;

  // just check pos/att for now
  CmdPos pos = getCmdPos();

  if(fabs(pos.x) > 1.5 || !finite(pos.x)) 
    mle_ok = false;
  if(fabs(pos.y) > 1.5 || !finite(pos.y)) 
    mle_ok = false;
  if(fabs(pos.z) > 3.0 || !finite(pos.z)) 
    mle_ok = false;
  if(fabs(pos.phi) > 1.0 || !finite(pos.phi)) 
    mle_ok = false;
  if(fabs(pos.theta) > 1.0 || !finite(pos.theta)) 
    mle_ok = false;
  if(fabs(pos.psi) > 1.0 || !finite(pos.psi)) 
    mle_ok = false;
 
  return mle_ok;
}

void MotionLimiter::sendLogData(const TimeSpec& ts, const SimulatorMotionAcceleration& mf_output, 
				const int& status)
{
  sendLogData(ts, mf_output, fud_null, status);
}


// 09JUN2002 send all the data to be logged over our DUECA channels
void MotionLimiter::sendLogData(const TimeSpec& ts, const SimulatorMotionAcceleration& mf_output, 
				const MotionFilterUserData& usr_data, const int& status)
{
    StreamWriter<MotionActuatorLengths> mal(length_token, ts);
    StreamWriter<MotionGimbalPositions> mgp(gimbal_token, ts);
    StreamWriter<MotionCommandedPosVelAcc> mcpva(pva_token, ts);
    StreamWriter<SimulatorMotionAcceleration> sma(filter_output_token,ts);
    StreamWriter<SimulatorCabMotion> scm(result_token, ts);
    StreamWriter<MotionFilterUserData> mfud(filter_user_token, ts);

    for (int i=0;i<6;++i) {
      // MotionActuatorLengths for logging
      mal.data().j[i] = mle.getJackLength(i+1);
      mal.data().jd[i] = mle.getJackVelocity(i+1);
      mal.data().jdd[i] = mle.getJackAcceleration(i+1);
      mal.data().status = status;

      // MotionGimbalPositions for MotionViewer
      mgp.data().x[i] = mle.getUGPointX(i+1);
      mgp.data().y[i] = mle.getUGPointY(i+1);
      mgp.data().z[i] = mle.getUGPointZ(i+1);
      mgp.data().status = status;
    }

    // MotionCommandedPosVelAcc for logging
    // remember this is inertial and in upper gimbal center
    MotionCommandedPosVelAcc cpva_ug_inertial = getMCPVA();
    cpva_ug_inertial.status = status;
    mcpva.data() = cpva_ug_inertial;

    // SimulatorMotionAcceleration for logging
    // output of motionfilter, this is also inertial/upper gimbal
    sma.data() = mf_output;

    // SimulatorCabMotion for logging
    // can be compared directly to VehicleCabMotion from CabinPositionCorrector
    SimulatorCabMotion scm_ug, scm_ref;

    // 1) convert accelerations and velocities from inertial to body
    //    assume sms is up-to-date
    //    not sure about this
    double sf, cf, st, ct, sp, cp;
    sf = sin(sms.phi); cf = cos(sms.phi);
    st = sin(sms.theta); ct = cos(sms.theta);
    sp = sin(sms.psi); cp = cos(sms.psi);

    scm_ug.xdotdot = ct*cp * cpva_ug_inertial.xdotdot +
                     ct*sp * cpva_ug_inertial.ydotdot -
                     st    * cpva_ug_inertial.zdotdot;

    scm_ug.ydotdot = (sf*st*cp - cf*sp) * cpva_ug_inertial.xdotdot +
                     (sf*st*sp + cf*cp) * cpva_ug_inertial.ydotdot +
                     (sf*ct)            * cpva_ug_inertial.zdotdot;

    scm_ug.zdotdot = (cf*st*cp + sf*sp) * cpva_ug_inertial.xdotdot +
                     (cf*st*sp - sf*cp) * cpva_ug_inertial.ydotdot +
                     (cf*ct)            * cpva_ug_inertial.zdotdot;


    scm_ug.xdot = ct*cp * cpva_ug_inertial.xdot +
                  ct*sp * cpva_ug_inertial.ydot -
                  st    * cpva_ug_inertial.zdot;

    scm_ug.ydot = (sf*st*cp - cf*sp) * cpva_ug_inertial.xdot +
                  (sf*st*sp + cf*cp) * cpva_ug_inertial.ydot +
                  (sf*ct)            * cpva_ug_inertial.zdot;

    scm_ug.zdot = (cf*st*cp + sf*sp) * cpva_ug_inertial.xdot +
                  (cf*st*sp - sf*cp) * cpva_ug_inertial.ydot +
                  (cf*ct)            * cpva_ug_inertial.zdot;

    // 2) convert from upper gimbal to reference point for SCM (e.g. DERP)

    // velocity
    double p = cpva_ug_inertial.p;
    double q = cpva_ug_inertial.q;
    double r = cpva_ug_inertial.r;

    scm_ref.xdot =              - r*y_SCM_ref + q*z_SCM_ref + scm_ug.xdot;
    scm_ref.ydot =  r*x_SCM_ref               - p*z_SCM_ref + scm_ug.ydot;
    scm_ref.zdot = -q*x_SCM_ref + p*y_SCM_ref               + scm_ug.zdot;

    // acceleration
    double pd = cpva_ug_inertial.pdot;
    double qd = cpva_ug_inertial.qdot;
    double rd = cpva_ug_inertial.rdot;

    scm_ref.xdotdot = (-r*r - q*q)*x_SCM_ref + (p*q - rd)  *y_SCM_ref + (qd + p*r)  *z_SCM_ref + scm_ug.xdotdot;
    scm_ref.ydotdot = (rd + p*q)  *x_SCM_ref + (-r*r - p*p)*y_SCM_ref + (q*r - pd)  *z_SCM_ref + scm_ug.ydotdot;
    scm_ref.zdotdot = (p*r - qd)  *x_SCM_ref + (q*r + pd)  *y_SCM_ref + (-q*q - p*p)*z_SCM_ref + scm_ug.zdotdot;

    // rotations
    scm_ref.p = p;
    scm_ref.q = q;
    scm_ref.r = r;

    scm_ref.pdot = pd;
    scm_ref.qdot = qd;
    scm_ref.rdot = rd;

    // 3) calculate specific forces
    const double g = 9.813;
    scm_ref.fx = scm_ref.xdotdot + g*st;
    scm_ref.fy = scm_ref.ydotdot - g*ct*sf;
    scm_ref.fz = scm_ref.zdotdot - g*ct*cf;

    // 4) fill channel
    scm.data() = scm_ref;

    // filter user data
    mfud.data() = usr_data;
}

MotionCommandedPosVelAcc MotionLimiter::getMCPVA()
{
  MotionCommandedPosVelAcc cpva;

  int status=0; // unused

  // filling it all in
  double q0 = mle.getPlatformAttitude(4);
  double q1 = mle.getPlatformAttitude(1);
  double q2 = mle.getPlatformAttitude(2);
  double q3 = mle.getPlatformAttitude(3);
  cpva.x = mle.getPlatformPosition(1);
  cpva.y = mle.getPlatformPosition(2);
  cpva.z = mle.getPlatformPosition(3);
  cpva.theta = asin(2.0*q2*q0-2.0*q1*q3);
  cpva.psi = acos( limit1((q0*q0+q1*q1-q2*q2-q3*q3)/cos(cpva.theta)) ) *
	SIGN(q1*q2+q0*q3);
  cpva.phi = acos( limit1((q0*q0-q1*q1-q2*q2+q3*q3)/cos(cpva.theta)) ) *
	SIGN(q2*q3+q0*q1);
  cpva.xdot = mle.getPlatformVelocity(1);
  cpva.ydot = mle.getPlatformVelocity(2);
  cpva.zdot = mle.getPlatformVelocity(3);
  cpva.p = mle.getPlatformRotation(1);
  cpva.q = mle.getPlatformRotation(2);
  cpva.r = mle.getPlatformRotation(3);
  cpva.xdotdot = mle.getPlatformAcceleration(1);
  cpva.ydotdot = mle.getPlatformAcceleration(2);
  cpva.zdotdot = mle.getPlatformAcceleration(3);
  cpva.pdot = mle.getPlatformAcceleration(4);
  cpva.qdot = mle.getPlatformAcceleration(5);
  cpva.rdot = mle.getPlatformAcceleration(6);

  cpva.status = status; // zero for now

  return cpva;
}

CmdPos MotionLimiter::getCmdPos()
{
  CmdPos cp;

  double q0 = mle.getPlatformAttitude(4);
  double q1 = mle.getPlatformAttitude(1);
  double q2 = mle.getPlatformAttitude(2);
  double q3 = mle.getPlatformAttitude(3);
  cp.x = mle.getPlatformPosition(1);
  cp.y = mle.getPlatformPosition(2);
  cp.z = mle.getPlatformPosition(3);
  cp.theta = asin(2.0*q2*q0-2.0*q1*q3);
  cp.psi = acos( limit1((q0*q0+q1*q1-q2*q2-q3*q3)/cos(cp.theta)) ) *
	SIGN(q1*q2+q0*q3);
  cp.phi = acos( limit1((q0*q0-q1*q1-q2*q2+q3*q3)/cos(cp.theta)) ) *
	SIGN(q2*q3+q0*q1);

  return cp;
}

// this routine contains the main simulation process of your module. You
// should read the input channels here, and calculate and write the
// appropriate output
void MotionLimiter::doWork(const TimeSpec& ts)
{
  // the data from the model we're going to use
  static VehicleCabMotion cabmotion;

  // the latest reply from the motion base
  bool got_reply=false;
  MotionBaseResultData result;

  // the position setpoints sent out
  CmdPos drive;

  // MLE status
  int status;

  // time for which we want the data
  TimeSpec ts2(ts.getValidityStart()+motion_system_delay,
               ts.getValidityEnd()+motion_system_delay);

#ifdef HAVE_ETHERCAT
  if(!fake_io) {

    // initial work cycle, after module start
    if(do_calc.firstWorkCycle(ts)) {
      D_MOD(classname << " first work cycle @ " << ts);
    }

    // last work cycle, after module stop
    if(do_calc.lastWorkCycle(ts)) {
      D_MOD(classname << " last work cycle @ " << ts);
    }

    // notify the motion system of the time
    interface->dueca_tick = ts.getValidityStart();
    
    // check we have a reply for our previous outgoing packet
    interface->read();
    got_reply = interface->countRecentIOErrorCycles() == 0;
    result.counter = uint32_t(interface->controller_dueca_tick_echo_sl);
    result.status = uint32_t(interface->controller_state);
    result.actual_pos[0] = interface->measured.X;
    result.actual_pos[1] = interface->measured.Y;
    result.actual_pos[2] = interface->measured.Z;
    result.actual_pos[3] = interface->measured.phi;
    result.actual_pos[4] = interface->measured.theta;
    result.actual_pos[5] = interface->measured.psi;
    std::copy(interface->measured.leg.begin(), 
              interface->measured.leg.end(),
              result.actual_len.begin());
  }
#endif

  if (reply_out_token) {
    StreamWriter<MotionBaseResultData> y(*reply_out_token, ts);
    y.data() = result;
  }
  
  if(old_MotionState != cur_MotionState)
  {
     I_MOD("MotionLimiter in work mode: " << cur_MotionState);
  }

  // check the state we are supposed to be in
  switch (getAndCheckState(ts)) {

/*************************************************/
/*                                               */
/*                  INACTIVE                     */
/*                                               */
/*************************************************/
  case SimulationState::Inactive: {
    // we're down
    // 1) check the motion base is down
    // 2) put the MotionLimiterEngine in DOWN
    // 3) send down command
    // 4) produce output for triggering purposes

    if(!fake_io) {
	// 1) reality check
      if(got_reply) {
        // he says he's down & he *is* down
        // else flag motion error
#ifdef HAVE_ETHERCAT
        if (interface->controller_state != MotionInterface::StDownLock) {
	  W_MOD(classname << " motion base not down in Inactive");
          flagMotionError(ts);
        }
#endif
      }
    }
    
    // 2) am I down? I think I'm down, aren't I?
    mle.beDown();

    if(!fake_io) {
      // 3) ...and stay down
      writeMotion(mcpva_down, CMD_DOWNANDLOCK);
    }

    // 4) output for any modules triggering on us
    sendLogData(ts2, sma_null);

    break;
  }

/*************************************************/
/*                                               */
/*          INACTIVE TO HOLDCURRENT              */
/*                                               */
/*************************************************/
  case SimulationState::Inactive_HoldCurrent: {
    // we're going up
    // 1) check whether the motion base arrived in neutral, and switch state
    // 2) send neutral command
    // 3) produce output on the channels

    if(!fake_io) {
	// 1) are we there yet?
      if(got_reply) {
#ifdef HAVE_ETHERCAT
	if( interface->controller_state == MotionInterface::StMoveToNeutral) {
	  // OK, we're still going up
	  cur_MotionState = MotionLimiterEngine::GOING_NEUTRAL;
	  if(old_MotionState == MotionLimiterEngine::DOWN) {
	    I_MOD(classname << " going up, driven by MCC");
	  }
	} else if( interface->controller_state == MotionInterface::StDownLock ) {
	  I_MOD(classname << " waiting to go up, driven by MCC");
	} else if( interface->controller_state == MotionInterface::StNeutral ) {
	  // so he thinks he's neutral ...
#endif
	  // update the MLE
	  mle.beNeutral();
          
	  // signal DUSIME we've completed the transition
	  transitionComplete();

#ifdef HAVE_ETHERCAT
	} else {
	  // something strange
	  W_MOD(classname << " MotionBase reports unexpected state: " << result.status);
	  flagMotionError(ts);
	}
#endif

	// 2) whether we're already there or not, send neutral
        writeMotion(mcpva_neutral, CMD_NEUTRAL);
      } else {
	W_MOD(classname << " no reply in Inactive to HoldCurrent");
      }
    } else { // !fake_io
      // assume we're there
      
      // update the MLE
      mle.beNeutral();
      
      // signal DUSIME we've completed the transition
      transitionComplete();
    }

    // 3) produce output on the channels
    sendLogData(ts2, sma_null);

    break;
    }

/*************************************************/
/*                                               */
/*                  HOLD CURRENT                 */
/*                                               */
/*************************************************/
  case SimulationState::HoldCurrent: {
    // we're up & ready to go
    // 0) see if there is any new configuration requested
    // 1) check we have input from the model, even though it's not used
    // 2) check we all agree on being neutral
    // 3) start filling command history for following performance test
    // 4) send neutral command OR start sending MLE output
    // 5) produce output on the channels

    // 0) handle MotionConfiguration events
    if(conf_in_token.getNumWaitingEvents(ts))
    {
      // confirmation event to be sent out
      bool send_MCout;
      MotionConfiguration MCout;
      MCout.event_type = MotionConfiguration::Confirm;

      try {
	EventReader<MotionConfiguration> mc(conf_in_token, ts);
	
	// is this indeed a request requiring a confirmation?
	if(mc.data().event_type == MotionConfiguration::Request) {
	  send_MCout = true;

	  if(!mc.data().motion) {
	      I_MOD("MotionLimiter turning off motion");
	      stay_still = true;
	      MCout.motion = false;
	  } else {
	    I_MOD("MotionLimiter turning on motion");
	    stay_still = false;
	    MCout.motion = true;
	  }
	  
	  // handle multiple motion filters
	  if( selectMotionFilter(mc.data().filter)){
	    I_MOD("MotionLimiter switching to motion filter # " << mc.data().filter);
	    MCout.filter = mc.data().filter;
	    MCout.filter_confirmed = true;
	  } else {
	    W_MOD("MotionLimiter received invalid request for motion filter # " << mc.data().filter);
	    MCout.filter = mc.data().filter;
	    MCout.filter_confirmed = false;
	  }
	  
	  // handle parameter settings in motion filter
	  if(mc.data().param != -1) {
	    if( mf->set_param(mc.data().param) ) {
	      I_MOD("MotionLimiter selected motion filter parameter set # " << mc.data().param);
	      MCout.param = mc.data().param;
	      MCout.param_confirmed = true;
	    } else {
	      W_MOD("MotionLimiter could not select motion filter parameter set # " << mc.data().param);
	      MCout.param = mc.data().param;
	      MCout.param_confirmed = false;
	    }
	  } else {
	    // still confirm
	    MCout.param = -1;
	    MCout.param_confirmed = true;
	  }
	} else {
	  // probably picked up our own confirmation
	  send_MCout = false;
	}
      }
      catch(Exception& e) {
	W_MOD("MotionLimiter: something went wrong when reading a MotionConfiguration Event");
	flagCommError(ts);
      }
      
      // send out the confirmation
      if(send_MCout) {
	try {
	  EventWriter<MotionConfiguration> mc_out(conf_out_token);
	  mc_out.data() = MCout;
	} catch(Exception& e) {
	  W_MOD("MotionLimiter: something went wrong when send a MotionConfiguration confirmation event");
	}
      }
    }
    
    // 1) try to get input from the model for previous time step
    try {
      StreamReader<VehicleCabMotion> vcm(input_token, ts2);
      // we don't do anything with it, but that's not important
    } catch(Exception& e) {
      W_MOD("MotionLimiter: no data from model during HoldCurrent for " << ts2);
      flagCommError(ts);
    }

    if(!fake_io) {
      // 2) are we really neutral?
      if(got_reply) {
	// he says he's neutral & he *is* neutral
	// else flag motion error
#ifdef HAVE_ETHERCAT
	if (interface->controller_state == MotionInterface::StCue) {
	  W_MOD(classname << " MotionBase (still?) in Cue instead of Neutral");
	} else if (interface->controller_state != MotionInterface::StNeutral) {
	  W_MOD(classname << " MotionBase reports unexpected state");
	  flagMotionError(ts);
	}
#endif
      }

      // 3) DON'T keep a history of commanded setpoints, to be compared to results later

      // 4) keep sending neutral command
      writeMotion(mcpva_neutral, CMD_NEUTRAL);
    }

    // 5) produce output on the channels
    sendLogData(ts2, sma_null);
    
    break;
  }

/*************************************************/
/*                                               */
/*         CALIBRATE TO HOLD CURRENT             */
/*                                               */
/*************************************************/
  case SimulationState::Calibrate_HoldCurrent: {
    // we're dithering, not implemented yet
    // 1) just signal transition complete, untill MCC can do dithering
    // 2) since we know our timespec and are ready to go to Cue, let's set the settling timer here
    //    (see Advance_HoldCurrent) OS 24APR2002
    // 3) produce output on the channels

    // 1)
    transitionComplete();

    // 2)
    settling_time_counter = settling_time/my_time_spec.getDtInSeconds();

    // 3) produce output on the channels
    sendLogData(ts2, sma_null);

    break;
  }

/*************************************************/
/*                                               */
/*               ADVANCE / REPLAY                */
/*                                               */
/*************************************************/
  case SimulationState::Replay:
  case SimulationState::Advance: {
    // we're running
    // 1) check if anybody wants us to go to Neutral
    // if so, follow steps as in AdvanceToHoldCurrent:
    // 2) feed NEUTRAL to MLE, it brakes and returns to neutral
    // 2a) fake motion filter outputs as all zeroes for logging
    // 3) check MLE for transition complete
    // 3a) reset motion filter when done
    // otherwise do our normal stuff:
    // 2) check we have input from model
    // 3) feed model data to MF + MLE
    // the rest is done in both cases:
    // 4) get a packet out to the MCC
    // 4a) 29APR2002 send the output of the motion filter to be logged
    // 5) check MCC reply for following errors
    // 6) keep a history of setpoints to use in 4)

    // 1) handle MotionRequests
    if (request_token.getNumWaitingEvents(ts)) {
      EventReader<MotionRequest> mr(request_token, ts);
      
      if(mr.data().position == MotionRequest::NEUTRAL) {
	neutral_requested = true;
	request_client_name = mr.data().sender;
	I_MOD("MotionLimiter: Neutral position requested by " << request_client_name);
      }
    }

    // a neutral position is wanted, probably for motion tests
    if (neutral_requested) {
      // 2) feed neutral, starts braking
      status = mle.integrate(sma_null, MotionLimiterEngine::IN_NEUTRAL, cur_MotionState);
      
      // 2a) fake the motion filter output for logging
      sma_unsafe_ug = sma_null;
      
      // 3) if my Engine reports arrival in Neutral, I'm almost done!
      if(cur_MotionState == MotionLimiterEngine::IN_NEUTRAL) {
	if(old_MotionState != MotionLimiterEngine::IN_NEUTRAL) {
	  I_MOD("MotionLimiter reports arrival in Neutral, settling");
	}
	 
	if(settling_time_counter) {
	  settling_time_counter--;
	} else {
	  // 3a) reset motion filter and state, and acknowledge request
	  mf->reset();
	  neutral_requested = false;
	   
	  // make sure it's really REALLY in neutral
	  mle.beNeutral();
	   
	  // send event
	  {
	    EventWriter<MotionConfirm> mc(confirm_token);
	    mc.data() = MotionConfirm(request_client_name,MotionConfirm::NEUTRAL);
	  }

	  I_MOD("MotionLimiter settled into neutral");
	  //prepare for the next time
	  settling_time_counter = settling_time/my_time_spec.getDtInSeconds();
	}
      }
    } else {
      
      // 2) try to get input from the model for the time at which it needs to be finished
      try {
	StreamReader<VehicleCabMotion> vcm(input_token, ts2);
	cabmotion = vcm.data();
      } catch(NoDataAvailable& e) {
	double data_age = 0.0;
	DataTimeSpec data_ts;
	
	// if no new data available, get the newest and check its age
	try {
	  StreamReaderLatest<VehicleCabMotion> vcml(input_token);
	  cabmotion = vcml.data();
	  
	  // check the data's age, in seconds
	  data_ts = vcml.timeSpec();
	  data_age = (int(ts2.getValidityStart()) - 
		      int(data_ts.getValidityStart())) * 
	    Ticker::single()->getTimeGranule();
	} catch(Exception& e) {
	  E_MOD(getId() << " caught " << e << " while trying to get older data, going to safe");
	  do_calc.criticalErrorNodeWide();
	}
	
	// absolute maximum age, to catch serious problems
	if (data_age> 0.100) {
	  E_MOD(getId() << " @ " << ts << " wanted " << ts2 << " got " << data_ts
		<< " which is too old (" << data_age << " s), going to safe" );
	  do_calc.criticalErrorNodeWide();
	} else if (!loose_timing) {
	  // keep a tab on how often this happens and go to Hold if we're fed up
	  int staleness = (ts2.getValidityStart() - data_ts.getValidityStart()) / ts.getValiditySpan();
	  old_data_tolerance -= staleness;
	  
	  if(old_data_tolerance < 0) { // that's it!
	    W_MOD(getId() << " @ " << ts << " reached maximum amount of data staleness while trying " <<
		  ts2 << " and getting " << data_ts);
	    {
	      EventWriter<SimStateRequest> ssr(ssr_token);
	      ssr.data() = SimStateRequest(SimulationState::HoldCurrent);
	    }
	  } else {
	    W_MOD(getId() << " @ " << ts << " wanted " << ts2 << " got " << data_ts << 
		  " and will accept " << old_data_tolerance << " more" );
	  }
	} else { // loose timing, just complain and continue
	  W_MOD(getId() << " @ " << ts << " wanted " << ts2 << " got " << data_ts);
	}
      } catch(Exception& e) {
	// this is probably fatal, advise to go to safe
	E_MOD("MotionLimiter: caught other exception: " << e);
	do_calc.criticalErrorNodeWide();
      }

      // 3) filter and limit
      // first make sure we're up-to-date and then
      // let the motion filter do its work
      updateSimulatorMotionState();

      // catch NaN and nasty stuff like that
      if(sanitizeInput(cabmotion)) {
	E_MOD("MotionLimiter encountered unhealthy inputs for " << ts);
	do_calc.criticalErrorNodeWide();
      }

      mf->integrate(cabmotion, sms, sma_unsafe_ug, fud);

      // check for insane motion filter
      if(sanitizeMFOutput(sma_unsafe_ug)) {
	E_MOD("MotionLimiter encountered unhealthy filter outputs for " << ts);
	do_calc.criticalErrorNodeWide();
      }
       
      //  pre-limit the accelerations
      preLimit(sma_unsafe_ug);

      // run the output of the motion filter
      // through the motion limiter
      // allow still motion, i.e. no motion cues, but going neutral & down
      if(stay_still) {
	status = mle.integrate(sma_null, MotionLimiterEngine::ACTIVE, cur_MotionState);
      }	else {
	status = mle.integrate(sma_unsafe_ug, MotionLimiterEngine::ACTIVE, cur_MotionState);
      }
    }

    // from now on the motion limiter engine can be queried
    // for a safe state

    // 4) send it out 
    writeMotion(getMCPVA(), CMD_CUE);
      
    // 4a) output the motion log data
    sendLogData(ts2, sma_unsafe_ug, fud, status);

    // 5) is the motion base following our commands?
    if(!fake_io) {
#ifdef HAVE_ETHERCAT
      if(got_reply) {
	if(interface->controller_state == MotionInterface::StNeutral) {
	  W_MOD(classname << " waiting to go to cue");
	} else if(interface->controller_state != MotionInterface::StCue) {
	  W_MOD(classname << " MotionBase reports unexpected state: " << result.status);
	  flagCommError(ts);
	}
      }
#endif
    }

    break;
  }

/*************************************************/
/*                                               */
/*           ADVANCE TO HOLD CURRENT             */
/*                                               */
/*************************************************/
  case SimulationState::Advance_HoldCurrent: {
    // we're braking
    // 1) check we have input from model, even though it's not used
    // 2) feed NEUTRAL to MLE, it brakes and returns to neutral
    // 3) check MLE for tranistion complete
    // 4) get the packet out to the MCC
    // 5) check MCC reply for following errors
    // 6) keep a history of setpoints to use in 5)

    // 1) try to get input from the model for previous time step, even though it's not used
    try {
      StreamReader<VehicleCabMotion> vcm(input_token, ts2);
    } catch(Exception& e) {
      W_MOD("MotionLimiter: no data from model in Advance to HoldCurrent for " << ts2);
      flagCommError(ts);
    }

    // 2) feed the MLE to brake and return to neutral
    status = mle.integrate(sma_null, MotionLimiterEngine::IN_NEUTRAL, cur_MotionState);
    
    // 3) if my Engine reports arrival in Neutral, I'm almost done!
    if(cur_MotionState == MotionLimiterEngine::IN_NEUTRAL) {
      if(!settling_started) {
	settling_started = true;
      }
      
      if(settling_time_counter > 0) {
	settling_time_counter--;
      } else {
	transitionComplete();
	// reset the motion filter
	mf->reset();
	
	I_MOD("MotionLimiter settled into neutral");
	  
	// really really be in neutral (no more residual velocities)
	mle.beNeutral();

	//prepare for the next time, we're now getting HoldCurrent
	settling_time_counter = settling_time/my_time_spec.getDtInSeconds();
	settling_started = false;
	
	// reset old data tolerance 
	old_data_tolerance = delay_tolerance;
      }
    }

    // from now on the motion limiter engine can be queried
    // for a safe state

    // 4) send it out
    writeMotion(getMCPVA(), CMD_CUE);

    // 4a) keep triggering the logger
    sendLogData(ts2, sma_null);

    // 5) is the motion base following our commands?
    if(!fake_io) {
#ifdef HAVE_ETHERCAT
      if(got_reply) {
	if( interface->controller_state != MotionInterface::StCue) {
	  W_MOD(classname << " MotionBase reports unexpected state: " << result.status);
	  flagCommError(ts);
	}
      }
#endif
    }

    break;
    }

/*************************************************/
/*                                               */
/*          HOLD CURRENT TO INACTIVE             */
/*                                               */
/*************************************************/
  case SimulationState::HoldCurrent_Inactive: {
    // we're going down
    // 1) check whether MCC is down yet
    //    if so, signal DUSIME and reset MLE to DOWN
    // 2) send down packet to MCC
    // 3) produce output on the channels

    if(fake_io) {
      // just assume we're there
      
      // update the MLE
      mle.beDown();
      
      // update our own state
      cur_MotionState = MotionLimiterEngine::DOWN;
      
      // signal DUSIME we've completed the transition
      transitionComplete();
    } else {
      // 1) are we there yet?
      if(got_reply) {
#ifdef HAVE_ETHERCAT
	if(interface->controller_state == MotionInterface::StMoveToDownAndLock) {
	  // OK, we're still going down
	  cur_MotionState = MotionLimiterEngine::GOING_DOWN;
	  if(old_MotionState == MotionLimiterEngine::IN_NEUTRAL)// just one msg
	    I_MOD(classname << " going down, driven by MCC");
	} else if(interface->controller_state == MotionInterface::StNeutral) {
	  I_MOD(classname << " waiting to go down, driven by MCC");
	} else if(interface->controller_state == MotionInterface::StDownLock) {
	  // so he thinks he's down ...
#endif
	  I_MOD("MotionLimiter: arrived down, driven by MCC");

	  // update the MLE
	  mle.beDown();
	  
	  // update our own state
	  cur_MotionState = MotionLimiterEngine::DOWN;
	  
	  // signal DUSIME we've completed the transition
	  transitionComplete();

#ifdef HAVE_ETHERCAT
	} else {
	  // something strange
	  W_MOD(classname << " MotionBase reports unexpected state: " << result.status);
	  flagMotionError(ts);
	}
#endif

      }
      
      // 2) send packet
      writeMotion(mcpva_down, CMD_DOWNANDLOCK);
    }

    //3) produce output on the channels
    sendLogData(ts2, sma_null);

    break;
  }

  default:
    // other states should never be entered for a SimulationModule,
    // HardwareModules on the other hand have more states. Throw an
    // exception if we get here,
    throw CannotHandleState(getId(),GlobalId(), "state unhandled");
  }

  // write to hardware
  if(!fake_io) {
#ifdef HAVE_ETHERCAT
    interface->write();
#endif
  }

  // for next step;
  old_MotionState = cur_MotionState;
  
  if (snapshotNow()) {
  }
}

void MotionLimiter::doSafe(const TimeSpec& ts)
{
  // you may not assume anything about communications, channels, etcetera
  // only control your hardware into a safe mode. No getAndCheckState either,
  // this runs completely alone, aside from comm with the hardware
  
  // process incoming data and prepare output (tick)
  if (!fake_io) {

    // do start-up stuff within Activity
    if(starting) {
      D_MOD(classname << " first cycle/starting, initial startup @ " << ts);
      starting = false;

#ifdef HAVE_ETHERCAT
      // init EtherCAT if first time
      if(!started) {
	D_MOD(classname << " opening EtherCAT device");
	interface->open(my_time_spec.getDtInSeconds());
	started = true;
      }
#endif
    }

#ifdef HAVE_ETHERCAT
    interface->read();

    /*
    D_MOD(classname << " MCC @ " << interface->controller_dueca_tick_echo_tc <<
	  " state: " << interface->controller_state <<
	  " @ " << ts);
    D_MOD(classname << " recent IO error cycles: " << 
	  interface->countRecentIOErrorCycles());
    D_MOD(classname << " Rx position: " << interface->measured.X << ", " <<
	  interface->measured.Y << ", " << interface->measured.Z);
    D_MOD(classname << " ticks: " << interface->controller_dueca_tick_echo_tc <<
	  ", " << interface->controller_dueca_tick_echo_sl << ", secondary: " << 
	  interface->secondary_dueca_tick_echo_tc << ", " << 
	  interface->secondary_dueca_tick_echo_sl << " @ " << ts);
    */

    commsOK = interface->countRecentIOErrorCycles() == 0 &&
      (MotionInterface::StDownLock <= interface->controller_state &&
       interface->controller_state <= MotionInterface::StMoveToDownAndLock);

    // notify the motion system of the time
    interface->dueca_tick = ts.getValidityStart();

#endif
  }

  // check the system state is correct
  downOK = fake_io ||
#ifdef HAVE_ETHERCAT
    interface->controller_state == MotionInterface::StDownLock;
#else
  false;
#endif

   // status from the MLE
  int status = 0;

  // debug
  if(old_MotionState != cur_MotionState) {
    I_MOD("MotionLimiter in safe mode: " << cur_MotionState);
  }
  
  // The MotionLimiterEngine knows what state we're in
  switch (cur_MotionState){
  case MotionLimiterEngine::DOWN: {
    // we're down because a) we're starting up
    //                    b) we've completed a safety stop
    //                    c) we've completed a normal shutdown
    
    if (!fake_io) {
      writeMotion(mcpva_down, CMD_DOWNANDLOCK);
    }
    
    // from now on we can get to work, as queried in isPrepared()

    break;
    }
  case MotionLimiterEngine::IN_NEUTRAL: {

    if(!fake_io) {
      // if countdown expires, start going down, under the direction of the MCC,
      // but keeping our MLE in the loop to keep the states synced.
      // Untill then keep commanding neutral
      if(--neutral_countdown > 20) {
	status = mle.integrate(sma_null, MotionLimiterEngine::IN_NEUTRAL,
			       cur_MotionState);
	
	// write ML output
	writeMotion(getMCPVA(), CMD_CUE);
        
	D_MOD("MotionLimiter: settling " << neutral_countdown);
      } else if (neutral_countdown > 0) {
	writeMotion(mcpva_neutral, CMD_NEUTRAL);
	
	D_MOD("MotionLimiter/safe: sendNeutral " << neutral_countdown);
      }	else {
	writeMotion(mcpva_down, CMD_DOWNANDLOCK);
	D_MOD("MotionLimiter: sending down");
	
	// TODO: use return value (status)
	mle.integrate(sma_null, MotionLimiterEngine::DOWN, cur_MotionState);
      }
    } else {
      // just go down
      cur_MotionState = MotionLimiterEngine::GOING_DOWN;
    }

    break;
    }
  case MotionLimiterEngine::ACTIVE: {
    // this is when we panic into safe mode while moving/cueing.
    // we start the mle braking and send its output to the motion base,
    // keeping it dumb & happy by continuing to send cmdCue.

    // Our module can't be finalStopped until we have replied positively
    // on isInitialPrepared (which has a check on MLE::DOWN), so we can
    // be sure we can finish this state wind down.
    // TODO: use return value (status)
    status = mle.integrate(sma_null, MotionLimiterEngine::IN_NEUTRAL, cur_MotionState);
    writeMotion(getMCPVA(),CMD_CUE);
   
    break;
    }
  case MotionLimiterEngine::GOING_NEUTRAL: {
    // we have braked and come to a standstill, now
    // we're going back to neutral

    // prepare the neutral countdown
#define SECONDS_IN_NEUTRAL 4.0
    neutral_countdown = int(SECONDS_IN_NEUTRAL/my_time_spec.getDtInSeconds());

    // intentional fall-through
    }
  case MotionLimiterEngine::BRAKING:
  case MotionLimiterEngine::STILL:{
    // we're recovering from a panic, moving back to neutral
    // MLE is in command and motion base still thinks we're in cmdCue
    // TODO: use return value (status)
    status = mle.integrate(sma_null, MotionLimiterEngine::IN_NEUTRAL, cur_MotionState);
    
    writeMotion(getMCPVA(), CMD_CUE);
    
    break;
  }
  case MotionLimiterEngine::GOING_DOWN: {
    if(!fake_io) {
      // keep going down, keeping the MLE in the loop
      // this is open loop, so the motion base is not necessarily really down
      // when the mle thinks it is. In isPrepared this is checked before we return to work
      writeMotion(mcpva_down, CMD_DOWNANDLOCK);
      
      // TODO: use return value (status)
      mle.integrate(sma_null, MotionLimiterEngine::DOWN, cur_MotionState);
    } else {
	mle.beDown();
	cur_MotionState = MotionLimiterEngine::DOWN;
    }

    break;
  }
  default: {
    // nothing, rest is old testing modes
    break;
  }
  }

  // write to actual hardware
  if(!fake_io) {
#ifdef HAVE_ETHERCAT
    interface->write();
#endif
  }

  // for next step
  old_MotionState = cur_MotionState;
}

void MotionLimiter::trimCalculation(const TimeSpec& ts, const TrimMode& mode)
{
  //
}

// Make a TypeCreator object for this module, the TypeCreator
// will check in with the scheme-interpreting code, and enable the
// creation of modules of this type
static TypeCreator<MotionLimiter> a(MotionLimiter::getMyParameterTable());

CmdPos::CmdPos(double X, double Y, double Z, double Phi, double Theta, double Psi):
x(X), y(Y), z(Z), phi(Phi), theta(Theta), psi(Psi)
{}

CmdPos::CmdPos():
x(0.0), y(0.0), z(0.0), phi(0.0), theta(0.0), psi(0.0)
{}

CmdPos::~CmdPos()
{}
