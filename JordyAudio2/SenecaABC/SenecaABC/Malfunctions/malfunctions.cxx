/* ------------------------------------------------------------------   */
/*      item            : malfunctions.cxx
        made by         : peter
	from template   : DusimeModuleTemplate.cxx
        template made by: Rene van Paassen
        date            : Fri Mar 17 11:01:16 2017
	category        : body file
        description     :
	changes         : Fri Mar 17 11:01:16 2017 first version
	template changes: 030401 RvP Added template creation comment
	                  060512 RvP Modified token checking code
			  131224 RvP convert snap.data_size to
			         snap.getDataSize()
        language        : C++
        copyright       : (c) 2016 TUDelft-AE-C&S
*/


#define malfunctions_cxx
// include the definition of the module class
#include "malfunctions.hxx"

// include the debug writing header, by default, write warning and
// error messages
#define D_MOD
#define I_MOD
#define W_MOD
#define E_MOD
#include <debug.h>

// include additional files needed for your calculation here
#include <Ticker.hxx> // from malfunction_select, not needed if triggering on token
//#include <sstream> // ??

// the standard package for DUSIME, including template source
#define DO_INSTANTIATE
#include <dusime.h>

// additional definitions
#define SET_SPIN_VALUE(A,B) gtk_spin_button_set_value(GTK_SPIN_BUTTON(A), B);
#define SET_TOGGLE_ACTV(A,B) gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(A), B);
//TODO use this too
//#define SET_SPIN_DATA(A) dmi.data().A = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(A));

// class/module name
const char* const malfunctions::classname = "malfunctions";

// initial condition/trim table
const IncoTable* malfunctions::getMyIncoTable()
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

// GTK callbacks
static GladeCallbackTable cbtable[] =
{
  // links the button, with signal pressed, to ButtonPress
  { "P_control_button", "clicked", gtk_callback(&malfunctions::onControlButtonClicked)},
  { "P_mass_button", "clicked", gtk_callback(&malfunctions::onMassButtonClicked)},
  { "P_engine_button", "clicked", gtk_callback(&malfunctions::onEngineButtonClicked)},
  { "P_display_button", "clicked", gtk_callback(&malfunctions::onDisplayButtonClicked)},
  { "P_failure_button", "clicked", gtk_callback(&malfunctions::onFailureButtonClicked)},
  { "P_failureclear_button", "clicked", gtk_callback(&malfunctions::onFailureclearButtonClicked)},
  // close off in familiar style
  { NULL, NULL, NULL, NULL }
};

// parameters to be inserted
const ParameterTable* malfunctions::getMyParameterTable()
{
  static const ParameterTable parameter_table[] = {
    { "set-timing",
      new MemberCall<_ThisModule_,TimeSpec>
        (&_ThisModule_::setTimeSpec), set_timing_description },

    { "check-timing",
      new MemberCall<_ThisModule_,vector<int> >
      (&_ThisModule_::checkTiming), check_timing_description },

    { "set-position-and-size",
      new MemberCall<malfunctions, vector<int> >
      (&malfunctions::setWindowPositionSize),
      "Supply the position (offset x, offset y) and the size (width, height) for the window, <=0 are ignored" },

    /* You can extend this table with labels and MemberCall or
       VarProbe pointers to perform calls or insert values into your
       class objects. Please also add a description (c-style string).

       Note that for efficiency, set_timing_description and
       check_timing_description are pointers to pre-defined strings,
       you can simply enter the descriptive strings in the table. */

    /* The table is closed off with NULL pointers for the variable
       name and MemberCall/VarProbe object. The description is used to
       give an overall description of the module. */
    { NULL, NULL, "view and edit malfunctions status of the model"} };

  return parameter_table;
}

