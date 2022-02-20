/* ------------------------------------------------------------------   */
/*      item            : B747PFD.hxx
        made by         : mamulder
	from template   : DusimeModuleTemplate.hxx
        template made by: Rene van Paassen
        date            : Wed Jan 24 11:19:18 2007
	category        : header file 
        description     : 
	changes         : Wed Jan 24 11:19:18 2007 first version
	template changes: 030401 RvP Added template creation comment
        language        : C++
*/

#ifndef B747PFD_hxx
#define B747PFD_hxx

#ifdef B747PFD_cxx
static const char h_id[] =
"$Id: B747PFD.hxx,v 1.1 2020/03/20 16:17:33 ostroosma Exp $";
#endif

// include the dusime header
#include <dusime.h>
USING_DUECA_NS;

// This includes headers for the objects that are sent over the channels
#include "comm-objects.h"

// Seneca model data
#include "StatesOutputs.h"

// include headers for functions/classes you need in the module
#include "PFD_B747.h"
#include "gs_loc_bar.hxx"
#include "fm_anunciations.hxx"
#include "attitude_indicator.hxx"
#include "compass.hxx"
//#include <B747ModelIO.h>
#include <LinearSystem.hxx>

/** A module.
    
    The instructions to create an module of this class from the Scheme
    script are:

    \verbinclude b747-pfd.scm
*/
class B747PFD: public SimulationModule
{
private: // simulation data

  // declare the data you need in your simulation
  PFD_B747            pfdWindow;
  gs_loc_bar          *m_gs, *m_loc;
  fm_anunciations     *m_fm_anun;
  attitude_indicator  *m_att_indicator;
  compass             *m_compass;
  int                 window_x, window_y, window_width, window_height;
  double              mag_hdg_offset;
  bool                show_fd,threshold,reduce_left,reduce_right;
  LinearSystem        *sys_ias;
  Vector              num_ias, den_ias;
  double              tau_ias;
  Vector              in_ias, out_ias;
  double              dt;
//  bool                citation_mode;
  int                 vliegtuigtype;
  double	      Lambda;	      
  float	          flapAngleDeg, Vstall, Vman, V1, V2, FAS;
  float           Sp_factor;
  bool   	      Slip_top, Slip_beta, sustained_climb_angle;
  float 	      Slip, Climb, Database;

	bool in_hold;
	// display event
	bool frozen_v, frozen_h;
	float offset_v_value, offset_h_value;
	// vars added for display event
	float disp_v, disp_m, disp_h, disp_hdot, offset_v_set, offset_v_stepsize, offset_h_set, offset_h_stepsize;
	int offset_v_nsteps, offset_h_nsteps;

private: // trim calculation data
  // declare the trim calculation data needed for your simulation

private: // snapshot data
  // declare, if you need, the room for placing snapshot data

private: // channel access
  StreamChannelReadToken<CitationOutput> in_token;
  StreamChannelReadToken<NavData> nav_token;
  //EventChannelReadToken<MalfunctionsChannel> mal_token;
  EventChannelReadToken<DisplayEvent> display_token;
  EventChannelWriteToken<DisplayEvent> display_feedback_token;
  // optional channel //edit peter
  StreamChannelReadToken<Vc_Channel> *Vc_token;

// StreamChannelReadToken<ModelOutput>       mo_token;
//  StreamChannelReadToken<FDSignal>          fds_token;
//  EventChannelReadToken<FMSReferenceData>   fms_ref_token;
//  StreamChannelReadToken<APModes>           apm_token;

private: // activity allocation
  /** Callback object for simulation calculation. */
  Callback<B747PFD>  cb1;

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
  B747PFD(Entity* e, const char* part, const PrioritySpec& ts);

  /** Continued construction. This is called after all script
      parameters have been read and filled in, according to the
      parameter table. Your running environment, e.g. for OpenGL
      drawing, is also prepared. Any lengty initialisations (like
      reading the 4 GB of wind tables) should be done here.
      Return false if something in the parameters is wrong (by
      the way, it would help if you printed what!) May be deleted. */
  bool complete();

  /** Destructor. */
  ~B747PFD();

  // add here the member functions you want to be called with further 
  // parameters. These are then also added in the parameter table
  // The most common one (addition of time spec) is given here. 
  // Delete if not needed!

  /** Specify a time specification for the simulation activity. */
  bool setTimeSpec(const TimeSpec& ts);

  /** Request check on the timing. */
  bool checkTiming(const vector<int>& i);

  /** Set the window properties */
  bool setWindowProperties(const vector<int>& i);
  
  /** Set the state of an anunciation flag */
  //void set_anunciation(int flag, int state);

  /** Expect input from cv-calculation module over Vc_Channel channel. */
  bool readCv(const bool& b);
  
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

  /** Perform a trim calculation. Should NOT use current state 
      uses event channels parallel to the stream data channels,
      calculates, based on the event channel input, the steady state
      output. */
  void trimCalculation(const TimeSpec& ts, const TrimMode& mode);
};

#endif
