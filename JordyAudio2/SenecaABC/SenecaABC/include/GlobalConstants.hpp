#ifndef _GLOBALCONSTANTS_H_
#define _GLOBALCONSTANTS_H_

#include <cmath>

const double pi = 3.1415;
const double g  = 9.80665;

const double ft2m = 0.305;
const double m2ft = 1/ft2m;

const double nm2m = 1852.0;
const double n2nm = 1/nm2m;

const double kts2ms = nm2m / 3600.0;
const double ms2kts = 1/kts2ms;

const double deg2rad = pi / 180.0;
const double rad2deg = 1/deg2rad;

const double terrain_clearance  = 1000.0 * ft2m; 

const double terrain_lookahead_range  = 15.0 * nm2m;
const double terrain_scan_range       = 15.0 * nm2m;
const double terrain_angle_scan_range = 15.0 * nm2m;
const double traffic_scan_range       = 30.0 * nm2m;


const double disp_range_miles     =    5.0;
const double disp_range_pix       =  800.0;
const double disp_range_steps     =    5.0;
const double disp_height_feet     = 6000.0;
const double disp_height_pix      =  400.0;
const double disp_height_stepsize = 1000.0;

const double V_stall = 47.0; // m/s ind = 91 kts
const double V_MO = 135.0;   // m/s ind


const double m       = 4500.0; 
const double W       = m * g;  
const double S       = 24.99;
const double e       = 0.85;
const double A       = 6.69;
const double K       = 1.0/(pi*A*e);
const double CD0     = 0.016;
const double beta    = 9296.0;
const double rho_ssl = 1.225;

const double c_T = 0.87;

const double CLCD_max       = 16.7073;
const double CL_at_CLCD_max = 0.5348;

const double velocity_scale = 30.0;

const double caus_height = 100.0;
const double caus_radius = 500.0;

const double pz_height = 1000.0 * ft2m;
const double pz_radius =    5.0 * nm2m;

inline double iasToTas(double vias, double alt)
{
  const double rho      = rho_ssl*exp(-alt/beta);
  const double rho_frac = sqrt(rho_ssl/rho); 

  return vias * rho_frac;
}

inline double tasToIas(double vtas, double alt)
{
  const double rho      = rho_ssl*exp(-alt/beta);
  const double rho_frac = sqrt(rho_ssl/rho); 

  return vtas / rho_frac;
}
#endif /* _GLOBALCONSTANTS_H_ */
