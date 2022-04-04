/* ------------------------------------------------------------------   */
/*      item            : CitationNavigator.cxx
        made by         : stroosma
	from template   : DusimeModuleTemplate.cxx
        template made by: Rene van Paassen
        date            : Thu Jan 20 12:34:22 2005
	category        : body file 
        description     : 
	changes         : Thu Jan 20 12:34:22 2005 first version
	template changes: 030401 RvP Added template creation comment
        language        : C++
*/

static const char c_id[] =
"$Id: CitationNavigator.cxx,v 1.1.1.1 2022/02/17 15:04:28 matteopiras Exp $";

#define CitationNavigator_cxx
// include the definition of the module class
#include "CitationNavigator.hxx"

// include the debug writing header, by default, write warning and 
// error messages
#define D_MOD
#define I_MOD
#define W_MOD
#define E_MOD
#include <debug.h>

// include additional files needed for your calculation here
#include <cstring>
#include <cmath>
#include <fstream>

// the standard package for DUSIME, including template source
#define DO_INSTANTIATE
#include <dusime.h>

// class/module name
const char* const CitationNavigator::classname = "citation-navigator";

// initial condition/trim table
const IncoTable* CitationNavigator::getMyIncoTable()
{
  static IncoTable inco_table[] = {
    // enter pairs of IncoVariable and VarProbe pointers (i.e. 
    // objects made with new), in this table.
    // For example
//    {(new IncoVariable("example", 0.0, 1.0, 0.01))
//     ->forMode(FlightPath, Constraint)
//     ->forMode(Speed, Control),
//     new VarProbe<CitationNavigator,double>
//       (REF_MEMBER(&CitationNavigator::i_example))}
    
    // always close off with:
    { NULL, NULL} };

  return inco_table;
}

// parameters to be inserted
const ParameterTable* CitationNavigator::getMyParameterTable()
{
  static const ParameterTable parameter_table[] = {
    { "set-timing", 
      new MemberCall<CitationNavigator,TimeSpec>
        (&CitationNavigator::setTimeSpec), set_timing_description },

    { "check-timing", 
      new MemberCall<CitationNavigator,vector<int> >
      (&CitationNavigator::checkTiming), check_timing_description },

    { "event-master",
      new VarProbe<CitationNavigator, bool>
      (REF_MEMBER(&CitationNavigator::MCP737Event_master)),
      "act as JOIN_MASTER on the MCP737Event channel" },

    { "magnetic-variation",
      new VarProbe<CitationNavigator, float>
      (REF_MEMBER(&CitationNavigator::mag_var)),
      "magnetic variation in radians" },

    { "mcp-captain-in-command",
      new VarProbe<CitationNavigator, bool>
      (REF_MEMBER(&CitationNavigator::mcp_capt)),
      "take the course selection from the captain's side of the MCP" },

    { "use-pilot-control-config", 
      new MemberCall<CitationNavigator,bool >
      (&CitationNavigator::usePilotControlConfig), 
      "monitor the PilotControlConfig stream channel" },

    /* You can extend this table with labels and MemberCall or
       VarProbe pointers to perform calls or insert values into your
       class objects. Please also add a description (c-style string).  

       Note that for efficiency, set_timing_description and
       check_timing_description are pointers to pre-defined strings,
       you can simply enter the descriptive strings in the table. */

    /* The table is closed off with NULL pointers for the variable
       name and MemberCall/VarProbe object. The description is used to
       give an overall description of the module. */
    { NULL, NULL, "handles MCP and navigation data"} };

  return parameter_table;
}

