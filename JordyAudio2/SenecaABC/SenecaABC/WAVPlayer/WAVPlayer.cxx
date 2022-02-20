/* ------------------------------------------------------------------   */
/*      item            : WAVPlayer.cxx
        made by         : jcomans
  from template   : DusimeModuleTemplate.cxx
        template made by: Rene van Paassen
        date            : Wed Sep 12 20:39:31 2012
  category        : body file
        description     :
  changes         : Wed Sep 12 20:39:31 2012 first version
  template changes: 030401 RvP Added template creation comment
                    060512 RvP Modified token checking code
        language        : C++
*/

static const char c_id[] =
"$Id: WAVPlayer.cxx,v 1.1.1.1 2022/02/17 15:04:28 matteopiras Exp $";

#define WAVPlayer_cxx
// include the definition of the module class
#include "WAVPlayer.hxx"

// include the debug writing header, by default, write warning and
// error messages
//#define D_MOD
#define I_MOD
#define W_MOD
#define E_MOD
#include <debug.h>

// include additional files needed for your calculation here
#include <cmath> // for log10

// the standard package for DUSIME, including template source
#define DO_INSTANTIATE
#include <dusime.h>

// class/module name
const char* const WAVPlayer::classname = "wav-player";

// initial condition/trim table
const IncoTable* WAVPlayer::getMyIncoTable()
{
  static IncoTable inco_table[] = {
    { NULL, NULL} };

  return inco_table;
}

// parameters to be inserted
const ParameterTable* WAVPlayer::getMyParameterTable()
{
  static const ParameterTable parameter_table[] = {
    { "set-timing",
      new MemberCall<WAVPlayer,TimeSpec>
        (&WAVPlayer::setTimeSpec), set_timing_description },

    { "check-timing",
      new MemberCall<WAVPlayer,vector<int> >
      (&WAVPlayer::checkTiming), check_timing_description },

    { "add-sound-file",
      new MemberCall<WAVPlayer,vstring>
      (&WAVPlayer::addSoundFile),
      "Add a new sound clip to the list" },

    { "master-gain",
      new VarProbe<WAVPlayer, float>
      (REF_MEMBER(&WAVPlayer::master_gain)),
      "Master gain for all sounds" },

    { "max-torque",
      new VarProbe<WAVPlayer, float>
      (REF_MEMBER(&WAVPlayer::max_torque)),
      "Maximum torque value" },

    { "rpm-pitch",
      new MemberCall<WAVPlayer, vector<float> >
      (&WAVPlayer::setRPMPitch),
      "Give 4 values: rpm_idle pitch_rpm_idle rpm_max pitch_rpm_max" },
    
//     { "add-looped-sound-file",
//       new MemberCall<WAVPlayer,vstring>
//       (&WAVPlayer::addLoopedSoundFile), "Add a new sound clip to the list" },
//

    { NULL, NULL, "please give a description of this module"} };

  return parameter_table;
}

// constructor
WAVPlayer::WAVPlayer(Entity* e, const char* part, const
           PrioritySpec& ps) :
  SimulationModule(e, classname, part, getMyIncoTable(), 0),

  // initialize the data you need in your simulation
  sound_player(),
  master_gain(1.0), //TODO set this in the sound_player itself
  m_sound_list( MAX_SOUNDS ),
  m_sound_max_repeat( MAX_SOUNDS ),
  m_sound_times_played( MAX_SOUNDS ),
  engine_pitch_min(0.0),
  engine_pitch_den(1.0),
  rpm_idle(800),
  pitch_rpm_idle(0.5),
  rpm_max(2800),
  pitch_rpm_max(2.5),
  //
  max_torque(0.080),

  // initialize the data you need for the trim calculation

  // initialize the channel access tokens
  // example
  // my_token(getId(), NameSet(getEntity(), "MyData", part)),

  sounddata_token( getId(), NameSet( getEntity(), "PropSoundData", part ) ),

  w_audio1(getId(), NameSet("audio", "AnyAudioClass", ""),
        "AudioObjectFixed", "xrpm1L",
          Channel::Continuous,
          Channel::OneOrMoreEntries, Channel::MixedPacking),

  w_audio2(getId(), NameSet("audio", "AnyAudioClass", ""),
        "AudioObjectFixed", "xrpm1R",
          Channel::Continuous,
          Channel::OneOrMoreEntries, Channel::MixedPacking),

  w_audio3(getId(), NameSet("audio", "AnyAudioClass", ""),
        "AudioObjectFixed", "xrpm2L",
          Channel::Continuous,
          Channel::OneOrMoreEntries, Channel::MixedPacking),

  w_audio4(getId(), NameSet("audio", "AnyAudioClass", ""),
        "AudioObjectFixed", "xrpm2R",
          Channel::Continuous,
          Channel::OneOrMoreEntries, Channel::MixedPacking),

 // label invullen en in modfile aantal parameters koppelen aan het label

  // activity initialization
  cb1(this, &WAVPlayer::doCalculation),
  do_calc(getId(), "Play a sound sample", &cb1, ps)
{
  // do the actions you need for the simulation

  // connect the triggers for simulation
  do_calc.setTrigger( sounddata_token );

  // Initialize all times played to zero
  for ( std::vector<uint>::iterator it = m_sound_times_played.begin(); it != m_sound_times_played.end(); ++it )
  {
    *it = 0;
  }
}

