/* ------------------------------------------------------------------   */
/*      item            : CvCalculation.cxx
        made by         : hkoolstra
	from template   : DusimeModuleTemplate.cxx
        template made by: Rene van Paassen
        date            : Fri Mar  8 13:03:04 2013
	category        : body file 
        description     : 
	changes         : Fri Mar  8 13:03:04 2013 first version
	template changes: 030401 RvP Added template creation comment
	                  060512 RvP Modified token checking code
        language        : C++
*/

static const char c_id[] =
"$Id: CvCalculation.cxx,v 1.1.1.1 2022/02/17 15:04:28 matteopiras Exp $";

#define CvCalculation_cxx
// include the definition of the module class
#include "CvCalculation.hxx"

// include the debug writing header, by default, write warning and 
// error messages
#define W_MOD
#define E_MOD
#define D_MOD
#include <debug.h>

// include additional files needed for your calculation here

// the standard package for DUSIME, including template source
#define DO_INSTANTIATE
#include <dusime.h>

// class/module name
const char* const CvCalculation::classname = "cv-calculation";

// initial condition/trim table
const IncoTable* CvCalculation::getMyIncoTable()
{
  static IncoTable inco_table[] = {
    // enter pairs of IncoVariable and VarProbe pointers (i.e. 
    // objects made with new), in this table.
    // For example
//    {(new IncoVariable("example", 0.0, 1.0, 0.01))
//     ->forMode(FlightPath, Constraint)
//     ->forMode(Speed, Control),
//     new VarProbe<CvCalculation,double>
//       (REF_MEMBER(&CvCalculation::i_example))}
    
    // always close off with:
    { NULL, NULL} };

  return inco_table;
}

// parameters to be inserted
const ParameterTable* CvCalculation::getMyParameterTable()
{
  static const ParameterTable parameter_table[] = {
    { "set-timing", 
      new MemberCall<CvCalculation,TimeSpec>
        (&CvCalculation::setTimeSpec), set_timing_description },

    { "check-timing", 
      new MemberCall<CvCalculation,vector<int> >
      (&CvCalculation::checkTiming), check_timing_description },

    { "vliegtuigtype",
      new VarProbe<CvCalculation, int >
      (&CvCalculation::vliegtuigtype), 
      "1 = Citation 2= Piper Seneca"},

    { "ARI",
      new VarProbe<CvCalculation, double >
      (&CvCalculation::ARI), 
      "Percentage aileron rudder interconnect"},

    { "Threshold_factor",
      new VarProbe<CvCalculation, double >
      (&CvCalculation::Threshold_factor), 
      "Factor om Thresholds op te hogen"},

    { "Threshold_factor_rate",
      new VarProbe<CvCalculation, double >
      (&CvCalculation::Threshold_factor_rate), 
      "Factor om Rate Thresholds op te hogen"},

    /* You can extend this table with labels and MemberCall or
       VarProbe pointers to perform calls or insert values into your
       class objects. Please also add a description (c-style string).  

       Note that for efficiency, set_timing_description and
       check_timing_description are pointers to pre-defined strings,
       you can simply enter the descriptive strings in the table. */

    /* The table is closed off with NULL pointers for the variable
       name and MemberCall/VarProbe object. The description is used to
       give an overall description of the module. */
    { NULL, NULL, "Calculates minimum lateral control speed"} };

  return parameter_table;
}

