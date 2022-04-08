/* ------------------------------------------------------------------   */
/*      item            : MFD.cxx
        made by         : jordy
	from template   : DusimeModuleTemplate.cxx
        template made by: Rene van Paassen
        date            : Fri Apr 24 15:53:44 2020
	category        : body file
        description     :
	changes         : Fri Apr 24 15:53:44 2020 first version
	template changes: 030401 RvP Added template creation comment
	                  060512 RvP Modified token checking code
			  131224 RvP convert snap.data_size to
			         snap.getDataSize()
        language        : C++
        copyright       : (c) 2016 TUDelft-AE-C&S
*/


#define MFD_cxx
// include the definition of the module class
#include "MFD.hxx"
// include the debug writing header, by default, write warning and
// error messages
#define W_MOD
#define E_MOD
#define D_MOD
#include <debug.h>

// include additional files needed for your calculation here
#include "MFDGaugeData.hxx"
//#include <CitStatesOutputs.h>
#include <StatesOutputs.h>
#include <GlobalConstants.hpp>

// the standard package for DUSIME, including template source
#define DO_INSTANTIATE
#include <dusime.h>

#include <vector>
#include <fstream>
#include <Eigen/Dense>
using namespace Eigen;
using namespace std;
using Eigen::MatrixXd;

const char* const MFD::classname = "mfd";

