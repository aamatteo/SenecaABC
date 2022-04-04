/* ------------------------------------------------------------------ */
/*      item            : SimulatorMotionState.hxx
        generated by    : matteo (matteo)
        date            : Thu 24 Mar 2022
        category        : header file
        description     : DUECA Communication Object (DCO)
                          automatically generated by dueca-codegen
        codegen version : 110
        language        : C++
*/

#ifndef SimulatorMotionState_hxx
#define SimulatorMotionState_hxx

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
#error "Generated SimulatorMotionState.hxx too old, please clean with 'make mrproper'"
#endif
#include <CommObjectTraits.hxx>
#endif
#include <iostream>




/**internal motion state in sim inertial (except p/q/r)
   FROM MotionLimiter
   TO GenericMotionFilter
    */
struct SimulatorMotionState
{
  /** typedef for internal reference */
  typedef SimulatorMotionState __ThisDCOType__;

public:
  /** The name of this class. */
  static const char* const classname;


  /** A class member */
  double x;

  /** A class member */
  double y;

  /** A class member */
  double z;

  /** A class member */
  double q0;

  /** A class member */
  double q1;

  /** A class member */
  double q2;

  /** A class member */
  double q3;

  /** A class member */
  double xdot;

  /** A class member */
  double ydot;

  /** A class member */
  double zdot;

  /** A class member */
  double p;

  /** A class member */
  double q;

  /** A class member */
  double r;

  /** A class member */
  double phi;

  /** A class member */
  double theta;

  /** A class member */
  double psi;

public:
  /** a "magic" number, hashed out of the class definition,
      that will be used to check consistency of the sent objects
      across the dueca nodes. */
  static const uint32_t magic_check_number;

  /** default constructor. */
  SimulatorMotionState();

  /** Constructor with arguments */
  SimulatorMotionState(
        const double& x,
        const double& y,
        const double& z,
        const double& q0,
        const double& q1,
        const double& q2,
        const double& q3,
        const double& xdot,
        const double& ydot,
        const double& zdot,
        const double& p,
        const double& q,
        const double& r,
        const double& phi,
        const double& theta,
        const double& psi);

  /** copy constructor. */
  SimulatorMotionState(const SimulatorMotionState& o);

#if !defined(__DCO_NOPACK)
  /** constructor to restore an SimulatorMotionState from amorphous storage. */
  SimulatorMotionState(dueca::AmorphReStore& r);
#endif

  /** destructor. */
  ~SimulatorMotionState();

#if !defined(__DCO_STANDALONE)
  /** new operator "new", which places objects not on a
      heap, but in one of the memory arenas. This to speed up
      memory management. */
  static void* operator new(size_t size);

  /** new operator "delete", to go with the new version
      of operator new. */
  static void operator delete(void* p);

  /** placement "new", needed for stl. */
  inline static void* operator new(size_t size, SimulatorMotionState*& o)
  { return reinterpret_cast<void*>(o); }
#endif

#if !defined(__DCO_NOPACK)
  /** packs the SimulatorMotionState into amorphous storage. */
  void packData(::dueca::AmorphStore& s) const;

  /** packs the SimulatorMotionState into amorphous storage.
      only differences with a previous object are packed. */
  void packDataDiff(::dueca::AmorphStore& s, const SimulatorMotionState& ref) const;

  /** unpacks the SimulatorMotionState from an amorphous storage. */
  void unPackData(::dueca::AmorphReStore& s);

  /** unpacks the differences for SimulatorMotionState
      from an amorphous storage. */
  void unPackDataDiff(::dueca::AmorphReStore& s);
#endif

  /** Test for equality. */
  bool operator == (const SimulatorMotionState& o) const;

  /** Test for inequality. */
  inline bool operator != (const SimulatorMotionState& o) const
  { return !(*this == o); }

  /** Assignment operator. */
  SimulatorMotionState& operator=(const SimulatorMotionState& o);

  /** prints the SimulatorMotionState to a stream. */
  std::ostream & print(std::ostream& s) const;
};

#if !defined(__DCO_NOPACK)
/** pack the object into amorphous storage. */
inline void packData(::dueca::AmorphStore& s,
                     const SimulatorMotionState& o)
{ o.packData(s); }

/** pack the differences between this object and another
    into amorphous storage. */
inline void packDataDiff(dueca::AmorphStore& s,
                         const SimulatorMotionState& o,
                         const SimulatorMotionState& ref)
{ o.packDataDiff(s, ref); }

/** unpack the object from amorphous storage. */
inline void unPackData(::dueca::AmorphReStore& s,
                       SimulatorMotionState& o)
{ o.unPackData(s); }

/** unpack the differences to this object from storage. */
inline void unPackDataDiff(dueca::AmorphReStore& s,
                           SimulatorMotionState& o)
{ o.unPackDataDiff(s); }
#endif

namespace std {
/** print to a stream. */
inline std::ostream &
operator << (std::ostream& s, const SimulatorMotionState& o)
{ return o.print(s); }
};

#if !defined(__DCO_STANDALONE)
namespace dueca {
/** Template specialization, defines a trait that is needed if
    SimulatorMotionState is ever used inside other dco objects. */
template <>
struct dco_nested<SimulatorMotionState> : public dco_isnested { };
};
#endif


#endif