// constructor
CvCalculation::CvCalculation(Entity* e, const char* part, const
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
  // state parameters
  database(1.0),
  de0(0.0),
  trim_incr(0.00026),
  trim_tab_pos(0.0),
  Vtas(125),
  de(0),
  da(0),
  dr(0),
  alpha(0.02),
  beta(0),
  nz(1),
  ffl(25),
  ffr(25),
  pb(0),
  rb(0),
  qc(0),
  phi(0),
  theta(0),
  height(10),
  // aircraft constantes
  b(12.5),
  c(2.0569),

  // variabelen parameter analyse
  S1(0.0),
  S2(0.0),
  S3(0.0),
  cov_reset(false),
  cov_reset_new(false),
  para_reset(false),
  para_reset_new(false),
  Data_go(false),


  // data voor threshold exceedance detect
  ref_rho(0.0),
  b_ref(3.0),
  kf_factor(10000.0),
  tijd_1(0),
  tijd_2(0),
  tijd_3(0),
  tijd_alarm(0),
  rij_reset(false),
  Threshold_detect(false),
  reset_uit(false),
  Threshold_param(0),
  temp1(0.0),
  temp2(0.0),
  temp3(0.0),
  i(0),
  ii(0),
  iii(0),
  iiii(0),
  i5(0),


// Variablen Vc bererekning
  p_dot(0.0),
  r_dot(0.0),
  alpha_0(0.03),
  beta_0(0.0),
  Vright(40.0),
  Vright1(40.0),
  Vright2(40.0),
  Vleft(40.0),
  Vleft1(40.0),
  Vleft2(40.0),
  beta_rud_right(0.0),
  beta_rud_left(0.0),
  tau(0.0),
  tau2(0.0),
  pmax(0.0),

// De hoek instellingen TODO
  Phi_req(0.5236), // 30 graden
  maxt(1.5),
 
  Eff_dB(0.0),
  Eff_dNz(0.0),
  dtt(0.0),
  hoek(0.0),
  // De default Citation waarde vliegtuig type 1 
  damin(-0.65 / 3), // TODO hack for lower sensitivity of sidestick
  damax(0.65 / 3),
  drmin(-0.38 ),
  drmax(0.38 ),
  // Waarden voor de joy stick uitsluitend voor testen
  /*damin(-0.13),
  damax(0.13),
  drmin(-0.076),
  drmax(0.068),*/
  C10L(0.0),
  C10R(0.0),
  C9R(0.0),
  C9R1(0.0),
  C9R2(0.0),
  C9L(0.0),
  C9L1(0.0),
  C9L2(0.0),
  C0_r(0.0),
  C0_l(0.0),
  C_b(0.0),
  C1(0.0),
  C2(0.0),
  C3(0.0),
  C4(0.0),
  C5L(0.0),
  C5R(0.0),
  C6(0.0),
  C7(0.0),
  C8(0.0),
  F(0.0),
  F_dot(0.0),
  dV(0.0),
  Vc1(60.0),
  Vc2(60.0),

// demping newton
  Nd(0.5),
// Available rudder at Vc
  Y1(0.0),
  Y2(0.0),
  Y3(0.0),
  Max_SPRT(0.0),
  Max_SPRT_I(0.0),
  Max_SPRT_rate(0.0),
  Max_SPRT_rate_I(0.0),

//adverse_yaw variabelen
  Adverse_yaw(false),
  da_yaw(0.0),
  yaw_demp(0.0),
  yaw_rad(0.0),
  ad_beta1(0.0),
  ad_beta2(0.0),
  ad_beta3(0.0),
  C11R(0.0),
  C11L(0.0),
  dr_eng(0.0),
  beta_s(0.0),
  da_s(0.0),
  dr_s(0.0),
  del1(0.0),
  i6(0),

// variabelen van emergencies
   asym_x(0.0),
   asym_y(0.0),
   asym_z(0.0),
   asym_mass(0.0),
   rudder_power(1.0),
   aileron_power(1.0),
   rudder_bias(0.0),

// intialize de matrices en vectoren voor parameter identificatie en Threshold detect
  P1(10,10),
  P2(10,10),
  P3(10,10),
  P1_bew(10,10),
  P2_bew(10,10),
  P3_bew(10,10),
  P1_reset(10,10),
  P2_reset(10,10),
  P3_reset(10,10),
  I(10,10),
  R(4,4),
  A1(3,3),
  A2(3,2),
  N(10,10),
  Ar(4,4),
  Br(4,2),
  K1(10),
  K2(10),
  K3(10),
  Z(4),
  par(40),
  u(10),
  u1(10),
  u2(10),
  u3(10),
  u_old(10),
  a(40),
  a_bew(40),
  a_bew2(40),
  Z_pred(4),
  error(4),
  V(10),
  V2(2),
  V3_1(3),
  V3_2(3),
  V3_3(3),
  reeks(27),
  reeks2(10),
  SPRT_SL(40),
  SL_update(40),
  SL_update_old(40),
  SPRT_SL_rate(40),
  SPRT_SL_bew(40),
  SL_N(40),
  KF_threshold2(40),
  KF_threshold_rate(40),
  KF_reset(40),
  Xa0(4),
  Xa1(4),
  Ua(2),
  Ya(4),
  Rk1a(4),
  Rk2a(4),
  Rk3a(4),
  Rk4a(4),

  // initialize the data you need for the trim calculation

  // initialize the channel access tokens
  //pc_token(getId(), NameSet(getEntity(), "PrimaryControls", part), 101),
  cpi_token(getId(), NameSet(getEntity(), "CitationPilotInput", part), 101),
  ps_token(getId(), NameSet(getEntity(), "PrimarySwitches", part), 101),
  in_token(getId(), NameSet(getEntity(), "CitationOutput", part),101),
  uit_token(getId(), NameSet(getEntity(), "Vc_Channel", part)),
  //mal_token(getId(), NameSet(getEntity(), "MalfunctionsChannel", part)),

  // activity initialization
  // myclock(),
  cb1(this, &CvCalculation::doCalculation),
  do_calc(getId(), "calculates parameters and minimum roll control speed", &cb1, ps)
{
  // do the actions you need for the simulation

  // connect the triggers for simulation
  // do_calc.setTrigger(*Ticker::single());
  // do the actions you need for the simulation

  // connect the triggers for simulation
 // do_calc.setTrigger(pc_token && ps_token && in_token );
  do_calc.setTrigger(ps_token && in_token && cpi_token);

// dit is de plaats voor de initialisaties van de matices en vectoren

 P1=MatrixXd::Identity(10,10);
 P2=MatrixXd::Identity(10,10);
 P3=MatrixXd::Identity(10,10);
 P1_bew=MatrixXd::Identity(10,10);
 P2_bew=MatrixXd::Identity(10,10);
 P3_bew=MatrixXd::Identity(10,10);
 P1_reset=MatrixXd::Identity(10,10);
 P2_reset=MatrixXd::Identity(10,10);
 P3_reset=MatrixXd::Identity(10,10);
 I=MatrixXd::Identity(10,10);
 R=MatrixXd::Identity(4,4);
 A1=MatrixXd::Zero(3,3);
 A2=MatrixXd::Zero(3,2);
 N=MatrixXd::Identity(10,10);
 Ar=MatrixXd::Zero(4,4);
 Br=MatrixXd::Zero(4,2);
 K1=VectorXd::Zero(10);
 K2=VectorXd::Zero(10);
 K3=VectorXd::Zero(10);
 Z=VectorXd::Zero(4);
 par=VectorXd::Zero(40);
 u=VectorXd::Zero(10);
 u1=VectorXd::Zero(10);
 u2=VectorXd::Zero(10);
 u3=VectorXd::Zero(10);
 u_old=VectorXd::Zero(10);
 a=VectorXd::Zero(40);
 a_bew=VectorXd::Zero(40);
 a_bew2=VectorXd::Zero(40); 
 Z_pred=VectorXd::Zero(4);
 error=VectorXd::Zero(4);
 V=VectorXd::Zero(10);
 V2=VectorXd::Zero(2);
 V3_1=VectorXd::Zero(3);
 V3_2=VectorXd::Zero(3);
 V3_3=VectorXd::Zero(3);
 reeks=VectorXi::Zero(27);
 reeks2=VectorXi::Zero(10);
 SPRT_SL=VectorXd::Zero(40);
 SL_update=VectorXd::Zero(40);
 SL_update_old=VectorXd::Zero(40);
 SPRT_SL_rate=VectorXd::Zero(40);
 SPRT_SL_bew=VectorXd::Zero(40);
 SL_N=VectorXi::Zero(40);
 KF_threshold2=VectorXd::Zero(40);
 KF_threshold_rate=VectorXd::Zero(40);
 KF_reset=VectorXi::Constant(40,50); // eerste 5 seconden geen acties
 Xa0=VectorXd::Zero(4);
 Xa1=VectorXd::Zero(4);
 Ua=VectorXd::Zero(2);
 Ya=VectorXd::Zero(4);
 Rk1a=VectorXd::Zero(4);
 Rk2a=VectorXd::Zero(4);
 Rk3a=VectorXd::Zero(4);
 Rk4a=VectorXd::Zero(4);
}

bool CvCalculation::complete()
{
  /* All your parameters have been set. You may do extended
   initialisation here. Return false if something is wrong. */
 R(0,0) = 3.5e-3;
 R(1,1) = 6.9e-4;
 R(2,2) = 6.9e-6;
 R(3,3) = 6.9e-6;

if (vliegtuigtype==1){
 KF_threshold2<< 380,380,380,380,380,380,380,380,380,380,0,0,0,0,0,0,0,0,0,0,18313,18313,18313,18313,18313,18313,18313,18313,1813,1813,6988,6988,6988,6988,6988,6988,6988,6988,6988,6988;

// Bogus waarde voor citation rate tgroot genoeg om rate resets te voorkomen, echte rates zijn nog niet bekend;
KF_threshold_rate<<18313,18313,18313,18313,18313,18313,18313,18313,1813,1813,18313,18313,18313,18313,18313,18313,18313,18313,1813,1813,18313,18313,18313,18313,18313,18313,18313,18313,1813,1813,18313,18313,18313,18313,18313,18313,18313,18313,1813,1813;

reeks<< 0,2,3,4,5,6,7,8,9,20,22,23,24,25,26,27,28,29,30,32,33,34,35,36,37,38,39;

 N(1,1) = 0.0;
 N(6,6) = 10000.0;
 N(7,7) = 10000.0;
 N(9,9)= 0.0001;

P1<< 0.001669, -2.8815e-09, -0.00098471,  -0.0016374,  -6.1203e-05,  -0.0011966,   0.0043084,  -0.0045925,   -0.0025086,   1.8365e-06,
  -2.8815e-09,  9.9997e-10, -6.2089e-09,  -4.6492e-08, -2.3199e-09,   2.383e-09,  -3.0869e-09,  2.9675e-09,  -1.0072e-07,  3.9513e-11,
  -0.00098471, -6.2089e-09,  0.0037852,   -0.00066189,  0.00076109,   0.00061234, -0.0029491,   0.0032881,   -0.026604,   -6.1842e-06,
  -0.0016374,  -4.6492e-08, -0.00066189,   0.079166,   -0.00089365,  -0.00098232, -0.0088918,   0.006044,    -0.19537,     7.6156e-05,
  -6.1203e-05, -2.3199e-09,  0.00076109,  -0.00089365,  0.00025792,   2.7427e-05, -0.00029192,  0.0003387,   -0.0061128,  -1.2395e-06,
  -0.0011966,   2.383e-09,   0.00061234,  -0.00098232,  2.7427e-05,   0.0014866,  -0.0034002,   0.0038102,    0.017321,   -3.5657e-06,
   0.0043084,  -3.0869e-09, -0.0029491,   -0.0088918,  -0.00029192,  -0.0034002,   0.13766,    -0.138,        0.022843,    5.6192e-06, 
  -0.0045925,   2.9675e-09,  0.0032881,    0.006044,    0.0003387,    0.0038102,  -0.138,       0.13969,     -0.048298,   -4.281e-05,
  -0.0025086,  -1.0072e-07, -0.026604,    -0.19537,    -0.0061128,    0.017321,    0.022843,   -0.048298,    40.408,      -0.0041124,
   1.8365e-06,  3.9513e-11, -6.1842e-06,   7.6156e-05, -1.2395e-06,  -3.5657e-06,  5.6192e-06, -4.281e-05,   -0.0041124,   2.5e-06;

P2<<3.3015e-06, -2.8099e-09, -1.9124e-06,-3.0116e-06, -1.1132e-07, -2.3754e-06,  8.5411e-06, -9.0889e-06,  -2.398e-05,   5.4828e-09,
  -2.8099e-09,  9.8429e-10, -5.8392e-09, -4.3836e-08, -2.2203e-09,  2.1701e-09, -3.2825e-09,  3.4276e-09,  -5.1165e-07,  8.0824e-11,
  -1.9124e-06, -5.8392e-09,  7.6424e-06,  1.3671e-08,  1.5469e-06,  1.1017e-06, -5.954e-06,   6.7596e-06,  -0.00026818,  9.5842e-09,
  -3.0116e-06, -4.3836e-08,  1.3671e-08,  0.00016606, -1.4224e-06, -2.7235e-06, -1.8412e-05,  1.3796e-05,  -0.0019718,   3.105e-07,
  -1.1132e-07, -2.2203e-09,  1.5469e-06, -1.4224e-06,  5.2113e-07,  2.7802e-08, -6.0003e-07,  7.237e-07,   -6.1127e-05,  2.4835e-09,
  -2.3754e-06,  2.1701e-09,  1.1017e-06, -2.7235e-06,  2.7802e-08,  2.9978e-06, -6.6685e-06,  7.3881e-06,   0.00017541, -2.1354e-08,
   8.5411e-06, -3.2825e-09, -5.954e-06,  -1.8412e-05, -6.0003e-07, -6.6685e-06,  0.00027302, -0.00027382,   0.0002369,  -8.2599e-09,
  -9.0889e-06,  3.4276e-09,  6.7596e-06,  1.3796e-05,  7.237e-07,   7.3881e-06, -0.00027382,  0.00027741,  -0.00049633, -4.3768e-08,
  -2.398e-05,  -5.1165e-07, -0.00026818, -0.0019718,  -6.1127e-05,  0.00017541,  0.0002369,  -0.00049633,   0.41214,    -4.1961e-05,
   5.4828e-09,  8.0824e-11,  9.5842e-09,  3.105e-07,   2.4835e-09, -2.1354e-08, -8.2599e-09, -4.3768e-08,  -4.1961e-05,  8.3767e-09;

P3<<3.3015e-06,  -2.8099e-09,  -1.9124e-06,  -3.0116e-06,  -1.1132e-07,  -2.3754e-06,   8.5411e-06,  -9.0889e-06,   -2.398e-05,   5.4828e-09,
  -2.8099e-09,   9.8429e-10,  -5.8392e-09,  -4.3836e-08,  -2.2203e-09,   2.1701e-09,  -3.2825e-09,   3.4276e-09,  -5.1165e-07,   8.0824e-11,
  -1.9124e-06,  -5.8392e-09,   7.6424e-06,   1.3671e-08,   1.5469e-06,   1.1017e-06,  -5.954e-06,    6.7596e-06,  -0.00026818,   9.5842e-09,
  -3.0116e-06,  -4.3836e-08,   1.3671e-08,   0.00016606,  -1.4224e-06,  -2.7235e-06,  -1.8412e-05,   1.3796e-05,  -0.0019718,    3.105e-07,
  -1.1132e-07,  -2.2203e-09,   1.5469e-06,  -1.4224e-06,   5.2113e-07,   2.7802e-08,  -6.0003e-07,   7.237e-07,   -6.1127e-05,   2.4835e-09,
  -2.3754e-06,   2.1701e-09,   1.1017e-06,  -2.7235e-06,   2.7802e-08,   2.9978e-06,  -6.6685e-06,   7.3881e-06,   0.00017541,  -2.1354e-08,
   8.5411e-06,  -3.2825e-09,   -5.954e-06,  -1.8412e-05,  -6.0003e-07,  -6.6685e-06,   0.00027302,  -0.00027382,   0.0002369,   -8.2599e-09,
  -9.0889e-06,   3.4276e-09,   6.7596e-06,   1.3796e-05,   7.237e-07,    7.3881e-06,  -0.00027382,   0.00027741,  -0.00049633,  -4.3768e-08,
  -2.398e-05,   -5.1165e-07,  -0.00026818,   -0.0019718,  -6.1127e-05,   0.00017541,   0.0002369,   -0.00049633,   0.41214,     -4.1961e-05, 
   5.4828e-09,   8.0824e-11,   9.5842e-09,   3.105e-07,    2.4835e-09,  -2.1354e-08,  -8.2599e-09,  -4.3768e-08,  -4.1961e-05,   8.3767e-09;

   a<< -0.021097, 0.022758, -0.016627, -0.0168,   -0.025878, 0.0067777, -0.023389, 0.02772, -0.065752, -2.32e-05,
        0.0,      0.0,       2.0,       0.0,       0.0,      0.0,        0.0,      0.0,      0.0,       0.0,
       -0.049022, 0.0,      -0.34534,   0.082208, -0.12795,  0.0025048,  0.018111,-0.016973, 2.5535,    4.7e-05,
        0.029511, 0.0,      -0.016807, -0.043544, -0.006342,-0.017741,   0.086958,-0.086916,-0.30196,  -1.09e-06;
}

if(vliegtuigtype==2){
 // dr max en min aangepast voor niet lineaire aileron
 damin=-0.6358;
 damax= 0.6358;
 drmin=-0.6109;
 drmax= 0.6109;
 b=11.85;
 c=1.61;
 //  normalisation 5

 N(1,1) = 0.0;
 N(6,6) = 10000.0;
 N(7,7)= 10000.0;
 N(9,9)= 0.001;

/*
 // Thresholds and PKF en preset based op set 1
 KF_threshold2<< 791516.964145650, 0, 15110.4112457280, 52750.5405778678, 551912.517698700, 318525.386050743, 95299.3348240684, 113906.213395134, 840.713399593233, 98723.9706233512, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 14839.3436064064, 0, 497.903948180236, 371.466951705362, 60095.4275947635, 137486.695870298, 6355.88371798726, 3580.75418188506, 147.278283027082, 23941.0818938808, 24599.9352778278, 0, 1672.10478840389, 2598.37198105787, 360479.459838852, 786270.521062900, 43050.4945132972, 35214.1813864950, 427.384899638033, 215897.614155335;

 KF_threshold_rate<< 2440.84924490589, 0, 249.966462028399, 271.922401767275, 5863.58367033065, 3680.60341945783, 1262.96058287651, 1313.83831308951, 27.9086968019825, 1324.35727786152, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 117.013104133082, 0, 15.5278729973081, 12.5375570159161, 204.836396958237, 472.610954741070, 47.3597949181529, 58.4706008157073, 7.13246265035838, 239.973015299243, 464.667129097612, 0, 33.7575916488650, 71.4113625072723, 828.424933436138, 1136.96791615773, 181.592218839220, 167.069243761424, 18.5976940717957, 658.722244937798;

 P1<< 1.63848000594475e-09, -1.33399394180875e-10, 1.89172622342902e-09, 1.50232819247341e-09, 2.35412260002199e-10, 1.64374156844900e-10, -1.38417513913474e-07, 9.97681294938830e-08, 1.08987932851927e-08, -4.84141245827621e-11,
-1.33399394180876e-10, 4.88675296270931e-11, -2.83816304117269e-10, -6.73518201134083e-10, -2.79463559571785e-11, -2.12617719394415e-11, 2.00796591874671e-08, -1.22679777248508e-08, -2.83053004357332e-09, 1.16744263326164e-11, 
1.89172622342899e-09, -2.83816304117223e-10, 1.11271448672692e-08, 2.03721428151950e-09, 1.26588036681007e-09, -5.03416481428379e-11, -2.63809496623072e-07, 2.11225816141770e-07, 1.88128610234594e-08, -7.99444630545131e-11, 
1.50232819247334e-09, -6.73518201134113e-10, 2.03721428151930e-09, 2.31078015863529e-08, -1.37647145639822e-10, 1.12503035277926e-09, -5.09349422188293e-07, 5.01451227018610e-07, 5.61314566380965e-09, -3.54815709010657e-11, 
2.35412260002205e-10, -2.79463559571785e-11, 1.26588036681009e-09, -1.37647145639866e-10, 2.23278434033878e-10, -1.09867998565941e-10, 2.69518928410905e-09, -1.80524539625918e-09, 1.11771989561276e-09, -5.16229013756543e-12, 
1.64374156844896e-10, -2.12617719394458e-11, -5.03416481428885e-11, 1.12503035277936e-09, -1.09867998565934e-10, 3.59208013255241e-10, -1.37709724407437e-07, 1.30823365649180e-07, 1.26993341725119e-09, -5.67307889176170e-12, 
-1.38417513913473e-07, 2.00796591874648e-08, -2.63809496623076e-07, -5.09349422188299e-07, 2.69518928411326e-09, -1.37709724407440e-07, 7.63191817712648e-05, -4.62501912086634e-05, -2.87878665359929e-06, 5.60827344569726e-09, 
9.97681294938825e-08, -1.22679777248573e-08, 2.11225816141748e-07, 5.01451227018610e-07, -1.80524539624950e-09, 1.30823365649175e-07, -4.62501912086640e-05, 7.05421809111647e-05, -1.29579103816056e-06, -1.51062987852682e-09, 
1.08987932851912e-08, -2.83053004357194e-09, 1.88128610234673e-08, 5.61314566380695e-09, 1.11771989561058e-09, 1.26993341725126e-09, -2.87878665359903e-06, -1.29579103816105e-06, 1.08160820854516e-06, -4.78920788043694e-09, 
-4.84141245827538e-11, 1.16744263326101e-11, -7.99444630545508e-11, -3.54815709010513e-11, -5.16229013755574e-12, -5.67307889176125e-12, 5.60827344569559e-09, -1.51062987852444e-09, -4.78920788043701e-09, 2.73550466705335e-11;

 P2<< 9.87614745441404e-08, -3.20743134322032e-09, 2.67168689484626e-07, -2.04296930793923e-09, 3.91226764797033e-08, -1.05927951563085e-08, -2.17460432538552e-06, 2.15301324443317e-06, -1.48309388040089e-09, 5.97452495042266e-12, 
-3.20743134322032e-09, 5.45349380008226e-10, -9.77023648416971e-09, -1.06689911485773e-08, -1.21171386813089e-09, -3.12201981615211e-10, 3.83887967132412e-07, -3.87395498003041e-07, -3.91235805523069e-09, 2.30337528519271e-11, 
2.67168689484626e-07, -9.77023648416974e-09, 1.20041612364281e-06, 5.00279917821274e-08, 1.61062251099085e-07, -3.71726607422262e-08, -1.34362427795894e-05, 1.33952730448321e-05, -1.39323883867169e-08, 7.77808587002583e-11, 
-2.04296930793659e-09, -1.06689911485765e-08, 5.00279917821269e-08, 6.78627964983691e-07, -3.58064995034934e-09, 4.25075018445061e-08, -2.08653454652851e-05, 2.06950552457875e-05, -3.70232242074433e-08, 2.12415979079925e-10, 
3.91226764797042e-08, -1.21171386813083e-09, 1.61062251099088e-07, -3.58064995034792e-09, 2.77966928491521e-08, -9.52450378462038e-09, -8.92548598878113e-07, 8.92127674521782e-07, 2.67710811950797e-09, -1.65175634502285e-11, 
-1.05927951563075e-08, -3.12201981615151e-10, -3.71726607422242e-08, 4.25075018445054e-08, -9.52450378462062e-09, 1.81483580350140e-08, -6.55833474083801e-06, 6.55163348037405e-06, -1.50542607235344e-09, 7.61434816075634e-12, 
-2.17460432538616e-06, 3.83887967132354e-07, -1.34362427795899e-05, -2.08653454652848e-05, -8.92548598878120e-07, -6.55833474083792e-06, 0.00353029579759222, -0.00350038344220582, -1.55280214424758e-06, 6.65880381671154e-10, 
2.15301324443339e-06, -3.87395498003033e-07, 1.33952730448320e-05, 2.06950552457884e-05, 8.92127674521782e-07, 6.55163348037422e-06, -0.00350038344220587, 0.00352442623862392, -1.39377828705128e-06, -1.91004228035794e-09, 
-1.48309388039400e-09, -3.91235805523249e-09, -1.39323883866991e-08, -3.70232242073522e-08, 2.67710811950818e-09, -1.50542607234790e-09, -1.55280214424936e-06, -1.39377828704668e-06, 1.96767636050817e-06, -9.94170525856345e-09, 
5.97452495041320e-12, 2.30337528519350e-11, 7.77808587002271e-11, 2.12415979079599e-10, -1.65175634502255e-11, 7.61434816073178e-12, 6.65880381676369e-10, -1.91004228037921e-09, -9.94170525856302e-09, 5.63362180351011e-11;

 P3<< 1.14551283228706e-08, -4.87074069419361e-10, 3.95678809273261e-08, 3.63886643411473e-09, 4.80183652117214e-09, -2.19113940420830e-09, 1.82741254342236e-07, -1.78015406274725e-07, 3.43776364880069e-09, -1.86942288997897e-11, 
-4.87074069418478e-10, 1.57023133937938e-10, -1.91814879803685e-09, -8.03520873256715e-10, -1.98911935633168e-10, -8.18831242555681e-11, 7.36917056917174e-08, -7.51080076124586e-08, -1.60219400063225e-09, 8.91044272679100e-12, 
3.95678809273279e-08, -1.91814879804128e-09, 1.69236321283443e-07, 2.76855565303259e-08, 1.85637458186444e-08, -4.26623728321869e-09, -1.40648243919656e-06, 1.43059347334240e-06, 7.75305706549776e-09, -4.45684290817580e-11, 
3.63886643411840e-09, -8.03520873256935e-10, 2.76855565303435e-08, 8.17669224132012e-08, 1.20376226102294e-09, 9.69391316596225e-09, -5.15459688734098e-06, 5.16147168406876e-06, -8.47684132912233e-09, 4.09675084123538e-11, 
4.80183652117241e-09, -1.98911935633181e-10, 1.85637458186451e-08, 1.20376226102295e-09, 2.91044868036010e-09, -1.30684652872293e-09, 8.97210101811491e-08, -8.66648487680944e-08, 2.12808683069639e-09, -1.09228055810541e-11, 
-2.19113940420849e-09, -8.18831242554580e-11, -4.26623728321992e-09, 9.69391316596280e-09, -1.30684652872282e-09, 3.70188777859846e-09, -1.56098087742866e-06, 1.56340828171381e-06, -1.79633572265780e-09, 8.25626211092451e-12, 
1.82741254342271e-07, 7.36917056916681e-08, -1.40648243919640e-06, -5.15459688734114e-06, 8.97210101810913e-08, -1.56098087742863e-06, 0.000996237643565977, -0.000979057880752260, -8.84841010179440e-07, -1.13321858690082e-09, 
-1.78015406274735e-07, -7.51080076124076e-08, 1.43059347334217e-06, 5.16147168406887e-06, -8.66648487680539e-08, 1.56340828171381e-06, -0.000979057880752258, 0.000999976741101433, -1.85510158052052e-06, 2.78202078822109e-09, 
3.43776364883289e-09, -1.60219400063188e-09, 7.75305706565732e-09, -8.47684132911076e-09, 2.12808683069507e-09, -1.79633572266274e-09, -8.84841010177169e-07, -1.85510158052338e-06, 9.29782910905000e-07, -3.95997212205474e-09, 
-1.86942288999824e-11, 8.91044272678942e-12, -4.45684290827010e-11, 4.09675084122972e-11, -1.09228055810485e-11, 8.25626211095523e-12, -1.13321858691661e-09, 2.78202078823699e-09, -3.95997212205515e-09, 2.08237186582425e-11;

a<< -0.0308772883231833, 0.0671973675723898, -0.0159802636974651, 0.0122979915420684, -0.000347103917732944, 0.0101756992289666, -0.181355660173267, 0.175105439014018, -0.00480238095895971, 2.79201888493636e-05, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, -0.208256986442760, 0, -0.760143970590263, 0.286681808798022, -0.130324749905777, 0.0191976590520059, 14.8789199897326, -14.8234135142840, 0.0104274791598574, -6.15521915100737e-05, 0.0906440828477609, 0, -0.0205182423444698, -0.160423098461244, 0.0119238468937957, -0.0600258884563090, 28.1537831990120, -28.1793288405871, 0.00506744239261858, -2.34095779802381e-05;

*/

// Alterantieve  presets  85 knots
// Nieuwe set, de 85 knots set 

//KF Threshold no 3, 6 en 21 ( all base 1) aangepast door *10
// Aanpassing 3 voor normale operaties 6,7,8 en 21 ivm vliegen met eng failure


 KF_threshold2<< 2242271.08567350, 0, 249692.984286332, 187803.597032117, 2253445.75276500, 4615193.30195690, 1169465.30321854, 1089052.94136798, 3318.79887084696, 162214.887919472, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 841709.626237524, 0, 2990.49215869357, 2955.05188065918, 453393.680622072, 614873.151879246, 14315.7545009661, 14655.2724316482, 94.9897189459934, 19248.4607302424, 124983.170580703, 0, 17679.7627731089, 3194.66769935484, 999973.542824151, 1245125.82950538, 34133.7283140863, 31454.5442073502, 403.967780778700, 69156.7434376117;

KF_threshold_rate<< 6037.45846521588, 0, 528.091235643929, 574.881474386551, 20594.1256809355, 7149.30744326587, 2174.19964864665, 2162.48868264668, 59.1423758951110, 1762.91542076309, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 303.956257954613, 0, 25.5037718701922, 36.0141856123303, 960.671728130533, 595.095988766905, 59.3749925635470, 99.3260800292633, 4.74948594729967, 112.445882863100, 1219.60023166509, 0, 141.411665045944, 105.112961197808, 4791.05900113938, 1240.71034961306, 269.402038130864, 441.387206993596, 17.2600122225914, 501.455801948795;

a<<-0.0280852584434944, 0.0636857218461411, -0.0145745213979791, 0.0100634268280214, -0.000138143504902897, 0.00882462127824329, 0.108125661002141, -0.0875270756400517, 0.000833434368083792, -9.99786910500338e-06, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, -0.224728054425402, 0, -0.729917038145103, 0.334997342249588, -0.125907442215103, 0.0236118876504478, 15.6669034088039, -15.8099530767972, 0.0109426231237286, 3.12144536164516e-05, 0.0696810946996236, 0, -0.0745039795089068, -0.149571862057628, 0.00877485788330483, -0.0548130410417611, 23.8205217994665, -23.8616536159093, 0.0148989056238146, -7.57018873506680e-05;


P1<<2.12526880979485e-09, -2.01302913690794e-10, 1.24987314359267e-09, 1.15726266513158e-09, 2.18359360610688e-10, 6.13727927652202e-12, -1.60575468510951e-08, 1.60553918419190e-08, -1.57779254359540e-09, 9.02963885796799e-12, 
-2.01302913690787e-10, 1.19143012989183e-10, -3.83694050646643e-10, -1.73001378937404e-09, -2.72008239921233e-11, -5.46433988325522e-11, 2.48791319327714e-08, -2.39719438069782e-08, -9.77975182826113e-11, 1.05182295302669e-12, 
1.24987314359274e-09, -3.83694050646646e-10, 1.23774287297742e-08, 7.50019443089923e-09, 7.48384805092419e-10, 1.00020048565796e-09, -6.07098232372523e-07, 6.03975774524699e-07, 8.91551530797952e-10, -6.88918131441685e-12, 
1.15726266513154e-09, -1.73001378937399e-09, 7.50019443089930e-09, 5.93198902051391e-08, -2.40315921477295e-10, 2.45827018835735e-09, -1.13180631664373e-06, 1.14367942167825e-06, -5.03792280931450e-09, 2.81649518617364e-11, 
2.18359360610695e-10, -2.72008239921263e-11, 7.48384805092428e-10, -2.40315921477241e-10, 1.74182891415604e-10, -1.63899835396465e-10, 3.63622522125797e-08, -3.70890006560019e-08, 4.45368847367399e-10, -2.86981610717755e-12, 
6.13727927652374e-12, -5.46433988325504e-11, 1.00020048565790e-09, 2.45827018835741e-09, -1.63899835396467e-10, 8.71128283139129e-10, -3.50022660596439e-07, 3.51061913522744e-07, -1.45770816972442e-09, 8.99632002150632e-12, 
-1.60575468510927e-08, 2.48791319327681e-08, -6.07098232372527e-07, -1.13180631664379e-06, 3.63622522125846e-08, -3.50022660596439e-07, 0.000160454314673047, -0.000146473824405132, -8.51247969591856e-07, 8.90278820081756e-10, 
1.60553918419275e-08, -2.39719438069802e-08, 6.03975774524666e-07, 1.14367942167828e-06, -3.70890006559961e-08, 3.51061913522742e-07, -0.000146473824405138, 0.000160619476066021, -2.00106775791788e-06, 8.21987232473460e-09, 
-1.57779254359597e-09, -9.77975182824674e-11, 8.91551530798685e-10, -5.03792280931519e-09, 4.45368847366960e-10, -1.45770816972481e-09, -8.51247969591753e-07, -2.00106775791787e-06, 3.53242396521335e-06, -2.14570159782615e-08, 
9.02963885797102e-12, 1.05182295302623e-12, -6.88918131442134e-12, 2.81649518617389e-11, -2.86981610717554e-12, 8.99632002150786e-12, 8.90278820082516e-10, 8.21987232473567e-09, -2.14570159782616e-08, 1.34361719632753e-10;

P2<<5.62769412880536e-08, -9.20468068502002e-10, 6.28113640911577e-08, -4.99860254900488e-08, 1.30894851520319e-08, -8.00013478325295e-09, 1.20253081827829e-06, -1.12932316126292e-06, -3.73718640143792e-08, 2.04454478419765e-10, 
-9.20468068501918e-10, 6.38875965895869e-10, -1.87820535101264e-09, -1.17780448499667e-08, -1.32438514877487e-10, -3.22816054763489e-10, 1.94095684921161e-07, -1.93572647923692e-07, 1.07140957147646e-09, 5.44092864240106e-14, 
6.28113640911582e-08, -1.87820535101248e-09, 5.65744537387132e-07, -8.33886289030632e-09, 4.11759244191576e-08, 9.90519804697994e-09, -1.33071786731347e-05, 1.33700471623625e-05, -7.13220145169289e-08, 3.80895499904813e-10, 
-4.99860254900491e-08, -1.17780448499663e-08, -8.33886289030825e-09, 8.64515029256726e-07, -2.58018690455494e-08, 5.82618826128131e-08, -2.29602166137024e-05, 2.33470468019951e-05, 4.66592868231797e-08, -1.77188080772004e-10, 
1.30894851520321e-08, -1.32438514877489e-10, 4.11759244191569e-08, -2.58018690455479e-08, 8.25556717606641e-09, -5.54434249232916e-09, 7.76373302297896e-07, -7.92817136152782e-07, 1.99859580330195e-09, -1.06391916358753e-11, 
-8.00013478325293e-09, -3.22816054763461e-10, 9.90519804698029e-09, 5.82618826128122e-08, -5.54434249232945e-09, 2.12243213364805e-08, -8.56171370825601e-06, 8.60738075645873e-06, -7.49610314217738e-09, 3.50034507814993e-11, 
1.20253081827842e-06, 1.94095684921152e-07, -1.33071786731345e-05, -2.29602166137025e-05, 7.76373302297960e-07, -8.56171370825589e-06, 0.00393267430747739, -0.00387493630970564, -4.61401626866619e-06, 5.36488660729256e-09, 
-1.12932316126286e-06, -1.93572647923670e-07, 1.33700471623620e-05, 2.33470468019948e-05, -7.92817136152883e-07, 8.60738075645892e-06, -0.00387493630970548, 0.00396297808279679, -9.54170283237025e-06, 2.97302907807183e-08, 
-3.73718640143931e-08, 1.07140957147470e-09, -7.13220145168943e-08, 4.66592868231677e-08, 1.99859580330156e-09, -7.49610314217502e-09, -4.61401626867163e-06, -9.54170283236781e-06, 2.01056453432173e-05, -1.16858204186282e-07, 
2.04454478419834e-10, 5.44092864330551e-14, 3.80895499904599e-10, -1.77188080772015e-10, -1.06391916358728e-11, 3.50034507814758e-11, 5.36488660732486e-09, 2.97302907807018e-08, -1.16858204186282e-07, 7.03811478992085e-10; 

P3<<7.24716337044950e-09, -5.73418538725842e-10, 4.02883251061622e-09, 4.86391281775315e-09, 5.36019713325815e-10, -4.97027840154639e-11, -2.83934057449698e-08, 3.76850249053742e-08, -5.86852471358806e-09, 3.38138090670014e-11, 
-5.73418538725889e-10, 2.57004853506886e-10, -1.02250888352314e-09, -5.27752485435706e-09, -7.84913930391683e-12, -3.31208275249443e-10, 1.49286754913156e-07, -1.49743945238499e-07, -1.22460123052285e-10, 2.16462841000274e-12, 
4.02883251061618e-09, -1.02250888352317e-09, 3.38701801070822e-08, 2.67978317752873e-08, 1.79579249971499e-09, 3.30391086484216e-09, -1.91564448650127e-06, 1.91601045104993e-06, 8.42458345324702e-09, -5.25515874327347e-11, 
4.86391281775329e-09, -5.27752485435693e-09, 2.67978317752856e-08, 1.99752567806844e-07, -2.00804565646480e-09, 1.50828343107838e-08, -6.76616586396965e-06, 6.84866212320643e-06, 2.66927827592662e-08, -1.83588031350606e-10, 
5.36019713325856e-10, -7.84913930391919e-12, 1.79579249971506e-09, -2.00804565646463e-09, 6.32042268064244e-10, -1.22805556854124e-09, 4.18250269255929e-07, -4.23512087159605e-07, 1.61028018143963e-09, -8.10533241060504e-12, 
-4.97027840154666e-11, -3.31208275249439e-10, 3.30391086484215e-09, 1.50828343107833e-08, -1.22805556854122e-09, 5.57325264946680e-09, -2.26433212350340e-06, 2.28245651983805e-06, -3.27227610424162e-09, 1.30660614681410e-11, 
-2.83934057449623e-08, 1.49286754913159e-07, -1.91564448650119e-06, -6.76616586396973e-06, 4.18250269255922e-07, -2.26433212350351e-06, 0.00100962086764748, -0.000998464955169278, 7.29011861516403e-08, -4.22991587724055e-09, 
3.76850249053853e-08, -1.49743945238504e-07, 1.91601045104998e-06, 6.84866212320640e-06, -4.23512087159581e-07, 2.28245651983804e-06, -0.000998464955169269, 0.00102393433724418, -2.25632225494332e-06, 4.74706279552323e-09, 
-5.86852471358839e-09, -1.22460123052528e-10, 8.42458345324644e-09, 2.66927827592685e-08, 1.61028018143973e-09, -3.27227610424118e-09, 7.29011861515966e-08, -2.25632225494329e-06, 5.09361824321377e-06, -3.08197245332542e-08, 
3.38138090670022e-11, 2.16462841000388e-12, -5.25515874327299e-11, -1.83588031350608e-10, -8.10533241060467e-12, 1.30660614681379e-11, -4.22991587724034e-09, 4.74706279552329e-09, -3.08197245332522e-08, 1.93178841841407e-10;



reeks<< 0, 2, 3, 4, 5, 6, 7, 8, 9, 20, 22, 23, 24, 25, 26, 27, 28, 29, 30, 32, 33, 34, 35, 36, 37, 38, 39;

// De Individule Threshold waarden zijn gemeten actuele waarden en moeten vermenigvuldig d worden met een factor die uit de config file komt 
KF_threshold2 *= Threshold_factor;
KF_threshold_rate *= Threshold_factor_rate;

// De P reset waarden zijn gerelateerd aan de grootte van de parameter (hjk), behalve door dFn (=8) en dF (=9) afhankelijke variabelen
// die worden respectievelijk 10 of blijven 1.
for(i=0;i<8;i++){  
	P1_reset(i,i)=0.25*a(i)*a(i)+1e-9;
	P2_reset(i,i)=0.25*a(i+20)*a(i+20)+1e-9;
	P3_reset(i,i)=0.25*a(i+30)*a(i+30)+1e-9;
}
P1_reset(8,8)=10;
P2_reset(8,8)=10;
P3_reset(8,8)=10;

}

P1_bew=P1;
P2_bew=P2;
P3_bew=P3;
a_bew=a;
a_bew2=a;
  return true;
}

// destructor  pc_token(getId() ,  NameSet(getEntity() ,  "PrimaryControls" ,  part) ,  101) , 
CvCalculation::~CvCalculation()
{
  //
}

// as an example ,  the setTimeSpec function
bool CvCalculation::setTimeSpec(const TimeSpec& ts)
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
bool CvCalculation::checkTiming(const vector<int>& i)
{
  if (i.size() == 3) {
  new TimingCheck(do_calc ,  i[0] ,  i[1] ,  i[2]);
  }
  else if (i.size() == 2) {
  new TimingCheck(do_calc ,  i[0] ,  i[1]);
  } 
  else {
  return false;
  }
  return true;
}

// tell DUECA you are prepared
bool CvCalculation::isPrepared()
{

  bool res = in_token.isValid() && cpi_token.isValid() && ps_token.isValid() && uit_token.isValid(); //mal_token.isValid()

  if (!res) {
  W_MOD(getId() << '/' << classname << " not prepared ,  flags=" <<
	  in_token.isValid() << cpi_token.isValid()<< ps_token.isValid()<<uit_token.isValid() ); //mal_token.isValid()
  }

  // return result of checks
  return res;
}

// start the module
void CvCalculation::startModule(const TimeSpec &time)
{
  do_calc.switchOn(time);
}

// stop the module
void CvCalculation::stopModule(const TimeSpec &time)
{
  do_calc.switchOff(time);
}

// fill a snapshot with state data. You may remove this method (and the
// declaration) if you specified to the SimulationModule that the size of 
// state snapshots is zero
void CvCalculation::fillSnapshot(const TimeSpec& ts ,  
          Snapshot& snap ,  bool from_trim)
{
  // The most efficient way of filling a snapshot is with an AmorphStore
  // object.
  AmorphStore s(snap.accessData() ,  snap.getDataSize());

  if (from_trim) {
  // use packData(s ,  trim_state_variable1); ... to pack your state into 
  // the snapshot
  }
  else {
  // this is a snapshot from the running simulation. Dusime takes care 
  // that no other snapshot is taken at the same time ,  so you can safely
  // pack the data you copied into (or left into) the snapshot state 
  // variables in here
  // use packData(s ,  snapshot_state_variable1); ...
  }
}

// reload from a snapshot. You may remove this method (and the
// declaration) if you specified to the SimulationModule that the size of 
// state snapshots is zero
void CvCalculation::loadSnapshot(const TimeSpec& t ,  const Snapshot& snap)
{
  // access the data in the snapshot with an P1=P1_bew;AmorphReStore object
  AmorphReStore s(snap.data ,  snap.data_size);

  // use unPackData(s ,  real_state_variable1 ); ... to unpack the data 
  // from the snapshot. 
  // You can safely do this ,  while snapshot loading is going on the 
  // simulation is in HoldCurrent or the activity is stopped. 
}

// this routine contains the main simulation process of your module. You 
// should read the input channels here ,  and calculate and write the 
// appropriate output
void CvCalculation::doCalculation(const TimeSpec& ts)
	{
  	// check the state we are supposed to be in
	switch (getAndCheckState(ts))
		{
		case SimulationState::HoldCurrent:
			{
			// reset de KF naar minimaal 2 seconden ; meer indien er een covariance reset is (500)
			// In Hold current altijd SRT's op nul zetten
			KF_reset=VectorXi::Constant(40,50);
			SPRT_SL=VectorXd::Zero(40);
			SPRT_SL_rate=VectorXd::Zero(40);
			SPRT_SL_bew=VectorXd::Zero(40);
			Threshold_detect=false;
/*
			if (mal_token.getNumWaitingEvents(ts))
				{
				try
					{
					EventReader<MalfunctionsChannel> mal(mal_token, ts);
	
					// De failuere waarden worden ingelezen voor aanpassen a() aan failure waarden
			
					if (asym_x != mal.data().asym_x)
						{
						asym_x = mal.data().asym_x;
						D_MOD(classname<< " Reset asym x: "<< asym_x <<endl);
					}
					if (asym_y != mal.data().asym_y)
						{
						asym_y = mal.data().asym_y;
						D_MOD(classname<< " Reset asym y: "<< asym_y <<endl);
					}
					if (asym_z != mal.data().asym_z)
						{
						asym_z = mal.data().asym_z;
						D_MOD(classname<< " Reset asym z: "<< asym_z <<endl);
					}
					if (asym_mass != mal.data().asym_max)
						{
						asym_mass = mal.data().asym_max;
						D_MOD(classname<< " Reset asym mass: "<< asym_mass <<endl);
					}
		
					if (rudder_power != mal.data().rudder_power)
						{
						rudder_power = mal.data().rudder_power;
						D_MOD(classname<< " Reset rudder power: "<< rudder_power <<endl);
					}
					if (aileron_power != mal.data().aileron_power)
						{
						aileron_power = mal.data().aileron_power;
						D_MOD(classname<< " Reset aileron power: "<< aileron_power <<endl);
					}
			
					if (reset_uit!= mal.data().reset_uit)
						{
						reset_uit=mal.data().reset_uit;
						D_MOD(classname<< " Reset is set to: "<< reset_uit <<endl);
					}
				
					if (Phi_req != mal.data().Phi_req * 0.017453)
						{
						Phi_req=mal.data().Phi_req * 0.017453;
						D_MOD(classname<< "VC: Resetting Phi_req to:"<< Phi_req/0.017453 << endl);
					}
	
					if (maxt != mal.data().maxt)
						{
						maxt=mal.data().maxt;
						D_MOD(classname<< "VC: Resetting maxt to:"<< maxt << endl);
					}
	
					/*
					voor test zijn database 1 en 2 nog gelijk. 
					Alleen aanpassen parameters niet de covariance vd parameters
					Hier moeten databases van preset failure kunnen worden geladen
					* /
					if (database != mal.data().database)
						{
						// nieuwe database moet worden geladen
						database=mal.data().database;
					

						// standaard database 
						if (database==1 || database==3)
							{
							a=a_bew;
							if (database==1){ D_MOD( "Resetting to  standard database:"<< database<< " Vc display=on" << endl)}
							if (database==3){ D_MOD( "Resetting to  standard database:"<< database<< " Vc display=off" << endl)}
							P1=P1_bew; P2=P2_bew; P3=P3_bew;
				
							Vright=40.0; Vright1=40.0; Vright2=40.0;
							Vleft=40.0;  Vleft1=40.0;  Vleft2=40.0;
							a_bew2=a;
						} 	
				
						// database aanpassen aan emergency
						if (database==2 || database==4)
							{
							a=a_bew;
				
							// Aanpassing aan lateral asymmetry alleen voor PA34
							if (vliegtuigtype==2)
								{
								a(8)=   -0.2 *asym_y*asym_mass/400 ;
								a(28)= 3.736 *asym_y*asym_mass/400 ;
								a(38)= 0.2355242564 *asym_y*asym_mass/400 ;
							}
							// aanpassen aan control effectiveness
							a(4)*=aileron_power;
							a(24)*=aileron_power;
							a(34)*=aileron_power;
							a(5)*=rudder_power;
							a(25)*=rudder_power;
							a(35)*=rudder_power;
		
							// aanpassen aan rudder hardover
							if (abs(rudder_bias)>0)
								{
								// rudder power wordt naar nul
								a(5)=0;
								a(25)=0;
								a(35)=0;
								// Rudder bias converteren naar radialen
								a(9)=a_bew(5)*rudder_bias*0.0175;
								a(29)=a_bew(25)*rudder_bias*0.0175;
								a(39)=a_bew(35)*rudder_bias*0.0175;
							}
		
							if (database==2){ D_MOD( "Resetting to emergency values:"<< database<< " Vc display is on" << endl);}
							if (database==4){ D_MOD( "Resetting to emergency values:"<< database<< " Vc display is off" << endl);}
							P1=P1_bew; P2=P2_bew; P3=P3_bew;
							Vright=40.0; Vright1=40.0; Vright2=40.0;
							Vleft=40.0;  Vleft1=40.0;  Vleft2=40.0;
							a_bew2=a;  // de eventueel gewijzigde a met de fout
						}
					}
			
			
					cov_reset_new = mal.data().reset_cov;
					if (cov_reset_new != cov_reset)
						{
						D_MOD( "VC: Reseting Covariance_1:"<< cov_reset<< endl);
						cov_reset = cov_reset_new;
						P1=P1_bew;
						P2=P2_bew;
						P3=P3_bew;
						SPRT_SL=SPRT_SL*0;
						SPRT_SL_rate=SPRT_SL_rate*0;
						SPRT_SL_bew=SPRT_SL_bew*0;
						Threshold_detect=false;
						// Naar 500 ipv 50 bij covariance reset
						for (i=0;i<40;i++){KF_reset(i)=500;}
						Threshold_detect=false;
						D_MOD( "VC: Reseting Covariance_2:"<< cov_reset<< endl);
					}
		
			
					para_reset_new = mal.data().reset_para;
					if (para_reset_new != para_reset)
						{
						D_MOD( "VC: Reseting Parameters_1:"<< para_reset<< endl);
						para_reset= para_reset_new;
						a=a_bew2;   // Niet de eerste set maar de set met eventueel aangepaste emergency
						D_MOD( "VC: Reseting Parameters_2:"<< para_reset<< endl);
						Vright=40.0;
						Vright1=40.0;
						Vright2=40.0;
						Vleft=40.0;
						Vleft1=40.0;
						Vleft2=40.0;
						D_MOD(" VC: Resettting Vc s  "<<endl);	
					}
	
				}
				catch (Exception& e)
					{
					cout << classname <<  ": Error while reading malfunctions channel" << endl;
				} 
			}  // Einde checken mal channel
*/


			// only repeat the output ,  do not change the model state
			StreamWriter<Vc_Channel>VcWrite(uit_token, ts);
			VcWrite.data().Threshold=false;  
			VcWrite.data().Reduce_left=false;	
			VcWrite.data().Reduce_right=false;
			VcWrite.data().Vc_1 = 0.0; //
			VcWrite.data().Vc_2 = 0.0; 
	
			break;
  		} // einde hold
 		
		case SimulationState::Replay:
 		
		case SimulationState::Advance:
			{
/*
			if (mal_token.getNumWaitingEvents(ts))
				{
				try
					{
					EventReader<MalfunctionsChannel> mal(mal_token, ts);
	
					if (reset_uit!= mal.data().reset_uit)
						{
						reset_uit=mal.data().reset_uit;
						D_MOD( " Reset is set to: "<< reset_uit <<endl);
					}
		
					cov_reset_new = mal.data().reset_cov;
					if (cov_reset_new != cov_reset)
						{
						D_MOD( "VC: Reseting Covariance_1:"<< cov_reset<< endl);
						cov_reset = cov_reset_new;
						P1=P1_bew;
						P2=P2_bew;
						P3=P3_bew;
						for (i=0;i<40;i++){KF_reset(i)=500;}
						SPRT_SL=SPRT_SL*0;
						SPRT_SL_rate=SPRT_SL_rate*0;
						SPRT_SL_bew=SPRT_SL_bew*0;
						Threshold_detect=false;
						D_MOD( "VC: Reseting Covariance_2:"<< cov_reset<< endl);
					}

			
					para_reset_new = mal.data().reset_para;
					if (para_reset_new != para_reset)
						{
						D_MOD( "VC: Reseting Parameters from:"<< para_reset<< endl);
						para_reset= para_reset_new;
						a=a_bew2;
						D_MOD( "VC: Reseting Parameters to:"<< para_reset<< endl);
						Vright=40.0;
						Vright1=40.0;
						Vright2=40.0;
						Vleft=40.0;
						Vleft1=40.0;
						Vleft2=40.0;
						D_MOD(" VC: Resettting Vc s  "<<endl) 	
				
					}

					if (Phi_req != mal.data().Phi_req * 0.017453)
						{
						Phi_req=mal.data().Phi_req * 0.017453;
						D_MOD( "VC: Resetting Phi_req to:"<< Phi_req/0.017453 << endl);
					}
			
					if (maxt != mal.data().maxt)
						{
						maxt=mal.data().maxt;
						D_MOD( "VC: Resetting maxt to:"<< maxt << endl);
					}
	
				}
				catch (Exception& e)
					{
					cout << classname <<  ": Error while reading malfunctions channel" << endl;
				} 
			}
*/ 
			// obtain a pointer to the model input
			//real_T* U = reinterpret_cast<real_T*>(rtmGetU(S));
			//real_T* Y = reinterpret_cast<real_T*>(rtmGetY(S));
			try 
				{
				//StreamReader<PrimaryControls> pc(pc_token ,  ts);
				StreamReader<CitationPilotInput> cpi(cpi_token ,  ts);
				StreamReader<PrimarySwitches> ps(ps_token ,  ts);
				StreamReader<CitationOutput> in(in_token ,  ts);
		
				// DE verstelling moet gelijkblijven aan de verstelling in het model dus increase  aanpassen!!
				if(ps.data().trim_up) 
					{
					trim_tab_pos -= trim_incr; // TODO check sign
					//D_MOD(getId() << " trim up to " << trim_tab_pos);
				}
				else if(ps.data().trim_down) 
					{
					trim_tab_pos += trim_incr; // TODO check sign
					//D_MOD(getId() << " trim down to " << trim_tab_pos);
				}
				
				// de = pc.data().uy + de0 + trim_tab_pos; // HACK ,  trim through elevator
				//  da = pc.data().ux;
				//  dr = pc.data().uz;
				de = cpi.data().de; 
				da = cpi.data().da;
				dr = cpi.data().dr;
				
			
		
				// de state output
				Vtas  = in.data().y[Y_vtas]; 

				pb  = in.data().y[Y_p] * b / (2 * Vtas);   
				qc  = in.data().y[Y_q] * b / (2 * Vtas);  
				rb  = in.data().y[Y_r] * b / (2 * Vtas);  
				alpha = in.data().y[Y_alpha]; 
				beta  = in.data().y[Y_beta];  
				theta = in.data().y[Y_theta]; 
				height= in.data().y[Y_ralt];
				phi = in.data().y[Y_phi]; 
				nz  = in.data().y[Y_n]*b/(Vtas*Vtas); 
				
			
					
				if(vliegtuigtype==1)
					{
					ffl = (in.data().y[Y_torqueleft] -140) /(Vtas * Vtas);  
					ffr = (in.data().y[Y_torqueright]-140) / (Vtas * Vtas); 
				}
				
				if(vliegtuigtype==2)
					{
					// fflow is nu de torque  !!
					ffl = (in.data().y[Y_torqueleft] )*1000 / pow(Vtas,3);  
					ffr = (in.data().y[Y_torqueright])*1000 / pow (Vtas,3); 
					// Lineariseren naar niet lineaire aileron van de piper seneca
					da=da -0.3778 * pow(da,3);

					// nieuwe manier van Z berekenen
					Z(0)=(-in.data().y[Y_fycg] + 9.802*cos(alpha)*sin(phi) - in.data().y[Y_r] *cos(alpha)*Vtas + in.data().y[Y_p]*sin(alpha))/Vtas;
					//-g0*cos(theta)*sin(phi)+ay + r*cos(alpha)*vtas - p*sin(alpha)*vtas;( Matlab model output ay)
					Z(2)=in.data().y[Y_pdot]*b/(Vtas*2);  
					Z(3)=in.data().y[Y_rdot]*b/(Vtas*2);  
					


				}
				Data_go=true;
				de0 = in.data().y[Y_de0]; 
			}
			catch(Exception &e) 
				{
			W_MOD(getId() << " caught " << e << " @ " << ts);
			Data_go=false;
			}
	
			// store old values 
			u3=u2;
			tijd_3=tijd_2;
			u2=u1;
			tijd_2=tijd_1;
			tijd_1=ts.getValidityStart();
			// de input vector
			u1<< beta,phi,pb,rb,da,dr,ffl,ffr,nz,1;
/*			
			// Calculate the derivative over two dt's
			Z=(u1.head(4)-u3.head(4))*2000/(tijd_1-tijd_3);
			u=u2; // Middelste u gebruiken voor input 
*/
			u=u1;


			
			 // Alternatief afgeleiden uit model met herleide beta_dot v_dot/Vtas neemt geen turbulentie mee!!!
			//from P: Matlab anyb= ay  -g0*cos(theta)*sin(phi) + r*cos(alpha)*vtas - p*sin(alpha)*vtas;



			//TODO   tijdelijke verandering 240=>480 en alternatieve Z
	
			// Ook geen SPRT en KF als V<30 => indicatie van op de grond   
			// Oude criterium=>  if  (tijd_1-tijd_3)>240 

			if( Data_go==false || height<2)    // als  er data mist ( of op de grond) de berekening van a() en SPRT niet uitvoeren
				{  
				//if (tijd_1-tijd_3>240 ){D_MOD( classname << "Delta tijd >240 =" << (tijd_1-tijd_3) <<endl)}
				if (Data_go==false){D_MOD( classname << "No valid data for KF and SPRT"  <<endl)}
			}
			else 
				{
						// Kalman Filter
				Z*=(b/Vtas); // adaptation derivatives  to get V independent parameters
				// correctie beta dot voor bekende versnellingen 
				Z(0)=Z(0) - 2*pb*sin(alpha) + 2*rb*cos(alpha);
				// Predict  dot product
				Z_pred(0)=u.dot(a.head(10));
				Z_pred(1)=u.dot(a.segment(10,10));
				Z_pred(2)=u.dot(a.segment(20,10));
				Z_pred(3)=u.dot(a.tail(10));
				
				// meetfout (kolom)
				error= Z - Z_pred;      //Vier dimensionele fout
			
/*				// tIJDELIJKE CHECK  XXXXXXXX
				if (abs(error(0))>abs(Z_pred(0)) &&  abs(Z_pred(0))>0.01){cout<< " grote fout in rij 1 " << endl;}
				if (abs(error(2))>abs(Z_pred(2)) &&  abs(Z_pred(2))>0.01){cout<< " grote fout in rij 3 " << endl;}
				if (abs(error(3))>abs(Z_pred(3)) &&  abs(Z_pred(3))>0.01){cout<< " grote fout in rij 4 " << endl;}
*/		
				// Kalman parameters
				S1=u.dot(P1*u) + R(0,0);
				S2=u.dot(P2*u) + R(2,2);
				S3=u.dot(P3*u) + R(3,3);  
				
				//Kalman gains
				K1=(P1*u)/S1;
				K2=(P2*u)/S2;
				K3=(P3*u)/S3;
				
				// Resetten van R op  actuele gemeten waarden
				R(0,0)= 0.995*R(0,0)+0.005*(error(0)*error(0));
				R(2,2)= 0.995*R(2,2)+0.005*(error(2)*error(2));
				R(3,3)= 0.995*R(3,3)+0.005*(error(3)*error(3));
				//  geen aanpassing als inhibit true is 
		
				if (reset_uit==false)
					{
								
					a.head(10)=a.head(10)+K1*error(0);
					a.segment(20,10)=a.segment(20,10)+K2*error(2);
					a.tail(10)=a.tail(10)+K3*error(3);
				
					// verbeterde Pkf
					P1=(I-K1*u.transpose())*P1;
					P2=(I-K2*u.transpose())*P2;
					// cout<< " K2(8):" << K2(8) << endl;


					P3=(I-K3*u.transpose())*P3;
						
				}
		
				// goed zetten bekende waarden (dependencies on phi)
				a(1)=9.82*(b/(Vtas*Vtas))*cos(theta);
				if(phi!=0){a(1)=a(1)*sin(phi)/phi;}
				a(21)=0;
				a(31)=0;
				
				// voorkom onzin waardes voor dempingsconstantes
				if(a(22)>-0.001) {a(22)=-0.001;}
				if(a(33)>-0.001) {a(33)=-0.001;}

//				if (i5==1){cout<<  " a(28)="<< a(28) << "  K2(8)=" << K2(8) << " SD(8,8)=" << sqrt(P2(8,8)) <<  "  Ref_Rho(8,8)=" << sqrt(P2_bew(8,8)) <<   endl;}
					
				// DE SPRT Routine// Looking for threshold exceedances
				if (reset_uit==false)
					{ 
				
					// de projectie van de fout op de input en normalisatie
					SL_update.head(10) =       error(0)*((N*u)/(u.dot(N*u)));
					SL_update.segment(20,10) = error(2)*((N*u)/(u.dot(N*u)));
					SL_update.tail(10) =       error(3)*((N*u)/(u.dot(N*u)));
					
					u_old=u;
				
					
					// bepalen van de sprt 			
					for (i=0; i<27 ; i++)
						{   
						ii=reeks(i); // het nummer van de parameter (+1) dat gecheckt moet worden
						
							
						// bepalen van de standaard deviatie van de parameter
						if(ii<10) { ref_rho= max(sqrt(P1(ii,ii)),sqrt(P1_bew(ii,ii)));}
						if(ii>19 && ii<30){ ref_rho= max(sqrt(P2(ii-20,ii-20)),sqrt(P2_bew(ii-20,ii-20)));}
						if(ii>29) {ref_rho= max(sqrt(P3(ii-30,ii-30)),sqrt(P3_bew(ii-30,ii-30)));}
					
						// de gesommeerde en genormalizeerde fout
						temp2=SL_update_old(ii) + SL_update(ii)/ref_rho;
						// temp1 is de tweezijdige log likelyhood ratio	
						if(abs(temp2)>5) 
							{
							temp1 =   (b_ref * abs(temp2) ) -0.69315 ; 
						} // log(0.5);
						else 
							{
							temp1=log(cosh(b_ref*temp2));
						}

						// aftellen van de samples voor reset pause na reset of bij start
						KF_reset(ii)=fmax(KF_reset(ii)-1,0);
						
						if (i==8  && KF_reset(ii) ==1){cout<<" Threshold detect  rij 1 wordt active"<< endl;}
						if (i==17 && KF_reset(ii) ==1){cout<<" Threshold detect  rij 3 wordt active"<< endl;}
						if (i==26 && KF_reset(ii) ==1){cout<<" Threshold detect  rij 4 wordt active"<< endl;}
				
						// oude SPRT_SL bewaren voor rate berekeningen
						SPRT_SL_bew(ii)=SPRT_SL(ii);                
						// En hier komt de test waarde	
						SPRT_SL(ii)=fmax(0,temp1-0.5*SL_N(ii)*b_ref*b_ref);
						
						// en de rate waarde
						SPRT_SL_rate(ii)=0.95*SPRT_SL_rate(ii) +0.05 * (SPRT_SL(ii)-SPRT_SL_bew(ii) );
						
/*						if (ii==9)
							{
							 cout << "SPRT_SL(9) " << SPRT_SL(ii) << " ref_rho: " << ref_rho << " SL_N: " << SL_N(ii)<< "  KF_Reset" << KF_reset(ii) <<endl;
						}
*/							
						if (SPRT_SL(ii)==0) 
							{
							SL_update_old(ii)=0;
							SPRT_SL_rate(ii)=0;
							SL_N(ii)=1;
						}
						else
							{
							SL_update_old(ii)=temp2;
							SL_N(ii)++;
						}
					}


					// Nu de vergelijking met threshold values
					for(i=0;i<27;i++) 
						{   
						ii=reeks(i);  // Bepalen van rangnummer die parameter (+1) dat gecheckt moet worden ( niet alle par. worden gebruikt)
						iii=floor((ii)/10)+1;    // de rij waarin gewerkt wordt
					
						// Detect Threshold exceedance 
						if ( ( SPRT_SL(ii) > KF_threshold2(ii) ||  SPRT_SL_rate(ii)>KF_threshold_rate(ii)  ) && KF_reset(ii)==0 )
							{
							Threshold_detect=true;
							Threshold_param=ii;
							tijd_alarm=ts.getValidityStart();
							
							if ( SPRT_SL(ii) > KF_threshold2(ii)) 
								{    
								D_MOD( classname<< "Fout det. at par (base 1): "<<ii+1<< "  SPRT:"<< SPRT_SL(ii)<<" Limit="<< KF_threshold2(ii) <<endl)
							}
							else
								{
								D_MOD( classname<< "Rate Fout det. at par (base 1): "<<ii+1<< "  SPRT:"<< SPRT_SL_rate(ii)<<" Limit="<<KF_threshold_rate(ii) <<endl)
							}
				
							// alrijd rij reset 
							rij_reset=true;
							if  (rij_reset==true) 
								{
								if (iii==1)
									{
									P1=P1_reset; 
									KF_reset.head(10)= VectorXi::Constant(10,500);
									SPRT_SL.head(10)= VectorXd::Constant(10,0.0);
									SPRT_SL_rate.head(10)= VectorXd::Constant(10,0.0);
									SL_update_old.head(10)= VectorXd::Constant(10,0.0);
								}
								if (iii==3) 
									{
									P2=P2_reset;
									KF_reset.segment(20,10)    = VectorXi::Constant(10,500);
									SPRT_SL.segment(20,10)     = VectorXd::Constant(10,0.0);
									SPRT_SL_rate.segment(20,10)= VectorXd::Constant(10,0.0);
									SL_update_old.segment(20,10)= VectorXd::Constant(10,0.0);
								}

								if (iii==4)
									{
									P3=P3_reset; 
									KF_reset.tail(10)    = VectorXi::Constant(10,500);
									SPRT_SL.tail(10)     = VectorXd::Constant(10,0.0);
									SPRT_SL_rate.tail(10)= VectorXd::Constant(10,0.0);
									SL_update_old.tail(10)= VectorXd::Constant(10,0.0);
								}
								D_MOD( classname<< "Rij reset: " <<iii<< "  Set P= P_reset" << " Rust voor N samples:" << KF_reset(ii) <<endl)
							}
							// Else een single reset:
							else    
								{
								D_MOD( classname<< " Single reset op ii= "<<ii<< endl)
								if (iii==0) { P1(ii,ii)=P1_reset(ii,ii);}
								if (iii==2) { P2(ii-20,ii-20)=P2_reset(ii-20,ii-20);}
								if (iii==3) { P3(ii-30,ii-30)=P3_reset(ii-30,ii-30);}
								SPRT_SL(ii)=0;SPRT_SL_rate(ii)=0;SL_update_old(ii)=0;
								KF_reset(ii)=500;
								//KF_threshold2<<100, 0, 10000, 8000; //555,0,52008,33335;
							}
						}
					} 
				}
				//cout<<"SPRT (25)="<<SPRT_SL(25)<<endl;
				if((tijd_alarm + 30000)<ts.getValidityStart() && Threshold_detect==true)
					{
					Threshold_detect=false;
					Threshold_param=0;
					D_MOD( classname<< " Resetting: Alarm="<< Threshold_detect<<endl)
				} // na 15 seconden warning uit  

			}  // SPR en KF gedaan omdat dt binnen bounderies lag Vc altijd berekenenen	
			Max_SPRT=0;
			Max_SPRT_rate=0;
			for(i=0;i<27;i++) 
				{   
				ii=reeks(i);
				if ( Max_SPRT< (SPRT_SL(ii)/ KF_threshold2(ii)) )
					{ 
					Max_SPRT= (SPRT_SL(ii)/ KF_threshold2(ii));
					Max_SPRT_I=ii+1;
				}
				if ( Max_SPRT_rate< (SPRT_SL_rate(ii)/KF_threshold_rate(ii)) )
					{ 
					Max_SPRT_rate= (SPRT_SL(ii)/ KF_threshold2(ii));
					Max_SPRT_rate_I=ii+51;
				}				
			}

			//calculate VC-1 and Vc-2
			
			// correctie van sideslip parameters met bekende waarde
			// Correctie alleen toepassen in berekening C4 a(2) en a(3) zelf niet aanpassen
			// dat leidt tot threshold exceedance
			/*a(2)=a(2) + 2*sin(alpha);
			a(3)=a(3) - 2*cos(alpha);
			*/
			p_dot=Z(2);
			r_dot=Z(3);
			// Aerokoppeling is uitgeschakeld, alleen gebruiken voor de correctie van de VC bij off line simulaties
			// Berekening Aerokoppelling niet elke tijdstap nodig teller i5 ingevoerd
			// Aerokop bij rechterrol
			i5++; 
			/*
			if (i5==1 || i5==25)
				{ 
				// right roll coupling
				if (i5==1)
					{
					// zonder rudder
					i=1;
					beta_0= beta;
					Vright=Vright1;
					//D_MOD(classname<<" Aerok rechts Ail "<<C9R1<<" At time"<<tijd_1<<endl)
				}
				if (i5==25)
					{
					// met max rudder Y2= predicted right rudder available at Vright
					i=2;
					beta_0 = beta -  Y2*a(35)/a(30);
					Vright=Vright2;
					//D_MOD(classname<<" Aerok rechts Rud "<<C9R1<<" At time"<<tijd_1<<endl)
				}
				alpha_0=alpha*pow((Vtas/Vright),2);
			
				tau2=-b/(Vright*a(22));   //Tau and Pmax voor rechterrol
				if (tau2<0) {tau2=0.01;}   //bescherming tegen over flow
			
				pmax=fabs(Phi_req)/(maxt + tau2 * (exp(-maxt/tau2)-1));
			
				// benadering roll coupling 
				Eff_dB=0;
				Eff_dNz=0;
				temp1=0;
				for (dtt=0.0;dtt<maxt;dtt+=0.04)
					{
					hoek=(pmax*(dtt + tau2*(exp(-dtt/tau2)-1)));
					Eff_dB=Eff_dB+(alpha_0*sin(hoek) + beta_0*(cos(hoek)-1) + (1-exp((Vright/b)*a(0)*dtt))*(a(4)*(damin-da)/a(0)) )*(maxt-dtt);
					Eff_dNz=Eff_dNz+(-beta_0*sin(hoek) + alpha_0*(cos(hoek)-1))*(maxt-dtt);
					temp1+=dtt;
				}
				Eff_dB=(Eff_dB/temp1);
				Eff_dNz=(Eff_dNz/temp1)/alpha_0;
				C9R= - Eff_dB * (a(20)/a(24)) - (a(28)/a(24)) * (1/pow(Vright,2)) * Eff_dNz;
				if (i==1){C9R1=C9R;}
				if (i==2){C9R2=C9R;}
			} 
			// Aerokoppeling linkerrol	
			if (i5==15 || i5==40){ 
				// aileron roll
				if (i5==15)
					{
					i=1;
					beta_0= beta;
					Vleft=Vleft1;
				}
				// rudder roll Y1 is predicted left rudder available at Vleft
				if (i5==40
					){
					i=2;
					beta_0 = beta  -Y1*a(35)/a(30);
					Vleft=Vleft2;
				}
				alpha_0=alpha*pow((Vtas/Vleft),2);
				tau2=-b/(Vleft*a(22));    // Tau and Pmax voor linkerrol
				if (tau2<0){ tau2=0.01;}  // bescherming tegen overflow
				pmax=-fabs(Phi_req)/(maxt + tau2*(exp(-maxt/tau2)-1));
				Eff_dB=0;
				Eff_dNz=0;
				temp1=0;
				// Benadering roll koppeling
				for (dtt=0;dtt<maxt;dtt+=0.04)
					{
					hoek=(pmax*(dtt + tau2*(exp(-dtt/tau2)-1)));
					Eff_dB=Eff_dB+(alpha_0*sin(hoek) + beta_0*(cos(hoek)-1) + (1-exp((Vleft/b)*a(0)*dtt))*(a(4)*(damax-da)/a(0)) )*(maxt-dtt);
					Eff_dNz=Eff_dNz+(-beta_0*sin(hoek) + alpha_0*(cos(hoek)-1))*(maxt-dtt);
					temp1+=dtt;
				}
				Eff_dB=(Eff_dB/temp1);
				Eff_dNz=(Eff_dNz/temp1)/alpha_0;
				C9L= - Eff_dB * (a(20)/a(24)) - (a(28)/a(24)) * (1/pow(Vleft,2)) * Eff_dNz;
				if (i==1){ C9L1=C9L;}
				if (i==2){ C9L2=C9L;}
			} 
			*/
			C9L=0;C9R=0;     // Aerokoppeling op nul gezet
			if(i5>49){i5=0;}	
		
			// bereken constantes zie formule blad met actuele V
			// C0_r=fabs(Phi_req)*b*a(22)/(-2*a(24)); // p_max/(Phi_req*da_available)
			// C0_l=-C0_r;
			// Niewe manier beter geschikt voor checken of er een minimu speed bestaat
			C_b= (-2/(b*a(22)))*( a(24) );
			//correctie present roll en p_dot tegengesteld teken
			C3= (+ p_dot/a(24) - pb*a(22)/a(24)) ;  // + a(i,29)/a(i,24); Niet toepassen is al mee gerekend 
			// correctie van sideslip parameters met bekende waarde
		
			//Effect asymmetric weight or lift
			C6=-a(28)*(1/(Vtas*Vtas))/a(24); // nz = changed to 1/V^2
	

			// berekenen van aileron en rudder nodig ivm thrust asymmetry
			if (abs(a(35))>0.015)
				{ 
		
				A2<< a(4), a(5), a(24), a(25), a(34), a(35);
				V3_1<< -(a(6)*ffl+a(7)*ffr), -(a(26)*ffl+a(27)*ffr), -( a(36)*ffl+a(37)*ffr);
			
				// benieuwd of dit werkt
			
				V2=(A2.transpose()*A2).colPivHouseholderQr().solve(A2.transpose()*V3_1);
				C4=V2(0);
				dr_eng=V2(1);
			}
			else 
				{
				// de benodigde da indien geen rudder available is
				A2<< a(4), a(0), a(24), a(20), a(34), a(30);
				V3_1<< -(a(6)*ffl+a(7)*ffr), -(a(26)*ffl+a(27)*ffr), -( a(36)*ffl+a(37)*ffr);
				// Dit werkt!!
				V2=(A2.transpose()*A2).colPivHouseholderQr().solve(A2.transpose()*V3_1);
				// V2(0) =da   V2(1)=beta 
				C4=V2(0);
			}

			// Hier worden de stabiele da_s en dr_s en beta_s  uitgerekend
			beta_s=beta_s*0.99 + 0.01 * (beta);
			da_s= da_s*0.99 + 0.01*(da -  C3);
			dr_s= dr_s*0.99 + 0.01*dr;
	

			// Nu kijken of er nog rudder over is op Vc zo niet dan ontstaat beta en is extra aileron nodig => C10R/L 
		
			if ( abs(dr_eng) < (0.98* drmax) && abs(a(35))>0.015 ) 
				{
				Y1=(drmax - dr_s - dr_eng*(pow(Vtas/Vleft,3)-1) -  (damax - da_s) * fmax((-a(34)/a(35)),0.25) );		
				Y2=(drmin - dr_s - dr_eng*(pow(Vtas/Vright,3)-1) - (damin - da_s) * fmax((-a(34)/a(35)),0.25) );	
				if (Y1<0)
					{
					C10L=fmin( (0.5*damax),(-Y1 * (a(35)/a(30)) * (-a(20)/a(24)) ) );
					C5L=0;
					Adverse_yaw=true;
				}	
				else 
					{
					C10L=0;
					C11L=0;
					Adverse_yaw=false;
					C5L=-Y1 * (a(35) / a(30) ) * (-a(20)/a(24));
				}
				if (Y2 > 0)
					{
					C10R=fmax((0.5*damin ),(-Y2 * (a(35)/a(30)) * (-a(20)/a(24)) ) );
					Adverse_yaw=true;
					C5R=0;
				}	
				else 
					{
					C10R=0;
					C11R=0;
					C5R=-Y2 * (a(35)/a(30)) * (-a(20)/a(24));
					Adverse_yaw=false;
				}
			}
			else 
				{
				// If this is true maximum rudder has already been reached or ndr is close to zero (failed rudder)
				C5L=0;
				C5R=0;
				C10R=0;
				C10L=0;
				Adverse_yaw=true;
			}

			if (Adverse_yaw==true)
				{
				//Aileron input at Vc
				da_yaw=(damin - da_s- C4*(pow(Vtas/Vright,3) - 1) - C6*(pow(Vtas/Vright,2) - 1));
		
				tau=-b/(Vright*a(22));
				Ar<< a(0), a(1) ,a(2), a(3), 0, 0, 2.0, 0, a(20), 0.0 ,a(22), a(23),a(30), 0.0 ,a(32), a(33);
				Br<< a(5), a(4), 0.0, 0.0 , a(25), 0.0 , a(35), a(34);
				del1=(maxt/9)*(Vright/b)*0.5;
		
				//Runga Kutta intergratie
				Ya<< 0,0,0,0;  //Begin waarde t=0;
				Ua<< 0, da_yaw; // De input = constant
				for(i6=0;i6<8;i6++)
					{
					Xa0=  Ya;
					Rk1a=( Ar * Xa0 + Br * Ua)*del1;
					Xa1=Xa0 + Rk1a;
					Rk2a= ( Ar * Xa1 + Br * Ua)*del1;
					Xa1=Xa0+Rk2a;
					Rk3a=( Ar * Xa1 + Br * Ua)*del1;
					Xa1= Xa0 + 2.0 * Rk3a;
					Rk4a=( Ar * Xa1 + Br * Ua)*del1;
					Ya=Xa0+(Rk1a+2*(Rk2a+Rk3a)+Rk4a)/3.0;
				}
				pmax=Ya(1) * (1/(tau*exp(-maxt/tau)+maxt-tau));
				C11R= - pmax * (-b / (2*Vright) )*( a(22) / a(24));
		
				// En nu voor links
				//Aileron input at Vc
				da_yaw=(damax - da_s - C4*(pow(Vtas/Vleft,3) - 1) - C6*(pow(Vtas/Vleft,2) - 1));
		
				tau=-b/(Vleft*a(22));
				del1=(maxt/9)*(Vleft/b)*0.5;
		
				// Runga Kutta intergratie
				Ya<< 0,0,0,0;  // Begin waarde t=0;
				Ua<< 0, da_yaw; // De input = constant
				for(i6=0;i6<8;i6++)
					{
					Xa0=  Ya;
					Rk1a=( Ar * Xa0 + Br * Ua)*del1;
					Xa1=Xa0 + Rk1a;
					Rk2a= ( Ar * Xa1 + Br * Ua)*del1;
					Xa1=Xa0+Rk2a;
					Rk3a=( Ar * Xa1 + Br * Ua)*del1;
					Xa1= Xa0 + 2.0 * Rk3a;
					Rk4a=( Ar * Xa1 + Br * Ua)*del1;
					Ya=Xa0+(Rk1a+2*(Rk2a+Rk3a)+Rk4a)/3.0;
				}
				pmax=Ya(1)* (1/(tau*exp(-maxt/tau)+maxt-tau));
				C11L= - pmax * (-b / (2*Vleft) )*( a(22) / a(24));         
			}

			//All rolls
			tau=-b/(Vtas*a(22));
			//bescherming tegen over flow
			if (tau<0){ tau = 0.01 ;}
			C2=tau/Vtas;
			C1=tau*(exp(-maxt/tau)-2) + maxt;

			// ROLL rechts
			for (i=1;i<3;i++)
				{
				if (i==2){
					Vright=Vright2;
					C7=(damin - da_s -  C4 * (pow((Vtas/Vright),3)-1) -C6*(pow((Vtas/Vright),2)-1) - C5R - C9R2 - C10R - C11R);
				}
				if (i==1){
					Vright=Vright1;
					C7=(damin - da_s - C4 * (pow((Vtas/Vright),3)-1) - C6 *(pow((Vtas/Vright),2)-1) - C9R1 -C10R - C11R);
					
				}
				//  Check of er wel een nulpunt is door F waarde bij minimum speed (25 m/s) te berekenenen voor aileron only roll!!!!
				if ( (C_b*(C1*25 + C2*625)*(damin - da_s - C4*(pow((Vtas/Vright),3)-1) - C6*(pow((Vtas/Vright),2)-1) - C9R1  -C10R -C11R) - abs(Phi_req))<0)
					{
					F= (C1*Vright + C2*pow(Vright,2))*C_b*C7  - abs(Phi_req);
					F_dot=(C1+2*C2*Vright)*C7*C_b  +  (C1*Vright + C2 * pow(Vright,2) )*C_b*(3*C4*pow(Vtas,3)/pow(Vright,4) + 2*C6* pow(Vtas,2)/pow(Vright,3) );
					dV=F/F_dot;
					if (dV>Nd){ dV=Nd;} // beperken maximale aanpassing tot dm/sec per itteratiesec 
					if (dV<-Nd){ dV=-Nd;}
					Vright=Vright-dV;  // Newton approximation
					if (Vright>Vtas+15){Vright=Vtas+15;}
					if (Vright<25){Vright=25;}
				}
				else
					{
					Vright=25;
				}
				if (i==2) {Vright2=Vright;}
				if (i==1) {Vright1=Vright;}
		
			}
	
			//Left ROLL
			for (i=1;i<3;i++)
				{
				if (i==2)
					{
					Vleft=Vleft2;			
					C7=(damax - da_s  -  C4 * (pow((Vtas/Vleft),3)-1) -C6*(pow((Vtas/Vleft),2)-1) - C5L - C9L2 -C10L -C11L);
		
				}
				if (i==1)
					{
					Vleft=Vleft1;
					C7=(damax - da_s  - C4 * (pow((Vtas/Vleft),3)-1) - C6 *(pow((Vtas/Vleft),2)-1) - C9L1 -C10L -C11L);
				}
				// checken of er een oplossing is
				if ( (C_b*(C1*25 + C2*625)*(damax - da_s - C4*(pow((Vtas/Vleft),3)-1) - C6*(pow((Vtas/Vleft),2)-1) - C9L1  - C10L - C11L) + abs(Phi_req))>0)
					{
					F= (C1*Vleft + C2*pow(Vleft,2))*C_b*C7  + abs(Phi_req);
					F_dot=(C1+2*C2*Vleft)*C7*C_b  +  (C1*Vleft + C2* pow(Vleft,2))*C_b*(3*C4*pow(Vtas,3)/pow(Vleft,4) + 2*C6* pow(Vtas,2)/pow(Vleft,3) );
					dV=F/F_dot;
					if (dV>Nd){ dV=Nd;} // beperken maximale aanpassing tot dm/sec per itteratiesec 
					if (dV<-Nd){ dV=-Nd;}
					Vleft=Vleft-dV;  // Newton approximation
					if (Vleft>Vtas+15){Vleft=Vtas+15;}
					if (Vleft<25){Vleft=25;}
				}
				else
					{
					Vleft=25;
				}
				if (i==1) {Vleft1=Vleft;}
				if (i==2) {Vleft2=Vleft;}
			}
	// PFD gebruikt KTAS maar presenteert KCAS

			if (Vleft1<Vright1)
				{
				Vc1=Vright1*1.9438;
				Vc2=Vright2*1.9438;
			}
			else 
				{
				Vc1=Vleft1*1.9438;
				Vc2=Vleft2*1.9438;
			}
			/*
				if (Vleft1>70 && i5==10){ 
				cout<< " Vleft > 70m/s  C10L=" << C10L << "   C7="<< C7 << "   C9L1=" << C9L1 <<  "  damax=" << damax << " da=" << da << endl;
				cout<< " C3=" << C3 << "  C4="<< C4 << "   C6=" << C6 <<  "  C_b" << C_b << " C1=" << C1 << "  C2="<< C2 <<endl;
				}
				if (i5==10){ 
				cout<< " Error(0)=" << error(0) << " Rho_ref(9)=" << max(sqrt(P1(9,9)),sqrt(P1_bew(9,9)))  <<  endl;
				cout<< " SRT_SL(9)" << SPRT_SL(9) << "  SL_update(9)=" << SL_update(9) << " SL_update_old(9)=" << SL_update_old(9)  <<endl;
				}
				//if (Vright1>70){ cout<< " Vright > 70m/s  C10R=" << C10R << endl;}
			*/  
			
			// if (i5==10){cout<< "SPRT_rate 23=" << SPRT_SL_rate(23) << "  SPRT(30)=" << SPRT_SL(30) << endl; }


			StreamWriter<Vc_Channel>VcWrite(uit_token, ts);
			
			
			VcWrite.data().Threshold=Threshold_detect; 

			if (Threshold_detect==true)
				{VcWrite.data().Threshold_param=Threshold_param;
			}
			else
				{
					if (Max_SPRT>Max_SPRT_rate)
						{ Threshold_param= round((Max_SPRT_I + Max_SPRT)*100);
					}
					else
						{Threshold_param= round((Max_SPRT_rate_I + Max_SPRT_rate)*100);
					}
				VcWrite.data().Threshold_param=Threshold_param;
			}
				
			
			if( (da > (damax*0.95)) &&  (pb > 0)  && ((pb/p_dot) < -0.5 || p_dot>0 ) )
				{
				VcWrite.data().Reduce_left = true;
			}else
				{
				VcWrite.data().Reduce_left = false;
			}
			if( (da<damin*0.95) &&  (pb<0)  && ( (pb/p_dot) < -0.5  || p_dot < 0 ) )
				{
				VcWrite.data().Reduce_right = true;
			}else
				{
				VcWrite.data().Reduce_right = false;
			}
			
			// Als database>2 dan wordt Vc negatief weggeschreven hierdoor niet gedisplayed maar wel in output file
			if (database<3) {	
			
				VcWrite.data().Vc_1 = Vc1;
				VcWrite.data().Vc_2 = Vc2;
			}
			else
			{
				VcWrite.data().Vc_1 = -Vc1;
				VcWrite.data().Vc_2 = -Vc2;}

				
				/*
				if (i5==2 || i5==27 ) // slechts 1 keer per seconde
				=======
				if (i5==5 ){
					cout <<  " C4:" << C4 << "  C6:" << C6 << "a(28):" << a(28)<< " C1:" << C1<<  " C2:" << C2 << " C7:" << C7 << "  C8:" << C8 <<endl; 
					}
				*/
				
				

				break;
		} 
		default:
		// other states should never be entered for a SimulationModule ,  
		// HardwareModules on the other hand have more states. Throw an
		// exception if we get here ,  
		throw CannotHandleState(getId() , GlobalId() ,  "state unhandled");	
	  }
}

  



void CvCalculation::trimCalculation(const TimeSpec& ts ,  const TrimMode& mode)
{
  // read the event equivalent of the input data
  // example
  // EventReader u(i_input_token ,  ts);

  // using the input ,  and the data put into your trim variables , 
  // calculate the derivative of the state. DO NOT use the state
  // vector of the normal simulation here ,  because it might be that
  // this is done while the simulation runs!  
  // Some elements in this state derivative are needed as target ,  copy
  // these out again into trim variables (see you TrimTable

  // trim calculation
  switch(mode) {
  case FlightPath: {
  // one type of trim calculation ,  find a power setting and attitude
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
  // ground ,  power/speed 0
  }
  break;

  default:
  W_MOD(getId() << " cannot calculate inco mode " << mode);
  }

  // This works just like a normal calculation ,  only you provide the
  // steady state value (if your system is stable anyhow). So ,  if you
  // have other modules normally depending on your output ,  you should
  // also produce the equivalent output here. 
  // EventWriter<MyOutput> y(output_token ,  ts);

  // write the output into the output channel ,  using the EventWriter
  // N.B. you may also use:
  // output_token.sendEvent(ts ,  new MyOutput(arguments));
  // this is slightly more efficient. However ,  the EventWriter makes
  // it easier ,  because the code will look much more like your normal
  // calculation code.

  // now return. The real results from the trim calculation ,  as you
  // specified them in the TrimTable ,  will now be collected and sent
  // off for processing.
}







// Make a TypeCreator object for this module ,  the TypeCreator
// will check in with the scheme-interpreting code ,  and enable the
// creation of modules of this type
static TypeCreator<CvCalculation> a(CvCalculation::getMyParameterTable());

