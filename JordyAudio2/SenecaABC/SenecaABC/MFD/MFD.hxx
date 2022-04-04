/* ------------------------------------------------------------------   */
/*      item            : G1000.hxx
        made by         : jcomans
	from template   : DusimeModuleTemplate.hxx
        template made by: Rene van Paassen
        date            : Mon Mar 31 18:03:23 2014
	category        : header file
        description     :
	changes         : Mon Mar 31 18:03:23 2014 first version
	template changes: 030401 RvP Added template creation comment
        language        : C++
*/

#ifndef MFD_hxx
#define MFD_hxx

// include the dusime header
#include <dusime.h>
USING_DUECA_NS;

// This includes headers for the objects that are sent over the channels
#include "comm-objects.h"

// include headers for functions/classes you need in the module
#include "MFDGLWindow.hxx"

#include <boost/scoped_ptr.hpp>

/** A module.

    The instructions to create an module of this class from the Scheme
    script are:

    \verbinclude g1000.scm
*/
class MFD: public SimulationModule
{
private: // simulation data
  // declare the data you need in your simulation
  MFDGLWindow g1000_glwindow_;

  bool fpl_page;
  bool mouse_left;
  bool reset_gear;

  int mouse_x;
  int mouse_y;
  float rudder_bias, gear_pos, eventgeardown;

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
  StreamChannelReadToken<CitationOutput> citation_out_read_token_;
  StreamChannelReadToken<SecondaryControls> secondary_controls_read_token_;
  EventChannelReadToken<AP2G1000Channel> ap2g_token;
  EventChannelReadToken<APIncoEvent> apinco_token;
  EventChannelReadToken<FailureEvent> fail_token;
  EventChannelReadToken<GFC700Event> gfc_token;
  StreamChannelReadToken<AutopilotChannel> ap_token;
  // StreamChannelReadToken<ManifoldChannel> ma_token;
  EventChannelReadToken<ControlEvent> control_token;
  EventChannelReadToken<Trim_inco> trim_inco_token;

  typedef StreamChannelReadToken<AutopilotTargets> APTargetsReadToken;
  boost::scoped_ptr<APTargetsReadToken> ap_targets_read_token_;

private: // activity allocation
  /** You might also need a clock. Don't mis-use this, because it is
      generally better to trigger on the incoming channels */
  //PeriodicAlarm        myclock;

  Callback<MFD>   _display_update_callback;
  ActivityCallback  _display_update_activity;


public: // class name and trim/parameter tables
  /** Name of the module. */
  static const char* const           classname;

  /** Return the initial condition table. */
  static const IncoTable*            getMyIncoTable();

  /** Return the parameter table. */
  static const ParameterTable*       getMyParameterTable();

public: // construction and further specification
  /** Constructor. Is normally called from scheme/the creation script. */
  MFD(Entity* e, const char* part, const PrioritySpec& ts);

  /** Continued construction. This is called after all script
      parameters have been read and filled in, according to the
      parameter table. Your running environment, e.g. for OpenGL
      drawing, is also prepared. Any lengty initialisations (like
      reading the 4 GB of wind tables) should be done here.
      Return false if something in the parameters is wrong (by
      the way, it would help if you printed what!) May be deleted. */
  bool complete();

  /** Destructor. */
  ~MFD();

  // add here the member functions you want to be called with further
  // parameters. These are then also added in the parameter table
  // The most common one (addition of time spec) is given here.
  // Delete if not needed!

  /** Specify a time specification for the simulation activity. */
  bool setTimeSpec(const TimeSpec& ts);

  bool setWindowPositionSize(const vector<int> &p);

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
};

#endif
