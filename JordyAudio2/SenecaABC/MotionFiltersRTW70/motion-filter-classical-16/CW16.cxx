/* ------------------------------------------------------------------   */
/*      item            : CW16.cxx
        made by         : Olaf Stroosma
        Date            : 260712
        category        : header file
        description     : ClassicalWashout filter (RTW 7.0 2007b)
        language        : C++
		documentation   :
*/

#define CW16_cc
#include "CW16.hxx"
#include <iostream>

#include "CW16IO.h"

extern "C" {
#define RTW_GENERATED_S_FUNCTION
#include <simstruc.h>
#include "cw16.h"
}
// the cw16.h file defines the assert macro to be null. This is
// not wat we want, we need assert to check the dimensions of the
// model against those of the DUECA simulation. Therefore:
#undef assert

// rtw40 and rtw41, belonging to Matlab 6.0 and 6.1 respectively, no
// longer have the NSTATES defined
#ifndef NSTATES
# if defined(NCSTATES) && defined(NDSTATES)
#  define NSTATES (NCSTATES + NDSTATES)
# elif defined(NCSTATES)
#  define NSTATES NCSTATES
# elif defined(NDSTATES)
#  define NSTATES NDSTATES
# else
#  error "Neither NSTATES, NCSTATES nor NDSTATES defined"
# endif
#endif

#define MY_MODEL_NAME cw16

extern "C" {
#include <rtw_prototypes.h>
#include <rt_sim.h>
rtModel_cw16 * MY_MODEL_NAME(void);
}
#include <cassert>

#define D_MOD
#define I_MOD
#define W_MOD
#define E_MOD
#include <debug.h>

#define DO_INSTANTIATE
#define INCLUDE_TEMPLATE_SOURCE
#include <CoreCreator.hxx>
#include <MemberCall.hxx>


CW16::CW16():
  S(NULL), cur_par(NULL), par_set_selected(false), sg("CW16")
{
  /* ---------------------------------------------------------------- */
  /* Real-time workshop model initialisation                          */

  // initialise global stuff
  rt_InitInfAndNaN(sizeof(real_T));

  // create the model
  S = createAndInitialiseModel();

  // do one output call, be very careful with these, since they have
  // side effects. State changes after an outputs call cannot undo these
  rtmiOutputs(rtmGetRTWRTModelMethodsInfo(S), 0);

  // good to go
  sg.leaveState();
}

cw16_rtModel *CW16::createAndInitialiseModel(Parameters_cw16 *p)
{
  cw16_rtModel * S = cw16();
  if (S == NULL) {
    E_MOD(" Cannot create model \"cw16\"");
    exit(1);
  }
  if (rtmGetErrorStatus(S) != NULL) {
    E_MOD(" Error creating model \"cw16\"");
    exit(1);
  }

  // further initialisation
  rtmiInitializeSizes(rtmGetRTWRTModelMethodsInfo(S));
  rtmiInitializeSampleTimes(rtmGetRTWRTModelMethodsInfo(S));

  // timing engine
  const char* status = rt_SimInitTimingEngine
    (rtmGetNumSampleTimes(S),    rtmGetStepSize(S),
     rtmGetSampleTimePtr(S),     rtmGetOffsetTimePtr(S),
     rtmGetSampleHitPtr(S),      rtmGetSampleTimeTaskIDPtr(S),
     rtmGetTStart(S),            &rtmGetSimTimeStep(S),
     &rtmGetTimingData(S));
  if (status != NULL) {
    E_MOD(" Failure in timing engine \"cw16\"");
    exit(1);
  }

  // set the parameters, if provided
  // Simulink model handles memory allocation for this,
  // we just copy the required parameters into it
  // default behaviour is using the parameters from the generated code
  if(p) {
    memcpy(S->ModelData.defaultParam, p,
	   sizeof(Parameters_cw16)); 
  } else {} // default

  // integration data
#if NCSTATES > 0
  rt_ODECreateIntegrationData(rtmGetRTWSolverInfo(S));
  if(rtmGetErrorStatus(S) != NULL) {
    E_MOD(" Failure integration data \"cw16\"");
    exit(1);
  }
#endif
  rtmiStart(rtmGetRTWRTModelMethodsInfo(S));
  if (rtmGetErrorStatus(S) != NULL) {
    E_MOD(" Cannot start \"cw16\"");
    exit(1);
  }
  
  return S;
}

