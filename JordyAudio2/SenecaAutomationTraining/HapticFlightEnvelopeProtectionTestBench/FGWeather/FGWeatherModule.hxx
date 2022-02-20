/* ------------------------------------------------------------------   */
/*      item            : FGWeatherModule.hxx
        made by         : dirkvanbaelen
	from template   : DuecaModuleTemplate.hxx
        template made by: Rene van Paassen
        date            : Fri Oct  7 13:26:49 2016
	category        : header file
        description     :
	changes         : Fri Oct  7 13:26:49 2016 first version
	template changes: 030401 RvP Added template creation comment
        language        : C++
*/

#ifndef FGWeatherModule_hxx
#define FGWeatherModule_hxx

// include the dusime header
#include <dueca.h>
USING_DUECA_NS;

// This includes headers for the objects that are sent over the channels
#include "comm-objects.h"

// include headers for functions/classes you need in the module
#include <string>

/** This module forms a proxy to flightgear for the purpose of changing the weather currently shown.

    Flightgear must be started up with an option to listen to telnet communication.
    Example:
    \verbatim
    fgfs --telnet=port
    \endverbatim
    The variables are:
    <ul>
    <li> port: port to be used
    </ul>

    You probably also want to include the TelnetInterfaceModule
    And your dueca.mod file should include someting like this:
      (make-module 'fg-weather-module "" sim-priority
        'set-timing sim-timing
        'check-timing 10000 15000 400
      )
      (make-module 'telnet-interface-module "" sim-priority
        'set-timing sim-timing
        'check-timing 10000 15000 400
        'ip "127.0.0.1"
        'port 5401
      )

    \verbinclude fg-weather-module.scm
 */
class FGWeatherModule: public Module
{
private: // simulation data

  /** Define the partnamne for the channel */
  string m_read_part_name;
  string m_write_part_name;

private: // channel access
  // declare StreamChannelReadToken<Type>, StreamChannelWriteToken<Type>
  // EventChannelReadToken<Type>, EventChannelWriteToken<Type>
  // access tokens for all the channels you read and write
  // example
  // StreamChannelReadToken<MyData>  my_token;

  EventChannelReadToken  < FGWeatherInput > *m_read_weather;
  EventChannelWriteToken < TelnetInput >    *m_write_telnet;

private: // activity allocation
  PeriodicAlarm m_clock;

  /** Callback object for simulation calculation. */
  Callback<FGWeatherModule>  cb1;

  /** Activity for simulation calculation. */
  ActivityCallback      do_calc;

public: // class name and trim/parameter tables
  /** Name of the module. */
  static const char* const           classname;

  /** Return the parameter table. */
  static const ParameterTable*       getMyParameterTable();

public: // construction and further specification
  /** Constructor. Is normally called from scheme/the creation script. */
  FGWeatherModule(Entity* e, const char* part, const PrioritySpec& ts);

  /** Continued construction. This is called after all script
      parameters have been read and filled in, according to the
      parameter table. Your running environment, e.g. for OpenGL
      drawing, is also prepared. Any lengty initialisations (like
      reading the 4 GB of wind tables) should be done here.
      Return false if something in the parameters is wrong (by
      the way, it would help if you printed what!) May be deleted. */
  bool complete();

  /** Destructor. */
  ~FGWeatherModule();

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

private:
  /** Convert from the incomming channel to a metar message */
  const std::string fgWeatherInputToMetar( const FGWeatherInput p_input );
  const std::string cloudInfoToMetar( FGWeatherInput::cloudCover p_cover, int p_altitude );
  const std::string numToString( int p_number, int p_digits );

  /** Send the actual telnet message, private as intefacing should happen through channel */
  void sendFGMessage( const std::string p_message );
};

#endif
