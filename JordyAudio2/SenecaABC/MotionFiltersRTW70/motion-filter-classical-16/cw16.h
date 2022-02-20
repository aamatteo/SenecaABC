/*
 * cw16.h
 *
 * Real-Time Workshop code generation for Simulink model "cw16.mdl".
 *
 * Model Version              : 1.125
 * Real-Time Workshop version : 7.0  (R2007b)  02-Aug-2007
 * C source code generated on : Sat Jul 23 11:13:50 2016
 */
#ifndef RTW_HEADER_cw16_h_
#define RTW_HEADER_cw16_h_
#ifndef cw16_COMMON_INCLUDES_
# define cw16_COMMON_INCLUDES_
#include <stdlib.h>
#include <math.h>
#include <stddef.h>
#include <string.h>
#include "rtwtypes.h"
#include "rt_logging.h"
#include "rt_nonfinite.h"
#include "rtlibsrc.h"
#endif                                 /* cw16_COMMON_INCLUDES_ */

#include "cw16_types.h"
#ifndef _RTW_COMBINE_MULTIPLE_MODELS
#define MODEL_NAME                     cw16
#define NSAMPLE_TIMES                  (2)                       /* Number of sample times */
#define NINPUTS                        (21)                      /* Number of model inputs */
#define NOUTPUTS                       (12)                      /* Number of model outputs */
#define NBLOCKIO                       (40)                      /* Number of data output port signals */
#define NUM_ZC_EVENTS                  (0)                       /* Number of zero-crossing events */
#ifndef NCSTATES
# define NCSTATES                      (59)                      /* Number of continuous states */
#elif NCSTATES != 59
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
#define cw16_rtModel                   rtModel_cw16

/* Block signals (auto storage) */
typedef struct {
  real_T Integrator;                   /* '<S13>/Integrator' */
  real_T Integrator1;                  /* '<S13>/Integrator1' */
  real_T Integrator2;                  /* '<S13>/Integrator2' */
  real_T Sum;                          /* '<S31>/Sum' */
  real_T Sum_e;                        /* '<S27>/Sum' */
  real_T Sum_n;                        /* '<S32>/Sum' */
  real_T Sum_h;                        /* '<S28>/Sum' */
  real_T Sum_k;                        /* '<S30>/Sum' */
  real_T Sum_nm;                       /* '<S29>/Sum' */
  real_T torequiredEulerangles[2];     /* '<S17>/to required Euler angles' */
  real_T Gain1;                        /* '<S35>/Gain1' */
  real_T Gain3;                        /* '<S35>/Gain3' */
  real_T betadlimiting[2];             /* '<S36>/betad limiting' */
  real_T Sum_j;                        /* '<S24>/Sum' */
  real_T Sum_b;                        /* '<S21>/Sum' */
  real_T Sum_bl;                       /* '<S23>/Sum' */
  real_T Sum_g;                        /* '<S20>/Sum' */
  real_T Sum_hv;                       /* '<S25>/Sum' */
  real_T Sum_bly;                      /* '<S22>/Sum' */
  real_T Sum1[3];                      /* '<S3>/Sum1' */
  real_T Integrator_a;                 /* '<S12>/Integrator' */
  real_T Integrator1_f;                /* '<S12>/Integrator1' */
  real_T Integrator2_c;                /* '<S12>/Integrator2' */
  real_T Sum4[3];                      /* '<S1>/Sum4' */
  real_T Integrator3;                  /* '<S23>/Integrator3' */
  real_T Integrator3_a;                /* '<S24>/Integrator3' */
  real_T Integrator3_c;                /* '<S25>/Integrator3' */
  real_T Integrator3_am;               /* '<S30>/Integrator3' */
  real_T Integrator3_k;                /* '<S31>/Integrator3' */
  real_T Integrator3_cu;               /* '<S32>/Integrator3' */
  real_T Gain;                         /* '<S38>/Gain' */
  real_T Gain1_j;                      /* '<S38>/Gain1' */
  real_T Gain2;                        /* '<S38>/Gain2' */
  real_T Integrator_h;                 /* '<S38>/Integrator' */
  real_T Integrator3_o;                /* '<S38>/Integrator3' */
  real_T Gain_n;                       /* '<S39>/Gain' */
  real_T Gain1_c;                      /* '<S39>/Gain1' */
  real_T Gain2_e;                      /* '<S39>/Gain2' */
  real_T Integrator_l;                 /* '<S39>/Integrator' */
  real_T Integrator3_d;                /* '<S39>/Integrator3' */
} BlockIO_cw16;

