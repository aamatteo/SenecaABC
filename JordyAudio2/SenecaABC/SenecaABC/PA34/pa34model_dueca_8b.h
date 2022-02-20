/*
 * pa34model_dueca_8b.h
 *
 * Real-Time Workshop code generation for Simulink model "pa34model_dueca_8b.mdl".
 *
 * Model Version              : 1.20293
 * Real-Time Workshop version : 7.0  (R2007b)  02-Aug-2007
 * C source code generated on : Tue Jul 14 10:39:43 2015
 */
#ifndef RTW_HEADER_pa34model_dueca_8b_h_
#define RTW_HEADER_pa34model_dueca_8b_h_
#ifndef pa34model_dueca_8b_COMMON_INCLUDES_
# define pa34model_dueca_8b_COMMON_INCLUDES_
#include <stdlib.h>
#include <math.h>
#include <stddef.h>
#include <string.h>
#include "rtwtypes.h"
#include "rt_logging.h"
#include "rt_nonfinite.h"
#include "rt_atan2.h"
#include "rt_rand.h"
#include "rtlibsrc.h"
#endif                                 /* pa34model_dueca_8b_COMMON_INCLUDES_ */

#include "pa34model_dueca_8b_types.h"
#ifndef _RTW_COMBINE_MULTIPLE_MODELS
#define MODEL_NAME                     pa34model_dueca_8b
#define NSAMPLE_TIMES                  (2)                       /* Number of sample times */
#define NINPUTS                        (26)                      /* Number of model inputs */
#define NOUTPUTS                       (47)                      /* Number of model outputs */
#define NBLOCKIO                       (22)                      /* Number of data output port signals */
#define NUM_ZC_EVENTS                  (0)                       /* Number of zero-crossing events */
#ifndef NCSTATES
# define NCSTATES                      (17)                      /* Number of continuous states */
#elif NCSTATES != 17
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
#define pa34model_dueca_8b_rtModel     rtModel_pa34model_dueca_8b

