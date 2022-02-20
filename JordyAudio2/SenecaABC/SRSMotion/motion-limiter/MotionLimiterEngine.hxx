/* ------------------------------------------------------------------   */
/*      item            : MotionLimiterEngine.hxx
        made by         : Rene' van Paassen
        date            : 19990324
	category        : header file 
        description     : 
	changes         : 19990324 Rvp first version
	                  010723 DUECA first version OS
	                  010809 OS renamed from MotionLimiter
			  adapted for DUECA
			  020814 Updated to use MTL, checked against
			  the reference implementation in scilab; it works!
        language        : C++
*/

#ifndef MotionLimiterEngine_hh
#define MotionLimiterEngine_hh

#ifdef MotionLimiterEngine_cc
const static char h_id[] =
"$Id: MotionLimiterEngine.hxx,v 1.9 2017/08/07 16:12:03 ostroosma Exp $";
#endif

#ifdef USING_EIGEN3
#include <Eigen/Dense>

// a normal matrix, allocates its own storage
typedef Eigen::MatrixXd Matrix;
// 6x6 eigen matrix
typedef Eigen::Matrix<double,3,3> Matrix33d;
typedef Eigen::Matrix<double,6,6> Matrix66d;
typedef Eigen::Matrix<double,3,6> Matrix36d;

// a matrix that takes external storage
typedef Eigen::Map<Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic,Eigen::RowMajor> > MatrixE;
// a normal vector, allocates its own storage
typedef Eigen::VectorXd Vector;
typedef Eigen::Matrix<double,6,1> Vector6d;
typedef Eigen::Matrix<double,4,1> Vector4d; // for quaternions
typedef Eigen::Matrix<double,3,1> Vector3d;

// a vector that takes external storage
typedef Eigen::Map<Eigen::VectorXd> VectorE;

#else
#include <mtl/mtl.h>
using namespace mtl;

// a normal matrix, allocates its own storage 
typedef matrix<double, rectangle<>, dense<>, row_major>::type Matrix;
// a matrix that takes external storage
typedef matrix<double, rectangle<>, dense<external>, row_major>::type MatrixE;

// a normal vector, allocates its own storage 
typedef dense1D<double> Vector;
// a vector that takes external storage
typedef external_vec<double> VectorE;

#endif

#include <vector>
#include <cmath>


class SimulatorMotionAcceleration;

// defines for the status word
#define MOTION_TEST		0X01
#define JACK_BRAKE		0X02
#define JACK_MIN		0X04
#define JACK_MAX		0X08

/** A class that can check and if necessary limit the acceleration
    inputs to a Stewart-type motion platform. The current
    implementation uses a regular configuration, with the gimbal
    points on a circle, regularly spaced, but the principle works for
    any six-legged device. Based on calculation of jack length,
    velocity and acceleration, braking decisions are made and
    implemented, to precisely stop the jacks at the maximum or minimum
    length. */
class MotionLimiterEngine
{
  /** For debugging, the main in EngineTest must be our friend. */
  friend int main();

  /** An enumerated type, defining the state of each of the
      actuators/jacks. */
  enum JackState {
    ARRIVED_MAX = -3,
    HOLD_MAX = -2,
    BRAKE_NEGATIVE = -1,
    MOVING = 0,
    BRAKE_POSITIVE = 1,
    HOLD_MIN = 2,
    ARRIVED_MIN = 3
  };
#ifdef USING_EIGEN3
 
  /** Position of the upper centroid point, in an earth-fixed
      reference frame. x "forward", parallel to earth, y to the right
      and z pointing down. (0, 0, 0) is the neutral position of the
      simulator. */
  Vector3d xm;

  /** Quaternion, defining the rotation of the simulator cabin. */ 
  Vector4d am;

  /** Velocity of the upper centroid point, in the earth-fixed
      reference frame. */
  Vector3d xmd;

  /** Rotational speed of the cabin, in the cabin-fixed reference
      frame. */
  Vector3d amd;

  /** Length of all six actuators. */
  Vector6d q;

  /** Velocity of all six actuators. */
  Vector6d qd;

  /** Acceleration of all six actuators. */
  Vector6d qdd; 

  /** A vector giving the motion state of all six actuators. */
  std::vector<JackState> js;

  /** Rotation matrix, rotates any vector in the simulator body
      reference frame to a vector in a reference frame parallel to the
      reference frame. */
  Matrix33d Uq;

  /** Input vector, giving the three linear accelerations, in the ef
      reference frame, and the three rotational accelerations, in the
      body reference frame, but corrected for any braking actions to
      keep within the motion limits. */
  Vector6d amf_safe;
  
  /// \group Data about platform geometry 
  //@{
  /** Geometry of the upper gimbal points, in body reference frame. */
  Matrix36d UGgeom;

