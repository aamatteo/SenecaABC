/* ------------------------------------------------------------------   */
/*      item            : MotionLimiterEngine.cc
        made by         : Rene' van Paassen
        date            : 19990324
	category        : body file
        description     :
	changes         : 19990324 RvP first version
	20010723 OS DUECA first version
	010809 OS renamed from MotionLimiter
	adapted for DUECA
        language        : C++
*/

#ifdef TEST
#include <iostream>
#define D_MOD(A) // cerr << A << endl;
#define I_MOD(A) // cerr << A << endl;
//cout << A << endl;
#define W_MOD(A) cerr << A << endl;
#define E_MOD(A) cerr << A << endl;
#else
//#define D_MOD
#define I_MOD
#define W_MOD
#define E_MOD
#include <debug.h>
#endif
//#define DDEB( A ) cout << A << endl
//#define DDEB( A )

#define MotionLimiterEngine_cc
#include "MotionLimiterEngine.hxx"
#include "MotionAux.hxx"
#include <cmath>
#ifdef USING_EIGEN3
#define copy(A, B) B = A
#define print_vector( A ) std::cout << #A << ": " << A << std::endl;
#else
#include <mtl/lu.h>
#include <mtl/matrix.h>
#endif

//#include "SimulatorMotionAcceleration.hxx"
//#include "SimulatorMotionState.hxx"
#include "comm-objects.h"
//#include "../MotionFilter/GenericMotionFilter.hxx"

// NO_CHECK = true practically disables the MotionLimiter
// TO CHECK! maybe this should be taken out OS 9AUG2001
#define NO_CHECK false

const double MotionLimiterEngine::negligible_dist = 1.0e-5;
const double MotionLimiterEngine::qd_almost_zero = 0.005;
const double MotionLimiterEngine::qdd_almost_zero = 0.005;
const double MotionLimiterEngine::small_dist = 0.005;
const double MotionLimiterEngine::clamp_xgain =  40.0;//100.0; // up to 100 if needed, was 50.0 [OS 26JUL2002]
const double MotionLimiterEngine::clamp_vgain = 20.0; //50.0; // up to 50 if needed, was 20.0 [OS]. 20 again
const double MotionLimiterEngine::xmdd_transition = 0.2;
const double MotionLimiterEngine::amdd_transition = 0.1;
const double MotionLimiterEngine::xmd_transition = 0.2;
const double MotionLimiterEngine::amd_transition = 0.1;
const double MotionLimiterEngine::dm_almost_zero = 0.001;
const double MotionLimiterEngine::ddm_almost_zero = 0.002;
const double MotionLimiterEngine::motiontest_xmdd = 0.1;
const double MotionLimiterEngine::motiontest_amdd = 0.1;
const double MotionLimiterEngine::motionfiltertest_xmdd = 0.3;
const double MotionLimiterEngine::motionfiltertest_amdd = 0.3;

template<class T>
inline void limit(const T& tmin, T& tolimit, const T& tmax)
{
  if (tolimit > tmax) tolimit = tmax;
  if (tolimit < tmin) tolimit = tmin;
}

MotionLimiterEngine::MotionLimiterEngine(double q_min, double q_max,
					 double qdd_max, double qdd_max_braking,
					 double UGradius, double LGradius,
					 double UGphi, double LGphi, double Hlg,
					 double hard_buffer,
					 double dt, int isteps) :
#ifdef USING_EIGEN3
  xm(), am(), xmd(), amd(),
  q(), qd(), qdd(), js(7), Uq(), amf_safe(),
  UGgeom(), LGgeom(), UGpos(),
#else
  
  xm(3), am(4), xmd(3), amd(3),
  q(6), qd(6), qdd(6), js(7), Uq(3,3), amf_safe(6),
  UGgeom(3,6), LGgeom(3,6), UGpos(3,6),
#endif
  q_middle(0.5*(q_min+q_max)),
  q_min(q_min), q_max(q_max), qdd_max(qdd_max), qdd_max_braking(qdd_max_braking),
  dt(dt), dti(dt / isteps), isteps(isteps),
  motion_mode(DOWN), 
  previous_motion_mode(DOWN),
  still_counter(-1), motiontest_count(-1),
  motiontest_part(int(1.5/dt)), motionfiltertest_count(-1),
  motionfiltertest_part(int(5.0/dt)),
#ifdef USING_EIGEN3
  xm_down(), xm_neutral(), am_down(), am_neutral(),
#else
  xm_down(3), am_down(4), xm_neutral(3), am_neutral(4),
#endif
  six1s(1, 6), JKacc0(6), amf(6), qdd_demand(6), qdd_brake(6),
  xm_new(3), am_new(4), xmd_new(3), amd_new(3),
  JKvec(3,6), JKdir(3,6), UGvel(3,6), JKdird(3,6), jacob(6,6),
  jacobLU(6,6),
#ifndef USING_EIGEN3
  jacobP(6),