/* Block signals (auto storage) */
typedef struct {
  real_T WhiteNoise[4];                /* '<S37>/White Noise' */
  real_T UnitDelay[12];                /* '<S34>/Unit Delay' */
  real_T Memory[2];                    /* '<S33>/Memory' */
  real_T Init[12];                     /* '<S9>/Init' */
  real_T x0dot[12];                    /* '<S1>/calc x0dot' */
  real_T y[10];                        /* '<S10>/adjusting CG due  to failure' */
  real_T Ef_uit[2];                    /* '<S10>/Setting rudder hardover' */
  real_T Pil_uit[10];                  /* '<S10>/Setting rudder hardover' */
  real_T engine[17];                   /* '<S10>/Engine Params' */
  real_T xgw[12];                      /* '<S34>/Dryden Wind Turbulence Model Embedded' */
  real_T xgustdot[3];                  /* '<S33>/Discrete Wind Gust Model Embedded' */
  real_T cur[2];                       /* '<S33>/Discrete Wind Gust Model Embedded' */
  real_T state_dot[12];                /* '<S1>/Equations of Motion' */
  real_T stateo[12];                   /* '<S6>/Wind Effect' */
  real_T atmoso[12];                   /* '<S6>/Wind Effect' */
  real_T d1;                           /* '<S6>/Ground Model' */
  real_T eng_state_dot[2];             /* '<S6>/Calculate Thrust Parameters' */
  real_T Thrust[12];                   /* '<S6>/Calculate Thrust Parameters' */
  real_T n_lr[4];                      /* '<S6>/Calculate Thrust Parameters' */
  real_T map_l;
  real_T map_r;
  real_T TmpHiddenBufferAtSFunctionInpor[6];/* '<S6>/AERO FORCES EN MOMENTS' */
  real_T FMAb[6];                      /* '<S6>/AERO FORCES EN MOMENTS' */
  boolean_T stop;                      /* '<S12>/Stop Function' */
} BlockIO_pa34model_dueca_8b;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T UnitDelay_DSTATE[12];         /* '<S34>/Unit Delay' */
  real_T NextOutput[4];                /* '<S37>/White Noise' */
  real_T Memory_PreviousInput[2];      /* '<S33>/Memory' */
  real_T Memory1_PreviousInput;        /* '<S9>/Memory1' */
  real_T Memory_PreviousInput_j[12];   /* '<S9>/Memory' */
  real_T W_basis;                      /* '<S10>/adjusting CG due  to failure' */
  real_T Cg_x_basis;                   /* '<S10>/adjusting CG due  to failure' */
  real_T Cg_y_basis;                   /* '<S10>/adjusting CG due  to failure' */
  real_T Cg_z_basis;                   /* '<S10>/adjusting CG due  to failure' */
  real_T Ixx_basis;                    /* '<S10>/adjusting CG due  to failure' */
  real_T Iyy_basis;                    /* '<S10>/adjusting CG due  to failure' */
  real_T Izz_basis;                    /* '<S10>/adjusting CG due  to failure' */
  real_T Ixz_basis;                    /* '<S10>/adjusting CG due  to failure' */
  real_T wheelspin_left;               /* '<S6>/Ground Model' */
  real_T wheelspin_right;              /* '<S6>/Ground Model' */
  real_T E1[104];                      /* '<S6>/Calculate Thrust Parameters' */
  real_T E2[104];                      /* '<S6>/Calculate Thrust Parameters' */
  real_T E3[104];                      /* '<S6>/Calculate Thrust Parameters' */
  real_T E4[91];                       /* '<S6>/Calculate Thrust Parameters' */
  real_T CT1[320];                     /* '<S6>/Calculate Thrust Parameters' */
  real_T CT2[320];                     /* '<S6>/Calculate Thrust Parameters' */
  real_T CT3[320];                     /* '<S6>/Calculate Thrust Parameters' */
  real_T CT4[320];                     /* '<S6>/Calculate Thrust Parameters' */
  real_T CPmin[64];                    /* '<S6>/Calculate Thrust Parameters' */
  real_T rpm1;                         /* '<S6>/Calculate Thrust Parameters' */
  real_T rpm2;                         /* '<S6>/Calculate Thrust Parameters' */
  real_T Th1;                          /* '<S6>/Calculate Thrust Parameters' */
  real_T Th2;                          /* '<S6>/Calculate Thrust Parameters' */
  real_T Table_7[76];                  /* '<S6>/AERO FORCES EN MOMENTS' */
  real_T Table_8[95];                  /* '<S6>/AERO FORCES EN MOMENTS' */
  real_T Table_9[76];                  /* '<S6>/AERO FORCES EN MOMENTS' */
  real_T Table_10[76];                 /* '<S6>/AERO FORCES EN MOMENTS' */
  real_T Table_11[76];                 /* '<S6>/AERO FORCES EN MOMENTS' */
  real_T Table_12[95];                 /* '<S6>/AERO FORCES EN MOMENTS' */
  real_T Table_13[76];                 /* '<S6>/AERO FORCES EN MOMENTS' */
  real_T Table_14[76];                 /* '<S6>/AERO FORCES EN MOMENTS' */
  real_T Table_15[76];                 /* '<S6>/AERO FORCES EN MOMENTS' */
  real_T Table_16[95];                 /* '<S6>/AERO FORCES EN MOMENTS' */
  real_T Table_17[5];                  /* '<S6>/AERO FORCES EN MOMENTS' */
  real_T Table_20[76];                 /* '<S6>/AERO FORCES EN MOMENTS' */
  real_T Table_21[95];                 /* '<S6>/AERO FORCES EN MOMENTS' */
  real_T Table_22[76];                 /* '<S6>/AERO FORCES EN MOMENTS' */
  real_T Table_23[76];                 /* '<S6>/AERO FORCES EN MOMENTS' */
  real_T Table_24[8];                  /* '<S6>/AERO FORCES EN MOMENTS' */
  real_T Table_25[38];                 /* '<S6>/AERO FORCES EN MOMENTS' */
  real_T Table_26[76];                 /* '<S6>/AERO FORCES EN MOMENTS' */
  real_T Table_27a[38];                /* '<S6>/AERO FORCES EN MOMENTS' */
  real_T Table_27b[38];                /* '<S6>/AERO FORCES EN MOMENTS' */
  real_T Table_27c[38];                /* '<S6>/AERO FORCES EN MOMENTS' */
  real_T Table_28a[38];                /* '<S6>/AERO FORCES EN MOMENTS' */
  real_T Table_28b[38];                /* '<S6>/AERO FORCES EN MOMENTS' */
  real_T Table_28c[38];                /* '<S6>/AERO FORCES EN MOMENTS' */
  real_T Table_29[10];                 /* '<S6>/AERO FORCES EN MOMENTS' */
  real_T Table_30[95];                 /* '<S6>/AERO FORCES EN MOMENTS' */
  real_T Table_32a[38];                /* '<S6>/AERO FORCES EN MOMENTS' */
  real_T Table_32b[38];                /* '<S6>/AERO FORCES EN MOMENTS' */
  struct {
    void *LoggedData;
  } Scope_PWORK;                       /* '<S6>/Scope' */

  uint32_T PreLookUpIndexSearchaltitude_DW;/* '<S39>/PreLook-Up Index Search  (altitude)' */
  uint32_T PreLookUpIndexSearchprobofexcee;/* '<S39>/PreLook-Up Index Search  (prob of exceed)' */
  uint32_T RandSeed[4];                /* '<S37>/White Noise' */
  struct {
    int_T IcNeedsLoading;
  } TrimState_IWORK;                   /* '<S1>/Trim State' */

  struct {
    int_T IcNeedsLoading;
  } InitialEngineState_IWORK;          /* '<S6>/Initial Engine State' */

  boolean_T W_basis_not_empty;         /* '<S10>/adjusting CG due  to failure' */
} D_Work_pa34model_dueca_8b;