  /** Geometry of the lower gimbal points, in earth-fixed reference
      frame. */
  Matrix36d LGgeom;

  /** Position of the upper gimbal points, in earth-fixed reference
      frame. */
  Matrix36d UGpos;  
#else
 
  /** Position of the upper centroid point, in an earth-fixed
      reference frame. x "forward", parallel to earth, y to the right
      and z pointing down. (0, 0, 0) is the neutral position of the
      simulator. */
  Vector xm;

  /** Quaternion, defining the rotation of the simulator cabin. */ 
  Vector am;

  /** Velocity of the upper centroid point, in the earth-fixed
      reference frame. */
  Vector xmd;

  /** Rotational speed of the cabin, in the cabin-fixed reference
      frame. */
  Vector amd;

  /** Length of all six actuators. */
  Vector q;

  /** Velocity of all six actuators. */
  Vector qd;

  /** Acceleration of all six actuators. */
  Vector qdd; 

  /** A vector giving the motion state of all six actuators. */
  std::vector<JackState> js;

  /** Rotation matrix, rotates any vector in the simulator body
      reference frame to a vector in a reference frame parallel to the
      ef reference frame. */
  Matrix Uq;

  /** Input vector, giving the three linear accelerations, in the ef
      reference frame, and the three rotational accelerations, in the
      body reference frame, but corrected for any braking actions to
      keep within the motion limits. */
  Vector amf_safe;
  
  /// \group Data about platform geometry 
  //@{
  /** Geometry of the upper gimbal points, in body reference frame. */
  Matrix UGgeom;

  /** Geometry of the lower gimbal points, in earth-fixed reference
      frame. */
  Matrix LGgeom;

  /** Position of the upper gimbal points, in earth-fixed reference
      frame. */
  Matrix UGpos;  
  //@}
#endif
  
  /** Unused. */
  double q_middle;
  
  /** Minimum allowed length of the actuators. */
  double q_min;

  /** Maximum allowed length of the actuators. */
  double q_max;

  /** Maximum allowed acceleration of the actuators. */
  double qdd_max;

  /** Maximum allowed braking acceleration for limiting of the actuators. */
  double qdd_max_braking;

  /** Time step of one update. */
  double dt;

  /** If multiple integration steps fit into one update, time step of
      a single integration step. */
  double dti;

  /** Number of steps in an update. */
  int isteps;

// OS 11SEP2001 make this enum public
public:
  /** State of the complete motion machine. */
  enum MotionState {
    DOWN = 0,
    IN_NEUTRAL = 1,
    ACTIVE = 2, 
    MOTION_TEST_OLD = 3,
    MOTION_FILTER_TEST = 4,
    STILL = 5,
    BRAKING = 6,
    GOING_NEUTRAL = 7,
    GOING_DOWN = 8
  };
private:
  MotionState motion_mode;
  MotionState previous_motion_mode;
  int still_counter, motiontest_count, motiontest_part;
  int motionfiltertest_count, motionfiltertest_part;
  //GenericMotionFilter mf;
#ifdef USING_EIGEN3
  Vector3d xm_down, xm_neutral;
  Vector4d am_down, am_neutral;
#else
  Vector xm_down, am_down, xm_neutral, am_neutral;
#endif

  enum TransitionState {
    INIT,
    ACCELERATE,
    COAST, 
    DECELERATE,
    CLAMP
  };

  // logoc for movements
  TransitionState transition_state[2];

  // constant work files
  Matrix six1s;
  Vector JKacc0, amf, qdd_demand, qdd_brake;
  Vector xm_new, am_new, xmd_new, amd_new;
  Matrix JKvec, JKdir, UGvel, JKdird, jacob, jacobLU;
#ifndef USING_EIGEN3
  dense1D<int> jacobP;
#endif

  Vector amf_still;
  Vector correction;

