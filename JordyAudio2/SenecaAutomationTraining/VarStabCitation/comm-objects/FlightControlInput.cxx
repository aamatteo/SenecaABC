/* ------------------------------------------------------------------ */
/*      item            : FlightControlInput.cxx
        generated by    : matteo (matteo)
        date            : Wed 15 Dec 2021
        category        : body file
        description     : DUECA Communication Object (DCO),
                          automatically generated by dueca-codegen
        codegen version : 110
        language        : C++
*/

#include "FlightControlInput.hxx"
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
// to the members of a FlightControlInput object
static ::dueca::CommObjectMemberAccess
  <FlightControlInput,double >
  FlightControlInput_member_de(&FlightControlInput::de, "de");
static ::dueca::CommObjectMemberAccess
  <FlightControlInput,double >
  FlightControlInput_member_da(&FlightControlInput::da, "da");
static ::dueca::CommObjectMemberAccess
  <FlightControlInput,double >
  FlightControlInput_member_dr(&FlightControlInput::dr, "dr");
static ::dueca::CommObjectMemberAccess
  <FlightControlInput,double >
  FlightControlInput_member_df(&FlightControlInput::df, "df");
static ::dueca::CommObjectMemberAccess
  <FlightControlInput,double >
  FlightControlInput_member_gear(&FlightControlInput::gear, "gear");
static ::dueca::CommObjectMemberAccess
  <FlightControlInput,double >
  FlightControlInput_member_pla1(&FlightControlInput::pla1, "pla1");
static ::dueca::CommObjectMemberAccess
  <FlightControlInput,double >
  FlightControlInput_member_pla2(&FlightControlInput::pla2, "pla2");
static ::dueca::CommObjectMemberAccess
  <FlightControlInput,bool >
  FlightControlInput_member_ecrequest(&FlightControlInput::ecrequest, "ecrequest");

// assemble the above entries into a table in the order in which they
// appear in the FlightControlInput object
static const ::dueca::CommObjectDataTable entriestable[] = {
  { &FlightControlInput_member_de },
  { &FlightControlInput_member_da },
  { &FlightControlInput_member_dr },
  { &FlightControlInput_member_df },
  { &FlightControlInput_member_gear },
  { &FlightControlInput_member_pla1 },
  { &FlightControlInput_member_pla2 },
  { &FlightControlInput_member_ecrequest },
  { NULL }
};

#endif

// class name, static
const char * const FlightControlInput::classname = "FlightControlInput";

// magic number, hashed from class name and member names / classes
const uint32_t FlightControlInput::magic_check_number=0xe62662a7;

#if !defined(__DCO_STANDALONE)
// functor table, provides access to user-defined metafunctions through the
// data class registry
static dueca::functortable_type functortable;

// register this class, provides access to a packing/unpacking object,
// and to the member access tables
static ::dueca::DataClassRegistrar registrar
  (FlightControlInput::classname, NULL,
   entriestable, &functortable,
   new ::dueca::DataSetSubsidiary<FlightControlInput>());

#endif

#ifndef __CUSTOM_DEFAULT_CONSTRUCTOR
FlightControlInput::FlightControlInput():
    de(0.0f),
    da(0.0f),
    dr(0.0f),
    df(0.0f),
    gear(0.0f),
    pla1(0.0f),
    pla2(0.0f),
    ecrequest(true)
{
  DOBS("default constructor FlightControlInput");
}
#endif

#ifndef __CUSTOM_FULL_CONSTRUCTOR
FlightControlInput::FlightControlInput(
        const double& de,
        const double& da,
        const double& dr,
        const double& df,
        const double& gear,
        const double& pla1,
        const double& pla2,
        const bool& ecrequest) :
    de(de),
    da(da),
    dr(dr),
    df(df),
    gear(gear),
    pla1(pla1),
    pla2(pla2),
    ecrequest(ecrequest)
{
  DOBS("complete constructor FlightControlInput");
}
#endif

#ifndef __CUSTOM_FULLSINGLES_CONSTRUCTOR
#endif

#ifndef __CUSTOM_COPY_CONSTRUCTOR
FlightControlInput::FlightControlInput(const FlightControlInput& other):
    de(other.de),
    da(other.da),
    dr(other.dr),
    df(other.df),
    gear(other.gear),
    pla1(other.pla1),
    pla2(other.pla2),
    ecrequest(other.ecrequest)
{
  DOBS("copy constructor FlightControlInput");
}
#endif

#if !defined(__CUSTOM_AMORPHRESTORE_CONSTRUCTOR) && !defined(__DCO_NOPACK)
FlightControlInput::FlightControlInput(dueca::AmorphReStore& s):
        de(s),
        da(s),
        dr(s),
        df(s),
        gear(s),
        pla1(s),
        pla2(s),
        ecrequest(s)
{
  DOBS("amorph constructor FlightControlInput");
}
#endif

#if !defined(__CUSTOM_ARRAY_SIZE_INIT_CONSTRUCTOR)
#endif

