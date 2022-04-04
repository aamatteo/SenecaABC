/* ------------------------------------------------------------------ */
/*      item            : AutopilotTargets.cxx
        generated by    : matteo (matteo)
        date            : Thu 24 Mar 2022
        category        : body file
        description     : DUECA Communication Object (DCO),
                          automatically generated by dueca-codegen
        codegen version : 110
        language        : C++
*/

#include "AutopilotTargets.hxx"
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
// to the members of a AutopilotTargets object
static ::dueca::CommObjectMemberAccess
  <AutopilotTargets,double >
  AutopilotTargets_member_Vcmd(&AutopilotTargets::Vcmd, "Vcmd");
static ::dueca::CommObjectMemberAccess
  <AutopilotTargets,double >
  AutopilotTargets_member_Vx(&AutopilotTargets::Vx, "Vx");
static ::dueca::CommObjectMemberAccess
  <AutopilotTargets,double >
  AutopilotTargets_member_Vmin(&AutopilotTargets::Vmin, "Vmin");
static ::dueca::CommObjectMemberAccess
  <AutopilotTargets,double >
  AutopilotTargets_member_Vmax(&AutopilotTargets::Vmax, "Vmax");
static ::dueca::CommObjectMemberAccess
  <AutopilotTargets,double >
  AutopilotTargets_member_altitude(&AutopilotTargets::altitude, "altitude");

// assemble the above entries into a table in the order in which they
// appear in the AutopilotTargets object
static const ::dueca::CommObjectDataTable entriestable[] = {
  { &AutopilotTargets_member_Vcmd },
  { &AutopilotTargets_member_Vx },
  { &AutopilotTargets_member_Vmin },
  { &AutopilotTargets_member_Vmax },
  { &AutopilotTargets_member_altitude },
  { NULL }
};

#endif

// class name, static
const char * const AutopilotTargets::classname = "AutopilotTargets";

// magic number, hashed from class name and member names / classes
const uint32_t AutopilotTargets::magic_check_number=0x7da224cb;

#if !defined(__DCO_STANDALONE)
// functor table, provides access to user-defined metafunctions through the
// data class registry
static dueca::functortable_type functortable;

// register this class, provides access to a packing/unpacking object,
// and to the member access tables
static ::dueca::DataClassRegistrar registrar
  (AutopilotTargets::classname, NULL,
   entriestable, &functortable,
   new ::dueca::DataSetSubsidiary<AutopilotTargets>());

#endif

#ifndef __CUSTOM_DEFAULT_CONSTRUCTOR
AutopilotTargets::AutopilotTargets():
    Vcmd(0.0),
    Vx(0.0),
    Vmin(0.0),
    Vmax(0.0),
    altitude(0.0)
{
  DOBS("default constructor AutopilotTargets");
}
#endif

#ifndef __CUSTOM_FULL_CONSTRUCTOR
AutopilotTargets::AutopilotTargets(
        const double& Vcmd,
        const double& Vx,
        const double& Vmin,
        const double& Vmax,
        const double& altitude) :
    Vcmd(Vcmd),
    Vx(Vx),
    Vmin(Vmin),
    Vmax(Vmax),
    altitude(altitude)
{
  DOBS("complete constructor AutopilotTargets");
}
#endif

#ifndef __CUSTOM_FULLSINGLES_CONSTRUCTOR
#endif

#ifndef __CUSTOM_COPY_CONSTRUCTOR
AutopilotTargets::AutopilotTargets(const AutopilotTargets& other):
    Vcmd(other.Vcmd),
    Vx(other.Vx),
    Vmin(other.Vmin),
    Vmax(other.Vmax),
    altitude(other.altitude)
{
  DOBS("copy constructor AutopilotTargets");
}
#endif

#if !defined(__CUSTOM_AMORPHRESTORE_CONSTRUCTOR) && !defined(__DCO_NOPACK)
AutopilotTargets::AutopilotTargets(dueca::AmorphReStore& s):
        Vcmd(s),
        Vx(s),
        Vmin(s),
        Vmax(s),
        altitude(s)
{
  DOBS("amorph constructor AutopilotTargets");
}
#endif

#if !defined(__CUSTOM_ARRAY_SIZE_INIT_CONSTRUCTOR)
#endif

#ifndef __CUSTOM_DESTRUCTOR
AutopilotTargets::~AutopilotTargets()
{
  DOBS("destructor AutopilotTargets");
}
#endif