// initial condition/trim table
const IncoTable* MFD::getMyIncoTable()
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
const ParameterTable* MFD::getMyParameterTable()
{
  static const ParameterTable parameter_table[] = {
    { "set-timing",
      new MemberCall<MFD,TimeSpec>
        (&MFD::setTimeSpec), set_timing_description },

    { "check-timing",
      new MemberCall<MFD,vector<int> >
      (&MFD::checkTiming), check_timing_description },

    { "position-and-size",
      new MemberCall<MFD,vector<int> >
      (&MFD::setWindowPositionSize)},

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
MFD::MFD(Entity* e, const char* part, const
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

  fpl_page(false),
  mouse_left(false),
  mouse_x(false),
  mouse_y(false),
  reset_gear(false),

  rudder_bias(0.0),
  gear_pos(0.0),
  eventgeardown(0.0),

  // initialize the data you need for the trim calculation

  // initialize the channel access tokens
  // example
  // my_token(getId(), NameSet(getEntity(), "MyData", part)),
  citation_out_read_token_(getId(), NameSet(getEntity(), "CitationOutput", part)),
  secondary_controls_read_token_(getId(), NameSet(getEntity(), "SecondaryControls", part)),
  ap2g_token(getId(), NameSet(getEntity(), "AP2G1000Channel", part)),
  apinco_token(getId(), NameSet(getEntity(), "APIncoEvent", part)),
  fail_token(getId(), NameSet(getEntity(), "FailureEvent", part)),
  gfc_token(getId(), NameSet(getEntity(), "GFC700Event", part)),
  ap_token(getId(), NameSet(getEntity(), "AutopilotChannel", part)),
  //ma_token(getId(), NameSet(getEntity(), "ManifoldChannel", part)),
  control_token(getId(), NameSet(getEntity(), "ControlEvent", part)),
  trim_inco_token(getId(), NameSet(getEntity(), "Trim_inco", part)),


  ap_targets_read_token_(new APTargetsReadToken(getId(), NameSet(getEntity(),"AutopilotTargets", ""))),

  // activity initialization
  // myclock(),
  _display_update_callback(this, &MFD::doCalculation),
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

bool MFD::complete()
{
  /* All your parameters have been set. You may do extended
     initialisation here. Return false if something is wrong. */

  g1000_glwindow_.openWindow();
  g1000_glwindow_.init();


  return true;
}

// destructor
MFD::~MFD()
{
  //
}

// as an example, the setTimeSpec function
bool MFD::setTimeSpec(const TimeSpec& ts)
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
bool MFD::checkTiming(const vector<int>& i)
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

bool MFD::setWindowPositionSize(const vector<int> &p)
{
  if (p.size() != 4) return false;

  g1000_glwindow_.setWindow(p[0], p[1], p[2], p[3]);

  return true;
}

// tell DUECA you are prepared
bool MFD::isPrepared()
{
  bool res = true;

  // Example checking a token:
  CHECK_TOKEN(citation_out_read_token_);
  CHECK_TOKEN(secondary_controls_read_token_);
  CHECK_TOKEN(ap2g_token);
  CHECK_TOKEN(apinco_token);
  CHECK_TOKEN(fail_token);
  CHECK_TOKEN(gfc_token);
  CHECK_TOKEN(ap_token);
  CHECK_TOKEN(control_token);
  CHECK_TOKEN(trim_inco_token);
  // CHECK_TOKEN(ma_token);

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
void MFD::startModule(const TimeSpec &time)
{
  _display_update_activity.switchOn(time);
}

// stop the module
void MFD::stopModule(const TimeSpec &time)
{
  _display_update_activity.switchOff(time);
}

// this routine contains the main simulation process of your module. You
// should read the input channels here, and calculate and write the
// appropriate output


void MFD::doCalculation(const TimeSpec& ts)
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
      MFDGaugeData&  g1000_data   = g1000_glwindow_.getG1000Data();

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
      g1000_data.active_leg = ap2g_reader.data().active_leg;
      g1000_data.active_vnv_leg = ap2g_reader.data().active_vnv_leg;
    }
    catch (Exception& e)
    {
      W_MOD(classname << ": Error while reading AP2G1000Channel!");
    }
  }

  if (gfc_token.getNumWaitingEvents(ts))
  {
    try
    {
      EventReader<GFC700Event> gfc(gfc_token, ts);
      MFDGaugeData&  g1000_data   = g1000_glwindow_.getG1000Data();
      g1000_data.msg = gfc.data().msg;
      g1000_data.range = gfc.data().range;
    }
    catch (Exception& e)
    {
      W_MOD(classname << ": Error while reading AP2G1000Channel!");
    }
  }else{
    MFDGaugeData&  g1000_data   = g1000_glwindow_.getG1000Data();
    g1000_data.msg = 13;
  }

  if (fail_token.getNumWaitingEvents(ts))
  {
    try
    {
      EventReader<FailureEvent> fail(fail_token, ts);
      MFDGaugeData&  g1000_data   = g1000_glwindow_.getG1000Data();

      g1000_data.GPS_failure = fail.data().GPS_failure;
      g1000_data.VOR_failure = fail.data().VOR_failure;

    }
    catch (Exception& e)
    {
      W_MOD(classname << ": Error while reading AP2G1000Channel!");
    }
  }
//////////////////////
  if (control_token.getNumWaitingEvents(ts))
  {
    try
    {
      EventReader<ControlEvent> control(control_token, ts);
      rudder_bias = control.data().rudder_bias;
      //display_lg_failure = control.data().display_lg_failure;

    }
    catch (Exception& e)
    {
      W_MOD(classname << " caught " << e << " @ " << ts << " when reading ControlEvent" );
    }
  }

/////////////////


  if(trim_inco_token.getNumWaitingEvents(ts))
  {
    try
    {
      EventReader<Trim_inco> trim(trim_inco_token, ts);
      //EventWriter<CitationPilotInput> cpi_trim(cpi_trim_token, ts);

      //D_MOD(classname << " Trim_input from inco: " << trim.data());

      //cpi_trim.data().de = trim.data().de_trim;
      //cpi_trim.data().da = trim.data().da_trim;
      //cpi_trim.data().dr = trim.data().dr_trim;

      // de wordt goed gezet maar da dr en gear niet
      // same problem for flaps?
      // this thing is read by the FCSAdapter - only de is set, the rest is ignored

      //flap_pos = trim.data().flaps_trim; // rad
      gear_pos = trim.data().gear_trim; // 0 or 1
      //I_MOD(classname << " (trim_inco) gear position: " << gear_pos );
      //I_MOD(classname << " (trim_inco) flap position: " << flap_pos/DEG2RAD << " deg" );

      // engine wordt getrimd vanuit trim channel

      //inco_loaded = true;
    }
    catch(Exception& e)
    {
      W_MOD(classname << " caught " << e << " @ " << ts << " (reading Trim_inco)" );
    }
  }






  if (apinco_token.getNumWaitingEvents(ts))
  {
    try
    {
      EventReader<APIncoEvent> apinco(apinco_token, ts);
      MFDGaugeData&  g1000_data   = g1000_glwindow_.getG1000Data();

      g1000_data.fp_name = apinco.data().fp_name;

    }
    catch (Exception& e)
    {
      W_MOD(classname << ": Error while reading AP2G1000Channel!");
    }
  }

  try
  {
    StreamReader<CitationOutput> citout_stream_reader(citation_out_read_token_, ts);

    MFDGaugeData&  g1000_data   = g1000_glwindow_.getG1000Data();

    const float* citoutput = citout_stream_reader.data().y;
    g1000_data.dt = ts.getDtInSeconds();

    g1000_data.pitch   = citoutput[Y_theta];
    g1000_data.roll    = citoutput[Y_phi];
    g1000_data.heading = citoutput[Y_psi];

    g1000_data.gamma = citoutput[Y_gamma];
    g1000_data.chi   = citoutput[Y_chi];

    g1000_data.altitude = citoutput[Y_h];
    g1000_data.hdot     = citoutput[Y_hdot];

    g1000_data.Vias = tasToIas(citoutput[Y_vtas], g1000_data.altitude);
    g1000_data.Vtas = citoutput[Y_vtas];

    g1000_data.n1_left   = 0;//citoutput[Y_n1left];
    g1000_data.n1_right  = 0;//citoutput[Y_n1right];
    g1000_data.n2_left   = 0;//citoutput[Y_n2left];
    g1000_data.n2_right  = 0;//citoutput[Y_n2right];
    g1000_data.itt_left  = 650.0;
    g1000_data.itt_right = 650.0;

    g1000_data.rpm_left = citoutput[Y_rpmleft];
    g1000_data.rpm_right = citoutput[Y_rpmright];
    g1000_data.tl_left = citoutput[Y_pla10];
    g1000_data.tl_right = citoutput[Y_pla20];

    g1000_data.x = citoutput[Y_y];
    g1000_data.y = citoutput[Y_x];

    // landing gear
    // TODO: implement asymmetric and stuck gears
    int ngear = 0;
    int lgear = 0;
    int rgear = 0;

    //display_lg_failure = display_lg_failure;
    //cout << display_lg_failure << endl;
    if(citoutput[Y_gear] == 0.0f){

      //gear = 0;
      ngear = 0;
      lgear = 0;
      rgear = 0;
      //cout << "LG CHECK DEPLOYMENT 0 = UP" << endl;

      // test landing gear display


    }

    else if (citoutput[Y_gear] > 0.999f ){

      //display_lg_failure = 1;
      //cout << display_lg_failure << endl;

      if (rudder_bias != 0){

        //cout << "LG CHECK DEPLOYMENT -1" << endl;
        //gear = -1;
        ngear =  1;
        rgear =  1;
        lgear = -1;


        reset_gear = true;
      }
      else {
        //gear = 1;

        ngear = 1;
        lgear = 1;
        rgear = 1;

        }

      }

   //else if(citoutput[Y_gear] > 0.999f){
      //gear = 1;
      //rudder_bias = rudder_bias;
      //cout << rudder_bias << endl;
      //cout << "LG CHECK DEPLOYMENT TRANSIT = 1" << endl;
      //cout << eventgeardown << endl;
    //}

    else if(citoutput[Y_gear] > 0.0f){
      //gear = 2;
      ngear = 2;
      lgear = 2;
      rgear = 2;





    }


    if(reset_gear == true && citoutput[Y_gear] < 0.999f){

      rudder_bias = 0;
    }



    g1000_data.lgear = lgear;
    g1000_data.ngear = ngear;
    g1000_data.rgear = rgear;
    

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
    MFDGaugeData&  g1000_data   = g1000_glwindow_.getG1000Data();

    g1000_data.theta_ref = ap_reader.data().theta_ref;
    g1000_data.phi_ref   = ap_reader.data().phi_ref;

    g1000_data.brg = ap_reader.data().brg;
    g1000_data.dtk = ap_reader.data().dtk;
    g1000_data.dme = ap_reader.data().dme;

    g1000_data.dist_to_top = ap_reader.data().dist_to_top;
    g1000_data.time_to_bod = ap_reader.data().time_to_bod;
    g1000_data.fpa_req = ap_reader.data().fpa_req;

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

//   try
//   {
//     StreamReaderLatest<ManifoldChannel> ma_reader(ma_token, ts);
//     MFDGaugeData&  g1000_data   = g1000_glwindow_.getG1000Data();
// //
//     g1000_data.map_left   = ma_reader.data().map_l;
//     g1000_data.map_right   = ma_reader.data().map_r;
// //
// }
//   catch(Exception& e)
//   {
//     // Provide some feedback about the exception
//     W_MOD(getId()
//           << "\t" << classname << ":\t"
//           << "Caught an exception while reading Manifold by the MFD");
//     W_MOD(getId()
//           << "\t" << classname << ":\t"
//           << e.what() );
//   }

  // FPL button now only on the PFD
  // MFDGaugeData&  g1000_data   = g1000_glwindow_.getG1000Data();
  // // if(g1000_data.mouse_clicked>old_mouse_clicked){
  // //   D_MOD("G1000 notices button press")
  // // }
  // // old_mouse_clicked = g1000_data.mouse_clicked;
  //
  // mouse_left = g1000_data.mouse_left;
  // mouse_x = g1000_data.mouse_x;
  // mouse_y = g1000_data.mouse_y;
  //
  //
  // if(mouse_left && mouse_x>1261 && mouse_x<1310 && mouse_y>211 && mouse_y<240){
  //   fpl_page = !fpl_page;
  //   g1000_data.mouse_left = false;
  // }
  // g1000_data.fpl_page = fpl_page;
  g1000_glwindow_.redraw();
}



// Make a TypeCreator object for this module, the TypeCreator
// will check in with the scheme-interpreting code, and enable the
// creation of modules of this type
static TypeCreator<MFD> a(MFD::getMyParameterTable());
