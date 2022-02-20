/* ------------------------------------------------------------------ */
/*      item            : FGIncoEvent.cxx
        generated by    : matteo (matteo)
        date            : Wed 15 Dec 2021
        category        : body file
        description     : DUECA Communication Object (DCO),
                          automatically generated by dueca-codegen
        codegen version : 110
        language        : C++
*/

#include "FGIncoEvent.hxx"
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
// to the members of a FGIncoEvent object
static ::dueca::CommObjectMemberAccess
  <FGIncoEvent,float >
  FGIncoEvent_member_lat_zero(&FGIncoEvent::lat_zero, "lat_zero");
static ::dueca::CommObjectMemberAccess
  <FGIncoEvent,float >
  FGIncoEvent_member_lon_zero(&FGIncoEvent::lon_zero, "lon_zero");
static ::dueca::CommObjectMemberAccess
  <FGIncoEvent,float >
  FGIncoEvent_member_alt_zero(&FGIncoEvent::alt_zero, "alt_zero");
static ::dueca::CommObjectMemberAccess
  <FGIncoEvent,float >
  FGIncoEvent_member_psi_zero(&FGIncoEvent::psi_zero, "psi_zero");

// assemble the above entries into a table in the order in which they
// appear in the FGIncoEvent object
static const ::dueca::CommObjectDataTable entriestable[] = {
  { &FGIncoEvent_member_lat_zero },
  { &FGIncoEvent_member_lon_zero },
  { &FGIncoEvent_member_alt_zero },
  { &FGIncoEvent_member_psi_zero },
  { NULL }
};

#endif

// class name, static
const char * const FGIncoEvent::classname = "FGIncoEvent";

// magic number, hashed from class name and member names / classes
const uint32_t FGIncoEvent::magic_check_number=0x642fcc9b;

#if !defined(__DCO_STANDALONE)
// functor table, provides access to user-defined metafunctions through the
// data class registry
static dueca::functortable_type functortable;

// register this class, provides access to a packing/unpacking object,
// and to the member access tables
static ::dueca::DataClassRegistrar registrar
  (FGIncoEvent::classname, NULL,
   entriestable, &functortable,
   new ::dueca::DataSetSubsidiary<FGIncoEvent>());

#endif

#ifndef __CUSTOM_DEFAULT_CONSTRUCTOR
FGIncoEvent::FGIncoEvent()
{
  DOBS("default constructor FGIncoEvent");
}
#endif

#ifndef __CUSTOM_FULL_CONSTRUCTOR
FGIncoEvent::FGIncoEvent(
        const float& lat_zero,
        const float& lon_zero,
        const float& alt_zero,
        const float& psi_zero) :
    lat_zero(lat_zero),
    lon_zero(lon_zero),
    alt_zero(alt_zero),
    psi_zero(psi_zero)
{
  DOBS("complete constructor FGIncoEvent");
}
#endif

#ifndef __CUSTOM_FULLSINGLES_CONSTRUCTOR
#endif

#ifndef __CUSTOM_COPY_CONSTRUCTOR
FGIncoEvent::FGIncoEvent(const FGIncoEvent& other):
    lat_zero(other.lat_zero),
    lon_zero(other.lon_zero),
    alt_zero(other.alt_zero),
    psi_zero(other.psi_zero)
{
  DOBS("copy constructor FGIncoEvent");
}
#endif

#if !defined(__CUSTOM_AMORPHRESTORE_CONSTRUCTOR) && !defined(__DCO_NOPACK)
FGIncoEvent::FGIncoEvent(dueca::AmorphReStore& s):
        lat_zero(s),
        lon_zero(s),
        alt_zero(s),
        psi_zero(s)
{
  DOBS("amorph constructor FGIncoEvent");
}
#endif

#if !defined(__CUSTOM_ARRAY_SIZE_INIT_CONSTRUCTOR)
#endif

#ifndef __CUSTOM_DESTRUCTOR
FGIncoEvent::~FGIncoEvent()
{
  DOBS("destructor FGIncoEvent");
}
#endif

