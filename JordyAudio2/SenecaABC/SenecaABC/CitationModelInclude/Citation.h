/*
 * Citation.h
 *
 * Real-Time Workshop code generation for Simulink model "Citation.mdl".
 *
 * Model Version              : 1.676
 * Real-Time Workshop version : 7.0  (R2007b)  02-Aug-2007
 * C source code generated on : Tue May 13 12:53:06 2014
 */
#ifndef RTW_HEADER_Citation_h_
#define RTW_HEADER_Citation_h_
#ifndef Citation_COMMON_INCLUDES_
# define Citation_COMMON_INCLUDES_
#include <stdlib.h>
#include <stddef.h>
#include <math.h>
#include <string.h>
#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#include "rt_logging.h"
#include "rt_atan2.h"
#include "rt_nonfinite.h"
#include "rtlibsrc.h"
#endif                                 /* Citation_COMMON_INCLUDES_ */

#include "Citation_types.h"
#ifndef _RTW_COMBINE_MULTIPLE_MODELS
#define MODEL_NAME                     Citation
#define NSAMPLE_TIMES                  (2)                       /* Number of sample times */
#define NINPUTS                        (26)                      /* Number of model inputs */
#define NOUTPUTS                       (47)                      /* Number of model outputs */
#define NBLOCKIO                       (44)                      /* Number of data output port signals */
#define NUM_ZC_EVENTS                  (0)                       /* Number of zero-crossing events */
#ifndef NCSTATES
# define NCSTATES                      (24)                      /* Number of continuous states */
#elif NCSTATES != 24
# error Invalid specification of NCSTATES defined in compiler command
#endif
#endif                                 /* _RTW_COMBINE_MULTIPLE_MODELS */

/* Macros for accessing real-time model data structure */
#ifndef rtmGetBlkStateChangeFlag
# define rtmGetBlkStateChangeFlag(rtm) ((rtm)->ModelData.blkStateChange)
#endif

#ifndef rtmSetBlkStateChangeFlag
# define rtmSetBlkStateChangeFlag(rtm, val) ((rtm)->ModelData.blkStateChange = (val))
#endif

#ifndef rtmGetBlockIO
# define rtmGetBlockIO(rtm)            ((rtm)->ModelData.blockIO)
#endif

#ifndef rtmSetBlockIO
# define rtmSetBlockIO(rtm, val)       ((rtm)->ModelData.blockIO = (val))
#endif

#ifndef rtmGetChecksums
# define rtmGetChecksums(rtm)          ((rtm)->Sizes.checksums)
#endif

#ifndef rtmSetChecksums
# define rtmSetChecksums(rtm, val)     ((rtm)->Sizes.checksums = (val))
#endif

#ifndef rtmGetClockTick0
# define rtmGetClockTick0(rtm)         ((rtm)->Timing.clockTick0)
#endif

#ifndef rtmSetClockTick0
# define rtmSetClockTick0(rtm, val)    ((rtm)->Timing.clockTick0 = (val))
#endif

#ifndef rtmGetClockTick1
# define rtmGetClockTick1(rtm)         ((rtm)->Timing.clockTick1)
#endif

#ifndef rtmSetClockTick1
# define rtmSetClockTick1(rtm, val)    ((rtm)->Timing.clockTick1 = (val))
#endif

#ifndef rtmGetClockTickH0
# define rtmGetClockTickH0(rtm)        ((rtm)->Timing.clockTickH0)
#endif

#ifndef rtmSetClockTickH0
# define rtmSetClockTickH0(rtm, val)   ((rtm)->Timing.clockTickH0 = (val))
#endif

#ifndef rtmGetClockTickH1
# define rtmGetClockTickH1(rtm)        ((rtm)->Timing.clockTickH1)
#endif

#ifndef rtmSetClockTickH1
# define rtmSetClockTickH1(rtm, val)   ((rtm)->Timing.clockTickH1 = (val))
#endif

#ifndef rtmGetConstBlockIO
# define rtmGetConstBlockIO(rtm)       ((rtm)->ModelData.constBlockIO)
#endif

#ifndef rtmSetConstBlockIO
# define rtmSetConstBlockIO(rtm, val)  ((rtm)->ModelData.constBlockIO = (val))
#endif

#ifndef rtmGetContStateDisabled
# define rtmGetContStateDisabled(rtm)  ((rtm)->ModelData.contStateDisabled)
#endif

#ifndef rtmSetContStateDisabled
# define rtmSetContStateDisabled(rtm, val) ((rtm)->ModelData.contStateDisabled = (val))
#endif

#ifndef rtmGetContStates
# define rtmGetContStates(rtm)         ((rtm)->ModelData.contStates)
#endif

#ifndef rtmSetContStates
# define rtmSetContStates(rtm, val)    ((rtm)->ModelData.contStates = (val))
#endif

#ifndef rtmGetDataMapInfo
# define rtmGetDataMapInfo(rtm)        ((rtm)->DataMapInfo)
#endif

#ifndef rtmSetDataMapInfo
# define rtmSetDataMapInfo(rtm, val)   ((rtm)->DataMapInfo = (val))
#endif

#ifndef rtmGetDbBufClockTick0
# define rtmGetDbBufClockTick0(rtm)    ((rtm)->Timing.rtmDbBufClockTick0)
#endif

#ifndef rtmSetDbBufClockTick0
# define rtmSetDbBufClockTick0(rtm, val) ((rtm)->Timing.rtmDbBufClockTick0 = (val))
#endif

#ifndef rtmGetDbBufClockTick1
# define rtmGetDbBufClockTick1(rtm)    ((rtm)->Timing.rtmDbBufClockTick1)
#endif

#ifndef rtmSetDbBufClockTick1
# define rtmSetDbBufClockTick1(rtm, val) ((rtm)->Timing.rtmDbBufClockTick1 = (val))
#endif

#ifndef rtmGetDbBufClockTickH0
# define rtmGetDbBufClockTickH0(rtm)   ((rtm)->Timing.rtmDbBufClockTickH0)
#endif

#ifndef rtmSetDbBufClockTickH0
# define rtmSetDbBufClockTickH0(rtm, val) ((rtm)->Timing.rtmDbBufClockTickH0 = (val))
#endif

#ifndef rtmGetDbBufClockTickH1
# define rtmGetDbBufClockTickH1(rtm)   ((rtm)->Timing.rtmDbBufClockTickH1)
#endif

#ifndef rtmSetDbBufClockTickH1
# define rtmSetDbBufClockTickH1(rtm, val) ((rtm)->Timing.rtmDbBufClockTickH1 = (val))
#endif

#ifndef rtmGetDbBufContT0
# define rtmGetDbBufContT0(rtm)        ((rtm)->Timing.rtmDbBufContT0)
#endif

#ifndef rtmSetDbBufContT0
# define rtmSetDbBufContT0(rtm, val)   ((rtm)->Timing.rtmDbBufContT0 = (val))
#endif

#ifndef rtmGetDbBufContT1
# define rtmGetDbBufContT1(rtm)        ((rtm)->Timing.rtmDbBufContT1)
#endif

#ifndef rtmSetDbBufContT1
# define rtmSetDbBufContT1(rtm, val)   ((rtm)->Timing.rtmDbBufContT1 = (val))
#endif

#ifndef rtmGetDbBufLastBufWr0
# define rtmGetDbBufLastBufWr0(rtm)    ((rtm)->Timing.rtmDbBufLastBufWr0)
#endif

#ifndef rtmSetDbBufLastBufWr0
# define rtmSetDbBufLastBufWr0(rtm, val) ((rtm)->Timing.rtmDbBufLastBufWr0 = (val))
#endif

#ifndef rtmGetDbBufLastBufWr1
# define rtmGetDbBufLastBufWr1(rtm)    ((rtm)->Timing.rtmDbBufLastBufWr1)
#endif

#ifndef rtmSetDbBufLastBufWr1
# define rtmSetDbBufLastBufWr1(rtm, val) ((rtm)->Timing.rtmDbBufLastBufWr1 = (val))
#endif

#ifndef rtmGetDbBufReadBuf0
# define rtmGetDbBufReadBuf0(rtm)      ((rtm)->Timing.rtmDbBufReadBuf0)
#endif

#ifndef rtmSetDbBufReadBuf0
# define rtmSetDbBufReadBuf0(rtm, val) ((rtm)->Timing.rtmDbBufReadBuf0 = (val))
#endif

#ifndef rtmGetDbBufReadBuf1
# define rtmGetDbBufReadBuf1(rtm)      ((rtm)->Timing.rtmDbBufReadBuf1)
#endif

#ifndef rtmSetDbBufReadBuf1
# define rtmSetDbBufReadBuf1(rtm, val) ((rtm)->Timing.rtmDbBufReadBuf1 = (val))
#endif

#ifndef rtmGetDbBufWriteBuf0
# define rtmGetDbBufWriteBuf0(rtm)     ((rtm)->Timing.rtmDbBufWriteBuf0)
#endif

#ifndef rtmSetDbBufWriteBuf0
# define rtmSetDbBufWriteBuf0(rtm, val) ((rtm)->Timing.rtmDbBufWriteBuf0 = (val))
#endif

#ifndef rtmGetDbBufWriteBuf1
# define rtmGetDbBufWriteBuf1(rtm)     ((rtm)->Timing.rtmDbBufWriteBuf1)
#endif

#ifndef rtmSetDbBufWriteBuf1
# define rtmSetDbBufWriteBuf1(rtm, val) ((rtm)->Timing.rtmDbBufWriteBuf1 = (val))
#endif

#ifndef rtmGetDefaultParam
# define rtmGetDefaultParam(rtm)       ((rtm)->ModelData.defaultParam)
#endif

#ifndef rtmSetDefaultParam
# define rtmSetDefaultParam(rtm, val)  ((rtm)->ModelData.defaultParam = (val))
#endif

#ifndef rtmGetDerivCacheNeedsReset
# define rtmGetDerivCacheNeedsReset(rtm) ((rtm)->ModelData.derivCacheNeedsReset)
#endif

#ifndef rtmSetDerivCacheNeedsReset
# define rtmSetDerivCacheNeedsReset(rtm, val) ((rtm)->ModelData.derivCacheNeedsReset = (val))
#endif

#ifndef rtmGetDirectFeedThrough
# define rtmGetDirectFeedThrough(rtm)  ((rtm)->Sizes.sysDirFeedThru)
#endif

#ifndef rtmSetDirectFeedThrough
# define rtmSetDirectFeedThrough(rtm, val) ((rtm)->Sizes.sysDirFeedThru = (val))
#endif

#ifndef rtmGetErrorStatusFlag
# define rtmGetErrorStatusFlag(rtm)    ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatusFlag
# define rtmSetErrorStatusFlag(rtm, val) ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetFinalTime
# define rtmGetFinalTime(rtm)          ((rtm)->Timing.tFinal)
#endif

#ifndef rtmSetFinalTime
# define rtmSetFinalTime(rtm, val)     ((rtm)->Timing.tFinal = (val))
#endif

#ifndef rtmGetFirstInitCondFlag
# define rtmGetFirstInitCondFlag(rtm)  ((rtm)->Timing.firstInitCondFlag)
#endif

#ifndef rtmSetFirstInitCondFlag
# define rtmSetFirstInitCondFlag(rtm, val) ((rtm)->Timing.firstInitCondFlag = (val))
#endif

#ifndef rtmGetH2LBufBeingRead0
# define rtmGetH2LBufBeingRead0(rtm)   ((rtm)->Timing.rtmH2LBufBeingRead0)
#endif

#ifndef rtmSetH2LBufBeingRead0
# define rtmSetH2LBufBeingRead0(rtm, val) ((rtm)->Timing.rtmH2LBufBeingRead0 = (val))
#endif

#ifndef rtmGetH2LBufBeingRead1
# define rtmGetH2LBufBeingRead1(rtm)   ((rtm)->Timing.rtmH2LBufBeingRead1)
#endif

#ifndef rtmSetH2LBufBeingRead1
# define rtmSetH2LBufBeingRead1(rtm, val) ((rtm)->Timing.rtmH2LBufBeingRead1 = (val))
#endif

#ifndef rtmGetH2LDbBufClockTick0
# define rtmGetH2LDbBufClockTick0(rtm) ((rtm)->Timing.rtmH2LDbBufClockTick0)
#endif

#ifndef rtmSetH2LDbBufClockTick0
# define rtmSetH2LDbBufClockTick0(rtm, val) ((rtm)->Timing.rtmH2LDbBufClockTick0 = (val))
#endif

#ifndef rtmGetH2LDbBufClockTick1
# define rtmGetH2LDbBufClockTick1(rtm) ((rtm)->Timing.rtmH2LDbBufClockTick1)
#endif

#ifndef rtmSetH2LDbBufClockTick1
# define rtmSetH2LDbBufClockTick1(rtm, val) ((rtm)->Timing.rtmH2LDbBufClockTick1 = (val))
#endif

#ifndef rtmGetH2LDbBufClockTickH0
# define rtmGetH2LDbBufClockTickH0(rtm) ((rtm)->Timing.rtmH2LDbBufClockTickH0)
#endif

#ifndef rtmSetH2LDbBufClockTickH0
# define rtmSetH2LDbBufClockTickH0(rtm, val) ((rtm)->Timing.rtmH2LDbBufClockTickH0 = (val))
#endif

#ifndef rtmGetH2LDbBufClockTickH1
# define rtmGetH2LDbBufClockTickH1(rtm) ((rtm)->Timing.rtmH2LDbBufClockTickH1)
#endif

#ifndef rtmSetH2LDbBufClockTickH1
# define rtmSetH2LDbBufClockTickH1(rtm, val) ((rtm)->Timing.rtmH2LDbBufClockTickH1 = (val))
#endif

#ifndef rtmGetH2LDbBufContT0
# define rtmGetH2LDbBufContT0(rtm)     ((rtm)->Timing.rtmH2LDbBufContT0)
#endif

#ifndef rtmSetH2LDbBufContT0
# define rtmSetH2LDbBufContT0(rtm, val) ((rtm)->Timing.rtmH2LDbBufContT0 = (val))
#endif

#ifndef rtmGetH2LDbBufContT1
# define rtmGetH2LDbBufContT1(rtm)     ((rtm)->Timing.rtmH2LDbBufContT1)
#endif

#ifndef rtmSetH2LDbBufContT1
# define rtmSetH2LDbBufContT1(rtm, val) ((rtm)->Timing.rtmH2LDbBufContT1 = (val))
#endif

#ifndef rtmGetH2LLastBufWr0
# define rtmGetH2LLastBufWr0(rtm)      ((rtm)->Timing.rtmH2LLastBufWr0)
#endif

#ifndef rtmSetH2LLastBufWr0
# define rtmSetH2LLastBufWr0(rtm, val) ((rtm)->Timing.rtmH2LLastBufWr0 = (val))
#endif

#ifndef rtmGetH2LLastBufWr1
# define rtmGetH2LLastBufWr1(rtm)      ((rtm)->Timing.rtmH2LLastBufWr1)
#endif

#ifndef rtmSetH2LLastBufWr1
# define rtmSetH2LLastBufWr1(rtm, val) ((rtm)->Timing.rtmH2LLastBufWr1 = (val))
#endif

