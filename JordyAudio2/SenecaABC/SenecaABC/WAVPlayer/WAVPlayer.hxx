/* ------------------------------------------------------------------   */
/*      item            : WAVPlayer.hxx
        made by         : jcomans
  from template   : DusimeModuleTemplate.hxx
        template made by: Rene van Paassen
        date            : Wed Sep 12 20:39:31 2012
  category        : header file
        description     :
  changes         : Wed Sep 12 20:39:31 2012 first version
  template changes: 030401 RvP Added template creation comment
        language        : C++
*/

#ifndef WAVPlayer_hxx
#define WAVPlayer_hxx

// include the dusime header
#include <dusime.h>
USING_DUECA_NS;

// This includes headers for the objects that are sent over the channels
#include "comm-objects.h"

// include headers for functions/classes you need in the module
#include <PeriodicAlarm.hxx>
#include "SimpleSoundPlayer.hxx"


/** A module.

    The instructions to create an module of this class from the Scheme
    script are:

    \verbinclude wav-player.scm
*/
class WAVPlayer: public SimulationModule
{
private: // simulation data
  enum Sounds
  {
    NO = 0,
    ENGINE_LEFT,
    ENGINE_RIGHT,
    ENGINE_LEFT_IDLE,
    ENGINE_RIGHT_IDLE,
    MAX_SOUNDS
  };

  // declare the data you need in your simulation
  SimpleSoundPlayer sound_player;
  
  // overall gain setting
  float master_gain;

  // List the sounds we want to play
  std::vector < int > m_sound_list;

  // Keep track of how many times we play it and the maximum
  std::vector < uint > m_sound_max_repeat;
  std::vector < uint > m_sound_times_played;
  
  // Engine sound pitch settings
  float engine_pitch_min, engine_pitch_den;
  float rpm_idle, pitch_rpm_idle;
  float rpm_max, pitch_rpm_max;
  float max_torque;

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
  StreamChannelReadToken<PropSoundData> sounddata_token;
    
  ChannelWriteToken w_audio1;
  ChannelWriteToken w_audio2;
  ChannelWriteToken w_audio3;
  ChannelWriteToken w_audio4;

private: // activity allocation

  /** Callback object for simulation calculation. */
  Callback<WAVPlayer>  cb1;

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
  WAVPlayer(Entity* e, const char* part, const PrioritySpec& ts);

  /** Continued construction. This is called after all script
      parameters have been read and filled in, according to the
      parameter table. Your running environment, e.g. for OpenGL
      drawing, is also prepared. Any lengty initialisations (like
      reading the 4 GB of wind tables) should be done here.
      Return false if something in the parameters is wrong (by
      the way, it would help if you printed what!) May be deleted. */
  bool complete();

  /** Destructor. */
  ~WAVPlayer();

  // add here the member functions you want to be called with further
  // parameters. These are then also added in the parameter table
  // The most common one (addition of time spec) is given here.
  // Delete if not needed!

  /** Specify a time specification for the simulation activity. */
  bool setTimeSpec(const TimeSpec& ts);

  /** Request check on the timing. */
  bool checkTiming(const vector<int>& i);

  /** Add sound files */
  bool addSoundFile(const vstring& file);
  bool addLoopedSoundFile(const vstring& file);
  
  /* Engine sound pitch settings */
  bool setRPMPitch(const vector<float>& i);

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
