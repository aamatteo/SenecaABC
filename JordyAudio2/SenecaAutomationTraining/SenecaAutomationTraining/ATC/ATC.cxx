/* ------------------------------------------------------------------   */
/*      item            : ATC.cxx
        made by         : matteo
        from template   : DusimeModuleTemplate.cxx
        template made by: Rene van Paassen
        date            : Tue Feb  8 17:29:27 2022
        category        : body file
        description     :
        changes         : Tue Feb  8 17:29:27 2022 first version
        template changes: 030401 RvP Added template creation comment
                          060512 RvP Modified token checking code
                          131224 RvP convert snap.data_size to
                                 snap.getDataSize()
        language        : C++
        copyright       : (c) 2016 TUDelft-AE-C&S
*/


#define ATC_cxx
// include the definition of the module class
#include "ATC.hxx"

// include the debug writing header. Warning and error messages
// are on by default, debug and info can be selected by
// uncommenting the respective defines
#define D_MOD
//#define I_MOD
#include <debug.h>

// include additional files needed for your calculation here

#include "StatesOutputs.h"

CitationOutput c;

// the standard package for DUSIME, including template source
#define DO_INSTANTIATE
#include <dusime.h>

// class/module name
const char* const ATC::classname = "atc";

// initial condition/trim table
const IncoTable* ATC::getMyIncoTable()
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
const ParameterTable* ATC::getMyParameterTable()
{
  static const ParameterTable parameter_table[] = {
    { "set-timing",
      new MemberCall<_ThisModule_,TimeSpec>
        (&_ThisModule_::setTimeSpec), set_timing_description },

    { "check-timing",
      new MemberCall<_ThisModule_,std::vector<int> >
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
    { NULL, NULL, "please give a description of this module"} };

  return parameter_table;
}

// constructor
ATC::ATC(Entity* e, const char* part, const
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

  lat(0),
  lon(0),
  playcomm(true),
  time_req(0.0),
  audio_trigger_time(0.0),
  audio_trigger_doc2(0.0),
  audio_trigger_twr2(0.0),

  // initialize the data you need for the trim calculation

  // initialize the channel access tokens, check the documentation for the
  // various parameters. Some examples:
  // r_mytoken(getId(), NameSet(getEntity(), MyData::classname, part),
  //           MyData::classname, 0, Channel::Events, Channel::ReadAllData),
  // w_mytoken(getId(), NameSet(getEntity(), MyData::classname, part),
  //           MyData::classname, "label", Channel::Continuous),

  // sample communication


  w_comm(getId(), NameSet("audio", "AnyAudioClass", ""), // added by Matteo Piras - up to here all ok
         "AudioObjectFixed", "audiot", Channel::Events,
         Channel::OneOrMoreEntries, Channel::MixedPacking),

  w_doc1(getId(), NameSet("audio", "AnyAudioClass", ""), // added by Matteo Piras - up to here all ok
         "AudioObjectFixed", "phdoc1", Channel::Events,

         Channel::OneOrMoreEntries, Channel::MixedPacking),
  w_doc3(getId(), NameSet("audio", "AnyAudioClass", ""), // added by Matteo Piras - up to here all ok
         "AudioObjectFixed", "phdoc3", Channel::Events,
         Channel::OneOrMoreEntries, Channel::MixedPacking),

  w_doc4(getId(), NameSet("audio", "AnyAudioClass", ""), // added by Matteo Piras - up to here all ok
         "AudioObjectFixed", "phdoc4", Channel::Events,
         Channel::OneOrMoreEntries, Channel::MixedPacking),

  w_spz1(getId(), NameSet("audio", "AnyAudioClass", ""), // added by Matteo Piras - up to here all ok
         "AudioObjectFixed", "phspz1", Channel::Events,
         Channel::OneOrMoreEntries, Channel::MixedPacking),

  w_spz2(getId(), NameSet("audio", "AnyAudioClass", ""), // added by Matteo Piras - up to here all ok
         "AudioObjectFixed", "phspz2", Channel::Events,
         Channel::OneOrMoreEntries, Channel::MixedPacking),

  w_spz3(getId(), NameSet("audio", "AnyAudioClass", ""), // added by Matteo Piras - up to here all ok
         "AudioObjectFixed", "phspz3", Channel::Events,
         Channel::OneOrMoreEntries, Channel::MixedPacking),

  w_spz4(getId(), NameSet("audio", "AnyAudioClass", ""), // added by Matteo Piras - up to here all ok
         "AudioObjectFixed", "phspz4", Channel::Events,
         Channel::OneOrMoreEntries, Channel::MixedPacking),

  w_spz5(getId(), NameSet("audio", "AnyAudioClass", ""), // added by Matteo Piras - up to here all ok
         "AudioObjectFixed", "phspz5", Channel::Events,
         Channel::OneOrMoreEntries, Channel::MixedPacking),

  w_spz6(getId(), NameSet("audio", "AnyAudioClass", ""), // added by Matteo Piras - up to here all ok
         "AudioObjectFixed", "phspz6", Channel::Events,
         Channel::OneOrMoreEntries, Channel::MixedPacking),

  w_spz7(getId(), NameSet("audio", "AnyAudioClass", ""), // added by Matteo Piras - up to here all ok
         "AudioObjectFixed", "phspz7", Channel::Events,
         Channel::OneOrMoreEntries, Channel::MixedPacking),

  w_spz8(getId(), NameSet("audio", "AnyAudioClass", ""), // added by Matteo Piras - up to here all ok
         "AudioObjectFixed", "phspz8", Channel::Events,
         Channel::OneOrMoreEntries, Channel::MixedPacking),

  w_spz9(getId(), NameSet("audio", "AnyAudioClass", ""), // added by Matteo Piras - up to here all ok
         "AudioObjectFixed", "phspz9", Channel::Events,
         Channel::OneOrMoreEntries, Channel::MixedPacking),

  w_svt1(getId(), NameSet("audio", "AnyAudioClass", ""), // added by Matteo Piras - up to here all ok
         "AudioObjectFixed", "phsvt1", Channel::Events,
         Channel::OneOrMoreEntries, Channel::MixedPacking),

  w_svt2(getId(), NameSet("audio", "AnyAudioClass", ""), // added by Matteo Piras - up to here all ok
         "AudioObjectFixed", "phsvt2", Channel::Events,
         Channel::OneOrMoreEntries, Channel::MixedPacking),

  w_svt3(getId(), NameSet("audio", "AnyAudioClass", ""), // added by Matteo Piras - up to here all ok
         "AudioObjectFixed", "phsvt3", Channel::Events,
         Channel::OneOrMoreEntries, Channel::MixedPacking),

  w_svt4(getId(), NameSet("audio", "AnyAudioClass", ""), // added by Matteo Piras - up to here all ok
         "AudioObjectFixed", "phsvt4", Channel::Events,
         Channel::OneOrMoreEntries, Channel::MixedPacking),

  w_twr1(getId(), NameSet("audio", "AnyAudioClass", ""), // added by Matteo Piras - up to here all ok
         "AudioObjectFixed", "twr1", Channel::Events,
         Channel::OneOrMoreEntries, Channel::MixedPacking),

  w_twr2(getId(), NameSet("audio", "AnyAudioClass", ""), // added by Matteo Piras - up to here all ok
         "AudioObjectFixed", "twr2", Channel::Events,
         Channel::OneOrMoreEntries, Channel::MixedPacking),

  w_twr3(getId(), NameSet("audio", "AnyAudioClass", ""), // added by Matteo Piras - up to here all ok
         "AudioObjectFixed", "twr3", Channel::Events,
         Channel::OneOrMoreEntries, Channel::MixedPacking),

  w_twr4(getId(), NameSet("audio", "AnyAudioClass", ""), // added by Matteo Piras - up to here all ok
         "AudioObjectFixed", "twr4", Channel::Events,
         Channel::OneOrMoreEntries, Channel::MixedPacking),

  w_twr5(getId(), NameSet("audio", "AnyAudioClass", ""), // added by Matteo Piras - up to here all ok
         "AudioObjectFixed", "twr5", Channel::Events,
         Channel::OneOrMoreEntries, Channel::MixedPacking),

  w_twr6(getId(), NameSet("audio", "AnyAudioClass", ""), // added by Matteo Piras - up to here all ok
         "AudioObjectFixed", "twr6", Channel::Events,
         Channel::OneOrMoreEntries, Channel::MixedPacking),

  w_twr7(getId(), NameSet("audio", "AnyAudioClass", ""), // added by Matteo Piras - up to here all ok
         "AudioObjectFixed", "twr7", Channel::Events,
         Channel::OneOrMoreEntries, Channel::MixedPacking),

  w_twr8(getId(), NameSet("audio", "AnyAudioClass", ""), // added by Matteo Piras - up to here all ok
         "AudioObjectFixed", "twr8", Channel::Events,
         Channel::OneOrMoreEntries, Channel::MixedPacking),

  w_twr8bis(getId(), NameSet("audio", "AnyAudioClass", ""), // added by Matteo Piras - up to here all ok
         "AudioObjectFixed", "twr8bis", Channel::Events,
         Channel::OneOrMoreEntries, Channel::MixedPacking),

  w_twr9(getId(), NameSet("audio", "AnyAudioClass", ""), // added by Matteo Piras - up to here all ok
         "AudioObjectFixed", "twr9", Channel::Events,
         Channel::OneOrMoreEntries, Channel::MixedPacking),

  w_twr10(getId(), NameSet("audio", "AnyAudioClass", ""), // added by Matteo Piras - up to here all ok
         "AudioObjectFixed", "twr10", Channel::Events,
         Channel::OneOrMoreEntries, Channel::MixedPacking),

  w_twr11(getId(), NameSet("audio", "AnyAudioClass", ""), // added by Matteo Piras - up to here all ok
         "AudioObjectFixed", "twr11", Channel::Events,
         Channel::OneOrMoreEntries, Channel::MixedPacking),

  w_twr12(getId(), NameSet("audio", "AnyAudioClass", ""), // added by Matteo Piras - up to here all ok
         "AudioObjectFixed", "twr12", Channel::Events,
         Channel::OneOrMoreEntries, Channel::MixedPacking),

  w_twr13(getId(), NameSet("audio", "AnyAudioClass", ""), // added by Matteo Piras - up to here all ok
         "AudioObjectFixed", "twr13", Channel::Events,
         Channel::OneOrMoreEntries, Channel::MixedPacking),

  w_twr14(getId(), NameSet("audio", "AnyAudioClass", ""), // added by Matteo Piras - up to here all ok
         "AudioObjectFixed", "twr14", Channel::Events,
         Channel::OneOrMoreEntries, Channel::MixedPacking),

  w_twr15(getId(), NameSet("audio", "AnyAudioClass", ""), // added by Matteo Piras - up to here all ok
         "AudioObjectFixed", "twr15", Channel::Events,
         Channel::OneOrMoreEntries, Channel::MixedPacking),

  w_twr16(getId(), NameSet("audio", "AnyAudioClass", ""), // added by Matteo Piras - up to here all ok
         "AudioObjectFixed", "twr16", Channel::Events,
         Channel::OneOrMoreEntries, Channel::MixedPacking),

  w_twr17(getId(), NameSet("audio", "AnyAudioClass", ""), // added by Matteo Piras - up to here all ok
         "AudioObjectFixed", "twr17", Channel::Events,
         Channel::OneOrMoreEntries, Channel::MixedPacking),

  w_twr18(getId(), NameSet("audio", "AnyAudioClass", ""), // added by Matteo Piras - up to here all ok
         "AudioObjectFixed", "twr18", Channel::Events,
         Channel::OneOrMoreEntries, Channel::MixedPacking),

  w_twr19(getId(), NameSet("audio", "AnyAudioClass", ""), // added by Matteo Piras - up to here all ok
         "AudioObjectFixed", "twr19", Channel::Events,
         Channel::OneOrMoreEntries, Channel::MixedPacking),

  w_twr20(getId(), NameSet("audio", "AnyAudioClass", ""), // added by Matteo Piras - up to here all ok
          "AudioObjectFixed", "twr20", Channel::Events,
          Channel::OneOrMoreEntries, Channel::MixedPacking),



  citation_token(getId(), NameSet(getEntity(), "CitationOutput", part),101),



  // activity initialization
  //myclock(),
  cb1(this, &_ThisModule_::doCalculation),
  do_calc(getId(), "contains comm info ", &cb1, ps)
{
  // do the actions you need for the simulation

  std::cout << "Testing the initialization" << std::endl;
  // connect the triggers for simulation
  do_calc.setTrigger(citation_token);

  // connect the triggers for trim calculation. Leave this out if you
  // don not need input for trim calculation
  //trimCalculationCondition(/* fill in your trim triggering channels */);
}

bool ATC::complete()
{
  /* All your parameters have been set. You may do extended
     initialisation here. Return false if something is wrong. */
  return true;
}

// destructor
ATC::~ATC()
{
  //
}

// as an example, the setTimeSpec function
bool ATC::setTimeSpec(const TimeSpec& ts)
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
bool ATC::checkTiming(const std::vector<int>& i)
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
bool ATC::isPrepared()
{
  bool res = true;

  // Example checking a token:
  // CHECK_TOKEN(w_somedata);


  // Example checking anything
  // CHECK_CONDITION(myfile.good());
  // CHECK_CONDITION2(sometest, "some test failed");


  CHECK_TOKEN(w_comm);
  CHECK_TOKEN(citation_token);

  D_MOD("PREPARED");

  // return result of checks
  return res;
}

// start the module
void ATC::startModule(const TimeSpec &time)
{
  do_calc.switchOn(time);
}

// stop the module
void ATC::stopModule(const TimeSpec &time)
{
  do_calc.switchOff(time);
}

// fill a snapshot with state data. You may remove this method (and the
// declaration) if you specified to the SimulationModule that the size of
// state snapshots is zero
void ATC::fillSnapshot(const TimeSpec& ts,
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
void ATC::loadSnapshot(const TimeSpec& t, const Snapshot& snap)
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
void ATC::doCalculation(const TimeSpec& ts)
{
  //std::cout << "this is a test" << std::endl;
  // check the state we are supposed to be in
  switch (getAndCheckState(ts)) {
  case SimulationState::HoldCurrent: {
    // only repeat the output, do not change the model state

    try
    {
      StreamReader<CitationOutput> cit(citation_token, ts);

      lon = cit.data().y[Y_y];
      lat = cit.data().y[Y_x];


    }
    catch(Exception& e)
    {
      W_MOD(getId()<< classname << " caught " << e << " @ " << ts <<
                   " -- reading CitationOutput Channel");
    }








    D_MOD("STUCK IN HOLD");

    break;
    }

  case SimulationState::Replay:
  case SimulationState::Advance: {

    // access the input
    // example:
    // try {
    //   DataReader<MyInput> u(input_token, ts);
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

    try
    {
      StreamReader<CitationOutput> cit(citation_token, ts);

      lon = cit.data().y[Y_y];
      lat = cit.data().y[Y_x];



    }
    catch(Exception& e) {
      W_MOD(getId() << classname << " caught " << e << " @ " << ts <<
                    " -- reading CitationOutput Channel");
    }

    //lat  = c.y[Y_y];
    //lon  = c.y[Y_x];

    //std::cout << "LONG IS :";
    //std::cout << lon << std::endl;
    //std::cout << "playcomm is : ";
    //std::cout << playcomm << std::endl;


    if (lon < 14000 && playcomm == true){
        // time_req = clock();
        // std::cout << "TIME REQ START IS  : %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
        // std::cout <<time_req << std::endl;

        DataWriter<AudioObjectFixed> snddoc1(w_doc1, ts);
        snddoc1.data().volume = 1.0f;
        snddoc1.data().pitch = 1.0;
        //D_MOD("COMM TESTING POSITIVE %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%");
        playcomm = false;
        audio_trigger_time = clock();

        //std::cout << playcomm;

        // time_req = clock() - time_req;
        //time_req = (float)time_req/CLOCKS_PER_SEC;

        // std::cout << "TIME END IS  :";
        // std::cout << time_req << std::endl;
        // std::cout << "_________________________________________________________________________________________________________%";

                //if(time_req > 10) {
                  //DataWriter <AudioObjectFixed> sndtwr1(w_twr1, ts);
                  //sndtwr1.data().volume = 1.0f;
                  //sndtwr1.data().pitch = 1.0;
                //
    }

    if (audio_trigger_time != clock_t(0.0) && (clock() - audio_trigger_time)/CLOCKS_PER_SEC > 15) {
      DataWriter <AudioObjectFixed> sndtwr1(w_twr1, ts);
      sndtwr1.data().volume = 1.0f;
      sndtwr1.data().pitch = 1.0;

      audio_trigger_time = clock_t(0.0);
      //playcomm = true;

      audio_trigger_doc2 = clock();

    }

    if (audio_trigger_doc2 != clock_t(0.0) && (clock() - audio_trigger_doc2)/CLOCKS_PER_SEC > 16) {
      DataWriter <AudioObjectFixed> snddoc2(w_comm, ts);
      snddoc2.data().volume = 1.0f;
      snddoc2.data().pitch = 1.0;

      audio_trigger_doc2 = clock_t(0.0);
      audio_trigger_twr2 = clock();
    }


    if (audio_trigger_twr2 != clock_t(0.0) && (clock() - audio_trigger_twr2)/CLOCKS_PER_SEC > 8) {
      DataWriter <AudioObjectFixed> sndtwr2(w_twr2, ts);
      sndtwr2.data().volume = 1.0f;
      sndtwr2.data().pitch = 1.0;

      audio_trigger_twr2 = clock_t(0.0);

    }






    //std::cout << time_req << std::endl;
    //std::cout << clock() << std::endl;





    //std::cout << "PLAYCOMM AFTER IS : ";
    //std::cout << playcomm << std::endl;


    /**
      if(radioevent == true){

          DataWriter<AudioObjectFixed> sndcomm(w_comm, ts);
          sndcomm.data().volume = 0.5f;
          sndcomm.data().pitch = 1.0;
          D_MOD("comm sound sent");


      } */

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
  // DataWriter<MyOutput> y(output_token, ts);

  // write the output into the output channel, using the stream writer
  // y.data().var1 = something; ...

  if (snapshotNow()) {
    // keep a copy of the model state. Snapshot sending is done in the
    // sendSnapshot routine, later, and possibly at lower priority
    // e.g.
    // snapshot_state_variable1 = state_variable1; ...
    // (or maybe if your state is very large, there is a cleverer way ...)
  }
}

void ATC::trimCalculation(const TimeSpec& ts, const TrimMode& mode)
{
  // read the event equivalent of the input data
  // example
  // DataReader<MyData> u(i_input_token, ts);

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
  // DataWriter<MyOutput> y(output_token, ts);

  // write the output into the output channel, using the DataWriter

  // now return. The real results from the trim calculation, as you
  // specified them in the TrimTable, will now be collected and sent
  // off for processing.
}

// Make a TypeCreator object for this module, the TypeCreator
// will check in with the scheme-interpreting code, and enable the
// creation of modules of this type
static TypeCreator<ATC> a(ATC::getMyParameterTable());