#endif
  amf_still(6),
  correction(6)
{
  // calculate the geometry matrix for the lower gimbal
  // odd upper gimbal points, assumes a triangle pointing in x direction
  double psi0d = UGphi * 0.5;
  for (int ii = 0; ii < 6; ii += 2) {
    UGgeom(0,ii) = cos(psi0d) * UGradius;
    UGgeom(1,ii) = sin(psi0d) * UGradius;
    UGgeom(2,ii) = 0.0;
    psi0d += M_PI * 2.0/3.0;
  }

  // even upper gimbal points
  psi0d = -UGphi * 0.5;
  for (int ii = 1; ii < 6; ii += 2) {
    psi0d += M_PI * 2.0/3.0;
    UGgeom(0,ii) = cos(psi0d) * UGradius;
    UGgeom(1,ii) = sin(psi0d) * UGradius;
    UGgeom(2,ii) = 0.0;
  }

  //DDEB("UGgeom " << UGgeom << endl);
  //D_MOD("UGgeom");
#ifdef D_MOD_ACTIVE
  //print_all_matrix(UGgeom);
#endif

  // odd lower gimbal points, correspond to odd upper gimbal points too
  psi0d = M_PI / 3.0 - LGphi*0.5;
  for (int ii = 0; ii < 6; ii += 2) {
    LGgeom(0,ii) = cos(psi0d) * LGradius;
    LGgeom(1,ii) = sin(psi0d) * LGradius;
    LGgeom(2,ii) = Hlg;
    psi0d += M_PI * 2.0/3.0;
  }

  // even lower gimbal points
  psi0d = M_PI / 3.0 + LGphi*0.5;
  for (int ii = 1; ii < 6; ii += 2) {
    LGgeom(0,ii) = cos(psi0d) * LGradius;
    LGgeom(1,ii) = sin(psi0d) * LGradius;
    LGgeom(2,ii) = Hlg;
    psi0d += M_PI * 2.0/3.0;
  }
  //D_MOD("LGgeom");
#ifdef D_MOD_ACTIVE
  //print_all_matrix(LGgeom);
#endif

#ifdef USING_EIGEN3
  am_down.setZero(); am_down(3) = 1.0;
  am_neutral = am_down;
  am = am_down; 
  xm_down.setZero();
  xm_neutral.setZero();
  xm.setZero();
  amf.setZero();
#else
  // neutral and down position stuff
  mtl::set(am_down, 0.0); am_down[3] = 1.0; // quaternion!
  copy(am_down, am);                        // am = am_down;
  copy(am_down, am_neutral);                // am_neutral = am_down;
  scale(xm_neutral, 0.0);                   // xm_neutral = 0.0;
  copy(xm_neutral, xm);                     // xm = xm_neutral
  copy(xm_neutral, xm_down);                // xm_down = xm_neutral;

  // dummy vectors to use the plat2jack routine
  // TO CHECK! masking member variables? OS
  Vector xmd(3), amd(3);
  mtl::set(xmd, 0.0); mtl::set(amd, 0.0); mtl::set(amf, 0.0);

  // plat2jack uses six1s. 
  mtl::set(six1s, 1.0);
#endif
  // use plat2jack to calculate the length of the cylinders
  plat2jack(amf, false);// 090401 OS was (amf, false)
  while (q[0] > q_min - hard_buffer + 0.005) {
    // step "down" in small steps, to find the lower position of the
    // platform
    xm[2] += 0.001;
    plat2jack(amf, true);
  }
  plat2jack(amf, true);// 090401 OS was (amf, false)
  //D_MOD("lower platform position: " << xm);
#ifdef D_MOD_ACTIVE
  print_vector(xm);
#endif

  // TO CHECK! OS: where do we start?
  // copy the state, initial in down
#ifdef USING_EIGEN3
  xm_down = xm;
  am_down = am;
  amf_safe.setZero();
#else
  copy(xm, xm_down); //  xm_down=xm;
  //print_vector(xm_down);
  copy(am, am_down); // am_down=am;
  // OS 16AUG2001
  mtl::set(amf_safe, 0.0);
#endif
  motion_mode = DOWN;


  // assume initial state of the jacks is moving.
  for (int ii = 0; ii <= 5; ii++)
    js[ii] = MOVING;
  
  // prepare the rotation matrix
  u_quat(am, Uq);
}


MotionLimiterEngine::~MotionLimiterEngine()
{
  // apparently nothing else
}

