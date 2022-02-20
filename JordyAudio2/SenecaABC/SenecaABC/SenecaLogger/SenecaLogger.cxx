/* ------------------------------------------------------------------   */
/*      item            : SenecaLogger.cxx
        made by         : jordy
	from template   : DusimeModuleTemplate.cxx
        template made by: Rene van Paassen
        date            : Sat May 30 13:33:44 2020
	category        : body file
        description     :
	changes         : Sat May 30 13:33:44 2020 first version
	template changes: 030401 RvP Added template creation comment
	                  060512 RvP Modified token checking code
			  131224 RvP convert snap.data_size to
			         snap.getDataSize()
        language        : C++
        copyright       : (c) 2016 TUDelft-AE-C&S
*/


#define SenecaLogger_cxx
// include the definition of the module class
#include "SenecaLogger.hxx"
#include <clocale>

// include the debug writing header. Warning and error messages
// are on by default, debug and info can be selected by
// uncommenting the respective defines
//#define D_MOD
//#define I_MOD
#include <debug.h>

// include additional files needed for your calculation here

// the standard package for DUSIME, including template source
#define DO_INSTANTIATE
#include <dusime.h>

// class/module name
const char* const SenecaLogger::classname = "seneca-logger";

// initial condition/trim table
const IncoTable* SenecaLogger::getMyIncoTable()
{
  static IncoTable inco_table[] = {
    // enter pairs of IncoVariable and VarProbe pointers (i.e.
    // objects made with new), in this table.
    // For example
//    {(new IncoVariable("example", 0.0, 1.0, 0.01))
//     ->forMode(FlightPath, Constraint)
//     ->forMode(Speed, Control),
//     new VarProbe<_ThisModule_,double>
//       (REF_MEMBER(&_ThisModule_::i_example))}

    // always close off with:
    { NULL, NULL} };

  return inco_table;
}

