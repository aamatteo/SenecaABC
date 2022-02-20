/* ------------------------------------------------------------------   */
/*      item            : GFC700GUI.hxx
        made by         : jordy
	from template   : DusimeModuleTemplate.hxx
        template made by: Rene van Paassen
        date            : Fri Mar 27 18:11:28 2020
	category        : header file
        description     :
	changes         : Fri Mar 27 18:11:28 2020 first version
	template changes: 030401 RvP Added template creation comment
        language        : C++
        copyright       : (c) 2016 TUDelft-AE-C&S
*/

#ifndef GFC700GUI_hxx
#define GFC700GUI_hxx

// include the dusime header
#include <dusime.h>
USING_DUECA_NS;

// This includes headers for the objects that are sent over the channels
#include "comm-objects.h"

// include headers for functions/classes you need in the module
#include <Ticker.hxx>

#include <dirent.h>

#include <list>

#include <GtkGladeWindow.hxx>


/** A module.

    The instructions to create an module of this class from the Scheme
    script are:

    \verbinclude gf-c700-gui.scm
*/
class GFC700GUI: public SimulationModule
{
  /** self-define the module type, to ease writing the parameter table */
  typedef GFC700GUI _ThisModule_;

private:

  SimulationState prev_state;

  GtkGladeWindow winglade;

  GtkWidget *theWindow;
  GtkWidget *fixed1;
  GtkWidget *apr_button;
  GtkWidget *nav_button;
  GtkWidget *hdg_button;
  GtkWidget *ap_button;
  GtkWidget *fd_button;
  GtkWidget *alt_button;
  GtkWidget *vnv_button;
  GtkWidget *bc_button;
  GtkWidget *vs_button;
  GtkWidget *noseup_button;
  GtkWidget *flc_button;
  GtkWidget *nosedn_button;
  GtkWidget *alt_select;
  GtkWidget *hdg_select;
  GtkWidget *crs_select;
  GtkWidget *cdi_button;

  int hdg;
  int prev_hdg;

  int alt;
  int prev_alt;

  int crs;
  int prev_crs;

  // enum msg{
	// GFC700_NONE,
	// GFC700_AP,
	// GFC700_FD,
	// GFC700_HDG,
	// GFC700_ALT,
	// GFC700_NAV,
	// GFC700_VNV,
	// GFC700_APR,
	// GFC700_BC,
	// GFC700_VS,
	// GFC700_NOSEUP,
	// GFC700_FLC,
	// GFC700_NOSEDN,
  // };
  bool apr_pressed;
  // float alt_select_value;

public:

  bool setWindowPositionSize(const vector< int >& p_vector);

  void on_apr_button_clicked(GtkButton *button,
         gpointer user_data);

  void on_nav_button_clicked(GtkButton *button,
        gpointer user_data);

  void on_hdg_button_clicked(GtkButton *button,
        gpointer user_data);

  void on_ap_button_clicked(GtkButton *button,
        gpointer user_data);

  void on_fd_button_clicked(GtkButton *button,
        gpointer user_data);

  void on_alt_button_clicked(GtkButton *button,
        gpointer user_data);

  void on_vnv_button_clicked(GtkButton *button,
        gpointer user_data);

  void on_bc_button_clicked(GtkButton *button,
        gpointer user_data);

  void on_vs_button_clicked(GtkButton *button,
        gpointer user_data);

  void on_noseup_button_clicked(GtkButton *button,
        gpointer user_data);

  void on_flc_button_clicked(GtkButton *button,
        gpointer user_data);

  void on_nosedn_button_clicked(GtkButton *button,
        gpointer user_data);

  void on_cdi_button_clicked(GtkButton *button,
        gpointer user_data);

  void alt_select_changed(GtkSpinButton *spin_button,
        gpointer user_data);

  void hdg_select_changed(GtkSpinButton *spin_button,
        gpointer user_data);

  void crs_select_changed(GtkSpinButton *spin_button,
        gpointer user_data);
private:
  // Glade generated function to create the window (copy&paste)
  //GtkWidget* create_GFC700(void);



private: // simulation data
  // declare the data you need in your simulation

private: // trim calculation data
  // declare the trim calculation data needed for your simulation

private: // snapshot data
  // declare, if you need, the room for placing snapshot data

private: // channel access
  // declare access tokens for all the channels you read and write
  // examples:
  // ChannelReadToken    r_mytoken;
  // ChannelWriteToken   w_mytoken;
  EventChannelWriteToken<GFC700Event> gfc_token;

private: // activity allocation
  /** You might also need a clock. Don't mis-use this, because it is
      generally better to trigger on the incoming channels */
  PeriodicAlarm        myclock;

  /** Callback object for simulation calculation. */
  Callback<GFC700GUI>  cb1;

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
  GFC700GUI(Entity* e, const char* part, const PrioritySpec& ts);

  /** Continued construction. This is called after all script
      parameters have been read and filled in, according to the
      parameter table. Your running environment, e.g. for OpenGL
      drawing, is also prepared. Any lengty initialisations (like
      reading the 4 GB of wind tables) should be done here.
      Return false if something in the parameters is wrong (by
      the way, it would help if you printed what!) May be deleted. */
  bool complete();

  /** Destructor. */
  ~GFC700GUI();

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