// calculates the new jack lengths and (optionally) the
// jack velocities and accelerations and puts it in the member
// variables q, qd and qdd. These are then up-to-date.
// It gets its data from the member variables in the motion state
// (am, xm, amd, xmd) and the proposed accelerations in parameter amf
// This amf is only a proposal since braking actions can limit the
// final accelerations
void MotionLimiterEngine::plat2jack(const Vector& amf,
				    bool q_only)
{
  // calculate the projection matrix for the quaternion orientation
  u_quat(am, Uq);

  // with this, the position of the upper gimbal points is calculated
  //  UGpos = Uq * UGgeom + xm * six1s;
#ifdef USING_EIGEN3
  static Eigen::Matrix<double,1,6> six1s = Eigen::Matrix<double,1,6>::Ones();
  UGpos = Uq * UGgeom + xm * six1s;
  JKvec = UGpos - LGgeom;
  for (int ii = 0; ii < 6; ii++) {
    q[ii] = JKvec.block<3,1>(0,ii).norm();
    JKdir.block<3,1>(0,ii) = JKvec.block<3,1>(0,ii).normalized();
  }
#else
  double w1[18], w2[18]; MatrixE m1(w1, 3, 6), m2(w2, 3, 6);
  mtl::set(UGpos, 0.0);      // matrix mult adds to old data!
  mult(Uq, UGgeom, UGpos);
  mtl::set(m1, 0.0);
  mult(MatrixE(xm.data(), 3, 1), six1s, m1);
  add(m1, UGpos);
  
  //DDEB("UGpos" << UGpos << "xm" << xm << "six1s" << six1s);

  // JKvec contains the vectors from lower to upper gimbal points
  // JKvec = UGpos - LGgeom;
  copy(scaled(LGgeom, -1.0), JKvec);
  add(UGpos, JKvec);

  //print_all_matrix(JKvec);

  // Now we normalise these vectors, to get direction vectors.
  copy(JKvec, JKdir);
  for (int ii = 0; ii < 6; ii++) {
    q[ii] = sqrt(sum_squares(columns(JKvec)[ii]));
    scale(columns(JKdir)[ii], 1.0/q[ii]);
  }
#endif
  
  //DDEB("JKdir" << JKdir);
  // if we only want the jack lengths, we're done
  if (q_only) return;
  
#ifdef USING_EIGEN3
  // velocity upper gimbal points
  for (int ii = 6; ii--; ) {
    UGvel.block<3,1>(0,ii) = xmd + amd.cross(Uq * UGgeom.block<3,1>(0,ii));
  }

  // jacobian
  // 1st 3 columns of the jacobian are from the direction vectors
  jacob.block<6,3>(0,0) = JKdir.transpose();
  // next 3 are cross product with direction vectors
  for (int ii = 6; ii--; ) {
    jacob.block<1,3>(ii,3) = (Uq * UGgeom.block<3,1>(0,ii)).cross(JKdir.block<3,1>(0,ii));
  }
  
  // jack extension velocity, based on jacobian
  Vector6d v5; v5.block<3,1>(0,0) = xmd; v5.block<3,1>(3,0) = amd;
  qd = jacob * v5;

  // jack direction vector derivative
  for (int ii = 0; ii < 6; ii++) {
    // v4 is velocity UG point in 3d, re-used later
    Vector3d v4 = xmd + amd.cross(Uq * UGgeom.block<3,1>(0,ii));
    JKdird.block<3,1>(0,ii) = (-qd(ii)*JKdir.block<3,1>(0,ii) + v4) / q(ii);

    JKacc0(ii) = JKdir.block<3,1>(0,ii).dot(amd.cross(v4)) +
      q(ii) * JKdird.block<3,1>(0,ii).squaredNorm();
  }
  qdd = JKacc0 + jacob * amf;
  
#else
  // Calculate the velocity of the ug points
  double w3[3], w4[3]; VectorE v3(w3, 3), v4(w4, 3);  
  for (int ii = 0; ii < 6; ii++) {
    mult(Uq, columns(UGgeom)[ii], v3);
    cross(amd, v3, v4);
    add(xmd, v4, columns(UGvel)[ii]);
    // UGvel.Column(ii) = xmd + cross(amd, Uq * UGgeom.Column(ii));
  }
  //DDEB("UGvel" << UGvel);

  // construct a jacobian
  //  for (int ii = 1; ii <=6; ii++) {
  //  jacob.Row(ii) = (JKdir.Column(ii) &
  //    cross(Uq*UGgeom.Column(ii), JKdir.Column(ii))).t();
  //}
  // the first three columns contain the transpose of the direction
  // matrix
  copy(columns(trans(JKdir))[0], columns(jacob)[0]);
  copy(columns(trans(JKdir))[1], columns(jacob)[1]);
  copy(columns(trans(JKdir))[2], columns(jacob)[2]);
  for (int ii = 6; ii--; ) {
    mult(Uq, columns(UGgeom)[ii], v3);
    cross(v3, columns(JKdir)[ii], v4);
    for (int jj = 3; jj--; ) jacob(ii, 3+jj) = v4[jj];
  }

  /*  jacob = JKdir.t() |
    (cross(Uq*(UGgeom.Column(1)), JKdir.Column(1)).t() &
     cross(Uq*(UGgeom.Column(2)), JKdir.Column(2)).t() &

     cross(Uq*(UGgeom.Column(3)), JKdir.Column(3)).t() &
     cross(Uq*(UGgeom.Column(4)), JKdir.Column(4)).t() &
     cross(Uq*(UGgeom.Column(5)), JKdir.Column(5)).t() &
     cross(Uq*(UGgeom.Column(6)), JKdir.Column(6)).t()); */

  //DDEB("jacob" << jacob);
  
  // extension velocity is to be calculated as:
  double w5[6]; VectorE v5(w5, 6);
  for (int ii = 3; ii--; ) {
    v5[ii] = xmd[ii];
    v5[ii+3] = amd[ii];
  }
  mult(jacob, v5, qd);
  //qd = jacob * (xmd & amd);

  // next piece of work; calculating the extension / contraction
  // ACCELERATION of the jacks. First in 3d. Two contributions are
  // recognised; one due to acceleration itself, the other due to
  // "coriolis" effects; the turning of the platform.

  // this implementation is partly based on Haeck, achieved by
  // differentiation of the solution for the velocity given there

  for (int ii = 0; ii < 6; ii++) {
    // calculation 1; derivative of the Jack direction vectors
    //JKdird.Column(ii) = (-qd(ii)*JKdir.Column(ii) + xmd +
    //			 cross(amd, Uq*UGgeom.Column(ii))) / q(ii);
    mult(Uq, columns(UGgeom)[ii], v3);
    cross(amd, v3, v4);
    add(v4, xmd, v3);
    add(v3, scaled(columns(JKdir)[ii], -qd[ii]), columns(JKdird)[ii]);
    scale(columns(JKdird)[ii], 1.0/q[ii]);

    // calculation 2, kinematic jack acceleration
    //JKacc0.Row(ii) = q(ii)*((JKdird.Column(ii)).t()*JKdird.Column(ii)) +
    //  (JKdir.Column(ii)).t()*
    //  (cross(amd, cross(amd, Uq*UGgeom.Column(ii))));
    // v4 still contains: cross(amd, Uq*UGgeom.Column(ii))
    cross(amd, v4, v3);
    JKacc0[ii] =  dot(columns(JKdir)[ii], v3) + 
      q[ii] * dot(columns(JKdird)[ii], columns(JKdird)[ii]);
  }
  //DDEB("JKdird" << JKdird);

  mult(jacob, amf, v5);
  add(v5, JKacc0, qdd);
  //qdd = jacob * amf + JKacc0;  // corrected from -
#endif
  // check for maximum jack acceleration [OS] 14-7
  // OS 9AUG01 should probably send a motion message
  // OS 21AUG2001 maybe obsolete
  /*  for (int ii = 0; ii < 6; ii++){
    if (qdd[ii] > qdd_max || qdd[ii] < -qdd_max)
      I_MOD("max jack acceleration # " << ii);
    if (qd[ii] > 2.0 || qd[ii] < -2.0)
      I_MOD("jack velocity > 2.0 m/s for jack # " << ii);
  }
  */
  //DDEB("qdd" << qdd);
}


