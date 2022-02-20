/* ------------------------------------------------------------------ */
/*      item            : CLTestCommandExtra.cxx
        made by         : Rene van Paassen (repa)
        date            : Tue 02 Dec 2014
        category        : body file
        description     : DUECA Communication Object (DCO)
                          additional methods and data
        codegen version : 110
        language        : C++
*/

#include <fstream>
#include <cmath>
void CLTestCommand::step()
{
  idx++;
}

// -0.5 for simple euler, but 0 for runge-kutta
const double stpf = -0.5*0;

#ifdef USING_EIGEN3
const Eigen::Vector2d& CLTestCommand::du(const Eigen::VectorXd& x, double dt)
#else
const Vector& CLTestCommand::du(const VectorE& x, double dt)
#endif
{
  if (idx < idx_start) {
    // perform a 0.5-0.5cos(w_ini*t) move to the offset position
    _du[0] = offset*(0.5*w_ini*w_ini*cos(w_ini*((idx+stpf)*DeltaT+dt)));
    //_du[1] = offset*( 0.5*w_ini*sin(w_ini*idx*DeltaT+dt));
    _du[1] = x[0];
    endpos = x[1];
  } 
  else if (idx >= idx_still) {
    // implement a weak decay, to get any possible errors to zero
    _du[0] = -1.5*x[0] -1.0*x[1];
    _du[1] = x[0];
  }
  else if (idx >= idx_end) {
    // perform the 0.5+0.5cos(w_ini*t) move back from the current pos to zero
    _du[0] = -endpos*(0.5*w_ini*w_ini*cos(w_ini*((idx-idx_end+stpf)*DeltaT+dt)));
    //_du[1] = endpos*(  0.5*w_ini*sin(w_ini*idx-(idx_end)*DeltaT+dt));
    _du[1] = x[0];
  }    
  else {
    switch (test) {
    case TestSawtooth: {
      unsigned idxs = (idx - idx_start) % idx_cycle;
      // the sawtooth starts "at the bottom"
      if (idxs < idx_halftooth || idxs >= idx_cycle - idx_halftooth) {
	// "positive" acceleration phase, at start and end
	_du[0] = accel_tooth;
	//std::cout << "pos accel " << idxs << ' ' << idx << std::endl;
      }
      else if (idxs >= idx_cycle/2 - idx_halftooth &&
	       idxs < idx_cycle/2 + idx_halftooth) {
	// "negative" acceleration phase, in the middle
	_du[0] = -accel_tooth;
	//std::cout << "neg accel " << idxs << ' ' << idx << std::endl;
      }
      else {
	// coasting, constant speed
	_du[0] = 0.0;
	//std::cout << "coast     " << idxs << ' ' << idx << std::endl;
      }
      _du[1] = x[0];
    }
      break;
    case TestSine:
      // sine function, also starts at bottom
      _du[0] = amplitude * w_sine * w_sine * 
	cos(w_sine * ( (idx - idx_start+stpf) * DeltaT + dt) );
      _du[1] = x[0];
      break;
    case TestFile:
      // file input read
      _du[0] = fileinput[idx - idx_start];
      _du[1] = x[0];
      break;
    case TestStill:
      _du[0] = 0.0;
      _du[1] = 0.0;
      break;
    }
    endpos = x[1];
  }
  return _du;
}

static const char *file_invalid = 
  "Invalid file; cannot read file with test input";
static const char *tooth_invalid = 
  "Invalid sawtooth; cannot accelerate to required speed";
static const char *profile_invalid =
  "Invalid profile; ends with non-zero velocity";

const static double eps = 1e-8;

bool CLTestCommand::complete()
{
  return idx > idx_still;
}

