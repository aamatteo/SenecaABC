/* ------------------------------------------------------------------ */
/*      item            : MotionRequest.cxx
        generated by    : matteo (matteo)
        date            : Wed 15 Dec 2021
        category        : body file
        description     : DUECA Communication Object (DCO),
                          automatically generated by dueca-codegen
        codegen version : 110
        language        : C++
*/

#include "MotionRequest.hxx"
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
// to the members of a MotionRequest object
static ::dueca::CommObjectMemberAccess
  <MotionRequest,vstring >
  MotionRequest_member_sender(&MotionRequest::sender, "sender");
static ::dueca::CommObjectMemberAccess
  <MotionRequest,MotionRequest::motion_position >
  MotionRequest_member_position(&MotionRequest::position, "position");

// assemble the above entries into a table in the order in which they
// appear in the MotionRequest object
static const ::dueca::CommObjectDataTable entriestable[] = {
  { &MotionRequest_member_sender },
  { &MotionRequest_member_position },
  { NULL }
};

#endif

// class name, static
const char * const MotionRequest::classname = "MotionRequest";

// magic number, hashed from class name and member names / classes
const uint32_t MotionRequest::magic_check_number=0xa554cd54;

#if !defined(__DCO_STANDALONE)
// functor table, provides access to user-defined metafunctions through the
// data class registry
static dueca::functortable_type functortable;

// register this class, provides access to a packing/unpacking object,
// and to the member access tables
static ::dueca::DataClassRegistrar registrar
  (MotionRequest::classname, NULL,
   entriestable, &functortable,
   new ::dueca::DataSetSubsidiary<MotionRequest>());

#endif

#ifndef __CUSTOM_DEFAULT_CONSTRUCTOR
MotionRequest::MotionRequest()
{
  DOBS("default constructor MotionRequest");
}
#endif

#ifndef __CUSTOM_FULL_CONSTRUCTOR
MotionRequest::MotionRequest(
        const vstring& sender,
        const motion_position& position) :
    sender(sender),
    position(position)
{
  DOBS("complete constructor MotionRequest");
}
#endif

#ifndef __CUSTOM_FULLSINGLES_CONSTRUCTOR
#endif

#ifndef __CUSTOM_COPY_CONSTRUCTOR
MotionRequest::MotionRequest(const MotionRequest& other):
    sender(other.sender),
    position(other.position)
{
  DOBS("copy constructor MotionRequest");
}
#endif

#if !defined(__CUSTOM_AMORPHRESTORE_CONSTRUCTOR) && !defined(__DCO_NOPACK)
MotionRequest::MotionRequest(dueca::AmorphReStore& s):
        sender(s),
        position(motion_position(uint8_t(s)))
{
  DOBS("amorph constructor MotionRequest");
}
#endif

#if !defined(__CUSTOM_ARRAY_SIZE_INIT_CONSTRUCTOR)
#endif

#ifndef __CUSTOM_DESTRUCTOR
MotionRequest::~MotionRequest()
{
  DOBS("destructor MotionRequest");
}
#endif

#if !defined(__DCO_STANDALONE)
void* MotionRequest::operator new(size_t size)
{
  DOBS("operator new MotionRequest");
  static ::dueca::Arena* my_arena = arena_pool.findArena
    (sizeof(MotionRequest));
  return my_arena->alloc(size);
}

void MotionRequest::operator delete(void* v)
{
  DOBS("operator delete MotionRequest");
  static ::dueca::Arena* my_arena = arena_pool.findArena
    (sizeof(MotionRequest));
  my_arena->free(v);
}
#endif

#if !defined(__CUSTOM_FUNCTION_PACKDATADIFF) && !defined(__DCO_NOPACK)
void MotionRequest::packDataDiff(::dueca::AmorphStore& s, const MotionRequest& ref) const
{
  DOBS("packDataDiff MotionRequest");
  ::dueca::IndexMemory im;
  ::dueca::checkandpackdiffsingle(this->sender, ref.sender,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->position, ref.position,
                         s, im);
  im.closeoff(s);
}
#endif

#if !defined(__CUSTOM_FUNCTION_UNPACKDATA) && !defined(__DCO_NOPACK)
void MotionRequest::unPackData(::dueca::AmorphReStore& s)
{
  DOBS("unPackData MotionRequest");

  ::unPackData(s, this->sender);
  ::unPackData(s, this->position);

}
#endif

#if !defined(__CUSTOM_FUNCTION_UNPACKDATADIFF) && !defined(__DCO_NOPACK)
void MotionRequest::unPackDataDiff(dueca::AmorphReStore& s)
{
  DOBS("unPackDataDiff MotionRequest");
  ::dueca::IndexRecall im;
  ::dueca::checkandunpackdiffsingle(this->sender, s, im);
  ::dueca::checkandunpackdiffsingle(this->position, s, im);
}
#endif

#ifndef __CUSTOM_OPERATOR_EQUAL
bool MotionRequest::operator == (const MotionRequest& other) const
{
  DOBS("operator == MotionRequest");
  if (this->sender != other.sender) return false;
  if (this->position != other.position) return false;
  return true;
}
#endif

#ifndef __CUSTOM_OPERATOR_ASSIGN
MotionRequest&
MotionRequest::operator=(const MotionRequest& other)
{
  DOBS("operator = MotionRequest");
  if (this == &other) return *this;
  this->sender = other.sender;
  this->position = other.position;
  return *this;
}
#endif

#if !defined(__CUSTOM_FUNCTION_PACKDATA) && !defined(__DCO_NOPACK)
void MotionRequest::packData(::dueca::AmorphStore& s) const
{
  DOBS("packData MotionRequest");
  ::packData(s, this->sender);
  ::packData(s, this->position);
}
#endif

#ifndef __CUSTOM_FUNCTION_PRINT
std::ostream & MotionRequest::print(std::ostream& s) const
{
  s << "MotionRequest("
    << "sender=" << this->sender << ','
    << "position=" << this->position
    << ')';
  return s;
}
#endif


            #ifndef __CUSTOM_GETSTRING_motion_position
const char* const getString(const MotionRequest::motion_position &o)
{
  static const char* motion_position_names[] = {
    "NEUTRAL",
    "DOWN"};

  return motion_position_names[int(o)];
}
#endif

#ifndef __CUSTOM_READFROMSTRING_motion_position
void readFromString(MotionRequest::motion_position &o, const std::string& s)
{
  for (int ii = 2; ii--; ) {
    if (std::string(getString(MotionRequest::motion_position(ii))) == s) {
      o = MotionRequest::motion_position(ii);
      return;
    }
  }
  throw(dueca::ConversionNotDefined());
}
#endif

#if !defined(__CUSTOM_PACKDATA_motion_position) && !defined(__DCO_NOPACK)
void packData(::dueca::AmorphStore& s,
              const MotionRequest::motion_position &o)
{ packData(s, uint8_t(o));}
#endif

#if !defined(__CUSTOM_UNPACKDATA_motion_position) && !defined(__DCO_NOPACK)
void unPackData(::dueca::AmorphReStore& s,
                MotionRequest::motion_position &o)
{ uint8_t tmp(s); o = MotionRequest::motion_position(tmp); }
#endif

namespace dueca {;
template <>
const char* getclassname<MotionRequest::motion_position>()
{ return "MotionRequest::motion_position"; }
};