#ifndef rtmGetIntgData
# define rtmGetIntgData(rtm)           ((rtm)->ModelData.intgData)
#endif

#ifndef rtmSetIntgData
# define rtmSetIntgData(rtm, val)      ((rtm)->ModelData.intgData = (val))
#endif

#ifndef rtmGetL2HDbBufClockTick
# define rtmGetL2HDbBufClockTick(rtm)  ((rtm)->Timing.rtmL2HDbBufClockTick)
#endif

#ifndef rtmSetL2HDbBufClockTick
# define rtmSetL2HDbBufClockTick(rtm, val) ((rtm)->Timing.rtmL2HDbBufClockTick = (val))
#endif

#ifndef rtmGetL2HDbBufClockTickH
# define rtmGetL2HDbBufClockTickH(rtm) ((rtm)->Timing.rtmL2HDbBufClockTickH)
#endif

#ifndef rtmSetL2HDbBufClockTickH
# define rtmSetL2HDbBufClockTickH(rtm, val) ((rtm)->Timing.rtmL2HDbBufClockTickH = (val))
#endif

#ifndef rtmGetL2HDbBufContT
# define rtmGetL2HDbBufContT(rtm)      ((rtm)->Timing.rtmL2HDbBufContT)
#endif

#ifndef rtmSetL2HDbBufContT
# define rtmSetL2HDbBufContT(rtm, val) ((rtm)->Timing.rtmL2HDbBufContT = (val))
#endif

#ifndef rtmGetL2HLastBufWr
# define rtmGetL2HLastBufWr(rtm)       ((rtm)->Timing.rtmL2HLastBufWr)
#endif

#ifndef rtmSetL2HLastBufWr
# define rtmSetL2HLastBufWr(rtm, val)  ((rtm)->Timing.rtmL2HLastBufWr = (val))
#endif

#ifndef rtmGetMdlRefGlobalTID
# define rtmGetMdlRefGlobalTID(rtm)    ((rtm)->Timing.mdlref_GlobalTID)
#endif

#ifndef rtmSetMdlRefGlobalTID
# define rtmSetMdlRefGlobalTID(rtm, val) ((rtm)->Timing.mdlref_GlobalTID = (val))
#endif

#ifndef rtmGetMdlRefTriggerTID
# define rtmGetMdlRefTriggerTID(rtm)   ((rtm)->Timing.mdlref_TriggerTID)
#endif

#ifndef rtmSetMdlRefTriggerTID
# define rtmSetMdlRefTriggerTID(rtm, val) ((rtm)->Timing.mdlref_TriggerTID = (val))
#endif

#ifndef rtmGetModelMappingInfo
# define rtmGetModelMappingInfo(rtm)   ((rtm)->SpecialInfo.mappingInfo)
#endif

#ifndef rtmSetModelMappingInfo
# define rtmSetModelMappingInfo(rtm, val) ((rtm)->SpecialInfo.mappingInfo = (val))
#endif

#ifndef rtmGetModelName
# define rtmGetModelName(rtm)          ((rtm)->modelName)
#endif

#ifndef rtmSetModelName
# define rtmSetModelName(rtm, val)     ((rtm)->modelName = (val))
#endif

#ifndef rtmGetNumBlockIO
# define rtmGetNumBlockIO(rtm)         ((rtm)->Sizes.numBlockIO)
#endif

#ifndef rtmSetNumBlockIO
# define rtmSetNumBlockIO(rtm, val)    ((rtm)->Sizes.numBlockIO = (val))
#endif

#ifndef rtmGetNumBlockParams
# define rtmGetNumBlockParams(rtm)     ((rtm)->Sizes.numBlockPrms)
#endif

#ifndef rtmSetNumBlockParams
# define rtmSetNumBlockParams(rtm, val) ((rtm)->Sizes.numBlockPrms = (val))
#endif

#ifndef rtmGetNumBlocks
# define rtmGetNumBlocks(rtm)          ((rtm)->Sizes.numBlocks)
#endif

#ifndef rtmSetNumBlocks
# define rtmSetNumBlocks(rtm, val)     ((rtm)->Sizes.numBlocks = (val))
#endif

#ifndef rtmGetNumContStates
# define rtmGetNumContStates(rtm)      ((rtm)->Sizes.numContStates)
#endif

#ifndef rtmSetNumContStates
# define rtmSetNumContStates(rtm, val) ((rtm)->Sizes.numContStates = (val))
#endif

#ifndef rtmGetNumDWork
# define rtmGetNumDWork(rtm)           ((rtm)->Sizes.numDwork)
#endif

#ifndef rtmSetNumDWork
# define rtmSetNumDWork(rtm, val)      ((rtm)->Sizes.numDwork = (val))
#endif

#ifndef rtmGetNumInputPorts
# define rtmGetNumInputPorts(rtm)      ((rtm)->Sizes.numIports)
#endif

#ifndef rtmSetNumInputPorts
# define rtmSetNumInputPorts(rtm, val) ((rtm)->Sizes.numIports = (val))
#endif

#ifndef rtmGetNumNonSampledZCs
# define rtmGetNumNonSampledZCs(rtm)   ((rtm)->Sizes.numNonSampZCs)
#endif

#ifndef rtmSetNumNonSampledZCs
# define rtmSetNumNonSampledZCs(rtm, val) ((rtm)->Sizes.numNonSampZCs = (val))
#endif

#ifndef rtmGetNumOutputPorts
# define rtmGetNumOutputPorts(rtm)     ((rtm)->Sizes.numOports)
#endif

#ifndef rtmSetNumOutputPorts
# define rtmSetNumOutputPorts(rtm, val) ((rtm)->Sizes.numOports = (val))
#endif

#ifndef rtmGetNumSFcnParams
# define rtmGetNumSFcnParams(rtm)      ((rtm)->Sizes.numSFcnPrms)
#endif

#ifndef rtmSetNumSFcnParams
# define rtmSetNumSFcnParams(rtm, val) ((rtm)->Sizes.numSFcnPrms = (val))
#endif

#ifndef rtmGetNumSFunctions
# define rtmGetNumSFunctions(rtm)      ((rtm)->Sizes.numSFcns)
#endif

#ifndef rtmSetNumSFunctions
# define rtmSetNumSFunctions(rtm, val) ((rtm)->Sizes.numSFcns = (val))
#endif

#ifndef rtmGetNumSampleTimes
# define rtmGetNumSampleTimes(rtm)     ((rtm)->Sizes.numSampTimes)
#endif

#ifndef rtmSetNumSampleTimes
# define rtmSetNumSampleTimes(rtm, val) ((rtm)->Sizes.numSampTimes = (val))
#endif

#ifndef rtmGetNumU
# define rtmGetNumU(rtm)               ((rtm)->Sizes.numU)
#endif

#ifndef rtmSetNumU
# define rtmSetNumU(rtm, val)          ((rtm)->Sizes.numU = (val))
#endif

#ifndef rtmGetNumY
# define rtmGetNumY(rtm)               ((rtm)->Sizes.numY)
#endif

#ifndef rtmSetNumY
# define rtmSetNumY(rtm, val)          ((rtm)->Sizes.numY = (val))
#endif

#ifndef rtmGetOdeF
# define rtmGetOdeF(rtm)               ((rtm)->ModelData.odeF)
#endif

#ifndef rtmSetOdeF
# define rtmSetOdeF(rtm, val)          ((rtm)->ModelData.odeF = (val))
#endif

#ifndef rtmGetOdeY
# define rtmGetOdeY(rtm)               ((rtm)->ModelData.odeY)
#endif

#ifndef rtmSetOdeY
# define rtmSetOdeY(rtm, val)          ((rtm)->ModelData.odeY = (val))
#endif

#ifndef rtmGetOffsetTimePtr
# define rtmGetOffsetTimePtr(rtm)      ((rtm)->Timing.offsetTimes)
#endif

#ifndef rtmSetOffsetTimePtr
# define rtmSetOffsetTimePtr(rtm, val) ((rtm)->Timing.offsetTimes = (val))
#endif

#ifndef rtmGetOptions
# define rtmGetOptions(rtm)            ((rtm)->Sizes.options)
#endif

#ifndef rtmSetOptions
# define rtmSetOptions(rtm, val)       ((rtm)->Sizes.options = (val))
#endif

#ifndef rtmGetParamIsMalloced
# define rtmGetParamIsMalloced(rtm)    ((rtm)->ModelData.paramIsMalloced)
#endif

#ifndef rtmSetParamIsMalloced
# define rtmSetParamIsMalloced(rtm, val) ((rtm)->ModelData.paramIsMalloced = (val))
#endif

#ifndef rtmGetPath
# define rtmGetPath(rtm)               ((rtm)->path)
#endif

#ifndef rtmSetPath
# define rtmSetPath(rtm, val)          ((rtm)->path = (val))
#endif

#ifndef rtmGetPerTaskSampleHits
# define rtmGetPerTaskSampleHits(rtm)  ((rtm)->Timing.RateInteraction)
#endif

#ifndef rtmSetPerTaskSampleHits
# define rtmSetPerTaskSampleHits(rtm, val) ((rtm)->Timing.RateInteraction = (val))
#endif

#ifndef rtmGetPerTaskSampleHitsPtr
# define rtmGetPerTaskSampleHitsPtr(rtm) ((rtm)->Timing.perTaskSampleHits)
#endif

#ifndef rtmSetPerTaskSampleHitsPtr
# define rtmSetPerTaskSampleHitsPtr(rtm, val) ((rtm)->Timing.perTaskSampleHits = (val))
#endif

#ifndef rtmGetPrevZCSigState
# define rtmGetPrevZCSigState(rtm)     ((rtm)->ModelData.prevZCSigState)
#endif

#ifndef rtmSetPrevZCSigState
# define rtmSetPrevZCSigState(rtm, val) ((rtm)->ModelData.prevZCSigState = (val))
#endif

#ifndef rtmGetRTWExtModeInfo
# define rtmGetRTWExtModeInfo(rtm)     ((rtm)->extModeInfo)
#endif

#ifndef rtmSetRTWExtModeInfo
# define rtmSetRTWExtModeInfo(rtm, val) ((rtm)->extModeInfo = (val))
#endif

#ifndef rtmGetRTWGeneratedSFcn
# define rtmGetRTWGeneratedSFcn(rtm)   ((rtm)->Sizes.rtwGenSfcn)
#endif

#ifndef rtmSetRTWGeneratedSFcn
# define rtmSetRTWGeneratedSFcn(rtm, val) ((rtm)->Sizes.rtwGenSfcn = (val))
#endif

#ifndef rtmGetRTWLogInfo
# define rtmGetRTWLogInfo(rtm)         ((rtm)->rtwLogInfo)
#endif

#ifndef rtmSetRTWLogInfo
# define rtmSetRTWLogInfo(rtm, val)    ((rtm)->rtwLogInfo = (val))
#endif

#ifndef rtmGetRTWRTModelMethodsInfo
# define rtmGetRTWRTModelMethodsInfo(rtm) ((rtm)->modelMethodsInfo)
#endif

#ifndef rtmSetRTWRTModelMethodsInfo
# define rtmSetRTWRTModelMethodsInfo(rtm, val) ((rtm)->modelMethodsInfo = (val))
#endif

#ifndef rtmGetRTWSfcnInfo
# define rtmGetRTWSfcnInfo(rtm)        ((rtm)->sfcnInfo)
#endif

#ifndef rtmSetRTWSfcnInfo
# define rtmSetRTWSfcnInfo(rtm, val)   ((rtm)->sfcnInfo = (val))
#endif

#ifndef rtmGetRTWSolverInfo
# define rtmGetRTWSolverInfo(rtm)      ((rtm)->solverInfo)
#endif

#ifndef rtmSetRTWSolverInfo
# define rtmSetRTWSolverInfo(rtm, val) ((rtm)->solverInfo = (val))
#endif

#ifndef rtmGetReservedForXPC
# define rtmGetReservedForXPC(rtm)     ((rtm)->SpecialInfo.xpcData)
#endif

#ifndef rtmSetReservedForXPC
# define rtmSetReservedForXPC(rtm, val) ((rtm)->SpecialInfo.xpcData = (val))
#endif

#ifndef rtmGetRootDWork
# define rtmGetRootDWork(rtm)          ((rtm)->Work.dwork)
#endif

#ifndef rtmSetRootDWork
# define rtmSetRootDWork(rtm, val)     ((rtm)->Work.dwork = (val))
#endif

#ifndef rtmGetSFunctions
# define rtmGetSFunctions(rtm)         ((rtm)->childSfunctions)
#endif

#ifndef rtmSetSFunctions
# define rtmSetSFunctions(rtm, val)    ((rtm)->childSfunctions = (val))
#endif

#ifndef rtmGetSampleHitPtr
# define rtmGetSampleHitPtr(rtm)       ((rtm)->Timing.sampleHits)
#endif

#ifndef rtmSetSampleHitPtr
# define rtmSetSampleHitPtr(rtm, val)  ((rtm)->Timing.sampleHits = (val))
#endif

#ifndef rtmGetSampleTimePtr
# define rtmGetSampleTimePtr(rtm)      ((rtm)->Timing.sampleTimes)
#endif

#ifndef rtmSetSampleTimePtr
# define rtmSetSampleTimePtr(rtm, val) ((rtm)->Timing.sampleTimes = (val))
#endif

#ifndef rtmGetSampleTimeTaskIDPtr
# define rtmGetSampleTimeTaskIDPtr(rtm) ((rtm)->Timing.sampleTimeTaskIDPtr)
#endif

#ifndef rtmSetSampleTimeTaskIDPtr
# define rtmSetSampleTimeTaskIDPtr(rtm, val) ((rtm)->Timing.sampleTimeTaskIDPtr = (val))
#endif

#ifndef rtmGetSimMode
# define rtmGetSimMode(rtm)            ((rtm)->simMode)
#endif

#ifndef rtmSetSimMode
# define rtmSetSimMode(rtm, val)       ((rtm)->simMode = (val))
#endif

#ifndef rtmGetSimTimeStep
# define rtmGetSimTimeStep(rtm)        ((rtm)->Timing.simTimeStep)
#endif

#ifndef rtmSetSimTimeStep
# define rtmSetSimTimeStep(rtm, val)   ((rtm)->Timing.simTimeStep = (val))
#endif

#ifndef rtmGetStartTime
# define rtmGetStartTime(rtm)          ((rtm)->Timing.tStart)
#endif

#ifndef rtmSetStartTime
# define rtmSetStartTime(rtm, val)     ((rtm)->Timing.tStart = (val))
#endif

#ifndef rtmGetStepSize
# define rtmGetStepSize(rtm)           ((rtm)->Timing.stepSize)
#endif

#ifndef rtmSetStepSize
# define rtmSetStepSize(rtm, val)      ((rtm)->Timing.stepSize = (val))
#endif

#ifndef rtmGetStepSize0
# define rtmGetStepSize0(rtm)          ((rtm)->Timing.stepSize0)
#endif

#ifndef rtmSetStepSize0
# define rtmSetStepSize0(rtm, val)     ((rtm)->Timing.stepSize0 = (val))
#endif

