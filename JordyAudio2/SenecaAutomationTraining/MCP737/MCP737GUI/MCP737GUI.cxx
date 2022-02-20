/* ------------------------------------------------------------------   */
/*      item            : MCP737GUI.cxx
        made by         : stroosma
	from template   : DusimeModuleTemplate.cxx
        template made by: Rene van Paassen
        date            : Fri Jun 25 13:20:17 2004
	category        : body file 
        description     : 
	changes         : Fri Jun 25 13:20:17 2004 first version
	template changes: 030401 RvP Added template creation comment
        language        : C++
*/

static const char c_id[] =
"$Id: MCP737GUI.cxx,v 1.9 2017/03/16 16:10:35 dirkvanbaelen Exp $";

#define MCP737GUI_cxx
// include the definition of the module class
#include "MCP737GUI.hxx"

// include the debug writing header, by default, write warning and 
// error messages
//#define D_MOD
#define I_MOD
#define W_MOD
#define E_MOD
#include <debug.h>

// include additional files needed for your calculation here
#include <Ticker.hxx>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "MCPButton.hxx"
#include "MCPControl.hxx"
#include "MCPNumber.hxx"
#include "MCPSwitch.hxx"
#include "MCPLight.hxx"

// the standard package for DUSIME, including template source
#define DO_INSTANTIATE
#include <dusime.h>

// class/module name
const char* const MCP737GUI::classname = "mcp737-gui";

// initial condition/trim table
const IncoTable* MCP737GUI::getMyIncoTable()
{
  static IncoTable inco_table[] = {
    // always close off with:
    { NULL, NULL} };

  return inco_table;
}

// parameters to be inserted
const ParameterTable* MCP737GUI::getMyParameterTable()
{
  static const ParameterTable parameter_table[] = {
    { "set-timing", 
      new MemberCall<MCP737GUI,TimeSpec>
        (&MCP737GUI::setTimeSpec), set_timing_description },

    { "check-timing", 
      new MemberCall<MCP737GUI,vector<int> >
      (&MCP737GUI::checkTiming), check_timing_description },

    { "join-master",
      new VarProbe<MCP737GUI, bool>
      REF_MEMBER(&MCP737GUI::join_master),
      "act as master for MCP737Events, if no hardware MCP is present"},

    { "set-position",
        new MemberCall< MCP737GUI, vector< int > >
        (&MCP737GUI::setWindowPosition),
        "Supply the position (offset x, offset y) for the window, <0 are ignored" },

    /* You can extend this table with labels and MemberCall or
       VarProbe pointers to perform calls or insert values into your
       class objects. Please also add a description (c-style string).  

       Note that for efficiency, set_timing_description and
       check_timing_description are pointers to pre-defined strings,
       you can simply enter the descriptive strings in the table. */

    /* The table is closed off with NULL pointers for the variable
       name and MemberCall/VarProbe object. The description is used to
       give an overall description of the module. */
    { NULL, NULL, "A GUI to test or replace the MCP737 hardware"} };

  return parameter_table;
}

