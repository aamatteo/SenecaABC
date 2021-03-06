/* ------------------------------------------------------------------ */
/*      item            : PrimarySwitches.hxx
        generated by    : matteo (matteo)
        date            : Thu 24 Mar 2022
        category        : header file
        description     : DUECA Communication Object (DCO)
                          automatically generated by dueca-codegen
        codegen version : 110
        language        : C++
*/

#ifndef PrimarySwitches_hxx
#define PrimarySwitches_hxx

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
#error "Generated PrimarySwitches.hxx too old, please clean with 'make mrproper'"
#endif
#include <CommObjectTraits.hxx>
#endif
#include <iostream>


#ifdef DUECA_CONFIG_HDF5
#include <H5Cpp.h>
#include <hdf5utils/HDF5DCOMetaFunctor.hxx>
#endif


/** typical switches on the primary control inputs
    */
struct PrimarySwitches
{
  /** typedef for internal reference */
  typedef PrimarySwitches __ThisDCOType__;

public:
  /** The name of this class. */
  static const char* const classname;


  /** radio transmit switch */
  bool xmit;

  /** pitch trim up */
  bool trim_up;

  /** pitch trim down */
  bool trim_down;

  /** autopilot disconnect switch */
  bool AP_disconnect;

public:
  /** a "magic" number, hashed out of the class definition,
      that will be used to check consistency of the sent objects
      across the dueca nodes. */
  static const uint32_t magic_check_number;

  /** default constructor. */
  PrimarySwitches();

  /** Constructor with arguments */
  PrimarySwitches(
        const bool& xmit,
        const bool& trim_up,
        const bool& trim_down,
        const bool& AP_disconnect);

  /** copy constructor. */
  PrimarySwitches(const PrimarySwitches& o);

#if !defined(__DCO_NOPACK)
  /** constructor to restore an PrimarySwitches from amorphous storage. */
  PrimarySwitches(dueca::AmorphReStore& r);
#endif

  /** destructor. */
  ~PrimarySwitches();

#if !defined(__DCO_STANDALONE)
  /** new operator "new", which places objects not on a
      heap, but in one of the memory arenas. This to speed up
      memory management. */
  static void* operator new(size_t size);

  /** new operator "delete", to go with the new version
      of operator new. */
  static void operator delete(void* p);

  /** placement "new", needed for stl. */
  inline static void* operator new(size_t size, PrimarySwitches*& o)
  { return reinterpret_cast<void*>(o); }
#endif

#if !defined(__DCO_NOPACK)
  /** packs the PrimarySwitches into amorphous storage. */
  void packData(::dueca::AmorphStore& s) const;

  /** packs the PrimarySwitches into amorphous storage.
      only differences with a previous object are packed. */
  void packDataDiff(::dueca::AmorphStore& s, const PrimarySwitches& ref) const;

  /** unpacks the PrimarySwitches from an amorphous storage. */
  void unPackData(::dueca::AmorphReStore& s);

  /** unpacks the differences for PrimarySwitches
      from an amorphous storage. */
  void unPackDataDiff(::dueca::AmorphReStore& s);
#endif

  /** Test for equality. */
  bool operator == (const PrimarySwitches& o) const;

  /** Test for inequality. */
  inline bool operator != (const PrimarySwitches& o) const
  { return !(*this == o); }

  /** Assignment operator. */
  PrimarySwitches& operator=(const PrimarySwitches& o);

  /** prints the PrimarySwitches to a stream. */
  std::ostream & print(std::ostream& s) const;
};

#if !defined(__DCO_NOPACK)
/** pack the object into amorphous storage. */
inline void packData(::dueca::AmorphStore& s,
                     const PrimarySwitches& o)
{ o.packData(s); }

/** pack the differences between this object and another
    into amorphous storage. */
inline void packDataDiff(dueca::AmorphStore& s,
                         const PrimarySwitches& o,
                         const PrimarySwitches& ref)
{ o.packDataDiff(s, ref); }

/** unpack the object from amorphous storage. */
inline void unPackData(::dueca::AmorphReStore& s,
                       PrimarySwitches& o)
{ o.unPackData(s); }

/** unpack the differences to this object from storage. */
inline void unPackDataDiff(dueca::AmorphReStore& s,
                           PrimarySwitches& o)
{ o.unPackDataDiff(s); }
#endif

namespace std {
/** print to a stream. */
inline std::ostream &
operator << (std::ostream& s, const PrimarySwitches& o)
{ return o.print(s); }
};

#if !defined(__DCO_STANDALONE)
namespace dueca {
/** Template specialization, defines a trait that is needed if
    PrimarySwitches is ever used inside other dco objects. */
template <>
struct dco_nested<PrimarySwitches> : public dco_isnested { };
};
#endif

#if defined(DUECA_CONFIG_HDF5)
// functors guarded in a separate namespace
namespace PrimarySwitches_space {

  // writes to file, reading from channel
  class HDF5DCOWriteFunctor: public dueca::hdf5log::HDF5DCOWriteFunctor
  {
    PrimarySwitches example;
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
    PrimarySwitches example;
  public:
    // constructor, to be invoked by the metafunctor
    HDF5DCOReadFunctor(boost::weak_ptr<H5::H5File> file,
                       const std::string& path,
                       bool readticks);
    // the functor member used by channel writing code
    bool operator() (void* dpointer);
  };
} // end namespace PrimarySwitches_space
#endif


#endif
