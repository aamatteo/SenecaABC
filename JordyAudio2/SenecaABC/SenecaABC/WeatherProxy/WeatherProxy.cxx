/* ------------------------------------------------------------------   */
/*      item            : WeatherProxy.cxx
        made by         : Peter van Oorschot
	from template   : DusimeModuleTemplate.cxx
        template made by: Rene van Paassen
        date            : Wed Apr 19 13:18:53 2017
	category        : body file 
        description     : 
	changes         : Wed Apr 19 13:18:53 2017 first version
	template changes: 030401 RvP Added template creation comment
	                  060512 RvP Modified token checking code
			  131224 RvP convert snap.data_size to 
			         snap.getDataSize()
        language        : C++
        copyright       : (c) 2016 TUDelft-AE-C&S
*/


#define WeatherProxy_cxx
// include the definition of the module class
#include "WeatherProxy.hxx"

// include the debug writing header, by default, write warning and 
// error messages
#define D_MOD
#define I_MOD
#define W_MOD
#define E_MOD
#include <debug.h>

// include additional files needed for your calculation here

// the standard package for DUSIME, including template source
#define DO_INSTANTIATE
#include <dusime.h>

// conversion
#ifndef KTS2MPS
#define KTS2MPS 0.5144444
#endif

// class/module name
const char* const WeatherProxy::classname = "weather-proxy";

// initial condition/trim table
const IncoTable* WeatherProxy::getMyIncoTable()
{
  static IncoTable inco_table[] = {
    // enter pairs of IncoVariable and VarProbe pointers (i.e. 
    // objects made with new), in this table.
    // For example
//    {(new IncoVariable("example", 0.0, 1.0, 0.01))
//     ->forMode(FlightPath, Constraint)
//     ->forMode(Speed, Control),
//     new VarProbe<_ThisModule_,double>
//       (REF_MEMBER(&_ThisModule_::i_example))}
    
    // always close off with:
    { NULL, NULL} };

  return inco_table;
}

// parameters to be inserted
const ParameterTable* WeatherProxy::getMyParameterTable()
{
  static const ParameterTable parameter_table[] = {
    { "set-timing", 
      new MemberCall<_ThisModule_,TimeSpec>
        (&_ThisModule_::setTimeSpec), set_timing_description },

    { "check-timing", 
      new MemberCall<_ThisModule_,vector<int> >
      (&_ThisModule_::checkTiming), check_timing_description },

    /* You can extend this table with labels and MemberCall or
       VarProbe pointers to perform calls or insert values into your
       class objects. Please also add a description (c-style string).  

       Note that for efficiency, set_timing_description and
       check_timing_description are pointers to pre-defined strings,
       you can simply enter the descriptive strings in the table. */

    /* The table is closed off with NULL pointers for the variable
       name and MemberCall/VarProbe object. The description is used to
       give an overall description of the module. */
    { NULL, NULL, "Sends updates of weather data to FGWeather"} };

  return parameter_table;
}

