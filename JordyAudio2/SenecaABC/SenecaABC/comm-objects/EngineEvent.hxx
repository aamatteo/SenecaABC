/* ------------------------------------------------------------------ */
/*      item            : EngineEvent.hxx
        generated by    : matteo (matteo)
        date            : Thu 24 Mar 2022
        category        : header file
        description     : DUECA Communication Object (DCO)
                          automatically generated by dueca-codegen
        codegen version : 110
        language        : C++
*/

#ifndef EngineEvent_hxx
#define EngineEvent_hxx

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
#error "Generated EngineEvent.hxx too old, please clean with 'make mrproper'"
#endif
#include <CommObjectTraits.hxx>
#endif
#include <iostream>




/** An automatically generated class
    */
struct EngineEvent
{
  /** typedef for internal reference */
  typedef EngineEvent __ThisDCOType__;

public:
  /** The name of this class. */
  static const char* const classname;


  /** A class member */
  int id;

  /** limit available engine power */
  float power_left;

  /** A class member */
  float power_right;

  /** limit max rpm */
  float max_rpm_left;

  /** A class member */
  float max_rpm_right;

  /** adjustment time */
  float time_left;

  /** A class member */
  float time_right;

public:
  /** a "magic" number, hashed out of the class definition,
      that will be used to check consistency of the sent objects
      across the dueca nodes. */
  static const uint32_t magic_check_number;

  /** default constructor. */
  EngineEvent();

  /** Constructor with arguments */
  EngineEvent(
        const int& id,
        const float& power_left,
        const float& power_right,
        const float& max_rpm_left,
        const float& max_rpm_right,
        const float& time_left,
        const float& time_right);

  /** copy constructor. */
  EngineEvent(const EngineEvent& o);

#if !defined(__DCO_NOPACK)
  /** constructor to restore an EngineEvent from amorphous storage. */
  EngineEvent(dueca::AmorphReStore& r);
#endif

  /** destructor. */
  ~EngineEvent();

#if !defined(__DCO_STANDALONE)
  /** new operator "new", which places objects not on a
      heap, but in one of the memory arenas. This to speed up
      memory management. */
  static void* operator new(size_t size);

  /** new operator "delete", to go with the new version
      of operator new. */
  static void operator delete(void* p);

  /** placement "new", needed for stl. */
  inline static void* operator new(size_t size, EngineEvent*& o)
  { return reinterpret_cast<void*>(o); }
#endif

#if !defined(__DCO_NOPACK)
  /** packs the EngineEvent into amorphous storage. */
  void packData(::dueca::AmorphStore& s) const;

  /** packs the EngineEvent into amorphous storage.
      only differences with a previous object are packed. */
  void packDataDiff(::dueca::AmorphStore& s, const EngineEvent& ref) const;

  /** unpacks the EngineEvent from an amorphous storage. */
  void unPackData(::dueca::AmorphReStore& s);

  /** unpacks the differences for EngineEvent
      from an amorphous storage. */
  void unPackDataDiff(::dueca::AmorphReStore& s);
#endif

  /** Test for equality. */
  bool operator == (const EngineEvent& o) const;

  /** Test for inequality. */
  inline bool operator != (const EngineEvent& o) const
  { return !(*this == o); }

  /** Assignment operator. */
  EngineEvent& operator=(const EngineEvent& o);

  /** prints the EngineEvent to a stream. */
  std::ostream & print(std::ostream& s) const;
};

#if !defined(__DCO_NOPACK)
/** pack the object into amorphous storage. */
inline void packData(::dueca::AmorphStore& s,
                     const EngineEvent& o)
{ o.packData(s); }

/** pack the differences between this object and another
    into amorphous storage. */
inline void packDataDiff(dueca::AmorphStore& s,
                         const EngineEvent& o,
                         const EngineEvent& ref)
{ o.packDataDiff(s, ref); }

/** unpack the object from amorphous storage. */
inline void unPackData(::dueca::AmorphReStore& s,
                       EngineEvent& o)
{ o.unPackData(s); }

/** unpack the differences to this object from storage. */
inline void unPackDataDiff(dueca::AmorphReStore& s,
                           EngineEvent& o)
{ o.unPackDataDiff(s); }
#endif

namespace std {
/** print to a stream. */
inline std::ostream &
operator << (std::ostream& s, const EngineEvent& o)
{ return o.print(s); }
};

#if !defined(__DCO_STANDALONE)
namespace dueca {
/** Template specialization, defines a trait that is needed if
    EngineEvent is ever used inside other dco objects. */
template <>
struct dco_nested<EngineEvent> : public dco_isnested { };
};
#endif


#endif
