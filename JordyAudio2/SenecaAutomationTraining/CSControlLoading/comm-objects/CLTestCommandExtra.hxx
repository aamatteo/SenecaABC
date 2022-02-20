/* ------------------------------------------------------------------ */
/*      item            : CLTestCommandExtra.hxx
        made by         : Rene van Paassen (repa)
        date            : Tue 02 Dec 2014
        category        : header file
        description     : DUECA Communication Object (DCO)
                          additional methods and data
        codegen version : 110
        language        : C++
*/

/* Note that this is included *within* the CLTestCommand class. 
   Functions defined here become member functions of that class
   Variables defined here become member variables. */

/** Go to the next timestep/next timestep value */
void step();

/** Return the input vector, first element is commanded acceleration, 
    second is commanded velocity */
#ifdef USING_EIGEN3
const Eigen::Vector2d& du(const Eigen::VectorXd& x, double dt);
#else
const Vector& du(const VectorE& x, double dt);
#endif

/** Reset to the initial point */
void reset(double dt);

/** Give a condensed description of the test */
std::string line();

/** Is the test command complete? */
bool complete();

/** Data, command vector */
#ifdef USING_EIGEN3
Eigen::Vector2d _du;
#else
Vector _du;
#endif

/** File read data */
std::vector<double> fileinput;

/** Index for the file data or movement calculation */
unsigned idx;

/** Start of measurement */
unsigned idx_start;

/** End of measurement */
unsigned idx_end;

/** Duration of a single measurement cycle */
unsigned idx_cycle;

/** Duration of half a sawtooth */
unsigned idx_halftooth;

/** Point after which the test stops */
unsigned idx_still;

/** End of measurement position */
double endpos;

/** Time step size */
double DeltaT;

/** Frequency of the initial and final move */
double w_ini;

/** Frequency of sine input */
double w_sine;

/** Acceleration level in the sawtooth round-off */
double accel_tooth;
