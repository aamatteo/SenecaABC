/* ------------------------------------------------------------------ */
/*      item            : PrimaryControls.hxx
        generated by    : matteo (matteo)
        date            : Thu 24 Mar 2022
        category        : header file
        description     : DUECA Communication Object (DCO)
                          automatically generated by dueca-codegen
        codegen version : 110
        language        : C++
        item            : PrimaryControls.dco
        made by         : Rene' van Paassen
        date            : long ago...
        description     : Typical set of variables to describe input from 
                          primary controls (stick or column, rudder pedals)
        copyright       : (c) 2018 TUDelft-AE-C&S
*/

#ifndef PrimaryControls_hxx
#define PrimaryControls_hxx

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
#error "Generated PrimaryControls.hxx too old, please clean with 'make mrproper'"
#endif
#include <CommObjectTraits.hxx>
#endif
#include <iostream>


#ifdef DUECA_CONFIG_HDF5
#include <H5Cpp.h>
#include <hdf5utils/HDF5DCOMetaFunctor.hxx>
#endif


/** Aircraft-oriented set of control inputs
   
    The input variables (ux, uy, etc.) may be scaled by the module
    doing the input, such as joystick control or control loading. The
    displacement, velocity and force/torque values should correspond to
    the inputs measured on the actual device. Note that these will
    typically may not be correct for joysticks that don't have force
    measurement.
    */
struct PrimaryControls
{
  /** typedef for internal reference */
  typedef PrimaryControls __ThisDCOType__;

public:
  /** The name of this class. */
  static const char* const classname;


  /** input around x-axis; roll, left positive */
  float ux;

  /** input about y axis; pitch, forward positive */
  float uy;

  /** input about z axis; yaw (pedals, twist..), left positive */
  float uz;

  /** for helicopters, collective input */
  float uc;

  /** displacement of the control about x axis */
  float Sx;

  /** displacement of the control about y axis */
  float Sy;

  /** displacement of the control about z axis */
  float Sz;

  /** displacement of the control about collective axis */
  float Sc;

  /** velocity of the control about x axis */
  float dSx;

  /** velocity of the control about y axis */
  float dSy;

  /** velocity of the control about z axis */
  float dSz;

  /** velocity of the control about collective axis */
  float dSc;

  /** moment of the control about x axis */
  float Mx;

  /** moment of the control about y axis */
  float My;

  /** moment of the control about z axis */
  float Mz;

  /** moment of the control about collective axis */
  float Mc;

  /** input left brake */
  float fbrake_left;

  /** input right brake */
  float fbrake_right;

  /** test input, used for end-to-end time delay measurement; it
      should be passed through model update and visual
      generation, and may there generate a visual indication */
  int32_t test;

public:
  /** a "magic" number, hashed out of the class definition,
      that will be used to check consistency of the sent objects
      across the dueca nodes. */
  static const uint32_t magic_check_number;

  /** default constructor. */
  PrimaryControls();

  /** Constructor with arguments */
  PrimaryControls(
        const float& ux,
        const float& uy,
        const float& uz,
        const float& uc,
        const float& Sx,
        const float& Sy,
        const float& Sz,
        const float& Sc,
        const float& dSx,
        const float& dSy,
        const float& dSz,
        const float& dSc,
        const float& Mx,
        const float& My,
        const float& Mz,
        const float& Mc,
        const float& fbrake_left,
        const float& fbrake_right,
        const int32_t& test);

  /** copy constructor. */
  PrimaryControls(const PrimaryControls& o);

#if !defined(__DCO_NOPACK)
  /** constructor to restore an PrimaryControls from amorphous storage. */
  PrimaryControls(dueca::AmorphReStore& r);
#endif

  /** destructor. */
  ~PrimaryControls();

#if !defined(__DCO_STANDALONE)
  /** new operator "new", which places objects not on a
      heap, but in one of the memory arenas. This to speed up
      memory management. */
  static void* operator new(size_t size);

  /** new operator "delete", to go with the new version
      of operator new. */
  static void operator delete(void* p);

  /** placement "new", needed for stl. */
  inline static void* operator new(size_t size, PrimaryControls*& o)
  { return reinterpret_cast<void*>(o); }
#endif

#if !defined(__DCO_NOPACK)
  /** packs the PrimaryControls into amorphous storage. */
  void packData(::dueca::AmorphStore& s) const;

  /** packs the PrimaryControls into amorphous storage.
      only differences with a previous object are packed. */
  void packDataDiff(::dueca::AmorphStore& s, const PrimaryControls& ref) const;

  /** unpacks the PrimaryControls from an amorphous storage. */
  void unPackData(::dueca::AmorphReStore& s);

  /** unpacks the differences for PrimaryControls
      from an amorphous storage. */
  void unPackDataDiff(::dueca::AmorphReStore& s);
#endif

  /** Test for equality. */
  bool operator == (const PrimaryControls& o) const;

  /** Test for inequality. */
  inline bool operator != (const PrimaryControls& o) const
  { return !(*this == o); }

  /** Assignment operator. */
  PrimaryControls& operator=(const PrimaryControls& o);

  /** prints the PrimaryControls to a stream. */
  std::ostream & print(std::ostream& s) const;
};

#if !defined(__DCO_NOPACK)
/** pack the object into amorphous storage. */
inline void packData(::dueca::AmorphStore& s,
                     const PrimaryControls& o)
{ o.packData(s); }

/** pack the differences between this object and another
    into amorphous storage. */
inline void packDataDiff(dueca::AmorphStore& s,
                         const PrimaryControls& o,
                         const PrimaryControls& ref)
{ o.packDataDiff(s, ref); }

/** unpack the object from amorphous storage. */
inline void unPackData(::dueca::AmorphReStore& s,
                       PrimaryControls& o)
{ o.unPackData(s); }

/** unpack the differences to this object from storage. */
inline void unPackDataDiff(dueca::AmorphReStore& s,
                           PrimaryControls& o)
{ o.unPackDataDiff(s); }
#endif

namespace std {
/** print to a stream. */
inline std::ostream &
operator << (std::ostream& s, const PrimaryControls& o)
{ return o.print(s); }
};

#if !defined(__DCO_STANDALONE)
namespace dueca {
/** Template specialization, defines a trait that is needed if
    PrimaryControls is ever used inside other dco objects. */
template <>
struct dco_nested<PrimaryControls> : public dco_isnested { };
};
#endif

#if defined(DUECA_CONFIG_HDF5)
// functors guarded in a separate namespace
namespace PrimaryControls_space {

  // writes to file, reading from channel
  class HDF5DCOWriteFunctor: public dueca::hdf5log::HDF5DCOWriteFunctor
  {
    PrimaryControls example;
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
    PrimaryControls example;
  public:
    // constructor, to be invoked by the metafunctor
    HDF5DCOReadFunctor(boost::weak_ptr<H5::H5File> file,
                       const std::string& path,
                       bool readticks);
    // the functor member used by channel writing code
    bool operator() (void* dpointer);
  };
} // end namespace PrimaryControls_space
#endif


#endif