/* ------------------------------------------------------------------ */
/*      item            : ViewSpec.hxx
        generated by    : matteo (matteo)
        date            : Wed 15 Dec 2021
        category        : header file
        description     : DUECA Communication Object (DCO)
                          automatically generated by dueca-codegen
        codegen version : 110
        language        : C++
        item            : ViewSpec.dco
        made by         : Rene' van Paassen
        date            : 1612xx
        description     : View specifications for WorldView
        copyright       : (c) 2016 TUDelft-AE-C&S
*/

#ifndef ViewSpec_hxx
#define ViewSpec_hxx

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
#error "Generated ViewSpec.hxx too old, please clean with 'make mrproper'"
#endif
#include <CommObjectTraits.hxx>
#endif
#include <iostream>

#include <stringoptions.h>

#include <inttypes.h>
#include <vector>
typedef std::vector<int> vector_int_t;

#include <vector>
typedef std::vector<float> vector_float_t;


/** Helper struct that defines the parameters for a view
    */
struct ViewSpec
{
  /** typedef for internal reference */
  typedef ViewSpec __ThisDCOType__;

public:
  /** The name of this class. */
  static const char* const classname;


  /** Name for this specification */
  vstring name;

  /** Name for the window it should be in. Empty for default */
  vstring winname;

  /** Optionally, specify (by OGRE name) a display overlay with mask */
  vstring overlay;

  /** Coordinates for the viewport. If empty, the complete window
      is assumed: left, top, width, height */
  vector_int_t portcoords;

  /** Eye position and optionally rotation, offset from a base (cg or
      otherwise) position */
  vector_float_t eye_pos;

  /** Frustrum data, containing, in this order
      near plane distance
      far plane distance
      and then, option 1: field of view y
      option 2: left, right, bottom, top, of near plane in eye coord */
  vector_float_t frustum_data;

  /** Flag to turn rendering of shadows in the window on (TRUE) or off
      (FALSE) Tested for OGRE only so far and only
      SHADOWTYPE_STENCIL_MODULATIVE technique.  Make sure that in your
      scene the groundplane and large structures you don't want to
      cast shadows you specify the castShadows parameter of an entity
      is set to "false".<br> Added by Mark Mulder 17/08/2010 */
  bool render_shadows;

  /** shadowing technique */
  vstring shadow_technique;

  /** color for shadow */
  vector_float_t shadow_colour;

  /** far distance for shadowing */
  float shadow_farDistance;

public:
  /** a "magic" number, hashed out of the class definition,
      that will be used to check consistency of the sent objects
      across the dueca nodes. */
  static const uint32_t magic_check_number;

  /** default constructor. */
  ViewSpec();

  /** Constructor with arguments */
  ViewSpec(
        const vstring& name,
        const vstring& winname,
        const vstring& overlay,
        const vector_int_t& portcoords,
        const vector_float_t& eye_pos,
        const vector_float_t& frustum_data,
        const bool& render_shadows,
        const vstring& shadow_technique,
        const vector_float_t& shadow_colour,
        const float& shadow_farDistance);

  /** Constructor with all single (non-iterable) arguments */
  ViewSpec(
        const vstring& name,
        const vstring& winname,
        const vstring& overlay,
        const bool& render_shadows,
        const vstring& shadow_technique,
        const float& shadow_farDistance);

  /** copy constructor. */
  ViewSpec(const ViewSpec& o);

#if !defined(__DCO_NOPACK)
  /** constructor to restore an ViewSpec from amorphous storage. */
  ViewSpec(dueca::AmorphReStore& r);
#endif

  /** destructor. */
  ~ViewSpec();

#if !defined(__DCO_STANDALONE)
  /** new operator "new", which places objects not on a
      heap, but in one of the memory arenas. This to speed up
      memory management. */
  static void* operator new(size_t size);

  /** new operator "delete", to go with the new version
      of operator new. */
  static void operator delete(void* p);

  /** placement "new", needed for stl. */
  inline static void* operator new(size_t size, ViewSpec*& o)
  { return reinterpret_cast<void*>(o); }
#endif

#if !defined(__DCO_NOPACK)
  /** packs the ViewSpec into amorphous storage. */
  void packData(::dueca::AmorphStore& s) const;

  /** packs the ViewSpec into amorphous storage.
      only differences with a previous object are packed. */
  void packDataDiff(::dueca::AmorphStore& s, const ViewSpec& ref) const;

  /** unpacks the ViewSpec from an amorphous storage. */
  void unPackData(::dueca::AmorphReStore& s);

  /** unpacks the differences for ViewSpec
      from an amorphous storage. */
  void unPackDataDiff(::dueca::AmorphReStore& s);
#endif

  /** Test for equality. */
  bool operator == (const ViewSpec& o) const;

  /** Test for inequality. */
  inline bool operator != (const ViewSpec& o) const
  { return !(*this == o); }

  /** Assignment operator. */
  ViewSpec& operator=(const ViewSpec& o);

  /** prints the ViewSpec to a stream. */
  std::ostream & print(std::ostream& s) const;

// Additional custom code
#include "ViewSpecExtra.hxx"
};

#if !defined(__DCO_NOPACK)
/** pack the object into amorphous storage. */
inline void packData(::dueca::AmorphStore& s,
                     const ViewSpec& o)
{ o.packData(s); }

/** pack the differences between this object and another
    into amorphous storage. */
inline void packDataDiff(dueca::AmorphStore& s,
                         const ViewSpec& o,
                         const ViewSpec& ref)
{ o.packDataDiff(s, ref); }

/** unpack the object from amorphous storage. */
inline void unPackData(::dueca::AmorphReStore& s,
                       ViewSpec& o)
{ o.unPackData(s); }

/** unpack the differences to this object from storage. */
inline void unPackDataDiff(dueca::AmorphReStore& s,
                           ViewSpec& o)
{ o.unPackDataDiff(s); }
#endif

namespace std {
/** print to a stream. */
inline std::ostream &
operator << (std::ostream& s, const ViewSpec& o)
{ return o.print(s); }
};

#if !defined(__DCO_STANDALONE)
namespace dueca {
/** Template specialization, defines a trait that is needed if
    ViewSpec is ever used inside other dco objects. */
template <>
struct dco_nested<ViewSpec> : public dco_isnested { };
};
#endif


#endif