// parameters to be inserted
const ParameterTable* SenecaLogger::getMyParameterTable()
{
  static const ParameterTable parameter_table[] = {
    { "set-timing",
      new MemberCall<_ThisModule_,TimeSpec>
        (&_ThisModule_::setTimeSpec), set_timing_description },

    { "check-timing",
      new MemberCall<_ThisModule_,vector<int> >
      (&_ThisModule_::checkTiming), check_timing_description },

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
SenecaLogger::SenecaLogger(Entity* e, const char* part, const
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

  tab(","),
  time(0.0),

  x(0.0),
  y(0.0),
  h(0.0),
  Vtas(0.0),
  theta(0.0),
  phi(0.0),
  psi(0.0),
  alpha(0.0),
  beta(0.0),
  hdot(0.0),
  p(0.0),
  q(0.0),
  r(0.0),
  de(0.0),
  da(0.0),
  dr(0.0),
  theta_ref(0.0),
  phi_ref(0.0),

  curVerticalState(0),
  curLateralState(0),
  APstate(0),

  // initialize the data you need in your simulation

  // initialize the data you need for the trim calculation

  // initialize the channel access tokens, check the documentation for the
  in_token(getId(), NameSet(getEntity(), "CitationOutput", part),101),
  ap2g_token(getId(), NameSet(getEntity(), "AP2G1000Channel", part)),
  ap_token(getId(), NameSet(getEntity(), "AutopilotChannel", part)),
  // various parameters. Some examples:
  // r_mytoken(getId(), NameSet(getEntity(), MyData::classname, part),
  //           MyData::classname, 0, Channel::Events, Channel::ReadAllData),
  // w_mytoken(getId(), NameSet(getEntity(), MyData::classname, part),
  //           MyData::classname, "label", Channel::Continuous),

  // activity initialization
  myclock(),
  cb1(this, &_ThisModule_::doCalculation),
  do_calc(getId(), "", &cb1, ps)
{
  // do the actions you need for the simulation

  // connect the triggers for simulation
  do_calc.setTrigger(in_token && ap_token);

  // connect the triggers for trim calculation. Leave this out if you
  // don not need input for trim calculation
  //trimCalculationCondition(/* fill in your trim triggering channels */);
}

bool SenecaLogger::complete()
{
  /* All your parameters have been set. You may do extended
     initialisation here. Return false if something is wrong. */
  return true;
}

// destructor
SenecaLogger::~SenecaLogger()
{
  //
}

// as an example, the setTimeSpec function
bool SenecaLogger::setTimeSpec(const TimeSpec& ts)
{
  // a time span of 0 is not acceptable
  if (ts.getValiditySpan() == 0) return false;

  // specify the timespec to the activity
  do_calc.setTimeSpec(ts);
  // or do this with the clock if you have it (don't do both!)
  // myclock.changePeriodAndOffset(ts);

  // do whatever else you need to process this in your model
  // hint: ts.getDtInSeconds()

  // return true if everything is acceptable
  return true;
}

// and the checkTiming function
bool SenecaLogger::checkTiming(const vector<int>& i)
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
bool SenecaLogger::isPrepared()
{
  bool res = true;

  // Example checking a token:
  // CHECK_TOKEN(w_somedata);
  CHECK_TOKEN(in_token);
  CHECK_TOKEN(ap_token);
  CHECK_TOKEN(ap2g_token);
  // Example checking anything
  // CHECK_CONDITION(myfile.good());
  // CHECK_CONDITION2(sometest, "some test failed");

  // return result of checks
  return res;
}

// start the module
void SenecaLogger::startModule(const TimeSpec &time)
{
  do_calc.switchOn(time);
  std::setlocale(LC_NUMERIC, "C");
}

// stop the module
void SenecaLogger::stopModule(const TimeSpec &time)
{
  do_calc.switchOff(time);
  std::string titles =std::string("time") + tab + std::string("x") + tab + std::string("y") + tab + std::string("h") + tab + std::string("Vtas") +
  tab + std::string("theta") + tab + std::string("phi") + tab + std::string("psi") + tab + std::string("alpha") + tab + std::string("beta") +
  tab + std::string("hdot") + tab + std::string("p") + tab + std::string("q") + tab + std::string("r") + tab + std::string("de") +tab + std::string("da") +
  tab + std::string("dr") + tab + std::string("theta_ref") +  tab + std::string("phi_ref") +
  tab + std::string("APstate") + tab + std::string("curVerticalState") + tab + std::string("curLateralState") + tab + std::string("\n");

  std::string log = titles+ss;
  std::ofstream ofs("log1.csv", std::ofstream::out);
  ofs.write(log.c_str(), sizeof(char)*log.size());
  ofs.close();
}

// fill a snapshot with state data. You may remove this method (and the
// declaration) if you specified to the SimulationModule that the size of
// state snapshots is zero
void SenecaLogger::fillSnapshot(const TimeSpec& ts,
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
void SenecaLogger::loadSnapshot(const TimeSpec& t, const Snapshot& snap)
{
  // access the data in the snapshot with an AmorphReStore object
  AmorphReStore s(snap.data, snap.getDataSize());

  // use unPackData(s, real_state_variable1 ); ... to unpack the data
  // from the snapshot.
  // You can safely do this, while snapshot loading is going on the
  // simulation is in HoldCurrent or the activity is stopped.
}

// this routine contains the main simulation process of your module. You
// should read the input channels here, and calculate and write the
// appropriate output
void SenecaLogger::doCalculation(const TimeSpec& ts)
{
  // check the state we are supposed to be in
  switch (getAndCheckState(ts)) {
  case SimulationState::HoldCurrent: {
    // only repeat the output, do not change the model state

    break;
    }

  case SimulationState::Replay:
  case SimulationState::Advance: {

    //##########################################################################
    // Read AutopilotChannel
    //##########################################################################
    try
    {
      StreamReader<AutopilotChannel> ap(ap_token, ts);
      theta_ref = ap.data().theta_ref;
      phi_ref = ap.data().phi_ref;
      de = ap.data().de;
      da = ap.data().da;
      dr = ap.data().dr;
    }
    catch(Exception& e)
    {
      W_MOD(getId()<< classname << " caught " << e << " @ " << ts <<
                      " -- reading CitationOutput Channel");
    }

    //##########################################################################
    // Read CitationOutput
    //##########################################################################
    try
    {
      StreamReader<CitationOutput> in(in_token, ts);
      x = in.data().y[Y_y];
      y = in.data().y[Y_x];
      h = in.data().y[Y_h];

      Vtas = in.data().y[Y_vtas];

      theta = in.data().y[Y_theta];
      phi = in.data().y[Y_phi];
      psi = in.data().y[Y_psi];

      alpha = in.data().y[Y_alpha];
      beta = in.data().y[Y_beta];

      hdot = in.data().y[Y_hdot];

      p = in.data().y[Y_p];
      q = in.data().y[Y_q];
      r = in.data().y[Y_r];

    }
    catch(Exception& e)
    {
      W_MOD(getId()<< classname << " caught " << e << " @ " << ts <<
                      " -- reading CitationOutput Channel");
    }



    //##########################################################################
    // Read AP2
    //##########################################################################
    if (ap2g_token.getNumWaitingEvents(ts))
    {
      try
      {
        EventReader<AP2G1000Channel> ap2g_reader(ap2g_token, ts);

        curVerticalState = ap2g_reader.data().ap_vertical;
        curLateralState = ap2g_reader.data().ap_lateral;
        APstate = ap2g_reader.data().APstate;

      }
      catch (Exception& e)
      {
        W_MOD(classname << ": Error while reading AP2G1000Channel!");
      }
    }

    //##########################################################################
    // Write to string
    //##########################################################################

    ss += std::to_string(time) + tab +
          std::to_string(x) + tab +
          std::to_string(y) + tab +
          std::to_string(h) + tab +
          std::to_string(Vtas) + tab +
          std::to_string(theta) + tab +
          std::to_string(phi) + tab +
          std::to_string(psi) + tab +
          std::to_string(alpha) + tab +
          std::to_string(beta) + tab +
          std::to_string(hdot) + tab +
          std::to_string(p) + tab +
          std::to_string(q) + tab +
          std::to_string(r) + tab +
          std::to_string(de) + tab +
          std::to_string(da) + tab +
          std::to_string(dr) + tab +
          std::to_string(theta_ref) + tab +
          std::to_string(phi_ref) + tab +
          std::to_string(APstate) + tab +
          std::to_string(curVerticalState) + tab +
          std::to_string(curLateralState) + tab +
          "\n";

    time += ts.getDtInSeconds();
    // access the input
    // example:
    // try {
    //   DataReader<MyInput> u(input_token, ts);
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

    // do the simulation calculations, one step

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
  // DataWriter<MyOutput> y(output_token, ts);

  // write the output into the output channel, using the stream writer
  // y.data().var1 = something; ...

  if (snapshotNow()) {
    // keep a copy of the model state. Snapshot sending is done in the
    // sendSnapshot routine, later, and possibly at lower priority
    // e.g.
    // snapshot_state_variable1 = state_variable1; ...
    // (or maybe if your state is very large, there is a cleverer way ...)
  }
}

void SenecaLogger::trimCalculation(const TimeSpec& ts, const TrimMode& mode)
{
  // read the event equivalent of the input data
  // example
  // DataReader<MyData> u(i_input_token, ts);

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
  // DataWriter<MyOutput> y(output_token, ts);

  // write the output into the output channel, using the DataWriter

  // now return. The real results from the trim calculation, as you
  // specified them in the TrimTable, will now be collected and sent
  // off for processing.
}

// Make a TypeCreator object for this module, the TypeCreator
// will check in with the scheme-interpreting code, and enable the
// creation of modules of this type
static TypeCreator<SenecaLogger> a(SenecaLogger::getMyParameterTable());
