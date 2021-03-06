/* ------------------------------------------------------------------ */
/*      item            : PropSoundData.cxx
        generated by    : matteo (matteo)
        date            : Thu 24 Mar 2022
        category        : body file
        description     : DUECA Communication Object (DCO),
                          automatically generated by dueca-codegen
        codegen version : 110
        language        : C++
*/

#include "PropSoundData.hxx"
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
// to the members of a PropSoundData object
static ::dueca::CommObjectMemberAccess
  <PropSoundData,dueca::fixvector<2,float> >
  PropSoundData_member_rpm(&PropSoundData::rpm, "rpm");
static ::dueca::CommObjectMemberAccess
  <PropSoundData,dueca::fixvector<2,float> >
  PropSoundData_member_torque(&PropSoundData::torque, "torque");
static ::dueca::CommObjectMemberAccess
  <PropSoundData,dueca::fixvector<2,bool> >
  PropSoundData_member_power(&PropSoundData::power, "power");
static ::dueca::CommObjectMemberAccess
  <PropSoundData,float >
  PropSoundData_member_tas(&PropSoundData::tas, "tas");
static ::dueca::CommObjectMemberAccess
  <PropSoundData,int >
  PropSoundData_member_sounds(&PropSoundData::sounds, "sounds");

// assemble the above entries into a table in the order in which they
// appear in the PropSoundData object
static const ::dueca::CommObjectDataTable entriestable[] = {
  { &PropSoundData_member_rpm },
  { &PropSoundData_member_torque },
  { &PropSoundData_member_power },
  { &PropSoundData_member_tas },
  { &PropSoundData_member_sounds },
  { NULL }
};

#endif

// class name, static
const char * const PropSoundData::classname = "PropSoundData";

// magic number, hashed from class name and member names / classes
const uint32_t PropSoundData::magic_check_number=0xb22bef74;

#if !defined(__DCO_STANDALONE)
// functor table, provides access to user-defined metafunctions through the
// data class registry
static dueca::functortable_type functortable;

// register this class, provides access to a packing/unpacking object,
// and to the member access tables
static ::dueca::DataClassRegistrar registrar
  (PropSoundData::classname, NULL,
   entriestable, &functortable,
   new ::dueca::DataSetSubsidiary<PropSoundData>());

#endif

#ifndef __CUSTOM_DEFAULT_CONSTRUCTOR
PropSoundData::PropSoundData():
    sounds(0)
{
  DOBS("default constructor PropSoundData");
}
#endif

#ifndef __CUSTOM_FULL_CONSTRUCTOR
PropSoundData::PropSoundData(
        const dueca::fixvector<2,float>& rpm,
        const dueca::fixvector<2,float>& torque,
        const dueca::fixvector<2,bool>& power,
        const float& tas,
        const int& sounds) :
    rpm(rpm),
    torque(torque),
    power(power),
    tas(tas),
    sounds(sounds)
{
  DOBS("complete constructor PropSoundData");
}
#endif

#ifndef __CUSTOM_FULLSINGLES_CONSTRUCTOR
PropSoundData::PropSoundData(
        const float& tas,
        const int& sounds) :
    tas(tas),
    sounds(sounds)
{
  DOBS("complete single argument constructor PropSoundData");
}
#endif

#ifndef __CUSTOM_COPY_CONSTRUCTOR
PropSoundData::PropSoundData(const PropSoundData& other):
    rpm(other.rpm),
    torque(other.torque),
    power(other.power),
    tas(other.tas),
    sounds(other.sounds)
{
  DOBS("copy constructor PropSoundData");
}
#endif

#if !defined(__CUSTOM_AMORPHRESTORE_CONSTRUCTOR) && !defined(__DCO_NOPACK)
PropSoundData::PropSoundData(dueca::AmorphReStore& s):
        tas(s),
        sounds(s)
{
  ::dueca::unpackiterable(s, this->rpm,
                          dueca::pack_traits<dueca::fixvector<2,float> >()); 
  ::dueca::unpackiterable(s, this->torque,
                          dueca::pack_traits<dueca::fixvector<2,float> >()); 
  ::dueca::unpackiterable(s, this->power,
                          dueca::pack_traits<dueca::fixvector<2,bool> >()); 
  DOBS("amorph constructor PropSoundData");
}
#endif

#if !defined(__CUSTOM_ARRAY_SIZE_INIT_CONSTRUCTOR)
#endif

#ifndef __CUSTOM_DESTRUCTOR
PropSoundData::~PropSoundData()
{
  DOBS("destructor PropSoundData");
}
#endif

#if !defined(__DCO_STANDALONE)
void* PropSoundData::operator new(size_t size)
{
  DOBS("operator new PropSoundData");
  static ::dueca::Arena* my_arena = arena_pool.findArena
    (sizeof(PropSoundData));
  return my_arena->alloc(size);
}

void PropSoundData::operator delete(void* v)
{
  DOBS("operator delete PropSoundData");
  static ::dueca::Arena* my_arena = arena_pool.findArena
    (sizeof(PropSoundData));
  my_arena->free(v);
}
#endif

