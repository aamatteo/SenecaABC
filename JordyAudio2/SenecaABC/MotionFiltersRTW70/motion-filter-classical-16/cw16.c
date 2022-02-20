/*
 * cw16.c
 *
 * Real-Time Workshop code generation for Simulink model "cw16.mdl".
 *
 * Model Version              : 1.125
 * Real-Time Workshop version : 7.0  (R2007b)  02-Aug-2007
 * C source code generated on : Sat Jul 23 11:13:50 2016
 */

#include <math.h>
#include "cw16.h"
#include "cw16_private.h"

/* Block parameters (auto storage) */
static Parameters_cw16 cw16_DefaultParameters = {
  5.2359877559829890E-002,
  0.0,
  0.0,
  0.0,
  0.0,
  0.0,
  0.2,
  1.0,
  1.0,
  0.8,
  0.8,
  1.0,
  1.0,
  1.0,
  1.0,
  1.0,
  1.0,
  1.0,
  1.0,
  0.2,
  0.5,
  5.0,
  2.0,
  2.0,
  1.0,
  1.0,
  1.0,
  1.0,
  1.0,
  1.0,
  1.0,
  1.0,
  1.0,
  1.0,

  { 0.6, 0.0, 0.0, 0.0, 0.6, 0.0, 0.0, 0.0, 0.5 },

  { 0.6, 0.0, 0.0, 0.0, 0.6, 0.0, 0.0, 0.0, 0.6 },
  1.0,
  0.0,
  0.0,
  0.0,
  0.0,
  -1.2075,
  0.0
};

real_T look1_binlc(real_T u0, const real_T *const bp0, const real_T *const table,
                   uint32_T maxIndex)
{
  real_T y;
  uint32_T bpIdx;
  real_T frac;
  real_T fractions;

  /* Lookup 1-D
     Search method: 'binary'
     Use previous index: 'off'
     Interpolation method: 'Linear'
     Extrapolation method: 'Clip'
     Use last breakpoint for index at or above upper limit: 'off'
   */
  bpIdx = plook_u32ddd_binc(u0, bp0, maxIndex, &frac);
  fractions = frac;
  y = intrp1d_ydd_lc(bpIdx, fractions, table);
  return y;
}

uint32_T plook_u32ddd_binc(real_T u, const real_T *const bp, uint32_T maxIndex,
  real_T *fraction)
{
  uint32_T bpIndex;
  real_T bpLeftCast;
  real_T bpRghtCast;

  /* Prelookup Index and Fraction
     Search method: 'binary'
     Process out of range input: 'Clip to range'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'off'
   */
  if (u < bp[0U]) {
    bpIndex = 0U;
    *fraction = 0.0;
  } else if (u < bp[maxIndex]) {
    bpIndex = binsearch_u32d(u, bp, (maxIndex + 1U) >> 1U, maxIndex);
    bpLeftCast = bp[bpIndex];
    bpRghtCast = bp[bpIndex + 1U];
    *fraction = (u - bpLeftCast) / (bpRghtCast - bpLeftCast);
  } else {
    bpIndex = maxIndex - 1U;
    *fraction = 1.0;
  }

  return bpIndex;
}

real_T intrp1d_ydd_lc(uint32_T bpIndex, real_T frac, const real_T *const table)
{
  real_T y;
  real_T yL_0d0;
  real_T yR_0d0;

  /* Interpolation 1-D
     Interpolation method: 'Linear'
     Extrapolation method: 'Clip'
     Use last breakpoint for index at or above upper limit: 'off'
   */
  yR_0d0 = table[bpIndex + 1U];
  yL_0d0 = table[bpIndex];
  y = (yR_0d0 - yL_0d0) * frac + yL_0d0;
  return y;
}

uint32_T binsearch_u32d(real_T u, const real_T *const bp, uint32_T startIndex,
  uint32_T maxIndex)
{
  uint32_T bpIndex;
  uint32_T iRght;
  uint32_T iLeft;
  uint32_T bpIdx;

  /* Binary Search */
  bpIdx = startIndex;
  iLeft = 0U;
  iRght = maxIndex;
  while (iRght - iLeft > 1U) {
    if (u < bp[bpIdx]) {
      iRght = bpIdx;
    } else {
      iLeft = bpIdx;
    }

    bpIdx = (iRght + iLeft) >> 1U;
  }

  bpIndex = iLeft;
  return bpIndex;
}

/* Initial conditions for root system: '<Root>' */
static void MdlInitialize(rtModel_cw16 *cw16_rtM)
{
  /* InitializeConditions for Integrator: '<S13>/Integrator' */
  ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)->Integrator_CSTATE =
    0.0;

  /* InitializeConditions for Integrator: '<S13>/Integrator1' */
  ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)->Integrator1_CSTATE
    = 0.0;

  /* InitializeConditions for Integrator: '<S13>/Integrator2' */
  ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)->Integrator2_CSTATE
    = 0.0;

  /* InitializeConditions for Integrator: '<S14>/Integrator' */
  ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
    ->Integrator_CSTATE_c = ((Parameters_cw16 *)
    cw16_rtM->ModelData.defaultParam)->xref_filt;

  /* InitializeConditions for Integrator: '<S14>/Integrator1' */
  ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
    ->Integrator1_CSTATE_m = ((Parameters_cw16 *)
    cw16_rtM->ModelData.defaultParam)->yref_filt;

  /* InitializeConditions for Integrator: '<S14>/Integrator2' */
  ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
    ->Integrator2_CSTATE_f = ((Parameters_cw16 *)
    cw16_rtM->ModelData.defaultParam)->zref_filt;

  /* InitializeConditions for Integrator: '<S31>/Integrator2' */
  ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
    ->Integrator2_CSTATE_f2 = 0.0;

  /* InitializeConditions for Integrator: '<S31>/Integrator4' */
  ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)->Integrator4_CSTATE
    = 0.0;

  /* InitializeConditions for Integrator: '<S27>/Integrator2' */
  ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
    ->Integrator2_CSTATE_b = 0.0;

  /* InitializeConditions for Integrator: '<S32>/Integrator2' */
  ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
    ->Integrator2_CSTATE_e = 0.0;

  /* InitializeConditions for Integrator: '<S32>/Integrator4' */
  ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
    ->Integrator4_CSTATE_j = 0.0;

  /* InitializeConditions for Integrator: '<S28>/Integrator2' */
  ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
    ->Integrator2_CSTATE_g = 0.0;

  /* InitializeConditions for Integrator: '<S30>/Integrator2' */
  ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
    ->Integrator2_CSTATE_j = 0.0;

  /* InitializeConditions for Integrator: '<S30>/Integrator4' */
  ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
    ->Integrator4_CSTATE_c = 0.0;

  /* InitializeConditions for Integrator: '<S29>/Integrator2' */
  ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
    ->Integrator2_CSTATE_n = 0.0;

  /* InitializeConditions for Integrator: '<S38>/Integrator1' */
  ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
    ->Integrator1_CSTATE_b = 0.0;

  /* InitializeConditions for Integrator: '<S39>/Integrator1' */
  ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
    ->Integrator1_CSTATE_c = 0.0;

  /* TransferFcn Block: '<S35>/Transfer Fcn2' */
  ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
    ->TransferFcn2_CSTATE = 0.0;

  /* TransferFcn Block: '<S35>/Transfer Fcn3' */
  ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
    ->TransferFcn3_CSTATE = 0.0;

  /* TransferFcn Block: '<S35>/Transfer Fcn5' */
  ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
    ->TransferFcn5_CSTATE = 0.0;

  /* TransferFcn Block: '<S35>/Transfer Fcn4' */
  ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
    ->TransferFcn4_CSTATE = 0.0;

  /* TransferFcn Block: '<S40>/Transfer Fcn2' */
  ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
    ->TransferFcn2_CSTATE_n = 0.0;

  /* TransferFcn Block: '<S40>/Transfer Fcn5' */
  ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
    ->TransferFcn5_CSTATE_l = 0.0;

  /* InitializeConditions for Integrator: '<S36>/rate limited beta' */
  ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
    ->ratelimitedbeta_CSTATE[0] = 0.0;
  ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
    ->ratelimitedbeta_CSTATE[1] = 0.0;

  /* TransferFcn Block: '<S41>/Transfer Fcn2' */
  ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
    ->TransferFcn2_CSTATE_b = 0.0;

  /* TransferFcn Block: '<S41>/Transfer Fcn5' */
  ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
    ->TransferFcn5_CSTATE_m = 0.0;

  /* InitializeConditions for Integrator: '<S24>/Integrator2' */
  ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
    ->Integrator2_CSTATE_m = 0.0;

  /* InitializeConditions for Integrator: '<S24>/Integrator4' */
  ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
    ->Integrator4_CSTATE_a = 0.0;

  /* InitializeConditions for Integrator: '<S21>/Integrator2' */
  ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
    ->Integrator2_CSTATE_nu = 0.0;

  /* InitializeConditions for Integrator: '<S23>/Integrator2' */
  ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
    ->Integrator2_CSTATE_k = 0.0;

  /* InitializeConditions for Integrator: '<S23>/Integrator4' */
  ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
    ->Integrator4_CSTATE_e = 0.0;

  /* InitializeConditions for Integrator: '<S20>/Integrator2' */
  ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
    ->Integrator2_CSTATE_p = 0.0;

  /* InitializeConditions for Integrator: '<S25>/Integrator2' */
  ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
    ->Integrator2_CSTATE_a = 0.0;

  /* InitializeConditions for Integrator: '<S25>/Integrator4' */
  ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
    ->Integrator4_CSTATE_o = 0.0;

  /* InitializeConditions for Integrator: '<S22>/Integrator2' */
  ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
    ->Integrator2_CSTATE_c = 0.0;

  /* InitializeConditions for Integrator: '<S12>/Integrator' */
  ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
    ->Integrator_CSTATE_b = 0.0;

  /* InitializeConditions for Integrator: '<S12>/Integrator1' */
  ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
    ->Integrator1_CSTATE_i = 0.0;

  /* InitializeConditions for Integrator: '<S12>/Integrator2' */
  ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
    ->Integrator2_CSTATE_pu = 0.0;

  /* InitializeConditions for Integrator: '<S11>/Integrator' */
  ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
    ->Integrator_CSTATE_l = 0.0;

  /* InitializeConditions for Integrator: '<S11>/Integrator1' */
  ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
    ->Integrator1_CSTATE_ii = 0.0;

  /* InitializeConditions for Integrator: '<S11>/Integrator2' */
  ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
    ->Integrator2_CSTATE_h = 0.0;

  /* TransferFcn Block: '<S45>/Transfer Fcn' */
  ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)->TransferFcn_CSTATE
    = 0.0;

  /* TransferFcn Block: '<S45>/Transfer Fcn1' */
  ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
    ->TransferFcn1_CSTATE = 0.0;

  /* TransferFcn Block: '<S45>/Transfer Fcn2' */
  ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
    ->TransferFcn2_CSTATE_a = 0.0;

  /* InitializeConditions for Integrator: '<S23>/Integrator3' */
  ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)->Integrator3_CSTATE
    = 0.0;

  /* InitializeConditions for Integrator: '<S24>/Integrator3' */
  ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
    ->Integrator3_CSTATE_m = 0.0;

  /* InitializeConditions for Integrator: '<S25>/Integrator3' */
  ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
    ->Integrator3_CSTATE_k = 0.0;

  /* InitializeConditions for Integrator: '<S30>/Integrator3' */
  ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
    ->Integrator3_CSTATE_a = 0.0;

  /* InitializeConditions for Integrator: '<S31>/Integrator3' */
  ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
    ->Integrator3_CSTATE_n = 0.0;

  /* InitializeConditions for Integrator: '<S32>/Integrator3' */
  ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
    ->Integrator3_CSTATE_e = 0.0;

  /* InitializeConditions for Integrator: '<S38>/Integrator2' */
  ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
    ->Integrator2_CSTATE_jl = 0.0;

  /* InitializeConditions for Integrator: '<S38>/Integrator4' */
  ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
    ->Integrator4_CSTATE_f = 0.0;

  /* InitializeConditions for Integrator: '<S38>/Integrator' */
  ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
    ->Integrator_CSTATE_bb = 0.0;

  /* InitializeConditions for Integrator: '<S38>/Integrator3' */
  ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
    ->Integrator3_CSTATE_nd = 0.0;

  /* InitializeConditions for Integrator: '<S39>/Integrator2' */
  ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
    ->Integrator2_CSTATE_mi = 0.0;

  /* InitializeConditions for Integrator: '<S39>/Integrator4' */
  ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
    ->Integrator4_CSTATE_cn = 0.0;

  /* InitializeConditions for Integrator: '<S39>/Integrator' */
  ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
    ->Integrator_CSTATE_a = 0.0;

  /* InitializeConditions for Integrator: '<S39>/Integrator3' */
  ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
    ->Integrator3_CSTATE_o = 0.0;
}

/* Start for root system: '<Root>' */
static void MdlStart(rtModel_cw16 *cw16_rtM)
{
  MdlInitialize(cw16_rtM);
}

