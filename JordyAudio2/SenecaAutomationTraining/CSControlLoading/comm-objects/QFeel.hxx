/* ------------------------------------------------------------------ */
/*      item            : QFeel.hxx
        generated by    : matteo (matteo)
        date            : Wed 15 Dec 2021
        category        : header file
        description     : DUECA Communication Object (DCO)
                          automatically generated by dueca-codegen
        codegen version : 110
        language        : C++
*/

#ifndef QFeel_hxx
#define QFeel_hxx

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
#error "Generated QFeel.hxx too old, please clean with 'make mrproper'"
#endif
#include <CommObjectTraits.hxx>
#endif
#include <iostream>

#include <fixvector.hxx>
#ifdef DUECA_CONFIG_HDF5
#include <H5Cpp.h>
#include <hdf5utils/HDF5DCOMetaFunctor.hxx>
#endif


/** This communicatable object transmits the effects of aerodynamic and
    other forces on the controls back to the control loading simulation
    The QFeel version has been configured for 6 cl axes.
    */
struct QFeel
{
  /** typedef for internal reference */
  typedef QFeel __ThisDCOType__;

public:
  /** The name of this class. */
  static const char* const classname;


  /** Additional moment on the stick or column in x (roll) axis */
  dueca::fixvector<6,float> mom_offset;

  /** Additional position on the stick or column in x (roll) axis */
  dueca::fixvector<6,float> pos_offset;

  /** Additional spring constant in x (roll) axis */
  dueca::fixvector<6,float> extra_spring;

  /** Additional damping constant in x (roll) axis */
  dueca::fixvector<6,float> extra_damping;

public:
  /** a "magic" number, hashed out of the class definition,
      that will be used to check consistency of the sent objects
      across the dueca nodes. */
  static const uint32_t magic_check_number;

  /** default constructor. */
  QFeel();

  /** Constructor with arguments */
  QFeel(
        const dueca::fixvector<6,float>& mom_offset,
        const dueca::fixvector<6,float>& pos_offset,
        const dueca::fixvector<6,float>& extra_spring,
        const dueca::fixvector<6,float>& extra_damping);

  /** copy constructor. */
  QFeel(const QFeel& o);

#if !defined(__DCO_NOPACK)
  /** constructor to restore an QFeel from amorphous storage. */
  QFeel(dueca::AmorphReStore& r);
#endif

  /** destructor. */
  ~QFeel();

#if !defined(__DCO_STANDALONE)
  /** new operator "new", which places objects not on a
      heap, but in one of the memory arenas. This to speed up
      memory management. */
  static void* operator new(size_t size);

  /** new operator "delete", to go with the new version
      of operator new. */
  static void operator delete(void* p);

  /** placement "new", needed for stl. */
  inline static void* operator new(size_t size, QFeel*& o)
  { return reinterpret_cast<void*>(o); }
#endif

#if !defined(__DCO_NOPACK)
  /** packs the QFeel into amorphous storage. */
  void packData(::dueca::AmorphStore& s) const;

  /** packs the QFeel into amorphous storage.
      only differences with a previous object are packed. */
  void packDataDiff(::dueca::AmorphStore& s, const QFeel& ref) const;

  /** unpacks the QFeel from an amorphous storage. */
  void unPackData(::dueca::AmorphReStore& s);

  /** unpacks the differences for QFeel
      from an amorphous storage. */
  void unPackDataDiff(::dueca::AmorphReStore& s);
#endif

  /** Test for equality. */
  bool operator == (const QFeel& o) const;

  /** Test for inequality. */
  inline bool operator != (const QFeel& o) const
  { return !(*this == o); }

  /** Assignment operator. */
  QFeel& operator=(const QFeel& o);

  /** prints the QFeel to a stream. */
  std::ostream & print(std::ostream& s) const;
};

#if !defined(__DCO_NOPACK)
/** pack the object into amorphous storage. */
inline void packData(::dueca::AmorphStore& s,
                     const QFeel& o)
{ o.packData(s); }

/** pack the differences between this object and another
    into amorphous storage. */
inline void packDataDiff(dueca::AmorphStore& s,
                         const QFeel& o,
                         const QFeel& ref)
{ o.packDataDiff(s, ref); }

/** unpack the object from amorphous storage. */
inline void unPackData(::dueca::AmorphReStore& s,
                       QFeel& o)
{ o.unPackData(s); }

/** unpack the differences to this object from storage. */
inline void unPackDataDiff(dueca::AmorphReStore& s,
                           QFeel& o)
{ o.unPackDataDiff(s); }
#endif

namespace std {
/** print to a stream. */
inline std::ostream &
operator << (std::ostream& s, const QFeel& o)
{ return o.print(s); }
};

#if !defined(__DCO_STANDALONE)
namespace dueca {
/** Template specialization, defines a trait that is needed if
    QFeel is ever used inside other dco objects. */
template <>
struct dco_nested<QFeel> : public dco_isnested { };
};
#endif

#if defined(DUECA_CONFIG_HDF5)
// functors guarded in a separate namespace
namespace QFeel_space {

  // writes to file, reading from channel
  class HDF5DCOWriteFunctor: public dueca::hdf5log::HDF5DCOWriteFunctor
  {
    QFeel example;
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
    QFeel example;
  public:
    // constructor, to be invoked by the metafunctor
    HDF5DCOReadFunctor(boost::weak_ptr<H5::H5File> file,
                       const std::string& path,
                       bool readticks);
    // the functor member used by channel writing code
    bool operator() (void* dpointer);
  };
} // end namespace QFeel_space
#endif


#endif
