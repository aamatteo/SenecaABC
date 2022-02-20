/* ------------------------------------------------------------------   */
/*      item            : FGVisual.hxx
        made by         : repa
	from template   : DuecaModuleTemplate.hxx
        template made by: Rene van Paassen
        date            : Tue Feb  8 16:30:42 2005
	category        : header file
        description     :
	changes         : Tue Feb  8 16:30:42 2005 first version
	template changes: 030401 RvP Added template creation comment
        language        : C++
*/

#ifndef FGVisual_hxx
#define FGVisual_hxx

#ifdef FGVisual_cxx
static const char h_id[] =
"$Id: FGVisual.hxx,v 1.1 2020/07/16 12:30:08 jkvanleeuwen Exp $";
#endif

// include the dusime header
#include <dueca.h>
#include <dusime.h>
using namespace dueca;

// This includes headers for the objects that are sent over the channels
#include "comm-objects.h"

// include headers for functions/classes you need in the module
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/** This module forms a proxy to flightgear, for the purpose of using
    flightgear as an image generator. [OS]: take the following with a grain
    of salt, probably outdated.

    Flightgear must be started up with an option to use the
    outsidevisual.xml communication specification file. Check that
    outsidevisual.xml is included in the FlightGear/Protocols directory. As
    an example:
    \verbatim
    fgfs --generic=socket,dir,hz,machine,port,style,outsidevisual --fdm=external
    \endverbatim
    The variables are:
    <ul>
    <li> dir: direction of io, must be 'in'
    <li> hz: rate of input
    <li> machine: ip address or machine name
    <li> port: port to be used
    <li> style: must be 'udp' for this communication
    <li> outsidevisual: the specified protocol
    </ul>

    Flightgear includes facilities to adjust the eye position of the
    observer. Your best option would be to not do this adjustment in
    your simulation code, but send the aircraft cg position over to
    flightgear and use flightgear's facilities to adjust for eye
    position. You can add a --config option to the fgfs startup line
    to adjust this:
    \verbatim
    fgfs --config=eyeheight.xml \
      --generic=socket,dir,hz,machine,port,style,outsidevisual
    \endverbatim

    You can add a --fov=?? flag to match the field of view to the fov
    of your set-up

    With the xml file looking like:
    \verbatim
<?xml version="1.0"?>
<PropertyList>
 <sim>

  <description>simple outside visual</description>
  <author>Rene van Paassen</author>
  <status>early-production</status>

  <flight-model>external</flight-model>

  <panel>
    <path>Aircraft/737/Panels/737-ifr-panel.xml</path>
    <visibility>false</visibility>
  </panel>

  <view>
   <internal archive="y">false</internal>
   <config>
     <!-- x/y/z == right/up/back -->
     <x-offset-m archive="y">0</x-offset-m>
     <y-offset-m archive="y">0</y-offset-m>
     <z-offset-m archive="y">0</z-offset-m>
     <pitch-offset-deg archive="y">-0.0</pitch-offset-deg>
   </config>
  </view>
  <view n="1">
   <config>
     <!-- big plane, so extend chase view offset a bit -->
     <z-offset-m type="double" archive="y">-80.0</z-offset-m>
   </config>
  </view>

  <chase-distance-m>-30</chase-distance-m>

 </sim>

</PropertyList>
    \endverbatim

    The instructions to create a module of this class from the Scheme
    script are:

    \verbinclude fg-visual.scm
 */
class FGVisual: public Module
{
private: // simulation data
  /** Socket for communication to flightgear. */
  int sockfd;

  /** Ip or host address for the data. */
  std::string receiver;

  /** Ip number of my own interface, used to select sending over only
      one interface. */
  std::string own_interface;

  /** Port number for the data packets. */
  int port;

  /** Destination for the packets. */
  struct sockaddr_in dest_address;

  /** Gain for if the z-axis points down. */
  double z_gain;

  /** Latitude of the visual at position (0, 0). */
  double lat_zero;

  /** Longitude of the visual at position (0, 0). */
  double lon_zero;

  /** Altitude offset of the visual at pos (0, 0) */
  double h_zero;

  /** Flag to indicate whether the z-axis is pointing up or,
      otherwise, down. */
  bool z_points_up;

  /** Heading of the x-axis. This assumes that the model uses a
      right-handed axis system, with the z-axis either pointing up or
      down. */
  double psi_zero;

  /** Scaling factors from x, y to lat, lon. */
  double x2lat, x2lon, y2lat, y2lon;

  /** Flag that determines debug output. */
  bool debug;

  /** Flag to indicate that VCP x, y is actually filled with lat/lon */
  bool VCPxyIsLatLon;

private: // channel access
  /** Standardized channel for receiving position data. */
  StreamChannelReadToken<VehicleCabPosition> vcp_token;
  EventChannelReadToken<FGIncoEvent> fginco_token;

private: // activity allocation
  /** Callback object for simulation calculation. */
  Callback<FGVisual>  cb1;

  /** Activity for simulation calculation. */
  ActivityCallback      do_calc;

public: // class name and trim/parameter tables
  /** Name of the module. */
  static const char* const           classname;

  /** Return the parameter table. */
  static const ParameterTable*       getMyParameterTable();

public: // construction and further specification
  /** Constructor. Is normally called from scheme/the creation script. */
  FGVisual(Entity* e, const char* part, const PrioritySpec& ts);

  /** Continued construction. This is called after all script
      parameters have been read and filled in, according to the
      parameter table. Your running environment, e.g. for OpenGL
      drawing, is also prepared. Any lengty initialisations (like
      reading the 4 GB of wind tables) should be done here.
      Return false if something in the parameters is wrong (by
      the way, it would help if you printed what!) May be deleted. */
  bool complete();

  /** Destructor. */
  ~FGVisual();

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
};

#endif