/* Continuous states (auto storage) */
typedef struct {
  real_T Integrator_CSTATE;            /* '<S13>/Integrator' */
  real_T Integrator1_CSTATE;           /* '<S13>/Integrator1' */
  real_T Integrator2_CSTATE;           /* '<S13>/Integrator2' */
  real_T Integrator_CSTATE_c;          /* '<S14>/Integrator' */
  real_T Integrator1_CSTATE_m;         /* '<S14>/Integrator1' */
  real_T Integrator2_CSTATE_f;         /* '<S14>/Integrator2' */
  real_T Integrator2_CSTATE_f2;        /* '<S31>/Integrator2' */
  real_T Integrator4_CSTATE;           /* '<S31>/Integrator4' */
  real_T Integrator2_CSTATE_b;         /* '<S27>/Integrator2' */
  real_T Integrator2_CSTATE_e;         /* '<S32>/Integrator2' */
  real_T Integrator4_CSTATE_j;         /* '<S32>/Integrator4' */
  real_T Integrator2_CSTATE_g;         /* '<S28>/Integrator2' */
  real_T Integrator2_CSTATE_j;         /* '<S30>/Integrator2' */
  real_T Integrator4_CSTATE_c;         /* '<S30>/Integrator4' */
  real_T Integrator2_CSTATE_n;         /* '<S29>/Integrator2' */
  real_T Integrator1_CSTATE_b;         /* '<S38>/Integrator1' */
  real_T Integrator1_CSTATE_c;         /* '<S39>/Integrator1' */
  real_T TransferFcn2_CSTATE;          /* '<S35>/Transfer Fcn2' */
  real_T TransferFcn3_CSTATE;          /* '<S35>/Transfer Fcn3' */
  real_T TransferFcn5_CSTATE;          /* '<S35>/Transfer Fcn5' */
  real_T TransferFcn4_CSTATE;          /* '<S35>/Transfer Fcn4' */
  real_T TransferFcn2_CSTATE_n;        /* '<S40>/Transfer Fcn2' */
  real_T TransferFcn5_CSTATE_l;        /* '<S40>/Transfer Fcn5' */
  real_T ratelimitedbeta_CSTATE[2];    /* '<S36>/rate limited beta' */
  real_T TransferFcn2_CSTATE_b;        /* '<S41>/Transfer Fcn2' */
  real_T TransferFcn5_CSTATE_m;        /* '<S41>/Transfer Fcn5' */
  real_T Integrator2_CSTATE_m;         /* '<S24>/Integrator2' */
  real_T Integrator4_CSTATE_a;         /* '<S24>/Integrator4' */
  real_T Integrator2_CSTATE_nu;        /* '<S21>/Integrator2' */
  real_T Integrator2_CSTATE_k;         /* '<S23>/Integrator2' */
  real_T Integrator4_CSTATE_e;         /* '<S23>/Integrator4' */
  real_T Integrator2_CSTATE_p;         /* '<S20>/Integrator2' */
  real_T Integrator2_CSTATE_a;         /* '<S25>/Integrator2' */
  real_T Integrator4_CSTATE_o;         /* '<S25>/Integrator4' */
  real_T Integrator2_CSTATE_c;         /* '<S22>/Integrator2' */
  real_T Integrator_CSTATE_b;          /* '<S12>/Integrator' */
  real_T Integrator1_CSTATE_i;         /* '<S12>/Integrator1' */
  real_T Integrator2_CSTATE_pu;        /* '<S12>/Integrator2' */
  real_T Integrator_CSTATE_l;          /* '<S11>/Integrator' */
  real_T Integrator1_CSTATE_ii;        /* '<S11>/Integrator1' */
  real_T Integrator2_CSTATE_h;         /* '<S11>/Integrator2' */
  real_T TransferFcn_CSTATE;           /* '<S45>/Transfer Fcn' */
  real_T TransferFcn1_CSTATE;          /* '<S45>/Transfer Fcn1' */
  real_T TransferFcn2_CSTATE_a;        /* '<S45>/Transfer Fcn2' */
  real_T Integrator3_CSTATE;           /* '<S23>/Integrator3' */
  real_T Integrator3_CSTATE_m;         /* '<S24>/Integrator3' */
  real_T Integrator3_CSTATE_k;         /* '<S25>/Integrator3' */
  real_T Integrator3_CSTATE_a;         /* '<S30>/Integrator3' */
  real_T Integrator3_CSTATE_n;         /* '<S31>/Integrator3' */
  real_T Integrator3_CSTATE_e;         /* '<S32>/Integrator3' */
  real_T Integrator2_CSTATE_jl;        /* '<S38>/Integrator2' */
  real_T Integrator4_CSTATE_f;         /* '<S38>/Integrator4' */
  real_T Integrator_CSTATE_bb;         /* '<S38>/Integrator' */
  real_T Integrator3_CSTATE_nd;        /* '<S38>/Integrator3' */
  real_T Integrator2_CSTATE_mi;        /* '<S39>/Integrator2' */
  real_T Integrator4_CSTATE_cn;        /* '<S39>/Integrator4' */
  real_T Integrator_CSTATE_a;          /* '<S39>/Integrator' */
  real_T Integrator3_CSTATE_o;         /* '<S39>/Integrator3' */
} ContinuousStates_cw16;

