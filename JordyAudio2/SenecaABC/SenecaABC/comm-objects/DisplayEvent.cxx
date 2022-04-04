/* ------------------------------------------------------------------ */
/*      item            : DisplayEvent.cxx
        generated by    : matteo (matteo)
        date            : Thu 24 Mar 2022
        category        : body file
        description     : DUECA Communication Object (DCO),
                          automatically generated by dueca-codegen
        codegen version : 110
        language        : C++
*/

#include "DisplayEvent.hxx"
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
// to the members of a DisplayEvent object
static ::dueca::CommObjectMemberAccess
  <DisplayEvent,int >
  DisplayEvent_member_id(&DisplayEvent::id, "id");
static ::dueca::CommObjectMemberAccess
  <DisplayEvent,bool >
  DisplayEvent_member_frozen_h(&DisplayEvent::frozen_h, "frozen_h");
static ::dueca::CommObjectMemberAccess
  <DisplayEvent,bool >
  DisplayEvent_member_frozen_v(&DisplayEvent::frozen_v, "frozen_v");
static ::dueca::CommObjectMemberAccess
  <DisplayEvent,float >
  DisplayEvent_member_offset_h_value(&DisplayEvent::offset_h_value, "offset_h_value");
static ::dueca::CommObjectMemberAccess
  <DisplayEvent,float >
  DisplayEvent_member_offset_h_time(&DisplayEvent::offset_h_time, "offset_h_time");
static ::dueca::CommObjectMemberAccess
  <DisplayEvent,float >
  DisplayEvent_member_offset_v_value(&DisplayEvent::offset_v_value, "offset_v_value");
static ::dueca::CommObjectMemberAccess
  <DisplayEvent,float >
  DisplayEvent_member_offset_v_time(&DisplayEvent::offset_v_time, "offset_v_time");
static ::dueca::CommObjectMemberAccess
  <DisplayEvent,float >
  DisplayEvent_member_offset_phi(&DisplayEvent::offset_phi, "offset_phi");
static ::dueca::CommObjectMemberAccess
  <DisplayEvent,float >
  DisplayEvent_member_offset_theta(&DisplayEvent::offset_theta, "offset_theta");
static ::dueca::CommObjectMemberAccess
  <DisplayEvent,float >
  DisplayEvent_member_offset_psi(&DisplayEvent::offset_psi, "offset_psi");

// assemble the above entries into a table in the order in which they
// appear in the DisplayEvent object
static const ::dueca::CommObjectDataTable entriestable[] = {
  { &DisplayEvent_member_id },
  { &DisplayEvent_member_frozen_h },
  { &DisplayEvent_member_frozen_v },
  { &DisplayEvent_member_offset_h_value },
  { &DisplayEvent_member_offset_h_time },
  { &DisplayEvent_member_offset_v_value },
  { &DisplayEvent_member_offset_v_time },
  { &DisplayEvent_member_offset_phi },
  { &DisplayEvent_member_offset_theta },
  { &DisplayEvent_member_offset_psi },
  { NULL }
};

#endif

// class name, static
const char * const DisplayEvent::classname = "DisplayEvent";

// magic number, hashed from class name and member names / classes
const uint32_t DisplayEvent::magic_check_number=0x4e06b82a;

#if !defined(__DCO_STANDALONE)
// functor table, provides access to user-defined metafunctions through the
// data class registry
static dueca::functortable_type functortable;

// register this class, provides access to a packing/unpacking object,
// and to the member access tables
static ::dueca::DataClassRegistrar registrar
  (DisplayEvent::classname, NULL,
   entriestable, &functortable,
   new ::dueca::DataSetSubsidiary<DisplayEvent>());

#endif

#ifndef __CUSTOM_DEFAULT_CONSTRUCTOR
DisplayEvent::DisplayEvent():
    id(0),
    frozen_h(false),
    frozen_v(false),
    offset_h_value(0.0f),
    offset_h_time(0.0f),
    offset_v_value(0.0f),
    offset_v_time(0.0f),
    offset_phi(0.0f),
    offset_theta(0.0f),
    offset_psi(0.0f)
{
  DOBS("default constructor DisplayEvent");
}
#endif

