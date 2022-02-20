/* ------------------------------------------------------------------   */
/*      item            : MotionViewerModule.cxx
        made by         : stroosma
        date            : 010726
	category        : body file
        description     :
	changes         : 010726 first version
        language        : C++
*/

const static char c_id[] =
"$Id: MotionViewerModule.cxx,v 1.5 2019/10/01 12:32:49 fltsim Exp $";

#define MotionViewerModule_cxx
// include the definition of the module class
#include "MotionViewerModule.hxx"

// include the debug writing header, by default, write warning and 
// error messages
#define W_MOD
#define E_MOD
#include <debug.h>

// include additional files needed for your calculation here
#include <sstream>
#define RAD2DEG 57.2957795

// the standard package for DUSIME, including template source
#define DO_INSTANTIATE
#include <dusime.h>

// class/module name
const char* const MotionViewerModule::classname = "motion-viewer";

// initial condition/trim table
const IncoTable* MotionViewerModule::getMyIncoTable()
{
  static IncoTable inco_table[] = {
    // enter pairs of IncoVariable and VarProbe pointers (i.e.
    // objects made with new), in this table.
    // For example
//    {(new IncoVariable("example", 0.0, 1.0, 0.01))
//     ->forMode(FlightPath, Constraint)
//     ->forMode(Speed, Control),
//     new VarProbe<MotionViewerModule,double>
//       (REF_MEMBER(&MotionViewerModule::i_example))}
    
    // always close off with:
    { NULL, NULL} };

  return inco_table;
}

// parameters to be inserted
const ParameterTable* MotionViewerModule::getMyParameterTable()
{
  static const ParameterTable parameter_table[] = {
    { "set-timing", 
      new MemberCall<MotionViewerModule,TimeSpec>
        (&MotionViewerModule::setTimeSpec)},

    { "set-position-and-size",
      new MemberCall<MotionViewerModule,vector<int> >
      (&MotionViewerModule::setWindowPositionSize)},

    // always close off with:
    { NULL, NULL} };

  return parameter_table;
}

// constructor
MotionViewerModule::MotionViewerModule(Entity* e, const char* part, const
		       PrioritySpec& ps) :
  SimulationModule(e, classname, part, getMyIncoTable()),

  // initialize the data you need in your simulation
  drawer(new MotionViewer),
  // initialize the data you need for the trim calculation
  
  // initialize the channel access tokens
  // example
  // my_token(getId(), NameSet(getEntity(), "MyData", part)),
  mgp_token(getId(), NameSet(getEntity(), "MotionGimbalPositions", part)),
  mcpva_token(getId(), NameSet(getEntity(), "MotionCommandedPosVelAcc", part),101),

  // activity initialization
  cb1(this, &MotionViewerModule::doCalculation),

  //cb2(this, &MotionViewerModule::doTrimCalculation),
  do_calc(getId(), "MotionViewer calculation", &cb1, ps)
{
  // do the actions you need for the simulation

  // connect the triggers for simulation and trim, and activate trim
  do_calc.setTrigger(mgp_token && mcpva_token);
}


// destructor
MotionViewerModule::~MotionViewerModule()
{
  //
}

bool MotionViewerModule::complete(void)
{
	drawer->openWindow();
	return true;
}

// as an example, the setTimeSpec function
bool MotionViewerModule::setTimeSpec(const TimeSpec& ts)
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


// tell DUECA you are prepared
bool MotionViewerModule::isPrepared()
{
  // do whatever calculations you need to prepare the model. Return
  // with false if something is wrong

  // return true if all tokens are valid
  bool res = true;

  CHECK_TOKEN(mgp_token);
  CHECK_TOKEN(mcpva_token);

  return res;
}

// start the module
void MotionViewerModule::startModule(const TimeSpec &time)
{
  do_calc.switchOn(time);
}

// stop the module
void MotionViewerModule::stopModule(const TimeSpec &time)
{
  do_calc.switchOff(time);
}

