/* ------------------------------------------------------------------ */
/*      item            : BaseObjectMotion.hxx
        generated by    : matteo (matteo)
        date            : Wed 15 Dec 2021
        category        : header file
        description     : DUECA Communication Object (DCO)
                          automatically generated by dueca-codegen
        codegen version : 110
        language        : C++
        item            : BaseObjectMotion.dco
        made by         : Rene' van Paassen
        date            : 171119
        description     : Describes position and speed of object in 3d space
        copyright       : (c) 2017 TUDelft-AE-C&S
*/

#ifndef BaseObjectMotion_hxx
#define BaseObjectMotion_hxx

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
#error "Generated BaseObjectMotion.hxx too old, please clean with 'make mrproper'"
#endif
#include <CommObjectTraits.hxx>
#endif
#include <iostream>

#include <fixvector.hxx>
#include "BaseObjectPosition.hxx"
#ifdef DUECA_CONFIG_HDF5
#include <H5Cpp.h>
#include <hdf5utils/HDF5DCOMetaFunctor.hxx>
#endif


/** This provides the movement of an object, and the first derivative of that
    the class has a simple extrapolation method (extrapolate), that provides
    an object with extrapolated position. 
    */
struct BaseObjectMotion : public BaseObjectPosition
{
  /** typedef for internal reference */
  typedef BaseObjectMotion __ThisDCOType__;

public:
  /** The name of this class. */
  static const char* const classname;


  /** rotational rate of the object, in body-fixed coordinate system */
  dueca::fixvector<3,float> omega;

  /** rate of the object, in body-fixed coordinate system, 
      the sign of dt determines whether this vector is earth-fixed or
      body fixed over integration */
  dueca::fixvector<3,float> uvw;

  /** time step of a possible integration/extrapolation
      if positive; integrate with velocity vector following body
      if zero; no integration
      if negative; integrate with velocity vector fixed in the world */
  float dt;

public:
  /** a "magic" number, hashed out of the class definition,
      that will be used to check consistency of the sent objects
      across the dueca nodes. */
  static const uint32_t magic_check_number;

  /** default constructor. */
  BaseObjectMotion();

  /** Constructor with arguments */
  BaseObjectMotion(
        const BaseObjectPosition& parent_BaseObjectPosition,
        const dueca::fixvector<3,float>& omega,
        const dueca::fixvector<3,float>& uvw,
        const float& dt);

  /** Constructor with all single (non-iterable) arguments */
  BaseObjectMotion(
        const float& dt);

  /** copy constructor. */
  BaseObjectMotion(const BaseObjectMotion& o);

#if !defined(__DCO_NOPACK)
  /** constructor to restore an BaseObjectMotion from amorphous storage. */
  BaseObjectMotion(dueca::AmorphReStore& r);
#endif

  /** destructor. */
  ~BaseObjectMotion();

#if !defined(__DCO_STANDALONE)
  /** new operator "new", which places objects not on a
      heap, but in one of the memory arenas. This to speed up
      memory management. */
  static void* operator new(size_t size);

  /** new operator "delete", to go with the new version
      of operator new. */
  static void operator delete(void* p);

  /** placement "new", needed for stl. */
  inline static void* operator new(size_t size, BaseObjectMotion*& o)
  { return reinterpret_cast<void*>(o); }
#endif

#if !defined(__DCO_NOPACK)
  /** packs the BaseObjectMotion into amorphous storage. */
  void packData(::dueca::AmorphStore& s) const;

  /** packs the BaseObjectMotion into amorphous storage.
      only differences with a previous object are packed. */
  void packDataDiff(::dueca::AmorphStore& s, const BaseObjectMotion& ref) const;

  /** unpacks the BaseObjectMotion from an amorphous storage. */
  void unPackData(::dueca::AmorphReStore& s);

  /** unpacks the differences for BaseObjectMotion
      from an amorphous storage. */
  void unPackDataDiff(::dueca::AmorphReStore& s);
#endif

  /** Test for equality. */
  bool operator == (const BaseObjectMotion& o) const;

  /** Test for inequality. */
  inline bool operator != (const BaseObjectMotion& o) const
  { return !(*this == o); }

  /** Assignment operator. */
  BaseObjectMotion& operator=(const BaseObjectMotion& o);

  /** prints the BaseObjectMotion to a stream. */
  std::ostream & print(std::ostream& s) const;

// Additional custom code
#include "BaseObjectMotionExtra.hxx"
};

#if !defined(__DCO_NOPACK)
/** pack the object into amorphous storage. */
inline void packData(::dueca::AmorphStore& s,
                     const BaseObjectMotion& o)
{ o.packData(s); }

/** pack the differences between this object and another
    into amorphous storage. */
inline void packDataDiff(dueca::AmorphStore& s,
                         const BaseObjectMotion& o,
                         const BaseObjectMotion& ref)
{ o.packDataDiff(s, ref); }

/** unpack the object from amorphous storage. */
inline void unPackData(::dueca::AmorphReStore& s,
                       BaseObjectMotion& o)
{ o.unPackData(s); }

/** unpack the differences to this object from storage. */
inline void unPackDataDiff(dueca::AmorphReStore& s,
                           BaseObjectMotion& o)
{ o.unPackDataDiff(s); }
#endif

namespace std {
/** print to a stream. */
inline std::ostream &
operator << (std::ostream& s, const BaseObjectMotion& o)
{ return o.print(s); }
};

#if !defined(__DCO_STANDALONE)
namespace dueca {
/** Template specialization, defines a trait that is needed if
    BaseObjectMotion is ever used inside other dco objects. */
template <>
struct dco_nested<BaseObjectMotion> : public dco_isnested { };
};
#endif

#if defined(DUECA_CONFIG_HDF5)
// functors guarded in a separate namespace
namespace BaseObjectMotion_space {

  // writes to file, reading from channel
  class HDF5DCOWriteFunctor: public dueca::hdf5log::HDF5DCOWriteFunctor
  {
    BaseObjectMotion example;
    BaseObjectPosition_space::HDF5DCOWriteFunctor __parent__;
  public:
    // constructor, to be invoked by the metafunctor
    HDF5DCOWriteFunctor(boost::weak_ptr<H5::H5File> file,
                        const std::string& path,
                        size_t chunksize,
                        const std::string& label,
                        bool compress, bool writeticks,
                        const dueca::DataTimeSpec* startend);

    // the functor member used by channel reading code
    bool operator() (const void* dpointer, const dueca::DataTimeSpec& ts);
  };

  // reads from file, writing to channel
  class HDF5DCOReadFunctor: public dueca::hdf5log::HDF5DCOReadFunctor
  {
    BaseObjectMotion example;
    BaseObjectPosition_space::HDF5DCOReadFunctor __parent__;
  public:
    // constructor, to be invoked by the metafunctor
    HDF5DCOReadFunctor(boost::weak_ptr<H5::H5File> file,
                       const std::string& path,
                       bool readticks);
    // the functor member used by channel writing code
    bool operator() (void* dpointer);
  };
} // end namespace BaseObjectMotion_space
#endif


#endif
