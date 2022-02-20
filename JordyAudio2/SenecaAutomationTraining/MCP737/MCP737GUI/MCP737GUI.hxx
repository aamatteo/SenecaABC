/* ------------------------------------------------------------------   */
/*      item            : MCP737GUI.hxx
        made by         : stroosma
	from template   : DusimeModuleTemplate.hxx
        template made by: Rene van Paassen
        date            : Fri Jun 25 13:20:17 2004
	category        : header file 
        description     : 
	changes         : Fri Jun 25 13:20:17 2004 first version
	template changes: 030401 RvP Added template creation comment
        language        : C++
*/

#ifndef MCP737GUI_hxx
#define MCP737GUI_hxx

#ifdef MCP737GUI_cxx
static const char h_id[] =
"$Id: MCP737GUI.hxx,v 1.6 2017/03/16 16:10:36 dirkvanbaelen Exp $";
#endif

// include the dusime header
#include <dusime.h>

// This includes headers for the objects that are sent over the channels
#include "comm-objects.h"

// include headers for functions/classes you need in the module
#include <DuecaGLWindow.hxx>
#include "project_utilities.h"
#include "MCPElement.hxx"
#include <list>
#include <map>

/** A module.
    
    The instructions to create an module of this class from the Scheme
    script are:

    \verbinclude mcp7-3-7-gui.scm
*/
class MCP737GUI: public SimulationModule, public DuecaGLWindow
{
private: // simulation data
  // declare the data you need in your simulation
  ProjectUtilities utils;

  // all the screen elements for GUI events
  list<MCPElement*> in_elements;
  // all the output elements for hardware events
  map<MCP737Event::msgType, MCPElement*> out_elements;
  void fillElementsList();

  // texture id
  GLuint texture_id;

  // channel distribution
  bool join_master;

  // pointers to Mach/IAS elements for switching
  MCPElement *mach_ctrl1, *mach_ctrl2, *mach_number;
  MCPElement *ias_ctrl1, *ias_ctrl2, *ias_number;

  // pointer to the AT light for switching
  MCPElement *at_lgt;

  // pointer to the V/S element for switching
  MCPElement *vs_number;

  // Storage for the scheme entries for the position of the window
  int m_position_x;
  int m_position_y;

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
  EventChannelReadToken<MCP737Event> in_token;
  EventChannelWriteToken<MCP737Event> *out_token;

private: // activity allocation
  /** Callback object for simulation calculation. */
  Callback<MCP737GUI>  cb1;

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
  MCP737GUI(Entity* e, const char* part, const PrioritySpec& ts);

  /** Continued construction. This is called after all script
      parameters have been read and filled in, according to the
      parameter table. Your running environment, e.g. for OpenGL
      drawing, is also prepared. Any lengty initialisations (like
      reading the 4 GB of wind tables) should be done here.
      Return false if something in the parameters is wrong (by
      the way, it would help if you printed what!) May be deleted. */
  bool complete();

  /** Destructor. */
  ~MCP737GUI();

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

public:
  // OpenGL stuff

  /** \group Prototypes for interation handling. 
      This class adheres to -- as much as is practical -- the calling
      conventions for Glut. */

  /** This is called if the size of the window is changed. You might
      need to update the image set-up for a different screen
      format. */
  virtual void reshape(int x, int y);

  /** Called when a key is pressed. */
  //virtual void keyboard(unsigned char key, int x, int y);

  /** Called when a function key is pressed.
      \todo Does not currently work under gtk. */
  //virtual void special(int key, int x, int y);
  
  /** This is called whenever the display needs to be redrawn. When
      called, the appropriate window has been made current. */
  virtual void display();

  /** This is called when the window is ready, for first-time
      set-up. */
  virtual void initGL();

  /** This is called whenever a mouse button event comes in */
  virtual void mouse(int button, int state, int x, int y);

  /** This is called whenever a mouse motion event comes in. */
  //virtual void motion(int x, int y);

  /** This is called whenever a mouse motion event comes in, but none
      of the buttons are pressed. */
  //virtual void passive(int x, int y);

public:
  // Dueca-scheme startup functions
  // Interface to the position the window
  bool setWindowPosition( const vector< int >& p_vector );

};

#endif
