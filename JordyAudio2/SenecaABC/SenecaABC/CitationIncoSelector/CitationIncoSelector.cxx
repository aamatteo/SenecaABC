/* ------------------------------------------------------------------   */
/*      item            : CitationIncoSelector.cxx
        made by         : stroosma
	from template   : DusimeModuleTemplate.cxx
        template made by: Rene van Paassen
        date            : Wed Jan 12 10:47:18 2005
	category        : body file
        description     :
	changes         : Wed Jan 12 10:47:18 2005 first version
	template changes: 030401 RvP Added template creation comment
        language        : C++
*/

static const char c_id[] =
"$Id: CitationIncoSelector.cxx,v 1.2 2020/07/20 10:09:55 jkvanleeuwen Exp $";

#define CitationIncoSelector_cxx
// include the definition of the module class
#include "CitationIncoSelector.hxx"

// include the debug writing header, by default, write warning and
// error messages
//#define D_MOD
#define I_MOD
#define W_MOD
#define E_MOD
#include <debug.h>

// include additional files needed for your calculation here
#include <fstream>

// file juggling headers
#include <cstring>

// the standard package for DUSIME, including template source
#define DO_INSTANTIATE
#include <dusime.h>

// conversions
#ifndef DEG2RAD
#define DEG2RAD 1.7453291e-2
#endif

#ifndef FT2M
#define FT2M 0.3048
#endif

#ifndef KTS2MPS
#define KTS2MPS 0.5144444
#endif

// class/module name
const char* const CitationIncoSelector::classname = "citation-inco-selector";

// the pointer to the module
CitationIncoSelector* CitationIncoSelector::theOne(NULL);

// initial condition/trim table
const IncoTable* CitationIncoSelector::getMyIncoTable()
{
  static IncoTable inco_table[] = {
    // always close off with:
    { NULL, NULL} };

  return inco_table;
}

// parameters to be inserted
const ParameterTable* CitationIncoSelector::getMyParameterTable()
{
  static const ParameterTable parameter_table[] = {
    { "set-timing",
      new MemberCall<CitationIncoSelector,TimeSpec>
        (&CitationIncoSelector::setTimeSpec), set_timing_description },

    { "check-timing",
      new MemberCall<CitationIncoSelector,vector<int> >
      (&CitationIncoSelector::checkTiming), check_timing_description },

    { "vliegtuigtype",
      new VarProbe<CitationIncoSelector, int >
      (&CitationIncoSelector::vliegtuigtype),
      "1 = Citation, 2 = Piper Seneca"},

    /* You can extend this table with labels and MemberCall or
       VarProbe pointers to perform calls or insert values into your
       class objects. Please also add a description (c-style string).

       Note that for efficiency, set_timing_description and
       check_timing_description are pointers to pre-defined strings,
       you can simply enter the descriptive strings in the table. */

    /* The table is closed off with NULL pointers for the variable
       name and MemberCall/VarProbe object. The description is used to
       give an overall description of the module. */
    { NULL, NULL, "selects initial condition and turbulence"} };

  return parameter_table;
}

// GTK callbacks
static GladeCallbackTable cbtable[] =
{
  // links the button, with signal pressed, to ButtonPress
  { "sendbutton", "clicked", gtk_callback(&CitationIncoSelector::onSendButtonClicked)},
  { "savebutton", "clicked", gtk_callback(&CitationIncoSelector::onSnapshotButtonClicked)},
  { "checkbutton1", "toggled", gtk_callback(&CitationIncoSelector::onCheckButton1Toggled)}, // to en/disable turb. int. spin.
  { "reposbutton", "clicked", gtk_callback(&CitationIncoSelector::onReposButtonClicked)},
  { "Send_wind", "clicked", gtk_callback(&CitationIncoSelector::onWindButtonClicked)},
  // close off in familiar style
  { NULL, NULL, NULL, NULL }
};


// constructor