// constructor
malfunctions::malfunctions(Entity* e, const char* part, const
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
  // GUI
  winglade(),
  //GTK widgets from header - set to NULL - then define in ECI::complete() - and check in ECI::isPrepared()
  P_engine_button(NULL),
  Pleft(NULL),
  Pright(NULL),
  PLEFT_RPM(NULL),
  PRIGHT_RPM(NULL),
  g_engine_time_left(NULL), g_engine_time_right(NULL),
  P_mass_button(NULL),
  Px(NULL),
  Py(NULL),
  Pz(NULL),
  Pmass(NULL),
  Prate(NULL),
  POld_x(NULL),
  POld_y(NULL),
  POld_z(NULL),
  POld_mass(NULL),
  P_control_button(NULL),
  Paileron(NULL),
  Prudder(NULL),
  Prudder_bias(NULL),
  PARI(NULL),
  PScenario(NULL), // not used atm

  g_frozen_v(NULL), g_frozen_h(NULL), g_offset_v_value(NULL),
  g_offset_v_time(NULL), g_offset_h_value(NULL), g_offset_h_time(NULL),
  g_GPS_failure(NULL), g_VOR_failure(NULL), g_ADC_failure(NULL),
  g_PFD_failure(NULL), g_GMU_failure(NULL), g_HSI_failure(NULL),
  g_AFCS_pit_failure(NULL), g_AFCS_rol_failure(NULL), g_clogged_sp(NULL),
  g_clogged_pt(NULL),

  // initialize the data you need for the trim calculation

  // initialize the channel access tokens, check the documentation for the
  // various parameters. Some examples:
  // r_mytoken(getId(), NameSet(getEntity(), MyData::classname, part),
  //           MyData::classname, 0, Channel::Events, Channel::ReadAllData),
  // w_mytoken(getId(), NameSet(getEntity(), MyData::classname, part),
  //           MyData::classname, "label", Channel::Continuous),
  mass_token(getId(), NameSet(getEntity(), "MassEvent", part), ChannelDistribution::NO_OPINION),
  engine_token(getId(), NameSet(getEntity(), "EngineEvent", part), ChannelDistribution::NO_OPINION),
  control_token(getId(), NameSet(getEntity(), "ControlEvent", part), ChannelDistribution::NO_OPINION),
  display_token(getId(), NameSet(getEntity(), "DisplayEvent", part), ChannelDistribution::NO_OPINION),
  failure_token(getId(), NameSet(getEntity(), "FailureEvent", part), ChannelDistribution::NO_OPINION),

  mass_feedback_token(getId(), NameSet(getEntity(), "MassEvent", "feedback")),

  mass_read_token(getId(), NameSet(getEntity(), "MassEvent", part)),
  engine_read_token(getId(), NameSet(getEntity(), "EngineEvent", part)),
  control_read_token(getId(), NameSet(getEntity(), "ControlEvent", part)),
  display_read_token(getId(), NameSet(getEntity(), "DisplayEvent", part)),

  // activity initialization
  // myclock(),
  cb1(this, &_ThisModule_::doCalculation),
  do_calc(getId(), "View and edit malfunctions status of the model", &cb1, ps)
{
  // do the actions you need for the simulation
  winglade.readGladeFile("malfunctions.glade", "MalfunctionWindow", reinterpret_cast<gpointer>(this), cbtable);

  // connect the triggers for simulation
  do_calc.setTrigger(*Ticker::single()); //TODO: replace by tokens of channels being read

  // connect the triggers for trim calculation. Leave this out if you
  // don not need input for trim calculation
  //trimCalculationCondition(/* fill in your trim triggering channels */);
}

bool malfunctions::complete()
{
  /* All your parameters have been set. You may do extended
     initialisation here. Return false if something is wrong. */

  // find widgets, checked in isPrepared()
  PScenario = winglade["Scenario"];
  //engine
  P_engine_button = winglade["P_engine_button"]; // button
  Pleft = winglade["g_power_left"];
  Pright = winglade["g_power_right"];
  PLEFT_RPM = winglade["LEFT_RPM"];
  PRIGHT_RPM = winglade["RIGHT_RPM"];
  g_engine_time_left = winglade["g_engine_time_left"];
  g_engine_time_right = winglade["g_engine_time_right"];
  //mass
  P_mass_button = winglade["P_mass_button"]; // button
  Px = winglade["Spin_x"];
  Py = winglade["Spin_y"];
  Pz = winglade["Spin_z"];
  Pmass = winglade["Spin_mass"];
  Prate = winglade["Spin_rate"];
  POld_x = winglade["Old_x"];
  POld_y = winglade["Old_y"];
  POld_z = winglade["Old_z"];
  POld_mass = winglade["Old_mass"];
  //control
  P_control_button = winglade["P_control_button"]; // button
  Paileron = winglade["Aileron_Power"];
  Prudder = winglade["Rudder_Power"];
  Prudder_bias = winglade["Spin_rudder"];
  PARI = winglade["ARI"];
  //display
  g_frozen_v = winglade["g_frozen_v"];
  g_frozen_h = winglade["g_frozen_h"];
  g_offset_v_value = winglade["g_offset_v_value"];
  g_offset_v_time = winglade["g_offset_v_time"];
  g_offset_h_value = winglade["g_offset_h_value"];
  g_offset_h_time = winglade["g_offset_h_time"];
  g_GPS_failure = winglade["g_GPS_failure"];
  g_VOR_failure = winglade["g_VOR_failure"];
  g_ADC_failure = winglade["g_ADC_failure"];
  g_PFD_failure = winglade["g_PFD_failure"];
  g_GMU_failure = winglade["g_GMU_failure"];
  g_HSI_failure = winglade["g_HSI_failure"];
  g_AFCS_pit_failure = winglade["g_AFCS_pit_failure"];
  g_AFCS_rol_failure = winglade["g_AFCS_rol_failure"];
  g_clogged_sp = winglade["g_clogged_sp"];
  g_clogged_pt = winglade["g_clogged_pt"];

  // Show glade window.
  winglade.show();

  return true;
}

// destructor
malfunctions::~malfunctions()
{
  //
}

// as an example, the setTimeSpec function
bool malfunctions::setTimeSpec(const TimeSpec& ts)
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
bool malfunctions::checkTiming(const vector<int>& i)
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
bool malfunctions::isPrepared()
{
  bool res = true;

  // Example checking a token:
  // CHECK_TOKEN(w_somedata);
  CHECK_TOKEN(mass_token);
  CHECK_TOKEN(engine_token);
  CHECK_TOKEN(control_token);
  CHECK_TOKEN(display_token);
  CHECK_TOKEN(failure_token);

  CHECK_TOKEN(mass_feedback_token);

  CHECK_TOKEN(mass_read_token);
  CHECK_TOKEN(engine_read_token);
  CHECK_TOKEN(control_read_token);
  CHECK_TOKEN(display_read_token);

  // Example checking anything
  // CHECK_CONDITION(myfile.good());
  // CHECK_CONDITION2(sometest, "some test failed");
  CHECK_CONDITION(PScenario);
  //engine
  CHECK_CONDITION(P_engine_button);
  CHECK_CONDITION(Pleft);
  CHECK_CONDITION(Pright);
  CHECK_CONDITION(PLEFT_RPM);
  CHECK_CONDITION(PRIGHT_RPM);
  CHECK_CONDITION(g_engine_time_left);
  CHECK_CONDITION(g_engine_time_right);
  //mass
  CHECK_CONDITION(P_mass_button);
  CHECK_CONDITION(P_control_button);
  CHECK_CONDITION(Px);
  CHECK_CONDITION(Py);
  CHECK_CONDITION(Pz);
  CHECK_CONDITION(Pmass);
  CHECK_CONDITION(Prate);
  CHECK_CONDITION(POld_x);
  CHECK_CONDITION(POld_y);
  CHECK_CONDITION(POld_z);
  CHECK_CONDITION(POld_mass);
  //controls
  CHECK_CONDITION(Paileron);
  CHECK_CONDITION(Prudder);
  CHECK_CONDITION(Prudder_bias);
  CHECK_CONDITION(PARI);
  //display
  CHECK_CONDITION(g_frozen_v);
  CHECK_CONDITION(g_frozen_h);
  CHECK_CONDITION(g_offset_v_value);
  CHECK_CONDITION(g_offset_v_time);
  CHECK_CONDITION(g_offset_h_value);
  CHECK_CONDITION(g_offset_h_time);
  CHECK_CONDITION(g_GPS_failure);
  CHECK_CONDITION(g_VOR_failure);
  CHECK_CONDITION(g_ADC_failure);
  CHECK_CONDITION(g_PFD_failure);
  CHECK_CONDITION(g_GMU_failure);
  CHECK_CONDITION(g_HSI_failure);
  CHECK_CONDITION(g_AFCS_pit_failure);
  CHECK_CONDITION(g_AFCS_rol_failure);
  CHECK_CONDITION(g_clogged_sp);
  CHECK_CONDITION(g_clogged_pt);

  // return result of checks
  return res;
}

// start the module
void malfunctions::startModule(const TimeSpec &time)
{
  do_calc.switchOn(time);
}

// stop the module
void malfunctions::stopModule(const TimeSpec &time)
{
  do_calc.switchOff(time);
}

// fill a snapshot with state data. You may remove this method (and the
// declaration) if you specified to the SimulationModule that the size of
// state snapshots is zero
void malfunctions::fillSnapshot(const TimeSpec& ts,
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
void malfunctions::loadSnapshot(const TimeSpec& t, const Snapshot& snap)
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
void malfunctions::doCalculation(const TimeSpec& ts)
{

	// incoming engine event
	while (engine_read_token.getNumWaitingEvents(ts))
	{
		try
		{
			EventReader<EngineEvent> e(engine_read_token, ts);

			// set GUI
			SET_SPIN_VALUE(PScenario, e.data().id);
			//SET_TOGGLE_ACTV(Pleft, !e.data().power_left);
			//SET_TOGGLE_ACTV(Pright, !e.data().power_right);
			SET_SPIN_VALUE(Pleft, e.data().power_left);
			SET_SPIN_VALUE(Pright, e.data().power_right);
			SET_SPIN_VALUE(PLEFT_RPM, e.data().max_rpm_left);
			SET_SPIN_VALUE(PRIGHT_RPM, e.data().max_rpm_right);
			SET_SPIN_VALUE(g_engine_time_left, e.data().time_left);
			SET_SPIN_VALUE(g_engine_time_right, e.data().time_right);
		}
		catch (Exception& e)
		{
			W_MOD(classname << ": Error while reading EngineEvent @ " << ts);
		}
	}

	// incoming mass event
	while (mass_read_token.getNumWaitingEvents(ts))
	{
		try
		{
			EventReader<MassEvent> m(mass_read_token, ts);

			// set GUI
			SET_SPIN_VALUE(PScenario, m.data().id);
			SET_SPIN_VALUE(Px, m.data().x);
			SET_SPIN_VALUE(Py, m.data().y);
			SET_SPIN_VALUE(Pz, m.data().z);
			SET_SPIN_VALUE(Pmass, m.data().mass);
			SET_SPIN_VALUE(Prate, m.data().time);
		}
		catch (Exception& e)
		{
			W_MOD(classname << ": Error while reading MassEvent @ " << ts);
		}
	}

	// incoming control event
	while (control_read_token.getNumWaitingEvents(ts))
	{
		try
		{
			EventReader<ControlEvent> c(control_read_token, ts);

			// set GUI
			SET_SPIN_VALUE(PScenario, c.data().id);
			SET_SPIN_VALUE(Paileron, c.data().aileron_power);
			SET_SPIN_VALUE(Prudder, c.data().rudder_power);
			SET_SPIN_VALUE(Prudder_bias, c.data().rudder_bias);
			SET_SPIN_VALUE(PARI, c.data().ARI);
		}
		catch (Exception& e)
		{
			W_MOD(classname << ": Error while reading ControlEvent @ " << ts);
		}
	}

	// incoming display event
	while (display_read_token.getNumWaitingEvents(ts))
	{
		try
		{
			EventReader<DisplayEvent> d(display_read_token, ts);

			// set GUI
			SET_SPIN_VALUE(PScenario, d.data().id);
			SET_TOGGLE_ACTV(g_frozen_h, d.data().frozen_h);
			SET_SPIN_VALUE(g_offset_h_value, d.data().offset_h_value);
			SET_SPIN_VALUE(g_offset_h_time, d.data().offset_h_time);
			SET_TOGGLE_ACTV(g_frozen_v, d.data().frozen_v);
			SET_SPIN_VALUE(g_offset_v_value, d.data().offset_v_value);
			SET_SPIN_VALUE(g_offset_v_time, d.data().offset_v_time);
		}
		catch (Exception& e)
		{
			W_MOD(classname << ": Error while reading DisplayEvent @ " << ts);
		}
	}

	// incoming update of the mass change in the model
	while (mass_feedback_token.getNumWaitingEvents(ts))
	{
		try
		{
			EventReader<MassEvent> y(mass_feedback_token, ts);

			// set GUI
			snprintf(text,11,"%+08.2f",y.data().x);
			gtk_entry_set_text(GTK_ENTRY(POld_x),text);
			snprintf(text,11,"%+08.2f",y.data().y);
			gtk_entry_set_text(GTK_ENTRY(POld_y),text);
			snprintf(text,11,"%+08.2f",y.data().z);
			gtk_entry_set_text(GTK_ENTRY(POld_z),text);
			snprintf(text,11,"%+08.2f",y.data().mass);
			gtk_entry_set_text(GTK_ENTRY(POld_mass),text);
		}
		catch (Exception& e)
		{
			W_MOD(classname << ": Error while reading MassEvent feedback @ " << ts);
		}
	}

  // check the state we are supposed to be in
  switch (getAndCheckState(ts)) {
  case SimulationState::HoldCurrent: {
    // only repeat the output, do not change the model state

    break;
    }
  case SimulationState::Replay:
  case SimulationState::Advance: {
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
  // StreamWriter<MyOutput> y(output_token, ts);

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

void malfunctions::trimCalculation(const TimeSpec& ts, const TrimMode& mode)
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


void malfunctions::onMassButtonClicked(GtkButton *button, gpointer user_data)
{
	//D_MOD(classname << " MassButtonClicked");
	EventWriter<MassEvent> m(mass_token);

	// mass shift data
	m.data().id    = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(PScenario));
	m.data().x     = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(Px));
	m.data().y     = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(Py));
	m.data().z     = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(Pz));
	m.data().mass  = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(Pmass));
	m.data().time  = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(Prate));

	D_MOD(classname << " sending mass event");
}