/* Outputs for root system: '<Root>' */
static void MdlOutputs(rtModel_cw16 *cw16_rtM, int_T tid)
{
  /* local block i/o variables */
  real_T rtb_Sum5[3];
  real_T rtb_y[9];
  real_T rtb_xdd_i_ugp[3];
  real_T rtb_x_filt[3];
  real_T rtb_xd_filt[3];
  real_T rtb_TmpHiddenBufferAtSFunctionI[9];
  real_T rtb_TmpHiddenBufferAtSFunctio_l[6];
  real_T rtb_TmpHiddenBufferAtSFunctio_c[3];
  real_T rtb_TmpHiddenBufferAtSFunctio_b[6];
  real_T rtb_TmpHiddenBufferAtSFunctio_d[6];
  real_T rtb_Sum2[3];
  real_T rtb_ratelimitedbeta[2];
  real_T rtb_MultiportSwitch[3];
  real_T rtb_psidot;
  real_T rtb_Integrator4;
  real_T rtb_Integrator2;
  real_T rtb_Sum4[3];
  real_T rtb_MatrixGain[3];
  real_T rtb_TransferFcn2;
  real_T rtb_TransferFcn1;
  real_T rtb_TransferFcn;

  {
    real_T cg_in[6];
    int32_T i;
    real_T rtb_Sum2_d_idx;
    real_T rtb_controllergain_idx;
    real_T rtb_Gain2_idx;
    real_T rtb_Gain2_idx_0;
    real_T rtb_Gain2_idx_1;

    /* Integrator: '<S13>/Integrator' */
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Integrator =
      ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
      ->Integrator_CSTATE;

    /* Integrator: '<S13>/Integrator1' */
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Integrator1 =
      ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
      ->Integrator1_CSTATE;

    /* Integrator: '<S13>/Integrator2' */
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Integrator2 =
      ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
      ->Integrator2_CSTATE;

    /* SignalConversion: '<S42>/TmpHiddenBufferAt SFunction Inport4' incorporates:
     *  Constant: '<S43>/xref_ac'
     *  Constant: '<S43>/xref_filt'
     *  Constant: '<S43>/yref_ac'
     *  Constant: '<S43>/yref_filt'
     *  Constant: '<S43>/zref_ac'
     *  Constant: '<S43>/zref_filt'
     */
    rtb_TmpHiddenBufferAtSFunctio_d[0] = ((Parameters_cw16 *)
      cw16_rtM->ModelData.defaultParam)->xref_ac;
    rtb_TmpHiddenBufferAtSFunctio_d[1] = ((Parameters_cw16 *)
      cw16_rtM->ModelData.defaultParam)->yref_ac;
    rtb_TmpHiddenBufferAtSFunctio_d[2] = ((Parameters_cw16 *)
      cw16_rtM->ModelData.defaultParam)->zref_ac;
    rtb_TmpHiddenBufferAtSFunctio_d[3] = ((Parameters_cw16 *)
      cw16_rtM->ModelData.defaultParam)->xref_filt;
    rtb_TmpHiddenBufferAtSFunctio_d[4] = ((Parameters_cw16 *)
      cw16_rtM->ModelData.defaultParam)->yref_filt;
    rtb_TmpHiddenBufferAtSFunctio_d[5] = ((Parameters_cw16 *)
      cw16_rtM->ModelData.defaultParam)->zref_filt;

    /* Embedded MATLAB: '<S4>/calculate position and velocity in filter reference point, for state feedback inside filter' incorporates:
     *   Inport: '<Root>/Input'
     */
    {
      real_T eml_phi;
      real_T eml_theta;
      real_T eml_psi;
      real_T eml_cf;
      real_T eml_sf;
      real_T eml_ct;
      real_T eml_cp;
      int32_T eml_i0;
      real_T eml_w[3];
      real_T eml_dx[3];
      real_T eml_T[9];
      int32_T eml_i1;
      real_T eml_dv0[3];

      /*  This block supports the Embedded MATLAB subset. */
      /*  See the help menu for details.  */
      /*  This function transforms simulator position and velocities, which are  */
      /*  given in the upper gimbal point, to the filter reference position. */
      /*  The refpos input is expected to contain: */
      /*  [xref_ac; yref_ac; zref_ac; xref_filt; yref_filt; zref_filt] */
      /*  All these positions are given relative to the UGP (although in */
      /*  this function we're only interested in the difference) */
      /*  get some names attached */
      eml_phi = ((ExternalInputs_cw16 *) cw16_rtM->ModelData.inputs)->Input[15];
      eml_theta = ((ExternalInputs_cw16 *) cw16_rtM->ModelData.inputs)->Input[16];
      eml_psi = ((ExternalInputs_cw16 *) cw16_rtM->ModelData.inputs)->Input[17];

      /*  gonio stuff */
      eml_cf = cos(eml_phi);
      eml_sf = sin(eml_phi);
      eml_ct = cos(eml_theta);
      eml_theta = sin(eml_theta);
      eml_cp = cos(eml_psi);
      eml_phi = sin(eml_psi);
      for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
        eml_w[eml_i0] = ((ExternalInputs_cw16 *) cw16_rtM->ModelData.inputs)
          ->Input[3 + eml_i0+15];

        /*  position to translate over */
        /*  filt - ugp(=0)   */
        eml_dx[eml_i0] = rtb_TmpHiddenBufferAtSFunctio_d[3 + eml_i0];
      }

      /*  transformation from inertial to body */
      eml_T[0] = eml_cp * eml_ct;
      eml_T[3] = eml_phi * eml_ct;
      eml_T[6] = -eml_theta;
      eml_T[1] = eml_cp * eml_theta * eml_sf - eml_phi * eml_cf;
      eml_T[4] = eml_cp * eml_cf + eml_phi * eml_theta * eml_sf;
      eml_T[7] = eml_ct * eml_sf;
      eml_T[2] = eml_cp * eml_theta * eml_cf + eml_phi * eml_sf;
      eml_T[5] = eml_phi * eml_theta * eml_cf - eml_cp * eml_sf;
      eml_T[8] = eml_ct * eml_cf;

      /*  position from UGP to filter */
      for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
        eml_phi = 0.0;
        for (eml_i1 = 0; eml_i1 < 3; eml_i1++) {
          eml_phi += eml_T[eml_i1 + 3 * eml_i0] * eml_dx[eml_i1];
        }

        rtb_x_filt[eml_i0] = ((ExternalInputs_cw16 *) cw16_rtM->ModelData.inputs)
          ->Input[eml_i0+9] + eml_phi;
      }

      /*  velocity from UGP to filter */
      eml_dv0[0] = eml_w[1] * eml_dx[2] - eml_w[2] * eml_dx[1];
      eml_dv0[1] = eml_w[2] * eml_dx[0] - eml_w[0] * eml_dx[2];
      eml_dv0[2] = eml_w[0] * eml_dx[1] - eml_w[1] * eml_dx[0];
      for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
        eml_phi = 0.0;
        for (eml_i1 = 0; eml_i1 < 3; eml_i1++) {
          eml_phi += eml_T[eml_i1 + 3 * eml_i0] * eml_dv0[eml_i1];
        }

        rtb_xd_filt[eml_i0] = ((ExternalInputs_cw16 *)
          cw16_rtM->ModelData.inputs)->Input[eml_i0+12] + eml_phi;
      }
    }

    /* Sum: '<S10>/Sum3' */
    rtb_MatrixGain[0] = ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)
      ->Integrator - rtb_xd_filt[0];
    rtb_MatrixGain[1] = ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)
      ->Integrator1 - rtb_xd_filt[1];
    rtb_MatrixGain[2] = ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)
      ->Integrator2 - rtb_xd_filt[2];

    /* Gain: '<S10>/Gain2' */
    rtb_Gain2_idx = 0.1 * rtb_MatrixGain[0];
    rtb_Gain2_idx_0 = 0.1 * rtb_MatrixGain[1];
    rtb_Gain2_idx_1 = 0.1 * rtb_MatrixGain[2];

    /* Integrator: '<S14>/Integrator' */
    rtb_TransferFcn2 = ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
      ->Integrator_CSTATE_c;

    /* Integrator: '<S14>/Integrator1' */
    rtb_TransferFcn1 = ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
      ->Integrator1_CSTATE_m;

    /* Integrator: '<S14>/Integrator2' */
    rtb_TransferFcn = ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates
      )->Integrator2_CSTATE_f;

    /* Sum: '<S10>/Sum4' */
    rtb_MatrixGain[0] = rtb_TransferFcn2 - rtb_x_filt[0];
    rtb_MatrixGain[1] = rtb_TransferFcn1 - rtb_x_filt[1];
    rtb_MatrixGain[2] = rtb_TransferFcn - rtb_x_filt[2];

    /* Sum: '<S10>/Sum5' incorporates:
     *  Gain: '<S10>/Gain3'
     */
    rtb_MatrixGain[0] = 0.5 * rtb_MatrixGain[0] + rtb_Gain2_idx;
    rtb_MatrixGain[1] = 0.5 * rtb_MatrixGain[1] + rtb_Gain2_idx_0;
    rtb_MatrixGain[2] = 0.5 * rtb_MatrixGain[2] + rtb_Gain2_idx_1;

    /* Step: '<S50>/Step' */
    rtb_Gain2_idx_1 = rtmGetTaskTime(cw16_rtM, 0);
    if (rtb_Gain2_idx_1 < 0.0) {
      rtb_TransferFcn = 0.0;
    } else {
      rtb_TransferFcn = 0.2;
    }

    /* Clock: '<S50>/Clock' */
    rtb_TransferFcn1 = rtmGetT(cw16_rtM);

    /* Sum: '<S50>/Output' incorporates:
     *  Constant: '<S50>/Constant'
     *  Constant: '<S50>/Constant1'
     *  Product: '<S50>/Product'
     *  Sum: '<S50>/Sum'
     */
    rtb_TransferFcn *= rtb_TransferFcn1;

    /* Saturate: '<S8>/Saturation' */
    rtb_Gain2_idx_1 = rt_SATURATE(rtb_TransferFcn, 0.0, 1.0);

    /* SignalConversion: '<S49>/TmpHiddenBufferAt SFunction Inport1' incorporates:
     *  Product: '<S8>/Product'
     */
    rtb_TmpHiddenBufferAtSFunctionI[0] = rtb_Gain2_idx_1 * ((ExternalInputs_cw16
      *) cw16_rtM->ModelData.inputs)->Input[0];
    rtb_TmpHiddenBufferAtSFunctionI[1] = rtb_Gain2_idx_1 * ((ExternalInputs_cw16
      *) cw16_rtM->ModelData.inputs)->Input[1];
    for (i = 0; i < 7; i++) {
      rtb_TmpHiddenBufferAtSFunctionI[i + 2] = ((ExternalInputs_cw16 *)
        cw16_rtM->ModelData.inputs)->Input[i + 2];
    }

    /* SignalConversion: '<S49>/TmpHiddenBufferAt SFunction Inport2' incorporates:
     *  Constant: '<S51>/xref_ac'
     *  Constant: '<S51>/xref_filt'
     *  Constant: '<S51>/yref_ac'
     *  Constant: '<S51>/yref_filt'
     *  Constant: '<S51>/zref_ac'
     *  Constant: '<S51>/zref_filt'
     */
    rtb_TmpHiddenBufferAtSFunctio_l[0] = ((Parameters_cw16 *)
      cw16_rtM->ModelData.defaultParam)->xref_ac;
    rtb_TmpHiddenBufferAtSFunctio_l[1] = ((Parameters_cw16 *)
      cw16_rtM->ModelData.defaultParam)->yref_ac;
    rtb_TmpHiddenBufferAtSFunctio_l[2] = ((Parameters_cw16 *)
      cw16_rtM->ModelData.defaultParam)->zref_ac;
    rtb_TmpHiddenBufferAtSFunctio_l[3] = ((Parameters_cw16 *)
      cw16_rtM->ModelData.defaultParam)->xref_filt;
    rtb_TmpHiddenBufferAtSFunctio_l[4] = ((Parameters_cw16 *)
      cw16_rtM->ModelData.defaultParam)->yref_filt;
    rtb_TmpHiddenBufferAtSFunctio_l[5] = ((Parameters_cw16 *)
      cw16_rtM->ModelData.defaultParam)->zref_filt;

    /* Embedded MATLAB: '<S8>/Embedded MATLAB Function' */
    {
      real_T eml_p;
      real_T eml_q;
      real_T eml_r;
      real_T eml_pd;
      real_T eml_qd;
      real_T eml_rd;
      real_T eml_dx;
      real_T eml_dy;
      real_T eml_dz;
      int32_T eml_i0;

      /*  This block supports the Embedded MATLAB subset. */
      /*  See the help menu for details.  */
      /*  This function transforms the filter inputs, which are given in the */
      /*  aircraft reference position, to the filter reference position. */
      /*  The refpos input is expected to contain: */
      /*  [xref_ac; yref_ac; zref_ac; xref_filt; yref_filt; zref_filt] */
      /*  All these positions are given relative to the UGP (although in */
      /*  this function we're only interested in the difference) */
      /*  get some names attached */
      eml_p = rtb_TmpHiddenBufferAtSFunctionI[3];
      eml_q = rtb_TmpHiddenBufferAtSFunctionI[4];
      eml_r = rtb_TmpHiddenBufferAtSFunctionI[5];
      eml_pd = rtb_TmpHiddenBufferAtSFunctionI[6];
      eml_qd = rtb_TmpHiddenBufferAtSFunctionI[7];
      eml_rd = rtb_TmpHiddenBufferAtSFunctionI[8];

      /*  position to translate over */
      /*  filt-ac */
      eml_dx = rtb_TmpHiddenBufferAtSFunctio_l[3] -
        rtb_TmpHiddenBufferAtSFunctio_l[0];
      eml_dy = rtb_TmpHiddenBufferAtSFunctio_l[4] -
        rtb_TmpHiddenBufferAtSFunctio_l[1];
      eml_dz = rtb_TmpHiddenBufferAtSFunctio_l[5] -
        rtb_TmpHiddenBufferAtSFunctio_l[2];

      /*  specific forces */
      /*  f_mf = f_ac + wd x r + w x (w x r) */
      /*  output */
      for (eml_i0 = 0; eml_i0 < 9; eml_i0++) {
        rtb_y[eml_i0] = rtb_TmpHiddenBufferAtSFunctionI[eml_i0];
      }

      rtb_y[0] = ((((-eml_r) * eml_r - eml_q * eml_q) * eml_dx + (eml_p * eml_q
        - eml_rd) * eml_dy) + (eml_qd + eml_p * eml_r) * eml_dz) +
        rtb_TmpHiddenBufferAtSFunctionI[0];
      rtb_y[1] = (((eml_rd + eml_p * eml_q) * eml_dx + ((-eml_r) * eml_r - eml_p
        * eml_p) * eml_dy) + (eml_q * eml_r - eml_pd) * eml_dz) +
        rtb_TmpHiddenBufferAtSFunctionI[1];
      rtb_y[2] = (((eml_p * eml_r - eml_qd) * eml_dx + (eml_q * eml_r + eml_pd) *
                   eml_dy) + ((-eml_q) * eml_q - eml_p * eml_p) * eml_dz) +
        rtb_TmpHiddenBufferAtSFunctionI[2];
    }

    /* Sum: '<S18>/Sum1' incorporates:
     *  Constant: '<S18>/Constant'
     */
    rtb_MultiportSwitch[0] = rtb_y[0];
    rtb_MultiportSwitch[1] = rtb_y[1];
    rtb_MultiportSwitch[2] = 9.80665 + rtb_y[2];

    /* Gain Block: '<S18>/kf'
     * About '<S18>/kf :'
     *   Gain value: kf


     */
    {
      static const int_T dims[3] = { 3, 3, 1 };

      rt_MatMultRR_Dbl((real_T *)rtb_Sum2, (real_T *)&((Parameters_cw16 *)
        cw16_rtM->ModelData.defaultParam)->kf[0],
                       (real_T *)rtb_MultiportSwitch, &dims[0]);
    }

    /* Sum: '<S18>/Sum2' incorporates:
     *  Constant: '<S18>/Constant'
     */
    rtb_Sum2[2] -= 9.80665;

    /* Fcn: '<S34>/Fcn9' incorporates:
     *  Inport: '<Root>/Input'
     */
    cg_in[0] = rtb_Sum2[0];
    cg_in[1] = rtb_Sum2[1];
    cg_in[2] = rtb_Sum2[2];
    cg_in[3] = ((ExternalInputs_cw16 *) cw16_rtM->ModelData.inputs)->Input[15];
    cg_in[4] = ((ExternalInputs_cw16 *) cw16_rtM->ModelData.inputs)->Input[16];
    cg_in[5] = ((ExternalInputs_cw16 *) cw16_rtM->ModelData.inputs)->Input[17];
    rtb_TransferFcn = ((sin(cg_in[3]) * sin(cg_in[4]) * cos(cg_in[5]) - cos
                        (cg_in[3]) * sin(cg_in[5])) * cg_in[1] + cg_in[0] * cos
                       (cg_in[4]) * cos(cg_in[5])) + (cos(cg_in[3]) * sin(cg_in
      [4]) * cos(cg_in[5]) + sin(cg_in[3]) * sin(cg_in[5])) * cg_in[2];

    /* Fcn: '<S34>/Fcn1' incorporates:
     *  Inport: '<Root>/Input'
     */
    cg_in[0] = rtb_Sum2[0];
    cg_in[1] = rtb_Sum2[1];
    cg_in[2] = rtb_Sum2[2];
    cg_in[3] = ((ExternalInputs_cw16 *) cw16_rtM->ModelData.inputs)->Input[15];
    cg_in[4] = ((ExternalInputs_cw16 *) cw16_rtM->ModelData.inputs)->Input[16];
    cg_in[5] = ((ExternalInputs_cw16 *) cw16_rtM->ModelData.inputs)->Input[17];
    rtb_TransferFcn1 = ((sin(cg_in[3]) * sin(cg_in[4]) * sin(cg_in[5]) + cos
                         (cg_in[3]) * cos(cg_in[5])) * cg_in[1] + cg_in[0] * cos
                        (cg_in[4]) * sin(cg_in[5])) + (cos(cg_in[3]) * sin
      (cg_in[4]) * sin(cg_in[5]) - sin(cg_in[3]) * cos(cg_in[5])) * cg_in[2];

    /* Fcn: '<S34>/Fcn2' incorporates:
     *  Inport: '<Root>/Input'
     */
    cg_in[0] = rtb_Sum2[0];
    cg_in[1] = rtb_Sum2[1];
    cg_in[2] = rtb_Sum2[2];
    cg_in[3] = ((ExternalInputs_cw16 *) cw16_rtM->ModelData.inputs)->Input[15];
    cg_in[4] = ((ExternalInputs_cw16 *) cw16_rtM->ModelData.inputs)->Input[16];
    cg_in[5] = ((ExternalInputs_cw16 *) cw16_rtM->ModelData.inputs)->Input[17];
    rtb_TransferFcn2 = (cg_in[1] * sin(cg_in[3]) * cos(cg_in[4]) + (-cg_in[0]) *
                        sin(cg_in[4])) + cg_in[2] * cos(cg_in[3]) * cos(cg_in[4]);

    /* Sum: '<S16>/Sum' incorporates:
     *  Constant: '<S16>/Constant'
     */
    rtb_MultiportSwitch[0] = rtb_TransferFcn;
    rtb_MultiportSwitch[1] = rtb_TransferFcn1;
    rtb_MultiportSwitch[2] = 9.80665 + rtb_TransferFcn2;

    /* Integrator: '<S31>/Integrator2' */
    rtb_TransferFcn = ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates
      )->Integrator2_CSTATE_f2;

    /* Gain: '<S31>/Gain1' incorporates:
     *  Gain: '<S31>/Gain'
     */
    rtb_Gain2_idx_1 = ((Parameters_cw16 *) cw16_rtM->ModelData.defaultParam)
      ->HPomeganx * rtb_TransferFcn * ((Parameters_cw16 *)
      cw16_rtM->ModelData.defaultParam)->HPomeganx;

    /* Integrator: '<S31>/Integrator4' */
    rtb_TransferFcn = ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates
      )->Integrator4_CSTATE;

    /* Sum: '<S31>/Sum' incorporates:
     *  Gain: '<S16>/Gain4'
     *  Gain: '<S31>/Gain2'
     *  Gain: '<S31>/Gain3'
     *  Gain: '<S31>/Gain4'
     *  Sum: '<S31>/Sum1'
     */
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Sum = ((Parameters_cw16 *)
      cw16_rtM->ModelData.defaultParam)->gainfx * rtb_MultiportSwitch[0] -
      (((Parameters_cw16 *) cw16_rtM->ModelData.defaultParam)->HPzetax *
       rtb_TransferFcn * ((Parameters_cw16 *) cw16_rtM->ModelData.defaultParam
       )->HPomeganx * 2.0 + rtb_Gain2_idx_1);

    /* Integrator: '<S27>/Integrator2' */
    rtb_TransferFcn = ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates
      )->Integrator2_CSTATE_b;

    /* Sum: '<S27>/Sum' incorporates:
     *  Gain: '<S27>/Gain1'
     */
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Sum_e = ((BlockIO_cw16 *)
      cw16_rtM->ModelData.blockIO)->Sum - ((Parameters_cw16 *)
      cw16_rtM->ModelData.defaultParam)->HPomegabx * rtb_TransferFcn;

    /* Integrator: '<S32>/Integrator2' */
    rtb_TransferFcn = ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates
      )->Integrator2_CSTATE_e;

    /* Gain: '<S32>/Gain1' incorporates:
     *  Gain: '<S32>/Gain'
     */
    rtb_Gain2_idx_1 = ((Parameters_cw16 *) cw16_rtM->ModelData.defaultParam)
      ->HPomegany * rtb_TransferFcn * ((Parameters_cw16 *)
      cw16_rtM->ModelData.defaultParam)->HPomegany;

    /* Integrator: '<S32>/Integrator4' */
    rtb_TransferFcn = ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates
      )->Integrator4_CSTATE_j;

    /* Sum: '<S32>/Sum' incorporates:
     *  Gain: '<S16>/Gain3'
     *  Gain: '<S32>/Gain2'
     *  Gain: '<S32>/Gain3'
     *  Gain: '<S32>/Gain4'
     *  Sum: '<S32>/Sum1'
     */
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Sum_n = ((Parameters_cw16 *)
      cw16_rtM->ModelData.defaultParam)->gainfy * rtb_MultiportSwitch[1] -
      (((Parameters_cw16 *) cw16_rtM->ModelData.defaultParam)->HPzetay *
       rtb_TransferFcn * ((Parameters_cw16 *) cw16_rtM->ModelData.defaultParam
       )->HPomegany * 2.0 + rtb_Gain2_idx_1);

    /* Integrator: '<S28>/Integrator2' */
    rtb_TransferFcn = ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates
      )->Integrator2_CSTATE_g;

    /* Sum: '<S28>/Sum' incorporates:
     *  Gain: '<S28>/Gain1'
     */
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Sum_h = ((BlockIO_cw16 *)
      cw16_rtM->ModelData.blockIO)->Sum_n - ((Parameters_cw16 *)
      cw16_rtM->ModelData.defaultParam)->HPomegaby * rtb_TransferFcn;

    /* Gain: '<S16>/Gain5' */
    rtb_Gain2_idx = ((Parameters_cw16 *) cw16_rtM->ModelData.defaultParam)
      ->gainfz * rtb_MultiportSwitch[2];

    /* Step: '<S33>/Step' */
    rtb_Gain2_idx_1 = rtmGetTaskTime(cw16_rtM, 0);
    if (rtb_Gain2_idx_1 < 0.0) {
      rtb_TransferFcn = 0.0;
    } else {
      rtb_TransferFcn = 0.2;
    }

    /* Clock: '<S33>/Clock' */
    rtb_TransferFcn1 = rtmGetT(cw16_rtM);

    /* Sum: '<S33>/Output' incorporates:
     *  Constant: '<S33>/Constant'
     *  Constant: '<S33>/Constant1'
     *  Product: '<S33>/Product'
     *  Sum: '<S33>/Sum'
     */
    rtb_TransferFcn *= rtb_TransferFcn1;

    /* Saturate: '<S16>/Saturation1' */
    rtb_Gain2_idx_1 = rtb_TransferFcn;

    /* Integrator: '<S30>/Integrator2' */
    rtb_TransferFcn = ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates
      )->Integrator2_CSTATE_j;

    /* Gain: '<S30>/Gain1' incorporates:
     *  Gain: '<S30>/Gain'
     */
    rtb_Gain2_idx_0 = ((Parameters_cw16 *) cw16_rtM->ModelData.defaultParam)
      ->HPomeganz * rtb_TransferFcn * ((Parameters_cw16 *)
      cw16_rtM->ModelData.defaultParam)->HPomeganz;

    /* Integrator: '<S30>/Integrator4' */
    rtb_TransferFcn = ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates
      )->Integrator4_CSTATE_c;

    /* Sum: '<S30>/Sum' incorporates:
     *  Gain: '<S30>/Gain2'
     *  Gain: '<S30>/Gain3'
     *  Gain: '<S30>/Gain4'
     *  Product: '<S16>/Product2'
     *  Saturate: '<S16>/Saturation1'
     *  Sum: '<S30>/Sum1'
     */
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Sum_k = rtb_Gain2_idx *
      rt_SATURATE(rtb_Gain2_idx_1, 0.0, 1.0) - (((Parameters_cw16 *)
      cw16_rtM->ModelData.defaultParam)->HPzetaz * rtb_TransferFcn *
      ((Parameters_cw16 *) cw16_rtM->ModelData.defaultParam)->HPomeganz * 2.0 +
      rtb_Gain2_idx_0);

    /* Integrator: '<S29>/Integrator2' */
    rtb_TransferFcn = ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates
      )->Integrator2_CSTATE_n;

    /* Sum: '<S29>/Sum' incorporates:
     *  Gain: '<S29>/Gain1'
     */
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Sum_nm = ((BlockIO_cw16 *)
      cw16_rtM->ModelData.blockIO)->Sum_k - ((Parameters_cw16 *)
      cw16_rtM->ModelData.defaultParam)->HPomegabz * rtb_TransferFcn;

    /* Sum: '<S1>/Sum5' */
    rtb_Sum5[0] = rtb_MatrixGain[0] + ((BlockIO_cw16 *)
      cw16_rtM->ModelData.blockIO)->Sum_e;
    rtb_Sum5[1] = rtb_MatrixGain[1] + ((BlockIO_cw16 *)
      cw16_rtM->ModelData.blockIO)->Sum_h;
    rtb_Sum5[2] = rtb_MatrixGain[2] + ((BlockIO_cw16 *)
      cw16_rtM->ModelData.blockIO)->Sum_nm;

    /* Integrator: '<S38>/Integrator1' */
    rtb_TransferFcn = ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates
      )->Integrator1_CSTATE_b;

    /* Integrator: '<S39>/Integrator1' */
    rtb_TransferFcn1 = ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
      ->Integrator1_CSTATE_c;

    /* SignalConversion: '<S17>/TmpHiddenBufferAtto required Euler anglesInport1' */
    rtb_ratelimitedbeta[0] = rtb_TransferFcn;
    rtb_ratelimitedbeta[1] = rtb_TransferFcn1;

    /* Gain Block: '<S17>/to required Euler angles'
     * About '<S17>/to required Euler angles :'
     *   Gain value: [0 -1/g ;1/g 0]


     */
    {
      static const int_T dims[3] = { 2, 2, 1 };

      rt_MatMultRR_Dbl((real_T *)((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO
                       )->torequiredEulerangles, (real_T *)
                       &cw16_ConstP.torequiredEulerangles[0],
                       (real_T *)rtb_ratelimitedbeta, &dims[0]);
    }

    /* TransferFcn Block: '<S35>/Transfer Fcn2' */
    rtb_TransferFcn = 50.0*((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)
      ->torequiredEulerangles[0];
    rtb_TransferFcn += -2500.0*((ContinuousStates_cw16 *)
      cw16_rtM->ModelData.contStates)->TransferFcn2_CSTATE;

    /* Gain: '<S35>/Gain' */
    rtb_TransferFcn *= 1.0 / ((Parameters_cw16 *)
      cw16_rtM->ModelData.defaultParam)->Beta_rate;

    /* Lookup_n-D: '<S35>/Lookup Table' */
    rtb_TransferFcn = look1_binlc(rtb_TransferFcn, &cw16_ConstP.pooled12[0],
      &cw16_ConstP.pooled11[0], 200U);

    /* Gain: '<S35>/Gain1' */
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Gain1 = ((Parameters_cw16 *)
      cw16_rtM->ModelData.defaultParam)->Beta_rate * rtb_TransferFcn;

    /* TransferFcn Block: '<S35>/Transfer Fcn3' */
    rtb_TransferFcn = 50.0*((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Gain1;
    rtb_TransferFcn += -2500.0*((ContinuousStates_cw16 *)
      cw16_rtM->ModelData.contStates)->TransferFcn3_CSTATE;

    /* TransferFcn Block: '<S35>/Transfer Fcn5' */
    rtb_TransferFcn1 = 50.0*((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)
      ->torequiredEulerangles[1];
    rtb_TransferFcn1 += -2500.0*((ContinuousStates_cw16 *)
      cw16_rtM->ModelData.contStates)->TransferFcn5_CSTATE;

    /* Gain: '<S35>/Gain2' */
    rtb_TransferFcn1 *= 1.0 / ((Parameters_cw16 *)
      cw16_rtM->ModelData.defaultParam)->Beta_rate;

    /* Lookup_n-D: '<S35>/Lookup Table1' */
    rtb_TransferFcn1 = look1_binlc(rtb_TransferFcn1, &cw16_ConstP.pooled12[0],
      &cw16_ConstP.pooled11[0], 200U);

    /* Gain: '<S35>/Gain3' */
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Gain3 = ((Parameters_cw16 *)
      cw16_rtM->ModelData.defaultParam)->Beta_rate * rtb_TransferFcn1;

    /* TransferFcn Block: '<S35>/Transfer Fcn4' */
    rtb_TransferFcn1 = 50.0*((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)
      ->Gain3;
    rtb_TransferFcn1 += -2500.0*((ContinuousStates_cw16 *)
      cw16_rtM->ModelData.contStates)->TransferFcn4_CSTATE;

    /* TransferFcn Block: '<S40>/Transfer Fcn2' */
    rtb_TransferFcn2 = 12.5*((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)
      ->torequiredEulerangles[0];
    rtb_TransferFcn2 += -156.25*((ContinuousStates_cw16 *)
      cw16_rtM->ModelData.contStates)->TransferFcn2_CSTATE_n;

    /* TransferFcn Block: '<S40>/Transfer Fcn5' */
    rtb_psidot = 12.5*((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)
      ->torequiredEulerangles[1];
    rtb_psidot += -156.25*((ContinuousStates_cw16 *)
      cw16_rtM->ModelData.contStates)->TransferFcn5_CSTATE_l;

    /* Integrator: '<S36>/rate limited beta' */
    rtb_ratelimitedbeta[0] = ((ContinuousStates_cw16 *)
      cw16_rtM->ModelData.contStates)->ratelimitedbeta_CSTATE[0];
    rtb_ratelimitedbeta[1] = ((ContinuousStates_cw16 *)
      cw16_rtM->ModelData.contStates)->ratelimitedbeta_CSTATE[1];

    /* Gain: '<S36>/controller gain' */
    rtb_controllergain_idx = (rtb_ratelimitedbeta[1] - ((BlockIO_cw16 *)
      cw16_rtM->ModelData.blockIO)->torequiredEulerangles[1]) *
      ((Parameters_cw16 *) cw16_rtM->ModelData.defaultParam)->Ktiltrate;

    /* Sum: '<S36>/Sum' incorporates:
     *  Gain: '<S36>/controller gain'
     *  Sum: '<S36>/Sum1'
     */
    rtb_Gain2_idx = rtb_TransferFcn2 - (rtb_ratelimitedbeta[0] - ((BlockIO_cw16 *)
      cw16_rtM->ModelData.blockIO)->torequiredEulerangles[0]) *
      ((Parameters_cw16 *) cw16_rtM->ModelData.defaultParam)->Ktiltrate;
    rtb_Sum2_d_idx = rtb_psidot - rtb_controllergain_idx;

    /* Saturate: '<S36>/betad limiting' */
    rtb_Gain2_idx_1 = -((Parameters_cw16 *) cw16_rtM->ModelData.defaultParam)
      ->Beta_rate;
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->betadlimiting[0] =
      rt_SATURATE(rtb_Gain2_idx, rtb_Gain2_idx_1, ((Parameters_cw16 *)
      cw16_rtM->ModelData.defaultParam)->Beta_rate);
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->betadlimiting[1] =
      rt_SATURATE(rtb_Sum2_d_idx, rtb_Gain2_idx_1, ((Parameters_cw16 *)
      cw16_rtM->ModelData.defaultParam)->Beta_rate);

    /* TransferFcn Block: '<S41>/Transfer Fcn2' */
    rtb_psidot = 12.5*((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)
      ->betadlimiting[0];
    rtb_psidot += -156.25*((ContinuousStates_cw16 *)
      cw16_rtM->ModelData.contStates)->TransferFcn2_CSTATE_b;

    /* TransferFcn Block: '<S41>/Transfer Fcn5' */
    rtb_TransferFcn2 = 12.5*((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)
      ->betadlimiting[1];
    rtb_TransferFcn2 += -156.25*((ContinuousStates_cw16 *)
      cw16_rtM->ModelData.contStates)->TransferFcn5_CSTATE_m;

    /* Fcn: '<S44>/phidot' incorporates:
     *  Inport: '<Root>/Input'
     */
    for (i = 0; i < 6; i++) {
      cg_in[i] = ((ExternalInputs_cw16 *) cw16_rtM->ModelData.inputs)->Input[i +
        15];
    }

    rtb_Integrator4 = (cg_in[4] * sin(cg_in[0]) + cg_in[5] * cos(cg_in[0])) *
      tan(cg_in[1]) + cg_in[3];

    /* Fcn: '<S44>/thetadot' incorporates:
     *  Inport: '<Root>/Input'
     */
    for (i = 0; i < 6; i++) {
      cg_in[i] = ((ExternalInputs_cw16 *) cw16_rtM->ModelData.inputs)->Input[i +
        15];
    }

    rtb_Integrator2 = cg_in[4] * cos(cg_in[0]) - cg_in[5] * sin(cg_in[0]);

    /* Sum: '<S37>/Sum2' incorporates:
     *  Inport: '<Root>/Input'
     */
    rtb_Sum2_d_idx = (((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)
                      ->torequiredEulerangles[1] - ((ExternalInputs_cw16 *)
      cw16_rtM->ModelData.inputs)->Input[16]) * ((Parameters_cw16 *)
      cw16_rtM->ModelData.defaultParam)->Ktilteuler + (0.0 - rtb_Integrator2) *
      ((Parameters_cw16 *) cw16_rtM->ModelData.defaultParam)->Ktilteulerrate;

    /* MultiPortSwitch: '<S17>/Multiport Switch' incorporates:
     *  Constant: '<S17>/tilt  coordination mode switch'
     *  Constant: '<S35>/Sim euler angles1'
     *  Constant: '<S36>/Sim euler angles1'
     *  Constant: '<S37>/Sim euler angles1'
     *  Constant: '<S37>/reference tilt rate'
     *  Gain: '<S37>/euler rate tilt gain'
     *  Gain: '<S37>/euler tilt gain'
     *  Inport: '<Root>/Input'
     *  Sum: '<S37>/Sum1'
     *  Sum: '<S37>/Sum2'
     *  Sum: '<S37>/Sum6'
     */
    switch ((int32_T)((Parameters_cw16 *) cw16_rtM->ModelData.defaultParam)
            ->tiltcoordinationmethod) {
     case 1:
      rtb_MultiportSwitch[0] = rtb_TransferFcn;
      rtb_MultiportSwitch[1] = rtb_TransferFcn1;
      rtb_MultiportSwitch[2] = 0.0;
      break;

     case 2:
      rtb_MultiportSwitch[0] = rtb_psidot;
      rtb_MultiportSwitch[1] = rtb_TransferFcn2;
      rtb_MultiportSwitch[2] = 0.0;
      break;

     default:
      rtb_MultiportSwitch[0] = (((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)
        ->torequiredEulerangles[0] - ((ExternalInputs_cw16 *)
        cw16_rtM->ModelData.inputs)->Input[15]) * ((Parameters_cw16 *)
        cw16_rtM->ModelData.defaultParam)->Ktilteuler + (0.0 - rtb_Integrator4) *
        ((Parameters_cw16 *) cw16_rtM->ModelData.defaultParam)->Ktilteulerrate;
      rtb_MultiportSwitch[1] = rtb_Sum2_d_idx;
      rtb_MultiportSwitch[2] = 0.0;
      break;
    }

    /* Gain Block: '<S19>/Matrix Gain'
     * About '<S19>/Matrix Gain :'
     *   Gain value: kw


     */
    {
      static const int_T dims[3] = { 3, 3, 1 };

      rt_MatMultRR_Dbl((real_T *)rtb_MatrixGain, (real_T *)&((Parameters_cw16 *)
        cw16_rtM->ModelData.defaultParam)->kw[0],
                       (real_T *)&rtb_y[3], &dims[0]);
    }

    /* Gain Block: '<S19>/Matrix Gain1'
     * About '<S19>/Matrix Gain1 :'
     *   Gain value: kw


     */
    {
      static const int_T dims[3] = { 3, 3, 1 };

      rt_MatMultRR_Dbl((real_T *)rtb_Sum4, (real_T *)&((Parameters_cw16 *)
        cw16_rtM->ModelData.defaultParam)->kw[0],
                       (real_T *)&rtb_y[6], &dims[0]);
    }

    /* Fcn: '<S44>/psidot' incorporates:
     *  Inport: '<Root>/Input'
     */
    for (i = 0; i < 6; i++) {
      cg_in[i] = ((ExternalInputs_cw16 *) cw16_rtM->ModelData.inputs)->Input[i +
        15];
    }

    rtb_psidot = (cg_in[4] * sin(cg_in[0]) + cg_in[5] * cos(cg_in[0])) / cos
      (cg_in[1]);

    /* Fcn: '<S26>/phidd' incorporates:
     *  Inport: '<Root>/Input'
     */
    rtb_TransferFcn = (((((1.0 + pow(tan(((ExternalInputs_cw16 *)
      cw16_rtM->ModelData.inputs)->Input[16]), 2.0)) * sin(((ExternalInputs_cw16
      *) cw16_rtM->ModelData.inputs)->Input[15]) * rtb_Integrator2 + cos
                          (((ExternalInputs_cw16 *) cw16_rtM->ModelData.inputs
      )->Input[15]) * rtb_Integrator4 * tan(((ExternalInputs_cw16 *)
      cw16_rtM->ModelData.inputs)->Input[16])) * rtb_MatrixGain[1] + ((1.0 + pow
                           (tan(((ExternalInputs_cw16 *)
      cw16_rtM->ModelData.inputs)->Input[16]), 2.0)) * cos(((ExternalInputs_cw16
      *) cw16_rtM->ModelData.inputs)->Input[15]) * rtb_Integrator2 - sin
      (((ExternalInputs_cw16 *) cw16_rtM->ModelData.inputs)->Input[15]) *
      rtb_Integrator4 * tan(((ExternalInputs_cw16 *) cw16_rtM->ModelData.inputs
      )->Input[16])) * rtb_MatrixGain[2]) + rtb_Sum4[0]) + sin
                       (((ExternalInputs_cw16 *) cw16_rtM->ModelData.inputs)
                        ->Input[15]) * tan(((ExternalInputs_cw16 *)
      cw16_rtM->ModelData.inputs)->Input[16]) * rtb_Sum4[1]) + cos
      (((ExternalInputs_cw16 *) cw16_rtM->ModelData.inputs)->Input[15]) * tan
      (((ExternalInputs_cw16 *) cw16_rtM->ModelData.inputs)->Input[16]) *
      rtb_Sum4[2];

    /* Gain: '<S15>/Gain9' */
    rtb_Gain2_idx_1 = ((Parameters_cw16 *) cw16_rtM->ModelData.defaultParam)
      ->gainp * rtb_TransferFcn;

    /* Integrator: '<S24>/Integrator2' */
    rtb_TransferFcn = ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates
      )->Integrator2_CSTATE_m;

    /* Gain: '<S24>/Gain1' incorporates:
     *  Gain: '<S24>/Gain'
     */
    rtb_Gain2_idx_0 = ((Parameters_cw16 *) cw16_rtM->ModelData.defaultParam)
      ->HPomeganphi * rtb_TransferFcn * ((Parameters_cw16 *)
      cw16_rtM->ModelData.defaultParam)->HPomeganphi;

    /* Integrator: '<S24>/Integrator4' */
    rtb_TransferFcn = ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates
      )->Integrator4_CSTATE_a;

    /* Sum: '<S24>/Sum' incorporates:
     *  Gain: '<S24>/Gain2'
     *  Gain: '<S24>/Gain3'
     *  Gain: '<S24>/Gain4'
     *  Sum: '<S24>/Sum1'
     */
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Sum_j = rtb_Gain2_idx_1 -
      (((Parameters_cw16 *) cw16_rtM->ModelData.defaultParam)->HPzetaphi *
       rtb_TransferFcn * ((Parameters_cw16 *) cw16_rtM->ModelData.defaultParam
       )->HPomeganphi * 2.0 + rtb_Gain2_idx_0);

    /* Integrator: '<S21>/Integrator2' */
    rtb_TransferFcn = ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates
      )->Integrator2_CSTATE_nu;

    /* Sum: '<S21>/Sum' incorporates:
     *  Gain: '<S21>/Gain1'
     */
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Sum_b = ((BlockIO_cw16 *)
      cw16_rtM->ModelData.blockIO)->Sum_j - ((Parameters_cw16 *)
      cw16_rtM->ModelData.defaultParam)->HPomegabphi * rtb_TransferFcn;

    /* Fcn: '<S26>/thetadd' incorporates:
     *  Inport: '<Root>/Input'
     */
    rtb_TransferFcn = (((-sin(((ExternalInputs_cw16 *)
      cw16_rtM->ModelData.inputs)->Input[15])) * rtb_Integrator4 *
                        rtb_MatrixGain[1] + cos(((ExternalInputs_cw16 *)
      cw16_rtM->ModelData.inputs)->Input[15]) * rtb_Integrator4 *
                        rtb_MatrixGain[2]) + cos(((ExternalInputs_cw16 *)
      cw16_rtM->ModelData.inputs)->Input[15]) * rtb_Sum4[1]) - sin
      (((ExternalInputs_cw16 *) cw16_rtM->ModelData.inputs)->Input[15]) *
      rtb_Sum4[2];

    /* Gain: '<S15>/Gain8' */
    rtb_Gain2_idx_1 = ((Parameters_cw16 *) cw16_rtM->ModelData.defaultParam)
      ->gainq * rtb_TransferFcn;

    /* Integrator: '<S23>/Integrator2' */
    rtb_TransferFcn = ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates
      )->Integrator2_CSTATE_k;

    /* Gain: '<S23>/Gain1' incorporates:
     *  Gain: '<S23>/Gain'
     */
    rtb_Gain2_idx_0 = ((Parameters_cw16 *) cw16_rtM->ModelData.defaultParam)
      ->HPomegantheta * rtb_TransferFcn * ((Parameters_cw16 *)
      cw16_rtM->ModelData.defaultParam)->HPomegantheta;

    /* Integrator: '<S23>/Integrator4' */
    rtb_TransferFcn = ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates
      )->Integrator4_CSTATE_e;

    /* Sum: '<S23>/Sum' incorporates:
     *  Gain: '<S23>/Gain2'
     *  Gain: '<S23>/Gain3'
     *  Gain: '<S23>/Gain4'
     *  Sum: '<S23>/Sum1'
     */
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Sum_bl = rtb_Gain2_idx_1 -
      (((Parameters_cw16 *) cw16_rtM->ModelData.defaultParam)->HPzetatheta *
       rtb_TransferFcn * ((Parameters_cw16 *) cw16_rtM->ModelData.defaultParam
       )->HPomegantheta * 2.0 + rtb_Gain2_idx_0);

    /* Integrator: '<S20>/Integrator2' */
    rtb_TransferFcn = ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates
      )->Integrator2_CSTATE_p;

    /* Sum: '<S20>/Sum' incorporates:
     *  Gain: '<S20>/Gain1'
     */
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Sum_g = ((BlockIO_cw16 *)
      cw16_rtM->ModelData.blockIO)->Sum_bl - ((Parameters_cw16 *)
      cw16_rtM->ModelData.defaultParam)->HPomegabtheta * rtb_TransferFcn;

    /* Fcn: '<S26>/psidd' incorporates:
     *  Inport: '<Root>/Input'
     */
    rtb_TransferFcn = (((cos(((ExternalInputs_cw16 *) cw16_rtM->ModelData.inputs)
      ->Input[16]) * cos(((ExternalInputs_cw16 *) cw16_rtM->ModelData.inputs)
                         ->Input[15]) * rtb_Integrator4 + sin
                         (((ExternalInputs_cw16 *) cw16_rtM->ModelData.inputs)
                          ->Input[15]) * sin(((ExternalInputs_cw16 *)
      cw16_rtM->ModelData.inputs)->Input[16]) * rtb_Integrator2) / pow(cos
      (((ExternalInputs_cw16 *) cw16_rtM->ModelData.inputs)->Input[16]), 2.0) *
                        rtb_MatrixGain[1] + (cos(((ExternalInputs_cw16 *)
      cw16_rtM->ModelData.inputs)->Input[15]) * sin(((ExternalInputs_cw16 *)
      cw16_rtM->ModelData.inputs)->Input[16]) * rtb_Integrator2 - cos
      (((ExternalInputs_cw16 *) cw16_rtM->ModelData.inputs)->Input[16]) * sin
      (((ExternalInputs_cw16 *) cw16_rtM->ModelData.inputs)->Input[15]) *
      rtb_Integrator4) / pow(cos(((ExternalInputs_cw16 *)
      cw16_rtM->ModelData.inputs)->Input[16]), 2.0) * rtb_MatrixGain[2]) + sin
                       (((ExternalInputs_cw16 *) cw16_rtM->ModelData.inputs)
                        ->Input[15]) / cos(((ExternalInputs_cw16 *)
      cw16_rtM->ModelData.inputs)->Input[16]) * rtb_Sum4[1]) + cos
      (((ExternalInputs_cw16 *) cw16_rtM->ModelData.inputs)->Input[15]) / cos
      (((ExternalInputs_cw16 *) cw16_rtM->ModelData.inputs)->Input[16]) *
      rtb_Sum4[2];

    /* Gain: '<S15>/Gain7' */
    rtb_Gain2_idx_1 = ((Parameters_cw16 *) cw16_rtM->ModelData.defaultParam)
      ->gainr * rtb_TransferFcn;

    /* Integrator: '<S25>/Integrator2' */
    rtb_TransferFcn = ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates
      )->Integrator2_CSTATE_a;

    /* Gain: '<S25>/Gain1' incorporates:
     *  Gain: '<S25>/Gain'
     */
    rtb_Gain2_idx_0 = ((Parameters_cw16 *) cw16_rtM->ModelData.defaultParam)
      ->HPomeganpsi * rtb_TransferFcn * ((Parameters_cw16 *)
      cw16_rtM->ModelData.defaultParam)->HPomeganpsi;

    /* Integrator: '<S25>/Integrator4' */
    rtb_TransferFcn = ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates
      )->Integrator4_CSTATE_o;

    /* Sum: '<S25>/Sum' incorporates:
     *  Gain: '<S25>/Gain2'
     *  Gain: '<S25>/Gain3'
     *  Gain: '<S25>/Gain4'
     *  Sum: '<S25>/Sum1'
     */
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Sum_hv = rtb_Gain2_idx_1 -
      (((Parameters_cw16 *) cw16_rtM->ModelData.defaultParam)->HPzetapsi *
       rtb_TransferFcn * ((Parameters_cw16 *) cw16_rtM->ModelData.defaultParam
       )->HPomeganpsi * 2.0 + rtb_Gain2_idx_0);

    /* Integrator: '<S22>/Integrator2' */
    rtb_TransferFcn = ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates
      )->Integrator2_CSTATE_c;

    /* Sum: '<S22>/Sum' incorporates:
     *  Gain: '<S22>/Gain1'
     */
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Sum_bly = ((BlockIO_cw16 *)
      cw16_rtM->ModelData.blockIO)->Sum_hv - ((Parameters_cw16 *)
      cw16_rtM->ModelData.defaultParam)->HPomegabpsi * rtb_TransferFcn;

    /* Sum: '<S3>/Sum1' */
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Sum1[0] =
      rtb_MultiportSwitch[0] + ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)
      ->Sum_b;
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Sum1[1] =
      rtb_MultiportSwitch[1] + ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)
      ->Sum_g;
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Sum1[2] =
      rtb_MultiportSwitch[2] + ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)
      ->Sum_bly;

    /* Integrator: '<S12>/Integrator' */
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Integrator_a =
      ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
      ->Integrator_CSTATE_b;

    /* Integrator: '<S12>/Integrator1' */
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Integrator1_f =
      ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
      ->Integrator1_CSTATE_i;

    /* Integrator: '<S12>/Integrator2' */
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Integrator2_c =
      ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
      ->Integrator2_CSTATE_pu;

    /* Sum: '<S9>/Sum3' */
    rtb_Sum4[0] = ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Integrator_a -
      rtb_Integrator4;
    rtb_Sum4[1] = ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Integrator1_f
      - rtb_Integrator2;
    rtb_Sum4[2] = ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Integrator2_c
      - rtb_psidot;

    /* Gain: '<S9>/euler rate feedback' */
    rtb_Gain2_idx = 0.5 * rtb_Sum4[0];
    rtb_Gain2_idx_0 = 0.5 * rtb_Sum4[1];
    rtb_Gain2_idx_1 = 0.5 * rtb_Sum4[2];

    /* Integrator: '<S11>/Integrator' */
    rtb_TransferFcn = ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates
      )->Integrator_CSTATE_l;

    /* Integrator: '<S11>/Integrator1' */
    rtb_TransferFcn1 = ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
      ->Integrator1_CSTATE_ii;

    /* Integrator: '<S11>/Integrator2' */
    rtb_TransferFcn2 = ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
      ->Integrator2_CSTATE_h;

    /* Sum: '<S9>/Sum4' incorporates:
     *  Inport: '<Root>/Input'
     */
    rtb_Sum4[0] = rtb_TransferFcn - ((ExternalInputs_cw16 *)
      cw16_rtM->ModelData.inputs)->Input[15];
    rtb_Sum4[1] = rtb_TransferFcn1 - ((ExternalInputs_cw16 *)
      cw16_rtM->ModelData.inputs)->Input[16];
    rtb_Sum4[2] = rtb_TransferFcn2 - ((ExternalInputs_cw16 *)
      cw16_rtM->ModelData.inputs)->Input[17];

    /* Sum: '<S1>/Sum4' incorporates:
     *  Gain: '<S9>/euler feedback'
     *  Sum: '<S9>/Sum5'
     */
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Sum4[0] = (0.2 * rtb_Sum4[0]
      + rtb_Gain2_idx) + ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Sum1[0];
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Sum4[1] = (0.2 * rtb_Sum4[1]
      + rtb_Gain2_idx_0) + ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Sum1
      [1];
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Sum4[2] = (0.2 * rtb_Sum4[2]
      + rtb_Gain2_idx_1) + ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Sum1
      [2];

    /* TransferFcn Block: '<S45>/Transfer Fcn' */
    rtb_TransferFcn = 1.0*((ContinuousStates_cw16 *)
      cw16_rtM->ModelData.contStates)->TransferFcn_CSTATE;

    /* TransferFcn Block: '<S45>/Transfer Fcn1' */
    rtb_TransferFcn1 = 1.0*((ContinuousStates_cw16 *)
      cw16_rtM->ModelData.contStates)->TransferFcn1_CSTATE;

    /* TransferFcn Block: '<S45>/Transfer Fcn2' */
    rtb_TransferFcn2 = 1.0*((ContinuousStates_cw16 *)
      cw16_rtM->ModelData.contStates)->TransferFcn2_CSTATE_a;

    /* Fcn: '<S5>/pd' incorporates:
     *  Inport: '<Root>/Input'
     */
    rtb_Gain2_idx_0 = ((-cos(((ExternalInputs_cw16 *) cw16_rtM->ModelData.inputs)
      ->Input[16])) * rtb_Integrator2 * rtb_TransferFcn2 + ((BlockIO_cw16 *)
      cw16_rtM->ModelData.blockIO)->Sum4[0]) - sin(((ExternalInputs_cw16 *)
      cw16_rtM->ModelData.inputs)->Input[16]) * ((BlockIO_cw16 *)
      cw16_rtM->ModelData.blockIO)->Sum4[2];

    /* Fcn: '<S5>/qd' incorporates:
     *  Inport: '<Root>/Input'
     */
    rtb_Gain2_idx = (((cos(((ExternalInputs_cw16 *) cw16_rtM->ModelData.inputs
      )->Input[16]) * cos(((ExternalInputs_cw16 *) cw16_rtM->ModelData.inputs)
                          ->Input[15]) * rtb_Integrator4 - sin
                       (((ExternalInputs_cw16 *) cw16_rtM->ModelData.inputs)
                        ->Input[16]) * rtb_Integrator2 * sin
                       (((ExternalInputs_cw16 *) cw16_rtM->ModelData.inputs)
                        ->Input[15])) * rtb_TransferFcn2 + (-sin
      (((ExternalInputs_cw16 *) cw16_rtM->ModelData.inputs)->Input[15])) *
                      rtb_Integrator4 * rtb_TransferFcn1) + cos
                     (((ExternalInputs_cw16 *) cw16_rtM->ModelData.inputs)
                      ->Input[15]) * ((BlockIO_cw16 *)
      cw16_rtM->ModelData.blockIO)->Sum4[1]) + cos(((ExternalInputs_cw16 *)
      cw16_rtM->ModelData.inputs)->Input[16]) * sin(((ExternalInputs_cw16 *)
      cw16_rtM->ModelData.inputs)->Input[15]) * ((BlockIO_cw16 *)
      cw16_rtM->ModelData.blockIO)->Sum4[2];

    /* Fcn: '<S5>/rd' incorporates:
     *  Inport: '<Root>/Input'
     */
    rtb_Gain2_idx_1 = (((-cos(((ExternalInputs_cw16 *)
      cw16_rtM->ModelData.inputs)->Input[15])) * rtb_Integrator4 *
                        rtb_TransferFcn1 - (sin(((ExternalInputs_cw16 *)
      cw16_rtM->ModelData.inputs)->Input[16]) * rtb_Integrator2 * cos
      (((ExternalInputs_cw16 *) cw16_rtM->ModelData.inputs)->Input[15]) + cos
      (((ExternalInputs_cw16 *) cw16_rtM->ModelData.inputs)->Input[16]) * sin
      (((ExternalInputs_cw16 *) cw16_rtM->ModelData.inputs)->Input[15]) *
      rtb_Integrator4) * rtb_TransferFcn2) - sin(((ExternalInputs_cw16 *)
      cw16_rtM->ModelData.inputs)->Input[15]) * ((BlockIO_cw16 *)
      cw16_rtM->ModelData.blockIO)->Sum4[1]) + cos(((ExternalInputs_cw16 *)
      cw16_rtM->ModelData.inputs)->Input[16]) * cos(((ExternalInputs_cw16 *)
      cw16_rtM->ModelData.inputs)->Input[15]) * ((BlockIO_cw16 *)
      cw16_rtM->ModelData.blockIO)->Sum4[2];

    /* SignalConversion: '<S47>/TmpHiddenBufferAt SFunction Inport2' */
    rtb_TmpHiddenBufferAtSFunctio_c[0] = rtb_Gain2_idx_0;
    rtb_TmpHiddenBufferAtSFunctio_c[1] = rtb_Gain2_idx;
    rtb_TmpHiddenBufferAtSFunctio_c[2] = rtb_Gain2_idx_1;

    /* SignalConversion: '<S47>/TmpHiddenBufferAt SFunction Inport4' incorporates:
     *  Constant: '<S48>/xref_ac'
     *  Constant: '<S48>/xref_filt'
     *  Constant: '<S48>/yref_ac'
     *  Constant: '<S48>/yref_filt'
     *  Constant: '<S48>/zref_ac'
     *  Constant: '<S48>/zref_filt'
     */
    rtb_TmpHiddenBufferAtSFunctio_b[0] = ((Parameters_cw16 *)
      cw16_rtM->ModelData.defaultParam)->xref_ac;
    rtb_TmpHiddenBufferAtSFunctio_b[1] = ((Parameters_cw16 *)
      cw16_rtM->ModelData.defaultParam)->yref_ac;
    rtb_TmpHiddenBufferAtSFunctio_b[2] = ((Parameters_cw16 *)
      cw16_rtM->ModelData.defaultParam)->zref_ac;
    rtb_TmpHiddenBufferAtSFunctio_b[3] = ((Parameters_cw16 *)
      cw16_rtM->ModelData.defaultParam)->xref_filt;
    rtb_TmpHiddenBufferAtSFunctio_b[4] = ((Parameters_cw16 *)
      cw16_rtM->ModelData.defaultParam)->yref_filt;
    rtb_TmpHiddenBufferAtSFunctio_b[5] = ((Parameters_cw16 *)
      cw16_rtM->ModelData.defaultParam)->zref_filt;

    /* Embedded MATLAB: '<S7>/move inertial acceleration setpoints in MF reference point to UGP reference point' incorporates:
     *   Inport: '<Root>/Input'
     */
    {
      real_T eml_phi;
      real_T eml_theta;
      real_T eml_psi;
      real_T eml_cf;
      real_T eml_sf;
      real_T eml_ct;
      real_T eml_cp;
      real_T eml_T[9];
      int32_T eml_i0;
      real_T eml_w[3];
      real_T eml_dx[3];
      real_T eml_dv0[3];
      int32_T eml_i1;
      real_T eml_b[3];
      real_T eml_dv1[3];
      real_T eml_dv2[3];

      /*  This block supports the Embedded MATLAB subset. */
      /*  See the help menu for details.  */
      /*  This function transforms the filter inputs, which are given in the */
      /*  aircraft reference position, to the filter reference position. */
      /*  The refpos input is expected to contain: */
      /*  [xref_ac; yref_ac; zref_ac; xref_filt; yref_filt; zref_filt] */
      /*  All these positions are given relative to the UGP (although in */
      /*  this function we're only interested in the difference) */
      /*  get some names attached */
      eml_phi = ((ExternalInputs_cw16 *) cw16_rtM->ModelData.inputs)->Input[15];
      eml_theta = ((ExternalInputs_cw16 *) cw16_rtM->ModelData.inputs)->Input[16];
      eml_psi = ((ExternalInputs_cw16 *) cw16_rtM->ModelData.inputs)->Input[17];

      /*  gonio stuff */
      eml_cf = cos(eml_phi);
      eml_sf = sin(eml_phi);
      eml_ct = cos(eml_theta);
      eml_theta = sin(eml_theta);
      eml_cp = cos(eml_psi);
      eml_phi = sin(eml_psi);

      /*  transform from inertial to body */
      /*  [OS] 20130611 fixed typo (sf->st) */
      eml_T[0] = eml_cp * eml_ct;
      eml_T[3] = eml_phi * eml_ct;
      eml_T[6] = -eml_theta;
      eml_T[1] = eml_cp * eml_theta * eml_sf - eml_phi * eml_cf;
      eml_T[4] = eml_cp * eml_cf + eml_phi * eml_theta * eml_sf;
      eml_T[7] = eml_ct * eml_sf;
      eml_T[2] = eml_cp * eml_theta * eml_cf + eml_phi * eml_sf;
      eml_T[5] = eml_phi * eml_theta * eml_cf - eml_cp * eml_sf;
      eml_T[8] = eml_ct * eml_cf;

      /*  translate to UGP */
      for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
        eml_w[eml_i0] = ((ExternalInputs_cw16 *) cw16_rtM->ModelData.inputs)
          ->Input[3 + eml_i0+15];

        /*  position to translate over */
        /*  ugp(=0) - filt */
        eml_dx[eml_i0] = -rtb_TmpHiddenBufferAtSFunctio_b[3 + eml_i0];

        /*  transform from body to inertial */
        eml_dv0[eml_i0] = 0.0;
        for (eml_i1 = 0; eml_i1 < 3; eml_i1++) {
          eml_dv0[eml_i0] += eml_T[eml_i0 + 3 * eml_i1] * rtb_Sum5[eml_i1];
        }
      }

      eml_b[0] = eml_w[1] * eml_dx[2] - eml_w[2] * eml_dx[1];
      eml_b[1] = eml_w[2] * eml_dx[0] - eml_w[0] * eml_dx[2];
      eml_b[2] = eml_w[0] * eml_dx[1] - eml_w[1] * eml_dx[0];
      eml_dv1[0] = rtb_TmpHiddenBufferAtSFunctio_c[1] * eml_dx[2] -
        rtb_TmpHiddenBufferAtSFunctio_c[2] * eml_dx[1];
      eml_dv1[1] = rtb_TmpHiddenBufferAtSFunctio_c[2] * eml_dx[0] -
        rtb_TmpHiddenBufferAtSFunctio_c[0] * eml_dx[2];
      eml_dv1[2] = rtb_TmpHiddenBufferAtSFunctio_c[0] * eml_dx[1] -
        rtb_TmpHiddenBufferAtSFunctio_c[1] * eml_dx[0];
      eml_dv2[0] = eml_w[1] * eml_b[2] - eml_w[2] * eml_b[1];
      eml_dv2[1] = eml_w[2] * eml_b[0] - eml_w[0] * eml_b[2];
      eml_dv2[2] = eml_w[0] * eml_b[1] - eml_w[1] * eml_b[0];
      for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
        eml_w[eml_i0] = (eml_dv0[eml_i0] + eml_dv1[eml_i0]) + eml_dv2[eml_i0];
      }

      for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
        rtb_xdd_i_ugp[eml_i0] = 0.0;
        for (eml_i1 = 0; eml_i1 < 3; eml_i1++) {
          rtb_xdd_i_ugp[eml_i0] = rtb_xdd_i_ugp[eml_i0] + eml_T[eml_i1 + 3 *
            eml_i0] * eml_w[eml_i1];
        }
      }
    }

    /* Outport: '<Root>/Output' incorporates:
     *  Inport: '<Root>/Input'
     */
    ((ExternalOutputs_cw16 *) cw16_rtM->ModelData.outputs)->Output_g[0] =
      rtb_xdd_i_ugp[0];
    ((ExternalOutputs_cw16 *) cw16_rtM->ModelData.outputs)->Output_g[1] =
      rtb_xdd_i_ugp[1];
    ((ExternalOutputs_cw16 *) cw16_rtM->ModelData.outputs)->Output_g[2] =
      rtb_xdd_i_ugp[2];
    ((ExternalOutputs_cw16 *) cw16_rtM->ModelData.outputs)->Output_g[3] =
      rtb_Gain2_idx_0;
    ((ExternalOutputs_cw16 *) cw16_rtM->ModelData.outputs)->Output_g[4] =
      rtb_Gain2_idx;
    ((ExternalOutputs_cw16 *) cw16_rtM->ModelData.outputs)->Output_g[5] =
      rtb_Gain2_idx_1;
    ((ExternalOutputs_cw16 *) cw16_rtM->ModelData.outputs)->Output_g[6] =
      ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->torequiredEulerangles[1];
    ((ExternalOutputs_cw16 *) cw16_rtM->ModelData.outputs)->Output_g[7] =
      rtb_ratelimitedbeta[1];
    ((ExternalOutputs_cw16 *) cw16_rtM->ModelData.outputs)->Output_g[8] =
      rtb_controllergain_idx;
    ((ExternalOutputs_cw16 *) cw16_rtM->ModelData.outputs)->Output_g[9] =
      ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->torequiredEulerangles[1];
    ((ExternalOutputs_cw16 *) cw16_rtM->ModelData.outputs)->Output_g[10] =
      ((ExternalInputs_cw16 *) cw16_rtM->ModelData.inputs)->Input[16];
    ((ExternalOutputs_cw16 *) cw16_rtM->ModelData.outputs)->Output_g[11] =
      rtb_Sum2_d_idx;

    /* Integrator: '<S23>/Integrator3' */
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Integrator3 =
      ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
      ->Integrator3_CSTATE;

    /* Integrator: '<S24>/Integrator3' */
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Integrator3_a =
      ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
      ->Integrator3_CSTATE_m;

    /* Integrator: '<S25>/Integrator3' */
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Integrator3_c =
      ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
      ->Integrator3_CSTATE_k;

    /* Integrator: '<S30>/Integrator3' */
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Integrator3_am =
      ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
      ->Integrator3_CSTATE_a;

    /* Integrator: '<S31>/Integrator3' */
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Integrator3_k =
      ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
      ->Integrator3_CSTATE_n;

    /* Integrator: '<S32>/Integrator3' */
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Integrator3_cu =
      ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
      ->Integrator3_CSTATE_e;

    /* Gain: '<S38>/Gain' incorporates:
     *  Gain: '<S17>/Gain6'
     *  Gain: '<S38>/Gain3'
     *  Gain: '<S38>/Gain4'
     *  Integrator: '<S38>/Integrator2'
     *  Integrator: '<S38>/Integrator4'
     *  Sum: '<S38>/Sum'
     *  Sum: '<S38>/Sum1'
     */
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Gain = (((Parameters_cw16 *)
      cw16_rtM->ModelData.defaultParam)->gainfxtilt * rtb_Sum2[0] -
      (((Parameters_cw16 *) cw16_rtM->ModelData.defaultParam)->LPzetax *
       ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
       ->Integrator4_CSTATE_f * 2.0 + ((ContinuousStates_cw16 *)
      cw16_rtM->ModelData.contStates)->Integrator2_CSTATE_jl)) *
      ((Parameters_cw16 *) cw16_rtM->ModelData.defaultParam)->LPomeganx;

    /* Gain: '<S38>/Gain1' */
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Gain1_j = ((Parameters_cw16 *)
      cw16_rtM->ModelData.defaultParam)->LPomeganx * ((BlockIO_cw16 *)
      cw16_rtM->ModelData.blockIO)->Gain;

    /* Gain: '<S38>/Gain2' */
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Gain2 = ((Parameters_cw16 *)
      cw16_rtM->ModelData.defaultParam)->LPomeganx * ((BlockIO_cw16 *)
      cw16_rtM->ModelData.blockIO)->Gain;

    /* Integrator: '<S38>/Integrator' */
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Integrator_h =
      ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
      ->Integrator_CSTATE_bb;

    /* Integrator: '<S38>/Integrator3' */
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Integrator3_o =
      ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
      ->Integrator3_CSTATE_nd;

    /* Gain: '<S39>/Gain' incorporates:
     *  Gain: '<S17>/Gain2'
     *  Gain: '<S39>/Gain3'
     *  Gain: '<S39>/Gain4'
     *  Integrator: '<S39>/Integrator2'
     *  Integrator: '<S39>/Integrator4'
     *  Sum: '<S39>/Sum'
     *  Sum: '<S39>/Sum1'
     */
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Gain_n = (((Parameters_cw16 *)
      cw16_rtM->ModelData.defaultParam)->gainfytilt * rtb_Sum2[1] -
      (((Parameters_cw16 *) cw16_rtM->ModelData.defaultParam)->LPzetay *
       ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
       ->Integrator4_CSTATE_cn * 2.0 + ((ContinuousStates_cw16 *)
      cw16_rtM->ModelData.contStates)->Integrator2_CSTATE_mi)) *
      ((Parameters_cw16 *) cw16_rtM->ModelData.defaultParam)->LPomegany;

    /* Gain: '<S39>/Gain1' */
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Gain1_c = ((Parameters_cw16 *)
      cw16_rtM->ModelData.defaultParam)->LPomegany * ((BlockIO_cw16 *)
      cw16_rtM->ModelData.blockIO)->Gain_n;

    /* Gain: '<S39>/Gain2' */
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Gain2_e = ((Parameters_cw16 *)
      cw16_rtM->ModelData.defaultParam)->LPomegany * ((BlockIO_cw16 *)
      cw16_rtM->ModelData.blockIO)->Gain_n;

    /* Integrator: '<S39>/Integrator' */
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Integrator_l =
      ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
      ->Integrator_CSTATE_a;

    /* Integrator: '<S39>/Integrator3' */
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Integrator3_d =
      ((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
      ->Integrator3_CSTATE_o;
  }

  /* tid is required for a uniform function interface. This system
   * is single rate, and in this case, tid is not accessed. */
  UNUSED_PARAMETER(tid);
}