  // some constants, hopefully good for a normal range of motion
  // systems
  static const double negligible_dist;
  static const double qd_almost_zero;
  static const double qdd_almost_zero;
  static const double small_dist;
  static const double clamp_xgain;
  static const double clamp_vgain;
  static const double xmdd_transition;
  static const double amdd_transition;
  static const double xmd_transition;
  static const double amd_transition;
  static const double dm_almost_zero;
  static const double ddm_almost_zero;
  static const double motiontest_xmdd;
  static const double motiontest_amdd;
  static const double motionfiltertest_xmdd;
  static const double motionfiltertest_amdd;

private:
  void plat2jack(const Vector& amf, bool q_only);
  MotionLimiterEngine(const MotionLimiterEngine& );

public:
  /** Constructor for the motion limiting engine. 
      \param JKminlen  Minimum allowed length of the actuators. 
      \param JKmaxlen  Maximum allowed length of the actuators. 
      \param JKmaxacc  Maximum acceleration of the actuators.
      \param JKmaxbrake Maximum braking/limiting acceleration of the actuators.
      \param UGradius  Radius of the circle on which the upper gimbal
                       points lie.
      \param UGphi     Distance between two upper gimbal points, in
                       degrees. 
      \param LGradius  Radius of the circle for the lower gimbal
                       points.
      \param LGphi     Distance between two lower gimbal points. 
      \param Hlg       Z coordinate of the lower gimbal points. 
      \param hard_buffer Distance to the hard stop, from the minimum
                       length of the actuators. 
      \param dt        Time step, in seconds.
      \param isteps    Number of integration steps to take in each
                       time step. */
  MotionLimiterEngine(double JKminlen, double JKmaxlen, double JKmaxacc, double JKmaxbrake,
		      double UGradius, double LGradius,
		      double UGphi, double LGphi, double Hlg, 
		      double hard_buffer,
		      double dt, int isteps);

  /** Destructor. */
  ~MotionLimiterEngine();

  int integrate(/*int motion_mode, */
#ifdef USING_EIGEN3
		 const VectorE& amf_in, Vector6d& amfc,
#else
  		 const VectorE& amf_in, Vector& amfc,
#endif       
		 const MotionState& cmd_motion_mode,
		 MotionState& cur_motion_mode);

  
  int integrate(const SimulatorMotionAcceleration&,
		const MotionState& cmd_motion_mode, 
		MotionState& cur_motion_mode); 
  
  bool goTarget(const Vector& xm_target, 
		const Vector& am_target,
		Vector& amf);
  // OS 13AUG2001 go to a position/attitude
  // "because I say so", probably to sync with actual motion base
  // through position measurement received by MotionController
  bool beTarget(const Vector& xm_target, const Vector& am_target);
  // OS 13AUG2001 Utility to reset at neutral
  inline bool beNeutral(){ motion_mode=IN_NEUTRAL; return beTarget(xm_neutral, am_neutral);}
  // OS 15AUG2001 Utility to reset at down
  inline bool beDown(){ motion_mode=DOWN; return beTarget(xm_down, am_down);}
  
  inline double getJackLength(int jack) {return q[jack-1];};
  inline double getJackVelocity(int jack) {return qd[jack-1];};
  inline double getJackAcceleration(int jack) {return qdd[jack-1];}
  inline double getPlatformPosition(int idx) {return xm[idx-1];}
  inline double getPlatformVelocity(int idx) {return xmd[idx-1];}
  inline double getPlatformAttitude(int idx) {
    // probably not correct, hopefully it works
    //return (2.0 * asin(am(idx-1))); }
    // OS 20AUG2001, now just export the quaternions
    return am[idx-1]; }

  inline double getPlatformRotation(int idx) {return amd[idx-1];}
  inline double getPlatformAcceleration(int idx) {return amf_safe[idx-1];}// OS 16AUG2001
  inline double getRotationMatrix(int ii, int jj) {return Uq(ii-1,jj-1); }
  inline double getUGPointX(int ii) {return UGpos(0,ii-1);}
  inline double getUGPointY(int ii) {return UGpos(1,ii-1);}
  inline double getUGPointZ(int ii) {return UGpos(2,ii-1);}
  inline double getLGPointX(int ii) {return LGgeom(0,ii-1);}
  inline double getLGPointY(int ii) {return LGgeom(1,ii-1);}
  inline double getLGPointZ(int ii) {return LGgeom(2,ii-1);}
  friend std::ostream& operator << (std::ostream&, const MotionLimiterEngine::MotionState m);
  friend std::ostream& operator << (std::ostream&, const MotionLimiterEngine::JackState m);
#ifdef USING_EIGEN3
  inline const Matrix& getJacob() const { return jacob;}
  inline const Matrix36d& getUGPoints() const {return this->UGpos; }
  inline const Vector& getKinAcc() const {return JKacc0; }
  inline const Matrix& getJKdir() const {return JKdir;}
  inline const Matrix& getUGvel() const {return UGvel;}
  inline const Matrix& getJKdird() const {return JKdird;}
#else
  inline const Matrix& getJacob() const { return jacob;}
  inline const Matrix& getUGPoints() const {return this->UGpos; }
  inline const Vector& getKinAcc() const {return JKacc0; }
  inline const Matrix& getJKdir() const {return JKdir;}
  inline const Matrix& getUGvel() const {return UGvel;}
  inline const Matrix& getJKdird() const {return JKdird;}
#endif
  inline void setDt(double newdt) {dt = newdt; dti = newdt/isteps;}
};


#endif





