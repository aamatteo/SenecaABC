/* ------------------------------------------------------------------ */
/*      item            : PilotControlConfig.hxx
        generated by    : matteo (matteo)
        date            : Thu 24 Mar 2022
        category        : header file
        description     : DUECA Communication Object (DCO)
                          automatically generated by dueca-codegen
        codegen version : 110
        language        : C++
*/

#ifndef PilotControlConfig_hxx
#define PilotControlConfig_hxx

#include <inttypes.h>

#if !defined(__DCO_NOPACK)
namespace dueca {
class AmorphStore;
class AmorphReStore;
struct DataWriterArraySize;
};
#endif
#if !defined(__DCO_STANDALONE)
namespace dueca {
struct CommObjectDataTable;
};
#include <gencodegen.h>
#if GENCODEGEN != 110
#error "Generated PilotControlConfig.hxx too old, please clean with 'make mrproper'"
#endif
#include <CommObjectTraits.hxx>
#endif
#include <iostream>




/** An automatically generated class
    */
struct PilotControlConfig
{
  /** typedef for internal reference */
  typedef PilotControlConfig __ThisDCOType__;

public:
  /** The name of this class. */
  static const char* const classname;


  /** MASTER: provides single input to model

      SLAVE: physically follows motions of master

      IGNORED: moves freely, no input to model

      COOP: moves independently and provides part of input to model

            ratio is determined by capt_bias (1.0=capt in ctrl, 0.0=fo in ctrl)
 */
  enum ctrl_cfg {
    MASTER,
    SLAVE,
    IGNORED,
    COOP
  };

  /** A class member */
  ctrl_cfg captain;

  /** A class member */
  ctrl_cfg first_officer;

  /** A class member */
  float capt_bias;

  /** A class member */
  bool joystick_override;

public:
  /** a "magic" number, hashed out of the class definition,
      that will be used to check consistency of the sent objects
      across the dueca nodes. */
  static const uint32_t magic_check_number;

  /** default constructor. */
  PilotControlConfig();

  /** Constructor with arguments */
  PilotControlConfig(
        const ctrl_cfg& captain,
        const ctrl_cfg& first_officer,
        const float& capt_bias,
        const bool& joystick_override);

  /** copy constructor. */
  PilotControlConfig(const PilotControlConfig& o);

#if !defined(__DCO_NOPACK)
  /** constructor to restore an PilotControlConfig from amorphous storage. */
  PilotControlConfig(dueca::AmorphReStore& r);
#endif

  /** destructor. */
  ~PilotControlConfig();

#if !defined(__DCO_STANDALONE)
  /** new operator "new", which places objects not on a
      heap, but in one of the memory arenas. This to speed up
      memory management. */
  static void* operator new(size_t size);

  /** new operator "delete", to go with the new version
      of operator new. */
  static void operator delete(void* p);

  /** placement "new", needed for stl. */
  inline static void* operator new(size_t size, PilotControlConfig*& o)
  { return reinterpret_cast<void*>(o); }
#endif

#if !defined(__DCO_NOPACK)
  /** packs the PilotControlConfig into amorphous storage. */
  void packData(::dueca::AmorphStore& s) const;

  /** packs the PilotControlConfig into amorphous storage.
      only differences with a previous object are packed. */
  void packDataDiff(::dueca::AmorphStore& s, const PilotControlConfig& ref) const;

  /** unpacks the PilotControlConfig from an amorphous storage. */
  void unPackData(::dueca::AmorphReStore& s);

  /** unpacks the differences for PilotControlConfig
      from an amorphous storage. */
  void unPackDataDiff(::dueca::AmorphReStore& s);
#endif

  /** Test for equality. */
  bool operator == (const PilotControlConfig& o) const;

  /** Test for inequality. */
  inline bool operator != (const PilotControlConfig& o) const
  { return !(*this == o); }

  /** Assignment operator. */
  PilotControlConfig& operator=(const PilotControlConfig& o);

  /** prints the PilotControlConfig to a stream. */
  std::ostream & print(std::ostream& s) const;
};

#if !defined(__DCO_NOPACK)
/** pack the object into amorphous storage. */
inline void packData(::dueca::AmorphStore& s,
                     const PilotControlConfig& o)
{ o.packData(s); }

/** pack the differences between this object and another
    into amorphous storage. */
inline void packDataDiff(dueca::AmorphStore& s,
                         const PilotControlConfig& o,
                         const PilotControlConfig& ref)
{ o.packDataDiff(s, ref); }

/** unpack the object from amorphous storage. */
inline void unPackData(::dueca::AmorphReStore& s,
                       PilotControlConfig& o)
{ o.unPackData(s); }

/** unpack the differences to this object from storage. */
inline void unPackDataDiff(dueca::AmorphReStore& s,
                           PilotControlConfig& o)
{ o.unPackDataDiff(s); }
#endif

const char* const getString(const PilotControlConfig::ctrl_cfg &o);
void readFromString(PilotControlConfig::ctrl_cfg &o, const std::string& s);
#if !defined(__DCO_NOPACK)
void packData(::dueca::AmorphStore& s,
              const PilotControlConfig::ctrl_cfg &o);
void unPackData(::dueca::AmorphReStore& s,
                PilotControlConfig::ctrl_cfg &o);
#endif
namespace dueca {
  template <>
  const char* getclassname<PilotControlConfig::ctrl_cfg>();
};

PRINT_NS_START;
inline std::ostream&
operator << (std::ostream& s, const PilotControlConfig::ctrl_cfg& o)
{ return s << getString(o); }
inline std::istream&
operator >> (std::istream& s, PilotControlConfig::ctrl_cfg& o)
{ std::string tmp; s >> tmp; readFromString(o, tmp); return s; }
PRINT_NS_END;

namespace std {
/** print to a stream. */
inline std::ostream &
operator << (std::ostream& s, const PilotControlConfig& o)
{ return o.print(s); }
};

#if !defined(__DCO_STANDALONE)
namespace dueca {
/** Template specialization, defines a trait that is needed if
    PilotControlConfig is ever used inside other dco objects. */
template <>
struct dco_nested<PilotControlConfig> : public dco_isnested { };
template <>
struct dco_nested< PilotControlConfig::ctrl_cfg > : public dco_isenum { };
};
#endif


#endif