/* ------------------------------------------------------------------ */
/*      item            : MCP737Event.cxx
        generated by    : matteo (matteo)
        date            : Thu 24 Mar 2022
        category        : body file
        description     : DUECA Communication Object (DCO),
                          automatically generated by dueca-codegen
        codegen version : 110
        language        : C++
*/

#include "MCP737Event.hxx"
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
// to the members of a MCP737Event object
static ::dueca::CommObjectMemberAccess
  <MCP737Event,int >
  MCP737Event_member_sender(&MCP737Event::sender, "sender");
static ::dueca::CommObjectMemberAccess
  <MCP737Event,int >
  MCP737Event_member_receiver(&MCP737Event::receiver, "receiver");
static ::dueca::CommObjectMemberAccess
  <MCP737Event,MCP737Event::msgType >
  MCP737Event_member_msg(&MCP737Event::msg, "msg");
static ::dueca::CommObjectMemberAccess
  <MCP737Event,float >
  MCP737Event_member_data(&MCP737Event::data, "data");

// assemble the above entries into a table in the order in which they
// appear in the MCP737Event object
static const ::dueca::CommObjectDataTable entriestable[] = {
  { &MCP737Event_member_sender },
  { &MCP737Event_member_receiver },
  { &MCP737Event_member_msg },
  { &MCP737Event_member_data },
  { NULL }
};

#endif

// class name, static
const char * const MCP737Event::classname = "MCP737Event";

// magic number, hashed from class name and member names / classes
const uint32_t MCP737Event::magic_check_number=0xbb62c921;

#if !defined(__DCO_STANDALONE)
// functor table, provides access to user-defined metafunctions through the
// data class registry
static dueca::functortable_type functortable;

// register this class, provides access to a packing/unpacking object,
// and to the member access tables
static ::dueca::DataClassRegistrar registrar
  (MCP737Event::classname, NULL,
   entriestable, &functortable,
   new ::dueca::DataSetSubsidiary<MCP737Event>());

#endif

#ifndef __CUSTOM_DEFAULT_CONSTRUCTOR
MCP737Event::MCP737Event():
    sender(0),
    receiver(0),
    msg(MCP_NONE),
    data(0)
{
  DOBS("default constructor MCP737Event");
}
#endif

#ifndef __CUSTOM_FULL_CONSTRUCTOR
MCP737Event::MCP737Event(
        const int& sender,
        const int& receiver,
        const msgType& msg,
        const float& data) :
    sender(sender),
    receiver(receiver),
    msg(msg),
    data(data)
{
  DOBS("complete constructor MCP737Event");
}
#endif

#ifndef __CUSTOM_FULLSINGLES_CONSTRUCTOR
#endif

#ifndef __CUSTOM_COPY_CONSTRUCTOR
MCP737Event::MCP737Event(const MCP737Event& other):
    sender(other.sender),
    receiver(other.receiver),
    msg(other.msg),
    data(other.data)
{
  DOBS("copy constructor MCP737Event");
}
#endif

#if !defined(__CUSTOM_AMORPHRESTORE_CONSTRUCTOR) && !defined(__DCO_NOPACK)
MCP737Event::MCP737Event(dueca::AmorphReStore& s):
        sender(s),
        receiver(s),
        msg(msgType(uint32_t(s))),
        data(s)
{
  DOBS("amorph constructor MCP737Event");
}
#endif

#if !defined(__CUSTOM_ARRAY_SIZE_INIT_CONSTRUCTOR)
#endif

#ifndef __CUSTOM_DESTRUCTOR
MCP737Event::~MCP737Event()
{
  DOBS("destructor MCP737Event");
}
#endif

#if !defined(__DCO_STANDALONE)
void* MCP737Event::operator new(size_t size)
{
  DOBS("operator new MCP737Event");
  static ::dueca::Arena* my_arena = arena_pool.findArena
    (sizeof(MCP737Event));
  return my_arena->alloc(size);
}

void MCP737Event::operator delete(void* v)
{
  DOBS("operator delete MCP737Event");
  static ::dueca::Arena* my_arena = arena_pool.findArena
    (sizeof(MCP737Event));
  my_arena->free(v);
}
#endif

#if !defined(__CUSTOM_FUNCTION_PACKDATADIFF) && !defined(__DCO_NOPACK)
void MCP737Event::packDataDiff(::dueca::AmorphStore& s, const MCP737Event& ref) const
{
  DOBS("packDataDiff MCP737Event");
  ::dueca::IndexMemory im;
  ::dueca::checkandpackdiffsingle(this->sender, ref.sender,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->receiver, ref.receiver,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->msg, ref.msg,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->data, ref.data,
                         s, im);
  im.closeoff(s);
}
#endif