// constructor
CitationNavigator::CitationNavigator(Entity* e, const char* part, const
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
  nd(0.0, 0.0, 0.0, 0.0, NavData::NODIR, 0.0, 0.0, 0.0, 0.0, 0.0,
     NavData::NONE, NavData::NONE, NavData::NONE, NavData::NONE), 
  MCP737Event_master(false),
  mag_var(0.0),
  mcp_capt(true),
  prev_capt_ctrl_cfg(PilotControlConfig::IGNORED), 
  prev_fo_ctrl_cfg(PilotControlConfig::IGNORED),

  // initialize the data you need for the trim calculation

  // initialize the channel access tokens
  // example
  // my_token(getId(), NameSet(getEntity(), "MyData", part)),
  co_token(getId(), NameSet(getEntity(), "CitationOutput", part),101),
  nav_token(getId(), NameSet(getEntity(), "NavData", part)),
  star_token(getId(), NameSet(getEntity(), "STARSelect", part)),
  mcpin_token(getId(), NameSet(getEntity(), "MCP737Event", part)),
  mcpout_token(NULL), // we'll make it later
  pcc_token(NULL),
  pcc_cmd_token(getId(), NameSet(getEntity(), "PilotControlConfig", "command")),

  // activity initialization
  cb1(this, &CitationNavigator::doCalculation),
  do_calc(getId(), "navigating", &cb1, ps)
{
  // do the actions you need for the simulation
  for(int i=0; i<3; i++) {
    lnav_ref[i] = 0.0;
    hdg_ref[i] = 0.0;
    ils_ref[i] = 0.0;
  }

  // connect the triggers for simulation
  // moved to complete
  //do_calc.setTrigger(co_token);
  
  // connect the triggers for trim calculation. Leave this out if you 
  // don not need input for trim calculation 
  //trimCalculationCondition(/* fill in your trim triggering channels */);
}

bool CitationNavigator::complete()
{
  /* All your parameters have been set. You may do extended
     initialisation here. Return false if something is wrong. */
  
  // open the outgoing event channel
  if(MCP737Event_master) {
    mcpout_token = new EventChannelWriteToken<MCP737Event>
      (getId(), NameSet(getEntity(), "MCP737Event", getPart()),
       ChannelDistribution::JOIN_MASTER);
  }
  else {
    mcpout_token = new EventChannelWriteToken<MCP737Event>
      (getId(), NameSet(getEntity(), "MCP737Event", getPart()),
       ChannelDistribution::NO_OPINION);
  }

  // set the triggers
  if(pcc_token) {
    do_calc.setTrigger(co_token && *pcc_token);
  }
  else {
    do_calc.setTrigger(co_token);
  }

  return true;
}

// destructor
CitationNavigator::~CitationNavigator()
{
  //
  delete pcc_token;
}

// as an example, the setTimeSpec function
bool CitationNavigator::setTimeSpec(const TimeSpec& ts)
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
bool CitationNavigator::checkTiming(const vector<int>& i)
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

// handle PilotControlConfig channel
bool CitationNavigator::usePilotControlConfig(const bool& b)
{
  if(b) {
    pcc_token = new StreamChannelReadToken<PilotControlConfig>(getId(), NameSet(getEntity(), "PilotControlConfig", getPart()));
  }
  else {
    delete pcc_token;
    pcc_token = NULL;
  }

  return true;
}

// tell DUECA you are prepared
bool CitationNavigator::isPrepared()
{
  // do whatever additional calculations you need to prepare the model. 

  // Check that all conditions for running are good. 
  bool res = true;

  CHECK_TOKEN(co_token);
  CHECK_TOKEN(nav_token);
  CHECK_TOKEN(star_token);
  CHECK_TOKEN(mcpin_token);
  CHECK_TOKEN(pcc_cmd_token);

  if(mcpout_token) CHECK_TOKEN(*mcpout_token);
  if(pcc_token) CHECK_TOKEN(*pcc_token);

  // return result of check
  return res;
}

// start the module
void CitationNavigator::startModule(const TimeSpec &time)
{
  do_calc.switchOn(time);
}

// stop the module
void CitationNavigator::stopModule(const TimeSpec &time)
{
  do_calc.switchOff(time);
}

// fill a snapshot with state data. You may remove this method (and the
// declaration) if you specified to the SimulationModule that the size of 
// state snapshots is zero
void CitationNavigator::fillSnapshot(const TimeSpec& ts, 
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
void CitationNavigator::loadSnapshot(const TimeSpec& t, const Snapshot& snap)
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
void CitationNavigator::doCalculation(const TimeSpec& ts)
{
  // handle events from the MCP
  while(mcpin_token.getNumWaitingEvents(ts)) {
    try {
      EventReader<MCP737Event> mcp(mcpin_token, ts);
    
      // handle only events intended for us
      if(mcp.data().receiver & SYS_SIM) {
	
	// handle mode button pushes
	// HDG
	if(mcp.data().msg == MCP737Event::MCP_HDG_PUSH) {
	  if(nd.lateral_mode != NavData::HDG) { // on
	    turnOffLateralModes(NavData::HDG, ts);
	    
	    nd.lateral_mode = NavData::HDG;
	    mcpout_token->sendEvent(new MCP737Event(SYS_SIM, SYS_GUI | SYS_MCP,
						    MCP737Event::MCP_HDG_ON, 1.0), ts);
	    
	    // set the reference course and heading bug, as specified in the STAR
	    // TODO: check if this is actually convenient
	    nd.course_ref = hdg_ref[2];
	    if(mcp_capt) {
	      mcpout_token->sendEvent(new MCP737Event(SYS_SIM, SYS_GUI | SYS_MCP,
						      MCP737Event::MCP_COURSE1_SET, 
						      nearbyint(hdg_ref[2]*RAD2DEG)), ts);
	    }
	    else {
	      mcpout_token->sendEvent(new MCP737Event(SYS_SIM, SYS_GUI | SYS_MCP,
						      MCP737Event::MCP_COURSE2_SET, 
						      nearbyint(hdg_ref[2]*RAD2DEG)), ts);
	    }
	    
	    nd.heading_ref = hdg_ref[2];
	    mcpout_token->sendEvent(new MCP737Event(SYS_SIM, SYS_GUI | SYS_MCP,
						    MCP737Event::MCP_HDG_SET, 
						    nearbyint(hdg_ref[2]*RAD2DEG)), ts);
	  }
	  else { // off
	    nd.lateral_mode = NavData::NONE;// TODO check this!
	    mcpout_token->sendEvent(new MCP737Event(SYS_SIM, SYS_GUI | SYS_MCP,
						    MCP737Event::MCP_HDG_OFF, -1.0), ts);
	  }
	}
	// LNAV
	if(mcp.data().msg == MCP737Event::MCP_LNAV_PUSH) {
	  if(nd.lateral_mode != NavData::LNAV) { // on
	    turnOffLateralModes(NavData::LNAV, ts);
	    
	    nd.lateral_mode = NavData::LNAV;
	    mcpout_token->sendEvent(new MCP737Event(SYS_SIM, SYS_GUI | SYS_MCP,
						    MCP737Event::MCP_LNAV_ON, 1.0), ts);
	    
	    // set the reference course and heading bug, as specified in the STAR
	    // TODO: check if this is actually convenient
	    nd.course_ref = lnav_ref[2];
	    if(mcp_capt) {
	      mcpout_token->sendEvent(new MCP737Event(SYS_SIM, SYS_GUI | SYS_MCP,
						      MCP737Event::MCP_COURSE1_SET, 
						      nearbyint(lnav_ref[2]*RAD2DEG)), ts);
	    }
	    else {
	      mcpout_token->sendEvent(new MCP737Event(SYS_SIM, SYS_GUI | SYS_MCP,
						      MCP737Event::MCP_COURSE2_SET, 
						      nearbyint(lnav_ref[2]*RAD2DEG)), ts);
	    }
	    
	    nd.heading_ref = lnav_ref[2];
	    mcpout_token->sendEvent(new MCP737Event(SYS_SIM, SYS_GUI | SYS_MCP,
						    MCP737Event::MCP_HDG_SET, 
						    nearbyint(lnav_ref[2]*RAD2DEG)), ts);
	}
	  else { // off
	    nd.lateral_mode = NavData::NONE;// TODO check this!
	    mcpout_token->sendEvent(new MCP737Event(SYS_SIM, SYS_GUI | SYS_MCP,
						    MCP737Event::MCP_LNAV_OFF, -1.0), ts);
	  }
	}
	// APP
	if(mcp.data().msg == MCP737Event::MCP_APP_PUSH) {
	  if(nd.lateral_mode != NavData::LOC) { // not active
	    if(nd.armed_lateral_mode != NavData::LOC) { // arm
	      nd.armed_lateral_mode = NavData::LOC;
	      mcpout_token->sendEvent(new MCP737Event(SYS_SIM, SYS_GUI | SYS_MCP,
						      MCP737Event::MCP_APP_ON, 1.0), ts);
	      // switch to ILS references
	      nd.course_ref = ils_ref[2];
	      if(mcp_capt) {
		mcpout_token->sendEvent(new MCP737Event(SYS_SIM, SYS_GUI | SYS_MCP,
							MCP737Event::MCP_COURSE1_SET, 
							nearbyint(ils_ref[2]*RAD2DEG)), ts);
	      }
	      else {
		mcpout_token->sendEvent(new MCP737Event(SYS_SIM, SYS_GUI | SYS_MCP,
							MCP737Event::MCP_COURSE2_SET, 
							nearbyint(ils_ref[2]*RAD2DEG)), ts);
	      }
	    }
	    else { // unarm
	      nd.armed_lateral_mode = NavData::NONE;
	      mcpout_token->sendEvent(new MCP737Event(SYS_SIM, SYS_GUI | SYS_MCP,
						      MCP737Event::MCP_APP_OFF, -1.0), ts);
	    }
	  }
	  else { // active
	    nd.lateral_mode = NavData::NONE;
	    mcpout_token->sendEvent(new MCP737Event(SYS_SIM, SYS_GUI | SYS_MCP,
						    MCP737Event::MCP_APP_OFF, -1.0), ts);
	  }
	}
	
	// handle set points
	if( (mcp.data().msg == MCP737Event::MCP_COURSE1_SET && mcp_capt) ||
	    (mcp.data().msg == MCP737Event::MCP_COURSE2_SET && !mcp_capt) ) {
	  nd.course_ref = mcp.data().data*DEG2RAD;
	}
	if(mcp.data().msg == MCP737Event::MCP_HDG_SET) {
	  nd.heading_ref = mcp.data().data*DEG2RAD;
	}
	if(mcp.data().msg == MCP737Event::MCP_ALT_SET) {
	  nd.alt_ref = mcp.data().data;
	}
	if(mcp.data().msg == MCP737Event::MCP_SPD_SET) {
	  nd.speed_ref = mcp.data().data;
	}
	
	// handle pilot control transfers initiated through MCP
	// for now it's either/or
	if(mcp.data().msg == MCP737Event::MCP_CWS_A_PUSH) {
	  pcc_cmd_token.sendEvent(new PilotControlConfig(PilotControlConfig::MASTER, 
							 PilotControlConfig::IGNORED, 1.0, false), ts);
	}
	if(mcp.data().msg == MCP737Event::MCP_CWS_B_PUSH) {
	  pcc_cmd_token.sendEvent(new PilotControlConfig(PilotControlConfig::IGNORED, 
							 PilotControlConfig::MASTER, 1.0, false), ts);
	}
	
	//D_MOD(getId() << " received " << mcp.data());
      }
    }
    catch(Exception& e) {
      // weird, but not fatal
      W_MOD(classname << " caught " << e);
    }
  }

  // check the state we are supposed to be in
  switch (getAndCheckState(ts)) {
  case SimulationState::HoldCurrent: {
    // only repeat the output, do not change the model state

    if(star_token.getNumWaitingEvents(ts)) {
      EventReader<STARSelect> star(star_token, ts);

      I_MOD(getId() << " initializing STAR " << star.data().name);

      readStarFile(star.data().name);

      // if ap modes selected, fill in the STAR values
      switch(nd.lateral_mode) {
      case NavData::LNAV : {
	nd.course_ref = lnav_ref[2];
	if(mcp_capt) {
	  mcpout_token->sendEvent(new MCP737Event(SYS_SIM, SYS_GUI | SYS_MCP,
						  MCP737Event::MCP_COURSE1_SET, 
						  nearbyint(lnav_ref[2]*RAD2DEG)), ts);
	}
	else {
	  mcpout_token->sendEvent(new MCP737Event(SYS_SIM, SYS_GUI | SYS_MCP,
						  MCP737Event::MCP_COURSE2_SET, 
						  nearbyint(lnav_ref[2]*RAD2DEG)), ts);
	}

	nd.heading_ref = lnav_ref[2];
	mcpout_token->sendEvent(new MCP737Event(SYS_SIM, SYS_GUI | SYS_MCP,
						MCP737Event::MCP_HDG_SET, 
						nearbyint(lnav_ref[2]*RAD2DEG)), ts);
	break;
      }
      case NavData::HDG : {
	nd.course_ref = hdg_ref[2];
	if(mcp_capt) {
	  mcpout_token->sendEvent(new MCP737Event(SYS_SIM, SYS_GUI | SYS_MCP,
						  MCP737Event::MCP_COURSE1_SET, 
						  nearbyint(hdg_ref[2]*RAD2DEG)), ts);
	}
	else {
	  mcpout_token->sendEvent(new MCP737Event(SYS_SIM, SYS_GUI | SYS_MCP,
						  MCP737Event::MCP_COURSE2_SET, 
						  nearbyint(hdg_ref[2]*RAD2DEG)), ts);
	}
	nd.heading_ref = hdg_ref[2];
	mcpout_token->sendEvent(new MCP737Event(SYS_SIM, SYS_GUI | SYS_MCP,
						MCP737Event::MCP_HDG_SET, 
						nearbyint(hdg_ref[2]*RAD2DEG)), ts);
	break;
      }
      case NavData::LOC : {
	nd.course_ref = ils_ref[2];
	if(mcp_capt) {
	  mcpout_token->sendEvent(new MCP737Event(SYS_SIM, SYS_GUI | SYS_MCP,
						  MCP737Event::MCP_COURSE1_SET, 
						  nearbyint(ils_ref[2]*RAD2DEG)), ts);
	}
	else {
	  mcpout_token->sendEvent(new MCP737Event(SYS_SIM, SYS_GUI | SYS_MCP,
						  MCP737Event::MCP_COURSE2_SET, 
						  nearbyint(ils_ref[2]*RAD2DEG)), ts);
	}
	  
	nd.heading_ref = ils_ref[2];
	mcpout_token->sendEvent(new MCP737Event(SYS_SIM, SYS_GUI | SYS_MCP,
						MCP737Event::MCP_HDG_SET, 
						nearbyint(ils_ref[2]*RAD2DEG)), ts);
	break;
      }
      default: {
	break;
      }
      }
	
      // set the reference speed
      nd.speed_ref = 0.0; //Peter: changed from 97 (all refs set to zero)
      mcpout_token->sendEvent(new MCP737Event(SYS_SIM, SYS_GUI | SYS_MCP,
					      MCP737Event::MCP_SPD_SET, 
					      nd.speed_ref), ts);
    }

    //break;
    // intentional fall-through
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

    try {
      StreamReader<CitationOutput> co(co_token, ts);
      float x = co.data().y[Y_x];
      float y = co.data().y[Y_y];
     
      // do the simulation calculations, one step

      switch (nd.lateral_mode) {
      case NavData::HDG : {
	
	// if loc mode armed, calculate ils deviations and present everything rel. to ILS
	if(nd.armed_lateral_mode == NavData::LOC) {
	  // calculate with ils_ref[012]
	  NavData::to_from dummy;
	  nd.ils_loc_dev = getDeviation(x, y, ils_ref[0], ils_ref[1], ils_ref[2] - mag_var,
					dummy);
	  nd.course_dev = nd.ils_loc_dev;

	  // GS deviation
	  nd.ils_gs_dev = 3.0*DEG2RAD - atan2(co.data().y[Y_h], 
					      sqrt( (ils_ref[0]-x)*(ils_ref[0]-x) +
						    (ils_ref[1]-y)*(ils_ref[1]-y) ));
	  
	  // calculate distance + time2go to ils_ref[01]
	  nd.distance = sqrt( (ils_ref[0]-x)*(ils_ref[0]-x) +
			      (ils_ref[1]-y)*(ils_ref[1]-y) );
	  nd.time2go = nd.distance / co.data().y[Y_vtas];// seconds
	  
	  // capture localizer
	  if(fabs(nd.ils_loc_dev) < 2.0*DEG2RAD) { // TODO: check value
	    turnOffLateralModes(NavData::LOC, ts);
	    nd.lateral_mode = NavData::LOC;
	    nd.armed_lateral_mode = NavData::NONE;

	    // set the reference course, as specified in the STAR
	    // TODO: check if this is actually convenient
	    nd.course_ref = ils_ref[2];
	    if(mcp_capt) {
	      mcpout_token->sendEvent(new MCP737Event(SYS_SIM, SYS_GUI | SYS_MCP,
						      MCP737Event::MCP_COURSE1_SET, 
						      nearbyint(ils_ref[2]*RAD2DEG)), ts);
	    }
	    else {
	      mcpout_token->sendEvent(new MCP737Event(SYS_SIM, SYS_GUI | SYS_MCP,
						      MCP737Event::MCP_COURSE1_SET, 
						      nearbyint(ils_ref[2]*RAD2DEG)), ts);
	    }
	  }
	}
	else {
	  // calculate course_dev with hdg_ref[0], hdg_ref[1], nd.course_ref
	  nd.course_dev = getDeviation(x, y, hdg_ref[0], hdg_ref[1], nd.course_ref - mag_var,
				       nd.direction);

	  // calculate distance + time2go to hdg_ref[01]
	  nd.distance = sqrt( (hdg_ref[0]-x)*(hdg_ref[0]-x) +
			      (hdg_ref[1]-y)*(hdg_ref[1]-y) );
	  nd.time2go = nd.distance / co.data().y[Y_vtas];// seconds

	  nd.ils_loc_dev = 0.0;
	  nd.ils_gs_dev = 0.0;
	}

	break;
      }
      case NavData::LNAV : {
 	// calculate course_dev with lnav_ref[012]
	// TODO: check if we use course from FMS (lnav_ref[2]) or 
	// course from EFIS (nd.course_ref)
	nd.course_dev = getDeviation(x, y, lnav_ref[0], lnav_ref[1], nd.course_ref - mag_var,
				     nd.direction);

	// calculate distance + time2go to lnav_ref[01]
	nd.distance = sqrt( (lnav_ref[0]-x)*(lnav_ref[0]-x) +
			    (lnav_ref[1]-y)*(lnav_ref[1]-y) );
	nd.time2go = nd.distance / co.data().y[Y_vtas];// seconds
	
	// if loc mode armed, also calculate ils deviations
	if(nd.armed_lateral_mode == NavData::LOC) {
	  // calculate with ils_ref[012]
	  NavData::to_from dummy;
	  nd.ils_loc_dev = getDeviation(x, y, ils_ref[0], ils_ref[1], ils_ref[2] - mag_var,
					dummy);
	  // GS deviation
	  nd.ils_gs_dev = 3.0*DEG2RAD - atan2(co.data().y[Y_h], 
					      sqrt( (ils_ref[0]-x)*(ils_ref[0]-x) +
						    (ils_ref[1]-y)*(ils_ref[1]-y) ));
	  // capture localizer
	  if(fabs(nd.ils_loc_dev) < 2.0*DEG2RAD) { // TODO: check value
	    turnOffLateralModes(NavData::LOC, ts);
	    nd.lateral_mode = NavData::LOC;
	    nd.armed_lateral_mode = NavData::NONE;

	    // set the reference course, as specified in the STAR
	    // TODO: check if this is actually convenient
	    nd.course_ref = ils_ref[2];
	    mcpout_token->sendEvent(new MCP737Event(SYS_SIM, SYS_GUI | SYS_MCP,
						    (mcp_capt ? MCP737Event::MCP_COURSE1_SET : MCP737Event::MCP_COURSE2_SET), 
						    nearbyint(ils_ref[2]*RAD2DEG)), ts);
	  }
	}
	else {
	  nd.ils_loc_dev = 0.0;
	  nd.ils_gs_dev = 0.0;
	}
	
	break;
      }
      case NavData::LOC : {
 	// calculate course_dev with ils_ref[012]
	nd.course_dev = getDeviation(x, y, ils_ref[0], ils_ref[1], nd.course_ref - mag_var,
				     nd.direction);

	// calculate distance + time2go to ils_ref[01]
	nd.distance = sqrt( (ils_ref[0]-x)*(ils_ref[0]-x) +
			    (ils_ref[1]-y)*(ils_ref[1]-y) );
	nd.time2go = nd.distance / co.data().y[Y_vtas];// seconds

	// calculate ILS deviations
	NavData::to_from dummy;
	nd.ils_loc_dev = getDeviation(x, y, ils_ref[0], ils_ref[1], ils_ref[2] - mag_var,
				      dummy);
	// GS deviation
	nd.ils_gs_dev = 3.0*DEG2RAD - atan2(co.data().y[Y_h], 
					    sqrt( (ils_ref[0]-x)*(ils_ref[0]-x) +
						  (ils_ref[1]-y)*(ils_ref[1]-y) ));
	break;
      }
      default: {
	nd.course_dev = 0.0;
	nd.ils_loc_dev = 0.0;
	nd.ils_gs_dev = 0.0;
	nd.distance = 0.0;
	nd.time2go = 0.0;
	
	break;
      }
      }

      // handle pilot control transfers
      // TODO handle initialisation
      if(pcc_token) {
	StreamReader<PilotControlConfig> pcc(*pcc_token, ts);

	if(pcc.data().captain != prev_capt_ctrl_cfg) {
	  if(pcc.data().captain == PilotControlConfig::MASTER) {
	    // captain is in control
	    mcpout_token->sendEvent(new MCP737Event(SYS_SIM, SYS_GUI | SYS_MCP, 
						    MCP737Event::MCP_CWS_A_ON, 1.0), ts);	
	  } else {
	    // captain is not in control
	    mcpout_token->sendEvent(new MCP737Event(SYS_SIM, SYS_GUI | SYS_MCP, 
						    MCP737Event::MCP_CWS_A_OFF, -1.0), ts);	
	  }
	  
	  prev_capt_ctrl_cfg = pcc.data().captain;
	}
	
	if(pcc.data().first_officer != prev_fo_ctrl_cfg) {
	  if(pcc.data().first_officer == PilotControlConfig::MASTER) {
	    // first officer is in control
	    mcpout_token->sendEvent(new MCP737Event(SYS_SIM, SYS_GUI | SYS_MCP, 
						    MCP737Event::MCP_CWS_B_ON, 1.0), ts);	
	  } else {
	    // first officer is not in control
	    mcpout_token->sendEvent(new MCP737Event(SYS_SIM, SYS_GUI | SYS_MCP, 
						    MCP737Event::MCP_CWS_B_OFF, -1.0), ts);	
	  }
	  
	  prev_fo_ctrl_cfg = pcc.data().first_officer;
	}
      }
    }
    catch(Exception& e) {
      W_MOD(getId() << " caught " << e << " @ " << ts);
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
  StreamWriter<NavData> nav(nav_token, ts);

  // write the output into the output channel, using the stream writer
  // y.data().var1 = something; ...

  // copy our state to the output
  nav.data() = nd;
  nav.data().course_ref = DEG2RAD*nearbyint(nd.course_ref*RAD2DEG);
  nav.data().heading_ref = DEG2RAD*nearbyint(nd.heading_ref*RAD2DEG);



  if (snapshotNow()) {
    // keep a copy of the model state. Snapshot sending is done in the 
    // sendSnapshot routine, later, and possibly at lower priority
    // e.g. 
    // snapshot_state_variable1 = state_variable1; ...
    // (or maybe if your state is very large, there is a cleverer way ...)
  }
} 

void CitationNavigator::trimCalculation(const TimeSpec& ts, const TrimMode& mode)
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

void CitationNavigator:: turnOffLateralModes(NavData::efis_modes except,const TimeSpec& ts)
{
  if(except == nd.lateral_mode ) return;
  else {
    switch(nd.lateral_mode) {
    case NavData::HDG: {
      mcpout_token->sendEvent(new MCP737Event(SYS_SIM, SYS_MCP | SYS_GUI,
					      MCP737Event::MCP_HDG_OFF, -1.0), ts);
      break;
    }
    case NavData::LNAV: {
      mcpout_token->sendEvent(new MCP737Event(SYS_SIM, SYS_MCP | SYS_GUI,
					      MCP737Event::MCP_LNAV_OFF, -1.0), ts);
      break;
    }
    case NavData::LOC: {
      mcpout_token->sendEvent(new MCP737Event(SYS_SIM, SYS_MCP | SYS_GUI,
					      MCP737Event::MCP_APP_OFF, -1.0), ts);
      break;
    }
    default: {
      break;
    }
    }
  }  
  return;
}

void CitationNavigator::readStarFile(const vstring& name)
{
  ifstream in;
  //char *filename;
  //int namesize = strlen(name.c_str())+1+5;

  //filename = new char(namesize);
  //snprintf(filename, namesize, "%s.star", name.c_str());
  string filename = name + ".star";

  in.open(filename.c_str());

  if(in.good()) {
    in >> lnav_ref[0] >> lnav_ref[1] >> lnav_ref[2];
    in >> hdg_ref[0] >> hdg_ref[1] >> hdg_ref[2];
    in >> ils_ref[0] >> ils_ref[1] >> ils_ref[2];
  }
  
  D_MOD(getId() << " ref LNAV: " << lnav_ref[0] << ", " <<
	lnav_ref[1] << ", " << lnav_ref[2]);
  D_MOD(getId() << " ref HDG: " << hdg_ref[0] << ", " <<
	hdg_ref[1] << ", " << hdg_ref[2]);
  D_MOD(getId() << " ref LOC: " << ils_ref[0] << ", " <<
	ils_ref[1] << ", " << ils_ref[2]);

  //delete filename;
}

/* Calculating the angle between two objects, seen from object 1
   Axes are defined as:  X^
                          |
                          |                             
                          |-----> Y
*/
double CitationNavigator::getAngle(double x1, double y1, double x2, double y2)
{
  if (x1 == x2) {
    if (y1 > y2) {
      return 1.5*M_PI;
    }
    else {
      return 0.5*M_PI;
    }
  }
  else {
    double angle = atan2((y2-y1),(x2-x1));
    
    // Keep angle positive -> (0, 2*PI)
    if (angle < 0)
      angle = angle + 2*M_PI;
    
    return angle;
  }
}

double CitationNavigator::getDeviation(const double x1, const double y1, 
				       const double x2, const double y2,
				       const double hdg, NavData::to_from & dir)
{
  double angle = getAngle(x1, y1, x2, y2);

  double dev = angle - hdg;
  
  // Keep deviation between (-PI, 0) and (0, PI)
  if (dev > M_PI) {
    dev -= 2*M_PI;
  }
  
  // do to/from calculation
  if (dev < 0.5*M_PI && dev > -0.5*M_PI) {
    dir = NavData::TO;
  }
  else {
    dir = NavData::FROM;
    dev += M_PI;
    if (dev > M_PI) {
      dev -= 2*M_PI;
    }
    dev = -dev;
  }
  
  return dev;
}

// Make a TypeCreator object for this module, the TypeCreator
// will check in with the scheme-interpreting code, and enable the
// creation of modules of this type
static TypeCreator<CitationNavigator> a(CitationNavigator::getMyParameterTable());