CitationIncoSelector::CitationIncoSelector(Entity* e, const char* part, const
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
  SimulationModule(e, classname, part, getMyIncoTable(), sizeof(real_T)*NCSTATES),

  // initialize the data you need in your simulation
  prev_state(SimulationState::Undefined),
  // GUI buttons
  sendbutton(NULL), reposbutton(NULL),
  // GUI items
  theWindow(NULL), combo1(NULL),
  turbbutton(NULL), turbspinner(NULL),
  filewindow(NULL), reposX(NULL), reposY(NULL), reposZ(NULL), reposPsi(NULL),lat_N(NULL),long_E(NULL),
  windbutton(NULL), windvelspinner(NULL), winddirspinner(NULL),shearbutton(NULL),
  //
  snap_trim(false),
  trim_de(0.0),
  trim_da(0.0),
  trim_dr(0.0),
  trim_pla1(0.75),
  trim_pla2(0.75),
  trim_gear(0.0),
  trim_flaps(0.0),
  //
  snap_available(false),

  // initialize the data you need for the trim calculation

  // initialize the channel access tokens
  // example
  // my_token(getId(), NameSet(getEntity(), "MyData", part)),
  snap_token(getId(), NameSet(getEntity(), "Snapshot", "set"), ChannelDistribution::JOIN_MASTER),
  star_token(getId(), NameSet(getEntity(), "STARSelect", "")),
  sr_token(getId(), NameSet(getEntity(), "SnapshotRequest", "")),
  repos_token(getId(), NameSet(getEntity(), "Reposition", ""), ChannelDistribution::NO_OPINION),
  trim_inco_token(getId(), NameSet(getEntity(), "Trim_inco","")),
  in_token(getId(), NameSet(getEntity(), "CitationOutput",part),101),
  cpi_token(getId(), NameSet(getEntity(), "CitationPilotInput", part), 101),
  inco_sel_token(getId(), NameSet(getEntity(), "INCOSelect","")),
  turb_write_token(getId(), NameSet(getEntity(), "WindEvent", ""), ChannelDistribution::NO_OPINION),
  turb_read_token(getId(), NameSet(getEntity(), "WindEvent",part)),

 // activity initialization
  cb1(this, &CitationIncoSelector::doCalculation),
  do_calc(getId(), "selecting the inco", &cb1, ps)
{
  // do the actions you need for the simulation
  winglade.readGladeFile("citincosel.glade", "CitIncoSel", reinterpret_cast<gpointer>(this), cbtable);

  // establish a global pointer to myself
  theOne = this;

  // connect the triggers for simulation
  do_calc.setTrigger(*Ticker::single());

  // connect the triggers for trim calculation. Leave this out if you
  // don not need input for trim calculation
  //trimCalculationCondition(/* fill in your trim triggering channels */);
}

bool CitationIncoSelector::complete()
{
  /* All your parameters have been set. You may do extended
     initialisation here. Return false if something is wrong. */

  sendbutton = winglade["sendbutton"];
  reposbutton = winglade["reposbutton"];

  // find the main window
  theWindow = winglade["CitIncoSel"];

  // create the secondary windows
  // note this is still necessary because GladeWindow cannot handle
  // multiple windows per glade file
  filewindow = create_fileselection1();

  // find the relevant widgets
  combo1 = winglade["combo1"];
  if(!combo1) {
    E_MOD(getId() << " couldn't find the combo1 widget ");
    return false;
  }

  turbbutton = winglade["checkbutton1"];
  if(!turbbutton) {
    E_MOD(getId() << " couldn't find the checkbutton1 widget ");
    return false;
  }

  shearbutton = winglade["checkbutton2"];
  if(!turbbutton) {
    E_MOD(getId() << " couldn't find the wind shear button2 widget ");
    return false;
  }

  turbspinner = winglade["spinbutton1"];
  if(!turbspinner) {
    E_MOD(getId() << " couldn't find the spinbutton1 widget ");
    return false;
  }

  reposX = winglade["reposx_spin"];
  if(!reposX) {
    E_MOD(getId() << " couldn't find the reposx_spin widget ");
    return false;
  }

  reposY = winglade["reposy_spin"];
  if(!reposY) {
    E_MOD(getId() << " couldn't find the reposy_spin widget ");
    return false;
  }

  reposZ = winglade["reposalt_spin"];
  if(!reposZ) {
    E_MOD(getId() << " couldn't find the reposalt_spin widget ");
    return false;
  }

  reposPsi = winglade["reposhdg_spin"];
  if(!reposPsi) {
    E_MOD(getId() << " couldn't find the reposhdg_spin widget ");
    return false;
  }


  lat_N = winglade["lat_N"];
  if(!lat_N) {
    E_MOD(getId() << " couldn't find the latitude widget ");
    return false;
  }

  long_E= winglade["long_E"];
  if(!long_E) {
    E_MOD(getId() << " couldn't find the longtitude widget ");
    return false;
   }

  windbutton =winglade["Send_wind"];
  if(!windbutton){
    E_MOD(getId() << " could not find the Send wind widget");
    return false;
    }

  windvelspinner =winglade["Wind_vel"];
  if(!windvelspinner){
    E_MOD(getId() << " could not find the  wind vel widget");
    return false;
    }

  winddirspinner =winglade["Wind_dir"];
  if(!windbutton){
    E_MOD(getId() << " copuld not find the  wind dir widget");
    return false;
    }

  // fill in the combo list
  // get a list of .inco files
  struct dirent **incolist;
  int ninco = scandir(".", &incolist, is_inco_file, alphasort);

  // put them in a GTK list
  GList *glist = NULL;

  for(int i=0; i< ninco; i++) {
    char* inco = new char[strlen(incolist[i]->d_name)-5+1];
    strncpy(inco, incolist[i]->d_name, strlen(incolist[i]->d_name)-5);
    inco[strlen(incolist[i]->d_name)-5] = '\0';
    glist = g_list_append(glist, inco);
  }

  // add the strings to the dropdown list
  // TODO GTKCombo is deprecated, replace
  gtk_combo_set_popdown_strings (GTK_COMBO (combo1), glist);

  // show the window
  gtk_widget_show(theWindow);

  // read the template
  if(!readIncoTemplate("template.inco.txt")) return false;

  // toggle the turbulence intensity spin button based on turb toggle
  gtk_widget_set_sensitive(GTK_WIDGET(turbspinner),
			   gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(turbbutton)));

  return true;
}

