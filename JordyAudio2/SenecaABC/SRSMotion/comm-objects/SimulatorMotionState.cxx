/* ------------------------------------------------------------------ */
/*      item            : SimulatorMotionState.cxx
        generated by    : matteo (matteo)
        date            : Thu 24 Mar 2022
        category        : body file
        description     : DUECA Communication Object (DCO),
                          automatically generated by dueca-codegen
        codegen version : 110
        language        : C++
*/

#include "SimulatorMotionState.hxx"
#include <iostream>
#include <cassert>
#if !defined(__DCO_NOPACK)
#include <AmorphStore.hxx>
#include <PackUnpackTemplates.hxx>
#endif
#include <DataWriterArraySize.hxx>
#define DOBS(A)
#if !defined(__DCO_STANDALONE)
#include <Arena.hxx>
#include <ArenaPool.hxx>
#include <DataClassRegistrar.hxx>
#include <CommObjectMemberAccess.hxx>
#include <DCOFunctor.hxx>
#include <DCOMetaFunctor.hxx>

#define DO_INSTANTIATE
#include <DataSetSubsidiary.hxx>
#endif




#if !defined(__DCO_STANDALONE)
// static CommObjectMemberAccess objects, that can provide flexible access
// to the members of a SimulatorMotionState object
static ::dueca::CommObjectMemberAccess
  <SimulatorMotionState,double >
  SimulatorMotionState_member_x(&SimulatorMotionState::x, "x");
static ::dueca::CommObjectMemberAccess
  <SimulatorMotionState,double >
  SimulatorMotionState_member_y(&SimulatorMotionState::y, "y");
static ::dueca::CommObjectMemberAccess
  <SimulatorMotionState,double >
  SimulatorMotionState_member_z(&SimulatorMotionState::z, "z");
static ::dueca::CommObjectMemberAccess
  <SimulatorMotionState,double >
  SimulatorMotionState_member_q0(&SimulatorMotionState::q0, "q0");
static ::dueca::CommObjectMemberAccess
  <SimulatorMotionState,double >
  SimulatorMotionState_member_q1(&SimulatorMotionState::q1, "q1");
static ::dueca::CommObjectMemberAccess
  <SimulatorMotionState,double >
  SimulatorMotionState_member_q2(&SimulatorMotionState::q2, "q2");
static ::dueca::CommObjectMemberAccess
  <SimulatorMotionState,double >
  SimulatorMotionState_member_q3(&SimulatorMotionState::q3, "q3");
static ::dueca::CommObjectMemberAccess
  <SimulatorMotionState,double >
  SimulatorMotionState_member_xdot(&SimulatorMotionState::xdot, "xdot");
static ::dueca::CommObjectMemberAccess
  <SimulatorMotionState,double >
  SimulatorMotionState_member_ydot(&SimulatorMotionState::ydot, "ydot");
static ::dueca::CommObjectMemberAccess
  <SimulatorMotionState,double >
  SimulatorMotionState_member_zdot(&SimulatorMotionState::zdot, "zdot");
static ::dueca::CommObjectMemberAccess
  <SimulatorMotionState,double >
  SimulatorMotionState_member_p(&SimulatorMotionState::p, "p");
static ::dueca::CommObjectMemberAccess
  <SimulatorMotionState,double >
  SimulatorMotionState_member_q(&SimulatorMotionState::q, "q");
static ::dueca::CommObjectMemberAccess
  <SimulatorMotionState,double >
  SimulatorMotionState_member_r(&SimulatorMotionState::r, "r");
static ::dueca::CommObjectMemberAccess
  <SimulatorMotionState,double >
  SimulatorMotionState_member_phi(&SimulatorMotionState::phi, "phi");
static ::dueca::CommObjectMemberAccess
  <SimulatorMotionState,double >
  SimulatorMotionState_member_theta(&SimulatorMotionState::theta, "theta");
static ::dueca::CommObjectMemberAccess
  <SimulatorMotionState,double >
  SimulatorMotionState_member_psi(&SimulatorMotionState::psi, "psi");

// assemble the above entries into a table in the order in which they
// appear in the SimulatorMotionState object
static const ::dueca::CommObjectDataTable entriestable[] = {
  { &SimulatorMotionState_member_x },
  { &SimulatorMotionState_member_y },
  { &SimulatorMotionState_member_z },
  { &SimulatorMotionState_member_q0 },
  { &SimulatorMotionState_member_q1 },
  { &SimulatorMotionState_member_q2 },
  { &SimulatorMotionState_member_q3 },
  { &SimulatorMotionState_member_xdot },
  { &SimulatorMotionState_member_ydot },
  { &SimulatorMotionState_member_zdot },
  { &SimulatorMotionState_member_p },
  { &SimulatorMotionState_member_q },
  { &SimulatorMotionState_member_r },
  { &SimulatorMotionState_member_phi },
  { &SimulatorMotionState_member_theta },
  { &SimulatorMotionState_member_psi },
  { NULL }
};

#endif

// class name, static
const char * const SimulatorMotionState::classname = "SimulatorMotionState";