void malfunctions::onControlButtonClicked(GtkButton *button, gpointer user_data)
{
	//D_MOD(classname << " ControlButtonClicked");
	EventWriter<ControlEvent> c(control_token);

	// control data
	c.data().id                  = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(PScenario));
	c.data().aileron_power       = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(Paileron));
	c.data().aileron_power_time  = 0.0;
	c.data().aileron_offset      = 0.0;
	c.data().aileron_offset_time = 0.0;
	c.data().rudder_power        = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(Prudder));
	c.data().rudder_power_time   = 0.0;
	c.data().rudder_offset       = 0.0;
	c.data().rudder_offset_time  = 0.0;
	c.data().rudder_bias         = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(Prudder_bias));
	c.data().ARI                 = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(PARI));

	D_MOD(classname << " sending control event");
}

void malfunctions::onEngineButtonClicked(GtkButton *button, gpointer user_data)
{
	//D_MOD(classname << " EngineButtonClicked");
	EventWriter<EngineEvent> e(engine_token);

	// engine data
	e.data().id            = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(PScenario));
	e.data().power_left    = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(Pleft));
	e.data().power_right   = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(Pright));
	e.data().max_rpm_left  = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(PLEFT_RPM));
	e.data().max_rpm_right = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(PRIGHT_RPM));
	e.data().time_left     = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(g_engine_time_left));
	e.data().time_right    = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(g_engine_time_right));

	D_MOD(classname << " sending engine event");
}