#ifndef __CUSTOM_DESTRUCTOR
FlightControlInput::~FlightControlInput()
{
  DOBS("destructor FlightControlInput");
}
#endif

#if !defined(__DCO_STANDALONE)
void* FlightControlInput::operator new(size_t size)
{
  DOBS("operator new FlightControlInput");
  static ::dueca::Arena* my_arena = arena_pool.findArena
    (sizeof(FlightControlInput));
  return my_arena->alloc(size);
}

void FlightControlInput::operator delete(void* v)
{
  DOBS("operator delete FlightControlInput");
  static ::dueca::Arena* my_arena = arena_pool.findArena
    (sizeof(FlightControlInput));
  my_arena->free(v);
}
#endif

#if !defined(__CUSTOM_FUNCTION_PACKDATADIFF) && !defined(__DCO_NOPACK)
void FlightControlInput::packDataDiff(::dueca::AmorphStore& s, const FlightControlInput& ref) const
{
  DOBS("packDataDiff FlightControlInput");
  ::dueca::IndexMemory im;
  ::dueca::checkandpackdiffsingle(this->de, ref.de,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->da, ref.da,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->dr, ref.dr,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->df, ref.df,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->gear, ref.gear,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->pla1, ref.pla1,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->pla2, ref.pla2,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->ecrequest, ref.ecrequest,
                         s, im);
  im.closeoff(s);
}
#endif

#if !defined(__CUSTOM_FUNCTION_UNPACKDATA) && !defined(__DCO_NOPACK)
void FlightControlInput::unPackData(::dueca::AmorphReStore& s)
{
  DOBS("unPackData FlightControlInput");

  ::unPackData(s, this->de);
  ::unPackData(s, this->da);
  ::unPackData(s, this->dr);
  ::unPackData(s, this->df);
  ::unPackData(s, this->gear);
  ::unPackData(s, this->pla1);
  ::unPackData(s, this->pla2);
  ::unPackData(s, this->ecrequest);

}
#endif

#if !defined(__CUSTOM_FUNCTION_UNPACKDATADIFF) && !defined(__DCO_NOPACK)
void FlightControlInput::unPackDataDiff(dueca::AmorphReStore& s)
{
  DOBS("unPackDataDiff FlightControlInput");
  ::dueca::IndexRecall im;
  ::dueca::checkandunpackdiffsingle(this->de, s, im);
  ::dueca::checkandunpackdiffsingle(this->da, s, im);
  ::dueca::checkandunpackdiffsingle(this->dr, s, im);
  ::dueca::checkandunpackdiffsingle(this->df, s, im);
  ::dueca::checkandunpackdiffsingle(this->gear, s, im);
  ::dueca::checkandunpackdiffsingle(this->pla1, s, im);
  ::dueca::checkandunpackdiffsingle(this->pla2, s, im);
  ::dueca::checkandunpackdiffsingle(this->ecrequest, s, im);
}
#endif

#ifndef __CUSTOM_OPERATOR_EQUAL
bool FlightControlInput::operator == (const FlightControlInput& other) const
{
  DOBS("operator == FlightControlInput");
  if (this->de != other.de) return false;
  if (this->da != other.da) return false;
  if (this->dr != other.dr) return false;
  if (this->df != other.df) return false;
  if (this->gear != other.gear) return false;
  if (this->pla1 != other.pla1) return false;
  if (this->pla2 != other.pla2) return false;
  if (this->ecrequest != other.ecrequest) return false;
  return true;
}
#endif

#ifndef __CUSTOM_OPERATOR_ASSIGN
FlightControlInput&
FlightControlInput::operator=(const FlightControlInput& other)
{
  DOBS("operator = FlightControlInput");
  if (this == &other) return *this;
  this->de = other.de;
  this->da = other.da;
  this->dr = other.dr;
  this->df = other.df;
  this->gear = other.gear;
  this->pla1 = other.pla1;
  this->pla2 = other.pla2;
  this->ecrequest = other.ecrequest;
  return *this;
}
#endif

#if !defined(__CUSTOM_FUNCTION_PACKDATA) && !defined(__DCO_NOPACK)
void FlightControlInput::packData(::dueca::AmorphStore& s) const
{
  DOBS("packData FlightControlInput");
  ::packData(s, this->de);
  ::packData(s, this->da);
  ::packData(s, this->dr);
  ::packData(s, this->df);
  ::packData(s, this->gear);
  ::packData(s, this->pla1);
  ::packData(s, this->pla2);
  ::packData(s, this->ecrequest);
}
#endif

#ifndef __CUSTOM_FUNCTION_PRINT
std::ostream & FlightControlInput::print(std::ostream& s) const
{
  s << "FlightControlInput("
    << "de=" << this->de << ','
    << "da=" << this->da << ','
    << "dr=" << this->dr << ','
    << "df=" << this->df << ','
    << "gear=" << this->gear << ','
    << "pla1=" << this->pla1 << ','
    << "pla2=" << this->pla2 << ','
    << "ecrequest=" << this->ecrequest
    << ')';
  return s;
}
#endif


