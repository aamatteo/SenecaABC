/* ------------------------------------------------------------------ */
/*      item            : SimulatorCabMotion.hxx
        generated by    : matteo (matteo)
        date            : Thu 24 Mar 2022
        category        : header file
        description     : DUECA Communication Object (DCO)
                          automatically generated by dueca-codegen
        codegen version : 110
        language        : C++
*/

#ifndef SimulatorCabMotion_hxx
#define SimulatorCabMotion_hxx

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
#error "Generated SimulatorCabMotion.hxx too old, please clean with 'make mrproper'"
#endif
#include <CommObjectTraits.hxx>
#endif
#include <iostream>




/**for evaluation of motion filter,
   comparable with VehicleCabMotion
   FROM MotionLimiter
   TO ... (logger)
    */
struct SimulatorCabMotion
{
  /** typedef for internal reference */
  typedef SimulatorCabMotion __ThisDCOType__;

public:
  /** The name of this class. */
  static const char* const classname;


  /** A class member */
  double xdotdot;

  /** A class member */
  double ydotdot;

  /** A class member */
  double zdotdot;

  /** A class member */
  double fx;

  /** A class member */
  double fy;

  /** A class member */
  double fz;

  /** A class member */
  double xdot;

  /** A class member */
  double ydot;

  /** A class member */
  double zdot;

  /** A class member */
  double pdot;

  /** A class member */
  double qdot;

  /** A class member */
  double rdot;

  /** A class member */
  double p;

  /** A class member */
  double q;

  /** A class member */
  double r;

public:
  /** a "magic" number, hashed out of the class definition,
      that will be used to check consistency of the sent objects
      across the dueca nodes. */
  static const uint32_t magic_check_number;

  /** default constructor. */
  SimulatorCabMotion();

  /** Constructor with arguments */
  SimulatorCabMotion(
        const double& xdotdot,
        const double& ydotdot,
        const double& zdotdot,
        const double& fx,
        const double& fy,
        const double& fz,
        const double& xdot,
        const double& ydot,
        const double& zdot,
        const double& pdot,
        const double& qdot,
        const double& rdot,
        const double& p,
        const double& q,
        const double& r);

  /** copy constructor. */
  SimulatorCabMotion(const SimulatorCabMotion& o);

#if !defined(__DCO_NOPACK)
  /** constructor to restore an SimulatorCabMotion from amorphous storage. */
  SimulatorCabMotion(dueca::AmorphReStore& r);
#endif

  /** destructor. */
  ~SimulatorCabMotion();

#if !defined(__DCO_STANDALONE)
  /** new operator "new", which places objects not on a
      heap, but in one of the memory arenas. This to speed up
      memory management. */
  static void* operator new(size_t size);

  /** new operator "delete", to go with the new version
      of operator new. */
  static void operator delete(void* p);

  /** placement "new", needed for stl. */
  inline static void* operator new(size_t size, SimulatorCabMotion*& o)
  { return reinterpret_cast<void*>(o); }
#endif

#if !defined(__DCO_NOPACK)
  /** packs the SimulatorCabMotion into amorphous storage. */
  void packData(::dueca::AmorphStore& s) const;

  /** packs the SimulatorCabMotion into amorphous storage.
      only differences with a previous object are packed. */
  void packDataDiff(::dueca::AmorphStore& s, const SimulatorCabMotion& ref) const;

  /** unpacks the SimulatorCabMotion from an amorphous storage. */
  void unPackData(::dueca::AmorphReStore& s);

  /** unpacks the differences for SimulatorCabMotion
      from an amorphous storage. */
  void unPackDataDiff(::dueca::AmorphReStore& s);
#endif

  /** Test for equality. */
  bool operator == (const SimulatorCabMotion& o) const;

  /** Test for inequality. */
  inline bool operator != (const SimulatorCabMotion& o) const
  { return !(*this == o); }

  /** Assignment operator. */
  SimulatorCabMotion& operator=(const SimulatorCabMotion& o);

  /** prints the SimulatorCabMotion to a stream. */
  std::ostream & print(std::ostream& s) const;
};

#if !defined(__DCO_NOPACK)
/** pack the object into amorphous storage. */
inline void packData(::dueca::AmorphStore& s,
                     const SimulatorCabMotion& o)
{ o.packData(s); }

/** pack the differences between this object and another
    into amorphous storage. */
inline void packDataDiff(dueca::AmorphStore& s,
                         const SimulatorCabMotion& o,
                         const SimulatorCabMotion& ref)
{ o.packDataDiff(s, ref); }

/** unpack the object from amorphous storage. */
inline void unPackData(::dueca::AmorphReStore& s,
                       SimulatorCabMotion& o)
{ o.unPackData(s); }

/** unpack the differences to this object from storage. */
inline void unPackDataDiff(dueca::AmorphReStore& s,
                           SimulatorCabMotion& o)
{ o.unPackDataDiff(s); }
#endif

namespace std {
/** print to a stream. */
inline std::ostream &
operator << (std::ostream& s, const SimulatorCabMotion& o)
{ return o.print(s); }
};

#if !defined(__DCO_STANDALONE)
namespace dueca {
/** Template specialization, defines a trait that is needed if
    SimulatorCabMotion is ever used inside other dco objects. */
template <>
struct dco_nested<SimulatorCabMotion> : public dco_isnested { };
};
#endif


#endif