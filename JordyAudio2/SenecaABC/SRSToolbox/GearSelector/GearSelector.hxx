/* ------------------------------------------------------------------   */
/*      item            : GearSelector.hxx
        made by         : stroosma
	from template   : DusimeModuleTemplate.hxx
        template made by: Rene van Paassen
        date            : Thu Nov  6 09:01:34 2003
	category        : header file 
        description     : 
	changes         : Thu Nov  6 09:01:34 2003 first version
	template changes: 030401 RvP Added template creation comment
        language        : C++
*/

#ifndef GearSelector_hxx
#define GearSelector_hxx

#ifdef GearSelector_cxx
static const char h_id[] =
"$Id: GearSelector.hxx,v 1.7 2008/03/17 13:21:44 jellerbroek Exp $";
#endif

// include the dusime header
#include <dusime.h>

// This includes headers for the objects that are sent over the channels
#include "comm-objects.h"

// include headers for functions/classes you need in the module
#include <GtkGladeWindow.hxx>

/** A simulation module. */
class GearSelector: public SimulationModule
{
private: // simulation data
  // declare the data you need in your simulation

  GtkGladeWindow winglade;
#if GTK_MAJOR_VERSION == 2
  GtkLabel          *masterlabel;
#else
  GtkWindow         *theWindow;
#endif
  GtkToggleButton   *gearup;
  GtkToggleButton   *gearoff;
  GtkToggleButton   *geardwn;
 
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
  StreamChannelWriteToken<SecondarySwitches> *out_token;
  StreamChannelReadToken<SecondarySwitches> *in_token;

private: // activity allocation
  /** Callback object for simulation calculation. */
  Callback<GearSelector>  cb1;

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
  GearSelector(Entity* e, const char* part, const PrioritySpec& ts);

  /** Continued construction. This is called after all script
      parameters have been read and filled in, according to the
      parameter table. Your running environment, e.g. for OpenGL
      drawing, is also prepared. Any lengty initialisations (like
      reading the 4 GB of wind tables) should be done here.
      Return false if something in the parameters is wrong (by
      the way, it would help if you printed what!) May be deleted. */
  bool complete();

  /** Destructor. */
  ~GearSelector();

  // add here the member functions you want to be called with further 
  // parameters. These are then also added in the parameter table
  // The most common one (addition of time spec) is given here. 
  // Delete if not needed!

  /** Specify a time specification for the simulation activity. */
  bool setTimeSpec(const TimeSpec& ts);

  /** Request check on the timing. */
  bool checkTiming(const vector<int>& i);

  /** Set the (initial) state to Up. */
  bool setUp(const bool& b);

   /** Set the (initial) state to Off. */
  bool setOff(const bool& b);

  /** Set the (initial) state to Down. */
  bool setDown(const bool& b);

  /** Act as master (sending) or slave (receiving) */
  bool setMaster(const bool& b);
      
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
  void trimCalculation(const TimeSpec& ts, const IncoMode& mode);
};

#endif
