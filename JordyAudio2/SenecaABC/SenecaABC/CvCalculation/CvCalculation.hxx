/* ------------------------------------------------------------------   */
/*      item            : CvCalculation.hxx
        made by         : hkoolstra
	from template   : DusimeModuleTemplate.hxx
        template made by: Rene van Paassen
        date            : Fri Mar  8 13:03:04 2013
	category        : header file 
        description     : 
	changes         : Fri Mar  8 13:03:04 2013 first version
	template changes: 030401 RvP Added template creation comment
        language        : C++
*/

#ifndef CvCalculation_hxx
#define CvCalculation_hxx

// include the dusime header
#include <dusime.h>

// This includes headers for the objects that are sent over the channels
#include "comm-objects.h"

// Hier staat de enumeration van de output
#include "StatesOutputs.h"

// include headers for functions/classes you need in the module
#include <Ticker.hxx>

//voor math functies
#include <math.h>

// De nieuwe libeigen3 class
#include <Eigen/Dense>
using namespace Eigen;

USING_DUECA_NS;



// include headers for functions/classes you need in the module


/** A module.
    
    The instructions to create an module of this class from the Scheme
    script are:

    \verbinclude cv-calculation.scm
*/
class CvCalculation: public SimulationModule
{
private: // simulation data

  // declare the data you need in your simulation

  int vliegtuigtype;

  double ARI;

  double Threshold_factor, Threshold_factor_rate;	

  double database;
   /** initial (trimmed) pitch value */
  double de0;
  
  /** elevator trim */
  double trim_incr;
  double trim_tab_pos;// rad -0.26 ... 0.26

  /** state parameters*/
  double  Vtas,de,da,dr,alpha,beta,nz,ffl,ffr,pb,rb,qc,phi,theta,height;

  /** Constants  Vliegtuig variabelen*/
  double b,c; 

 /** variabelen voor param identificatie*/
  double S1,S2,S3;
  bool cov_reset, cov_reset_new, para_reset, para_reset_new,Data_go;

  /** parameters for threshold detect*/

  double ref_rho,b_ref,kf_factor,tijd_1,tijd_2,tijd_3,tijd_alarm;
  bool rij_reset,Threshold_detect,reset_uit;
  int Threshold_param;
  double temp1,temp2,temp3;
  int i, ii, iii, iiii,i5;

/** Variabelen voor Vc calculation */
  double p_dot,r_dot,alpha_0,beta_0,Vright,Vright1,Vright2,Vleft,Vleft1,Vleft2;
  double beta_rud_right,beta_rud_left,tau,tau2,pmax,Phi_req,maxt,Eff_dB,Eff_dNz,dtt,hoek,damin,damax,drmin,drmax;
  double C10L,C10R,C9R,C9R1,C9R2,C9L,C9L1,C9L2,C0_r,C0_l,C_b,C1,C2,C3,C4,C5L,C5R,C6,C7,C8,F,F_dot,dV,Vc1,Vc2,Nd,Y1,Y2,Y3;
  double Max_SPRT,Max_SPRT_I,Max_SPRT_rate,Max_SPRT_rate_I;
/** variabelen voor berekenen adverse yaw */
  bool Adverse_yaw;
  double da_yaw,yaw_demp,yaw_rad,ad_beta1,ad_beta2,ad_beta3,C11R,C11L,dr_eng,beta_s,da_s,dr_s,del1;
  int i6;


/** variabelen van emergencies*/
 double asym_x, asym_y,	asym_z, asym_mass, rudder_power, aileron_power, rudder_bias;