void CLTestCommand::reset(double dt)
{
  // set the index to zero, reset the file vector
  idx = 0;
  fileinput.clear();
  DeltaT = dt;
  endpos = 0.0;
  
  // calculate movement time, rounded off to steps
  idx_start = unsigned(round(move_time/DeltaT));
  
  // frequency of the initial movement
  w_ini = M_PI * 1.0 / (idx_start*DeltaT);

  // further steps depend on the input type
  switch(test) {
  case TestStill:
  case TestSine:
  case TestSawtooth: {
    // number of steps in a cycle, round off to be even
    idx_cycle = 2*unsigned(round(0.5*period / DeltaT));

    // sine frequency on the basis of the rounded no of steps
    w_sine = M_PI * 2.0 / (idx_cycle * DeltaT);

    // end index
    idx_end = idx_start + idx_cycle * repetitions;
    
    // for sawtooth, calculate a nominal speed, on the basis of
    // triangular movement from 0 to max. Teeth are "rounded off" to
    // limit acceleration
    if (test == TestSawtooth) {
      if (max_accel < eps || period < eps) {
	throw(CLException(tooth_invalid));
      }
      double vnom = 4.0*amplitude/period;
      idx_halftooth = ceil( (abs(vnom) / max_accel) / DeltaT );
      if (2*idx_halftooth > idx_cycle/2) {
	throw(CLException(tooth_invalid));
      }
      // now re-calculate the acceleration level to achieve the calculated 
      // velocity at the end of the acceleration period
      accel_tooth = vnom/(idx_halftooth * DeltaT);
    }

  }
    break;
  case TestFile: {
    ifstream f(file.c_str());
    double vsum = 0.0;
    while (f.good()) {
      double a;
      f >> a;
      if (f.good()) {
	vsum += a*DeltaT;
	fileinput.push_back(a);
      }
    }
    if (f.bad()) {
      throw(CLException(file_invalid));
    }
    if (abs(vsum) > 0.001*max_vel) {
      throw(CLException(profile_invalid));
    }
    idx_end = idx_start + fileinput.size();
  }
    break;
  }

#ifndef USING_EIGEN3
  _du.resize(2);
#endif
  
  // last thing is the run-out period
  idx_still = idx_end + idx_start;
}

#include <sstream>
#include <integrate_rungekutta.hxx>

std::string CLTestCommand::line()
{
  std::stringstream l;
  l << "Ch" << channel << ' ' << test 
    << " m=" << move_time 
    << "s; o=" << offset;
  if (test == TestFile) {
    l << " file=" << file;
  } 
  else {
    l << " T=" << period << "s";
    if (repetitions > 1) {
      l << "(x" << repetitions << ")";
    }
    l << " v_mx=" << max_vel << " a_mx=" << max_accel; 
  }

  return l.str();
}
  
#ifdef TEST
#include <iostream>

struct MiniModel
{
  CLTestCommand cmd;
  double dt;
  RungeKuttaWorkspace rkwork;
  double x_data[2];
  VectorE x;

  void derivative(VectorE& xd, double dt)
  {
#ifdef USING_EIGEN3
    xd.block(0,0,2,1) = cmd.du(x,dt);
#else
    mtl::copy(cmd.du(x, dt), xd);
#endif
  }

  inline const VectorE& X() const {return x;}

  void setState(const VectorE& newx)
  {
#ifdef USING_EIGEN3
    x = newx;
#else
    mtl::copy(newx, x);
#endif
  }    

  void step()
  {
    integrate_rungekutta(*this, rkwork, dt);
    cmd.step();
  }

  MiniModel(const CLTestCommand& _cmd, double dt) :
    cmd(_cmd),
    dt(dt),
    rkwork(2),
    x(x_data, 2)
  {
#ifdef USING_EIGEN3
    x.setZero();
#else
    mtl::set(x, 0.0);
#endif
    cmd.reset(dt);
  }
};


#ifndef USING_EIGEN3
std::ostream& operator << (std::ostream& os, const Vector& v)
{
  //os << "Vector(";
  for (unsigned ii = 0; ii < v.size(); ii++) {
    os << v[ii] << " ";
  }
  //return os << ")";
  return os;
}
#endif

int main()
{
  CLTestCommand cmd;
  cmd.test = CLTestCommand::TestSine;
  cmd.amplitude = 0.8;
  cmd.offset = -0.8;
  cmd.max_accel = 8.0;
  cmd.max_vel = 0.5;
  cmd.move_time = 1.0;
  cmd.period = 0.1;
  cmd.repetitions = 100;
  cmd.file = "test.dmp";
  double dt = 0.0004;

  MiniModel mm(cmd, dt);


  for (int ii = int((2*cmd.move_time+cmd.period*cmd.repetitions)/dt); ii--; ) {
    mm.step();
    std::cout << mm.cmd.idx << ' ' << mm.cmd.du(mm.x, dt)[0] << ' '
	      << mm.cmd.du(mm.x, dt)[1] << ' '
	      << mm.x[0] << ' ' << mm.x[1] << std::endl;
  }


}

#endif