void malfunctions::onDisplayButtonClicked(GtkButton *button, gpointer user_data)
{
	//D_MOD(classname << " DisplayButtonClicked");
	EventWriter<DisplayEvent> d(display_token);

	// display data
	d.data().id             = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(PScenario));
	d.data().frozen_h       = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(g_frozen_h));
	d.data().offset_h_value = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(g_offset_h_value));
	d.data().offset_h_time  = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(g_offset_h_time));
	d.data().frozen_v       = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(g_frozen_v));
	d.data().offset_v_value = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(g_offset_v_value));
	d.data().offset_v_time  = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(g_offset_v_time));
	d.data().offset_phi     = 0.0;
	d.data().offset_theta   = 0.0;
	d.data().offset_psi     = 0.0;

	D_MOD(classname << " sending display event");
}

void malfunctions::onFailureButtonClicked(GtkButton *button, gpointer user_data)
{
  EventWriter<FailureEvent> fail(failure_token);

  fail.data().GPS_failure = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(g_GPS_failure));;
  fail.data().VOR_failure = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(g_VOR_failure));;
  fail.data().ADC_failure = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(g_ADC_failure));;
  fail.data().PFD_failure = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(g_PFD_failure));;
  fail.data().GMU_failure = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(g_GMU_failure));;
  fail.data().HSI_failure = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(g_HSI_failure));;
  fail.data().AFCS_pit = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(g_AFCS_pit_failure));;
  fail.data().AFCS_rol = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(g_AFCS_rol_failure));;
  fail.data().clogged_sp = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(g_clogged_sp));;
  fail.data().clogged_pt = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(g_clogged_pt));;
}