/* State derivatives (auto storage) */
typedef struct {
  real_T Integrator_CSTATE;            /* '<S13>/Integrator' */
  real_T Integrator1_CSTATE;           /* '<S13>/Integrator1' */
  real_T Integrator2_CSTATE;           /* '<S13>/Integrator2' */
  real_T Integrator_CSTATE_c;          /* '<S14>/Integrator' */
  real_T Integrator1_CSTATE_m;         /* '<S14>/Integrator1' */
  real_T Integrator2_CSTATE_f;         /* '<S14>/Integrator2' */
  real_T Integrator2_CSTATE_f2;        /* '<S31>/Integrator2' */
  real_T Integrator4_CSTATE;           /* '<S31>/Integrator4' */
  real_T Integrator2_CSTATE_b;         /* '<S27>/Integrator2' */
  real_T Integrator2_CSTATE_e;         /* '<S32>/Integrator2' */
  real_T Integrator4_CSTATE_j;         /* '<S32>/Integrator4' */
  real_T Integrator2_CSTATE_g;         /* '<S28>/Integrator2' */
  real_T Integrator2_CSTATE_j;         /* '<S30>/Integrator2' */
  real_T Integrator4_CSTATE_c;         /* '<S30>/Integrator4' */
  real_T Integrator2_CSTATE_n;         /* '<S29>/Integrator2' */
  real_T Integrator1_CSTATE_b;         /* '<S38>/Integrator1' */
  real_T Integrator1_CSTATE_c;         /* '<S39>/Integrator1' */
  real_T TransferFcn2_CSTATE;          /* '<S35>/Transfer Fcn2' */
  real_T TransferFcn3_CSTATE;          /* '<S35>/Transfer Fcn3' */
  real_T TransferFcn5_CSTATE;          /* '<S35>/Transfer Fcn5' */
  real_T TransferFcn4_CSTATE;          /* '<S35>/Transfer Fcn4' */
  real_T TransferFcn2_CSTATE_n;        /* '<S40>/Transfer Fcn2' */
  real_T TransferFcn5_CSTATE_l;        /* '<S40>/Transfer Fcn5' */
  real_T ratelimitedbeta_CSTATE[2];    /* '<S36>/rate limited beta' */
  real_T TransferFcn2_CSTATE_b;        /* '<S41>/Transfer Fcn2' */
  real_T TransferFcn5_CSTATE_m;        /* '<S41>/Transfer Fcn5' */
  real_T Integrator2_CSTATE_m;         /* '<S24>/Integrator2' */
  real_T Integrator4_CSTATE_a;         /* '<S24>/Integrator4' */
  real_T Integrator2_CSTATE_nu;        /* '<S21>/Integrator2' */
  real_T Integrator2_CSTATE_k;         /* '<S23>/Integrator2' */
  real_T Integrator4_CSTATE_e;         /* '<S23>/Integrator4' */
  real_T Integrator2_CSTATE_p;         /* '<S20>/Integrator2' */
  real_T Integrator2_CSTATE_a;         /* '<S25>/Integrator2' */
  real_T Integrator4_CSTATE_o;         /* '<S25>/Integrator4' */
  real_T Integrator2_CSTATE_c;         /* '<S22>/Integrator2' */
  real_T Integrator_CSTATE_b;          /* '<S12>/Integrator' */
  real_T Integrator1_CSTATE_i;         /* '<S12>/Integrator1' */
  real_T Integrator2_CSTATE_pu;        /* '<S12>/Integrator2' */
  real_T Integrator_CSTATE_l;          /* '<S11>/Integrator' */
  real_T Integrator1_CSTATE_ii;        /* '<S11>/Integrator1' */
  real_T Integrator2_CSTATE_h;         /* '<S11>/Integrator2' */
  real_T TransferFcn_CSTATE;           /* '<S45>/Transfer Fcn' */
  real_T TransferFcn1_CSTATE;          /* '<S45>/Transfer Fcn1' */
  real_T TransferFcn2_CSTATE_a;        /* '<S45>/Transfer Fcn2' */
  real_T Integrator3_CSTATE;           /* '<S23>/Integrator3' */
  real_T Integrator3_CSTATE_m;         /* '<S24>/Integrator3' */
  real_T Integrator3_CSTATE_k;         /* '<S25>/Integrator3' */
  real_T Integrator3_CSTATE_a;         /* '<S30>/Integrator3' */
  real_T Integrator3_CSTATE_n;         /* '<S31>/Integrator3' */
  real_T Integrator3_CSTATE_e;         /* '<S32>/Integrator3' */
  real_T Integrator2_CSTATE_jl;        /* '<S38>/Integrator2' */
  real_T Integrator4_CSTATE_f;         /* '<S38>/Integrator4' */
  real_T Integrator_CSTATE_bb;         /* '<S38>/Integrator' */
  real_T Integrator3_CSTATE_nd;        /* '<S38>/Integrator3' */
  real_T Integrator2_CSTATE_mi;        /* '<S39>/Integrator2' */
  real_T Integrator4_CSTATE_cn;        /* '<S39>/Integrator4' */
  real_T Integrator_CSTATE_a;          /* '<S39>/Integrator' */
  real_T Integrator3_CSTATE_o;         /* '<S39>/Integrator3' */
} StateDerivatives_cw16;

