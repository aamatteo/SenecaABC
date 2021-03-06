/* ------------------------------------------------------------------   */
/*      item            : GearSelector.cxx
        made by         : stroosma
	from template   : DusimeModuleTemplate.cxx
        template made by: Rene van Paassen
        date            : Thu Nov  6 09:01:34 2003
	category        : body file 
        description     : 
	changes         : Thu Nov  6 09:01:34 2003 first version
	template changes: 030401 RvP Added template creation comment
        language        : C++
*/

static const char c_id[] =
"$Id: GearSelector.cxx,v 1.11 2008/03/17 13:21:44 jellerbroek Exp $";

#define GearSelector_cxx
// include the definition of the module class
#include "GearSelector.hxx"

// include the debug writing header, by default, write warning and 
// error messages
#define W_MOD
#define E_MOD
#include <debug.h>

// include additional files needed for your calculation here
#include <Ticker.hxx>

// the standard package for DUSIME, including template source
#define DO_INSTANTIATE
#include <dusime.h>

// class/module name
const char* const GearSelector::classname = "gear-selector";

// initial condition/trim table
const IncoTable* GearSelector::getMyIncoTable()
{
  static IncoTable inco_table[] = {
    // enter pairs of IncoVariable and VarProbe pointers (i.e. 
    // objects made with new), in this table.
    // For example
//    {(new IncoVariable("example", 0.0, 1.0, 0.01))
//     ->forMode(FlightPath, Constraint)
//     ->forMode(Speed, Control),
//     new VarProbe<GearSelector,double>
//       (REF_MEMBER(&GearSelector::i_example))}
    
    // always close off with:
    { NULL, NULL} };

  return inco_table;
}

// parameters to be inserted
const ParameterTable* GearSelector::getMyParameterTable()
{
  static const ParameterTable parameter_table[] = {
    { "set-timing", 
      new MemberCall<GearSelector,TimeSpec>
        (&GearSelector::setTimeSpec), set_timing_description },

    { "check-timing", 
      new MemberCall<GearSelector,vector<int> >
      (&GearSelector::checkTiming), check_timing_description },

    { "initial-up", 
      new MemberCall<GearSelector,bool>
        (&GearSelector::setUp), "start with gear selected UP" },

    { "initial-off", 
      new MemberCall<GearSelector,bool>
        (&GearSelector::setOff), "start with gear selected OFF" },

    { "initial-down", 
      new MemberCall<GearSelector,bool>
        (&GearSelector::setDown), "start with gear selected DOWN" },
    
    { "master", 
      new MemberCall<GearSelector,bool>
        (&GearSelector::setMaster), "act as master, sending data" },

    /* You can extend this table with labels and MemberCall or
       VarProbe pointers to perform calls or insert values into your
       class objects. Please also add a description (c-style string).  

       Note that for efficiency, set_timing_description and
       check_timing_description are pointers to pre-defined strings,
       you can simply enter the descriptive strings in the table. */

    // always close off with:
    { NULL, NULL} };

  return parameter_table;
}

