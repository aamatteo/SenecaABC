/* ------------------------------------------------------------------ */
/*      item            : MotionBaseResultData.cxx
        generated by    : matteo (matteo)
        date            : Wed 15 Dec 2021
        category        : body file
        description     : DUECA Communication Object (DCO),
                          automatically generated by dueca-codegen
        codegen version : 110
        language        : C++
*/

#include "MotionBaseResultData.hxx"
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
// to the members of a MotionBaseResultData object
static ::dueca::CommObjectMemberAccess
  <MotionBaseResultData,uint32_t >
  MotionBaseResultData_member_counter(&MotionBaseResultData::counter, "counter");
static ::dueca::CommObjectMemberAccess
  <MotionBaseResultData,uint32_t >
  MotionBaseResultData_member_status(&MotionBaseResultData::status, "status");
static ::dueca::CommObjectMemberAccess
  <MotionBaseResultData,dueca::fixvector<6,float> >
  MotionBaseResultData_member_actual_pos(&MotionBaseResultData::actual_pos, "actual_pos");
static ::dueca::CommObjectMemberAccess
  <MotionBaseResultData,dueca::fixvector<6,float> >
  MotionBaseResultData_member_actual_len(&MotionBaseResultData::actual_len, "actual_len");

// assemble the above entries into a table in the order in which they
// appear in the MotionBaseResultData object
static const ::dueca::CommObjectDataTable entriestable[] = {
  { &MotionBaseResultData_member_counter },
  { &MotionBaseResultData_member_status },
  { &MotionBaseResultData_member_actual_pos },
  { &MotionBaseResultData_member_actual_len },
  { NULL }
};

#endif

// class name, static
const char * const MotionBaseResultData::classname = "MotionBaseResultData";

// magic number, hashed from class name and member names / classes
const uint32_t MotionBaseResultData::magic_check_number=0x4fd69043;

#if !defined(__DCO_STANDALONE)
// functor table, provides access to user-defined metafunctions through the
// data class registry
static dueca::functortable_type functortable;

// register this class, provides access to a packing/unpacking object,
// and to the member access tables
static ::dueca::DataClassRegistrar registrar
  (MotionBaseResultData::classname, NULL,
   entriestable, &functortable,
   new ::dueca::DataSetSubsidiary<MotionBaseResultData>());

#endif

#ifndef __CUSTOM_DEFAULT_CONSTRUCTOR
MotionBaseResultData::MotionBaseResultData()
{
  DOBS("default constructor MotionBaseResultData");
}
#endif

#ifndef __CUSTOM_FULL_CONSTRUCTOR
MotionBaseResultData::MotionBaseResultData(
        const uint32_t& counter,
        const uint32_t& status,
        const dueca::fixvector<6,float>& actual_pos,
        const dueca::fixvector<6,float>& actual_len) :
    counter(counter),
    status(status),
    actual_pos(actual_pos),
    actual_len(actual_len)
{
  DOBS("complete constructor MotionBaseResultData");
}
#endif

#ifndef __CUSTOM_FULLSINGLES_CONSTRUCTOR
MotionBaseResultData::MotionBaseResultData(
        const uint32_t& counter,
        const uint32_t& status) :
    counter(counter),
    status(status)
{
  DOBS("complete single argument constructor MotionBaseResultData");
}
#endif

#ifndef __CUSTOM_COPY_CONSTRUCTOR
MotionBaseResultData::MotionBaseResultData(const MotionBaseResultData& other):
    counter(other.counter),
    status(other.status),
    actual_pos(other.actual_pos),
    actual_len(other.actual_len)
{
  DOBS("copy constructor MotionBaseResultData");
}
#endif

#if !defined(__CUSTOM_AMORPHRESTORE_CONSTRUCTOR) && !defined(__DCO_NOPACK)
MotionBaseResultData::MotionBaseResultData(dueca::AmorphReStore& s):
        counter(s),
        status(s)
{
  ::dueca::unpackiterable(s, this->actual_pos,
                          dueca::pack_traits<dueca::fixvector<6,float> >()); 
  ::dueca::unpackiterable(s, this->actual_len,
                          dueca::pack_traits<dueca::fixvector<6,float> >()); 
  DOBS("amorph constructor MotionBaseResultData");
}
#endif

#if !defined(__CUSTOM_ARRAY_SIZE_INIT_CONSTRUCTOR)
#endif

#ifndef __CUSTOM_DESTRUCTOR
MotionBaseResultData::~MotionBaseResultData()
{
  DOBS("destructor MotionBaseResultData");
}
#endif

#if !defined(__DCO_STANDALONE)
void* MotionBaseResultData::operator new(size_t size)
{
  DOBS("operator new MotionBaseResultData");
  static ::dueca::Arena* my_arena = arena_pool.findArena
    (sizeof(MotionBaseResultData));
  return my_arena->alloc(size);
}

