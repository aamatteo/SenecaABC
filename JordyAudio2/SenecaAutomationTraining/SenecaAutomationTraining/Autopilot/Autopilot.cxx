/* ------------------------------------------------------------------   */
/*      item            : Autopilot.cxx
        made by         : jordy
	      from template   : DusimeModuleTemplate.cxx
        template made by: Rene van Paassen
        date            : Sun Mar 22 10:58:09 2020
	category        : body file
        description     :
	changes         : Sun Mar 22 10:58:09 2020 first version
	template changes: 030401 RvP Added template creation comment
	                  060512 RvP Modified token checking code
			  131224 RvP convert snap.data_size to
			         snap.getDataSize()
        language        : C++
        copyright       : (c) 2016 TUDelft-AE-C&S
*/


#define Autopilot_cxx
// include the definition of the module class
#include "Autopilot.hxx"
#include <algorithm>
#include <GlobalConstants.hpp>
#include <vector>
#include <fstream>



// include the debug writing header. Warning and error messages
// are on by default, debug and info can be selected by
// uncommenting the respective defines
#define D_MOD
#define I_MOD
#define W_MOD
#include <debug.h>

// include additional files needed for your calculation here

// the standard package for DUSIME, including template source
#define DO_INSTANTIATE
#include <dusime.h>

#ifndef DEG2RAD
#define DEG2RAD 1.7453291e-2
#endif

#ifndef RAD2DEG
#define RAD2DEG 57.295779513
#endif

#ifndef FT2M
#define FT2M 0.3048
#endif

#ifndef MIN2S
#define MIN2S 0.0167
#endif

#ifndef KTS2MS
#define KTS2MS 0.5144
#endif


// class/module name
const char* const Autopilot::classname = "autopilot";

