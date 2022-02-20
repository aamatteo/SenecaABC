/*
 * rt_rand.h
 *
 * Real-Time Workshop code generation for Simulink model "pa34model_dueca_8b.mdl".
 *
 * Model Version              : 1.20293
 * Real-Time Workshop version : 7.0  (R2007b)  02-Aug-2007
 * C source code generated on : Tue Jul 14 10:39:43 2015
 */

#ifndef RTW_HEADER_rt_rand_h_
#define RTW_HEADER_rt_rand_h_
#include <math.h>
#include "rtwtypes.h"
# define MAXSEED                       2147483646                /* 2^31-2 */
# define SEED0                         1144108930                /* Seed #6, starting from seed = 1 */
# define RT_BIT16                      32768                     /* 2^15   */

extern real_T rt_Urand(uint32_T *seed);
extern real_T rt_NormalRand(uint32_T *seed);

#endif                                 /* RTW_HEADER_rt_rand_h_ */