// constructor
GearSelector::GearSelector(Entity* e, const char* part, const
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
#if GTK_MAJOR_VERSION == 2
  masterlabel(NULL),
#else
  theWindow(NULL),
#endif
  gearup(NULL),
  gearoff(NULL),
  geardwn(NULL),

  // initialize the data you need for the trim calculation

  // initialize the channel access tokens
  // example
  // my_token(getId(), NameSet(getEntity(), "MyData", part)),
  //out_token(getId(), NameSet(getEntity(), "SecondarySwitches", part), 101),
  out_token(NULL), in_token(NULL),

  // activity initialization
  cb1(this, &GearSelector::doCalculation),
  do_calc(getId(), "reading gear switch", &cb1, ps)
{
  // do the actions you need for the simulation
#if GTK_MAJOR_VERSION == 2
  winglade.readGladeFile("gearselector.glade2", "GearSelector", reinterpret_cast<gpointer>(this), NULL);
#else
  winglade.readGladeFile("gearselector.glade", "GearSelector", reinterpret_cast<gpointer>(this), NULL);
#endif
  gearup       = (GtkToggleButton*)winglade["gearup"];
  gearoff      = (GtkToggleButton*)winglade["gearoff"];
  geardwn      = (GtkToggleButton*)winglade["geardwn"];
#if GTK_MAJOR_VERSION == 2
  masterlabel  = (GtkLabel*)winglade["typelabel"];
#else
  theWindow    = (GtkWindow*)winglade["GearSelector"];
#endif
  // connect the triggers for simulation
  //do_calc.setTrigger(*Ticker::single()/* fill in your triggering channels */);
  
  // connect the triggers for trim calculation. Leave this out if you 
  // don not need input for trim calculation 
  //trimCalculationCondition(/* fill in your trim triggering channels */);
}

bool GearSelector::complete()
{
  /* All your parameters have been set. You may do extended
     initialisation here. Return false if something is wrong. */
  
  // master or slave mode has not been set
  if(out_token == NULL && in_token == NULL) {
    // default: act as master
    setMaster(true);

  }
  return true;
}

// destructor
GearSelector::~GearSelector()
{
  //
  if(out_token) delete out_token;
  if(in_token) delete in_token;
}

// as an example, the setTimeSpec function
bool GearSelector::setTimeSpec(const TimeSpec& ts)
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
bool GearSelector::checkTiming(const vector<int>& i)
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

// set the state to up
bool GearSelector::setUp(const bool& b)
{
  if(b) {
    gtk_toggle_button_set_active((GtkToggleButton*)gearup, true);
  }

  return true;
}

// set the state to off
bool GearSelector::setOff(const bool& b)
{
  if(b) {
    gtk_toggle_button_set_active((GtkToggleButton*)gearoff, true);
  }

  return true;
}

// set the state to down
bool GearSelector::setDown(const bool& b)
{
  if(b) {
    gtk_toggle_button_set_active((GtkToggleButton*)geardwn, true);
  }

  return true;
}

// act as master, send out SecondarySwitches
bool GearSelector::setMaster(const bool& b)
{
  if(b) {
    out_token = new StreamChannelWriteToken<SecondarySwitches>
      (getId(), NameSet(getEntity(), "SecondarySwitches", getPart()), 101);
    
    if(in_token) {
      delete in_token;
      in_token = NULL;
    }
    
    do_calc.setTrigger(*Ticker::single());
  }
  else {
    in_token = new StreamChannelReadToken<SecondarySwitches>
      (getId(), NameSet(getEntity(), "SecondarySwitches", getPart()), 101);

    if(out_token) {
      delete out_token;
      out_token = NULL;
    }

    do_calc.setTrigger(*in_token);
  }
#if GTK_MAJOR_VERSION == 2
  if(masterlabel) gtk_label_set_markup (masterlabel, (out_token ?
			       "<b>Switches Master</b>" :
                                   "<b>Switches Slave</b>"));
#else
  if(theWindow) gtk_window_set_title (theWindow, (out_token ?
			       "GearSelector master" :
			       "GearSelector slave"));
#endif


  return true;
}

// tell DUECA you are prepared
bool GearSelector::isPrepared()
{
  // do whatever additional calculations you need to prepare the model. 

  // Check that all conditions for running are good. 
  // It helps to indicate what the problems are
  bool res = true;
  
  if(out_token) {
    res &= out_token->isValid();
  }
  else if(in_token) {
    res &= in_token->isValid();
  }

  if (!res) {
    W_MOD(getId() << '/' << classname << " not prepared, token not valid");
  }

  // return result of check
  return res;
}

// start the module
void GearSelector::startModule(const TimeSpec &time)
{
  do_calc.switchOn(time);
}

// stop the module
void GearSelector::stopModule(const TimeSpec &time)
{
  do_calc.switchOff(time);
}

// fill a snapshot with state data. You may remove this method (and the
// declaration) if you specified to the SimulationModule that the size of 
// state snapshots is zero
void GearSelector::fillSnapshot(const TimeSpec& ts, 
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
void GearSelector::loadSnapshot(const TimeSpec& t, const Snapshot& snap)
{
  // access the data in the snapshot with an AmorphReStore object
  AmorphReStore s(snap.data, snap.data_size);

  // use unPackData(s, real_state_variable1 ); ... to unpack the data 
  // from the snapshot. 
  // You can safely do this, while snapshot loading is going on the 
  // simulation is in HoldCurrent or the activity is stopped. 
}

// this routine contains the main simulation process of your module. You 
// should read the input channels here, and calculate and write the 
// appropriate output
void GearSelector::doCalculation(const TimeSpec& ts)
{
  // check the state we are supposed to be in
  switch (getAndCheckState(ts)) {
  case SimulationState::HoldCurrent:
  case SimulationState::Replay:
  case SimulationState::Advance: {
    // access the input 
    // example:
    // try {
    //   StreamReader<MyInput> u(input_token, ts);
    //   throttle = u.data().throttle;    
    //   de = u.data().de; ....
    // } 
    // catch(Exception& e) {
    //   // strange, there is no input. Should I try to continue or not?
    // }
    /* The above piece of code shows a block in which you try to catch 
       error conditions (exceptions) to handle the case in which the input
       data is lost. This is not always necessary, if you normally do not
       foresee such a condition, and you don t mind being stopped when
       it happens, forget about the try/catch blocks. */

    // do the simulation calculations, one step
    // ... nothing
    break;
    }
  default:
    // other states should never be entered for a SimulationModule, 
    // HardwareModules on the other hand have more states. Throw an
    // exception if we get here, 
    throw CannotHandleState(getId(),GlobalId(), "state unhandled");
  }

  // DUECA applications are data-driven. From the time a module is switched
  // on, it should produce data, so that modules "downstreams" are 
  // activated
  // access your output channel(s)
  // example
  // StreamWriter<MyOutput> y(output_token, ts);
   if(out_token) {
     StreamWriter<SecondarySwitches> y(*out_token, ts);

     // write the output into the output channel, using the stream writer
     // y.data().var1 = something; ...
     y.data().gear_up = gtk_toggle_button_get_active(gearup);
     y.data().gear_neutral = gtk_toggle_button_get_active(gearoff);
     y.data().gear_down = gtk_toggle_button_get_active(geardwn);
   }
   else if (in_token) {
     try {
       StreamReader<SecondarySwitches> u(*in_token, ts);
       
       if (u.data().gear_up)
        gtk_toggle_button_set_active(gearup, true);
       else if (u.data().gear_neutral)
         gtk_toggle_button_set_active(gearoff, true);
       else
        gtk_toggle_button_set_active(geardwn, true);
     }
     catch (Exception& e) {
       W_MOD(classname << " caught unexpected " << e);
     }
   }

  if (snapshotNow()) {
    // keep a copy of the model state. Snapshot sending is done in the 
    // sendSnapshot routine, later, and possibly at lower priority
    // e.g. 
    // snapshot_state_variable1 = state_variable1; ...
    // (or maybe if your state is very large, there is a cleverer way ...)
  }
} 

void GearSelector::trimCalculation(const TimeSpec& ts, const TrimMode& mode)
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
static TypeCreator<GearSelector> a(GearSelector::getMyParameterTable());