// destructor
CitationIncoSelector::~CitationIncoSelector()
{
  //
}

// as an example, the setTimeSpec function
bool CitationIncoSelector::setTimeSpec(const TimeSpec& ts)
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
bool CitationIncoSelector::checkTiming(const vector<int>& i)
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
bool CitationIncoSelector::isPrepared()
{
  // do whatever additional calculations you need to prepare the model.

  // Check that all conditions for running are good.
  bool res = true;

  // token checks
  CHECK_TOKEN(snap_token);
  CHECK_TOKEN(star_token);
  CHECK_TOKEN(sr_token);
  CHECK_TOKEN(repos_token);
  CHECK_TOKEN(in_token);
  CHECK_TOKEN(trim_inco_token);
  CHECK_TOKEN(cpi_token);
  CHECK_TOKEN(inco_sel_token);
//  CHECK_TOKEN(turb_token);
  CHECK_TOKEN(turb_write_token);
  CHECK_TOKEN(turb_read_token);

  // gui item checks
  CHECK_CONDITION(sendbutton);
  CHECK_CONDITION(reposbutton);
  // TODO add all GtkWidgets here, instead of the check in complete()

  // return result of check
  return res;
}

// start the module
void CitationIncoSelector::startModule(const TimeSpec &time)
{
  do_calc.switchOn(time);
}

// stop the module
void CitationIncoSelector::stopModule(const TimeSpec &time)
{
  do_calc.switchOff(time);
}

