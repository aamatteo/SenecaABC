/* ------------------------------------------------------------------ */
/*      item            : Trim_inco.hxx
        generated by    : matteo (matteo)
        date            : Wed 15 Dec 2021
        category        : header file
        description     : DUECA Communication Object (DCO)
                          automatically generated by dueca-codegen
        codegen version : 110
        language        : C++
*/

#ifndef Trim_inco_hxx
#define Trim_inco_hxx

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
#error "Generated Trim_inco.hxx too old, please clean with 'make mrproper'"
#endif
#include <CommObjectTraits.hxx>
#endif
#include <iostream>




/** An automatically generated class
    */
struct Trim_inco
{
  /** typedef for internal reference */
  typedef Trim_inco __ThisDCOType__;

public:
  /** The name of this class. */
  static const char* const classname;


  /** A class member */
  float de_trim;

  /** A class member */
  float da_trim;

  /** A class member */
  float dr_trim;

  /** A class member */
  float pla1_trim;

  /** A class member */
  float pla2_trim;

  /** A class member */
  float gear_trim;

  /** A class member */
  float flaps_trim;

public:
  /** a "magic" number, hashed out of the class definition,
      that will be used to check consistency of the sent objects
      across the dueca nodes. */
  static const uint32_t magic_check_number;

  /** default constructor. */
  Trim_inco();

  /** Constructor with arguments */
  Trim_inco(
        const float& de_trim,
        const float& da_trim,
        const float& dr_trim,
        const float& pla1_trim,
        const float& pla2_trim,
        const float& gear_trim,
        const float& flaps_trim);

  /** copy constructor. */
  Trim_inco(const Trim_inco& o);

#if !defined(__DCO_NOPACK)
  /** constructor to restore an Trim_inco from amorphous storage. */
  Trim_inco(dueca::AmorphReStore& r);
#endif

  /** destructor. */
  ~Trim_inco();

#if !defined(__DCO_STANDALONE)
  /** new operator "new", which places objects not on a
      heap, but in one of the memory arenas. This to speed up
      memory management. */
  static void* operator new(size_t size);

  /** new operator "delete", to go with the new version
      of operator new. */
  static void operator delete(void* p);

  /** placement "new", needed for stl. */
  inline static void* operator new(size_t size, Trim_inco*& o)
  { return reinterpret_cast<void*>(o); }
#endif

#if !defined(__DCO_NOPACK)
  /** packs the Trim_inco into amorphous storage. */
  void packData(::dueca::AmorphStore& s) const;

  /** packs the Trim_inco into amorphous storage.
      only differences with a previous object are packed. */
  void packDataDiff(::dueca::AmorphStore& s, const Trim_inco& ref) const;

  /** unpacks the Trim_inco from an amorphous storage. */
  void unPackData(::dueca::AmorphReStore& s);

  /** unpacks the differences for Trim_inco
      from an amorphous storage. */
  void unPackDataDiff(::dueca::AmorphReStore& s);
#endif

  /** Test for equality. */
  bool operator == (const Trim_inco& o) const;

  /** Test for inequality. */
  inline bool operator != (const Trim_inco& o) const
  { return !(*this == o); }

  /** Assignment operator. */
  Trim_inco& operator=(const Trim_inco& o);

  /** prints the Trim_inco to a stream. */
  std::ostream & print(std::ostream& s) const;
};

#if !defined(__DCO_NOPACK)
/** pack the object into amorphous storage. */
inline void packData(::dueca::AmorphStore& s,
                     const Trim_inco& o)
{ o.packData(s); }

/** pack the differences between this object and another
    into amorphous storage. */
inline void packDataDiff(dueca::AmorphStore& s,
                         const Trim_inco& o,
                         const Trim_inco& ref)
{ o.packDataDiff(s, ref); }

/** unpack the object from amorphous storage. */
inline void unPackData(::dueca::AmorphReStore& s,
                       Trim_inco& o)
{ o.unPackData(s); }

/** unpack the differences to this object from storage. */
inline void unPackDataDiff(dueca::AmorphReStore& s,
                           Trim_inco& o)
{ o.unPackDataDiff(s); }
#endif

namespace std {
/** print to a stream. */
inline std::ostream &
operator << (std::ostream& s, const Trim_inco& o)
{ return o.print(s); }
};

#if !defined(__DCO_STANDALONE)
namespace dueca {
/** Template specialization, defines a trait that is needed if
    Trim_inco is ever used inside other dco objects. */
template <>
struct dco_nested<Trim_inco> : public dco_isnested { };
};
#endif


#endif
