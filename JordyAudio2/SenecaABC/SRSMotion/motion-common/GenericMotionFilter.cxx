/* ------------------------------------------------------------------   */
/*      item            : GenericMotionFilter.cxx
        made by         : Olaf Stroosma
        date            : 010608
        category        : header file 
        description     : Interface class for MotionFilters, used by
        					MotionLimiter
        language        : C++
		documentation   :
*/

#include "GenericMotionFilter.hxx"

#define DO_INSTANTIATE
#include <CoreCreator.hxx>
#define INCLUDE_TEMPLATE_SOURCE

GenericMotionFilter::GenericMotionFilter()
{
  // nothing for now
}

GenericMotionFilter::~GenericMotionFilter()
{
  // nothing for now
}

bool GenericMotionFilter::set_param(int i)
{
  // apparently someone didn't implement parameter setting
  // we shouldn't be called in that case
  // use -1 for param variable (Default) in MotionConfiguration event
  return false;
}

static const char* message = 
"You cannot use this generic motion filter as a main motion filter!";

// scheme connectivity. This class may serve as a common and
// referrable base class, but may not be created from scheme
SCM_FEATURES_NOIMPINH(GenericMotionFilter, ScriptCreatable, "generic-motion-filter");