void CW16::destroyModel(cw16_rtModel *dS)
{
  rt_SimDestroyTimingEngine(rtmGetTimingData(dS));
#if NCSTATES > 0
  rt_ODEDestroyIntegrationData(rtmGetRTWSolverInfo(dS));
#endif
  rtmiTerminate(rtmGetRTWRTModelMethodsInfo(dS));
}


CW16::~CW16()
{
  // somehow this is never called, but just be thorough

  destroyModel(S);

  // clean up parameters
  for(map<int,Parameters_cw16*>::iterator i = par_sets.begin();
      i != par_sets.end();i++) {
    delete i->second;
    par_sets.erase(i);
  }
}

// Virtual functions from GenericMotionFilter
void CW16::integrate(const VehicleCabMotion& vcm, 
		     const SimulatorMotionState& sms,
		     SimulatorMotionAcceleration& sma, 
		     MotionFilterUserData& fud)
{
  // make sure we're the only ones working with the model
  sg.accessState();

  // fill the input
  real_T* U = reinterpret_cast<real_T*>(rtmGetU(S));
  
  U[U_fx]=vcm.fx;
  U[U_fy]=vcm.fy;
  U[U_fz]=vcm.fz;
  U[U_p]=vcm.p;
  U[U_q]=vcm.q;
  U[U_r]=vcm.r;
  U[U_pd]=vcm.pdot;
  U[U_qd]=vcm.qdot;
  U[U_rd]=vcm.rdot;
  U[U_xS]=sms.x;
  U[U_yS]=sms.y;
  U[U_zS]=sms.z;
  U[U_xSd]=sms.xdot;
  U[U_ySd]=sms.ydot;
  U[U_zSd]=sms.zdot;
  U[U_phiS]=sms.phi;
  U[U_thetaS]=sms.theta;
  U[U_psiS]=sms.psi;
  U[U_pS]=sms.p;
  U[U_qS]=sms.q;
  U[U_rS]=sms.r;

  // do the simulation calculations, one step
  real_T tnext = rt_SimGetNextSampleHit(rtmGetTimingData(S), rtmGetNumSampleTimes(S));
  rtsiSetSolverStopTime(rtmGetRTWSolverInfo(S), tnext);

  // call for an update CW16::
  rtmiUpdate(rtmGetRTWRTModelMethodsInfo(S), 0);

  // do the hit array updates for the single discrete task
  rt_SimUpdateDiscreteTaskSampleHits(rtmGetNumSampleTimes(S),
                                     rtmGetTimingData(S),
                                     rtmGetSampleHitPtr(S),
                                     rtmGetTPtr(S));
    
  // if task 0 is continuous, to an integration step update
  if (rtmGetSampleTime(S, 0) == CONTINUOUS_SAMPLE_TIME) {
    rt_ODEUpdateContinuousStates(rtmGetRTWSolverInfo(S));
  }

  // calculate outputs for continuous or base rate
  // (this is originally called before rtmiUpdate)
  rtmiOutputs(rtmGetRTWRTModelMethodsInfo(S), 0);
  
  // output
  real_T* Y = reinterpret_cast<real_T*>(rtmGetY(S));
  sma.xdotdot = Y[Y_ax];
  sma.ydotdot = Y[Y_ay];
  sma.zdotdot = Y[Y_az];
  sma.pdot = Y[Y_pdot];
  sma.qdot = Y[Y_qdot];
  sma.rdot = Y[Y_rdot];
  
  fud.data[0] = Y[Y_y1];
  fud.data[1] = Y[Y_y2];
  fud.data[2] = Y[Y_y3];
  fud.data[3] = Y[Y_y4];
  fud.data[4] = Y[Y_y5];
  fud.data[5] = Y[Y_y6];

  // we're done
  sg.leaveState();
}

