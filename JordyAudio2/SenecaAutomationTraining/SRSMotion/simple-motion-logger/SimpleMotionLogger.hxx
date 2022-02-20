/* ------------------------------------------------------------------   */
/*      item            : SimpleMotionLogger.hxx
        made by         : simona
        date            : 020501
	category        : header file 
        description     : 
	changes         : 020501 first version
        language        : C++
*/

#ifndef SimpleMotionLogger_hxx
#define SimpleMotionLogger_hxx

#ifdef SimpleMotionLogger_cxx
static const char h_id[] =
"$Id: SimpleMotionLogger.hxx,v 1.2 2021/10/25 12:50:16 ostroosma Exp $";
#endif

// include the dusime header
#include <dusime.h>

// include headers for the objects that are sent over the channels
/*#include "VehicleCabMotion.hxx"
#include "SimulatorMotionAcceleration.hxx"
#include "MotionCommandedPosVelAcc.hxx"
#include "MotionActuatorLengths.hxx"
#include "SimulatorCabMotion.hxx"
#include "MotionBaseResultData.hxx"*/
#include "comm-objects.h"

// include headers for functions/classes you need in the module
#include <fstream>

/** A simulation module. */
class SimpleMotionLogger: public SimulationModule
{
private: // simulation data
  // declare the data you need in your simulation
  // output file
  ofstream out;

  float measured_pos[6];
  float measured_len[6];

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
  StreamChannelReadToken<VehicleCabMotion> vcm_token;
  StreamChannelReadToken<SimulatorMotionAcceleration> sma_token;
  StreamChannelReadToken<MotionCommandedPosVelAcc> mcpva_token;
  StreamChannelReadToken<MotionActuatorLengths> mal_token;
  StreamChannelReadToken<SimulatorCabMotion> scm_token;
  StreamChannelReadToken<MotionBaseResultData> mbrd_token;
  StreamChannelReadToken<MotionFilterUserData> fud_token;

private: // activity allocation
  /// Callback object for simulation calculation
  Callback<SimpleMotionLogger>  cb1;

  /// Activity for simulation calculation
  ActivityCallback      do_calc;

public: // class name and trim/parameter tables
  /// Name of the module.
  static const char* const           classname;

  /// Return the initial condition table
  static const IncoTable*            getMyIncoTable();

  /// Return the parameter table
  static const ParameterTable*       getMyParameterTable();

public: // construction and further specification
  /** Constructor. Is normally called from scheme/the creation script. */
  SimpleMotionLogger(Entity* e, const char* part, const PrioritySpec& ts);

  /** Continued construction. This is called after all script
      parameters have been read and filled in, according to the
      parameter table. Your running environment, e.g. for OpenGL
      drawing, is also prepared. Any lengty initialisations (like
      reading the 4 GB of wind tables) should be done here.
      Return false if something in the parameters is wrong (by
      the way, it would help if you printed what!) May be deleted. */
  bool complete();

  /** Destructor. */
  ~SimpleMotionLogger();

  // add here the member functions you want to be called with further
  // parameters. These are then also added in the parameter table
  // The most common one (addition of time spec) is given here.
  // Delete if not needed!

  /** Specify a time specification for the simulation activity. */
  bool setTimeSpec(const TimeSpec& ts);

  /** Request check on the timing. */
  bool checkTiming(const vector<int>& i);

public: // member functions for cooperation with DUECA
  /// indicate that everything is ready
  bool isPrepared();

  /// start responsiveness to input data
  void startModule(const TimeSpec &time);

  /// stop responsiveness to input data
  void stopModule(const TimeSpec &time);

public: // the member functions that are called for activities
  /// the method that implements the main calculation
  void doCalculation(const TimeSpec& ts);

public: // member functions for cooperation with DUSIME
  /// For the Snapshot capability, fill the snapshot "snap" with the
  /// data saved at a point in your simulation (if from_trim is false)
  /// or with the state data calculated in the trim calculation (if
  /// from_trim is true)
  void fillSnapshot(const TimeSpec& ts,
		    Snapshot& snap, bool from_trim);

  /// Restoring the state of the simulation from a snapshot
  void loadSnapshot(const TimeSpec& t, const Snapshot& snap);

  /** Perform a trim calculation. Should NOT use current state
      uses event channels parallel to the stream data channels,
      calculates, based on the event channel input, the steady state
      output. */
  void trimCalculation(const TimeSpec& ts, const IncoMode& mode);
};

#endif