bool WAVPlayer::complete()
{
  /* All your parameters have been set. You may do extended
     initialisation here. Return false if something is wrong. */

  // List the sounds
  try
  {
    // left engine
    m_sound_max_repeat[ENGINE_LEFT] = 9999;
    m_sound_list[ENGINE_LEFT]       = sound_player.addSoundFile("audio/xrpm2L.wav");
    sound_player.setLoop( m_sound_list[ENGINE_LEFT], true );
    // right engine
    m_sound_max_repeat[ENGINE_RIGHT] = 9999;
    m_sound_list[ENGINE_RIGHT]       = sound_player.addSoundFile("audio/xrpm2R.wav");
    sound_player.setLoop( m_sound_list[ENGINE_RIGHT], true );
    // left engine idle
    m_sound_max_repeat[ENGINE_LEFT_IDLE] = 9999;
    m_sound_list[ENGINE_LEFT_IDLE]       = sound_player.addSoundFile("audio/xrpm1L.wav");
    sound_player.setLoop( m_sound_list[ENGINE_LEFT_IDLE], true );
    // right engine idle
    m_sound_max_repeat[ENGINE_RIGHT_IDLE] = 9999;
    m_sound_list[ENGINE_RIGHT_IDLE]       = sound_player.addSoundFile("audio/xrpm1R.wav");
    sound_player.setLoop( m_sound_list[ENGINE_RIGHT_IDLE], true );
    
  }
  catch ( ... )
  {
    E_MOD( getId() << '/' << classname << " Something went wrong with loading continuous engine sound." );
    m_sound_max_repeat[ENGINE_LEFT]  = 0;
    m_sound_list[ENGINE_LEFT]        = -1;
    m_sound_max_repeat[ENGINE_RIGHT] = 0;
    m_sound_list[ENGINE_RIGHT]       = -1;
    m_sound_max_repeat[ENGINE_LEFT_IDLE]  = 0;
    m_sound_list[ENGINE_LEFT_IDLE]        = -1;
    m_sound_max_repeat[ENGINE_RIGHT_IDLE] = 0;
    m_sound_list[ENGINE_RIGHT_IDLE]       = -1;
  }

  m_sound_list[ NO ] = -1;

  return true;
}

// destructor
WAVPlayer::~WAVPlayer()
{
  //
}

// as an example, the setTimeSpec function
bool WAVPlayer::setTimeSpec(const TimeSpec& ts)
{
  // a time span of 0 is not acceptable
  if (ts.getValiditySpan() == 0) return false;

  // specify the timespec to the activity
  do_calc.setTimeSpec(ts);

  // do whatever else you need to process this in your model
  // hint: ts.getDtInSeconds()

  // return true if everything is acceptable
  return true;
}

// and the checkTiming function
bool WAVPlayer::checkTiming(const vector<int>& i)
{
  if (i.size() == 3) {
    new TimingCheck(do_calc, i[0], i[1], i[2]);
  }
  else if (i.size() == 2) {
    new TimingCheck(do_calc, i[0], i[1]);
  }
  else {
    return false;
  }
  return true;
}

bool WAVPlayer::addSoundFile(const vstring& file)
{
  size_t idx = sound_player.addSoundFile( file.c_str() );
  sound_player.setLoop(idx, false);
  sound_player.setPitch(idx, 1.0);
  sound_player.setGain(idx, master_gain);

  return true;
}

bool WAVPlayer::addLoopedSoundFile(const vstring& file)
{
  const size_t idx = sound_player.addSoundFile( file.c_str() );

  sound_player.setLoop(idx, true);
  sound_player.setPitch(idx, 1.0);
  sound_player.setGain(idx, master_gain);

  return true;
}

bool WAVPlayer::setRPMPitch(const vector<float>& i)
{
  if (i.size() == 4)
  {
    rpm_idle        = i[0];
    pitch_rpm_idle  = i[1];
    rpm_max         = i[2];
    pitch_rpm_max   = i[3];
  }
  else
  {
    E_MOD(getId() << '/' << classname << ": error in rpm-pitch. Usage: rpm_idle pitch_rpm_idle rpm_max pitch_rpm_max");
    return false;
  }
  
  // Calculate engine sound pitch settings
  engine_pitch_den = ( rpm_max - rpm_idle ) / ( pitch_rpm_max - pitch_rpm_idle );
  engine_pitch_min = rpm_idle - pitch_rpm_idle*engine_pitch_den;
  I_MOD( classname << " Engine pitch calculated: min=" << engine_pitch_min 
                   << " den=" << engine_pitch_den 
                   << " Pitch is 1 at " << engine_pitch_min + engine_pitch_den << " RPM" );
  
  return true;
}