// fill a snapshot with state data. You may remove this method (and the
// declaration) if you specified to the SimulationModule that the size of
// state snapshots is zero
void CitationIncoSelector::fillSnapshot(const TimeSpec& ts,
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

// Saving van Snapshot dat wordt gekregen van model
//PETER: snapshot is saved to file by function CitationIncoSelector::onOKButtonClicked
void CitationIncoSelector::loadSnapshot(const TimeSpec& t, const Snapshot& snap)
{
  // access the data in the snapshot with an AmorphReStore object
  AmorphReStore s(snap.data, snap.data_size);

  incoming_snap.clear();

  double d;
  if (vliegtuigtype==1){
     for(int i=0;i<NCSTATES;i++) {
	unPackData(s, d);
	incoming_snap.push_back(d);
	D_MOD(classname << "  received state: " << i << " Value=" << d);
	}
    D_MOD(classname << " received new snapshot from model  NCSTATES= " << NCSTATES << " Vliegtuigtype="<< vliegtuigtype);
    if(!GTK_IS_WIDGET(filewindow)) {
       filewindow = create_fileselection1();
    }
    gtk_widget_show(filewindow); // snapshot is saved on clicking OK
  }
  if (vliegtuigtype==2){

    for(int i=0;i<17;i++) {
  	unPackData(s, d);
	incoming_snap.push_back(d);
	D_MOD(classname << "  received state: " << i << " Value=" << d);
   }
   D_MOD(classname << " received new snapshot from model  Max i was= " <<  NCSTATES << " Vliegtuigtype="<< vliegtuigtype);


   if(!GTK_IS_WIDGET(filewindow)) {
    filewindow = create_fileselection1();
   }
   gtk_widget_show(filewindow); // snapshot is saved on clicking OK

  // use unPackData(s, real_state_variable1 ); ... to unpack the data
  // from the snapshot.
  // You can safely do this, while snapshot loading is going on the
  // simulation is in HoldCurrent or the activity is stopped
  }
}

// this routine contains the main simulation process of your module. You
// should read the input channels here, and calculate and write the
// appropriate output

void CitationIncoSelector::doCalculation(const TimeSpec& ts)
{
	// Read Wind/Turb.
	if (turb_read_token.getNumWaitingEvents(ts))
	{
		try
		{
			EventReader<WindEvent> w(turb_read_token, ts);

			// update the GUI
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(turbbutton), w.data().turbulence);
			gtk_spin_button_set_value(GTK_SPIN_BUTTON(turbspinner), w.data().turb_int);
			gtk_spin_button_set_value(GTK_SPIN_BUTTON(windvelspinner), w.data().wind_vel);
			gtk_spin_button_set_value(GTK_SPIN_BUTTON(winddirspinner), w.data().wind_dir);
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(shearbutton), w.data().gust);
		}
		catch (Exception& e)
		{
			W_MOD(classname << " caught " << e << " @ " << ts << " while reading WindEvent");
		}
	}


  // check the state we are supposed to be in
  switch (getAndCheckState(ts)) {
  case SimulationState::HoldCurrent: {

	if(prev_state != SimulationState::HoldCurrent) {
		// enable buttons
		gtk_widget_set_sensitive(GTK_WIDGET(sendbutton), true);
		gtk_widget_set_sensitive(GTK_WIDGET(reposbutton), true);
		//
		prev_state = SimulationState::HoldCurrent;
	}

    // Check for new INCOSelect events
	while (inco_sel_token.getNumWaitingEvents(ts))
	{
		try
		{
 			EventReader<INCOSelect> inco_sel(inco_sel_token, ts);

 			const char *theFileName = const_cast<char*>(inco_sel.data().name.c_str());

 			// remove the .inco from the file name
			char* theFileNameBase = new char[strlen(theFileName)-5+1];
			strncpy(theFileNameBase, theFileName, strlen(theFileName)-5);
			theFileNameBase[strlen(theFileName)-5] = '\0';

			// select file in dropdown menu
 			gtk_entry_set_text(GTK_ENTRY(GTK_COMBO(combo1)->entry), theFileNameBase);

 			// The following code is based on the code from onSendButtonClicked()
 			// not included is the loading of the wind and turbulence settings from the GUI
 			// as we only want to load the INCO

			// load the corresponding file, also includes setting snap_available=true to send a Trim_inco event
			Snapshot* theSnap = readInco( theFileName );

			// send it out
			if(theSnap) {
				sendInco(theSnap);
			}

			// configure the FMS
			star_token.sendEvent(new STARSelect( theFileNameBase ), SimTime::now());
		}
		catch (Exception& e)
		{
			W_MOD(classname << ": Error while reading INCO Select @ " << ts);
		}
	}

    // send data in case a new inco file is loaded : set via readInco
    if(snap_available) {
      // Channel openen voor extra inco data
      EventWriter<Trim_inco> trim(trim_inco_token, ts);

      trim.data().de_trim    = trim_de;
      trim.data().da_trim    = trim_da;
      trim.data().dr_trim    = trim_dr;
      trim.data().pla1_trim  = trim_pla1;
      trim.data().pla2_trim  = trim_pla2;
      trim.data().gear_trim  = trim_gear;
      trim.data().flaps_trim = trim_flaps;

      snap_available = false;
    }

    break;
  }
  case SimulationState::Replay:
  case SimulationState::Advance: {

	if(prev_state != SimulationState::Advance) {
		// disable buttons
		gtk_widget_set_sensitive(GTK_WIDGET(sendbutton), false);
		gtk_widget_set_sensitive(GTK_WIDGET(reposbutton), false);
		//
		prev_state = SimulationState::Advance;
	}

	// read data for snapshot / inco file creation
	if (snap_trim==true){
		try {
			StreamReaderLatest<CitationPilotInput> cpi(cpi_token);
			//StreamReaderLatest<CitationOutput>in(in_token);
			trim_de    = cpi.data().de ; //
			trim_da    = cpi.data().da; //
			trim_dr    = cpi.data().dr; //
			trim_pla1  = cpi.data().pla1;
			trim_pla2  = cpi.data().pla2;
			trim_gear  = cpi.data().gear;
			trim_flaps = cpi.data().df;
			// Foute redenering herstelt 6 mei.
		            // flaps zitten niet in CPI channel als in solo solo wordt gewerkt
			// trim_flaps=in.data().y[Y_flaps];
			snap_trim=false;
			D_MOD(classname << ": Trim inputs from snap time gathered   NCstates= " <<  NCSTATES << " Vliegtuigtype="<< vliegtuigtype << endl);
		}
		catch (Exception& e)
		{
		  W_MOD( classname << ": Error while reading CitationPilotInput for new trim valuess");
		}
    }

    // output of current location
    try {
		//StreamReader<PrimaryControls> pc(pc_token ,  ts);
		StreamReaderLatest<CitationOutput> in(in_token);

		snprintf(text,11,"%+08.2f",in.data().y[Y_x]);
		//gtk_entry_set_text(GTK_ENTRY(lat_N),text);
		gtk_label_set_text(GTK_LABEL(lat_N),text);
		snprintf(text,11,"%+08.2f",in.data().y[Y_y]);
		//gtk_entry_set_text(GTK_ENTRY(long_E),text);
		gtk_label_set_text(GTK_LABEL(long_E),text);
    }
    catch (Exception& e)
	{
		W_MOD( classname <<  ": Error while reading Citation Output Channel");
	}


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

void CitationIncoSelector::trimCalculation(const TimeSpec& ts, const TrimMode& mode)
{
}

// my functions

// Glade generated function to create the file selector window (copy&paste)
GtkWidget* CitationIncoSelector::create_fileselection1 (void)
{
  GtkWidget *fileselection1;
  GtkWidget *ok_button1;
  GtkWidget *cancel_button1;
  GtkTooltips *tooltips;

  tooltips = gtk_tooltips_new ();

  fileselection1 = gtk_file_selection_new ("Save state as inco file");
  gtk_object_set_data (GTK_OBJECT (fileselection1), "fileselection1", fileselection1);
  gtk_container_set_border_width (GTK_CONTAINER (fileselection1), 10);

  ok_button1 = GTK_FILE_SELECTION (fileselection1)->ok_button;
  gtk_object_set_data (GTK_OBJECT (fileselection1), "ok_button1", ok_button1);
  gtk_widget_show (ok_button1);
  GTK_WIDGET_SET_FLAGS (ok_button1, GTK_CAN_DEFAULT);
  gtk_tooltips_set_tip (tooltips, ok_button1, "Save inco file", NULL);

  cancel_button1 = GTK_FILE_SELECTION (fileselection1)->cancel_button;
  gtk_object_set_data (GTK_OBJECT (fileselection1), "cancel_button1", cancel_button1);
  gtk_widget_show (cancel_button1);
  GTK_WIDGET_SET_FLAGS (cancel_button1, GTK_CAN_DEFAULT);
  gtk_tooltips_set_tip (tooltips, cancel_button1, "Cancel saving", NULL);

  gtk_signal_connect (GTK_OBJECT (ok_button1), "clicked",
                      GTK_SIGNAL_FUNC (CitationIncoSelector_on_ok_button1_clicked),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (cancel_button1), "clicked",
                      GTK_SIGNAL_FUNC (CitationIncoSelector_on_cancel_button1_clicked),
                      NULL);

  gtk_object_set_data (GTK_OBJECT (fileselection1), "tooltips", tooltips);

  return fileselection1;
}


// Read inco file en maak er een snapshot van
Snapshot* CitationIncoSelector::readInco(const char* filename)
{
  // De hele procedure per vliegtuig type apart
  // voor vliegtuig type 2 geen NCSTATES gebruiken
  if (vliegtuigtype==2){
	Snapshot* snap = new Snapshot((17)*sizeof(double), NameSet(getEntity(), "pa_34_model", ""));

	// make an amorphstore object to access the data in the snapshot
	AmorphStore s(snap->accessData(), snap->getDataSize());

	// open the file
	ifstream f;
	f.open(filename);
	if (!f.good()) {
		delete snap;
		E_MOD(classname << ": Bad snapshot file " << filename << " while opening");
		return NULL;
	}

	// read the data from file
	// gobble all comments
	string comment;

	while(f.peek() == '#') {
		getline(f, comment, '\n');
		D_MOD(classname << ": gobbling comment: " << comment);
	}

	// read the states
	int idx;
	double t;

	// DE inco file is 24 lines + 3 comment lines-> groter dan NCSTATES!
	//edit BUT the 3 comment lines are already taken care of above
	// and the whole thing stops when ii is only 19
	//OPTION replace for loop by while f.good() and idx<24
	for (int ii = 0; ii < 24; ii++)
	{
//		if(f.peek() == '#') {
//			// this will give problems ... no new data, resend old data, ii++ increases,
//			getline(f, comment, '\n');
//			D_MOD(classname << ": gobbling comment: " << comment);
//		}
//		else {
			D_MOD(classname << ": peeked " << f.peek());
			f >> idx >> t;
			getline(f, comment, '\n');
//		}

		D_MOD(classname << " (" << ii << ") f=" << f.good() << " PA_Read idx " << idx << " state " << t << " & comment " << comment);

		if (f.bad()) {
			delete snap;
			E_MOD(classname << ": Bad snapshot file " << filename << " while reading");
			return NULL;
		}
		// 17 variabelen naar de state
		if(idx<18){
			packData(s, t);
			D_MOD("data to snapshot");
		}
		else{
			// Hier de inco variabelen vaststellen die niet tot de PA34 state behoren
			// these are send out as Trim_inco
			if (idx==18) trim_de=t;
			if (idx==19) trim_da=t;
			if (idx==20) trim_dr=t;
			if (idx==21) trim_pla1=t;
			if (idx==22) trim_pla2=t;
			if (idx==23) trim_gear=t;
			if (idx==24) trim_flaps=t;
			D_MOD("data to trim");
		}
 	}

	// there is a new snapshot available, so also send out trim event
	snap_available = true;

	// return the snapshot
	return snap;
  }
  else{
	Snapshot* snap = new Snapshot((NCSTATES)*sizeof(double),
				NameSet(getEntity(), "citation-model", ""));
        // make an amorphstore object to access the data in the snapshot
       AmorphStore s(snap->accessData(), snap->getDataSize());

	// open the file
	ifstream f;
	f.open(filename);
	if (!f.good()) {
	delete snap;
	E_MOD( "Bad snapshot file " << filename << " while opening");
	return NULL;
	}

	// read the data from file
	// gobble all comments
	string comment;

	while(f.peek() == '#') {
	getline(f, comment, '\n');
	D_MOD("gobbling comment: " << comment);
	}

	// read the states
	int idx;
	double t;

	// DE inco file is groter dan de number of states
	for (int ii = 0; ii < NCSTATES; ii++) {
	if(f.peek() == '#') {
	getline(f, comment, '\n');
	D_MOD("gobbling comment: " << comment);
	}
	else {
	D_MOD("peeked " << f.peek());
	f >> idx >> t;
	getline(f, comment, '\n');
	}
	D_MOD(" f=" << f.good() << "Cit Read idx " << idx << " state " << t << " & comment " << comment);

	if (f.bad()) {
	delete snap;
	E_MOD( "Bad snapshot file " << filename << " while reading");
	return NULL;
	}
	// Alle variabelen naar de state
	packData(s, t);
	}
  return snap;
  }

}

// Read template for saving inco files
bool CitationIncoSelector::readIncoTemplate(const char* filename)
{
  ifstream f;
  f.open(filename);
  if(!f.good()) {
    W_MOD(classname << " cannot open template for inco files " << filename);
    return false;
  }

  string line;
  while(f.good()) {
    getline(f, line, '\n');
    D_MOD("read template line " << line);
    incotemplate.push_back(line);
  }

  return true;
}

// Process a "Send" button click
void CitationIncoSelector::onSendButtonClicked(GtkButton *button,
					       gpointer user_data)
{
  // get the selected inco
  const char *theFileNameBase;
  char *theFileName;
  theFileNameBase = gtk_entry_get_text(GTK_ENTRY(GTK_COMBO(combo1)->entry));
  theFileName = new char[strlen(theFileNameBase)+6];
  snprintf(theFileName, strlen(theFileNameBase)+6, "%s.inco",theFileNameBase);

  // load the corresponding file
  Snapshot* theSnap = readInco(theFileName);

  // send it out
  if(theSnap) {
    sendInco(theSnap);
  }

  // send the wind and turbulence
  sendWindEvent();

  // configure the FMS
  star_token.sendEvent(new STARSelect(theFileNameBase), SimTime::now());
}

// Process a turbulence enable/disable toggle
void CitationIncoSelector::onCheckButton1Toggled(GtkButton *button,
					       gpointer user_data)
{
  // toggle the intensity spin button
  gtk_widget_set_sensitive(GTK_WIDGET(turbspinner),
			   gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button)));
}