#ifndef rtmGetStepSize1
# define rtmGetStepSize1(rtm)          ((rtm)->Timing.stepSize1)
#endif

#ifndef rtmSetStepSize1
# define rtmSetStepSize1(rtm, val)     ((rtm)->Timing.stepSize1 = (val))
#endif

#ifndef rtmGetStopRequestedFlag
# define rtmGetStopRequestedFlag(rtm)  ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequestedFlag
# define rtmSetStopRequestedFlag(rtm, val) ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetTaskCounters
# define rtmGetTaskCounters(rtm)       ((rtm)->Timing.TaskCounters)
#endif

#ifndef rtmSetTaskCounters
# define rtmSetTaskCounters(rtm, val)  ((rtm)->Timing.TaskCounters = (val))
#endif

#ifndef rtmGetTaskTime0
# define rtmGetTaskTime0(rtm)          ((rtm)->Timing.taskTime0)
#endif

#ifndef rtmSetTaskTime0
# define rtmSetTaskTime0(rtm, val)     ((rtm)->Timing.taskTime0 = (val))
#endif

#ifndef rtmGetTaskTime1
# define rtmGetTaskTime1(rtm)          ((rtm)->Timing.taskTime1)
#endif

#ifndef rtmSetTaskTime1
# define rtmSetTaskTime1(rtm, val)     ((rtm)->Timing.taskTime1 = (val))
#endif

#ifndef rtmGetTimePtr
# define rtmGetTimePtr(rtm)            ((rtm)->Timing.t)
#endif

#ifndef rtmSetTimePtr
# define rtmSetTimePtr(rtm, val)       ((rtm)->Timing.t = (val))
#endif

#ifndef rtmGetTimingData
# define rtmGetTimingData(rtm)         ((rtm)->Timing.timingData)
#endif

#ifndef rtmSetTimingData
# define rtmSetTimingData(rtm, val)    ((rtm)->Timing.timingData = (val))
#endif

#ifndef rtmGetU
# define rtmGetU(rtm)                  ((rtm)->ModelData.inputs)
#endif

#ifndef rtmSetU
# define rtmSetU(rtm, val)             ((rtm)->ModelData.inputs = (val))
#endif

#ifndef rtmGetVarNextHitTimesListPtr
# define rtmGetVarNextHitTimesListPtr(rtm) ((rtm)->Timing.varNextHitTimesList)
#endif

#ifndef rtmSetVarNextHitTimesListPtr
# define rtmSetVarNextHitTimesListPtr(rtm, val) ((rtm)->Timing.varNextHitTimesList = (val))
#endif

#ifndef rtmGetY
# define rtmGetY(rtm)                  ((rtm)->ModelData.outputs)
#endif

#ifndef rtmSetY
# define rtmSetY(rtm, val)             ((rtm)->ModelData.outputs = (val))
#endif

#ifndef rtmGetZCCacheNeedsReset
# define rtmGetZCCacheNeedsReset(rtm)  ((rtm)->ModelData.zCCacheNeedsReset)
#endif

#ifndef rtmSetZCCacheNeedsReset
# define rtmSetZCCacheNeedsReset(rtm, val) ((rtm)->ModelData.zCCacheNeedsReset = (val))
#endif

#ifndef rtmGetZCSignalValues
# define rtmGetZCSignalValues(rtm)     ((rtm)->ModelData.zcSignalValues)
#endif

#ifndef rtmSetZCSignalValues
# define rtmSetZCSignalValues(rtm, val) ((rtm)->ModelData.zcSignalValues = (val))
#endif

#ifndef rtmGet_TimeOfLastOutput
# define rtmGet_TimeOfLastOutput(rtm)  ((rtm)->Timing.timeOfLastOutput)
#endif

#ifndef rtmSet_TimeOfLastOutput
# define rtmSet_TimeOfLastOutput(rtm, val) ((rtm)->Timing.timeOfLastOutput = (val))
#endif

#ifndef rtmGetdX
# define rtmGetdX(rtm)                 ((rtm)->ModelData.derivs)
#endif

#ifndef rtmSetdX
# define rtmSetdX(rtm, val)            ((rtm)->ModelData.derivs = (val))
#endif

#ifndef rtmGetChecksumVal
# define rtmGetChecksumVal(rtm, idx)   ((rtm)->Sizes.checksums[idx])
#endif

#ifndef rtmSetChecksumVal
# define rtmSetChecksumVal(rtm, idx, val) ((rtm)->Sizes.checksums[idx] = (val))
#endif

#ifndef rtmGetDWork
# define rtmGetDWork(rtm, idx)         ((rtm)->Work.dwork[idx])
#endif

#ifndef rtmSetDWork
# define rtmSetDWork(rtm, idx, val)    ((rtm)->Work.dwork[idx] = (val))
#endif

#ifndef rtmGetOffsetTime
# define rtmGetOffsetTime(rtm, idx)    ((rtm)->Timing.offsetTimes[idx])
#endif

#ifndef rtmSetOffsetTime
# define rtmSetOffsetTime(rtm, idx, val) ((rtm)->Timing.offsetTimes[idx] = (val))
#endif

#ifndef rtmGetSFunction
# define rtmGetSFunction(rtm, idx)     ((rtm)->childSfunctions[idx])
#endif

#ifndef rtmSetSFunction
# define rtmSetSFunction(rtm, idx, val) ((rtm)->childSfunctions[idx] = (val))
#endif

#ifndef rtmGetSampleTime
# define rtmGetSampleTime(rtm, idx)    ((rtm)->Timing.sampleTimes[idx])
#endif

#ifndef rtmSetSampleTime
# define rtmSetSampleTime(rtm, idx, val) ((rtm)->Timing.sampleTimes[idx] = (val))
#endif

#ifndef rtmGetSampleTimeTaskID
# define rtmGetSampleTimeTaskID(rtm, idx) ((rtm)->Timing.sampleTimeTaskIDPtr[idx])
#endif

#ifndef rtmSetSampleTimeTaskID
# define rtmSetSampleTimeTaskID(rtm, idx, val) ((rtm)->Timing.sampleTimeTaskIDPtr[idx] = (val))
#endif

#ifndef rtmGetVarNextHitTime
# define rtmGetVarNextHitTime(rtm, idx) ((rtm)->Timing.varNextHitTimesList[idx])
#endif

#ifndef rtmSetVarNextHitTime
# define rtmSetVarNextHitTime(rtm, idx, val) ((rtm)->Timing.varNextHitTimesList[idx] = (val))
#endif

#ifndef rtmIsContinuousTask
# define rtmIsContinuousTask(rtm, tid) ((tid) == 0)
#endif

#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#ifndef rtmIsFirstInitCond
# define rtmIsFirstInitCond(rtm)       (rtmGetT((rtm)) == (rtmGetTStart((rtm))))
#endif

#ifndef rtmIsMajorTimeStep
# define rtmIsMajorTimeStep(rtm)       (((rtm)->Timing.simTimeStep) == MAJOR_TIME_STEP)
#endif

#ifndef rtmIsMinorTimeStep
# define rtmIsMinorTimeStep(rtm)       (((rtm)->Timing.simTimeStep) == MINOR_TIME_STEP)
#endif

#ifndef rtmIsSampleHit
# define rtmIsSampleHit(rtm, sti, tid) ((rtmIsMajorTimeStep((rtm)) && (rtm)->Timing.sampleHits[(rtm)->Timing.sampleTimeTaskIDPtr[sti]]))
#endif

#ifndef rtmIsSpecialSampleHit
# define rtmIsSpecialSampleHit(rtm, sti, prom_sti, tid) (rtmIsMajorTimeStep((rtm)) && (rtm)->Timing.sampleHits[(rtm)->Timing.sampleTimeTaskIDPtr[sti]])
#endif

#ifndef rtmGetStopRequested
# define rtmGetStopRequested(rtm)      ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
# define rtmSetStopRequested(rtm, val) ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
# define rtmGetStopRequestedPtr(rtm)   (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
# define rtmGetT(rtm)                  (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmSetT
# define rtmSetT(rtm, val)             (rtmGetTPtr((rtm))[0] = (val))
#endif

#ifndef rtmGetTFinal
# define rtmGetTFinal(rtm)             ((rtm)->Timing.tFinal)
#endif

#ifndef rtmSetTFinal
# define rtmSetTFinal(rtm, val)        ((rtm)->Timing.tFinal = (val))
#endif

#ifndef rtmGetTPtr
# define rtmGetTPtr(rtm)               ((rtm)->Timing.t)
#endif

#ifndef rtmSetTPtr
# define rtmSetTPtr(rtm, val)          ((rtm)->Timing.t = (val))
#endif

#ifndef rtmGetTStart
# define rtmGetTStart(rtm)             ((rtm)->Timing.tStart)
#endif

#ifndef rtmSetTStart
# define rtmSetTStart(rtm, val)        ((rtm)->Timing.tStart = (val))
#endif

#ifndef rtmGetTaskTime
# define rtmGetTaskTime(rtm, sti)      (rtmGetTPtr((rtm))[(rtm)->Timing.sampleTimeTaskIDPtr[sti]])
#endif

#ifndef rtmSetTaskTime
# define rtmSetTaskTime(rtm, sti, val) (rtmGetTPtr((rtm))[sti] = (val))
#endif

#ifndef rtmGetTimeOfLastOutput
# define rtmGetTimeOfLastOutput(rtm)   ((rtm)->Timing.timeOfLastOutput)
#endif

#ifndef rtmSetTimeOfLastOutput
# define rtmSetTimeOfLastOutput(rtm, val) ((rtm)->Timing.timeOfLastOutput = (val))
#endif

/* Definition for use in the target main file */
#define Citation_rtModel               rtModel_Citation

/* Block signals for system '<S22>/MATLAB Function1' */
typedef struct {
  real_T y[12];                        /* '<S22>/MATLAB Function1' */
} rtB_MATLABFunction1_Citation;

/* Block signals for system '<S22>/MATLAB Function5' */
typedef struct {
  real_T y[12];                        /* '<S22>/MATLAB Function5' */
} rtB_MATLABFunction5_Citation;

/* Block signals for system '<S22>/MATLAB Function7' */
typedef struct {
  real_T y[12];                        /* '<S22>/MATLAB Function7' */
} rtB_MATLABFunction7_Citation;

/* Block signals for system '<S39>/MATLAB Function10' */
typedef struct {
  real_T y[12];                        /* '<S39>/MATLAB Function10' */
} rtB_MATLABFunction10_Citation;

/* Block signals for system '<S104>/MATLAB Function1' */
typedef struct {
  real_T y[12];                        /* '<S104>/MATLAB Function1' */
} rtB_MATLABFunction1_Citation_l;

/* Block signals (auto storage) */
typedef struct {
  real_T Integrator[12];               /* '<S16>/Integrator' */
  real_T Saturation[8];                /* '<S36>/Saturation' */
  real_T Abs;                          /* '<S43>/Abs' */
  real_T Sfunction;                    /* '<S51>/S-function' */
  real_T CZag;                         /* '<S46>/CZ// ag' */
  real_T hedot;                        /* '<S94>/hedot' */
  real_T MaxStrutDeflection;           /* '<S125>/Max Strut Deflection' */
  real_T alphadot;                     /* '<S99>/alphadot' */
  real_T betadot;                      /* '<S99>/betadot' */
  real_T VTASdot;                      /* '<S98>/VTASdot' */
  real_T phidot;                       /* '<S93>/phidot' */
  real_T thetadot;                     /* '<S93>/thetadot' */
  real_T psidot;                       /* '<S93>/psidot' */
  real_T xedot;                        /* '<S94>/xedot' */
  real_T yedot;                        /* '<S94>/yedot' */
  real_T Gain;                         /* '<S5>/Gain' */
  real_T Gain_h;                       /* '<S6>/Gain' */
  real_T Gain_o;                       /* '<S7>/Gain' */
  real_T Gain_m;                       /* '<S8>/Gain' */
  real_T Gain_n;                       /* '<S9>/Gain' */
  real_T Switch;                       /* '<S79>/Switch' */
  real_T Switch_b;                     /* '<S80>/Switch' */
  real_T Switch_a;                     /* '<S87>/Switch' */
  real_T Switch_d;                     /* '<S88>/Switch' */
  real_T y[12];                        /* '<S21>/MATLAB Function9' */
  real_T y_m[3];                       /* '<S96>/Embedded MATLAB Function' */
  rtB_MATLABFunction5_Citation sf_MATLABFunction2_a;/* '<S104>/MATLAB Function2' */
  rtB_MATLABFunction1_Citation_l sf_MATLABFunction10_f;/* '<S104>/MATLAB Function10' */
  rtB_MATLABFunction1_Citation_l sf_MATLABFunction1_lc;/* '<S104>/MATLAB Function1' */
  rtB_MATLABFunction10_Citation sf_MATLABFunction10;/* '<S97>/MATLAB Function10' */
  rtB_MATLABFunction5_Citation sf_MATLABFunction2_p;/* '<S65>/MATLAB Function2' */
  rtB_MATLABFunction5_Citation sf_MATLABFunction10_c;/* '<S65>/MATLAB Function10' */
  rtB_MATLABFunction5_Citation sf_MATLABFunction1_j;/* '<S65>/MATLAB Function1' */
  rtB_MATLABFunction5_Citation sf_MATLABFunction3;/* '<S26>/MATLAB Function3' */
  rtB_MATLABFunction5_Citation sf_MATLABFunction2_d;/* '<S26>/MATLAB Function2' */
  rtB_MATLABFunction5_Citation sf_MATLABFunction1_l;/* '<S26>/MATLAB Function1' */
  rtB_MATLABFunction10_Citation sf_MATLABFunction10_o;/* '<S39>/MATLAB Function10' */
  rtB_MATLABFunction5_Citation sf_MATLABFunction9_o;/* '<S22>/MATLAB Function9' */
  rtB_MATLABFunction7_Citation sf_MATLABFunction8;/* '<S22>/MATLAB Function8' */
  rtB_MATLABFunction7_Citation sf_MATLABFunction7;/* '<S22>/MATLAB Function7' */
  rtB_MATLABFunction5_Citation sf_MATLABFunction6;/* '<S22>/MATLAB Function6' */
  rtB_MATLABFunction5_Citation sf_MATLABFunction5;/* '<S22>/MATLAB Function5' */
  rtB_MATLABFunction1_Citation sf_MATLABFunction2;/* '<S22>/MATLAB Function2' */
  rtB_MATLABFunction1_Citation sf_MATLABFunction1;/* '<S22>/MATLAB Function1' */
} BlockIO_Citation;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T Sfunction_RWORK[3];           /* '<S51>/S-function' */
  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA[12];
    real_T TimeStampB;
    real_T LastUAtTimeB[12];
  } winddot_RWORK;                     /* '<S92>/winddot' */

  struct {
    void *LoggedData;
  } Scope3_PWORK;                      /* '<S104>/Scope3' */

  struct {
    void *LoggedData;
  } Scope4_PWORK;                      /* '<S104>/Scope4' */

  struct {
    void *LoggedData;
  } Scope6_PWORK;                      /* '<S125>/Scope6' */

  int_T Sfunction_IWORK[3];            /* '<S51>/S-function' */
} D_Work_Citation;

