/* ------------------------------------------------------------------ */
/*      item            : NavData.cxx
        generated by    : matteo (matteo)
        date            : Wed 15 Dec 2021
        category        : body file
        description     : DUECA Communication Object (DCO),
                          automatically generated by dueca-codegen
        codegen version : 110
        language        : C++
*/

#include "NavData.hxx"
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
// to the members of a NavData object
static ::dueca::CommObjectMemberAccess
  <NavData,float >
  NavData_member_ils_loc_dev(&NavData::ils_loc_dev, "ils_loc_dev");
static ::dueca::CommObjectMemberAccess
  <NavData,float >
  NavData_member_ils_gs_dev(&NavData::ils_gs_dev, "ils_gs_dev");
static ::dueca::CommObjectMemberAccess
  <NavData,float >
  NavData_member_course_dev(&NavData::course_dev, "course_dev");
static ::dueca::CommObjectMemberAccess
  <NavData,float >
  NavData_member_course_ref(&NavData::course_ref, "course_ref");
static ::dueca::CommObjectMemberAccess
  <NavData,NavData::to_from >
  NavData_member_direction(&NavData::direction, "direction");
static ::dueca::CommObjectMemberAccess
  <NavData,float >
  NavData_member_heading_ref(&NavData::heading_ref, "heading_ref");
static ::dueca::CommObjectMemberAccess
  <NavData,float >
  NavData_member_speed_ref(&NavData::speed_ref, "speed_ref");
static ::dueca::CommObjectMemberAccess
  <NavData,float >
  NavData_member_alt_ref(&NavData::alt_ref, "alt_ref");
static ::dueca::CommObjectMemberAccess
  <NavData,float >
  NavData_member_distance(&NavData::distance, "distance");
static ::dueca::CommObjectMemberAccess
  <NavData,float >
  NavData_member_time2go(&NavData::time2go, "time2go");
static ::dueca::CommObjectMemberAccess
  <NavData,NavData::efis_modes >
  NavData_member_lateral_mode(&NavData::lateral_mode, "lateral_mode");
static ::dueca::CommObjectMemberAccess
  <NavData,NavData::efis_modes >
  NavData_member_armed_lateral_mode(&NavData::armed_lateral_mode, "armed_lateral_mode");
static ::dueca::CommObjectMemberAccess
  <NavData,NavData::efis_modes >
  NavData_member_vertical_mode(&NavData::vertical_mode, "vertical_mode");
static ::dueca::CommObjectMemberAccess
  <NavData,NavData::efis_modes >
  NavData_member_armed_vertical_mode(&NavData::armed_vertical_mode, "armed_vertical_mode");

// assemble the above entries into a table in the order in which they
// appear in the NavData object
static const ::dueca::CommObjectDataTable entriestable[] = {
  { &NavData_member_ils_loc_dev },
  { &NavData_member_ils_gs_dev },
  { &NavData_member_course_dev },
  { &NavData_member_course_ref },
  { &NavData_member_direction },
  { &NavData_member_heading_ref },
  { &NavData_member_speed_ref },
  { &NavData_member_alt_ref },
  { &NavData_member_distance },
  { &NavData_member_time2go },
  { &NavData_member_lateral_mode },
  { &NavData_member_armed_lateral_mode },
  { &NavData_member_vertical_mode },
  { &NavData_member_armed_vertical_mode },
  { NULL }
};

#endif

// class name, static
const char * const NavData::classname = "NavData";

// magic number, hashed from class name and member names / classes
const uint32_t NavData::magic_check_number=0x710349ec;

#if !defined(__DCO_STANDALONE)
// functor table, provides access to user-defined metafunctions through the
// data class registry
static dueca::functortable_type functortable;

// register this class, provides access to a packing/unpacking object,
// and to the member access tables
static ::dueca::DataClassRegistrar registrar
  (NavData::classname, NULL,
   entriestable, &functortable,
   new ::dueca::DataSetSubsidiary<NavData>());

#endif

#ifndef __CUSTOM_DEFAULT_CONSTRUCTOR
NavData::NavData()
{
  DOBS("default constructor NavData");
}
#endif

