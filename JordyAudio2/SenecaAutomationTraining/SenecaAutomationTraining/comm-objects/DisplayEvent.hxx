/* ------------------------------------------------------------------ */
/*      item            : DisplayEvent.hxx
        generated by    : matteo (matteo)
        date            : Wed 15 Dec 2021
        category        : header file
        description     : DUECA Communication Object (DCO)
                          automatically generated by dueca-codegen
        codegen version : 110
        language        : C++
*/

#ifndef DisplayEvent_hxx
#define DisplayEvent_hxx

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
#error "Generated DisplayEvent.hxx too old, please clean with 'make mrproper'"
#endif
#include <CommObjectTraits.hxx>
#endif
#include <iostream>




/** An automatically generated class
    */
struct DisplayEvent
{
  /** typedef for internal reference */
  typedef DisplayEvent __ThisDCOType__;

public:
  /** The name of this class. */
  static const char* const classname;


  /** A class member */
  int id;

  /** freeze displays */
  bool frozen_h;

  /** A class member */
  bool frozen_v;

  /** altitude offset */
  float offset_h_value;

  /** A class member */
  float offset_h_time;

  /** KIAS offset */
  float offset_v_value;

  /** A class member */
  float offset_v_time;

  /** attitude and compass offset */
  float offset_phi;

  /** A class member */
  float offset_theta;

  /** A class member */
  float offset_psi;

public:
  /** a "magic" number, hashed out of the class definition,
      that will be used to check consistency of the sent objects
      across the dueca nodes. */
  static const uint32_t magic_check_number;

  /** default constructor. */
  DisplayEvent();

  /** Constructor with arguments */
  DisplayEvent(
        const int& id,
        const bool& frozen_h,
        const bool& frozen_v,
        const float& offset_h_value,
        const float& offset_h_time,
        const float& offset_v_value,
        const float& offset_v_time,
        const float& offset_phi,
        const float& offset_theta,
        const float& offset_psi);

  /** copy constructor. */
  DisplayEvent(const DisplayEvent& o);

#if !defined(__DCO_NOPACK)
  /** constructor to restore an DisplayEvent from amorphous storage. */
  DisplayEvent(dueca::AmorphReStore& r);
#endif

  /** destructor. */
  ~DisplayEvent();

#if !defined(__DCO_STANDALONE)
  /** new operator "new", which places objects not on a
      heap, but in one of the memory arenas. This to speed up
      memory management. */
  static void* operator new(size_t size);

  /** new operator "delete", to go with the new version
      of operator new. */
  static void operator delete(void* p);

  /** placement "new", needed for stl. */
  inline static void* operator new(size_t size, DisplayEvent*& o)
  { return reinterpret_cast<void*>(o); }
#endif

#if !defined(__DCO_NOPACK)
  /** packs the DisplayEvent into amorphous storage. */
  void packData(::dueca::AmorphStore& s) const;

  /** packs the DisplayEvent into amorphous storage.
      only differences with a previous object are packed. */
  void packDataDiff(::dueca::AmorphStore& s, const DisplayEvent& ref) const;

  /** unpacks the DisplayEvent from an amorphous storage. */
  void unPackData(::dueca::AmorphReStore& s);

  /** unpacks the differences for DisplayEvent
      from an amorphous storage. */
  void unPackDataDiff(::dueca::AmorphReStore& s);
#endif

  /** Test for equality. */
  bool operator == (const DisplayEvent& o) const;

  /** Test for inequality. */
  inline bool operator != (const DisplayEvent& o) const
  { return !(*this == o); }

  /** Assignment operator. */
  DisplayEvent& operator=(const DisplayEvent& o);

  /** prints the DisplayEvent to a stream. */
  std::ostream & print(std::ostream& s) const;
};

#if !defined(__DCO_NOPACK)
/** pack the object into amorphous storage. */
inline void packData(::dueca::AmorphStore& s,
                     const DisplayEvent& o)
{ o.packData(s); }

/** pack the differences between this object and another
    into amorphous storage. */
inline void packDataDiff(dueca::AmorphStore& s,
                         const DisplayEvent& o,
                         const DisplayEvent& ref)
{ o.packDataDiff(s, ref); }

/** unpack the object from amorphous storage. */
inline void unPackData(::dueca::AmorphReStore& s,
                       DisplayEvent& o)
{ o.unPackData(s); }

/** unpack the differences to this object from storage. */
inline void unPackDataDiff(dueca::AmorphReStore& s,
                           DisplayEvent& o)
{ o.unPackDataDiff(s); }
#endif

namespace std {
/** print to a stream. */
inline std::ostream &
operator << (std::ostream& s, const DisplayEvent& o)
{ return o.print(s); }
};

#if !defined(__DCO_STANDALONE)
namespace dueca {
/** Template specialization, defines a trait that is needed if
    DisplayEvent is ever used inside other dco objects. */
template <>
struct dco_nested<DisplayEvent> : public dco_isnested { };
};
#endif


#endif
