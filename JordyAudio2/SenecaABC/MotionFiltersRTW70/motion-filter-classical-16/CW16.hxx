/* ------------------------------------------------------------------   */
/*      item            : CW12.hxx
        made by         : Olaf Stroosma
        date            : 260712
        category        : header file
        description     : ClassicalWashout filter (RTW 7.0 R2007b)
        language        : C++
	documentation   :
*/

#ifndef CW16_hh
#define CW16_hh

// include headers for functions/classes you need in the module
#include "GenericMotionFilter.hxx"
#include <SchemeData.hxx>
#include <ParameterTable.hxx>
#include <StateGuard.hxx>
#include "comm-objects.h"
#include <map>

#include "cw16_types.h"
#define cw16_rtModel                   rtModel_cw16

class CW16: public GenericMotionFilter
{
public:
  SCM_FEATURES_DEF;

private:
  /** Simulink generated model. */
  cw16_rtModel *S;

  /** Map with parameter sets in Simulink format, with ID. */
  map<int, struct Parameters_cw16*> par_sets;

  /** The current parameter struct. */
  Parameters_cw16* cur_par;

  /** flag if user has explicitly selected a default parameter set, otherwise use first one. */
  bool par_set_selected;

  /** guard against concurrent access to our state. */
  dueca::StateGuard sg;

public:
  /** Constructor. */
  CW16();

  /** Destructor */
  ~CW16();

  /** complete call. */
  bool complete();

  // Virtual functions from GenericMotionFilter
  /** Do a single integration step. */
  void integrate(const VehicleCabMotion&, const SimulatorMotionState&,
		 SimulatorMotionAcceleration&, MotionFilterUserData& );

  /** Reset the filter, re-initialise. */
  void reset();

  /** Specify the time step, ignored. */
  void set_dt(double);

  /** Select parameter set. */
  bool set_param(int);

  // Parameter table functions
  bool addParameterSet(const ScriptCreatable& ps);
  bool selectParameterSet(const int& i);

  /** Add parameters in comm object form. */
  bool addParameterSet(const Cw16ParameterSet&);

  /** run-time configuration */
  static const dueca::ParameterTable* getParameterTable();

private:
  /** Create and initialise a model. */
  cw16_rtModel *createAndInitialiseModel(Parameters_cw16 *p = NULL);

  /** Destroy it again. */
  void destroyModel(cw16_rtModel *S);

  /** Get newly allocated Simulink parameter struct, from ParameterSet. */
  struct Parameters_cw16* getNewParameters(const Cw16ParameterSet&);
};



#endif
