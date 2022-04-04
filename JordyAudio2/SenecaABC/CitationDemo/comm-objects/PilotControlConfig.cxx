/* ------------------------------------------------------------------ */
/*      item            : PilotControlConfig.cxx
        generated by    : matteo (matteo)
        date            : Thu 24 Mar 2022
        category        : body file
        description     : DUECA Communication Object (DCO),
                          automatically generated by dueca-codegen
        codegen version : 110
        language        : C++
*/

#include "PilotControlConfig.hxx"
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
// to the members of a PilotControlConfig object
static ::dueca::CommObjectMemberAccess
  <PilotControlConfig,PilotControlConfig::ctrl_cfg >
  PilotControlConfig_member_captain(&PilotControlConfig::captain, "captain");
static ::dueca::CommObjectMemberAccess
  <PilotControlConfig,PilotControlConfig::ctrl_cfg >
  PilotControlConfig_member_first_officer(&PilotControlConfig::first_officer, "first_officer");
static ::dueca::CommObjectMemberAccess
  <PilotControlConfig,float >
  PilotControlConfig_member_capt_bias(&PilotControlConfig::capt_bias, "capt_bias");
static ::dueca::CommObjectMemberAccess
  <PilotControlConfig,bool >
  PilotControlConfig_member_joystick_override(&PilotControlConfig::joystick_override, "joystick_override");

// assemble the above entries into a table in the order in which they
// appear in the PilotControlConfig object
static const ::dueca::CommObjectDataTable entriestable[] = {
  { &PilotControlConfig_member_captain },
  { &PilotControlConfig_member_first_officer },
  { &PilotControlConfig_member_capt_bias },
  { &PilotControlConfig_member_joystick_override },
  { NULL }
};

#endif

// class name, static
const char * const PilotControlConfig::classname = "PilotControlConfig";

// magic number, hashed from class name and member names / classes
const uint32_t PilotControlConfig::magic_check_number=0x91ba11d4;

#if !defined(__DCO_STANDALONE)
// functor table, provides access to user-defined metafunctions through the
// data class registry
static dueca::functortable_type functortable;

// register this class, provides access to a packing/unpacking object,
// and to the member access tables
static ::dueca::DataClassRegistrar registrar
  (PilotControlConfig::classname, NULL,
   entriestable, &functortable,
   new ::dueca::DataSetSubsidiary<PilotControlConfig>());

#endif

#ifndef __CUSTOM_DEFAULT_CONSTRUCTOR
PilotControlConfig::PilotControlConfig():
    captain(IGNORED),
    first_officer(IGNORED),
    capt_bias(1.0),
    joystick_override(false)
{
  DOBS("default constructor PilotControlConfig");
}
#endif

#ifndef __CUSTOM_FULL_CONSTRUCTOR
PilotControlConfig::PilotControlConfig(
        const ctrl_cfg& captain,
        const ctrl_cfg& first_officer,
        const float& capt_bias,
        const bool& joystick_override) :
    captain(captain),
    first_officer(first_officer),
    capt_bias(capt_bias),
    joystick_override(joystick_override)
{
  DOBS("complete constructor PilotControlConfig");
}
#endif

#ifndef __CUSTOM_FULLSINGLES_CONSTRUCTOR
#endif

#ifndef __CUSTOM_COPY_CONSTRUCTOR
PilotControlConfig::PilotControlConfig(const PilotControlConfig& other):
    captain(other.captain),
    first_officer(other.first_officer),
    capt_bias(other.capt_bias),
    joystick_override(other.joystick_override)
{
  DOBS("copy constructor PilotControlConfig");
}
#endif

#if !defined(__CUSTOM_AMORPHRESTORE_CONSTRUCTOR) && !defined(__DCO_NOPACK)
PilotControlConfig::PilotControlConfig(dueca::AmorphReStore& s):
        captain(ctrl_cfg(uint8_t(s))),
        first_officer(ctrl_cfg(uint8_t(s))),
        capt_bias(s),
        joystick_override(s)
{
  DOBS("amorph constructor PilotControlConfig");
}
#endif

#if !defined(__CUSTOM_ARRAY_SIZE_INIT_CONSTRUCTOR)
#endif

#ifndef __CUSTOM_DESTRUCTOR
PilotControlConfig::~PilotControlConfig()
{
  DOBS("destructor PilotControlConfig");
}
#endif

#if !defined(__DCO_STANDALONE)
void* PilotControlConfig::operator new(size_t size)
{
  DOBS("operator new PilotControlConfig");
  static ::dueca::Arena* my_arena = arena_pool.findArena
    (sizeof(PilotControlConfig));
  return my_arena->alloc(size);
}

void PilotControlConfig::operator delete(void* v)
{
  DOBS("operator delete PilotControlConfig");
  static ::dueca::Arena* my_arena = arena_pool.findArena
    (sizeof(PilotControlConfig));
  my_arena->free(v);
}
#endif

