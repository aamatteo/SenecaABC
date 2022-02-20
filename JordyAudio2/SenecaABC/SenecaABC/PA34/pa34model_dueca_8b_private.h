/*
 * pa34model_dueca_8b_private.h
 *
 * Real-Time Workshop code generation for Simulink model "pa34model_dueca_8b.mdl".
 *
 * Model Version              : 1.20293
 * Real-Time Workshop version : 7.0  (R2007b)  02-Aug-2007
 * C source code generated on : Tue Jul 14 10:39:43 2015
 */
#ifndef RTW_HEADER_pa34model_dueca_8b_private_h_
#define RTW_HEADER_pa34model_dueca_8b_private_h_
#include "rtwtypes.h"
#  include "rtlibsrc.h"
#define CALL_EVENT                     (MAX_uint8_T)
#ifndef RTW_COMMON_DEFINES_
# define RTW_COMMON_DEFINES_
#define rt_VALIDATE_MEMORY(S, ptr)     if(!(ptr)) {\
 rtmSetErrorStatus(pa34model_dueca_8b_rtM, RT_MEMORY_ALLOCATION_ERROR);\
 return(S);\
 }
#if !defined(_WIN32)
#define rt_FREE(ptr)                   if((ptr) != NULL) {\
 free((ptr));\
 (ptr) = NULL;\
 }
#else

/* Visual and other windows compilers delcare free without const! */
#define rt_FREE(ptr)                   if((ptr) != NULL) {\
 free((void *)(ptr));\
 (ptr) = NULL;\
 }
#endif
#endif                                 /* RTW_COMMON_DEFINES_ */

#ifdef rt_VALIDATE_MEMORY
#undef rt_VALIDATE_MEMORY
#define rt_VALIDATE_MEMORY(S, ptr)     if(!(ptr)) {\
 rtmSetErrorStatus(pa34model_dueca_8b_rtM, RT_MEMORY_ALLOCATION_ERROR);\
 return(S);\
 }
#endif

#ifndef __RTWTYPES_H__
#error This file requires rtwtypes.h to be included
#else
#ifdef TMWTYPES_PREVIOUSLY_INCLUDED
#error This file requires rtwtypes.h to be included before tmwtypes.h
#else

/* Check for inclusion of an incorrect version of rtwtypes.h */
#ifndef RTWTYPES_ID_C08S16I32L32N32F1
#error This code was generated with a different "rtwtypes.h" than the file included
#endif                                 /* RTWTYPES_ID_C08S16I32L32N32F1 */
#endif                                 /* TMWTYPES_PREVIOUSLY_INCLUDED */
#endif                                 /* __RTWTYPES_H__ */

real_T cbaabiecohlncbaa_atan2(real_T eml_y, real_T eml_x);
real_T imohohdjdjmocjmo_max(real_T eml_x, real_T eml_y);
real_T aiekgdbamoppphln_interp1(real_T eml_par1[9], real_T eml_par2[9], real_T
  eml_par3);
real_T djeklfcbcjecopph_interp1(real_T eml_par1[6], real_T eml_par2[6], real_T
  eml_par3);
real_T aaaajecbeknghdbi_min(real_T eml_x, real_T eml_y);
real_T glfkekfchdjmlngl_interp1(real_T eml_par1[4], real_T eml_par2[4], real_T
  eml_par3);
real_T djmobaaadjmofkng_min(real_T eml_x[2]);
real_T ppphopphfkngdbie_max(real_T eml_x[2]);
void ecjegdjmimgdkngl_min(real_T eml_x[6], real_T eml_minval[3]);
void lfcbjmglknopimgl_mldivide(real_T eml_A[9], real_T eml_B[3], real_T eml_Y[3]);
uint32_T plook_bincpa(real_T u, const real_T *const bp, uint32_T maxIndex,
                      real_T *fraction, uint32_T *prevIndex);
real_T intrp2d_lca(const uint32_T *const bpIndex, const real_T *const frac,
                   const real_T *const table, uint32_T stride, const uint32_T *
                   const maxIndex);
uint32_T binsearch_u32d_prevIdx(real_T u, const real_T *const bp, uint32_T
  startIndex, uint32_T maxIndex);
void pa34mo_AEROFORCESENMOMENTS_Init(rtModel_pa34model_dueca_8b *rtm);
void pa34model_d_AEROFORCESENMOMENTS(rtModel_pa34model_dueca_8b *rtm);
void CalculateThrustParameters_Init(rtModel_pa34model_dueca_8b *rtm);
void pa34m_CalculateThrustParameters(rtModel_pa34model_dueca_8b *rtm);

#if defined(MULTITASKING)
#  error Model (pa34model_dueca_8b) was built in \
SingleTasking solver mode, however the MULTITASKING define is \
present. If you have multitasking (e.g. -DMT or -DMULTITASKING) \
defined on the RTW page of Simulation parameter dialog, please \
remove it and on the Solver page, select solver mode \
MultiTasking. If the Simulation parameter dialog is configured \
correctly, please verify that your template makefile is \
configured correctly.
#endif
#endif                                 /* RTW_HEADER_pa34model_dueca_8b_private_h_ */
