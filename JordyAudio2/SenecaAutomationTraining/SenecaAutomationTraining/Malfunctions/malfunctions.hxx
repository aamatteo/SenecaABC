/* ------------------------------------------------------------------   */
/*      item            : malfunctions.hxx
        made by         : peter
	from template   : DusimeModuleTemplate.hxx
        template made by: Rene van Paassen
        date            : Fri Mar 17 11:01:16 2017
	category        : header file
        description     :
	changes         : Fri Mar 17 11:01:16 2017 first version
	template changes: 030401 RvP Added template creation comment
        language        : C++
        copyright       : (c) 2016 TUDelft-AE-C&S
*/

#ifndef malfunctions_hxx
#define malfunctions_hxx

// include the dusime header
#include <dusime.h>
USING_DUECA_NS;

// This includes headers for the objects that are sent over the channels
#include "comm-objects.h"

// include headers for functions/classes you need in the module
#include <GtkGladeWindow.hxx>


/** A module.

    The instructions to create an module of this class from the Scheme
    script are:

    \verbinclude malfunctions.scm
*/
class malfunctions: public SimulationModule
{
  /** self-define the module type, to ease writing the parameter table */
  typedef malfunctions _ThisModule_;

private: // simulation data
  // declare the data you need in your simulation

  // GUI
  GtkGladeWindow winglade;
  GtkWidget  *P_engine_button;
  GtkWidget  *Pleft;
  GtkWidget  *Pright;
  GtkWidget  *PLEFT_RPM;
  GtkWidget  *PRIGHT_RPM;
  GtkWidget  *g_engine_time_left;
  GtkWidget  *g_engine_time_right;
  GtkWidget  *P_mass_button;
  GtkWidget  *Px;
  GtkWidget  *Py;
  GtkWidget  *Pz;
  GtkWidget  *Pmass;
  GtkWidget  *Prate;
  GtkWidget  *POld_x;
  GtkWidget  *POld_y;
  GtkWidget  *POld_z;
  GtkWidget  *POld_mass;
  GtkWidget  *P_control_button;
  GtkWidget  *Paileron;
  GtkWidget  *Prudder;
  GtkWidget  *Prudder_bias;
  GtkWidget  *PARI;
  GtkWidget  *PScenario;
  // display
  GtkWidget *g_frozen_v;
  GtkWidget *g_frozen_h;
  GtkWidget *g_offset_v_value;
  GtkWidget *g_offset_v_time;
  GtkWidget *g_offset_h_value;
  GtkWidget *g_offset_h_time;

  GtkWidget *g_GPS_failure;
  GtkWidget *g_VOR_failure;
  GtkWidget *g_ADC_failure;
  GtkWidget *g_PFD_failure;
  GtkWidget *g_GMU_failure;
  GtkWidget *g_HSI_failure;
  GtkWidget *g_AFCS_pit_failure;
  GtkWidget *g_AFCS_rol_failure;
  GtkWidget *g_clogged_sp;
  GtkWidget *g_clogged_pt;

  char text[12];

public: // GTK callbacks
  // Process button clicks
  void onControlButtonClicked(GtkButton *button, gpointer user_data);
  void onMassButtonClicked(GtkButton *button, gpointer user_data);
  void onEngineButtonClicked(GtkButton *button, gpointer user_data);
  void onDisplayButtonClicked(GtkButton *button, gpointer user_data);

  void onFailureButtonClicked(GtkButton *button, gpointer user_data);
  void onFailureclearButtonClicked(GtkButton *button, gpointer user_data);

  // Interface to the position and size of the window
  bool setWindowPositionSize(const vector< int >& p_vector);

private: // trim calculation data
  // declare the trim calculation data needed for your simulation

private: // snapshot data
  // declare, if you need, the room for placing snapshot data

private: // channel access
  // declare access tokens for all the channels you read and write
  // examples:
  // ChannelReadToken    r_mytoken;
  // ChannelWriteToken   w_mytoken;
  EventChannelWriteToken<MassEvent> mass_token;
  EventChannelWriteToken<EngineEvent> engine_token;
  EventChannelWriteToken<ControlEvent> control_token;
  EventChannelWriteToken<DisplayEvent> display_token;
  EventChannelWriteToken<FailureEvent> failure_token;

  EventChannelReadToken<MassEvent> mass_feedback_token;

  EventChannelReadToken<MassEvent> mass_read_token;
  EventChannelReadToken<EngineEvent> engine_read_token;
  EventChannelReadToken<ControlEvent> control_read_token;
  EventChannelReadToken<DisplayEvent> display_read_token;

private: // activity allocation
  /** You might also need a clock. Don't mis-use this, because it is
      generally better to trigger on the incoming channels */
  //PeriodicAlarm        myclock;

  /** Callback object for simulation calculation. */
  Callback<malfunctions>  cb1;

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
  malfunctions(Entity* e, const char* part, const PrioritySpec& ts);

  /** Continued construction. This is called after all script
      parameters have been read and filled in, according to the
      parameter table. Your running environment, e.g. for OpenGL
      drawing, is also prepared. Any lengty initialisations (like
      reading the 4 GB of wind tables) should be done here.
      Return false if something in the parameters is wrong (by
      the way, it would help if you printed what!) May be deleted. */
  bool complete();

  /** Destructor. */
  ~malfunctions();

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
