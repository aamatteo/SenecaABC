/* ------------------------------------------------------------------   */
/*      item            : B747PFD.cxx
        made by         : mamulder
	from template   : DusimeModuleTemplate.cxx
        template made by: Rene van Paassen
        date            : Wed Jan 24 11:19:18 2007
	category        : body file
        description     :
	changes         : Wed Jan 24 11:19:18 2007 first version
	template changes: 030401 RvP Added template creation comment
	                  060512 RvP Modified token checking code
        language        : C++
*/

static const char c_id[] =
"$Id: B747PFD.cxx,v 1.1.1.1 2022/02/17 15:04:23 matteopiras Exp $";

#define B747PFD_cxx
// include the definition of the module class
#include "B747PFD.hxx"

// include the debug writing header, by default, write warning and
// error messages
//#define D_MOD
#define I_MOD
#define W_MOD
#define E_MOD
#include <debug.h>

// include additional files needed for your calculation here
#include "pfd_frame.hxx"
#include <cmath>
#include <Ticker.hxx>

// the standard package for DUSIME, including template source
#define DO_INSTANTIATE
#include <dusime.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef DEG2RAD
#define DEG2RAD 1.7453291e-2
#endif

#ifndef RAD2DEG
#define RAD2DEG 57.295779513
#endif

#ifndef KTS2MPS
#define KTS2MPS 0.5144444
#endif

#ifndef FT2M
#define FT2M 0.3048
#endif

// class/module name
const char* const B747PFD::classname = "b747-pfd";

// initial condition/trim table
const IncoTable* B747PFD::getMyIncoTable()
{
  static IncoTable inco_table[] = {


    // always close off with:
    { NULL, NULL} };

  return inco_table;
}

// parameters to be inserted
const ParameterTable* B747PFD::getMyParameterTable()
{
  static const ParameterTable parameter_table[] = {
    { "set-timing",
      new MemberCall<B747PFD,TimeSpec>
        (&B747PFD::setTimeSpec), set_timing_description },

    { "check-timing",
      new MemberCall<B747PFD,vector<int> >
      (&B747PFD::checkTiming), check_timing_description },

    { "set-window-properties",
      new MemberCall<B747PFD,vector<int> >
      (&B747PFD::setWindowProperties) },

    { "set-heading-offset",
      new VarProbe<B747PFD, double>
      (REF_MEMBER(&B747PFD::mag_hdg_offset)),
      "set the offset between magnetic and true heading" },

    { "tau-indicated-airspeed",
      new VarProbe<B747PFD, double>
      (REF_MEMBER(&B747PFD::tau_ias)),
      "the dynamics of the airspeed indicator"},

 /*   { "citation-mode",
      new VarProbe<B747PFD, bool>
      (REF_MEMBER(&B747PFD::citation_mode)),
      "special mode for Citation"},
*/

    { "Lambda",
      new VarProbe<B747PFD, double >
      (&B747PFD::Lambda),
      "Forgetting functie voor stabiele slip"},

 // edits peter
    { "read-cv-channel",
      new MemberCall<B747PFD, bool>
      (&B747PFD::readCv),
      "Read from Vc_Channel"},

    { "slip-at-top",
      new VarProbe<B747PFD, bool >
      (&B747PFD::Slip_top),
      "Conventional slip indicator at the top, instead of centered"},

    { "slip-beta",
      new VarProbe<B747PFD, bool >
      (&B747PFD::Slip_beta),
      "Slip indication based on beta, instead of side force"},

    { "sustained-climb-angle",
      new VarProbe<B747PFD, bool >
      (&B747PFD::sustained_climb_angle),
      "Display sustained climb angle"},

    /* You can extend this table with labels and MemberCall or
       VarProbe pointers to perform calls or insert values into your
       class objects. Please also add a description (c-style string).

       Note that for efficiency, set_timing_description and
       check_timing_description are pointers to pre-defined strings,
       you can simply enter the descriptive strings in the table. */

    /* The table is closed off with NULL pointers for the variable
       name and MemberCall/VarProbe object. The description is used to
       give an overall description of the module. */
    { NULL, NULL, "draws B747-style PFD"} };

  return parameter_table;
}

