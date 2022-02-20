/* ------------------------------------------------------------------   */
/*      item            : GFC700GUI.cxx
        made by         : jordy
	from template   : DusimeModuleTemplate.cxx
        template made by: Rene van Paassen
        date            : Fri Mar 27 18:11:28 2020
	category        : body file
        description     :
	changes         : Fri Mar 27 18:11:28 2020 first version
	template changes: 030401 RvP Added template creation comment
	                  060512 RvP Modified token checking code
			  131224 RvP convert snap.data_size to
			         snap.getDataSize()
        language        : C++
        copyright       : (c) 2016 TUDelft-AE-C&S
*/


#define GFC700GUI_cxx
// include the definition of the module class
#include "GFC700GUI.hxx"

// include the debug writing header. Warning and error messages
// are on by default, debug and info can be selected by
// uncommenting the respective defines
// #define D_MOD
//#define I_MOD
#include <debug.h>

// include additional files needed for your calculation here

// the standard package for DUSIME, including template source
#define DO_INSTANTIATE
#include <dusime.h>

// class/module name
const char* const GFC700GUI::classname = "gf-c700-gui";

//GFC700GUI* GFC700GUI::theOne(NULL);

// initial condition/trim table
const IncoTable* GFC700GUI::getMyIncoTable()
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

// GTK callbacks
static GladeCallbackTable cbtable[] =
{
  // links the button, with signal pressed, to ButtonPress
  { "apr_button", "clicked", gtk_callback(&GFC700GUI::on_apr_button_clicked)},
  { "nav_button", "clicked", gtk_callback(&GFC700GUI::on_nav_button_clicked)},
  { "hdg_button", "clicked", gtk_callback(&GFC700GUI::on_hdg_button_clicked)},
  { "ap_button", "clicked", gtk_callback(&GFC700GUI::on_ap_button_clicked)},
  { "fd_button", "clicked", gtk_callback(&GFC700GUI::on_fd_button_clicked)},
  { "alt_button", "clicked", gtk_callback(&GFC700GUI::on_alt_button_clicked)},
  { "vnv_button", "clicked", gtk_callback(&GFC700GUI::on_vnv_button_clicked)},
  { "bc_button", "clicked", gtk_callback(&GFC700GUI::on_bc_button_clicked)},
  { "vs_button", "clicked", gtk_callback(&GFC700GUI::on_vs_button_clicked)},
  { "noseup_button", "clicked", gtk_callback(&GFC700GUI::on_noseup_button_clicked)},
  { "cdi_button", "clicked", gtk_callback(&GFC700GUI::on_cdi_button_clicked)},
  { "flc_button", "clicked", gtk_callback(&GFC700GUI::on_flc_button_clicked)},
  { "nosedn_button", "clicked", gtk_callback(&GFC700GUI::on_nosedn_button_clicked)},
  // { "alt_select", "value-changed", gtk_callback(&GFC700GUI::alt_select_changed)},
  // { "hdg_select", "value-changed", gtk_callback(&GFC700GUI::hdg_select_changed)},
  // { "crs_select", "value-changed", gtk_callback(&GFC700GUI::crs_select_changed)},
  // close off in familiar style
  { NULL, NULL, NULL, NULL }
};

