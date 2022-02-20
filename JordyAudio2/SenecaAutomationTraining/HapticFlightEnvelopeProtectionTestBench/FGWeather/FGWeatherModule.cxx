/* ------------------------------------------------------------------   */
/*      item            : FGWeatherModule.cxx
        made by         : dirkvanbaelen
	from template   : DuecaModuleTemplate.cxx
        template made by: Rene van Paassen
        date            : Fri Oct  7 13:26:49 2016
	category        : body file
        description     :
	changes         : Fri Oct  7 13:26:49 2016 first version
	template changes: 030401 RvP Added template creation comment
	                  060512 RvP Modified token checking code
        language        : C++
*/

#define FGWeatherModule_cxx
// include the definition of the module class
#include "FGWeatherModule.hxx"

// include the debug writing header, by default, write warning and
// error messages
#define D_MOD
#define I_MOD
#define W_MOD
#define E_MOD
#include <debug.h>

// include additional files needed for your calculation here
#include <boost/lexical_cast.hpp>

// the standard package for DUSIME, including template source
#define DO_INSTANTIATE
#include <dueca.h>

// class/module name
const char* const FGWeatherModule::classname = "fg-weather-module";

// Parameters to be inserted
const ParameterTable* FGWeatherModule::getMyParameterTable()
{
  static const ParameterTable parameter_table[] = {
    { "set-timing",
      new MemberCall<FGWeatherModule,TimeSpec>
        (&FGWeatherModule::setTimeSpec), set_timing_description },

    { "check-timing",
      new MemberCall<FGWeatherModule,vector<int> >
      (&FGWeatherModule::checkTiming), check_timing_description },

    { "set-read-part-name",
      new VarProbe< FGWeatherModule, string > ( &FGWeatherModule::m_read_part_name ),
      "The part name from which we should read the data (to make sure the part name of the module and reading can be different for center and left/right displays" },

    { "set-write-part-name",
      new VarProbe< FGWeatherModule, string > ( &FGWeatherModule::m_write_part_name ),
      "The part name from which we should write the telnet data (to make sure the part name of the module and reading can be different for center and left/right displays" },

    /* You can extend this table with labels and MemberCall or
       VarProbe pointers to perform calls or insert values into your
       class objects. Please also add a description (c-style string).

       Note that for efficiency, set_timing_description and
       check_timing_description are pointers to pre-defined strings,
       you can simply enter the descriptive strings in the table. */

    /* The table is closed off with NULL pointers for the variable
       name and MemberCall/VarProbe object. The description is used to
       give an overall description of the module. */
    { NULL, NULL,
      "This module communicates weather instructions to a\n"
      "flightgear (fgfs) simulation, to create an outside visual" } };

  return parameter_table;
}

// constructor
FGWeatherModule::FGWeatherModule(Entity* e, const char* part, const
		   PrioritySpec& ps) :
  /* The following line initialises the SimulationModule base class.
     You always pass the pointer to the entity, give the classname and the
     part arguments.
     If you give a NULL pointer instead of the inco table, you will not be
     called for trim condition calculations, which is normal if you for
     example implement logging or a display.
     If you give 0 for the snapshot state, you will not be called to
     fill a snapshot, or to restore your state from a snapshot. Only
     applicable if you have no state. */
  Module(e, classname, part),

  // initialize the data you need in your simulation
  m_read_part_name( part ),
  m_write_part_name( part ),

  // initialize the data you need for the trim calculation

  // initialize the channel access tokens
  m_read_weather( NULL ),
  m_write_telnet( NULL ),

  // activity initialization
  m_clock(),
  cb1(this, &FGWeatherModule::doCalculation),
  do_calc(getId(), "Send weather update to FG", &cb1, ps)
{
  // do the actions you need for the simulation

  // connect the triggers for simulation
  // DURING TEST PHASE TRIGGER ON THE CLOCK AND SEND DUMMY DATA
  do_calc.setTrigger( m_clock );
}

bool FGWeatherModule::complete()
{
  /* All your parameters have been set. You may do extended
     initialisation here. Return false if something is wrong. */

  /** Open the channel for reading */
  m_read_weather = new EventChannelReadToken < FGWeatherInput >( getId(), NameSet( getEntity(), "FGWeatherInput", m_read_part_name.c_str() ) );

  /** And writing */
  m_write_telnet = new EventChannelWriteToken < TelnetInput >( getId(), NameSet( getEntity(), "TelnetInput", m_write_part_name.c_str() ), ChannelDistribution::JOIN_MASTER );

  return true;
}

// destructor
FGWeatherModule::~FGWeatherModule()
{
  //
}

// as an example, the setTimeSpec function
bool FGWeatherModule::setTimeSpec(const TimeSpec& ts)
{
  // a time span of 0 is not acceptable
  if (ts.getValiditySpan() == 0) return false;

  // specify the timespec to the activity
  do_calc.setTimeSpec(ts);
  // or do this with the clock if you have it (don't do both!)
  // myclock.changePeriodAndOffset(ts);

  // do whatever else you need to process this in your model
  // hint: ts.getDtInSeconds()

  // return true if everything is acceptable
  return true;
}

// and the checkTiming function
bool FGWeatherModule::checkTiming(const vector<int>& i)
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

// tell DUECA you are prepared
bool FGWeatherModule::isPrepared()
{
  bool res = true;

  // Example checking a token:
  CHECK_TOKEN( *m_read_weather );
  CHECK_TOKEN( *m_write_telnet );

  // return result of checks
  return res;
}

