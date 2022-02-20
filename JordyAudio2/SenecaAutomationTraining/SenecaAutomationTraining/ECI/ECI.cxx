/* ------------------------------------------------------------------   */
/*	item            : ECI.cxx
	made by         : Peter van Oorschot
	from template   : DusimeModuleTemplate.cxx
	template made by: Rene van Paassen
	date            : Tue Feb 28 14:58:16 2017
	category        : body file
	description     :
	changes         : Tue Feb 28 14:58:16 2017 first version
	template changes: 030401 RvP Added template creation comment
	                  060512 RvP Modified token checking code
	                  131224 RvP convert snap.data_size to snap.getDataSize()
	language        : C++
	copyright       : (c) 2016 TUDelft-AE-C&S
*/


#define ECI_cxx
// include the definition of the module class
#include "ECI.hxx"

// include the debug writing header, by default, write warning and
// error messagesFA
//#define D_MOD
//#define I_MOD
#define W_MOD
#define E_MOD
#include <debug.h>

// include additional files needed for your calculation here
#include <Ticker.hxx> // for stopwatch
#include <dirent.h>
#include <fstream>
#include <boost/lexical_cast.hpp>
#include <cmath>

// the standard package for DUSIME, including template source
#define DO_INSTANTIATE
#include <dusime.h>

#ifndef KTS2MPS
#define KTS2MPS 0.5144444
#endif

// class/module name
const char* const ECI::classname = "st-eci";

// initial condition/trim table
const IncoTable* ECI::getMyIncoTable()
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
  { "g_send_button", "clicked", gtk_callback(&ECI::onSendButtonClicked)},
  { "g_reset_button", "clicked", gtk_callback(&ECI::onResetButtonClicked)},
  // close off in familiar style
  { NULL, NULL, NULL, NULL }
};

