/* ------------------------------------------------------------------ */
/*      item            : MotionRequest.hxx
        generated by    : matteo (matteo)
        date            : Thu 24 Mar 2022
        category        : header file
        description     : DUECA Communication Object (DCO)
                          automatically generated by dueca-codegen
        codegen version : 110
        language        : C++
*/

#ifndef MotionRequest_hxx
#define MotionRequest_hxx

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
#error "Generated MotionRequest.hxx too old, please clean with 'make mrproper'"
#endif
#include <CommObjectTraits.hxx>
#endif
#include <iostream>

#include <stringoptions.h>


/**request to position the cabin in the neutral position
   FROM ... (motion test modules)
   TO MotionLimiter
    */
struct MotionRequest
{
  /** typedef for internal reference */
  typedef MotionRequest __ThisDCOType__;

public:
  /** The name of this class. */
  static const char* const classname;


  /** Enumerated type for an automatically generated object class */
  enum motion_position {
    NEUTRAL,
    DOWN
  };

  /** A class member */
  vstring sender;

  /** A class member */
  motion_position position;

public:
  /** a "magic" number, hashed out of the class definition,
      that will be used to check consistency of the sent objects
      across the dueca nodes. */
  static const uint32_t magic_check_number;

  /** default constructor. */
  MotionRequest();

  /** Constructor with arguments */
  MotionRequest(
        const vstring& sender,
        const motion_position& position);

  /** copy constructor. */
  MotionRequest(const MotionRequest& o);

#if !defined(__DCO_NOPACK)
  /** constructor to restore an MotionRequest from amorphous storage. */
  MotionRequest(dueca::AmorphReStore& r);
#endif

  /** destructor. */
  ~MotionRequest();

#if !defined(__DCO_STANDALONE)
  /** new operator "new", which places objects not on a
      heap, but in one of the memory arenas. This to speed up
      memory management. */
  static void* operator new(size_t size);

  /** new operator "delete", to go with the new version
      of operator new. */
  static void operator delete(void* p);

  /** placement "new", needed for stl. */
  inline static void* operator new(size_t size, MotionRequest*& o)
  { return reinterpret_cast<void*>(o); }
#endif

#if !defined(__DCO_NOPACK)
  /** packs the MotionRequest into amorphous storage. */
  void packData(::dueca::AmorphStore& s) const;

  /** packs the MotionRequest into amorphous storage.
      only differences with a previous object are packed. */
  void packDataDiff(::dueca::AmorphStore& s, const MotionRequest& ref) const;

  /** unpacks the MotionRequest from an amorphous storage. */
  void unPackData(::dueca::AmorphReStore& s);

  /** unpacks the differences for MotionRequest
      from an amorphous storage. */
  void unPackDataDiff(::dueca::AmorphReStore& s);
#endif

  /** Test for equality. */
  bool operator == (const MotionRequest& o) const;

  /** Test for inequality. */
  inline bool operator != (const MotionRequest& o) const
  { return !(*this == o); }

  /** Assignment operator. */
  MotionRequest& operator=(const MotionRequest& o);

  /** prints the MotionRequest to a stream. */
  std::ostream & print(std::ostream& s) const;
};

#if !defined(__DCO_NOPACK)
/** pack the object into amorphous storage. */
inline void packData(::dueca::AmorphStore& s,
                     const MotionRequest& o)
{ o.packData(s); }

/** pack the differences between this object and another
    into amorphous storage. */
inline void packDataDiff(dueca::AmorphStore& s,
                         const MotionRequest& o,
                         const MotionRequest& ref)
{ o.packDataDiff(s, ref); }

/** unpack the object from amorphous storage. */
inline void unPackData(::dueca::AmorphReStore& s,
                       MotionRequest& o)
{ o.unPackData(s); }

/** unpack the differences to this object from storage. */
inline void unPackDataDiff(dueca::AmorphReStore& s,
                           MotionRequest& o)
{ o.unPackDataDiff(s); }
#endif

const char* const getString(const MotionRequest::motion_position &o);
void readFromString(MotionRequest::motion_position &o, const std::string& s);
#if !defined(__DCO_NOPACK)
void packData(::dueca::AmorphStore& s,
              const MotionRequest::motion_position &o);
void unPackData(::dueca::AmorphReStore& s,
                MotionRequest::motion_position &o);
#endif
namespace dueca {
  template <>
  const char* getclassname<MotionRequest::motion_position>();
};

PRINT_NS_START;
inline std::ostream&
operator << (std::ostream& s, const MotionRequest::motion_position& o)
{ return s << getString(o); }
inline std::istream&
operator >> (std::istream& s, MotionRequest::motion_position& o)
{ std::string tmp; s >> tmp; readFromString(o, tmp); return s; }
PRINT_NS_END;

namespace std {
/** print to a stream. */
inline std::ostream &
operator << (std::ostream& s, const MotionRequest& o)
{ return o.print(s); }
};

#if !defined(__DCO_STANDALONE)
namespace dueca {
/** Template specialization, defines a trait that is needed if
    MotionRequest is ever used inside other dco objects. */
template <>
struct dco_nested<MotionRequest> : public dco_isnested { };
template <>
struct dco_nested< MotionRequest::motion_position > : public dco_isenum { };
};
#endif


#endif