#if !defined(__CUSTOM_FUNCTION_UNPACKDATA) && !defined(__DCO_NOPACK)
void MCP737Event::unPackData(::dueca::AmorphReStore& s)
{
  DOBS("unPackData MCP737Event");

  ::unPackData(s, this->sender);
  ::unPackData(s, this->receiver);
  ::unPackData(s, this->msg);
  ::unPackData(s, this->data);

}
#endif

#if !defined(__CUSTOM_FUNCTION_UNPACKDATADIFF) && !defined(__DCO_NOPACK)
void MCP737Event::unPackDataDiff(dueca::AmorphReStore& s)
{
  DOBS("unPackDataDiff MCP737Event");
  ::dueca::IndexRecall im;
  ::dueca::checkandunpackdiffsingle(this->sender, s, im);
  ::dueca::checkandunpackdiffsingle(this->receiver, s, im);
  ::dueca::checkandunpackdiffsingle(this->msg, s, im);
  ::dueca::checkandunpackdiffsingle(this->data, s, im);
}
#endif

#ifndef __CUSTOM_OPERATOR_EQUAL
bool MCP737Event::operator == (const MCP737Event& other) const
{
  DOBS("operator == MCP737Event");
  if (this->sender != other.sender) return false;
  if (this->receiver != other.receiver) return false;
  if (this->msg != other.msg) return false;
  if (this->data != other.data) return false;
  return true;
}
#endif

#ifndef __CUSTOM_OPERATOR_ASSIGN
MCP737Event&
MCP737Event::operator=(const MCP737Event& other)
{
  DOBS("operator = MCP737Event");
  if (this == &other) return *this;
  this->sender = other.sender;
  this->receiver = other.receiver;
  this->msg = other.msg;
  this->data = other.data;
  return *this;
}
#endif

#if !defined(__CUSTOM_FUNCTION_PACKDATA) && !defined(__DCO_NOPACK)
void MCP737Event::packData(::dueca::AmorphStore& s) const
{
  DOBS("packData MCP737Event");
  ::packData(s, this->sender);
  ::packData(s, this->receiver);
  ::packData(s, this->msg);
  ::packData(s, this->data);
}
#endif

#ifndef __CUSTOM_FUNCTION_PRINT
std::ostream & MCP737Event::print(std::ostream& s) const
{
  s << "MCP737Event("
    << "sender=" << this->sender << ','
    << "receiver=" << this->receiver << ','
    << "msg=" << this->msg << ','
    << "data=" << this->data
    << ')';
  return s;
}
#endif


            #ifndef __CUSTOM_GETSTRING_msgType
