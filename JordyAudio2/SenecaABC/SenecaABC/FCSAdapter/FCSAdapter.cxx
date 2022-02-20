/* ------------------------------------------------------------------   */
/*      item            : FCSAdapter.cxx
        made by         : simona
	from template   : HardwareModuleTemplate.cxx
        template made by: Rene van Paassen
        date            : Fri Apr 27 16:40:29 2012
	category        : body file
        description     :
	changes         : Fri Apr 27 16:40:29 2012 first version
	template changes: 030401 RvP Added template creation comment
        language        : C++
*/

static const char c_id[] =
"$Id: FCSAdapter.cxx,v 1.1.1.1 2022/02/17 15:04:28 matteopiras Exp $";

#define FCSAdapter_cxx
// include the definition of the module class
#include "FCSAdapter.hxx"

// include additional files needed for your calculation here
#include <cmath>

// conversions
#define DEG2RAD 0.0174533

// include the debug writing header, by default, write warning and
// error messages
// #define D_MOD
#define I_MOD
#define W_MOD
#define E_MOD
#include <debug.h>

// the standard package for DUSIME, including template source
#define DO_INSTANTIATE
#include <dusime.h>

// class/module name
const char* const FCSAdapter::classname = "fcs-adapter";

// initial condition/trim table
const IncoTable* FCSAdapter::getMyIncoTable()
{
  static IncoTable inco_table[] = {
    // enter pairs of IncoVariable and VarProbe pointers (i.e.
    // objects made with new), in this table.
    // For example
//    {(new IncoVariable("example", 0.0, 1.0, 0.01))
//     ->forMode(FlightPath, Constraint)
//     ->forMode(Speed, Control),
//     new VarProbe<FCSAdapter,double>
//       (REF_MEMBER(&FCSAdapter::i_example))}

    // always close off with:
    { NULL, NULL} };

  return inco_table;
}

// parameters to be inserted
const ParameterTable* FCSAdapter::getMyParameterTable()
{
  static const ParameterTable parameter_table[] = {
    { "set-timing",
      new MemberCall<FCSAdapter,TimeSpec>
        (&FCSAdapter::setTimeSpec)},

    { "check-timing",
      new MemberCall<FCSAdapter,vector<int> >
      (&FCSAdapter::checkTiming)},

    { "use-column",
      new MemberCall<FCSAdapter, bool>
      (&FCSAdapter::useColumn)},

    { "use-sidestick",
      new MemberCall<FCSAdapter, bool>
      (&FCSAdapter::useSidestick)},

    { "read-config-channel",
      new MemberCall<FCSAdapter, bool>
      (&FCSAdapter::readConfig)},

    { "trim-speed-rad-per-sec",
      new VarProbe<FCSAdapter, double>
      (REF_MEMBER(&FCSAdapter::trim_speed)),
      "speed of elevator trim, rad/s" },

    { "sidestick-x-gain",
      new VarProbe<FCSAdapter, float>
      (&FCSAdapter::uxgain),
      "gain on ux for sidestick"},

    { "sidestick-y-gain",
      new VarProbe<FCSAdapter, float>
      (&FCSAdapter::uygain),
      "gain on uy for sidestick"},

    { "use-qfeel",
      new VarProbe<FCSAdapter, bool>
      (&FCSAdapter::use_qfeel),
      "trim pitch column through qfeel channel"},

    { "use-qfeel-pos",
      new VarProbe<FCSAdapter, bool>
      (&FCSAdapter::use_qfeel_pos),
      "trim pitch column through position offset in qfeel channel (or moment offset)"},

    { "column-pitch-gain",
      new VarProbe<FCSAdapter, double>
      (&FCSAdapter::column_gain_y),
      "pitch gain in column control-loader: column pos [rad] -> de [rad]"},

    { "column-pitch-stiffness",
      new VarProbe<FCSAdapter, double>
      (&FCSAdapter::column_stiffness_y),
      "pitch stiffness in column control-loader"},

    // always close off with:
    { NULL, NULL} };

  return parameter_table;
}