// Proces a wind send button clicked (only for PA34)
void CitationIncoSelector::onWindButtonClicked(GtkButton *button,
						   gpointer user_data)
{
   sendWindEvent();
}

void CitationIncoSelector::sendWindEvent()
{
	EventWriter<WindEvent> w(turb_write_token);

	bool turb = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(turbbutton));

	w.data().id         = 0;
	w.data().turbulence = turb;
	w.data().turb_int   = ( turb ? gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(turbspinner)) : -1.0 );
	w.data().wind_vel   = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(windvelspinner));
	w.data().wind_dir   = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(winddirspinner));
	w.data().gust       = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(shearbutton));

	I_MOD(classname << " sending new wind vector" );
}



// Process a "Take snapshot" button click
void CitationIncoSelector::onSnapshotButtonClicked(GtkButton *button,
						   gpointer user_data)
{

  // Tell the model we want a snapshot
  SnapshotRequest *sr = new SnapshotRequest(true);

  sr_token.sendEvent(sr, SimTime::now());

  snap_trim=true;
   D_MOD(classname << "Snap_trim= " <<  snap_trim << " Vliegtuigtype="<< vliegtuigtype);
  //

 }

// Process a Cancel button click in filewindow
void CitationIncoSelector::onCancelButtonClicked(GtkButton *button,
						 gpointer user_data)
{
  gtk_widget_hide(filewindow);
}

