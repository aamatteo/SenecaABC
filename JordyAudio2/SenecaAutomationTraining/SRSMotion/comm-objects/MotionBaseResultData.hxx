/* ------------------------------------------------------------------ */
/*      item            : MotionBaseResultData.hxx
        generated by    : matteo (matteo)
        date            : Wed 15 Dec 2021
        category        : header file
        description     : DUECA Communication Object (DCO)
                          automatically generated by dueca-codegen
        codegen version : 110
        language        : C++
*/

#ifndef MotionBaseResultData_hxx
#define MotionBaseResultData_hxx

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
#error "Generated MotionBaseResultData.hxx too old, please clean with 'make mrproper'"
#endif
#include <CommObjectTraits.hxx>
#endif
#include <iostream>

#include <fixvector.hxx>


/**Raw data received from Motion Control Cabinet
    29APR2002: now internal to the MotionLimiter
   MotionBaseProxy stripped a sync word and a checksum after receiving it
   FROM (MotionBaseProxy) MotionLimiter
   TO (MotionController) MotionLimiter
    */
struct MotionBaseResultData
{
  /** typedef for internal reference */
  typedef MotionBaseResultData __ThisDCOType__;

public:
  /** The name of this class. */
  static const char* const classname;


  /** A class member */
  uint32_t counter;

  /** A class member */
  uint32_t status;

  /** A class member */
  dueca::fixvector<6,float> actual_pos;

  /** A class member */
  dueca::fixvector<6,float> actual_len;

public:
  /** a "magic" number, hashed out of the class definition,
      that will be used to check consistency of the sent objects
      across the dueca nodes. */
  static const uint32_t magic_check_number;

  /** default constructor. */
  MotionBaseResultData();

  /** Constructor with arguments */
  MotionBaseResultData(
        const uint32_t& counter,
        const uint32_t& status,
        const dueca::fixvector<6,float>& actual_pos,
        const dueca::fixvector<6,float>& actual_len);

  /** Constructor with all single (non-iterable) arguments */
  MotionBaseResultData(
        const uint32_t& counter,
        const uint32_t& status);

  /** copy constructor. */
  MotionBaseResultData(const MotionBaseResultData& o);

#if !defined(__DCO_NOPACK)
  /** constructor to restore an MotionBaseResultData from amorphous storage. */
  MotionBaseResultData(dueca::AmorphReStore& r);
#endif

  /** destructor. */
  ~MotionBaseResultData();

#if !defined(__DCO_STANDALONE)
  /** new operator "new", which places objects not on a
      heap, but in one of the memory arenas. This to speed up
      memory management. */
  static void* operator new(size_t size);

  /** new operator "delete", to go with the new version
      of operator new. */
  static void operator delete(void* p);

  /** placement "new", needed for stl. */
  inline static void* operator new(size_t size, MotionBaseResultData*& o)
  { return reinterpret_cast<void*>(o); }
#endif

#if !defined(__DCO_NOPACK)
  /** packs the MotionBaseResultData into amorphous storage. */
  void packData(::dueca::AmorphStore& s) const;

  /** packs the MotionBaseResultData into amorphous storage.
      only differences with a previous object are packed. */
  void packDataDiff(::dueca::AmorphStore& s, const MotionBaseResultData& ref) const;

  /** unpacks the MotionBaseResultData from an amorphous storage. */
  void unPackData(::dueca::AmorphReStore& s);

  /** unpacks the differences for MotionBaseResultData
      from an amorphous storage. */
  void unPackDataDiff(::dueca::AmorphReStore& s);
#endif

  /** Test for equality. */
  bool operator == (const MotionBaseResultData& o) const;

  /** Test for inequality. */
  inline bool operator != (const MotionBaseResultData& o) const
  { return !(*this == o); }

  /** Assignment operator. */
  MotionBaseResultData& operator=(const MotionBaseResultData& o);

  /** prints the MotionBaseResultData to a stream. */
  std::ostream & print(std::ostream& s) const;
};

#if !defined(__DCO_NOPACK)
/** pack the object into amorphous storage. */
inline void packData(::dueca::AmorphStore& s,
                     const MotionBaseResultData& o)
{ o.packData(s); }

/** pack the differences between this object and another
    into amorphous storage. */
inline void packDataDiff(dueca::AmorphStore& s,
                         const MotionBaseResultData& o,
                         const MotionBaseResultData& ref)
{ o.packDataDiff(s, ref); }

/** unpack the object from amorphous storage. */
inline void unPackData(::dueca::AmorphReStore& s,
                       MotionBaseResultData& o)
{ o.unPackData(s); }

/** unpack the differences to this object from storage. */
inline void unPackDataDiff(dueca::AmorphReStore& s,
                           MotionBaseResultData& o)
{ o.unPackDataDiff(s); }
#endif

namespace std {
/** print to a stream. */
inline std::ostream &
operator << (std::ostream& s, const MotionBaseResultData& o)
{ return o.print(s); }
};

#if !defined(__DCO_STANDALONE)
namespace dueca {
/** Template specialization, defines a trait that is needed if
    MotionBaseResultData is ever used inside other dco objects. */
template <>
struct dco_nested<MotionBaseResultData> : public dco_isnested { };
};
#endif


#endif