/* State disabled  */
typedef struct {
  boolean_T Integrator_CSTATE;         /* '<S13>/Integrator' */
  boolean_T Integrator1_CSTATE;        /* '<S13>/Integrator1' */
  boolean_T Integrator2_CSTATE;        /* '<S13>/Integrator2' */
  boolean_T Integrator_CSTATE_c;       /* '<S14>/Integrator' */
  boolean_T Integrator1_CSTATE_m;      /* '<S14>/Integrator1' */
  boolean_T Integrator2_CSTATE_f;      /* '<S14>/Integrator2' */
  boolean_T Integrator2_CSTATE_f2;     /* '<S31>/Integrator2' */
  boolean_T Integrator4_CSTATE;        /* '<S31>/Integrator4' */
  boolean_T Integrator2_CSTATE_b;      /* '<S27>/Integrator2' */
  boolean_T Integrator2_CSTATE_e;      /* '<S32>/Integrator2' */
  boolean_T Integrator4_CSTATE_j;      /* '<S32>/Integrator4' */
  boolean_T Integrator2_CSTATE_g;      /* '<S28>/Integrator2' */
  boolean_T Integrator2_CSTATE_j;      /* '<S30>/Integrator2' */
  boolean_T Integrator4_CSTATE_c;      /* '<S30>/Integrator4' */
  boolean_T Integrator2_CSTATE_n;      /* '<S29>/Integrator2' */
  boolean_T Integrator1_CSTATE_b;      /* '<S38>/Integrator1' */
  boolean_T Integrator1_CSTATE_c;      /* '<S39>/Integrator1' */
  boolean_T TransferFcn2_CSTATE;       /* '<S35>/Transfer Fcn2' */
  boolean_T TransferFcn3_CSTATE;       /* '<S35>/Transfer Fcn3' */
  boolean_T TransferFcn5_CSTATE;       /* '<S35>/Transfer Fcn5' */
  boolean_T TransferFcn4_CSTATE;       /* '<S35>/Transfer Fcn4' */
  boolean_T TransferFcn2_CSTATE_n;     /* '<S40>/Transfer Fcn2' */
  boolean_T TransferFcn5_CSTATE_l;     /* '<S40>/Transfer Fcn5' */
  boolean_T ratelimitedbeta_CSTATE[2]; /* '<S36>/rate limited beta' */
  boolean_T TransferFcn2_CSTATE_b;     /* '<S41>/Transfer Fcn2' */
  boolean_T TransferFcn5_CSTATE_m;     /* '<S41>/Transfer Fcn5' */
  boolean_T Integrator2_CSTATE_m;      /* '<S24>/Integrator2' */
  boolean_T Integrator4_CSTATE_a;      /* '<S24>/Integrator4' */
  boolean_T Integrator2_CSTATE_nu;     /* '<S21>/Integrator2' */
  boolean_T Integrator2_CSTATE_k;      /* '<S23>/Integrator2' */
  boolean_T Integrator4_CSTATE_e;      /* '<S23>/Integrator4' */
  boolean_T Integrator2_CSTATE_p;      /* '<S20>/Integrator2' */
  boolean_T Integrator2_CSTATE_a;      /* '<S25>/Integrator2' */
  boolean_T Integrator4_CSTATE_o;      /* '<S25>/Integrator4' */
  boolean_T Integrator2_CSTATE_c;      /* '<S22>/Integrator2' */
  boolean_T Integrator_CSTATE_b;       /* '<S12>/Integrator' */
  boolean_T Integrator1_CSTATE_i;      /* '<S12>/Integrator1' */
  boolean_T Integrator2_CSTATE_pu;     /* '<S12>/Integrator2' */
  boolean_T Integrator_CSTATE_l;       /* '<S11>/Integrator' */
  boolean_T Integrator1_CSTATE_ii;     /* '<S11>/Integrator1' */
  boolean_T Integrator2_CSTATE_h;      /* '<S11>/Integrator2' */
  boolean_T TransferFcn_CSTATE;        /* '<S45>/Transfer Fcn' */
  boolean_T TransferFcn1_CSTATE;       /* '<S45>/Transfer Fcn1' */
  boolean_T TransferFcn2_CSTATE_a;     /* '<S45>/Transfer Fcn2' */
  boolean_T Integrator3_CSTATE;        /* '<S23>/Integrator3' */
  boolean_T Integrator3_CSTATE_m;      /* '<S24>/Integrator3' */
  boolean_T Integrator3_CSTATE_k;      /* '<S25>/Integrator3' */
  boolean_T Integrator3_CSTATE_a;      /* '<S30>/Integrator3' */
  boolean_T Integrator3_CSTATE_n;      /* '<S31>/Integrator3' */
  boolean_T Integrator3_CSTATE_e;      /* '<S32>/Integrator3' */
  boolean_T Integrator2_CSTATE_jl;     /* '<S38>/Integrator2' */
  boolean_T Integrator4_CSTATE_f;      /* '<S38>/Integrator4' */
  boolean_T Integrator_CSTATE_bb;      /* '<S38>/Integrator' */
  boolean_T Integrator3_CSTATE_nd;     /* '<S38>/Integrator3' */
  boolean_T Integrator2_CSTATE_mi;     /* '<S39>/Integrator2' */
  boolean_T Integrator4_CSTATE_cn;     /* '<S39>/Integrator4' */
  boolean_T Integrator_CSTATE_a;       /* '<S39>/Integrator' */
  boolean_T Integrator3_CSTATE_o;      /* '<S39>/Integrator3' */
} StateDisabled_cw16;