#ifndef __CUSTOM_FULL_CONSTRUCTOR
NavData::NavData(
        const float& ils_loc_dev,
        const float& ils_gs_dev,
        const float& course_dev,
        const float& course_ref,
        const to_from& direction,
        const float& heading_ref,
        const float& speed_ref,
        const float& alt_ref,
        const float& distance,
        const float& time2go,
        const efis_modes& lateral_mode,
        const efis_modes& armed_lateral_mode,
        const efis_modes& vertical_mode,
        const efis_modes& armed_vertical_mode) :
    ils_loc_dev(ils_loc_dev),
    ils_gs_dev(ils_gs_dev),
    course_dev(course_dev),
    course_ref(course_ref),
    direction(direction),
    heading_ref(heading_ref),
    speed_ref(speed_ref),
    alt_ref(alt_ref),
    distance(distance),
    time2go(time2go),
    lateral_mode(lateral_mode),
    armed_lateral_mode(armed_lateral_mode),
    vertical_mode(vertical_mode),
    armed_vertical_mode(armed_vertical_mode)
{
  DOBS("complete constructor NavData");
}
#endif

#ifndef __CUSTOM_FULLSINGLES_CONSTRUCTOR
#endif

#ifndef __CUSTOM_COPY_CONSTRUCTOR
NavData::NavData(const NavData& other):
    ils_loc_dev(other.ils_loc_dev),
    ils_gs_dev(other.ils_gs_dev),
    course_dev(other.course_dev),
    course_ref(other.course_ref),
    direction(other.direction),
    heading_ref(other.heading_ref),
    speed_ref(other.speed_ref),
    alt_ref(other.alt_ref),
    distance(other.distance),
    time2go(other.time2go),
    lateral_mode(other.lateral_mode),
    armed_lateral_mode(other.armed_lateral_mode),
    vertical_mode(other.vertical_mode),
    armed_vertical_mode(other.armed_vertical_mode)
{
  DOBS("copy constructor NavData");
}
#endif

#if !defined(__CUSTOM_AMORPHRESTORE_CONSTRUCTOR) && !defined(__DCO_NOPACK)
NavData::NavData(dueca::AmorphReStore& s):
        ils_loc_dev(s),
        ils_gs_dev(s),
        course_dev(s),
        course_ref(s),
        direction(to_from(uint8_t(s))),
        heading_ref(s),
        speed_ref(s),
        alt_ref(s),
        distance(s),
        time2go(s),
        lateral_mode(efis_modes(uint8_t(s))),
        armed_lateral_mode(efis_modes(uint8_t(s))),
        vertical_mode(efis_modes(uint8_t(s))),
        armed_vertical_mode(efis_modes(uint8_t(s)))
{
  DOBS("amorph constructor NavData");
}
#endif

#if !defined(__CUSTOM_ARRAY_SIZE_INIT_CONSTRUCTOR)
#endif

#ifndef __CUSTOM_DESTRUCTOR
NavData::~NavData()
{
  DOBS("destructor NavData");
}
#endif

#if !defined(__DCO_STANDALONE)
void* NavData::operator new(size_t size)
{
  DOBS("operator new NavData");
  static ::dueca::Arena* my_arena = arena_pool.findArena
    (sizeof(NavData));
  return my_arena->alloc(size);
}

void NavData::operator delete(void* v)
{
  DOBS("operator delete NavData");
  static ::dueca::Arena* my_arena = arena_pool.findArena
    (sizeof(NavData));
  my_arena->free(v);
}
#endif

#if !defined(__CUSTOM_FUNCTION_PACKDATADIFF) && !defined(__DCO_NOPACK)
void NavData::packDataDiff(::dueca::AmorphStore& s, const NavData& ref) const
{
  DOBS("packDataDiff NavData");
  ::dueca::IndexMemory im;
  ::dueca::checkandpackdiffsingle(this->ils_loc_dev, ref.ils_loc_dev,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->ils_gs_dev, ref.ils_gs_dev,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->course_dev, ref.course_dev,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->course_ref, ref.course_ref,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->direction, ref.direction,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->heading_ref, ref.heading_ref,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->speed_ref, ref.speed_ref,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->alt_ref, ref.alt_ref,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->distance, ref.distance,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->time2go, ref.time2go,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->lateral_mode, ref.lateral_mode,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->armed_lateral_mode, ref.armed_lateral_mode,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->vertical_mode, ref.vertical_mode,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->armed_vertical_mode, ref.armed_vertical_mode,
                         s, im);
  im.closeoff(s);
}
#endif