int MotionLimiterEngine::integrate(const VectorE& amf_in, // proposed acc. by motionfilter
#ifdef USING_EIGEN3
				   Vector6d& amfc,			// corrected (safe) acc.
#else
				   Vector& amfc,			// corrected (safe) acc.                                   
#endif
				   const MotionState& m_mode,	// commanded motion mode
				   MotionState& cur_m_mode)		// current motion mode output
{
  // OS: the status word with info on jack states
  // for now (21AUG2001) only aggregate info, maybe later per jack info.
  // this status is combined with the test bit by the MotionLimiter
  int status = 0;
  
  // we work with the proposed accelerations coming from the DUECA MotionLimiter module
  // TO CHECK! eliminate the temporary amf and use only amf_in?
  // OS 14AUG2001: to limit dependence on newmat, maybe only use array params
  // and put them in like amf << in_array; Note: no bounds checking!
#ifdef USING_EIGEN3
  amf = amf_in;
#else
  copy(amf_in, amf);
#endif
  // attempt to steer the cabin slowly to neutral during demo motions
  // needed because of numerical instability when driving the accelerations
  // old code from MotionDemo S/W
/* 	ColumnVector xd(3);
	ColumnVector ad(3);
	ColumnVector xdd(3);
	ColumnVector add(3);
	xd << 0.0 << 0.0 << 0.0;
	ad << 0.0 << 0.0 << 0.0;
	xdd << 0.0 << 0.0 << 0.0;
	add << 0.0 << 0.0 << 0.0;

 */

  // old code from MotionDemo
  // amf_in is already filtered by the DUECA MotionLimiter module
  //amf += mf.filter(xd, ad, xdd, add, xm, am, xmd, amd);
  
  // OS 9AUG2001 Begin of state machine governing up, down, active...
  // We don't care about that any more: the MotionController controls
  // this now through open loop commands to the Motion Control Cabinet
  // Therefore no more motion base knowledge is needed for this.
  // OS 11SEP2001 Update: we do need to brake to go from Advance/Active
  // to HoldCurrent/Neutral, so we need this state machine after all

  bool mode_complete;
  if (motion_mode == GOING_DOWN || motion_mode == DOWN) {
    mode_complete = goTarget(xm_down, am_down, amf);
  }
  else {  
    mode_complete = goTarget(xm_neutral, am_neutral, amf);
  }
  
  if (mode_complete) {
    MotionState old_mode = motion_mode;
    // reached a stable state, see if any motion logic required,
    if (motion_mode >= STILL) {
      // internal mode logic, was transitioning
      switch(motion_mode) {
      case STILL:
	motion_mode = GOING_NEUTRAL;
	break;
      case BRAKING:
	motion_mode = STILL;
	break;
      case GOING_NEUTRAL:
	motion_mode = IN_NEUTRAL;
	break;
      case GOING_DOWN:
	motion_mode = DOWN;
	break;
      default:
	break;
      }
    }
    else if (int(motion_mode) != m_mode) {
      // note: this part can only be entered with the motion in one of
      // the static modes; DOWN, IN_NEUTRAL, ACTIVE, MOTION_TEST or
      // MOTION_FILTER_TEST
      switch(m_mode) {
      case 0: // down requested
	// down goes via neutral
	if (motion_mode == IN_NEUTRAL) {
	  motion_mode = GOING_DOWN;
	}
	else if (motion_mode != DOWN) {
	  motion_mode = BRAKING;
	}
	break;
      case 1: // neutral requested
	if (motion_mode == DOWN) {
	  motion_mode = GOING_NEUTRAL;
	}
	else if (motion_mode != IN_NEUTRAL) {
	  motion_mode = BRAKING;
	}	  
	break;
      case 2: // active requested
	// active goes via neutral
	if (motion_mode == IN_NEUTRAL) {
	  motion_mode = ACTIVE;
	  // restore the desired
	  // amf!
	  copy(amf_in, amf);
	}
	else if (motion_mode == DOWN) {
	  motion_mode = GOING_NEUTRAL;
	}
	else if (motion_mode != ACTIVE) {
	  motion_mode = BRAKING;
	}
	break;
      case 3: // test requested
	if (motion_mode == IN_NEUTRAL) {
	  motion_mode = MOTION_TEST_OLD;
	  motiontest_count = -1;
	}
	else if (motion_mode == DOWN) {
	  motion_mode = GOING_NEUTRAL;
	}
	else if (motion_mode != MOTION_TEST_OLD) {
	  motion_mode = BRAKING;
	}
	break;
      case 4: // motion filter test requested
	if (motion_mode == IN_NEUTRAL) {
	  motion_mode = MOTION_FILTER_TEST;
	  motionfiltertest_count = -1; // set the counter to start
	  // with the mf test
	}
	else if (motion_mode == DOWN) {
	  motion_mode = GOING_NEUTRAL;
	}
	else if (motion_mode != MOTION_FILTER_TEST) {
	  motion_mode = BRAKING;
	}
	break;
      default: // noting
	break;
      }
    }
    
    if (old_mode != motion_mode) {
      I_MOD("MotionLimiter mode transition, from " << int(old_mode)
	    << " to " << int(motion_mode));
    }
  }

  // dont check for the following motion modes, since they may pass
  // the buffer limits
  bool no_check = motion_mode == GOING_DOWN || motion_mode == DOWN;
  // || motion_mode == GOING_NEUTRAL; // formerly also RvP 

  // OS 9AUG2001 End of state machine

  // calculate the jack accelerations etc, with this amf
  try {
    plat2jack(amf, false);
  }
  catch (exception& e) {
    cerr << "in plat2jack " << e.what() << endl;
  }
  

  if (!NO_CHECK && !no_check) {
    for (int ii = 0; ii < 6; ii++) {
      
      // calculate the distance from an end point
      // NOTE: this distance is according to the VELOCITY of the jack
      double dist;
      if (qd[ii] > 0) {
	dist = q_max - q[ii];
      }
      else {
	dist = q[ii] - q_min;
      }
      

      // brake state machine

      // test jack speed, position and velocity for transitions in the
      // brake machine

      switch (js[ii]) {
      case MOVING:
	
	if ((dist - fabs(qd[ii])*dt) * qdd_max_braking
	    <= 0.5 * qd[ii]*qd[ii]) {
	  
	  // closing in to the end, time to start braking
	  js[ii] = qd[ii] > 0 ? BRAKE_NEGATIVE : BRAKE_POSITIVE;

	  // calculate the required acceleration to stop at the end
	  if (dist > negligible_dist) {
	    qdd_demand[ii] = int(js[ii]) * 0.5 * qd[ii]*qd[ii] / dist;
	  }
	  else {
	    qdd_demand[ii] = int(js[ii]) * min(qdd_max_braking, fabs(qd[ii]) / dt);
	  }

	  // OS 9AUG2001 probably send a MotionMessage as well
	  I_MOD("MotionLimiter start braking jack " << ii << ", d=" << dist
		<< " v=" << qd[ii] << " a=" << qdd_demand[ii] <<
		" btime=" << qd[ii]/qdd_demand[ii]);
	  
	}
	else {
	  qdd_demand[ii] = qdd[ii];
	}
	break;
	
      case BRAKE_POSITIVE:
      case BRAKE_NEGATIVE:

	// set the status
	status |= (JACK_BRAKE<<4*ii);

	// see whether braking is still necessary
	if (int(js[ii]) * qd[ii] + qdd_max_braking * dt > 0.0) {
	  qdd_demand[ii] = -qd[ii] / dt;
	  if (js[ii] == BRAKE_POSITIVE) {
	    js[ii] = ARRIVED_MIN;
	    I_MOD("MotionLimiter approaching min position jack " << ii);
	  }
	  else {
	    js[ii] = ARRIVED_MAX;
	    I_MOD("MotionLimiter approaching max position jack " << ii);
	  }
	  D_MOD("MotionLimiter d=" << dist << " v=" << qd[ii] 
		<< " demand accel=" << qdd_demand[ii]);
	}
	else {
	  // re-calculate necessary acceleration
	  if (dist > negligible_dist) {
	    qdd_demand[ii] = int(js[ii]) *
	      min(qdd_max_braking, 0.5 * qd[ii]*qd[ii] / dist);
	  }
	  else if (dist > 0.0) {
	    qdd_demand[ii] = int(js[ii]) *
	      min(qdd_max_braking, fabs(qd[ii])/dt);
	  }
	  else {
	    qdd_demand[ii] = int(js[ii]) * qdd_max_braking;
	  }
	}
	break;

      case ARRIVED_MIN:
      case ARRIVED_MAX:

	if (js[ii] == ARRIVED_MIN) {
	  I_MOD("MotionLimiter arrived at min position jack " << 
		ii << ", d=" << q[ii] - q_min << ", v=" << qd[ii]);
	  js[ii] = HOLD_MIN;
	}
	else {
	  I_MOD("MotionLimiter arrived at max position jack " << 
		ii << ", d=" << q[ii] - q_max << ", v=" << qd[ii]);
	  js[ii] = HOLD_MAX;
	}
	// intentional fall-through, now the hold phase begins

      case HOLD_MIN:
      case HOLD_MAX:
	// condition for releasing the brake;
	// 1 - demanded acceleration leads away from the buffer
	// 2 - actual velocity is negligible (no reason for further braking)
	// 3 - we have arrived at the buffer
	if (js[ii] == HOLD_MIN) {
	  if ((int(js[ii]) * qdd[ii] > qdd_almost_zero &&
	       int(js[ii]) * qd[ii] > -qd_almost_zero &&
	       q[ii] - q_min > -small_dist)) {
	    js[ii] = MOVING;
	    qdd_demand[ii] = qdd[ii];
	    I_MOD("MotionLimiter releasing brake jack " << ii 
		  << " qdd=" << qdd[ii]);
	  }
	  else {
	    // damp the motion, keep the jack in neutral position
	    qdd_demand[ii] = -clamp_vgain*qd[ii] - clamp_xgain*(q[ii]-q_min);
	    D_MOD("MotionLimiter holding jack " << ii 
		  << " qdd_demand=" << qdd_demand[ii]
		  << " xerr=" << q[ii] - q_min << " verr=" << qd[ii]);
	  }
	}
	// condition for releasing the brake;
	// 1 - demanded acceleration leads away from the buffer
	// 2 - actual velocity is negligible (no reason for further braking)
	// 3 - we have arrived at the buffer
	else {
	  if ((int(js[ii]) * qdd[ii] > qdd_almost_zero &&
	       int(js[ii]) * qd[ii] > -qd_almost_zero &&
	       q[ii] - q_max < small_dist)) {
	    js[ii] = MOVING;
	    qdd_demand[ii] = qdd[ii];
	    I_MOD("MotionLimiter releasing brake jack " << ii 
		  << " qdd=" << qdd[ii]);
	  }
	  else {
	    // damp the motion, keep the jack in neutral position
	    qdd_demand[ii] = - clamp_vgain*qd[ii] - clamp_xgain*(q[ii]-q_max);
	    D_MOD("MotionLimiter holding jack " << ii 
		  << " qdd_demand=" << qdd_demand[ii]
		  << " xerr=" << q[ii] - q_max << " verr=" << qd[ii]);
	  }
	}
	break;
      }

      // limit the demanded acceleration
      if (qdd_demand[ii] > qdd_max) {
	W_MOD("MotionLimiter limiting jack acceleration #" << ii << 
	      " from " << qdd_demand[ii] << " to " << qdd_max);
	qdd_demand[ii] = qdd_max;
      }
      if (qdd_demand[ii] < -qdd_max) {
	W_MOD("MotionLimiter limiting jack acceleration #" << ii << 
	      " from " << qdd_demand[ii] << " to " << -qdd_max);
	qdd_demand[ii] = -qdd_max;
      }

    }  


#ifdef USING_EIGEN3
    qdd_brake = qdd_demand - qdd;
    correction = jacob.colPivHouseholderQr().solve(qdd_brake);
    amfc = amf + correction;
#else
    // calculate the braking acceleration;
    // qdd_brake = qdd_demand - qdd;
    add(qdd_demand, scaled(qdd, -1.0), qdd_brake);
    /*    if (js[2] != MOVING) {
      cout << "orig, demand, brake" << endl;
      print_vector(qdd);
      print_vector(qdd_demand);
      print_vector(qdd_brake);
      print_vector(amf);
      }*/
  
    // correct the input acceleration to achieve the desired
    // jack accelerations
    mtl::set(jacobP, 0);
    double dt[36]; MatrixE tst(dt,6, 6);
    copy(jacob, tst);
    lu_factor(tst, jacobP);
    lu_inverse(tst, jacobP, jacobLU);
    // test calculation
    mtl::set(tst, 0.0);
    mult(jacob, jacobLU, tst);
    if (0 &&js[2] != MOVING) {
      print_all_matrix(tst);
    }
    mult(jacobLU, qdd_brake, correction);
    //print_all_matrix(jacob);
    //print_vector(qdd_brake);
    //print_vector(correction);
    add(amf, correction, amfc);
    if (0 && js[4] != MOVING) {
      cout << " orig + corrected, correction" << endl;
      print_vector(amf);
      print_vector(amfc);
      print_vector(correction);
    }
#endif
  }
  else {
    
    copy(amf, amfc);

    // and reset the jack state. for neutral, a jack state that is
    // still braking gives a jolt after return
    for (int ii = 6; ii--; ) js[ii] = MOVING;
  }
  
  if (0 && js[2] != MOVING) {
    cout << "orig qdd" << endl;
    print_vector(qdd);
  }
  // 30MAY2002 re-calculate jack accelerations for limited accelerations demand
  plat2jack(amfc, false);

  if (0 && js[2] != MOVING) {
    cout << "new qdd, and demanded one" << endl;
    print_vector(qdd);
    print_vector(qdd_demand);
  }
  
  // work vector
  double d1[3], d2[3]; 
  VectorE v3a(d1, 3), v3b(d2, 3);

  // integrate to obtain the new position and velocity of the platform
  // OS 9AUG2001 provided we listen to the amfc!
#ifdef USING_EIGEN3
  for (int ii = 1; ii <= isteps; ii++) {
    xmd_new = xmd + amfc.block<3,1>(0,0) * dti;
    xm_new = xm + 0.5*dti*(xmd + xmd_new);

    u_quat(am, Uq);
    amd_new = amd + amfc.block<3,1>(3,0) * dti;

    quat_der(am, 0.5*dti*Uq.transpose()*(amd + amd_new), am_new);
    am_new += am; qnorm(am_new);
    
    // prepare next step
    xm = xm_new; xmd = xmd_new;
    am = am_new; amd = amd_new;
  }
#else
  for (int ii = 1; ii <= isteps; ii++) {

    // calculate the new speed and rotation velocity
    //xmd_new = xmd + dti*amfc.Rows(1,3);
    //amd_new = amd + dti*amfc.Rows(4,6);
    add(xmd, scaled(amfc(0,3), dti), xmd_new);
    add(amd, scaled(amfc(3,6), dti), amd_new);

    // calculate the new position and orientation
    // note that -- O imperfection -- rotational speeds and
    // accelerations are given in the platform axis system, while
    // linear accelerations and speed are given in the baseframe
    // axis systeml
    // xm_new = xm + 0.5*dti*(xmd + xmd_new);
    add(xmd, xmd_new, v3a);
    add(xm, scaled(v3a, 0.5*dti), xm_new);
    u_quat(am, Uq);
    
    // am_new = qnorm(am + quat_der(am, 0.5*dti*Uq.t()*(amd + amd_new)));
    add(amd, amd_new, v3a);
    mult(trans(Uq), scaled(v3a, 0.5*dti), v3b);
    //print_vector(am); print_vector(v3b);
    quat_der(am, v3b, am_new);
    add(am, am_new);
    //print_vector(am_new);
    qnorm(am_new);
    //print_vector(am_new);

    // omitted re-calculation of jack accelerations, can be inserted
    // if refinement requested.

    // prepare for the next step
    copy(xm_new, xm); copy(am_new, am);
    copy(xmd_new, xmd); copy(amd_new, amd);
  }
#endif
  
  // OS 11SEP2001 output
  cur_m_mode = motion_mode;
  
  // OS 21AUG2001
  return status;
  
  // prepare the output to the motion control system
  // for now: jack lengths and jack speeds
  // OS 9AUG2001 this is no longer necessary,
  // the MotionLimiter module takes whatever it needs
  // through our accessor functions
  // TO CHECK! eliminate output & command_status_word from parameters
/*   for (int ii = 6; ii--; ) {
    output[ii] = (q(ii+1) - q_middle);
//    output[ii] = (q(ii+1));// [OS] 260600
    output[ii+6] = qd(ii+1);
    output[ii+12] = qdd(ii+1);
    }

  // output command word
  switch(motion_mode) {
  case DOWN:
    command_status_word = H2MCC_COMMAND_CONTROL_DOWN;
    break;
  case GOING_NEUTRAL:
  case GOING_DOWN:
    command_status_word = H2MCC_COMMAND_CONTROL_WEAK;
    break;
  default:
    command_status_word = H2MCC_COMMAND_CONTROL_STIFF;
    break;
  }
 */
}
// OS 16AUG2001 interface to the old MotionLimiter::integrate
int MotionLimiterEngine::integrate(const SimulatorMotionAcceleration& sma,
				   const MotionState& cmd_motion_mode, 
				   MotionState& cur_motion_mode)
{
  double d[6] = {sma.xdotdot, sma.ydotdot, sma.zdotdot, 
		 sma.pdot, sma.qdot, sma.rdot};
  VectorE amf_in(d, 6);

  return integrate(amf_in, amf_safe, cmd_motion_mode, cur_motion_mode);
}

