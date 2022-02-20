/* ------------------------------------------------------------------ */
/*      item            : Trim_inco.cxx
        generated by    : matteo (matteo)
        date            : Wed 15 Dec 2021
        category        : body file
        description     : DUECA Communication Object (DCO),
                          automatically generated by dueca-codegen
        codegen version : 110
        language        : C++
*/

#include "Trim_inco.hxx"
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
// to the members of a Trim_inco object
static ::dueca::CommObjectMemberAccess
  <Trim_inco,float >
  Trim_inco_member_de_trim(&Trim_inco::de_trim, "de_trim");
static ::dueca::CommObjectMemberAccess
  <Trim_inco,float >
  Trim_inco_member_da_trim(&Trim_inco::da_trim, "da_trim");
static ::dueca::CommObjectMemberAccess
  <Trim_inco,float >
  Trim_inco_member_dr_trim(&Trim_inco::dr_trim, "dr_trim");
static ::dueca::CommObjectMemberAccess
  <Trim_inco,float >
  Trim_inco_member_pla1_trim(&Trim_inco::pla1_trim, "pla1_trim");
static ::dueca::CommObjectMemberAccess
  <Trim_inco,float >
  Trim_inco_member_pla2_trim(&Trim_inco::pla2_trim, "pla2_trim");
static ::dueca::CommObjectMemberAccess
  <Trim_inco,float >
  Trim_inco_member_gear_trim(&Trim_inco::gear_trim, "gear_trim");
static ::dueca::CommObjectMemberAccess
  <Trim_inco,float >
  Trim_inco_member_flaps_trim(&Trim_inco::flaps_trim, "flaps_trim");

// assemble the above entries into a table in the order in which they
// appear in the Trim_inco object
static const ::dueca::CommObjectDataTable entriestable[] = {
  { &Trim_inco_member_de_trim },
  { &Trim_inco_member_da_trim },
  { &Trim_inco_member_dr_trim },
  { &Trim_inco_member_pla1_trim },
  { &Trim_inco_member_pla2_trim },
  { &Trim_inco_member_gear_trim },
  { &Trim_inco_member_flaps_trim },
  { NULL }
};

#endif

// class name, static
const char * const Trim_inco::classname = "Trim_inco";

// magic number, hashed from class name and member names / classes
const uint32_t Trim_inco::magic_check_number=0x39c21a28;

#if !defined(__DCO_STANDALONE)
// functor table, provides access to user-defined metafunctions through the
// data class registry
static dueca::functortable_type functortable;

// register this class, provides access to a packing/unpacking object,
// and to the member access tables
static ::dueca::DataClassRegistrar registrar
  (Trim_inco::classname, NULL,
   entriestable, &functortable,
   new ::dueca::DataSetSubsidiary<Trim_inco>());

#endif

#ifndef __CUSTOM_DEFAULT_CONSTRUCTOR
Trim_inco::Trim_inco()
{
  DOBS("default constructor Trim_inco");
}
#endif

#ifndef __CUSTOM_FULL_CONSTRUCTOR
Trim_inco::Trim_inco(
        const float& de_trim,
        const float& da_trim,
        const float& dr_trim,
        const float& pla1_trim,
        const float& pla2_trim,
        const float& gear_trim,
        const float& flaps_trim) :
    de_trim(de_trim),
    da_trim(da_trim),
    dr_trim(dr_trim),
    pla1_trim(pla1_trim),
    pla2_trim(pla2_trim),
    gear_trim(gear_trim),
    flaps_trim(flaps_trim)
{
  DOBS("complete constructor Trim_inco");
}
#endif

#ifndef __CUSTOM_FULLSINGLES_CONSTRUCTOR
#endif

#ifndef __CUSTOM_COPY_CONSTRUCTOR
Trim_inco::Trim_inco(const Trim_inco& other):
    de_trim(other.de_trim),
    da_trim(other.da_trim),
    dr_trim(other.dr_trim),
    pla1_trim(other.pla1_trim),
    pla2_trim(other.pla2_trim),
    gear_trim(other.gear_trim),
    flaps_trim(other.flaps_trim)
{
  DOBS("copy constructor Trim_inco");
}
#endif

#if !defined(__CUSTOM_AMORPHRESTORE_CONSTRUCTOR) && !defined(__DCO_NOPACK)
Trim_inco::Trim_inco(dueca::AmorphReStore& s):
        de_trim(s),
        da_trim(s),
        dr_trim(s),
        pla1_trim(s),
        pla2_trim(s),
        gear_trim(s),
        flaps_trim(s)
{
  DOBS("amorph constructor Trim_inco");
}
#endif

#if !defined(__CUSTOM_ARRAY_SIZE_INIT_CONSTRUCTOR)
#endif

#ifndef __CUSTOM_DESTRUCTOR
Trim_inco::~Trim_inco()
{
  DOBS("destructor Trim_inco");
}
#endif