// tell DUECA you are prepared
bool WAVPlayer::isPrepared()
{
  bool res = true;

  // Example checking a token:
  // CHECK_TOKEN(w_somedata);
  CHECK_TOKEN( sounddata_token );
  CHECK_TOKEN( w_audio1 );
  CHECK_TOKEN( w_audio2 );
  CHECK_TOKEN( w_audio3 );
  CHECK_TOKEN( w_audio4 );

  // Example checking anything
  // CHECK_CONDITION(myfile.good());

  // return result of checks
  return res;
}

// start the module
void WAVPlayer::startModule(const TimeSpec &time)
{
  do_calc.switchOn(time);
}

// stop the module
void WAVPlayer::stopModule(const TimeSpec &time)
{
  do_calc.switchOff(time);
}

void WAVPlayer::fillSnapshot(const TimeSpec& ts, Snapshot& snap, bool from_trim) {}

void WAVPlayer::loadSnapshot(const TimeSpec& t, const Snapshot& snap) {}

void WAVPlayer::doCalculation(const TimeSpec& ts)
{
  switch( getAndCheckState(ts) ) {
    case SimulationState::HoldCurrent:
    {
      sound_player.stopAllSound();
      break;
    }
    case SimulationState::Replay:
    case SimulationState::Advance:
    {
      std::vector <Sounds> playback_request( 0 );
      std::vector <Sounds> playback_stop( 0 );

		try {
			// Lets try to read the sound data
			StreamReader<PropSoundData> sound_reader( sounddata_token, ts );
            
            DataWriter<AudioObjectFixed> xrpm1L(w_audio1,ts);
            DataWriter<AudioObjectFixed> xrpm1R(w_audio2,ts);
            
            DataWriter<AudioObjectFixed> xrpm2L(w_audio3,ts);
            DataWriter<AudioObjectFixed> xrpm2R(w_audio4,ts);

			float  eng_rpm;
			float  eng_trq;
			bool   eng_pwr;
			Sounds THIS_RUNNING;
			Sounds THIS_IDLE;

			// loop for going over engines 1 and 2
			for (int eng_nr=0; eng_nr<2; eng_nr++)
			{
				eng_rpm = sound_reader.data().rpm[ eng_nr ];
				eng_trq = sound_reader.data().torque[ eng_nr ] / max_torque; // between 0 and 1
				eng_pwr = sound_reader.data().power[ eng_nr ];
				THIS_RUNNING = (eng_nr == 0 ? ENGINE_LEFT : ENGINE_RIGHT);
				THIS_IDLE = (eng_nr == 0 ? ENGINE_LEFT_IDLE : ENGINE_RIGHT_IDLE);
				
				// currently using two sound files, one idle and one a step up
				// two more sound files are available for higher RPM
				// to include these, there has to be a smooth transition (in pitch and gain)
				// something for later
                
				if ( eng_rpm > 850 )
				{
					// stop the other sound
//                    playback_stop.push_back(THIS_IDLE);
					
					// gogogo
//                    playback_request.push_back(THIS_RUNNING);
					
					// take into account torque
					// reduce "heard rpm" based on torque lower, but only above idle rpm
					eng_rpm -= (eng_rpm-800)/2000 * (1-eng_trq) * 150;
					
					// Change the pitch, based on rpm
//                    sound_player.setPitch( m_sound_list[THIS_RUNNING],
//                                           (eng_rpm - engine_pitch_min) / engine_pitch_den
//                                         );
					
					// Change the gain, based on torque
					// 0 : 1 -*-> 0:3 -exp-> 1:~20 -/-> 0.025:~0.5 -+-> 0.525:~1
//                    sound_player.setGain( m_sound_list[THIS_RUNNING],
//                                          master_gain*(0.5f + exp(eng_trq * 3.0f)/40.0f) // gain between 0.5 and 1.0
//                                        );
                    
                    //send to WorldListener
                    
                    if (eng_nr == 1) {
                        xrpm1L.data().pitch = 0.0;
                        xrpm1L.data().volume = 0.0f;
                        xrpm2L.data().pitch = (eng_rpm - engine_pitch_min) / engine_pitch_den;
                        xrpm2L.data().volume = master_gain*(0.5f + exp(eng_trq * 3.0f)/40.0f);
                    }
                    else if (eng_nr == 2) {
                        xrpm1R.data().pitch = 0.0;
                        xrpm1R.data().volume = 0.0f;
                        xrpm2R.data().pitch = (eng_rpm - engine_pitch_min) / engine_pitch_den;
                        xrpm2R.data().volume = master_gain*(0.5f + exp(eng_trq * 3.0f)/40.0f);
                    }
				}
				else if ( eng_rpm > 400 && eng_pwr )
				{
					// stop the other sound
//                    playback_stop.push_back(THIS_RUNNING);
					
					// run idle
//                    playback_request.push_back(THIS_IDLE);
					
					// Change the pitch, based on rpm
//                    sound_player.setPitch( m_sound_list[THIS_IDLE],
//                                           eng_rpm/800.0f
//                                         );
					
					// Change the gain, based on torque
//                    sound_player.setGain( m_sound_list[THIS_IDLE],
//                                          master_gain*0.35f*(eng_trq+1)
//                                        );
                    
                    if (eng_nr == 1) {
                        xrpm2L.data().pitch = 0.0;
                        xrpm2L.data().volume = 0.0f;
                        
                        xrpm1L.data().pitch = eng_rpm/800.0f;
                        xrpm1L.data().volume = master_gain*0.35f*(eng_trq+1);
                    }
                    else if (eng_nr == 2) {
                        xrpm2R.data().pitch = 0.0;
                        xrpm2R.data().volume = 0.0f;
                        
                        xrpm1R.data().pitch = eng_rpm/800.0f;
                        xrpm1R.data().volume = master_gain*0.35f*(eng_trq+1);
                    }
				}
                
                //ToevoegingAnnemarie
                
				else
				{
					// stop all
//                    playback_stop.push_back(THIS_RUNNING);
//                    playback_stop.push_back(THIS_IDLE);
                    
                    xrpm1L.data().pitch = 0.0;
                    xrpm1L.data().volume = 0.0f;
                    xrpm2L.data().pitch = 0.0;
                    xrpm2L.data().volume = 0.0f;
                    
                    xrpm1R.data().pitch = 0.0;
                    xrpm1R.data().volume = 0.0f;
                    xrpm2R.data().pitch = 0.0;
                    xrpm2R.data().volume = 0.0f;
				}
			}
			
			// also on the channel:
			// sound_reader.data().tas;
			// sound_reader.data().sounds;
			
		}
		catch(Exception& e)
		{
			W_MOD( getId() << '/' << classname << "Error reading PropSoundData channel @ " << ts << ": " << e );
		}
      
      
      //TODO 
      // this whole process of adding items to lists and then going through those lists looks complicated
      // plus we have all the vectors and variable creations on every thick,
      // which will not help in running things smoothly
      // can't we just define some functions for these tasks, which are called instead of the adding to lists
      // just like sound_player.setPitch() is already called above
      //
      // however, keep:
      // sound_player.isSoundPlaying()
      // m_sound_times_played and m_sound_max_repeat
      

      // As long as there is a size in the request song, start it
      for ( std::vector<Sounds>::iterator it = playback_request.begin(); it != playback_request.end(); ++it )
      {
        // Do it this sound!
        Sounds this_sound = *it;
        int sound_id = m_sound_list[ this_sound ];
        try
        {
          if ( !sound_player.isSoundPlaying( sound_id ) && m_sound_times_played[ this_sound ] < m_sound_max_repeat[ this_sound ] )
          {
            sound_player.playSound( sound_id );
            m_sound_times_played[ this_sound ]++;
            D_MOD( getId() << '/' << classname << ": Playing sound " << sound_id );
          }
        }
        catch( ... )
        {
          W_MOD( getId() << '/' << classname << " Failed to lookup: " << sound_id );
        }
      }

      // Next we should stop sounds which are no longer to be used
      for ( std::vector<Sounds>::iterator it = playback_stop.begin(); it != playback_stop.end(); ++it )
      {
        // Do it this sound!
        Sounds this_sound = *it;
        int sound_id = m_sound_list[ this_sound ];
        try
        {
          if ( sound_player.isSoundPlaying( sound_id ) )
          {
            sound_player.stopSound( sound_id );
            m_sound_times_played[ this_sound ] = 0;
            D_MOD( getId() << '/' << classname << ": Stopping sound " << sound_id );
          }
        }
        catch( ... )
        {
          W_MOD( getId() << '/' << classname << " Failed to lookup: " << sound_id );
        }
      }

      break;
    }
    default:
    {
      break;
    }
  }
}

void WAVPlayer::trimCalculation(const TimeSpec& ts, const TrimMode& mode) {}

// Make a TypeCreator object for this module, the TypeCreator
// will check in with the scheme-interpreting code, and enable the
// creation of modules of this type
static TypeCreator<WAVPlayer> a(WAVPlayer::getMyParameterTable());