// Process an OK button click in filewindow
// this is the actual saving to the new inco file
void CitationIncoSelector::onOKButtonClicked(GtkButton *button,
					     gpointer user_data)
{
  const gchar* savefilename = gtk_file_selection_get_filename(GTK_FILE_SELECTION(filewindow));

  D_MOD("save filename: " << savefilename);

  if(savefilename[strlen(savefilename)] == '/') {
    // no file selected, just a directory
    W_MOD(classname << " no file name selected: " << savefilename);

    // TODO generate a new (unique!) filename ourselves
  }
  else {
    FILE *outfile;

    // TODO check if given name ends in .inco, else add it

    outfile = fopen(savefilename, "w");

    time_t now = time(NULL);
    if (vliegtuigtype==1){
      fprintf(outfile, "# Citation state inco file, generated on %s", ctime(&now));
    }
    if (vliegtuigtype==2){
      fprintf(outfile, "#  PA-34 state incofile generated on %s", ctime(&now));
    }
    fprintf(outfile, "# Description: saved state from DUECA simulation\n");
    fprintf(outfile, "#\tstate\tvalue\tstate description\n");



    if(!incoming_snap.empty()) {
      list<string>::const_iterator iter;
      list<double>::const_iterator iter2;

//TODO aanpassen aan vliegtuig type
    if (vliegtuigtype==1){
      for(iter = incotemplate.begin(), iter2 = incoming_snap.begin();
	   iter!=incotemplate.end() && iter2!=incoming_snap.end();
	   iter++, iter2++){
	      fprintf(outfile, iter->c_str(), *iter2);
	      fprintf(outfile,"\n");
      }
    }
    if (vliegtuigtype==2){
      for(iter = incotemplate.begin(), iter2 = incoming_snap.begin();
	   iter!=incotemplate.end() && iter2!=incoming_snap.end();
	   iter++, iter2++){
	      fprintf(outfile, iter->c_str(), *iter2);
	      fprintf(outfile,"\n");
      }
      // Nu de extra data toevoegen die niet in de snap zaten
                fprintf(outfile, iter->c_str(), trim_de); fprintf(outfile,"\n");
      iter++  ; fprintf(outfile, iter->c_str(), trim_da); fprintf(outfile,"\n");
      iter++  ; fprintf(outfile, iter->c_str(), trim_dr); fprintf(outfile,"\n");
      iter++  ; fprintf(outfile, iter->c_str(), trim_pla1); fprintf(outfile,"\n");
      iter++  ; fprintf(outfile, iter->c_str(), trim_pla2); fprintf(outfile,"\n");
      iter++  ; fprintf(outfile, iter->c_str(), trim_gear); fprintf(outfile,"\n");
      iter++  ; fprintf(outfile, iter->c_str(), trim_flaps); fprintf(outfile,"\n");
     }

      fclose(outfile);
    }
  }


  // we're done
  gtk_widget_hide(filewindow);
}