#if !defined(__CUSTOM_FUNCTION_PACKDATADIFF) && !defined(__DCO_NOPACK)
void PilotControlConfig::packDataDiff(::dueca::AmorphStore& s, const PilotControlConfig& ref) const
{
  DOBS("packDataDiff PilotControlConfig");
  ::dueca::IndexMemory im;
  ::dueca::checkandpackdiffsingle(this->captain, ref.captain,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->first_officer, ref.first_officer,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->capt_bias, ref.capt_bias,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->joystick_override, ref.joystick_override,
                         s, im);
  im.closeoff(s);
}
#endif

#if !defined(__CUSTOM_FUNCTION_UNPACKDATA) && !defined(__DCO_NOPACK)
void PilotControlConfig::unPackData(::dueca::AmorphReStore& s)
{
  DOBS("unPackData PilotControlConfig");

  ::unPackData(s, this->captain);
  ::unPackData(s, this->first_officer);
  ::unPackData(s, this->capt_bias);
  ::unPackData(s, this->joystick_override);

}
#endif

#if !defined(__CUSTOM_FUNCTION_UNPACKDATADIFF) && !defined(__DCO_NOPACK)
void PilotControlConfig::unPackDataDiff(dueca::AmorphReStore& s)
{
  DOBS("unPackDataDiff PilotControlConfig");
  ::dueca::IndexRecall im;
  ::dueca::checkandunpackdiffsingle(this->captain, s, im);
  ::dueca::checkandunpackdiffsingle(this->first_officer, s, im);
  ::dueca::checkandunpackdiffsingle(this->capt_bias, s, im);
  ::dueca::checkandunpackdiffsingle(this->joystick_override, s, im);
}
#endif

#ifndef __CUSTOM_OPERATOR_EQUAL
bool PilotControlConfig::operator == (const PilotControlConfig& other) const
{
  DOBS("operator == PilotControlConfig");
  if (this->captain != other.captain) return false;
  if (this->first_officer != other.first_officer) return false;
  if (this->capt_bias != other.capt_bias) return false;
  if (this->joystick_override != other.joystick_override) return false;
  return true;
}
#endif

#ifndef __CUSTOM_OPERATOR_ASSIGN
PilotControlConfig&
PilotControlConfig::operator=(const PilotControlConfig& other)
{
  DOBS("operator = PilotControlConfig");
  if (this == &other) return *this;
  this->captain = other.captain;
  this->first_officer = other.first_officer;
  this->capt_bias = other.capt_bias;
  this->joystick_override = other.joystick_override;
  return *this;
}
#endif

#if !defined(__CUSTOM_FUNCTION_PACKDATA) && !defined(__DCO_NOPACK)
void PilotControlConfig::packData(::dueca::AmorphStore& s) const
{
  DOBS("packData PilotControlConfig");
  ::packData(s, this->captain);
  ::packData(s, this->first_officer);
  ::packData(s, this->capt_bias);
  ::packData(s, this->joystick_override);
}
#endif

#ifndef __CUSTOM_FUNCTION_PRINT
std::ostream & PilotControlConfig::print(std::ostream& s) const
{
  s << "PilotControlConfig("
    << "captain=" << this->captain << ','
    << "first_officer=" << this->first_officer << ','
    << "capt_bias=" << this->capt_bias << ','
    << "joystick_override=" << this->joystick_override
    << ')';
  return s;
}
#endif


            #ifndef __CUSTOM_GETSTRING_ctrl_cfg
const char* const getString(const PilotControlConfig::ctrl_cfg &o)
{
  static const char* ctrl_cfg_names[] = {
    "MASTER",
    "SLAVE",
    "IGNORED",
    "COOP"};

  return ctrl_cfg_names[int(o)];
}
#endif

#ifndef __CUSTOM_READFROMSTRING_ctrl_cfg
void readFromString(PilotControlConfig::ctrl_cfg &o, const std::string& s)
{
  for (int ii = 4; ii--; ) {
    if (std::string(getString(PilotControlConfig::ctrl_cfg(ii))) == s) {
      o = PilotControlConfig::ctrl_cfg(ii);
      return;
    }
  }
  throw(dueca::ConversionNotDefined());
}
#endif

#if !defined(__CUSTOM_PACKDATA_ctrl_cfg) && !defined(__DCO_NOPACK)
void packData(::dueca::AmorphStore& s,
              const PilotControlConfig::ctrl_cfg &o)
{ packData(s, uint8_t(o));}
#endif

#if !defined(__CUSTOM_UNPACKDATA_ctrl_cfg) && !defined(__DCO_NOPACK)
void unPackData(::dueca::AmorphReStore& s,
                PilotControlConfig::ctrl_cfg &o)
{ uint8_t tmp(s); o = PilotControlConfig::ctrl_cfg(tmp); }
#endif

namespace dueca {;
template <>
const char* getclassname<PilotControlConfig::ctrl_cfg>()
{ return "PilotControlConfig::ctrl_cfg"; }
};