void malfunctions::onFailureclearButtonClicked(GtkButton *button, gpointer user_data)
{
  EventWriter<FailureEvent> fail(failure_token);

  SET_TOGGLE_ACTV(g_GPS_failure, false);
  SET_TOGGLE_ACTV(g_VOR_failure, false);
  SET_TOGGLE_ACTV(g_ADC_failure, false);
  SET_TOGGLE_ACTV(g_PFD_failure, false);
  SET_TOGGLE_ACTV(g_GMU_failure, false);
  SET_TOGGLE_ACTV(g_HSI_failure, false);
  SET_TOGGLE_ACTV(g_AFCS_pit_failure, false);
  SET_TOGGLE_ACTV(g_AFCS_rol_failure, false);
  SET_TOGGLE_ACTV(g_clogged_sp, false);
  SET_TOGGLE_ACTV(g_clogged_pt, false);


  fail.data().GPS_failure = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(g_GPS_failure));;
  fail.data().VOR_failure = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(g_VOR_failure));;
  fail.data().ADC_failure = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(g_ADC_failure));;
  fail.data().PFD_failure = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(g_PFD_failure));;
  fail.data().GMU_failure = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(g_GMU_failure));;
  fail.data().HSI_failure = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(g_HSI_failure));;
  fail.data().AFCS_pit = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(g_AFCS_pit_failure));;
  fail.data().AFCS_rol = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(g_AFCS_rol_failure));;
  fail.data().clogged_sp = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(g_clogged_sp));;
  fail.data().clogged_pt = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(g_clogged_pt));;
}


// Interface to the position and size of the window
bool malfunctions::setWindowPositionSize( const vector< int >& p_vector )
{
    bool succes = true;

    // Check for the size
    if ( p_vector.size() == 4 )
    {
        winglade.setWindow( p_vector );
    }
    else
    {
        E_MOD( getId() << "/" << classname << "::setWindowPositionSize: an incorrect number of elements are supplied, no 4 but " << p_vector.size() );
        succes = false;
    }

    return succes;
}


// Make a TypeCreator object for this module, the TypeCreator
// will check in with the scheme-interpreting code, and enable the
// creation of modules of this type
static TypeCreator<malfunctions> a(malfunctions::getMyParameterTable());