// constructor
MCP737GUI::MCP737GUI(Entity* e, const char* part, const
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
  //DuecaGLWindow("MCP737", false, DGL_MOUSECLICK), // old API
  DuecaGLWindow("MCP737"),

  // initialize the data you need in your simulation
  texture_id(0),
  join_master(false), // old behavior as default
  m_position_x( 0 ),
  m_position_y( 0 ),

  // initialize the data you need for the trim calculation

  // initialize the channel access tokens
  // example
  // my_token(getId(), NameSet(getEntity(), "MyData", part)),
  in_token(getId(), NameSet(getEntity(), "MCP737Event", getPart())),
  out_token(NULL),

  // activity initialization
  cb1(this, &MCP737GUI::doCalculation),
  do_calc(getId(), "drawing the MCP", &cb1, ps)
{
  // do the actions you need for the simulation

  // connect the triggers for simulation
  do_calc.setTrigger(*Ticker::single());
  
}

bool MCP737GUI::complete()
{
  /* All your parameters have been set. You may do extended
     initialisation here. Return false if something is wrong. */

  if(join_master) {
    out_token = new EventChannelWriteToken<MCP737Event>(getId(), NameSet(getEntity(), "MCP737Event", getPart()), 
							ChannelDistribution::JOIN_MASTER );
  }
  else {
   out_token = new EventChannelWriteToken<MCP737Event>(getId(), NameSet(getEntity(), "MCP737Event", getPart()), 
							ChannelDistribution::NO_OPINION );
  }
    

  // OpenGL window
  setWindow( m_position_x, m_position_y, 1400, 240);// TODO set pixel dimension of texture file here
  openWindow();

  // fill in all the elements
  fillElementsList();

  return true;
}

// destructor
MCP737GUI::~MCP737GUI()
{
  //
  delete out_token;
}

// as an example, the setTimeSpec function
bool MCP737GUI::setTimeSpec(const TimeSpec& ts)
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
bool MCP737GUI::checkTiming(const vector<int>& i)
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
bool MCP737GUI::isPrepared()
{
  // do whatever additional calculations you need to prepare the model. 

  // Check that all conditions for running are good. 
  // It helps to indicate what the problems are
  bool res = true;

  CHECK_TOKEN(in_token);
  CHECK_TOKEN(*out_token);

  // return result of check
  return res;
}

// start the module
void MCP737GUI::startModule(const TimeSpec &time)
{
  do_calc.switchOn(0);
}

// stop the module
void MCP737GUI::stopModule(const TimeSpec &time)
{
  do_calc.switchOff(time);
}

// fill a snapshot with state data. You may remove this method (and the
// declaration) if you specified to the SimulationModule that the size of 
// state snapshots is zero
void MCP737GUI::fillSnapshot(const TimeSpec& ts, 
                              Snapshot& snap, bool from_trim)
{
}

// reload from a snapshot. You may remove this method (and the
// declaration) if you specified to the SimulationModule that the size of 
// state snapshots is zero
void MCP737GUI::loadSnapshot(const TimeSpec& t, const Snapshot& snap)
{

}

// this routine contains the main simulation process of your module. You 
// should read the input channels here, and calculate and write the 
// appropriate output
void MCP737GUI::doCalculation(const TimeSpec& ts)
{
  // check the state we are supposed to be in
  switch (getAndCheckState(ts)) {
  case SimulationState::HoldCurrent:
  case SimulationState::Replay:
  case SimulationState::Advance: {

    if(in_token.getNumWaitingEvents(ts)) {
      EventReader<MCP737Event> r(in_token, ts);

      // handle events destined for us
      if(r.data().receiver & SYS_GUI) {
	D_MOD("MCP737GUI received update: " << r.data());

	// handle event by type
	switch(r.data().msg) {
	  // start hackorama
	  // enable or disable MACH and IAS
	case MCP737Event::MCP_CO_MACH: {
	  ias_ctrl1->enable(false); ias_ctrl2->enable(false); ias_number->enable(false); 
	  mach_ctrl1->enable(true); mach_ctrl2->enable(true); mach_number->enable(true); 
	  out_elements[MCP737Event::MCP_SPD_SET] = mach_number;
	  redraw();
	  break;
	}
	case MCP737Event::MCP_CO_IAS: {
	  mach_ctrl1->enable(false); mach_ctrl2->enable(false); mach_number->enable(false); 
	  ias_ctrl1->enable(true); ias_ctrl2->enable(true); ias_number->enable(true); 
	  out_elements[MCP737Event::MCP_SPD_SET] = ias_number;
	  redraw();
	  break;
	}
	  // switch AT light
	case MCP737Event::MCP_AT_ON: {
	  at_lgt->setValue(1.0);
	  redraw();
	  break;
	}
	case MCP737Event::MCP_AT_OFF: {
	  at_lgt->setValue(0.0);
	  redraw();
	  break;
	}
	case MCP737Event::MCP_AT_BLINK: {
	  at_lgt->setValue(0.5);
	  redraw();
	  break;
	}
	  // enable/disable (vertical) speed indications
	case MCP737Event::MCP_VS_DISP_ON: {
	  vs_number->enable(true);
	  redraw();
	  break;
	}
	case MCP737Event::MCP_VS_DISP_OFF: {
	  vs_number->enable(false);
	  redraw();
	  break;
	}
	case MCP737Event::MCP_SPD_DISP_ON: {
	  if(mach_ctrl1->isEnabled()) mach_number->enable(true);
	  else ias_number->enable(true);
	  redraw();
	  break;
	}
	case MCP737Event::MCP_SPD_DISP_OFF: {
	  mach_number->enable(false);
	  ias_number->enable(false);
	  redraw();
	  break;
	}
	  // end hackorama

	default: {
	  break;
	}
	}

	// update the GUI from the event
	map<MCP737Event::msgType, MCPElement*>::iterator iter = out_elements.find(r.data().msg);
	if(iter == out_elements.end()) {
	  W_MOD("MCP737GUI received an event without associated screen element: " << r.data());
	}
	else {
	  iter->second->setValue(r.data().data);
	  
	  // request a redraw
	  redraw();
	}
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

void MCP737GUI::trimCalculation(const TimeSpec& ts, const TrimMode& mode)
{
}

/** This is called if the size of the window is changed. You might
    need to update the image set-up for a different screen
    format. */
void MCP737GUI::reshape(int x, int y)
{
   glViewport (0, 0, (GLsizei) x, (GLsizei) y);

   glMatrixMode (GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(-1.0 ,1.0, -1.0, 1.0);// fixed coordinate axes

}

/** This is called whenever the display needs to be redrawn. When
    called, the appropriate window has been made current. */
void MCP737GUI::display()
{
  // clear screen
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // viewing matrix
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // texture
  glEnable (GL_TEXTURE_2D);
  glBindTexture (GL_TEXTURE_2D, texture_id);
  
  glColor3f(1.0, 1.0, 1.0);
  glBegin(GL_QUADS);
  glTexCoord2f (0.0f,1.0f); 	// upper left corner of image
  glVertex2f(-1.0, 1.0);
  glTexCoord2f (1.0f,1.0f); 	// upper right corner of image
  glVertex2f( 1.0, 1.0);
  glTexCoord2f (1.0f,0.0f);// lower right corner of image
  glVertex2f(1.0,-1.0);
  glTexCoord2f (0.0f,0.0);// lower left corner of image
  glVertex2f(-1.0,-1.0);
  glEnd();

  glDisable (GL_TEXTURE_2D);

  // all variable elements
  for(list<MCPElement *>::const_iterator iter=in_elements.begin();
      iter != in_elements.end(); iter++) {
    (*iter)->draw();
  }
 

  swapBuffers();
}

/** This is called when the window is ready, for first-time
    set-up. */
void MCP737GUI::initGL()
{
  glClearColor (0.0, 0.0, 0.0, 0.0);

  // load textures
  glGenTextures(1, &texture_id); 
  D_MOD("Loading MCP texture @ ID " << texture_id);

  if(! utils.loadTGA("mcp737.tga", texture_id)) {
    E_MOD("MCP737GUI can't find file mcp737.tga, have you run links.script?");
  }
    

}

/** This is called whenever a mouse button event comes in */
void MCP737GUI::mouse(int button, int state, int x, int y)
{
  // normalize
  float xn = x / (0.5*getWidth()) - 1.0;
  float yn = 1.0 - y / (0.5*getHeight());

  // debug
  if( state == GLUT_DOWN && button == GLUT_LEFT_BUTTON) {
    D_MOD("MCP737GUI left down @ ( " << xn << ", " << yn << " )");
  }
  else if ( state == GLUT_DOWN && button == GLUT_RIGHT_BUTTON) {
    D_MOD("MCP737GUI right down @ ( " << xn << ", " << yn << " )");
  }

  // check all our elements
  if( state == GLUT_DOWN) {
    for(list<MCPElement *>::iterator iter=in_elements.begin();
	iter != in_elements.end(); iter++) {
      // it's a hit
      if( (*iter)->checkClick(xn, yn, button)) {
	redraw();
	continue;// we're done
      }
    }
  }
}

void MCP737GUI::fillElementsList()
{
  // TODO fill all the stuff
  MCPButton *but;
  MCPNumber *num;
  MCPControl *ctl;
  MCPSwitch *sw;
  MCPLight *lgt;

  // backlight switch
  sw = new MCPSwitch(-0.44, -0.32, -0.34, 0.16,
		     out_token,
		     MCP737Event(SYS_GUI, SYS_MCP, MCP737Event::MCP_LIGHT_ON, 1.0),
		     MCP737Event(SYS_GUI, SYS_MCP, MCP737Event::MCP_LIGHT_OFF, -1.0));
  in_elements.push_back(sw);


  // left FD switch
  sw = new MCPSwitch(-0.835, -0.79, -0.775, -0.375,
		     out_token,
		     MCP737Event(SYS_GUI, SYS_SIM, MCP737Event::MCP_FD_L_ON, 0.0),
		     MCP737Event(SYS_GUI, SYS_SIM, MCP737Event::MCP_FD_L_OFF, 0.0));
  sw->loadTextureFile("fdl.tga");
  in_elements.push_back(sw);
  out_elements[MCP737Event::MCP_FD_L_ON] = sw;
  out_elements[MCP737Event::MCP_FD_L_OFF] = sw;

  // right FD switch
  sw = new MCPSwitch(0.775, 0.82, -0.775, -0.39,
		     out_token,
		     MCP737Event(SYS_GUI, SYS_SIM, MCP737Event::MCP_FD_R_ON, 0.0),
		     MCP737Event(SYS_GUI, SYS_SIM, MCP737Event::MCP_FD_R_OFF, 0.0));
  sw->loadTextureFile("fdr.tga");
  in_elements.push_back(sw);
  out_elements[MCP737Event::MCP_FD_R_ON] = sw;
  out_elements[MCP737Event::MCP_FD_R_OFF] = sw;

  // AT switch
  sw = new MCPSwitch(-0.73, -0.67, 0.06, 0.41,
		     out_token,
		     MCP737Event(SYS_GUI, SYS_SIM | SYS_GUI, MCP737Event::MCP_AT_ON, 1.0),
		     MCP737Event(SYS_GUI, SYS_SIM | SYS_GUI, MCP737Event::MCP_AT_OFF, -1.0));
  sw->loadTextureFile("at.tga");
  in_elements.push_back(sw);
  out_elements[MCP737Event::MCP_AT_ON] = sw;
  out_elements[MCP737Event::MCP_AT_OFF] = sw;

  // AP disengage switch
  sw = new MCPSwitch(0.55, 0.63, -0.975, -0.425,
		     out_token,
		     MCP737Event(SYS_GUI, SYS_SIM, MCP737Event::MCP_AP_DISENGAGE_ON, 0.0),
		     MCP737Event(SYS_GUI, SYS_SIM, MCP737Event::MCP_AP_DISENGAGE_OFF, 0.0));
  sw->loadTextureFile("ap.tga");
  in_elements.push_back(sw);
  out_elements[MCP737Event::MCP_AP_DISENGAGE_ON] = sw;
  out_elements[MCP737Event::MCP_AP_DISENGAGE_OFF] = sw;

  // AT light (switching done as hack, maybe need a multimap)
  lgt = new MCPLight(-0.71, -0.68, 0.5, 0.56);
  lgt->setColor(0.0, 1.0, 0.0);
  in_elements.push_back(lgt);
  at_lgt = lgt;
  out_elements[MCP737Event::MCP_AT_BLINK] = lgt;
 
  // N1 button
  but = new MCPButton(-0.77, -0.71,-0.775, -0.6,
		      out_token,
		      MCP737Event(SYS_GUI, SYS_SIM, MCP737Event::MCP_N1_PUSH, 0.0));
  in_elements.push_back(but);
  out_elements[MCP737Event::MCP_N1_ON] = but;
  out_elements[MCP737Event::MCP_N1_OFF] = but;

  // SPEED button
  but = new MCPButton(-0.66, -0.6,-0.775, -0.6,
		      out_token,
		      MCP737Event(SYS_GUI, SYS_SIM, MCP737Event::MCP_SPD_PUSH, 0.0));
  in_elements.push_back(but);
  out_elements[MCP737Event::MCP_SPD_ON] = but;
  out_elements[MCP737Event::MCP_SPD_OFF] = but;

  // C/O button
  but = new MCPButton(-0.62, -0.58,-0.09, 0.16,
		      out_token,
		      MCP737Event(SYS_GUI, SYS_SIM, MCP737Event::MCP_CO_PUSH, 0.0));
  in_elements.push_back(but);

  // LVL CHG button
  but = new MCPButton(-0.4, -0.34,-0.775, -0.6,
		      out_token,
		      MCP737Event(SYS_GUI, SYS_SIM, MCP737Event::MCP_LVL_CHG_PUSH, 0.0));
  in_elements.push_back(but);
  out_elements[MCP737Event::MCP_LVL_CHG_ON] = but;
  out_elements[MCP737Event::MCP_LVL_CHG_OFF] = but;

  // VNAV button
  but = new MCPButton(-0.4, -0.34, 0.34, 0.5,
		      out_token,
		      MCP737Event(SYS_GUI, SYS_SIM, MCP737Event::MCP_VNAV_PUSH, 0.0));
  in_elements.push_back(but);
  out_elements[MCP737Event::MCP_VNAV_ON] = but;
  out_elements[MCP737Event::MCP_VNAV_OFF] = but;
  
  // HDG SEL button
  but = new MCPButton(-0.25, -0.18,-0.775, -0.6,
		      out_token,
		      MCP737Event(SYS_GUI, SYS_SIM, MCP737Event::MCP_HDG_PUSH, 0.0));
  in_elements.push_back(but);
  out_elements[MCP737Event::MCP_HDG_ON] = but;
  out_elements[MCP737Event::MCP_HDG_OFF] = but;

  // LNAV button
  but = new MCPButton(-0.1, -0.04, 0.34, 0.5,
		      out_token,
		      MCP737Event(SYS_GUI, SYS_SIM, MCP737Event::MCP_LNAV_PUSH, 0.0));
  in_elements.push_back(but);
  out_elements[MCP737Event::MCP_LNAV_ON] = but;
  out_elements[MCP737Event::MCP_LNAV_OFF] = but;
  
  // VOR LOC button
  but = new MCPButton(-0.1, -0.04, -0.2, 0.0,
		      out_token,
		      MCP737Event(SYS_GUI, SYS_SIM, MCP737Event::MCP_VOR_LOC_PUSH, 0.0));
  in_elements.push_back(but);
  out_elements[MCP737Event::MCP_VOR_LOC_ON] = but;
  out_elements[MCP737Event::MCP_VOR_LOC_OFF] = but;

  
  // APP button
  but = new MCPButton(-0.1, -0.04, -0.8, -0.63,
		      out_token,
		      MCP737Event(SYS_GUI, SYS_SIM, MCP737Event::MCP_APP_PUSH, 0.0));
  in_elements.push_back(but);
  out_elements[MCP737Event::MCP_APP_ON] = but;
  out_elements[MCP737Event::MCP_APP_OFF] = but;
  
  // ALT HLD button
  but = new MCPButton(0.05, 0.12, -0.8, -0.61,
		      out_token,
		      MCP737Event(SYS_GUI, SYS_SIM, MCP737Event::MCP_ALT_PUSH, 0.0));
  in_elements.push_back(but);
  out_elements[MCP737Event::MCP_ALT_ON] = but;
  out_elements[MCP737Event::MCP_ALT_OFF] = but;
  
  // V/S button
  but = new MCPButton(0.16, 0.23, -0.8, -0.61,
		      out_token,
		      MCP737Event(SYS_GUI, SYS_SIM, MCP737Event::MCP_VS_PUSH, 0.0));
  in_elements.push_back(but);
  out_elements[MCP737Event::MCP_VS_ON] = but;
  out_elements[MCP737Event::MCP_VS_OFF] = but;
  
  // CMD A button
  but = new MCPButton(0.46, 0.52, 0.34, 0.51,
		      out_token,
		      MCP737Event(SYS_GUI, SYS_SIM, MCP737Event::MCP_CMD_A_PUSH, 0.0));
  in_elements.push_back(but);
  out_elements[MCP737Event::MCP_CMD_A_ON] = but;
  out_elements[MCP737Event::MCP_CMD_A_OFF] = but;
  
  // CMD B button
  but = new MCPButton(0.64, 0.71, 0.34, 0.51,
		      out_token,
		      MCP737Event(SYS_GUI, SYS_SIM, MCP737Event::MCP_CMD_B_PUSH, 0.0));
  in_elements.push_back(but);
  out_elements[MCP737Event::MCP_CMD_B_ON] = but;
  out_elements[MCP737Event::MCP_CMD_B_OFF] = but;
  
  // CWS A button
  but = new MCPButton(0.46, 0.52, -0.17, 0.02,
		      out_token,
		      MCP737Event(SYS_GUI, SYS_SIM, MCP737Event::MCP_CWS_A_PUSH, 0.0));
  in_elements.push_back(but);
  out_elements[MCP737Event::MCP_CWS_A_ON] = but;
  out_elements[MCP737Event::MCP_CWS_A_OFF] = but;
  
   // CWS B button
  but = new MCPButton(0.64, 0.71, -0.17, 0.02,
		      out_token,
		      MCP737Event(SYS_GUI, SYS_SIM, MCP737Event::MCP_CWS_B_PUSH, 0.0));
  in_elements.push_back(but);
  out_elements[MCP737Event::MCP_CWS_B_ON] = but;
  out_elements[MCP737Event::MCP_CWS_B_OFF] = but;
  
  // IAS / MACH indication
  num = new MCPNumber(-0.55, 0.400, 0,"%03.0f");
  ias_number = num;
		      
  in_elements.push_back(num);
  out_elements[MCP737Event::MCP_SPD_SET] = num;

  // IAS / MACH on/off (invisible, no texture)
  sw = new MCPSwitch(-0.57, -0.47, 0.725, 0.83,
		     out_token,
		     MCP737Event(SYS_GUI, SYS_MCP | SYS_SIM | SYS_GUI, MCP737Event::MCP_SPD_DISP_ON, 1.0),
		     MCP737Event(SYS_GUI, SYS_MCP | SYS_SIM | SYS_GUI, MCP737Event::MCP_SPD_DISP_OFF, -1.0));
  sw->setValue(true);
  in_elements.push_back(sw);
 
  // IAS controls
  float dummy_gain = 1.0;
  ctl = new MCPControl(-0.55,-0.52,-0.425,0.0, -1.0*dummy_gain, -10.0*dummy_gain, 0.0, out_token, 
		       MCP737Event(SYS_GUI, SYS_SIM | SYS_MCP, MCP737Event::MCP_SPD_SET, 0.0), num);
  in_elements.push_back(ctl);
  ias_ctrl1 = ctl;

  ctl = new MCPControl(-0.52,-0.47,-0.425,0.0, 1.0*dummy_gain, 10.0*dummy_gain, 0.0, out_token, 
		       MCP737Event(SYS_GUI, SYS_SIM | SYS_MCP, MCP737Event::MCP_SPD_SET, 0.0), num);
  in_elements.push_back(ctl);
  ias_ctrl2 = ctl;

  // MACH indication
  num = new MCPNumber(-0.52, 0.400, 0.0,"%0.2f");
  mach_number = num;
  num->setNumDigits(2);
  num->enable(false);

  in_elements.push_back(num);
  //out_elements[MCP737Event::MCP_SPD_SET] = num;

  // MACH controls
  ctl = new MCPControl(-0.55,-0.52, -0.425,0.0,-0.01, -0.10, 0.0, out_token, 
		       MCP737Event(SYS_GUI, SYS_SIM | SYS_MCP, MCP737Event::MCP_SPD_SET, 0.0), num);
  in_elements.push_back(ctl);
  mach_ctrl1 = ctl;
  ctl->enable(false);

  ctl = new MCPControl(-0.52,-0.47, -0.425, 0.0, 0.01, 0.10, 0.0, out_token, 
		       MCP737Event(SYS_GUI, SYS_SIM | SYS_MCP, MCP737Event::MCP_SPD_SET, 0.0), num);
  in_elements.push_back(ctl);
  mach_ctrl2 = ctl;
  ctl->enable(false);

  // MACH decimal point
  lgt = new MCPLight(-0.533, -0.529, 0.383, 0.408);
  lgt->setColor(1.0, 0.0, 0.0);
  in_elements.push_back(lgt);
  out_elements[MCP737Event::MCP_CO_IAS] = lgt;
  out_elements[MCP737Event::MCP_CO_MACH] = lgt;
 

  // COURSE1 indication
  num = new MCPNumber(-0.92, 0.4, 0,"%03.0f");
		      
  in_elements.push_back(num);
  out_elements[MCP737Event::MCP_COURSE1_SET] = num;

  // COURSE1 controls
  ctl = new MCPControl(-0.96,-0.92,-0.275,0.22, -1.0, -10.0, 0.0, out_token, 
		       MCP737Event(SYS_GUI, SYS_SIM | SYS_MCP, MCP737Event::MCP_COURSE1_SET, 0.0), num, true);
  in_elements.push_back(ctl);
  
  ctl = new MCPControl(-0.92,-0.87,-0.275,0.22, 1.0, 10.0, 0.0, out_token, 
		       MCP737Event(SYS_GUI, SYS_SIM | SYS_MCP, MCP737Event::MCP_COURSE1_SET, 0.0), num, true);
  in_elements.push_back(ctl);

  // HEADING indication
  num = new MCPNumber(-0.26, 0.4, 0,"%03.0f");
		      
  in_elements.push_back(num);
  out_elements[MCP737Event::MCP_HDG_SET] = num;

  // HEADING controls
  ctl = new MCPControl(-0.26,-0.22,-0.23,0.18, -1.0, -10.0, 0.0, out_token, 
		       MCP737Event(SYS_GUI, SYS_SIM | SYS_MCP, MCP737Event::MCP_HDG_SET, 0.0), num, true);
  in_elements.push_back(ctl);
  
  ctl = new MCPControl(-0.22,-0.18,-0.23,0.18, 1.0, 10.0, 0.0, out_token, 
		       MCP737Event(SYS_GUI, SYS_SIM | SYS_MCP, MCP737Event::MCP_HDG_SET, 0.0), num, true);
  in_elements.push_back(ctl);
  
  // ALT indication
  num = new MCPNumber(0.02, 0.4, 0,"%03.0f");
  num->setNumDigits(5);
		      
  in_elements.push_back(num);
  out_elements[MCP737Event::MCP_ALT_SET] = num;

  // ALT controls
  ctl = new MCPControl(0.03, 0.08, -0.275, 0.275, -100.0, -1000.0, 0.0, out_token, 
		       MCP737Event(SYS_GUI, SYS_SIM | SYS_MCP, MCP737Event::MCP_ALT_SET, 0.0), num);
  in_elements.push_back(ctl);
  
  ctl = new MCPControl(0.08, 0.13, -0.275, 0.275, 100.0, 1000.0, 0.0, out_token, 
		       MCP737Event(SYS_GUI, SYS_SIM | SYS_MCP, MCP737Event::MCP_ALT_SET, 0.0), num);
  in_elements.push_back(ctl);

  // V/S indication
  num = new MCPNumber(0.22, 0.4, 0,"%03.0f");
  num->setNumDigits(4);
  num->allowMinus(true);
  num->enable(false);
  vs_number = num;
		      
  in_elements.push_back(num);
  out_elements[MCP737Event::MCP_VS_SET] = num;

  // V/S on/off (invisible, no texture)
  sw = new MCPSwitch(0.24, 0.37, 0.75, 0.88,
		     out_token,
		     MCP737Event(SYS_GUI, SYS_MCP | SYS_GUI | SYS_SIM, MCP737Event::MCP_VS_DISP_ON, 1.0),
		     MCP737Event(SYS_GUI, SYS_MCP | SYS_GUI | SYS_SIM, MCP737Event::MCP_VS_DISP_OFF, -1.0));
  sw->setValue(-1.0);
  in_elements.push_back(sw);
  out_elements[MCP737Event::MCP_VS_DISP_ON] = sw;
  out_elements[MCP737Event::MCP_VS_DISP_OFF] = sw;

  // ALT controls
  ctl = new MCPControl(0.32, 0.36, -0.725, -0.275, 50.0, 100.0, 0.0, out_token, 
		       MCP737Event(SYS_GUI, SYS_SIM | SYS_MCP, MCP737Event::MCP_VS_SET, 0.0), num);
  in_elements.push_back(ctl);
  
  ctl = new MCPControl(0.32, 0.36, -0.275, 0.15, -50.0, -100.0, 0.0, out_token, 
		       MCP737Event(SYS_GUI, SYS_SIM | SYS_MCP, MCP737Event::MCP_VS_SET, 0.0), num);
  in_elements.push_back(ctl);
  
  // COURSE2 indication
  num = new MCPNumber(0.81, 0.4, 0,"%03.0f");
		      
  in_elements.push_back(num);
  out_elements[MCP737Event::MCP_COURSE2_SET] = num;

  // COURSE2 controls
  ctl = new MCPControl(0.84, 0.91, -0.3, 0.2, -1.0, -10.0, 0.0, out_token, 
		       MCP737Event(SYS_GUI, SYS_SIM | SYS_MCP, MCP737Event::MCP_COURSE2_SET, 0.0), num, true);
  in_elements.push_back(ctl);
  
  ctl = new MCPControl(0.91,0.95,-0.3,0.2, 1.0, 10.0, 0.0, out_token, 
		       MCP737Event(SYS_GUI, SYS_SIM | SYS_MCP, MCP737Event::MCP_COURSE2_SET, 0.0), num, true);
  in_elements.push_back(ctl);

}


// Make a TypeCreator object for this module, the TypeCreator
// will check in with the scheme-interpreting code, and enable the
// creation of modules of this type
static TypeCreator<MCP737GUI> a(MCP737GUI::getMyParameterTable());

// Interface to the position the window
bool MCP737GUI::setWindowPosition( const vector< int >& p_vector )
{
  bool succes = true;

  // Check for the size
  if ( p_vector.size() == 2 )
  {
    // Check the x shift for the limit
    int x_shift = p_vector[ 0 ];
    if ( x_shift >= 0 )
    {
      m_position_x = x_shift;
    }
    else
    {
      W_MOD( getId() << "/" << classname << "::setWindowPosition: You supplied a negative number for the x position (" << x_shift << ") this is ignored." );
    }

    // Check the y shift for the limit
    int y_shift = p_vector[ 1 ];
    if ( y_shift >= 0 )
    {
      m_position_y = y_shift;
    }
    else
    {
      W_MOD( getId() << "/" << classname << "::setWindowPosition: You supplied a negative number for the y position (" << y_shift << ") this is ignored." );
    }
  }
  else
  {
    E_MOD( getId() << "/" << classname << "::setWindowPosition: an incorrect number of elements are supplied, no 2 but " << p_vector.size() );
    succes = false;
  }

  return succes;
}
