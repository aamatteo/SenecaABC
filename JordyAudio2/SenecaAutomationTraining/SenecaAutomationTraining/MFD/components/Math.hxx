//************************************************************
// Math.hxx
//
// Created on Tue May  8 21:50:33 2012 by Jan Comans
//
// Copyright 2012 Jan Comans -- j.comans@tudelft.nl
//
// License TBD
//************************************************************

#ifndef _MATH_H_
#define _MATH_H_

#include <cmath>

// Rounding
inline float  round(float  value) { return floor(value+0.5f); }
inline double round(double value) { return floor(value+0.5);  }

// Angle conversions
inline float  deg2rad(float  angle) { return angle * 3.1415f/180.0f; }
inline double deg2rad(double angle) { return angle * 3.1415/180.0;   }

inline float  rad2deg(float  angle) { return angle * 180.0f/3.1415f; }
inline double rad2deg(double angle) { return angle * 180.0/3.1415;   }

// Altitude conversions
inline float  ft2m(float  alt) { return alt * 0.305f; }
inline double ft2m(double alt) { return alt * 0.305;  }

inline float  m2ft(float  alt) { return alt / 0.305f; }
inline double m2ft(double alt) { return alt / 0.305;  }

// Speed conversions
inline float  kts2ms(float  V) { return V * 0.5144f; }
inline double kts2ms(double V) { return V * 0.5144;  }

inline float  ms2kts(float  V) { return V / 0.5144f; }
inline double ms2kts(double V) { return V / 0.5144;  }

// Distancce conversions
inline float  m2nm(float  value) { return value * 0.00053995680; }
inline double m2nm(double value) { return value * 0.00053995680; }

inline float  nm2m(float  value) { return value / 0.00053995680; }
inline double nm2m(double value) { return value / 0.00053995680; }
#endif /* _MATH_H_ */