// parameters to be inserted
const ParameterTable* GFC700GUI::getMyParameterTable()
{
  static const ParameterTable parameter_table[] = {
    { "set-timing",
      new MemberCall<_ThisModule_,TimeSpec>
        (&_ThisModule_::setTimeSpec), set_timing_description },

    { "check-timing",
      new MemberCall<_ThisModule_,vector<int> >
      (&_ThisModule_::checkTiming), check_timing_description },

      { "set-position-and-size",
        new MemberCall<GFC700GUI, vector<int> >
        (&GFC700GUI::setWindowPositionSize),
        "Supply the position (offset x, offset y) and the size (width, height) for the window, <=0 are ignored" },

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
GFC700GUI::GFC700GUI(Entity* e, const char* part, const
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

  // initialize the data you need for the trim calculation

  // initialize the channel access tokens, check the documentation for the
  // various parameters. Some examples:
  // r_mytoken(getId(), NameSet(getEntity(), MyData::classname, part),
  //           MyData::classname, 0, Channel::Events, Channel::ReadAllData),
  // w_mytoken(getId(), NameSet(getEntity(), MyData::classname, part),
  //           MyData::classname, "label", Channel::Continuous),
  prev_state(SimulationState::Undefined),


  // GUI items
  winglade(),

  // GUI buttons
  apr_button(NULL), nav_button(NULL), hdg_button(NULL), ap_button(NULL),
  fd_button(NULL), alt_button(NULL), vnv_button(NULL), bc_button(NULL),
  vs_button(NULL), noseup_button(NULL), flc_button(NULL), nosedn_button(NULL),
  cdi_button(NULL), alt_select(NULL), hdg_select(NULL), crs_select(NULL),

  hdg(0),
  prev_hdg(0),

  alt(0),
  prev_alt(0),

  crs(0),
  prev_crs(0),

  apr_pressed(false),
  // alt_select_value(0),

  gfc_token(getId(), NameSet(getEntity(), "GFC700Event", part), ChannelDistribution::NO_OPINION),

  // activity initialization
  myclock(),
  cb1(this, &_ThisModule_::doCalculation),
  do_calc(getId(), "", &cb1, ps)
{

  // do the actions you need for the simulation
  winglade.readGladeFile("gfcgui.glade", "gfc700gui", reinterpret_cast<gpointer>(this), cbtable);


  // connect the triggers for simulation
  do_calc.setTrigger( myclock );

  // connect the triggers for trim calculation. Leave this out if you
  // don not need input for trim calculation
//   trimCalculationCondition(/* fill in your trim triggering channels */);
}

bool GFC700GUI::complete()
{
  /* All your parameters have been set. You may do extended
     initialisation here. Return false if something is wrong. */
     // g_send_button = winglade["g_send_button"];
     // g_reset_button = winglade["g_reset_button"];
     apr_button = winglade["apr_button"];
     nav_button = winglade["nav_button"];
     hdg_button = winglade["hdg_button"];
     ap_button = winglade["ap_button"];
     fd_button = winglade["fd_button"];
     alt_button = winglade["alt_button"];
     vnv_button = winglade["vnv_button"];
     bc_button = winglade["bc_button"];
     vs_button = winglade["vs_button"];
     noseup_button = winglade["noseup_button"];
     flc_button = winglade["flc_button"];
     nosedn_button = winglade["nosedn_button"];
     cdi_button = winglade["cdi_button"];
     alt_select = winglade["alt_select"];
     hdg_select = winglade["hdg_select"];
     crs_select = winglade["crs_select"];


     winglade.show();

  return true;
}

// destructor
GFC700GUI::~GFC700GUI()
{
  //
}

// as an example, the setTimeSpec function
bool GFC700GUI::setTimeSpec(const TimeSpec& ts)
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
bool GFC700GUI::checkTiming(const vector<int>& i)
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
bool GFC700GUI::isPrepared()
{
  bool res = true;

  // Example checking a token:
  // CHECK_TOKEN(w_somedata);

  // Example checking anything
  // CHECK_CONDITION(myfile.good());
  // CHECK_CONDITION2(sometest, "some test failed");

  CHECK_CONDITION(apr_button);
  CHECK_CONDITION(nav_button);
  CHECK_CONDITION(hdg_button);
  CHECK_CONDITION(ap_button);
  CHECK_CONDITION(fd_button);
  CHECK_CONDITION(alt_button);
  CHECK_CONDITION(vnv_button);
  CHECK_CONDITION(bc_button);
  CHECK_CONDITION(vs_button);
  CHECK_CONDITION(noseup_button);
  CHECK_CONDITION(flc_button);
  CHECK_CONDITION(nosedn_button);
  CHECK_CONDITION(cdi_button);
  CHECK_CONDITION(alt_select);
  CHECK_CONDITION(hdg_select);
  CHECK_CONDITION(crs_select);

  CHECK_TOKEN(gfc_token);

  // return result of checks
  return res;
}

// start the module
void GFC700GUI::startModule(const TimeSpec &time)
{
  do_calc.switchOn(time);
}

// stop the module
void GFC700GUI::stopModule(const TimeSpec &time)
{
  do_calc.switchOff(time);
}

// fill a snapshot with state data. You may remove this method (and the
// declaration) if you specified to the SimulationModule that the size of
// state snapshots is zero
void GFC700GUI::fillSnapshot(const TimeSpec& ts,
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
void GFC700GUI::loadSnapshot(const TimeSpec& t, const Snapshot& snap)
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
void GFC700GUI::doCalculation(const TimeSpec& ts)
{
  // check the state we are supposed to be in
  switch (getAndCheckState(ts)) {
  case SimulationState::HoldCurrent: {
    // only repeat the output, do not change the model state



    if(prev_state != SimulationState::HoldCurrent) {
  		// enable buttons
  		// gtk_widget_set_sensitive(GTK_WIDGET(g_send_button), true);
  		// gtk_widget_set_sensitive(GTK_WIDGET(g_reset_button), true);

      gtk_widget_set_sensitive(GTK_WIDGET(apr_button), true);
      gtk_widget_set_sensitive(GTK_WIDGET(nav_button), true);
      gtk_widget_set_sensitive(GTK_WIDGET(hdg_button), true);
      gtk_widget_set_sensitive(GTK_WIDGET(ap_button), true);
      gtk_widget_set_sensitive(GTK_WIDGET(fd_button), true);
      gtk_widget_set_sensitive(GTK_WIDGET(alt_button), true);
      gtk_widget_set_sensitive(GTK_WIDGET(vnv_button), true);
      gtk_widget_set_sensitive(GTK_WIDGET(bc_button), true);
      gtk_widget_set_sensitive(GTK_WIDGET(vs_button), true);
      gtk_widget_set_sensitive(GTK_WIDGET(noseup_button), true);
      gtk_widget_set_sensitive(GTK_WIDGET(flc_button), true);
      gtk_widget_set_sensitive(GTK_WIDGET(nosedn_button), true);
      gtk_widget_set_sensitive(GTK_WIDGET(cdi_button), true);
      // gtk_widget_set_sensitive(GTK_WIDGET(alt_update_button), true);
  		// mark the simulation state we are in now
  		prev_state = SimulationState::HoldCurrent;
  	}

    break;
    }

  case SimulationState::Replay:
  case SimulationState::Advance: {
    if(prev_state != SimulationState::Advance) {
  		// disable buttons
  		//gtk_widget_set_sensitive(GTK_WIDGET(g_send_button), false); // comment this line to use the send button in advance
  		// gtk_widget_set_sensitive(GTK_WIDGET(g_reset_button), false);
  		// mark the simulation state we are in now
  		prev_state = SimulationState::Advance;

  	}

    hdg = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(hdg_select));
    alt = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(alt_select));
    crs = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(crs_select));

    if(hdg!=prev_hdg){
      EventWriter<GFC700Event> gfc_writer(gfc_token);
      gfc_writer.data().alt_select = alt;
      gfc_writer.data().hdg_select = hdg;
      gfc_writer.data().crs_select = crs;
      gfc_writer.data().msg = GFC700Event::GFC700_NONE;
    }
    if(alt!=prev_alt){
      EventWriter<GFC700Event> gfc_writer(gfc_token);
      gfc_writer.data().alt_select = alt;
      gfc_writer.data().hdg_select = hdg;
      gfc_writer.data().crs_select = crs;
      gfc_writer.data().msg = GFC700Event::GFC700_NONE;
    }
    if(crs!=prev_crs){
      EventWriter<GFC700Event> gfc_writer(gfc_token);
      gfc_writer.data().alt_select = alt;
      gfc_writer.data().hdg_select = hdg;
      gfc_writer.data().crs_select = crs;
      gfc_writer.data().msg = GFC700Event::GFC700_NONE;
    }

    prev_hdg = hdg;
    prev_alt = alt;
    prev_crs = crs;

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


  // EventWriter<GFC700Event> gfc_writer(gfc_token, ts);
  // if(apr_pressed){
  //   gfc_writer.data().msg = GFC700Event::GFC700_APR;
  //   D_MOD("MSG send")
  //   // gfc_writer.data().data = 0.0;
  //   apr_pressed = false;
  // }



  if (snapshotNow()) {
    // keep a copy of the model state. Snapshot sending is done in the
    // sendSnapshot routine, later, and possibly at lower priority
    // e.g.
    // snapshot_state_variable1 = state_variable1; ...
    // (or maybe if your state is very large, there is a cleverer way ...)
  }
}

void GFC700GUI::trimCalculation(const TimeSpec& ts, const TrimMode& mode)
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

void GFC700GUI::on_apr_button_clicked(GtkButton *button, gpointer user_data)
{
  apr_pressed = true;
  // gfc_token.sendEvent(new GFC700Event(GFC700Event::GFC700_APR, 0.0), ts);
  EventWriter<GFC700Event> gfc_writer(gfc_token);
  gfc_writer.data().msg = GFC700Event::GFC700_APR;
  gfc_writer.data().alt_select = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(alt_select));
  gfc_writer.data().hdg_select = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(hdg_select));
  gfc_writer.data().crs_select = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(crs_select));
  //D_MOD("APR button clicked and send")
}