#if !defined(__CUSTOM_FUNCTION_UNPACKDATA) && !defined(__DCO_NOPACK)
void NavData::unPackData(::dueca::AmorphReStore& s)
{
  DOBS("unPackData NavData");

  ::unPackData(s, this->ils_loc_dev);
  ::unPackData(s, this->ils_gs_dev);
  ::unPackData(s, this->course_dev);
  ::unPackData(s, this->course_ref);
  ::unPackData(s, this->direction);
  ::unPackData(s, this->heading_ref);
  ::unPackData(s, this->speed_ref);
  ::unPackData(s, this->alt_ref);
  ::unPackData(s, this->distance);
  ::unPackData(s, this->time2go);
  ::unPackData(s, this->lateral_mode);
  ::unPackData(s, this->armed_lateral_mode);
  ::unPackData(s, this->vertical_mode);
  ::unPackData(s, this->armed_vertical_mode);

}
#endif

#if !defined(__CUSTOM_FUNCTION_UNPACKDATADIFF) && !defined(__DCO_NOPACK)
void NavData::unPackDataDiff(dueca::AmorphReStore& s)
{
  DOBS("unPackDataDiff NavData");
  ::dueca::IndexRecall im;
  ::dueca::checkandunpackdiffsingle(this->ils_loc_dev, s, im);
  ::dueca::checkandunpackdiffsingle(this->ils_gs_dev, s, im);
  ::dueca::checkandunpackdiffsingle(this->course_dev, s, im);
  ::dueca::checkandunpackdiffsingle(this->course_ref, s, im);
  ::dueca::checkandunpackdiffsingle(this->direction, s, im);
  ::dueca::checkandunpackdiffsingle(this->heading_ref, s, im);
  ::dueca::checkandunpackdiffsingle(this->speed_ref, s, im);
  ::dueca::checkandunpackdiffsingle(this->alt_ref, s, im);
  ::dueca::checkandunpackdiffsingle(this->distance, s, im);
  ::dueca::checkandunpackdiffsingle(this->time2go, s, im);
  ::dueca::checkandunpackdiffsingle(this->lateral_mode, s, im);
  ::dueca::checkandunpackdiffsingle(this->armed_lateral_mode, s, im);
  ::dueca::checkandunpackdiffsingle(this->vertical_mode, s, im);
  ::dueca::checkandunpackdiffsingle(this->armed_vertical_mode, s, im);
}
#endif

#ifndef __CUSTOM_OPERATOR_EQUAL
bool NavData::operator == (const NavData& other) const
{
  DOBS("operator == NavData");
  if (this->ils_loc_dev != other.ils_loc_dev) return false;
  if (this->ils_gs_dev != other.ils_gs_dev) return false;
  if (this->course_dev != other.course_dev) return false;
  if (this->course_ref != other.course_ref) return false;
  if (this->direction != other.direction) return false;
  if (this->heading_ref != other.heading_ref) return false;
  if (this->speed_ref != other.speed_ref) return false;
  if (this->alt_ref != other.alt_ref) return false;
  if (this->distance != other.distance) return false;
  if (this->time2go != other.time2go) return false;
  if (this->lateral_mode != other.lateral_mode) return false;
  if (this->armed_lateral_mode != other.armed_lateral_mode) return false;
  if (this->vertical_mode != other.vertical_mode) return false;
  if (this->armed_vertical_mode != other.armed_vertical_mode) return false;
  return true;
}
#endif

#ifndef __CUSTOM_OPERATOR_ASSIGN
NavData&
NavData::operator=(const NavData& other)
{
  DOBS("operator = NavData");
  if (this == &other) return *this;
  this->ils_loc_dev = other.ils_loc_dev;
  this->ils_gs_dev = other.ils_gs_dev;
  this->course_dev = other.course_dev;
  this->course_ref = other.course_ref;
  this->direction = other.direction;
  this->heading_ref = other.heading_ref;
  this->speed_ref = other.speed_ref;
  this->alt_ref = other.alt_ref;
  this->distance = other.distance;
  this->time2go = other.time2go;
  this->lateral_mode = other.lateral_mode;
  this->armed_lateral_mode = other.armed_lateral_mode;
  this->vertical_mode = other.vertical_mode;
  this->armed_vertical_mode = other.armed_vertical_mode;
  return *this;
}
#endif