/* Continuous states (auto storage) */
typedef struct {
  real_T Integrator_CSTATE[12];        /* '<S16>/Integrator' */
  real_T Integrator_CSTATE_g;          /* '<S6>/Integrator' */
  real_T Integrator_CSTATE_m;          /* '<S5>/Integrator' */
  real_T Integrator_CSTATE_i;          /* '<S7>/Integrator' */
  real_T Washout_CSTATE;               /* '<S136>/Washout' */
  real_T Integrator_CSTATE_ip;         /* '<S8>/Integrator' */
  real_T Integrator_CSTATE_k;          /* '<S9>/Integrator' */
  real_T N1state_CSTATE;               /* '<S76>/N1 state' */
  real_T N1state_CSTATE_h;             /* '<S84>/N1 state' */
  real_T Parameter_CSTATE;             /* '<S134>/Parameter' */
  real_T Parameter_CSTATE_g;           /* '<S133>/Parameter' */
  real_T N2state_CSTATE;               /* '<S77>/N2 state' */
  real_T N2state_CSTATE_l;             /* '<S85>/N2 state' */
} ContinuousStates_Citation;

/* State derivatives (auto storage) */
typedef struct {
  real_T Integrator_CSTATE[12];        /* '<S16>/Integrator' */
  real_T Integrator_CSTATE_g;          /* '<S6>/Integrator' */
  real_T Integrator_CSTATE_m;          /* '<S5>/Integrator' */
  real_T Integrator_CSTATE_i;          /* '<S7>/Integrator' */
  real_T Washout_CSTATE;               /* '<S136>/Washout' */
  real_T Integrator_CSTATE_ip;         /* '<S8>/Integrator' */
  real_T Integrator_CSTATE_k;          /* '<S9>/Integrator' */
  real_T N1state_CSTATE;               /* '<S76>/N1 state' */
  real_T N1state_CSTATE_h;             /* '<S84>/N1 state' */
  real_T Parameter_CSTATE;             /* '<S134>/Parameter' */
  real_T Parameter_CSTATE_g;           /* '<S133>/Parameter' */
  real_T N2state_CSTATE;               /* '<S77>/N2 state' */
  real_T N2state_CSTATE_l;             /* '<S85>/N2 state' */
} StateDerivatives_Citation;

/* State disabled  */
typedef struct {
  boolean_T Integrator_CSTATE[12];     /* '<S16>/Integrator' */
  boolean_T Integrator_CSTATE_g;       /* '<S6>/Integrator' */
  boolean_T Integrator_CSTATE_m;       /* '<S5>/Integrator' */
  boolean_T Integrator_CSTATE_i;       /* '<S7>/Integrator' */
  boolean_T Washout_CSTATE;            /* '<S136>/Washout' */
  boolean_T Integrator_CSTATE_ip;      /* '<S8>/Integrator' */
  boolean_T Integrator_CSTATE_k;       /* '<S9>/Integrator' */
  boolean_T N1state_CSTATE;            /* '<S76>/N1 state' */
  boolean_T N1state_CSTATE_h;          /* '<S84>/N1 state' */
  boolean_T Parameter_CSTATE;          /* '<S134>/Parameter' */
  boolean_T Parameter_CSTATE_g;        /* '<S133>/Parameter' */
  boolean_T N2state_CSTATE;            /* '<S77>/N2 state' */
  boolean_T N2state_CSTATE_l;          /* '<S85>/N2 state' */
} StateDisabled_Citation;

/* External inputs (root inport signals with auto storage) */
typedef struct {
  real_T Input[26];                    /* '<Root>/Input' */
} ExternalInputs_Citation;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real_T Output[47];                   /* '<Root>/Output' */
} ExternalOutputs_Citation;