// send a snapshot
Snapshot* MotionViewerModule::sendSnapshot(const TimeSpec& t, bool for_inco)
{
  // fill in the size of your snapshot state for the new snapshot
  Snapshot* snap = new Snapshot(0, getNameSet());
  AmorphStore s(snap->accessData(), snap->getDataSize());

  // use packData(s, ...) to pack your state into the snapshot

  // return the snapshot
  return snap;
}

// reload from a snapshot
void MotionViewerModule::loadSnapshot(const TimeSpec& t, const Snapshot& snap)
{
  // access the data in the snapshot with an AmorphReStore object
  AmorphReStore store(snap.data, snap.data_size);

  // use unpackData(s, ... ) to unpack the data from the snapshot. 
  // You can safely do this, while snapshot loading is going on the 
  // simulation is in HoldCurrent or the activity is stopped. 
}


void MotionViewerModule::doCalculation(const TimeSpec& ts)
{
  // check the state we are supposed to be in
  switch (getAndCheckState(ts)) {
  case SimulationState::HoldCurrent:
  case SimulationState::Advance: {
    // access the input
    // example
    // const MyInput* u;
    // input_token.getAccess(u, t);
    //const MotionGimbalPositions* u;
    
    // check if we're too slow
    if (do_calc.noScheduledBehind())
      {
	W_MOD(classname << " lagging... skip " );
	return;
      }
    
    try {
      StreamReader<MotionGimbalPositions> mgp (mgp_token, ts);
      StreamReader<MotionCommandedPosVelAcc> mcpva(mcpva_token, ts);

      // do the simulation calculations, one step
      // OS: fill in the data in the drawer
      for (int i = 0; i<6; ++i)
	{
	  drawer->legs[i].x1 = mgp.data().x[i];
	  drawer->legs[i].y1 = mgp.data().y[i];
	  drawer->legs[i].z1 = mgp.data().z[i];
	  drawer->legs[i].status = 0;
	  // 25APR2002 status
	  drawer->legs[i].status = 0;
	  // braking, 50%
	  if( (mgp.data().status >> 4*i) & JACK_BRAKE )
	    drawer->legs[i].status = 50;
	  // min/max position, 100%
	  if( ( (mgp.data().status >> 4*i) & JACK_MIN ) ||
	      ( (mgp.data().status >> 4*i) & JACK_MAX ) )
	    drawer->legs[i].status = 100;
	}
      
      // display the status
      stringstream s;
      s << "motion status: " << mgp.data().status;
      drawer->display_text = s.str();

      // set cab orientation
      drawer->cabin.x = mcpva.data().x;
      drawer->cabin.y = mcpva.data().y;
      drawer->cabin.z = mcpva.data().z;
      drawer->cabin.phi= mcpva.data().phi*RAD2DEG;
      drawer->cabin.theta = mcpva.data().theta*RAD2DEG;
      drawer->cabin.psi = mcpva.data().psi*RAD2DEG;

      // tell the display
      drawer->redraw();
    }
    catch(Exception& e)
      {
	W_MOD(classname << " caught " << e << " @ " << ts);
      }

    break;
    }
  default:{
    break;
  }
  }

  if (snapshotNow()) {
    // keep a copy of the model state. Snapshot sending is done in the
    // sendSnapshot routine, later, and possibly at lower priority
  }
}

bool MotionViewerModule::setWindowPositionSize(const vector<int> &p_vector)
{
  bool succes = true;

  // Check for the size
  if ( p_vector.size() == 4 )
  {
    // Note that the number are the x-position, y-position, width, height
    drawer->setWindow( p_vector );
  }
  else
  {
    E_MOD( getId() << "/" << classname << "::setWindowPositionSize: an incorrect number of elements are supplied, no 4 but " << p_vector.size() );
    succes = false;
  }

  return succes;
}

// Make a TypeCreator object for this module, the TypeCreator
// will check in with the scheme-interpreting code, and enable the
// creation of modules of this type
static TypeCreator<MotionViewerModule> a(MotionViewerModule::getMyParameterTable());