bool CW16::complete()
{
  // check if there are parameter sets defined, but none selected. 
  // in that case, the parameters from the code generation would be used, which
  // probably isn't what the user is expecting. Use the lowest ID by default instead.
  if(!par_sets.empty() && !par_set_selected) {
    int default_par_set = par_sets.begin()->first;
    W_MOD("CW16: parameter sets defined, but none selected, using set " << default_par_set);
    set_param(default_par_set);
  }

  return true;
}

void CW16::reset()
{
  // get lock
  sg.accessState();

  cw16_rtModel* Snew = createAndInitialiseModel(cur_par);
  cw16_rtModel* Sold = S;
  S = Snew;
  destroyModel(Sold);

  // done
  sg.leaveState();
}

void CW16::set_dt(double dt)
{
  // ignore, dt is set in Simulink model, 
  // changing it here is too risky,
  // just do a check
  if(S) {
    if( fabs(dt-S->Timing.stepSize) > 1e-5) {
      W_MOD("CW16 motion filter received incorrect timing step size: " << 
	    dt << " instead of " << S->Timing.stepSize);
    }
  }
}

bool CW16::set_param(int i)
{
  // get lock
  sg.accessState();

  map<int, Parameters_cw16*>::const_iterator p = par_sets.find(i);

  if(p == par_sets.end()) {
    W_MOD("CW16 cannot find parameter set " << i);

    sg.leaveState();

    return false;
  }
  else {
    I_MOD("CW16 setting parameter set " << i);

    // set the current parameters and reset
    cur_par = p->second;

    sg.leaveState();

    this->reset();
  }

  return true;
}

bool CW16::addParameterSet(const ScriptCreatable& ps_in) 
{
  // check if it's actually the right type
#if GENCODEGEN >= 110
  const ScriptCreatableDataHolder<Cw16ParameterSet> *ps =
    dynamic_cast<const ScriptCreatableDataHolder<Cw16ParameterSet> *>(&ps_in);
#else
  const Cw16ParameterSet *ps = dynamic_cast<const Cw16ParameterSet*> (&ps_in);
#endif

  // if it's not, fail
  if(ps == NULL) {
    E_MOD("CW16 received invalid parameter set through add-parameter-set");
    return false;
  }

#if GENCODEGEN >= 110
  return addParameterSet(ps->data());
#else
  return addParameterSet(*ps);
#endif
}

bool CW16::selectParameterSet(const int& i) {
  par_set_selected = true;

  return set_param(i);
}

bool CW16::addParameterSet(const Cw16ParameterSet& ps) 
{
  // convert to Simulink form
  struct Parameters_cw16* p = getNewParameters(ps);

  // get lock
  sg.accessState();
  
  // check if id exists and clean up if needed
  map<int, Parameters_cw16*>::const_iterator iter = par_sets.find(ps.id);

  if(iter == par_sets.end()) {
    // just save it
    par_sets[ps.id] = p;
  } else {
    delete iter->second;

    // save new one
    par_sets[ps.id] = p;
  }
  
  D_MOD("CW16 saved parameter set: " << ps);
  
  // done
  sg.leaveState();

  return true;
}

// parameters to be inserted
const ParameterTable* CW16::getParameterTable()
{
  static const ParameterTable parameter_table[] = {
    { "add-parameter-set",
      new MemberCall<CW16, ScriptCreatable>
      (&CW16::addParameterSet), "add a set of parameters to choose from"},

    { "select-parameter-set",
      new MemberCall<CW16, int>
      (&CW16::selectParameterSet), "select the default set of parameters"},
    
    /* You can extend this table with labels and MemberCall or
       VarProbe pointers to perform calls or insert values into your
       class objects. Please also add a description (c-style string).  

       Note that for efficiency, set_timing_description and
       check_timing_description are pointers to pre-defined strings,
       you can simply enter the descriptive strings in the table. */

    /* The table is closed off with NULL pointers for the variable
       name and MemberCall/VarProbe object. The description is used to
       give an overall description of the module. */
    { NULL, NULL, "configurable motion filter"} };

  return parameter_table;
}

