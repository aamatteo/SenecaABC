/* ------------------------------------------------------------------ */
/*      item            : APIncoEvent.hxx
        generated by    : matteo (matteo)
        date            : Wed 15 Dec 2021
        category        : header file
        description     : DUECA Communication Object (DCO)
                          automatically generated by dueca-codegen
        codegen version : 110
        language        : C++
*/

#ifndef APIncoEvent_hxx
#define APIncoEvent_hxx

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
#error "Generated APIncoEvent.hxx too old, please clean with 'make mrproper'"
#endif
#include <CommObjectTraits.hxx>
#endif
#include <iostream>

#include <iostream>


/** An automatically generated class
    */
struct APIncoEvent
{
  /** typedef for internal reference */
  typedef APIncoEvent __ThisDCOType__;

public:
  /** The name of this class. */
  static const char* const classname;


  /** A class member */
  int APstate;

  /** A class member */
  int verticalFDstate;

  /** A class member */
  int lateralFDstate;

  /** A class member */
  int active_nav_source;

  /** A class member */
  float altSelect;

  /** A class member */
  float hdgSelect;

  /** A class member */
  float crsSelect;

  /** A class member */
  std::string fp_name;

public:
  /** a "magic" number, hashed out of the class definition,
      that will be used to check consistency of the sent objects
      across the dueca nodes. */
  static const uint32_t magic_check_number;

  /** default constructor. */
  APIncoEvent();

  /** Constructor with arguments */
  APIncoEvent(
        const int& APstate,
        const int& verticalFDstate,
        const int& lateralFDstate,
        const int& active_nav_source,
        const float& altSelect,
        const float& hdgSelect,
        const float& crsSelect,
        const std::string& fp_name);

  /** copy constructor. */
  APIncoEvent(const APIncoEvent& o);

#if !defined(__DCO_NOPACK)
  /** constructor to restore an APIncoEvent from amorphous storage. */
  APIncoEvent(dueca::AmorphReStore& r);
#endif

  /** destructor. */
  ~APIncoEvent();

#if !defined(__DCO_STANDALONE)
  /** new operator "new", which places objects not on a
      heap, but in one of the memory arenas. This to speed up
      memory management. */
  static void* operator new(size_t size);

  /** new operator "delete", to go with the new version
      of operator new. */
  static void operator delete(void* p);

  /** placement "new", needed for stl. */
  inline static void* operator new(size_t size, APIncoEvent*& o)
  { return reinterpret_cast<void*>(o); }
#endif

#if !defined(__DCO_NOPACK)
  /** packs the APIncoEvent into amorphous storage. */
  void packData(::dueca::AmorphStore& s) const;

  /** packs the APIncoEvent into amorphous storage.
      only differences with a previous object are packed. */
  void packDataDiff(::dueca::AmorphStore& s, const APIncoEvent& ref) const;

  /** unpacks the APIncoEvent from an amorphous storage. */
  void unPackData(::dueca::AmorphReStore& s);

  /** unpacks the differences for APIncoEvent
      from an amorphous storage. */
  void unPackDataDiff(::dueca::AmorphReStore& s);
#endif

  /** Test for equality. */
  bool operator == (const APIncoEvent& o) const;

  /** Test for inequality. */
  inline bool operator != (const APIncoEvent& o) const
  { return !(*this == o); }

  /** Assignment operator. */
  APIncoEvent& operator=(const APIncoEvent& o);

  /** prints the APIncoEvent to a stream. */
  std::ostream & print(std::ostream& s) const;
};

#if !defined(__DCO_NOPACK)
/** pack the object into amorphous storage. */
inline void packData(::dueca::AmorphStore& s,
                     const APIncoEvent& o)
{ o.packData(s); }

/** pack the differences between this object and another
    into amorphous storage. */
inline void packDataDiff(dueca::AmorphStore& s,
                         const APIncoEvent& o,
                         const APIncoEvent& ref)
{ o.packDataDiff(s, ref); }

/** unpack the object from amorphous storage. */
inline void unPackData(::dueca::AmorphReStore& s,
                       APIncoEvent& o)
{ o.unPackData(s); }

/** unpack the differences to this object from storage. */
inline void unPackDataDiff(dueca::AmorphReStore& s,
                           APIncoEvent& o)
{ o.unPackDataDiff(s); }
#endif

namespace std {
/** print to a stream. */
inline std::ostream &
operator << (std::ostream& s, const APIncoEvent& o)
{ return o.print(s); }
};

#if !defined(__DCO_STANDALONE)
namespace dueca {
/** Template specialization, defines a trait that is needed if
    APIncoEvent is ever used inside other dco objects. */
template <>
struct dco_nested<APIncoEvent> : public dco_isnested { };
};
#endif


#endif
