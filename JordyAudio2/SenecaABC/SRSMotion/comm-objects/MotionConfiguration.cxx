/* ------------------------------------------------------------------ */
/*      item            : MotionConfiguration.cxx
        generated by    : matteo (matteo)
        date            : Thu 24 Mar 2022
        category        : body file
        description     : DUECA Communication Object (DCO),
                          automatically generated by dueca-codegen
        codegen version : 110
        language        : C++
*/

#include "MotionConfiguration.hxx"
#include <iostream>
#include <cassert>
#if !defined(__DCO_NOPACK)
#include <AmorphStore.hxx>
#include <PackUnpackTemplates.hxx>
#endif
#include <DataWriterArraySize.hxx>
#define DOBS(A)
#if !defined(__DCO_STANDALONE)
#include <Arena.hxx>
#include <ArenaPool.hxx>
#include <DataClassRegistrar.hxx>
#include <CommObjectMemberAccess.hxx>
#include <DCOFunctor.hxx>
#include <DCOMetaFunctor.hxx>

#define DO_INSTANTIATE
#include <DataSetSubsidiary.hxx>
#endif




#if !defined(__DCO_STANDALONE)
// static CommObjectMemberAccess objects, that can provide flexible access
// to the members of a MotionConfiguration object
static ::dueca::CommObjectMemberAccess
  <MotionConfiguration,MotionConfiguration::evt_type >
  MotionConfiguration_member_event_type(&MotionConfiguration::event_type, "event_type");
static ::dueca::CommObjectMemberAccess
  <MotionConfiguration,bool >
  MotionConfiguration_member_motion(&MotionConfiguration::motion, "motion");
static ::dueca::CommObjectMemberAccess
  <MotionConfiguration,int >
  MotionConfiguration_member_filter(&MotionConfiguration::filter, "filter");
static ::dueca::CommObjectMemberAccess
  <MotionConfiguration,int >
  MotionConfiguration_member_param(&MotionConfiguration::param, "param");
static ::dueca::CommObjectMemberAccess
  <MotionConfiguration,bool >
  MotionConfiguration_member_filter_confirmed(&MotionConfiguration::filter_confirmed, "filter_confirmed");
static ::dueca::CommObjectMemberAccess
  <MotionConfiguration,bool >
  MotionConfiguration_member_param_confirmed(&MotionConfiguration::param_confirmed, "param_confirmed");

// assemble the above entries into a table in the order in which they
// appear in the MotionConfiguration object
static const ::dueca::CommObjectDataTable entriestable[] = {
  { &MotionConfiguration_member_event_type },
  { &MotionConfiguration_member_motion },
  { &MotionConfiguration_member_filter },
  { &MotionConfiguration_member_param },
  { &MotionConfiguration_member_filter_confirmed },
  { &MotionConfiguration_member_param_confirmed },
  { NULL }
};

#endif

// class name, static
const char * const MotionConfiguration::classname = "MotionConfiguration";

// magic number, hashed from class name and member names / classes
const uint32_t MotionConfiguration::magic_check_number=0x48e99948;

#if !defined(__DCO_STANDALONE)
// functor table, provides access to user-defined metafunctions through the
// data class registry
static dueca::functortable_type functortable;

// register this class, provides access to a packing/unpacking object,
// and to the member access tables
static ::dueca::DataClassRegistrar registrar
  (MotionConfiguration::classname, NULL,
   entriestable, &functortable,
   new ::dueca::DataSetSubsidiary<MotionConfiguration>());

#endif

#ifndef __CUSTOM_DEFAULT_CONSTRUCTOR
MotionConfiguration::MotionConfiguration():
    event_type(Request),
    param(-1),
    filter_confirmed(false),
    param_confirmed(false)
{
  DOBS("default constructor MotionConfiguration");
}
#endif

#ifndef __CUSTOM_FULL_CONSTRUCTOR
MotionConfiguration::MotionConfiguration(
        const evt_type& event_type,
        const bool& motion,
        const int& filter,
        const int& param,
        const bool& filter_confirmed,
        const bool& param_confirmed) :
    event_type(event_type),
    motion(motion),
    filter(filter),
    param(param),
    filter_confirmed(filter_confirmed),
    param_confirmed(param_confirmed)
{
  DOBS("complete constructor MotionConfiguration");
}
#endif

#ifndef __CUSTOM_FULLSINGLES_CONSTRUCTOR
#endif

#ifndef __CUSTOM_COPY_CONSTRUCTOR
MotionConfiguration::MotionConfiguration(const MotionConfiguration& other):
    event_type(other.event_type),
    motion(other.motion),
    filter(other.filter),
    param(other.param),
    filter_confirmed(other.filter_confirmed),
    param_confirmed(other.param_confirmed)
{
  DOBS("copy constructor MotionConfiguration");
}
#endif

#if !defined(__CUSTOM_AMORPHRESTORE_CONSTRUCTOR) && !defined(__DCO_NOPACK)
MotionConfiguration::MotionConfiguration(dueca::AmorphReStore& s):
        event_type(evt_type(uint8_t(s))),
        motion(s),
        filter(s),
        param(s),
        filter_confirmed(s),
        param_confirmed(s)
{
  DOBS("amorph constructor MotionConfiguration");
}
#endif

#if !defined(__CUSTOM_ARRAY_SIZE_INIT_CONSTRUCTOR)
#endif

#ifndef __CUSTOM_DESTRUCTOR
MotionConfiguration::~MotionConfiguration()
{
  DOBS("destructor MotionConfiguration");
}
#endif

#if !defined(__DCO_STANDALONE)
void* MotionConfiguration::operator new(size_t size)
{
  DOBS("operator new MotionConfiguration");
  static ::dueca::Arena* my_arena = arena_pool.findArena
    (sizeof(MotionConfiguration));
  return my_arena->alloc(size);
}