#if !defined(__DCO_STANDALONE)
void* Trim_inco::operator new(size_t size)
{
  DOBS("operator new Trim_inco");
  static ::dueca::Arena* my_arena = arena_pool.findArena
    (sizeof(Trim_inco));
  return my_arena->alloc(size);
}

void Trim_inco::operator delete(void* v)
{
  DOBS("operator delete Trim_inco");
  static ::dueca::Arena* my_arena = arena_pool.findArena
    (sizeof(Trim_inco));
  my_arena->free(v);
}
#endif

#if !defined(__CUSTOM_FUNCTION_PACKDATADIFF) && !defined(__DCO_NOPACK)
void Trim_inco::packDataDiff(::dueca::AmorphStore& s, const Trim_inco& ref) const
{
  DOBS("packDataDiff Trim_inco");
  ::dueca::IndexMemory im;
  ::dueca::checkandpackdiffsingle(this->de_trim, ref.de_trim,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->da_trim, ref.da_trim,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->dr_trim, ref.dr_trim,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->pla1_trim, ref.pla1_trim,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->pla2_trim, ref.pla2_trim,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->gear_trim, ref.gear_trim,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->flaps_trim, ref.flaps_trim,
                         s, im);
  im.closeoff(s);
}
#endif

#if !defined(__CUSTOM_FUNCTION_UNPACKDATA) && !defined(__DCO_NOPACK)
void Trim_inco::unPackData(::dueca::AmorphReStore& s)
{
  DOBS("unPackData Trim_inco");

  ::unPackData(s, this->de_trim);
  ::unPackData(s, this->da_trim);
  ::unPackData(s, this->dr_trim);
  ::unPackData(s, this->pla1_trim);
  ::unPackData(s, this->pla2_trim);
  ::unPackData(s, this->gear_trim);
  ::unPackData(s, this->flaps_trim);

}
#endif

#if !defined(__CUSTOM_FUNCTION_UNPACKDATADIFF) && !defined(__DCO_NOPACK)
void Trim_inco::unPackDataDiff(dueca::AmorphReStore& s)
{
  DOBS("unPackDataDiff Trim_inco");
  ::dueca::IndexRecall im;
  ::dueca::checkandunpackdiffsingle(this->de_trim, s, im);
  ::dueca::checkandunpackdiffsingle(this->da_trim, s, im);
  ::dueca::checkandunpackdiffsingle(this->dr_trim, s, im);
  ::dueca::checkandunpackdiffsingle(this->pla1_trim, s, im);
  ::dueca::checkandunpackdiffsingle(this->pla2_trim, s, im);
  ::dueca::checkandunpackdiffsingle(this->gear_trim, s, im);
  ::dueca::checkandunpackdiffsingle(this->flaps_trim, s, im);
}
#endif

#ifndef __CUSTOM_OPERATOR_EQUAL
bool Trim_inco::operator == (const Trim_inco& other) const
{
  DOBS("operator == Trim_inco");
  if (this->de_trim != other.de_trim) return false;
  if (this->da_trim != other.da_trim) return false;
  if (this->dr_trim != other.dr_trim) return false;
  if (this->pla1_trim != other.pla1_trim) return false;
  if (this->pla2_trim != other.pla2_trim) return false;
  if (this->gear_trim != other.gear_trim) return false;
  if (this->flaps_trim != other.flaps_trim) return false;
  return true;
}
#endif

#ifndef __CUSTOM_OPERATOR_ASSIGN
Trim_inco&
Trim_inco::operator=(const Trim_inco& other)
{
  DOBS("operator = Trim_inco");
  if (this == &other) return *this;
  this->de_trim = other.de_trim;
  this->da_trim = other.da_trim;
  this->dr_trim = other.dr_trim;
  this->pla1_trim = other.pla1_trim;
  this->pla2_trim = other.pla2_trim;
  this->gear_trim = other.gear_trim;
  this->flaps_trim = other.flaps_trim;
  return *this;
}
#endif

#if !defined(__CUSTOM_FUNCTION_PACKDATA) && !defined(__DCO_NOPACK)
void Trim_inco::packData(::dueca::AmorphStore& s) const
{
  DOBS("packData Trim_inco");
  ::packData(s, this->de_trim);
  ::packData(s, this->da_trim);
  ::packData(s, this->dr_trim);
  ::packData(s, this->pla1_trim);
  ::packData(s, this->pla2_trim);
  ::packData(s, this->gear_trim);
  ::packData(s, this->flaps_trim);
}
#endif

#ifndef __CUSTOM_FUNCTION_PRINT
std::ostream & Trim_inco::print(std::ostream& s) const
{
  s << "Trim_inco("
    << "de_trim=" << this->de_trim << ','
    << "da_trim=" << this->da_trim << ','
    << "dr_trim=" << this->dr_trim << ','
    << "pla1_trim=" << this->pla1_trim << ','
    << "pla2_trim=" << this->pla2_trim << ','
    << "gear_trim=" << this->gear_trim << ','
    << "flaps_trim=" << this->flaps_trim
    << ')';
  return s;
}
#endif