// constructor
FCSAdapter::FCSAdapter(Entity* e, const char* part, const
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
  HardwareModule(e, classname, part, getMyIncoTable(), 0),

  // initialize the data you need in your simulation
  dt(0.01),
  myCPI(), myPCC(PilotControlConfig::MASTER, PilotControlConfig::MASTER, 1.0, false),
  read_column(false), read_sidestick(false),
  use_qfeel(false), use_qfeel_pos(false), myQF(),
  column_gain_y(1.0), column_stiffness_y(100.0), // reasonable
  uxgain(-0.005), uygain(-0.005), // reasonable defaults for Citation
  h2s_trigger(), s2h_trigger(),
  de0(0.0), trim_tab_pos(0.0), trim_speed(0.0), trim_incr(0.0),
  vtas(100), altitude(1000),q(1000),
  hardware_ok(false),

  ap_on(false),
  ap_de(0),
  ap_da(0),
  ap_dr(0),
  ap_da_old(0),
  ap_dr_old(0),

  // default input from joystick/midconsole
  pc_token(getId(), NameSet(getEntity(), "PrimaryControls", part), 101),
  sc_token(getId(), NameSet(getEntity(), "SecondaryControls", part), 101),
  ps_token(getId(), NameSet(getEntity(), "PrimarySwitches", part), 101),
  ss_token(getId(), NameSet(getEntity(), "SecondarySwitches", part), 101),
  in_token(getId(), NameSet(getEntity(), "CitationOutput", part),101),



  // optional input from column
  pc_cpt_token(NULL), ps_cpt_token(NULL),

  // optional input from sidestick
  sso_token(NULL), ss_fo_token(NULL),

  // output to model
  cpi_token(getId(), NameSet(getEntity(), "CitationPilotInput", part), 101),

  // optional output to column (for trimming and slaving)
  qf_token(NULL),

  // optional output to sidestick (for trimming and slaving)
  ssi_token(NULL),

  // input and output to change our configuration
  pcc_cmd_token(NULL),
  pcc_token(getId(), NameSet(getEntity(), "PilotControlConfig", part), 101),

  // trimmed inputs from model
  cpi_trim_token (getId(), NameSet(getEntity(), "CitationPilotInput", "trim")),

  ap_token(getId(), NameSet(getEntity(), "AutopilotChannel", part),101),
  apinco_token(getId(), NameSet(getEntity(), "APIncoEvent", ""), ChannelDistribution::JOIN_MASTER),

  // activity initialization
  s2h_cb1(this, &FCSAdapter::doSim2HW),
  s2h_cb2(this, &FCSAdapter::doSafeSim2HW),
  do_sim2hw(this, "driving control loaders", &s2h_cb1, &s2h_cb2, ps),
  h2s_cb(this, &FCSAdapter::doHW2Sim),
  do_hw2sim(getId(), "combining input from control loaders for model", &h2s_cb, ps)
{
  // do the actions you need for the simulation

  // add default channels to trigger
  h2s_trigger.addTerm(pc_token);
  h2s_trigger.addTerm(sc_token);
  h2s_trigger.addTerm(ps_token);
  h2s_trigger.addTerm(ss_token);


  // reverse activity triggered on clock for now
  // later probably on model output
  s2h_trigger.addTerm(my_clock);
}

bool FCSAdapter::complete()
{
  /* All your parameters have been set. You may do extended
     initialisation here. Return false if something is wrong. */

  // set the triggers
  do_sim2hw.setTrigger(s2h_trigger);
  do_hw2sim.setTrigger(h2s_trigger);

  // now that we know the time step, set the trim increment
  trim_incr = trim_speed*dt;

  // update my configuration to a more sensible default
  if(!pc_cpt_token)
    myPCC.captain = PilotControlConfig::IGNORED;
  if(!sso_token)
    myPCC.first_officer = PilotControlConfig::IGNORED;
  if(pc_cpt_token && sso_token) { // when using both, start with CAPT
    myPCC.captain = PilotControlConfig::MASTER;
    myPCC.first_officer = PilotControlConfig::IGNORED;
  }

  // allow QFeel with RH pedals and sidestick
  if( read_sidestick && use_qfeel) {
    qf_token = new StreamChannelWriteToken<QFeel>
      (getId(), NameSet(getEntity(), "QFeel", ""));
  }

  return true;
}

// destructor
FCSAdapter::~FCSAdapter()
{
  //
}

// as an example, the setTimeSpec function
bool FCSAdapter::setTimeSpec(const TimeSpec& ts)
{
  // a time span of 0 is not acceptable
  if (ts.getValiditySpan() == 0) return false;

  // specify the timespec to the activities
  do_hw2sim.setTimeSpec(ts);
  do_sim2hw.setTimeSpec(ts);

  // do whatever else you need to process this in your model
  // hint: ts.getDtInSeconds()
  dt = ts.getDtInSeconds();

  // return true if everything is acceptable
  return true;
}

// and the checkTiming function
bool FCSAdapter::checkTiming(const vector<int>& i)
{
  if (i.size() == 3) {
    new TimingCheck(do_hw2sim, i[0], i[1], i[2]);
    new TimingCheck(do_sim2hw, i[0], i[1], i[2]);
  }
  else if (i.size() == 2) {
    new TimingCheck(do_hw2sim, i[0], i[1]);
    new TimingCheck(do_sim2hw, i[0], i[1]);
  }
  else {
    return false;
  }
  return true;
}

/** Expect channels from column. */
bool FCSAdapter::useColumn(const bool& b)
{
  if(b) {
    // make incoming channel
    // TODO make part name configurable, now expects "column"
    pc_cpt_token = new StreamChannelReadToken<PrimaryControls>
      (getId(), NameSet(getEntity(), "PrimaryControls", "column"), 101);

    // add to trigger of hw2sim activity
    h2s_trigger.addTerm(*pc_cpt_token);

    // switches
    ps_cpt_token = new StreamChannelReadToken<PrimarySwitches>
      (getId(), NameSet(getEntity(), "PrimarySwitches", "column"), 101);

    // add to trigger of hw2sim activity
    h2s_trigger.addTerm(*ps_cpt_token);

    // make outgoing channel
    qf_token = new StreamChannelWriteToken<QFeel>
      (getId(), NameSet(getEntity(), "QFeel", ""));

    // remember to read it
    read_column = true;
  } else {
    // if token was created already, we cannot remove it from trigger, so fail
    if(pc_cpt_token || ps_cpt_token) {
      E_MOD(classname << " make up your mind about using the column!");
      return false;
    }
    delete pc_cpt_token; pc_cpt_token = NULL;
    delete ps_cpt_token; ps_cpt_token = NULL;
    delete qf_token; qf_token = NULL;

    read_column = false;
  }

  return true;
}

/** Expect channels from sidestick. */
bool FCSAdapter::useSidestick(const bool& b)
{
  if(b) {
    // make incoming channel for stick input
    // TODO look at part names, hard-coded for now
    sso_token = new StreamChannelReadToken<SideStickOutput>
      (getId(), NameSet(getEntity(), "SideStickOutput", ""), 101);

    // add to trigger of hw2sim activity
    h2s_trigger.addTerm(*sso_token);

    // make incoming channel for stick switches
    ss_fo_token = new StreamChannelReadToken<StickSwitches>
      (getId(), NameSet(getEntity(), "StickSwitches", "sidestick"), 101);

    // add to trigger of hw2sim activity
    h2s_trigger.addTerm(*ss_fo_token);

    // make outgoing channel
    ssi_token = new StreamChannelWriteToken<SideStickInput>
      (getId(), NameSet(getEntity(), "SideStickInput", ""));

    // remember to read it
    read_sidestick = true;
  } else {
    // if token was created already, we cannot remove it from trigger, so fail
    if(sso_token || ss_fo_token) {
      E_MOD(classname << " make up your mind about using the sidestick!");
      return false;
    }
    delete sso_token; sso_token = NULL;
    delete ss_fo_token; ss_fo_token = NULL;
    delete ssi_token; ssi_token = NULL;

    read_sidestick = false;
  }

  return true;
}

/** Expect configuration changing channel. */
bool FCSAdapter::readConfig(const bool& b)
{
  if(b) {
    // make incoming channel
    pcc_cmd_token = new EventChannelReadToken<PilotControlConfig>
      (getId(), NameSet(getEntity(), "PilotControlConfig", "command"));
  } else {
    delete pcc_cmd_token; pcc_cmd_token = NULL;
  }

  return true;
}

// tell DUECA you are prepared to start your safety work
bool FCSAdapter::isInitialPrepared()
{
  // do whatever checks on the hardware that you need before working
  // with it. Return true when things are (seem?) OK

  return true;
}

// tell DUECA you are prepared
bool FCSAdapter::isPrepared()
{
  // do whatever additional calculations you need to prepare the model.

  bool res = true;
  CHECK_TOKEN(ap_token);
  CHECK_TOKEN(apinco_token);
  CHECK_TOKEN(pc_token);
  CHECK_TOKEN(sc_token);
  CHECK_TOKEN(ps_token);
  CHECK_TOKEN(ss_token);
  CHECK_TOKEN(in_token);
  if(pc_cpt_token) CHECK_TOKEN(*pc_cpt_token);
  if(ps_cpt_token) CHECK_TOKEN(*ps_cpt_token);
  if(sso_token) CHECK_TOKEN(*sso_token);
  if(ss_fo_token) CHECK_TOKEN(*ss_fo_token);
  CHECK_TOKEN(cpi_token);
  if(qf_token) CHECK_TOKEN(*qf_token);
  if(ssi_token) CHECK_TOKEN(*ssi_token);
  if(pcc_cmd_token) CHECK_TOKEN(*pcc_cmd_token);
  CHECK_TOKEN(pcc_token);

  // return result of checks
  return res;
}

// start the module
void FCSAdapter::initialStartModule(const TimeSpec &time)
{
  hardware_ok = false;
  do_sim2hw.switchOn(time);
}

// start the module
void FCSAdapter::startModule(const TimeSpec &time)
{
  do_sim2hw.switchWork(time);
  do_hw2sim.switchOn(time);
}

// stop the module work
void FCSAdapter::stopModule(const TimeSpec &time)
{
  // unset the hardware_ok flag, so the safe strategy is forced to re-evaluate
  hardware_ok = false;
  do_sim2hw.switchSafe(time);
  do_hw2sim.switchOff(time);
}

// also stop the safe mode
void FCSAdapter::finalStopModule(const TimeSpec& time)
{
  do_sim2hw.switchOff(time);
}

// fill a snapshot with state data. You may remove this method (and the
// declaration) if you specified to the SimulationModule that the size of
// state snapshots is zero
void FCSAdapter::fillSnapshot(const TimeSpec& ts,
			    Snapshot& snap, bool from_trim)
{
}

// reload from a snapshot. You may remove this method (and the
// declaration) if you specified to the SimulationModule that the size of
// state snapshots is zero
void FCSAdapter::loadSnapshot(const TimeSpec& t, const Snapshot& snap)
{
}

// this routine contains the main simulation process of your module. You
// should read the input channels here, and calculate and write the
// appropriate output

////////////////////////////////////////////////////////////////////////////////
// SIM 2 HW
////////////////////////////////////////////////////////////////////////////////
void FCSAdapter::doSim2HW(const TimeSpec& ts)
{
  // check the state we are supposed to be in
  switch (getAndCheckState(ts)) {
  case SimulationState::Inactive: {
  }
  break;

  case SimulationState::Inactive_HoldCurrent: {
    // if the state transition is complete, tell the module
    if (true) {
      transitionComplete();
    }
  }
  break;

  case SimulationState::Calibrate_HoldCurrent: {
    if (true) {
      transitionComplete();
    }
  }
  break;

  case SimulationState::HoldCurrent: {
    // only repeat the output, do not change the model state
    if(apinco_token.getNumWaitingEvents(ts))
    {
      try
      {
        ap_de = 0;
        ap_da = 0;
        ap_dr = 0;
      }
      catch(Exception& e)
      {
        W_MOD(classname << " caught " << e << " @ "<<ts<< " (reading AP Inco)");
      }
    }

    // handle initialization events from model
    if(cpi_trim_token.getNumWaitingEvents(ts)) {
      try {
	EventReader<CitationPilotInput> cpi(cpi_trim_token, ts);

	// set new pitch trim values
	de0 =  cpi.data().de;
	trim_tab_pos = 0.0;

	D_MOD(classname << " received new trim inputs: " << cpi.data());
      } catch (Exception& e) {
	W_MOD(classname << " caught " << e << " @ " << ts);
      }
    }
  }
    // intentional fall-through
    //break;

  case SimulationState::Advance: {

    // read channel calulate q;
    try {
      StreamReaderLatest<CitationOutput> in(in_token);
      vtas     = in.data().y[Y_vtas];
      altitude = in.data().y[Y_h];

      // dynamische druk met gelineariseerde rho (fout =nul op SL en 6000 voet)
      q=vtas*vtas*1.225*0.5*(1-altitude*0.00008325);

      if (q < 1000.0) { q = 1000.0; }
      // 1000 is de dynamische druk van 78 KCAS)
#if 0
      myQF.extra_spring_x=((q-1000.0)/1000.0) * 10.0;
      myQF.extra_spring_y=((q-1000.0)/1000.0) * 793.8 * 0.6;
      myQF.extra_spring_z=((q-1000.0)/1000.0) * 3000.0;
#else
      myQF.extra_spring[0]=((q-1000.0)/1000.0) * 10.0;        // column? (roll)
      myQF.extra_spring[1]=((q-1000.0)/1000.0) * 793.8 * 0.6; // column? (pitch)
      myQF.extra_spring[2]=((q-1000.0)/1000.0) * 3000.0; // LH pedals
      //myQF.extra_spring[3] ??
      //myQF.extra_spring[4] ??
      myQF.extra_spring[5]=((q-1000.0)/1000.0) * 3000.0; // RH pedals
#endif
	}
	catch (Exception& e)
	{
	cout << classname <<  ": Error while reading CitationOutput for qfeel values" << endl;
	}

    // trimming of column
    if(use_qfeel && fabs(column_gain_y) > 1e-3) {
      if(use_qfeel_pos) {
	    // trim through position offset
#if 0
	    myQF.pos_offset_y = (de0 + trim_tab_pos)/column_gain_y ;
	    myQF.mom_offset_y = 0.0;
#else
	    myQF.pos_offset[1] = (de0 + trim_tab_pos)/column_gain_y ;
	    myQF.mom_offset[1] = 0.0;
#endif
      }
      else {
	    // trim through moment offset
	    // DE standaard column stiffnes is die voor 80 knopen
#if 0
	    myQF.pos_offset_y = 0.0;
	    myQF.mom_offset_y = (de0 + trim_tab_pos)/column_gain_y * (column_stiffness_y + ((q-1000.0)/1000.0) * 793.8 * 0.6);
#else
	    myQF.pos_offset[1] = 0.0;
	    myQF.mom_offset[1] = (de0 + trim_tab_pos)/column_gain_y * (column_stiffness_y + ((q-1000.0)/1000.0) * 793.8 * 0.6);
#endif
      }
    }



    // TODO: slave and coop(?) modes

  }
  break;

  case SimulationState::Advance_HoldCurrent: {
    if (true) {
      // reset trim
      trim_tab_pos = 0.0;

      transitionComplete();
    }
  }
  break;

  case SimulationState::HoldCurrent_Inactive: {
    if (true) {
      transitionComplete();
    }
  }
  break;

  default:
    // other states should never be entered, however, if in the future
    // the system is expanded, warn that things have gone wrong.
    // throwing the exception will cause the safe activity to be called
    // in the future
    throw CannotHandleState(getId(),GlobalId(), "state unhandled");
  }

  // output TODO
  if(use_qfeel) {
    StreamWriter<QFeel> qf(*qf_token, ts);

    qf.data() = myQF;
  }
}

////////////////////////////////////////////////////////////////////////////////
// HW 2 SIM
////////////////////////////////////////////////////////////////////////////////

void FCSAdapter::doSafeSim2HW(const TimeSpec& ts)
{
  hardware_ok = true;
}

void FCSAdapter::doHW2Sim(const TimeSpec& ts)
{
  // change configuration if requested
  if(pcc_cmd_token) {
    if(pcc_cmd_token->getNumWaitingEvents(ts)) {
      try {
	EventReader<PilotControlConfig> pcc(*pcc_cmd_token, ts);

	myPCC = pcc.data();
	D_MOD(classname << " received new config: " << myPCC);
      } catch(Exception &e) {
	W_MOD(classname << " caught " << e << " while reading PCC");
      }
    }
  }

  // read default channels
  try {
    #ifdef D_MOD_ACTIVE
    StreamReaderLatest<PrimaryControls> pc(pc_token);
    StreamReaderLatest<SecondaryControls> sc(sc_token);
    StreamReaderLatest<PrimarySwitches> ps(ps_token);
    StreamReaderLatest<SecondarySwitches> ss(ss_token);
    StreamReaderLatest<AutopilotChannel> ap(ap_token);

    // D_MOD(classname << "pc @ " << ts.getValidityStart() << "," <<
	  // pc.timeSpec().getValidityStart() << "," << sc.timeSpec().getValidityStart() <<
	  // "," << ps.timeSpec().getValidityStart() << "," <<
	  // ss.timeSpec().getValidityStart());
    #else
    StreamReader<PrimaryControls> pc(pc_token, ts);
    StreamReader<SecondaryControls> sc(sc_token, ts);
    StreamReader<PrimarySwitches> ps(ps_token, ts);
    StreamReader<SecondarySwitches> ss(ss_token, ts);
    StreamReaderLatest<AutopilotChannel> ap(ap_token, ts);

    #endif

    // move the elevator trim tab
    // note that the default (joystick) can always adjust pitch trim,
    // even when one of the others is in command

    if(ps.data().trim_up) {
      trim_tab_pos -= trim_incr;
      D_MOD(classname << " trim up to " << trim_tab_pos);
    }
    else if(ps.data().trim_down) {
      trim_tab_pos += trim_incr;
      D_MOD(classname << " trim down to " << trim_tab_pos);
    }
    /// Here we read out the trim


    if(ap.data().APstate == 1){
      ap_de = ap.data().de;
      ap_da = ap.data().da;
      ap_dr = ap.data().dr;
    } else{
      // uda = -40 * (p_error - 0.05 * (p-p_old)/ts.getDtInSeconds());
      // da = da_old + ts.getDtInSeconds()*(-1/Tservo*da_old+1/Tservo*uda_old);
      //
      // uda_old = uda;
      // da_old = da;
      ap_da = ap_da_old + ts.getDtInSeconds()*(-1.0/1.0*ap_da);
      ap_dr = ap_dr_old + ts.getDtInSeconds()*(-1.0/1.0*ap_dr);

      ap_da_old = ap_da;
      ap_dr_old = ap_dr;
    }

    // Maybe we need to clip the following values:
    myCPI.de = pc.data().uy + de0 + trim_tab_pos + ap_de; // default: trim through elevator
    myCPI.da = pc.data().ux + ap_da;
    myCPI.dr = pc.data().uz + ap_dr;

    #ifdef D_MOD_ACTIVE
    double old_df = myCPI.df;
    #endif
    myCPI.df = sc.data().flap_setting * DEG2RAD;
    // SRS pedestal: for input of 30 (B777), set 40 deg (Citation)
    if(sc.data().flap_setting > 29.0)
      myCPI.df = 40.0 * DEG2RAD;
    #ifdef D_MOD_ACTIVE
    if(fabs(myCPI.df - old_df) > 1e-5) {
      D_MOD(classname << " new flap setting: " << myCPI.df/DEG2RAD);
    }
    #endif
    myCPI.gear = (ss.data().gear_down ? 1.0 : 0.0);
    myCPI.pla1 = sc.data().throttle_left;
    myCPI.pla2 = sc.data().throttle_right;
  } catch(Exception& e) {
    W_MOD(classname << " caught " << e << " @ " << ts);
  }

  // handle captain's side
  if(read_column) {
    try {
      StreamReader<PrimaryControls> pc(*pc_cpt_token, ts);

      switch(myPCC.captain) {
        case PilotControlConfig::MASTER: {
	  // A/P: this kludge will leave the CLS out of trim on A/P disconnect
          if(use_qfeel)
            myCPI.de = pc.data().uy + ap_de; // trim with QFeel, except A/P
          else
            myCPI.de = pc.data().uy + de0 + trim_tab_pos; // trim through elevator

          myCPI.da = pc.data().ux + ap_da;
          myCPI.dr = pc.data().uz + ap_dr;

        break;
        }
        case PilotControlConfig::SLAVE:
        case PilotControlConfig::IGNORED:
        default: {

        // ignore, use myCPI from other source(s)
        break;
        }
        case PilotControlConfig::COOP: {

	       // if FO plays along, fill our part of the input
      	  if(myPCC.first_officer == PilotControlConfig::COOP && myPCC.capt_bias < 1.01 && myPCC.capt_bias > 0.0) {
      	     myCPI.de = pc.data().uy*myPCC.capt_bias; // note: trim is done with QFeel!
      	      myCPI.da = pc.data().ux*myPCC.capt_bias;
      	       myCPI.dr = pc.data().uz*myPCC.capt_bias;
      	      }
              break;
            }
      }
    } catch (Exception& e) {
      W_MOD(classname << " caught " << e << " @ " << ts <<
	    " while reading column inputs");
    }

    // trim switches
    try {
      StreamReader<PrimarySwitches> ps(*ps_cpt_token, ts);
      // move the elevator trim tab, if in control
      if(myPCC.captain == PilotControlConfig::MASTER || myPCC.captain == PilotControlConfig::COOP) {
	       if(ps.data().trim_up) {
	          trim_tab_pos -= trim_incr;
	          D_MOD(classname << " column trim up to " << trim_tab_pos);
	       }else if(ps.data().trim_down) {
	          trim_tab_pos += trim_incr;
	          D_MOD(classname << " column trim down to " << trim_tab_pos);
	       }
      }
     } catch (Exception& e) {
      W_MOD(classname << " caught " << e << " @ " << ts <<
	    " while reading column switches");
    }
  }

  // handle first officer's side
  if(read_sidestick) {
    try {
      #ifdef D_MOD_ACTIVE
      StreamReaderLatest<SideStickOutput> sso(*sso_token);
      D_MOD(classname << " sso @ " << ts.getValidityStart() << "," <<
	    sso.timeSpec().getValidityStart());
      #else
      StreamReader<SideStickOutput> sso(*sso_token, ts);
      #endif
      switch(myPCC.first_officer) {
      case PilotControlConfig::MASTER: {
      	// sidestick uses fake trimming and no rudder pedal input
      	myCPI.de = sso.data().pitch_aft_pos * uygain + de0 + trim_tab_pos;
      	myCPI.da = sso.data().roll_aft_pos * uxgain;
      	// myCPI.dr = whatever came from default (joystick)

    	break;
      }
      case PilotControlConfig::SLAVE:
      case PilotControlConfig::IGNORED:
      default: {

    	// ignore, use myCPI from other source(s)
    	break;
      }
      case PilotControlConfig::COOP: {
      	// if CPT plays along, fill our part of the input
      	if(myPCC.captain == PilotControlConfig::COOP &&
      	   myPCC.capt_bias < 1.01 && myPCC.capt_bias > 0.0) {
      	  myCPI.de = (sso.data().pitch_aft_pos * uygain + de0 + trim_tab_pos)*(1.0-myPCC.capt_bias);
      	  myCPI.da = (sso.data().roll_aft_pos * uxgain)*(1.0-myPCC.capt_bias);
      	  //myCPI.dr = part of the captain's input, hmmm, so that doesn't work yet... time to include FO pedals
	       }

	    break;
      }
      }

    } catch (Exception& e) {
      W_MOD(classname << " caught " << e << " @ " << ts <<
	    " while reading sidestick inputs");
    }

    // trim switches
    try {
      #ifdef D_MOD_ACTIVE
      StreamReaderLatest<StickSwitches> ss(*ss_fo_token);
      D_MOD(classname << " sticksw @ " << ts.getValidityStart() << "," <<
	    ss.timeSpec().getValidityStart());
      #else
      StreamReader<StickSwitches> ss(*ss_fo_token, ts);
      #endif

      // move the elevator trim tab, if in control
      if(myPCC.first_officer == PilotControlConfig::MASTER || myPCC.first_officer == PilotControlConfig::COOP) {
      	if(ss.data().coolie_up) {
      	  trim_tab_pos -= trim_incr;
      	  D_MOD(classname << " sidestick trim up to " << trim_tab_pos);
      	}
      	else if(ss.data().coolie_down) {
      	  trim_tab_pos += trim_incr;
      	  D_MOD(classname << " sidestick trim down to " << trim_tab_pos);
      	}
      }
    } catch (Exception& e) {
      W_MOD(classname << " caught " << e << " @ " << ts <<
	    " while reading sidestick switches");
    }
  }

  // send out my configuration

  // try
  // {
  //   StreamReader<AutopilotChannel> ap(ap_token, ts);
  //   //D_MOD("Autopilot channel succesfully read")
  //   // if(ap.data().ap_on){
  //   //   myCPI.de = ap.data().de;
  //   // }
  // }
  // catch(Exception& e)
  // {
  //   W_MOD(getId()<< classname << " caught " << e << " @ " << ts << " -- reading Autopilot Channel");
  // }
  //
  // {
  //   StreamWriter<PilotControlConfig> pcc(pcc_token, ts);
  //
  //   pcc.data() = myPCC;
  // }

  // send out the output to the model
  {
    StreamWriter<CitationPilotInput> cpi(cpi_token, ts);
    cpi.data() = myCPI;
  }
}

void FCSAdapter::trimCalculation(const TimeSpec& ts, const TrimMode& mode)
{
}

// Make a TypeCreator object for this module, the TypeCreator
// will check in with the scheme-interpreting code, and enable the
// creation of modules of this type
static TypeCreator<FCSAdapter> a(FCSAdapter::getMyParameterTable());