#ifndef __CUSTOM_FULL_CONSTRUCTOR
DisplayEvent::DisplayEvent(
        const int& id,
        const bool& frozen_h,
        const bool& frozen_v,
        const float& offset_h_value,
        const float& offset_h_time,
        const float& offset_v_value,
        const float& offset_v_time,
        const float& offset_phi,
        const float& offset_theta,
        const float& offset_psi) :
    id(id),
    frozen_h(frozen_h),
    frozen_v(frozen_v),
    offset_h_value(offset_h_value),
    offset_h_time(offset_h_time),
    offset_v_value(offset_v_value),
    offset_v_time(offset_v_time),
    offset_phi(offset_phi),
    offset_theta(offset_theta),
    offset_psi(offset_psi)
{
  DOBS("complete constructor DisplayEvent");
}
#endif

#ifndef __CUSTOM_FULLSINGLES_CONSTRUCTOR
#endif

#ifndef __CUSTOM_COPY_CONSTRUCTOR
DisplayEvent::DisplayEvent(const DisplayEvent& other):
    id(other.id),
    frozen_h(other.frozen_h),
    frozen_v(other.frozen_v),
    offset_h_value(other.offset_h_value),
    offset_h_time(other.offset_h_time),
    offset_v_value(other.offset_v_value),
    offset_v_time(other.offset_v_time),
    offset_phi(other.offset_phi),
    offset_theta(other.offset_theta),
    offset_psi(other.offset_psi)
{
  DOBS("copy constructor DisplayEvent");
}
#endif

#if !defined(__CUSTOM_AMORPHRESTORE_CONSTRUCTOR) && !defined(__DCO_NOPACK)
DisplayEvent::DisplayEvent(dueca::AmorphReStore& s):
        id(s),
        frozen_h(s),
        frozen_v(s),
        offset_h_value(s),
        offset_h_time(s),
        offset_v_value(s),
        offset_v_time(s),
        offset_phi(s),
        offset_theta(s),
        offset_psi(s)
{
  DOBS("amorph constructor DisplayEvent");
}
#endif

#if !defined(__CUSTOM_ARRAY_SIZE_INIT_CONSTRUCTOR)
#endif

#ifndef __CUSTOM_DESTRUCTOR
DisplayEvent::~DisplayEvent()
{
  DOBS("destructor DisplayEvent");
}
#endif

#if !defined(__DCO_STANDALONE)
void* DisplayEvent::operator new(size_t size)
{
  DOBS("operator new DisplayEvent");
  static ::dueca::Arena* my_arena = arena_pool.findArena
    (sizeof(DisplayEvent));
  return my_arena->alloc(size);
}

void DisplayEvent::operator delete(void* v)
{
  DOBS("operator delete DisplayEvent");
  static ::dueca::Arena* my_arena = arena_pool.findArena
    (sizeof(DisplayEvent));
  my_arena->free(v);
}
#endif

#if !defined(__CUSTOM_FUNCTION_PACKDATADIFF) && !defined(__DCO_NOPACK)
void DisplayEvent::packDataDiff(::dueca::AmorphStore& s, const DisplayEvent& ref) const
{
  DOBS("packDataDiff DisplayEvent");
  ::dueca::IndexMemory im;
  ::dueca::checkandpackdiffsingle(this->id, ref.id,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->frozen_h, ref.frozen_h,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->frozen_v, ref.frozen_v,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->offset_h_value, ref.offset_h_value,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->offset_h_time, ref.offset_h_time,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->offset_v_value, ref.offset_v_value,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->offset_v_time, ref.offset_v_time,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->offset_phi, ref.offset_phi,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->offset_theta, ref.offset_theta,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->offset_psi, ref.offset_psi,
                         s, im);
  im.closeoff(s);
}
#endif

#if !defined(__CUSTOM_FUNCTION_UNPACKDATA) && !defined(__DCO_NOPACK)
void DisplayEvent::unPackData(::dueca::AmorphReStore& s)
{
  DOBS("unPackData DisplayEvent");

  ::unPackData(s, this->id);
  ::unPackData(s, this->frozen_h);
  ::unPackData(s, this->frozen_v);
  ::unPackData(s, this->offset_h_value);
  ::unPackData(s, this->offset_h_time);
  ::unPackData(s, this->offset_v_value);
  ::unPackData(s, this->offset_v_time);
  ::unPackData(s, this->offset_phi);
  ::unPackData(s, this->offset_theta);
  ::unPackData(s, this->offset_psi);

}
#endif

