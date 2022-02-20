/* ------------------------------------------------------------------ */
/*      item            : MCP737Event.hxx
        generated by    : matteo (matteo)
        date            : Wed 15 Dec 2021
        category        : header file
        description     : DUECA Communication Object (DCO)
                          automatically generated by dueca-codegen
        codegen version : 110
        language        : C++
*/

#ifndef MCP737Event_hxx
#define MCP737Event_hxx

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
#error "Generated MCP737Event.hxx too old, please clean with 'make mrproper'"
#endif
#include <CommObjectTraits.hxx>
#endif
#include <iostream>

#include "MCPSystems.hxx"


/** An automatically generated class
    */
struct MCP737Event
{
  /** typedef for internal reference */
  typedef MCP737Event __ThisDCOType__;

public:
  /** The name of this class. */
  static const char* const classname;


  /** Enumerated type for an automatically generated object class */
  enum msgType {
    MCP_UNKNOWN,
    MCP_NONE,
    /** write only */
    MCP_ON,
    MCP_OFF,
    MCP_LIGHT_ON,
    MCP_LIGHT_OFF,
    MCP_AT_BLINK,
    /** read/write */
    MCP_N1_ON,
    MCP_N1_OFF,
    MCP_N1_PUSH,
    MCP_SPD_ON,
    MCP_SPD_OFF,
    MCP_SPD_PUSH,
    MCP_LVL_CHG_ON,
    MCP_LVL_CHG_OFF,
    MCP_LVL_CHG_PUSH,
    MCP_HDG_ON,
    MCP_HDG_OFF,
    MCP_HDG_PUSH,
    MCP_VOR_LOC_ON,
    MCP_VOR_LOC_OFF,
    MCP_VOR_LOC_PUSH,
    MCP_APP_ON,
    MCP_APP_OFF,
    MCP_APP_PUSH,
    MCP_ALT_ON,
    MCP_ALT_OFF,
    MCP_ALT_PUSH,
    MCP_VS_ON,
    MCP_VS_OFF,
    MCP_VS_PUSH,
    MCP_CMD_A_ON,
    MCP_CMD_A_OFF,
    MCP_CMD_A_PUSH,
    MCP_CMD_B_ON,
    MCP_CMD_B_OFF,
    MCP_CMD_B_PUSH,
    MCP_VNAV_ON,
    MCP_VNAV_OFF,
    MCP_VNAV_PUSH,
    MCP_LNAV_ON,
    MCP_LNAV_OFF,
    MCP_LNAV_PUSH,
    MCP_CWS_A_ON,
    MCP_CWS_A_OFF,
    MCP_CWS_A_PUSH,
    MCP_CWS_B_ON,
    MCP_CWS_B_OFF,
    MCP_CWS_B_PUSH,
    MCP_CO_MACH,
    MCP_CO_IAS,
    MCP_CO_PUSH,
    MCP_COURSE1_SET,
    MCP_COURSE2_SET,
    MCP_SPD_SET,
    MCP_HDG_SET,
    MCP_ALT_SET,
    MCP_VS_SET,
    /** write only */
    MCP_VS_DISP_ON,
    MCP_VS_DISP_OFF,
    MCP_SPD_DISP_ON,
    MCP_SPD_DISP_OFF,
    /** read only */
    MCP_AT_ON,
    MCP_AT_OFF,
    MCP_FD_L_ON,
    MCP_FD_L_OFF,
    MCP_FD_R_ON,
    MCP_FD_R_OFF,
    MCP_AP_DISENGAGE_ON,
    MCP_AP_DISENGAGE_OFF,
    /** EFIS messages */
    MCP_EFIS_WXR_CPT,
    MCP_EFIS_WXR_FO,
    MCP_EFIS_STA_CPT,
    MCP_EFIS_STA_FO,
    MCP_EFIS_WPT_CPT,
    MCP_EFIS_WPT_FO,
    MCP_EFIS_ARPT_CPT,
    MCP_EFIS_ARPT_FO,
    MCP_EFIS_DATA_CPT,
    MCP_EFIS_DATA_FO,
    MCP_EFIS_POS_CPT,
    MCP_EFIS_POS_FO,
    MCP_EFIS_TERR_CPT,
    MCP_EFIS_TERR_FO,
    MCP_EFIS_ND_APP_CPT,
    MCP_EFIS_ND_APP_FO,
    MCP_EFIS_ND_VOR_CPT,
    MCP_EFIS_ND_VOR_FO,
    MCP_EFIS_ND_MAP_CPT,
    MCP_EFIS_ND_MAP_FO,
    MCP_EFIS_ND_PLN_CPT,
    MCP_EFIS_ND_PLN_FO,
    MCP_EFIS_ND_RNG_5_CPT,
    MCP_EFIS_ND_RNG_5_FO,
    MCP_EFIS_ND_RNG_10_CPT,
    MCP_EFIS_ND_RNG_10_FO,
    MCP_EFIS_ND_RNG_20_CPT,
    MCP_EFIS_ND_RNG_20_FO,
    MCP_EFIS_ND_RNG_40_CPT,
    MCP_EFIS_ND_RNG_40_FO,
    MCP_EFIS_ND_RNG_80_CPT,
    MCP_EFIS_ND_RNG_80_FO,
    MCP_EFIS_ND_RNG_160_CPT,
    MCP_EFIS_ND_RNG_160_FO,
    MCP_EFIS_ND_RNG_320_CPT,
    MCP_EFIS_ND_RNG_320_FO,
    MCP_EFIS_ND_RNG_640_CPT,
    MCP_EFIS_ND_RNG_640_FO,
    MCP_EFIS_CTR_CPT,
    MCP_EFIS_CTR_FO,
    MCP_EFIS_TFC_CPT,
    MCP_EFIS_TFC_FO,
    MCP_EFIS_VOR1,
    MCP_EFIS_ADF1,
    MCP_EFIS_OFF1,
    MCP_EFIS_VOR2,
    MCP_EFIS_ADF2,
    MCP_EFIS_OFF2,
    MCP_EFIS_FPV,
    MCP_EFIS_MTRS,
    MCP_EFIS_MINS,
    MCP_EFIS_BARO,
    MCP_EFIS_BARO_ON,
    MCP_EFIS_RADIO_ON,
    MCP_EFIS_HPA_ON,
    MCP_EFIS_IN_ON,
    MCP_EFIS_MINS_INCR_CPT,
    MCP_EFIS_MINS_INCR_FO,
    MCP_EFIS_MINS_DECR_CPT,
    MCP_EFIS_MINS_DECR_FO,
    MCP_EFIS_BARO_INCR_CPT,
    MCP_EFIS_BARO_INCR_FO,
    MCP_EFIS_BARO_DECR_CPT,
    MCP_EFIS_BARO_DECR_FO
  };

