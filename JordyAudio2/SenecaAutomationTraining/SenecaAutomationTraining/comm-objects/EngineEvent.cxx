/* ------------------------------------------------------------------ */
/*      item            : EngineEvent.cxx
        generated by    : matteo (matteo)
        date            : Wed 15 Dec 2021
        category        : body file
        description     : DUECA Communication Object (DCO),
                          automatically generated by dueca-codegen
        codegen version : 110
        language        : C++
*/

#include "EngineEvent.hxx"
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
// to the members of a EngineEvent object
static ::dueca::CommObjectMemberAccess
  <EngineEvent,int >
  EngineEvent_member_id(&EngineEvent::id, "id");
static ::dueca::CommObjectMemberAccess
  <EngineEvent,float >
  EngineEvent_member_power_left(&EngineEvent::power_left, "power_left");
static ::dueca::CommObjectMemberAccess
  <EngineEvent,float >
  EngineEvent_member_power_right(&EngineEvent::power_right, "power_right");
static ::dueca::CommObjectMemberAccess
  <EngineEvent,float >
  EngineEvent_member_max_rpm_left(&EngineEvent::max_rpm_left, "max_rpm_left");
static ::dueca::CommObjectMemberAccess
  <EngineEvent,float >
  EngineEvent_member_max_rpm_right(&EngineEvent::max_rpm_right, "max_rpm_right");
static ::dueca::CommObjectMemberAccess
  <EngineEvent,float >
  EngineEvent_member_time_left(&EngineEvent::time_left, "time_left");
static ::dueca::CommObjectMemberAccess
  <EngineEvent,float >
  EngineEvent_member_time_right(&EngineEvent::time_right, "time_right");

// assemble the above entries into a table in the order in which they
// appear in the EngineEvent object
static const ::dueca::CommObjectDataTable entriestable[] = {
  { &EngineEvent_member_id },
  { &EngineEvent_member_power_left },
  { &EngineEvent_member_power_right },
  { &EngineEvent_member_max_rpm_left },
  { &EngineEvent_member_max_rpm_right },
  { &EngineEvent_member_time_left },
  { &EngineEvent_member_time_right },
  { NULL }
};

#endif

// class name, static
const char * const EngineEvent::classname = "EngineEvent";

// magic number, hashed from class name and member names / classes
const uint32_t EngineEvent::magic_check_number=0xeff4c5d5;

#if !defined(__DCO_STANDALONE)
// functor table, provides access to user-defined metafunctions through the
// data class registry
static dueca::functortable_type functortable;

// register this class, provides access to a packing/unpacking object,
// and to the member access tables
static ::dueca::DataClassRegistrar registrar
  (EngineEvent::classname, NULL,
   entriestable, &functortable,
   new ::dueca::DataSetSubsidiary<EngineEvent>());

#endif

#ifndef __CUSTOM_DEFAULT_CONSTRUCTOR
EngineEvent::EngineEvent()
{
  DOBS("default constructor EngineEvent");
}
#endif

#ifndef __CUSTOM_FULL_CONSTRUCTOR
EngineEvent::EngineEvent(
        const int& id,
        const float& power_left,
        const float& power_right,
        const float& max_rpm_left,
        const float& max_rpm_right,
        const float& time_left,
        const float& time_right) :
    id(id),
    power_left(power_left),
    power_right(power_right),
    max_rpm_left(max_rpm_left),
    max_rpm_right(max_rpm_right),
    time_left(time_left),
    time_right(time_right)
{
  DOBS("complete constructor EngineEvent");
}
#endif

#ifndef __CUSTOM_FULLSINGLES_CONSTRUCTOR
#endif

#ifndef __CUSTOM_COPY_CONSTRUCTOR
EngineEvent::EngineEvent(const EngineEvent& other):
    id(other.id),
    power_left(other.power_left),
    power_right(other.power_right),
    max_rpm_left(other.max_rpm_left),
    max_rpm_right(other.max_rpm_right),
    time_left(other.time_left),
    time_right(other.time_right)
{
  DOBS("copy constructor EngineEvent");
}
#endif

#if !defined(__CUSTOM_AMORPHRESTORE_CONSTRUCTOR) && !defined(__DCO_NOPACK)
EngineEvent::EngineEvent(dueca::AmorphReStore& s):
        id(s),
        power_left(s),
        power_right(s),
        max_rpm_left(s),
        max_rpm_right(s),
        time_left(s),
        time_right(s)
{
  DOBS("amorph constructor EngineEvent");
}
#endif

#if !defined(__CUSTOM_ARRAY_SIZE_INIT_CONSTRUCTOR)
#endif

#ifndef __CUSTOM_DESTRUCTOR
EngineEvent::~EngineEvent()
{
  DOBS("destructor EngineEvent");
}
#endif

