/* ------------------------------------------------------------------   */
/*      item            : FGVisual.cxx
        made by         : repa
	from template   : DuecaModuleTemplate.cxx
        template made by: Rene van Paassen
        date            : Tue Feb  8 16:30:42 2005
	category        : body file
        description     :
	changes         : Tue Feb  8 16:30:42 2005 first version
	template changes: 030401 RvP Added template creation comment
        language        : C++
*/

static const char c_id[] =
"$Id: FGVisual.cxx,v 1.1.1.1 2022/02/17 15:04:23 matteopiras Exp $";

#define FGVisual_cxx
// include the definition of the module class
#include "FGVisual.hxx"

// include the debug writing header, by default, write warning and
// error messages
//#define D_MOD
#define I_MOD
#define W_MOD
#define E_MOD
#include <debug.h>

// include additional files needed for your calculation here
#include <cmath>
#include <sys/types.h>
#include <sys/socket.h>

// the standard package for DUSIME, including template source
#define DO_INSTANTIATE
#include <dusime.h>

static const double rad2deg = 180.0 / M_PI;
static const double deg2rad = M_PI / 180.0;
static const double m2ft = 1.0 / 0.3048;

// class/module name
const char* const FGVisual::classname = "fg-visual";

const static unsigned MSG_MAX = 100;

// Parameters to be inserted
const ParameterTable* FGVisual::getMyParameterTable()
{
  static const ParameterTable parameter_table[] = {
    { "set-timing",
      new MemberCall<FGVisual,TimeSpec>
        (&FGVisual::setTimeSpec), set_timing_description },

    { "check-timing",
      new MemberCall<FGVisual,vector<int> >
      (&FGVisual::checkTiming), check_timing_description },

    { "receiver",
      new VarProbe<FGVisual,string>(&FGVisual::receiver),
      "Ip number of the computer running the flightgear visual" },

    { "own-interface",
      new VarProbe<FGVisual,string>(&FGVisual::own_interface),
      "IP number of the own interface used to send the data packets" },

    { "port",
      new VarProbe<FGVisual,int>(&FGVisual::port),
      "Port number at which the flightgear program is listening" },

    { "lat-zero",
      new VarProbe<FGVisual,double>(REF_MEMBER(&FGVisual::lat_zero)),
      "Latitude of the origin of the simulation [rad]" },

    { "lon-zero",
      new VarProbe<FGVisual,double>(REF_MEMBER(&FGVisual::lon_zero)),
      "Longitude of the origin of the simulation [rad]"},

    { "alt-zero",
      new VarProbe<FGVisual,double>(REF_MEMBER(&FGVisual::h_zero)),
      "Altitude of the origin of the simulation [m]"},

    { "psi-zero",
      new VarProbe<FGVisual,double>(REF_MEMBER(&FGVisual::psi_zero)),
      "Heading of the x-axis of the simulation [rad]" },

    { "z-points-up",
      new VarProbe<FGVisual,bool>(REF_MEMBER(&FGVisual::z_points_up)),
      "True if your z-axis points upward" },

    { "xy-is-latlon",
      new VarProbe<FGVisual,bool>(REF_MEMBER(&FGVisual::VCPxyIsLatLon)),
      "True if VehicleCabPosition x and y contain lat lon values" },

    { "debug",
      new VarProbe<FGVisual,bool>(REF_MEMBER(&FGVisual::debug)),
      "Set to true if you want to spit out debug output" },

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
      "This module communicates aircraft position and orientation to a\n"
      "flightgear (fgfs) simulation, to create an outside visual" } };

  return parameter_table;
}

