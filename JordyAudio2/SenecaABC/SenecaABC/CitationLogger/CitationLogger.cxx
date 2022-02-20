/* ------------------------------------------------------------------   */
/*      item            : CitationLogger.cxx
        made by         : stroosma
	from template   : DusimeModuleTemplate.cxx
        template made by: Rene van Paassen
        date            : Thu Jan 13 13:48:31 2005
	category        : body file
        description     :
	changes         : Thu Jan 13 13:48:31 2005 first version
	template changes: 030401 RvP Added template creation comment
        language        : C++
*/

static const char c_id[] =
"$Id: CitationLogger.cxx,v 1.1.1.1 2022/02/17 15:04:28 matteopiras Exp $";

#define CitationLogger_cxx
// include the definition of the module class
#include "CitationLogger.hxx"

// include the debug writing header, by default, write warning and
// error messages
#define D_MOD
#define I_MOD
#define W_MOD
#define E_MOD
#include <debug.h>

// include additional files needed for your calculation here
#include <cstring>
#include <ctime>
#include <Ticker.hxx>

// the standard package for DUSIME, including template source
#define DO_INSTANTIATE
#include <dusime.h>

// class/module name
const char* const CitationLogger::classname = "citation-logger";

// initial condition/trim table
const IncoTable* CitationLogger::getMyIncoTable()
{
  static IncoTable inco_table[] = {
    // enter pairs of IncoVariable and VarProbe pointers (i.e.
    // objects made with new), in this table.
    // For example
//    {(new IncoVariable("example", 0.0, 1.0, 0.01))
//     ->forMode(FlightPath, Constraint)
//     ->forMode(Speed, Control),
//     new VarProbe<CitationLogger,double>
//       (REF_MEMBER(&CitationLogger::i_example))}

    // always close off with:
    { NULL, NULL} };

  return inco_table;
}