/* Parameters (auto storage) */
struct Parameters_Citation {
  real_T Integrator_IC[12];            /* Expression: x0
                                        * '<S16>/Integrator'
                                        */
  real_T CDAM_RowIdx[22];              /* Expression: matdam(2:23,1)
                                        * '<S41>/CDAM'
                                        */
  real_T CDAM_ColIdx[22];              /* Expression: matdam(1,2:23)
                                        * '<S41>/CDAM'
                                        */
  real_T CDAM_Table[484];              /* Expression: matdam(2:23,2:23)
                                        * '<S41>/CDAM'
                                        */
  real_T Integrator_IC_p;              /* Expression: u0(1)
                                        * '<S6>/Integrator'
                                        */
  real_T delimits_UpperSat;            /* Expression: 0.26
                                        * '<S2>/de limits'
                                        */
  real_T delimits_LowerSat;            /* Expression: -0.35
                                        * '<S2>/de limits'
                                        */
  real_T Integrator_IC_g;              /* Expression: u0(2)
                                        * '<S5>/Integrator'
                                        */
  real_T dalimits_UpperSat;            /* Expression: 0.65
                                        * '<S2>/da limits'
                                        */
  real_T dalimits_LowerSat;            /* Expression: -0.65
                                        * '<S2>/da limits'
                                        */
  real_T Integrator_IC_a;              /* Expression: u0(3)
                                        * '<S7>/Integrator'
                                        */
  real_T drlimits_UpperSat;            /* Expression: 0.38
                                        * '<S2>/dr limits'
                                        */
  real_T drlimits_LowerSat;            /* Expression: -0.38
                                        * '<S2>/dr limits'
                                        */
  real_T Washout_A;                    /* Computed Parameter: A
                                        * '<S136>/Washout'
                                        */
  real_T Washout_C;                    /* Computed Parameter: C
                                        * '<S136>/Washout'
                                        */
  real_T Washout_D;                    /* Computed Parameter: D
                                        * '<S136>/Washout'
                                        */
  real_T Integrator_IC_j;              /* Expression: u0(7)
                                        * '<S8>/Integrator'
                                        */
  real_T Integrator_IC_gq;             /* Expression: u0(8)
                                        * '<S9>/Integrator'
                                        */
  real_T Saturation_UpperSat[8];       /* Expression: [ 15  37  22  15  20  10 40 180/pi]*pi/180
                                        * '<S36>/Saturation'
                                        */
  real_T Saturation_LowerSat[8];       /* Expression: [-20 -37 -22 -15 -20 -10 0  0]*pi/180
                                        * '<S36>/Saturation'
                                        */
  real_T CDAF_RowIdx[22];              /* Expression: matdaf(2:23,1)
                                        * '<S41>/CDAF'
                                        */
  real_T CDAF_ColIdx[22];              /* Expression: matdaf(1,2:23)
                                        * '<S41>/CDAF'
                                        */
  real_T CDAF_Table[484];              /* Expression: matdaf(2:23,2:23)
                                        * '<S41>/CDAF'
                                        */
  real_T Constant_Value;               /* Expression: 1
                                        * '<S48>/Constant'
                                        */
  real_T Sat_UpperSat;                 /* Expression: 21
                                        * '<S37>/Sat'
                                        */
  real_T Sat_LowerSat;                 /* Expression: -inf
                                        * '<S37>/Sat'
                                        */
  real_T ms2kts_Gain[8];               /* Expression: [1; 1; 1; 1; 1; 1.9438; 1.9438; 1.9438]
                                        * '<S36>/m//s2kts'
                                        */
  real_T Switch_Threshold;             /* Expression: 0
                                        * '<S48>/Switch'
                                        */
  real_T CDEAF_RowIdx[22];             /* Expression: matdeaf(2:23,1)
                                        * '<S41>/CDEAF'
                                        */
  real_T CDEAF_ColIdx[22];             /* Expression: matdeaf(1,2:23)
                                        * '<S41>/CDEAF'
                                        */
  real_T CDEAF_Table[484];             /* Expression: matdeaf(2:23,2:23)
                                        * '<S41>/CDEAF'
                                        */
  real_T CDWAW_RowIdx[6];              /* Expression: matdwaw(2:7,1)
                                        * '<S41>/CDWAW'
                                        */
  real_T CDWAW_ColIdx[6];              /* Expression: matdwaw(1,2:7)
                                        * '<S41>/CDWAW'
                                        */
  real_T CDWAW_Table[36];              /* Expression: matdwaw(2:7,2:7)
                                        * '<S41>/CDWAW'
                                        */
  real_T Betafactor0598_Gain;          /* Expression: .598
                                        * '<S41>/Betafactor=0.598'
                                        */
  real_T CDQAF_RowIdx[22];             /* Expression: matdqaf(2:23,1)
                                        * '<S41>/CDQAF'
                                        */
  real_T CDQAF_ColIdx[22];             /* Expression: matdqaf(1,2:23)
                                        * '<S41>/CDQAF'
                                        */
  real_T CDQAF_Table[484];             /* Expression: matdqaf(2:23,2:23)
                                        * '<S41>/CDQAF'
                                        */
  real_T Br001056_Gain;                /* Expression: 0.01056
                                        * '<S41>/B+r= 0.01056'
                                        */
  real_T CDUAF_RowIdx[22];             /* Expression: matduaf(2:23,1)
                                        * '<S41>/CDUAF'
                                        */
  real_T CDUAF_ColIdx[22];             /* Expression: matduaf(1,2:23)
                                        * '<S41>/CDUAF'
                                        */
  real_T CDUAF_Table[484];             /* Expression: matduaf(2:23,2:23)
                                        * '<S41>/CDUAF'
                                        */
  real_T KUUT_XData[3];                /* Expression: matuut(1,:)
                                        * '<S41>/KUUT'
                                        */
  real_T KUUT_YData[3];                /* Expression: matuut(2,:)
                                        * '<S41>/KUUT'
                                        */
  real_T CDGAF_RowIdx[3];              /* Expression: matdgaf(2:4,1)
                                        * '<S41>/CDGAF'
                                        */
  real_T CDGAF_ColIdx[3];              /* Expression: matdgaf(1,2:4)
                                        * '<S41>/CDGAF'
                                        */
  real_T CDGAF_Table[9];               /* Expression: matdgaf(2:4,2:4)
                                        * '<S41>/CDGAF'
                                        */
  real_T KGEDHR_XData[10];             /* Expression: matedhr(1,:)
                                        * '<S41>/KGEDHR'
                                        */
  real_T KGEDHR_YData[10];             /* Expression: matedhr(2,:)
                                        * '<S41>/KGEDHR'
                                        */
  real_T CD2CX_Gain;                   /* Expression: -1
                                        * '<S38>/CD2CX'
                                        */
  real_T CYBAF_RowIdx[2];              /* Expression: matybaf(2:3,1)
                                        * '<S47>/CYBAF'
                                        */
  real_T CYBAF_ColIdx[2];              /* Expression: matybaf(1,2:3)
                                        * '<S47>/CYBAF'
                                        */
  real_T CYBAF_Table[4];               /* Expression: matybaf(2:3,2:3)
                                        * '<S47>/CYBAF'
                                        */
  real_T CYBAB_RowIdx[4];              /* Expression: matybab(2:5,1)
                                        * '<S47>/CYBAB'
                                        */
  real_T CYBAB_ColIdx[4];              /* Expression: matybab(1,2:5)
                                        * '<S47>/CYBAB'
                                        */
  real_T CYBAB_Table[16];              /* Expression: matybab(2:5,2:5)
                                        * '<S47>/CYBAB'
                                        */
  real_T CYWAF_RowIdx[2];              /* Expression: matywaf(2:3,1)
                                        * '<S47>/CYWAF'
                                        */
  real_T CYWAF_ColIdx[2];              /* Expression: matywaf(1,2:3)
                                        * '<S47>/CYWAF'
                                        */
  real_T CYWAF_Table[4];               /* Expression: matywaf(2:3,2:3)
                                        * '<S47>/CYWAF'
                                        */
  real_T CYRUAF_RowIdx[2];             /* Expression: matyuaf(2:3,1)
                                        * '<S47>/CYRUAF'
                                        */
  real_T CYRUAF_ColIdx[2];             /* Expression: matyuaf(1,2:3)
                                        * '<S47>/CYRUAF'
                                        */
  real_T CYRUAF_Table[4];              /* Expression: matyuaf(2:3,2:3)
                                        * '<S47>/CYRUAF'
                                        */
  real_T Sat_UpperSat_m;               /* Expression: inf
                                        * '<S55>/Sat'
                                        */
  real_T Sat_LowerSat_p;               /* Expression: 0.06981
                                        * '<S55>/Sat'
                                        */
  real_T CYRAF_RowIdx[2];              /* Expression: matyraf(2:3,1)
                                        * '<S47>/CYRAF'
                                        */
  real_T CYRAF_ColIdx[2];              /* Expression: matyraf(1,2:3)
                                        * '<S47>/CYRAF'
                                        */
  real_T CYRAF_Table[4];               /* Expression: matyraf(2:3,2:3)
                                        * '<S47>/CYRAF'
                                        */
  real_T CYBUAF_RowIdx[2];             /* Expression: matbuaf(2:3,1)
                                        * '<S47>/CYBUAF'
                                        */
  real_T CYBUAF_ColIdx[2];             /* Expression: matbuaf(1,2:3)
                                        * '<S47>/CYBUAF'
                                        */
  real_T CYBUAF_Table[4];              /* Expression: matbuaf(2:3,2:3)
                                        * '<S47>/CYBUAF'
                                        */
  real_T KUUT_XData_e[3];              /* Expression: matuut(1,:)
                                        * '<S47>/KUUT'
                                        */
  real_T KUUT_YData_f[3];              /* Expression: matuut(2,:)
                                        * '<S47>/KUUT'
                                        */
  real_T CLAM_RowIdx[22];              /* Expression: matlam(2:23,1)
                                        * '<S42>/CLAM'
                                        */
  real_T CLAM_ColIdx[22];              /* Expression: matlam(1,2:23)
                                        * '<S42>/CLAM'
                                        */
  real_T CLAM_Table[484];              /* Expression: matlam(2:23,2:23)
                                        * '<S42>/CLAM'
                                        */
  real_T CLAF_RowIdx[22];              /* Expression: matlaf(2:23,1)
                                        * '<S42>/CLAF'
                                        */
  real_T CLAF_ColIdx[22];              /* Expression: matlaf(1,2:23)
                                        * '<S42>/CLAF'
                                        */
  real_T CLAF_Table[484];              /* Expression: matlaf(2:23,2:23)
                                        * '<S42>/CLAF'
                                        */
  real_T CLEAM_RowIdx[2];              /* Expression: matleam(2:3,1)
                                        * '<S42>/CLEAM'
                                        */
  real_T CLEAM_ColIdx[2];              /* Expression: matleam(1,2:3)
                                        * '<S42>/CLEAM'
                                        */
  real_T CLEAM_Table[4];               /* Expression: matleam(2:3,2:3)
                                        * '<S42>/CLEAM'
                                        */
  real_T CLEAF_RowIdx[22];             /* Expression: matleaf(2:23,1)
                                        * '<S42>/CLEAF'
                                        */
  real_T CLEAF_ColIdx[22];             /* Expression: matleaf(1,2:23)
                                        * '<S42>/CLEAF'
                                        */
  real_T CLEAF_Table[484];             /* Expression: matleaf(2:23,2:23)
                                        * '<S42>/CLEAF'
                                        */
  real_T Sat_UpperSat_a;               /* Expression: 1
                                        * '<S50>/Sat'
                                        */
  real_T Sat_LowerSat_o;               /* Expression: -inf
                                        * '<S50>/Sat'
                                        */
  real_T CLQAF_RowIdx[22];             /* Expression: matlqaf(2:23,1)
                                        * '<S42>/CLQAF'
                                        */
  real_T CLQAF_ColIdx[22];             /* Expression: matlqaf(1,2:23)
                                        * '<S42>/CLQAF'
                                        */
  real_T CLQAF_Table[484];             /* Expression: matlqaf(2:23,2:23)
                                        * '<S42>/CLQAF'
                                        */
  real_T KQXL_XData[2];                /* Expression: matqxl(1,:)
                                        * '<S42>/KQXL'
                                        */
  real_T KQXL_YData[2];                /* Expression: matqxl(2,:)
                                        * '<S42>/KQXL'
                                        */
  real_T CLUAF_RowIdx[22];             /* Expression: matluaf(2:23,1)
                                        * '<S42>/CLUAF'
                                        */
  real_T CLUAF_ColIdx[22];             /* Expression: matluaf(1,2:23)
                                        * '<S42>/CLUAF'
                                        */
  real_T CLUAF_Table[484];             /* Expression: matluaf(2:23,2:23)
                                        * '<S42>/CLUAF'
                                        */
  real_T CLQUAF_RowIdx[2];             /* Expression: matqlaf(2:3,1)
                                        * '<S42>/CLQUAF'
                                        */
  real_T CLQUAF_ColIdx[2];             /* Expression: matqlaf(1,2:3)
                                        * '<S42>/CLQUAF'
                                        */
  real_T CLQUAF_Table[4];              /* Expression: matqlaf(2:3,2:3)
                                        * '<S42>/CLQUAF'
                                        */
  real_T KUUT_XData_a[3];              /* Expression: matuut(1,:)
                                        * '<S42>/KUUT'
                                        */
  real_T KUUT_YData_m[3];              /* Expression: matuut(2,:)
                                        * '<S42>/KUUT'
                                        */
  real_T CLGAF_RowIdx[3];              /* Expression: matlgaf(2:4,1)
                                        * '<S42>/CLGAF'
                                        */
  real_T CLGAF_ColIdx[3];              /* Expression: matlgaf(1,2:4)
                                        * '<S42>/CLGAF'
                                        */
  real_T CLGAF_Table[9];               /* Expression: matlgaf(2:4,2:4)
                                        * '<S42>/CLGAF'
                                        */
  real_T Sat_UpperSat_a1;              /* Expression: 0.04
                                        * '<S49>/Sat'
                                        */
  real_T Sat_LowerSat_n;               /* Expression: -inf
                                        * '<S49>/Sat'
                                        */
  real_T rad2deg_Gain;                 /* Expression: (180/pi)
                                        * '<S49>/rad2deg'
                                        */
  real_T VDOMMYR37_XData[3];           /* Expression: vdommyr37(1,:)
                                        * '<S49>/VDOMMYR37'
                                        */
  real_T VDOMMYR37_YData[3];           /* Expression: vdommyr37(2,:)
                                        * '<S49>/VDOMMYR37'
                                        */
  real_T VDOMMYR40_Gain;               /* Expression: 1.6
                                        * '<S49>/VDOMMYR40'
                                        */
  real_T KGELHR_XData[10];             /* Expression: matelhr(1,:)
                                        * '<S42>/KGELHR'
                                        */
  real_T KGELHR_YData[10];             /* Expression: matelhr(2,:)
                                        * '<S42>/KGELHR'
                                        */
  real_T CL2CZ_Gain;                   /* Expression: -1
                                        * '<S38>/CL2CZ'
                                        */
  real_T CIBAF_RowIdx[3];              /* Expression: matibaf(2:4,1)
                                        * '<S43>/CIBAF'
                                        */
  real_T CIBAF_ColIdx[3];              /* Expression: matibaf(1,2:4)
                                        * '<S43>/CIBAF'
                                        */
  real_T CIBAF_Table[9];               /* Expression: matibaf(2:4,2:4)
                                        * '<S43>/CIBAF'
                                        */
  real_T CIBMH_RowIdx[9];              /* Expression: matibmh(2:10,1)
                                        * '<S43>/CIBMH'
                                        */
  real_T CIBMH_ColIdx[9];              /* Expression: matibmh(1,2:10)
                                        * '<S43>/CIBMH'
                                        */
  real_T CIBMH_Table[81];              /* Expression: matibmh(2:10,2:10)
                                        * '<S43>/CIBMH'
                                        */
  real_T Sfunction_P1_Size[2];         /* Computed Parameter: P1Size
                                        * '<S51>/S-function'
                                        */
  real_T Sfunction_P1[3];              /* Expression: yindex
                                        * '<S51>/S-function'
                                        */
  real_T Sfunction_P2_Size[2];         /* Computed Parameter: P2Size
                                        * '<S51>/S-function'
                                        */
  real_T Sfunction_P2[4];              /* Expression: xindex
                                        * '<S51>/S-function'
                                        */
  real_T Sfunction_P3_Size[2];         /* Computed Parameter: P3Size
                                        * '<S51>/S-function'
                                        */
  real_T Sfunction_P3[3];              /* Expression: zindex
                                        * '<S51>/S-function'
                                        */
  real_T Sfunction_P4_Size[2];         /* Computed Parameter: P4Size
                                        * '<S51>/S-function'
                                        */
  real_T Sfunction_P4[36];             /* Expression: table
                                        * '<S51>/S-function'
                                        */
  real_T CIWAF_RowIdx[2];              /* Expression: matiwaf(2:3,1)
                                        * '<S43>/CIWAF'
                                        */
  real_T CIWAF_ColIdx[2];              /* Expression: matiwaf(1,2:3)
                                        * '<S43>/CIWAF'
                                        */
  real_T CIWAF_Table[4];               /* Expression: matiwaf(2:3,2:3)
                                        * '<S43>/CIWAF'
                                        */
  real_T CIRUAF_RowIdx[2];             /* Expression: matiuaf(2:3,1)
                                        * '<S43>/CIRUAF'
                                        */
  real_T CIRUAF_ColIdx[2];             /* Expression: matiuaf(1,2:3)
                                        * '<S43>/CIRUAF'
                                        */
  real_T CIRUAF_Table[4];              /* Expression: matiuaf(2:3,2:3)
                                        * '<S43>/CIRUAF'
                                        */
  real_T CIRUMH_RowIdx[9];             /* Expression: matrumh(2:10,1)
                                        * '<S43>/CIRUMH'
                                        */
  real_T CIRUMH_ColIdx[9];             /* Expression: matrumh(1,2:10)
                                        * '<S43>/CIRUMH'
                                        */
  real_T CIRUMH_Table[81];             /* Expression: matrumh(2:10,2:10)
                                        * '<S43>/CIRUMH'
                                        */
  real_T CIWTAM_RowIdx[2];             /* Expression: matwtam(2:3,1)
                                        * '<S43>/CIWTAM'
                                        */
  real_T CIWTAM_ColIdx[2];             /* Expression: matwtam(1,2:3)
                                        * '<S43>/CIWTAM'
                                        */
  real_T CIWTAM_Table[4];              /* Expression: matwtam(2:3,2:3)
                                        * '<S43>/CIWTAM'
                                        */
  real_T CIPAF_RowIdx[2];              /* Expression: matipaf(2:3,1)
                                        * '<S43>/CIPAF'
                                        */
  real_T CIPAF_ColIdx[2];              /* Expression: matipaf(1,2:3)
                                        * '<S43>/CIPAF'
                                        */
  real_T CIPAF_Table[4];               /* Expression: matipaf(2:3,2:3)
                                        * '<S43>/CIPAF'
                                        */
  real_T CIPMH_RowIdx[9];              /* Expression: matipmh(2:10,1)
                                        * '<S43>/CIPMH'
                                        */
  real_T CIPMH_ColIdx[9];              /* Expression: matipmh(1,2:10)
                                        * '<S43>/CIPMH'
                                        */
  real_T CIPMH_Table[81];              /* Expression: matipmh(2:10,2:10)
                                        * '<S43>/CIPMH'
                                        */
  real_T CIRAF_RowIdx[3];              /* Expression: matiraf(2:4,1)
                                        * '<S43>/CIRAF'
                                        */
  real_T CIRAF_ColIdx[3];              /* Expression: matiraf(1,2:4)
                                        * '<S43>/CIRAF'
                                        */
  real_T CIRAF_Table[9];               /* Expression: matiraf(2:4,2:4)
                                        * '<S43>/CIRAF'
                                        */
  real_T LROLL_XData[3];               /* Expression: mateif(1,:)
                                        * '<S43>/LROLL'
                                        */
  real_T LROLL_YData[3];               /* Expression: mateif(2,:)
                                        * '<S43>/LROLL'
                                        */
  real_T Sat_UpperSat_m0;              /* Expression: 1
                                        * '<S52>/Sat'
                                        */
  real_T Sat_LowerSat_f;               /* Expression: 0
                                        * '<S52>/Sat'
                                        */
  real_T CMAM_RowIdx[22];              /* Expression: matmam(2:23,1)
                                        * '<S44>/CMAM '
                                        */
  real_T CMAM_ColIdx[22];              /* Expression: matmam(1,2:23)
                                        * '<S44>/CMAM '
                                        */
  real_T CMAM_Table[484];              /* Expression: matmam(2:23,2:23)
                                        * '<S44>/CMAM '
                                        */
  real_T CMAF_RowIdx[22];              /* Expression: matmaf(2:23,1)
                                        * '<S44>/CMAF'
                                        */
  real_T CMAF_ColIdx[22];              /* Expression: matmaf(1,2:23)
                                        * '<S44>/CMAF'
                                        */
  real_T CMAF_Table[484];              /* Expression: matmaf(2:23,2:23)
                                        * '<S44>/CMAF'
                                        */
  real_T CMEAM_RowIdx[22];             /* Expression: matmeam(2:23,1)
                                        * '<S44>/CMEAM'
                                        */
  real_T CMEAM_ColIdx[22];             /* Expression: matmeam(1,2:23)
                                        * '<S44>/CMEAM'
                                        */
  real_T CMEAM_Table[484];             /* Expression: matmeam(2:23,2:23)
                                        * '<S44>/CMEAM'
                                        */
  real_T CMEAF_RowIdx[22];             /* Expression: matmeaf(2:23,1)
                                        * '<S44>/CMEAF'
                                        */
  real_T CMEAF_ColIdx[22];             /* Expression: matmeaf(1,2:23)
                                        * '<S44>/CMEAF'
                                        */
  real_T CMEAF_Table[484];             /* Expression: matmeaf(2:23,2:23)
                                        * '<S44>/CMEAF'
                                        */
  real_T ealphas_XData[3];             /* Expression: ealphas(1,:)
                                        * '<S53>/ealphas'
                                        */
  real_T ealphas_YData[3];             /* Expression: ealphas(2,:)
                                        * '<S53>/ealphas'
                                        */
  real_T ealphag_XData[3];             /* Expression: ealphag(1,:)
                                        * '<S53>/ealphag'
                                        */
  real_T ealphag_YData[3];             /* Expression: ealphag(2,:)
                                        * '<S53>/ealphag'
                                        */
  real_T Sat_UpperSat_k;               /* Expression: 1
                                        * '<S53>/Sat'
                                        */
  real_T Sat_LowerSat_m;               /* Expression: 0
                                        * '<S53>/Sat'
                                        */
  real_T KEMEAS1_XData[3];             /* Expression: matemv1(1,:)
                                        * '<S44>/KEMEAS1'
                                        */
  real_T KEMEAS1_YData[3];             /* Expression: matemv1(2,:)
                                        * '<S44>/KEMEAS1'
                                        */
  real_T KEMEAS2_XData[3];             /* Expression: matemv2(1,:)
                                        * '<S44>/KEMEAS2'
                                        */
  real_T KEMEAS2_YData[3];             /* Expression: matemv2(2,:)
                                        * '<S44>/KEMEAS2'
                                        */
  real_T CMRBR_RowIdx[2];              /* Expression: matmrbr(2:3,1)
                                        * '<S44>/CMRBR'
                                        */
  real_T CMRBR_ColIdx[2];              /* Expression: matmrbr(1,2:3)
                                        * '<S44>/CMRBR'
                                        */
  real_T CMRBR_Table[4];               /* Expression: matmrbr(2:3,2:3)
                                        * '<S44>/CMRBR'
                                        */
  real_T CMETAM_RowIdx[2];             /* Expression: matetam(2:3,1)
                                        * '<S44>/CMETAM'
                                        */
  real_T CMETAM_ColIdx[2];             /* Expression: matetam(1,2:3)
                                        * '<S44>/CMETAM'
                                        */
  real_T CMETAM_Table[4];              /* Expression: matetam(2:3,2:3)
                                        * '<S44>/CMETAM'
                                        */
  real_T Neg_Gain;                     /* Expression: -1
                                        * '<S44>/Neg '
                                        */
  real_T CMBBF_RowIdx[17];             /* Expression: matmbbf(2:18,1)
                                        * '<S44>/CMBBF'
                                        */
  real_T CMBBF_ColIdx[17];             /* Expression: matmbbf(1,2:18)
                                        * '<S44>/CMBBF'
                                        */
  real_T CMBBF_Table[289];             /* Expression: matmbbf(2:18,2:18)
                                        * '<S44>/CMBBF'
                                        */
  real_T CMQAF_RowIdx[22];             /* Expression: matmqaf(2:23,1)
                                        * '<S44>/CMQAF'
                                        */
  real_T CMQAF_ColIdx[22];             /* Expression: matmqaf(1,2:23)
                                        * '<S44>/CMQAF'
                                        */
  real_T CMQAF_Table[484];             /* Expression: matmqaf(2:23,2:23)
                                        * '<S44>/CMQAF'
                                        */
  real_T massinit_Value[8];            /* Expression: massinit
                                        * '<S3>/massinit'
                                        */
  real_T KQXM_XData[2];                /* Expression: matqxm(1,:)
                                        * '<S44>/KQXM'
                                        */
  real_T KQXM_YData[2];                /* Expression: matqxm(2,:)
                                        * '<S44>/KQXM'
                                        */
  real_T CMQUAF_RowIdx[22];            /* Expression: matquaf(2:23,1)
                                        * '<S44>/CMQUAF'
                                        */
  real_T CMQUAF_ColIdx[22];            /* Expression: matquaf(1,2:23)
                                        * '<S44>/CMQUAF'
                                        */
  real_T CMQUAF_Table[484];            /* Expression: matquaf(2:23,2:23)
                                        * '<S44>/CMQUAF'
                                        */
  real_T CMEUAF_RowIdx[22];            /* Expression: mateuaf(2:23,1)
                                        * '<S44>/CMEUAF'
                                        */
  real_T CMEUAF_ColIdx[22];            /* Expression: mateuaf(1,2:23)
                                        * '<S44>/CMEUAF'
                                        */
  real_T CMEUAF_Table[484];            /* Expression: mateuaf(2:23,2:23)
                                        * '<S44>/CMEUAF'
                                        */
  real_T KUUT_XData_l[3];              /* Expression: matuut(1,:)
                                        * '<S44>/KUUT'
                                        */
  real_T KUUT_YData_g[3];              /* Expression: matuut(2,:)
                                        * '<S44>/KUUT'
                                        */
  real_T CMGAF_RowIdx[3];              /* Expression: matmgaf(2:4,1)
                                        * '<S44>/CMGAF'
                                        */
  real_T CMGAF_ColIdx[3];              /* Expression: matmgaf(1,2:4)
                                        * '<S44>/CMGAF'
                                        */
  real_T CMGAF_Table[9];               /* Expression: matmgaf(2:4,2:4)
                                        * '<S44>/CMGAF'
                                        */
  real_T rad2deg_Gain_l;               /* Expression: (180/pi)
                                        * '<S44>/rad2deg'
                                        */
  real_T VDOMMYR38_XData[3];           /* Expression: vdommyr38(1,:)
                                        * '<S44>/VDOMMYR38'
                                        */
  real_T VDOMMYR38_YData[3];           /* Expression: vdommyr38(2,:)
                                        * '<S44>/VDOMMYR38'
                                        */
  real_T Sat_UpperSat_mn;              /* Expression: inf
                                        * '<S54>/Sat'
                                        */
  real_T Sat_LowerSat_j;               /* Expression: 0.25
                                        * '<S54>/Sat'
                                        */
  real_T Neg_Gain_a;                   /* Expression: -1
                                        * '<S54>/Neg'
                                        */
  real_T KGEMEAS_XData[3];             /* Expression: matemve(1,:)
                                        * '<S44>/KGEMEAS'
                                        */
  real_T KGEMEAS_YData[3];             /* Expression: matemve(2,:)
                                        * '<S44>/KGEMEAS'
                                        */
  real_T KGEMHR_XData[10];             /* Expression: matemhr(1,:)
                                        * '<S44>/KGEMHR'
                                        */
  real_T KGEMHR_YData[10];             /* Expression: matemhr(2,:)
                                        * '<S44>/KGEMHR'
                                        */
  real_T CNBAF_RowIdx[2];              /* Expression: matnbaf(2:3,1)
                                        * '<S45>/CNBAF'
                                        */
  real_T CNBAF_ColIdx[2];              /* Expression: matnbaf(1,2:3)
                                        * '<S45>/CNBAF'
                                        */
  real_T CNBAF_Table[4];               /* Expression: matnbaf(2:3,2:3)
                                        * '<S45>/CNBAF'
                                        */
  real_T CNBMH_RowIdx[9];              /* Expression: matnbmh(2:10,1)
                                        * '<S45>/CNBMH'
                                        */
  real_T CNBMH_ColIdx[9];              /* Expression: matnbmh(1,2:10)
                                        * '<S45>/CNBMH'
                                        */
  real_T CNBMH_Table[81];              /* Expression: matnbmh(2:10,2:10)
                                        * '<S45>/CNBMH'
                                        */
  real_T CNBAB_RowIdx[4];              /* Expression: matnbab(2:5,1)
                                        * '<S45>/CNBAB'
                                        */
  real_T CNBAB_ColIdx[4];              /* Expression: matnbab(1,2:5)
                                        * '<S45>/CNBAB'
                                        */
  real_T CNBAB_Table[16];              /* Expression: matnbab(2:5,2:5)
                                        * '<S45>/CNBAB'
                                        */
  real_T CNWAF_RowIdx[3];              /* Expression: matnwaf(2:4,1)
                                        * '<S45>/CNWAF'
                                        */
  real_T CNWAF_ColIdx[3];              /* Expression: matnwaf(1,2:4)
                                        * '<S45>/CNWAF'
                                        */
  real_T CNWAF_Table[9];               /* Expression: matnwaf(2:4,2:4)
                                        * '<S45>/CNWAF'
                                        */
  real_T CNWMH_RowIdx[9];              /* Expression: matnwmh(2:10,1)
                                        * '<S45>/CNWMH'
                                        */
  real_T CNWMH_ColIdx[9];              /* Expression: matnwmh(1,2:10)
                                        * '<S45>/CNWMH'
                                        */
  real_T CNWMH_Table[81];              /* Expression: matnwmh(2:10,2:10)
                                        * '<S45>/CNWMH'
                                        */
  real_T CNRUAF_RowIdx[2];             /* Expression: matnuaf(2:3,1)
                                        * '<S45>/CNRUAF'
                                        */
  real_T CNRUAF_ColIdx[2];             /* Expression: matnuaf(1,2:3)
                                        * '<S45>/CNRUAF'
                                        */
  real_T CNRUAF_Table[4];              /* Expression: matnuaf(2:3,2:3)
                                        * '<S45>/CNRUAF'
                                        */
  real_T CNRTAM_RowIdx[2];             /* Expression: matrtam(2:3,1)
                                        * '<S45>/CNRTAM'
                                        */
  real_T CNRTAM_ColIdx[2];             /* Expression: matrtam(1,2:3)
                                        * '<S45>/CNRTAM'
                                        */
  real_T CNRTAM_Table[4];              /* Expression: matrtam(2:3,2:3)
                                        * '<S45>/CNRTAM'
                                        */
  real_T CNPAF_RowIdx[3];              /* Expression: matnpaf(2:4,1)
                                        * '<S45>/CNPAF'
                                        */
  real_T CNPAF_ColIdx[3];              /* Expression: matnpaf(1,2:4)
                                        * '<S45>/CNPAF'
                                        */
  real_T CNPAF_Table[9];               /* Expression: matnpaf(2:4,2:4)
                                        * '<S45>/CNPAF'
                                        */
  real_T CNPMH_RowIdx[9];              /* Expression: matnpmh(2:10,1)
                                        * '<S45>/CNPMH'
                                        */
  real_T CNPMH_ColIdx[9];              /* Expression: matnpmh(1,2:10)
                                        * '<S45>/CNPMH'
                                        */
  real_T CNPMH_Table[81];              /* Expression: matnpmh(2:10,2:10)
                                        * '<S45>/CNPMH'
                                        */
  real_T CNRAF_RowIdx[2];              /* Expression: matnraf(2:3,1)
                                        * '<S45>/CNRAF'
                                        */
  real_T CNRAF_ColIdx[2];              /* Expression: matnraf(1,2:3)
                                        * '<S45>/CNRAF'
                                        */
  real_T CNRAF_Table[4];               /* Expression: matnraf(2:3,2:3)
                                        * '<S45>/CNRAF'
                                        */
  real_T xref_Value;                   /* Expression: xcgref
                                        * '<S22>/xref'
                                        */
  real_T yref_Value;                   /* Expression: ycgref
                                        * '<S22>/yref'
                                        */
  real_T zref_Value;                   /* Expression: zcgref
                                        * '<S22>/zref'
                                        */
  real_T LLMNair_Gain[3];              /* Expression: [span chord span]
                                        * '<S57>/LL,M,N air'
                                        */
  real_T LLMNstab_Gain[3];             /* Expression: [span chord span]
                                        * '<S57>/LL,M,N stab'
                                        */
  real_T LLMNbody_Gain[3];             /* Expression: [span chord span]
                                        * '<S57>/LL,M,N body'
                                        */
  real_T LLMNearth_Gain[3];            /* Expression: [span chord span]
                                        * '<S57>/LL,M,N earth'
                                        */
  real_T CXug_Gain;                    /* Expression: 2
                                        * '<S46>/CX// ug'
                                        */
  real_T CDalpha_Value;                /* Expression: 0.57
                                        * '<S46>/CDalpha'
                                        */
  real_T zero_Value;                   /* Expression: 0
                                        * '<S46>/zero'
                                        */
  real_T zero_Value_b;                 /* Expression: 0
                                        * '<S47>/zero'
                                        */
  real_T CZug_Gain;                    /* Expression: 2
                                        * '<S46>/CZ// ug'
                                        */
  real_T CLalpha_Value;                /* Expression: 5.51
                                        * '<S46>/CLalpha'
                                        */
  real_T CZag_Gain;                    /* Expression: -1
                                        * '<S46>/CZ// ag'
                                        */
  real_T zero1_Value;                  /* Expression: 0
                                        * '<S46>/zero1'
                                        */
  real_T zero_Value_j;                 /* Expression: 0
                                        * '<S43>/zero'
                                        */
  real_T neg_Gain;                     /* Expression: -1
                                        * '<S43>/neg '
                                        */
  real_T zero_Value_f;                 /* Expression: 0
                                        * '<S44>/zero'
                                        */
  real_T CMAAM_RowIdx[21];             /* Expression: matmaam(2:22,1)
                                        * '<S44>/CMAAM'
                                        */
  real_T CMAAM_ColIdx[21];             /* Expression: matmaam(1,2:22)
                                        * '<S44>/CMAAM'
                                        */
  real_T CMAAM_Table[441];             /* Expression: matmaam(2:22,2:22)
                                        * '<S44>/CMAAM'
                                        */
  real_T CMAAF_RowIdx[21];             /* Expression: matmaaf(2:22,1)
                                        * '<S44>/CMAAF'
                                        */
  real_T CMAAF_ColIdx[21];             /* Expression: matmaaf(1,2:22)
                                        * '<S44>/CMAAF'
                                        */
  real_T CMAAF_Table[441];             /* Expression: matmaaf(2:22,2:22)
                                        * '<S44>/CMAAF'
                                        */
  real_T Gain_Gain;                    /* Expression: -2*lh/chord
                                        * '<S44>/Gain'
                                        */
  real_T Neg1_Gain;                    /* Expression: -1
                                        * '<S44>/Neg1'
                                        */
  real_T zero_Value_jj;                /* Expression: 0
                                        * '<S45>/zero'
                                        */
  real_T Neg_Gain_j;                   /* Expression: -1
                                        * '<S45>/Neg'
                                        */
  real_T xref_Value_l;                 /* Expression: xcgref
                                        * '<S26>/xref'
                                        */
  real_T yref_Value_j;                 /* Expression: ycgref
                                        * '<S26>/yref'
                                        */
  real_T zref_Value_f;                 /* Expression: zcgref
                                        * '<S26>/zref'
                                        */
  real_T LLMNair_Gain_c[3];            /* Expression: [span chord span]
                                        * '<S60>/LL,M,N air'
                                        */
  real_T LLMNstab_Gain_l[3];           /* Expression: [span chord span]
                                        * '<S60>/LL,M,N stab'
                                        */
  real_T LLMNbody_Gain_m[3];           /* Expression: [span chord span]
                                        * '<S60>/LL,M,N body'
                                        */
  real_T LLMNearth_Gain_a[3];          /* Expression: [span chord span]
                                        * '<S60>/LL,M,N earth'
                                        */
  real_T N1state_IC;                   /* Expression: xt0(2)
                                        * '<S76>/N1 state'
                                        */
  real_T THR_RowIdx[11];               /* Expression: matthr(2:12,1)
                                        * '<S75>/THR'
                                        */
  real_T THR_ColIdx[11];               /* Expression: matthr(1,2:12)
                                        * '<S75>/THR'
                                        */
  real_T THR_Table[121];               /* Expression: matthr(2:12,2:12)
                                        * '<S75>/THR'
                                        */
  real_T lbs2N_Gain;                   /* Expression: 0.4536*g0
                                        * '<S75>/lbs2N'
                                        */
  real_T Deng_Value[2];                /* Expression: Deng
                                        * '<S71>/Deng'
                                        */
  real_T Tn2Xtleft_Gain;               /* Expression: 1/sqrt(1+tan(tilteng(1))*tan(tilteng(1))+tan(toweng(1))*tan(toweng(1)))
                                        * '<S71>/Tn2Xt left'
                                        */
  real_T xeng1_Value;                  /* Expression: xeng(1)
                                        * '<S71>/xeng1'
                                        */
  real_T yeng1_Value;                  /* Expression: yeng(1)
                                        * '<S71>/yeng1'
                                        */
  real_T zeng1_Value;                  /* Expression: zeng(1)
                                        * '<S71>/zeng1'
                                        */
  real_T N1state_IC_f;                 /* Expression: xt0(2)
                                        * '<S84>/N1 state'
                                        */
  real_T THR_RowIdx_k[11];             /* Expression: matthr(2:12,1)
                                        * '<S83>/THR'
                                        */
  real_T THR_ColIdx_a[11];             /* Expression: matthr(1,2:12)
                                        * '<S83>/THR'
                                        */
  real_T THR_Table_k[121];             /* Expression: matthr(2:12,2:12)
                                        * '<S83>/THR'
                                        */
  real_T lbs2N_Gain_l;                 /* Expression: 0.4536*g0
                                        * '<S83>/lbs2N'
                                        */
  real_T Tn2Xtright_Gain;              /* Expression: 1/sqrt(1+tan(tilteng(2))*tan(tilteng(2))+tan(toweng(2))*tan(toweng(2)))
                                        * '<S71>/Tn2Xt right'
                                        */
  real_T xeng2_Value;                  /* Expression: xeng(2)
                                        * '<S71>/xeng2'
                                        */
  real_T yeng2_Value;                  /* Expression: yeng(2)
                                        * '<S71>/yeng2'
                                        */
  real_T zeng2_Value;                  /* Expression: zeng(2)
                                        * '<S71>/zeng2'
                                        */
  real_T Neg_Gain_f;                   /* Expression: -1
                                        * '<S65>/Neg '
                                        */
  real_T zero_Value_m;                 /* Expression: 0
                                        * '<S97>/zero'
                                        */
  real_T Parameter_IC;                 /* Expression: winddir
                                        * '<S134>/Parameter'
                                        */
  real_T Parameter_IC_h;               /* Expression: Vw915
                                        * '<S133>/Parameter'
                                        */
  real_T Switch_Threshold_m;           /* Expression: 300
                                        * '<S132>/Switch'
                                        */
  real_T Constant_Value_a;             /* Expression: 0
                                        * '<S132>/Constant'
                                        */
  real_T FVNogroundcontact_Value;      /* Expression: 0
                                        * '<S116>/FV No ground contact'
                                        */
  real_T FSSideForce_Value;            /* Expression: 0
                                        * '<S110>/FS Side Force'
                                        */
  real_T FVNogroundcontact_Value_o;    /* Expression: 0
                                        * '<S119>/FV No ground contact'
                                        */
  real_T FSSideForce_Value_d;          /* Expression: 0
                                        * '<S111>/FS Side Force'
                                        */
  real_T FVNogroundcontact_Value_a;    /* Expression: 0
                                        * '<S122>/FV No ground contact'
                                        */
  real_T FSSideForce_Value_h;          /* Expression: 0
                                        * '<S112>/FS Side Force'
                                        */
  real_T Fmu_Value;                    /* Expression: 0
                                        * '<S113>/Fmu'
                                        */
  real_T FSSideForce_Value_b;          /* Expression: 0
                                        * '<S113>/FS Side Force'
                                        */
  real_T MaxStrutDeflection_UpperSat;  /* Expression: deltagmax4
                                        * '<S125>/Max Strut Deflection'
                                        */
  real_T MaxStrutDeflection_LowerSat;  /* Expression: -inf
                                        * '<S125>/Max Strut Deflection'
                                        */
  real_T FVNogroundcontact_Value_j;    /* Expression: 0
                                        * '<S125>/FV No ground contact'
                                        */
  real_T zero_Value_fs[6];             /* Expression: [0 0 0 0 0 0]
                                        * '<S19>/zero'
                                        */
  real_T Switch_Threshold_p;           /* Expression: 0.95
                                        * '<S19>/Switch'
                                        */
  real_T zero_Value_l;                 /* Expression: 0
                                        * '<S38>/zero'
                                        */
  real_T CLFAAF_RowIdx[22];            /* Expression: matfaaf(2:23,1)
                                        * '<S42>/CLFAAF'
                                        */
  real_T CLFAAF_ColIdx[22];            /* Expression: matfaaf(1,2:23)
                                        * '<S42>/CLFAAF'
                                        */
  real_T CLFAAF_Table[484];            /* Expression: matfaaf(2:23,2:23)
                                        * '<S42>/CLFAAF'
                                        */
  real_T KFAXL_XData[2];               /* Expression: matfaxl(1,:)
                                        * '<S42>/KFAXL'
                                        */
  real_T KFAXL_YData[2];               /* Expression: matfaxl(2,:)
                                        * '<S42>/KFAXL'
                                        */
  real_T Gain_Gain_e;                  /* Expression: 0.01
                                        * '<S42>/Gain'
                                        */
  real_T CL2CZadot_Gain;               /* Expression: -1
                                        * '<S38>/CL2CZ adot'
                                        */
  real_T FCMFAGF_Gain;                 /* Expression: -2
                                        * '<S44>/FCMFAGF'
                                        */
  real_T LLMNair_Gain_h[3];            /* Expression: [span chord span]
                                        * '<S58>/LL,M,N air'
                                        */
  real_T LLMNstab_Gain_m[3];           /* Expression: [span chord span]
                                        * '<S58>/LL,M,N stab'
                                        */
  real_T LLMNbody_Gain_p[3];           /* Expression: [span chord span]
                                        * '<S58>/LL,M,N body'
                                        */
  real_T LLMNearth_Gain_g[3];          /* Expression: [span chord span]
                                        * '<S58>/LL,M,N earth'
                                        */
  real_T zero_Value_fv;                /* Expression: 0
                                        * '<S18>/zero'
                                        */
  real_T zero1_Value_o;                /* Expression: 0
                                        * '<S38>/zero1'
                                        */
  real_T LLMNair_Gain_e[3];            /* Expression: [span chord span]
                                        * '<S59>/LL,M,N air'
                                        */
  real_T LLMNstab_Gain_o[3];           /* Expression: [span chord span]
                                        * '<S59>/LL,M,N stab'
                                        */
  real_T LLMNbody_Gain_o[3];           /* Expression: [span chord span]
                                        * '<S59>/LL,M,N body'
                                        */
  real_T LLMNearth_Gain_k[3];          /* Expression: [span chord span]
                                        * '<S59>/LL,M,N earth'
                                        */
  real_T N2state_IC;                   /* Expression: xt0(1)
                                        * '<S77>/N2 state'
                                        */
  real_T FUELFL_RowIdx[13];            /* Expression: matff(2:14,1)
                                        * '<S75>/FUELFL'
                                        */
  real_T FUELFL_ColIdx[13];            /* Expression: matff(1,2:14)
                                        * '<S75>/FUELFL'
                                        */
  real_T FUELFL_Table[169];            /* Expression: matff(2:14,2:14)
                                        * '<S75>/FUELFL'
                                        */
  real_T kgs2lbshr_Gain;               /* Expression: 3600/0.4536
                                        * '<S75>/kg//s2lbs//hr'
                                        */
  real_T N2state_IC_i;                 /* Expression: xt0(1)
                                        * '<S85>/N2 state'
                                        */
  real_T FUELFL_RowIdx_e[13];          /* Expression: matff(2:14,1)
                                        * '<S83>/FUELFL'
                                        */
  real_T FUELFL_ColIdx_b[13];          /* Expression: matff(1,2:14)
                                        * '<S83>/FUELFL'
                                        */
  real_T FUELFL_Table_i[169];          /* Expression: matff(2:14,2:14)
                                        * '<S83>/FUELFL'
                                        */
  real_T kgs2lbshr_Gain_d;             /* Expression: 3600/0.4536
                                        * '<S83>/kg//s2lbs//hr'
                                        */
  real_T Constant_Value_k[2];          /* Expression: [0; 0]
                                        * '<S1>/Constant'
                                        */
  real_T Gain_Gain_eq;                 /* Expression: 13
                                        * '<S5>/Gain'
                                        */
  real_T Gain_Gain_g;                  /* Expression: 13
                                        * '<S6>/Gain'
                                        */
  real_T Gain_Gain_h;                  /* Expression: 13
                                        * '<S7>/Gain'
                                        */
  real_T Gain_Gain_m;                  /* Expression: 0.9
                                        * '<S8>/Gain'
                                        */
  real_T Gain_Gain_a;                  /* Expression: 0.6
                                        * '<S9>/Gain'
                                        */
  real_T rad2deg_Gain_p;               /* Expression: (180/pi)
                                        * '<S74>/rad2deg'
                                        */
  real_T Saturation_UpperSat_i;        /* Expression: 62
                                        * '<S75>/Saturation'
                                        */
  real_T Saturation_LowerSat_m;        /* Expression: 13.5
                                        * '<S75>/Saturation'
                                        */
  real_T m2ft_Gain;                    /* Expression: (1/0.3048)
                                        * '<S77>/m2ft'
                                        */
  real_T ft2FL_Gain;                   /* Expression: .01
                                        * '<S77>/ft2FL'
                                        */
  real_T N2D_RowIdx[9];                /* Expression: matn2d(2:10,1)
                                        * '<S77>/N2D'
                                        */
  real_T N2D_ColIdx[9];                /* Expression: matn2d(1,2:10)
                                        * '<S77>/N2D'
                                        */
  real_T N2D_Table[81];                /* Expression: matn2d(2:10,2:10)
                                        * '<S77>/N2D'
                                        */
  real_T N1D_RowIdx[13];               /* Expression: matn1d(2:14,1)
                                        * '<S76>/N1D'
                                        */
  real_T N1D_ColIdx[13];               /* Expression: matn1d(1,2:14)
                                        * '<S76>/N1D'
                                        */
  real_T N1D_Table[169];               /* Expression: matn1d(2:14,2:14)
                                        * '<S76>/N1D'
                                        */
  real_T Droop_Gain;                   /* Expression: 2
                                        * '<S76>/Droop'
                                        */
  real_T fN1cmax_XData[6];             /* Expression: [0 25 40 70 94  120]
                                        * '<S76>/fN1cmax'
                                        */
  real_T fN1cmax_YData[6];             /* Expression: [0   0   1   12 14  18]
                                        * '<S76>/fN1cmax'
                                        */
  real_T Switch_Threshold_j;           /* Expression: 0
                                        * '<S78>/Switch'
                                        */
  real_T fN1cmin_XData[5];             /* Expression: [25     50   60   94 100]
                                        * '<S76>/fN1cmin'
                                        */
  real_T fN1cmin_YData[5];             /* Expression: [-0.05  -0.05    -1    -30 -28]
                                        * '<S76>/fN1cmin'
                                        */
  real_T Switch_Threshold_l;           /* Expression: 0
                                        * '<S79>/Switch'
                                        */
  real_T Droop_XData[2];               /* Expression: [0 100]
                                        * '<S77>/Droop'
                                        */
  real_T Droop_YData[2];               /* Expression: [0.1  2]
                                        * '<S77>/Droop'
                                        */
  real_T fN2max_XData[4];              /* Expression: [25 40 70 94]
                                        * '<S77>/fN2max'
                                        */
  real_T fN2max_YData[4];              /* Expression: [0 3 8 10]
                                        * '<S77>/fN2max'
                                        */
  real_T Switch_Threshold_jq;          /* Expression: 0
                                        * '<S81>/Switch'
                                        */
  real_T fN2min_XData[5];              /* Expression: [25     50   60   94 100]
                                        * '<S77>/fN2min'
                                        */
  real_T fN2min_YData[5];              /* Expression: [-0.05  -0.05    -2    -20 -28]
                                        * '<S77>/fN2min'
                                        */
  real_T Switch_Threshold_d;           /* Expression: 0
                                        * '<S80>/Switch'
                                        */
  real_T rad2deg_Gain_g;               /* Expression: (180/pi)
                                        * '<S82>/rad2deg'
                                        */
  real_T Saturation_UpperSat_e;        /* Expression: 62
                                        * '<S83>/Saturation'
                                        */
  real_T Saturation_LowerSat_l;        /* Expression: 13.5
                                        * '<S83>/Saturation'
                                        */
  real_T m2ft_Gain_h;                  /* Expression: (1/0.3048)
                                        * '<S85>/m2ft'
                                        */
  real_T ft2FL_Gain_p;                 /* Expression: .01
                                        * '<S85>/ft2FL'
                                        */
  real_T N2D_RowIdx_f[9];              /* Expression: matn2d(2:10,1)
                                        * '<S85>/N2D'
                                        */
  real_T N2D_ColIdx_k[9];              /* Expression: matn2d(1,2:10)
                                        * '<S85>/N2D'
                                        */
  real_T N2D_Table_e[81];              /* Expression: matn2d(2:10,2:10)
                                        * '<S85>/N2D'
                                        */
  real_T N1D_RowIdx_k[13];             /* Expression: matn1d(2:14,1)
                                        * '<S84>/N1D'
                                        */
  real_T N1D_ColIdx_m[13];             /* Expression: matn1d(1,2:14)
                                        * '<S84>/N1D'
                                        */
  real_T N1D_Table_f[169];             /* Expression: matn1d(2:14,2:14)
                                        * '<S84>/N1D'
                                        */
  real_T Droop_Gain_n;                 /* Expression: 2
                                        * '<S84>/Droop'
                                        */
  real_T fN1cmax_XData_i[6];           /* Expression: [0 25 40 70 94  120]
                                        * '<S84>/fN1cmax'
                                        */
  real_T fN1cmax_YData_h[6];           /* Expression: [0   0   1   12 14  18]
                                        * '<S84>/fN1cmax'
                                        */
  real_T Switch_Threshold_pu;          /* Expression: 0
                                        * '<S86>/Switch'
                                        */
  real_T fN1cmin_XData_e[5];           /* Expression: [25     50   60   94 100]
                                        * '<S84>/fN1cmin'
                                        */
  real_T fN1cmin_YData_m[5];           /* Expression: [-0.05  -0.05    -1    -30 -28]
                                        * '<S84>/fN1cmin'
                                        */
  real_T Switch_Threshold_e;           /* Expression: 0
                                        * '<S87>/Switch'
                                        */
  real_T Droop_XData_h[2];             /* Expression: [0 100]
                                        * '<S85>/Droop'
                                        */
  real_T Droop_YData_g[2];             /* Expression: [0.1  2]
                                        * '<S85>/Droop'
                                        */
  real_T fN2max_XData_k[4];            /* Expression: [25 40 70 94]
                                        * '<S85>/fN2max'
                                        */
  real_T fN2max_YData_p[4];            /* Expression: [0 3 8 10]
                                        * '<S85>/fN2max'
                                        */
  real_T Switch_Threshold_h;           /* Expression: 0
                                        * '<S89>/Switch'
                                        */
  real_T fN2min_XData_e[5];            /* Expression: [25     50   60   94 100]
                                        * '<S85>/fN2min'
                                        */
  real_T fN2min_YData_m[5];            /* Expression: [-0.05  -0.05    -2    -20 -28]
                                        * '<S85>/fN2min'
                                        */
  real_T Switch_Threshold_b;           /* Expression: 0
                                        * '<S88>/Switch'
                                        */
  real_T Neg_Gain_m;                   /* Expression: -1
                                        * '<S104>/Neg '
                                        */
  real_T Constant_Value_h;             /* Expression: 0
                                        * '<S133>/Constant'
                                        */
  real_T Constant_Value_f;             /* Expression: 0
                                        * '<S134>/Constant'
                                        */
  real_T KGEDHR_XData_g[10];           /* Expression: matedhr(1,:)
                                        * '<S48>/KGEDHR'
                                        */
  real_T KGEDHR_YData_m[10];           /* Expression: matedhr(2,:)
                                        * '<S48>/KGEDHR'
                                        */
  real_T Sat_UpperSat_j;               /* Expression: 1
                                        * '<S48>/Sat'
                                        */
  real_T Sat_LowerSat_g;               /* Expression: 0
                                        * '<S48>/Sat'
                                        */
  real_T NonegativeStrutdeflection_UpperSat;/* Expression: inf
                                             * '<S122>/No negative  Strut deflection'
                                             */
  real_T NonegativeStrutdeflection_LowerSat;/* Expression: 0
                                             * '<S122>/No negative  Strut deflection'
                                             */
  real_T PreventEarthfrompullingacwhenFDFV_UpperSat;/* Expression: inf
                                                     * '<S122>/Prevent Earth  from pulling a//c when FD>FV'
                                                     */
  real_T PreventEarthfrompullingacwhenFDFV_LowerSat;/* Expression: 0
                                                     * '<S122>/Prevent Earth  from pulling a//c when FD>FV'
                                                     */
  real_T NonegativeStrutdeflection_UpperSat_m;/* Expression: inf
                                               * '<S119>/No negative  Strut deflection'
                                               */
  real_T NonegativeStrutdeflection_LowerSat_i;/* Expression: 0
                                               * '<S119>/No negative  Strut deflection'
                                               */
  real_T PreventEarthfrompullingacwhenFDFV_UpperSat_d;/* Expression: inf
                                                       * '<S119>/Prevent Earth  from pulling a//c when FD>FV'
                                                       */
  real_T PreventEarthfrompullingacwhenFDFV_LowerSat_i;/* Expression: 0
                                                       * '<S119>/Prevent Earth  from pulling a//c when FD>FV'
                                                       */
  real_T NonegativeStrutdeflection_UpperSat_ma;/* Expression: inf
                                                * '<S116>/No negative  Strut deflection'
                                                */
  real_T NonegativeStrutdeflection_LowerSat_k;/* Expression: 0
                                               * '<S116>/No negative  Strut deflection'
                                               */
  real_T PreventEarthfrompullingacwhenFDFV_UpperSat_f;/* Expression: inf
                                                       * '<S116>/Prevent Earth  from pulling a//c when FD>FV'
                                                       */
  real_T PreventEarthfrompullingacwhenFDFV_LowerSat_e;/* Expression: 0
                                                       * '<S116>/Prevent Earth  from pulling a//c when FD>FV'
                                                       */
  real_T PreventEarthfrompullingacwhenFDFV_UpperSat_d1;/* Expression: inf
                                                        * '<S125>/Prevent Earth  from pulling a//c when FD>FV'
                                                        */
  real_T PreventEarthfrompullingacwhenFDFV_LowerSat_d;/* Expression: 0
                                                       * '<S125>/Prevent Earth  from pulling a//c when FD>FV'
                                                       */
  real_T Switch_Threshold_c;           /* Expression: 0
                                        * '<S125>/Switch'
                                        */
  real_T Switch1_Threshold;            /* Expression: 0
                                        * '<S122>/Switch1'
                                        */
  real_T Switch1_Threshold_m;          /* Expression: 0
                                        * '<S119>/Switch1'
                                        */
  real_T Switch1_Threshold_g;          /* Expression: 0
                                        * '<S116>/Switch1'
                                        */
};