// Process a reposition button click
void CitationIncoSelector::onReposButtonClicked(GtkButton *button,
						gpointer user_data)
{
  D_MOD(classname << "Repos");

  Reposition* repos = new Reposition();

  repos->repos_x = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(reposX));
  repos->repos_y = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(reposY));
  repos->repos_h = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(reposZ))*FT2M; //0.3048;
  repos->repos_psi = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(reposPsi))*DEG2RAD; //M_PI/180.0;

  repos_token.sendEvent(repos, SimTime::now());

}

// Send the initial condition snapshot to the model
// NOTE: the Snapshot will be deleted after this!
void CitationIncoSelector::sendInco(Snapshot* snap)
{
  if(getCurrentState() == SimulationState::HoldCurrent) {
    snap_token.sendEvent(snap, SimTime::now());// DUECA deletes snap
  }
  else {
    W_MOD(getId() << " can't send inco when not in HoldCurrent");
  }
}

extern "C" {
  void CitationIncoSelector_on_cancel_button1_clicked(GtkButton *button,
						      gpointer user_data)
  {
    // pass it on to the module
    if(CitationIncoSelector::theOne) {
      CitationIncoSelector::theOne->onCancelButtonClicked(button, user_data);
    }
  }

  void CitationIncoSelector_on_ok_button1_clicked(GtkButton *button,
						      gpointer user_data)
  {
    // pass it on to the module
    if(CitationIncoSelector::theOne) {
      CitationIncoSelector::theOne->onOKButtonClicked(button, user_data);
    }
  }

  // the compare function to filter .inco files out of the directory
  static int is_inco_file(const struct dirent* entry)
  {
    return (strlen(entry->d_name) > 6) &&
      !strcmp(".inco", &(entry->d_name[strlen(entry->d_name) - 5]));
  }

}

// Make a TypeCreator object for this module, the TypeCreator
// will check in with the scheme-interpreting code, and enable the
// creation of modules of this type
static TypeCreator<CitationIncoSelector> a(CitationIncoSelector::getMyParameterTable());
