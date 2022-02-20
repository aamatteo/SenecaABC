/* ------------------------------------------------------------------   */
/*      item            : G1000.cxx
        made by         : jcomans
	from template   : DusimeModuleTemplate.cxx
        template made by: Rene van Paassen
        date            : Mon Mar 31 18:03:23 2014
	category        : body file
        description     :
	changes         : Mon Mar 31 18:03:23 2014 first version
	template changes: 030401 RvP Added template creation comment
	                  060512 RvP Modified token checking code
        language        : C++
*/

static const char c_id[] =
"$Id: G1000.cxx,v 1.26 2021/03/11 16:09:47 jordyleeuwen Exp $";

#define G1000_cxx
// include the definition of the module class
#include "G1000.hxx"

// include the debug writing header, by default, write warning and
// error messages
#define W_MOD
#define E_MOD
//#define D_MOD
#include <debug.h>

// include additional files needed for your calculation here
#include "G1000GaugeData.hxx"
//#include <CitStatesOutputs.h>
#include <StatesOutputs.h>
#include <GlobalConstants.hpp>

// the standard package for DUSIME, including template source
#define DO_INSTANTIATE
#include <dusime.h>

// class/module name
const char* const G1000::classname = "g1000";

// initial condition/trim table
const IncoTable* G1000::getMyIncoTable()
{
  static IncoTable inco_table[] = {
    // enter pairs of IncoVariable and VarProbe pointers (i.e.
    // objects made with new), in this table.
    // For example
//    {(new IncoVariable("example", 0.0, 1.0, 0.01))
//     ->forMode(FlightPath, Constraint)
//     ->forMode(Speed, Control),
//     new VarProbe<G1000,double>
//       (REF_MEMBER(&G1000::i_example))}

    // always close off with:
    { NULL, NULL} };

  return inco_table;
}