/* Real-time Model Data Structure */
struct rtModel_Citation {
  const char_T *path;
  const char_T *modelName;
  struct SimStruct_tag * *childSfunctions;
  const char_T *errorStatus;
  SS_SimMode simMode;
  RTWLogInfo *rtwLogInfo;
  RTWExtModeInfo *extModeInfo;
  RTWRTModelMethodsInfo modelMethodsInfo;
  RTWSolverInfo *solverInfo;
  void *sfcnInfo;

  /*
   * ModelData:
   * The following substructure contains information regarding
   * the data used in the model.
   */
  struct {
    void *blockIO;
    const void *constBlockIO;
    real_T *defaultParam;
    ZCSigState *prevZCSigState;
    real_T *contStates;
    real_T *derivs;
    real_T *zcSignalValues;
    void *inputs;
    void *outputs;
    boolean_T *contStateDisabled;
    boolean_T zCCacheNeedsReset;
    boolean_T derivCacheNeedsReset;
    boolean_T blkStateChange;
    boolean_T paramIsMalloced;
  } ModelData;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    uint32_T checksums[4];
    uint32_T options;
    int_T numContStates;
    int_T numU;
    int_T numY;
    int_T numSampTimes;
    int_T numBlocks;
    int_T numBlockIO;
    int_T numBlockPrms;
    int_T numDwork;
    int_T numSFcnPrms;
    int_T numSFcns;
    int_T numIports;
    int_T numOports;
    int_T numNonSampZCs;
    int_T sysDirFeedThru;
    int_T rtwGenSfcn;
  } Sizes;

  /*
   * SpecialInfo:
   * The following substructure contains special information
   * related to other components that are dependent on RTW.
   */
  struct {
    const void *mappingInfo;
    void *xpcData;
  } SpecialInfo;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    time_T stepSize;
    time_T tStart;
    time_T tFinal;
    time_T timeOfLastOutput;
    void *timingData;
    real_T *varNextHitTimesList;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *sampleTimes;
    time_T *offsetTimes;
    int_T *sampleTimeTaskIDPtr;
    int_T *sampleHits;
    int_T *perTaskSampleHits;
    time_T *t;
  } Timing;

  /*
   * Work:
   * The following substructure contains information regarding
   * the work vectors in the model.
   */
  struct {
    void *dwork;
  } Work;
};