// initial condition/trim table
const IncoTable* Autopilot::getMyIncoTable()
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
const ParameterTable* Autopilot::getMyParameterTable()
{
  static const ParameterTable parameter_table[] = {
    { "set-timing",
      new MemberCall<_ThisModule_,TimeSpec>
        (&_ThisModule_::setTimeSpec), set_timing_description },

    { "check-timing",
      new MemberCall<_ThisModule_,vector<int> >
      (&_ThisModule_::checkTiming), check_timing_description },

    { "use-column",
      new VarProbe<Autopilot, bool>
      REF_MEMBER(&Autopilot::use_column), "is using column"},

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
Autopilot::Autopilot(Entity* e, const char* part, const
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


  STMvertical(7,5),
  STMlateral(4,3),
  pos(2,1),
  start(2,1),
  finish(2,1),

  vnv_start(0,0),
  vnv_finish(0,0),
  vnv_next_wp(0,0),

  APstate(0),
  ap_disengaged(false),
  ap_on(false),
  fd_on(false),

  t(0),
  de(0),
  da(0),
  dr(0),

  theta(0),
  theta_ref(0),
  theta_old(0),
  theta_error(0),
  theta_roll_addendum(0),
  q(0),
  q_ref(0),
  q_old(0),
  q_error(0),
  q_int(0),
  theta_ref_loop(0),
  theta_ref_old(0),
  theta_ref_command(0),
  theta_ref_pit(0),

  phi(0),
  phi_old(0),
  phi_ref(0),
  phi_error(0),
  p(0),
  p_ref(0),
  p_old(0),
  p_error(0),
  p_int(0),
  phi_ref_loop(0),
  phi_ref_old(0),
  phi_ref_command(0),
  phi_ref_rol(0),

  beta(0),
  beta_error(0),
  r(0),
  r_ref(0),
  r_error(0),

  Vtas(0),
  VtasSBY(0),
  alpha(0),
  VSref(0),
  VS(0),
  VS_roll_addendum(0),
  phi_abs(0),

  alt(0),
  alt_ref(0),
  alt_old(0),
  alt_error(0),

  V_ref(0),
  V_error(0),
  V_old(0),

  hdg(0),
  hdg_error_old(0),
  hdg_error(0),
  hdg_select_old(0),
  hdg_int(0),

  msg(GFC700Event::GFC700_NONE),
  curStateVertical(0),
  prevStateVertical(0),
  curStateLateral(0),
  prevStateLateral(0),
  alt_select_input(0),
  alt_select(0),
  hdg_select(0),
  Vswitched(false),
  Lswitched(false),
  changed_to_alt_captured(false),
  need_update(false),
  reset_hdg(false),

  ap_flash_timer(0),
  pit_flash_timer(0),
  rol_flash_timer(0),
  ap_flash(false),
  pit_flash(false),
  rol_flash(false),

  x(0),
  y(0),
  nav_d(0),
  nav_R(0),
  nav_beta(0),
  nav_direct(0),
  nav_total_radial(0),
  nav_extension(0),
  nav_p3x(0),
  nav_p3y(0),
  nav_alpha(0),
  hdg_ref(0),
  hdg_ref_old(0),
  dtk(0),

  active_nav_source(0),
  nav_alpha_true(0),
  needle_deviation(0),
  dist_to_top(0),
  iter_wps(0),
  distance_to_next_vnv(0),
  time_to_bod(0),
  switch_to_vpth(false),
  alt_v_until_switch(0),

  de_old(0),
  crs_select(0),
  active_leg(0),
  active_vnv_leg(0),
  gps_dist(0),
  update_hsi(false),

  dx(0),
  alt_v(0),
  vnav_situation(0),

  theta_at_switch(0),
  VS_at_switch(0),

  alts_flash_state(0),
  alt_flash_state(0),
  alts_flash_timer(0),
  alt_flash_timer(0),

  timer(0),

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
  prev_PFD_failure(false),

  prev_clogged_pt(false),
  pressure_1(0),
  pressure_2(0),
  pressure_3(0),
  pressure_4(0),
  q1(0),
  dp(0),

  prev_GPS_failure(false),
  frozen_x(0),
  frozen_y(0),
  frozen_vs(0),

  prev_clogged_sp(false),
  frozen_altitude(0),

  ude(0),
  ude_old(0),
  uda(0),
  uda_old(0),
  da_old(0),
  Tservo(0.4),

  fp_filename(""),
  fp_prev_file_name("none"),
  fp_comment(""),
  nr_of_wp(0),
  fp_location(1,3),
  wp_names(),
  fp_wp(""),
  fp_lat(0),
  fp_lon(0),
  fp_alt(0),
  dummy_string(""),
  nav_dtk(0),
  delta_x(0),
  delta_y(0),

  vor1_x(0),
  vor1_y(0),
  vor2_x(0),
  vor2_y(0),
  use_vor1(0),
  use_vor2(0),

  curveRadius(0),

  prev_nav_R(0),
  vor_flag_state(true),
  prev_vor_flag_state(true),

  needleOffset(0),
  prevNeedleOffset(0),
  HSItimeConstant(0.8),
  prevCourse(0),
  prev_nav_source(0),
  switchToVor(false),
  prev_crs_select(0),

  fpa_req(0),
  phi_rate1(0),

  // initialize the channel access tokens, check the documentation for the
  in_token(getId(), NameSet(getEntity(), "CitationOutput", part),101),
  ap_token(getId(), NameSet(getEntity(), "AutopilotChannel", part),101),
  gfcr_token(getId(), NameSet(getEntity(), "GFC700Event", ""), ChannelDistribution::JOIN_MASTER),
  fail_token(getId(), NameSet(getEntity(), "FailureEvent", ""), ChannelDistribution::JOIN_MASTER),
  apinco_token(getId(), NameSet(getEntity(), "APIncoEvent", ""), ChannelDistribution::JOIN_MASTER),
  ap2g_token(getId(), NameSet(getEntity(), "AP2G1000Channel", ""), ChannelDistribution::JOIN_MASTER),

  ps_token(NULL),
  // activity initialization
  myclock(),
  cb1(this, &_ThisModule_::doCalculation),
  do_calc(getId(), "", &cb1, ps)

{
  // do the actions you need for the simulation
  // connect the triggers for simulation
  do_calc.setTrigger( in_token );

}

bool Autopilot::complete()
{
  /* All your parameters have been set. You may do extended
     initialisation here. Return false if something is wrong. */
     if(use_column){
       ps_token = new StreamChannelReadToken<PrimarySwitches>(getId(), NameSet(getEntity(), "PrimarySwitches", "column"),101);
     } else{
       ps_token = new StreamChannelReadToken<PrimarySwitches>(getId(), NameSet(getEntity(), "PrimarySwitches", ""),101);
     }
  return true;
}

// destructor
Autopilot::~Autopilot()
{
  delete ps_token;
  //
}

// as an example, the setTimeSpec function
bool Autopilot::setTimeSpec(const TimeSpec& ts)
{
  // a time span of 0 is not acceptable
  if (ts.getValiditySpan() == 0) return false;

  // specify the timespec to the activity
  do_calc.setTimeSpec(ts);

  // return true if everything is acceptable
  return true;
}

// and the checkTiming function
bool Autopilot::checkTiming(const vector<int>& i)
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
bool Autopilot::isPrepared()
{
  bool res = true;

  // Checking tokens:
  CHECK_TOKEN(in_token);
  CHECK_TOKEN(ap_token);
  CHECK_TOKEN(gfcr_token);
  CHECK_TOKEN(fail_token);
  CHECK_TOKEN(apinco_token);
  CHECK_TOKEN(ap2g_token);
  CHECK_TOKEN(*ps_token);

  // return result of checks
  return res;
}

// start the module
void Autopilot::startModule(const TimeSpec &time)
{
  do_calc.switchOn(time);
}

// stop the module
void Autopilot::stopModule(const TimeSpec &time)
{
  do_calc.switchOff(time);
}

// fill a snapshot with state data. You may remove this method (and the
// declaration) if you specified to the SimulationModule that the size of
// state snapshots is zero
void Autopilot::fillSnapshot(const TimeSpec& ts,
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
void Autopilot::loadSnapshot(const TimeSpec& t, const Snapshot& snap)
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
void Autopilot::doCalculation(const TimeSpec& ts)
{
  // check the state we are supposed to be in
  switch (getAndCheckState(ts)) {
  case SimulationState::HoldCurrent: {
    // only repeat the output, do not change the model state
    if (gfcr_token.getNumWaitingEvents(ts))
    {
      try
      {
        EventReader<GFC700Event> gfc(gfcr_token, ts);
        msg = gfc.data().msg;
        crs_select = round(gfc.data().crs_select);
        alt_select_input = round(gfc.data().alt_select);
        hdg_select = round(gfc.data().hdg_select);
        if(alt_select_input !=0){
          alt_select = alt_select_input;
        }
        // CDI button pressed
        if(msg==12){
          active_nav_source = active_nav_source + 1;
          if(active_nav_source > 2){
            active_nav_source = 0;
          }
          if(curStateLateral == 3){
            curStateLateral = 1;
            Lswitched = true;
          }
          if(curStateVertical == 4){
            curStateVertical = 1;
            Vswitched = true;
          }
        }

        need_update = true;
      }
      catch (Exception& e)
      {
        W_MOD(classname << ": Error while reading GFC700Event!");
      }
    }

    try
    {
      StreamReader<CitationOutput> in(in_token, ts);
      V_old = Vtas;
      alt_old = alt;
      p_old = p;
      q_old = q;
      phi_old = phi;
      theta_old = theta;

      x = in.data().y[Y_y];
      y = in.data().y[Y_x];
      alt = in.data().y[Y_h];

      Vtas = in.data().y[Y_vtas];
      VtasSBY = in.data().y[Y_vtas];
      VS = in.data().y[Y_hdot];
      hdg = in.data().y[Y_psi] * RAD2DEG;
      hdg = (static_cast<int>(hdg) % 360 + 360) %360;

      phi = in.data().y[Y_phi];
      theta = in.data().y[Y_theta];

      p = in.data().y[Y_p];
      q = in.data().y[Y_q];
      r = in.data().y[Y_r];

      alpha = in.data().y[Y_alpha];
      beta = in.data().y[Y_beta];
    }
    catch(Exception& e)
    {
      W_MOD(getId()<< classname << " caught " << e << " @ " << ts <<
                      " -- reading CitationOutput Channel");
    }

    if(apinco_token.getNumWaitingEvents(ts))
    {
      try
      {
        EventReader<APIncoEvent> apinco(apinco_token, ts);
        APstate = apinco.data().APstate;
        curStateLateral = apinco.data().lateralFDstate;
        curStateVertical = apinco.data().verticalFDstate;
        active_nav_source = apinco.data().active_nav_source;
        fp_filename = apinco.data().fp_name;

        ap_flash = false;
        rol_flash = 0;
        pit_flash = 0;
        active_leg = 0;
        active_vnv_leg = 0;
        vnav_situation = 0;
        phi_ref = 0;
        phi_ref_old = 0;
        phi_ref_loop = 0;
        phi_ref_command = 0;

        // Resetting some values with new inco
        theta_ref = 0;
        theta_ref_old = 0;
        theta_ref_pit = 0;
        q_int = 0;
        ude_old = 0;
        de_old = 0;

        p_int = 0;
        hdg_int = 0;
        phi_ref = 0;
        phi_ref_old = 0;
        phi_ref_loop = 0;
        phi_ref_command = 0;
        phi_ref_rol = 0;
        da_old = 0;
        uda_old = 0;

        AFCS_pit = false;
        AFCS_rol = false;

        need_update = true;

      }
      catch(Exception& e)
      {
        W_MOD(classname << " caught " << e << " @ "<<ts<< " (reading AP Inco)");
      }
    }

    if(fp_filename != fp_prev_file_name && fp_filename.length()>0){
      std::ifstream myfile (fp_filename);

      myfile >> fp_comment >> dummy_string >> dummy_string;
      myfile >> fp_comment >> dummy_string;
      myfile >> fp_comment >> dummy_string >> dummy_string;
      myfile >> fp_comment >> dummy_string;

      myfile >> fp_comment >> use_vor1 >> use_vor2;
      myfile >> fp_comment >> vor1_x >> vor1_y;
      myfile >> fp_comment >> vor2_x >> vor2_y;

      myfile >> fp_comment >> nr_of_wp;
      fp_location.resize(nr_of_wp, 5);
      wp_names.clear();
      for(int i=0; i<nr_of_wp; i++){
        myfile >> fp_wp >> fp_lat >> fp_lon >> fp_alt;
        wp_names.push_back(fp_wp);
        fp_location(i,0) = fp_lat;
        fp_location(i,1) = fp_lon;
        fp_location(i,2) = fp_alt;
      }
      if(nr_of_wp>0){
        fp_location(0,3) = 0;
        fp_location(0,4) = 0;
      }
      for(int i=1; i<nr_of_wp; i++){
        delta_x = fp_location(i,0)-fp_location(i-1,0);
        delta_y = fp_location(i,1)-fp_location(i-1,1);
        nav_dtk = RAD2DEG * (atan2(delta_x, delta_y));
        if(nav_dtk<0){
          nav_dtk +=360;
        }
        fp_location(i,3) = nav_dtk;
        fp_location(i,4) = sqrt(delta_x*delta_x+delta_y*delta_y);
      }
      myfile.close();

      need_update = true;
    }
    fp_prev_file_name = fp_filename;


    pos = {x, y};
    switch (active_nav_source){
      case 0: // GPS
        vor_flag_state = true;
        // GPS failure
        if(GPS_failure && prev_GPS_failure == false){
          frozen_x = x;
          frozen_y = y;
        }
        if(GPS_failure){
          pos = {frozen_x, frozen_y};
        }
        prev_GPS_failure = GPS_failure;


        if(nr_of_wp>0 && active_leg+1<nr_of_wp){
          start = {fp_location(active_leg, 0), fp_location(active_leg, 1)};
          finish = {fp_location(active_leg+1, 0), fp_location(active_leg+1, 1)};

          float turnradius = 1.2*Vtas*Vtas/(9.81*0.364);
          Eigen::Vector2d next_wp;

          if(active_leg+2<nr_of_wp){
            next_wp = {fp_location(active_leg+2, 0), fp_location(active_leg+2, 1)};
            curveRadius = Autopilot::getCurveRadius(start, finish, next_wp, turnradius);
          }else{
            curveRadius = 0.0;
          }

          if( (pos-finish).norm() < max(curveRadius, 200.0f) && active_leg < nr_of_wp-2)
          {
            active_leg = active_leg+1;
            need_update = true;
          }


          if(active_vnv_leg+2<nr_of_wp){
            vnv_start = {fp_location(active_vnv_leg,0), fp_location(active_vnv_leg,1)};
            vnv_finish = {fp_location(active_vnv_leg+1,0), fp_location(active_vnv_leg+1,1)};
            vnv_next_wp = {fp_location(active_vnv_leg+2,0), fp_location(active_vnv_leg+2,1)};

            float abc = getAngle(vnv_start, vnv_finish, vnv_next_wp);
            if(abc>180){
              abc = 360 - abc;
            }

            Eigen::Vector2d end_of_curve = getMid(vnv_next_wp, vnv_finish, abc, turnradius);

            if( (pos-end_of_curve).norm() < 200 )
            {
              active_vnv_leg = active_vnv_leg+1;
              need_update = true;
            }
            if(active_vnv_leg+2<nr_of_wp){
              vnv_start = {fp_location(active_vnv_leg,0), fp_location(active_vnv_leg,1)};
              vnv_finish = {fp_location(active_vnv_leg+1,0), fp_location(active_vnv_leg+1,1)};
              vnv_next_wp = {fp_location(active_vnv_leg+2,0), fp_location(active_vnv_leg+2,1)};
            }
          }


          start = {fp_location(active_leg, 0), fp_location(active_leg, 1)};
          finish = {fp_location(active_leg+1, 0), fp_location(active_leg+1, 1)};

        }else{
          start = {0.0, 0.0};
          finish = {0.0, 0.0};
        }

        break;

      case 1: // NAV Radio 1
        if(use_vor1){

          if((pos[0]-vor1_x)*sin(crs_select*DEG2RAD) + (pos[1]-vor1_y)*cos(crs_select*DEG2RAD) <0){
            // to
            vor_flag_state=true;
            finish = {vor1_x, vor1_y};
            start = {finish[0]+100000*sin(DEG2RAD*(crs_select-180)),
                      finish[1]+100000*cos(DEG2RAD*(crs_select-180))};
          }else{
            // from
            vor_flag_state=false;
            start = {vor1_x, vor1_y};
            finish = {start[0]-100000*sin(DEG2RAD*(crs_select-180)),
                      start[1]-100000*cos(DEG2RAD*(crs_select-180))};
          }
        }else{
          start = {0.0, 0.0};
          finish = {0.0, 0.0};
        }
        break;

      case 2: // NAV Radio 2
        if(use_vor2){
          if((pos[0]-vor2_x)*sin(crs_select*DEG2RAD) + (pos[1]-vor2_y)*cos(crs_select*DEG2RAD) <0){
            vor_flag_state=true;
            finish = {vor2_x, vor2_y};
            start = {finish[0]+100000*sin(DEG2RAD*(crs_select-180)),
                      finish[1]+100000*cos(DEG2RAD*(crs_select-180))};
          }else{
            vor_flag_state=false;
            start = {vor2_x, vor2_y};
            finish = {start[0]+100000*sin(DEG2RAD*(crs_select)),
                      start[1]+100000*cos(DEG2RAD*(crs_select))};
          }

        }else{
          start = {0.0, 0.0};
          finish = {0.0, 0.0};
        }
        break;
    }

    //##############################################################################
    // Lateral navigation computations
    //##############################################################################
        if(vor_flag_state!=prev_vor_flag_state){
          need_update = true;
        }
        prev_vor_flag_state = vor_flag_state;

        nav_d = ((pos - start) - ( (pos-start).dot(finish-start)/
                 pow((finish-start).norm(),2)) * (finish-start)).norm();
        nav_R = (pos-finish).norm();
        if(!vor_flag_state){
          nav_R = (pos-start).norm();
        }
        nav_beta = atan2((finish[0]-start[0]),(finish[1]-start[1]));

        nav_direct = sqrt(pow(nav_R,2)-pow(nav_d,2));
        nav_total_radial = (finish-start).norm();
        nav_extension = nav_total_radial - nav_direct + 13000;
        nav_p3x = start[0] + nav_extension*sin(nav_beta);
        nav_p3y = start[1] + nav_extension*cos(nav_beta);
        Vector2d p3 = {nav_p3x, nav_p3y};
        nav_alpha_true = RAD2DEG*atan2((finish[0]-pos[0]), (finish[1]-pos[1]));
        nav_alpha = RAD2DEG*atan2((p3[0]-pos[0]), (p3[1]-pos[1]));

        if(!vor_flag_state && active_nav_source == 1){
          nav_alpha_true = RAD2DEG*atan2((pos[0]-vor1_x), (pos[1]-vor1_y));;
        }
        if(!vor_flag_state && active_nav_source == 2){
          nav_alpha_true = RAD2DEG*atan2((pos[0]-vor2_x), (pos[1]-vor2_y));;
        }

        if(nav_alpha_true<0){
          nav_alpha_true += 360;
        }
        if(nav_alpha_true>360){
          nav_alpha_true -= 360;
        }
        if(nav_alpha<0){
          nav_alpha += 360;
        }
        if(nav_alpha>360){
          nav_alpha -= 360;
        }

        nav_beta = RAD2DEG*nav_beta;
        if(nav_beta<0){
          nav_beta += 360;
        }
        if(nav_beta>360){
          nav_beta -= 360;
        }


        needle_deviation = nav_alpha_true - course;


        if(needle_deviation<-180){
          needle_deviation +=360;
        }
        if(needle_deviation>180){
          needle_deviation -= 360;
        }

        if(active_nav_source == 0){
          if(needle_deviation<0){
            needle_deviation = -nav_d/1852/2*10;
          }else{
            needle_deviation = nav_d/1852/2*10;
          }
        }else{
          needle_deviation = nav_alpha_true - course;
        }

        if(needle_deviation>180){
          needle_deviation -= 360;
        }
        if(needle_deviation<-180){
          needle_deviation += 360;
        }

        if(!vor_flag_state){
          needle_deviation = -needle_deviation;
        }

        // This code makes the needle moves smoothly

        needleOffset = needle_deviation;
        if(active_nav_source != prev_nav_source){
          switchToVor = true;
          prev_crs_select = crs_select;
        }
        if((switchToVor && abs(nav_beta-course)<0.1) || (switchToVor && crs_select != prev_crs_select)){
          switchToVor = false;
        }

        if(active_nav_source==0 || switchToVor){
          if(nav_beta-prevCourse > 180){
            course = prevCourse+ts.getDtInSeconds()/0.4*(nav_beta-360-prevCourse);
          }else if (nav_beta-prevCourse < -180){
            course = prevCourse+ts.getDtInSeconds()/0.4*(nav_beta+360-prevCourse);
          }else{
            course = prevCourse+ts.getDtInSeconds()/0.4*(nav_beta-prevCourse);
          }
        }else{
          course = nav_beta;
        }


        prev_nav_source = active_nav_source;

        if(isnan(course)){
          prevCourse = 0;
          prevNeedleOffset = 0;
        }else{
          prevCourse = course;
          prevNeedleOffset = needleOffset;
        }

        if(needleOffset>10){
          needleOffset = 10;
        } else if(needleOffset<-10){
          needleOffset = -10;
        }

        if(need_update){
          Autopilot::update_G1000(APstate, curStateVertical, curStateLateral,
                                  0, alt_select,  alt_ref/FT2M, V_ref, hdg_select,
                                  VSref, ap_flash, pit_flash, rol_flash,
                                  active_nav_source, nav_beta, vnav_situation, alt_v,
                                  active_leg, alts_flash_state, alt_flash_state,
                                  vor_flag_state);
          need_update = false;
        }

    break;
    }

  case SimulationState::Replay:
  case SimulationState::Advance: {


    // Eigen::MatrixXd fp_location = load_csv<Eigen::MatrixXd>("fp_test1.csv");
    // int nr_of_wp = fp_location.rows();
    // read the flight plan if a new one becomes available


//##############################################################################
// STM Matrices
//##############################################################################
    STMvertical << 1, 2, 3, 4, 5,
                   0, 2, 3, 4, 5,
                   0, 1, 3, 4, 5,
                   0, 2, 1, 4, 5,
                   0, 2, 3, 1, 5,
                   0, 2, 3, 4, 1,
                   0, 2, 3, 4, 5;

    STMlateral  << 1, 2, 3,
                   0, 2, 3,
                   0, 1, 3,
                   0, 2, 1;

//##############################################################################
// Import data from channels
//##############################################################################
    // Import GFC700Event: button press
    if (gfcr_token.getNumWaitingEvents(ts))
    {
      try
      {
        EventReader<GFC700Event> gfc(gfcr_token, ts);
        msg = gfc.data().msg;
        crs_select = round(gfc.data().crs_select);
        alt_select_input = round(gfc.data().alt_select);
        hdg_select = round(gfc.data().hdg_select);
        if(alt_select_input !=0){
          alt_select = alt_select_input;
        }

        // AP button pressed
        if(msg==0){
          if(APstate != 1 && PFD_failure == false){
            APstate = 1;
            Vswitched = true;
            Lswitched = true;
            need_update = true;
            curStateVertical = 1;
            curStateLateral = 1;


            phi_ref_old = phi*RAD2DEG;
            phi_ref_command = phi*RAD2DEG;
            theta_ref_old = theta;
            theta_ref_command = theta;
          }
          else{
            APstate = 2;
            ap_disengaged = true;
            need_update = true;
          }
        }

        // FD button pressed
        if(msg==7){
          if(APstate == 2){
            APstate = 0;
            need_update = true;
            curStateLateral = 0;
            curStateVertical = 0;
          } else if(APstate == 0){
            APstate = 2;
            curStateVertical = 1;
            curStateLateral = 1;
            need_update = true;
          }
        }



        // Button from lateral modes pressed
        if(msg>4 && msg<7 && GMU_failure == false){
          need_update = true;
          Lswitched = true;
          prevStateLateral = curStateLateral;
          curStateLateral = STMlateral(prevStateLateral, msg-4);
          if(prevStateLateral == 0 && curStateLateral != 0){
            APstate = 2;
            curStateVertical = 1;
          }
          if(curStateLateral==3 && fp_filename.length()==0){
            curStateLateral = prevStateLateral;
          }
        }

        // Button from vertical modes pressed
        if(msg>0 && msg<5 && ADC_failure == false){
          alt_flash_state = 0;
          alts_flash_state = 0;
          need_update = true;
          Vswitched = true;
          prevStateVertical = curStateVertical;
          curStateVertical = STMvertical(prevStateVertical, msg);
          if(curStateVertical == 4){
            if(curStateLateral !=3){
              curStateVertical = prevStateVertical;
            } else if(active_nav_source !=0){
              curStateVertical = prevStateVertical;
            }
          }
          if(prevStateVertical == 0 && curStateVertical != 0){
            APstate = 2;
            curStateLateral = 1;
          }
        }

        // CDI button pressed
        if(msg==12){
          active_nav_source = active_nav_source + 1;
          if(active_nav_source > 2){
            active_nav_source = 0;
          }
          if(curStateLateral == 3){
            curStateLateral = 1;
            Lswitched = true;
          }
          if(curStateVertical == 4){
            curStateVertical = 1;
            Vswitched = true;
          }
        }

        need_update = true;
      }
      catch (Exception& e)
      {
        W_MOD(classname << ": Error while reading GFC700Event!");
      }
    }
    // Import PrimarySwitches: AP_disconnect (working as CWS)
    try
    {
      StreamReader<PrimarySwitches> ps(*ps_token, ts);
      if(ps.data().AP_disconnect && APstate == 1){
        APstate = 3;
        need_update = true;
      }
      if(ps.data().AP_disconnect==false && APstate == 3){
        APstate = 1;
        if(curStateLateral == 1){
          Lswitched = true;
        }
        if(curStateVertical == 1){
          Vswitched = true;
        }
        need_update = true;
      }
    }
    catch (Exception& e)
    {
      W_MOD(classname << ": Error while reading FailureEvent!");
    }


    // Import FailureEvent: failures
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

        need_update = true;
      }
      catch (Exception& e)
      {
        W_MOD(classname << ": Error while reading FailureEvent!");
      }
    }

    // Import CitationOutput: statevector
    try
    {
    	StreamReader<CitationOutput> in(in_token, ts);
      V_old = Vtas;
      alt_old = alt;
      p_old = p;
      q_old = q;
      phi_old = phi;
      theta_old = theta;

      x = in.data().y[Y_y];
      y = in.data().y[Y_x];
      alt = in.data().y[Y_h];

      Vtas = in.data().y[Y_vtas];
      VtasSBY = in.data().y[Y_vtas];
      VS = in.data().y[Y_hdot];
      hdg = in.data().y[Y_psi] * RAD2DEG;
      hdg = (static_cast<int>(hdg) % 360 + 360) %360;

      phi = in.data().y[Y_phi];
      theta = in.data().y[Y_theta];

      p = in.data().y[Y_p];
      q = in.data().y[Y_q];
      r = in.data().y[Y_r];

      alpha = in.data().y[Y_alpha];
      beta = in.data().y[Y_beta];
    }
    catch(Exception& e)
    {
    	W_MOD(getId()<< classname << " caught " << e << " @ " << ts <<
                      " -- reading CitationOutput Channel");
    }

    // Initiate vectors for lateral navigation


//##############################################################################
// Active navigation source
//##############################################################################
pos = {x, y};
switch (active_nav_source){
  case 0: // GPS
    vor_flag_state = true;
    // GPS failure
    if(GPS_failure && prev_GPS_failure == false){
      frozen_x = x;
      frozen_y = y;
    }
    if(GPS_failure){
      pos = {frozen_x, frozen_y};
    }
    prev_GPS_failure = GPS_failure;


    if(nr_of_wp>0 && active_leg+1<nr_of_wp){
      start = {fp_location(active_leg, 0), fp_location(active_leg, 1)};
      finish = {fp_location(active_leg+1, 0), fp_location(active_leg+1, 1)};

      float turnradius = 1.2*Vtas*Vtas/(9.81*0.364);
      Eigen::Vector2d next_wp;

      if(active_leg+2<nr_of_wp){
        next_wp = {fp_location(active_leg+2, 0), fp_location(active_leg+2, 1)};
        curveRadius = Autopilot::getCurveRadius(start, finish, next_wp, turnradius);
      }else{
        curveRadius = 0.0;
      }

      if( (pos-finish).norm() < max(curveRadius, 200.0f) && active_leg < nr_of_wp-2)
      {
        active_leg = active_leg+1;
        need_update = true;
      }


      if(active_vnv_leg+2<nr_of_wp){
        vnv_start = {fp_location(active_vnv_leg,0), fp_location(active_vnv_leg,1)};
        vnv_finish = {fp_location(active_vnv_leg+1,0), fp_location(active_vnv_leg+1,1)};
        vnv_next_wp = {fp_location(active_vnv_leg+2,0), fp_location(active_vnv_leg+2,1)};

        float abc = getAngle(vnv_start, vnv_finish, vnv_next_wp);
        if(abc>180){
          abc = 360 - abc;
        }

        Eigen::Vector2d end_of_curve = getMid(vnv_next_wp, vnv_finish, abc, turnradius);

        if( (pos-end_of_curve).norm() < 200 )
        {
          active_vnv_leg = active_vnv_leg+1;
          need_update = true;
        }
        if(active_vnv_leg+2<nr_of_wp){
          vnv_start = {fp_location(active_vnv_leg,0), fp_location(active_vnv_leg,1)};
          vnv_finish = {fp_location(active_vnv_leg+1,0), fp_location(active_vnv_leg+1,1)};
          vnv_next_wp = {fp_location(active_vnv_leg+2,0), fp_location(active_vnv_leg+2,1)};
        }
      }


      start = {fp_location(active_leg, 0), fp_location(active_leg, 1)};
      finish = {fp_location(active_leg+1, 0), fp_location(active_leg+1, 1)};

    }else{
      start = {0.0, 0.0};
      finish = {0.0, 0.0};
    }

    break;

  case 1: // NAV Radio 1
    if(use_vor1){

      if((pos[0]-vor1_x)*sin(crs_select*DEG2RAD) + (pos[1]-vor1_y)*cos(crs_select*DEG2RAD) <0){
        // to
        vor_flag_state=true;
        finish = {vor1_x, vor1_y};
        start = {finish[0]+100000*sin(DEG2RAD*(crs_select-180)),
                  finish[1]+100000*cos(DEG2RAD*(crs_select-180))};
      }else{
        // from
        vor_flag_state=false;
        start = {vor1_x, vor1_y};
        finish = {start[0]-100000*sin(DEG2RAD*(crs_select-180)),
                  start[1]-100000*cos(DEG2RAD*(crs_select-180))};
      }
    }else{
      start = {0.0, 0.0};
      finish = {0.0, 0.0};
    }
    break;

  case 2: // NAV Radio 2
    if(use_vor2){
      if((pos[0]-vor2_x)*sin(crs_select*DEG2RAD) + (pos[1]-vor2_y)*cos(crs_select*DEG2RAD) <0){
        vor_flag_state=true;
        finish = {vor2_x, vor2_y};
        start = {finish[0]+100000*sin(DEG2RAD*(crs_select-180)),
                  finish[1]+100000*cos(DEG2RAD*(crs_select-180))};
      }else{
        vor_flag_state=false;
        start = {vor2_x, vor2_y};
        finish = {start[0]+100000*sin(DEG2RAD*(crs_select)),
                  start[1]+100000*cos(DEG2RAD*(crs_select))};
      }

    }else{
      start = {0.0, 0.0};
      finish = {0.0, 0.0};
    }
    break;
}

//##############################################################################
// Lateral navigation computations
//##############################################################################
    if(vor_flag_state!=prev_vor_flag_state){
      need_update = true;
    }
    prev_vor_flag_state = vor_flag_state;

    nav_d = ((pos - start) - ( (pos-start).dot(finish-start)/
             pow((finish-start).norm(),2)) * (finish-start)).norm();
    nav_R = (pos-finish).norm();
    if(!vor_flag_state){
      nav_R = (pos-start).norm();
    }
    nav_beta = atan2((finish[0]-start[0]),(finish[1]-start[1]));

    nav_direct = sqrt(pow(nav_R,2)-pow(nav_d,2));
    nav_total_radial = (finish-start).norm();
    nav_extension = nav_total_radial - nav_direct + 13000;
    nav_p3x = start[0] + nav_extension*sin(nav_beta);
    nav_p3y = start[1] + nav_extension*cos(nav_beta);
    Vector2d p3 = {nav_p3x, nav_p3y};
    nav_alpha_true = RAD2DEG*atan2((finish[0]-pos[0]), (finish[1]-pos[1]));
    nav_alpha = RAD2DEG*atan2((p3[0]-pos[0]), (p3[1]-pos[1]));

    if(!vor_flag_state && active_nav_source == 1){
      nav_alpha_true = RAD2DEG*atan2((pos[0]-vor1_x), (pos[1]-vor1_y));;
    }
    if(!vor_flag_state && active_nav_source == 2){
      nav_alpha_true = RAD2DEG*atan2((pos[0]-vor2_x), (pos[1]-vor2_y));;
    }

    if(nav_alpha_true<0){
      nav_alpha_true += 360;
    }
    if(nav_alpha_true>360){
      nav_alpha_true -= 360;
    }
    if(nav_alpha<0){
      nav_alpha += 360;
    }
    if(nav_alpha>360){
      nav_alpha -= 360;
    }

    nav_beta = RAD2DEG*nav_beta;
    if(nav_beta<0){
      nav_beta += 360;
    }
    if(nav_beta>360){
      nav_beta -= 360;
    }
    if(active_nav_source!=0)
    {
      nav_beta = crs_select;
    }


    needle_deviation = nav_alpha_true - course;


    if(needle_deviation<-180){
      needle_deviation +=360;
    }
    if(needle_deviation>180){
      needle_deviation -= 360;
    }

    if(active_nav_source == 0){
      if(needle_deviation<0){
        needle_deviation = -nav_d/1852/2*10;
      }else{
        needle_deviation = nav_d/1852/2*10;
      }
    }else{
      needle_deviation = nav_alpha_true - course;
    }

    if(needle_deviation>180){
      needle_deviation -= 360;
    }
    if(needle_deviation<-180){
      needle_deviation += 360;
    }

    if(!vor_flag_state){
      needle_deviation = -needle_deviation;
    }

    if(active_nav_source==1 && !use_vor1)
    {
      needle_deviation = 10;
    }
    if(active_nav_source==2 && !use_vor2)
    {
      needle_deviation = 10;
    }

    // This code makes the needle moves smoothly

    needleOffset = prevNeedleOffset+ts.getDtInSeconds()*(-1/HSItimeConstant*prevNeedleOffset+1/HSItimeConstant*needle_deviation);


    if(active_nav_source != prev_nav_source){
      switchToVor = true;
      prev_crs_select = crs_select;
    }
    if((switchToVor && abs(nav_beta-course)<0.1) || (switchToVor && crs_select != prev_crs_select)){
    // if((switchToVor && abs(nav_beta-course)<0.1)){
      switchToVor = false;
    }

    if(active_nav_source==0 || switchToVor){
      if(nav_beta-prevCourse > 180){
        course = prevCourse+ts.getDtInSeconds()/0.4*(nav_beta-360-prevCourse);
      }else if (nav_beta-prevCourse < -180){
        course = prevCourse+ts.getDtInSeconds()/0.4*(nav_beta+360-prevCourse);
      }else{
        course = prevCourse+ts.getDtInSeconds()/0.4*(nav_beta-prevCourse);
      }
    }else{
      course = nav_beta;
    }

    if(needleOffset>10){
      needleOffset = 10;
    } else if(needleOffset<-10){
      needleOffset = -10;
    }


    if(isnan(needleOffset)){
      prevCourse = 0;
      prevNeedleOffset = 0;
    }else{
      prevCourse = course;
      prevNeedleOffset = needleOffset;
    }
    prev_nav_source = active_nav_source;




//##############################################################################
// Failures
//##############################################################################
    // Blocked Static Port
    if(prev_clogged_sp == false && clogged_sp){
      frozen_altitude = alt;
      frozen_vs = VS;
      pressure_3 = calc_p(alt);
    }
    if(clogged_sp){
      pressure_4 = calc_p(alt);
      alt = frozen_altitude;
      VS = frozen_vs;
      dp = pressure_4-pressure_3;
      Vtas = sqrt((2*(dp+(0.5*1.225*Vtas*Vtas)))/1.225);

    }
    prev_clogged_sp = clogged_sp;


    // ADC failure
    if(curStateVertical > 1 && ADC_failure){
      curStateVertical = 1;
      Vswitched = true;
    }

    // GMU failure
    if(curStateLateral > 1 && GMU_failure){
      curStateLateral = 1;
      Lswitched = true;
    }

    // Blocked Pitot Tube
    if(prev_clogged_pt == false && clogged_pt == true){
      pressure_1 = calc_p(alt);
      q1 = 0.5*1.225*Vtas*Vtas;
      //q1_tas = 0.5*1.225*V1_tas*V1_tas;
    }
    if(clogged_pt){
      pressure_2 = calc_p(alt);
      dp = pressure_1-pressure_2;
      //Vtas = sqrt((2*(dp+q1))/1.225);
      Vtas = sqrt((2*(dp+q1))/1.225);
    }
    prev_clogged_pt = clogged_pt;

    // PFD failure
    if(PFD_failure && !prev_PFD_failure){
      APstate = 0;
      need_update = true;
    }


//##############################################################################
// Vertical Flight Director
//##############################################################################
    switch (curStateVertical) {
      case 0: // OFF
        theta_ref = 0;
        break;

      case 1: // PIT
        if(Vswitched){
          need_update = true;
          theta_ref_pit = theta;
          Vswitched = false;
          ap_flash = false;
          pit_flash = true;
          pit_flash_timer = 0;
        }

        if(msg==10){
          theta_ref_pit += 0.5*DEG2RAD;
          need_update = true;
        }
        if(msg==11){
          theta_ref_pit -= 0.5*DEG2RAD;
          need_update = true;
        }

        theta_ref = theta_ref_pit;

        if(pit_flash){
          pit_flash_timer = pit_flash_timer + ts.getDtInSeconds();
          if(pit_flash_timer > 3){
            pit_flash = false;
            need_update = true;
          }
        }

        if(alt<alt_select*FT2M && alt+VS*7>alt_select*FT2M
           && VS>50*FT2M*MIN2S && ADC_failure==false){

          curStateVertical = 6;
          changed_to_alt_captured = true;
        }

        if(alt>alt_select*FT2M && alt+VS*7<alt_select*FT2M
           && VS<-50*FT2M*MIN2S && ADC_failure==false){

          curStateVertical = 6;
          changed_to_alt_captured = true;
        }

        //D_MOD("Theta ref in FD: " << theta_ref*RAD2DEG)
        break;

      case 2: // VS
        if(Vswitched){
          need_update = true;
          VSref = floor((VS/FT2M/MIN2S + 50)/100)*100;
          Vswitched = false;
          pit_flash = false;
        }

        if(msg==10){
          VSref = VSref + 100;
          need_update = true;
        }
        if(msg==11){
          VSref = VSref - 100;
          need_update = true;
        }
        VSref = std::max(-1200, std::min((int) VSref, 1500));

        if(clogged_sp){
          theta_ref = 0;
        } else{
          phi_abs = abs(phi * RAD2DEG);
          VS_roll_addendum = 0.0991 * pow(phi_abs,2) + 0.5062 * phi_abs;

          if(Vtas!=0){
            theta_ref = asin((VSref+VS_roll_addendum) * FT2M * MIN2S /VtasSBY)+alpha;
          } else{
            theta_ref = 0;
          }
        }

        if(alt<alt_select*FT2M && alt+VS*7>alt_select*FT2M && VS>50*FT2M*MIN2S){
          curStateVertical = 6;
          changed_to_alt_captured = true;
        }

        if(alt>alt_select*FT2M && alt+VS*7<alt_select*FT2M && VS<-50*FT2M*MIN2S){
          curStateVertical = 6;
          changed_to_alt_captured = true;
        }
        break;

      case 3: // ALT
        if(Vswitched){
          alt_ref = ((int)(alt/FT2M) + 5)/10*10*FT2M;
          need_update = true;
          Vswitched = false;
          pit_flash = false;
        }

        if(changed_to_alt_captured){
          alt_ref = alt_select*FT2M;
          need_update = true;
          changed_to_alt_captured = false;

          alt_flash_state = 1;
          alt_flash_timer = 0;
          pit_flash = false;
        }

        if(alt_flash_state != 0){
          alt_flash_timer = alt_flash_timer + ts.getDtInSeconds();
          if(int(2*alt_flash_timer) % 2 == 1 && alt_flash_state == 1){
            alt_flash_state = 2;
            need_update = true;
          } else if(int(2*alt_flash_timer) % 2 == 0 && alt_flash_state == 2){
            alt_flash_state = 1;
            need_update = true;
          }

          if(alt_flash_timer > 10){
            alt_flash_state = 0;
            need_update = true;
          }
        }

        alt_error = alt_ref - alt;
        theta_ref = (alt_error - (alt-alt_old)/ts.getDtInSeconds()) * DEG2RAD;

        // LIMIT theta_ref in ALT modus to maximum 150 ft/m
        if(Vtas != 0){
          if(theta_ref > asin(150 * FT2M * MIN2S/Vtas)+alpha){
            theta_ref = asin(150 * FT2M * MIN2S/Vtas)+alpha;
          }
          if(theta_ref < asin(-150 * FT2M * MIN2S/Vtas)+alpha){
            theta_ref = asin(-150 * FT2M * MIN2S/Vtas)+alpha;
          }
        }else{
          theta_ref = 0;
        }

        break;

      case 4: // VPATH
        if(Vswitched){
          need_update = true;
          Vswitched = false;
          pit_flash = false;

          alt_ref = ((int)(alt/FT2M) + 5)/10*10*FT2M;
        }

        if(nr_of_wp>0 && active_vnv_leg+1<nr_of_wp){
          alt_v = fp_location(active_vnv_leg+1,2);
          iter_wps = 1;
          distance_to_next_vnv = (pos- vnv_finish).norm();
          while(alt_v == -1 && active_vnv_leg+1+iter_wps<nr_of_wp){
            alt_v = fp_location(active_vnv_leg+1+iter_wps,2);
            distance_to_next_vnv += fp_location(active_vnv_leg+1+iter_wps,4);
            iter_wps += 1;
          }
          time_to_bod = (alt-alt_v*FT2M)/(Vtas*0.04366);

        }else{
          alt_v = alt/FT2M;
          time_to_bod = 0.0;
        }

        switch (vnav_situation) {
          
          case 0: // ALT active, VPATH armed
            fpa_req = tan((alt-alt_v*FT2M)/distance_to_next_vnv);
            alt_error = alt_ref - alt;
            theta_ref = (alt_error - (alt-alt_old)/ts.getDtInSeconds())*DEG2RAD;

            if(theta_ref > 6*DEG2RAD){
              theta_ref = 6*DEG2RAD;
            }
            if(theta_ref < -3*DEG2RAD){
              theta_ref = -3*DEG2RAD;
            }

            dx = (alt-alt_v*FT2M)/tan(2.5*DEG2RAD);


            dist_to_top = distance_to_next_vnv-dx;
            //distance_to_next_vnv<dx
            if(dist_to_top<0 && alt_v != -1 && alt-alt_v*FT2M>25){
              vnav_situation = 1;
              need_update = true;
              switch_to_vpth = true;
            }
            break;

          case 1: // VPATH active, ALV armed
            //theta_ref = alpha - 2.5*DEG2RAD;
            fpa_req = tan((alt-alt_v*FT2M)/distance_to_next_vnv);
            theta_ref = alpha - fpa_req;

            if(switch_to_vpth){
              alt_v_until_switch = alt_v;
              switch_to_vpth = false;
            }

            if(alt-alt_v_until_switch*FT2M<20 && alt_v_until_switch != -1){
              vnav_situation = 0;
              alt_ref = alt_v_until_switch*FT2M;
              need_update = true;
            }
            break;
        }

        if(curStateLateral !=3){
          curStateVertical = 1;
          Vswitched = true;
        }
        break;

      case 5: // FLC
        if(Vswitched){
          V_ref = tasToIas(Vtas, alt)/KTS2MS;
          need_update = true;
          Vswitched = false;
          pit_flash = false;
        }

        if(msg==10){
          V_ref = V_ref - 5;
          need_update = true;
        }

        if(msg==11){
          V_ref = V_ref + 5;
          need_update = true;
        }

        V_ref = std::max(85, std::min( (int) V_ref, 200));

        V_error = V_ref*KTS2MS - tasToIas(Vtas, alt);
        theta_ref = (V_error - 2*KTS2MS* (tasToIas(Vtas,alt)-
                    tasToIas(V_old,alt))/(ts.getDtInSeconds())) * -4 * DEG2RAD;

        if(alt<alt_select*FT2M && alt+VS*7>alt_select*FT2M && VS>50*FT2M*MIN2S){
          curStateVertical = 6;
          changed_to_alt_captured = true;
        }

        if(alt>alt_select*FT2M && alt+VS*7<alt_select*FT2M && VS<-50*FT2M*MIN2S){
          curStateVertical = 6;
          changed_to_alt_captured = true;
        }
        break;

      case 6: // ALTS
        if(changed_to_alt_captured){
          alt_ref = alt_select*FT2M;
          need_update = true;
          changed_to_alt_captured = false;
          theta_at_switch = theta;
          VS_at_switch = theta;
          pit_flash = false;
          alts_flash_state = 1;
          alts_flash_timer = 0;
        }

        if(alts_flash_state != 0){
          alts_flash_timer = alts_flash_timer + ts.getDtInSeconds();
          if(int(2*alts_flash_timer) % 2 == 1 && alts_flash_state == 1){
            alts_flash_state = 2;
            need_update = true;
          } else if(int(2*alts_flash_timer) % 2 == 0 && alts_flash_state == 2){
            alts_flash_state = 1;
            need_update = true;
          }

          if(alts_flash_timer > 10){
            alts_flash_state = 0;
            need_update = true;
          }
        }

        // theta_at_switch = theta_at_switch  - VS_at_switch/6*ts.getDtInSeconds();
        theta_at_switch -= VS_at_switch/9*ts.getDtInSeconds();
        alt_error = alt_ref - alt;
        theta_ref = (alt_error - (alt-alt_old)/ts.getDtInSeconds()) * DEG2RAD;

        if(theta >0){
          theta_ref = min(theta_at_switch, theta_ref);
        }
        if(theta < 0){
          theta_ref = max(theta_at_switch, theta_ref);
        }

        if(alt>alt_select*FT2M-2 && VS>10*FT2M*MIN2S){
          curStateVertical = 3;
          changed_to_alt_captured = true;
          alts_flash_state = 0;
        }
        if(alt<alt_select*FT2M+2 && VS<10*FT2M*MIN2S){
          curStateVertical = 3;
          changed_to_alt_captured = true;
          alts_flash_state = 0;
        }
        break;
    }

//##############################################################################
// Lateral Flight Director
//##############################################################################
    phi_rate1 = RAD2DEG * atan(Vtas/KTS2MS/364);

    switch (curStateLateral){
      case 0: // AP OFF
        if(Lswitched){
          need_update = true;
          Lswitched = false;
          rol_flash = false;
        }
        if(rol_flash || pit_flash){
          rol_flash = false;
          pit_flash = false;
        }
        break;


      case 1: // ROL Hold
        if(Lswitched){

          need_update = true;
          Lswitched = false;
          rol_flash = true;
          rol_flash_timer = 0;

          if(phi>6*DEG2RAD ){
            phi_ref_rol = min(phi*RAD2DEG, 22.0);
          }
          else if(phi<-6*DEG2RAD){
            phi_ref_rol = max(phi*RAD2DEG, -22.0);
          }else{
            phi_ref_rol = 0;
          }
        }

        phi_ref = phi_ref_rol;

        if(rol_flash){
          rol_flash_timer = rol_flash_timer + ts.getDtInSeconds();
          if(rol_flash_timer > 3){
            rol_flash = false;
            need_update = true;
          }
        }

        break;

      case 2: // HDG hold
        if(Lswitched){
          need_update = true;
          Lswitched = false;
          rol_flash = false;
          hdg_int = 0;
          reset_hdg = true;
        }

        if(hdg_select != hdg_select_old){
          hdg_int = 0;
          reset_hdg = true;
        }

        hdg_select_old = hdg_select;
        hdg_error = hdg_select - hdg;

        if(hdg_error > 180){
          hdg_error = -360 + hdg_error;
        }
        if (hdg_error < -180){
          hdg_error = 360 + hdg_error;
        }

        if(reset_hdg){
          hdg_error_old = hdg_error;
          reset_hdg = false;
        }

        hdg_int = hdg_int + hdg_error * ts.getDtInSeconds();
        phi_ref = 1.0*(hdg_error + 0.0001*hdg_int - 15.0*
                  (hdg_error-hdg_error_old)/ts.getDtInSeconds());
        hdg_error_old = hdg_error;

        if(phi_ref>phi_rate1){
          phi_ref = phi_rate1;
        }
        if(phi_ref<-phi_rate1){
          phi_ref = -phi_rate1;
        }
        break;

      case 3: // NAV
        if(Lswitched){
          need_update = true;
          Lswitched = false;
          rol_flash = false;
        }

        if(nav_alpha>nav_beta){
          hdg_ref = std::min(nav_beta+30, nav_beta-(nav_beta-nav_alpha)*10);
        }else{
          hdg_ref = std::max(nav_beta-30, nav_beta-(nav_beta-nav_alpha)*10);
        }



        if(hdg_ref != hdg_ref_old){
          hdg_int = 0;
          reset_hdg = true;
        }

        hdg_ref_old = hdg_ref;
        hdg_error = hdg_ref - hdg;

        if(hdg_error > 180){
          hdg_error = -360 + hdg_error;
        }
        if (hdg_error < -180){
          hdg_error = 360 + hdg_error;
        }

        if(reset_hdg){
          hdg_error_old = hdg_error;
          reset_hdg = false;
        }

        hdg_int = hdg_int + hdg_error * ts.getDtInSeconds();
        phi_ref = 1.0*(hdg_error + 0.0001*hdg_int - 15.0*
                  (hdg_error-hdg_error_old)/ts.getDtInSeconds());

        hdg_error_old = hdg_error;

        if(phi_ref>phi_rate1){
          phi_ref = phi_rate1;
        }
        if(phi_ref<-phi_rate1){
          phi_ref = -phi_rate1;
        }

        if(VOR_failure && active_nav_source != 0){
          phi_ref = 0;
        }
        break;
    }

//##############################################################################
// Autopilot & Flight Director
//##############################################################################

// Smooth out Flight Director with first order lag
phi_ref_loop = phi_ref_old + ts.getDtInSeconds()*(-1/2.0*phi_ref_old+1/2.0*phi_ref_command);
phi_ref_old = phi_ref_loop;
phi_ref_command = phi_ref;
phi_ref = phi_ref_loop;

theta_ref_loop = theta_ref_old + ts.getDtInSeconds()*(-1/1.0*theta_ref_old+1/1.0*theta_ref_command);
theta_ref_old = theta_ref_loop;
theta_ref_command = theta_ref;
theta_ref = theta_ref_loop;

// Bypass low pass filter when using CWS
if(APstate == 3){
  phi_ref = phi_ref_rol;
  phi_ref_old = phi_ref;
  phi_ref_command = phi_ref;
}
if(APstate == 3){
  theta_ref = theta_ref_pit;
  theta_ref_old = theta_ref;
  theta_ref_command = theta_ref;
}

    switch (APstate){
      case 0: // OFF
        // Use pilot input as delta_e
        ap_flash = false;
        ap_on = false;
        fd_on = false;

        alt_flash_state = 0;
        alts_flash_state = 0;
        break;

      case 1: // ON
        // Use theta_ref to calculate
        ap_on = true;
        fd_on = true;

        if (theta_ref<-7.5*DEG2RAD)
        {
          theta_ref = -7.5*DEG2RAD;
        }
        if (theta_ref > 15 * DEG2RAD)
        {
          theta_ref = 15 * DEG2RAD;
        }

        phi_abs = abs(phi * RAD2DEG);
        theta_roll_addendum = 0.0031 * pow(phi_abs,2) - 0.0027 * phi_abs;
    	  theta_error = theta_ref - theta + theta_roll_addendum*DEG2RAD;
        q_ref = (theta_error+(0.02*(theta-theta_old)/ts.getDtInSeconds()))*0.8;
        q_error = q_ref - q;
        q_int = q_int + q_error * ts.getDtInSeconds();

        ude = ((q_error) +(q_int * 2) -(0.02*(q-q_old)/ts.getDtInSeconds()))*-4;
        de = de_old + ts.getDtInSeconds()*(-1/Tservo*de_old+1/Tservo*ude_old);

        ude_old = ude;
        de_old = de;


        if(de>25*DEG2RAD){
          de = 25*DEG2RAD;
        }
        if(de<-25*DEG2RAD){
          de = -25*DEG2RAD;
        }

        // Lateral AP:

        phi_error = phi_ref - phi*RAD2DEG;
        p_ref = phi_error * 0.1;
        p_error = p_ref - p;

        uda = -40 * (p_error - 0.05 * (p-p_old)/ts.getDtInSeconds());
        da = da_old + ts.getDtInSeconds()*(-1/(Tservo*3)*da_old+1/(Tservo*3)*uda_old);  // making the Tservo bigger here -> needed bc to abrupt change in roll when engaging a/p

        uda_old = uda;
        da_old = da;

        if(da>25*DEG2RAD){
          da = 25*DEG2RAD;
        }
        if(da<-25*DEG2RAD){
          da = -25*DEG2RAD;
        }

        beta_error = 0 - beta;
        r_ref = -1 * beta_error;
        r_error = r_ref - r;
        dr = r_error * -100 * DEG2RAD;

        if(dr>15*DEG2RAD){
          dr = 15*DEG2RAD;
        }
        if(dr<-15*DEG2RAD){
          dr = -15*DEG2RAD;
        }


        break;

      case 2: // Only FD on
        ap_on = false;
        fd_on = true;

        if(ap_disengaged){
          need_update = true;
          ap_disengaged = false;
          pit_flash = false;
          rol_flash = false;

          ap_flash = true;
          ap_flash_timer = 0;
        }

        if(ap_flash && !PFD_failure){
          ap_flash_timer = ap_flash_timer + ts.getDtInSeconds();
          if(ap_flash_timer >3){
            ap_flash = false;
            need_update = true;
          }
        }
        break;

      case 3: // CWS
        phi_ref_rol = phi*RAD2DEG;
        theta_ref_pit = theta;

        break;
    }
msg = GFC700Event::GFC700_NONE;

// #############################################################################
// Do navigation calculation again so that PFD and MFD always show GPS info
// #############################################################################
if(active_nav_source != 0){
  if(GPS_failure && prev_GPS_failure == false){
    frozen_x = x;
    frozen_y = y;
  }
  if(GPS_failure){
    pos = {frozen_x, frozen_y};
  }
  prev_GPS_failure = GPS_failure;


  if(nr_of_wp>0 && active_leg+1<nr_of_wp){
    start = {fp_location(active_leg, 0), fp_location(active_leg, 1)};
    finish = {fp_location(active_leg+1, 0), fp_location(active_leg+1, 1)};

    float turnradius = 1.2*Vtas*Vtas/(9.81*0.364);
    Eigen::Vector2d next_wp;

    if(active_leg+2<nr_of_wp){
      next_wp = {fp_location(active_leg+2, 0), fp_location(active_leg+2, 1)};
      curveRadius = Autopilot::getCurveRadius(start, finish, next_wp, turnradius);
    }else{
      curveRadius = 0.0;
    }

    if( (pos-finish).norm() < max(curveRadius, 200.0f) && active_leg < nr_of_wp-2)
    {
      active_leg = active_leg+1;
      need_update = true;
    }

    start = {fp_location(active_leg, 0), fp_location(active_leg, 1)};
    finish = {fp_location(active_leg+1, 0), fp_location(active_leg+1, 1)};

  }else{
    start = {0.0, 0.0};
    finish = {0.0, 0.0};
  }
  nav_R = (pos-finish).norm();
  nav_alpha_true = RAD2DEG*atan2((finish[0]-pos[0]), (finish[1]-pos[1]));
  if(nav_alpha_true<0){
    nav_alpha_true += 360;
  }
  if(nav_alpha_true>360){
    nav_alpha_true -= 360;
  }
}
if(active_leg+1<nr_of_wp){
  dtk = fp_location(active_leg+1,3);
}else{
  dtk = 0;
}

if(AFCS_rol && APstate == 1){
  da = 1*DEG2RAD;
}
if(AFCS_pit && APstate == 1){
  de = 1*DEG2RAD;
}

//##############################################################################
// Update G1000
//##############################################################################
    if(need_update){
      if(PFD_failure && !prev_PFD_failure){
        ap_flash = true;
      } else if(PFD_failure){
        ap_flash = false;
      }
      prev_PFD_failure = PFD_failure;

      Autopilot::update_G1000(APstate, curStateVertical, curStateLateral,
                              0, alt_select,  alt_ref/FT2M, V_ref, hdg_select,
                              VSref, ap_flash, pit_flash, rol_flash,
                              active_nav_source, nav_beta, vnav_situation, alt_v,
                              active_leg, alts_flash_state, alt_flash_state,
                              vor_flag_state);
      need_update = false;
      //I_MOD("Course:" << course)
    }
    // -------------------------------------------------------------------------
    break;
    }
  default:
    // other states should never be entered for a SimulationModule,
    // HardwareModules on the other hand have more states. Throw an
    // exception if we get here,
    throw CannotHandleState(getId(),GlobalId(), "state unhandled");
  }


//##############################################################################
// Send control surface deflections and screen references always
//##############################################################################


  StreamWriter<AutopilotChannel> ap(ap_token, ts);
  ap.data().APstate = APstate;
  ap.data().de = de;
  ap.data().da = da;
  ap.data().dr = dr;
  ap.data().theta_ref = RAD2DEG*theta_ref;
  ap.data().phi_ref = phi_ref;
  ap.data().needle_deviation = needleOffset;
  ap.data().dme = nav_R /1852;

  ap.data().course = course;
  ap.data().brg = nav_alpha_true;
  ap.data().dtk = dtk;

  ap.data().nav_R = nav_R;
  ap.data().vnav_R = distance_to_next_vnv;
  ap.data().dist_to_top = dist_to_top;
  ap.data().time_to_bod = time_to_bod;
  ap.data().fpa_req = fpa_req;
  if(Vtas > 20){
    ap.data().turn_rate = 1091*tan(phi)/(Vtas/KTS2MS);
  } else{
    ap.data().turn_rate = 0;
  }
  if (snapshotNow()) {
    // keep a copy of the model state. Snapshot sending is done in the
    // sendSnapshot routine, later, and possibly at lower priority
    // e.g.
    // snapshot_state_variable1 = state_variable1; ...
    // (or maybe if your state is very large, there is a cleverer way ...)
  }
}

void Autopilot::trimCalculation(const TimeSpec& ts, const TrimMode& mode)
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

//##############################################################################
// Definitions
//##############################################################################
void Autopilot::update_G1000(int APstate, int ap_vertical, int ap_lateral,
      int ap_armed, float target_alt, float alt_hold, float target_speed,
      float hdg_bug, float target_vs, bool ap_flash, bool pit_flash,
      bool rol_flash, int active_nav_source, float course, int vnav_situation,
      float alt_v, int active_leg, int alts_flash_state, int alt_flash_state,
      bool vor_flag_state)
{
  EventWriter<AP2G1000Channel> ap2g_writer(ap2g_token);
  ap2g_writer.data().APstate = APstate;
  ap2g_writer.data().ap_vertical = ap_vertical;
  ap2g_writer.data().ap_lateral = ap_lateral;
  ap2g_writer.data().ap_armed = ap_armed;
  ap2g_writer.data().target_alt = round(target_alt);
  ap2g_writer.data().target_speed = target_speed;
  ap2g_writer.data().hdg_bug = hdg_bug;
  ap2g_writer.data().target_vs = target_vs;
  ap2g_writer.data().alt_hold = round(alt_hold);
  ap2g_writer.data().ap_flash = ap_flash;
  ap2g_writer.data().pit_flash = pit_flash;
  ap2g_writer.data().rol_flash = rol_flash;
  ap2g_writer.data().active_nav_source = active_nav_source;
  ap2g_writer.data().course = course;
  ap2g_writer.data().vnav_situation = vnav_situation;
  ap2g_writer.data().altitude_target_vnav = alt_v;
  ap2g_writer.data().active_leg = active_leg;
  ap2g_writer.data().active_vnv_leg = active_vnv_leg;
  ap2g_writer.data().alts_flash_state = alts_flash_state;
  ap2g_writer.data().alt_flash_state = alt_flash_state;
  ap2g_writer.data().vor_flag_state = vor_flag_state;
}

float Autopilot::calc_p(float h){
    const float p0 = 101325;
    const float T0 = 288.15;
    const float g = 9.80665;
    const float R = 287;
    const float a = -0.0065;

    return p0 * pow(((T0 + a * h)/T0),-(g/(a*R)));
}

float Autopilot::getCurveRadius(Eigen::Vector2d A, Eigen::Vector2d B, Eigen::Vector2d C, float r){
  float abc = RAD2DEG * (atan2(C(1)-B(1), C(0)-B(0)) - atan2(A(1)-B(1), A(0)-B(0)));
  if(abc<0){
    abc = abc + 360;
  }

  float AB = pow(pow(B(0)-A(0), 2)+pow(B(1)-A(1),2), 0.5);
  float EB = abs(r/(tan(0.5*abc/RAD2DEG)));
  return EB;
}


float Autopilot::getAngle(Eigen::Vector2d A, Eigen::Vector2d B, Eigen::Vector2d C){
  float ang = RAD2DEG * (atan2(C(1)-B(1), C(0)-B(0)) - atan2(A(1)-B(1), A(0)-B(0)));
  if(ang<0){
    return ang + 360;
  }
  else{
    return ang;
  }
}

Eigen::Vector2d Autopilot::getMid(Eigen::Vector2d A, Eigen::Vector2d B, float abc, float r){
  float AB = pow(pow(B(0)-A(0), 2)+pow(B(1)-A(1),2), 0.5);
  float EB = r/(tan(0.5*abc/RAD2DEG));
  float AE = AB - EB;

  Eigen::Vector2d E(0,0);

  float hab;

  if(A(1)<=B(1)){
    hab = asin((B(1)-A(1))/AB);
    E(1) = A(1)+AE*sin(hab);
  } else{
    hab = asin((A(1)-B(1))/AB);
    E(1) = A(1)-AE*sin(hab);
  }

  if(A(0)<=B(0)){
    E(0) = A(0)+AE*cos(hab);
  } else{
    E(0) = A(0)-AE*cos(hab);
  }

  return E;
}

// Make a TypeCreator object for this module, the TypeCreator
// will check in with the scheme-interpreting code, and enable the
// creation of modules of this type
static TypeCreator<Autopilot> a(Autopilot::getMyParameterTable());
