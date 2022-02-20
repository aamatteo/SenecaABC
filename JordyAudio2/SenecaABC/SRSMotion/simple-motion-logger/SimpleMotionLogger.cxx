/* ------------------------------------------------------------------   */
/*      item            : SimpleMotionLogger.cxx
        made by         : simona
        date            : 020501
	category        : body file
        description     :
	changes         : 020501 first version
        language        : C++
*/

static const char c_id[] =
"$Id: SimpleMotionLogger.cxx,v 1.4 2021/10/25 12:50:16 ostroosma Exp $";

#define SimpleMotionLogger_cxx
// include the definition of the module class
#include "SimpleMotionLogger.hxx"

// include additional files needed for your calculation here
#include <time.h>
#include <iomanip>

#define I_MOD
#define W_MOD
#define E_MOD
#include <debug.h>

// the standard package for DUSIME, including template source
#define DO_INSTANTIATE
#include <dusime.h>


// class/module name
const char* const SimpleMotionLogger::classname = "simple-motion-logger";

// initial condition/trim table
const IncoTable* SimpleMotionLogger::getMyIncoTable()
{
  static IncoTable inco_table[] = {
    // enter pairs of IncoVariable and VarProbe pointers (i.e.
    // objects made with new), in this table.
    // For example
//    {(new IncoVariable("example", 0.0, 1.0, 0.01))
//     ->forMode(FlightPath, Constraint)
//     ->forMode(Speed, Control),
//     new VarProbe<SimpleMotionLogger,double>
//       (REF_MEMBER(&SimpleMotionLogger::i_example))}

    // always close off with:
    { NULL, NULL} };

  return inco_table;
}

// parameters to be inserted
const ParameterTable* SimpleMotionLogger::getMyParameterTable()
{
  static const ParameterTable parameter_table[] = {
    { "set-timing",
      new MemberCall<SimpleMotionLogger,TimeSpec>
        (&SimpleMotionLogger::setTimeSpec)},

    { "check-timing",
      new MemberCall<SimpleMotionLogger,vector<int> >
      (&SimpleMotionLogger::checkTiming)},

    // always close off with:
    { NULL, NULL} };

  return parameter_table;
}

