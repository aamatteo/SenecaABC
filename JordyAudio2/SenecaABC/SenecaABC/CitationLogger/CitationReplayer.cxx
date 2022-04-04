/* ------------------------------------------------------------------   */
/*      item            : CitationReplayer.cxx
        made by         : stroosma
	from template   : DusimeModuleTemplate.cxx
        template made by: Rene van Paassen
        date            : Thu Mar  2 12:13:32 2006
	category        : body file 
        description     : 
	changes         : Thu Mar  2 12:13:32 2006 first version
	template changes: 030401 RvP Added template creation comment
        language        : C++
*/

static const char c_id[] =
"$Id: CitationReplayer.cxx,v 1.1.1.1 2022/02/17 15:04:28 matteopiras Exp $";

#define CitationReplayer_cxx
// include the definition of the module class
#include "CitationReplayer.hxx"

// include the debug writing header, by default, write warning and 
// error messages
//#define D_MOD
#define I_MOD
#define W_MOD
#define E_MOD
#include <debug.h>

// include additional files needed for your calculation here
#include <cmath>
#include <Ticker.hxx>

// the standard package for DUSIME, including template source
#define DO_INSTANTIATE
#include <dusime.h>

// class/module name
const char* const CitationReplayer::classname = "citation-replayer";

// initial condition/trim table
const IncoTable* CitationReplayer::getMyIncoTable()
{
  static IncoTable inco_table[] = {
    // enter pairs of IncoVariable and VarProbe pointers (i.e. 
    // objects made with new), in this table.
    // For example
//    {(new IncoVariable("example", 0.0, 1.0, 0.01))
//     ->forMode(FlightPath, Constraint)
//     ->forMode(Speed, Control),
//     new VarProbe<CitationReplayer,double>
//       (REF_MEMBER(&CitationReplayer::i_example))}
    
    // always close off with:
    { NULL, NULL} };

  return inco_table;
}

// parameters to be inserted
const ParameterTable* CitationReplayer::getMyParameterTable()
{
  static const ParameterTable parameter_table[] = {
    /*{ "set-timing", 
      new MemberCall<CitationReplayer,TimeSpec>
      (&CitationReplayer::setTimeSpec), set_timing_description },*/

    { "check-timing", 
      new MemberCall<CitationReplayer,vector<int> >
      (&CitationReplayer::checkTiming), check_timing_description },

    { "file-name",
      new MemberCall<CitationReplayer,vstring>
      (&CitationReplayer::setFileName)},

    { "continuous-playback",
      new VarProbe<CitationReplayer,bool>
      (&CitationReplayer::continuous_playback)},

    { "use-motion",
      new VarProbe<CitationReplayer,bool>
      (&CitationReplayer::use_motion)},

    { "reset-in-hold",
      new VarProbe<CitationReplayer,bool>
      (&CitationReplayer::reset_in_hold)},

    /* You can extend this table with labels and MemberCall or
       VarProbe pointers to perform calls or insert values into your
       class objects. Please also add a description (c-style string).  

       Note that for efficiency, set_timing_description and
       check_timing_description are pointers to pre-defined strings,
       you can simply enter the descriptive strings in the table. */

    /* The table is closed off with NULL pointers for the variable
       name and MemberCall/VarProbe object. The description is used to
       give an overall description of the module. */
    { NULL, NULL, "please give a description of this module"} };

  return parameter_table;
}