/* External data declarations for dependent source files */
extern const char *RT_MEMORY_ALLOCATION_ERROR;

/* Simulation structure */
extern rtModel_Citation *const Citation_rtM;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : Citation
 * '<S1>'   : Citation/Cessna Citation 500
 * '<S2>'   : Citation/Cessna Citation 500/Actuators
 * '<S3>'   : Citation/Cessna Citation 500/Citation model DASMAT
 * '<S4>'   : Citation/Cessna Citation 500/Controllers
 * '<S5>'   : Citation/Cessna Citation 500/Actuators/da
 * '<S6>'   : Citation/Cessna Citation 500/Actuators/de
 * '<S7>'   : Citation/Cessna Citation 500/Actuators/dr
 * '<S8>'   : Citation/Cessna Citation 500/Actuators/flaps
 * '<S9>'   : Citation/Cessna Citation 500/Actuators/gear
 * '<S10>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL
 * '<S11>'  : Citation/Cessna Citation 500/Citation model DASMAT/Embedded MATLAB Function
 * '<S12>'  : Citation/Cessna Citation 500/Citation model DASMAT/Rudder hardover
 * '<S13>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/AFM
 * '<S14>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/AIRDATA
 * '<S15>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/EFM
 * '<S16>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/EQM
 * '<S17>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/FM SORT
 * '<S18>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/GRAVITY
 * '<S19>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/LANDING GEAR
 * '<S20>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/OBSERVATIONS
 * '<S21>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/WIND//TURBULENCE
 * '<S22>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/AFM/Aero axes-cg transformation
 * '<S23>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/AFM/Aeromod
 * '<S24>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/AFM/FMaerodims
 * '<S25>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/AFM/FMgustdims
 * '<S26>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/AFM/Gust axes-cg transformation
 * '<S27>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/AFM/Aero axes-cg transformation/MATLAB Function1
 * '<S28>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/AFM/Aero axes-cg transformation/MATLAB Function2
 * '<S29>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/AFM/Aero axes-cg transformation/MATLAB Function3
 * '<S30>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/AFM/Aero axes-cg transformation/MATLAB Function4
 * '<S31>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/AFM/Aero axes-cg transformation/MATLAB Function5
 * '<S32>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/AFM/Aero axes-cg transformation/MATLAB Function6
 * '<S33>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/AFM/Aero axes-cg transformation/MATLAB Function7
 * '<S34>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/AFM/Aero axes-cg transformation/MATLAB Function8
 * '<S35>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/AFM/Aero axes-cg transformation/MATLAB Function9
 * '<S36>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/AFM/Aeromod/SubSystem1
 * '<S37>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/AFM/Aeromod/SubSystem1/Ground effect
 * '<S38>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/AFM/Aeromod/SubSystem1/model
 * '<S39>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/AFM/Aeromod/SubSystem1/pqrnondims
 * '<S40>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/AFM/Aeromod/SubSystem1/rud-rudtrim coupling
 * '<S41>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/AFM/Aeromod/SubSystem1/model/CDCAL
 * '<S42>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/AFM/Aeromod/SubSystem1/model/CLCAL
 * '<S43>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/AFM/Aeromod/SubSystem1/model/CLLCAL
 * '<S44>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/AFM/Aeromod/SubSystem1/model/CMCAL
 * '<S45>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/AFM/Aeromod/SubSystem1/model/CNCAL
 * '<S46>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/AFM/Aeromod/SubSystem1/model/CXGUST CZGUST
 * '<S47>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/AFM/Aeromod/SubSystem1/model/CYCAL
 * '<S48>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/AFM/Aeromod/SubSystem1/model/CDCAL/KBASD
 * '<S49>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/AFM/Aeromod/SubSystem1/model/CLCAL/CLGEAF
 * '<S50>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/AFM/Aeromod/SubSystem1/model/CLCAL/SP0
 * '<S51>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/AFM/Aeromod/SubSystem1/model/CLLCAL/CIBAB
 * '<S52>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/AFM/Aeromod/SubSystem1/model/CLLCAL/LFACT
 * '<S53>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/AFM/Aeromod/SubSystem1/model/CMCAL/EALPHA
 * '<S54>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/AFM/Aeromod/SubSystem1/model/CMCAL/LFCMEGAF
 * '<S55>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/AFM/Aeromod/SubSystem1/model/CYCAL/LSFACT
 * '<S56>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/AFM/Aeromod/SubSystem1/pqrnondims/MATLAB Function10
 * '<S57>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/AFM/FMaerodims/dims
 * '<S58>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/AFM/FMaerodims/dims1
 * '<S59>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/AFM/FMaerodims/dims2
 * '<S60>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/AFM/FMgustdims/dims
 * '<S61>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/AFM/Gust axes-cg transformation/MATLAB Function1
 * '<S62>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/AFM/Gust axes-cg transformation/MATLAB Function2
 * '<S63>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/AFM/Gust axes-cg transformation/MATLAB Function3
 * '<S64>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/AIRDATA/MATLAB Function
 * '<S65>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/EFM/Engine axes-cg transformation
 * '<S66>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/EFM/Engmod
 * '<S67>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/EFM/Engine axes-cg transformation/MATLAB Function1
 * '<S68>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/EFM/Engine axes-cg transformation/MATLAB Function10
 * '<S69>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/EFM/Engine axes-cg transformation/MATLAB Function2
 * '<S70>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/EFM/Engmod/Citation eng_mod
 * '<S71>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/EFM/Engmod/Citation eng_mod/Subsystem1
 * '<S72>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/EFM/Engmod/Citation eng_mod/Subsystem1/JT15 Dynamic
 * '<S73>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/EFM/Engmod/Citation eng_mod/Subsystem1/JT15 Dynamic1
 * '<S74>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/EFM/Engmod/Citation eng_mod/Subsystem1/JT15 Dynamic/Subsystem
 * '<S75>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/EFM/Engmod/Citation eng_mod/Subsystem1/JT15 Dynamic/Subsystem/engine
 * '<S76>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/EFM/Engmod/Citation eng_mod/Subsystem1/JT15 Dynamic/Subsystem/engine/Fan
 * '<S77>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/EFM/Engmod/Citation eng_mod/Subsystem1/JT15 Dynamic/Subsystem/engine/Gasgenerator
 * '<S78>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/EFM/Engmod/Citation eng_mod/Subsystem1/JT15 Dynamic/Subsystem/engine/Fan/Max accel
 * '<S79>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/EFM/Engmod/Citation eng_mod/Subsystem1/JT15 Dynamic/Subsystem/engine/Fan/Max decel
 * '<S80>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/EFM/Engmod/Citation eng_mod/Subsystem1/JT15 Dynamic/Subsystem/engine/Gasgenerator/Max accel
 * '<S81>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/EFM/Engmod/Citation eng_mod/Subsystem1/JT15 Dynamic/Subsystem/engine/Gasgenerator/Min accel
 * '<S82>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/EFM/Engmod/Citation eng_mod/Subsystem1/JT15 Dynamic1/Subsystem
 * '<S83>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/EFM/Engmod/Citation eng_mod/Subsystem1/JT15 Dynamic1/Subsystem/engine
 * '<S84>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/EFM/Engmod/Citation eng_mod/Subsystem1/JT15 Dynamic1/Subsystem/engine/Fan
 * '<S85>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/EFM/Engmod/Citation eng_mod/Subsystem1/JT15 Dynamic1/Subsystem/engine/Gasgenerator
 * '<S86>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/EFM/Engmod/Citation eng_mod/Subsystem1/JT15 Dynamic1/Subsystem/engine/Fan/Max accel
 * '<S87>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/EFM/Engmod/Citation eng_mod/Subsystem1/JT15 Dynamic1/Subsystem/engine/Fan/Max decel
 * '<S88>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/EFM/Engmod/Citation eng_mod/Subsystem1/JT15 Dynamic1/Subsystem/engine/Gasgenerator/Max accel
 * '<S89>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/EFM/Engmod/Citation eng_mod/Subsystem1/JT15 Dynamic1/Subsystem/engine/Gasgenerator/Min accel
 * '<S90>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/EQM/CFMa correction
 * '<S91>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/EQM/State Derivatives
 * '<S92>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/EQM/State Derivatives/Vabdot
 * '<S93>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/EQM/State Derivatives/eulerdot
 * '<S94>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/EQM/State Derivatives/hxydot
 * '<S95>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/EQM/State Derivatives/mass properties
 * '<S96>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/EQM/State Derivatives/pqrdot
 * '<S97>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/EQM/State Derivatives/states transformation
 * '<S98>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/EQM/State Derivatives/Vabdot/Vdot
 * '<S99>'  : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/EQM/State Derivatives/Vabdot/abdot
 * '<S100>' : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/EQM/State Derivatives/pqrdot/Embedded MATLAB Function
 * '<S101>' : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/EQM/State Derivatives/states transformation/MATLAB Function1
 * '<S102>' : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/EQM/State Derivatives/states transformation/MATLAB Function10
 * '<S103>' : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/GRAVITY/MATLAB Function10
 * '<S104>' : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/LANDING GEAR/Gear axes-cg transformation
 * '<S105>' : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/LANDING GEAR/Landing Gear model
 * '<S106>' : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/LANDING GEAR/Gear axes-cg transformation/MATLAB Function1
 * '<S107>' : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/LANDING GEAR/Gear axes-cg transformation/MATLAB Function10
 * '<S108>' : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/LANDING GEAR/Gear axes-cg transformation/MATLAB Function2
 * '<S109>' : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/LANDING GEAR/Landing Gear model/Correct for terrain elevation
 * '<S110>' : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/LANDING GEAR/Landing Gear model/Left Main Gear
 * '<S111>' : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/LANDING GEAR/Landing Gear model/Nose Gear
 * '<S112>' : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/LANDING GEAR/Landing Gear model/Right Main Gear
 * '<S113>' : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/LANDING GEAR/Landing Gear model/Tail Scraper
 * '<S114>' : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/LANDING GEAR/Landing Gear model/Left Main Gear/Axes Transformation Heading attached vertical axis to body axis
 * '<S115>' : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/LANDING GEAR/Landing Gear model/Left Main Gear/Calculation of the Moments
 * '<S116>' : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/LANDING GEAR/Landing Gear model/Left Main Gear/FV Vertical Force
 * '<S117>' : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/LANDING GEAR/Landing Gear model/Nose Gear/Axes Transformation Heading attached vertical axis to body axis
 * '<S118>' : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/LANDING GEAR/Landing Gear model/Nose Gear/Calculation of the Moments
 * '<S119>' : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/LANDING GEAR/Landing Gear model/Nose Gear/F Vertical Force
 * '<S120>' : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/LANDING GEAR/Landing Gear model/Right Main Gear/Axes Transformation Heading attached vertical axis to body axis
 * '<S121>' : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/LANDING GEAR/Landing Gear model/Right Main Gear/Calculation of the Moments
 * '<S122>' : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/LANDING GEAR/Landing Gear model/Right Main Gear/FV Vertical Force
 * '<S123>' : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/LANDING GEAR/Landing Gear model/Tail Scraper/Axes Transformation Heading attached vertical axis to body axis
 * '<S124>' : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/LANDING GEAR/Landing Gear model/Tail Scraper/Calculation of the Moments
 * '<S125>' : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/LANDING GEAR/Landing Gear model/Tail Scraper/FV Vertical Force
 * '<S126>' : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/OBSERVATIONS/Acceleration
 * '<S127>' : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/OBSERVATIONS/Energy
 * '<S128>' : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/OBSERVATIONS/Flight-Path
 * '<S129>' : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/OBSERVATIONS/Acceleration/Transpose
 * '<S130>' : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/WIND//TURBULENCE/Logarithmic Wind model
 * '<S131>' : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/WIND//TURBULENCE/MATLAB Function9
 * '<S132>' : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/WIND//TURBULENCE/Logarithmic Wind model/Logarithmic Wind model
 * '<S133>' : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/WIND//TURBULENCE/Logarithmic Wind model/Logarithmic Wind model/Vwind915
 * '<S134>' : Citation/Cessna Citation 500/Citation model DASMAT/AIRCRAFT MODEL/WIND//TURBULENCE/Logarithmic Wind model/Logarithmic Wind model/Windddirection
 * '<S135>' : Citation/Cessna Citation 500/Controllers/Embedded MATLAB Function
 * '<S136>' : Citation/Cessna Citation 500/Controllers/Yaw damper
 */
#endif                                 /* RTW_HEADER_Citation_h_ */