// constructor
B747PFD::B747PFD(Entity* e, const char* part, const
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
  pfdWindow("Primary Flight Display", false),
  m_gs(new gs_loc_bar(105.1f, 77.5f, 90.0f, 0.7f, "gs_bar")), m_loc(new gs_loc_bar(69.0f, 41.4f, 0.0f, 2.5f, "loc_bar")),
  m_fm_anun(new fm_anunciations()),
  m_att_indicator(new attitude_indicator()),
  m_compass(new compass()),
  window_x(100),
  window_y(100),
  window_width(640),
  window_height(480),
  mag_hdg_offset(1.2),
  show_fd(false),
  threshold(false),
  reduce_left(false),
  reduce_right(false),
  num_ias(2), den_ias(2),
  tau_ias(1.0),
  in_ias(1), out_ias(1),
  dt(0.02),
 // citation_mode(false),
  // de floats van de referentie speeds
  flapAngleDeg(0.0),
  Vstall(1),
  Vman(1),
  V1(-100.0),
  V2(-120.0),
  FAS(-140.0),
  Sp_factor(0.0),
  Slip_top(true),
  Slip_beta(false),
  sustained_climb_angle(false),
  Slip(0.0),
  Climb(0.0),
  Database(5.0),
  // simulation state is HoldCurrent
  in_hold(true),
  // display event
  frozen_v(false),
  frozen_h(false),
  offset_v_value(0.0),
  offset_h_value(0.0),
  // display indication
  disp_v(0.0),
  disp_m(0.0),
  disp_h(0.0),
  disp_hdot(0.0),
  offset_v_set(0.0),
  offset_v_stepsize(0.0),
  offset_h_set(0.0),
  offset_h_stepsize(0.0),
  offset_v_nsteps(0),
  offset_h_nsteps(0),

  // initialize the data you need for the trim calculation

  // initialize the channel access tokens
  in_token(getId(), NameSet(getEntity(), "CitationOutput", part),101),
  nav_token(getId(), NameSet(getEntity(), "NavData", part),101),
  //mal_token(getId(), NameSet(getEntity(), "MalfunctionsChannel", part)),
  display_token(getId(), NameSet(getEntity(), "DisplayEvent", part)),
  display_feedback_token(getId(), NameSet(getEntity(), "DisplayEvent", "feedback")),
  //Vc_token(getId(), NameSet(getEntity(), "Vc_Channel", part),101),
  Vc_token(NULL),

/*
  mo_token(getId(), NameSet(getEntity(), "ModelOutput", part)),
  fds_token(getId(), NameSet(getEntity(), "FDSignal", part)),
  nd_token(getId(), NameSet(getEntity(), "NavData", part)),
  fms_ref_token(getId(), NameSet(getEntity(), "FMSReferenceData", part)),
  mcp_token(getId(), NameSet(getEntity(), "MCP737Event", part)),
  apm_token(getId(), NameSet(getEntity(), "APModes", part)),
*/

  // activity initialization
  cb1(this, &B747PFD::doCalculation),
  do_calc(getId(), "Display the primary flight display (PFD)", &cb1, ps)
{
  // do the actions you need for the simulation

  // connect the triggers for simulation
  do_calc.setTrigger(in_token && nav_token); // && Vc_token

  // connect the triggers for trim calculation. Leave this out if you
  // don not need input for trim calculation
  //trimCalculationCondition(/* fill in your trim triggering channels */);
}


bool B747PFD::complete()
{
  /* All your parameters have been set. You may do extended
     initialisation here. Return false if something is wrong. */
  gl2DObject* root = new pfd_frame();
  pfdWindow.set2DObjectRoot(root);
  // root->addChild(m_fm_anun);
  root->addChild(m_att_indicator);
  // m_att_indicator->addChild(m_gs);
  // m_att_indicator->addChild(m_loc);
  // root->addChild(m_compass);
  // m_compass->enableHeadingBug();

  pfdWindow.setWindow(window_x, window_y, window_width, window_height);
  pfdWindow.openWindow();
  pfdWindow.reshape(window_width, window_height);

  pfdWindow.disableAltBug();  // disableSpdBug
  pfdWindow.disableAltBug();  // disableAltBug

  // make the dynamic system for the airspeed indicator
  num_ias[0] = tau_ias; num_ias[1] = 0.0;
  den_ias[0] = tau_ias; den_ias[1] = 1.0;
  sys_ias = new LinearSystem(num_ias, den_ias, dt);

  return true;
}

// destructor
B747PFD::~B747PFD()
{
  //
}

// as an example, the setTimeSpec function
bool B747PFD::setTimeSpec(const TimeSpec& ts)
{
  // a time span of 0 is not acceptable
  if (ts.getValiditySpan() == 0) return false;

  // specify the timespec to the activity
  do_calc.setTimeSpec(ts);

  // do whatever else you need to process this in your model
  // hint: ts.getDtInSeconds()
  dt = ts.getDtInSeconds();

  // return true if everything is acceptable
  return true;
}

// and the checkTiming function
bool B747PFD::checkTiming(const vector<int>& i)
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

// and the setWindowProperties function
bool B747PFD::setWindowProperties(const vector<int>& i)
{
  if (i.size() == 2)
  {
    window_x = i[0];
    window_y = i[1];
  }
  else if (i.size() == 4)
  {
    window_x = i[0];
    window_y = i[1];
    window_width = i[2];
    window_height = i[3];
  }
  else
  {
    E_MOD(getId() << '/' << classname << ": error in set-window-properties. Useage: x, y, width, height");
    return false;
  }
  return true;
}

// Expect input from cv-calculation module over Vc_Channel channel. //TODO edits peter
bool B747PFD::readCv(const bool& b)
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

// tell DUECA you are prepared
bool B747PFD::isPrepared()
{
  bool res = true;

  CHECK_TOKEN(in_token);
  CHECK_TOKEN(nav_token);
  //CHECK_TOKEN(mal_token);
  CHECK_TOKEN(display_token);
  CHECK_TOKEN(display_feedback_token);
 // CHECK_TOKEN(mcp_token);

  //CHECK_TOKEN(Vc_token);
  if(Vc_token) CHECK_TOKEN(*Vc_token);

/*
  CHECK_TOKEN(mo_token);
  CHECK_TOKEN(fds_token);
  CHECK_TOKEN(nd_token);
  CHECK_TOKEN(fms_ref_token);
  CHECK_TOKEN(mcp_token);
  CHECK_TOKEN(apm_token);
*/
  // Example checking anything
  // CHECK_CONDITION(myfile.good());

  // return result of checks
  return res;
}

// start the module
void B747PFD::startModule(const TimeSpec &time)
{
  do_calc.switchOn(time);
}

// stop the module
void B747PFD::stopModule(const TimeSpec &time)
{
  do_calc.switchOff(time);
}

// this routine contains the main simulation process of your module. You
// should read the input channels here, and calculate and write the
// appropriate output
void B747PFD::doCalculation(const TimeSpec& ts)
{
  in_hold = false;

  // avoid overload
  if(do_calc.noScheduledBehind()) {
    W_MOD(classname << " behind @ " << ts);
    return;
  }

//MCP invoer uitzetten
/*
  if(mcp_token.getNumWaitingEvents(ts)) {
    try {
      EventReader<MCP737Event> mcp(mcp_token, ts);
      if(mcp.data().msg == MCP737Event::MCP_FD_L_ON) {
        m_att_indicator->showFD(true);
        show_fd = true;
      } else if (mcp.data().msg == MCP737Event::MCP_FD_L_OFF) {
        m_att_indicator->showFD(false);
        show_fd = false;
        m_fm_anun->clear(FD);
      } else if (mcp.data().msg == MCP737Event::MCP_ALT_SET) {
        pfdWindow.selectedAlt(mcp.data().data);
      } else if (mcp.data().msg == MCP737Event::MCP_SPD_SET) {
        pfdWindow.selectedTas(mcp.data().data);
      } else if (mcp.data().msg == MCP737Event::MCP_HDG_SET) {
        m_compass->selectedHeading(mcp.data().data);
      } else if (mcp.data().msg == MCP737Event::MCP_AT_ON) {
        m_fm_anun->engage(SPD);
      } else if (mcp.data().msg == MCP737Event::MCP_AT_OFF) {
        m_fm_anun->clear(SPD);
     }
    }
    catch(Exception& e) {
      W_MOD(classname << " caught " << e << " @ " << ts);
    }
  }
*/
// Voorlopig vastzetten van de mcp waarden op vaste waarden later wellicht via aparte interface
	m_att_indicator->showFD(false);
	show_fd = false;
	// m_fm_anun->clear(FD);
	//pfdWindow.selectedAlt(7000); // via navdata
	//pfdWindow.selectedTas(125);
	//m_compass->selectedHeading(360);
	// m_fm_anun->clear(SPD);

/*
  if (fms_ref_token.getNumWaitingEvents(ts)) {
    D_MOD(getId() << '/' << classname << ": Received FMSReferenceData event");
    try {
      EventReader<FMSReferenceData> in(fms_ref_token, ts);

	pfdWindow.updateReferenceData(in.data().selectedFlapAngle,
				      in.data().landingFlapAngle,
				      in.data().Vref, in.data().Vstall,
				      in.data().Vplackard, in.data().Vmaneuver,
				      in.data().V1, in.data().V2, in.data().FAS);

      D_MOD(classname << in.data());

    }
    catch (Exception &e) {
      E_MOD(getId() << '/' << classname << ": Unable to access received FMSReferenceData event: " << e);
    }
  }
*/

	while (display_token.getNumWaitingEvents(ts))
	{
		D_MOD(classname << ": Received DisplayEvent");
		try
		{
			EventReader<DisplayEvent> d(display_token, ts);

			//indicated altitude comes from: y[Y_h]  m (conv. to ft)   --> disp_h
			// also note y[Y_hdot]
			//indicated speed comes from: Y_vtas  m/s (conv. to kts)   --> disp_v
			// also include the mach number: disp_m from in.data().y[Y_m] (for now only included for frozen display)

			// ALTITUDE INDICATION
			frozen_h       = d.data().frozen_h;
			offset_h_value = d.data().offset_h_value;
			// update if reference != current
			if ( abs(offset_h_value - offset_h_set) > 0.001) {
				//number of steps to make
				offset_h_nsteps = d.data().offset_h_time / dt;
				// at least one step
				if (offset_h_nsteps <= 0) offset_h_nsteps = 1;
				//size of each step
				offset_h_stepsize = (offset_h_value - offset_h_set) / offset_h_nsteps;
			}

			// VELOCITY INDICATION
			frozen_v       = d.data().frozen_v;
			offset_v_value = d.data().offset_v_value;
			// update if reference != current
			if ( abs(offset_v_value - offset_v_set) > 0.001) {
				//number of steps to make
				offset_v_nsteps = d.data().offset_v_time / dt;
				// at least one step
				if (offset_v_nsteps <= 0) offset_v_nsteps = 1;
				//size of each step
				offset_v_stepsize = (offset_v_value - offset_v_set) / offset_v_nsteps;
			}
		}
		catch (Exception& e)
		{
			W_MOD(classname << ": Error while reading DisplayEvent @ " << ts);
		}
	}


  // check the state we are supposed to be in
  switch (getAndCheckState(ts)) {
    case SimulationState::HoldCurrent:
      in_hold = true;

      // is this fall-through intentional???
    case SimulationState::Replay:
    case SimulationState::Advance: {


/*
	if (mal_token.getNumWaitingEvents(ts))
	{
		// read from MalfunctionsChannel
		try
		{
			EventReader<MalfunctionsChannel> mal(mal_token, ts);

			if (Slip_top != mal.data().Slip_top){
				Slip_top=mal.data().Slip_top;
				I_MOD(classname << ": Slip indication location set to: "<< Slip_top );
			}
			if (Slip_beta != mal.data().Slip_beta){
				Slip_beta=mal.data().Slip_beta;
				I_MOD(classname << ": Slip beta set to: "<< Slip_beta << " with Lambda="<< Lambda );
			}
			if (mal.data().database < 3){
				sustained_climb_angle=true;
				I_MOD(classname << ": showing sustained_climb_angle");
			}else{
				sustained_climb_angle=false;
			}
		}
		catch (Exception& e)
		{
			W_MOD(classname << ": Error while reading MalfunctionsChannel @ " << ts);
		}
	}
*/

	if(Vc_token) {
		// read from Vc_Channel + output to display
		try
		{
			StreamReader<Vc_Channel> Vc(*Vc_token, ts);

			threshold    = Vc.data().Threshold;
			reduce_left  = Vc.data().Reduce_left;
			reduce_right = Vc.data().Reduce_right;
			V1          = Vc.data().Vc_1 * KTS2MPS * Sp_factor;
			V2          = Vc.data().Vc_2 * KTS2MPS * Sp_factor;

			pfdWindow.selectedAlt(Vc.data().Threshold_param);

			// if (threshold){
			// 	m_fm_anun->engage(MANEUVER);
			// }else{
			// 	m_fm_anun->clear(MANEUVER);
			// }

			// if (Vc.data().Reduce_left){
			// 	m_fm_anun->engage(RED_L);
			// }else{
			// 	m_fm_anun->clear(RED_L);
			// }
      //
			// if (Vc.data().Reduce_right){
			// 	m_fm_anun->engage(RED_R);
			// }else{
			// 	m_fm_anun->clear(RED_R);
			// }
		}
		catch(Exception &e)
		{
			W_MOD(getId()<< classname << " caught " << e << " @ " << ts << " -- reading Vc_Channel");
		}
	}

	// read from CitationOutput + output to display
	try
	{
		StreamReader<CitationOutput> in(in_token, ts);

        // determine which speed set we'll use
        // TODO get this from FMS
      //   if (in_hold) {   //getCurrentState() == SimulationState::HoldCurrent) {
			// pfdWindow.setSpeedsSet(0);// light
      //   }


		if (offset_h_nsteps > 0 || offset_v_nsteps > 0)
		{
			// ALTITUDE: change indicator offset
			if (offset_h_nsteps > 0) {
				offset_h_set += offset_h_stepsize;
				offset_h_nsteps--;

				//D_MOD(classname << ": altitude indicator offset = " << offset_h_set << "  real="<< in.data().y[Y_h]/FT2M);

				// just to be sure
				if (offset_h_nsteps == 0) offset_h_set = offset_h_value;
			}

			// SPEED: change indicator offset
			if (offset_v_nsteps > 0) {
				offset_v_set += offset_v_stepsize;
				offset_v_nsteps--;

				//D_MOD(classname << ": velocity indicator offset = " << offset_v_set << "  real="<< in.data().y[Y_vtas]/KTS2MPS);

				// just to be sure
				if (offset_v_nsteps == 0) offset_v_set = offset_v_value;
			}

			// send current values for logging
			EventWriter<DisplayEvent> d(display_feedback_token,ts);
			d.data().offset_h_value = offset_h_set;
			d.data().offset_v_value = offset_v_set;
		}


		// Indicated altitude: only update if display is not frozen
		if (!frozen_h) {
			// incoming speed in meters
			// add offset value
			disp_h = in.data().y[Y_h]/FT2M + offset_h_set;
			// incoming climb "speed" in meters (per second?)
			disp_hdot = in.data().y[Y_hdot]/FT2M*60.0;

			// if offset is moving in, also change climb speed needle
			if (offset_h_nsteps > 0) disp_hdot += offset_h_stepsize/dt*10.0;
		}

		// Indicated airspeed: only update if display is not frozen
		if (!frozen_v) {
			// incoming speed in m/s
			// add offset value
      // const double rho      = 1.225*exp(-alt/9296.0);
      // const double rho_frac = sqrt(1.225/1.225*exp(-disp_h/9296.0));
      //
      // return vtas / rho_frac;

			disp_v = (in.data().y[Y_vtas]/sqrt(1.0/(exp(-in.data().y[Y_h]/9296.0))))/KTS2MPS + offset_v_set;
			disp_m = in.data().y[Y_m];

			// no negative speeds
			if (disp_v < 0) disp_v = 0.1f;
		}


        // filter the CAS/IAS
        // in_ias[0] = value going into LinearSystem
        // out_ias[0] = (output from LinearSystem) going to display
        in_ias[0] = disp_v;
        // depends on simstate
        if(in_hold) {
          out_ias[0] = disp_v;
          in_ias[0] /= tau_ias; // state is not what we think it is?
          sys_ias->acceptState(in_ias);
        }
        else {
          out_ias = sys_ias->step(in_ias);
        }

        // debug: show unfiltered ias as speed bug
        //pfdWindow.selectedTas(in_ias[0]);

		// set speed [knots], Mach, climb speed (?), altitude [ft]
		pfdWindow.setAircraftState( out_ias[0], disp_m, disp_hdot, disp_h );

        // update time in PFD, for speed trend
        pfdWindow.setCurrentTime(ts.getValidityStart()*Ticker::single()->getTimeGranule());

		// attitude
        m_att_indicator->setAttitude(in.data().y[Y_theta], in.data().y[Y_phi]);


		//  bereken sustained climb angle (theta!)
		if (sustained_climb_angle){
			Climb = in.data().y[Y_alpha] + asin(in.data().y[Y_hdot] / in.data().y[Y_vtas] + in.data().y[Y_vtasdot]/9.80);}
		else{
			Climb = -100.0;
		}

		// slip indicator
		if(Slip_beta){
			// use Y_beta
			Slip = (1-Lambda)*Slip + Lambda * in.data().y[Y_beta];
			m_att_indicator->setSideSlip(Slip, Slip_top, Slip_beta, Climb);
		}
		else{
			// use Y_fycg
			Slip = (1-Lambda)*Slip + Lambda * in.data().y[Y_fycg]*-0.1;
			m_att_indicator->setSideSlip(Slip, Slip_top, Slip_beta, Climb);
		}

		// Speed correctie factor uitrekenen: Van TAS naar KEAS
		Sp_factor = pow( (1 - in.data().y[Y_h]/FT2M*6.87559/1000000.0), 2.12805);
		// NU van TAS naar EAS

		 // Flap angle in degrees
		flapAngleDeg = in.data().y[Y_df0] * RAD2DEG;

		// Maneuver speed (manual section 2.3)
		if (flapAngleDeg > 0.1) { Vman = 115.0f*KTS2MPS; } // max flap speed = 115 KIAS
		else                    { Vman = 135.0f*KTS2MPS; } // Va, design maneuvering speed: given as 135 KIAS in section 2.3

		// Stall speed
		Vstall = 32.4f - in.data().y[Y_df0]*3;

		/*
		// De limiet speed in de stripe display is het minimum van (Vstall, V1)
		//if(Vstall>V1){ FAS = Vstall; }
		//else         { FAS = V1; }
		FAS = ( Vstall>V1 ? Vstall : V1 );
		*/

		// TAS
	 	//pfdWindow.selectedTas(V2/KTS2MPS);

	 	// ALL SPEEDS IN M/S !!
		// 1 m/s = 1.94384 knots
		// 1 knots = 0.514444 m/s

	 	// Speed limits
	 	// indicator markings are listed in the manual section 2.5
	 	// at Vman on the speedtape the flap position is given
		pfdWindow.updateReferenceData(flapAngleDeg,   // selectedFlapAngle
		                              25,             // landingFlapAngle
		                              0,              // Vref
		                              Vstall,         //
		                              205.0f*KTS2MPS, // Vne = 205 KIAS  (Vplackard)
		                              Vman,           // Vmaneuver
		                              V1,             //
		                              V2,             //
		                              FAS);           // nothing is done with this variable? FAS

		// compass heading
        // m_compass->currentHeading(in.data().y[Y_psi]/DEG2RAD + mag_hdg_offset);
        // m_compass->trackAngle(( in.data().y[Y_psi]+in.data().y[Y_beta] )/DEG2RAD);// TODO should be track, not heading // Added DEG2RAD conversion
	}
	catch(Exception &e)
	{
		W_MOD(getId()<< classname << " caught " << e << " @ " << ts << " while reading CitationOutput or NavData");
	}


	// read from NavData + output to display
	try
	{
		StreamReader<NavData> nav(nav_token, ts);

		// test: link between MCP and PFD
		// setting the bugs for altitude, speed and heading reference
		pfdWindow.selectedAlt(nav.data().alt_ref);
		pfdWindow.selectedTas(nav.data().speed_ref);
		// m_compass->selectedHeading(nav.data().heading_ref*RAD2DEG);


// FD uitschakelen
/*
       if(fds.data().active) {
          m_att_indicator->setFDBarsDeg(-1.0*fds.data().pitch, fds.data().roll); // TODO tune gain
          //m_att_indicator->setFDBarsDeg(fds.data().pitch-mo.data().data[Y_theta]/DEG2RAD,
          //fds.data().roll-0.0*mo.data().data[Y_phi]/DEG2RAD);
          m_fm_anun->clear(CMD);
          if(show_fd)
            m_fm_anun->engage(FD);
        } else {
          m_att_indicator->setFDBarsDeg(0.0, 0.0);
          m_fm_anun->clear(FD);
          m_fm_anun->engage(CMD);
        }
*/

		// Nulwaarde invoeren voor flight director
        m_att_indicator->setFDBarsDeg(0.0, 0.0);
        // m_fm_anun->clear(FD);
        //m_fm_anun->engage(CMD);

        // m_loc->angle(nav.data().ils_loc_dev);
        // m_gs->angle(nav.data().ils_gs_dev );
		pfdWindow.setILS(nav.data().distance/1852);

        // mode annunciators
        //m_fm_anun->engage(LNAV);
        //m_fm_anun->engage(VNAV_PTH);

        // A/T now turned on/off with MCP switch
        // m_fm_anun->engage(SPD);


		//	cout<< "Nav data loc" << nav.data().ils_loc_dev << " gs=" << nav.data().ils_gs_dev << endl;


		// Autopilot anuciator uitzetten en alleen clear commando
		//      de nieuwe anuciator commands
		// m_fm_anun->clear(GS);


// Tot hier gekomen; DE STANDAARD FLIGHTDIRECTOR SETTING, wellicht aan //TODO
/*
        // pitch
        if(apm.data().pitch_is_vnav) {
          m_fm_anun->engage(VNAV_PTH);
        } else if(apm.data().pitch_mode == 1 || apm.data().pitch_mode == 2) {
          m_fm_anun->engage(ALT);
        } else if(apm.data().pitch_mode == 3) {
          m_fm_anun->engage(VS);
	  m_fm_anun->arm(ALT); // automatically arm ALT mode with VS
        } else if(apm.data().pitch_mode == 4) {
          m_fm_anun->engage(FLCH_SPD);
	  m_fm_anun->arm(ALT); // automatically arm ALT mode with IAS
        } else if(apm.data().pitch_mode == 6) {
          m_fm_anun->engage(GS);
        }
        if(apm.data().pitch_mode != 6) {
          if(apm.data().app_armed) {
            m_fm_anun->arm(GS);
          } else {
            m_fm_anun->clear(GS);
          }
        }

        // roll
        if(apm.data().roll_mode == 2) {
          m_fm_anun->engage(HDG_SEL);
        } else if(apm.data().roll_mode == 3) {
          m_fm_anun->engage(LOC);
        } else if(apm.data().roll_mode == 4 || apm.data().roll_mode == 5) {
          m_fm_anun->engage(LNAV);
        }
        if(apm.data().roll_mode != 3) {
          if(apm.data().app_armed) {
            m_fm_anun->arm(LOC);
          } else {
            m_fm_anun->clear(LOC);
          }
        }
*/

	}
	catch(Exception &e)
	{
		W_MOD(getId()<< classname << " caught " << e << " @ " << ts << " while reading NavData");
	}


      // do the simulation calculations, one step
      m_fm_anun->update(float(ts.getDtInSeconds())); // update timer for highlight boxes
      pfdWindow.redraw();

      break;
      }
    default:
      // other states should never be entered for a SimulationModule,
      // HardwareModules on the other hand have more states. Throw an
      // exception if we get here,
      throw CannotHandleState(getId(),GlobalId(), "state unhandled");
  }
}

/*
void B747PFD::set_anunciation(int flag, int state)
{
  switch (state)
  {
    case APIndications::OFF:
      m_fm_anun->clear(flag);
      break;
    case APIndications::ARMED:
      m_fm_anun->arm(flag);
      break;
    case APIndications::ENGAGED:
      m_fm_anun->engage(flag);
      break;
  }
}
*/

void B747PFD::trimCalculation(const TimeSpec& ts, const TrimMode& mode)
{
}

// Make a TypeCreator object for this module, the TypeCreator
// will check in with the scheme-interpreting code, and enable the
// creation of modules of this type
static TypeCreator<B747PFD> a(B747PFD::getMyParameterTable());