// constructor
FGVisual::FGVisual(Entity* e, const char* part, const
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
  sockfd(-1),
  receiver(),
  own_interface(),
  port(7000),
  z_gain(1.0),
  lat_zero(0.0),
  lon_zero(0.0),
  h_zero(0.0),
  z_points_up(false),
  psi_zero(0.0),
  debug(false),
  VCPxyIsLatLon(false),
  vcp_token(getId(), NameSet(getEntity(), "VehicleCabPosition", ""), 101),
  fginco_token(getId(), NameSet(getEntity(), "FGIncoEvent", ""), ChannelDistribution::JOIN_MASTER),

  // activity initialization
  cb1(this, &FGVisual::doCalculation),
  do_calc(getId(), "send to flightgear", &cb1, ps)
{
  // do the actions you need for the simulation

  // connect the triggers for simulation
  do_calc.setTrigger(vcp_token);
}

bool FGVisual::complete()
{
  /* All your parameters have been set. You may do extended
     initialisation here. Return false if something is wrong. */

  /* Creation of the sending socket. */
  if (sockfd != -1) {
    close(sockfd);
  }
  sockfd = socket(PF_INET, SOCK_DGRAM, 0);
  if (sockfd == -1) {
    perror("Creating socket");
    return false;
  }

  // source address
  struct sockaddr_in src_address;
  memset(&src_address, 0, sizeof(src_address));
  src_address.sin_family = AF_INET;

  // if an interface was selected, try to set this one
  if (own_interface.size() &&
      inet_aton(own_interface.c_str(), &src_address.sin_addr) == 0) {
    E_MOD(getId() << '/' << classname << " source address invalid");
    return false;

    // and bind to the source address
    if (::bind(sockfd, reinterpret_cast<sockaddr*>(&src_address),
               sizeof(src_address)) != 0) {
      perror("Cannot bind to source");
      return false;
    }
  }

  // destination address
  memset(&dest_address, 0, sizeof(dest_address));
  dest_address.sin_family = AF_INET;

  // destination must have been filled in
  if (!receiver.size() ||
      inet_aton(receiver.c_str(), &dest_address.sin_addr) == 0) {
    E_MOD(getId() << '/' << classname << " invalid receiver address!");
    return false;
  }

  // and port too
  if (!port) {
    E_MOD(getId() << '/' << classname << " invalid port");
    return false;
  }
  dest_address.sin_port = htons(port);


  //////////////////////////////////////////////////////////////////////////////
  // I think I want to copy this to HoldCurrent
  //////////////////////////////////////////////////////////////////////////////
  /* Calculation of scaling factors. */
  const double a = 6378137.0;
  const double f = 1/298.2572;
  const double esqr = f*(2.0 - f);

  /* [OS] I'm suspicious of these...*/
  /*double RM = a*(1.0 + esqr*(1.5*sin(lat_zero)*sin(lat_zero) - 1));
    double RP = a*(1.0 + esqr*0.5*sin(lat_zero)*sin(lat_zero));*/
  /* from Matlab Flat Earth to LLA R2012a docs, using cos(mu_*zero*) */
  double RN = a/sqrt(1.0 - esqr*sin(lat_zero)*sin(lat_zero));
  double RM = RN*(1-esqr)/(1-esqr*sin(lat_zero)*sin(lat_zero));

  /* These give the scale factors for converting x and y positions to
     the lat/long coordinates needed for the simulation. Note that
     this is an approximation only valid around the lat_zero and
     lon_zero points.*/
  x2lat =  atan(1.0/RM) * cos(psi_zero);
  x2lon =  atan(1.0/(RN*cos(lat_zero))) * sin(psi_zero);
  y2lat = -atan(1.0/RM) * sin(psi_zero);
  y2lon =  atan(1.0/(RN*cos(lat_zero))) * cos(psi_zero);

  /* If the z axis points upward instead of downward, a correction is
     needed. */
  if (z_points_up) {
    y2lat = -y2lat;
    y2lon = -y2lon;
    z_gain = -1.0;
  }
  else {
    z_gain = 1.0;
  }
  //////////////////////////////////////////////////////////////////////////////
  // End of copy
  //////////////////////////////////////////////////////////////////////////////
  return true;
}

// destructor
FGVisual::~FGVisual()
{
  //
}

// as an example, the setTimeSpec function
bool FGVisual::setTimeSpec(const TimeSpec& ts)
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
bool FGVisual::checkTiming(const vector<int>& i)
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
bool FGVisual::isPrepared()
{
  // do whatever additional calculations you need to prepare the model.

  // Check that all conditions for running are good.
  // It helps to indicate what the problems are
  bool res = true;

  CHECK_CONDITION(sockfd != -1);
  CHECK_TOKEN(vcp_token);
  CHECK_TOKEN(fginco_token);

  // return result of check
  return res;
}

// start the module
void FGVisual::startModule(const TimeSpec &time)
{
  do_calc.switchOn(time);
}

// stop the module
void FGVisual::stopModule(const TimeSpec &time)
{
  do_calc.switchOff(time);
}

inline double mod_0_2pi(double a)
{
  if (a >= 0) return fmod(a, 2.0*M_PI);
  return fmod(a, 2.0*M_PI) + 2.0*M_PI;
}

inline double mod_pm_pi(double a)
{
  if (a > M_PI) return fmod(a + M_PI, 2.0*M_PI) - M_PI;
  if (a < -M_PI) return fmod(a - M_PI, 2.0*M_PI) + M_PI;
  return a;
}

inline double limit_pm_05pi(double a)
{
  if (a > M_PI_2) return M_PI_2;
  if (a < -M_PI_2) return -M_PI_2;
  return a;
}

// some net stuff
#include "NetCoder.hxx"

// this routine contains the main simulation process of your module. You
// should read the input channels here, and calculate and write the
// appropriate output
void FGVisual::doCalculation(const TimeSpec& ts)
{
  // access the input


  // switch (getAndCheckState(ts)) {
  // case SimulationState::HoldCurrent: {
  //   if(fginco_token.getNumWaitingEvents(ts))
  //   {
  //     try
  //     {
  //       I_MOD("READING NEW FG INPUTS")
  //       EventReader<FGIncoEvent> fginco(fginco_token, ts);
  //       lat_zero = fginco.data().lat_zero;
  //       lon_zero = fginco.data().lon_zero;
  //       h_zero = fginco.data().alt_zero;
  //       psi_zero = fginco.data().psi_zero;
  //
  //     }
  //     catch(Exception& e)
  //     {
  //       W_MOD(classname << " caught " << e << " @ "<<ts<< " (reading AP Inco)");
  //     }
  //   }
  //
  //   const double a = 6378137.0;
  //   const double f = 1/298.2572;
  //   const double esqr = f*(2.0 - f);
  //
  //   /* [OS] I'm suspicious of these...*/
  //   /*double RM = a*(1.0 + esqr*(1.5*sin(lat_zero)*sin(lat_zero) - 1));
  //     double RP = a*(1.0 + esqr*0.5*sin(lat_zero)*sin(lat_zero));*/
  //   /* from Matlab Flat Earth to LLA R2012a docs, using cos(mu_*zero*) */
  //   double RN = a/sqrt(1.0 - esqr*sin(lat_zero)*sin(lat_zero));
  //   double RM = RN*(1-esqr)/(1-esqr*sin(lat_zero)*sin(lat_zero));
  //
  //   /* These give the scale factors for converting x and y positions to
  //      the lat/long coordinates needed for the simulation. Note that
  //      this is an approximation only valid around the lat_zero and
  //      lon_zero points.*/
  //   x2lat =  atan(1.0/RM) * cos(psi_zero);
  //   x2lon =  atan(1.0/(RN*cos(lat_zero))) * sin(psi_zero);
  //   y2lat = -atan(1.0/RM) * sin(psi_zero);
  //   y2lon =  atan(1.0/(RN*cos(lat_zero))) * cos(psi_zero);
  //
  //   /* If the z axis points upward instead of downward, a correction is
  //      needed. */
  //   if (z_points_up) {
  //     y2lat = -y2lat;
  //     y2lon = -y2lon;
  //     z_gain = -1.0;
  //   }
  //   else {
  //     z_gain = 1.0;
  //   }
  //
  //
  //   break;
  //   }
  //
  // case SimulationState::Replay:
  // case SimulationState::Advance: {
  //
  //
  //
  //   break;
  //   }
  //   default:
  //     // other states should never be entered for a SimulationModule,
  //     // HardwareModules on the other hand have more states. Throw an
  //     // exception if we get here,
  //     throw CannotHandleState(getId(),GlobalId(), "state unhandled");
  // }
  if(fginco_token.getNumWaitingEvents(ts))
  {
    try
    {
      I_MOD("READING NEW FG INPUTS")
      EventReader<FGIncoEvent> fginco(fginco_token, ts);
      lat_zero = fginco.data().lat_zero;
      lon_zero = fginco.data().lon_zero;
      h_zero = fginco.data().alt_zero;
      psi_zero = fginco.data().psi_zero;

    }
    catch(Exception& e)
    {
      W_MOD(classname << " caught " << e << " @ "<<ts<< " (reading AP Inco)");
    }
  }

  const double a = 6378137.0;
  const double f = 1/298.2572;
  const double esqr = f*(2.0 - f);

  /* [OS] I'm suspicious of these...*/
  /*double RM = a*(1.0 + esqr*(1.5*sin(lat_zero)*sin(lat_zero) - 1));
    double RP = a*(1.0 + esqr*0.5*sin(lat_zero)*sin(lat_zero));*/
  /* from Matlab Flat Earth to LLA R2012a docs, using cos(mu_*zero*) */
  double RN = a/sqrt(1.0 - esqr*sin(lat_zero)*sin(lat_zero));
  double RM = RN*(1-esqr)/(1-esqr*sin(lat_zero)*sin(lat_zero));

  /* These give the scale factors for converting x and y positions to
     the lat/long coordinates needed for the simulation. Note that
     this is an approximation only valid around the lat_zero and
     lon_zero points.*/
  x2lat =  atan(1.0/RM) * cos(psi_zero);
  x2lon =  atan(1.0/(RN*cos(lat_zero))) * sin(psi_zero);
  y2lat = -atan(1.0/RM) * sin(psi_zero);
  y2lon =  atan(1.0/(RN*cos(lat_zero))) * cos(psi_zero);

  /* If the z axis points upward instead of downward, a correction is
     needed. */
  if (z_points_up) {
    y2lat = -y2lat;
    y2lon = -y2lon;
    z_gain = -1.0;
  }
  else {
    z_gain = 1.0;
  }

  try {
    StreamReader<VehicleCabPosition> vcp(vcp_token, ts);

    // create a buffer for the message
    //char message[MSG_MAX];
    Endian::Encoder msgbuffer( 6*sizeof(double) , Endian::network_order );

    // note: this solution is not valid near the poles!!!!

    D_MOD("LAT (FGVISUAL) = " << rad2deg * limit_pm_05pi(lat_zero + x2lat * vcp.data().x + y2lat * vcp.data().y));
    D_MOD("LON (FGVISUAL) = " << rad2deg * mod_pm_pi(lon_zero + x2lon * vcp.data().x + y2lon * vcp.data().y));

    // write the message
    /*int nbytes = snprintf
      (message, MSG_MAX, "%.10g,%.10g,%.10g,%.8g,%.8g,%.8g\n",
       c.data().lat,
       c.data().lon,
       -c.data().alt*m2ft,
       rad2deg * limit_pm_05pi(c.data().phi),
       rad2deg * limit_pm_05pi(c.data().tht),
       rad2deg * mod_0_2pi(c.data().psi)); */
    if (VCPxyIsLatLon) {
	msgbuffer <<  rad2deg * limit_pm_05pi(vcp.data().x)
		<<  rad2deg * mod_pm_pi(vcp.data().y)
		<<  (-z_gain*vcp.data().z + h_zero)*m2ft
		<<  rad2deg * (vcp.data().phi)
		<<  rad2deg * (vcp.data().theta)
		<<  rad2deg * mod_0_2pi(vcp.data().psi);
     } else {
	msgbuffer <<  rad2deg * limit_pm_05pi(lat_zero + x2lat * vcp.data().x +
						y2lat * vcp.data().y)
		<<  rad2deg * mod_pm_pi(lon_zero + x2lon * vcp.data().x +
					y2lon * vcp.data().y)
		<<  (-z_gain*vcp.data().z + h_zero)*m2ft
		<<  rad2deg * (vcp.data().phi)
		<<  rad2deg * (vcp.data().theta)
		<<  rad2deg * mod_0_2pi(vcp.data().psi);
     }

    // should have enough room
    //assert(nbytes < int(MSG_MAX));

    // if (sendto(sockfd, message, nbytes, 0,
// 	       reinterpret_cast<sockaddr*>(&dest_address),
// 	       sizeof(dest_address)) == -1) {
//       perror("Sending to flightgear");
//     }
//     if (debug) {
//       cout << message;
//     }
    if (sendto(sockfd, msgbuffer.data(), msgbuffer.size(), 0,
	       reinterpret_cast<sockaddr*>(&dest_address),
	       sizeof(dest_address)) == -1) {
      perror("Sending to flightgear");
    }


  }
  catch (NoDataAvailable& e) {
    W_MOD(getId() << '/' << classname << " data lost at " << ts);
  }
}

// Make a TypeCreator object for this module, the TypeCreator
// will check in with the scheme-interpreting code, and enable the
// creation of modules of this type
static TypeCreator<FGVisual> a(FGVisual::getMyParameterTable());