void GFC700GUI::on_nav_button_clicked(GtkButton *button, gpointer user_data)
{
  EventWriter<GFC700Event> gfc_writer(gfc_token);
  gfc_writer.data().msg = GFC700Event::GFC700_NAV;
  gfc_writer.data().alt_select = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(alt_select));
  gfc_writer.data().hdg_select = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(hdg_select));
  gfc_writer.data().crs_select = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(crs_select));
  D_MOD("NAV button clicked")
}
void GFC700GUI::on_hdg_button_clicked(GtkButton *button, gpointer user_data)
{
  EventWriter<GFC700Event> gfc_writer(gfc_token);
  gfc_writer.data().msg = GFC700Event::GFC700_HDG;
  gfc_writer.data().alt_select = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(alt_select));
  gfc_writer.data().hdg_select = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(hdg_select));
  gfc_writer.data().crs_select = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(crs_select));
  D_MOD("HDG button clicked")
}
void GFC700GUI::on_ap_button_clicked(GtkButton *button, gpointer user_data)
{
  EventWriter<GFC700Event> gfc_writer(gfc_token);
  gfc_writer.data().msg = GFC700Event::GFC700_AP;
  gfc_writer.data().alt_select = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(alt_select));
  gfc_writer.data().hdg_select = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(hdg_select));
  gfc_writer.data().crs_select = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(crs_select));
  D_MOD("AP button clicked")
}
void GFC700GUI::on_fd_button_clicked(GtkButton *button, gpointer user_data)
{
  EventWriter<GFC700Event> gfc_writer(gfc_token);
  gfc_writer.data().msg = GFC700Event::GFC700_FD;
  gfc_writer.data().alt_select = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(alt_select));
  gfc_writer.data().hdg_select = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(hdg_select));
  gfc_writer.data().crs_select = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(crs_select));
  D_MOD("FD button clicked")
}
void GFC700GUI::on_alt_button_clicked(GtkButton *button, gpointer user_data)
{
  EventWriter<GFC700Event> gfc_writer(gfc_token);
  gfc_writer.data().msg = GFC700Event::GFC700_ALT;
  gfc_writer.data().alt_select = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(alt_select));
  gfc_writer.data().hdg_select = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(hdg_select));
  gfc_writer.data().crs_select = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(crs_select));
  D_MOD("ALT button clicked")
}
void GFC700GUI::on_vnv_button_clicked(GtkButton *button, gpointer user_data)
{
  EventWriter<GFC700Event> gfc_writer(gfc_token);
  gfc_writer.data().msg = GFC700Event::GFC700_VNV;
  gfc_writer.data().alt_select = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(alt_select));
  gfc_writer.data().hdg_select = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(hdg_select));
  gfc_writer.data().crs_select = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(crs_select));
  D_MOD("VNV button clicked")
}
void GFC700GUI::on_bc_button_clicked(GtkButton *button, gpointer user_data)
{
  EventWriter<GFC700Event> gfc_writer(gfc_token);
  gfc_writer.data().msg = GFC700Event::GFC700_BC;
  gfc_writer.data().alt_select = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(alt_select));
  gfc_writer.data().hdg_select = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(hdg_select));
  gfc_writer.data().crs_select = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(crs_select));
  D_MOD("BC button clicked")
}
void GFC700GUI::on_vs_button_clicked(GtkButton *button, gpointer user_data)
{
  EventWriter<GFC700Event> gfc_writer(gfc_token);
  gfc_writer.data().msg = GFC700Event::GFC700_VS;
  gfc_writer.data().alt_select = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(alt_select));
  gfc_writer.data().hdg_select = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(hdg_select));
  gfc_writer.data().crs_select = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(crs_select));
  D_MOD("VS button clicked")
}
void GFC700GUI::on_noseup_button_clicked(GtkButton *button, gpointer user_data)
{
  EventWriter<GFC700Event> gfc_writer(gfc_token);
  gfc_writer.data().msg = GFC700Event::GFC700_NOSEUP;
  gfc_writer.data().alt_select = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(alt_select));
  gfc_writer.data().hdg_select = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(hdg_select));
  gfc_writer.data().crs_select = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(crs_select));
  D_MOD("NOSE UP button clicked")
}
void GFC700GUI::on_flc_button_clicked(GtkButton *button, gpointer user_data)
{
  EventWriter<GFC700Event> gfc_writer(gfc_token);
  gfc_writer.data().msg = GFC700Event::GFC700_FLC;
  gfc_writer.data().alt_select = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(alt_select));
  gfc_writer.data().hdg_select = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(hdg_select));
  gfc_writer.data().crs_select = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(crs_select));
  D_MOD("FLC button clicked")
}
void GFC700GUI::on_nosedn_button_clicked(GtkButton *button, gpointer user_data)
{
  EventWriter<GFC700Event> gfc_writer(gfc_token);
  gfc_writer.data().msg = GFC700Event::GFC700_NOSEDN;
  gfc_writer.data().alt_select = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(alt_select));
  gfc_writer.data().hdg_select = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(hdg_select));
  gfc_writer.data().crs_select = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(crs_select));
  D_MOD("NOSE DN button clicked")
}
void GFC700GUI::on_cdi_button_clicked(GtkButton *button, gpointer user_data)
{
  EventWriter<GFC700Event> gfc_writer(gfc_token);
  gfc_writer.data().msg = GFC700Event::GFC700_CDI;
  gfc_writer.data().alt_select = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(alt_select));
  gfc_writer.data().hdg_select = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(hdg_select));
  gfc_writer.data().crs_select = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(crs_select));
  D_MOD("NOSE DN button clicked")
}
void GFC700GUI::alt_select_changed(GtkSpinButton *spin_button, gpointer user_data)
{
  EventWriter<GFC700Event> gfc_writer(gfc_token);
  gfc_writer.data().alt_select = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(alt_select));
  gfc_writer.data().hdg_select = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(hdg_select));
  gfc_writer.data().crs_select = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(crs_select));
}
void GFC700GUI::hdg_select_changed(GtkSpinButton *spin_button, gpointer user_data)
{
  EventWriter<GFC700Event> gfc_writer(gfc_token);
  // gfc_writer.data().alt_select = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(alt_select));
  // gfc_writer.data().hdg_select = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(hdg_select));
  // gfc_writer.data().crs_select = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(crs_select));
}
void GFC700GUI::crs_select_changed(GtkSpinButton *spin_button, gpointer user_data)
{
  EventWriter<GFC700Event> gfc_writer(gfc_token);
  gfc_writer.data().alt_select = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(alt_select));
  gfc_writer.data().hdg_select = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(hdg_select));
  gfc_writer.data().crs_select = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(crs_select));
}

// void GFC700GUI::alt_select_changed(GtkSpinButton *spin_button, gpointer user_data)
// {
//   // Following if-statement required at start-up; spin_button
//   // if(alt_select_value!=round(gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(alt_select))))
//   // {
//   //   alt_select_value = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(alt_select));
//   //   D_MOD("where here")
//   //   EventWriter<GFC700Event> gfc_writer(gfc_token);
//   //   gfc_writer.data().alt_select = alt_select_value;
//   // }
//   // D_MOD("New alt select: "<<alt_select_value)
// }

// Make a TypeCreator object for this module, the TypeCreator
// will check in with the scheme-interpreting code, and enable the
// creation of modules of this type
bool GFC700GUI::setWindowPositionSize( const vector< int >& p_vector )
{
    bool succes = true;

    // Check for the size
    if ( p_vector.size() == 4 )
    {
        winglade.setWindow( p_vector );
    }
    else
    {
        E_MOD( getId() << "/" << classname << "::setWindowPositionSize: an incorrect number of elements are supplied, no 4 but " << p_vector.size() );
        succes = false;
    }

    return succes;
}

static TypeCreator<GFC700GUI> a(GFC700GUI::getMyParameterTable());