// parameters to be inserted
const ParameterTable* ECI::getMyParameterTable()
{
  static const ParameterTable parameter_table[] = {
    { "set-timing",
      new MemberCall<_ThisModule_,TimeSpec>
        (&_ThisModule_::setTimeSpec), set_timing_description },

    { "check-timing",
      new MemberCall<_ThisModule_,vector<int> >
      (&_ThisModule_::checkTiming), check_timing_description },

    { "set-position-and-size",
      new MemberCall<ECI, vector<int> >
      (&ECI::setWindowPositionSize),
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
    { NULL, NULL, "Experiment Control Interface for the SenecaTraining project."} };

  return parameter_table;
}

// constructor
ECI::ECI(Entity* e, const char* part, const
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
  prev_state(SimulationState::Undefined),
  dt(-1.0),
  stopwatch(0.0),
  run_start(0),
  pa34_v(0.0), pa34_h(0.0), pa34_gear(0.5),
  // GUI
  winglade(),
  //GTK widgets from header - set to NULL - then define in ECI::complete() - and check in ECI::isPrepared()
  g_sce_file_names(NULL),
  g_scenario_id(NULL),
  g_inco_file(NULL),
  g_sce_notes(NULL),
  g_send_button(NULL),
  g_reset_button(NULL),
  g_scetime(NULL),
  g_automationfailure(NULL),
  g_event_text(NULL),
  g_shift_x(NULL),
  g_shift_y(NULL),
  g_shift_z(NULL),
  g_shift_mass(NULL),
  g_shift_time(NULL),
  g_power_left(NULL), g_power_right(NULL),
  g_max_rpm_left(NULL), g_max_rpm_right(NULL),
  g_engine_time_left(NULL), g_engine_time_right(NULL),
  g_aileron_power(NULL),
  g_rudder_power(NULL),
  g_rudder_bias(NULL),
  g_ARI(NULL),
  g_turb_int(NULL),
  g_wind_vel(NULL),
  g_wind_dir(NULL),
  g_wind_shear(NULL),
  g_frozen_v(NULL), g_frozen_h(NULL),
  g_offset_v_value(NULL), g_offset_v_time(NULL), g_offset_h_value(NULL), g_offset_h_time(NULL),
  //tmp_txt(""),
  // selected sce file
  inco_file("<initialize>"),
  sce_name("<initialize>"),
  // general
  scenario_id(-1),
  eventtime(-1.0), eventspeed(-1.0), eventaltitude(-1.0), eventgear(-1.0), eventgeardown(-1.0),
  fpos(0),
  send_events(false),
  // events
  do_engineEvent(false),
  do_massEvent(false),
  do_controlEvent(false),
  do_displayEvent(false),
  do_windEvent(false),
  do_failureEvent(false),
  do_commEvent(false), // added by Matteo Piras
  radioevent(false),   // added by Matteo Piras

 // gear_fail(false),
  // engines
  power_left(1.0), power_right(1.0),
  max_rpm_left(2800), max_rpm_right(2800),
  engine_time_left(0.0), engine_time_right(0.0),
  // mass shift
  shift_x(0.0),
  shift_y(0.0),
  shift_z(0.0),
  shift_mass(0.0),
  shift_time(0.0),
  // controls
  aileron_power(1.0),
  rudder_power(1.0),
  rudder_bias(0.0),
  ARI(0.0),
  elevator_fix(0.0),
  // display
  frozen_v(false),
  frozen_h(false),
  offset_v_value(0.0),
  offset_v_time(0.0),
  offset_h_value(0.0),
  offset_h_time(0.0),
  // wind (incl. turb)
  enable_turb(false),
  enable_windshear(false),
  turb_int(-1.0),
  wind_vel(0.0),
  wind_dir(0.0),
  //
  fg_visibility(100000),
  fg_cloud0_alt(0), fg_cloud1_alt(0), fg_cloud2_alt(0),

  GPS_failure(false),
  VOR_failure(false),
  ADC_failure(false),
  PFD_failure(false),
  GMU_failure(false),
  AFCS_pit(false),
  AFCS_rol(false),
  clogged_sp(false),
  clogged_pt(false),

  APstate(-1),
  verticalFDstate(-1),
  lateralFDstate(-1),
  fp_name(""),

  lat_zero(0),
  lon_zero(0),
  alt_zero(0),
  psi_zero(0),

  active_nav_source(0),

  // fp_comment(""),
  // dummy_string(""),
  // repos_x(0),
  // repos_y(0),


  // initialize the data you need for the trim calculation

  // initialize the channel access tokens, check the documentation for the
  // various parameters. Some examples:
  // r_mytoken(getId(), NameSet(getEntity(), MyData::classname, part),
  //           MyData::classname, 0, Channel::Events, Channel::ReadAllData),
  // w_mytoken(getId(), NameSet(getEntity(), MyData::classname, part),
  //           MyData::classname, "label", Channel::Continuous),
  mass_token(getId(), NameSet(getEntity(), "MassEvent", part), ChannelDistribution::JOIN_MASTER),
  engine_token(getId(), NameSet(getEntity(), "EngineEvent", part), ChannelDistribution::JOIN_MASTER),
  control_token(getId(), NameSet(getEntity(), "ControlEvent", part), ChannelDistribution::JOIN_MASTER),
  display_token(getId(), NameSet(getEntity(), "DisplayEvent", part), ChannelDistribution::JOIN_MASTER),
  turb_token(getId(), NameSet(getEntity(), "WindEvent", part), ChannelDistribution::JOIN_MASTER),
  fail_token(getId(), NameSet(getEntity(), "FailureEvent", part), ChannelDistribution::JOIN_MASTER),
  inco_token(getId(), NameSet(getEntity(), "INCOSelect","")),
  apinco_token(getId(), NameSet(getEntity(), "APIncoEvent","")),
  fginco_token(getId(), NameSet(getEntity(), "FGIncoEvent","")),
  // repos_token(getId(), NameSet(getEntity(), "Reposition",part), ChannelDistribution::NO_OPINION),
  pa34_token(getId(), NameSet(getEntity(), "CitationOutput",part),101),
  comm_token(getId(), NameSet(getEntity(), "CommEvent", part), ChannelDistribution::JOIN_MASTER), // added by Matteo Piras
  // activity initialization
  myclock(),
  cb1(this, &ECI::doCalculation),
  do_calc(getId(), "ECI for the SenecaTraining project", &cb1, ps)
{
  // do the actions you need for the simulation
  winglade.readGladeFile("st_eci.glade", "eci", reinterpret_cast<gpointer>(this), cbtable);

  // connect the triggers for simulation
  do_calc.setTrigger( myclock ); //*Ticker::single()); //TODO replace by myclock() ?

  // connect the triggers for trim calculation. Leave this out if you
  // don not need input for trim calculation
  //trimCalculationCondition(/* fill in your trim triggering channels */);
}

bool ECI::complete()
{
  /* All your parameters have been set. You may do extended
     initialisation here. Return false if something is wrong. */

  // find widgets, checked in isPrepared()
  g_sce_file_names = winglade["g_sce_file_names"];
  g_scenario_id = winglade["g_scenario_id"];
  g_inco_file = winglade["g_inco_file"];
  g_sce_notes = winglade["g_sce_notes"];
  g_send_button = winglade["g_send_button"];
  g_reset_button = winglade["g_reset_button"];
  g_scetime = winglade["g_scetime"];
  g_automationfailure = winglade["g_automationfailure"];
  g_event_text = winglade["g_event_text"];
  g_shift_x = winglade["g_shift_x"];
  g_shift_y = winglade["g_shift_y"];
  g_shift_z = winglade["g_shift_z"];
  g_shift_mass = winglade["g_shift_mass"];
  g_shift_time = winglade["g_shift_time"];
  g_power_left = winglade["g_power_left"];
  g_power_right = winglade["g_power_right"];
  g_max_rpm_left = winglade["g_max_rpm_left"];
  g_max_rpm_right = winglade["g_max_rpm_right"];
  g_engine_time_left = winglade["g_engine_time_left"];
  g_engine_time_right = winglade["g_engine_time_right"];
  g_aileron_power = winglade["g_aileron_power"];
  g_rudder_power = winglade["g_rudder_power"];
  g_rudder_bias = winglade["g_rudder_bias"];
  g_ARI = winglade["g_ARI"];
  g_turb_int = winglade["g_turb_int"];
  g_wind_vel = winglade["g_wind_vel"];
  g_wind_dir = winglade["g_wind_dir"];
  g_wind_shear = winglade["g_wind_shear"];
  g_frozen_v = winglade["g_frozen_v"];
  g_frozen_h = winglade["g_frozen_h"];
  g_offset_v_value = winglade["g_offset_v_value"];
  g_offset_v_time = winglade["g_offset_v_time"];
  g_offset_h_value = winglade["g_offset_h_value"];
  g_offset_h_time = winglade["g_offset_h_time"];

/* DOES NOT WORK PROPERLY
  // Linked list for combobox entries.
  GList *sce_file_list = NULL;

  // Populate combo box with names of scenario files.
  DIR* dir = opendir(".");
  struct dirent* dp;
  while ( (dp = readdir(dir)) != NULL )
  {
    if ( strstr(dp->d_name, ".sce") != NULL )
    {
      D_MOD( classname << ": Found scenario file " << dp->d_name );
      sce_file_list = g_list_append( sce_file_list, dp->d_name );
    }
  }
  // Close directory.
  closedir(dir);
*/

  // fill in the combo list
  // get a list of .sce files
  struct dirent **scelist;
  int nfiles = scandir(".", &scelist, is_sce_file, alphasort);

  // put them in a GTK list
  GList *sce_file_list = NULL;

  for(int i=0; i< nfiles; i++) {
    char* inco = new char[strlen(scelist[i]->d_name)-4+1];
    strncpy(inco, scelist[i]->d_name, strlen(scelist[i]->d_name)-4);
    inco[strlen(scelist[i]->d_name)-4] = '\0';
    sce_file_list = g_list_append(sce_file_list, inco);
    //D_MOD( classname << ": Found scenario file " << inco );
  }

  // Add the strings to the dropdown list
  // TODO GTKCombo is deprecated, replace
  gtk_combo_set_popdown_strings( GTK_COMBO(g_sce_file_names), sce_file_list );

  // Set active element in GTK combo box.
//  gtk_entry_set_text(GTK_ENTRY(GTK_COMBO(g_sce_file_names)->entry), "0000_1.sce");

  // Show glade window.
  winglade.show();

  return true;
}

// destructor
ECI::~ECI()
{
  //
}

// as an example, the setTimeSpec function
bool ECI::setTimeSpec(const TimeSpec& ts)
{
  // a time span of 0 is not acceptable
  if (ts.getValiditySpan() == 0) return false;

  // specify the timespec to the activity
  do_calc.setTimeSpec(ts);
  // or do this with the clock if you have it (don't do both!)
  // myclock.changePeriodAndOffset(ts);

  // do whatever else you need to process this in your model
  dt = ts.getDtInSeconds();

  // return true if everything is acceptable
  return true;
}

// and the checkTiming function
bool ECI::checkTiming(const vector<int>& i)
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
bool ECI::isPrepared()
{
  bool res = true;

  // Example checking a token:
  // CHECK_TOKEN(w_somedata);
  CHECK_TOKEN(mass_token);
  CHECK_TOKEN(engine_token);
  CHECK_TOKEN(control_token);
  CHECK_TOKEN(display_token);
  CHECK_TOKEN(turb_token);
  CHECK_TOKEN(fail_token);
  CHECK_TOKEN(inco_token);
  CHECK_TOKEN(apinco_token);
  CHECK_TOKEN(fginco_token);
  // CHECK_TOKEN(repos_token);
  CHECK_TOKEN(pa34_token);
  CHECK_TOKEN(comm_token); // added by Matteo Piras


  // Example checking anything
  // CHECK_CONDITION(myfile.good());
  // CHECK_CONDITION2(sometest, "some test failed");
  CHECK_CONDITION(g_sce_file_names);
  CHECK_CONDITION(g_scenario_id);
  CHECK_CONDITION(g_inco_file);
  CHECK_CONDITION(g_sce_notes);
  CHECK_CONDITION(g_send_button);
  CHECK_CONDITION(g_reset_button);
  CHECK_CONDITION(g_scetime);
  CHECK_CONDITION(g_automationfailure);
  CHECK_CONDITION(g_event_text);
  CHECK_CONDITION(g_shift_x);
  CHECK_CONDITION(g_shift_y);
  CHECK_CONDITION(g_shift_z);
  CHECK_CONDITION(g_shift_mass);
  CHECK_CONDITION(g_shift_time);
  CHECK_CONDITION(g_power_left);
  CHECK_CONDITION(g_power_right);
  CHECK_CONDITION(g_max_rpm_left);
  CHECK_CONDITION(g_max_rpm_right);
  CHECK_CONDITION(g_engine_time_left);
  CHECK_CONDITION(g_engine_time_right);
  CHECK_CONDITION(g_aileron_power);
  CHECK_CONDITION(g_rudder_power);
  CHECK_CONDITION(g_rudder_bias);
  CHECK_CONDITION(g_ARI);
  CHECK_CONDITION(g_turb_int);
  CHECK_CONDITION(g_wind_vel);
  CHECK_CONDITION(g_wind_dir);
  CHECK_CONDITION(g_wind_shear);
  CHECK_CONDITION(g_frozen_v);
  CHECK_CONDITION(g_frozen_h);
  CHECK_CONDITION(g_offset_v_value);
  CHECK_CONDITION(g_offset_v_time);
  CHECK_CONDITION(g_offset_h_value);
  CHECK_CONDITION(g_offset_h_time);

  // return result of checks
  return res;
}

// start the module
void ECI::startModule(const TimeSpec &time)
{
  do_calc.switchOn(time);
}

// stop the module
void ECI::stopModule(const TimeSpec &time)
{
  do_calc.switchOff(time);
}

// fill a snapshot with state data. You may remove this method (and the
// declaration) if you specified to the SimulationModule that the size of
// state snapshots is zero
void ECI::fillSnapshot(const TimeSpec& ts,
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
void ECI::loadSnapshot(const TimeSpec& t, const Snapshot& snap)
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
void ECI::doCalculation(const TimeSpec& ts)
{
  // check the state we are supposed to be in
  switch (getAndCheckState(ts)) {
  case SimulationState::HoldCurrent: {
	// only repeat the output, do not change the model state

	if(prev_state != SimulationState::HoldCurrent) {
		// enable buttons
		gtk_widget_set_sensitive(GTK_WIDGET(g_send_button), true);
		gtk_widget_set_sensitive(GTK_WIDGET(g_reset_button), true);
		// reset timer (for display)
		stopwatch = 0;
		// mark the simulation state we are in now
		prev_state = SimulationState::HoldCurrent;
	}

	// time reached?
	// if eventtime is 0 (zero), directly send out event (treat event as inco)
	if ( fabs(eventtime) < 1e-6 ) {
		send_events = true;
		D_MOD( classname <<  " : EVENT specified as inco, sent in Hold");
	}

	break;
	}
  case SimulationState::Replay:
  case SimulationState::Advance: {
	// do the simulation calculations, one step

	if(prev_state != SimulationState::Advance) {
		// disable buttons
		gtk_widget_set_sensitive(GTK_WIDGET(g_send_button), false); // comment this line to use the send button in advance
		gtk_widget_set_sensitive(GTK_WIDGET(g_reset_button), false);
		// mark the simulation state we are in now
		prev_state = SimulationState::Advance;
		// remember start time
		run_start = ts.getValidityStart();
	}

	// read model output
    try {
		StreamReaderLatest<CitationOutput> out(pa34_token);

		pa34_v = out.data().y[Y_vtas]*3600/1852; // m/s to knots
		pa34_h = out.data().y[Y_h]*3.281; // m to ft
		pa34_gear = out.data().y[Y_gear0]; // 0=up, 1=down
    }
    catch (Exception& e)
	{
		W_MOD( classname <<  " : problem while reading CitationOutput");
	}

	// update the stopwatch
	stopwatch = ( ts.getValidityStart() - run_start )*( Ticker::single()->getTimeGranule() );
	//stopwatch += dt; // should be precise enough

	// GUI update time indication
	sprintf(tmp_txt, "%3.1f s", stopwatch);
	gtk_label_set_text( GTK_LABEL(g_scetime), tmp_txt );

	// event checks
	// GUI update upcoming event text
	if (eventtime < 0 && eventspeed < 0 && eventaltitude < 0 && eventgear < 0  && eventgeardown < 0 && radioevent == false) {// && gear_fail == false) {
		gtk_label_set_text( GTK_LABEL(g_event_text), "Finished all events." );
		//cout << "eventgeardownvalue is :";
		//cout << eventgeardown;

	}
	else {
		// timer going?
		if (stopwatch < eventtime) {
			sprintf(tmp_txt, "Event upcoming in %3.1f s", eventtime-stopwatch);
			gtk_label_set_text( GTK_LABEL(g_event_text), tmp_txt);
		}
		// time reached?
		if (eventtime >= 0 && stopwatch >= eventtime) {
			send_events = true;
			D_MOD( classname <<  " : EVENT specified time reached");
		}




		//TODO
		// the current way only works if the trigger is approached from one side
		// would be nice to set a boundary and if in bound, send the event
		// have to do enough checks to make sure it does not skip though this between two timesteps
		// or set large enough bounds
		// other option is to have a below/above variable, and if this changes it triggers

		// speed reached?
		if (eventspeed > 0 && pa34_v >= eventspeed) {
			send_events = true;
			D_MOD( classname <<  " : EVENT specified speed reached: " << pa34_v << " > " << eventspeed);
		}

		// altitude reached?
		if (eventaltitude > 0 && pa34_h <= eventaltitude) {
			send_events = true;
			D_MOD( classname <<  " : EVENT specified altitude reached: " << pa34_h << " > " << eventaltitude);
		}

		// gear in position?
		// set for gear going up after start
		if (eventgear > 0 && pa34_gear <= eventgear) {
			send_events = true;
			D_MOD( classname <<  " : EVENT specified gear position reached: " << pa34_gear << " < " << eventgear);
		}

		//if (gear_fail == true){

		    //send_events = true;
            //D_MOD( classname <<  " : EVENT specified gear failed: " << pa34_gear << " < " << eventgear);

		//}

        if (eventgeardown > 0.0 && pa34_gear >= eventgeardown ) {
            send_events = true;
            D_MOD( classname <<  " : EVENT specified gear position reached: " << pa34_gear << " > " << eventgeardown);
            cout << "eventgeardown value is: ";
            cout << eventgeardown;
        }

        if (eventtime > 0 && radioevent == true) {
            send_events = true;
            D_MOD( classname <<  " : EVENT radio comm is transmitted: ");
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

	// is there some event to send out?
	if (send_events)
	{
		// Send EngineEvent
		if (do_engineEvent){
			sendEngineEvent();
			do_engineEvent = false;
		}

		// Send MassEvent
		if (do_massEvent){
			sendMassEvent();
			do_massEvent = false;
		}

		// Send ControlEvent
		if (do_controlEvent){
			sendControlEvent();
			do_controlEvent = false;
		}

		// Send DisplayEvent
		if (do_displayEvent){
			sendDisplayEvent();
			do_displayEvent = false;
		}

        // Send CommEvent
        if (do_commEvent){
            sendCommEvent();
            do_commEvent = false;
        }


        // Send WindEvent
		if (do_windEvent){
			sendWindEvent();
			do_windEvent = false;
		}

    if (do_failureEvent){
      sendFailureEvent();
      do_failureEvent = false;
    }


		//reset all triggers
		send_events   = false;
        radioevent    = false;
		eventtime     = -1;
		eventspeed    = -1;
		eventaltitude = -1;
		eventgear     = -1;
		//gear_fail     = false;
		eventgeardown = -1;

		//read new event
		readScenarioFileNext( sce_name );

		// GUI update
		fullGUIupdate();
	}

  if (snapshotNow()) {
    // keep a copy of the model state. Snapshot sending is done in the
    // sendSnapshot routine, later, and possibly at lower priority
    // e.g.
    // snapshot_state_variable1 = state_variable1; ...
    // (or maybe if your state is very large, there is a cleverer way ...)
  }
}

void ECI::trimCalculation(const TimeSpec& ts, const TrimMode& mode)
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


void ECI::sendCommEvent() // added by Matteo Piras
{
    EventWriter<CommEvent> comm(comm_token); // SimTime::getTimeTick() or SimTime::now() included here?
    comm.data().radiocomm = radiocomm;
    D_MOD(classname << "sending communication event");
}


void ECI::sendEngineEvent()
{
	EventWriter<EngineEvent> e(engine_token); // SimTime::getTimeTick() or SimTime::now() included here?

	e.data().id            = scenario_id;
	e.data().power_left    = power_left;
	e.data().power_right   = power_right;
	e.data().max_rpm_left  = max_rpm_left;
	e.data().max_rpm_right = max_rpm_right;
	e.data().time_left     = engine_time_left;
	e.data().time_right    = engine_time_right;

	D_MOD(classname << "sending engine event");
}

void ECI::sendMassEvent()
{
	EventWriter<MassEvent> m(mass_token);

	m.data().id    = scenario_id;
	m.data().x     = shift_x;
	m.data().y     = shift_y;
	m.data().z     = shift_z;
	m.data().mass  = shift_mass;
	m.data().time  = shift_time;

	D_MOD(classname << " sending mass event");
}

void ECI::sendControlEvent()
{
	EventWriter<ControlEvent> c(control_token);

	c.data().id                  = scenario_id;
	c.data().aileron_power       = aileron_power;
	c.data().aileron_power_time  = 0.0;
	c.data().aileron_offset      = 0.0;
	c.data().aileron_offset_time = 0.0;
	c.data().rudder_power        = rudder_power;
	c.data().rudder_power_time   = 0.0;
	c.data().rudder_offset       = 0.0;
	c.data().rudder_offset_time  = 0.0;
	c.data().rudder_bias         = rudder_bias;
	//c.data().gear_fail           = false;
	c.data().ARI                 = ARI;
	c.data().elevator_fix        = elevator_fix;

	D_MOD(classname << " sending control event ");
}

void ECI::sendDisplayEvent()
{
	EventWriter<DisplayEvent> d(display_token);

	d.data().id             = scenario_id;
	d.data().frozen_h       = frozen_h;
	d.data().offset_h_value = offset_h_value;
	d.data().offset_h_time  = offset_h_time;
	d.data().frozen_v       = frozen_v;
	d.data().offset_v_value = offset_v_value;
	d.data().offset_v_time  = offset_v_time;
	d.data().offset_phi     = 0.0;
	d.data().offset_theta   = 0.0;
	d.data().offset_psi     = 0.0;

	D_MOD(classname << " sending display event");
}

void ECI::sendWindEvent()
{
	EventWriter<WindEvent> w(turb_token);

	w.data().turbulence = enable_turb;
	w.data().turb_int   = ( enable_turb ? turb_int : -1.0 );
	w.data().wind_vel   = wind_vel; // wind velocity   m/s
	w.data().wind_dir   = wind_dir; // wind direction  deg
	w.data().gust       = enable_windshear;

	w.data().visibility = fg_visibility; // [m]
	w.data().cloud_layer_0_altitude = fg_cloud0_alt; // [ft]
	w.data().cloud_layer_1_altitude = fg_cloud1_alt; // [ft]
	w.data().cloud_layer_2_altitude = fg_cloud2_alt; // [ft]

	D_MOD(classname << " sending wind event");
}

void ECI::sendFailureEvent()
{
	EventWriter<FailureEvent> fail(fail_token);
  fail.data().GPS_failure = GPS_failure;
  fail.data().VOR_failure = VOR_failure;
  fail.data().ADC_failure = ADC_failure;
  fail.data().PFD_failure = PFD_failure;
  fail.data().GMU_failure = GMU_failure;
  fail.data().AFCS_pit = AFCS_pit;
  fail.data().AFCS_rol = AFCS_rol;
  fail.data().clogged_sp = clogged_sp;
  fail.data().clogged_pt = clogged_pt;
	D_MOD(classname << " sending failure event");
}

// function to read a scenario file header
void ECI::readScenarioFileHeader(const vstring& name)
{
	string sce_file = name + ".sce";
	string var;
	string value;
	string comment;

	D_MOD(classname << " reading scenario file " << sce_file);

	// prepare to open the file
	ifstream f;
	// open the file
	f.open(sce_file.c_str());

	// check
	if (f.bad()) {
		E_MOD(classname << " Bad scenario, cannot read file " << sce_file);
		eventtime     = -1;
		eventspeed    = -1;
		eventaltitude = -1;
		eventgear     = -1;
		eventgeardown = -1;
		//gear_fail     = false;
		return;
	}

	// gobble all comments (start with #)
	// ignore all lines that are empty or begin with an "empty" character
	while(f.peek() == '#' || f.peek() == '\n' || f.peek() == ' ' || f.peek() == '\t') {
		getline(f, comment, '\n');

		if(f.peek() == '#')
			D_MOD(classname << ": gobbling comment: " << comment);
	}

	// get scenario ID and inco file
	f >> var >> scenario_id;
	if (var!="id") return;
	getline(f, comment, '\n');
	f >> var >> inco_file;
	if (var!="inco") return;
	getline(f, comment, '\n');
  f >> var >> APstate;
  if (var!="APstate") return;
  getline(f, comment, '\n');
  f >> var >> verticalFDstate;
  if (var!="verticalFDstate") return;
  getline(f, comment, '\n');
  f >> var >> lateralFDstate;
  if (var!="lateralFDstate") return;
  getline(f, comment, '\n');
  f >> var >> active_nav_source;
  if (var!="CDI") return;
  getline(f, comment, '\n');
  f >> var >> fp_name;
  if (var!="fp_name") return;
  getline(f, comment, '\n');

  f >> var >> lat_zero;
  if (var!="lat_zero") return;
  getline(f, comment, '\n');
  f >> var >> lon_zero;
  if (var!="lon_zero") return;
  getline(f, comment, '\n');
  f >> var >> alt_zero;
  if (var!="alt_zero") return;
  getline(f, comment, '\n');
  f >> var >> psi_zero;
  if (var!="psi_zero") return;
  getline(f, comment, '\n');

  I_MOD(classname << ": scenario_id = " << scenario_id );
  I_MOD(classname << ": inco_file = " << inco_file );
  I_MOD(classname << ": APstate = " << APstate );
  I_MOD(classname << ": verticalFDstate = " << verticalFDstate );
  I_MOD(classname << ": lateralFDstate = " << lateralFDstate );
  I_MOD(classname << ": lat_zero = " << lat_zero );
  I_MOD(classname << ": lon_zero = " << lon_zero );
  I_MOD(classname << ": alt_zero = " << alt_zero );
  I_MOD(classname << ": psi_zero = " << psi_zero );


	// save current position
	fpos = f.tellg();
	//D_MOD(classname << ": at position " << fpos );

	// close file
	f.close();


  // f.open(fp_name);
  // f >> fp_comment >> dummy_string;
  // f >> fp_comment >> dummy_string;
  // f >> fp_comment >> dummy_string;
  // f >> fp_comment >> dummy_string;
  //
  // f >> fp_comment >> dummy_string;
  // f >> fp_comment >> dummy_string;
  // f >> fp_comment >> dummy_string;
  //
  // f >> fp_comment >> dummy_string;
  // f >> fp_comment >> repos_y >> repos_x >> dummy_string;
  // D_MOD(fp_comment)
  // f.close();
}

void ECI::readScenarioFileNext(const vstring& name)
{
	string sce_file = name + ".sce";
	string var;
	string value;
	string comment;
	float eventtime_after = -1;
	bool event_button_press = false;

	// prepare to open the file
	ifstream f;
	// open file
	f.open(sce_file.c_str());
	D_MOD(classname << " reading scenario file " << sce_file);

	// go to the location we stopped last time
	if (fpos < 0) {
		W_MOD(classname << " end of file was already reached");
		return;
	}
	else f.seekg(fpos);

	// gobble all comments (start with #)
	// ignore all lines that are empty or begin with an "empty" character
	while(f.peek() == '#' || f.peek() == '\n' || f.peek() == ' ' || f.peek() == '\t')
	{
		getline(f, comment, '\n');

		if(comment.length() > 0)
			D_MOD(classname << ": gobbling comment: " << comment);
	}

	// the coming thing must be a scenario :)
	// the first line contains details on what events we will send
	if(f.good()) {
		getline(f, comment, '\n');
		D_MOD(classname << ": EVENT: " << comment );

		// what event?
		// options: controlEvent,massEvent,engineEvent,windEvent
		// multiple options are possible
		if (comment.find("controlEvent") != string::npos) do_controlEvent=true;
		if (comment.find("displayEvent") != string::npos) do_displayEvent=true;
		if (comment.find("engineEvent") != string::npos)  do_engineEvent=true;
		if (comment.find("massEvent") != string::npos)    do_massEvent=true;
		if (comment.find("windEvent") != string::npos)    do_windEvent=true;
    if (comment.find("failureEvent") != string::npos)    do_failureEvent=true;
	}

	// event settings, end with a white line
	while(f.good() && f.peek() != '\n')
	{
		if (f.peek() == '#') {
			getline(f, comment, '\n');
			D_MOD(classname << ": gobbling comment: " << comment);
			continue;
		}

		// if (f.peek() == '@') {  } // trigger

		f >> var >> value;
		getline(f, comment, '\n');
		D_MOD(classname <<": SETTINGS -- var:"<< var <<"; value:"<< value <<"; comment:"<< comment );

		try
		{
			if (f.bad()) {
				// bad, quit
				W_MOD(classname << ": BAD FILE" );
				return;
			}
			// note: the following lines all start with 'else if'

			// event triggers
			GET_SCENARIO_SETTING(float, eventtime)
			GET_SCENARIO_SETTING(float, eventspeed)
			GET_SCENARIO_SETTING(float, eventaltitude)
			GET_SCENARIO_SETTING(float, eventgear)
            GET_SCENARIO_SETTING(float, eventgeardown)
            //GET_SCENARIO_SETTING(float, gear_fail)
			GET_SCENARIO_SETTING(float, eventtime_after)
			ACTIVATE_SCENARIO_SETTING(event_button_press, @button_press)

			// engine event
			GET_SCENARIO_SETTING(float, power_left)
			GET_SCENARIO_SETTING(float, power_right)
			GET_SCENARIO_SETTING(float, max_rpm_left)
			GET_SCENARIO_SETTING(float, max_rpm_right)
			GET_SCENARIO_SETTING(float, engine_time_left)
			GET_SCENARIO_SETTING(float, engine_time_right)

			// mass event
			GET_SCENARIO_SETTING(float, shift_x)
			GET_SCENARIO_SETTING(float, shift_y)
			GET_SCENARIO_SETTING(float, shift_z)
			GET_SCENARIO_SETTING(float, shift_mass)
			GET_SCENARIO_SETTING(float, shift_time)

			// wind and turbulence
			GET_SCENARIO_SETTING(bool, enable_turb)
			GET_SCENARIO_SETTING(float, turb_int)
			GET_SCENARIO_SETTING(float, wind_vel)
			GET_SCENARIO_SETTING(float, wind_dir)
			GET_SCENARIO_SETTING(bool, enable_windshear)
			// flight gear specific settings
			GET_SCENARIO_SETTING(int, fg_visibility)
			GET_SCENARIO_SETTING(int, fg_cloud0_alt)
			GET_SCENARIO_SETTING(int, fg_cloud1_alt)
			GET_SCENARIO_SETTING(int, fg_cloud2_alt)

			// control event
			GET_SCENARIO_SETTING(float, aileron_power)
			GET_SCENARIO_SETTING(float, rudder_power)
			GET_SCENARIO_SETTING(float, rudder_bias)
            GET_SCENARIO_SETTING(float, rudder_offset)
            GET_SCENARIO_SETTING(float, rudder_offset_time)
			GET_SCENARIO_SETTING(float, ARI)
			GET_SCENARIO_SETTING(float, elevator_fix)

			// display event
			GET_SCENARIO_SETTING(bool, frozen_h)
			GET_SCENARIO_SETTING(float, offset_h_value)
			GET_SCENARIO_SETTING(float, offset_h_time)
			GET_SCENARIO_SETTING(bool, frozen_v)
			GET_SCENARIO_SETTING(float, offset_v_value)
			GET_SCENARIO_SETTING(float, offset_v_time)

      // failure event
      GET_SCENARIO_SETTING(bool, GPS_failure)
      GET_SCENARIO_SETTING(bool, VOR_failure)
      GET_SCENARIO_SETTING(bool, ADC_failure)
      GET_SCENARIO_SETTING(bool, PFD_failure)
      GET_SCENARIO_SETTING(bool, GMU_failure)
      GET_SCENARIO_SETTING(bool, AFCS_pit)
      GET_SCENARIO_SETTING(bool, AFCS_rol)
      GET_SCENARIO_SETTING(bool, clogged_sp)
      GET_SCENARIO_SETTING(bool, clogged_pt)

			else W_MOD(classname << ": skipping unknown scenario parameter " << var );
		}
		catch(boost::bad_lexical_cast &e)
		{
			E_MOD(classname << " caught error while loading scenario: " << e.what() );
			//TODO create some feedback to the GUI to indicate incomplete loading of scenario
		}
		catch( ... ){
			E_MOD(classname << "Unknown exception caught while loading scenario!");
		}
	}

	// save current position in file
	fpos = f.tellg();
	//D_MOD(classname << ": at position " << fpos );

	// close file
	f.close();

	// did we reach the end of the file?
	// this is the reason a newline is required after the last line of
	if (fpos < 0)
	{
		D_MOD(classname << ": end of file" );
		eventtime       = -999;
		eventspeed      = -999;
		eventaltitude   = -999;
		eventgear       = -999;
		eventgeardown   = -999;
		eventtime_after = -999;
		radioevent      = false;
	}

	// if eventtime_after was set, set eventtime (overruling any settings for eventtime)
	if (eventtime_after >= 0.0) {
		eventtime = stopwatch + eventtime_after;
	}

	// if event_button_press
	if (event_button_press) {
		// enable send button
		gtk_widget_set_sensitive(GTK_WIDGET(g_send_button), true);
		//TODO always disables when going to advance, so this does not work for the first event after start
	}
}

void ECI::onSendButtonClicked(GtkButton *button, gpointer user_data)
{
	/*TO DO on send button
	- get config file (for selected scenario)
	- load inco (by using IncoSelector)
	- read scenario (separate function to be called)
	*/

	D_MOD(classname << " SendButtonClicked");

	// check state
	if(prev_state == SimulationState::Advance) {
		// if in advance, we have to send an event instead of a scenario
		// do this by setting the time to the current time
		eventtime = stopwatch;

		// disable send buttons
		gtk_widget_set_sensitive(GTK_WIDGET(g_send_button), false);

		return;
	}

	// reset first
	resetParameters();

	//const gchar* sce_fn_cstr = gtk_entry_get_text(GTK_ENTRY(GTK_COMBO(g_sce_file_names)->entry));

	// get selected sce file
	sce_name = gtk_entry_get_text(GTK_ENTRY(GTK_COMBO(g_sce_file_names)->entry));

	// read sce file: header
	readScenarioFileHeader( sce_name );

  // EventWriter<Reposition> repos(repos_token);
  // repos.data().repos_x = repos_x;
  // repos.data().repos_y = repos_y;
  // repos.data().repos_h = 0;
  // repos.data().repos_psi = 0;

	// send inco file name
	EventWriter<INCOSelect> y(inco_token);
	y.data().id   = scenario_id;
	y.data().name = inco_file;
	y.data().note = gtk_entry_get_text(GTK_ENTRY(g_sce_notes));

  EventWriter<APIncoEvent> apinco(apinco_token);
  apinco.data().APstate = APstate;
  apinco.data().lateralFDstate = lateralFDstate;
  apinco.data().verticalFDstate = verticalFDstate;
  apinco.data().active_nav_source = active_nav_source;
  apinco.data().altSelect = 3500;
  apinco.data().hdgSelect = 45;
  apinco.data().crsSelect = 45;
  apinco.data().fp_name = fp_name;

  EventWriter<FGIncoEvent> fginco(fginco_token);
  fginco.data().lat_zero = lat_zero;
  fginco.data().lon_zero = lon_zero;
  fginco.data().alt_zero = alt_zero;
  fginco.data().psi_zero = psi_zero;



	// send out initial values
	sendAllEvents();

	// read sce file: first event
	readScenarioFileNext( sce_name );

	// GUI update
	fullGUIupdate();


}


void ECI::onResetButtonClicked(GtkButton *button, gpointer user_data)
{
	D_MOD(classname << " ResetButtonClicked");
	resetParameters();
	sendAllEvents();
	fullGUIupdate();
}


void ECI::resetParameters()
{
	// selected sce file
	inco_file="<reset>";
	sce_name="<reset>";
	// general
	scenario_id   = -2;
	eventtime     = -1;
	eventspeed    = -1;
	eventaltitude = -1;
	eventgear     = -1;
    eventgeardown = -1;
    radioevent    = false; 
	//gear_fail     = false;
	fpos=0;
	send_events=false;
	// events
	do_engineEvent=false;
	do_massEvent=false;
	do_controlEvent=false;
	do_displayEvent=false;
	do_windEvent=false;
	do_commEvent=false;
  do_failureEvent=false;
	// engines
	power_left=1.0;
	power_right=1.0;
	max_rpm_left=2800;
	max_rpm_right=2800;
	engine_time_left=0.0;
	engine_time_right=0.0;
	// mass shift
	shift_x=0.0;
	shift_y=0.0;
	shift_z=0.0;
	shift_mass=0.0;
	shift_time=0.0;
	// controls
	aileron_power=1.0;
	rudder_power=1.0;
	rudder_bias=0.0;
	ARI=0.0;
	elevator_fix=0.0;
	// display
	frozen_v=false;
	frozen_h=false;
	offset_v_value=0.0;
	offset_v_time=0.0;
	offset_h_value=0.0;
	offset_h_time=0.0;
	// wind (incl. turb)
	enable_turb=false;
	enable_windshear=false;
	turb_int=-1.0;
	wind_vel=0.0;
	wind_dir=0.0;
	//
	fg_visibility=100000;
	fg_cloud0_alt=0;
	fg_cloud1_alt=0;
	fg_cloud2_alt=0;

  GPS_failure = false;
  VOR_failure = false;
  ADC_failure = false;
  PFD_failure = false;
  GMU_failure = false;
  AFCS_pit = false;
  AFCS_rol = false;
  clogged_sp = false;
  clogged_pt = false;

}

void ECI::sendAllEvents()
{
	// send current values out
	sendEngineEvent( );
	sendMassEvent( );
	sendControlEvent( );
	sendCommEvent();
	sendDisplayEvent( );
	sendWindEvent( );
  sendFailureEvent( );
}

void ECI::fullGUIupdate()
{
	// inco file name
	gtk_label_set_text( GTK_LABEL(g_inco_file), const_cast<char*>(inco_file.c_str()) );

	// id
	sprintf(tmp_txt, "%d", scenario_id);
	gtk_label_set_text( GTK_LABEL(g_scenario_id), tmp_txt );

	// stopwatch and countdown
	gtk_label_set_text( GTK_LABEL(g_scetime), "00.0 s" );
	if (scenario_id < 0 ) {
		gtk_label_set_text( GTK_LABEL(g_event_text), "No scenario loaded." );
	}
	else if (eventtime < 0) {
		gtk_label_set_text( GTK_LABEL(g_event_text), "Finished all events." );
	} else {
		sprintf(tmp_txt, "Event upcoming in %3.1f s", eventtime-stopwatch);
		gtk_label_set_text( GTK_LABEL(g_event_text), tmp_txt);
	}
	//TODO quick text, can we do better or is this ok?
	if (eventspeed > 0) {
		sprintf(tmp_txt, "Event upcoming at %3.1f kts", eventspeed);
		gtk_label_set_text( GTK_LABEL(g_event_text), tmp_txt);
	}
	if (eventaltitude > 0) {
		sprintf(tmp_txt, "Event upcoming at %3.0f ft", eventaltitude);
		gtk_label_set_text( GTK_LABEL(g_event_text), tmp_txt);
	}
	if (eventgear > 0) {
		sprintf(tmp_txt, "Event if gear pos < %3.2f", eventgear);
		gtk_label_set_text( GTK_LABEL(g_event_text), tmp_txt);
	}

    if (eventgeardown > 0.0) {
        sprintf(tmp_txt, "Event if gear pos > %3.2f", eventgeardown);
        gtk_label_set_text( GTK_LABEL(g_event_text), tmp_txt);
    }

	// event
	//TODO check bools do_ : indicator of what will be send to be added to GUI

	// mass shift
	SET_LABEL_TEXT_2( shift_x,    g_shift_x );
	SET_LABEL_TEXT_2( shift_y,    g_shift_y );
	SET_LABEL_TEXT_2( shift_z,    g_shift_z );
	SET_LABEL_TEXT( shift_mass, g_shift_mass );
	SET_LABEL_TEXT( shift_time, g_shift_time );

	// engines
	SET_LABEL_TEXT_2( power_left, g_power_left );
	SET_LABEL_TEXT_2( power_right, g_power_right );
	SET_LABEL_TEXT_ROUND( max_rpm_left, g_max_rpm_left );
	SET_LABEL_TEXT_ROUND( max_rpm_right, g_max_rpm_right );
	SET_LABEL_TEXT( engine_time_left, g_engine_time_left );
	SET_LABEL_TEXT( engine_time_right, g_engine_time_right );

	// controls
	SET_LABEL_TEXT_2( aileron_power, g_aileron_power );
	SET_LABEL_TEXT_2( rudder_power, g_rudder_power );
	if (rudder_bias) { SET_LABEL_TEXT_2( rudder_bias, g_rudder_bias ); }
	else             { gtk_label_set_text( GTK_LABEL(g_rudder_bias), "OFF" ); } // instead of displaying 0.00
	SET_LABEL_TEXT_2( ARI, g_ARI );

	// display
	if (frozen_v) { gtk_label_set_text( GTK_LABEL(g_frozen_v), "YES" ); }
	else          { gtk_label_set_text( GTK_LABEL(g_frozen_v), "NO" ); }
	if (frozen_h) { gtk_label_set_text( GTK_LABEL(g_frozen_h), "YES" ); }
	else          { gtk_label_set_text( GTK_LABEL(g_frozen_h), "NO" ); }
	SET_LABEL_TEXT_ROUND( offset_v_value, g_offset_v_value );
	SET_LABEL_TEXT( offset_v_time, g_offset_v_time );
	SET_LABEL_TEXT_ROUND( offset_h_value, g_offset_h_value );
	SET_LABEL_TEXT( offset_h_time, g_offset_h_time );

	// wind (incl. turb)
	if (enable_turb) { SET_LABEL_TEXT_2( turb_int, g_turb_int ); }
	else             { gtk_label_set_text( GTK_LABEL(g_turb_int), "OFF" ); } // turb intensity not relevant
	if(enable_windshear) { gtk_label_set_text( GTK_LABEL(g_wind_shear), "YES" ); }
	else                 { gtk_label_set_text( GTK_LABEL(g_wind_shear), "NO" ); }
	SET_LABEL_TEXT_ROUND( wind_vel, g_wind_vel );
	SET_LABEL_TEXT_ROUND( wind_dir, g_wind_dir );
	//TODO fg_visibility, fg_cloud0_alt, fg_cloud1_alt, fg_cloud2_alt

  if(GPS_failure){
    sprintf(tmp_txt, "GPS failure");
  } else if(VOR_failure){
    sprintf(tmp_txt, "VOR failure");
  } else if(ADC_failure){
    sprintf(tmp_txt, "ADC failure");
  } else if(PFD_failure){
    sprintf(tmp_txt, "PFD failure");
  } else if(GMU_failure){
    sprintf(tmp_txt, "GMU failure");
  } else if(AFCS_pit){
    sprintf(tmp_txt, "Elevator servo");
  } else if(AFCS_rol){
    sprintf(tmp_txt, "Aileron servo");
  } else if(clogged_sp){
    sprintf(tmp_txt, "Blocked Static Port");
  } else if(clogged_pt){
    sprintf(tmp_txt, "Blocked Pitot Tube");
  } else{
    sprintf(tmp_txt, "None");
  }
  gtk_label_set_text( GTK_LABEL(g_automationfailure), tmp_txt);
}

extern "C" {
  // the compare function to filter .inco files out of the directory
  static int is_sce_file(const struct dirent* entry)
  {
    return (strlen(entry->d_name) > 5) && !strcmp(".sce", &(entry->d_name[strlen(entry->d_name) - 4]));
  }
}

// Interface to the position and size of the window
bool ECI::setWindowPositionSize( const vector< int >& p_vector )
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
static TypeCreator<ECI> a(ECI::getMyParameterTable());