// OS 13AUG2001 go to a position/attitude
// "because I say so", probably to sync with actual motion base
// through position measurement received by MotionController
// ATTENTION: am_target is quaternion!
bool MotionLimiterEngine::beTarget(const Vector& xm_target,
				   const Vector& am_target)
{
  // debug
  //cout << "beTarget( " << xm_target << am_target << ")" << endl;
  
  // the target position
  copy(xm_target, xm);
  copy(am_target, am);

#ifdef USING_EIGEN3
  xmd.setZero();
  amd.setZero();
#else
  // we're not moving
  mtl::set(xmd, 0.0);
  mtl::set(amd, 0.0);
#endif
  
  // update the jacks, assuming we don't ask for accelerations
  plat2jack(amf_still, false);

  // debug 21AUG2001
  //for (int ii = 1;ii<=6;++ii) cout << q[ii] << " ";
  //cout << endl;
  
  bool we_are_still = true;
  for (int i=0; i< 6; ++i) {
    // assume initial state of the jacks is moving.
    js[i] = MOVING;
    
    // check we're really not moving
    if ( fabs(qd[i]) > qd_almost_zero ) we_are_still = false;
  }
  
  return we_are_still;
  
  //	return true;
}

// OS 21AUG 2001 This whole function is obsolete now
// all these transitions are now done by the MotionController
// together with the MCC software
// OS 11SEP2001 Update: we do need this function to bring us back
// smoothly from Active to Neutral!
bool MotionLimiterEngine::goTarget(const Vector& xm_target, 
				   const Vector& am_target,
				   Vector& amf)
{
  // definition of the acceleration phases
  // for motion test and motionfilter test
  static const double acc_phases[] = 
  { 1.0, -1.0, -1.0, 1.0, -1.0, 1.0, 1.0, -1.0};

  // a counter to indicate the number of coordinates undergoing active
  // changes. A mode switch can take place as soon as in_action = 0;
  int in_action = 6;

  // reset the movement state machine when a coming from a different
  // motion mode into DDOWN or NEUTRAL
  if (previous_motion_mode != motion_mode && 
      (motion_mode == GOING_DOWN || motion_mode == GOING_NEUTRAL)) {
    for (int ii = 2; ii--; ) transition_state[ii] = INIT;
  }
  previous_motion_mode = motion_mode;

  switch(motion_mode) {
    
  case BRAKING:
    // brake linear motions
    for (int ii = 3; ii--; ) {
      if (xmd[ii] > dt * xmdd_transition) {
	amf[ii] = - xmdd_transition;
      }
      else if (xmd[ii] < -dt * xmdd_transition) {
	amf[ii] = xmdd_transition;
	     }
      else {
	amf[ii] = - xmd[ii] * clamp_vgain;
	in_action--;
      }

      // and brake rotations
      if (amd[ii] > dt * amdd_transition) {
	amf[ii+3] = - amdd_transition;
      }
      else if (amd[ii] < -dt * amdd_transition) {
	amf[ii+3] = amdd_transition;
      }
      else {
	amf[ii+3] = - amd[ii] * clamp_vgain;// [OS] 14-7 was amf[ii] = ...
	in_action--;
      }
    }
    break;
    
  case DOWN:
  case IN_NEUTRAL:
    // clamp at the desired position
    for (int ii = 3; ii--; ) {
      amf[ii] = - clamp_vgain*xmd[ii] +
	clamp_xgain*(xm_target[ii] - xm[ii]);
      limit(-xmdd_transition, amf[ii], xmdd_transition);
    }
    for (int ii = 3; ii--; ) {
      amf[ii+3] = - clamp_vgain*amd[ii] +
	clamp_xgain*(am_target[ii] - am[ii]);
      limit(-amdd_transition, amf[ii+3], amdd_transition);
    }
    in_action = 0;
    break;

  case STILL:
    if (still_counter == -1) still_counter = int(2.0 / dt);
    // keep still
    for (int ii = 3; ii--; ) {
      amf[ii] = - clamp_vgain * xmd[ii];
    }
    for (int ii = 3; ii--; ) {
      amf[ii+3] = - clamp_vgain * amd[ii];
    }
    if (still_counter-- == 0) {
      in_action = 0;
    }
    break;

  case ACTIVE:
    // do not change amf
    in_action = 0;
    break;

  case GOING_NEUTRAL:
  case GOING_DOWN: {

    // go to the target position in a controlled manner, do 3 by 3;
    // linear motions and rotational motions
    double nd_data[3]; VectorE normdist(nd_data, 3);
    for (int ii = 2; ii--; ) {
      double distance, xdd_transition, xd_transition, xd, af = 0.0;
      if (ii == 1) {

	// "distance" for rotation is the rotation angle of the
	// quaternion 
	double Lambda = am[3]; 
	if (Lambda > 1.0) Lambda = 1.0;
	if (Lambda < -1.0) Lambda = -1.0;
	distance = 2 * acos(Lambda);
	normdist[0] = am[0]; normdist[1] = am[1]; normdist[2] = am[2];
	if (distance > negligible_dist) {
#ifdef USING_EIGEN3
	  normdist = normdist / normdist.norm();
#else
	  scale(normdist, 1.0/two_norm(normdist));
#endif
	}
	xdd_transition = amdd_transition;
	xd_transition = amd_transition;

	// absolute value of speed
#ifdef USING_EIGEN3
	xd = amd.norm();
#else
	xd = two_norm(amd);
#endif
	}
      else {
	  
	  // for translations, it is the 3D distance
#ifdef USING_EIGEN3
	  normdist = xm - xm_target;
	  distance = normdist.norm();
	  if (distance > negligible_dist) normdist *= 1.0/distance;
	  xdd_transition = xmdd_transition;
	  xd_transition = xmd_transition;
	  xd = xmd.norm();
	  
#else
	  add(xm, scaled(xm_target, -1), normdist);
	  distance = two_norm(normdist);
	  if (distance > negligible_dist) scale(normdist, 1.0/distance);
	  xdd_transition = xmdd_transition;
	  xd_transition = xmd_transition;
	  xd = two_norm(xmd);
#endif
	}
      double absdist = fabs(distance);

      if (transition_state[ii] == INIT) {
	transition_state[ii] = ACCELERATE;
	I_MOD("newmove, ini->acc, set=" << ii <<
	      " d=" << distance << " xd=" << xd <<
	      " nd0=" << normdist[0] << " nd1=" << normdist[1] <<
	      " nd2=" << normdist[2]); 
      }

      if (transition_state[ii] == ACCELERATE) {
	
	// acceleration, braking and clamping algorithm
	if (absdist*xdd_transition > 0.5 * xd * xd) {
	  
	  if (absdist < dm_almost_zero && fabs(xd) < ddm_almost_zero) {
	    transition_state[ii]= CLAMP;
	    I_MOD("newmove, acc->clm, set=" << ii <<
		  " d=" << distance << " xd=" << xd <<
		  " nd0=" << normdist[0] << " nd1=" << normdist[1] <<
		  " nd2=" << normdist[2]); 
	  }
	  else if (xd + dt*xdd_transition < xd_transition) {
	    // increase the speed, if not yet at max speed in good direction
	    af = xdd_transition;
	    D_MOD("accelerating " << ii);
	  }
	  else if (xd < xd_transition) {
	    // increase the speed with an adjusted fraction
	    af = (xd_transition - xd) / dt;
	    D_MOD("scc to max speed " << ii);
	  }
	  else {
	    // keep the speed constant
	    transition_state[ii] = COAST;
	    I_MOD("newmove, acc->coa, set=" << ii <<
		  " d=" << distance << " xd=" << xd <<
		  " nd0=" << normdist[0] << " nd1=" << normdist[1] <<
		  " nd2=" << normdist[2]); 
	  }
	}
	else {
	  transition_state[ii] = DECELERATE;
	  I_MOD("newmove, acc->dec, set=" << ii <<
		  " d=" << distance << " xd=" << xd <<
		  " nd0=" << normdist[0] << " nd1=" << normdist[1] <<
		  " nd2=" << normdist[2]); 
	}
      }

      if (transition_state[ii] == COAST) {
	af = 0.0;
	
	if (absdist*xdd_transition <= 0.5 * xd * xd) {
	  transition_state[ii] = DECELERATE;
	  I_MOD("newmove, coa->dec, set=" << ii <<
		" d=" << distance << " xd=" << xd <<
		" nd0=" << normdist[0] << " nd1=" << normdist[1] <<
		" nd2=" << normdist[2]); 
	}
	else if (absdist < dm_almost_zero && fabs(xd) < ddm_almost_zero) {
	  transition_state[ii]= CLAMP;
	  I_MOD("newmove, coa->clm, set=" << ii <<
		" d=" << distance << " xd=" << xd <<
		" nd0=" << normdist[0] << " nd1=" << normdist[1] <<
		" nd2=" << normdist[2]); 
	}
      }

      if (transition_state[ii] == DECELERATE) {

	// have to brake, but how much?
	if (absdist > dm_almost_zero) {
	  af = -0.5 * xd*xd / absdist;
	  D_MOD("braking " << ii);
	  if (af < -1.1 * xdd_transition) {
	    af = -1.1 * xdd_transition;
	    W_MOD("MotionLimiter algorithm error 1, for coordinate " << ii);
	  }
	}
	else {
	  transition_state[ii] = CLAMP;
	  I_MOD("newmove, dec->cla, set=" << ii <<
		" d=" << distance << " xd=" << xd <<
		" nd0=" << normdist[0] << " nd1=" << normdist[1] <<
		" nd2=" << normdist[2]); 
	}
      }

      if (transition_state[ii] == CLAMP) {
	// clamp at the desired position
	if (ii == 0) {
	  for (int jj = 3; jj--; ) {
	    amf[jj] = - clamp_vgain*xmd[jj] +
	      clamp_xgain*(xm_target[jj] - xm[jj]);
	    limit(-xmdd_transition, amf[jj], xmdd_transition);
	  }
	}
	else {
	  for (int jj = 3; jj--; ) {
	    amf[jj+3] = - clamp_vgain*amd[jj] -
	      clamp_xgain*(am[jj]);
	    limit(-amdd_transition, amf[jj+3], amdd_transition);
	  }
	  // clamp at the position
	  //af = - clamp_vgain*xd + clamp_xgain*distance;
	  //if (af < -1.1 * xdd_transition) {
	  //  af = -1.1 * xdd_transition;
	  //}
	}
	in_action -= 3;
      }
      else {
	// copy back to the proper amf :
	if (ii == 1) {
	  amf[3] = -af * normdist[0];
	  amf[4] = -af * normdist[1];
	  amf[5] = -af * normdist[2];
	}
	else {
	  amf[0] = -af * normdist[0];
	  amf[1] = -af * normdist[1];
	  amf[2] = -af * normdist[2];
	}	
      }
    } // end of the iteration
  }
    break;
  
  case MOTION_TEST_OLD:
    {
      if (motiontest_count == -1) {
	motiontest_count = 6 * 8 * motiontest_part - 1;
      }
      // the coordinate to be tested
      int ix = motiontest_count / (8 * motiontest_part) + 1;
      // phase in testing this coordinate
      int ip = (motiontest_count - (ix-1)*8*motiontest_part) /
	motiontest_part + 1;
#ifdef USING_EIGEN3
      amf.setZero();
#else
      mtl::set(amf, 0.0);
#endif
      if (ix > 2) {
	amf[ix] = motiontest_amdd * acc_phases[ip - 1];
      }
      else {
	amf[ix] = motiontest_xmdd * acc_phases[ip - 1];
      }    
      
      // decrease the counter, motiontest can be interrupted any time
      motiontest_count--;
      in_action = 0;
      break; 
    }
  case MOTION_FILTER_TEST:
    {
      if (motionfiltertest_count == -1) {
	motionfiltertest_count = 6 * 8 * motionfiltertest_part - 1;
      }
      // the coordinate to be tested
      int ix = motionfiltertest_count / (8 * motionfiltertest_part) + 1;
      // phase in testing this coordinate
      int ip = (motionfiltertest_count - (ix-1)*8*motionfiltertest_part) /
	motionfiltertest_part + 1;
      
#ifdef USING_EIGEN3
      amf.setZero();
#else
      mtl::set(amf, 0.0);
#endif
      if (ix > 2) {
	amf[ix] = motionfiltertest_amdd * acc_phases[ip - 1];
      }
      else {
	amf[ix] = motionfiltertest_xmdd * acc_phases[ip - 1];
      }    

      // decrease the counter, test can be interrupted any time
      motionfiltertest_count--;
      in_action = 0;
      break; 
    }
  }

  // return true if a mode change can take place
  return (in_action == 0);
}