struct Parameters_cw16* CW16::getNewParameters(const Cw16ParameterSet& ps)
{
  struct Parameters_cw16* p = new struct Parameters_cw16;

  // translate the parameters

  // tilt coordination rate limit
  p->Beta_rate = ps.tilt_rate_limit*M_PI/180.0;

  // first order break frequencies
  p->HPomegabphi = ps.roll_hp_wb;
  p->HPomegabpsi = ps.yaw_hp_wb;
  p->HPomegabtheta = ps.pitch_hp_wb;
  p->HPomegabx = ps.surge_hp_wb;
  p->HPomegaby = ps.sway_hp_wb;
  p->HPomegabz = ps.heave_hp_wb;

  // second order break frequencies
  p->HPomeganphi = ps.roll_hp_wn;
  p->HPomeganpsi = ps.yaw_hp_wn;
  p->HPomegantheta = ps.pitch_hp_wn;
  p->HPomeganx = ps.surge_hp_wn;
  p->HPomegany = ps.sway_hp_wn;
  p->HPomeganz = ps.heave_hp_wn;

  // second order damping coefficients
  p->HPzetaphi = ps.roll_hp_z;
  p->HPzetapsi = ps.yaw_hp_z;
  p->HPzetatheta = ps.pitch_hp_z;
  p->HPzetax = ps.surge_hp_z;
  p->HPzetay = ps.sway_hp_z;
  p->HPzetaz = ps.heave_hp_z;

  // these values are experimental, so not tunable from dueca.mod (yet)
  // they are now taken from generated code
  p->Ktilteuler = 0.2;
  p->Ktilteulerrate = 0.5;
  p->Ktiltrate = 5.0;

  // low pass break frequencies, damping and enabling
  p->LPomeganx = ps.surge_lp_wn;
  p->LPomegany = ps.sway_lp_wn;
  p->LPzetax = ps.surge_lp_z;
  p->LPzetay = ps.sway_lp_z;
  p->gainfxtilt = ps.surge_tilt_gain;
  p->gainfytilt = ps.sway_tilt_gain;

  // filter gains
  for(int i=0;i<9;i++) {
    p->kf[i] = 0.0;
    p->kw[i] = 0.0;
  }
  
  p->kf[0] = ps.surge_gain; 
  p->kf[4] = ps.sway_gain;
  p->kf[8] = ps.heave_gain;
  p->kw[0] = ps.roll_gain; 
  p->kw[4] = ps.pitch_gain;
  p->kw[8] = ps.yaw_gain;

  // tilt coordination method
  p->tiltcoordinationmethod = ps.tilt_coordination_method;

  // new for CW16: reference points
  p->xref_ac = ps.ac_ref_pos_x;
  p->yref_ac = ps.ac_ref_pos_y;
  p->zref_ac = ps.ac_ref_pos_z;
  p->xref_filt = ps.filt_ref_pos_x;
  p->yref_filt = ps.filt_ref_pos_y;
  p->zref_filt = ps.filt_ref_pos_z;
  
  // channel selection gains for enable/disable (1 or 0)
  // note the difference with the filter gains!
  p->gainfx = ps.surge_selection_gain;
  p->gainfy = ps.sway_selection_gain;
  p->gainfz = ps.heave_selection_gain;
  p->gainp  = ps.roll_selection_gain;
  p->gainq  = ps.pitch_selection_gain;
  p->gainr  = ps.yaw_selection_gain;
  
  return p;
}

SCM_FEATURES_NOIMPINH(CW16, GenericMotionFilter, 
		      "motion-filter-classical-16");

static CoreCreator<CW16> gs(CW16::getParameterTable());


