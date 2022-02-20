/* ------------------------------------------------------------------   */
/*      item            : GenericMotionFilter.hxx
        made by         : Olaf Stroosma
        date            : 010608
        category        : header file 
        description     : Interface class for MotionFilters, used by
        					MotionLimiter
        language        : C++
		documentation   :
*/

#ifndef GenericMotionFilter_hxx
#define GenericMotionFilter_hxx

#include "comm-objects.h"
#include <ScriptCreatable.hxx>

USING_DUECA_NS;

class GenericMotionFilter: public ScriptCreatable
{
protected:
  /// Constructor.
  GenericMotionFilter();

  /// Destructor.
  virtual ~GenericMotionFilter();

public:

  /// This is a scheme-level callable class
  SCM_FEATURES_DEF;

public:
  /// This is the main function
  /// OS: output TBD
  virtual void integrate(const VehicleCabMotion&, 
			 const SimulatorMotionState&,
			 SimulatorMotionAcceleration&, 
			 MotionFilterUserData& ) = 0;
	
  /// This is the reset function
  /// OS: behaviour + input TBD
  virtual void reset() = 0;
  
  // This is the time step of the filter
  // called in MotionLimiter::setTimeSpec
  // dt in seconds
  virtual void set_dt(double dt) = 0;

  // This is the fine configuration capability
  // allows for selection of different parameter sets
  virtual bool set_param(int i);
};

#endif