/* Constant parameters (auto storage) */
typedef struct {
  /* Expression: [0 -1/g ;1/g 0]
   * '<S17>/to required Euler angles'
   */
  real_T torequiredEulerangles[4];

  /* Expression: tanh([-5:0.05:5])
   * Referenced by blocks:
   * '<S35>/Lookup Table'
   * '<S35>/Lookup Table1'
   */
  real_T pooled11[201];

  /* Expression: [-5:0.05:5]
   * Referenced by blocks:
   * '<S35>/Lookup Table'
   * '<S35>/Lookup Table1'
   */
  real_T pooled12[201];
} ConstParam_cw16;

/* External inputs (root inport signals with auto storage) */
typedef struct {
  real_T Input[21];                    /* '<Root>/Input' */
} ExternalInputs_cw16;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real_T Output_g[12];                 /* '<Root>/Output' */
} ExternalOutputs_cw16;

/* Parameters (auto storage) */
struct Parameters_cw16 {
  real_T Beta_rate;                    /* Expression: 1/Beta_rate
                                        * Referenced by blocks:
                                        * '<S35>/Gain'
                                        * '<S35>/Gain1'
                                        * '<S35>/Gain2'
                                        * '<S35>/Gain3'
                                        * '<S36>/betad limiting'
                                        */
  real_T HPomegabphi;                  /* Variable: HPomegabphi
                                        * '<S21>/Gain1'
                                        */
  real_T HPomegabpsi;                  /* Variable: HPomegabpsi
                                        * '<S22>/Gain1'
                                        */
  real_T HPomegabtheta;                /* Variable: HPomegabtheta
                                        * '<S20>/Gain1'
                                        */
  real_T HPomegabx;                    /* Variable: HPomegabx
                                        * '<S27>/Gain1'
                                        */
  real_T HPomegaby;                    /* Variable: HPomegaby
                                        * '<S28>/Gain1'
                                        */
  real_T HPomegabz;                    /* Variable: HPomegabz
                                        * '<S29>/Gain1'
                                        */
  real_T HPomeganphi;                  /* Variable: HPomeganphi
                                        * Referenced by blocks:
                                        * '<S24>/Gain'
                                        * '<S24>/Gain1'
                                        * '<S24>/Gain2'
                                        */
  real_T HPomeganpsi;                  /* Variable: HPomeganpsi
                                        * Referenced by blocks:
                                        * '<S25>/Gain'
                                        * '<S25>/Gain1'
                                        * '<S25>/Gain2'
                                        */
  real_T HPomegantheta;                /* Variable: HPomegantheta
                                        * Referenced by blocks:
                                        * '<S23>/Gain'
                                        * '<S23>/Gain1'
                                        * '<S23>/Gain2'
                                        */
  real_T HPomeganx;                    /* Variable: HPomeganx
                                        * Referenced by blocks:
                                        * '<S31>/Gain'
                                        * '<S31>/Gain1'
                                        * '<S31>/Gain2'
                                        */
  real_T HPomegany;                    /* Variable: HPomegany
                                        * Referenced by blocks:
                                        * '<S32>/Gain'
                                        * '<S32>/Gain1'
                                        * '<S32>/Gain2'
                                        */
  real_T HPomeganz;                    /* Variable: HPomeganz
                                        * Referenced by blocks:
                                        * '<S30>/Gain'
                                        * '<S30>/Gain1'
                                        * '<S30>/Gain2'
                                        */
  real_T HPzetaphi;                    /* Variable: HPzetaphi
                                        * '<S24>/Gain3'
                                        */
  real_T HPzetapsi;                    /* Variable: HPzetapsi
                                        * '<S25>/Gain3'
                                        */
  real_T HPzetatheta;                  /* Variable: HPzetatheta
                                        * '<S23>/Gain3'
                                        */
  real_T HPzetax;                      /* Variable: HPzetax
                                        * '<S31>/Gain3'
                                        */
  real_T HPzetay;                      /* Variable: HPzetay
                                        * '<S32>/Gain3'
                                        */
  real_T HPzetaz;                      /* Variable: HPzetaz
                                        * '<S30>/Gain3'
                                        */
  real_T Ktilteuler;                   /* Variable: Ktilteuler
                                        * '<S37>/euler tilt gain'
                                        */
  real_T Ktilteulerrate;               /* Variable: Ktilteulerrate
                                        * '<S37>/euler rate tilt gain'
                                        */
  real_T Ktiltrate;                    /* Variable: Ktiltrate
                                        * '<S36>/controller gain'
                                        */
  real_T LPomeganx;                    /* Variable: LPomeganx
                                        * Referenced by blocks:
                                        * '<S38>/Gain'
                                        * '<S38>/Gain1'
                                        * '<S38>/Gain2'
                                        */
  real_T LPomegany;                    /* Variable: LPomegany
                                        * Referenced by blocks:
                                        * '<S39>/Gain'
                                        * '<S39>/Gain1'
                                        * '<S39>/Gain2'
                                        */
  real_T LPzetax;                      /* Variable: LPzetax
                                        * '<S38>/Gain3'
                                        */
  real_T LPzetay;                      /* Variable: LPzetay
                                        * '<S39>/Gain3'
                                        */
  real_T gainfx;                       /* Variable: gainfx
                                        * '<S16>/Gain4'
                                        */
  real_T gainfxtilt;                   /* Variable: gainfxtilt
                                        * '<S17>/Gain6'
                                        */
  real_T gainfy;                       /* Variable: gainfy
                                        * '<S16>/Gain3'
                                        */
  real_T gainfytilt;                   /* Variable: gainfytilt
                                        * '<S17>/Gain2'
                                        */
  real_T gainfz;                       /* Variable: gainfz
                                        * '<S16>/Gain5'
                                        */
  real_T gainp;                        /* Variable: gainp
                                        * '<S15>/Gain9'
                                        */
  real_T gainq;                        /* Variable: gainq
                                        * '<S15>/Gain8'
                                        */
  real_T gainr;                        /* Variable: gainr
                                        * '<S15>/Gain7'
                                        */
  real_T kf[9];                        /* Variable: kf
                                        * '<S18>/kf'
                                        */
  real_T kw[9];                        /* Variable: kw
                                        * Referenced by blocks:
                                        * '<S19>/Matrix Gain'
                                        * '<S19>/Matrix Gain1'
                                        */
  real_T tiltcoordinationmethod;       /* Variable: tiltcoordinationmethod
                                        * '<S17>/tilt  coordination mode switch'
                                        */
  real_T xref_ac;                      /* Variable: xref_ac
                                        * Referenced by blocks:
                                        * '<S43>/xref_ac'
                                        * '<S48>/xref_ac'
                                        * '<S51>/xref_ac'
                                        */
  real_T xref_filt;                    /* Variable: xref_filt
                                        * Referenced by blocks:
                                        * '<S43>/xref_filt'
                                        * '<S48>/xref_filt'
                                        * '<S51>/xref_filt'
                                        * '<S14>/Integrator'
                                        */
  real_T yref_ac;                      /* Variable: yref_ac
                                        * Referenced by blocks:
                                        * '<S43>/yref_ac'
                                        * '<S48>/yref_ac'
                                        * '<S51>/yref_ac'
                                        */
  real_T yref_filt;                    /* Variable: yref_filt
                                        * Referenced by blocks:
                                        * '<S43>/yref_filt'
                                        * '<S48>/yref_filt'
                                        * '<S51>/yref_filt'
                                        * '<S14>/Integrator1'
                                        */
  real_T zref_ac;                      /* Variable: zref_ac
                                        * Referenced by blocks:
                                        * '<S43>/zref_ac'
                                        * '<S48>/zref_ac'
                                        * '<S51>/zref_ac'
                                        */
  real_T zref_filt;                    /* Variable: zref_filt
                                        * Referenced by blocks:
                                        * '<S43>/zref_filt'
                                        * '<S48>/zref_filt'
                                        * '<S51>/zref_filt'
                                        * '<S14>/Integrator2'
                                        */
};