/* Continuous states (auto storage) */
typedef struct {
  real_T TrimState_CSTATE[12];         /* '<S1>/Trim State' */
  real_T Integrator_CSTATE[3];         /* '<S33>/Integrator' */
  real_T InitialEngineState_CSTATE[2]; /* '<S6>/Initial Engine State' */
} ContinuousStates_pa34model_duec;

/* State derivatives (auto storage) */
typedef struct {
  real_T TrimState_CSTATE[12];         /* '<S1>/Trim State' */
  real_T Integrator_CSTATE[3];         /* '<S33>/Integrator' */
  real_T InitialEngineState_CSTATE[2]; /* '<S6>/Initial Engine State' */
} StateDerivatives_pa34model_duec;

/* State disabled  */
typedef struct {
  boolean_T TrimState_CSTATE[12];      /* '<S1>/Trim State' */
  boolean_T Integrator_CSTATE[3];      /* '<S33>/Integrator' */
  boolean_T InitialEngineState_CSTATE[2];/* '<S6>/Initial Engine State' */
} StateDisabled_pa34model_dueca_8;

/* Invariant block signals (auto storage) */
typedef struct {
  const real_T Constant1[12];          /* '<S2>/Constant1' */
  const real_T PreLookUpIndexSearchprobofe;/* '<S39>/PreLook-Up Index Search  (prob of exceed)' */
  const real_T Constant2[2];           /* '<S2>/Constant2' */
  const uint32_T PreLookUpIndexSearchprobo_a;/* '<S39>/PreLook-Up Index Search  (prob of exceed)' */
} ConstBlockIO_pa34model_dueca_8b;

/* For easy access from the SimStruct */
#define pa34model_dueca_8b_rtC(M)      ((ConstBlockIO_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->ModelData.constBlockIO)

/* Constant parameters (auto storage) */
typedef struct {
  /* Expression: h_vec
   * '<S39>/PreLook-Up Index Search  (altitude)'
   */
  real_T PreLookUpIndexSearch[12];

  /* Expression: sigma_vec'
   * '<S39>/Medium//High Altitude Intensity'
   */
  real_T MediumHighAltitudeIn[84];

  /* Expression: seed
   * '<S37>/White Noise'
   */
  real_T WhiteNoise_Seed[4];

  /* Expression: zeros(2,6)
   * '<S34>/Unit Delay'
   */
  real_T UnitDelay_X0[12];

  /* Expression: [120 120 80]
   * '<S33>/Gust build up lenght [m]'
   */
  real_T Gustbuilduplenghtm_Va[3];

  /* Expression: [3.5 3.0 3.0]
   * '<S33>/Gust amplitude [m//s]'
   */
  real_T Gustamplitudems_Value[3];

  /* Expression: terrainmap.xVec
   * '<S6>/TerrainMap'
   */
  real_T pooled9[2];

  /* Expression: terrainmap.hMat
   * '<S6>/TerrainMap'
   */
  real_T TerrainMap_Table[4];

  /* Computed Parameter: maxIndex
   * '<S39>/Medium//High Altitude Intensity'
   */
  uint32_T MediumHighAltitudeInt[2];
} ConstParam_pa34model_dueca_8b;

/* External inputs (root inport signals with auto storage) */
typedef struct {
  real_T In1[26];                      /* '<Root>/In1' */
} ExternalInputs_pa34model_dueca_;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real_T Out1[47];                     /* '<Root>/Out1' */
} ExternalOutputs_pa34model_dueca;