/* Update for root system: '<Root>' */
static void MdlUpdate(rtModel_cw16 *cw16_rtM, int_T tid)
{
  /* tid is required for a uniform function interface. This system
   * is single rate, and in this case, tid is not accessed. */
  UNUSED_PARAMETER(tid);
}

/* Derivatives for root system: '<Root>' */
static void MdlDerivatives(rtModel_cw16 *cw16_rtM)
{
  /* Derivatives for Integrator: '<S13>/Integrator' */
  ((StateDerivatives_cw16 *) cw16_rtM->ModelData.derivs)->Integrator_CSTATE =
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Sum_e;

  /* Derivatives for Integrator: '<S13>/Integrator1' */
  ((StateDerivatives_cw16 *) cw16_rtM->ModelData.derivs)->Integrator1_CSTATE =
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Sum_h;

  /* Derivatives for Integrator: '<S13>/Integrator2' */
  ((StateDerivatives_cw16 *) cw16_rtM->ModelData.derivs)->Integrator2_CSTATE =
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Sum_nm;

  /* Derivatives for Integrator: '<S14>/Integrator' */
  ((StateDerivatives_cw16 *) cw16_rtM->ModelData.derivs)->Integrator_CSTATE_c =
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Integrator;

  /* Derivatives for Integrator: '<S14>/Integrator1' */
  ((StateDerivatives_cw16 *) cw16_rtM->ModelData.derivs)->Integrator1_CSTATE_m =
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Integrator1;

  /* Derivatives for Integrator: '<S14>/Integrator2' */
  ((StateDerivatives_cw16 *) cw16_rtM->ModelData.derivs)->Integrator2_CSTATE_f =
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Integrator2;

  /* Derivatives for Integrator: '<S31>/Integrator2' */
  ((StateDerivatives_cw16 *) cw16_rtM->ModelData.derivs)->Integrator2_CSTATE_f2 =
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Integrator3_k;

  /* Derivatives for Integrator: '<S31>/Integrator4' */
  ((StateDerivatives_cw16 *) cw16_rtM->ModelData.derivs)->Integrator4_CSTATE =
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Sum;

  /* Derivatives for Integrator: '<S27>/Integrator2' */
  ((StateDerivatives_cw16 *) cw16_rtM->ModelData.derivs)->Integrator2_CSTATE_b =
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Sum_e;

  /* Derivatives for Integrator: '<S32>/Integrator2' */
  ((StateDerivatives_cw16 *) cw16_rtM->ModelData.derivs)->Integrator2_CSTATE_e =
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Integrator3_cu;

  /* Derivatives for Integrator: '<S32>/Integrator4' */
  ((StateDerivatives_cw16 *) cw16_rtM->ModelData.derivs)->Integrator4_CSTATE_j =
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Sum_n;

  /* Derivatives for Integrator: '<S28>/Integrator2' */
  ((StateDerivatives_cw16 *) cw16_rtM->ModelData.derivs)->Integrator2_CSTATE_g =
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Sum_h;

  /* Derivatives for Integrator: '<S30>/Integrator2' */
  ((StateDerivatives_cw16 *) cw16_rtM->ModelData.derivs)->Integrator2_CSTATE_j =
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Integrator3_am;

  /* Derivatives for Integrator: '<S30>/Integrator4' */
  ((StateDerivatives_cw16 *) cw16_rtM->ModelData.derivs)->Integrator4_CSTATE_c =
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Sum_k;

  /* Derivatives for Integrator: '<S29>/Integrator2' */
  ((StateDerivatives_cw16 *) cw16_rtM->ModelData.derivs)->Integrator2_CSTATE_n =
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Sum_nm;

  /* Derivatives for Integrator: '<S38>/Integrator1' */
  ((StateDerivatives_cw16 *) cw16_rtM->ModelData.derivs)->Integrator1_CSTATE_b =
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Integrator_h;

  /* Derivatives for Integrator: '<S39>/Integrator1' */
  ((StateDerivatives_cw16 *) cw16_rtM->ModelData.derivs)->Integrator1_CSTATE_c =
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Integrator_l;

  /* TransferFcn Block: '<S35>/Transfer Fcn2' */
  {
    ((StateDerivatives_cw16 *) cw16_rtM->ModelData.derivs)->TransferFcn2_CSTATE =
      ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->torequiredEulerangles[0];
    ((StateDerivatives_cw16 *) cw16_rtM->ModelData.derivs)->TransferFcn2_CSTATE +=
      (-50.0)*((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
      ->TransferFcn2_CSTATE;
  }

  /* TransferFcn Block: '<S35>/Transfer Fcn3' */
  {
    ((StateDerivatives_cw16 *) cw16_rtM->ModelData.derivs)->TransferFcn3_CSTATE =
      ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Gain1;
    ((StateDerivatives_cw16 *) cw16_rtM->ModelData.derivs)->TransferFcn3_CSTATE +=
      (-50.0)*((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
      ->TransferFcn3_CSTATE;
  }

  /* TransferFcn Block: '<S35>/Transfer Fcn5' */
  {
    ((StateDerivatives_cw16 *) cw16_rtM->ModelData.derivs)->TransferFcn5_CSTATE =
      ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->torequiredEulerangles[1];
    ((StateDerivatives_cw16 *) cw16_rtM->ModelData.derivs)->TransferFcn5_CSTATE +=
      (-50.0)*((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
      ->TransferFcn5_CSTATE;
  }

  /* TransferFcn Block: '<S35>/Transfer Fcn4' */
  {
    ((StateDerivatives_cw16 *) cw16_rtM->ModelData.derivs)->TransferFcn4_CSTATE =
      ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Gain3;
    ((StateDerivatives_cw16 *) cw16_rtM->ModelData.derivs)->TransferFcn4_CSTATE +=
      (-50.0)*((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
      ->TransferFcn4_CSTATE;
  }

  /* TransferFcn Block: '<S40>/Transfer Fcn2' */
  {
    ((StateDerivatives_cw16 *) cw16_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_n = ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)
      ->torequiredEulerangles[0];
    ((StateDerivatives_cw16 *) cw16_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_n += (-12.5)*((ContinuousStates_cw16 *)
      cw16_rtM->ModelData.contStates)->TransferFcn2_CSTATE_n;
  }

  /* TransferFcn Block: '<S40>/Transfer Fcn5' */
  {
    ((StateDerivatives_cw16 *) cw16_rtM->ModelData.derivs)
      ->TransferFcn5_CSTATE_l = ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)
      ->torequiredEulerangles[1];
    ((StateDerivatives_cw16 *) cw16_rtM->ModelData.derivs)
      ->TransferFcn5_CSTATE_l += (-12.5)*((ContinuousStates_cw16 *)
      cw16_rtM->ModelData.contStates)->TransferFcn5_CSTATE_l;
  }

  /* Derivatives for Integrator: '<S36>/rate limited beta' */
  ((StateDerivatives_cw16 *) cw16_rtM->ModelData.derivs)->
    ratelimitedbeta_CSTATE[0] = ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)
    ->betadlimiting[0];
  ((StateDerivatives_cw16 *) cw16_rtM->ModelData.derivs)->
    ratelimitedbeta_CSTATE[1] = ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)
    ->betadlimiting[1];

  /* TransferFcn Block: '<S41>/Transfer Fcn2' */
  {
    ((StateDerivatives_cw16 *) cw16_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_b = ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)
      ->betadlimiting[0];
    ((StateDerivatives_cw16 *) cw16_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_b += (-12.5)*((ContinuousStates_cw16 *)
      cw16_rtM->ModelData.contStates)->TransferFcn2_CSTATE_b;
  }

  /* TransferFcn Block: '<S41>/Transfer Fcn5' */
  {
    ((StateDerivatives_cw16 *) cw16_rtM->ModelData.derivs)
      ->TransferFcn5_CSTATE_m = ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)
      ->betadlimiting[1];
    ((StateDerivatives_cw16 *) cw16_rtM->ModelData.derivs)
      ->TransferFcn5_CSTATE_m += (-12.5)*((ContinuousStates_cw16 *)
      cw16_rtM->ModelData.contStates)->TransferFcn5_CSTATE_m;
  }

  /* Derivatives for Integrator: '<S24>/Integrator2' */
  ((StateDerivatives_cw16 *) cw16_rtM->ModelData.derivs)->Integrator2_CSTATE_m =
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Integrator3_a;

  /* Derivatives for Integrator: '<S24>/Integrator4' */
  ((StateDerivatives_cw16 *) cw16_rtM->ModelData.derivs)->Integrator4_CSTATE_a =
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Sum_j;

  /* Derivatives for Integrator: '<S21>/Integrator2' */
  ((StateDerivatives_cw16 *) cw16_rtM->ModelData.derivs)->Integrator2_CSTATE_nu =
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Sum_b;

  /* Derivatives for Integrator: '<S23>/Integrator2' */
  ((StateDerivatives_cw16 *) cw16_rtM->ModelData.derivs)->Integrator2_CSTATE_k =
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Integrator3;

  /* Derivatives for Integrator: '<S23>/Integrator4' */
  ((StateDerivatives_cw16 *) cw16_rtM->ModelData.derivs)->Integrator4_CSTATE_e =
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Sum_bl;

  /* Derivatives for Integrator: '<S20>/Integrator2' */
  ((StateDerivatives_cw16 *) cw16_rtM->ModelData.derivs)->Integrator2_CSTATE_p =
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Sum_g;

  /* Derivatives for Integrator: '<S25>/Integrator2' */
  ((StateDerivatives_cw16 *) cw16_rtM->ModelData.derivs)->Integrator2_CSTATE_a =
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Integrator3_c;

  /* Derivatives for Integrator: '<S25>/Integrator4' */
  ((StateDerivatives_cw16 *) cw16_rtM->ModelData.derivs)->Integrator4_CSTATE_o =
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Sum_hv;

  /* Derivatives for Integrator: '<S22>/Integrator2' */
  ((StateDerivatives_cw16 *) cw16_rtM->ModelData.derivs)->Integrator2_CSTATE_c =
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Sum_bly;

  /* Derivatives for Integrator: '<S12>/Integrator' */
  ((StateDerivatives_cw16 *) cw16_rtM->ModelData.derivs)->Integrator_CSTATE_b =
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Sum1[0];

  /* Derivatives for Integrator: '<S12>/Integrator1' */
  ((StateDerivatives_cw16 *) cw16_rtM->ModelData.derivs)->Integrator1_CSTATE_i =
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Sum1[1];

  /* Derivatives for Integrator: '<S12>/Integrator2' */
  ((StateDerivatives_cw16 *) cw16_rtM->ModelData.derivs)->Integrator2_CSTATE_pu =
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Sum1[2];

  /* Derivatives for Integrator: '<S11>/Integrator' */
  ((StateDerivatives_cw16 *) cw16_rtM->ModelData.derivs)->Integrator_CSTATE_l =
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Integrator_a;

  /* Derivatives for Integrator: '<S11>/Integrator1' */
  ((StateDerivatives_cw16 *) cw16_rtM->ModelData.derivs)->Integrator1_CSTATE_ii =
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Integrator1_f;

  /* Derivatives for Integrator: '<S11>/Integrator2' */
  ((StateDerivatives_cw16 *) cw16_rtM->ModelData.derivs)->Integrator2_CSTATE_h =
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Integrator2_c;

  /* TransferFcn Block: '<S45>/Transfer Fcn' */
  {
    ((StateDerivatives_cw16 *) cw16_rtM->ModelData.derivs)->TransferFcn_CSTATE =
      ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Sum4[0];
    ((StateDerivatives_cw16 *) cw16_rtM->ModelData.derivs)->TransferFcn_CSTATE +=
      (0.0)*((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
      ->TransferFcn_CSTATE;
  }

  /* TransferFcn Block: '<S45>/Transfer Fcn1' */
  {
    ((StateDerivatives_cw16 *) cw16_rtM->ModelData.derivs)->TransferFcn1_CSTATE =
      ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Sum4[1];
    ((StateDerivatives_cw16 *) cw16_rtM->ModelData.derivs)->TransferFcn1_CSTATE +=
      (0.0)*((ContinuousStates_cw16 *) cw16_rtM->ModelData.contStates)
      ->TransferFcn1_CSTATE;
  }

  /* TransferFcn Block: '<S45>/Transfer Fcn2' */
  {
    ((StateDerivatives_cw16 *) cw16_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_a = ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)
      ->Sum4[2];
    ((StateDerivatives_cw16 *) cw16_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_a += (0.0)*((ContinuousStates_cw16 *)
      cw16_rtM->ModelData.contStates)->TransferFcn2_CSTATE_a;
  }

  /* Derivatives for Integrator: '<S23>/Integrator3' */
  ((StateDerivatives_cw16 *) cw16_rtM->ModelData.derivs)->Integrator3_CSTATE =
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Sum_bl;

  /* Derivatives for Integrator: '<S24>/Integrator3' */
  ((StateDerivatives_cw16 *) cw16_rtM->ModelData.derivs)->Integrator3_CSTATE_m =
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Sum_j;

  /* Derivatives for Integrator: '<S25>/Integrator3' */
  ((StateDerivatives_cw16 *) cw16_rtM->ModelData.derivs)->Integrator3_CSTATE_k =
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Sum_hv;

  /* Derivatives for Integrator: '<S30>/Integrator3' */
  ((StateDerivatives_cw16 *) cw16_rtM->ModelData.derivs)->Integrator3_CSTATE_a =
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Sum_k;

  /* Derivatives for Integrator: '<S31>/Integrator3' */
  ((StateDerivatives_cw16 *) cw16_rtM->ModelData.derivs)->Integrator3_CSTATE_n =
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Sum;

  /* Derivatives for Integrator: '<S32>/Integrator3' */
  ((StateDerivatives_cw16 *) cw16_rtM->ModelData.derivs)->Integrator3_CSTATE_e =
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Sum_n;

  /* Derivatives for Integrator: '<S38>/Integrator2' */
  ((StateDerivatives_cw16 *) cw16_rtM->ModelData.derivs)->Integrator2_CSTATE_jl =
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Integrator3_o;

  /* Derivatives for Integrator: '<S38>/Integrator4' */
  ((StateDerivatives_cw16 *) cw16_rtM->ModelData.derivs)->Integrator4_CSTATE_f =
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Gain;

  /* Derivatives for Integrator: '<S38>/Integrator' */
  ((StateDerivatives_cw16 *) cw16_rtM->ModelData.derivs)->Integrator_CSTATE_bb =
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Gain1_j;

  /* Derivatives for Integrator: '<S38>/Integrator3' */
  ((StateDerivatives_cw16 *) cw16_rtM->ModelData.derivs)->Integrator3_CSTATE_nd =
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Gain2;

  /* Derivatives for Integrator: '<S39>/Integrator2' */
  ((StateDerivatives_cw16 *) cw16_rtM->ModelData.derivs)->Integrator2_CSTATE_mi =
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Integrator3_d;

  /* Derivatives for Integrator: '<S39>/Integrator4' */
  ((StateDerivatives_cw16 *) cw16_rtM->ModelData.derivs)->Integrator4_CSTATE_cn =
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Gain_n;

  /* Derivatives for Integrator: '<S39>/Integrator' */
  ((StateDerivatives_cw16 *) cw16_rtM->ModelData.derivs)->Integrator_CSTATE_a =
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Gain1_c;

  /* Derivatives for Integrator: '<S39>/Integrator3' */
  ((StateDerivatives_cw16 *) cw16_rtM->ModelData.derivs)->Integrator3_CSTATE_o =
    ((BlockIO_cw16 *) cw16_rtM->ModelData.blockIO)->Gain2_e;
}

/* Projection for root system: '<Root>' */
static void MdlProjection(rtModel_cw16 *cw16_rtM)
{
}

/* Terminate for root system: '<Root>' */
static void MdlTerminate(rtModel_cw16 *cw16_rtM)
{
  rt_FREE(cw16_rtM->solverInfo);
  rt_FREE(cw16_rtM->sfcnInfo);

  /* model code */
  {
    void *ptr = cw16_rtM->ModelData.blockIO;
    rt_FREE(ptr);
  }

  {
    real_T *ptr = (real_T *) cw16_rtM->ModelData.contStates;
    rt_FREE(ptr);
  }

  {
    real_T *ptr = (real_T *) cw16_rtM->ModelData.inputs;
    rt_FREE(ptr);
  }

  {
    real_T *ptr = (real_T *) cw16_rtM->ModelData.outputs;
    rt_FREE(ptr);
  }

  if (cw16_rtM->ModelData.paramIsMalloced) {
    rt_FREE(cw16_rtM->ModelData.defaultParam);
  }

  rt_FREE(cw16_rtM->Timing.sampleTimes);
  rt_FREE(cw16_rtM->Timing.offsetTimes);
  rt_FREE(cw16_rtM->Timing.sampleTimeTaskIDPtr);
  rt_FREE(rtmGetTPtr(cw16_rtM));
  rt_FREE(cw16_rtM->Timing.sampleHits);

  {
    void *xptr = (void *) rtliGetLogXSignalPtrs(cw16_rtM->rtwLogInfo);
    void *yptr = (void *) rtliGetLogYSignalPtrs(cw16_rtM->rtwLogInfo);
    rt_FREE(xptr);
    rt_FREE(yptr);
  }

  rt_FREE(cw16_rtM->rtwLogInfo);
  rt_FREE(cw16_rtM);
}

/* Function to initialize sizes */
static void MdlInitializeSizes(rtModel_cw16 *cw16_rtM)
{
  cw16_rtM->Sizes.numContStates = (59);/* Number of continuous states */
  cw16_rtM->Sizes.numY = (12);         /* Number of model outputs */
  cw16_rtM->Sizes.numU = (21);         /* Number of model inputs */
  cw16_rtM->Sizes.sysDirFeedThru = (1);/* The model is direct feedthrough */
  cw16_rtM->Sizes.numSampTimes = (2);  /* Number of sample times */
  cw16_rtM->Sizes.numBlocks = (238);   /* Number of blocks */
  cw16_rtM->Sizes.numBlockIO = (40);   /* Number of block outputs */
  cw16_rtM->Sizes.numBlockPrms = (59); /* Sum of parameter "widths" */
}

/* Function to initialize sample times */
static void MdlInitializeSampleTimes(rtModel_cw16 *cw16_rtM)
{
  /* task periods */
  cw16_rtM->Timing.sampleTimes[0] = (0.0);
  cw16_rtM->Timing.sampleTimes[1] = (0.01);

  /* task offsets */
  cw16_rtM->Timing.offsetTimes[0] = (0.0);
  cw16_rtM->Timing.offsetTimes[1] = (0.0);
}

/* Function to register the model */
rtModel_cw16 *cw16(void)
{
  rtModel_cw16 *cw16_rtM;
  cw16_rtM = (rtModel_cw16 *) malloc(sizeof(rtModel_cw16));
  if (cw16_rtM == NULL) {
    return NULL;
  }

  (void) memset((char *)cw16_rtM,0,
                sizeof(rtModel_cw16));

  {
    /* Setup solver object */
    RTWSolverInfo *rt_SolverInfo = (RTWSolverInfo *) malloc(sizeof(RTWSolverInfo));
    rt_VALIDATE_MEMORY(cw16_rtM,rt_SolverInfo);
    cw16_rtM->solverInfo = (rt_SolverInfo);
    rtsiSetSimTimeStepPtr(cw16_rtM->solverInfo, &cw16_rtM->Timing.simTimeStep);
    rtsiSetTPtr(cw16_rtM->solverInfo, &rtmGetTPtr(cw16_rtM));
    rtsiSetStepSizePtr(cw16_rtM->solverInfo, &cw16_rtM->Timing.stepSize);
    rtsiSetdXPtr(cw16_rtM->solverInfo, &cw16_rtM->ModelData.derivs);
    rtsiSetContStatesPtr(cw16_rtM->solverInfo, &cw16_rtM->ModelData.contStates);
    rtsiSetNumContStatesPtr(cw16_rtM->solverInfo, &cw16_rtM->Sizes.numContStates);
    rtsiSetErrorStatusPtr(cw16_rtM->solverInfo, (&rtmGetErrorStatus(cw16_rtM)));
    rtsiSetModelMethodsPtr(cw16_rtM->solverInfo, &cw16_rtM->modelMethodsInfo);
    rtsiSetRTModelPtr(cw16_rtM->solverInfo, cw16_rtM);
  }

  /* timing info */
  {
    time_T *mdlPeriod;
    time_T *mdlOffset;
    time_T *mdlTaskTimes;
    int_T *mdlTsMap;
    int_T *mdlSampleHits;
    mdlPeriod = (time_T *) malloc(2 * sizeof(time_T));
    rt_VALIDATE_MEMORY(cw16_rtM,mdlPeriod);
    mdlOffset = (time_T *) malloc(2 * sizeof(time_T));
    rt_VALIDATE_MEMORY(cw16_rtM,mdlOffset);
    mdlTaskTimes = (time_T *) malloc(2 * sizeof(time_T));
    rt_VALIDATE_MEMORY(cw16_rtM,mdlTaskTimes);
    mdlTsMap = (int_T *) malloc(2 * sizeof(int_T));
    rt_VALIDATE_MEMORY(cw16_rtM,mdlTsMap);
    mdlSampleHits = (int_T *) malloc(2 * sizeof(int_T));
    rt_VALIDATE_MEMORY(cw16_rtM,mdlSampleHits);

    {
      int_T i;
      for (i = 0; i < NSAMPLE_TIMES; i++) {
        mdlPeriod[i] = 0.0;
        mdlOffset[i] = 0.0;
        mdlTaskTimes[i] = 0.0;
        mdlTsMap[i] = i;
        mdlSampleHits[i] = 1;
      }
    }

    cw16_rtM->Timing.sampleTimes = (&mdlPeriod[0]);
    cw16_rtM->Timing.offsetTimes = (&mdlOffset[0]);
    cw16_rtM->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    rtmSetTPtr(cw16_rtM, &mdlTaskTimes[0]);
    cw16_rtM->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtsiSetSolverMode(cw16_rtM->solverInfo, SOLVER_MODE_SINGLETASKING);

  /*
   * initialize model vectors and cache them in SimStruct
   */

  /* block I/O */
  {
    void *b = malloc(sizeof(BlockIO_cw16));
    rt_VALIDATE_MEMORY(cw16_rtM,b);
    cw16_rtM->ModelData.blockIO = (b);

    {
      int_T i;
      void *pVoidBlockIORegion;
      pVoidBlockIORegion = (void *)(&((BlockIO_cw16 *)
        cw16_rtM->ModelData.blockIO)->Integrator);
      for (i = 0; i < 46; i++) {
        ((real_T*)pVoidBlockIORegion)[i] = 0.0;
      }
    }
  }

  /* external inputs */
  {
    cw16_rtM->ModelData.inputs = (ExternalInputs_cw16 *) malloc(sizeof
      (ExternalInputs_cw16));
    rt_VALIDATE_MEMORY(cw16_rtM,((ExternalInputs_cw16 *)
      cw16_rtM->ModelData.inputs));

    {
      int_T i;
      for (i = 0; i < 21; i++) {
        ((ExternalInputs_cw16 *) cw16_rtM->ModelData.inputs)->Input[i] = 0.0;
      }
    }
  }

  /* external outputs */
  {
    cw16_rtM->ModelData.outputs = (ExternalOutputs_cw16 *) malloc(sizeof
      (ExternalOutputs_cw16));
    rt_VALIDATE_MEMORY(cw16_rtM,((ExternalOutputs_cw16 *)
      cw16_rtM->ModelData.outputs));

    {
      int_T i;
      for (i = 0; i < 12; i++) {
        ((ExternalOutputs_cw16 *) cw16_rtM->ModelData.outputs)->Output_g[i] =
          0.0;
      }
    }
  }

  /* parameters */
  {
    Parameters_cw16 *p;
    static int_T pSeen = FALSE;

    /* only malloc on multiple model instantiation */
    if (pSeen == TRUE ) {
      p = (Parameters_cw16 *) malloc(sizeof(Parameters_cw16));
      rt_VALIDATE_MEMORY(cw16_rtM,p);
      (void) memcpy(p,&cw16_DefaultParameters,
                    sizeof(Parameters_cw16));
      cw16_rtM->ModelData.paramIsMalloced = (TRUE);
    } else {
      p = &cw16_DefaultParameters;
      cw16_rtM->ModelData.paramIsMalloced = (FALSE);
      pSeen = TRUE;
    }

    cw16_rtM->ModelData.defaultParam = ((real_T *) p);
  }

  /* states (continuous)*/
  {
    real_T *x = (real_T *) malloc(sizeof(ContinuousStates_cw16));
    rt_VALIDATE_MEMORY(cw16_rtM,x);
    cw16_rtM->ModelData.contStates = (x);
    (void) memset((void *)x,0,
                  sizeof(ContinuousStates_cw16));
  }

  /* Model specific registration */
  cw16_rtM->modelName = ("cw16");
  cw16_rtM->path = ("cw16");
  rtmSetTStart(cw16_rtM, 0.0);
  rtmSetTFinal(cw16_rtM, 10.0);
  cw16_rtM->Timing.stepSize = (0.01);
  rtsiSetFixedStepSize(cw16_rtM->solverInfo, 0.01);

  /* Setup for data logging */
  {
    RTWLogInfo *rt_DataLoggingInfo = (RTWLogInfo *) malloc(sizeof(RTWLogInfo));
    rt_VALIDATE_MEMORY(cw16_rtM,rt_DataLoggingInfo);
    cw16_rtM->rtwLogInfo = (rt_DataLoggingInfo);
    rtliSetLogFormat(cw16_rtM->rtwLogInfo, 0);
    rtliSetLogMaxRows(cw16_rtM->rtwLogInfo, 0);
    rtliSetLogDecimation(cw16_rtM->rtwLogInfo, 1);
    rtliSetLogVarNameModifier(cw16_rtM->rtwLogInfo, "rt_");
    rtliSetLogT(cw16_rtM->rtwLogInfo, "");
    rtliSetLogX(cw16_rtM->rtwLogInfo, "");
    rtliSetLogXFinal(cw16_rtM->rtwLogInfo, "");
    rtliSetSigLog(cw16_rtM->rtwLogInfo, "");
    rtliSetLogXSignalInfo(cw16_rtM->rtwLogInfo, NULL);
    rtliSetLogXSignalPtrs(cw16_rtM->rtwLogInfo, NULL);
    rtliSetLogY(cw16_rtM->rtwLogInfo, "");
    rtliSetLogYSignalInfo(cw16_rtM->rtwLogInfo, NULL);
    rtliSetLogYSignalPtrs(cw16_rtM->rtwLogInfo, NULL);
  }

  cw16_rtM->Sizes.checksums[0] = (1878584042U);
  cw16_rtM->Sizes.checksums[1] = (2232006330U);
  cw16_rtM->Sizes.checksums[2] = (931249662U);
  cw16_rtM->Sizes.checksums[3] = (1739010298U);
  rtmiSetInitSizesFcn((cw16_rtM->modelMethodsInfo), MdlInitializeSizes);
  rtmiSetInitSampTimesFcn((cw16_rtM->modelMethodsInfo), MdlInitializeSampleTimes);
  rtmiSetStartFcn((cw16_rtM->modelMethodsInfo), MdlStart);
  rtmiSetOutputsFcn((cw16_rtM->modelMethodsInfo), MdlOutputs);
  rtmiSetUpdateFcn((cw16_rtM->modelMethodsInfo), MdlUpdate);
  rtmiSetDervisFcn((cw16_rtM->modelMethodsInfo), MdlDerivatives);
  rtmiSetProjectionFcn((cw16_rtM->modelMethodsInfo), MdlProjection);
  rtmiSetMassMatrixFcn((cw16_rtM->modelMethodsInfo), NULL);
  rtmiSetForcingFunctionFcn((cw16_rtM->modelMethodsInfo), NULL);
  rtmiSetTerminateFcn((cw16_rtM->modelMethodsInfo), MdlTerminate);
  rtmiSetRTModelPtr((cw16_rtM->modelMethodsInfo), cw16_rtM);
  return cw16_rtM;
}