#if !defined(__CUSTOM_FUNCTION_PACKDATADIFF) && !defined(__DCO_NOPACK)
void PropSoundData::packDataDiff(::dueca::AmorphStore& s, const PropSoundData& ref) const
{
  DOBS("packDataDiff PropSoundData");
  ::dueca::IndexMemory im;
  ::dueca::checkandpackdiffiterable(this->rpm, ref.rpm, s, im,
                          dueca::diffpack_traits<dueca::fixvector<2,float> >());
  ::dueca::checkandpackdiffiterable(this->torque, ref.torque, s, im,
                          dueca::diffpack_traits<dueca::fixvector<2,float> >());
  ::dueca::checkandpackdiffiterable(this->power, ref.power, s, im,
                          dueca::diffpack_traits<dueca::fixvector<2,bool> >());
  ::dueca::checkandpackdiffsingle(this->tas, ref.tas,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->sounds, ref.sounds,
                         s, im);
  im.closeoff(s);
}
#endif

#if !defined(__CUSTOM_FUNCTION_UNPACKDATA) && !defined(__DCO_NOPACK)
void PropSoundData::unPackData(::dueca::AmorphReStore& s)
{
  DOBS("unPackData PropSoundData");

  ::unPackData(s, this->tas);
  ::unPackData(s, this->sounds);

  ::dueca::unpackiterable(s, this->rpm,
                          dueca::pack_traits<dueca::fixvector<2,float> >()); 
  ::dueca::unpackiterable(s, this->torque,
                          dueca::pack_traits<dueca::fixvector<2,float> >()); 
  ::dueca::unpackiterable(s, this->power,
                          dueca::pack_traits<dueca::fixvector<2,bool> >()); 
}
#endif

#if !defined(__CUSTOM_FUNCTION_UNPACKDATADIFF) && !defined(__DCO_NOPACK)
void PropSoundData::unPackDataDiff(dueca::AmorphReStore& s)
{
  DOBS("unPackDataDiff PropSoundData");
  ::dueca::IndexRecall im;
  ::dueca::checkandunpackdiffiterable(this->rpm, s, im,
                          dueca::diffpack_traits<dueca::fixvector<2,float> >());
  ::dueca::checkandunpackdiffiterable(this->torque, s, im,
                          dueca::diffpack_traits<dueca::fixvector<2,float> >());
  ::dueca::checkandunpackdiffiterable(this->power, s, im,
                          dueca::diffpack_traits<dueca::fixvector<2,bool> >());
  ::dueca::checkandunpackdiffsingle(this->tas, s, im);
  ::dueca::checkandunpackdiffsingle(this->sounds, s, im);
}
#endif

#ifndef __CUSTOM_OPERATOR_EQUAL
bool PropSoundData::operator == (const PropSoundData& other) const
{
  DOBS("operator == PropSoundData");
  if (this->rpm != other.rpm) return false;
  if (this->torque != other.torque) return false;
  if (this->power != other.power) return false;
  if (this->tas != other.tas) return false;
  if (this->sounds != other.sounds) return false;
  return true;
}
#endif

#ifndef __CUSTOM_OPERATOR_ASSIGN
PropSoundData&
PropSoundData::operator=(const PropSoundData& other)
{
  DOBS("operator = PropSoundData");
  if (this == &other) return *this;
  this->rpm = other.rpm;
  this->torque = other.torque;
  this->power = other.power;
  this->tas = other.tas;
  this->sounds = other.sounds;
  return *this;
}
#endif

#if !defined(__CUSTOM_FUNCTION_PACKDATA) && !defined(__DCO_NOPACK)
void PropSoundData::packData(::dueca::AmorphStore& s) const
{
  DOBS("packData PropSoundData");
  ::packData(s, this->tas);
  ::packData(s, this->sounds);
  ::dueca::packiterable(s, this->rpm,
                        dueca::pack_traits<dueca::fixvector<2,float> >()); 
  ::dueca::packiterable(s, this->torque,
                        dueca::pack_traits<dueca::fixvector<2,float> >()); 
  ::dueca::packiterable(s, this->power,
                        dueca::pack_traits<dueca::fixvector<2,bool> >()); 
}
#endif

#ifndef __CUSTOM_FUNCTION_PRINT
std::ostream & PropSoundData::print(std::ostream& s) const
{
  s << "PropSoundData("
    << "rpm={";
  for (dueca::fixvector<2,float>::const_iterator ii = this->rpm.begin();
       ii != this->rpm.end(); ii++) {
    if (ii != this->rpm.begin()) s << ',';
    s << (*ii);
  }
  s << "},"
    << "torque={";
  for (dueca::fixvector<2,float>::const_iterator ii = this->torque.begin();
       ii != this->torque.end(); ii++) {
    if (ii != this->torque.begin()) s << ',';
    s << (*ii);
  }
  s << "},"
    << "power={";
  for (dueca::fixvector<2,bool>::const_iterator ii = this->power.begin();
       ii != this->power.end(); ii++) {
    if (ii != this->power.begin()) s << ',';
    s << (*ii);
  }
  s << "},"
    << "tas=" << this->tas << ','
    << "sounds=" << this->sounds
    << ')';
  return s;
}
#endif


