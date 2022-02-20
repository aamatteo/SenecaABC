/* ------------------------------------------------------------------   */
/*      item            : MotionAux.hxx
        made by         : Rene' van Paassen
        date            : 990325
	category        : header file 
        description     : 
	changes         : 990325 first version
			  010723 DUECA first version OS
			  020814 Converted to use MTL, RvP, added nice
			  comments 
        language        : C++
*/

#ifndef MotionAux_hxx
#define MotionAux_hxx

#ifdef MotionAux_cxx
const static char h_id[] =
"$Id: MotionAux.hxx,v 1.5 2017/08/29 15:12:37 ostroosma Exp $";
#endif

/** Calculate a 3by3 rotation matrix for a rotation defined by a
    quaternion. 
    \param q     The quaternion, in the form of 
                 (lambda_x, lambda_y, lambda_z, Lambda).
    \param Uq    Result, the rotation matrix. */
template <class Mat, class Vec> 
void u_quat(const Vec& q, Mat& Uq)
{
#ifdef USING_EIGEN3

#if EIGEN_VERSION_AT_LEAST(3,3,0)
  typedef typename Mat::value_type T; // requires Eigen 3.3
#else
  typedef double T; // default to most likely option
#endif

  T u = q.norm();

#else
  typedef typename matrix_traits<Mat>::value_type T;
  T u = sqrt(sum_squares(q));
#endif
  T Au = q[0] / u;
  T Bu = q[1] / u;
  T Cu = q[2] / u;
  T Du = q[3] / u;

  T result[9] = 
  {Du*Du + Au*Au - Bu*Bu - Cu*Cu, 2*(Au*Bu - Cu*Du), 2*(Au*Cu + Bu*Du),
   2*(Au*Bu + Cu*Du), Du*Du - Au*Au + Bu*Bu - Cu*Cu, 2*(Bu*Cu - Au*Du),
   2*(Au*Cu - Bu*Du), 2*(Bu*Cu + Au*Du), Du*Du - Au*Au - Bu*Bu + Cu*Cu};

#ifdef USING_EIGEN3
  typedef typename Eigen::Map<Eigen::Matrix<T,3,3,Eigen::RowMajor> > MatrixE;
  Uq = MatrixE(result);
#else
  typedef typename matrix<T, rectangle<>, dense<external>, row_major>::type MatrixE;
  copy(MatrixE(result, 3, 3), Uq);
#endif  
}
    
/** Calculate the cross product of two 3-element vectors. 
    \param v1          Vector 1
    \param v2          Vector 2
    \param v3          Result vector. */
template <class VecA, class VecB, class VecC>
void cross(const VecA& v1, const VecB& v2, VecC& v3)
{
  v3[0] = v1[1]*v2[2] - v1[2]*v2[1];
  v3[1] = v1[2]*v2[0] - v1[0]*v2[2];
  v3[2] = v1[0]*v2[1] - v1[1]*v2[0];
}

/** Calculates the derivative of a quaterion, for rotation with a
    vector containing rotation velocities. 
    \param q           Quaternion, in the form of 
                       (lambda_x, lambda_y, lambda_z, Lambda)
    \param omega       rotation vector, 3 elements
    \param dq          Result Quaternion, as above, must have four
                       elements. */
template <class VecA, class VecB, class VecC>
void quat_der(const VecA& q, const VecB& omega, VecC& dq)
{
  //typedef typename VecC::value_type T;
  //typedef external_vec<T> VectorE;

  // in principle:
  // dq = 0.5 [ dot(-omega, q(2..4)) ;
  //       q(1) * omega - omega x q(2..4)]
  
  dq[3] = -0.5 * (omega[0]*q[0] + omega[1]*q[1] + omega[2]*q[2]);
  dq[0] =  0.5 * (q[3]*omega[0] - (omega[1]*q[2] - omega[2]*q[1]));
  dq[1] =  0.5 * (q[3]*omega[1] - (omega[2]*q[0] - omega[0]*q[2]));
  dq[2] =  0.5 * (q[3]*omega[2] - (omega[0]*q[1] - omega[1]*q[0]));
}

/** Normalise a quaternion, or any other vector for that matter. */
template <class VecA>
void qnorm(VecA& q)
{
#ifdef USING_EIGEN3
  q.normalize();
#else
  scale(q, 1.0/two_norm(q));
#endif
}

/** Calculate a normalised quaternion, or any other vector. 
    \param q    Input vector
    \param qn   Normalised result. */
template <class VecA, class VecB>
void qnorm(const VecA& q, VecB& qn)
{
  copy(scaled(q, 1.0/two_norm(q)), qn);
}

#endif