void MotionBaseResultData::operator delete(void* v)
{
  DOBS("operator delete MotionBaseResultData");
  static ::dueca::Arena* my_arena = arena_pool.findArena
    (sizeof(MotionBaseResultData));
  my_arena->free(v);
}
#endif

#if !defined(__CUSTOM_FUNCTION_PACKDATADIFF) && !defined(__DCO_NOPACK)
void MotionBaseResultData::packDataDiff(::dueca::AmorphStore& s, const MotionBaseResultData& ref) const
{
  DOBS("packDataDiff MotionBaseResultData");
  ::dueca::IndexMemory im;
  ::dueca::checkandpackdiffsingle(this->counter, ref.counter,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->status, ref.status,
                         s, im);
  ::dueca::checkandpackdiffiterable(this->actual_pos, ref.actual_pos, s, im,
                          dueca::diffpack_traits<dueca::fixvector<6,float> >());
  ::dueca::checkandpackdiffiterable(this->actual_len, ref.actual_len, s, im,
                          dueca::diffpack_traits<dueca::fixvector<6,float> >());
  im.closeoff(s);
}
#endif

#if !defined(__CUSTOM_FUNCTION_UNPACKDATA) && !defined(__DCO_NOPACK)
void MotionBaseResultData::unPackData(::dueca::AmorphReStore& s)
{
  DOBS("unPackData MotionBaseResultData");

  ::unPackData(s, this->counter);
  ::unPackData(s, this->status);

  ::dueca::unpackiterable(s, this->actual_pos,
                          dueca::pack_traits<dueca::fixvector<6,float> >()); 
  ::dueca::unpackiterable(s, this->actual_len,
                          dueca::pack_traits<dueca::fixvector<6,float> >()); 
}
#endif

#if !defined(__CUSTOM_FUNCTION_UNPACKDATADIFF) && !defined(__DCO_NOPACK)
void MotionBaseResultData::unPackDataDiff(dueca::AmorphReStore& s)
{
  DOBS("unPackDataDiff MotionBaseResultData");
  ::dueca::IndexRecall im;
  ::dueca::checkandunpackdiffsingle(this->counter, s, im);
  ::dueca::checkandunpackdiffsingle(this->status, s, im);
  ::dueca::checkandunpackdiffiterable(this->actual_pos, s, im,
                          dueca::diffpack_traits<dueca::fixvector<6,float> >());
  ::dueca::checkandunpackdiffiterable(this->actual_len, s, im,
                          dueca::diffpack_traits<dueca::fixvector<6,float> >());
}
#endif

#ifndef __CUSTOM_OPERATOR_EQUAL
bool MotionBaseResultData::operator == (const MotionBaseResultData& other) const
{
  DOBS("operator == MotionBaseResultData");
  if (this->counter != other.counter) return false;
  if (this->status != other.status) return false;
  if (this->actual_pos != other.actual_pos) return false;
  if (this->actual_len != other.actual_len) return false;
  return true;
}
#endif

#ifndef __CUSTOM_OPERATOR_ASSIGN
MotionBaseResultData&
MotionBaseResultData::operator=(const MotionBaseResultData& other)
{
  DOBS("operator = MotionBaseResultData");
  if (this == &other) return *this;
  this->counter = other.counter;
  this->status = other.status;
  this->actual_pos = other.actual_pos;
  this->actual_len = other.actual_len;
  return *this;
}
#endif

#if !defined(__CUSTOM_FUNCTION_PACKDATA) && !defined(__DCO_NOPACK)
void MotionBaseResultData::packData(::dueca::AmorphStore& s) const
{
  DOBS("packData MotionBaseResultData");
  ::packData(s, this->counter);
  ::packData(s, this->status);
  ::dueca::packiterable(s, this->actual_pos,
                        dueca::pack_traits<dueca::fixvector<6,float> >()); 
  ::dueca::packiterable(s, this->actual_len,
                        dueca::pack_traits<dueca::fixvector<6,float> >()); 
}
#endif

#ifndef __CUSTOM_FUNCTION_PRINT
std::ostream & MotionBaseResultData::print(std::ostream& s) const
{
  s << "MotionBaseResultData("
    << "counter=" << this->counter << ','
    << "status=" << this->status << ','
    << "actual_pos={";
  for (dueca::fixvector<6,float>::const_iterator ii = this->actual_pos.begin();
       ii != this->actual_pos.end(); ii++) {
    if (ii != this->actual_pos.begin()) s << ',';
    s << (*ii);
  }
  s << "},"
    << "actual_len={";
  for (dueca::fixvector<6,float>::const_iterator ii = this->actual_len.begin();
       ii != this->actual_len.end(); ii++) {
    if (ii != this->actual_len.begin()) s << ',';
    s << (*ii);
  }
  s << "}"
    << ')';
  return s;
}
#endif