// constructor
CitationReplayer::CitationReplayer(Entity* e, const char* part, const
		       PrioritySpec& ps) :
  /* The following line initialises the SimulationModule base class. 
     You always pass the pointer to the entity, give the classname and the 
     part arguments.
     If you give a NULL pointer instead of the inco table, you will not be 
     called for trim condition calculations, which is normal if you for 
     example implement logging or a display.
     If you give 0 for the snapshot state, you will not be called to 
     fill a snapshot, or to restore your state from a snapshot. Only 
     applicable if you have no state. */
  SimulationModule(e, classname, part, getMyIncoTable(), 0),

  // initialize the data you need in your simulation
  hold_req_made(false),
  neutral_req_made(false),
  continuous_playback(false),
  use_motion(false),
  reset_in_hold(true),
  // VehicleCabPosition
  xcab(1.0), ycab(0.0), zcab(-0.25), //xcab(3.2), ycab(0.0), zcab(-0.75), //Peter: updated
  sf(0.0),cf(1.0),st(0.0),ct(1.0),sp(0.0),cp(1.0),
  //
  dt(-1.0),
  fade_in(0.0),

  // initialize the data you need for the trim calculation

  // initialize the channel access tokens
  // example
  // my_token(getId(), NameSet(getEntity(), "MyData", part)),
  state_token(getId(), NameSet(getEntity(), "CitationOutput", part), 101),
  vcp_token(getId(), NameSet(getEntity(), "VehicleCabPosition", part),101),
  vcm_token(getId(), NameSet(getEntity(), "VehicleCabMotion", part),101),
  snd_token(getId(), NameSet(getEntity(), "PropSoundData", part)),
  hold_request_token(getId(), NameSet("dusime", "SimStateRequest", ""),
	  ChannelDistribution::NO_OPINION),
  motion_request_token(getId(), NameSet(getEntity(), "MotionRequest", part)),
  motion_confirm_token(getId(), NameSet(getEntity(), "MotionConfirm", part)),
  // malfunctions status update/feedback
  mass_feedback_token(getId(), NameSet(getEntity(), "MassEvent", "feedback")), //TODO send data from log

  // activity initialization
  cb1(this, &CitationReplayer::doCalculation),
  do_calc(getId(), "replaying a log file", &cb1, ps)
{
  // do the actions you need for the simulation

  // connect the triggers for simulation
  do_calc.setTrigger(*Ticker::single());
  
  // connect the triggers for trim calculation. Leave this out if you 
  // don not need input for trim calculation 
  //trimCalculationCondition(/* fill in your trim triggering channels */);
}

bool CitationReplayer::complete()
{
  /* All your parameters have been set. You may do extended
     initialisation here. Return false if something is wrong. */
  bool result = true;

  result = readData();

  if(!result) E_MOD(classname << ": couldn't read file");

  return result;
}

// destructor
CitationReplayer::~CitationReplayer()
{
  //
}

// as an example, the setTimeSpec function
/*bool CitationReplayer::setTimeSpec(const TimeSpec& ts)
{
  // a time span of 0 is not acceptable
  if (ts.getValiditySpan() == 0) return false;

  // specify the timespec to the activity
  do_calc.setTimeSpec(ts);

  // do whatever else you need to process this in your model
  // hint: ts.getDtInSeconds()

  // return true if everything is acceptable
  return true;
}*/

// and the checkTiming function
bool CitationReplayer::checkTiming(const vector<int>& i)
{
  if (i.size() == 3) {
    new TimingCheck(do_calc, i[0], i[1], i[2]);
  }
  else if (i.size() == 2) {
    new TimingCheck(do_calc, i[0], i[1]);
  }
  else {
    return false;
  }
  return true;
}

bool CitationReplayer::setFileName(const vstring& fname)
{
  I_MOD(classname << ": playing from log file " << fname);
  
  file_stream.open(fname.data(), fstream::in);

  bool result = file_stream.is_open();

  if(!result) E_MOD(classname << ": couldn't open file " << fname);

  return result;
}

// tell DUECA you are prepared
bool CitationReplayer::isPrepared()
{
  // do whatever additional calculations you need to prepare the model.
  bool res = true;
  
  // check tokens
  //CHECK_TOKEN();
  CHECK_TOKEN(state_token);
  CHECK_TOKEN(vcp_token);
  CHECK_TOKEN(vcm_token);
  CHECK_TOKEN(snd_token);
  
  CHECK_TOKEN(hold_request_token);
  CHECK_TOKEN(motion_request_token);
//  CHECK_TOKEN(motion_confirm_token);

  // malfunctions status update/feedback
  CHECK_TOKEN(mass_feedback_token);

  // Check that all conditions for running are good. 
  // It helps to indicate what the problems are
//  bool res = state_token.isValid() && hold_request_token.isValid() && motion_request_token.isValid();

  if (use_motion) res &= motion_confirm_token.isValid();

  if (!res) {
    W_MOD(getId() << '/' << classname << " not prepared, flags=" <<
	  state_token.isValid() << hold_request_token.isValid() <<
	  motion_request_token.isValid() << 
	  (use_motion ? motion_confirm_token.isValid() : true));
  }

  // return result of check
  return res;
}

