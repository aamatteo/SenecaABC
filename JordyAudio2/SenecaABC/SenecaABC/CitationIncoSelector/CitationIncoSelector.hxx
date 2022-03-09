/* ------------------------------------------------------------------   */
/*      item            : CitationIncoSelector.hxx
        made by         : stroosma
	from template   : DusimeModuleTemplate.hxx
        template made by: Rene van Paassen
        date            : Wed Jan 12 10:47:18 2005
	category        : header file 
        description     : 
	changes         : Wed Jan 12 10:47:18 2005 first version
	template changes: 030401 RvP Added template creation comment
        language        : C++
*/

#ifndef CitationIncoSelector_hxx
#define CitationIncoSelector_hxx

#ifdef CitationIncoSelector_cxx
static const char h_id[] =
"$Id: CitationIncoSelector.hxx,v 1.1 2020/03/20 16:17:33 ostroosma Exp $";
#endif

// include the dusime header
#include <dusime.h>

// This includes headers for the objects that are sent over the channels
#include "comm-objects.h"

// Seneca model data
#include "StatesOutputs.h"
#include "Citation.h"//TODO #include "pa34model_dueca_8b.h"

// include headers for functions/classes you need in the module
#include <Ticker.hxx>
//extern "C"{
//#include <gtk/gtk.h>
//}
// headers for file juggling
#include <dirent.h>

#include <list>

#include <GtkGladeWindow.hxx>

USING_DUECA_NS

/** A module.
    
    The instructions to create an module of this class from the Scheme
    script are:

    \verbinclude citation-inco-selector.scm
*/
class CitationIncoSelector: public SimulationModule
{
private: // simulation data
  // declare the data you need in your simulation
  SimulationState prev_state;
  int vliegtuigtype;
  GtkGladeWindow winglade;
  
  // GTK widgets buttons
  GtkWidget *sendbutton;
  GtkWidget *reposbutton;
  // GTK widgets
  GtkWidget *theWindow;
  GtkWidget *combo1;
  GtkWidget *turbbutton;
  GtkWidget *turbspinner;
  GtkWidget *filewindow;
  GtkWidget *reposX;
  GtkWidget *reposY;
  GtkWidget *reposZ;
  GtkWidget *reposPsi;
  GtkWidget *lat_N;
  GtkWidget *long_E;
  GtkWidget *windbutton;
  GtkWidget *windvelspinner;
  GtkWidget *winddirspinner;
  GtkWidget *shearbutton;
  
  // temp text
  char text[12];

  // template for the inco files
  std::list<string> incotemplate;
  
  // incoming snapshot, to be saved
  list<double> incoming_snap;
  
 // trimstanden opslaan
 bool snap_trim;

 float trim_de, trim_da, trim_dr, trim_pla1, trim_pla2, trim_gear, trim_flaps;

  // snap is available, so send trim event
  bool snap_available;


public: // own public stuff
  // pointer to the module for C GTK callback
  static CitationIncoSelector* theOne;

  // Process a "Send" button click
  void onSendButtonClicked(GtkButton *button,
			   gpointer user_data);

  // Process a "Turbulence enable" button toggle
  void onCheckButton1Toggled(GtkButton *button,
			     gpointer user_data);

  // Process a "Take snapshot" button click
  void onSnapshotButtonClicked(GtkButton *button,
			       gpointer user_data);
  
  // Process a Cancel button click in filewindow
  void onCancelButtonClicked(GtkButton *button,
			gpointer user_data);
  
  // Process an OK button click in filewindow
  void onOKButtonClicked(GtkButton *button,
			 gpointer user_data);

  // Process a "Reposition" button click
  void onReposButtonClicked(GtkButton *button,
			    gpointer user_data);

  // Process a "Wind" button click
  void onWindButtonClicked(GtkButton *button,
			    gpointer user_data);


private: // own private functions
  // Glade generated function to create the window (copy&paste)
  GtkWidget* create_CitIncoSel(void);

  // Glade generated function to create the file selector window (copy&paste)
  GtkWidget* create_fileselection1 (void);

  // Read snapshot data from inco file
  Snapshot* readInco(const char* filename);
  
   // Read snapshot data from inco file
  bool readIncoTemplate(const char* filename);
  
 // Send the initial condition snapshot to the model
  void sendInco(Snapshot* snap);

private: // trim calculation data
  // declare the trim calculation data needed for your simulation

private: // snapshot data
  // declare, if you need, the room for placing snapshot data

private: // channel access
  // declare StreamChannelReadToken<Type>, StreamChannelWriteToken<Type>
  // EventChannelReadToken<Type>, EventChannelWriteToken<Type>
  // access tokens for all the channels you read and write
  // example
  // StreamChannelReadToken<MyData>  my_token;
  EventChannelWriteToken<Snapshot> snap_token;
  EventChannelWriteToken<STARSelect> star_token;
  EventChannelWriteToken<SnapshotRequest> sr_token;
  EventChannelWriteToken<Reposition> repos_token;
  EventChannelWriteToken<Trim_inco> trim_inco_token;
  StreamChannelReadToken<CitationOutput> in_token;
  StreamChannelReadToken<CitationPilotInput> cpi_token;
  EventChannelReadToken<INCOSelect> inco_sel_token;
  EventChannelWriteToken<WindEvent> turb_write_token;
  EventChannelReadToken<WindEvent> turb_read_token;
  
  // utility functions
  void sendWindEvent();

private: // activity allocation


  /** Callback object for simulation calculation. */
  Callback<CitationIncoSelector>  cb1;

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
  CitationIncoSelector(Entity* e, const char* part, const PrioritySpec& ts);

  /** Continued construction. This is called after all script
      parameters have been read and filled in, according to the
      parameter table. Your running environment, e.g. for OpenGL
      drawing, is also prepared. Any lengty initialisations (like
      reading the 4 GB of wind tables) should be done here.
      Return false if something in the parameters is wrong (by
      the way, it would help if you printed what!) May be deleted. */
  bool complete();

  /** Destructor. */
  ~CitationIncoSelector();

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

extern "C" {
  // the GTK callback function for the Cancel button in the file window
  static void CitationIncoSelector_on_cancel_button1_clicked(GtkButton *button,
							     gpointer user_data);

  // the GTK callback function for the OK button in the file window
  static void CitationIncoSelector_on_ok_button1_clicked(GtkButton *button,
							 gpointer user_data);

  // the compare function to filter .inco files out of the directory
  static int is_inco_file(const struct dirent* entry);
}

#endif