// parameters to be inserted
const ParameterTable* CitationLogger::getMyParameterTable()
{
  static const ParameterTable parameter_table[] = {
    { "set-timing",
      new MemberCall<CitationLogger,TimeSpec>
        (&CitationLogger::setTimeSpec), set_timing_description },

    { "check-timing",
      new MemberCall<CitationLogger,vector<int> >
      (&CitationLogger::checkTiming), check_timing_description },

    /*{ "read-cv-channel",
      new MemberCall<CitationLogger, bool>
      (&CitationLogger::readCv),
      "Read from Vc_Channel"},*/

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
CitationLogger::CitationLogger(Entity* e, const char* part, const
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
  out(),
  next_file_number(1),
  prev_state(SimulationState::HoldCurrent),
  //log_dir("."),
  //
  eventID(0),

  turbulence(false), wind_shear(false),
  turb_int(0.0), wind_vel(0.0), wind_dir(0.0),


  inco_file("<no inco file defined>"),
  notes("<no notes yet>"),

  curVerticalState(0),
  curLateralState(0),
  APstate(0),
  target_alt(0),
  target_speed(0),
  hdg_bug(0),
  target_vs(0),
  alt_hold(0),
  active_nav_source(0),
  course(0),
  altitude_target_vnav(0),
  active_leg(0),

  theta_ref(0),
  phi_ref(0),
  ap_de(0),
  ap_da(0),
  ap_dr(0),
  needle_deviation(0),
  dme(0),
  brg(0),
  nav_R(0),

  msg(GFC700Event::GFC700_NONE),
  alt_select(0),
  hdg_select(0),
  crs_select(0),

  GPS_failure(false),
  VOR_failure(false),
  ADC_failure(false),
  PFD_failure(false),
  GMU_failure(false),
  HSI_failure(false),
  AFCS_pit(false),
  AFCS_rol(false),
  clogged_sp(false),
  clogged_pt(false),


  // initialize the data you need for the trim calculation


  // initialize the channel access tokens
  out_token(getId(), NameSet(getEntity(), "CitationOutput", part),101),
  inco_sel_token(getId(), NameSet(getEntity(), "INCOSelect","")),
  turb_token(getId(),NameSet(getEntity(), "WindEvent",part)),
  ap2g_token(getId(), NameSet(getEntity(), "AP2G1000Channel", part)),
  ap_token(getId(), NameSet(getEntity(), "AutopilotChannel", part)),
  gfcr_token(getId(), NameSet(getEntity(), "GFC700Event", ""), ChannelDistribution::JOIN_MASTER),
  fail_token(getId(), NameSet(getEntity(), "FailureEvent", ""), ChannelDistribution::JOIN_MASTER),



  // activity initialization
  cb1(this, &CitationLogger::doCalculation),
  do_calc(getId(), "logging Citation data", &cb1, ps)
{
  // do the actions you need for the simulation

  // connect the triggers for simulation
  do_calc.setTrigger(out_token && ap_token); // cpi_token && Vc_token /*pc_token && sc_token && ps_token && ss_token &&*/

  // connect the triggers for trim calculation. Leave this out if you
  // don not need input for trim calculation
  //trimCalculationCondition(/* fill in your trim triggering channels */);
}

bool CitationLogger::complete()
{
  /* All your parameters have been set. You may do extended
     initialisation here. Return false if something is wrong. */

  // find an available log file number
  // get a list of XXXX.log files
  struct dirent **loglist;
  int ninco = scandir(".", &loglist, is_log_file, alphasort);  //TODO set directory  log_dir.c_str()

  // find the number of the last one
  int nr=0;
  if(ninco > 0) {
    sscanf(loglist[ninco-1]->d_name, "%d.log", &nr);
    I_MOD(getId() << " found latest log file with number " << nr);
  }
  else {
    nr = 0;
    I_MOD(getId() << " found no log files, starting with 0");
  }

  // continue with the next one
  next_file_number = nr + 1;

  return true;
}

// destructor
CitationLogger::~CitationLogger()
{
  //
}

// as an example, the setTimeSpec function
bool CitationLogger::setTimeSpec(const TimeSpec& ts)
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
bool CitationLogger::checkTiming(const vector<int>& i)
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

/*
// Expect input from cv-calculation module over Vc_Channel channel.
bool CitationLogger::readCv(const bool& b)
{
	if(b) {
		// make incoming channel
		Vc_token = new StreamChannelReadToken<Vc_Channel>
			(getId(), NameSet(getEntity(), "Vc_Channel", ""));
		D_MOD(classname << ": Enabled reading from channel Vc_Channel");
	}
	else {
		delete Vc_token; Vc_token = NULL;
		D_MOD(classname << ": Channel Vc_Channel will be ignored");
	}

	return true;
}
*/

// tell DUECA you are prepared
bool CitationLogger::isPrepared()
{
  // do whatever additional calculations you need to prepare the model.

  // Check that all conditions for running are good.
  // It helps to indicate what the problems are
  bool res = true;

  //CHECK_TOKEN(cpi_token);
  CHECK_TOKEN(out_token);
  CHECK_TOKEN(inco_sel_token);
  CHECK_TOKEN(turb_token);
  CHECK_TOKEN(ap2g_token);
  CHECK_TOKEN(ap_token);
  CHECK_TOKEN(gfcr_token);
  CHECK_TOKEN(fail_token);

  //if(Vc_token) CHECK_TOKEN(*Vc_token);

  /*pc_token.isValid() && sc_token.isValid() &&
    ps_token.isValid() && ss_token.isValid() &&
    out_token.isValid();
  if (!res) {
    W_MOD(getId() << '/' << classname << " not prepared, flags=" <<
	  pc_token.isValid() << sc_token.isValid() <<
	  ps_token.isValid() << ss_token.isValid() <<
	  out_token.isValid());
	  }*/

  // return result of check
  return res;
}

// start the module
void CitationLogger::startModule(const TimeSpec &time)
{
  do_calc.switchOn(time);
}

// stop the module
void CitationLogger::stopModule(const TimeSpec &time)
{
  do_calc.switchOff(time);
}

// fill a snapshot with state data. You may remove this method (and the
// declaration) if you specified to the SimulationModule that the size of
// state snapshots is zero
void CitationLogger::fillSnapshot(const TimeSpec& ts,
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
void CitationLogger::loadSnapshot(const TimeSpec& t, const Snapshot& snap)
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
void CitationLogger::doCalculation(const TimeSpec& ts)
{
  // check the state we are supposed to be in
  switch (getAndCheckState(ts)) {
  case SimulationState::HoldCurrent: {
    // state machine
    if(prev_state == SimulationState::Advance) {

      // close file
      out.close();
      out.clear();

      // establish next run number
      next_file_number++;

      prev_state = SimulationState::HoldCurrent;
    }

    // Check for new INCOSelect events,  read INCOSelect and write data to header of log file
	while (inco_sel_token.getNumWaitingEvents(ts))
	{
		try
		{
 			EventReader<INCOSelect> inco_sel(inco_sel_token, ts);

 			eventID   = inco_sel.data().id;
 			inco_file = inco_sel.data().name;
 			notes     = inco_sel.data().note;
		}
		catch (Exception& e)
		{
			W_MOD(classname << ": Error while reading INCO Select @ " << ts);
		}
	}

    break;
  }

  case SimulationState::Replay:
  case SimulationState::Advance: {
    // state machine
    if(prev_state == SimulationState::HoldCurrent) {

      // open file
      char name[10];
      snprintf(name, 10, "%04d.log",next_file_number);
      out.open(name); //TODO set directory using string log_dir

      // write header
      out << "% SenecaTraining log file generated with " << classname
          << " with CVS tag " << c_id << endl;
      out << "% eventID at start: " << eventID << "; loaded inco file: "
          << inco_file << endl;
      out << "% Notes: " << notes << endl;
      time_t tim = time(NULL);
      out << "% run started on " << ctime(&tim);
      out << "% " << endl;
      out << "time\tY_p\tY_q\tY_r\tY_vtas\tY_alpha\tY_beta\tY_phi\tY_theta\tY_psi\tY_h\tY_x\tY_y\tY_pdot\tY_qdot\tY_rdot\tY_vtasdot\tY_hdot\tY_ralt\tY_m\tY_uwinde\tY_vwinde\tY_wwinde\tY_fxcg\tY_fycg\tY_fzcg\tY_n\tY_gamma\tY_chi\tY_vground\tY_torqueleft\tY_rpmleft\tY_rpmleft_IGNORE\tY_torqueright\tY_rpmright\tY_rpmright_IGNORE\tY_flaps_IGNORE\tY_gear_IGNORE\tY_de0\tY_da0\tY_dr0\tY_dte0\tY_dta0\tY_dtr0\tY_df0\tY_gear0\tY_pla10\tY_pla20\tAPstate\tcurVerticalState\tcurLateralState\ttheta_erf\tphi_ref\tap_de\tap_da\tap_dr\ttarget_alt\ttarget_speed\thdg_bug\ttarget_vs\talt_hold\tactive_nav_source\tcourse\taltitude_target_vnav\tactive_leg\tneedle_deviation\tdme\tbrg\tnav_R\tButton_Press\talt_select_GUI\thdg_select_GUI\tcrs_select_GUI\tturbulence\twind_shear\tturb_int\twind_vel\twind_dir\tGPS_failure\tVOR_failure\tADC_failure\tPFD_failure\tGMU_failure\tHSI_failure\tAFCS_pit\tAFCS_rol\tclogged_sp\tclogged_pt\t"  << endl;

      // remember start time
      run_start = ts;

      // remember last state
      prev_state = SimulationState::Advance;
    }

  //////////////////////////////////////////////////////////////////////////////
  // Imports
  //////////////////////////////////////////////////////////////////////////////

  // CitationOutput
	try
	{
		StreamReader<CitationOutput> co(out_token, ts);
		_co = co.data();
	}
	catch(Exception& e)
	{
		W_MOD(classname << ": Error while reading CitationOutput @ " << ts);
	}


	// WindEvent
	if (turb_token.getNumWaitingEvents(ts))
	{
		try
		{
			EventReader<WindEvent> w(turb_token, ts);
			turbulence = w.data().turbulence;
			turb_int   = w.data().turb_int;
			wind_vel   = w.data().wind_vel;
			wind_dir   = w.data().wind_dir;
			wind_shear = w.data().gust;
		}
		catch (Exception& e)
		{
			W_MOD(classname << " caught " << e << " @ " << ts << " while reading WindEvent");
		}
	}

  //AP3G1000 channel
  if (ap2g_token.getNumWaitingEvents(ts))
  {
    try
    {
      EventReader<AP2G1000Channel> ap2g_reader(ap2g_token, ts);

      curVerticalState = ap2g_reader.data().ap_vertical;
      curLateralState = ap2g_reader.data().ap_lateral;
      APstate = ap2g_reader.data().APstate;
      target_alt = ap2g_reader.data().target_alt;
      target_speed = ap2g_reader.data().target_speed;
      hdg_bug = ap2g_reader.data().hdg_bug;
      target_vs = ap2g_reader.data().target_vs;
      alt_hold = ap2g_reader.data().alt_hold;
      active_nav_source = ap2g_reader.data().active_nav_source;
      course = ap2g_reader.data().course;
      altitude_target_vnav = ap2g_reader.data().altitude_target_vnav;
      active_leg = ap2g_reader.data().active_leg;

    }
    catch (Exception& e)
    {
      W_MOD(classname << ": Error while reading AP2G1000Channel!");
    }
  }

  // Autopilot channel
  try
  {
    StreamReader<AutopilotChannel> ap(ap_token, ts);
    theta_ref = ap.data().theta_ref;
    phi_ref = ap.data().phi_ref;
    ap_de = ap.data().de;
    ap_da = ap.data().da;
    ap_dr = ap.data().dr;
    needle_deviation = ap.data().needle_deviation;
    dme = ap.data().dme;
    brg = ap.data().brg;
    nav_R = ap.data().nav_R;
  }
  catch(Exception& e)
  {
    W_MOD(getId()<< classname << " caught " << e << " @ " << ts <<
                    " -- reading CitationOutput Channel");
  }

  msg = GFC700Event::GFC700_NONE;
  if (gfcr_token.getNumWaitingEvents(ts))
  {
    try
    {
      EventReader<GFC700Event> gfc(gfcr_token, ts);
      msg = gfc.data().msg;
      crs_select = round(gfc.data().crs_select);
      alt_select = round(gfc.data().alt_select);
      hdg_select = round(gfc.data().hdg_select);
    }
    catch (Exception& e)
    {
      W_MOD(classname << ": Error while reading GFC700Event!");
    }
  }

  if (fail_token.getNumWaitingEvents(ts))
  {
    try
    {
      EventReader<FailureEvent> fail(fail_token, ts);
      GPS_failure = fail.data().GPS_failure;
      VOR_failure = fail.data(). VOR_failure;
      ADC_failure = fail.data(). ADC_failure;
      PFD_failure = fail.data(). PFD_failure;
      GMU_failure = fail.data(). GMU_failure;
      HSI_failure = fail.data(). HSI_failure;
      AFCS_pit = fail.data(). AFCS_pit;
      AFCS_rol = fail.data(). AFCS_rol;
      clogged_sp = fail.data().clogged_sp;
      clogged_pt = fail.data().clogged_pt;

    }
    catch (Exception& e)
    {
      W_MOD(classname << ": Error while reading FailureEvent!");
    }
  }


    ////////////////////////////////////////////////////////////////////////////
    // Begin to write file
    ////////////////////////////////////////////////////////////////////////////

    // time
    out << (ts.getValidityStart() - run_start.getValidityStart()) * (Ticker::single()->getTimeGranule()) << '\t'; // [1]

	// from CitationOutput
    #if GENCODEGEN >= 110
    #define y_fixed_size y.size()
    #endif
    // [9..NOUTPUTS+8] model output - all from CitationOutput, defined as 47 item float array [2..48]
    for(unsigned int i=0;i<_co.y_fixed_size;i++) {
      out << _co.y[i] << '\t';
    }


    out << APstate << '\t' << curVerticalState << '\t' << curLateralState
        << '\t' << theta_ref << '\t' << phi_ref << '\t' << ap_de << '\t'
        << ap_da << '\t' << ap_dr << '\t';

    out << target_alt << '\t' << target_speed << '\t' << hdg_bug << '\t'
        << target_vs << '\t' << alt_hold << '\t' << active_nav_source << '\t'
        << course << '\t' << altitude_target_vnav << '\t' << active_leg << '\t';

    out << needle_deviation<< '\t' << dme << '\t' << brg << '\t' << nav_R << '\t';

    out << msg << '\t' << alt_select << '\t' << hdg_select << '\t' << crs_select << '\t';

    out << turbulence << '\t' << wind_shear << '\t' << turb_int << '\t'
        << wind_vel << '\t' << wind_dir << '\t';

    out << GPS_failure << '\t' << VOR_failure << '\t' << ADC_failure << '\t'
        << PFD_failure << '\t' << GMU_failure << '\t' << HSI_failure << '\t'
        << AFCS_pit << '\t' << AFCS_rol << '\t' << clogged_sp << '\t'
        << clogged_pt << '\t';



    // finish this line
    out << endl;
    //-*-*-*-*-*- END write to file -*-*-*-*-*-


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

void CitationLogger::trimCalculation(const TimeSpec& ts, const TrimMode& mode)
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

extern "C" {
  // the compare function to filter .log files out of the directory
  static int is_log_file(const struct dirent* entry)
  {
    return (strlen(entry->d_name) > 5) &&
      !strcmp(".log", &(entry->d_name[strlen(entry->d_name) - 4])) &&
      isdigit(entry->d_name[0]) &&
      isdigit(entry->d_name[1]) &&
      isdigit(entry->d_name[2]) &&
      isdigit(entry->d_name[3]) ;
      // a log file has a name with over 5 characters, the extension '.log' and the first 4 characters are digits
  }
}

// Make a TypeCreator object for this module, the TypeCreator
// will check in with the scheme-interpreting code, and enable the
// creation of modules of this type
static TypeCreator<CitationLogger> a(CitationLogger::getMyParameterTable());