ostream& operator << (ostream& os, const MotionLimiterEngine::JackState m)
{
  switch (m) {
  case MotionLimiterEngine::ARRIVED_MAX:
    os << "ARRIVED_MAX";
    break;
  case MotionLimiterEngine::HOLD_MAX:
    os << "HOLD_MAX";
    break;
  case MotionLimiterEngine::BRAKE_NEGATIVE:
    os << "BRAKE_NEGATIVE";
    break;
  case MotionLimiterEngine::MOVING:
    os << "MOVING";
    break;
  case MotionLimiterEngine::BRAKE_POSITIVE:
    os << "BRAKE_POSITIVE";
    break;
  case MotionLimiterEngine::HOLD_MIN:
    os << "HOLD_MIN";
    break;
  case MotionLimiterEngine::ARRIVED_MIN:
    os << "ARRIVED_MIN";
    break;
  }
  return os;
}

ostream& operator << (ostream& os, const MotionLimiterEngine::MotionState m)
{
  switch (m) {
  case MotionLimiterEngine::DOWN:
    os << "DOWN";
    break;
  case MotionLimiterEngine::IN_NEUTRAL:
    os << "IN_NEUTRAL";
    break;
  case MotionLimiterEngine::ACTIVE:
    os << "ACTIVE";
    break;
  case MotionLimiterEngine::MOTION_TEST_OLD:
    os << "MOTION_TEST_OLD";
    break;
  case MotionLimiterEngine::MOTION_FILTER_TEST:
    os << "MOTION_FILTER_TEST";
    break;
  case MotionLimiterEngine::STILL:
    os << "STILL";
    break;
  case MotionLimiterEngine::BRAKING:
    os << "BRAKING";
    break;

  case MotionLimiterEngine::GOING_NEUTRAL:
    os << "GOING_NEUTRAL";
    break;
  case MotionLimiterEngine::GOING_DOWN:
    os << "GOING_DOWN";
    break;
  }
  return os;
}