// constructor
WeatherProxy::WeatherProxy(Entity* e, const char* part, const
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
  SimulationModule(e, classname, part, getMyIncoTable(), 0),

  // initialize the data you need in your simulation
  myFGW(),

  // initialize the data you need for the trim calculation

  // initialize the channel access tokens, check the documentation for the
  // various parameters.
  r_token(getId(), NameSet(getEntity(), "WindEvent", part)),
  w_token(getId(), NameSet(getEntity(), "FGWeatherInput",""),
	  ChannelDistribution::JOIN_MASTER),
  
  // activity initialization
  myclock(),
  cb1(this, &_ThisModule_::doCalculation),
  do_calc(getId(), "Sends updates of weather data to FGWeather", &cb1, ps)
{
  // do the actions you need for the simulation

  // connect the triggers for simulation
  do_calc.setTrigger( myclock );
  
  // connect the triggers for trim calculation. Leave this out if you 
  // don not need input for trim calculation 
  //trimCalculationCondition(/* fill in your trim triggering channels */);
}

bool WeatherProxy::complete()
{
  /* All your parameters have been set. You may do extended
     initialisation here. Return false if something is wrong. */
  
  // default data for FGWeatherInput myFGW
  // not changed
  myFGW.station_id     = "EHAM";
  myFGW.date_time      = "231233Z";
  myFGW.temperature    = 15;        //[C]
  myFGW.dew_point      = 5;         //[C]
  myFGW.qnh            = 1013;      //[hPa]
  myFGW.outlook        = "NOSIG";
  // default, updated
  myFGW.visibility     = 100000;    //[m] (actual visibility, can be any positive value)
  myFGW.wind_direction = 0;         //[deg]
  myFGW.wind_velocity  = 0;         //[either m/s or knots] (later on in the chain KT is assumed)
  // data of the clouds
  myFGW.cloud_layer_0_altitude = 0; //[ft]
  myFGW.cloud_layer_0_cover    = FGWeatherInput::SKC;
  myFGW.cloud_layer_1_altitude = 0; //[ft]
  myFGW.cloud_layer_1_cover    = FGWeatherInput::SKC;
  myFGW.cloud_layer_2_altitude = 0; //[ft]
  myFGW.cloud_layer_2_cover    = FGWeatherInput::SKC;
  
  D_MOD(classname << ": Default values for FGWeatherInput are defined");
  
  return true;
}

// destructor
WeatherProxy::~WeatherProxy()
{
  //
}

// as an example, the setTimeSpec function
bool WeatherProxy::setTimeSpec(const TimeSpec& ts)
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
bool WeatherProxy::checkTiming(const vector<int>& i)
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
bool WeatherProxy::isPrepared()
{
  bool res = true;

  // Example checking a token:
  // CHECK_TOKEN(w_somedata);
  CHECK_TOKEN(r_token);
  CHECK_TOKEN(w_token);

  // Example checking anything
  // CHECK_CONDITION(myfile.good());
  // CHECK_CONDITION2(sometest, "some test failed");

  // return result of checks
  return res;
}

// start the module
void WeatherProxy::startModule(const TimeSpec &time)
{
  do_calc.switchOn(time);
			
  // send initial weather update
  EventWriter <FGWeatherInput> fgw(w_token);
  fgw.data() = myFGW;
  D_MOD(classname << ": Sending initial weather update");
}

// stop the module
void WeatherProxy::stopModule(const TimeSpec &time)
{
  do_calc.switchOff(time);
}

// fill a snapshot with state data. You may remove this method (and the
// declaration) if you specified to the SimulationModule that the size of 
// state snapshots is zero
void WeatherProxy::fillSnapshot(const TimeSpec& ts, 
                              Snapshot& snap, bool from_trim)
{
  // The most efficient way of filling a snapshot is with an AmorphStore
  // object.
  AmorphStore s(snap.accessData(), snap.getDataSize());

  if (from_trim) {
    // use packData(s, trim_state_variable1); ... to pack your state into 
    // the snapshot
  }
  else {
    // this is a snapshot from the running simulation. Dusime takes care 
    // that no other snapshot is taken at the same time, so you can safely
    // pack the data you copied into (or left into) the snapshot state 
    // variables in here
    // use packData(s, snapshot_state_variable1); ...
  }
}

// reload from a snapshot. You may remove this method (and the
// declaration) if you specified to the SimulationModule that the size of 
// state snapshots is zero
void WeatherProxy::loadSnapshot(const TimeSpec& t, const Snapshot& snap)
{
  // access the data in the snapshot with an AmorphReStore object
  AmorphReStore s(snap.data, snap.getDataSize());

  // use unPackData(s, real_state_variable1 ); ... to unpack the data 
  // from the snapshot. 
  // You can safely do this, while snapshot loading is going on the 
  // simulation is in HoldCurrent or the activity is stopped. 
}

// this routine contains the main simulation process of your module. You 
// should read the input channels here, and calculate and write the 
// appropriate output
void WeatherProxy::doCalculation(const TimeSpec& ts)
{
  // check the state we are supposed to be in
  // I think I should not have opted for a dusime module,
  // as this is required but not really used
  switch (getAndCheckState(ts)) {
  case SimulationState::HoldCurrent:
  case SimulationState::Replay:
  case SimulationState::Advance: {
  
	// Read Wind
	while (r_token.getNumWaitingEvents(ts))
	{
		try
		{
			// Weather data from WindEvent to FGWeatherInput
			
			EventReader<WindEvent> w(r_token, ts);
			WindEvent myINPUT = w.data();
			//NOTE negative values coming in over the channel should be ignored
			
			// update weather data
			if (myINPUT.wind_dir > -1e-3) {
				myFGW.wind_direction = myINPUT.wind_dir; //[deg]
			}
			if (myINPUT.wind_vel > -1e-3) {
				myFGW.wind_velocity  = myINPUT.wind_vel/KTS2MPS; // later on in the chain KT is assumed
			}
			if (myINPUT.visibility >= 0) {
				myFGW.visibility = myINPUT.visibility;
			}
			
			// https://en.wikipedia.org/wiki/Okta
			// SKC = sky clear;
			// FEW = 1 to 2 oktas;
			// SCT (Scattered) = 3 to 4 oktas;
			// BKN (Broken) = 5 to 7 oktas;
			// OVC (Overcast) = 8 oktas; 
			// NOT USED: NSC = nil significant cloud; CAVOK = ceiling and visibility okay.
			
			// update the clouds
			//TODO simple options for now, make all combinations available
			//layer
			if (myINPUT.cloud_layer_0_altitude > 0) {
				myFGW.cloud_layer_0_altitude = myINPUT.cloud_layer_0_altitude;
				myFGW.cloud_layer_0_cover    = FGWeatherInput::SCT; // Scattered
			}
			else if (myINPUT.cloud_layer_0_altitude == 0) {
				myFGW.cloud_layer_0_altitude = myINPUT.cloud_layer_0_altitude;
				myFGW.cloud_layer_0_cover    = FGWeatherInput::SKC;
			}
			//layer
			if (myINPUT.cloud_layer_1_altitude > 0) {
				myFGW.cloud_layer_1_altitude = myINPUT.cloud_layer_1_altitude;
				myFGW.cloud_layer_1_cover    = FGWeatherInput::BKN; // Broken
			}
			else if (myINPUT.cloud_layer_1_altitude == 0) {
				myFGW.cloud_layer_1_altitude = myINPUT.cloud_layer_1_altitude;
				myFGW.cloud_layer_1_cover    = FGWeatherInput::SKC;
			}
			//layer
			if (myINPUT.cloud_layer_2_altitude > 0) {
				myFGW.cloud_layer_2_altitude = myINPUT.cloud_layer_2_altitude;
				myFGW.cloud_layer_2_cover    = FGWeatherInput::OVC; // Overcast
			}
			else if (myINPUT.cloud_layer_2_altitude == 0) {
				myFGW.cloud_layer_2_altitude = myINPUT.cloud_layer_2_altitude;
				myFGW.cloud_layer_2_cover    = FGWeatherInput::SKC;
			}
			
			// send weather update
			EventWriter <FGWeatherInput> fgw(w_token);
			fgw.data() = myFGW;
			
			D_MOD(classname << ": Sending FGWeatherInput");
		}
		catch ( Exception &e )
		{
			W_MOD(classname << " caught " << e << " @ " << ts << " while reading WindEvent");
		}
		
	}
	
  break;
  }
  default:
    // other states should never be entered for a SimulationModule, 
    // HardwareModules on the other hand have more states. Throw an
    // exception if we get here, 
    throw CannotHandleState(getId(),GlobalId(), "state unhandled");
  }
}

void WeatherProxy::trimCalculation(const TimeSpec& ts, const TrimMode& mode)
{
  // read the event equivalent of the input data
  // example
  // EventReader u(i_input_token, ts);

  // using the input, and the data put into your trim variables,
  // calculate the derivative of the state. DO NOT use the state
  // vector of the normal simulation here, because it might be that
  // this is done while the simulation runs!  
  // Some elements in this state derivative are needed as target, copy
  // these out again into trim variables (see you TrimTable

  // trim calculation
  switch(mode) {
  case FlightPath: {
    // one type of trim calculation, find a power setting and attitude
    // belonging to a flight path angle and speed
  }
  break;

  case Speed: {
    // find a flightpath belonging to a speed and power setting (also
    // nice for gliders)
  }
  break;

  case Ground: {
    // find an altitude/attitude belonging to standing still on the 
    // ground, power/speed 0
  }
  break;

  default:
    W_MOD(getId() << " cannot calculate inco mode " << mode);
  break;
  }

  // This works just like a normal calculation, only you provide the
  // steady state value (if your system is stable anyhow). So, if you
  // have other modules normally depending on your output, you should
  // also produce the equivalent output here. 
  // EventWriter<MyOutput> y(output_token, ts);

  // write the output into the output channel, using the EventWriter
  // N.B. you may also use:
  // output_token.sendEvent(ts, new MyOutput(arguments));
  // this is slightly more efficient. However, the EventWriter makes
  // it easier, because the code will look much more like your normal
  // calculation code.

  // now return. The real results from the trim calculation, as you
  // specified them in the TrimTable, will now be collected and sent
  // off for processing.
}

// Make a TypeCreator object for this module, the TypeCreator
// will check in with the scheme-interpreting code, and enable the
// creation of modules of this type
static TypeCreator<WeatherProxy> a(WeatherProxy::getMyParameterTable());