/* Real-time Model Data Structure */
struct rtModel_pa34model_dueca_8b {
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
extern const ConstParam_pa34model_dueca_8b pa34model_dueca_8b_ConstP;

/* External data declarations for dependent source files */
extern const char *RT_MEMORY_ALLOCATION_ERROR;

/* Simulation structure */
extern rtModel_pa34model_dueca_8b *const pa34model_dueca_8b_rtM;

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
 * '<Root>' : pa34model_dueca_8b
 * '<S1>'   : pa34model_dueca_8b/Aircraft Model
 * '<S2>'   : pa34model_dueca_8b/Read Inco
 * '<S3>'   : pa34model_dueca_8b/Aircraft Model/Button1
 * '<S4>'   : pa34model_dueca_8b/Aircraft Model/Button2
 * '<S5>'   : pa34model_dueca_8b/Aircraft Model/Button3
 * '<S6>'   : pa34model_dueca_8b/Aircraft Model/Calculate Forces & Moments
 * '<S7>'   : pa34model_dueca_8b/Aircraft Model/Create Output1
 * '<S8>'   : pa34model_dueca_8b/Aircraft Model/Equations of Motion
 * '<S9>'   : pa34model_dueca_8b/Aircraft Model/Initial State_dot
 * '<S10>'  : pa34model_dueca_8b/Aircraft Model/Models
 * '<S11>'  : pa34model_dueca_8b/Aircraft Model/Name States
 * '<S12>'  : pa34model_dueca_8b/Aircraft Model/Stop Function
 * '<S13>'  : pa34model_dueca_8b/Aircraft Model/calc x0dot
 * '<S14>'  : pa34model_dueca_8b/Aircraft Model/Calculate Forces & Moments/AERO FORCES EN MOMENTS
 * '<S15>'  : pa34model_dueca_8b/Aircraft Model/Calculate Forces & Moments/Calculate Ground Model Parameters
 * '<S16>'  : pa34model_dueca_8b/Aircraft Model/Calculate Forces & Moments/Calculate Thrust Parameters
 * '<S17>'  : pa34model_dueca_8b/Aircraft Model/Calculate Forces & Moments/Conditional Sum1
 * '<S18>'  : pa34model_dueca_8b/Aircraft Model/Calculate Forces & Moments/Force due to gravity
 * '<S19>'  : pa34model_dueca_8b/Aircraft Model/Calculate Forces & Moments/Ground Model
 * '<S20>'  : pa34model_dueca_8b/Aircraft Model/Calculate Forces & Moments/Translation to cg
 * '<S21>'  : pa34model_dueca_8b/Aircraft Model/Calculate Forces & Moments/Wind Effect
 * '<S22>'  : pa34model_dueca_8b/Aircraft Model/Models/Atmospherical Model
 * '<S23>'  : pa34model_dueca_8b/Aircraft Model/Models/Engine Params
 * '<S24>'  : pa34model_dueca_8b/Aircraft Model/Models/Geometric Model
 * '<S25>'  : pa34model_dueca_8b/Aircraft Model/Models/Geometry Sel
 * '<S26>'  : pa34model_dueca_8b/Aircraft Model/Models/Ground Model
 * '<S27>'  : pa34model_dueca_8b/Aircraft Model/Models/Name Inputs
 * '<S28>'  : pa34model_dueca_8b/Aircraft Model/Models/Setting rudder hardover
 * '<S29>'  : pa34model_dueca_8b/Aircraft Model/Models/adjusting CG due  to failure
 * '<S30>'  : pa34model_dueca_8b/Aircraft Model/Models/Atmospherical Model/Calc Atmos
 * '<S31>'  : pa34model_dueca_8b/Aircraft Model/Models/Atmospherical Model/Calc Wind params
 * '<S32>'  : pa34model_dueca_8b/Aircraft Model/Models/Atmospherical Model/Wind Models
 * '<S33>'  : pa34model_dueca_8b/Aircraft Model/Models/Atmospherical Model/Wind Models/Discrete Wind Gust Model
 * '<S34>'  : pa34model_dueca_8b/Aircraft Model/Models/Atmospherical Model/Wind Models/Dryden Wind Turbulence Model
 * '<S35>'  : pa34model_dueca_8b/Aircraft Model/Models/Atmospherical Model/Wind Models/Wind Shear Model Embedded
 * '<S36>'  : pa34model_dueca_8b/Aircraft Model/Models/Atmospherical Model/Wind Models/Discrete Wind Gust Model/Discrete Wind Gust Model Embedded
 * '<S37>'  : pa34model_dueca_8b/Aircraft Model/Models/Atmospherical Model/Wind Models/Dryden Wind Turbulence Model/Band-Limited White Noise
 * '<S38>'  : pa34model_dueca_8b/Aircraft Model/Models/Atmospherical Model/Wind Models/Dryden Wind Turbulence Model/Dryden Wind Turbulence Model Embedded
 * '<S39>'  : pa34model_dueca_8b/Aircraft Model/Models/Atmospherical Model/Wind Models/Dryden Wind Turbulence Model/Turbulence Intensity at medium to high alt
 * '<S40>'  : pa34model_dueca_8b/Aircraft Model/Stop Function/Stop Function
 */
#endif                                 /* RTW_HEADER_pa34model_dueca_8b_h_ */