// magic number, hashed from class name and member names / classes
const uint32_t SimulatorMotionState::magic_check_number=0xe1fbb5df;

#if !defined(__DCO_STANDALONE)
// functor table, provides access to user-defined metafunctions through the
// data class registry
static dueca::functortable_type functortable;

// register this class, provides access to a packing/unpacking object,
// and to the member access tables
static ::dueca::DataClassRegistrar registrar
  (SimulatorMotionState::classname, NULL,
   entriestable, &functortable,
   new ::dueca::DataSetSubsidiary<SimulatorMotionState>());

#endif

#ifndef __CUSTOM_DEFAULT_CONSTRUCTOR
SimulatorMotionState::SimulatorMotionState()
{
  DOBS("default constructor SimulatorMotionState");
}
#endif

#ifndef __CUSTOM_FULL_CONSTRUCTOR
SimulatorMotionState::SimulatorMotionState(
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
        const double& psi) :
    x(x),
    y(y),
    z(z),
    q0(q0),
    q1(q1),
    q2(q2),
    q3(q3),
    xdot(xdot),
    ydot(ydot),
    zdot(zdot),
    p(p),
    q(q),
    r(r),
    phi(phi),
    theta(theta),
    psi(psi)
{
  DOBS("complete constructor SimulatorMotionState");
}
#endif

#ifndef __CUSTOM_FULLSINGLES_CONSTRUCTOR
#endif

#ifndef __CUSTOM_COPY_CONSTRUCTOR
SimulatorMotionState::SimulatorMotionState(const SimulatorMotionState& other):
    x(other.x),
    y(other.y),
    z(other.z),
    q0(other.q0),
    q1(other.q1),
    q2(other.q2),
    q3(other.q3),
    xdot(other.xdot),
    ydot(other.ydot),
    zdot(other.zdot),
    p(other.p),
    q(other.q),
    r(other.r),
    phi(other.phi),
    theta(other.theta),
    psi(other.psi)
{
  DOBS("copy constructor SimulatorMotionState");
}
#endif

#if !defined(__CUSTOM_AMORPHRESTORE_CONSTRUCTOR) && !defined(__DCO_NOPACK)
SimulatorMotionState::SimulatorMotionState(dueca::AmorphReStore& s):
        x(s),
        y(s),
        z(s),
        q0(s),
        q1(s),
        q2(s),
        q3(s),
        xdot(s),
        ydot(s),
        zdot(s),
        p(s),
        q(s),
        r(s),
        phi(s),
        theta(s),
        psi(s)
{
  DOBS("amorph constructor SimulatorMotionState");
}
#endif

#if !defined(__CUSTOM_ARRAY_SIZE_INIT_CONSTRUCTOR)
#endif

#ifndef __CUSTOM_DESTRUCTOR
SimulatorMotionState::~SimulatorMotionState()
{
  DOBS("destructor SimulatorMotionState");
}
#endif

#if !defined(__DCO_STANDALONE)
void* SimulatorMotionState::operator new(size_t size)
{
  DOBS("operator new SimulatorMotionState");
  static ::dueca::Arena* my_arena = arena_pool.findArena
    (sizeof(SimulatorMotionState));
  return my_arena->alloc(size);
}

void SimulatorMotionState::operator delete(void* v)
{
  DOBS("operator delete SimulatorMotionState");
  static ::dueca::Arena* my_arena = arena_pool.findArena
    (sizeof(SimulatorMotionState));
  my_arena->free(v);
}
#endif

#if !defined(__CUSTOM_FUNCTION_PACKDATADIFF) && !defined(__DCO_NOPACK)
void SimulatorMotionState::packDataDiff(::dueca::AmorphStore& s, const SimulatorMotionState& ref) const
{
  DOBS("packDataDiff SimulatorMotionState");
  ::dueca::IndexMemory im;
  ::dueca::checkandpackdiffsingle(this->x, ref.x,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->y, ref.y,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->z, ref.z,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->q0, ref.q0,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->q1, ref.q1,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->q2, ref.q2,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->q3, ref.q3,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->xdot, ref.xdot,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->ydot, ref.ydot,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->zdot, ref.zdot,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->p, ref.p,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->q, ref.q,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->r, ref.r,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->phi, ref.phi,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->theta, ref.theta,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->psi, ref.psi,
                         s, im);
  im.closeoff(s);
}
#endif

#if !defined(__CUSTOM_FUNCTION_UNPACKDATA) && !defined(__DCO_NOPACK)
void SimulatorMotionState::unPackData(::dueca::AmorphReStore& s)
{
  DOBS("unPackData SimulatorMotionState");

  ::unPackData(s, this->x);
  ::unPackData(s, this->y);
  ::unPackData(s, this->z);
  ::unPackData(s, this->q0);
  ::unPackData(s, this->q1);
  ::unPackData(s, this->q2);
  ::unPackData(s, this->q3);
  ::unPackData(s, this->xdot);
  ::unPackData(s, this->ydot);
  ::unPackData(s, this->zdot);
  ::unPackData(s, this->p);
  ::unPackData(s, this->q);
  ::unPackData(s, this->r);
  ::unPackData(s, this->phi);
  ::unPackData(s, this->theta);
  ::unPackData(s, this->psi);

}
#endif