// start the module
void CitationReplayer::startModule(const TimeSpec &time)
{
  do_calc.switchOn(time);
  
  // rewind the tape
  state_iter = state_queue.begin();
}

// stop the module
void CitationReplayer::stopModule(const TimeSpec &time)
{
  do_calc.switchOff(time);
}

// fill a snapshot with state data. You may remove this method (and the
// declaration) if you specified to the SimulationModule that the size of 
// state snapshots is zero
void CitationReplayer::fillSnapshot(const TimeSpec& ts, 
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
void CitationReplayer::loadSnapshot(const TimeSpec& t, const Snapshot& snap)
{
  // access the data in the snapshot with an AmorphReStore object
  AmorphReStore s(snap.data, snap.data_size);

  // use unPackData(s, real_state_variable1 ); ... to unpack the data 
  // from the snapshot. 
  // You can safely do this, while snapshot loading is going on the 
  // simulation is in HoldCurrent or the activity is stopped. 
}

// this routine contains the main simulation process of your module. You 
// should read the input channels here, and calculate and write the 
// appropriate output
void CitationReplayer::doCalculation(const TimeSpec& ts)
{
  CitationOutput Y;

  // check the state we are supposed to be in
  switch (getAndCheckState(ts)) {
  case SimulationState::HoldCurrent: {
    // only repeat the output, do not change the model state
	fade_in=0;
    
    if(reset_in_hold) {
      state_iter = state_queue.begin();
      D_MOD(classname << ": reset in hold");
    }

    Y = *state_iter;

    hold_req_made = false;

    break;
  }
  case SimulationState::Replay:
  case SimulationState::Advance: {
    // do the simulation calculations, one step
    Y = *state_iter;
    
	// let fade_in increase to 1 over a period of 2 seconds
	fade_in = fmin(1, fade_in + dt/2.0f);

    if(continuous_playback) { // at the end, return to neutral and start from the top
      if(!neutral_req_made) {
	++state_iter;

	if(state_iter==state_queue.end()) {
	  motion_request_token.sendEvent (new MotionRequest("CitationReplayer", MotionRequest::NEUTRAL), ts);
	  --state_iter;// back one up
	  neutral_req_made = true;
	  I_MOD(classname << ": reached end of playback, requesting Motion Neutral");
	}
      }
      else {
	if(use_motion) {
	  if (motion_confirm_token.getNumWaitingEvents(ts)) {
	    EventReader<MotionConfirm> mc(motion_confirm_token, ts);
	    
	    if(mc.data().position == MotionConfirm::NEUTRAL) {
	      state_iter = state_queue.begin();
	      neutral_req_made = false;
	      I_MOD(classname << ": Motion Neutral request granted, rewinding playback");
	    }
	  }
	}
	else {
	  state_iter = state_queue.begin();
	  neutral_req_made = false;
	  I_MOD(classname << ": Motion Neutral request ignored, rewinding playback");
	}
      }
    }
	else { // at the end, switch to holdcurrent
		if (!hold_req_made) {
			++state_iter;
			
			if (state_iter==state_queue.end()) {
				--state_iter;// back one up
				hold_request_token.sendEvent (new SimStateRequest(SimulationState::HoldCurrent), ts);
				hold_req_made = true;
				D_MOD(classname << ": hold request made");
			}
		}
	}
    
    break;
  }
  default:
    // other states should never be entered for a SimulationModule, 
    // HardwareModules on the other hand have more states. Throw an
    // exception if we get here, 
    throw CannotHandleState(getId(),GlobalId(), "state unhandled");
  }

  // DUECA applications are data-driven. From the time a module is switched
  // on, it should produce data, so that modules "downstreams" are 
  // activated
  // access your output channel(s)
  // example
  // StreamWriter<MyOutput> y(output_token, ts);

  // write the output into the output channel, using the stream writer
  // y.data().var1 = something; ...
  {
    StreamWriter<CitationOutput> y(state_token, ts);
    
    y.data() = Y;
    
    D_MOD(classname << ": sending data on channel CitationOutput");
  }
  
  
  /* BEGIN copy from PA34 */
  /* needed to modify:
    replace Y[] by Y.y[]
    snd.data().power[]
  */
  
  // visual output
  // transfrom from cg to pilot's eyepoint
  {
    sf=sin(Y.y[Y_phi]);   cf=cos(Y.y[Y_phi]);
    st=sin(Y.y[Y_theta]); ct=cos(Y.y[Y_theta]);
    sp=sin(Y.y[Y_psi]);   cp=cos(Y.y[Y_psi]);

    StreamWriter<VehicleCabPosition> vcp(vcp_token, ts);
    vcp.data().x     =  cp*ct*xcab + (cp*st*sf-sp*cf)*ycab + (cp*st*cf+sp*sf)*zcab +  Y.y[Y_x];
    vcp.data().y     =  sp*ct*xcab + (sp*st*sf+cp*cf)*ycab + (sp*st*cf-cp*sf)*zcab +  Y.y[Y_y];
    vcp.data().z     = -st   *xcab +  ct*sf          *ycab +  ct*cf          *zcab + -Y.y[Y_h];
    vcp.data().phi   = Y.y[Y_phi];
    vcp.data().theta = Y.y[Y_theta];
    vcp.data().psi   = Y.y[Y_psi];
    vcp.data().test  = 0;
  }
  
  // sound output
  {
    StreamWriter<PropSoundData> snd(snd_token, ts);
    snd.data().rpm[0]    = fade_in*Y.y[Y_rpmleft];
    snd.data().rpm[1]    = fade_in*Y.y[Y_rpmright];
    snd.data().torque[0] = Y.y[Y_torqueleft];
    snd.data().torque[1] = Y.y[Y_torqueright];
    //TODO
    //snd.data().power[0]  = (power_left > 0.01 ? true : false);
    //snd.data().power[1]  = (power_right > 0.01 ? true : false);
    snd.data().power[0] = true;
    snd.data().power[1] = true;
    //
    snd.data().tas       = Y.y[Y_vtas];
    snd.data().sounds    = 0; //TODO gear, flaps, bang, warning, etc.
  }

  // motion output
  // accelerations already at pilot's head, check [xyz]iacc in ac_genrl.mat
  // 14JAN05, output changed, anyib gave wrong values in turn, it's now an[xyz]b
  //    TODO: transform to the pilot's head
  // 23 september 2014 niet lineaire filtering ingebracht
  //TODO check correctness of comments
  {
    StreamWriter<VehicleCabMotion> vcm(vcm_token, ts);
    vcm.data().xdotdot = 0.0; // not an output, but also not used in current motion filter
    vcm.data().ydotdot = 0.0; // not an output, but also not used in current motion filter
    vcm.data().zdotdot = 0.0; // not an output, but also not used in current motion filter
    vcm.data().fx      = fade_in*2*atan(Y.y[Y_fxcg]/2); // input to the motion filter
    vcm.data().fy      = fade_in*2*atan(Y.y[Y_fycg]/2); // input to the motion filter
    vcm.data().fz      = ((fade_in*2*atan((Y.y[Y_fzcg]+9.8066)/2) )-9.8066); // input to the motion filter
    vcm.data().xdot    = 0.0; // not an output, but also not used in current motion filter
    vcm.data().ydot    = 0.0; // not an output, but also not used in current motion filter
    vcm.data().zdot    = 0.0; // not an output, but also not used in current motion filter
    vcm.data().pdot    = fade_in*0.5*atan(Y.y[Y_pdot]/0.5); // input to the motion filter
    vcm.data().qdot    = fade_in*0.5*atan(Y.y[Y_qdot]/0.5); // input to the motion filter
    vcm.data().rdot    = fade_in*0.5*atan(Y.y[Y_rdot]/0.5); // input to the motion filter
    vcm.data().p       = fade_in* 0.25*atan(Y.y[Y_p]/0.25); // not used in current motion filter
    vcm.data().q       = fade_in* 0.25*atan(Y.y[Y_q]/0.25); // not used in current motion filter
    vcm.data().r       = fade_in* 0.25*atan(Y.y[Y_r]/0.25); // not used in current motion filter
  }
  /* END copy from PA34 */
  
  
  /* OLD
  // visual output
  // transfrom from cg to pilot's eyepoint
  {
    sf=sin(Y.y[Y_phi]);cf=cos(Y.y[Y_phi]);st=sin(Y.y[Y_theta]);
    ct=cos(Y.y[Y_theta]);sp=sin(Y.y[Y_psi]);cp=cos(Y.y[Y_psi]);
    
    StreamWriter<VehicleCabPosition> vcp(vcp_token, ts);
    vcp.data().x =  cp*ct*xcab + (cp*st*sf-sp*cf)*ycab + (cp*st*cf+sp*sf)*zcab + Y.y[Y_x];
    vcp.data().y =  sp*ct*xcab + (sp*st*sf+cp*cf)*ycab + (sp*st*cf-cp*sf)*zcab + Y.y[Y_y];
    vcp.data().z = -st   *xcab +  ct*sf          *ycab +  ct*cf          *zcab + -Y.y[Y_h];
    vcp.data().phi = Y.y[Y_phi];
    vcp.data().theta = Y.y[Y_theta];
    vcp.data().psi = Y.y[Y_psi];
    vcp.data().test = 0;
  }
  
  // sound output
  {
    StreamWriter<PropSoundData> snd(snd_token, ts);
    
    snd.data().n1left = Y.y[Y_n1left];
    snd.data().n1right = Y.y[Y_n1right];
    snd.data().tas = Y.y[Y_vtas];
    snd.data().sounds = 0;
  }
  
  // motion output
  // accelerations already at pilot's head, check [xyz]iacc in ac_genrl.mat
  // 14JAN05, output changed, anyib gave wrong values in turn, it's now an[xyz]b
  //          TODO: transform to the pilot's head
  {
    StreamWriter<VehicleCabMotion> vcm(vcm_token, ts);
    vcm.data().xdotdot = 0.0; // not an output, but also not used in current motion filter
    vcm.data().ydotdot = 0.0; // not an output, but also not used in current motion filter
    vcm.data().zdotdot = 0.0; // not an output, but also not used in current motion filter
    vcm.data().fx = Y.y[Y_fxcg]*9.8066; // input to the motion filter
    vcm.data().fy = Y.y[Y_fycg]*9.8066; // input to the motion filter
    vcm.data().fz = Y.y[Y_fzcg]*9.8066; // input to the motion filter
    vcm.data().xdot = 0.0; // not an output, but also not used in current motion filter
    vcm.data().ydot = 0.0; // not an output, but also not used in current motion filter
    vcm.data().zdot = 0.0; // not an output, but also not used in current motion filter
    vcm.data().pdot = Y.y[Y_pdot]; // input to the motion filter
    vcm.data().qdot = Y.y[Y_qdot]; // input to the motion filter
    vcm.data().rdot = Y.y[Y_rdot]; // input to the motion filter
    vcm.data().p = Y.y[Y_p]; // not used in current motion filter
    vcm.data().q = Y.y[Y_q]; // not used in current motion filter
    vcm.data().r = Y.y[Y_r]; // not used in current motion filter
  }
  OLD */
  
  if (snapshotNow()) {
    // keep a copy of the model state. Snapshot sending is done in the 
    // sendSnapshot routine, later, and possibly at lower priority
    // e.g. 
    // snapshot_state_variable1 = state_variable1; ...
    // (or maybe if your state is very large, there is a cleverer way ...)
  }
} 

void CitationReplayer::trimCalculation(const TimeSpec& ts, const TrimMode& mode)
{
  // read the event equivalent of the input data
  // example
  // EventReader u(i_input_token, ts);

  // using the input, and the data put into your trim variables,
  // calculate the derivative of the state. DO NOT use the state
  // vector of the normal simulation here, because it might be that
  // this is done while the simulation runs!  
  // Some elements in this state derivative are needed as target, copy
  // these out again into trim variables (see you TrimTable

  // trim calculation
  switch(mode) {
  case FlightPath: {
    // one type of trim calculation, find a power setting and attitude
    // belonging to a flight path angle and speed
  }
  break;

  case Speed: {
    // find a flightpath belonging to a speed and power setting (also
    // nice for gliders)
  }
  break;

  case Ground: {
    // find an altitude/attitude belonging to standing still on the 
    // ground, power/speed 0
  }
  break;

  default:
    W_MOD(getId() << " cannot calculate inco mode " << mode);
  break;
  }

  // This works just like a normal calculation, only you provide the
  // steady state value (if your system is stable anyhow). So, if you
  // have other modules normally depending on your output, you should
  // also produce the equivalent output here. 
  // EventWriter<MyOutput> y(output_token, ts);

  // write the output into the output channel, using the EventWriter
  // N.B. you may also use:
  // output_token.sendEvent(ts, new MyOutput(arguments));
  // this is slightly more efficient. However, the EventWriter makes
  // it easier, because the code will look much more like your normal
  // calculation code.

  // now return. The real results from the trim calculation, as you
  // specified them in the TrimTable, will now be collected and sent
  // off for processing.
}


/** read the contents of file_stream into data_queue */
bool CitationReplayer::readData()
{
  double time_in;
  double dummy;
  CitationOutput co_in;
  int i;

  PeriodicTimeSpec *data_ts = NULL;
  double start_time = -1.0;
  //double diff_time = -1.0; // renamed dt, global variable
  int nsteps = 0;
  char dummy_char = '\0';
  char dummy_string[512];

  // eat up the comments at the start
  bool commentsread = false;
  while (!commentsread) {
    dummy_char = file_stream.peek();

    if(dummy_char == '\%' || dummy_char == '\n' ) {
      file_stream.getline(dummy_string, 512);
      I_MOD(classname << ": (comment) " << dummy_string);
    }
    else commentsread = true;
  }

  // start reading data
  while(!file_stream.eof()) {
    nsteps++;
    
    // time stamp
    file_stream >> time_in;
    
    // not quite zero, might be negative
    if(fabs(time_in) < 1e-3) time_in = 0.0;
      
    // figure out the rate of the logged data
    if(start_time < 0){
      start_time = time_in; // first time found
    }
    else if(dt < 0) {
      dt = time_in - start_time; // difference between first and second time found = timestep
      
      //dt = 0.04; //TODO fix (solo = 0.04, srs = 0.02)
      //Peter: experiencing problems with obtained time values, rounding error?
      
      // check the timestep
      if (dt < 1e-3) {
        dt = 0.02; //0.001;
        E_MOD(classname << ": timestep too small, set to " << dt << " seconds");
      }
      if (dt > 2.0) {
        dt = 0.02; //2.0;
        E_MOD(classname << ": timestep too large, set to " << dt << " seconds");
      }
      
      I_MOD(classname << ": found first step at " << start_time << " seconds");
      I_MOD(classname << ": found second step at " << time_in << " seconds");
      I_MOD(classname << ": therefor the time interval is " << dt << " seconds");
      I_MOD(classname << ": thinks time granule is " << Ticker::single()->getTimeGranule());
      data_ts = new PeriodicTimeSpec(0, int( dt / Ticker::single()->getTimeGranule() ) );
    }

    // data
    /* Peter: model inputs not logged at this location, starts with CitationOutput
    for(i=0;i<9;++i)
      file_stream >> dummy; // eat up the logged model inputs
    */
    
    // go over CitationOutput data, 47 values
    for(i=0;i<47;++i)
      file_stream >> co_in.y[i];
    
    // add data to tape
    state_queue.push_back(co_in);
    
    // discard the rest of the line
    file_stream.getline(dummy_string, 512);
    //TODO: use more data
  }
  // finished reading data
  I_MOD(classname << ": found " << nsteps << " steps");
  
  // check end time
  I_MOD(classname << ": found last step at " << time_in << " seconds");
  I_MOD(classname << ": based on that, the time interval is " << time_in/nsteps << " seconds");

  // rewind the tape
  state_iter = state_queue.begin();

  if(data_ts) {
    do_calc.setTimeSpec(*data_ts);
    I_MOD(classname << ": will replay data with " << *data_ts);
    delete data_ts;
  }

  return true;
}


// Make a TypeCreator object for this module, the TypeCreator
// will check in with the scheme-interpreting code, and enable the
// creation of modules of this type
static TypeCreator<CitationReplayer> a(CitationReplayer::getMyParameterTable());

