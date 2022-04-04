/* ------------------------------------------------------------------ */
/*      item            : MotionCommandedPosVelAcc.hxx
        generated by    : matteo (matteo)
        date            : Thu 24 Mar 2022
        category        : header file
        description     : DUECA Communication Object (DCO)
                          automatically generated by dueca-codegen
        codegen version : 110
        language        : C++
*/

#ifndef MotionCommandedPosVelAcc_hxx
#define MotionCommandedPosVelAcc_hxx

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
#error "Generated MotionCommandedPosVelAcc.hxx too old, please clean with 'make mrproper'"
#endif
#include <CommObjectTraits.hxx>
#endif
#include <iostream>




/**setpoints for positions, velocities and accelerations
   in sim inertial, except of course (p/q/r[dot])
   06JUN2002 origin of reference frame in UpperGimbalCenter, may change in future
   FROM MotionLimiter
   TO MotionController
   NOTE (29APR2002: deprecated) status is bitmask with 0x01 as testbit
        no output to motion base when testbit is set!
    */
struct MotionCommandedPosVelAcc
{
  /** typedef for internal reference */
  typedef MotionCommandedPosVelAcc __ThisDCOType__;

public:
  /** The name of this class. */
  static const char* const classname;


  /** A class member */
  int status;

  /** A class member */
  double x;

  /** A class member */
  double y;

  /** A class member */
  double z;

  /** A class member */
  double phi;

  /** A class member */
  double theta;

  /** A class member */
  double psi;

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
  double xdotdot;

  /** A class member */
  double ydotdot;

  /** A class member */
  double zdotdot;

  /** A class member */
  double pdot;

  /** A class member */
  double qdot;

  /** A class member */
  double rdot;

public:
  /** a "magic" number, hashed out of the class definition,
      that will be used to check consistency of the sent objects
      across the dueca nodes. */
  static const uint32_t magic_check_number;

  /** default constructor. */
  MotionCommandedPosVelAcc();

  /** Constructor with arguments */
  MotionCommandedPosVelAcc(
        const int& status,
        const double& x,
        const double& y,
        const double& z,
        const double& phi,
        const double& theta,
        const double& psi,
        const double& xdot,
        const double& ydot,
        const double& zdot,
        const double& p,
        const double& q,
        const double& r,
        const double& xdotdot,
        const double& ydotdot,
        const double& zdotdot,
        const double& pdot,
        const double& qdot,
        const double& rdot);

  /** copy constructor. */
  MotionCommandedPosVelAcc(const MotionCommandedPosVelAcc& o);

#if !defined(__DCO_NOPACK)
  /** constructor to restore an MotionCommandedPosVelAcc from amorphous storage. */
  MotionCommandedPosVelAcc(dueca::AmorphReStore& r);
#endif

  /** destructor. */
  ~MotionCommandedPosVelAcc();

#if !defined(__DCO_STANDALONE)
  /** new operator "new", which places objects not on a
      heap, but in one of the memory arenas. This to speed up
      memory management. */
  static void* operator new(size_t size);

  /** new operator "delete", to go with the new version
      of operator new. */
  static void operator delete(void* p);

  /** placement "new", needed for stl. */
  inline static void* operator new(size_t size, MotionCommandedPosVelAcc*& o)
  { return reinterpret_cast<void*>(o); }
#endif

#if !defined(__DCO_NOPACK)
  /** packs the MotionCommandedPosVelAcc into amorphous storage. */
  void packData(::dueca::AmorphStore& s) const;

  /** packs the MotionCommandedPosVelAcc into amorphous storage.
      only differences with a previous object are packed. */
  void packDataDiff(::dueca::AmorphStore& s, const MotionCommandedPosVelAcc& ref) const;

  /** unpacks the MotionCommandedPosVelAcc from an amorphous storage. */
  void unPackData(::dueca::AmorphReStore& s);

  /** unpacks the differences for MotionCommandedPosVelAcc
      from an amorphous storage. */
  void unPackDataDiff(::dueca::AmorphReStore& s);
#endif

  /** Test for equality. */
  bool operator == (const MotionCommandedPosVelAcc& o) const;

  /** Test for inequality. */
  inline bool operator != (const MotionCommandedPosVelAcc& o) const
  { return !(*this == o); }

  /** Assignment operator. */
  MotionCommandedPosVelAcc& operator=(const MotionCommandedPosVelAcc& o);

  /** prints the MotionCommandedPosVelAcc to a stream. */
  std::ostream & print(std::ostream& s) const;
};

#if !defined(__DCO_NOPACK)
/** pack the object into amorphous storage. */
inline void packData(::dueca::AmorphStore& s,
                     const MotionCommandedPosVelAcc& o)
{ o.packData(s); }

/** pack the differences between this object and another
    into amorphous storage. */
inline void packDataDiff(dueca::AmorphStore& s,
                         const MotionCommandedPosVelAcc& o,
                         const MotionCommandedPosVelAcc& ref)
{ o.packDataDiff(s, ref); }

/** unpack the object from amorphous storage. */
inline void unPackData(::dueca::AmorphReStore& s,
                       MotionCommandedPosVelAcc& o)
{ o.unPackData(s); }

/** unpack the differences to this object from storage. */
inline void unPackDataDiff(dueca::AmorphReStore& s,
                           MotionCommandedPosVelAcc& o)
{ o.unPackDataDiff(s); }
#endif

namespace std {
/** print to a stream. */
inline std::ostream &
operator << (std::ostream& s, const MotionCommandedPosVelAcc& o)
{ return o.print(s); }
};

#if !defined(__DCO_STANDALONE)
namespace dueca {
/** Template specialization, defines a trait that is needed if
    MotionCommandedPosVelAcc is ever used inside other dco objects. */
template <>
struct dco_nested<MotionCommandedPosVelAcc> : public dco_isnested { };
};
#endif


#endif