#if !defined(__DCO_STANDALONE)
void* EngineEvent::operator new(size_t size)
{
  DOBS("operator new EngineEvent");
  static ::dueca::Arena* my_arena = arena_pool.findArena
    (sizeof(EngineEvent));
  return my_arena->alloc(size);
}

void EngineEvent::operator delete(void* v)
{
  DOBS("operator delete EngineEvent");
  static ::dueca::Arena* my_arena = arena_pool.findArena
    (sizeof(EngineEvent));
  my_arena->free(v);
}
#endif

#if !defined(__CUSTOM_FUNCTION_PACKDATADIFF) && !defined(__DCO_NOPACK)
void EngineEvent::packDataDiff(::dueca::AmorphStore& s, const EngineEvent& ref) const
{
  DOBS("packDataDiff EngineEvent");
  ::dueca::IndexMemory im;
  ::dueca::checkandpackdiffsingle(this->id, ref.id,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->power_left, ref.power_left,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->power_right, ref.power_right,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->max_rpm_left, ref.max_rpm_left,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->max_rpm_right, ref.max_rpm_right,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->time_left, ref.time_left,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->time_right, ref.time_right,
                         s, im);
  im.closeoff(s);
}
#endif

#if !defined(__CUSTOM_FUNCTION_UNPACKDATA) && !defined(__DCO_NOPACK)
void EngineEvent::unPackData(::dueca::AmorphReStore& s)
{
  DOBS("unPackData EngineEvent");

  ::unPackData(s, this->id);
  ::unPackData(s, this->power_left);
  ::unPackData(s, this->power_right);
  ::unPackData(s, this->max_rpm_left);
  ::unPackData(s, this->max_rpm_right);
  ::unPackData(s, this->time_left);
  ::unPackData(s, this->time_right);

}
#endif

#if !defined(__CUSTOM_FUNCTION_UNPACKDATADIFF) && !defined(__DCO_NOPACK)
void EngineEvent::unPackDataDiff(dueca::AmorphReStore& s)
{
  DOBS("unPackDataDiff EngineEvent");
  ::dueca::IndexRecall im;
  ::dueca::checkandunpackdiffsingle(this->id, s, im);
  ::dueca::checkandunpackdiffsingle(this->power_left, s, im);
  ::dueca::checkandunpackdiffsingle(this->power_right, s, im);
  ::dueca::checkandunpackdiffsingle(this->max_rpm_left, s, im);
  ::dueca::checkandunpackdiffsingle(this->max_rpm_right, s, im);
  ::dueca::checkandunpackdiffsingle(this->time_left, s, im);
  ::dueca::checkandunpackdiffsingle(this->time_right, s, im);
}
#endif

#ifndef __CUSTOM_OPERATOR_EQUAL
bool EngineEvent::operator == (const EngineEvent& other) const
{
  DOBS("operator == EngineEvent");
  if (this->id != other.id) return false;
  if (this->power_left != other.power_left) return false;
  if (this->power_right != other.power_right) return false;
  if (this->max_rpm_left != other.max_rpm_left) return false;
  if (this->max_rpm_right != other.max_rpm_right) return false;
  if (this->time_left != other.time_left) return false;
  if (this->time_right != other.time_right) return false;
  return true;
}
#endif

#ifndef __CUSTOM_OPERATOR_ASSIGN
EngineEvent&
EngineEvent::operator=(const EngineEvent& other)
{
  DOBS("operator = EngineEvent");
  if (this == &other) return *this;
  this->id = other.id;
  this->power_left = other.power_left;
  this->power_right = other.power_right;
  this->max_rpm_left = other.max_rpm_left;
  this->max_rpm_right = other.max_rpm_right;
  this->time_left = other.time_left;
  this->time_right = other.time_right;
  return *this;
}
#endif

#if !defined(__CUSTOM_FUNCTION_PACKDATA) && !defined(__DCO_NOPACK)
void EngineEvent::packData(::dueca::AmorphStore& s) const
{
  DOBS("packData EngineEvent");
  ::packData(s, this->id);
  ::packData(s, this->power_left);
  ::packData(s, this->power_right);
  ::packData(s, this->max_rpm_left);
  ::packData(s, this->max_rpm_right);
  ::packData(s, this->time_left);
  ::packData(s, this->time_right);
}
#endif

#ifndef __CUSTOM_FUNCTION_PRINT
std::ostream & EngineEvent::print(std::ostream& s) const
{
  s << "EngineEvent("
    << "id=" << this->id << ','
    << "power_left=" << this->power_left << ','
    << "power_right=" << this->power_right << ','
    << "max_rpm_left=" << this->max_rpm_left << ','
    << "max_rpm_right=" << this->max_rpm_right << ','
    << "time_left=" << this->time_left << ','
    << "time_right=" << this->time_right
    << ')';
  return s;
}
#endif