#if !defined(__CUSTOM_FUNCTION_PACKDATA) && !defined(__DCO_NOPACK)
void NavData::packData(::dueca::AmorphStore& s) const
{
  DOBS("packData NavData");
  ::packData(s, this->ils_loc_dev);
  ::packData(s, this->ils_gs_dev);
  ::packData(s, this->course_dev);
  ::packData(s, this->course_ref);
  ::packData(s, this->direction);
  ::packData(s, this->heading_ref);
  ::packData(s, this->speed_ref);
  ::packData(s, this->alt_ref);
  ::packData(s, this->distance);
  ::packData(s, this->time2go);
  ::packData(s, this->lateral_mode);
  ::packData(s, this->armed_lateral_mode);
  ::packData(s, this->vertical_mode);
  ::packData(s, this->armed_vertical_mode);
}
#endif

#ifndef __CUSTOM_FUNCTION_PRINT
std::ostream & NavData::print(std::ostream& s) const
{
  s << "NavData("
    << "ils_loc_dev=" << this->ils_loc_dev << ','
    << "ils_gs_dev=" << this->ils_gs_dev << ','
    << "course_dev=" << this->course_dev << ','
    << "course_ref=" << this->course_ref << ','
    << "direction=" << this->direction << ','
    << "heading_ref=" << this->heading_ref << ','
    << "speed_ref=" << this->speed_ref << ','
    << "alt_ref=" << this->alt_ref << ','
    << "distance=" << this->distance << ','
    << "time2go=" << this->time2go << ','
    << "lateral_mode=" << this->lateral_mode << ','
    << "armed_lateral_mode=" << this->armed_lateral_mode << ','
    << "vertical_mode=" << this->vertical_mode << ','
    << "armed_vertical_mode=" << this->armed_vertical_mode
    << ')';
  return s;
}
#endif


            #ifndef __CUSTOM_GETSTRING_to_from
const char* const getString(const NavData::to_from &o)
{
  static const char* to_from_names[] = {
    "NODIR",
    "TO",
    "FROM"};

  return to_from_names[int(o)];
}
#endif

#ifndef __CUSTOM_READFROMSTRING_to_from
void readFromString(NavData::to_from &o, const std::string& s)
{
  for (int ii = 3; ii--; ) {
    if (std::string(getString(NavData::to_from(ii))) == s) {
      o = NavData::to_from(ii);
      return;
    }
  }
  throw(dueca::ConversionNotDefined());
}
#endif

#if !defined(__CUSTOM_PACKDATA_to_from) && !defined(__DCO_NOPACK)
void packData(::dueca::AmorphStore& s,
              const NavData::to_from &o)
{ packData(s, uint8_t(o));}
#endif

#if !defined(__CUSTOM_UNPACKDATA_to_from) && !defined(__DCO_NOPACK)
void unPackData(::dueca::AmorphReStore& s,
                NavData::to_from &o)
{ uint8_t tmp(s); o = NavData::to_from(tmp); }
#endif

namespace dueca {;
template <>
const char* getclassname<NavData::to_from>()
{ return "NavData::to_from"; }
};

            #ifndef __CUSTOM_GETSTRING_efis_modes
const char* const getString(const NavData::efis_modes &o)
{
  static const char* efis_modes_names[] = {
    "NONE",
    "HDG",
    "LNAV",
    "LOC",
    "ALT"};

  return efis_modes_names[int(o)];
}
#endif

#ifndef __CUSTOM_READFROMSTRING_efis_modes
void readFromString(NavData::efis_modes &o, const std::string& s)
{
  for (int ii = 5; ii--; ) {
    if (std::string(getString(NavData::efis_modes(ii))) == s) {
      o = NavData::efis_modes(ii);
      return;
    }
  }
  throw(dueca::ConversionNotDefined());
}
#endif

#if !defined(__CUSTOM_PACKDATA_efis_modes) && !defined(__DCO_NOPACK)
void packData(::dueca::AmorphStore& s,
              const NavData::efis_modes &o)
{ packData(s, uint8_t(o));}
#endif

#if !defined(__CUSTOM_UNPACKDATA_efis_modes) && !defined(__DCO_NOPACK)
void unPackData(::dueca::AmorphReStore& s,
                NavData::efis_modes &o)
{ uint8_t tmp(s); o = NavData::efis_modes(tmp); }
#endif

namespace dueca {;
template <>
const char* getclassname<NavData::efis_modes>()
{ return "NavData::efis_modes"; }
};