  /** A class member */
  int sender;

  /** A class member */
  int receiver;

  /** A class member */
  msgType msg;

  /** A class member */
  float data;

public:
  /** a "magic" number, hashed out of the class definition,
      that will be used to check consistency of the sent objects
      across the dueca nodes. */
  static const uint32_t magic_check_number;

  /** default constructor. */
  MCP737Event();

  /** Constructor with arguments */
  MCP737Event(
        const int& sender,
        const int& receiver,
        const msgType& msg,
        const float& data);

  /** copy constructor. */
  MCP737Event(const MCP737Event& o);

#if !defined(__DCO_NOPACK)
  /** constructor to restore an MCP737Event from amorphous storage. */
  MCP737Event(dueca::AmorphReStore& r);
#endif

  /** destructor. */
  ~MCP737Event();

#if !defined(__DCO_STANDALONE)
  /** new operator "new", which places objects not on a
      heap, but in one of the memory arenas. This to speed up
      memory management. */
  static void* operator new(size_t size);

  /** new operator "delete", to go with the new version
      of operator new. */
  static void operator delete(void* p);

  /** placement "new", needed for stl. */
  inline static void* operator new(size_t size, MCP737Event*& o)
  { return reinterpret_cast<void*>(o); }
#endif

#if !defined(__DCO_NOPACK)
  /** packs the MCP737Event into amorphous storage. */
  void packData(::dueca::AmorphStore& s) const;

  /** packs the MCP737Event into amorphous storage.
      only differences with a previous object are packed. */
  void packDataDiff(::dueca::AmorphStore& s, const MCP737Event& ref) const;

  /** unpacks the MCP737Event from an amorphous storage. */
  void unPackData(::dueca::AmorphReStore& s);

  /** unpacks the differences for MCP737Event
      from an amorphous storage. */
  void unPackDataDiff(::dueca::AmorphReStore& s);
#endif

  /** Test for equality. */
  bool operator == (const MCP737Event& o) const;

  /** Test for inequality. */
  inline bool operator != (const MCP737Event& o) const
  { return !(*this == o); }

  /** Assignment operator. */
  MCP737Event& operator=(const MCP737Event& o);

  /** prints the MCP737Event to a stream. */
  std::ostream & print(std::ostream& s) const;
};

#if !defined(__DCO_NOPACK)
/** pack the object into amorphous storage. */
inline void packData(::dueca::AmorphStore& s,
                     const MCP737Event& o)
{ o.packData(s); }

/** pack the differences between this object and another
    into amorphous storage. */
inline void packDataDiff(dueca::AmorphStore& s,
                         const MCP737Event& o,
                         const MCP737Event& ref)
{ o.packDataDiff(s, ref); }

/** unpack the object from amorphous storage. */
inline void unPackData(::dueca::AmorphReStore& s,
                       MCP737Event& o)
{ o.unPackData(s); }

/** unpack the differences to this object from storage. */
inline void unPackDataDiff(dueca::AmorphReStore& s,
                           MCP737Event& o)
{ o.unPackDataDiff(s); }
#endif

const char* const getString(const MCP737Event::msgType &o);
void readFromString(MCP737Event::msgType &o, const std::string& s);
#if !defined(__DCO_NOPACK)
void packData(::dueca::AmorphStore& s,
              const MCP737Event::msgType &o);
void unPackData(::dueca::AmorphReStore& s,
                MCP737Event::msgType &o);
#endif
namespace dueca {
  template <>
  const char* getclassname<MCP737Event::msgType>();
};

PRINT_NS_START;
inline std::ostream&
operator << (std::ostream& s, const MCP737Event::msgType& o)
{ return s << getString(o); }
inline std::istream&
operator >> (std::istream& s, MCP737Event::msgType& o)
{ std::string tmp; s >> tmp; readFromString(o, tmp); return s; }
PRINT_NS_END;

namespace std {
/** print to a stream. */
inline std::ostream &
operator << (std::ostream& s, const MCP737Event& o)
{ return o.print(s); }
};

#if !defined(__DCO_STANDALONE)
namespace dueca {
/** Template specialization, defines a trait that is needed if
    MCP737Event is ever used inside other dco objects. */
template <>
struct dco_nested<MCP737Event> : public dco_isnested { };
template <>
struct dco_nested< MCP737Event::msgType > : public dco_isenum { };
};
#endif


#endif