#if !defined(__DCO_STANDALONE)
void* AutopilotTargets::operator new(size_t size)
{
  DOBS("operator new AutopilotTargets");
  static ::dueca::Arena* my_arena = arena_pool.findArena
    (sizeof(AutopilotTargets));
  return my_arena->alloc(size);
}

void AutopilotTargets::operator delete(void* v)
{
  DOBS("operator delete AutopilotTargets");
  static ::dueca::Arena* my_arena = arena_pool.findArena
    (sizeof(AutopilotTargets));
  my_arena->free(v);
}
#endif

#if !defined(__CUSTOM_FUNCTION_PACKDATADIFF) && !defined(__DCO_NOPACK)
void AutopilotTargets::packDataDiff(::dueca::AmorphStore& s, const AutopilotTargets& ref) const
{
  DOBS("packDataDiff AutopilotTargets");
  ::dueca::IndexMemory im;
  ::dueca::checkandpackdiffsingle(this->Vcmd, ref.Vcmd,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->Vx, ref.Vx,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->Vmin, ref.Vmin,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->Vmax, ref.Vmax,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->altitude, ref.altitude,
                         s, im);
  im.closeoff(s);
}
#endif

#if !defined(__CUSTOM_FUNCTION_UNPACKDATA) && !defined(__DCO_NOPACK)
void AutopilotTargets::unPackData(::dueca::AmorphReStore& s)
{
  DOBS("unPackData AutopilotTargets");

  ::unPackData(s, this->Vcmd);
  ::unPackData(s, this->Vx);
  ::unPackData(s, this->Vmin);
  ::unPackData(s, this->Vmax);
  ::unPackData(s, this->altitude);

}
#endif

#if !defined(__CUSTOM_FUNCTION_UNPACKDATADIFF) && !defined(__DCO_NOPACK)
void AutopilotTargets::unPackDataDiff(dueca::AmorphReStore& s)
{
  DOBS("unPackDataDiff AutopilotTargets");
  ::dueca::IndexRecall im;
  ::dueca::checkandunpackdiffsingle(this->Vcmd, s, im);
  ::dueca::checkandunpackdiffsingle(this->Vx, s, im);
  ::dueca::checkandunpackdiffsingle(this->Vmin, s, im);
  ::dueca::checkandunpackdiffsingle(this->Vmax, s, im);
  ::dueca::checkandunpackdiffsingle(this->altitude, s, im);
}
#endif

#ifndef __CUSTOM_OPERATOR_EQUAL
bool AutopilotTargets::operator == (const AutopilotTargets& other) const
{
  DOBS("operator == AutopilotTargets");
  if (this->Vcmd != other.Vcmd) return false;
  if (this->Vx != other.Vx) return false;
  if (this->Vmin != other.Vmin) return false;
  if (this->Vmax != other.Vmax) return false;
  if (this->altitude != other.altitude) return false;
  return true;
}
#endif

#ifndef __CUSTOM_OPERATOR_ASSIGN
AutopilotTargets&
AutopilotTargets::operator=(const AutopilotTargets& other)
{
  DOBS("operator = AutopilotTargets");
  if (this == &other) return *this;
  this->Vcmd = other.Vcmd;
  this->Vx = other.Vx;
  this->Vmin = other.Vmin;
  this->Vmax = other.Vmax;
  this->altitude = other.altitude;
  return *this;
}
#endif

#if !defined(__CUSTOM_FUNCTION_PACKDATA) && !defined(__DCO_NOPACK)
void AutopilotTargets::packData(::dueca::AmorphStore& s) const
{
  DOBS("packData AutopilotTargets");
  ::packData(s, this->Vcmd);
  ::packData(s, this->Vx);
  ::packData(s, this->Vmin);
  ::packData(s, this->Vmax);
  ::packData(s, this->altitude);
}
#endif

#ifndef __CUSTOM_FUNCTION_PRINT
std::ostream & AutopilotTargets::print(std::ostream& s) const
{
  s << "AutopilotTargets("
    << "Vcmd=" << this->Vcmd << ','
    << "Vx=" << this->Vx << ','
    << "Vmin=" << this->Vmin << ','
    << "Vmax=" << this->Vmax << ','
    << "altitude=" << this->altitude
    << ')';
  return s;
}
#endif