 /** DE te gebruiken matrices met eigenlib */
  MatrixXd P1;
  MatrixXd P2;
  MatrixXd P3;
  MatrixXd P1_bew;
  MatrixXd P2_bew;
  MatrixXd P3_bew;
  MatrixXd P1_reset;
  MatrixXd P2_reset;
  MatrixXd P3_reset;
  MatrixXd I;
  MatrixXd R;
  MatrixXd A1;
  MatrixXd A2;
  MatrixXd N;
  MatrixXd Ar;
  MatrixXd Br;
  VectorXd K1;
  VectorXd K2;
  VectorXd K3;
  VectorXd Z;
  VectorXd par;
  VectorXd u;
  VectorXd u1;
  VectorXd u2;
  VectorXd u3;	
  VectorXd u_old;
  VectorXd a;
  VectorXd a_bew;
  VectorXd a_bew2;
  VectorXd Z_pred;
  VectorXd error;
  VectorXd V;
  VectorXd V2;
  VectorXd V3_1;
  VectorXd V3_2;
  VectorXd V3_3;
  VectorXi reeks;
  VectorXi reeks2;
  VectorXd SPRT_SL;
  VectorXd SL_update;
  VectorXd SL_update_old;
  VectorXd SPRT_SL_rate;
  VectorXd SPRT_SL_bew;
  VectorXi SL_N;
  VectorXd KF_threshold2;
  VectorXd KF_threshold_rate;
  VectorXi KF_reset;
  VectorXd Xa0;
  VectorXd Xa1;
  VectorXd Ua;
  VectorXd Ya;
  VectorXd Rk1a;
  VectorXd Rk2a;
  VectorXd Rk3a;
  VectorXd Rk4a;


private: // trim calculation data
  // declare the trim calculation data needed for your simulation

private: // snapshot data
  // declare, if you need, the room for placing snapshot data

private: // channel access
  //  StreamChannelReadToken<PrimaryControls> pc_token;
    StreamChannelReadToken<CitationPilotInput> cpi_token;
    StreamChannelReadToken<PrimarySwitches> ps_token;
    StreamChannelReadToken<CitationOutput> in_token;
    StreamChannelWriteToken<Vc_Channel> uit_token;
    //EventChannelReadToken<MalfunctionsChannel> mal_token;

private: // activity allocation
  /** You might also need a clock. Don't mis-use this, because it is
      generally better to trigger on the incoming channels */
  //PeriodicAlarm        myclock;

  /** Callback object for simulation calculation. */
  Callback<CvCalculation>  cb1;

  /** Activity for simulation calculation. */
  ActivityCallback      do_calc;
  
public: // class name and trim/parameter tables
  /** Name of the module. */
  static const char* const           classname;

  /** Return the initial condition table. */
  static const IncoTable*            getMyIncoTable();

  /** Return the parameter table. */
  static const ParameterTable*       getMyParameterTable();
  
public: // construction and further specification
  /** Constructor. Is normally called from scheme/the creation script. */
  CvCalculation(Entity* e, const char* part, const PrioritySpec& ts);

  /** Continued construction. This is called after all script
      parameters have been read and filled in, according to the
      parameter table. Your running environment, e.g. for OpenGL
      drawing, is also prepared. Any lengty initialisations (like
      reading the 4 GB of wind tables) should be done here.
      Return false if something in the parameters is wrong (by
      the way, it would help if you printed what!) May be deleted. */
  bool complete();

  /** Destructor. */
  ~CvCalculation();

  // add here the member functions you want to be called with further 
  // parameters. These are then also added in the parameter table
  // The most common one (addition of time spec) is given here. 
  // Delete if not needed!

  /** Specify a time specification for the simulation activity. */
  bool setTimeSpec(const TimeSpec& ts);

  /** Request check on the timing. */
  bool checkTiming(const vector<int>& i);

public: // member functions for cooperation with DUECA
  /** indicate that everything is ready. */
  bool isPrepared();

  /** start responsiveness to input data. */
  void startModule(const TimeSpec &time);
  
  /** stop responsiveness to input data. */
  void stopModule(const TimeSpec &time);

public: // the member functions that are called for activities
  /** the method that implements the main calculation. */
  void doCalculation(const TimeSpec& ts);

public: // member functions for cooperation with DUSIME
  /** For the Snapshot capability, fill the snapshot "snap" with the 
      data saved at a point in your simulation (if from_trim is false)
      or with the state data calculated in the trim calculation (if
      from_trim is true). */
  void fillSnapshot(const TimeSpec& ts, 
		    Snapshot& snap, bool from_trim);
  
  /** Restoring the state of the simulation from a snapshot. */
  void loadSnapshot(const TimeSpec& t, const Snapshot& snap);

  /** Perform a trim calculation. Should NOT use current state 
      uses event channels parallel to the stream data channels,
      calculates, based on the event channel input, the steady state
      output. */
void trimCalculation(const TimeSpec& ts, const TrimMode& mode);
};

#endif