void MotionConfiguration::operator delete(void* v)
{
  DOBS("operator delete MotionConfiguration");
  static ::dueca::Arena* my_arena = arena_pool.findArena
    (sizeof(MotionConfiguration));
  my_arena->free(v);
}
#endif

#if !defined(__CUSTOM_FUNCTION_PACKDATADIFF) && !defined(__DCO_NOPACK)
void MotionConfiguration::packDataDiff(::dueca::AmorphStore& s, const MotionConfiguration& ref) const
{
  DOBS("packDataDiff MotionConfiguration");
  ::dueca::IndexMemory im;
  ::dueca::checkandpackdiffsingle(this->event_type, ref.event_type,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->motion, ref.motion,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->filter, ref.filter,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->param, ref.param,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->filter_confirmed, ref.filter_confirmed,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->param_confirmed, ref.param_confirmed,
                         s, im);
  im.closeoff(s);
}
#endif

#if !defined(__CUSTOM_FUNCTION_UNPACKDATA) && !defined(__DCO_NOPACK)
void MotionConfiguration::unPackData(::dueca::AmorphReStore& s)
{
  DOBS("unPackData MotionConfiguration");

  ::unPackData(s, this->event_type);
  ::unPackData(s, this->motion);
  ::unPackData(s, this->filter);
  ::unPackData(s, this->param);
  ::unPackData(s, this->filter_confirmed);
  ::unPackData(s, this->param_confirmed);

}
#endif

#if !defined(__CUSTOM_FUNCTION_UNPACKDATADIFF) && !defined(__DCO_NOPACK)
void MotionConfiguration::unPackDataDiff(dueca::AmorphReStore& s)
{
  DOBS("unPackDataDiff MotionConfiguration");
  ::dueca::IndexRecall im;
  ::dueca::checkandunpackdiffsingle(this->event_type, s, im);
  ::dueca::checkandunpackdiffsingle(this->motion, s, im);
  ::dueca::checkandunpackdiffsingle(this->filter, s, im);
  ::dueca::checkandunpackdiffsingle(this->param, s, im);
  ::dueca::checkandunpackdiffsingle(this->filter_confirmed, s, im);
  ::dueca::checkandunpackdiffsingle(this->param_confirmed, s, im);
}
#endif

#ifndef __CUSTOM_OPERATOR_EQUAL
bool MotionConfiguration::operator == (const MotionConfiguration& other) const
{
  DOBS("operator == MotionConfiguration");
  if (this->event_type != other.event_type) return false;
  if (this->motion != other.motion) return false;
  if (this->filter != other.filter) return false;
  if (this->param != other.param) return false;
  if (this->filter_confirmed != other.filter_confirmed) return false;
  if (this->param_confirmed != other.param_confirmed) return false;
  return true;
}
#endif

#ifndef __CUSTOM_OPERATOR_ASSIGN
MotionConfiguration&
MotionConfiguration::operator=(const MotionConfiguration& other)
{
  DOBS("operator = MotionConfiguration");
  if (this == &other) return *this;
  this->event_type = other.event_type;
  this->motion = other.motion;
  this->filter = other.filter;
  this->param = other.param;
  this->filter_confirmed = other.filter_confirmed;
  this->param_confirmed = other.param_confirmed;
  return *this;
}
#endif

#if !defined(__CUSTOM_FUNCTION_PACKDATA) && !defined(__DCO_NOPACK)
void MotionConfiguration::packData(::dueca::AmorphStore& s) const
{
  DOBS("packData MotionConfiguration");
  ::packData(s, this->event_type);
  ::packData(s, this->motion);
  ::packData(s, this->filter);
  ::packData(s, this->param);
  ::packData(s, this->filter_confirmed);
  ::packData(s, this->param_confirmed);
}
#endif

#ifndef __CUSTOM_FUNCTION_PRINT
std::ostream & MotionConfiguration::print(std::ostream& s) const
{
  s << "MotionConfiguration("
    << "event_type=" << this->event_type << ','
    << "motion=" << this->motion << ','
    << "filter=" << this->filter << ','
    << "param=" << this->param << ','
    << "filter_confirmed=" << this->filter_confirmed << ','
    << "param_confirmed=" << this->param_confirmed
    << ')';
  return s;
}
#endif


            #ifndef __CUSTOM_GETSTRING_evt_type
const char* const getString(const MotionConfiguration::evt_type &o)
{
  static const char* evt_type_names[] = {
    "Request",
    "Confirm"};

  return evt_type_names[int(o)];
}
#endif

#ifndef __CUSTOM_READFROMSTRING_evt_type
void readFromString(MotionConfiguration::evt_type &o, const std::string& s)
{
  for (int ii = 2; ii--; ) {
    if (std::string(getString(MotionConfiguration::evt_type(ii))) == s) {
      o = MotionConfiguration::evt_type(ii);
      return;
    }
  }
  throw(dueca::ConversionNotDefined());
}
#endif

#if !defined(__CUSTOM_PACKDATA_evt_type) && !defined(__DCO_NOPACK)
void packData(::dueca::AmorphStore& s,
              const MotionConfiguration::evt_type &o)
{ packData(s, uint8_t(o));}
#endif

#if !defined(__CUSTOM_UNPACKDATA_evt_type) && !defined(__DCO_NOPACK)
void unPackData(::dueca::AmorphReStore& s,
                MotionConfiguration::evt_type &o)
{ uint8_t tmp(s); o = MotionConfiguration::evt_type(tmp); }
#endif

namespace dueca {;
template <>
const char* getclassname<MotionConfiguration::evt_type>()
{ return "MotionConfiguration::evt_type"; }
};