const char* const getString(const MCP737Event::msgType &o)
{
  static const char* msgType_names[] = {
    "MCP_UNKNOWN",
    "MCP_NONE",
    "MCP_ON",
    "MCP_OFF",
    "MCP_LIGHT_ON",
    "MCP_LIGHT_OFF",
    "MCP_AT_BLINK",
    "MCP_N1_ON",
    "MCP_N1_OFF",
    "MCP_N1_PUSH",
    "MCP_SPD_ON",
    "MCP_SPD_OFF",
    "MCP_SPD_PUSH",
    "MCP_LVL_CHG_ON",
    "MCP_LVL_CHG_OFF",
    "MCP_LVL_CHG_PUSH",
    "MCP_HDG_ON",
    "MCP_HDG_OFF",
    "MCP_HDG_PUSH",
    "MCP_VOR_LOC_ON",
    "MCP_VOR_LOC_OFF",
    "MCP_VOR_LOC_PUSH",
    "MCP_APP_ON",
    "MCP_APP_OFF",
    "MCP_APP_PUSH",
    "MCP_ALT_ON",
    "MCP_ALT_OFF",
    "MCP_ALT_PUSH",
    "MCP_VS_ON",
    "MCP_VS_OFF",
    "MCP_VS_PUSH",
    "MCP_CMD_A_ON",
    "MCP_CMD_A_OFF",
    "MCP_CMD_A_PUSH",
    "MCP_CMD_B_ON",
    "MCP_CMD_B_OFF",
    "MCP_CMD_B_PUSH",
    "MCP_VNAV_ON",
    "MCP_VNAV_OFF",
    "MCP_VNAV_PUSH",
    "MCP_LNAV_ON",
    "MCP_LNAV_OFF",
    "MCP_LNAV_PUSH",
    "MCP_CWS_A_ON",
    "MCP_CWS_A_OFF",
    "MCP_CWS_A_PUSH",
    "MCP_CWS_B_ON",
    "MCP_CWS_B_OFF",
    "MCP_CWS_B_PUSH",
    "MCP_CO_MACH",
    "MCP_CO_IAS",
    "MCP_CO_PUSH",
    "MCP_COURSE1_SET",
    "MCP_COURSE2_SET",
    "MCP_SPD_SET",
    "MCP_HDG_SET",
    "MCP_ALT_SET",
    "MCP_VS_SET",
    "MCP_VS_DISP_ON",
    "MCP_VS_DISP_OFF",
    "MCP_SPD_DISP_ON",
    "MCP_SPD_DISP_OFF",
    "MCP_AT_ON",
    "MCP_AT_OFF",
    "MCP_FD_L_ON",
    "MCP_FD_L_OFF",
    "MCP_FD_R_ON",
    "MCP_FD_R_OFF",
    "MCP_AP_DISENGAGE_ON",
    "MCP_AP_DISENGAGE_OFF",
    "MCP_EFIS_WXR_CPT",
    "MCP_EFIS_WXR_FO",
    "MCP_EFIS_STA_CPT",
    "MCP_EFIS_STA_FO",
    "MCP_EFIS_WPT_CPT",
    "MCP_EFIS_WPT_FO",
    "MCP_EFIS_ARPT_CPT",
    "MCP_EFIS_ARPT_FO",
    "MCP_EFIS_DATA_CPT",
    "MCP_EFIS_DATA_FO",
    "MCP_EFIS_POS_CPT",
    "MCP_EFIS_POS_FO",
    "MCP_EFIS_TERR_CPT",
    "MCP_EFIS_TERR_FO",
    "MCP_EFIS_ND_APP_CPT",
    "MCP_EFIS_ND_APP_FO",
    "MCP_EFIS_ND_VOR_CPT",
    "MCP_EFIS_ND_VOR_FO",
    "MCP_EFIS_ND_MAP_CPT",
    "MCP_EFIS_ND_MAP_FO",
    "MCP_EFIS_ND_PLN_CPT",
    "MCP_EFIS_ND_PLN_FO",
    "MCP_EFIS_ND_RNG_5_CPT",
    "MCP_EFIS_ND_RNG_5_FO",
    "MCP_EFIS_ND_RNG_10_CPT",
    "MCP_EFIS_ND_RNG_10_FO",
    "MCP_EFIS_ND_RNG_20_CPT",
    "MCP_EFIS_ND_RNG_20_FO",
    "MCP_EFIS_ND_RNG_40_CPT",
    "MCP_EFIS_ND_RNG_40_FO",
    "MCP_EFIS_ND_RNG_80_CPT",
    "MCP_EFIS_ND_RNG_80_FO",
    "MCP_EFIS_ND_RNG_160_CPT",
    "MCP_EFIS_ND_RNG_160_FO",
    "MCP_EFIS_ND_RNG_320_CPT",
    "MCP_EFIS_ND_RNG_320_FO",
    "MCP_EFIS_ND_RNG_640_CPT",
    "MCP_EFIS_ND_RNG_640_FO",
    "MCP_EFIS_CTR_CPT",
    "MCP_EFIS_CTR_FO",
    "MCP_EFIS_TFC_CPT",
    "MCP_EFIS_TFC_FO",
    "MCP_EFIS_VOR1",
    "MCP_EFIS_ADF1",
    "MCP_EFIS_OFF1",
    "MCP_EFIS_VOR2",
    "MCP_EFIS_ADF2",
    "MCP_EFIS_OFF2",
    "MCP_EFIS_FPV",
    "MCP_EFIS_MTRS",
    "MCP_EFIS_MINS",
    "MCP_EFIS_BARO",
    "MCP_EFIS_BARO_ON",
    "MCP_EFIS_RADIO_ON",
    "MCP_EFIS_HPA_ON",
    "MCP_EFIS_IN_ON",
    "MCP_EFIS_MINS_INCR_CPT",
    "MCP_EFIS_MINS_INCR_FO",
    "MCP_EFIS_MINS_DECR_CPT",
    "MCP_EFIS_MINS_DECR_FO",
    "MCP_EFIS_BARO_INCR_CPT",
    "MCP_EFIS_BARO_INCR_FO",
    "MCP_EFIS_BARO_DECR_CPT",
    "MCP_EFIS_BARO_DECR_FO"};

  return msgType_names[int(o)];
}
#endif

#ifndef __CUSTOM_READFROMSTRING_msgType
void readFromString(MCP737Event::msgType &o, const std::string& s)
{
  for (int ii = 134; ii--; ) {
    if (std::string(getString(MCP737Event::msgType(ii))) == s) {
      o = MCP737Event::msgType(ii);
      return;
    }
  }
  throw(dueca::ConversionNotDefined());
}
#endif

#if !defined(__CUSTOM_PACKDATA_msgType) && !defined(__DCO_NOPACK)
void packData(::dueca::AmorphStore& s,
              const MCP737Event::msgType &o)
{ packData(s, uint32_t(o));}
#endif

#if !defined(__CUSTOM_UNPACKDATA_msgType) && !defined(__DCO_NOPACK)
void unPackData(::dueca::AmorphReStore& s,
                MCP737Event::msgType &o)
{ uint32_t tmp(s); o = MCP737Event::msgType(tmp); }
#endif

namespace dueca {;
template <>
const char* getclassname<MCP737Event::msgType>()
{ return "MCP737Event::msgType"; }
};