/* Real-time Model Data Structure */
struct rtModel_cw16 {
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

/* Constant parameters (auto storage) */
extern const ConstParam_cw16 cw16_ConstP;

/* External data declarations for dependent source files */
extern const char *RT_MEMORY_ALLOCATION_ERROR;

/* Simulation structure */
extern rtModel_cw16 *const cw16_rtM;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S2>/SwitchControl' : Eliminated due to constant selection input
 * Block '<S2>/Constant' : Unused code path elimination
 * Block '<S6>/Gain1' : Unused code path elimination
 * Block '<S6>/Gain2' : Unused code path elimination
 * Block '<S6>/Nx-equation F_{DERP} F_{A}' : Unused code path elimination
 * Block '<S6>/Ny-equation F_{DERP} F_{A}' : Unused code path elimination
 * Block '<S6>/Nz-equation F_{DERP} F_{A}' : Unused code path elimination
 * Block '<S6>/Product' : Unused code path elimination
 * Block '<S6>/Product1' : Unused code path elimination
 * Block '<S46>/Clock' : Unused code path elimination
 * Block '<S46>/Constant' : Unused code path elimination
 * Block '<S46>/Constant1' : Unused code path elimination
 * Block '<S46>/Output' : Unused code path elimination
 * Block '<S46>/Product' : Unused code path elimination
 * Block '<S46>/Step' : Unused code path elimination
 * Block '<S46>/Sum' : Unused code path elimination
 * Block '<S6>/Saturation' : Unused code path elimination
 */

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
 * '<Root>' : cw16
 * '<S1>'   : cw16/Feedback Simulator State
 * '<S2>'   : cw16/Manual Switch
 * '<S3>'   : cw16/Motion Filter
 * '<S4>'   : cw16/Simulator state
 * '<S5>'   : cw16/Transform to pd, qd, rd
 * '<S6>'   : cw16/Translate from DERP to UGP in AC1
 * '<S7>'   : cw16/translate from  filter reference to  upper gimbal point  (motion base reference)
 * '<S8>'   : cw16/translate from A//C ref to filter ref in A//C
 * '<S9>'   : cw16/Feedback Simulator State/Euler angle and angular rate Feedback
 * '<S10>'  : cw16/Feedback Simulator State/Position Velocity Feedback
 * '<S11>'  : cw16/Feedback Simulator State/Euler angle and angular rate Feedback/integrating to beta
 * '<S12>'  : cw16/Feedback Simulator State/Euler angle and angular rate Feedback/integrating to betad
 * '<S13>'  : cw16/Feedback Simulator State/Position Velocity Feedback/integrating2
 * '<S14>'  : cw16/Feedback Simulator State/Position Velocity Feedback/integrating3
 * '<S15>'  : cw16/Motion Filter/High Pass Channel Angular Accelerations
 * '<S16>'  : cw16/Motion Filter/High Pass Channel Specific Forces
 * '<S17>'  : cw16/Motion Filter/Low Pass Channel Specific Forces
 * '<S18>'  : cw16/Motion Filter/f-scale
 * '<S19>'  : cw16/Motion Filter/w-scale
 * '<S20>'  : cw16/Motion Filter/High Pass Channel Angular Accelerations/HP 1st order pitch - wb
 * '<S21>'  : cw16/Motion Filter/High Pass Channel Angular Accelerations/HP 1st order roll - wb
 * '<S22>'  : cw16/Motion Filter/High Pass Channel Angular Accelerations/HP 1st order yaw - wb
 * '<S23>'  : cw16/Motion Filter/High Pass Channel Angular Accelerations/HP 2nd order pitch - wn
 * '<S24>'  : cw16/Motion Filter/High Pass Channel Angular Accelerations/HP 2nd order roll - wn
 * '<S25>'  : cw16/Motion Filter/High Pass Channel Angular Accelerations/HP 2nd order yaw - wn
 * '<S26>'  : cw16/Motion Filter/High Pass Channel Angular Accelerations/transformation of scaled A//C rotations to sim Euler angle accelerations
 * '<S27>'  : cw16/Motion Filter/High Pass Channel Specific Forces/HP 1st order X - wb
 * '<S28>'  : cw16/Motion Filter/High Pass Channel Specific Forces/HP 1st order Y - wb
 * '<S29>'  : cw16/Motion Filter/High Pass Channel Specific Forces/HP 1st order Z - wb
 * '<S30>'  : cw16/Motion Filter/High Pass Channel Specific Forces/HP 2n order Z - wn
 * '<S31>'  : cw16/Motion Filter/High Pass Channel Specific Forces/HP 2nd order X - wn
 * '<S32>'  : cw16/Motion Filter/High Pass Channel Specific Forces/HP 2nd order Y - wn
 * '<S33>'  : cw16/Motion Filter/High Pass Channel Specific Forces/Ramp1
 * '<S34>'  : cw16/Motion Filter/High Pass Channel Specific Forces/transformation from body to inertial frame of reference
 * '<S35>'  : cw16/Motion Filter/Low Pass Channel Specific Forces/1) straight differentiation
 * '<S36>'  : cw16/Motion Filter/Low Pass Channel Specific Forces/2) differentiation  with rate limit  compensation
 * '<S37>'  : cw16/Motion Filter/Low Pass Channel Specific Forces/3) controller
 * '<S38>'  : cw16/Motion Filter/Low Pass Channel Specific Forces/LP filter surge - X
 * '<S39>'  : cw16/Motion Filter/Low Pass Channel Specific Forces/LP filter sway - Y
 * '<S40>'  : cw16/Motion Filter/Low Pass Channel Specific Forces/2) differentiation  with rate limit  compensation/differentiating filter: betad
 * '<S41>'  : cw16/Motion Filter/Low Pass Channel Specific Forces/2) differentiation  with rate limit  compensation/differentiating filter: betadd
 * '<S42>'  : cw16/Simulator state/calculate position and velocity in filter reference point, for state feedback inside filter
 * '<S43>'  : cw16/Simulator state/reference points
 * '<S44>'  : cw16/Simulator state/transformation to Euler angle rates
 * '<S45>'  : cw16/Transform to pd, qd, rd/Integrate to  4: phid 5: thetad 6: psid
 * '<S46>'  : cw16/Translate from DERP to UGP in AC1/Ramp
 * '<S47>'  : cw16/translate from  filter reference to  upper gimbal point  (motion base reference)/move inertial acceleration setpoints in MF reference point to UGP reference point
 * '<S48>'  : cw16/translate from  filter reference to  upper gimbal point  (motion base reference)/reference points
 * '<S49>'  : cw16/translate from A//C ref to filter ref in A//C/Embedded MATLAB Function
 * '<S50>'  : cw16/translate from A//C ref to filter ref in A//C/Ramp
 * '<S51>'  : cw16/translate from A//C ref to filter ref in A//C/reference points
 */
#endif                                 /* RTW_HEADER_cw16_h_ */
