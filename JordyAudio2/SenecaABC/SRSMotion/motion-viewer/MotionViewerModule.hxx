/* ------------------------------------------------------------------   */
/*      item            : MotionViewerModule.hxx
        made by         : stroosma
        date            : 010726
	category        : header file 
        description     : 
	changes         : 010726 first version
        language        : C++
*/

#ifndef MotionViewerModule_hxx
#define MotionViewerModule_hxx

#ifdef MotionViewerModule_cxx
const static char h_id[] =
"$Id: MotionViewerModule.hxx,v 1.3 2019/10/01 12:32:49 fltsim Exp $";
#endif

// include the dusime header
#include <dusime.h>

// include headers for the objects that are sent over the channels
//#include "MotionGimbalPositions.hxx"
#include "comm-objects.h"

// include headers for functions/classes you need in the module
#include "MotionViewer.hxx"

// 25APR2002 defines for the status word
#define MOTION_TEST             0X01
#define JACK_BRAKE              0X02
#define JACK_MIN                0X04
#define JACK_MAX                0X08

/** A simulation module. */
class MotionViewerModule: public SimulationModule
{
private: // simulation data
  // declare the data you need in your simulation
	MotionViewer *drawer;
	
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
  StreamChannelReadToken<MotionGimbalPositions> mgp_token;
  StreamChannelReadToken<MotionCommandedPosVelAcc> mcpva_token;
		
private: // activity allocation
  /// Callback object for simulation calculation
  Callback<MotionViewerModule>  cb1;

  /// Callback object for trim calculation
  //Callback<MotionViewerModule>  cb2;

  /// Activity for simulation calculation
  ActivityCallback      do_calc;

  /// Activity for trim calculation
  //ActivityCallback      do_trim;
  
public: // class name and trim/parameter tables
  /// Name of the module.
  static const char* const           classname;

  /// Return the initial condition table
  static const IncoTable*            getMyIncoTable();

  /// Return the parameter table
  static const ParameterTable*       getMyParameterTable();
  
public: // construction and further specification
  /** Constructor. Is normally called from scheme/the creation script. */
  MotionViewerModule(Entity* e, const char* part, const PrioritySpec& ts);

	// called at the start when object is complete but not "started"
	bool complete(void);
	
  /** Destructor. */
  ~MotionViewerModule();

  // add here the member functions you want to be called with further 
  // parameters. These are then also added in the parameter table
  // The most common one (addition of time spec) is given here. 
  // Delete if not needed!

  /** Specify a time specification for the simulation activity. */
  bool setTimeSpec(const TimeSpec& ts);

public: // member functions for cooperation with DUECA
  /// indicate that everything is ready
  bool isPrepared();

  /// start responsiveness to input data
  void startModule(const TimeSpec &time);
  
  /// stop responsiveness to input data
  void stopModule(const TimeSpec &time);

public: // member functions for cooperation with DUSIME
  /// Snapshot capability, sending
  Snapshot* sendSnapshot(const TimeSpec& t, bool inco);
  
  /// Restoring state from snapshot
  void loadSnapshot(const TimeSpec& t, const Snapshot& snap);

public: // member functions that are called for activities
  /// the method that implements the main calculation
  void doCalculation(const TimeSpec& ts);

  /// the method that handles incoming events
  void receiveEvent(const TimeSpec& ts);
 
  /** Performs a trim calculation. Should NOT use current state 
      uses event channels parallel to the stream data channels,
      calculates based on the event channel input, the steady state
      output. */
  void doTrimCalculation(const TimeSpec& ts);

public: // Member functions for displays
	// Specify window position and size.
	bool setWindowPositionSize(const vector<int> &p_vector);
};

#endif