// parameters to be inserted
const ParameterTable* G1000::getMyParameterTable()
{
  static const ParameterTable parameter_table[] = {
    { "set-timing",
      new MemberCall<G1000,TimeSpec>
        (&G1000::setTimeSpec), set_timing_description },

    { "check-timing",
      new MemberCall<G1000,vector<int> >
      (&G1000::checkTiming), check_timing_description },

    { "position-and-size",
      new MemberCall<G1000,vector<int> >
      (&G1000::setWindowPositionSize)},

    { "use-simona-scaling",
      new VarProbe<G1000, bool>
      REF_MEMBER(&G1000::use_simona_scaling), "scales touchscreen for simona"},

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
G1000::G1000(Entity* e, const char* part, const
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
  g1000_glwindow_(),

  index_apc(-1),
  index_apr(-1),

  mouse_down(false),
  mouse_left(false),
  mouse_x(0),
  mouse_y(0),
  alt_select(1000),
  hdg_select(0),
  crs_select(0),
  crsNav1(0),
  crsNav2(0),
  active_nav_source(0),
  prev_nav_source(0),
  no_double_click(false),
  msg(GFC700Event::GFC700_NONE),
  need_update(false),

  acceleration_timer(0),
  increment(1),
  zoom_index(2),
  range_levels(NULL),
  range(5),

  heading(0),

  prev_msg(14),
  msg_animation(14),
  animation_timer(0),
  animation(false),

  dme_status(0),
  prev_dme_status(0),
  dme_animation_timer(0),
  dme_animation(false),

  // initialize the data you need for the trim calculation

  // initialize the channel access tokens
  // example
  // my_token(getId(), NameSet(getEntity(), "MyData", part)),
  citation_out_read_token_(getId(), NameSet(getEntity(), "CitationOutput", part)),
  secondary_controls_read_token_(getId(), NameSet(getEntity(), "SecondaryControls", part)),
  sw_token(getId(), NameSet(getEntity(), "SecondarySwitches", ""), 101),
  ap2g_token(getId(), NameSet(getEntity(), "AP2G1000Channel", part)),
  ap_token(getId(), NameSet(getEntity(), "AutopilotChannel", part)),
  apinco_token(getId(), NameSet(getEntity(), "APIncoEvent", part)),
  fail_token(getId(), NameSet(getEntity(), "FailureEvent", ""), ChannelDistribution::JOIN_MASTER),

  gfc_token(getId(), NameSet(getEntity(), "GFC700Event", ""), ChannelDistribution::JOIN_MASTER),

  ap_targets_read_token_(new APTargetsReadToken(getId(), NameSet(getEntity(),"AutopilotTargets", ""))),

  // activity initialization
  // myclock(),
  _display_update_callback(this, &G1000::doCalculation),
  _display_update_activity(getId(), "Update the G1000 display", &_display_update_callback, ps)
{
  // do the actions you need for the simulation

   _display_update_activity.setTrigger(citation_out_read_token_ && ap_token);

  // connect the triggers for simulation
  // do_calc.setTrigger(/* fill in your triggering channels,
  // 			or enter the clock here */);

  // // connect the triggers for trim calculation. Leave this out if you
  // // don not need input for trim calculation
  // trimCalculationCondition(/* fill in your trim triggering channels */);
}

bool G1000::complete()
{
  /* All your parameters have been set. You may do extended
     initialisation here. Return false if something is wrong. */

  g1000_glwindow_.openWindow();
  g1000_glwindow_.init();

  {
    ap2ChannelMap[0] = GFC700Event::GFC700_FLC;
    ap2ChannelMap[1] = GFC700Event::GFC700_VS;
    ap2ChannelMap[2] = GFC700Event::GFC700_APR;
    ap2ChannelMap[3] = GFC700Event::GFC700_NAV;
    ap2ChannelMap[4] = GFC700Event::GFC700_HDG;
    ap2ChannelMap[5] = GFC700Event::GFC700_AP;
    ap2ChannelMap[6] = GFC700Event::GFC700_NOSEDN;
    ap2ChannelMap[7] = GFC700Event::GFC700_NOSEUP;
    ap2ChannelMap[8] = GFC700Event::GFC700_BC;
    ap2ChannelMap[9] = GFC700Event::GFC700_VNV;
    ap2ChannelMap[10] = GFC700Event::GFC700_ALT;
    ap2ChannelMap[11] = GFC700Event::GFC700_FD;
  }

  range_levels = {1,2,5,7,10,12,15,20};


  return true;
}

// destructor
G1000::~G1000()
{
  //
}

// as an example, the setTimeSpec function
bool G1000::setTimeSpec(const TimeSpec& ts)
{
  // a time span of 0 is not acceptable
  if (ts.getValiditySpan() == 0) return false;

  // specify the timespec to the activity
  _display_update_activity.setTimeSpec(ts);
  // or do this with the clock if you have it (don't do both!)
  // myclock.changePeriodAndOffset(ts);

  // do whatever else you need to process this in your model
  // hint: ts.getDtInSeconds()

  // return true if everything is acceptable
  return true;
}

// and the checkTiming function
bool G1000::checkTiming(const vector<int>& i)
{
  if (i.size() == 3) {
    new TimingCheck(_display_update_activity, i[0], i[1], i[2]);
  }
  else if (i.size() == 2) {
    new TimingCheck(_display_update_activity, i[0], i[1]);
  }
  else {
    return false;
  }
  return true;
}

bool G1000::setWindowPositionSize(const vector<int> &p)
{
  if (p.size() != 4) return false;

  g1000_glwindow_.setWindow(p[0], p[1], p[2], p[3]);
  
  return true;
}

// tell DUECA you are prepared
bool G1000::isPrepared()
{
  bool res = true;

  // Example checking a token:
  CHECK_TOKEN(citation_out_read_token_);
  CHECK_TOKEN(secondary_controls_read_token_);
  CHECK_TOKEN(sw_token);
  CHECK_TOKEN(ap2g_token);
  CHECK_TOKEN(ap_token);
  CHECK_TOKEN(apinco_token);
  CHECK_TOKEN(fail_token);
  CHECK_TOKEN(gfc_token);

  if(ap_targets_read_token_ && !ap_targets_read_token_->isValid())
  {
    //W_MOD(getId() << "Disabeling AutopilotTargets channel");
    ap_targets_read_token_.reset();

    // Reset the trigger to exclude this the AutopilotTarget channel
    _display_update_activity.setTrigger(citation_out_read_token_
                                        && secondary_controls_read_token_);
  }

  // return result of checks
  return res;
}

// start the module
void G1000::startModule(const TimeSpec &time)
{
  _display_update_activity.switchOn(time);
}

// stop the module
void G1000::stopModule(const TimeSpec &time)
{
  _display_update_activity.switchOff(time);
}

// this routine contains the main simulation process of your module. You
// should read the input channels here, and calculate and write the
// appropriate output


void G1000::doCalculation(const TimeSpec& ts)
{

  // If drawing is slow, we wil be scheduled fater than we can handle. In this
  // case noScheduledBehind will be larger than zero. In that case, we skip
  // doing something untill we are back on track
  if(_display_update_activity.noScheduledBehind())
  {
    return;
  }

  // We always draw, so we don't care too much for the state.
  getAndCheckState(ts);

  if (ap2g_token.getNumWaitingEvents(ts))
  {
    try
    {
      EventReader<AP2G1000Channel> ap2g_reader(ap2g_token, ts);
      G1000GaugeData&  g1000_data   = g1000_glwindow_.getG1000Data();

      g1000_data.altitude_target = ap2g_reader.data().target_alt;
      g1000_data.target_speed    = ap2g_reader.data().target_speed;
      g1000_data.speed_target    = ap2g_reader.data().target_speed;
      g1000_data.curVerticalState = ap2g_reader.data().ap_vertical;
      g1000_data.curLateralState = ap2g_reader.data().ap_lateral;
      g1000_data.APstate = ap2g_reader.data().APstate;
      g1000_data.target_vs = ap2g_reader.data().target_vs;
      g1000_data.hdg_bug = ap2g_reader.data().hdg_bug;
      g1000_data.ap_armed = ap2g_reader.data().ap_armed;
      g1000_data.alt_hold = ap2g_reader.data().alt_hold;
      g1000_data.ap_flash = ap2g_reader.data().ap_flash;
      g1000_data.pit_flash = ap2g_reader.data().pit_flash;
      g1000_data.rol_flash = ap2g_reader.data().rol_flash;
      g1000_data.active_nav_source = ap2g_reader.data().active_nav_source;
      active_nav_source = ap2g_reader.data().active_nav_source;
      g1000_data.vnav_situation = ap2g_reader.data().vnav_situation;

      g1000_data.altitude_target_vnav = ap2g_reader.data().altitude_target_vnav;

      g1000_data.alts_flash_state = ap2g_reader.data().alts_flash_state;
      g1000_data.alt_flash_state = ap2g_reader.data().alt_flash_state;
      g1000_data.vor_flag_state = ap2g_reader.data().vor_flag_state;
      g1000_data.trueCourse = ap2g_reader.data().course;

      g1000_data.dt = ts.getDtInSeconds();
      g1000_data.active_leg = ap2g_reader.data().active_leg;


    }
    catch (Exception& e)
    {
      W_MOD(classname << ": Error while reading AP2G1000Channel!");
    }
  }

  if (apinco_token.getNumWaitingEvents(ts))
  {
    try
    {
      EventReader<APIncoEvent> apinco(apinco_token, ts);
      G1000GaugeData&  g1000_data   = g1000_glwindow_.getG1000Data();

      g1000_data.fp_name = apinco.data().fp_name;

    }
    catch (Exception& e)
    {
      W_MOD(classname << ": Error while reading apinco Channel!");
    }
  }

  if (fail_token.getNumWaitingEvents(ts))
  {
    try
    {
      EventReader<FailureEvent> fail(fail_token, ts);
      G1000GaugeData&  g1000_data   = g1000_glwindow_.getG1000Data();
      g1000_data.GPS_failure = fail.data().GPS_failure;
      g1000_data.VOR_failure = fail.data().VOR_failure;
      g1000_data.ADC_failure = fail.data().ADC_failure;
      g1000_data.PFD_failure = fail.data().PFD_failure;
      g1000_data.GMU_failure = fail.data().GMU_failure;
      g1000_data.HSI_failure = fail.data().HSI_failure;
      g1000_data.AFCS_pit = fail.data().AFCS_pit;
      g1000_data.AFCS_rol = fail.data().AFCS_rol;
      g1000_data.clogged_sp = fail.data().clogged_sp;
      g1000_data.clogged_pt = fail.data().clogged_pt;
    }
    catch (Exception& e)
    {
      W_MOD(classname << ": Error while reading FailureEvent!");
    }
  }



  try
  {
    StreamReader<CitationOutput> citout_stream_reader(citation_out_read_token_, ts);

    G1000GaugeData&  g1000_data   = g1000_glwindow_.getG1000Data();

    const float* citoutput = citout_stream_reader.data().y;

    g1000_data.pitch   = citoutput[Y_theta];
    g1000_data.roll    = citoutput[Y_phi];
    g1000_data.heading = citoutput[Y_psi];

    heading = 57.295 * citoutput[Y_psi];

    g1000_data.Y_fycg = citoutput[Y_fycg];

    g1000_data.gamma = citoutput[Y_gamma];
    g1000_data.chi   = citoutput[Y_chi];

    g1000_data.altitude = citoutput[Y_h];
    g1000_data.hdot     = citoutput[Y_hdot];

    g1000_data.Vias = tasToIas(citoutput[Y_vtas], g1000_data.altitude);
    g1000_data.Vtas = citoutput[Y_vtas];
    g1000_data.vtasdot = citoutput[Y_vtasdot];

    g1000_data.n1_left   = 0;//citoutput[Y_n1left];
    g1000_data.n1_right  = 0;//citoutput[Y_n1right];
    g1000_data.n2_left   = 0;//citoutput[Y_n2left];
    g1000_data.n2_right  = 0;//citoutput[Y_n2right];
    g1000_data.itt_left  = 650.0;
    g1000_data.itt_right = 650.0;

    g1000_data.rpm_left = citoutput[Y_rpmleft];
    g1000_data.rpm_right = citoutput[Y_rpmright];

    g1000_data.x = citoutput[Y_y];
    g1000_data.y = citoutput[Y_x];

    if(ap_targets_read_token_)
    {
      StreamReader<AutopilotTargets> ap_targets_reader(*ap_targets_read_token_, ts);
      const AutopilotTargets& ap_targets = ap_targets_reader.data();

      g1000_data.Vc_gamma_max = tasToIas(ap_targets.Vx, g1000_data.altitude);

      g1000_data.altitude_target = ap_targets.altitude;
      g1000_data.speed_target    = ap_targets.Vcmd;
      g1000_data.Vmin            = ap_targets.Vmin;
      g1000_data.Vmax            = ap_targets.Vmax;
    }

    g1000_data.trim_enabled = false;

    if(getCurrentState() == SimulationState::HoldCurrent)
    {
      StreamReader<SecondaryControls> secondary_controls_reader(secondary_controls_read_token_, ts);

      const double pla_offset = 0.235619;
      const double pla_range  = 1.0 - pla_offset;
      const double pla = pla_offset + pla_range * secondary_controls_reader.data().throttle_left;

      const double pla_diff = pla - citoutput[Y_pla10];

      const int trim = fabs(pla_diff) < 1e-2 ? 0 : pla_diff / fabs(pla_diff);

      g1000_data.trim_enabled = true;
      g1000_data.trim         = trim;

      g1000_data.tl_left = secondary_controls_reader.data().throttle_left;
      g1000_data.tl_right = secondary_controls_reader.data().throttle_right;

      StreamReader<SecondarySwitches> sw_reader(sw_token, ts);
      g1000_data.gear = sw_reader.data().gear_up;


    }
  }
  catch(Exception& e)
  {
    // Provide some feedback about the exception
    W_MOD(getId()
          << "\t" << classname << ":\t"
          << "Caught an exception while reading one of the G1000 channels");
    W_MOD(getId()
          << "\t" << classname << ":\t"
          << e.what() );
  }

  try
  {
    StreamReader<AutopilotChannel> ap_reader(ap_token, ts);
    G1000GaugeData&  g1000_data   = g1000_glwindow_.getG1000Data();

    g1000_data.theta_ref   = ap_reader.data().theta_ref;
    g1000_data.phi_ref   = ap_reader.data().phi_ref;
    g1000_data.needle_deviation = ap_reader.data().needle_deviation;
    g1000_data.dme = ap_reader.data().dme;
    g1000_data.brg = ap_reader.data().brg;
    g1000_data.course = ap_reader.data().course;
    g1000_data.nav_R = ap_reader.data().nav_R;
    g1000_data.vnav_R = ap_reader.data().vnav_R;
    g1000_data.turn_rate = ap_reader.data().turn_rate;

  }
  catch(Exception& e)
  {
    // Provide some feedback about the exception
    W_MOD(getId()
          << "\t" << classname << ":\t"
          << "Caught an exception while reading one of the G1000 channels");
    W_MOD(getId()
          << "\t" << classname << ":\t"
          << e.what() );
  }

  G1000GaugeData&  g1000_data   = g1000_glwindow_.getG1000Data();

  mouse_down = g1000_data.mouse_down;
  mouse_left = g1000_data.mouse_left;
  if(use_simona_scaling){
    mouse_x = (int)g1000_data.mouse_x/1024.0*1412.0;
    mouse_y = 768 - g1000_data.mouse_y;
    mouse_y = (int)(mouse_y-53.3)/661.0*912.0;
  }else{
    mouse_x = (int)g1000_data.mouse_x;
    mouse_y = 912-(int)g1000_data.mouse_y;
  }


  if(mouse_left){
    D_MOD("G1000 mouse left at: " << mouse_x <<", " << mouse_y);
    index_apc = -1;
    index_apr = -1;

    if(mouse_x>27 && mouse_x<27+49){
      // ap buttons left column
      index_apc = 0;
    }
    if(mouse_x>27+73 && mouse_x<27+73+49){
      // ap buttons left column
      index_apc = 1;
    }

    if((mouse_y-165)%(27+23)<27 && (mouse_y-165)<300 && (mouse_y-165)>0){
      index_apr = (int) (mouse_y-165) / (27+23);
    }

    if(mouse_x >= (212+85*5) && mouse_x <= (212+85*5+49) && mouse_y >= 35 && mouse_y<=(35+29)) {
      msg = GFC700Event::GFC700_CDI;
      active_nav_source +=1;
      if(active_nav_source>3){
        active_nav_source -= 3;
      }
      need_update = true;
    }

    if(mouse_x >= (212+85*6) && mouse_x <= (212+85*6+49) && mouse_y >= 35 && mouse_y<=(35+29)) {
      msg = GFC700Event::GFC700_DME;
      need_update = true;
      dme_status += 1;
      if(dme_status>2){
        dme_status =0;
      }
      if(dme_status<0){
        dme_status = 2;
      }
    }

    if(mouse_left && mouse_x>1261 && mouse_x<1310 && mouse_y>211 && mouse_y<240){
      msg = GFC700Event::GFC700_FPL;
      need_update = true;
    }

    if(mouse_y>510&&mouse_y<530 && mouse_x>57.5 && mouse_x<112.5){
      msg = GFC700Event::GFC700_SYNC;
      need_update = true;
      hdg_select = heading;
    }

    if(index_apc != -1 && index_apr != -1){
      //D_MOD("Button pressed: " << index_apr + 6 * index_apc)
      msg = ap2ChannelMap.at(index_apr + 6 * index_apc);
      need_update = true;
    }

    // if(mouse_y>535&&mouse_y<630 && mouse_x>85 && mouse_x<175){
    //   hdg_select += 1;
    //   no_double_click = true;
    //   msg = GFC700Event::GFC700_NONE;
    //   need_update = true;
    // }
    // if(mouse_y>530&&mouse_y<630 && mouse_x>0 && mouse_x<85){
    //   hdg_select -= 1;
    //   no_double_click = true;
    //   msg = GFC700Event::GFC700_NONE;
    //   need_update = true;
    // }
    //
    // if(mouse_y>530&&mouse_y<630 && mouse_x>(1414-85) && mouse_x<1414){
    //   crs_select += 1;
    //   no_double_click = true;
    //   msg = GFC700Event::GFC700_NONE;
    //   need_update = true;
    // }
    // if(mouse_y>530&&mouse_y<630 && mouse_x>(1414-175) && mouse_x<1414-85){
    //   crs_select -= 1;
    //   no_double_click = true;
    //   msg = GFC700Event::GFC700_NONE;
    //   need_update = true;
    // }

    if(mouse_y>400&&mouse_y<500 && mouse_x>(1414-85) && mouse_x<1414 && zoom_index+1<range_levels.size()){
      zoom_index += 1;
      range = range_levels[zoom_index];
      msg = GFC700Event::GFC700_NONE;
      need_update = true;
    }
    if(mouse_y>400&&mouse_y<500 && mouse_x>(1414-175) && mouse_x<1414-85 && zoom_index>0){
      zoom_index -= 1;
      range = range_levels[zoom_index];
      msg = GFC700Event::GFC700_NONE;
      need_update = true;
    }


    // if(mouse_y>35&&mouse_y<135 && mouse_x>85 && mouse_x<175){
    //   alt_select += 100;
    //   no_double_click = true;
    //   msg = GFC700Event::GFC700_NONE;
    //   need_update = true;
    // }
    // if(mouse_y>35&&mouse_y<135 && mouse_x>0 && mouse_x<85){
    //   alt_select -= 100;
    //   no_double_click = true;
    //   msg = GFC700Event::GFC700_NONE;
    //   need_update = true;
    // }
    g1000_data.mouse_left = false;

  }

  if(!mouse_down){
    acceleration_timer = 0;
  }

  if(mouse_down && !no_double_click){
    D_MOD("G1000 mouse down (no double click) at: " << mouse_x << ", " << mouse_y);

    acceleration_timer += ts.getDtInSeconds();
    if(acceleration_timer>3.5){
      increment = 10 * ts.getDtInSeconds()/0.2;
    } else if(acceleration_timer>1){
      increment = 5 * ts.getDtInSeconds()/0.2;
    }else{
      increment = ts.getDtInSeconds()/0.2;
    }

    if(mouse_y>530&&mouse_y<630 && mouse_x>85 && mouse_x<175){
      hdg_select += increment;
      msg = GFC700Event::GFC700_NONE;
      need_update = true;
    }
    if(mouse_y>530&&mouse_y<630 && mouse_x>0 && mouse_x<85){
      hdg_select -= increment;
      msg = GFC700Event::GFC700_NONE;
      need_update = true;
    }

    if(mouse_y>530&&mouse_y<630 && mouse_x>(1414-85) && mouse_x<1414){
      if(active_nav_source==1){
        crsNav1 += increment;
        need_update = true;
      }else if(active_nav_source==2){
        crsNav2 += increment;
        need_update = true;
      }
      // crs_select += increment;
      msg = GFC700Event::GFC700_NONE;

    }
    if(mouse_y>530&&mouse_y<630 && mouse_x>(1414-175) && mouse_x<1414-85){
      // crs_select -= increment;
      if(active_nav_source==1){
        crsNav1 -= increment;
        need_update = true;
      }else if(active_nav_source==2){
        crsNav2 -= increment;
        need_update = true;
      }
      msg = GFC700Event::GFC700_NONE;
    }
    if(mouse_y>35&&mouse_y<135 && mouse_x>85 && mouse_x<175){
      alt_select += increment*100;
      msg = GFC700Event::GFC700_NONE;
      need_update = true;
    }
    if(mouse_y>35&&mouse_y<135 && mouse_x>0 && mouse_x<85){
      alt_select -= increment*100;
      msg = GFC700Event::GFC700_NONE;
      need_update = true;
    }
  }
  no_double_click = false;

  if(active_nav_source != prev_nav_source){
    need_update = true;
  }
  prev_nav_source = active_nav_source;

  g1000_glwindow_.redraw();

  if(crsNav1>=360){
    crsNav1 -= 360;
  } else if(crsNav1<0){
    crsNav1 += 360;
  }

  if(crsNav2>=360){
    crsNav2 -= 360;
  } else if(crsNav2<0){
    crsNav2 += 360;
  }

  if(active_nav_source==1){
    crs_select = crsNav1;
  }else if(active_nav_source==2){
    crs_select = crsNav2;
  }


  if(crs_select>=360){
    crs_select -= 360;
  } else if(crs_select<0){
    crs_select += 360;
  }

  while(hdg_select>=360){
    hdg_select -= 360;
  }
  while(hdg_select<0){
    hdg_select += 360;
  }

  if(need_update){
    G1000::update_gfc(msg, alt_select, hdg_select, crs_select, range);
    need_update = false;
  }

  // G1000GaugeData&  g1000_data   = g1000_glwindow_.getG1000Data();

  // Some trickery here to extend to msg that we are sending to the bezel.
  // In this way, the 'button animation' is played for longer than just one
  // frame. Currently set to 0.2 seconds. Important: we do only update the
  // GFC event with one frame! That's why we want to reset to msg directly
  // to GFC700_NONE after we've send it!

  if(msg != prev_msg){
    msg_animation = msg;
    animation_timer = 0;
    animation = true;
  }

  if(animation){
    animation_timer += ts.getDtInSeconds();
  }
  if(animation_timer > 0.201){
    animation = false;
    msg_animation = GFC700Event::GFC700_NONE;
  }
  prev_msg = msg;


  if(dme_status != prev_dme_status){
    dme_animation = true;
    dme_animation_timer = 0;
  }
  if(dme_animation){
    dme_animation_timer += ts.getDtInSeconds();
  }
  if(dme_animation_timer > 0.201){
    dme_animation = false;
  }
  prev_dme_status = dme_status;

  g1000_data.GFC_msg = msg_animation;
  g1000_data.dme_status = dme_status;
  g1000_data.dme_animation = dme_animation;
  msg = GFC700Event::GFC700_NONE;


}

void G1000::update_gfc(GFC700Event::msgType msg, int alt_select, int hdg_select, int crs_select, int range){
  EventWriter<GFC700Event> gfc_writer(gfc_token);
  gfc_writer.data().msg = msg;
  gfc_writer.data().alt_select = floor(alt_select/100.0)*100;
  gfc_writer.data().hdg_select = hdg_select;
  gfc_writer.data().crs_select = crs_select;
  gfc_writer.data().range = range;

}


// Make a TypeCreator object for this module, the TypeCreator
// will check in with the scheme-interpreting code, and enable the
// creation of modules of this type
static TypeCreator<G1000> a(G1000::getMyParameterTable());