// constructor
SimpleMotionLogger::SimpleMotionLogger(Entity* e, const char* part, const
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
  SimulationModule(e, classname, part, getMyIncoTable(), 0
                   /* fill in the size of a snapshot of the state here */),

  // initialize the data you need in your simulation

  // initialize the data you need for the trim calculation

  // initialize the channel access tokens
  // example
  // my_token(getId(), NameSet(getEntity(), "MyData", part)),
  vcm_token(getId(), NameSet(getEntity(), "VehicleCabMotion", part), 101),
  sma_token(getId(), NameSet(getEntity(), "SimulatorMotionAcceleration", part), 101),
  mcpva_token(getId(), NameSet(getEntity(), "MotionCommandedPosVelAcc", part), 101),
  mal_token(getId(), NameSet(getEntity(), "MotionActuatorLengths", part), 101),
  scm_token(getId(), NameSet(getEntity(), "SimulatorCabMotion", part), 101),
  mbrd_token(getId(), NameSet(getEntity(), "MotionBaseResultData", part)),
  fud_token(getId(), NameSet(getEntity(), "MotionFilterUserData", part), 101),

  // activity initialization
  cb1(this, &SimpleMotionLogger::doCalculation),
  do_calc(getId(), "my calculation", &cb1, ps)
{
  // do the actions you need for the simulation

  // connect the triggers for simulation
  do_calc.setTrigger(vcm_token && sma_token && mcpva_token && mal_token && scm_token && fud_token/* fill in your triggering channels */);

  // connect the triggers for trim calculation. Leave this out if you
  // don not need input for trim calculation
  //trimCalculationCondition(/* fill in your trim triggering channels */);
}

bool SimpleMotionLogger::complete()
{
  /* All your parameters have been set. You may do extended
     initialisation here. Return false if something is wrong. */
  time_t tim = time(NULL);

  out.open("motion.log");
  if(out)
  {
     // SciLab format
/*     out << "// SimpleMotionLogger log file generated on " << ctime(&tim) << endl;
     out << "// Timespec | motionstatus | VehicleCabMotion(model) xd/yd/zd/p/q/r xdd/ydd/zdd/pd/qd/rd | " <<
            " SimulatorMotionAcceleration (motion filter) xdd/ydd/zdd/pd/qd/rd | " <<
	    " MotionCommandePosVelAcc (motion limiter)  x/y/z/phi/theta/psi xd/yd/zd/p/q/r xdd/ydd/zdd/pd/qd/rd" << endl;*/
     return true;
  }
  else
  {
    cerr << "SimpleMotionLogger: error opening file" << endl;
    return false;
  }
}

// destructor
SimpleMotionLogger::~SimpleMotionLogger()
{
  //
  out.close();
}

// as an example, the setTimeSpec function
bool SimpleMotionLogger::setTimeSpec(const TimeSpec& ts)
{
  // a time span of 0 is not acceptable
  if (ts.getValiditySpan() == 0) return false;

  // specify the timespec to the activity
  do_calc.setTimeSpec(ts);

  // do whatever else you need to process this in your model
  // hint: ts.getDtInSeconds()

  // return true if everything is acceptable
  return true;
}

// and the checkTiming function
bool SimpleMotionLogger::checkTiming(const vector<int>& i)
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

// tell DUECA you are prepared
bool SimpleMotionLogger::isPrepared()
{
  // do whatever calculations you need to prepare the model. Return
  // with false if something is wrong
  bool prep = vcm_token.isValid() && sma_token.isValid()
    && mcpva_token.isValid() && mal_token.isValid() && scm_token.isValid()
    && fud_token.isValid();

  I_MOD("SimpleMotionLogger " << ( prep? "is " : "is not ") << "prepared");

  if(!prep)
    W_MOD("SimpleMotionLogger tokens: " << vcm_token.isValid() << 
	  sma_token.isValid() << mcpva_token.isValid() << mal_token.isValid() <<
	  scm_token.isValid() << fud_token.isValid());

  return prep;
}

// start the module
void SimpleMotionLogger::startModule(const TimeSpec &time)
{
  do_calc.switchOn(time);
}

// stop the module
void SimpleMotionLogger::stopModule(const TimeSpec &time)
{
  do_calc.switchOff(time);

  // debug
  cout << "SimpleMotionLogger stopped" << endl;
}

// fill a snapshot with state data. You may remove this method (and the
// declaration) if you specified to the SimulationModule that the size of
// state snapshots is zero
void SimpleMotionLogger::fillSnapshot(const TimeSpec& ts,
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
void SimpleMotionLogger::loadSnapshot(const TimeSpec& t, const Snapshot& snap)
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
void SimpleMotionLogger::doCalculation(const TimeSpec& ts)
{
  // debug
  //cout << "SimpleMotionLogger got triggered on " << ts << endl;

  // check the state we are supposed to be in
  switch (getAndCheckState(ts)) {
  case SimulationState::HoldCurrent: {
    // only repeat the output, don not change the model state

    // access your output channel(s)
    // example
    // StreamWriter<MyOutput> y(output_token, ts);

    // write the output into the output channel, using the stream writer
    // y.data().var1 = something; ...

    // debug
    //cout << "SimpleMotionLogger in HoldCurrent on " << ts << endl;

    break;
    }

  case SimulationState::Replay:
  case SimulationState::Advance: {
    // access the input
    // example:
    // try {
    //   StreamReader<MyInput> u(input_token, ts);
    //   throttle = u.data().throttle;
    //   de = u.data().de; ....
    // }
    // catch(Exception& e) {
    //   // strange, there is no input. Should I try to continue or not?
    // }
    /* The above piece of code shows a block in which you try to catch
       error conditions (exceptions) to handle the case in which the input
       data is lost. This is not always necessary, if you normally do not
       foresee such a condition, and you don t mind being stopped when
       it happens, forget about the try/catch blocks. */

    // do the simulation calculations, one stp

    // access your output channel(s)
    // example
    // StreamWriter<MyOutput> y(output_token, ts);

    // write the output into the output channel, using the StreamWriter

    if(mbrd_token.isValid()) {
      try
	{
	  StreamReader<MotionBaseResultData> mbrd(mbrd_token, ts);
	  for(int i = 0; i < 6; i++) {
	    measured_pos[i] = mbrd.data().actual_pos[i];
	    measured_len[i] = mbrd.data().actual_len[i];
	  }
	}
      catch(Exception& e) {
	for(int i = 0; i < 6; i++) {
	  measured_pos[i] = -1.0;
	  measured_len[i] = -1.0;
	}
      }
    }
    else {
      for(int i = 0; i < 6; i++) {
	measured_pos[i] = -1.0;
	measured_len[i] = -1.0;
      }
    }

    try
    {
    StreamReader<VehicleCabMotion> vcm(vcm_token, ts);
    StreamReader<SimulatorMotionAcceleration> sma(sma_token, ts);
    StreamReader<MotionCommandedPosVelAcc> mcpva(mcpva_token, ts);
    StreamReader<MotionActuatorLengths> mal(mal_token, ts);
    StreamReader<SimulatorCabMotion> scm(scm_token, ts);
    StreamReader<MotionFilterUserData> fud(fud_token, ts);

    out << setw(15) << setfill(' ') << ts.getValidityStart()           // 1

      << setw(15) << setfill(' ') << mcpva.data().status      << '\t'  // 2

      // motion data from aircraft model
      // body frame with origin somewhere in cockpit (DERP?)
      << setw(15) << setfill(' ') << vcm.data().xdot          << '\t'  // 3
      << setw(15) << setfill(' ') << vcm.data().ydot          << '\t'  // 4
      << setw(15) << setfill(' ') << vcm.data().zdot          << '\t'  // 5
      << setw(15) << setfill(' ') << vcm.data().p             << '\t'  // 6
      << setw(15) << setfill(' ') << vcm.data().q             << '\t'  // 7
      << setw(15) << setfill(' ') << vcm.data().r             << '\t'  // 8
      << setw(15) << setfill(' ') << vcm.data().xdotdot       << '\t'  // 9
      << setw(15) << setfill(' ') << vcm.data().ydotdot       << '\t'  // 10
      << setw(15) << setfill(' ') << vcm.data().zdotdot       << '\t'  // 11
      << setw(15) << setfill(' ') << vcm.data().pdot          << '\t'  // 12
      << setw(15) << setfill(' ') << vcm.data().qdot          << '\t'  // 13
      << setw(15) << setfill(' ') << vcm.data().rdot          << '\t'  // 14
      << setw(15) << setfill(' ') << vcm.data().fx            << '\t'  // 15
      << setw(15) << setfill(' ') << vcm.data().fy            << '\t'  // 16
      << setw(15) << setfill(' ') << vcm.data().fz            << '\t'  // 17

      // resulting motion in simulator cabin
      // body frame with origin in DERP
      << setw(15) << setfill(' ') << scm.data().xdot          << '\t'  // 18
      << setw(15) << setfill(' ') << scm.data().ydot          << '\t'  // 19
      << setw(15) << setfill(' ') << scm.data().zdot          << '\t'  // 20
      << setw(15) << setfill(' ') << scm.data().p             << '\t'  // 21
      << setw(15) << setfill(' ') << scm.data().q             << '\t'  // 22
      << setw(15) << setfill(' ') << scm.data().r             << '\t'  // 23
      << setw(15) << setfill(' ') << scm.data().xdotdot       << '\t'  // 24
      << setw(15) << setfill(' ') << scm.data().ydotdot       << '\t'  // 25
      << setw(15) << setfill(' ') << scm.data().zdotdot       << '\t'  // 26
      << setw(15) << setfill(' ') << scm.data().pdot          << '\t'  // 27
      << setw(15) << setfill(' ') << scm.data().qdot          << '\t'  // 28
      << setw(15) << setfill(' ') << scm.data().rdot          << '\t'  // 29
      << setw(15) << setfill(' ') << scm.data().fx            << '\t'  // 30
      << setw(15) << setfill(' ') << scm.data().fy            << '\t'  // 31
      << setw(15) << setfill(' ') << scm.data().fz            << '\t'  // 32

      // output from motion filter
      // 09JUN2002 inertial frame in upper gimbal center
      << setw(15) << setfill(' ') << sma.data().xdotdot       << '\t'  // 33
      << setw(15) << setfill(' ') << sma.data().ydotdot       << '\t'  // 34
      << setw(15) << setfill(' ') << sma.data().zdotdot       << '\t'  // 35
      << setw(15) << setfill(' ') << sma.data().pdot          << '\t'  // 36
      << setw(15) << setfill(' ') << sma.data().qdot          << '\t'  // 37
      << setw(15) << setfill(' ') << sma.data().rdot          << '\t'  // 38

      // commanded setpoints
      // inertial frame with origin in upper gimbal center
      << setw(15) << setfill(' ') << mcpva.data().x           << '\t'  // 39
      << setw(15) << setfill(' ') << mcpva.data().y           << '\t'  // 40
      << setw(15) << setfill(' ') << mcpva.data().z           << '\t'  // 41
      << setw(15) << setfill(' ') << mcpva.data().phi         << '\t'  // 42
      << setw(15) << setfill(' ') << mcpva.data().theta       << '\t'  // 43
      << setw(15) << setfill(' ') << mcpva.data().psi         << '\t'  // 44
      << setw(15) << setfill(' ') << mcpva.data().xdot        << '\t'  // 45
      << setw(15) << setfill(' ') << mcpva.data().ydot        << '\t'  // 46
      << setw(15) << setfill(' ') << mcpva.data().zdot        << '\t'  // 47
      << setw(15) << setfill(' ') << mcpva.data().p           << '\t'  // 48
      << setw(15) << setfill(' ') << mcpva.data().q           << '\t'  // 49
      << setw(15) << setfill(' ') << mcpva.data().r           << '\t'  // 50
      << setw(15) << setfill(' ') << mcpva.data().xdotdot     << '\t'  // 51
      << setw(15) << setfill(' ') << mcpva.data().ydotdot     << '\t'  // 52
      << setw(15) << setfill(' ') << mcpva.data().zdotdot     << '\t'  // 53
      << setw(15) << setfill(' ') << mcpva.data().pdot        << '\t'  // 54
      << setw(15) << setfill(' ') << mcpva.data().qdot        << '\t'  // 55
      << setw(15) << setfill(' ') << mcpva.data().rdot        << '\t'; // 56

    for(int i=0; i<6; i++)
    {
       out << setw(15) << setfill(' ') << mal.data().j[i]   << '\t'; // 57 - 62
    }

    for(int i=0; i<6; i++)
    {
       out << setw(15) << setfill(' ') << mal.data().jd[i]   << '\t'; // 63 - 68
    }

    for(int i=0; i<6; i++)
    {
       out << setw(15) << setfill(' ') << mal.data().jdd[i]   << '\t'; // 69 - 74
    }

    for(int i=0; i<6; i++)
    {
       out << setw(15) << setfill(' ') << measured_pos[i]   << '\t'; // 75 - 80
    }

    for(int i=0; i<6; i++)
    {
      out << setw(15) << setfill(' ') << measured_len[i]   << '\t'; // 81 - 86
    }

    for(int i=0; i<6; i++)
    {
       out << setw(15) << setfill(' ') << fud.data().data[i]   << '\t'; // 87 - 92
    }

    out << endl;
    }
    catch(Exception& e) {
       cerr << "SimpleMotionLogger missed input on " << ts << endl;
    }


    break;
    }
  default:
    // other states should never be entered for a SimulationModule,
    // HardwareModules on the other hand have more states. Throw an
    // exception if we get here,
    throw CannotHandleState(getId(),GlobalId(), "state unhandled");
  }

  if (snapshotNow()) {
    // keep a copy of the model state. Snapshot sending is done in the
    // sendSnapshot routine, later, and possibly at lower priority
    // e.g.
    // snapshot_state_variable1 = state_variable1; ...
    // (or maybe if your state is very large, there is a cleverer way ...)
  }
}

void SimpleMotionLogger::trimCalculation(const TimeSpec& ts, const TrimMode& mode)
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

// Make a TypeCreator object for this module, the TypeCreator
// will check in with the scheme-interpreting code, and enable the
// creation of modules of this type
static TypeCreator<SimpleMotionLogger> a(SimpleMotionLogger::getMyParameterTable());

