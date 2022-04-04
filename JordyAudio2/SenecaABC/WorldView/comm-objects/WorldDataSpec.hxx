/* ------------------------------------------------------------------ */
/*      item            : WorldDataSpec.hxx
        generated by    : matteo (matteo)
        date            : Thu 24 Mar 2022
        category        : header file
        description     : DUECA Communication Object (DCO)
                          automatically generated by dueca-codegen
        codegen version : 110
        language        : C++
        item            : WorldDataSpec.dco
        made by         : Rene' van Paassen
        date            : 1612xx
        description     : WorldData specifications for WorldView
        copyright       : (c) 2016 TUDelft-AE-C&S
*/

#ifndef WorldDataSpec_hxx
#define WorldDataSpec_hxx

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
#error "Generated WorldDataSpec.hxx too old, please clean with 'make mrproper'"
#endif
#include <CommObjectTraits.hxx>
#endif
#include <iostream>

#include <stringoptions.h>

#include <vector>
#include <stringoptions.h>
#include <vector>


/** Helper struct that defines the parameters for a view
    */
struct WorldDataSpec
{
  /** typedef for internal reference */
  typedef WorldDataSpec __ThisDCOType__;

public:
  /** The name of this class. */
  static const char* const classname;


  /** Name for the object */
  vstring name;

  /** Type, determines behavior of the object  */
  vstring type;

  /** File names, for possibly a number of files to read the model,
      or any other specification caught in character strings */
  std::vector<vstring> filename;

  /** Position, x, y, z coordinates and/or Orientation, phi, theta,
      psi Euler angles, or anything else that the application might fancy */
  std::vector<double> coordinates;

public:
  /** a "magic" number, hashed out of the class definition,
      that will be used to check consistency of the sent objects
      across the dueca nodes. */
  static const uint32_t magic_check_number;

  /** default constructor. */
  WorldDataSpec();

  /** Constructor with arguments */
  WorldDataSpec(
        const vstring& name,
        const vstring& type,
        const std::vector<vstring>& filename,
        const std::vector<double>& coordinates);

  /** Constructor with all single (non-iterable) arguments */
  WorldDataSpec(
        const vstring& name,
        const vstring& type);

  /** copy constructor. */
  WorldDataSpec(const WorldDataSpec& o);

#if !defined(__DCO_NOPACK)
  /** constructor to restore an WorldDataSpec from amorphous storage. */
  WorldDataSpec(dueca::AmorphReStore& r);
#endif

  /** destructor. */
  ~WorldDataSpec();

#if !defined(__DCO_STANDALONE)
  /** new operator "new", which places objects not on a
      heap, but in one of the memory arenas. This to speed up
      memory management. */
  static void* operator new(size_t size);

  /** new operator "delete", to go with the new version
      of operator new. */
  static void operator delete(void* p);

  /** placement "new", needed for stl. */
  inline static void* operator new(size_t size, WorldDataSpec*& o)
  { return reinterpret_cast<void*>(o); }
#endif

#if !defined(__DCO_NOPACK)
  /** packs the WorldDataSpec into amorphous storage. */
  void packData(::dueca::AmorphStore& s) const;

  /** packs the WorldDataSpec into amorphous storage.
      only differences with a previous object are packed. */
  void packDataDiff(::dueca::AmorphStore& s, const WorldDataSpec& ref) const;

  /** unpacks the WorldDataSpec from an amorphous storage. */
  void unPackData(::dueca::AmorphReStore& s);

  /** unpacks the differences for WorldDataSpec
      from an amorphous storage. */
  void unPackDataDiff(::dueca::AmorphReStore& s);
#endif

  /** Test for equality. */
  bool operator == (const WorldDataSpec& o) const;

  /** Test for inequality. */
  inline bool operator != (const WorldDataSpec& o) const
  { return !(*this == o); }

  /** Assignment operator. */
  WorldDataSpec& operator=(const WorldDataSpec& o);

  /** prints the WorldDataSpec to a stream. */
  std::ostream & print(std::ostream& s) const;

// Additional custom code
#include "WorldDataSpecExtra.hxx"
};

#if !defined(__DCO_NOPACK)
/** pack the object into amorphous storage. */
inline void packData(::dueca::AmorphStore& s,
                     const WorldDataSpec& o)
{ o.packData(s); }

/** pack the differences between this object and another
    into amorphous storage. */
inline void packDataDiff(dueca::AmorphStore& s,
                         const WorldDataSpec& o,
                         const WorldDataSpec& ref)
{ o.packDataDiff(s, ref); }

/** unpack the object from amorphous storage. */
inline void unPackData(::dueca::AmorphReStore& s,
                       WorldDataSpec& o)
{ o.unPackData(s); }

/** unpack the differences to this object from storage. */
inline void unPackDataDiff(dueca::AmorphReStore& s,
                           WorldDataSpec& o)
{ o.unPackDataDiff(s); }
#endif

namespace std {
/** print to a stream. */
inline std::ostream &
operator << (std::ostream& s, const WorldDataSpec& o)
{ return o.print(s); }
};

#if !defined(__DCO_STANDALONE)
namespace dueca {
/** Template specialization, defines a trait that is needed if
    WorldDataSpec is ever used inside other dco objects. */
template <>
struct dco_nested<WorldDataSpec> : public dco_isnested { };
};
#endif


#endif