// start the module
void FGWeatherModule::startModule(const TimeSpec &time)
{
  do_calc.switchOn(time);

  // Make sure we set the visibility overwrite
  std::string vis_overwrite( "set environment/config/presets/visibility-m-override true " );
  sendFGMessage( vis_overwrite );
}

// stop the module
void FGWeatherModule::stopModule(const TimeSpec &time)
{
  do_calc.switchOff(time);
}

// this routine contains the main simulation process of your module. You
// should read the input channels here, and calculate and write the
// appropriate output
void FGWeatherModule::doCalculation(const TimeSpec& ts)
{
  try
  {
    while( m_read_weather->getNumWaitingEvents( ts ) )
    {
      EventReader < FGWeatherInput > weather_reader( *m_read_weather, ts );
      FGWeatherInput new_weather = weather_reader.data();

      // Send the info as plain string
      std::string metar_command = "set environment/metar/data ";
      metar_command += fgWeatherInputToMetar( new_weather );

      sendFGMessage( metar_command );

      // And also do the visibility overwrite
      std::string vis_overwrite( "set environment/config/presets/visibility-m " );
      vis_overwrite += numToString( new_weather.visibility, 0 );

      sendFGMessage( vis_overwrite );
    }
  }
  catch ( Exception &e )
  {
    W_MOD( classname << ": Error while reading FGWeatherInput @" << ts << ": " << e );
  }
}

// Make a TypeCreator object for this module, the TypeCreator
// will check in with the scheme-interpreting code, and enable the
// creation of modules of this type
static TypeCreator<FGWeatherModule> a(FGWeatherModule::getMyParameterTable());

const std::string FGWeatherModule::fgWeatherInputToMetar( const FGWeatherInput p_input )
{
  // A metar is a aviation weather report, an example:
  // EBAW 101320Z 04007KT 9999 FEW035 14/04 Q1022 NOSIG
  //     EBAW: locatoin identifier (here Antwerp)
  //     101320Z: day of the month (10th) plus the time (13:20) in zulu (GMT) time
  //     04007KT: Wind direction (040) and magintude (07 knots)
  //     9999: visibility (10km or more)
  //     FEW035: cloud information (0 to 2 octas at 3500 ft)
  //     14/04: temperature (14) and dewpoint (4)
  //     Q1022: QNH
  //     NOSIG: outlook for the comming hours (no significant change)

  // This function will build the metar using the available informaiotn in the channel object
  std::string metar = p_input.station_id;
  metar += " ";
  metar += p_input.date_time;
  metar += " ";
  metar += numToString( p_input.wind_direction, 3 );
  metar += numToString( p_input.wind_velocity, 2 );
  metar += "KT ";

  // The visibility should be max 9999
  if ( p_input.visibility < 9999 )
  {
    metar += numToString( p_input.visibility, 4 );
  }
  else
  {
    metar += numToString( 9999, 4 );
  }
  metar += " ";

  // Add the clouds
  metar += cloudInfoToMetar( p_input.cloud_layer_0_cover, p_input.cloud_layer_0_altitude );
  metar += " ";
  metar += cloudInfoToMetar( p_input.cloud_layer_1_cover, p_input.cloud_layer_1_altitude );
  metar += " ";
  metar += cloudInfoToMetar( p_input.cloud_layer_2_cover, p_input.cloud_layer_2_altitude );
  metar += " ";

  // Add temperature
  metar += numToString( p_input.temperature, 2 );
  metar += "/";
  metar += numToString( p_input.dew_point, 2 );
  metar += " ";

  // Presuure
  metar += "Q";
  metar += numToString( p_input.qnh, 4 );
  metar += " ";

  metar += p_input.outlook;

  // Finally return the final result
  return metar;
}

const std::string FGWeatherModule::cloudInfoToMetar( FGWeatherInput::cloudCover p_cover, int p_altitude )
{
  std::string cloud = "";

  switch ( p_cover )
  {
    case FGWeatherInput::SKC:
    {
      cloud += "";
      break;
    }
    case FGWeatherInput::FEW:
    {
      cloud += "FEW";
      break;
    }
    case FGWeatherInput::SCT:
    {
      cloud += "SCT";
      break;
    }
    case FGWeatherInput::BKN:
    {
      cloud += "BKN";
      break;
    }
    case FGWeatherInput::OVC:
    {
      cloud += "OVC";
      break;
    }
    default:
    {
      E_MOD( getId() << "/" << classname << ": Unknown cloud cover" );
      break;
    }
  }

  // add the altitude only when required
  if ( p_cover != FGWeatherInput::SKC )
  {
    cloud += numToString( p_altitude / 100, 3 );
  }

  return cloud;
}

const std::string FGWeatherModule::numToString( int p_number, int p_digits )
{
  std::string answer;

  int counter = p_digits - 1;
  while ( p_number < std::pow( 10, counter ) && counter > 0 )
  {
    answer += "0";
    counter--;
  }

  answer += boost::lexical_cast<std::string>( p_number );

  return answer;
}

void FGWeatherModule::sendFGMessage( const std::string p_message )
{
  // Make the writer
  EventWriter < TelnetInput > telnetWriter( *m_write_telnet, SimTime::getTimeTick() );
  telnetWriter.data().command_ready = true;
  telnetWriter.data().command       = p_message;
}