#if !defined(__DCO_STANDALONE)
void* FGIncoEvent::operator new(size_t size)
{
  DOBS("operator new FGIncoEvent");
  static ::dueca::Arena* my_arena = arena_pool.findArena
    (sizeof(FGIncoEvent));
  return my_arena->alloc(size);
}

void FGIncoEvent::operator delete(void* v)
{
  DOBS("operator delete FGIncoEvent");
  static ::dueca::Arena* my_arena = arena_pool.findArena
    (sizeof(FGIncoEvent));
  my_arena->free(v);
}
#endif

#if !defined(__CUSTOM_FUNCTION_PACKDATADIFF) && !defined(__DCO_NOPACK)
void FGIncoEvent::packDataDiff(::dueca::AmorphStore& s, const FGIncoEvent& ref) const
{
  DOBS("packDataDiff FGIncoEvent");
  ::dueca::IndexMemory im;
  ::dueca::checkandpackdiffsingle(this->lat_zero, ref.lat_zero,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->lon_zero, ref.lon_zero,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->alt_zero, ref.alt_zero,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->psi_zero, ref.psi_zero,
                         s, im);
  im.closeoff(s);
}
#endif

#if !defined(__CUSTOM_FUNCTION_UNPACKDATA) && !defined(__DCO_NOPACK)
void FGIncoEvent::unPackData(::dueca::AmorphReStore& s)
{
  DOBS("unPackData FGIncoEvent");

  ::unPackData(s, this->lat_zero);
  ::unPackData(s, this->lon_zero);
  ::unPackData(s, this->alt_zero);
  ::unPackData(s, this->psi_zero);

}
#endif

#if !defined(__CUSTOM_FUNCTION_UNPACKDATADIFF) && !defined(__DCO_NOPACK)
void FGIncoEvent::unPackDataDiff(dueca::AmorphReStore& s)
{
  DOBS("unPackDataDiff FGIncoEvent");
  ::dueca::IndexRecall im;
  ::dueca::checkandunpackdiffsingle(this->lat_zero, s, im);
  ::dueca::checkandunpackdiffsingle(this->lon_zero, s, im);
  ::dueca::checkandunpackdiffsingle(this->alt_zero, s, im);
  ::dueca::checkandunpackdiffsingle(this->psi_zero, s, im);
}
#endif

#ifndef __CUSTOM_OPERATOR_EQUAL
bool FGIncoEvent::operator == (const FGIncoEvent& other) const
{
  DOBS("operator == FGIncoEvent");
  if (this->lat_zero != other.lat_zero) return false;
  if (this->lon_zero != other.lon_zero) return false;
  if (this->alt_zero != other.alt_zero) return false;
  if (this->psi_zero != other.psi_zero) return false;
  return true;
}
#endif

#ifndef __CUSTOM_OPERATOR_ASSIGN
FGIncoEvent&
FGIncoEvent::operator=(const FGIncoEvent& other)
{
  DOBS("operator = FGIncoEvent");
  if (this == &other) return *this;
  this->lat_zero = other.lat_zero;
  this->lon_zero = other.lon_zero;
  this->alt_zero = other.alt_zero;
  this->psi_zero = other.psi_zero;
  return *this;
}
#endif

#if !defined(__CUSTOM_FUNCTION_PACKDATA) && !defined(__DCO_NOPACK)
void FGIncoEvent::packData(::dueca::AmorphStore& s) const
{
  DOBS("packData FGIncoEvent");
  ::packData(s, this->lat_zero);
  ::packData(s, this->lon_zero);
  ::packData(s, this->alt_zero);
  ::packData(s, this->psi_zero);
}
#endif

#ifndef __CUSTOM_FUNCTION_PRINT
std::ostream & FGIncoEvent::print(std::ostream& s) const
{
  s << "FGIncoEvent("
    << "lat_zero=" << this->lat_zero << ','
    << "lon_zero=" << this->lon_zero << ','
    << "alt_zero=" << this->alt_zero << ','
    << "psi_zero=" << this->psi_zero
    << ')';
  return s;
}
#endif


