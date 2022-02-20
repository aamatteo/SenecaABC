/*
 * Citation_private.h
 *
 * Real-Time Workshop code generation for Simulink model "Citation.mdl".
 *
 * Model Version              : 1.654
 * Real-Time Workshop version : 7.0  (R2007b)  02-Aug-2007
 * C source code generated on : Mon Feb 25 14:25:48 2013
 */
#ifndef RTW_HEADER_Citation_private_h_
#define RTW_HEADER_Citation_private_h_
#include "rtwtypes.h"
#  include "rtlibsrc.h"
#define CALL_EVENT                     (MAX_uint8_T)
#ifndef RTW_COMMON_DEFINES_
# define RTW_COMMON_DEFINES_
#define rt_VALIDATE_MEMORY(S, ptr)     if(!(ptr)) {\
 rtmSetErrorStatus(Citation_rtM, RT_MEMORY_ALLOCATION_ERROR);\
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
 rtmSetErrorStatus(Citation_rtM, RT_MEMORY_ALLOCATION_ERROR);\
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

extern void ac_axes(SimStruct *rts);
extern void ac_atmos(SimStruct *rts);
extern void table3(SimStruct *rts);

#if defined(MULTITASKING)
#  error Model (Citation) was built in \
SingleTasking solver mode, however the MULTITASKING define is \
present. If you have multitasking (e.g. -DMT or -DMULTITASKING) \
defined on the RTW page of Simulation parameter dialog, please \
remove it and on the Solver page, select solver mode \
MultiTasking. If the Simulation parameter dialog is configured \
correctly, please verify that your template makefile is \
configured correctly.
#endif
#endif                                 /* RTW_HEADER_Citation_private_h_ */