#if !defined(__CUSTOM_FUNCTION_UNPACKDATADIFF) && !defined(__DCO_NOPACK)
void DisplayEvent::unPackDataDiff(dueca::AmorphReStore& s)
{
  DOBS("unPackDataDiff DisplayEvent");
  ::dueca::IndexRecall im;
  ::dueca::checkandunpackdiffsingle(this->id, s, im);
  ::dueca::checkandunpackdiffsingle(this->frozen_h, s, im);
  ::dueca::checkandunpackdiffsingle(this->frozen_v, s, im);
  ::dueca::checkandunpackdiffsingle(this->offset_h_value, s, im);
  ::dueca::checkandunpackdiffsingle(this->offset_h_time, s, im);
  ::dueca::checkandunpackdiffsingle(this->offset_v_value, s, im);
  ::dueca::checkandunpackdiffsingle(this->offset_v_time, s, im);
  ::dueca::checkandunpackdiffsingle(this->offset_phi, s, im);
  ::dueca::checkandunpackdiffsingle(this->offset_theta, s, im);
  ::dueca::checkandunpackdiffsingle(this->offset_psi, s, im);
}
#endif

#ifndef __CUSTOM_OPERATOR_EQUAL
bool DisplayEvent::operator == (const DisplayEvent& other) const
{
  DOBS("operator == DisplayEvent");
  if (this->id != other.id) return false;
  if (this->frozen_h != other.frozen_h) return false;
  if (this->frozen_v != other.frozen_v) return false;
  if (this->offset_h_value != other.offset_h_value) return false;
  if (this->offset_h_time != other.offset_h_time) return false;
  if (this->offset_v_value != other.offset_v_value) return false;
  if (this->offset_v_time != other.offset_v_time) return false;
  if (this->offset_phi != other.offset_phi) return false;
  if (this->offset_theta != other.offset_theta) return false;
  if (this->offset_psi != other.offset_psi) return false;
  return true;
}
#endif

#ifndef __CUSTOM_OPERATOR_ASSIGN
DisplayEvent&
DisplayEvent::operator=(const DisplayEvent& other)
{
  DOBS("operator = DisplayEvent");
  if (this == &other) return *this;
  this->id = other.id;
  this->frozen_h = other.frozen_h;
  this->frozen_v = other.frozen_v;
  this->offset_h_value = other.offset_h_value;
  this->offset_h_time = other.offset_h_time;
  this->offset_v_value = other.offset_v_value;
  this->offset_v_time = other.offset_v_time;
  this->offset_phi = other.offset_phi;
  this->offset_theta = other.offset_theta;
  this->offset_psi = other.offset_psi;
  return *this;
}
#endif

#if !defined(__CUSTOM_FUNCTION_PACKDATA) && !defined(__DCO_NOPACK)
void DisplayEvent::packData(::dueca::AmorphStore& s) const
{
  DOBS("packData DisplayEvent");
  ::packData(s, this->id);
  ::packData(s, this->frozen_h);
  ::packData(s, this->frozen_v);
  ::packData(s, this->offset_h_value);
  ::packData(s, this->offset_h_time);
  ::packData(s, this->offset_v_value);
  ::packData(s, this->offset_v_time);
  ::packData(s, this->offset_phi);
  ::packData(s, this->offset_theta);
  ::packData(s, this->offset_psi);
}
#endif

#ifndef __CUSTOM_FUNCTION_PRINT
std::ostream & DisplayEvent::print(std::ostream& s) const
{
  s << "DisplayEvent("
    << "id=" << this->id << ','
    << "frozen_h=" << this->frozen_h << ','
    << "frozen_v=" << this->frozen_v << ','
    << "offset_h_value=" << this->offset_h_value << ','
    << "offset_h_time=" << this->offset_h_time << ','
    << "offset_v_value=" << this->offset_v_value << ','
    << "offset_v_time=" << this->offset_v_time << ','
    << "offset_phi=" << this->offset_phi << ','
    << "offset_theta=" << this->offset_theta << ','
    << "offset_psi=" << this->offset_psi
    << ')';
  return s;
}
#endif