#if !defined(__CUSTOM_FUNCTION_UNPACKDATADIFF) && !defined(__DCO_NOPACK)
void SimulatorMotionState::unPackDataDiff(dueca::AmorphReStore& s)
{
  DOBS("unPackDataDiff SimulatorMotionState");
  ::dueca::IndexRecall im;
  ::dueca::checkandunpackdiffsingle(this->x, s, im);
  ::dueca::checkandunpackdiffsingle(this->y, s, im);
  ::dueca::checkandunpackdiffsingle(this->z, s, im);
  ::dueca::checkandunpackdiffsingle(this->q0, s, im);
  ::dueca::checkandunpackdiffsingle(this->q1, s, im);
  ::dueca::checkandunpackdiffsingle(this->q2, s, im);
  ::dueca::checkandunpackdiffsingle(this->q3, s, im);
  ::dueca::checkandunpackdiffsingle(this->xdot, s, im);
  ::dueca::checkandunpackdiffsingle(this->ydot, s, im);
  ::dueca::checkandunpackdiffsingle(this->zdot, s, im);
  ::dueca::checkandunpackdiffsingle(this->p, s, im);
  ::dueca::checkandunpackdiffsingle(this->q, s, im);
  ::dueca::checkandunpackdiffsingle(this->r, s, im);
  ::dueca::checkandunpackdiffsingle(this->phi, s, im);
  ::dueca::checkandunpackdiffsingle(this->theta, s, im);
  ::dueca::checkandunpackdiffsingle(this->psi, s, im);
}
#endif

#ifndef __CUSTOM_OPERATOR_EQUAL
bool SimulatorMotionState::operator == (const SimulatorMotionState& other) const
{
  DOBS("operator == SimulatorMotionState");
  if (this->x != other.x) return false;
  if (this->y != other.y) return false;
  if (this->z != other.z) return false;
  if (this->q0 != other.q0) return false;
  if (this->q1 != other.q1) return false;
  if (this->q2 != other.q2) return false;
  if (this->q3 != other.q3) return false;
  if (this->xdot != other.xdot) return false;
  if (this->ydot != other.ydot) return false;
  if (this->zdot != other.zdot) return false;
  if (this->p != other.p) return false;
  if (this->q != other.q) return false;
  if (this->r != other.r) return false;
  if (this->phi != other.phi) return false;
  if (this->theta != other.theta) return false;
  if (this->psi != other.psi) return false;
  return true;
}
#endif

#ifndef __CUSTOM_OPERATOR_ASSIGN
SimulatorMotionState&
SimulatorMotionState::operator=(const SimulatorMotionState& other)
{
  DOBS("operator = SimulatorMotionState");
  if (this == &other) return *this;
  this->x = other.x;
  this->y = other.y;
  this->z = other.z;
  this->q0 = other.q0;
  this->q1 = other.q1;
  this->q2 = other.q2;
  this->q3 = other.q3;
  this->xdot = other.xdot;
  this->ydot = other.ydot;
  this->zdot = other.zdot;
  this->p = other.p;
  this->q = other.q;
  this->r = other.r;
  this->phi = other.phi;
  this->theta = other.theta;
  this->psi = other.psi;
  return *this;
}
#endif

#if !defined(__CUSTOM_FUNCTION_PACKDATA) && !defined(__DCO_NOPACK)
void SimulatorMotionState::packData(::dueca::AmorphStore& s) const
{
  DOBS("packData SimulatorMotionState");
  ::packData(s, this->x);
  ::packData(s, this->y);
  ::packData(s, this->z);
  ::packData(s, this->q0);
  ::packData(s, this->q1);
  ::packData(s, this->q2);
  ::packData(s, this->q3);
  ::packData(s, this->xdot);
  ::packData(s, this->ydot);
  ::packData(s, this->zdot);
  ::packData(s, this->p);
  ::packData(s, this->q);
  ::packData(s, this->r);
  ::packData(s, this->phi);
  ::packData(s, this->theta);
  ::packData(s, this->psi);
}
#endif

#ifndef __CUSTOM_FUNCTION_PRINT
std::ostream & SimulatorMotionState::print(std::ostream& s) const
{
  s << "SimulatorMotionState("
    << "x=" << this->x << ','
    << "y=" << this->y << ','
    << "z=" << this->z << ','
    << "q0=" << this->q0 << ','
    << "q1=" << this->q1 << ','
    << "q2=" << this->q2 << ','
    << "q3=" << this->q3 << ','
    << "xdot=" << this->xdot << ','
    << "ydot=" << this->ydot << ','
    << "zdot=" << this->zdot << ','
    << "p=" << this->p << ','
    << "q=" << this->q << ','
    << "r=" << this->r << ','
    << "phi=" << this->phi << ','
    << "theta=" << this->theta << ','
    << "psi=" << this->psi
    << ')';
  return s;
}
#endif


