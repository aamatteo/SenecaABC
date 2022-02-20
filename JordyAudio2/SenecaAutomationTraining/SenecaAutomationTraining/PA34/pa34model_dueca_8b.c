/*
 * pa34model_dueca_8b.c
 *
 * Real-Time Workshop code generation for Simulink model "pa34model_dueca_8b.mdl".
 *
 * Model Version              : 1.20293
 * Real-Time Workshop version : 7.0  (R2007b)  02-Aug-2007
 * C source code generated on : Tue Jul 14 10:39:43 2015
 */

#include <math.h>
#include "pa34model_dueca_8b.h"
#include "pa34model_dueca_8b_private.h"

/* Invariant block signals (auto storage) */
static ConstBlockIO_pa34model_dueca_8b pa34model_duec_InvariantSignals = {
  { 0.0, 0.0, 0.0, 6.1723961544292550E+001, 0.0, 1.0756466534785893E+000, 0.0,
    1.7424963634836945E-002, 0.0, 0.0, 0.0, -9.1440000000000009E+002 },/* '<S2>/Constant1' */
  0.0,                                 /* '<S39>/PreLook-Up Index Search  (prob of exceed)' */

  { 150.0, 150.0 },                    /* '<S2>/Constant2' */
  3U                                   /* '<S39>/PreLook-Up Index Search  (prob of exceed)' */
};

static void pa34model_c1_pa34model_dueca_8b(rtModel_pa34model_dueca_8b
  *pa34model_dueca_8b_rtM);
static void pa34mode_c19_pa34model_dueca_8b(rtModel_pa34model_dueca_8b
  *pa34model_dueca_8b_rtM);
uint32_T plook_bincpa(real_T u, const real_T *const bp, uint32_T maxIndex,
                      real_T *fraction, uint32_T *prevIndex)
{
  uint32_T bpIndex;
  uint32_T startIndex;
  real_T bpLeftCast;
  real_T bpRghtCast;

  /* Prelookup Index and Fraction
     Search method: 'binary'
     Process out of range input: 'Clip to range'
     Use previous index: 'on'
     Use last breakpoint for index at or above upper limit: 'on'
   */
  if (u < bp[0U]) {
    bpIndex = 0U;
    *fraction = 0.0;
  } else if (u < bp[maxIndex]) {
    startIndex = *prevIndex;
    bpIndex = binsearch_u32d_prevIdx(u, bp, startIndex, maxIndex);
    bpLeftCast = bp[bpIndex];
    bpRghtCast = bp[bpIndex + 1U];
    *fraction = (u - bpLeftCast) / (bpRghtCast - bpLeftCast);
  } else {
    bpIndex = maxIndex;
    *fraction = 0.0;
  }

  *prevIndex = bpIndex;
  return bpIndex;
}

real_T intrp2d_lca(const uint32_T *const bpIndex, const real_T *const frac,
                   const real_T *const table, uint32_T stride, const uint32_T *
                   const maxIndex)
{
  real_T y;
  real_T yL_1d;
  uint32_T offset_1d;
  real_T yL_0d0;
  real_T yR_0d0;

  /* Interpolation 2-D
     Interpolation method: 'Linear'
     Extrapolation method: 'Clip'
     Use last breakpoint for index at or above upper limit: 'on'
   */
  offset_1d = bpIndex[1U] * stride + bpIndex[0U];
  if (bpIndex[0U] == maxIndex[0U]) {
    yL_1d = table[offset_1d];
  } else {
    yR_0d0 = table[offset_1d + 1U];
    yL_0d0 = table[offset_1d];
    yL_1d = (yR_0d0 - yL_0d0) * frac[0U] + yL_0d0;
  }

  if (bpIndex[1U] == maxIndex[1U]) {
    y = yL_1d;
  } else {
    offset_1d = offset_1d + stride;
    if (bpIndex[0U] == maxIndex[0U]) {
      yR_0d0 = table[offset_1d];
    } else {
      yR_0d0 = table[offset_1d + 1U];
      yL_0d0 = table[offset_1d];
      yR_0d0 = (yR_0d0 - yL_0d0) * frac[0U] + yL_0d0;
    }

    y = (yR_0d0 - yL_1d) * frac[1U] + yL_1d;
  }

  return y;
}

uint32_T binsearch_u32d_prevIdx(real_T u, const real_T *const bp, uint32_T
  startIndex, uint32_T maxIndex)
{
  uint32_T bpIndex;
  uint32_T iRght;
  uint32_T iLeft;
  uint32_T bpIdx;
  uint32_T found;

  /* Binary Search using Previous Index */
  bpIdx = startIndex;
  iLeft = 0U;
  iRght = maxIndex;
  found = 0U;
  while (found == 0U) {
    if (u < bp[bpIdx]) {
      iRght = bpIdx - 1U;
      bpIdx = (iRght + iLeft) >> 1U;
    } else if (u < bp[bpIdx + 1U]) {
      found = 1U;
    } else {
      iLeft = bpIdx + 1U;
      bpIdx = (iRght + iLeft) >> 1U;
    }
  }

  bpIndex = bpIdx;
  return bpIndex;
}

/* Functions for block: '<S6>/AERO FORCES EN MOMENTS' */
static void pa34model_c1_pa34model_dueca_8b(rtModel_pa34model_dueca_8b
  *pa34model_dueca_8b_rtM)
{
  real_T eml_p;
  real_T eml_q;
  real_T eml_r;
  real_T eml_u;
  real_T eml_v;
  real_T eml_w;
  real_T eml_Vb[3];
  real_T eml_z;
  real_T eml_de;
  real_T eml_da;
  real_T eml_dr;
  real_T eml_df;
  real_T eml_gear;
  real_T eml_Sw;
  real_T eml_bw;
  real_T eml_cbarw;
  real_T eml_hOverb;
  real_T eml_vtas;
  int32_T eml_i;
  boolean_T eml_landed;
  real_T eml_alpha;
  real_T eml_beta;
  real_T eml_alpha_dot;
  real_T eml_qbar;
  real_T eml_CL_left;
  real_T eml_CL_right;
  real_T eml_CL_basic;
  real_T eml_CL_HT_left;
  real_T eml_CL_GE_HT_left;
  real_T eml_CL_HT_right;
  real_T eml_CL_GE_HT_right;
  real_T eml_K_GE_W;
  real_T eml_Tc_l;
  real_T eml_Tc_r;
  real_T eml_pb;
  real_T eml_rb;
  real_T eml_qc;
  int32_T eml_iL;
  real_T eml_delta_i;
  int32_T eml_k;
  int32_T eml_kL;
  real_T eml_delta_k;
  real_T eml_H1;
  real_T eml_H3;
  real_T eml_CL_DF;
  real_T eml_Epsilon_2;
  real_T eml_Tc;
  int32_T eml_ii;
  static int8_T eml_iv0[2] = { 1, 2 };

  int32_T eml_ii_0;
  int32_T eml_j;
  int32_T eml_jL;
  real_T eml_CL_q;
  static real_T eml_dv28[9] = { 0.033, 0.0222, 0.0152, 0.0104, 0.007, 0.0048,
    0.0022, 0.0, 0.0 };

  static real_T eml_dv29[9] = { 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 7.5, 10.0, 15.0 };

  static real_T eml_dv30[6] = { 0.054, 0.0336, 0.0168, 0.06, 0.0, 0.0 };

  static real_T eml_dv31[6] = { 0.0, 0.4, 1.0, 2.0, 4.0, 15.0 };

  static real_T eml_dv32[4] = { -0.084728, -0.084728, -0.074158, -0.055151 };

  static real_T eml_dv33[4] = { 0.0, 0.274, 0.48, 0.9599 };

  /*  ~=beta_dot */
  /*  basis lift f(alpha,Tc) */
  /*  lift due to flap f(alpha,df) */
  /*  Slipstream effect on flaps */
  /*  Increased dynamic presuure at HT f(alpha,Tc) */
  /*  Downwash angle at HT f(alpha,Tc) */
  /*  INcreased down wash angle HT due to flaps (alpha,df) */
  /*  CLq (alpha,Tc) */
  /*  CL alpa_dot (alpha,Tc) */
  /*  CD_basic(alpha,Tc) */
  /*  CD_basic(alpha,dF) */
  /*  CD_gear(df) */
  /*  Table 18 constants: CD_gear_imersed=0.002587; CL_a(wing)=5.2655 */
  /*  CL_alpha(HT)=0.8191 */
  /*  Table 19 GE_wing(H) GE_HT(H) =>lin interpolatie  */
  /*  Cm_wb f(alpa,Tc) */
  /*  Cm_wd (alpha,df) */
  /*  CM_q (alpha,Tc) */
  /*  CM_alpha_dot(alpha,Tc) */
  /*  CY_beta(Tc) */
  /*  Cl_beta(alpha) */
  /*  Cn_beta(alpha,Tc) */
  /*  CY_r */
  /*  Cl_r */
  /*  Cn_r */
  /*  CY_p */
  /*  Cl_p */
  /*  Cn_p */
  /*  Cl_da(,|da|) */
  /*  Cn_da (alpha,|da|) */
  /*  Table 31 CY_dr=0.13905 */
  /*  Cl_dr(alpha) */
  /*  */
  /* state = col( p, q, r, u, v, w, phi, theta, psi, x, y, z) */
  eml_p = ((BlockIO_pa34model_dueca_8b *)
           pa34model_dueca_8b_rtM->ModelData.blockIO)->stateo[0];
  eml_q = ((BlockIO_pa34model_dueca_8b *)
           pa34model_dueca_8b_rtM->ModelData.blockIO)->stateo[1];
  eml_r = ((BlockIO_pa34model_dueca_8b *)
           pa34model_dueca_8b_rtM->ModelData.blockIO)->stateo[2];
  eml_u = ((BlockIO_pa34model_dueca_8b *)
           pa34model_dueca_8b_rtM->ModelData.blockIO)->stateo[3];
  eml_v = ((BlockIO_pa34model_dueca_8b *)
           pa34model_dueca_8b_rtM->ModelData.blockIO)->stateo[4];
  eml_w = ((BlockIO_pa34model_dueca_8b *)
           pa34model_dueca_8b_rtM->ModelData.blockIO)->stateo[5];

  /* phi=state(7); */
  eml_Vb[0] = eml_u;
  eml_Vb[1] = eml_v;
  eml_Vb[2] = eml_w;
  eml_z = ((BlockIO_pa34model_dueca_8b *)
           pa34model_dueca_8b_rtM->ModelData.blockIO)->stateo[11];

  /* statedot (see state) */
  /* pilot_input = col( de, da, dr, dte, dta, dtr, df, gear, pla1, pla2) */
  eml_de = ((BlockIO_pa34model_dueca_8b *)
            pa34model_dueca_8b_rtM->ModelData.blockIO)->Pil_uit[0];
  eml_da = ((BlockIO_pa34model_dueca_8b *)
            pa34model_dueca_8b_rtM->ModelData.blockIO)->Pil_uit[1];
  eml_dr = ((BlockIO_pa34model_dueca_8b *)
            pa34model_dueca_8b_rtM->ModelData.blockIO)->Pil_uit[2];
  eml_df = ((BlockIO_pa34model_dueca_8b *)
            pa34model_dueca_8b_rtM->ModelData.blockIO)->Pil_uit[6];
  eml_gear = ((BlockIO_pa34model_dueca_8b *)
              pa34model_dueca_8b_rtM->ModelData.blockIO)->Pil_uit[7];

  /* atmos = col(rho, T, g, Vwind (3), Omegawind (3)) */
  /* geometry = col (S,b,cbar,rp_aero (3)) */
  eml_Sw = ((BlockIO_pa34model_dueca_8b *)
            pa34model_dueca_8b_rtM->ModelData.blockIO)
    ->TmpHiddenBufferAtSFunctionInpor[0];
  eml_bw = ((BlockIO_pa34model_dueca_8b *)
            pa34model_dueca_8b_rtM->ModelData.blockIO)
    ->TmpHiddenBufferAtSFunctionInpor[1];
  eml_cbarw = ((BlockIO_pa34model_dueca_8b *)
               pa34model_dueca_8b_rtM->ModelData.blockIO)
    ->TmpHiddenBufferAtSFunctionInpor[2];

  /* massmodel = col(m, Ixx, Iyy, Izz, Ixy, cg(3), Ixy , Izy) */
  /* ground effect factor */
  eml_hOverb = (-eml_z) + 10.0;

  /* h for ground effect */
  /* % Calculate vtas, alpha, beta, vtasdot, alphadot and betadot */
  eml_vtas = 0.0;
  for (eml_i = 0; eml_i < 3; eml_i++) {
    eml_vtas += eml_Vb[eml_i] * eml_Vb[eml_i];
  }

  eml_vtas = sqrt(eml_vtas);
  if ((eml_gear == 1.0) && (eml_z > -1.5) && (eml_vtas < 20.0)) {
    eml_landed = true;
  } else {
    eml_landed = false;
  }

  /*  Wijziging in landing module, landed blijft nu false */
  eml_alpha = cbaabiecohlncbaa_atan2(eml_w, eml_u);

  /* *sign(u)*min([1 abs(u)]); */
  eml_beta = asin(eml_v / eml_vtas);

  /* *sign(vtas)*min([1 abs(vtas)]); */
  eml_alpha_dot = (((BlockIO_pa34model_dueca_8b *)
                    pa34model_dueca_8b_rtM->ModelData.blockIO)->Init[5] * eml_u
                   - ((BlockIO_pa34model_dueca_8b *)
                      pa34model_dueca_8b_rtM->ModelData.blockIO)->Init[3] *
                   eml_w) / (pow(eml_u, 2.0) + pow(eml_w, 2.0));
  if (eml_landed) {
    eml_alpha = ((BlockIO_pa34model_dueca_8b *)
                 pa34model_dueca_8b_rtM->ModelData.blockIO)->stateo[7];
    eml_alpha_dot = eml_q;
  }

  /* Depending on the choice of aerodynamic model parametrization, rotational rate in the  */
  /* aerodynamic frame (Omega_a) instead of rotation in body frame (Omega_b) may be needed. */
  /* % Calculate qbar */
  eml_qbar = 0.5 * ((BlockIO_pa34model_dueca_8b *)
                    pa34model_dueca_8b_rtM->ModelData.blockIO)->atmoso[0] * pow
    (eml_vtas, 2.0);

  /*  Embedded matlab restrictie: */
  /*  Vooraf definieren van variabelen in if statements!! */
  eml_CL_left = 1.0;
  eml_CL_right = 1.0;
  eml_CL_basic = 0.0;
  eml_CL_HT_left = 0.0;
  eml_CL_GE_HT_left = 0.0;
  eml_CL_HT_right = 0.0;
  eml_CL_GE_HT_right = 0.0;
  eml_K_GE_W = 0.0;

  /* List of implemented functions: */
  /*  Thrust coeficienten apart voor linker en rechter motor;  */
  /*  De grafieken gaan uit van totale thrust dus daarom  */
  /*  individule thrust maal twee voor de */
  /*  juist coefficent voor lift change effect alleen x component ; */
  eml_Tc_l = 2.0 * ((BlockIO_pa34model_dueca_8b *)
                    pa34model_dueca_8b_rtM->ModelData.blockIO)->Thrust[0] /
    (eml_qbar * eml_Sw);

  /*  Tc Gebaseerd op linker motor */
  eml_Tc_r = 2.0 * ((BlockIO_pa34model_dueca_8b *)
                    pa34model_dueca_8b_rtM->ModelData.blockIO)->Thrust[6] /
    (eml_qbar * eml_Sw);

  /*  Tc gebaseerd op rechter motor */
  /*  body angular rates to non dimensional rates  in model reference frame */
  /*  pb=p*bw/(2*vtas);  */
  /*  rb=r*bw/(2*vtas); */
  eml_pb = (eml_p * cos(eml_alpha) + eml_r * sin(eml_alpha)) * eml_bw / (2.0 *
    eml_vtas);
  eml_rb = (eml_r * cos(eml_alpha) - eml_p * sin(eml_alpha)) * eml_bw / (2.0 *
    eml_vtas);
  eml_qc = eml_q * eml_cbarw / eml_vtas;

  /*  Bepalen indices en fractie van alpha: iL, iH, delta_i; */
  for (eml_i = 2; (eml_alpha > ((D_Work_pa34model_dueca_8b *)
         pa34model_dueca_8b_rtM->Work.dwork)->Table_8[eml_i - 1]) && (eml_i < 19);
       eml_i++) {
  }

  if (eml_alpha > ((D_Work_pa34model_dueca_8b *)
                   pa34model_dueca_8b_rtM->Work.dwork)->Table_8[18]) {
    eml_iL = 19;
    eml_i = 19;
    eml_delta_i = 0.0;
  } else if (eml_i == 2) {
    eml_iL = 2;
    eml_i = 2;
    eml_delta_i = 0.0;
  } else {
    eml_iL = eml_i - 1;
    eml_delta_i = (eml_alpha - ((D_Work_pa34model_dueca_8b *)
      pa34model_dueca_8b_rtM->Work.dwork)->Table_8[eml_iL - 1]) /
      (((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
       ->Table_8[eml_i - 1] - ((D_Work_pa34model_dueca_8b *)
        pa34model_dueca_8b_rtM->Work.dwork)->Table_8[eml_iL - 1]);
  }

  /*  Bepalen  indices en fractie van Flapstand: kL, kH, delta_k; */
  for (eml_k = 2; (eml_df > ((D_Work_pa34model_dueca_8b *)
         pa34model_dueca_8b_rtM->Work.dwork)->Table_8[19 * (eml_k - 1)]) &&
       (eml_k < 5); eml_k++) {
  }

  if (eml_df > ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
      ->Table_8[76]) {
    eml_kL = 5;
    eml_k = 5;
    eml_delta_k = 0.0;
  } else if (eml_k == 2) {
    eml_kL = 2;
    eml_k = 2;
    eml_delta_k = 0.0;
  } else {
    eml_kL = eml_k - 1;
    eml_delta_k = (eml_df - ((D_Work_pa34model_dueca_8b *)
      pa34model_dueca_8b_rtM->Work.dwork)->Table_8[19 * (eml_kL - 1)]) /
      (((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
       ->Table_8[19 * (eml_k - 1)] - ((D_Work_pa34model_dueca_8b *)
        pa34model_dueca_8b_rtM->Work.dwork)->Table_8[19 * (eml_kL - 1)]);
  }

  /* CL************************************************************************ */
  /*  De eerste twee tables zijn onafhankelijk van Tc en worden eerst  gedaan */
  /*  CL(alpha, df) Table 8 */
  eml_H1 = ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
    ->Table_8[(eml_iL - 1) + 19 * (eml_kL - 1)];
  eml_H3 = ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
    ->Table_8[(eml_i - 1) + 19 * (eml_kL - 1)];
  eml_H1 += eml_delta_k * (((D_Work_pa34model_dueca_8b *)
    pa34model_dueca_8b_rtM->Work.dwork)->Table_8[(eml_iL - 1) + 19 * (eml_k - 1)]
    - eml_H1);
  eml_CL_DF = eml_H1 + eml_delta_i * ((eml_H3 + eml_delta_k *
    (((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)->
     Table_8[(eml_i - 1) + 19 * (eml_k - 1)] - eml_H3)) - eml_H1);

  /*  Downwash at HT (Epsilon_2) Table 12(alpha,df) */
  eml_H1 = ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
    ->Table_12[(eml_iL - 1) + 19 * (eml_kL - 1)];
  eml_H3 = ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
    ->Table_12[(eml_i - 1) + 19 * (eml_kL - 1)];
  eml_H1 += eml_delta_k * (((D_Work_pa34model_dueca_8b *)
    pa34model_dueca_8b_rtM->Work.dwork)->Table_12[(eml_iL - 1) + 19 * (eml_k - 1)]
    - eml_H1);
  eml_Epsilon_2 = eml_H1 + eml_delta_i * ((eml_H3 + eml_delta_k *
    (((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
     ->Table_12[(eml_i - 1) + 19 * (eml_k - 1)] - eml_H3)) - eml_H1);
  eml_Tc = 0.0;

  /*  N Lift uitrekenen apart voor linker en rechter thust coefficient */
  for (eml_ii = 0; eml_ii < 2; eml_ii++) {
    eml_ii_0 = (int32_T)eml_iv0[eml_ii];
    if (eml_ii_0 == 1) {
      eml_Tc = eml_Tc_l;
    }

    if (eml_ii_0 == 2) {
      eml_Tc = eml_Tc_r;
    }

    /* Bepalen  indices en fractie van Tc, iL, iH, delta_i; */
    for (eml_j = 2; (eml_Tc > ((D_Work_pa34model_dueca_8b *)
           pa34model_dueca_8b_rtM->Work.dwork)->Table_7[19 * (eml_j - 1)]) &&
         (eml_j < 4); eml_j++) {
    }

    if (eml_Tc > ((D_Work_pa34model_dueca_8b *)
                  pa34model_dueca_8b_rtM->Work.dwork)->Table_7[57]) {
      eml_jL = 4;
      eml_j = 4;
      eml_p = 0.0;
    } else if (eml_j == 2) {
      eml_jL = 2;
      eml_j = 2;
      eml_p = 0.0;
    } else {
      eml_jL = eml_j - 1;
      eml_p = (eml_Tc - ((D_Work_pa34model_dueca_8b *)
                         pa34model_dueca_8b_rtM->Work.dwork)->Table_7[19 *
               (eml_jL - 1)]) / (((D_Work_pa34model_dueca_8b *)
        pa34model_dueca_8b_rtM->Work.dwork)->Table_7[19 * (eml_j - 1)] -
        ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
        ->Table_7[19 * (eml_jL - 1)]);
    }

    /*  Basis lift coefficient wing_body Table_7(alpha,Tc) */
    eml_H1 = ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork
      )->Table_7[(eml_iL - 1) + 19 * (eml_jL - 1)];
    eml_H3 = ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork
      )->Table_7[(eml_i - 1) + 19 * (eml_jL - 1)];
    eml_H1 += eml_p * (((D_Work_pa34model_dueca_8b *)
                        pa34model_dueca_8b_rtM->Work.dwork)->Table_7[(eml_iL - 1)
                       + 19 * (eml_j - 1)] - eml_H1);
    eml_z = eml_H1 + eml_delta_i * ((eml_H3 + eml_p *
      (((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
       ->Table_7[(eml_i - 1) + 19 * (eml_j - 1)] - eml_H3)) - eml_H1);

    /* Effect van Thrust op de delta lift due to flaps (factor K_1) */
    /* Table 9(alpha,Tc) */
    eml_H1 = ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork
      )->Table_9[(eml_iL - 1) + 19 * (eml_jL - 1)];
    eml_H3 = ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork
      )->Table_9[(eml_i - 1) + 19 * (eml_jL - 1)];
    eml_H1 += eml_p * (((D_Work_pa34model_dueca_8b *)
                        pa34model_dueca_8b_rtM->Work.dwork)->Table_9[(eml_iL - 1)
                       + 19 * (eml_j - 1)] - eml_H1);

    /* ************************** */
    eml_CL_basic = eml_z + eml_CL_DF * (eml_H1 + eml_delta_i * ((eml_H3 + eml_p *
      (((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
       ->Table_9[(eml_i - 1) + 19 * (eml_j - 1)] - eml_H3)) - eml_H1));

    /* ************************** */
    /*  basis lift horizontal tail */
    /*  Table_11 Down wash angle (Epsilon_1) at HT(alpha,Tc)  */
    eml_H1 = ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork
      )->Table_11[(eml_iL - 1) + 19 * (eml_jL - 1)];
    eml_H3 = ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork
      )->Table_11[(eml_i - 1) + 19 * (eml_jL - 1)];
    eml_H1 += eml_p * (((D_Work_pa34model_dueca_8b *)
                        pa34model_dueca_8b_rtM->Work.dwork)->Table_11[(eml_iL -
      1) + 19 * (eml_j - 1)] - eml_H1);
    eml_r = eml_H1 + eml_delta_i * ((eml_H3 + eml_p *
      (((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
       ->Table_11[(eml_i - 1) + 19 * (eml_j - 1)] - eml_H3)) - eml_H1);
    eml_q = eml_r;

    /*  De aoa horizontal tail in radians; 19/3/2014 - wordt plus */
    eml_z = eml_alpha - (eml_r + eml_Epsilon_2);

    /* De ungecorrigeerde lift v.d. horizontal tail  */
    /*  De waarde van CL_HT(de) is nog geschat op (1/3) van CL_HT(alpha)!!!!): */
    /*  Verhoogd van 0.2730 naar 0.35; */
    /* * */
    /*  schatting verhoogd naar 50% */
    /* CL_HT=alpha_h*0.8191 + de*0.4085;%* */
    /*  Table 10; Correctie factor delta q_bar HT(alpha,Tc) */
    eml_H1 = ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork
      )->Table_10[(eml_iL - 1) + 19 * (eml_jL - 1)];
    eml_H3 = ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork
      )->Table_10[(eml_i - 1) + 19 * (eml_jL - 1)];
    eml_H1 += eml_p * (((D_Work_pa34model_dueca_8b *)
                        pa34model_dueca_8b_rtM->Work.dwork)->Table_10[(eml_iL -
      1) + 19 * (eml_j - 1)] - eml_H1);
    eml_r = eml_H1 + eml_delta_i * ((eml_H3 + eml_p *
      (((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
       ->Table_10[(eml_i - 1) + 19 * (eml_j - 1)] - eml_H3)) - eml_H1);

    /*  De gecorrigeerde lift horizontal tail */
    /* ********************* */
    eml_df = (eml_z * 0.8191 + eml_de * 0.35) * (1.0 + eml_r);

    /* ********************* */
    /*   CL_q(Alpha,Tc)  Table 13 */
    eml_H1 = ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork
      )->Table_13[(eml_iL - 1) + 19 * (eml_jL - 1)];
    eml_H3 = ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork
      )->Table_13[(eml_i - 1) + 19 * (eml_jL - 1)];
    eml_H1 += eml_p * (((D_Work_pa34model_dueca_8b *)
                        pa34model_dueca_8b_rtM->Work.dwork)->Table_13[(eml_iL -
      1) + 19 * (eml_j - 1)] - eml_H1);

    /*  CL_q corrigeren qc/v is vereist ipv qc/2V */
    /* ***************************************************** */
    eml_CL_q = (eml_H1 + eml_delta_i * ((eml_H3 + eml_p *
      (((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
       ->Table_13[(eml_i - 1) + 19 * (eml_j - 1)] - eml_H3)) - eml_H1)) * eml_qc;

    /* * */
    /* ***************************************************** */
    /*  effect alpha-dot op CL Table 14 (alpha,Tc) */
    eml_H1 = ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork
      )->Table_14[(eml_iL - 1) + 19 * (eml_jL - 1)];
    eml_H3 = ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork
      )->Table_14[(eml_i - 1) + 19 * (eml_jL - 1)];
    eml_H1 += eml_p * (((D_Work_pa34model_dueca_8b *)
                        pa34model_dueca_8b_rtM->Work.dwork)->Table_14[(eml_iL -
      1) + 19 * (eml_j - 1)] - eml_H1);

    /*  CL_alpha_dot corrigeren qc/v is vereist ipv qc/2V */
    /* ***************************************************** */
    eml_p = (eml_H1 + eml_delta_i * ((eml_H3 + eml_p *
               (((D_Work_pa34model_dueca_8b *)
                 pa34model_dueca_8b_rtM->Work.dwork)->Table_14[(eml_i - 1) + 19 *
                (eml_j - 1)] - eml_H3)) - eml_H1)) * eml_alpha_dot * eml_cbarw /
      eml_vtas;

    /* ***************************************************** */
    /*  Ground effect  */
    /*  Effectieve wingspan b_eff berekenen */
    /*  Op basis van CL_W(alpha,Tc=0) table 7 en CL_DF */
    eml_H1 = ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork
      )->Table_7[eml_iL + 18];
    eml_H3 = eml_H1 + eml_delta_i * (((D_Work_pa34model_dueca_8b *)
      pa34model_dueca_8b_rtM->Work.dwork)->Table_7[eml_iL + 18] - eml_H1);
    eml_z = (eml_H3 + eml_CL_DF) / (eml_H3 / 10.13 + eml_CL_DF / 7.0);

    /*  Wat kromme manier om de hoogte H weer terug krijgen */
    eml_v = imohohdjdjmocjmo_max(eml_hOverb, 0.0);
    if (eml_v < 15.0) {
      /*  De bijdrage van de wing eerst de GE factor */
      eml_K_GE_W = aiekgdbamoppphln_interp1(eml_dv29, eml_dv28, eml_v);

      /*  De factor 5.2566=CL_alpha wing in rad^-1 */
      eml_w = eml_CL_basic * eml_K_GE_W * 5.2566;

      /* De bijdrage van de tail, geen correctie voor hoogte tail (h_t=h_w!) */
      /*  eerst de reductie van de down wash angle */
      /* De  ground effect factor voor de tail */
      /*  CL_Alpha_HT=0.8191 rad^-1 */
      eml_z = eml_df * djeklfcbcjecopph_interp1(eml_dv31, eml_dv30, eml_v) +
        (eml_q - eml_Epsilon_2) * pow(eml_z, 2.0) / (pow(eml_z, 2.0) + 4.0 * pow
        (eml_v + eml_v, 2.0)) * 0.8191 * eml_r;
    } else {
      eml_K_GE_W = 0.0;

      /* K_GE_HT=0; */
      eml_w = 0.0;
      eml_z = 0.0;
    }

    if (eml_ii_0 == 1) {
      eml_CL_left = ((((eml_CL_basic + eml_df) + eml_CL_q) + eml_p) + eml_w) +
        eml_z;
      eml_CL_HT_left = eml_df;
      eml_CL_GE_HT_left = eml_z;
    }

    if (eml_ii_0 == 2) {
      eml_CL_right = ((((eml_CL_basic + eml_df) + eml_CL_q) + eml_p) + eml_w) +
        eml_z;
      eml_CL_HT_right = eml_df;
      eml_CL_GE_HT_right = eml_z;
    }
  }

  /* ***************************************** */
  eml_Epsilon_2 = (eml_CL_left + eml_CL_right) * eml_qbar * eml_Sw / 2.0;

  /* ****************************************** */
  /* *********************************************************** */
  /* CD */
  /*  Voor drag berekening gemiddelde Tc rechts en links */
  eml_Tc = (eml_Tc_l + eml_Tc_r) / 2.0;

  /*  Opnieuw bepalen indices Tc op average Tc  */
  for (eml_j = 2; (eml_Tc > ((D_Work_pa34model_dueca_8b *)
         pa34model_dueca_8b_rtM->Work.dwork)->Table_7[19 * (eml_j - 1)]) &&
       (eml_j < 4); eml_j++) {
  }

  if (eml_Tc > ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
      ->Table_7[57]) {
    eml_jL = 4;
    eml_j = 4;
    eml_p = 0.0;
  } else if (eml_j == 2) {
    eml_jL = 2;
    eml_j = 2;
    eml_p = 0.0;
  } else {
    eml_jL = eml_j - 1;
    eml_p = (eml_Tc - ((D_Work_pa34model_dueca_8b *)
                       pa34model_dueca_8b_rtM->Work.dwork)->Table_7[19 * (eml_jL
              - 1)]) / (((D_Work_pa34model_dueca_8b *)
                         pa34model_dueca_8b_rtM->Work.dwork)->Table_7[19 *
                        (eml_j - 1)] - ((D_Work_pa34model_dueca_8b *)
      pa34model_dueca_8b_rtM->Work.dwork)->Table_7[19 * (eml_jL - 1)]);
  }

  /* CD_basic(alpha,Tc)  Table 15 */
  eml_H1 = ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
    ->Table_15[(eml_iL - 1) + 19 * (eml_jL - 1)];
  eml_H3 = ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
    ->Table_15[(eml_i - 1) + 19 * (eml_jL - 1)];
  eml_H1 += eml_p * (((D_Work_pa34model_dueca_8b *)
                      pa34model_dueca_8b_rtM->Work.dwork)->Table_15[(eml_iL - 1)
                     + 19 * (eml_j - 1)] - eml_H1);
  eml_z = eml_H1 + eml_delta_i * ((eml_H3 + eml_p * (((D_Work_pa34model_dueca_8b
    *) pa34model_dueca_8b_rtM->Work.dwork)->Table_15[(eml_i - 1) + 19 * (eml_j -
    1)] - eml_H3)) - eml_H1);

  /*  CD_flaps(alpha,flaps) Table 16 */
  eml_H1 = ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
    ->Table_16[(eml_iL - 1) + 19 * (eml_kL - 1)];
  eml_H3 = ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
    ->Table_16[(eml_i - 1) + 19 * (eml_kL - 1)];
  eml_H1 += eml_delta_k * (((D_Work_pa34model_dueca_8b *)
    pa34model_dueca_8b_rtM->Work.dwork)->Table_16[(eml_iL - 1) + 19 * (eml_k - 1)]
    - eml_H1);
  eml_v = eml_H1 + eml_delta_i * ((eml_H3 + eml_delta_k *
    (((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
     ->Table_16[(eml_i - 1) + 19 * (eml_k - 1)] - eml_H3)) - eml_H1);

  /*  Effect van thrust op flaps table 9(alpha,Tc) */
  eml_H1 = ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
    ->Table_9[(eml_iL - 1) + 19 * (eml_jL - 1)];
  eml_H3 = ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
    ->Table_9[(eml_i - 1) + 19 * (eml_jL - 1)];
  eml_H1 += eml_p * (((D_Work_pa34model_dueca_8b *)
                      pa34model_dueca_8b_rtM->Work.dwork)->Table_9[(eml_iL - 1)
                     + 19 * (eml_j - 1)] - eml_H1);
  eml_v *= eml_H1 + eml_delta_i * ((eml_H3 + eml_p *
    (((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)->
     Table_9[(eml_i - 1) + 19 * (eml_j - 1)] - eml_H3)) - eml_H1);

  /*  Ground effect */
  /*  Drag of gear (6.62 =Sw/Sprop) is d_q effect on gear table 17(df) */
  eml_H1 = ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
    ->Table_17[eml_kL - 1];

  /*  Drag due sideslip and rudder deflection */
  /*  Feather drag not included */
  /*  Resultaat */
  /* ************************************************* */
  eml_CL_q = ((((eml_z + eml_v) + (-pow(eml_CL_basic, 2.0)) * eml_K_GE_W) +
               ((eml_H1 + eml_delta_k * (((D_Work_pa34model_dueca_8b *)
    pa34model_dueca_8b_rtM->Work.dwork)->Table_17[eml_k - 1] - eml_H1)) +
                0.002587 * eml_Tc * 6.62) * eml_gear) + (0.598 * pow(eml_beta,
    2.0) + 0.01056 * pow(eml_beta - eml_dr, 2.0))) * eml_qbar * eml_Sw;

  /* ************************************************************************* */
  /* CY  */
  /* CY_beta table 24(Tc) */
  /*  tafel fout hersteld */
  eml_H1 = ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
    ->Table_24[1 + ((eml_jL - 1) << 1)];
  eml_z = (eml_H1 + eml_p * (((D_Work_pa34model_dueca_8b *)
             pa34model_dueca_8b_rtM->Work.dwork)->Table_24[1 + ((eml_j - 1) << 1)]
            - eml_H1)) * eml_beta;

  /* CY_r table 27(alpha) */
  eml_H1 = ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
    ->Table_27a[eml_iL + 18];
  eml_v = (eml_H1 + eml_delta_i * (((D_Work_pa34model_dueca_8b *)
             pa34model_dueca_8b_rtM->Work.dwork)->Table_27a[eml_i + 18] - eml_H1))
    * eml_rb;

  /* CY_p table 28(alpha) */
  eml_H1 = ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
    ->Table_28a[eml_iL + 18];

  /* CY_dr table(31) */
  /* ******************************************* */
  eml_CL_DF = (((eml_z + eml_v) + (eml_H1 + eml_delta_i *
    (((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
     ->Table_28a[eml_i + 18] - eml_H1)) * eml_pb) + 0.13905 * eml_dr) * eml_qbar
    * eml_Sw;

  /* ******************************************* */
  /* ************************************************************************** */
  /* Cl */
  /*  De roll due to thrust verschil   */
  /*  Cl_beta Table 25 (alpha) */
  eml_H1 = ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
    ->Table_25[eml_iL + 18];

  /*  Correctie van 0.6 cfm manual is verschil met DATCOM */
  /*  Maakt weining verschil in simulatie */
  eml_z = (eml_H1 + eml_delta_i * (((D_Work_pa34model_dueca_8b *)
             pa34model_dueca_8b_rtM->Work.dwork)->Table_25[eml_i + 18] - eml_H1))
    * eml_beta;

  /* Cl_p Table 28b (alpha) */
  eml_H1 = ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
    ->Table_28b[eml_iL + 18];
  eml_v = (eml_H1 + eml_delta_i * (((D_Work_pa34model_dueca_8b *)
             pa34model_dueca_8b_rtM->Work.dwork)->Table_28b[eml_i + 18] - eml_H1))
    * eml_pb;

  /* Cl_r Table 27b (alpha) */
  eml_H1 = ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
    ->Table_27b[eml_iL + 18];
  eml_w = (eml_H1 + eml_delta_i * (((D_Work_pa34model_dueca_8b *)
             pa34model_dueca_8b_rtM->Work.dwork)->Table_27b[eml_i + 18] - eml_H1))
    * eml_rb;

  /*  Cl_dr Table 32a(alpha) */
  eml_H1 = ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
    ->Table_32a[eml_iL + 18];

  /*  Cl_da Table 29(|da|)  */
  /* ************************************************************************* */
  eml_df = (((((0.5 * (eml_CL_left - eml_CL_right) * 0.32 + eml_z) + eml_v) +
              eml_w) + (eml_H1 + eml_delta_i * (((D_Work_pa34model_dueca_8b *)
    pa34model_dueca_8b_rtM->Work.dwork)->Table_32a[eml_i + 18] - eml_H1)) *
             eml_dr * ((BlockIO_pa34model_dueca_8b *)
                       pa34model_dueca_8b_rtM->ModelData.blockIO)->Ef_uit[1]) +
            ((BlockIO_pa34model_dueca_8b *)
             pa34model_dueca_8b_rtM->ModelData.blockIO)->Ef_uit[0] *
            glfkekfchdjmlngl_interp1(eml_dv33, eml_dv32, aaaajecbeknghdbi_min
             (0.9599, fabs(eml_da))) * eml_da) * eml_qbar * eml_Sw * eml_bw;

  /* ************************************************************************ */
  /* ************************************************************************ */
  /* Cm */
  /*  Cm_wb(alpha,Tc) table 20 */
  eml_H1 = ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
    ->Table_20[(eml_iL - 1) + 19 * (eml_jL - 1)];
  eml_H3 = ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
    ->Table_20[(eml_i - 1) + 19 * (eml_jL - 1)];
  eml_H1 += eml_p * (((D_Work_pa34model_dueca_8b *)
                      pa34model_dueca_8b_rtM->Work.dwork)->Table_20[(eml_iL - 1)
                     + 19 * (eml_j - 1)] - eml_H1);
  eml_v = eml_H1 + eml_delta_i * ((eml_H3 + eml_p * (((D_Work_pa34model_dueca_8b
    *) pa34model_dueca_8b_rtM->Work.dwork)->Table_20[(eml_i - 1) + 19 * (eml_j -
    1)] - eml_H3)) - eml_H1);

  /*  Cm_wb_df(alpha,df) table 21 */
  eml_H1 = ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
    ->Table_21[(eml_iL - 1) + 19 * (eml_kL - 1)];
  eml_H3 = ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
    ->Table_21[(eml_i - 1) + 19 * (eml_kL - 1)];
  eml_H1 += eml_delta_k * (((D_Work_pa34model_dueca_8b *)
    pa34model_dueca_8b_rtM->Work.dwork)->Table_21[(eml_iL - 1) + 19 * (eml_k - 1)]
    - eml_H1);
  eml_z = eml_H1 + eml_delta_i * ((eml_H3 + eml_delta_k *
    (((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
     ->Table_21[(eml_i - 1) + 19 * (eml_k - 1)] - eml_H3)) - eml_H1);

  /*  Effect of dq op flaps (alpha,Tc) table 9 */
  eml_H1 = ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
    ->Table_9[(eml_iL - 1) + 19 * (eml_jL - 1)];
  eml_H3 = ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
    ->Table_9[(eml_i - 1) + 19 * (eml_jL - 1)];
  eml_H1 += eml_p * (((D_Work_pa34model_dueca_8b *)
                      pa34model_dueca_8b_rtM->Work.dwork)->Table_9[(eml_iL - 1)
                     + 19 * (eml_j - 1)] - eml_H1);
  eml_v += eml_z * (eml_H1 + eml_delta_i * ((eml_H3 + eml_p *
    (((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)->
     Table_9[(eml_i - 1) + 19 * (eml_j - 1)] - eml_H3)) - eml_H1));

  /* Cm_q(alpha,Tc) Table 22 */
  eml_H1 = ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
    ->Table_22[(eml_iL - 1) + 19 * (eml_jL - 1)];
  eml_H3 = ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
    ->Table_22[(eml_i - 1) + 19 * (eml_jL - 1)];
  eml_H1 += eml_p * (((D_Work_pa34model_dueca_8b *)
                      pa34model_dueca_8b_rtM->Work.dwork)->Table_22[(eml_iL - 1)
                     + 19 * (eml_j - 1)] - eml_H1);
  eml_z = (eml_H1 + eml_delta_i * ((eml_H3 + eml_p *
             (((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork
              )->Table_22[(eml_i - 1) + 19 * (eml_j - 1)] - eml_H3)) - eml_H1)) *
    eml_qc;

  /* Cm_alpha_dot(alpha,Tc) Table 23 */
  eml_H1 = ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
    ->Table_23[(eml_iL - 1) + 19 * (eml_jL - 1)];
  eml_H3 = ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
    ->Table_23[(eml_i - 1) + 19 * (eml_jL - 1)];
  eml_H1 += eml_p * (((D_Work_pa34model_dueca_8b *)
                      pa34model_dueca_8b_rtM->Work.dwork)->Table_23[(eml_iL - 1)
                     + 19 * (eml_j - 1)] - eml_H1);

  /* ******************************************************************* */
  eml_q = ((((eml_v + (-((eml_CL_HT_left + eml_CL_HT_right) / 2.0)) *
              3.0559006211180120E+000) + (-((eml_CL_GE_HT_left +
    eml_CL_GE_HT_right) / 2.0)) * 3.0559006211180120E+000) + eml_z) + (eml_H1 +
            eml_delta_i * ((eml_H3 + eml_p * (((D_Work_pa34model_dueca_8b *)
    pa34model_dueca_8b_rtM->Work.dwork)->Table_23[(eml_i - 1) + 19 * (eml_j - 1)]
    - eml_H3)) - eml_H1)) * eml_alpha_dot * eml_cbarw / eml_vtas) * eml_qbar *
    eml_Sw * eml_cbarw;

  /* ******************************************************************* */
  /* ******************************************************************* */
  /* Cn */
  /*  Bepalen  indices en fractie van da; */
  /* Cn_beta(alpha,Tc) tabel 26 */
  eml_H1 = ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
    ->Table_26[(eml_iL - 1) + 19 * (eml_jL - 1)];
  eml_H3 = ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
    ->Table_26[(eml_i - 1) + 19 * (eml_jL - 1)];
  eml_H1 += eml_p * (((D_Work_pa34model_dueca_8b *)
                      pa34model_dueca_8b_rtM->Work.dwork)->Table_26[(eml_iL - 1)
                     + 19 * (eml_j - 1)] - eml_H1);

  /*  Probere om ook Cb beta met 0.6 te vermenigvuldigen */
  /*  Gevaarlijk ivm rudder authority */
  eml_r = (eml_H1 + eml_delta_i * ((eml_H3 + eml_p *
             (((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork
              )->Table_26[(eml_i - 1) + 19 * (eml_j - 1)] - eml_H3)) - eml_H1)) *
    eml_beta;

  /* Cn_p(alpha) tabel 28c */
  eml_H1 = ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
    ->Table_28c[eml_iL + 18];
  eml_p = (eml_H1 + eml_delta_i * (((D_Work_pa34model_dueca_8b *)
             pa34model_dueca_8b_rtM->Work.dwork)->Table_28c[eml_i + 18] - eml_H1))
    * eml_pb;

  /* Cn_r(alpha) tabel 27c */
  eml_H1 = ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
    ->Table_27c[eml_iL + 18];
  eml_w = (eml_H1 + eml_delta_i * (((D_Work_pa34model_dueca_8b *)
             pa34model_dueca_8b_rtM->Work.dwork)->Table_27c[eml_i + 18] - eml_H1))
    * eml_rb;

  /* Cn_dr(alpha) tabel 32b */
  eml_H1 = ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
    ->Table_32b[eml_iL + 18];
  eml_v = (eml_H1 + eml_delta_i * (((D_Work_pa34model_dueca_8b *)
             pa34model_dueca_8b_rtM->Work.dwork)->Table_32b[eml_i + 18] - eml_H1))
    * eml_dr * ((BlockIO_pa34model_dueca_8b *)
                pa34model_dueca_8b_rtM->ModelData.blockIO)->Ef_uit[1];

  /* Cn_da(alpha,|da|) table 30; */
  eml_k = 2;
  eml_z = fabs(eml_da);
  while ((eml_z > ((D_Work_pa34model_dueca_8b *)
                   pa34model_dueca_8b_rtM->Work.dwork)->Table_30[19 * (eml_k - 1)])
         && (eml_k < 5)) {
    eml_k++;
  }

  if (eml_z > ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork
      )->Table_30[76]) {
    eml_kL = 5;
    eml_k = 5;
    eml_delta_k = 0.0;
  } else if (eml_k == 2) {
    eml_kL = 2;
    eml_k = 2;
    eml_delta_k = 0.0;
  } else {
    eml_kL = eml_k - 1;
    eml_delta_k = (eml_z - ((D_Work_pa34model_dueca_8b *)
      pa34model_dueca_8b_rtM->Work.dwork)->Table_30[19 * (eml_kL - 1)]) /
      (((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
       ->Table_30[19 * (eml_k - 1)] - ((D_Work_pa34model_dueca_8b *)
        pa34model_dueca_8b_rtM->Work.dwork)->Table_30[19 * (eml_kL - 1)]);
  }

  eml_H1 = ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
    ->Table_30[(eml_iL - 1) + 19 * (eml_kL - 1)];
  eml_H3 = ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
    ->Table_30[(eml_i - 1) + 19 * (eml_kL - 1)];
  eml_H1 += eml_delta_k * (((D_Work_pa34model_dueca_8b *)
    pa34model_dueca_8b_rtM->Work.dwork)->Table_30[(eml_iL - 1) + 19 * (eml_k - 1)]
    - eml_H1);
  eml_z = ((((eml_r + eml_p) + eml_w * 2.0) + eml_v) + (eml_H1 + eml_delta_i *
            ((eml_H3 + eml_delta_k * (((D_Work_pa34model_dueca_8b *)
    pa34model_dueca_8b_rtM->Work.dwork)->Table_30[(eml_i - 1) + 19 * (eml_k - 1)]
    - eml_H3)) - eml_H1)) * eml_da * ((BlockIO_pa34model_dueca_8b *)
            pa34model_dueca_8b_rtM->ModelData.blockIO)->Ef_uit[0]) * eml_qbar *
    eml_Sw * eml_bw;
  if (fabs(eml_u) < 1.0) {
    eml_CL_q = 0.0;
    eml_Epsilon_2 = 0.0;
  }

  /*  Naar body axis */
  eml_p = (-eml_CL_q) * cos(eml_alpha) + eml_Epsilon_2 * sin(eml_alpha);
  eml_v = (-eml_Epsilon_2) * cos(eml_alpha) - eml_CL_q * sin(eml_alpha);
  eml_w = eml_df * cos(eml_alpha) - eml_z * sin(eml_alpha);
  eml_z = eml_df * sin(eml_alpha) + eml_z * cos(eml_alpha);
  if ((eml_landed == 1) && (eml_u < 0.0)) {
    /*  Voorkomen nuisance waarden bij tailwind op de grond */
    /*  tailwind !!! */
    eml_p = 0.0;
    eml_CL_DF = 0.0;
    eml_v = 0.0;
    eml_w = 0.0;
    eml_q = 0.0;
    eml_z = 0.0;
  }

  /* ************************************************* */
  for (eml_i = 0; eml_i < 6; eml_i++) {
    ((BlockIO_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->ModelData.blockIO)
      ->FMAb[eml_i] = 0.0;
  }

  ((BlockIO_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->ModelData.blockIO)
    ->FMAb[0] = eml_p;
  ((BlockIO_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->ModelData.blockIO)
    ->FMAb[1] = eml_CL_DF;
  ((BlockIO_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->ModelData.blockIO)
    ->FMAb[2] = eml_v;
  ((BlockIO_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->ModelData.blockIO)
    ->FMAb[3] = eml_w;
  ((BlockIO_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->ModelData.blockIO)
    ->FMAb[4] = eml_q;
  ((BlockIO_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->ModelData.blockIO)
    ->FMAb[5] = eml_z;

  /* FMAb=[CX;CY;CZ;Clb;Cm;Cnb]; */
}

/* Shared Utility Functions */
real_T cbaabiecohlncbaa_atan2(real_T eml_y, real_T eml_x)
{
  real_T eml_r;
  if ((!((boolean_T)rtIsNaN(eml_x))) && (!((boolean_T)rtIsNaN(eml_y)))) {
    if (((boolean_T)rtIsInf(eml_y)) && ((boolean_T)rtIsInf(eml_x))) {
      if (eml_x > 0.0) {
        eml_r = 7.8539816339744828E-001;
      } else {
        eml_r = 2.3561944901923448E+000;
      }

      if (eml_y < 0.0) {
        return -eml_r;
      }
    } else if (eml_x == 0.0) {
      if (eml_y > 0.0) {
        return 1.5707963267948966E+000;
      } else if (eml_y < 0.0) {
        return -1.5707963267948966E+000;
      } else {
        return 0.0;
      }
    } else {
      return rt_atan2(eml_y, eml_x);
    }
  } else {
    return rtNaN;
  }

  return eml_r;
}

real_T imohohdjdjmocjmo_max(real_T eml_x, real_T eml_y)
{
  if ((!(eml_x >= eml_y)) && (!((boolean_T)rtIsNaN(eml_y)))) {
    return eml_y;
  } else {
    return eml_x;
  }
}

real_T aiekgdbamoppphln_interp1(real_T eml_par1[9], real_T eml_par2[9], real_T
  eml_par3)
{
  real_T eml_yi;
  int32_T eml_k;
  real_T eml_x[9];
  real_T eml_d0;
  real_T eml_yv[9];
  boolean_T eml_x_0[9];
  real_T eml_y[9];
  boolean_T eml_y_0;
  int32_T eml_exitg1;
  boolean_T eml_b0;
  int32_T eml_low_ip1;
  int32_T eml_high_i;
  int32_T eml_mid_i;
  eml_yi = rtNaN;
  for (eml_k = 0; eml_k < 9; eml_k++) {
    eml_x[eml_k] = eml_par1[eml_k];
    eml_d0 = eml_par2[eml_k];
    eml_yv[eml_k] = eml_d0;
    eml_x_0[eml_k] = (boolean_T)rtIsNaN(eml_par1[eml_k]);
    eml_y[eml_k] = eml_d0;
  }

  eml_y_0 = false;
  eml_k = 1;
  do {
    eml_exitg1 = 0U;
    if (eml_k <= 9) {
      if (eml_x_0[eml_k - 1] == 0) {
        eml_b0 = true;
      } else {
        eml_b0 = false;
      }

      if (!eml_b0) {
        eml_y_0 = true;
        eml_exitg1 = 1U;
      } else {
        eml_k++;
      }
    } else {
      eml_exitg1 = 1U;
    }
  } while (eml_exitg1 == 0U);

  if (eml_y_0) {
    return rtNaN;
  } else {
    if (eml_par1[1] < eml_par1[0]) {
      for (eml_k = 0; eml_k < 9; eml_k++) {
        eml_x[eml_k] = eml_par1[8 + -1 * eml_k];
        eml_yv[eml_k] = eml_y[8 + -1 * eml_k];
      }
    }

    eml_k = 0;
    if ((!(eml_par3 > eml_x[8])) && (!(eml_par3 < eml_x[0]))) {
      eml_k = 1;
      eml_low_ip1 = 2;
      eml_high_i = 9;
      while ((uint32_T)eml_high_i > (uint32_T)eml_low_ip1) {
        eml_mid_i = (int32_T)((uint32_T)(eml_k + eml_high_i) >> 1);
        if (eml_par3 >= eml_x[eml_mid_i - 1]) {
          eml_k = eml_mid_i;
          eml_low_ip1 = eml_mid_i + 1;
        } else {
          eml_high_i = eml_mid_i;
        }
      }
    }

    if (eml_k > 0) {
      eml_low_ip1 = eml_k + 1;
      return eml_yv[eml_k - 1] + (eml_par3 - eml_x[eml_k - 1]) /
        (eml_x[eml_low_ip1 - 1] - eml_x[eml_k - 1]) * (eml_yv[eml_low_ip1 - 1] -
        eml_yv[eml_k - 1]);
    }
  }

  return eml_yi;
}

real_T djeklfcbcjecopph_interp1(real_T eml_par1[6], real_T eml_par2[6], real_T
  eml_par3)
{
  real_T eml_yi;
  int32_T eml_k;
  real_T eml_x[6];
  real_T eml_d1;
  real_T eml_yv[6];
  boolean_T eml_x_0[6];
  real_T eml_y[6];
  boolean_T eml_y_0;
  int32_T eml_exitg1;
  boolean_T eml_b1;
  int32_T eml_low_ip1;
  int32_T eml_high_i;
  int32_T eml_mid_i;
  eml_yi = rtNaN;
  for (eml_k = 0; eml_k < 6; eml_k++) {
    eml_x[eml_k] = eml_par1[eml_k];
    eml_d1 = eml_par2[eml_k];
    eml_yv[eml_k] = eml_d1;
    eml_x_0[eml_k] = (boolean_T)rtIsNaN(eml_par1[eml_k]);
    eml_y[eml_k] = eml_d1;
  }

  eml_y_0 = false;
  eml_k = 1;
  do {
    eml_exitg1 = 0U;
    if (eml_k <= 6) {
      if (eml_x_0[eml_k - 1] == 0) {
        eml_b1 = true;
      } else {
        eml_b1 = false;
      }

      if (!eml_b1) {
        eml_y_0 = true;
        eml_exitg1 = 1U;
      } else {
        eml_k++;
      }
    } else {
      eml_exitg1 = 1U;
    }
  } while (eml_exitg1 == 0U);

  if (eml_y_0) {
    return rtNaN;
  } else {
    if (eml_par1[1] < eml_par1[0]) {
      for (eml_k = 0; eml_k < 6; eml_k++) {
        eml_x[eml_k] = eml_par1[5 + -1 * eml_k];
        eml_yv[eml_k] = eml_y[5 + -1 * eml_k];
      }
    }

    eml_k = 0;
    if ((!(eml_par3 > eml_x[5])) && (!(eml_par3 < eml_x[0]))) {
      eml_k = 1;
      eml_low_ip1 = 2;
      eml_high_i = 6;
      while ((uint32_T)eml_high_i > (uint32_T)eml_low_ip1) {
        eml_mid_i = (int32_T)((uint32_T)(eml_k + eml_high_i) >> 1);
        if (eml_par3 >= eml_x[eml_mid_i - 1]) {
          eml_k = eml_mid_i;
          eml_low_ip1 = eml_mid_i + 1;
        } else {
          eml_high_i = eml_mid_i;
        }
      }
    }

    if (eml_k > 0) {
      eml_low_ip1 = eml_k + 1;
      return eml_yv[eml_k - 1] + (eml_par3 - eml_x[eml_k - 1]) /
        (eml_x[eml_low_ip1 - 1] - eml_x[eml_k - 1]) * (eml_yv[eml_low_ip1 - 1] -
        eml_yv[eml_k - 1]);
    }
  }

  return eml_yi;
}

real_T aaaajecbeknghdbi_min(real_T eml_x, real_T eml_y)
{
  if ((!(eml_x <= eml_y)) && (!((boolean_T)rtIsNaN(eml_y)))) {
    return eml_y;
  } else {
    return eml_x;
  }
}

real_T glfkekfchdjmlngl_interp1(real_T eml_par1[4], real_T eml_par2[4], real_T
  eml_par3)
{
  real_T eml_yi;
  int32_T eml_k;
  real_T eml_x[4];
  real_T eml_d2;
  real_T eml_yv[4];
  boolean_T eml_x_0[4];
  real_T eml_y[4];
  boolean_T eml_y_0;
  int32_T eml_exitg1;
  boolean_T eml_b2;
  int32_T eml_low_ip1;
  int32_T eml_high_i;
  int32_T eml_mid_i;
  eml_yi = rtNaN;
  for (eml_k = 0; eml_k < 4; eml_k++) {
    eml_x[eml_k] = eml_par1[eml_k];
    eml_d2 = eml_par2[eml_k];
    eml_yv[eml_k] = eml_d2;
    eml_x_0[eml_k] = (boolean_T)rtIsNaN(eml_par1[eml_k]);
    eml_y[eml_k] = eml_d2;
  }

  eml_y_0 = false;
  eml_k = 1;
  do {
    eml_exitg1 = 0U;
    if (eml_k <= 4) {
      if (eml_x_0[eml_k - 1] == 0) {
        eml_b2 = true;
      } else {
        eml_b2 = false;
      }

      if (!eml_b2) {
        eml_y_0 = true;
        eml_exitg1 = 1U;
      } else {
        eml_k++;
      }
    } else {
      eml_exitg1 = 1U;
    }
  } while (eml_exitg1 == 0U);

  if (eml_y_0) {
    return rtNaN;
  } else {
    if (eml_par1[1] < eml_par1[0]) {
      for (eml_k = 0; eml_k < 4; eml_k++) {
        eml_x[eml_k] = eml_par1[3 + -1 * eml_k];
        eml_yv[eml_k] = eml_y[3 + -1 * eml_k];
      }
    }

    eml_k = 0;
    if ((!(eml_par3 > eml_x[3])) && (!(eml_par3 < eml_x[0]))) {
      eml_k = 1;
      eml_low_ip1 = 2;
      eml_high_i = 4;
      while ((uint32_T)eml_high_i > (uint32_T)eml_low_ip1) {
        eml_mid_i = (int32_T)((uint32_T)(eml_k + eml_high_i) >> 1);
        if (eml_par3 >= eml_x[eml_mid_i - 1]) {
          eml_k = eml_mid_i;
          eml_low_ip1 = eml_mid_i + 1;
        } else {
          eml_high_i = eml_mid_i;
        }
      }
    }

    if (eml_k > 0) {
      eml_low_ip1 = eml_k + 1;
      return eml_yv[eml_k - 1] + (eml_par3 - eml_x[eml_k - 1]) /
        (eml_x[eml_low_ip1 - 1] - eml_x[eml_k - 1]) * (eml_yv[eml_low_ip1 - 1] -
        eml_yv[eml_k - 1]);
    }
  }

  return eml_yi;
}

/* Initial conditions for atomic system: '<S6>/AERO FORCES EN MOMENTS' */
void pa34mo_AEROFORCESENMOMENTS_Init(rtModel_pa34model_dueca_8b
  *pa34model_dueca_8b_rtM)
{
  /* Initialize code for chart: '<S6>/AERO FORCES EN MOMENTS' */
  {
    int32_T eml_i0;
    int32_T eml_i1;
    static real_T eml_dv0[76] = { 0.0, -0.1396, -0.1047, -0.0803, -0.0698,
      -0.0349, 0.0, 0.0349, 0.0698, 0.1047, 0.1396, 0.1606, 0.1763, 0.2025,
      0.2199, 0.2374, 0.2426, 0.2618, 0.2793, 0.0, -0.325, -0.1414, -0.0129,
      0.0422, 0.2258, 0.4095, 0.5932, 0.777, 0.9609, 1.1352, 1.2284, 1.2906,
      1.3811, 1.4265, 1.451, 1.4421, 1.3528, 1.2036, 0.2, -0.325, -0.1234,
      0.0175, 0.0779, 0.2787, 0.479, 0.6784, 0.8767, 1.0738, 1.2579, 1.378,
      1.4699, 1.5698, 1.6114, 1.638, 1.6424, 1.5782, 1.4449, 0.44, -0.315,
      -0.098, 0.0536, 0.1185, 0.3342, 0.5488, 0.762, 0.9734, 1.1827, 1.3764,
      1.4947, 1.5628, 1.6515, 1.699, 1.7265, 1.7281, 1.6661, 1.5487 };

    static real_T eml_dv1[95] = { 0.0, -0.1396, -0.1047, -0.0803, -0.0698,
      -0.0349, 0.0, 0.0349, 0.0698, 0.1047, 0.1396, 0.1606, 0.1763, 0.2025,
      0.2199, 0.2374, 0.2426, 0.2618, 0.2793, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.1745, 0.257,
      0.257, 0.257, 0.257, 0.257, 0.257, 0.257, 0.257, 0.2491, 0.225, 0.207,
      0.193, 0.149, 0.065, -0.044, -0.07, -0.09, 0.0, 0.4363, 0.4825, 0.4825,
      0.4825, 0.4825, 0.4825, 0.4825, 0.4825, 0.4779, 0.4491, 0.398, 0.357,
      0.323, 0.15, 0.015, -0.119, -0.14, -0.12, -0.02, 0.6981, 0.616, 0.616,
      0.616, 0.616, 0.616, 0.616, 0.616, 0.5979, 0.5591, 0.495, 0.432, 0.33,
      0.11, -0.035, -0.149, -0.17, -0.12, -0.02 };

    static real_T eml_dv2[76] = { 0.0, -0.1396, -0.1047, -0.0803, -0.0698,
      -0.0349, 0.0, 0.0349, 0.0698, 0.1047, 0.1396, 0.1606, 0.1763, 0.2025,
      0.2199, 0.2374, 0.2426, 0.2618, 0.2793, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
      1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.2, 1.3667,
      1.365, 1.363, 1.362, 1.3576, 1.3518, 1.3445, 1.3356, 1.325, 1.3125, 1.304,
      1.2971, 1.2844, 1.2751, 1.265, 1.2618, 1.2494, 1.237, 0.44, 1.7383, 1.7342,
      1.73, 1.7279, 1.7194, 1.7085, 1.6952, 1.6794, 1.6607, 1.6391, 1.6245,
      1.6128, 1.5915, 1.576, 1.5594, 1.5541, 1.534, 1.5142 };

    static real_T eml_dv3[76] = { 0.0, -0.1396, -0.1047, -0.0803, -0.0698,
      -0.0349, 0.0, 0.0349, 0.0698, 0.1047, 0.1396, 0.1606, 0.1763, 0.2025,
      0.2199, 0.2374, 0.2426, 0.2618, 0.2793, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.2, 0.2,
      0.2146, 0.2189, 0.22, 0.2202, 0.2165, 0.2098, 0.2, 0.1865, 0.1698, 0.158,
      0.1484, 0.131, 0.119, 0.1065, 0.1027, 0.089, 0.0715, 0.44, 0.346, 0.35,
      0.355, 0.356, 0.359, 0.3588, 0.356, 0.35, 0.341, 0.329, 0.321, 0.3147,
      0.302, 0.2905, 0.2767, 0.272, 0.252, 0.24 };

    static real_T eml_dv4[76] = { 0.0, -0.1396, -0.1047, -0.0803, -0.0698,
      -0.0349, 0.0, 0.0349, 0.0698, 0.1047, 0.1396, 0.1606, 0.1763, 0.2025,
      0.2199, 0.2374, 0.2426, 0.2618, 0.2793, 0.0, -0.0364, -0.0151, 0.0, 0.0065,
      0.0285, 0.0513, 0.0736, 0.0951, 0.1163, 0.1371, 0.1494, 0.1586, 0.1736,
      0.1836, 0.1934, 0.1963, 0.2069, 0.2163, 0.2, -0.0539, -0.0215, 0.0024,
      0.0127, 0.0464, 0.079, 0.1085, 0.135, 0.16, 0.1836, 0.1972, 0.2072, 0.2237,
      0.235, 0.2464, 0.25, 0.2633, 0.2734, 0.44, -0.0626, -0.0258, 0.0006,
      0.0119, 0.0494, 0.0862, 0.1203, 0.1518, 0.1812, 0.2084, 0.2236, 0.2345,
      0.2517, 0.2628, 0.2737, 0.277, 0.2889, 0.2975 };

    static real_T eml_dv5[95] = { 0.0, -0.1396, -0.1047, -0.0803, -0.0698,
      -0.0349, 0.0, 0.0349, 0.0698, 0.1047, 0.1396, 0.1606, 0.1763, 0.2025,
      0.2199, 0.2374, 0.2426, 0.2618, 0.2793, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.1745, 0.0269,
      0.0274, 0.0278, 0.028, 0.0287, 0.0294, 0.03, 0.0301, 0.0294, 0.0275,
      0.0255, 0.0235, 0.019, 0.0151, 0.0104, 0.0088, 0.0021, -0.0051, 0.4363,
      0.0495, 0.051, 0.0513, 0.0514, 0.0519, 0.0529, 0.0541, 0.0547, 0.0534,
      0.0481, 0.0419, 0.0353, 0.0195, 0.0, 0.0, 0.0, 0.0, 0.0, 0.6981, 0.0624,
      0.0635, 0.064, 0.0642, 0.0651, 0.0665, 0.0677, 0.0676, 0.0645, 0.0559,
      0.0469, 0.0379, 0.0166, 0.0, 0.0, 0.0, 0.0, 0.0 };

    static real_T eml_dv6[76] = { 0.0, -0.1396, -0.1047, -0.0803, -0.0698,
      -0.0349, 0.0, 0.0349, 0.0698, 0.1047, 0.1396, 0.1606, 0.1763, 0.2025,
      0.2199, 0.2374, 0.2426, 0.2618, 0.2793, 0.0, 4.1058, 4.1058, 4.1058,
      4.1058, 4.1058, 4.1058, 4.1058, 4.1058, 4.1058, 4.1058, 4.1058, 4.1058,
      4.1058, 4.1058, 4.1058, 4.1058, 4.1058, 4.1058, 0.2, 4.6065, 4.643, 4.6538,
      4.6565, 4.657, 4.6478, 4.631, 4.6065, 4.5727, 4.5309, 4.5013, 4.4773,
      4.4337, 4.4037, 4.3724, 4.3629, 4.3286, 4.2848, 0.44, 4.9719, 4.9819,
      4.9944, 4.9969, 5.0045, 5.004, 4.9969, 4.9819, 4.9594, 4.9294, 4.9093,
      4.8936, 4.8618, 4.833, 4.7984, 4.7867, 4.7366, 4.7066 };

    static real_T eml_dv7[76] = { 0.0, -0.1396, -0.1047, -0.0803, -0.0698,
      -0.0349, 0.0, 0.0349, 0.0698, 0.1047, 0.1396, 0.1606, 0.1763, 0.2025,
      0.2199, 0.2374, 0.2426, 0.2618, 0.2793, 0.0, 2.1054, 2.1183, 2.1361,
      2.1433, 2.1813, 2.1919, 2.1495, 2.1102, 2.0842, 2.0572, 2.0406, 2.0279,
      2.0063, 1.9913, 1.9735, 1.9676, 1.9474, 1.9386, 0.2, 3.3617, 3.4903,
      3.5681, 3.5617, 3.4793, 3.2836, 3.0085, 2.7945, 2.6414, 2.5106, 2.4395,
      2.4013, 2.3855, 2.3976, 2.467, 2.4834, 2.3019, 2.1271, 0.44, 4.1283,
      4.1919, 4.2471, 4.244, 4.196, 4.0338, 3.7679, 3.5244, 3.2989, 3.0617,
      2.9132, 2.8111, 2.6817, 2.6168, 2.5658, 2.5537, 2.3117, 2.11 };

    static real_T eml_dv8[76] = { 0.0, -0.1396, -0.1047, -0.0803, -0.0698,
      -0.0349, 0.0, 0.0349, 0.0698, 0.1047, 0.1396, 0.1606, 0.1763, 0.2025,
      0.2199, 0.2374, 0.2426, 0.2618, 0.2793, 0.0, 0.032, 0.0271, 0.026, 0.0261,
      0.0289, 0.0355, 0.0458, 0.06, 0.078, 0.0999, 0.1148, 0.1269, 0.1487,
      0.1645, 0.1812, 0.1864, 0.2062, 0.2252, 0.2, 0.0338, 0.029, 0.0278, 0.0279,
      0.0307, 0.0372, 0.0476, 0.0617, 0.0797, 0.1014, 0.1163, 0.1284, 0.1502,
      0.1659, 0.1825, 0.1877, 0.2075, 0.2264, 0.44, 0.036, 0.0311, 0.03, 0.0301,
      0.0328, 0.0393, 0.0496, 0.0638, 0.0817, 0.1034, 0.1182, 0.1302, 0.152,
      0.1677, 0.1843, 0.1895, 0.2092, 0.2281 };

    static real_T eml_dv9[95] = { 0.0, -0.1396, -0.1047, -0.0803, -0.0698,
      -0.0349, 0.0, 0.0349, 0.0698, 0.1047, 0.1396, 0.1606, 0.1763, 0.2025,
      0.2199, 0.2374, 0.2426, 0.2618, 0.2793, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.1745, 0.0,
      0.0046, 0.0078, 0.0092, 0.0138, 0.0184, 0.023, 0.0276, 0.0321, 0.0367,
      0.0395, 0.0415, 0.045, 0.0473, 0.0496, 0.0502, 0.0528, 0.0551, 0.4363,
      0.0138, 0.0224, 0.0285, 0.031, 0.0396, 0.0483, 0.0569, 0.0655, 0.0741,
      0.0827, 0.0878, 0.0917, 0.0982, 0.1025, 0.1068, 0.1081, 0.1128, 0.1171,
      0.6981, 0.0395, 0.0504, 0.0581, 0.0614, 0.0724, 0.0834, 0.0944, 0.1054,
      0.1163, 0.1273, 0.1339, 0.1389, 0.1471, 0.1526, 0.1581, 0.1597, 0.1658,
      0.1713 };

    static real_T eml_dv10[5] = { 0.0, 0.008275, 0.008256, 0.008227, 0.008198 };

    static real_T eml_dv11[76] = { 0.0, -0.1396, -0.1047, -0.0803, -0.0698,
      -0.0349, 0.0, 0.0349, 0.0698, 0.1047, 0.1396, 0.1606, 0.1763, 0.2025,
      0.2199, 0.2374, 0.2426, 0.2618, 0.2793, 0.0, -0.083, -0.0788, -0.0766,
      -0.0758, -0.0741, -0.0748, -0.075, -0.0743, -0.0736, -0.0772, -0.0828,
      -0.0895, -0.1017, -0.1131, -0.1242, -0.129, -0.1435, -0.1601, 0.2, -0.0933,
      -0.0884, -0.0857, -0.0848, -0.0823, -0.0823, -0.0818, -0.0802, -0.0787,
      -0.0814, -0.0864, -0.0927, -0.1042, -0.1151, -0.1257, -0.1302, -0.1442,
      -0.1601, 0.44, -0.1044, -0.0991, -0.0961, -0.0949, -0.092, -0.0915,
      -0.0904, -0.0883, -0.0861, -0.0883, -0.0928, -0.0988, -0.1098, -0.1203,
      -0.1305, -0.135, -0.1485, -0.1641 };

    static real_T eml_dv12[95] = { 0.0, -0.1396, -0.1047, -0.0803, -0.0698,
      -0.0349, 0.0, 0.0349, 0.0698, 0.1047, 0.1396, 0.1606, 0.1763, 0.2025,
      0.2199, 0.2374, 0.2426, 0.2618, 0.2793, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.1745,
      -0.0758, -0.0758, -0.0758, -0.0758, -0.0758, -0.0758, -0.0758, -0.0758,
      -0.0758, -0.0758, -0.0758, -0.0758, -0.0758, -0.0758, -0.0758, -0.0758,
      -0.0758, -0.0758, 0.4363, -0.1271, -0.1271, -0.1271, -0.1271, -0.1271,
      -0.1271, -0.1271, -0.1271, -0.1271, -0.1271, -0.1271, -0.1271, -0.1271,
      -0.1271, -0.1271, -0.1271, -0.1271, -0.1271, 0.6981, -0.1474, -0.1474,
      -0.1474, -0.1474, -0.1474, -0.1474, -0.1474, -0.1474, -0.1474, -0.1474,
      -0.1474, -0.1474, -0.1474, -0.1474, -0.1474, -0.1474, -0.1474, -0.1474 };

    static real_T eml_dv13[76] = { 0.0, -0.1396, -0.1047, -0.0803, -0.0698,
      -0.0349, 0.0, 0.0349, 0.0698, 0.1047, 0.1396, 0.1606, 0.1763, 0.2025,
      0.2199, 0.2374, 0.2426, 0.2618, 0.2793, 0.0, -4.669, -4.7085, -4.7629,
      -4.7849, -4.9011, -4.9333, -4.8037, -4.6837, -4.6041, -4.5218, -4.4709,
      -4.4321, -4.3662, -4.3202, -4.2659, -4.2479, -4.1861, -4.1592, 0.2, -8.508,
      -8.9011, -9.139, -9.1193, -8.8674, -8.2695, -7.4287, -6.7748, -6.3068,
      -5.9072, -5.69, -5.5731, -5.5249, -5.5619, -5.7739, -5.8241, -5.2696,
      -4.7353, 0.44, -10.8507, -11.0452, -11.2138, -11.2044, -11.0578, -10.562,
      -9.7493, -9.0054, -8.3162, -7.5913, -7.1375, -6.8256, -6.4302, -6.2317,
      -6.0758, -6.0391, -5.2995, -4.6832 };

    static real_T eml_dv14[76] = { 0.0, -0.1396, -0.1047, -0.0803, -0.0698,
      -0.0349, 0.0, 0.0349, 0.0698, 0.1047, 0.1396, 0.1606, 0.1763, 0.2025,
      0.2199, 0.2374, 0.2426, 0.2618, 0.2793, 0.0, -7.947, -7.947, -7.947,
      -7.947, -7.947, -7.947, -7.947, -7.947, -7.947, -7.947, -7.947, -7.947,
      -7.947, -7.947, -7.947, -7.947, -7.947, -7.947, 0.2, -9.4769, -9.5886,
      -9.6215, -9.6299, -9.6314, -9.6031, -9.5518, -9.4769, -9.3736, -9.2459,
      -9.1556, -9.0822, -8.9491, -8.8573, -8.7617, -8.7326, -8.6278, -8.4939,
      0.44, -10.5937, -10.6243, -10.6625, -10.6702, -10.6931, -10.6916, -10.6702,
      -10.6243, -10.5554, -10.4636, -10.4024, -10.3543, -10.2571, -10.1691,
      -10.0636, -10.0276, -9.8746, -9.7829 };

    static real_T eml_dv15[8] = { 0.0, 0.0, 0.0, -0.4461, 0.2, -0.4784, 0.44,
      -0.5089 };

    static real_T eml_dv16[38] = { 0.0, -0.1396, -0.1047, -0.0803, -0.0698,
      -0.0349, 0.0, 0.0349, 0.0698, 0.1047, 0.1396, 0.1606, 0.1763, 0.2025,
      0.2199, 0.2374, 0.2426, 0.2618, 0.2793, 0.0, -0.10234, -0.10779, -0.11158,
      -0.1132, -0.11858, -0.12393, -0.12925, -0.13455, -0.13983, -0.14464,
      -0.14699, -0.14839, -0.1501, -0.15054, -0.15001, -0.1491, -0.14312,
      -0.13452 };

    static real_T eml_dv17[76] = { 0.0, -0.1396, -0.1047, -0.0803, -0.0698,
      -0.0349, 0.0, 0.0349, 0.0698, 0.1047, 0.1396, 0.1606, 0.1763, 0.2025,
      0.2199, 0.2374, 0.2426, 0.2618, 0.2793, 0.0, 0.06607, 0.06632, 0.06685,
      0.06717, 0.06861, 0.07064, 0.07063, 0.07133, 0.06999, 0.06617, 0.06582,
      0.06567, 0.06697, 0.06796, 0.06868, 0.0684, 0.06574, 0.06173, 0.2, 0.06367,
      0.06391, 0.06444, 0.06475, 0.06618, 0.06821, 0.06821, 0.06891, 0.06758,
      0.06377, 0.06343, 0.06328, 0.0646, 0.0656, 0.06632, 0.06605, 0.0634,
      0.0594, 0.44, 0.06215, 0.06239, 0.06291, 0.06322, 0.06465, 0.06668,
      0.06668, 0.06738, 0.06606, 0.06225, 0.06191, 0.06177, 0.06309, 0.0641,
      0.06483, 0.06456, 0.06192, 0.05793 };

    static real_T eml_dv18[38] = { 0.0, -0.1396, -0.1047, -0.0803, -0.0698,
      -0.0349, 0.0, 0.0349, 0.0698, 0.1047, 0.1396, 0.1606, 0.1763, 0.2025,
      0.2199, 0.2374, 0.2426, 0.2618, 0.2793, 0.0, 0.15126, 0.15337, 0.15473,
      0.15528, 0.15701, 0.15854, 0.15988, 0.16103, 0.16198, 0.16273, 0.16309,
      0.16331, 0.16359, 0.16371, 0.16379, 0.1638, 0.1638, 0.16376 };

    static real_T eml_dv19[38] = { 0.0, -0.1396, -0.1047, -0.0803, -0.0698,
      -0.0349, 0.0, 0.0349, 0.0698, 0.1047, 0.1396, 0.1606, 0.1763, 0.2025,
      0.2199, 0.2374, 0.2426, 0.2618, 0.2793, 0.0, -0.0546, -0.01062, 0.02011,
      0.03327, 0.07705, 0.12075, 0.16437, 0.20793, 0.25143, 0.29238, 0.31401,
      0.32823, 0.34851, 0.35818, 0.36247, 0.3596, 0.33448, 0.29417 };

    static real_T eml_dv20[38] = { 0.0, -0.1396, -0.1047, -0.0803, -0.0698,
      -0.0349, 0.0, 0.0349, 0.0698, 0.1047, 0.1396, 0.1606, 0.1763, 0.2025,
      0.2199, 0.2374, 0.2426, 0.2618, 0.2793, 0.0, -0.05865, -0.05957, -0.06046,
      -0.0609, -0.06262, -0.06473, -0.06723, -0.0701, -0.07336, -0.0768,
      -0.07879, -0.08017, -0.08224, -0.08329, -0.08383, -0.08361, -0.08154,
      -0.0784 };

    static real_T eml_dv21[38] = { 0.0, -0.1396, -0.1047, -0.0803, -0.0698,
      -0.0349, 0.0, 0.0349, 0.0698, 0.1047, 0.1396, 0.1606, 0.1763, 0.2025,
      0.2199, 0.2374, 0.2426, 0.2618, 0.2793, 0.0, -0.15633, -0.16074, -0.16389,
      -0.16525, -0.16995, -0.17479, -0.17979, -0.18496, -0.19028, -0.17138,
      -0.15083, -0.13369, -0.11559, -0.09285, -0.05983, -0.04457, -0.04457,
      -0.04457 };

    static real_T eml_dv22[38] = { 0.0, -0.1396, -0.1047, -0.0803, -0.0698,
      -0.0349, 0.0, 0.0349, 0.0698, 0.1047, 0.1396, 0.1606, 0.1763, 0.2025,
      0.2199, 0.2374, 0.2426, 0.2618, 0.2793, 0.0, -0.4963, -0.4959, -0.4958,
      -0.4958, -0.4961, -0.4968, -0.4977, -0.4991, -0.4875, -0.4436, -0.4436,
      -0.4436, -0.4436, -0.4436, -0.4436, -0.4436, -0.4436, -0.4436 };

    static real_T eml_dv23[38] = { 0.0, -0.1396, -0.1047, -0.0803, -0.0698,
      -0.0349, 0.0, 0.0349, 0.0698, 0.1047, 0.1396, 0.1606, 0.1763, 0.2025,
      0.2199, 0.2374, 0.2426, 0.2618, 0.2793, 0.0, 0.01856, 0.00708, -0.00055,
      -0.00383, -0.01481, -0.02586, -0.03696, -0.04811, -0.05868, -0.06688,
      -0.06977, -0.07092, -0.07058, -0.06693, -0.05028, -0.04196, -0.01401,
      0.00293 };

    static real_T eml_dv24[10] = { 0.0, 0.0, 0.0, -0.084728, 0.274, -0.084728,
      0.48, -0.074158, 0.9599, -0.055151 };

    static real_T eml_dv25[95] = { 0.0, -0.1396, -0.1047, -0.0803, -0.0698,
      -0.0349, 0.0, 0.0349, 0.0698, 0.1047, 0.1396, 0.1606, 0.1763, 0.2025,
      0.2199, 0.2374, 0.2426, 0.2618, 0.2793, 0.0, -0.004356, -0.001895,
      -0.000172, 0.000566, 0.003027, 0.005489, 0.007952, 0.010415, 0.01288,
      0.015216, 0.016466, 0.0173, 0.018512, 0.019121, 0.019449, 0.01933,
      0.018133, 0.016132, 0.27402, -0.004356, -0.001895, -0.000172, 0.000566,
      0.003027, 0.005489, 0.007952, 0.010415, 0.01288, 0.015216, 0.016466,
      0.0173, 0.018512, 0.019121, 0.019449, 0.01933, 0.018133, 0.016132, 0.47997,
      -0.003813, -0.001659, -0.000151, 0.000495, 0.00265, 0.004804, 0.00696,
      0.009116, 0.011273, 0.013318, 0.014412, 0.015142, 0.016203, 0.016735,
      0.017023, 0.016919, 0.015871, 0.01412, 0.95993, -0.002835, -0.001234,
      -0.000112, 0.000368, 0.00197, 0.003573, 0.005176, 0.00678, 0.008384,
      0.009905, 0.010718, 0.011261, 0.01205, 0.012446, 0.01266, 0.012582,
      0.011803, 0.010501 };

    static real_T eml_dv26[38] = { 0.0, -0.1396, -0.1047, -0.0803, -0.0698,
      -0.0349, 0.0, 0.0349, 0.0698, 0.1047, 0.1396, 0.1606, 0.1763, 0.2025,
      0.2199, 0.2374, 0.2426, 0.2618, 0.2793, 0.0, 0.01995, 0.01831, 0.01701,
      0.01643, 0.01463, 0.01279, 0.01091, 0.00906, 0.00718, 0.00528, 0.00414,
      0.00329, 0.00187, 0.00092, -0.00004, -0.00033, -0.00033, -0.00033 };

    static real_T eml_dv27[38] = { 0.0, -0.1396, -0.1047, -0.0803, -0.0698,
      -0.0349, 0.0, 0.0349, 0.0698, 0.1047, 0.1396, 0.1606, 0.1763, 0.2025,
      0.2199, 0.2374, 0.2426, 0.2618, 0.2793, 0.0, -0.04816, -0.04883, -0.04927,
      -0.04938, -0.04994, -0.05039, -0.05078, -0.05111, -0.05138, -0.05159,
      -0.05168, -0.05174, -0.05184, -0.05184, -0.05184, -0.05184, -0.05184,
      -0.05184 };

    for (eml_i0 = 0; eml_i0 < 4; eml_i0++) {
      for (eml_i1 = 0; eml_i1 < 19; eml_i1++) {
        ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
          ->Table_7[eml_i1 + 19 * eml_i0] = eml_dv0[eml_i1 + 19 * eml_i0];
      }
    }

    for (eml_i0 = 0; eml_i0 < 5; eml_i0++) {
      for (eml_i1 = 0; eml_i1 < 19; eml_i1++) {
        ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
          ->Table_8[eml_i1 + 19 * eml_i0] = eml_dv1[eml_i1 + 19 * eml_i0];
      }
    }

    for (eml_i0 = 0; eml_i0 < 4; eml_i0++) {
      for (eml_i1 = 0; eml_i1 < 19; eml_i1++) {
        ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
          ->Table_9[eml_i1 + 19 * eml_i0] = eml_dv2[eml_i1 + 19 * eml_i0];
        ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
          ->Table_10[eml_i1 + 19 * eml_i0] = eml_dv3[eml_i1 + 19 * eml_i0];
        ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
          ->Table_11[eml_i1 + 19 * eml_i0] = eml_dv4[eml_i1 + 19 * eml_i0];
      }
    }

    for (eml_i0 = 0; eml_i0 < 5; eml_i0++) {
      for (eml_i1 = 0; eml_i1 < 19; eml_i1++) {
        ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
          ->Table_12[eml_i1 + 19 * eml_i0] = eml_dv5[eml_i1 + 19 * eml_i0];
      }
    }

    for (eml_i0 = 0; eml_i0 < 4; eml_i0++) {
      for (eml_i1 = 0; eml_i1 < 19; eml_i1++) {
        ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
          ->Table_13[eml_i1 + 19 * eml_i0] = eml_dv6[eml_i1 + 19 * eml_i0];
        ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
          ->Table_14[eml_i1 + 19 * eml_i0] = eml_dv7[eml_i1 + 19 * eml_i0];
        ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
          ->Table_15[eml_i1 + 19 * eml_i0] = eml_dv8[eml_i1 + 19 * eml_i0];
      }
    }

    for (eml_i0 = 0; eml_i0 < 5; eml_i0++) {
      for (eml_i1 = 0; eml_i1 < 19; eml_i1++) {
        ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
          ->Table_16[eml_i1 + 19 * eml_i0] = eml_dv9[eml_i1 + 19 * eml_i0];
      }

      ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
        ->Table_17[eml_i0] = eml_dv10[eml_i0];
    }

    for (eml_i0 = 0; eml_i0 < 4; eml_i0++) {
      for (eml_i1 = 0; eml_i1 < 19; eml_i1++) {
        ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
          ->Table_20[eml_i1 + 19 * eml_i0] = eml_dv11[eml_i1 + 19 * eml_i0];
      }
    }

    for (eml_i0 = 0; eml_i0 < 5; eml_i0++) {
      for (eml_i1 = 0; eml_i1 < 19; eml_i1++) {
        ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
          ->Table_21[eml_i1 + 19 * eml_i0] = eml_dv12[eml_i1 + 19 * eml_i0];
      }
    }

    for (eml_i1 = 0; eml_i1 < 4; eml_i1++) {
      for (eml_i0 = 0; eml_i0 < 19; eml_i0++) {
        ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
          ->Table_22[eml_i0 + 19 * eml_i1] = eml_dv13[eml_i0 + 19 * eml_i1];
        ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
          ->Table_23[eml_i0 + 19 * eml_i1] = eml_dv14[eml_i0 + 19 * eml_i1];
      }

      for (eml_i0 = 0; eml_i0 < 2; eml_i0++) {
        ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
          ->Table_24[eml_i0 + (eml_i1 << 1)] = eml_dv15[eml_i0 + (eml_i1 << 1)];
      }
    }

    for (eml_i0 = 0; eml_i0 < 2; eml_i0++) {
      for (eml_i1 = 0; eml_i1 < 19; eml_i1++) {
        ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
          ->Table_25[eml_i1 + 19 * eml_i0] = eml_dv16[eml_i1 + 19 * eml_i0];
      }
    }

    for (eml_i0 = 0; eml_i0 < 4; eml_i0++) {
      for (eml_i1 = 0; eml_i1 < 19; eml_i1++) {
        ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
          ->Table_26[eml_i1 + 19 * eml_i0] = eml_dv17[eml_i1 + 19 * eml_i0];
      }
    }

    for (eml_i0 = 0; eml_i0 < 2; eml_i0++) {
      for (eml_i1 = 0; eml_i1 < 19; eml_i1++) {
        ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
          ->Table_27a[eml_i1 + 19 * eml_i0] = eml_dv18[eml_i1 + 19 * eml_i0];
        ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
          ->Table_27b[eml_i1 + 19 * eml_i0] = eml_dv19[eml_i1 + 19 * eml_i0];
        ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
          ->Table_27c[eml_i1 + 19 * eml_i0] = eml_dv20[eml_i1 + 19 * eml_i0];
        ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
          ->Table_28a[eml_i1 + 19 * eml_i0] = eml_dv21[eml_i1 + 19 * eml_i0];
        ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
          ->Table_28b[eml_i1 + 19 * eml_i0] = eml_dv22[eml_i1 + 19 * eml_i0];
        ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
          ->Table_28c[eml_i1 + 19 * eml_i0] = eml_dv23[eml_i1 + 19 * eml_i0];
      }
    }

    for (eml_i1 = 0; eml_i1 < 5; eml_i1++) {
      for (eml_i0 = 0; eml_i0 < 2; eml_i0++) {
        ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
          ->Table_29[eml_i0 + (eml_i1 << 1)] = eml_dv24[eml_i0 + (eml_i1 << 1)];
      }

      for (eml_i0 = 0; eml_i0 < 19; eml_i0++) {
        ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
          ->Table_30[eml_i0 + 19 * eml_i1] = eml_dv25[eml_i0 + 19 * eml_i1];
      }
    }

    for (eml_i0 = 0; eml_i0 < 2; eml_i0++) {
      for (eml_i1 = 0; eml_i1 < 19; eml_i1++) {
        ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
          ->Table_32a[eml_i1 + 19 * eml_i0] = eml_dv26[eml_i1 + 19 * eml_i0];
        ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
          ->Table_32b[eml_i1 + 19 * eml_i0] = eml_dv27[eml_i1 + 19 * eml_i0];
      }
    }
  }
}

/* Output and update for atomic system: '<S6>/AERO FORCES EN MOMENTS' */
void pa34model_d_AEROFORCESENMOMENTS(rtModel_pa34model_dueca_8b
  *pa34model_dueca_8b_rtM)
{
  /* SignalConversion: '<S14>/TmpHiddenBufferAt SFunction Inport5' incorporates:
   *  Constant: '<S24>/chord'
   *  Constant: '<S24>/location_AERORP.x'
   *  Constant: '<S24>/location_AERORP.y'
   *  Constant: '<S24>/location_AERORP.z'
   *  Constant: '<S24>/wingarea'
   *  Constant: '<S24>/wingspan'
   */
  ((BlockIO_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->ModelData.blockIO)
    ->TmpHiddenBufferAtSFunctionInpor[0] = 19.39;
  ((BlockIO_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->ModelData.blockIO)
    ->TmpHiddenBufferAtSFunctionInpor[1] = 11.85;
  ((BlockIO_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->ModelData.blockIO)
    ->TmpHiddenBufferAtSFunctionInpor[2] = 1.61;
  ((BlockIO_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->ModelData.blockIO)
    ->TmpHiddenBufferAtSFunctionInpor[3] = 0.0;
  ((BlockIO_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->ModelData.blockIO)
    ->TmpHiddenBufferAtSFunctionInpor[4] = 0.0;
  ((BlockIO_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->ModelData.blockIO)
    ->TmpHiddenBufferAtSFunctionInpor[5] = 0.0;

  /* Embedded MATLAB: '<S6>/AERO FORCES EN MOMENTS' */
  pa34model_c1_pa34model_dueca_8b(pa34model_dueca_8b_rtM);
}

/* Functions for block: '<S6>/Calculate Thrust Parameters' */
static void pa34mode_c19_pa34model_dueca_8b(rtModel_pa34model_dueca_8b
  *pa34model_dueca_8b_rtM)
{
  real_T eml_Vb[3];
  real_T eml_V;
  int32_T eml_ii;
  real_T eml_rho_a;
  real_T eml_Temp;
  real_T eml_Right_orient[3];
  real_T eml_pla1;
  real_T eml_pla2;
  real_T eml_RPM_LEFT;
  real_T eml_RPM_RIGHT;
  real_T eml_rpm;
  real_T eml_rpm_max;
  real_T eml_PL;
  static int8_T eml_iv0[2] = { 1, 2 };

  int32_T eml_ii_0;
  int32_T eml_i;
  int32_T eml_rpm_L;
  int32_T eml_rpm_H;
  real_T eml_delta_rpm;
  int32_T eml_rho_L;
  real_T eml_delta_rho;
  real_T eml_H1;
  real_T eml_H3;
  real_T eml_P_sl;
  real_T eml_P_ft;
  real_T eml_Cp;
  real_T eml_delta_Cp;
  real_T eml_ct3;
  real_T eml_dv9[4];
  static real_T eml_dv10[4] = { 0.05, 0.1, 0.2, 0.3 };

  /*  This block supports the Embedded MATLAB subset. */
  /*  See the help menu for details. */
  /*  De lookuptables */
  /*  Inlezen inputs */
  /* kg/m3 */
  /* state = col( p, q, r, u, v, w, phi, theta, psi, x, y, z) */
  eml_Vb[0] = ((BlockIO_pa34model_dueca_8b *)
               pa34model_dueca_8b_rtM->ModelData.blockIO)->stateo[3];
  eml_Vb[1] = ((BlockIO_pa34model_dueca_8b *)
               pa34model_dueca_8b_rtM->ModelData.blockIO)->stateo[4];
  eml_Vb[2] = ((BlockIO_pa34model_dueca_8b *)
               pa34model_dueca_8b_rtM->ModelData.blockIO)->stateo[5];
  eml_V = 0.0;
  for (eml_ii = 0; eml_ii < 3; eml_ii++) {
    eml_V += eml_Vb[eml_ii] * eml_Vb[eml_ii];
  }

  eml_V = sqrt(eml_V);

  /* atmos = col(rho, T, g, Vwind (3), Omegawind (3)) */
  eml_rho_a = ((BlockIO_pa34model_dueca_8b *)
               pa34model_dueca_8b_rtM->ModelData.blockIO)->atmoso[0];
  eml_Temp = ((BlockIO_pa34model_dueca_8b *)
              pa34model_dueca_8b_rtM->ModelData.blockIO)->atmoso[1];

  /* engine= number,x1,y1,z1,phi1,theta1,psi1,x2,y2,z2,phi2,theta2,psi2; */
  /*  Left_X=engine(2:4); */
  /*  Right_X=engine(8:10); */
  for (eml_ii = 0; eml_ii < 3; eml_ii++) {
    eml_Vb[eml_ii] = ((BlockIO_pa34model_dueca_8b *)
                      pa34model_dueca_8b_rtM->ModelData.blockIO)->engine[4 +
      eml_ii];
    eml_Right_orient[eml_ii] = ((BlockIO_pa34model_dueca_8b *)
      pa34model_dueca_8b_rtM->ModelData.blockIO)->engine[10 + eml_ii];
  }

  eml_pla1 = ((BlockIO_pa34model_dueca_8b *)
              pa34model_dueca_8b_rtM->ModelData.blockIO)->engine[13];
  eml_pla2 = ((BlockIO_pa34model_dueca_8b *)
              pa34model_dueca_8b_rtM->ModelData.blockIO)->engine[14];
  eml_RPM_LEFT = ((BlockIO_pa34model_dueca_8b *)
                  pa34model_dueca_8b_rtM->ModelData.blockIO)->engine[15];
  eml_RPM_RIGHT = ((BlockIO_pa34model_dueca_8b *)
                   pa34model_dueca_8b_rtM->ModelData.blockIO)->engine[16];

  /*  Initialiseren want in if statement */
  /* Outputs */
  for (eml_ii = 0; eml_ii < 12; eml_ii++) {
    ((BlockIO_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->ModelData.blockIO)
      ->Thrust[eml_ii] = 0.0;
  }

  /*  output thrust als vector in body axis */
  for (eml_ii = 0; eml_ii < 2; eml_ii++) {
    ((BlockIO_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->ModelData.blockIO)
      ->eng_state_dot[eml_ii] = 0.0;
  }

  for (eml_ii = 0; eml_ii < 4; eml_ii++) {
    ((BlockIO_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->ModelData.blockIO)
      ->n_lr[eml_ii] = 0.0;
  }

  /* % Engine Model */
  /*  Engine modelling using Seneca III data */
  eml_rpm = 800.0;

  /* nodig vanwege if statements */
  eml_rpm_max = 800.0;

  /* nodig vanwege if statements */
  eml_PL = 0.0;

  /*  Nodig te definieren voor if statements */
  for (eml_ii = 0; eml_ii < 2; eml_ii++) {
    eml_ii_0 = (int32_T)eml_iv0[eml_ii];
    if (eml_ii_0 == 1) {
      eml_PL = eml_pla1;
      eml_rpm = ((D_Work_pa34model_dueca_8b *)
                 pa34model_dueca_8b_rtM->Work.dwork)->rpm1;
      eml_rpm_max = eml_RPM_LEFT;
    }

    if (eml_ii_0 == 2) {
      eml_PL = eml_pla2;
      eml_rpm = ((D_Work_pa34model_dueca_8b *)
                 pa34model_dueca_8b_rtM->Work.dwork)->rpm2;
      eml_rpm_max = eml_RPM_RIGHT;
    }

    /* % Motor tabellen ************************************************ */
    /*  Eerst motor vermogen bepalen */
    /*  Bepalen indices */
    for (eml_i = 2; (eml_rpm > ((D_Work_pa34model_dueca_8b *)
           pa34model_dueca_8b_rtM->Work.dwork)->E1[eml_i - 1]) && (eml_i < 12);
         eml_i++) {
    }

    if (eml_i == 2) {
      eml_rpm_L = 2;
      eml_rpm_H = 2;
      eml_delta_rpm = 0.0;
    } else if (eml_rpm > ((D_Work_pa34model_dueca_8b *)
                          pa34model_dueca_8b_rtM->Work.dwork)->E1[11]) {
      eml_rpm_L = 12;
      eml_rpm_H = 12;
      eml_delta_rpm = 0.0;
    } else {
      eml_rpm_L = eml_i - 1;
      eml_rpm_H = eml_i;
      eml_delta_rpm = (eml_rpm - ((D_Work_pa34model_dueca_8b *)
        pa34model_dueca_8b_rtM->Work.dwork)->E1[eml_rpm_L - 1]) /
        (((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)->
         E1[eml_i - 1] - ((D_Work_pa34model_dueca_8b *)
                          pa34model_dueca_8b_rtM->Work.dwork)->E1[eml_rpm_L - 1]);
    }

    for (eml_i = 2; (eml_rho_a > ((D_Work_pa34model_dueca_8b *)
           pa34model_dueca_8b_rtM->Work.dwork)->E4[13 * (eml_i - 1)]) && (eml_i <
          7); eml_i++) {
    }

    if (eml_i == 2) {
      eml_rho_L = 2;
      eml_i = 2;
      eml_delta_rho = 0.0;
    } else if (eml_rho_a > ((D_Work_pa34model_dueca_8b *)
                            pa34model_dueca_8b_rtM->Work.dwork)->E4[78]) {
      eml_rho_L = 7;
      eml_i = 7;
      eml_delta_rho = 0.0;
    } else {
      eml_rho_L = eml_i - 1;
      eml_delta_rho = (eml_rho_a - ((D_Work_pa34model_dueca_8b *)
        pa34model_dueca_8b_rtM->Work.dwork)->E4[13 * (eml_rho_L - 1)]) /
        (((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)->E4
         [13 * (eml_i - 1)] - ((D_Work_pa34model_dueca_8b *)
          pa34model_dueca_8b_rtM->Work.dwork)->E4[13 * (eml_rho_L - 1)]);
    }

    eml_H1 = ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork
      )->E4[(eml_rpm_L - 1) + 13 * (eml_rho_L - 1)];
    eml_H3 = ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork
      )->E4[(eml_rpm_H - 1) + 13 * (eml_rho_L - 1)];
    eml_H1 += eml_delta_rho * (((D_Work_pa34model_dueca_8b *)
      pa34model_dueca_8b_rtM->Work.dwork)->E4[(eml_rpm_L - 1) + 13 * (eml_i - 1)]
      - eml_H1);
    eml_delta_rho = eml_PL * (eml_H1 + eml_delta_rpm * ((eml_H3 + eml_delta_rho *
                                (((D_Work_pa34model_dueca_8b *)
      pa34model_dueca_8b_rtM->Work.dwork)->E4[(eml_rpm_H - 1) + 13 * (eml_i - 1)]
      - eml_H3)) - eml_H1));
    for (eml_i = 2; (eml_delta_rho > ((D_Work_pa34model_dueca_8b *)
           pa34model_dueca_8b_rtM->Work.dwork)->E1[13 * (eml_i - 1)]) && (eml_i <
          8); eml_i++) {
    }

    if (eml_i == 2) {
      eml_rho_L = 2;
      eml_i = 2;
      eml_delta_rho = 0.0;
    } else if (eml_delta_rho > ((D_Work_pa34model_dueca_8b *)
                pa34model_dueca_8b_rtM->Work.dwork)->E1[91]) {
      eml_rho_L = 8;
      eml_i = 8;
      eml_delta_rho = 0.0;
    } else {
      eml_rho_L = eml_i - 1;
      eml_delta_rho = (eml_delta_rho - ((D_Work_pa34model_dueca_8b *)
        pa34model_dueca_8b_rtM->Work.dwork)->E1[13 * (eml_rho_L - 1)]) /
        (((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)->E1
         [13 * (eml_i - 1)] - ((D_Work_pa34model_dueca_8b *)
          pa34model_dueca_8b_rtM->Work.dwork)->E1[13 * (eml_rho_L - 1)]);
    }

    eml_H1 = ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork
      )->E1[(eml_rpm_L - 1) + 13 * (eml_rho_L - 1)];
    eml_H3 = ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork
      )->E1[(eml_rpm_H - 1) + 13 * (eml_rho_L - 1)];
    eml_H1 += eml_delta_rho * (((D_Work_pa34model_dueca_8b *)
      pa34model_dueca_8b_rtM->Work.dwork)->E1[(eml_rpm_L - 1) + 13 * (eml_i - 1)]
      - eml_H1);
    eml_P_sl = eml_H1 + eml_delta_rpm * ((eml_H3 + eml_delta_rho *
      (((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)->E1
       [(eml_rpm_H - 1) + 13 * (eml_i - 1)] - eml_H3)) - eml_H1);
    eml_H1 = ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork
      )->E2[(eml_rpm_L - 1) + 13 * (eml_rho_L - 1)];
    eml_H3 = ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork
      )->E2[(eml_rpm_H - 1) + 13 * (eml_rho_L - 1)];
    eml_H1 += eml_delta_rho * (((D_Work_pa34model_dueca_8b *)
      pa34model_dueca_8b_rtM->Work.dwork)->E2[(eml_rpm_L - 1) + 13 * (eml_i - 1)]
      - eml_H1);
    eml_P_ft = eml_H1 + eml_delta_rpm * ((eml_H3 + eml_delta_rho *
      (((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)->E2
       [(eml_rpm_H - 1) + 13 * (eml_i - 1)] - eml_H3)) - eml_H1);
    eml_H1 = ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork
      )->E3[(eml_rpm_L - 1) + 13 * (eml_rho_L - 1)];
    eml_H3 = ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork
      )->E3[(eml_rpm_H - 1) + 13 * (eml_rho_L - 1)];
    eml_H1 += eml_delta_rho * (((D_Work_pa34model_dueca_8b *)
      pa34model_dueca_8b_rtM->Work.dwork)->E3[(eml_rpm_L - 1) + 13 * (eml_i - 1)]
      - eml_H1);
    eml_delta_rho = eml_H1 + eml_delta_rpm * ((eml_H3 + eml_delta_rho *
      (((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)->E3
       [(eml_rpm_H - 1) + 13 * (eml_i - 1)] - eml_H3)) - eml_H1);
    if (eml_rho_a > eml_delta_rho) {
      eml_P_ft = (eml_rho_a - eml_delta_rho) / (1.225 - eml_delta_rho) *
        eml_P_sl + (1.225 - eml_rho_a) / (1.225 - eml_delta_rho) * eml_P_ft;
    }

    /*  Nu Thrust bepalen D=1.93 */
    eml_delta_rho = eml_V * 5.1813471502590680E-001 * (60.0 / eml_rpm) * 0.9732;

    /*  0.9732 is cowling effect */
    eml_Cp = eml_P_ft * 7.457E+002 * 216000.0 / (eml_rho_a *
      2.6778518419299996E+001 * pow(eml_rpm, 3.0));

    /* bepalen indices J en Cp */
    for (eml_i = 2; (eml_delta_rho > ((D_Work_pa34model_dueca_8b *)
           pa34model_dueca_8b_rtM->Work.dwork)->CT1[eml_i - 1]) && (eml_i < 32);
         eml_i++) {
    }

    if (eml_i == 2) {
      eml_rho_L = 2;
      eml_rpm_L = 2;
      eml_delta_rho = 0.0;
    } else if (eml_delta_rho > ((D_Work_pa34model_dueca_8b *)
                pa34model_dueca_8b_rtM->Work.dwork)->CT1[31]) {
      eml_rho_L = 32;
      eml_rpm_L = 32;
      eml_delta_rho = 0.0;
    } else {
      eml_rho_L = eml_i - 1;
      eml_rpm_L = eml_i;
      eml_delta_rho = (eml_delta_rho - ((D_Work_pa34model_dueca_8b *)
        pa34model_dueca_8b_rtM->Work.dwork)->CT1[eml_rho_L - 1]) /
        (((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)->
         CT1[eml_i - 1] - ((D_Work_pa34model_dueca_8b *)
                           pa34model_dueca_8b_rtM->Work.dwork)->CT1[eml_rho_L -
         1]);
    }

    for (eml_i = 2; (eml_Cp > ((D_Work_pa34model_dueca_8b *)
           pa34model_dueca_8b_rtM->Work.dwork)->CT1[(eml_i - 1) << 5]) && (eml_i
          < 10); eml_i++) {
    }

    if (eml_i == 2) {
      eml_rpm_H = 2;
      eml_i = 2;
      eml_delta_Cp = 0.0;
    } else if (eml_Cp > ((D_Work_pa34model_dueca_8b *)
                         pa34model_dueca_8b_rtM->Work.dwork)->CT1[288]) {
      eml_rpm_H = 10;
      eml_i = 10;
      eml_delta_Cp = 0.0;
    } else {
      eml_rpm_H = eml_i - 1;
      eml_delta_Cp = (eml_Cp - ((D_Work_pa34model_dueca_8b *)
        pa34model_dueca_8b_rtM->Work.dwork)->CT1[(eml_rpm_H - 1) << 5]) /
        (((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)->
         CT1[(eml_i - 1) << 5] - ((D_Work_pa34model_dueca_8b *)
          pa34model_dueca_8b_rtM->Work.dwork)->CT1[(eml_rpm_H - 1) << 5]);
    }

    eml_H1 = ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork
      )->CT1[(eml_rho_L - 1) + ((eml_rpm_H - 1) << 5)];
    eml_H3 = ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork
      )->CT1[(eml_rpm_L - 1) + ((eml_rpm_H - 1) << 5)];
    eml_H1 += eml_delta_Cp * (((D_Work_pa34model_dueca_8b *)
      pa34model_dueca_8b_rtM->Work.dwork)->CT1[(eml_rho_L - 1) + ((eml_i - 1) <<
      5)] - eml_H1);
    eml_P_sl = eml_H1 + eml_delta_rho * ((eml_H3 + eml_delta_Cp *
      (((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)->CT1
       [(eml_rpm_L - 1) + ((eml_i - 1) << 5)] - eml_H3)) - eml_H1);
    eml_H1 = ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork
      )->CT2[(eml_rho_L - 1) + ((eml_rpm_H - 1) << 5)];
    eml_H3 = ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork
      )->CT2[(eml_rpm_L - 1) + ((eml_rpm_H - 1) << 5)];
    eml_H1 += eml_delta_Cp * (((D_Work_pa34model_dueca_8b *)
      pa34model_dueca_8b_rtM->Work.dwork)->CT2[(eml_rho_L - 1) + ((eml_i - 1) <<
      5)] - eml_H1);
    eml_delta_rpm = eml_H1 + eml_delta_rho * ((eml_H3 + eml_delta_Cp *
      (((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)->CT2
       [(eml_rpm_L - 1) + ((eml_i - 1) << 5)] - eml_H3)) - eml_H1);
    eml_H1 = ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork
      )->CT3[(eml_rho_L - 1) + ((eml_rpm_H - 1) << 5)];
    eml_H3 = ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork
      )->CT3[(eml_rpm_L - 1) + ((eml_rpm_H - 1) << 5)];
    eml_H1 += eml_delta_Cp * (((D_Work_pa34model_dueca_8b *)
      pa34model_dueca_8b_rtM->Work.dwork)->CT3[(eml_rho_L - 1) + ((eml_i - 1) <<
      5)] - eml_H1);
    eml_ct3 = eml_H1 + eml_delta_rho * ((eml_H3 + eml_delta_Cp *
      (((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)->CT3
       [(eml_rpm_L - 1) + ((eml_i - 1) << 5)] - eml_H3)) - eml_H1);
    eml_H1 = ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork
      )->CT4[(eml_rho_L - 1) + ((eml_rpm_H - 1) << 5)];
    eml_H3 = ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork
      )->CT4[(eml_rpm_L - 1) + ((eml_rpm_H - 1) << 5)];
    eml_H1 += eml_delta_Cp * (((D_Work_pa34model_dueca_8b *)
      pa34model_dueca_8b_rtM->Work.dwork)->CT4[(eml_rho_L - 1) + ((eml_i - 1) <<
      5)] - eml_H1);

    /*  roughly for low altitude */
    eml_dv9[0] = eml_P_sl;
    eml_dv9[1] = eml_delta_rpm;
    eml_dv9[2] = eml_ct3;
    eml_dv9[3] = eml_H1 + eml_delta_rho * ((eml_H3 + eml_delta_Cp *
      (((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)->CT4
       [(eml_rpm_L - 1) + ((eml_i - 1) << 5)] - eml_H3)) - eml_H1);
    eml_delta_rho = glfkekfchdjmlngl_interp1(eml_dv10, eml_dv9,
      imohohdjdjmocjmo_max(aaaajecbeknghdbi_min(eml_V / (20.0468 * sqrt(eml_Temp)),
      0.3), 0.05));
    eml_P_sl = eml_delta_rho * eml_rho_a * pow(eml_rpm / 60.0, 2.0) *
      1.3874880009999998E+001;
    ((BlockIO_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->ModelData.blockIO)
      ->eng_state_dot[0] = -(eml_P_ft / 5.0 / 3600.0);
    if (((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)->Th1 <
        -1000.0) {
      /*  ruwe schatting fuel flow!! */
      ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)->Th1 =
        eml_P_sl;
    }

    if (((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)->Th2 <
        -1000.0) {
      ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)->Th2 =
        eml_P_sl;
    }

    if (eml_ii_0 == 1) {
      ((BlockIO_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->ModelData.blockIO
        )->eng_state_dot[0] = -(eml_P_ft / 5.0 / 3600.0);

      /*  ruwe schatting fuel flow!! */
      ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)->Th1 =
        0.98 * ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
        ->Th1 + 0.02 * (eml_delta_rho * eml_rho_a * pow(eml_rpm / 60.0, 2.0) *
                        1.3874880009999998E+001);
    } else {
      ((BlockIO_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->ModelData.blockIO
        )->eng_state_dot[1] = -(eml_P_ft / 5.0 / 3600.0);

      /*  ruwe schatting fuel flow!! */
      ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)->Th2 =
        0.98 * ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
        ->Th2 + 0.02 * (eml_delta_rho * eml_rho_a * pow(eml_rpm / 60.0, 2.0) *
                        1.3874880009999998E+001);
    }

    /*  Nu engine dynamics invoeren (zonodig aanpassen van rpm) */
    /*  Aanpassen van rpm als de torque niet geleverd kan worden */
    eml_H1 = ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork
      )->CPmin[eml_rho_L + 31];
    eml_rpm -= ((eml_H1 + eml_delta_Cp * (((D_Work_pa34model_dueca_8b *)
      pa34model_dueca_8b_rtM->Work.dwork)->CPmin[eml_rpm_L + 31] - eml_H1)) -
                eml_Cp) * 125.0;

    /*  begrenzen */
    eml_rpm = imohohdjdjmocjmo_max(eml_rpm, 800.0);
    eml_rpm = aaaajecbeknghdbi_min(eml_rpm_max, eml_rpm);
    if (eml_ii_0 == 1) {
      ((BlockIO_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->ModelData.blockIO
        )->n_lr[0] = eml_rpm;
      ((BlockIO_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->ModelData.blockIO
        )->n_lr[1] = eml_P_ft / eml_rpm;

      /*  ruwe torque */
      ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)->rpm1 =
        eml_rpm;

    }

    if (eml_ii_0 == 2) {
      ((BlockIO_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->ModelData.blockIO
        )->n_lr[2] = eml_rpm;
      ((BlockIO_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->ModelData.blockIO
        )->n_lr[3] = eml_P_ft / eml_rpm;
      ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)->rpm2 =
        eml_rpm;

    }
  }

  /*  thrust naar body axis transformeren */
  /*  Thrust momenten in CG module */
  /*  Forces left */
  ((BlockIO_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->ModelData.blockIO)
    ->Thrust[0] = ((D_Work_pa34model_dueca_8b *)
                   pa34model_dueca_8b_rtM->Work.dwork)->Th1 * cos(eml_Vb[1]);
  ((BlockIO_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->ModelData.blockIO)
    ->Thrust[2] = (-((D_Work_pa34model_dueca_8b *)
                     pa34model_dueca_8b_rtM->Work.dwork)->Th1) * sin(eml_Vb[1]);

  /*  Force right */
  ((BlockIO_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->ModelData.blockIO)
    ->Thrust[6] = ((D_Work_pa34model_dueca_8b *)
                   pa34model_dueca_8b_rtM->Work.dwork)->Th2 * cos
    (eml_Right_orient[1]);
  ((BlockIO_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->ModelData.blockIO)
    ->Thrust[8] = (-((D_Work_pa34model_dueca_8b *)
                     pa34model_dueca_8b_rtM->Work.dwork)->Th2) * sin
    (eml_Right_orient[1]);
}

/* Initial conditions for atomic system: '<S6>/Calculate Thrust Parameters' */
void CalculateThrustParameters_Init(rtModel_pa34model_dueca_8b
  *pa34model_dueca_8b_rtM)
{
  /* Initialize code for chart: '<S6>/Calculate Thrust Parameters' */
  {
    int32_T eml_i0;
    int32_T eml_i1;
    static real_T eml_dv0[104] = { 0.0, 800.0, 1000.0, 1500.0, 2000.0, 2100.0,
      2200.0, 2300.0, 2400.0, 2500.0, 2600.0, 2700.0, 2800.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 10.0, 4.0, 5.2, 5.6, 6.0, 6.3,
      7.1, 11.0, 15.3, 21.7, 24.0, 24.5, 25.0, 20.0, 44.4, 46.7, 52.4, 57.4,
      60.4, 63.3, 68.0, 7.26E+001, 80.0, 84.0, 87.0, 89.0, 26.0, 68.0, 71.7,
      80.8, 90.0, 93.7, 97.5, 103.5, 107.0, 115.0, 120.0, 124.5, 129.5, 30.0,
      83.8, 88.2, 99.3, 111.5, 116.0, 119.5, 125.0, 1.298E+002, 138.0, 144.0,
      149.0, 156.5, 40.0, 1.231E+002, 1.297E+002, 1.461E+002, 162.5, 166.0,
      170.0, 1.752E+002, 183.0, 190.5, 200.5, 209.0, 220.0, 42.0, 131.0, 138.0,
      155.5, 173.0, 176.5, 180.0, 1.842E+002, 192.0, 199.5, 211.0, 220.5, 231.0
    };

    static real_T eml_dv1[104] = { 0.0, 800.0, 1000.0, 1500.0, 2000.0, 2100.0,
      2200.0, 2300.0, 2400.0, 2500.0, 2600.0, 2700.0, 2800.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 10.0, 13.3, 15.3, 18.3, 25.0,
      27.0, 29.0, 34.0, 38.0, 41.7, 44.3, 44.7, 60.0, 20.0, 50.0, 52.0, 60.0,
      70.0, 77.0, 84.0, 84.0, 93.0, 95.0, 96.0, 103.0, 115.0, 26.0, 75.0, 77.0,
      85.0, 101.0, 106.0, 112.2, 114.0, 124.0, 126.0, 130.0, 138.0, 148.0, 30.0,
      91.0, 95.0, 105.0, 118.0, 125.0, 131.0, 134.0, 144.0, 147.0, 153.0, 158.0,
      167.5, 40.0, 110.0, 115.0, 135.0, 160.5, 166.0, 173.0, 176.0, 186.0, 192.0,
      202.0, 211.0, 221.0, 42.0, 115.0, 121.0, 142.0, 169.0, 175.0, 183.0, 186.0,
      195.0, 205.5, 212.0, 221.0, 233.0 };

    static real_T eml_dv2[104] = { 0.0, 800.0, 1000.0, 1500.0, 2000.0, 2100.0,
      2200.0, 2300.0, 2400.0, 2500.0, 2600.0, 2700.0, 2800.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 10.0, 0.8238, 0.7519, 0.593,
      0.4612, 0.4377, 0.431, 0.415, 0.4008, 0.374, 0.3488, 0.3327, 0.3285, 20.0,
      1.3867, 1.2649, 0.9961, 0.7733, 0.7338, 0.6981, 0.6638, 0.618, 0.5726,
      0.5223, 0.4931, 0.4949, 26.0, 1.7399, 1.5729, 1.209, 0.9132, 0.8614,
      0.8119, 0.7558, 0.7075, 0.6461, 0.5929, 0.5587, 0.5567, 30.0, 1.9815,
      1.7873, 1.3652, 1.0239, 0.9644, 0.9075, 0.8437, 0.7835, 0.717, 0.6483,
      0.5991, 0.597, 40.0, 2.2309, 2.0657, 1.6935, 1.3749, 1.3172, 1.2576,
      1.1345, 1.0716, 0.9422, 0.8546, 0.7708, 0.7708, 42.0, 2.2836, 2.1252,
      1.7659, 1.455, 1.3982, 1.3385, 1.2649, 1.1721, 0.9992, 0.9218, 0.8437,
      0.8384 };

    static real_T eml_dv3[91] = { 0.0, 800.0, 1000.0, 1500.0, 2000.0, 2100.0,
      2200.0, 2300.0, 2400.0, 2500.0, 2600.0, 2700.0, 2800.0, 0.56861, 11.5,
      11.5, 11.5, 11.5, 11.5, 11.5, 13.0, 15.5, 20.0, 24.0, 27.0, 27.0, 0.6527,
      13.7, 13.7, 13.7, 13.7, 14.5, 16.8, 19.0, 22.2, 26.4, 30.5, 34.5, 34.5,
      0.77082, 16.8, 16.8, 16.8, 20.0, 22.0, 24.0, 26.6, 29.5, 33.0, 37.0, 40.0,
      40.0, 0.90464, 20.5, 20.5, 20.5, 25.5, 27.7, 29.9, 33.0, 35.0, 38.8, 41.2,
      42.0, 42.0, 1.05555, 24.8, 24.8, 24.8, 31.0, 32.9, 34.8, 37.8, 39.5, 42.0,
      42.0, 42.0, 42.0, 1.225, 29.9, 29.9, 31.0, 34.7, 36.2, 38.4, 42.0, 42.0,
      42.0, 42.0, 42.0, 42.0 };

    static real_T eml_dv4[320] = { 0.0, 0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7,
      0.8, 0.9, 1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0, 2.1, 2.2,
      2.3, 2.4, 2.5, 2.6, 2.7, 2.8, 2.9, 3.0, 0.0, -0.04973, -0.04973, -0.04245,
      -0.01705, -0.00566, -0.01788, -0.01755, -0.01352, -0.00981, -0.00928,
      -0.00994, -0.01132, -0.01259, -0.0138, -0.01525, -0.01622, -0.0173,
      -0.01827, -0.01868, -0.01941, -0.02017, -0.02063, -0.02137, -0.02169,
      -0.02159, -0.02213, -0.02254, -0.02268, -0.02242, -0.02201, -0.0206, 0.05,
      0.12, 0.12, 0.11758, 0.10215, 0.08856, 0.0772, 0.06734, 0.05893, 0.05164,
      0.04524, 0.03968, 0.03465, 0.03007, 0.02589, 0.02182, 0.01855, 0.0155,
      0.01271, 0.0106, 0.00838, 0.00622, 0.00446, 0.00259, 0.00113, -0.0002,
      -0.00143, -0.00257, -0.00362, -0.0046, -0.00551, -0.00635, 0.1, 0.16285,
      0.16285, 0.16285, 0.15273, 0.1445, 0.13546, 0.124, 0.11251, 0.10199,
      0.09259, 0.08397, 0.07631, 0.06928, 0.06288, 0.05669, 0.05152, 0.04677,
      0.04238, 0.03878, 0.03525, 0.03187, 0.02899, 0.02608, 0.02364, 0.02117,
      0.0192, 0.01734, 0.01552, 0.0136, 0.01176, 0.00952, 0.15, 0.17828, 0.17828,
      0.17828, 0.1688, 0.16215, 0.1569, 0.15243, 0.14724, 0.14123, 0.13275,
      0.12293, 0.11365, 0.10506, 0.09717, 0.08938, 0.08269, 0.07651, 0.07076,
      0.06586, 0.06119, 0.0568, 0.05294, 0.04909, 0.04584, 0.04254, 0.03976,
      0.03719, 0.03475, 0.03218, 0.02978, 0.02702, 0.2, 0.17787, 0.17787,
      0.17787, 0.17787, 0.1713, 0.16608, 0.16177, 0.15717, 0.15318, 0.15122,
      0.14818, 0.14371, 0.13688, 0.12808, 0.11953, 0.11181, 0.10456, 0.09785,
      0.09193, 0.08628, 0.08094, 0.07622, 0.07147, 0.06743, 0.06334, 0.05992,
      0.05668, 0.05368, 0.05056, 0.04759, 0.04432, 0.25, 0.17725, 0.17725,
      0.17725, 0.17725, 0.17725, 0.17275, 0.16892, 0.16296, 0.15816, 0.15572,
      0.15415, 0.15311, 0.15185, 0.14879, 0.1445, 0.1387, 0.13061, 0.12319,
      0.1165, 0.11013, 0.10402, 0.09857, 0.09322, 0.08847, 0.08372, 0.0797,
      0.07587, 0.07231, 0.06866, 0.06514, 0.06132, 0.3, 0.17135, 0.17135,
      0.17135, 0.17135, 0.17135, 0.17135, 0.17135, 0.16706, 0.162, 0.15893,
      0.15702, 0.15529, 0.15418, 0.15415, 0.15375, 0.15248, 0.14957, 0.14644,
      0.13965, 0.13269, 0.12597, 0.11999, 0.11399, 0.10865, 0.10332, 0.09872,
      0.09432, 0.0903, 0.08612, 0.08215, 0.07794, 0.35, 0.16297, 0.16297,
      0.16297, 0.16297, 0.16297, 0.16297, 0.16297, 0.16297, 0.16297, 0.16154,
      0.15911, 0.15661, 0.15502, 0.15432, 0.15387, 0.15503, 0.15612, 0.1562,
      0.15437, 0.15249, 0.14705, 0.1405, 0.13397, 0.12807, 0.12228, 0.11714,
      0.1123, 0.10772, 0.10269, 0.09869, 0.09409, 0.4, 0.1579, 0.1579, 0.1579,
      0.1579, 0.1579, 0.1579, 0.1579, 0.1579, 0.1579, 0.15902, 0.15912, 0.15749,
      0.15497, 0.15357, 0.15243, 0.15315, 0.15495, 0.15708, 0.15942, 0.16114,
      0.15958, 0.15838, 0.15318, 0.14683, 0.14057, 0.13502, 0.12977, 0.12476,
      0.11964, 0.11481, 0.10988 };

    static real_T eml_dv5[320] = { 0.0, 0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7,
      0.8, 0.9, 1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0, 2.1, 2.2,
      2.3, 2.4, 2.5, 2.6, 2.7, 2.8, 2.9, 3.0, 0.0, -0.05535, -0.05535, -0.00412,
      -0.00793, -0.01716, -0.02199, -0.02097, -0.01294, -0.00761, -0.007,
      -0.00726, -0.0081, -0.00875, -0.00942, -0.01022, -0.0111, -0.01163,
      -0.01247, -0.01313, -0.01371, -0.01424, -0.01472, -0.01525, -0.01582,
      -0.01631, -0.01679, -0.01726, -0.01777, -0.0182, -0.01938, -0.02067, 0.05,
      0.1119, 0.1119, 0.09635, 0.09117, 0.08857, 0.07733, 0.06772, 0.05949,
      0.05248, 0.04654, 0.04142, 0.03682, 0.03284, 0.02929, 0.02602, 0.02312,
      0.02052, 0.018, 0.01574, 0.01373, 0.01188, 0.01016, 0.00852, 0.00702,
      0.00563, 0.00432, 0.0031, 0.00187, 0.00077, -0.00026, -0.00122, 0.1,
      0.1381, 0.1381, 0.1381, 0.1381, 0.14717, 0.13572, 0.12395, 0.11264,
      0.10226, 0.09312, 0.08495, 0.07767, 0.07118, 0.06538, 0.06009, 0.05536,
      0.05106, 0.04707, 0.04345, 0.04017, 0.03715, 0.03434, 0.03171, 0.02932,
      0.02709, 0.025, 0.02305, 0.02114, 0.0194, 0.018, 0.01708, 0.15, 0.02325,
      0.02325, 0.12113, 0.15375, 0.17006, 0.16299, 0.1562, 0.14955, 0.14175,
      0.13275, 0.12335, 0.11445, 0.10629, 0.09884, 0.09198, 0.08563, 0.07999,
      0.07474, 0.06999, 0.06561, 0.06157, 0.05781, 0.05432, 0.05108, 0.04807,
      0.04525, 0.04259, 0.04004, 0.03769, 0.03539, 0.03422, 0.2, 0.0288, 0.0288,
      0.1292, 0.16267, 0.1794, 0.1746, 0.16937, 0.16486, 0.16073, 0.15611,
      0.15128, 0.14504, 0.1372, 0.12923, 0.12141, 0.11408, 0.10737, 0.10112,
      0.09537, 0.09004, 0.08512, 0.08044, 0.07616, 0.07221, 0.06848, 0.06498,
      0.06172, 0.05858, 0.05567, 0.05283, 0.05112, 0.25, 0.18212, 0.18212,
      0.18212, 0.18213, 0.18213, 0.18015, 0.17692, 0.17304, 0.16947, 0.16622,
      0.16353, 0.16086, 0.15717, 0.15258, 0.14707, 0.13973, 0.13266, 0.12574,
      0.11926, 0.11324, 0.10755, 0.10232, 0.09734, 0.0927, 0.08834, 0.08429,
      0.08044, 0.0768, 0.07334, 0.07001, 0.06778, 0.3, 0.17483, 0.17483, 0.17483,
      0.17482, 0.17482, 0.17757, 0.1794, 0.17829, 0.17573, 0.17283, 0.17013,
      0.16775, 0.1659, 0.16433, 0.16187, 0.1576, 0.15354, 0.14794, 0.14137,
      0.13505, 0.12886, 0.12307, 0.1175, 0.1123, 0.10744, 0.10283, 0.09847,
      0.09429, 0.09041, 0.08667, 0.08393, 0.35, 0.17693, 0.17693, 0.17693,
      0.17693, 0.17693, 0.17693, 0.17693, 0.17693, 0.17693, 0.17702, 0.17563,
      0.17325, 0.1713, 0.16964, 0.16797, 0.16655, 0.16544, 0.16224, 0.15882,
      0.15479, 0.14868, 0.14265, 0.13677, 0.13113, 0.12577, 0.12067, 0.11588,
      0.11129, 0.10697, 0.10284, 0.09964, 0.4, 0.16951, 0.16951, 0.16951,
      0.16951, 0.16951, 0.16951, 0.16951, 0.16951, 0.16951, 0.16951, 0.17552,
      0.17644, 0.17597, 0.17397, 0.17186, 0.16997, 0.16992, 0.1692, 0.16889,
      0.16701, 0.16406, 0.16048, 0.15476, 0.14903, 0.14343, 0.13797, 0.13278,
      0.12776, 0.12306, 0.11854, 0.11497 };

    static real_T eml_dv6[320] = { 0.0, 0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7,
      0.8, 0.9, 1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0, 2.1, 2.2,
      2.3, 2.4, 2.5, 2.6, 2.7, 2.8, 2.9, 3.0, 0.0, -0.0669, -0.0669, -0.0414,
      -0.0329, -0.02865, -0.0261, -0.0244, -0.01236, -0.00786, -0.00747,
      -0.00785, -0.00807, -0.00828, -0.00858, -0.00883, -0.00921, -0.00954,
      -0.00975, -0.01, -0.01029, -0.01058, -0.01084, -0.01105, -0.01132,
      -0.01157, -0.01182, -0.01209, -0.01233, -0.01262, -0.01285, -0.01308, 0.05,
      -0.06115, -0.06115, 0.0106, 0.03452, 0.04647, 0.05365, 0.05843, 0.05784,
      0.05228, 0.04666, 0.04166, 0.03739, 0.03368, 0.0304, 0.02749, 0.0249,
      0.02258, 0.02047, 0.01857, 0.01684, 0.01526, 0.01379, 0.01245, 0.0112,
      0.01004, 0.00896, 0.00795, 0.00699, 0.00608, 0.00523, 0.0044, 0.1, -0.1146,
      -0.1146, 0.02195, 0.06747, 0.09022, 0.10388, 0.11298, 0.11136, 0.1024,
      0.09346, 0.08544, 0.07836, 0.07207, 0.06648, 0.06146, 0.05696, 0.05291,
      0.04925, 0.04592, 0.04291, 0.04015, 0.03762, 0.03527, 0.03312, 0.03112,
      0.02926, 0.02752, 0.02589, 0.02437, 0.02292, 0.02154, 0.15, -0.22725,
      -0.22725, -0.00735, 0.06595, 0.1026, 0.12459, 0.13925, 0.14818, 0.14252,
      0.13293, 0.12351, 0.11485, 0.10689, 0.09968, 0.09307, 0.08697, 0.08146,
      0.07659, 0.07205, 0.0679, 0.0641, 0.06064, 0.05742, 0.05443, 0.05165,
      0.04906, 0.04662, 0.04436, 0.04224, 0.04024, 0.03833, 0.2, -0.2236,
      -0.2236, 0.0015, 0.07653, 0.11405, 0.13656, 0.15157, 0.1642, 0.16553,
      0.15998, 0.15272, 0.14367, 0.1373, 0.12938, 0.12193, 0.11496, 0.10849,
      0.10255, 0.09702, 0.09198, 0.08726, 0.08292, 0.07894, 0.07507, 0.07158,
      0.06832, 0.06528, 0.06244, 0.05973, 0.05731, 0.05491, 0.25, -0.14975,
      -0.14975, 0.03537, 0.09708, 0.12794, 0.14645, 0.15879, 0.17164, 0.1765,
      0.17331, 0.16855, 0.16405, 0.159, 0.153, 0.1467, 0.14005, 0.13322, 0.12665,
      0.12047, 0.11471, 0.10929, 0.10425, 0.09953, 0.09513, 0.09101, 0.08721,
      0.08358, 0.08017, 0.07696, 0.07394, 0.07107, 0.3, -0.0846, -0.0846, 0.0648,
      0.1146, 0.1395, 0.15444, 0.1644, 0.17473, 0.18026, 0.17967, 0.17766,
      0.17452, 0.17105, 0.16756, 0.16376, 0.1595, 0.15396, 0.14808, 0.14212,
      0.13599, 0.13015, 0.12454, 0.11928, 0.11435, 0.1097, 0.10532, 0.10118,
      0.09729, 0.09366, 0.09018, 0.08686, 0.35, -0.43785, -0.43785, -0.08488,
      0.03278, 0.09161, 0.12691, 0.15044, 0.16725, 0.17986, 0.18095, 0.18064,
      0.17942, 0.17815, 0.17645, 0.17407, 0.17148, 0.16826, 0.16475, 0.16018,
      0.1549, 0.14941, 0.14372, 0.13807, 0.13277, 0.12763, 0.12282, 0.11822,
      0.11392, 0.10985, 0.10595, 0.10226, 0.4, 0.17604, 0.17604, 0.17604,
      0.17604, 0.17604, 0.17604, 0.17604, 0.17604, 0.17604, 0.17604, 0.17884,
      0.18113, 0.18117, 0.18037, 0.17957, 0.17875, 0.17735, 0.17551, 0.17282,
      0.16964, 0.1657, 0.16076, 0.15551, 0.15021, 0.1448, 0.13965, 0.13471,
      0.13003, 0.12553, 0.12128, 0.11723 };

    static real_T eml_dv7[320] = { 0.0, 0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7,
      0.8, 0.9, 1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0, 2.1, 2.2,
      2.3, 2.4, 2.5, 2.6, 2.7, 2.8, 2.9, 3.0, 0.0, 0.0, 0.0, -0.02318, -0.0309,
      -0.03476, -0.03708, -0.03862, -0.03973, -0.03097, -0.02088, -0.01338,
      -0.00985, -0.00903, -0.0092, -0.00955, -0.00987, -0.01019, -0.01061,
      -0.0109, -0.01118, -0.01142, -0.01165, -0.01194, -0.01221, -0.01248,
      -0.01274, -0.01303, -0.0133, -0.01342, -0.01367, -0.014, 0.05, -0.0718,
      -0.0718, -0.01, 0.0106, 0.0209, 0.02708, 0.0312, 0.03414, 0.03635, 0.03807,
      0.03814, 0.03625, 0.03317, 0.02997, 0.0271, 0.0245, 0.02217, 0.02006,
      0.01817, 0.01645, 0.01487, 0.01342, 0.01205, 0.0108, 0.00961, 0.0085,
      0.00746, 0.00646, 0.00552, 0.00462, 0.00376, 0.1, -0.1492, -0.1492,
      -0.01378, 0.03137, 0.05394, 0.06748, 0.07651, 0.08296, 0.0846, 0.08469,
      0.0822, 0.07742, 0.07173, 0.06623, 0.06129, 0.05683, 0.05279, 0.04915,
      0.04586, 0.04286, 0.04009, 0.03756, 0.03521, 0.03303, 0.03101, 0.02912,
      0.02735, 0.02568, 0.02408, 0.02258, 0.02114, 0.15, -0.2322, -0.2322,
      -0.0345, 0.0314, 0.06435, 0.08412, 0.0973, 0.10671, 0.11378, 0.11898,
      0.11882, 0.11367, 0.10666, 0.09958, 0.09304, 0.0871, 0.08169, 0.07666,
      0.07215, 0.06805, 0.06425, 0.06076, 0.05752, 0.0545, 0.05171, 0.04911,
      0.04665, 0.04434, 0.04225, 0.04019, 0.03815, 0.2, -0.3108, -0.3108,
      -0.0597, 0.024, 0.06585, 0.09096, 0.1077, 0.11966, 0.12863, 0.13722,
      0.14336, 0.14513, 0.13727, 0.12951, 0.12204, 0.11504, 0.10865, 0.10268,
      0.09722, 0.0922, 0.08749, 0.08315, 0.07915, 0.07538, 0.07188, 0.0686,
      0.06553, 0.06262, 0.05991, 0.05733, 0.0549, 0.25, -0.29825, -0.29825,
      -0.04888, 0.03425, 0.07581, 0.10075, 0.11738, 0.12925, 0.13816, 0.14753,
      0.1552, 0.16143, 0.16023, 0.15427, 0.14741, 0.14022, 0.13327, 0.12679,
      0.12062, 0.11487, 0.1095, 0.10448, 0.09978, 0.09539, 0.09132, 0.08744,
      0.08379, 0.08037, 0.07713, 0.07409, 0.07116, 0.3, -0.1929, -0.1929,
      0.00045, 0.0649, 0.09712, 0.11646, 0.12935, 0.13856, 0.14546, 0.1544,
      0.1626, 0.17051, 0.17323, 0.17063, 0.16618, 0.16062, 0.15459, 0.14846,
      0.14218, 0.13603, 0.13029, 0.12474, 0.11956, 0.11464, 0.10997, 0.10561,
      0.10148, 0.09759, 0.09389, 0.09038, 0.08707, 0.35, -0.3255, -0.3255,
      -0.05268, 0.03827, 0.08374, 0.11102, 0.12921, 0.1422, 0.15194, 0.15995,
      0.16667, 0.17503, 0.18048, 0.17963, 0.17755, 0.17442, 0.17054, 0.16565,
      0.16051, 0.15523, 0.14947, 0.14373, 0.1382, 0.13294, 0.1279, 0.12306,
      0.11854, 0.11423, 0.11011, 0.10623, 0.10251, 0.4, -1.0972, -1.0972, -0.389,
      -0.15293, -0.0349, 0.03592, 0.08313, 0.11686, 0.14215, 0.16182, 0.17,
      0.17669, 0.18227, 0.18403, 0.18423, 0.18232, 0.18012, 0.17753, 0.1744,
      0.17027, 0.16576, 0.16086, 0.15556, 0.15019, 0.1449, 0.13976, 0.13491,
      0.13027, 0.12577, 0.12156, 0.11749 };

    static real_T eml_dv8[64] = { 0.0, 0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7,
      0.8, 0.9, 1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0, 2.1, 2.2,
      2.3, 2.4, 2.5, 2.6, 2.7, 2.8, 2.9, 3.0, 0.0, 0.0492, 0.04342, 0.03927,
      0.03676, 0.03478, 0.02931, 0.0164, -0.00546, -0.00546, -0.00546, -0.00546,
      -0.00546, -0.00546, -0.00546, -0.00546, -0.00546, -0.00546, -0.00546,
      -0.00546, -0.00546, -0.00546, -0.00546, -0.00546, -0.00546, -0.00546,
      -0.00546, -0.00546, -0.00546, -0.00546, -0.00546, -0.00546 };

    for (eml_i0 = 0; eml_i0 < 8; eml_i0++) {
      for (eml_i1 = 0; eml_i1 < 13; eml_i1++) {
        ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)->
          E1[eml_i1 + 13 * eml_i0] = eml_dv0[eml_i1 + 13 * eml_i0];
        ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)->
          E2[eml_i1 + 13 * eml_i0] = eml_dv1[eml_i1 + 13 * eml_i0];
        ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)->
          E3[eml_i1 + 13 * eml_i0] = eml_dv2[eml_i1 + 13 * eml_i0];
      }
    }

    for (eml_i0 = 0; eml_i0 < 7; eml_i0++) {
      for (eml_i1 = 0; eml_i1 < 13; eml_i1++) {
        ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)->
          E4[eml_i1 + 13 * eml_i0] = eml_dv3[eml_i1 + 13 * eml_i0];
      }
    }

    for (eml_i0 = 0; eml_i0 < 10; eml_i0++) {
      for (eml_i1 = 0; eml_i1 < 32; eml_i1++) {
        ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)->
          CT1[eml_i1 + (eml_i0 << 5)] = eml_dv4[eml_i1 + (eml_i0 << 5)];
        ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)->
          CT2[eml_i1 + (eml_i0 << 5)] = eml_dv5[eml_i1 + (eml_i0 << 5)];
        ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)->
          CT3[eml_i1 + (eml_i0 << 5)] = eml_dv6[eml_i1 + (eml_i0 << 5)];
        ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)->
          CT4[eml_i1 + (eml_i0 << 5)] = eml_dv7[eml_i1 + (eml_i0 << 5)];
      }
    }

    for (eml_i0 = 0; eml_i0 < 2; eml_i0++) {
      for (eml_i1 = 0; eml_i1 < 32; eml_i1++) {
        ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
          ->CPmin[eml_i1 + (eml_i0 << 5)] = eml_dv8[eml_i1 + (eml_i0 << 5)];
      }
    }

    ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)->rpm1 =
      2800.0;
    ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)->rpm2 =
      2800.0;
    ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)->Th1 =
      -99999.0;
    ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)->Th2 =
      -99999.0;
  }
}

/* Output and update for atomic system: '<S6>/Calculate Thrust Parameters' */
void pa34m_CalculateThrustParameters(rtModel_pa34model_dueca_8b
  *pa34model_dueca_8b_rtM)
{
  /* Embedded MATLAB: '<S6>/Calculate Thrust Parameters' */
  pa34mode_c19_pa34model_dueca_8b(pa34model_dueca_8b_rtM);
}

/* Shared Utility Functions */
void lfcbjmglknopimgl_mldivide(real_T eml_A[9], real_T eml_B[3], real_T eml_Y[3])
{
  int32_T eml_k;
  int8_T eml_pivot[3];
  int32_T eml_p;
  real_T eml_maxval;
  int32_T eml_i;
  real_T eml_rtemp;
  int32_T eml_iv0[3];
  int32_T eml_iv1[3];
  for (eml_k = 0; eml_k < 3; eml_k++) {
    eml_pivot[eml_k] = (int8_T)(1 + eml_k);
  }

  for (eml_k = 0; eml_k < 2; eml_k++) {
    eml_p = eml_k + 1;
    eml_maxval = fabs(eml_A[eml_k + 3 * eml_k]);
    for (eml_i = eml_k + 2; eml_i <= 3; eml_i++) {
      eml_rtemp = fabs(eml_A[(eml_i - 1) + 3 * eml_k]);
      if (eml_rtemp > eml_maxval) {
        eml_maxval = eml_rtemp;
        eml_p = eml_i;
      }
    }

    if (eml_p != eml_k + 1) {
      for (eml_i = 0; eml_i < 3; eml_i++) {
        eml_maxval = eml_A[(eml_p - 1) + 3 * eml_i];
        eml_A[(eml_p - 1) + 3 * eml_i] = eml_A[eml_k + 3 * eml_i];
        eml_A[eml_k + 3 * eml_i] = eml_maxval;
      }

      eml_i = (int32_T)eml_pivot[eml_k];
      eml_pivot[eml_k] = eml_pivot[eml_p - 1];
      eml_pivot[eml_p - 1] = (int8_T)eml_i;
    }

    if (eml_A[eml_k + 3 * eml_k] != 0.0) {
      for (eml_i = eml_k + 2; eml_i <= 3; eml_i++) {
        eml_A[(eml_i - 1) + 3 * eml_k] /= eml_A[eml_k + 3 * eml_k];
      }
    }

    for (eml_i = eml_k + 2; eml_i <= 3; eml_i++) {
      for (eml_p = eml_k + 2; eml_p <= 3; eml_p++) {
        eml_A[(eml_p - 1) + 3 * (eml_i - 1)] -= eml_A[(eml_p - 1) + 3 * eml_k] *
          eml_A[eml_k + 3 * (eml_i - 1)];
      }
    }
  }

  for (eml_k = 0; eml_k < 3; eml_k++) {
    eml_Y[eml_k] = 0.0;
    eml_iv0[eml_k] = eml_k;
    eml_iv1[eml_k] = eml_pivot[eml_k] - 1;
  }

  for (eml_k = 0; eml_k < 3; eml_k++) {
    eml_Y[eml_iv0[eml_k]] = eml_B[eml_iv1[eml_k]];
  }

  for (eml_i = 0; eml_i < 3; eml_i++) {
    for (eml_p = eml_i + 2; eml_p <= 3; eml_p++) {
      eml_Y[eml_p - 1] -= eml_Y[eml_i] * eml_A[(eml_p - 1) + 3 * eml_i];
    }
  }

  for (eml_i = 3; eml_i > 0; eml_i += -1) {
    eml_Y[eml_i - 1] /= eml_A[(eml_i - 1) + 3 * (eml_i - 1)];
    eml_p = eml_i - 1;
    for (eml_k = 1; eml_k <= eml_p; eml_k++) {
      eml_Y[eml_k - 1] -= eml_Y[eml_i - 1] * eml_A[(eml_k - 1) + 3 * (eml_i - 1)];
    }
  }
}

/* Shared Utility Functions */
void ecjegdjmimgdkngl_min(real_T eml_x[6], real_T eml_minval[3])
{
  int32_T eml_ix;
  int32_T eml_iy;
  int32_T eml_j;
  real_T eml_mtmp;
  int32_T eml_ix_0;
  for (eml_ix = 0; eml_ix < 3; eml_ix++) {
    eml_minval[eml_ix] = 0.0;
  }

  eml_ix = 0;
  eml_iy = 0;
  for (eml_j = 0; eml_j < 3; eml_j++) {
    eml_ix++;
    eml_mtmp = eml_x[eml_ix - 1];
    eml_ix_0 = eml_ix + 3;
    if ((!((boolean_T)rtIsNaN(eml_x[eml_ix_0 - 1]))) && (((boolean_T)rtIsNaN
          (eml_mtmp)) || (eml_x[eml_ix_0 - 1] < eml_mtmp))) {
      eml_mtmp = eml_x[eml_ix_0 - 1];
    }

    eml_iy++;
    eml_minval[eml_iy - 1] = eml_mtmp;
  }
}

/* Shared Utility Functions */
real_T djmobaaadjmofkng_min(real_T eml_x[2])
{
  real_T eml_minval;
  eml_minval = eml_x[0];
  if ((!((boolean_T)rtIsNaN(eml_x[1]))) && (((boolean_T)rtIsNaN(eml_minval)) ||
       (eml_x[1] < eml_minval))) {
    return eml_x[1];
  }

  return eml_minval;
}

real_T ppphopphfkngdbie_max(real_T eml_x[2])
{
  real_T eml_maxval;
  eml_maxval = eml_x[0];
  if ((!((boolean_T)rtIsNaN(eml_x[1]))) && (((boolean_T)rtIsNaN(eml_maxval)) ||
       (eml_x[1] > eml_maxval))) {
    return eml_x[1];
  }

  return eml_maxval;
}

/* Initial conditions for root system: '<Root>' */
static void MdlInitialize(rtModel_pa34model_dueca_8b *pa34model_dueca_8b_rtM)
{
  {
    int32_T i;

    /* Integrator Block: '<S1>/Trim State' */
    if (rtmIsFirstInitCond(pa34model_dueca_8b_rtM)) {
      ((ContinuousStates_pa34model_duec *)
        pa34model_dueca_8b_rtM->ModelData.contStates)->TrimState_CSTATE[0] = 0.0;
      ((ContinuousStates_pa34model_duec *)
        pa34model_dueca_8b_rtM->ModelData.contStates)->TrimState_CSTATE[1] = 0.0;
      ((ContinuousStates_pa34model_duec *)
        pa34model_dueca_8b_rtM->ModelData.contStates)->TrimState_CSTATE[2] = 0.0;
      ((ContinuousStates_pa34model_duec *)
        pa34model_dueca_8b_rtM->ModelData.contStates)->TrimState_CSTATE[3] =
        6.1723961544292550E+001;
      ((ContinuousStates_pa34model_duec *)
        pa34model_dueca_8b_rtM->ModelData.contStates)->TrimState_CSTATE[4] = 0.0;
      ((ContinuousStates_pa34model_duec *)
        pa34model_dueca_8b_rtM->ModelData.contStates)->TrimState_CSTATE[5] =
        1.0756466534785893E+000;
      ((ContinuousStates_pa34model_duec *)
        pa34model_dueca_8b_rtM->ModelData.contStates)->TrimState_CSTATE[6] = 0.0;
      ((ContinuousStates_pa34model_duec *)
        pa34model_dueca_8b_rtM->ModelData.contStates)->TrimState_CSTATE[7] =
        1.7424963634836945E-002;
      ((ContinuousStates_pa34model_duec *)
        pa34model_dueca_8b_rtM->ModelData.contStates)->TrimState_CSTATE[8] = 0.0;
      ((ContinuousStates_pa34model_duec *)
        pa34model_dueca_8b_rtM->ModelData.contStates)->TrimState_CSTATE[9] = 0.0;
      ((ContinuousStates_pa34model_duec *)
        pa34model_dueca_8b_rtM->ModelData.contStates)->TrimState_CSTATE[10] =
        0.0;
      ((ContinuousStates_pa34model_duec *)
        pa34model_dueca_8b_rtM->ModelData.contStates)->TrimState_CSTATE[11] =
        -9.1440000000000009E+002;
    }

    ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
      ->TrimState_IWORK.IcNeedsLoading = 1;
    for (i = 0; i < 12; i++) {
      /* InitializeConditions for UnitDelay: '<S34>/Unit Delay' */
      ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
        ->UnitDelay_DSTATE[i] = pa34model_dueca_8b_ConstP.UnitDelay_X0[i];
    }

    /* InitializeConditions for Integrator: '<S33>/Integrator' */
    ((ContinuousStates_pa34model_duec *)
      pa34model_dueca_8b_rtM->ModelData.contStates)->Integrator_CSTATE[0] = 0.0;
    ((ContinuousStates_pa34model_duec *)
      pa34model_dueca_8b_rtM->ModelData.contStates)->Integrator_CSTATE[1] = 0.0;
    ((ContinuousStates_pa34model_duec *)
      pa34model_dueca_8b_rtM->ModelData.contStates)->Integrator_CSTATE[2] = 0.0;

    /* InitializeConditions for Memory: '<S33>/Memory' */
    ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
      ->Memory_PreviousInput[0] = 0.0;
    ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
      ->Memory_PreviousInput[1] = 0.0;

    /* Integrator Block: '<S6>/Initial Engine State' */
    if (rtmIsFirstInitCond(pa34model_dueca_8b_rtM)) {
      ((ContinuousStates_pa34model_duec *)
        pa34model_dueca_8b_rtM->ModelData.contStates)->
        InitialEngineState_CSTATE[0] = 150.0;
      ((ContinuousStates_pa34model_duec *)
        pa34model_dueca_8b_rtM->ModelData.contStates)->
        InitialEngineState_CSTATE[1] = 150.0;
    }

    ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
      ->InitialEngineState_IWORK.IcNeedsLoading = 1;

    /* Initialize code for chart: '<S10>/adjusting CG due  to failure' */
    ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
      ->W_basis_not_empty = false;

    /* InitializeConditions for Memory: '<S9>/Memory1' */
    ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
      ->Memory1_PreviousInput = 1.0;
    for (i = 0; i < 12; i++) {
      /* InitializeConditions for Memory: '<S9>/Memory' */
      ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
        ->Memory_PreviousInput_j[i] = 0.0;
    }

    CalculateThrustParameters_Init(pa34model_dueca_8b_rtM);
    pa34mo_AEROFORCESENMOMENTS_Init(pa34model_dueca_8b_rtM);

    /* Initialize code for chart: '<S6>/Ground Model' */
    ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
      ->wheelspin_left = 0.0;
    ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
      ->wheelspin_right = 0.0;
  }
}

/* Start for root system: '<Root>' */
static void MdlStart(rtModel_pa34model_dueca_8b *pa34model_dueca_8b_rtM)
{
  /* RandomNumber Block: '<S37>/White Noise' */
  {
    uint32_T *RandSeed = (uint32_T *) &((D_Work_pa34model_dueca_8b *)
      pa34model_dueca_8b_rtM->Work.dwork)->RandSeed[0];
    uint32_T r, t;

    {
      int_T i1;
      const real_T *p_Seed = &pa34model_dueca_8b_ConstP.WhiteNoise_Seed[0];
      real_T *dw_NextOutput = &((D_Work_pa34model_dueca_8b *)
        pa34model_dueca_8b_rtM->Work.dwork)->NextOutput[0];
      for (i1=0; i1 < 4; i1++) {
        *RandSeed = (uint32_T)(p_Seed[i1]);
        r = *RandSeed >> 16;
        t = *RandSeed & RT_BIT16;
        *RandSeed = ((*RandSeed - (r << 16) - t) << 16) + t + r;
        if (*RandSeed < 1) {
          *RandSeed = SEED0;
        }

        if (*RandSeed > MAXSEED) {
          *RandSeed = MAXSEED;
        }

        dw_NextOutput[i1] =
          rt_NormalRand(RandSeed++) * 1.0 + 0.0;
      }
    }
  }

  MdlInitialize(pa34model_dueca_8b_rtM);
}

/* Outputs for root system: '<Root>' */
static void MdlOutputs(rtModel_pa34model_dueca_8b *pa34model_dueca_8b_rtM, int_T
  tid)
{
  /* local block i/o variables */
  real_T rtb_TrimState[12];
  real_T rtb_MediumHighAltitudeIntensity;
  real_T rtb_Clock;
  real_T rtb_Integrator[3];
  real_T rtb_InitialEngineState[2];
  real_T rtb_Sum_c[3];
  real_T rtb_Clock_o;
  real_T rtb_Vwinde[3];
  real_T rtb_Vwindb[3];
  real_T rtb_Omegawindb[3];
  real_T rtb_Vwindb_o[3];
  real_T rtb_V;
  real_T rtb_h;
  real_T rtb_DCMbe[9];
  real_T rtb_wingspan;
  real_T rtb_Vw6m;
  real_T rtb_Vwdir;
  real_T rtb_Kturb;
  real_T rtb_Kgust;
  real_T rtb_egust;
  real_T rtb_Kshear;
  real_T rtb_rho;
  real_T rtb_T;
  real_T rtb_g;
  real_T rtb_output[47];
  real_T rtb_FMAb[6];
  real_T rtb_FMTb[6];
  real_T rtb_FMb[6];
  real_T rtb_FMGb[6];
  real_T rtb_FMair[6];
  real_T rtb_xge[3];
  real_T rtb_yge[3];
  real_T rtb_TmpHiddenBufferAtSFunctionI[6];
  real_T rtb_TmpHiddenBufferAtSFunctio_a[12];
  real_T rtb_TmpHiddenBufferAtSFunctio_p[12];
  real_T rtb_TmpHiddenBufferAtSFunctio_n[12];
  real_T rtb_TmpHiddenBufferAtSFunctio_i[6];
  real_T rtb_TmpHiddenBufferAtSFunctio_o[26];
  real_T rtb_TmpHiddenBufferAtSFunctio_g[26];
  real_T rtb_PreLookUpIndexSearchaltitud;
  uint32_T rtb_PreLookUpIndexSearchaltit_o;
  boolean_T rtb_landed;

  {
    real_T fractionTmp_0d;
    real_T frac[2];
    uint32_T bpIndex[2];
    int32_T i;
    real_T rtb_Product_idx;
    real_T rtb_Product_idx_0;
    real_T rtb_Product1_idx;
    real_T rtb_Product1_idx_0;
    real_T rtb_Product1_idx_1;

    /* Integrator: '<S1>/Trim State' */
    if (((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
        ->TrimState_IWORK.IcNeedsLoading) {
      {
        int_T i1;
        real_T *xc = &((ContinuousStates_pa34model_duec *)
                       pa34model_dueca_8b_rtM->ModelData.contStates)
          ->TrimState_CSTATE[0];
        const real_T *u1 = &pa34model_dueca_8b_rtC(M)->Constant1[0];
        for (i1=0; i1 < 12; i1++) {
          xc[i1] = u1[i1];
        }
      }

      ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
        ->TrimState_IWORK.IcNeedsLoading = 0;
    }

    {
      int_T i1;
      real_T *y0 = rtb_TrimState;
      real_T *xc = &((ContinuousStates_pa34model_duec *)
                     pa34model_dueca_8b_rtM->ModelData.contStates)
        ->TrimState_CSTATE[0];
      for (i1=0; i1 < 12; i1++) {
        y0[i1] = xc[i1];
      }
    }

    /* Embedded MATLAB: '<S22>/Calc Atmos' */
    {
      real_T eml_he;

      /*  This block supports the Embedded MATLAB subset. */
      /*  See the help menu for details.  */
      /* Define constants */
      /* m/s2 */
      /* K */
      /* kg/m3 */
      /* K/m */
      /* K m2/s2 */
      /* m */
      /* m */
      eml_he = -rtb_TrimState[11];

      /* Calculate rho */
      eml_he = 6.37102E+006 * eml_he / (6.37102E+006 + eml_he);
      rtb_T = 2.8815E+002 + -0.0065 * eml_he;
      rtb_rho = 1.225 * pow(rtb_T / 2.8815E+002, 4.2558798127166773E+000);
      if (eml_he > 11000.0) {
        rtb_rho = rtb_rho * exp(-9.80665 / (2.8705287E+002 * rtb_T) * (eml_he -
          11000.0));
      }

      /* Calculate g */
      rtb_g = 9.82;
    }

    /* SignalConversion: '<S31>/TmpHiddenBufferAt SFunction Inport2' incorporates:
     *  Constant: '<S24>/chord'
     *  Constant: '<S24>/location_AERORP.x'
     *  Constant: '<S24>/location_AERORP.y'
     *  Constant: '<S24>/location_AERORP.z'
     *  Constant: '<S24>/wingarea'
     *  Constant: '<S24>/wingspan'
     */
    rtb_TmpHiddenBufferAtSFunctionI[0] = 19.39;
    rtb_TmpHiddenBufferAtSFunctionI[1] = 11.85;
    rtb_TmpHiddenBufferAtSFunctionI[2] = 1.61;
    rtb_TmpHiddenBufferAtSFunctionI[3] = 0.0;
    rtb_TmpHiddenBufferAtSFunctionI[4] = 0.0;
    rtb_TmpHiddenBufferAtSFunctionI[5] = 0.0;

    /* Embedded MATLAB: '<S22>/Calc Wind params' incorporates:
     *   Inport: '<Root>/In1'
     */
    {
      int32_T eml_i0;
      real_T eml_Vb[3];
      real_T eml_phi;
      real_T eml_theta;
      real_T eml_psi;
      real_T eml_d0;
      static boolean_T eml_bv0[3] = { true, false, false };

      real_T eml_dv0[9];
      real_T eml_dv1[9];
      static boolean_T eml_bv1[3] = { false, true, false };

      real_T eml_dv2[9];
      int32_T eml_i1;
      real_T eml_dv3[9];
      int32_T eml_i2;
      static boolean_T eml_bv2[3] = { false, false, true };

      /*  This block supports the Embedded MATLAB subset. */
      /*  See the help menu for details.  */
      /* state = col(p,q,r,u,v,w,\phi,\theta,\psi,x,y,z) */
      for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
        eml_Vb[eml_i0] = rtb_TrimState[3 + eml_i0];
      }

      eml_phi = rtb_TrimState[6];
      eml_theta = rtb_TrimState[7];
      eml_psi = rtb_TrimState[8];

      /* geometry = col (S,b,cbar,rp_aero (3)) */
      rtb_wingspan = rtb_TmpHiddenBufferAtSFunctionI[1];

      /* wind = col(Vw6m,direction,Kturb,Kgust,eventgust,Kshear) */
      rtb_Vw6m = ((ExternalInputs_pa34model_dueca_ *)
                  pa34model_dueca_8b_rtM->ModelData.inputs)->In1[10];
      rtb_Vwdir = ((ExternalInputs_pa34model_dueca_ *)
                   pa34model_dueca_8b_rtM->ModelData.inputs)->In1[11];
      rtb_Kturb = ((ExternalInputs_pa34model_dueca_ *)
                   pa34model_dueca_8b_rtM->ModelData.inputs)->In1[12];
      rtb_Kgust = ((ExternalInputs_pa34model_dueca_ *)
                   pa34model_dueca_8b_rtM->ModelData.inputs)->In1[13];
      rtb_egust = ((ExternalInputs_pa34model_dueca_ *)
                   pa34model_dueca_8b_rtM->ModelData.inputs)->In1[14];
      rtb_Kshear = ((ExternalInputs_pa34model_dueca_ *)
                    pa34model_dueca_8b_rtM->ModelData.inputs)->In1[15];

      /* % Calculate RF transformation matrices */
      /* transformation matrix from RFe (earth) to RFb (body) */
      /* create output */
      eml_d0 = 0.0;
      for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
        eml_d0 += eml_Vb[eml_i0] * eml_Vb[eml_i0];
      }

      rtb_V = sqrt(eml_d0);
      rtb_h = -rtb_TrimState[11];
      for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
        eml_dv0[3 * eml_i0] = (real_T)eml_bv0[eml_i0];
      }

      eml_dv0[1] = 0.0;
      eml_dv0[4] = cos(eml_phi);
      eml_dv0[7] = sin(eml_phi);
      eml_dv0[2] = 0.0;
      eml_dv0[5] = -sin(eml_phi);
      eml_dv0[8] = cos(eml_phi);
      eml_dv1[0] = cos(eml_theta);
      eml_dv1[3] = 0.0;
      eml_dv1[6] = -sin(eml_theta);
      for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
        eml_dv1[1 + 3 * eml_i0] = (real_T)eml_bv1[eml_i0];
      }

      eml_dv1[2] = sin(eml_theta);
      eml_dv1[5] = 0.0;
      eml_dv1[8] = cos(eml_theta);
      eml_dv2[0] = cos(eml_psi);
      eml_dv2[3] = sin(eml_psi);
      eml_dv2[6] = 0.0;
      eml_dv2[1] = -sin(eml_psi);
      eml_dv2[4] = cos(eml_psi);
      eml_dv2[7] = 0.0;
      for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
        for (eml_i1 = 0; eml_i1 < 3; eml_i1++) {
          eml_dv3[eml_i0 + 3 * eml_i1] = 0.0;
          for (eml_i2 = 0; eml_i2 < 3; eml_i2++) {
            eml_dv3[eml_i0 + 3 * eml_i1] += eml_dv0[eml_i0 + 3 * eml_i2] *
              eml_dv1[eml_i2 + 3 * eml_i1];
          }
        }

        eml_dv2[2 + 3 * eml_i0] = (real_T)eml_bv2[eml_i0];
      }

      for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
        for (eml_i1 = 0; eml_i1 < 3; eml_i1++) {
          rtb_DCMbe[eml_i0 + 3 * eml_i1] = 0.0;
          for (eml_i2 = 0; eml_i2 < 3; eml_i2++) {
            rtb_DCMbe[eml_i0 + 3 * eml_i1] = rtb_DCMbe[eml_i0 + 3 * eml_i1] +
              eml_dv3[eml_i0 + 3 * eml_i2] * eml_dv2[eml_i2 + 3 * eml_i1];
          }
        }
      }
    }

    /* Embedded MATLAB: '<S32>/Wind Shear Model Embedded' incorporates:
     *  Constant: '<S32>/Flight phase = C [0//1]'
     */
    {
      real_T eml_z0;
      real_T eml_x[2];
      real_T eml_extremum;
      real_T eml_dv0[9];
      int32_T eml_i0;
      static boolean_T eml_bv0[3] = { false, false, true };

      real_T eml_dv1[3];
      int32_T eml_i1;

      /*  Calculate wind shear */
      /*  Model according to MIL-F-8785C */
      /*  */
      /*  Inputs: phaseC [0/1], Vw6m [m/s], Vwdir [rad], h [m], DCM [3x3](not used) */
      /*  Outputs: Vwindb [m/s] */
      /* conversion factors */
      if (0.0 != 0.0) {
        /* determine z0 */
        eml_z0 = 0.15;

        /* ft */
      } else {
        eml_z0 = 2.0;

        /* ft */
      }

      /* altitude */
      eml_x[0] = rtb_h * 3.2808;
      eml_x[1] = 3.0;
      eml_extremum = eml_x[0];
      if ((!((boolean_T)rtIsNaN(eml_x[1]))) && (((boolean_T)rtIsNaN(eml_extremum))
           || (eml_x[1] > eml_extremum))) {
        eml_extremum = eml_x[1];
      }

      /* lower limit 3ft */
      /* calc ref_height */
      if (rtb_Kshear != 0.0) {
        /* calc wind */
        eml_z0 = (-rtb_Vw6m) * log(eml_extremum / eml_z0) / log(20.0 / eml_z0);

        /* wind in RFwind */
      } else {
        eml_z0 = -rtb_Vw6m;

        /* wind in RFwind */
      }

      /* uwindw = -Vw6m*(hft/ref_height)^(1/7); %power law */
      /* calc transformation matrix */
      /* transformation from RFwind to RFe */
      /* Calc VwindE */
      eml_dv0[0] = cos(rtb_Vwdir);
      eml_dv0[3] = -sin(rtb_Vwdir);
      eml_dv0[6] = 0.0;
      eml_dv0[1] = sin(rtb_Vwdir);
      eml_dv0[4] = cos(rtb_Vwdir);
      eml_dv0[7] = 0.0;
      for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
        eml_dv0[2 + 3 * eml_i0] = (real_T)eml_bv0[eml_i0];
      }

      eml_dv1[0] = eml_z0;
      eml_dv1[1] = 0.0;
      eml_dv1[2] = 0.0;
      for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
        rtb_Vwinde[eml_i0] = 0.0;
        for (eml_i1 = 0; eml_i1 < 3; eml_i1++) {
          rtb_Vwinde[eml_i0] = rtb_Vwinde[eml_i0] + eml_dv0[eml_i0 + 3 * eml_i1]
            * eml_dv1[eml_i1];
        }
      }

      /* wind in RFe */
      /* Vwindb = DCM*Vwinde; %wind in RFb */
    }

    /* Gain: '<S39>/m2ft' */
    rtb_PreLookUpIndexSearchaltitud = 3.2808 * rtb_h;

    /* PreLookup: '<S39>/PreLook-Up Index Search  (altitude)' */
    rtb_PreLookUpIndexSearchaltit_o = plook_bincpa
      (rtb_PreLookUpIndexSearchaltitud,
       &pa34model_dueca_8b_ConstP.PreLookUpIndexSearch[0], 11U,
       &rtb_PreLookUpIndexSearchaltitud, &((D_Work_pa34model_dueca_8b *)
        pa34model_dueca_8b_rtM->Work.dwork)->PreLookUpIndexSearchaltitude_DW);

    /* Interpolation_n-D: '<S39>/Medium//High Altitude Intensity' */
    fractionTmp_0d = rtb_PreLookUpIndexSearchaltitud;
    frac[0] = fractionTmp_0d;
    frac[1] = pa34model_dueca_8b_rtC(M)->PreLookUpIndexSearchprobofe;
    bpIndex[0] = rtb_PreLookUpIndexSearchaltit_o;
    bpIndex[1] = pa34model_dueca_8b_rtC(M)->PreLookUpIndexSearchprobo_a;
    rtb_MediumHighAltitudeIntensity = intrp2d_lca((uint32_T *)&bpIndex, (real_T *)
      &frac, &pa34model_dueca_8b_ConstP.MediumHighAltitudeIn[0], 12U,
      &pa34model_dueca_8b_ConstP.MediumHighAltitudeInt[0]);
    if (rtmIsSampleHit(pa34model_dueca_8b_rtM, 1, 0)) {
      /* RandomNumber: '<S37>/White Noise' */
      ((BlockIO_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->ModelData.blockIO
        )->WhiteNoise[0] = ((D_Work_pa34model_dueca_8b *)
                            pa34model_dueca_8b_rtM->Work.dwork)->NextOutput[0];
      ((BlockIO_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->ModelData.blockIO
        )->WhiteNoise[1] = ((D_Work_pa34model_dueca_8b *)
                            pa34model_dueca_8b_rtM->Work.dwork)->NextOutput[1];
      ((BlockIO_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->ModelData.blockIO
        )->WhiteNoise[2] = ((D_Work_pa34model_dueca_8b *)
                            pa34model_dueca_8b_rtM->Work.dwork)->NextOutput[2];
      ((BlockIO_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->ModelData.blockIO
        )->WhiteNoise[3] = ((D_Work_pa34model_dueca_8b *)
                            pa34model_dueca_8b_rtM->Work.dwork)->NextOutput[3];
      for (i = 0; i < 12; i++) {
        /* UnitDelay: '<S34>/Unit Delay' */
        ((BlockIO_pa34model_dueca_8b *)
          pa34model_dueca_8b_rtM->ModelData.blockIO)->UnitDelay[i] =
          ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
          ->UnitDelay_DSTATE[i];
      }
    }

    /* Embedded MATLAB: '<S34>/Dryden Wind Turbulence Model Embedded' incorporates:
     *  Constant: '<S34>/sample time (set in Mask)'
     */
    {
      real_T eml_n_u;
      real_T eml_n_v;
      real_T eml_n_w;
      real_T eml_n_p;
      int32_T eml_i0;
      real_T eml_vgw_d[2];
      real_T eml_wgw_d[2];
      real_T eml_b;
      real_T eml_h;
      real_T eml_V;
      real_T eml_Tew[9];
      static boolean_T eml_bv0[3] = { false, false, true };

      real_T eml_dv0[2];
      real_T eml_dv1[2];
      real_T eml_h_sat;
      real_T eml_Luvg_low;
      real_T eml_L_ug[2];
      real_T eml_L_vg[2];
      real_T eml_L_wg[2];
      real_T eml_dv2[2];
      real_T eml_dv3[2];
      real_T eml_sigma_wg[2];
      real_T eml_y[2];
      real_T eml_x[2];
      real_T eml_a[2];
      real_T eml_dv4[2];
      real_T eml_vgw[2];
      int32_T eml_iv0[2];
      real_T eml_dv5[2];
      real_T eml_Vgw[6];
      int32_T eml_iv1[3];
      real_T eml_Omegawindb_high[3];
      int32_T eml_i1;
      int8_T eml_iv2[3];
      real_T eml_Vwindb_high[3];
      real_T eml_Omegagw[6];
      real_T eml_dv6[3];
      int8_T eml_iv3[3];

      /*  Calculate wind turbulence */
      /*  Model according to MIL-F-8785C */
      /*  */
      /*  Inputs: Vw6m [m/s], Vwdir [rad], h [m], sigma_uvwg_high [-], V [m/s], DCM [3x3], b [m], noise [-], ts [s], xgw_d [6x2] */
      /*  Outputs: Vwindb [m/s], Omegawindb [rad/s], xgw [6x2] */
      /* Settings */
      /* ft */
      /* ft, MIL-F-8785C */
      /* scale length at medium and high altitudes */
      /* noise = col(n_u,n_v,n_w,n_p) */
      eml_n_u = ((BlockIO_pa34model_dueca_8b *)
                 pa34model_dueca_8b_rtM->ModelData.blockIO)->WhiteNoise[0];
      eml_n_v = ((BlockIO_pa34model_dueca_8b *)
                 pa34model_dueca_8b_rtM->ModelData.blockIO)->WhiteNoise[1];
      eml_n_w = ((BlockIO_pa34model_dueca_8b *)
                 pa34model_dueca_8b_rtM->ModelData.blockIO)->WhiteNoise[2];
      eml_n_p = ((BlockIO_pa34model_dueca_8b *)
                 pa34model_dueca_8b_rtM->ModelData.blockIO)->WhiteNoise[3];

      /* xgw_d = col(ugw_d,vgw_d,wgw_d,pgw_d,qgw_d,rgw_d) */
      for (eml_i0 = 0; eml_i0 < 2; eml_i0++) {
        eml_vgw_d[eml_i0] = ((BlockIO_pa34model_dueca_8b *)
                             pa34model_dueca_8b_rtM->ModelData.blockIO)
          ->UnitDelay[eml_i0 + 2];
        eml_wgw_d[eml_i0] = ((BlockIO_pa34model_dueca_8b *)
                             pa34model_dueca_8b_rtM->ModelData.blockIO)
          ->UnitDelay[eml_i0 + 4];
      }

      /* conversion factors */
      /* convert units */
      eml_b = rtb_wingspan * 3.2808;
      eml_h = rtb_h * 3.2808;
      eml_V = rtb_V * 3.2808;

      /* calculate transformation matrices */
      eml_Tew[0] = cos(rtb_Vwdir);
      eml_Tew[3] = -sin(rtb_Vwdir);
      eml_Tew[6] = 0.0;
      eml_Tew[1] = sin(rtb_Vwdir);
      eml_Tew[4] = cos(rtb_Vwdir);
      eml_Tew[7] = 0.0;
      for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
        eml_Tew[2 + 3 * eml_i0] = (real_T)eml_bv0[eml_i0];
      }

      /* from RFwind to RFe */
      /* determine scale lengths */
      eml_dv0[0] = eml_h;
      eml_dv0[1] = 1000.0;
      eml_dv1[0] = djmobaaadjmofkng_min(eml_dv0);
      eml_dv1[1] = 10.0;
      eml_h_sat = ppphopphfkngdbie_max(eml_dv1);
      eml_Luvg_low = eml_h_sat / pow(0.177 + 0.000823 * eml_h_sat, 1.2);
      eml_L_ug[0] = eml_Luvg_low;
      eml_L_ug[1] = 1.74997872E+003;
      eml_L_vg[0] = eml_Luvg_low;
      eml_L_vg[1] = 1.74997872E+003;
      eml_L_wg[0] = eml_h_sat;
      eml_L_wg[1] = 1.74997872E+003;

      /* determine RMS turbulence intensities */
      eml_h_sat = rtb_Vw6m * 3.2808 * 0.1;
      eml_dv2[0] = eml_h;
      eml_dv2[1] = 1000.0;
      eml_dv3[0] = djmobaaadjmofkng_min(eml_dv2);
      eml_dv3[1] = 0.0;
      eml_Luvg_low = eml_h_sat / pow(0.177 + 0.000823 * ppphopphfkngdbie_max
        (eml_dv3), 0.4);
      eml_sigma_wg[0] = eml_h_sat;
      eml_sigma_wg[1] = rtb_MediumHighAltitudeIntensity;
      eml_h_sat = pow(eml_b, 2.0);
      for (eml_i0 = 0; eml_i0 < 2; eml_i0++) {
        eml_y[eml_i0] = pow(eml_L_wg[eml_i0] * eml_h_sat,
                            3.3333333333333331E-001);

        /* calculate velocity filters */
        eml_x[eml_i0] = sqrt(eml_V / eml_L_ug[eml_i0] * 2.0 * (0.01));
        eml_a[eml_i0] = sqrt(eml_V / eml_L_vg[eml_i0] * 2.0 * (0.01));
      }

      eml_dv4[0] = eml_Luvg_low;
      eml_dv4[1] = rtb_MediumHighAltitudeIntensity;
      for (eml_i0 = 0; eml_i0 < 2; eml_i0++) {
        eml_vgw[eml_i0] = (1.0 - eml_V / eml_L_vg[eml_i0] * (0.01)) *
          eml_vgw_d[eml_i0] + eml_a[eml_i0] * eml_n_v * eml_dv4[eml_i0];
      }

      for (eml_i0 = 0; eml_i0 < 2; eml_i0++) {
        eml_L_vg[eml_i0] = (1.0 - eml_V / eml_L_wg[eml_i0] * (0.01)) *
          eml_wgw_d[eml_i0] + sqrt(eml_V / eml_L_wg[eml_i0] * 2.0 * (0.01)) *
          eml_n_w * eml_sigma_wg[eml_i0];
        eml_iv0[eml_i0] = eml_i0;
      }

      eml_dv5[0] = eml_Luvg_low;
      eml_dv5[1] = rtb_MediumHighAltitudeIntensity;
      for (eml_i0 = 0; eml_i0 < 2; eml_i0++) {
        eml_Vgw[eml_i0] = (1.0 - eml_V / eml_L_ug[eml_i0] * (0.01)) *
          ((BlockIO_pa34model_dueca_8b *)
           pa34model_dueca_8b_rtM->ModelData.blockIO)->UnitDelay[eml_iv0[eml_i0]]
          + eml_x[eml_i0] * eml_n_u * eml_dv5[eml_i0];
      }

      for (eml_i0 = 0; eml_i0 < 2; eml_i0++) {
        eml_Vgw[eml_i0 + 2] = eml_vgw[eml_i0];
        eml_Vgw[eml_i0 + 4] = eml_L_vg[eml_i0];
      }

      /* calculate velocities */
      /* turbulence in RFe */
      for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
        eml_iv1[eml_i0] = eml_i0;
      }

      for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
        eml_Omegawindb_high[eml_i0] = 0.0;
        for (eml_i1 = 0; eml_i1 < 3; eml_i1++) {
          eml_Omegawindb_high[eml_i0] += eml_Tew[eml_i0 + 3 * eml_i1] *
            eml_Vgw[eml_iv1[eml_i1] << 1];
        }
      }

      for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
        rtb_Vwindb[eml_i0] = 0.0;
        for (eml_i1 = 0; eml_i1 < 3; eml_i1++) {
          rtb_Vwindb[eml_i0] = rtb_Vwindb[eml_i0] + rtb_DCMbe[eml_i0 + 3 *
            eml_i1] * eml_Omegawindb_high[eml_i1];
        }

        /* turbulence in RFb */
        eml_iv2[eml_i0] = (int8_T)eml_i0;
        eml_Vwindb_high[eml_i0] = eml_Vgw[1 + (eml_iv2[eml_i0] << 1)];
      }

      /* calculate angular rate filters */
      eml_n_u = eml_b * 4.0 / 3.1415926535897931E+000;

      /* q+ */
      eml_h_sat = eml_b * 3.0 / 3.1415926535897931E+000;
      eml_Luvg_low = 1.0 - eml_V / (eml_b * 4.0 / 3.1415926535897931E+000) *
        (0.01);
      eml_n_v = 1.0 - eml_V / (eml_b * 3.0 / 3.1415926535897931E+000) * (0.01);
      for (eml_i0 = 0; eml_i0 < 2; eml_i0++) {
        eml_n_w = 2.6 / sqrt(eml_L_wg[eml_i0] * eml_b);

        /* r- */
        eml_Omegagw[eml_i0] = (1.0 - eml_n_w * (0.01)) *
          ((BlockIO_pa34model_dueca_8b *)
           pa34model_dueca_8b_rtM->ModelData.blockIO)->UnitDelay[eml_i0 + 6] +
          sqrt(eml_n_w * 2.0 * (0.01)) * eml_n_p * (0.95 * eml_sigma_wg[eml_i0] /
          eml_y[eml_i0]);
        eml_Omegagw[eml_i0 + 2] = eml_Luvg_low * ((BlockIO_pa34model_dueca_8b *)
          pa34model_dueca_8b_rtM->ModelData.blockIO)->UnitDelay[eml_i0 + 8] +
          (eml_L_vg[eml_i0] - eml_wgw_d[eml_i0]) / eml_n_u;
        eml_Omegagw[eml_i0 + 4] = eml_n_v * ((BlockIO_pa34model_dueca_8b *)
          pa34model_dueca_8b_rtM->ModelData.blockIO)->UnitDelay[eml_i0 + 10] -
          (eml_vgw[eml_i0] - eml_vgw_d[eml_i0]) / eml_h_sat;
      }

      /* calculate angular rates */
      /* turbulence in RFe */
      for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
        eml_iv1[eml_i0] = eml_i0;
      }

      for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
        eml_dv6[eml_i0] = 0.0;
        for (eml_i1 = 0; eml_i1 < 3; eml_i1++) {
          eml_dv6[eml_i0] += eml_Tew[eml_i0 + 3 * eml_i1] *
            eml_Omegagw[eml_iv1[eml_i1] << 1];
        }
      }

      for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
        rtb_Omegawindb[eml_i0] = 0.0;
        for (eml_i1 = 0; eml_i1 < 3; eml_i1++) {
          rtb_Omegawindb[eml_i0] = rtb_Omegawindb[eml_i0] + rtb_DCMbe[eml_i0 + 3
            * eml_i1] * eml_dv6[eml_i1];
        }

        /* turbulence in RFb */
        eml_iv3[eml_i0] = (int8_T)eml_i0;
        eml_Omegawindb_high[eml_i0] = eml_Omegagw[1 + (eml_iv3[eml_i0] << 1)];
      }

      if (!(eml_h <= 1000.0)) {
        if (eml_h >= 2000.0) {
          for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
            rtb_Vwindb[eml_i0] = eml_Vwindb_high[eml_i0];
            rtb_Omegawindb[eml_i0] = eml_Omegawindb_high[eml_i0];
          }
        } else {
          /* interpolate */
          eml_h_sat = (eml_h - 1000.0) / 1000.0;
          for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
            rtb_Vwindb[eml_i0] = (eml_Vwindb_high[eml_i0] - rtb_Vwindb[eml_i0]) *
              eml_h_sat + rtb_Vwindb[eml_i0];
            rtb_Omegawindb[eml_i0] = (eml_Omegawindb_high[eml_i0] -
              rtb_Omegawindb[eml_i0]) * eml_h_sat + rtb_Omegawindb[eml_i0];
          }
        }
      } else {
        /* select velocities and angular rates */
      }

      for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
        rtb_Vwindb[eml_i0] = rtb_Vwindb[eml_i0] / 3.2808;

        /* output all velocities */
        for (eml_i1 = 0; eml_i1 < 2; eml_i1++) {
          ((BlockIO_pa34model_dueca_8b *)
            pa34model_dueca_8b_rtM->ModelData.blockIO)->xgw[eml_i1 + (eml_i0 <<
            1)] = eml_Vgw[eml_i1 + (eml_i0 << 1)];
        }
      }

      for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
        for (eml_i1 = 0; eml_i1 < 2; eml_i1++) {
          ((BlockIO_pa34model_dueca_8b *)
            pa34model_dueca_8b_rtM->ModelData.blockIO)->xgw[eml_i1 + ((eml_i0 +
            3) << 1)] = eml_Omegagw[eml_i1 + (eml_i0 << 1)];
        }
      }
    }

    /* Product: '<S32>/Product' */
    fractionTmp_0d = rtb_Kturb * rtb_Vwindb[0];
    rtb_Product_idx = rtb_Kturb * rtb_Vwindb[1];
    rtb_Product_idx_0 = rtb_Kturb * rtb_Vwindb[2];

    /* Clock: '<S33>/Clock' */
    rtb_Clock = rtmGetT(pa34model_dueca_8b_rtM);

    /* Integrator: '<S33>/Integrator' */
    rtb_Integrator[0] = ((ContinuousStates_pa34model_duec *)
                         pa34model_dueca_8b_rtM->ModelData.contStates)
      ->Integrator_CSTATE[0];
    rtb_Integrator[1] = ((ContinuousStates_pa34model_duec *)
                         pa34model_dueca_8b_rtM->ModelData.contStates)
      ->Integrator_CSTATE[1];
    rtb_Integrator[2] = ((ContinuousStates_pa34model_duec *)
                         pa34model_dueca_8b_rtM->ModelData.contStates)
      ->Integrator_CSTATE[2];
    if (rtmIsSampleHit(pa34model_dueca_8b_rtM, 1, 0)) {
      /* Memory: '<S33>/Memory' */
      ((BlockIO_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->ModelData.blockIO
        )->Memory[0] = ((D_Work_pa34model_dueca_8b *)
                        pa34model_dueca_8b_rtM->Work.dwork)
        ->Memory_PreviousInput[0];
      ((BlockIO_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->ModelData.blockIO
        )->Memory[1] = ((D_Work_pa34model_dueca_8b *)
                        pa34model_dueca_8b_rtM->Work.dwork)
        ->Memory_PreviousInput[1];
    }

    /* Embedded MATLAB: '<S33>/Discrete Wind Gust Model Embedded' incorporates:
     *  Constant: '<S33>/Gust amplitude [m//s]'
     *  Constant: '<S33>/Gust build up lenght [m]'
     */
    {
      real_T eml_event;
      int32_T eml_k;
      real_T eml_Xg[3];
      real_T eml_tstart;
      real_T eml_event_duration;
      real_T eml_dv0[6];
      eml_event = rtb_egust;

      /*  Calculate gust */
      /*  Model according to MIL-F-8785C */
      /*  */
      /*  Inputs: GustBuildUp [m], GustAmp [m/s], V [m/s], event [s], t [s], xgust [m], prev [s] */
      /*  Outputs: Vwindb [m/s], xgustdot [m/s], cur [s] */
      /* gust state = col(xg,yg,zg) */
      for (eml_k = 0; eml_k < 3; eml_k++) {
        eml_Xg[eml_k] = rtb_Integrator[eml_k];
      }

      /* gust length */
      /* prev = col(tstart,event_duration) */
      eml_tstart = ((BlockIO_pa34model_dueca_8b *)
                    pa34model_dueca_8b_rtM->ModelData.blockIO)->Memory[0];
      eml_event_duration = ((BlockIO_pa34model_dueca_8b *)
                            pa34model_dueca_8b_rtM->ModelData.blockIO)->Memory[1];
      if (eml_event_duration > 0.0) {
        eml_event = eml_event_duration;
      }

      /* calc wind */
      for (eml_k = 0; eml_k < 3; eml_k++) {
        rtb_Vwindb_o[eml_k] =
          (pa34model_dueca_8b_ConstP.Gustamplitudems_Value[eml_k]) / 2.0 * (1.0
          - cos(3.1415926535897931E+000 * eml_Xg[eml_k] /
                (pa34model_dueca_8b_ConstP.Gustbuilduplenghtm_Va[eml_k])));
      }

      if (eml_event > 0.0) {
        /* define gust phase */
        eml_k = 1;
        if (rtb_Clock > eml_tstart + eml_event) {
          eml_k = 2;
        }
      } else {
        eml_k = 0;
      }

      if (eml_k == 1) {
        /* calc xgustdot */
        /* build up */
        /* limit the integral */
        for (eml_k = 0; eml_k < 3; eml_k++) {
          eml_dv0[eml_k] =
            (pa34model_dueca_8b_ConstP.Gustbuilduplenghtm_Va[eml_k]) -
            eml_Xg[eml_k];
          eml_dv0[eml_k + 3] = 1.0;
        }

        ecjegdjmimgdkngl_min(eml_dv0, eml_Xg);
        for (eml_k = 0; eml_k < 3; eml_k++) {
          ((BlockIO_pa34model_dueca_8b *)
            pa34model_dueca_8b_rtM->ModelData.blockIO)->xgustdot[eml_k] = rtb_V *
            eml_Xg[eml_k];
        }

        ((BlockIO_pa34model_dueca_8b *)
          pa34model_dueca_8b_rtM->ModelData.blockIO)->cur[0] = eml_tstart;
        ((BlockIO_pa34model_dueca_8b *)
          pa34model_dueca_8b_rtM->ModelData.blockIO)->cur[1] = eml_event;
      } else if (eml_k == 2) {
        /* fade out */
        for (eml_k = 0; eml_k < 3; eml_k++) {
          eml_dv0[eml_k] = eml_Xg[eml_k];
          eml_dv0[eml_k + 3] = 1.0;
        }

        ecjegdjmimgdkngl_min(eml_dv0, eml_Xg);

        /* limit the integral */
        eml_event_duration = -rtb_V;
        for (eml_k = 0; eml_k < 3; eml_k++) {
          ((BlockIO_pa34model_dueca_8b *)
            pa34model_dueca_8b_rtM->ModelData.blockIO)->xgustdot[eml_k] =
            eml_event_duration * eml_Xg[eml_k];
        }

        eml_event_duration = eml_Xg[0];
        for (eml_k = 2; eml_k < 4; eml_k++) {
          eml_event_duration += eml_Xg[eml_k - 1];
        }

        if (eml_event_duration < 1.0E-010) {
          /* event complete */
          for (eml_k = 0; eml_k < 2; eml_k++) {
            ((BlockIO_pa34model_dueca_8b *)
              pa34model_dueca_8b_rtM->ModelData.blockIO)->cur[eml_k] = 0.0;
          }
        } else {
          ((BlockIO_pa34model_dueca_8b *)
            pa34model_dueca_8b_rtM->ModelData.blockIO)->cur[0] = eml_tstart;
          ((BlockIO_pa34model_dueca_8b *)
            pa34model_dueca_8b_rtM->ModelData.blockIO)->cur[1] = eml_event;
        }
      } else {
        for (eml_k = 0; eml_k < 3; eml_k++) {
          ((BlockIO_pa34model_dueca_8b *)
            pa34model_dueca_8b_rtM->ModelData.blockIO)->xgustdot[eml_k] = 0.0;
        }

        ((BlockIO_pa34model_dueca_8b *)
          pa34model_dueca_8b_rtM->ModelData.blockIO)->cur[0] = rtb_Clock;
        ((BlockIO_pa34model_dueca_8b *)
          pa34model_dueca_8b_rtM->ModelData.blockIO)->cur[1] = eml_event;
      }
    }

    /* Sum: '<S32>/Sum' incorporates:
     *  Product: '<S32>/Product2'
     */
    fractionTmp_0d += rtb_Kgust * rtb_Vwindb_o[0];
    rtb_Product_idx += rtb_Kgust * rtb_Vwindb_o[1];
    rtb_Product_idx_0 += rtb_Kgust * rtb_Vwindb_o[2];

    /* Product: '<S32>/Product1' */
    rtb_Product1_idx = rtb_Kturb * rtb_Omegawindb[0];
    rtb_Product1_idx_0 = rtb_Kturb * rtb_Omegawindb[1];
    rtb_Product1_idx_1 = rtb_Kturb * rtb_Omegawindb[2];

    /* Integrator: '<S6>/Initial Engine State' */
    if (((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
        ->InitialEngineState_IWORK.IcNeedsLoading) {
      ((ContinuousStates_pa34model_duec *)
        pa34model_dueca_8b_rtM->ModelData.contStates)->
        InitialEngineState_CSTATE[0] = pa34model_dueca_8b_rtC(M)->Constant2[0];
      ((ContinuousStates_pa34model_duec *)
        pa34model_dueca_8b_rtM->ModelData.contStates)->
        InitialEngineState_CSTATE[1] = pa34model_dueca_8b_rtC(M)->Constant2[1];
      ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
        ->InitialEngineState_IWORK.IcNeedsLoading = 0;
    }

    rtb_InitialEngineState[0] = ((ContinuousStates_pa34model_duec *)
      pa34model_dueca_8b_rtM->ModelData.contStates)->InitialEngineState_CSTATE[0];
    rtb_InitialEngineState[1] = ((ContinuousStates_pa34model_duec *)
      pa34model_dueca_8b_rtM->ModelData.contStates)->InitialEngineState_CSTATE[1];

    /* Embedded MATLAB: '<S10>/adjusting CG due  to failure' incorporates:
     *   Inport: '<Root>/In1'
     */
    {
      real_T eml_delta_I;
      int32_T eml_i0;
      real_T eml_x;
      real_T eml_W;
      real_T eml_Ax;
      real_T eml_Ay;
      real_T eml_Az;
      real_T eml_dW;

      /*  This block supports the Embedded MATLAB subset. */
      /*  Aanpassing CG waarden aan failure  */
      if (!((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
          ->W_basis_not_empty) {
        /* parameters MT Aircraft according to loading sheet lbs and inches!!! */
        /* lbs (Leeg gewicht in lbs) */
        /* 2=max */
        /* 2=max */
        /* 2=max */
        /* 100lbs max */
        /* 85 lbs max */
        /*  max =240 lbs */
        /*  max= 240 lbs */
        /*  97.2 is Based on main spar station 106.628 is at 40% chord (c=5'3'') */
        /*  Nu overgaan naar metrisch (inches/12) *0.3048  */
        ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
          ->Cg_x_basis = 2.9822359932088309E-002;
        ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
          ->Cg_y_basis = 0.0;

        /*  Model reference frame */
        ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
          ->Cg_z_basis = 0.0;

        /*  Model reference frame */
        ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
          ->W_basis = 2.1373632000000002E+003;
        ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
          ->W_basis_not_empty = true;

        /*  Traagheids momenten ( Data file) voor volle belading 6 pax en full fuel */
        ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
          ->Ixx_basis = 7014.0;
        ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
          ->Iyy_basis = 2783.0;
        ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
          ->Izz_basis = 9193.0;
        ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
          ->Ixz_basis = -282.0;

        /*  Aanpassen aan ontbreken passagiers (alleen Iyy en IZZ) */
        eml_delta_I = (0.0 * pow(0.5664 + ((D_Work_pa34model_dueca_8b *)
          pa34model_dueca_8b_rtM->Work.dwork)->Cg_x_basis, 2.0) - 0.0 * pow
                       (1.5342 + ((D_Work_pa34model_dueca_8b *)
          pa34model_dueca_8b_rtM->Work.dwork)->Cg_x_basis, 2.0)) - 0.0 * pow
          (0.2972 - ((D_Work_pa34model_dueca_8b *)
                     pa34model_dueca_8b_rtM->Work.dwork)->Cg_x_basis, 2.0);
        ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
          ->Izz_basis = ((D_Work_pa34model_dueca_8b *)
                         pa34model_dueca_8b_rtM->Work.dwork)->Izz_basis +
          eml_delta_I;
        ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
          ->Iyy_basis = ((D_Work_pa34model_dueca_8b *)
                         pa34model_dueca_8b_rtM->Work.dwork)->Iyy_basis +
          eml_delta_I;
      }

      /*  Nu de aanpassing per tijdstap */
      for (eml_i0 = 0; eml_i0 < 10; eml_i0++) {
        ((BlockIO_pa34model_dueca_8b *)
          pa34model_dueca_8b_rtM->ModelData.blockIO)->y[eml_i0] = 0.0;
      }

      eml_delta_I = rtb_InitialEngineState[0] * 0.4536;
      if (!(eml_delta_I <= 120.0)) {
        eml_delta_I = 120.0;
      }

      eml_x = rtb_InitialEngineState[1] * 0.4536;
      if (!(eml_x <= 120.0)) {
        eml_x = 120.0;
      }

      /*  aanpassen traagheid aan verbruik fuel (tank op ca 10 ft uit middenlijn) */
      eml_W = (((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
               ->W_basis - eml_delta_I) - eml_x;

      /*  aanpassen aan emergency cg shift */
      eml_Ax = ((ExternalInputs_pa34model_dueca_ *)
                pa34model_dueca_8b_rtM->ModelData.inputs)->In1[19];
      eml_Ay = ((ExternalInputs_pa34model_dueca_ *)
                pa34model_dueca_8b_rtM->ModelData.inputs)->In1[20];
      eml_Az = ((ExternalInputs_pa34model_dueca_ *)
                pa34model_dueca_8b_rtM->ModelData.inputs)->In1[21];
      eml_dW = ((ExternalInputs_pa34model_dueca_ *)
                pa34model_dueca_8b_rtM->ModelData.inputs)->In1[22];

      /* y=zeros(8,1); */
      /*   Defacto een integrator en een state in MATLAB code) */
      ((BlockIO_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->ModelData.blockIO
        )->y[0] = eml_W + eml_dW;

      /*  Weight */
      ((BlockIO_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->ModelData.blockIO
        )->y[1] = ((((D_Work_pa34model_dueca_8b *)
                     pa34model_dueca_8b_rtM->Work.dwork)->Ixx_basis -
                    eml_delta_I * 9.290304) - eml_x * 9.290304) + eml_dW *
        eml_Ax * eml_Ax;

      /*  Ixx */
      ((BlockIO_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->ModelData.blockIO
        )->y[2] = (((D_Work_pa34model_dueca_8b *)
                    pa34model_dueca_8b_rtM->Work.dwork)->Iyy_basis -
                   (eml_delta_I + eml_x) * pow(((D_Work_pa34model_dueca_8b *)
        pa34model_dueca_8b_rtM->Work.dwork)->Cg_x_basis, 2.0)) + eml_dW * eml_Ay
        * eml_Ay;

      /*  Iyy */
      ((BlockIO_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->ModelData.blockIO
        )->y[3] = ((((D_Work_pa34model_dueca_8b *)
                     pa34model_dueca_8b_rtM->Work.dwork)->Izz_basis -
                    eml_delta_I * (9.290304 + pow(((D_Work_pa34model_dueca_8b *)
        pa34model_dueca_8b_rtM->Work.dwork)->Cg_x_basis, 2.0))) - eml_x *
                   (9.290304 + pow(((D_Work_pa34model_dueca_8b *)
        pa34model_dueca_8b_rtM->Work.dwork)->Cg_x_basis, 2.0))) + eml_dW *
        eml_Az * eml_Az;

      /*  Izz */
      ((BlockIO_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->ModelData.blockIO
        )->y[4] = ((D_Work_pa34model_dueca_8b *)
                   pa34model_dueca_8b_rtM->Work.dwork)->Ixz_basis + eml_dW *
        eml_Ax * eml_Az;

      /*  Izx */
      ((BlockIO_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->ModelData.blockIO
        )->y[5] = ((D_Work_pa34model_dueca_8b *)
                   pa34model_dueca_8b_rtM->Work.dwork)->Cg_x_basis + eml_dW *
        eml_Ax / (eml_dW + eml_W);

      /*  CG x */
      ((BlockIO_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->ModelData.blockIO
        )->y[6] = ((D_Work_pa34model_dueca_8b *)
                   pa34model_dueca_8b_rtM->Work.dwork)->Cg_y_basis + eml_dW *
        eml_Ay / (eml_dW + eml_W);

      /*  CG y */
      ((BlockIO_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->ModelData.blockIO
        )->y[7] = ((D_Work_pa34model_dueca_8b *)
                   pa34model_dueca_8b_rtM->Work.dwork)->Cg_z_basis + eml_dW *
        eml_Az / (eml_dW + eml_W);

      /*  CG z */
      /*  Nieuw toegevoegd */
      ((BlockIO_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->ModelData.blockIO
        )->y[8] = eml_dW * eml_Ax * eml_Ay;

      /*  Ixy   */
      ((BlockIO_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->ModelData.blockIO
        )->y[9] = eml_dW * eml_Az * eml_Ay;

      /*  Izy */
    }

    /* Embedded MATLAB: '<S1>/calc x0dot' */
    {
      real_T eml_phi;
      real_T eml_theta;
      real_T eml_psi;
      real_T eml_dv0[9];
      real_T eml_dv1[3];
      int32_T eml_i0;
      static boolean_T eml_bv0[3] = { true, false, false };

      real_T eml_dv2[9];
      real_T eml_dv3[9];
      static boolean_T eml_bv1[3] = { false, true, false };

      real_T eml_dv4[9];
      int32_T eml_i1;
      real_T eml_dv5[9];
      int32_T eml_i2;
      static boolean_T eml_bv2[3] = { false, false, true };

      real_T eml_dv6[3];
      real_T eml_dv7[9];
      real_T eml_dv8[3];
      real_T eml_dv9[3];

      /*  Calculate initial State derivative  */
      /* state = col( p, q, r, u, v, w, phi, theta, psi, x, y, z) */
      eml_phi = pa34model_dueca_8b_rtC(M)->Constant1[6];
      eml_theta = pa34model_dueca_8b_rtC(M)->Constant1[7];
      eml_psi = pa34model_dueca_8b_rtC(M)->Constant1[8];

      /* % Calculate RF transformation matrices */
      /* transformation matrix from RFe (earth) to RFb (body) */
      /* % Calculate and output state derivatives */
      /* kinematics */
      eml_dv0[0] = 1.0;
      eml_dv0[3] = sin(eml_phi) * tan(eml_theta);
      eml_dv0[6] = cos(eml_phi) * tan(eml_theta);
      eml_dv0[1] = 0.0;
      eml_dv0[4] = cos(eml_phi);
      eml_dv0[7] = -sin(eml_phi);
      eml_dv0[2] = 0.0;
      eml_dv0[5] = sin(eml_phi) / cos(eml_theta);
      eml_dv0[8] = cos(eml_phi) / cos(eml_theta);
      eml_dv1[0] = pa34model_dueca_8b_rtC(M)->Constant1[0];
      eml_dv1[1] = pa34model_dueca_8b_rtC(M)->Constant1[1];
      eml_dv1[2] = pa34model_dueca_8b_rtC(M)->Constant1[2];
      for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
        eml_dv2[3 * eml_i0] = (real_T)eml_bv0[eml_i0];
      }

      eml_dv2[1] = 0.0;
      eml_dv2[4] = cos(eml_phi);
      eml_dv2[7] = sin(eml_phi);
      eml_dv2[2] = 0.0;
      eml_dv2[5] = -sin(eml_phi);
      eml_dv2[8] = cos(eml_phi);
      eml_dv3[0] = cos(eml_theta);
      eml_dv3[3] = 0.0;
      eml_dv3[6] = -sin(eml_theta);
      for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
        eml_dv3[1 + 3 * eml_i0] = (real_T)eml_bv1[eml_i0];
      }

      eml_dv3[2] = sin(eml_theta);
      eml_dv3[5] = 0.0;
      eml_dv3[8] = cos(eml_theta);
      eml_dv4[0] = cos(eml_psi);
      eml_dv4[3] = sin(eml_psi);
      eml_dv4[6] = 0.0;
      eml_dv4[1] = -sin(eml_psi);
      eml_dv4[4] = cos(eml_psi);
      eml_dv4[7] = 0.0;
      for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
        for (eml_i1 = 0; eml_i1 < 3; eml_i1++) {
          eml_dv5[eml_i0 + 3 * eml_i1] = 0.0;
          for (eml_i2 = 0; eml_i2 < 3; eml_i2++) {
            eml_dv5[eml_i0 + 3 * eml_i1] += eml_dv2[eml_i0 + 3 * eml_i2] *
              eml_dv3[eml_i2 + 3 * eml_i1];
          }
        }

        eml_dv4[2 + 3 * eml_i0] = (real_T)eml_bv2[eml_i0];
      }

      eml_dv6[0] = pa34model_dueca_8b_rtC(M)->Constant1[3];
      eml_dv6[1] = pa34model_dueca_8b_rtC(M)->Constant1[4];
      eml_dv6[2] = pa34model_dueca_8b_rtC(M)->Constant1[5];
      for (eml_i2 = 0; eml_i2 < 3; eml_i2++) {
        for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
          eml_dv7[eml_i2 + 3 * eml_i0] = 0.0;
          for (eml_i1 = 0; eml_i1 < 3; eml_i1++) {
            eml_dv7[eml_i2 + 3 * eml_i0] += eml_dv5[eml_i0 + 3 * eml_i1] *
              eml_dv4[eml_i1 + 3 * eml_i2];
          }
        }

        eml_dv8[eml_i2] = 0.0;
        for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
          eml_dv8[eml_i2] += eml_dv0[eml_i2 + 3 * eml_i0] * eml_dv1[eml_i0];
        }

        eml_dv9[eml_i2] = 0.0;
        for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
          eml_dv9[eml_i2] += eml_dv7[eml_i2 + 3 * eml_i0] * eml_dv6[eml_i0];
        }

        ((BlockIO_pa34model_dueca_8b *)
          pa34model_dueca_8b_rtM->ModelData.blockIO)->x0dot[eml_i2] = 0.0;
      }

      for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
        ((BlockIO_pa34model_dueca_8b *)
          pa34model_dueca_8b_rtM->ModelData.blockIO)->x0dot[eml_i0 + 3] = 0.0;
      }

      for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
        ((BlockIO_pa34model_dueca_8b *)
          pa34model_dueca_8b_rtM->ModelData.blockIO)->x0dot[eml_i0 + 6] =
          eml_dv8[eml_i0];
      }

      for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
        ((BlockIO_pa34model_dueca_8b *)
          pa34model_dueca_8b_rtM->ModelData.blockIO)->x0dot[eml_i0 + 9] =
          eml_dv9[eml_i0];
      }

      /* d/dt of col( Omega_be, Vb, euler, Xe) */
    }

    if (rtmIsSampleHit(pa34model_dueca_8b_rtM, 1, 0)) {
      for (i = 0; i < 12; i++) {
        /* Switch: '<S9>/Init' incorporates:
         *  Memory: '<S9>/Memory'
         *  Memory: '<S9>/Memory1'
         */
        if (((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
            ->Memory1_PreviousInput != 0.0) {
          ((BlockIO_pa34model_dueca_8b *)
            pa34model_dueca_8b_rtM->ModelData.blockIO)->Init[i] =
            ((BlockIO_pa34model_dueca_8b *)
             pa34model_dueca_8b_rtM->ModelData.blockIO)->x0dot[i];
        } else {
          ((BlockIO_pa34model_dueca_8b *)
            pa34model_dueca_8b_rtM->ModelData.blockIO)->Init[i] =
            ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
            ->Memory_PreviousInput_j[i];
        }
      }
    }

    /* SignalConversion: '<S21>/TmpHiddenBufferAt SFunction Inport2' */
    rtb_TmpHiddenBufferAtSFunctio_n[0] = rtb_rho;
    rtb_TmpHiddenBufferAtSFunctio_n[1] = rtb_T;
    rtb_TmpHiddenBufferAtSFunctio_n[2] = rtb_g;
    rtb_TmpHiddenBufferAtSFunctio_n[3] = rtb_Vwinde[0];
    rtb_TmpHiddenBufferAtSFunctio_n[4] = rtb_Vwinde[1];
    rtb_TmpHiddenBufferAtSFunctio_n[5] = rtb_Vwinde[2];
    rtb_TmpHiddenBufferAtSFunctio_n[6] = fractionTmp_0d;
    rtb_TmpHiddenBufferAtSFunctio_n[7] = rtb_Product_idx;
    rtb_TmpHiddenBufferAtSFunctio_n[8] = rtb_Product_idx_0;
    rtb_TmpHiddenBufferAtSFunctio_n[9] = rtb_Product1_idx;
    rtb_TmpHiddenBufferAtSFunctio_n[10] = rtb_Product1_idx_0;
    rtb_TmpHiddenBufferAtSFunctio_n[11] = rtb_Product1_idx_1;

    /* Embedded MATLAB: '<S6>/Wind Effect' */
    {
      int32_T eml_i0;

      /* state = col( p, q, r, u, v, w, phi, theta, psi, x, y, z) */
      /* atmos = col(rho, T, g, Vwinde(3), Vgust (3), Omegagust (3)) */
      /* Compensation method copied from aeroblk_HL20/HL20 Airframe/Alpha,Beta,Mach */
      /* Note this determines the effect of sudden movement of air (or atmospheric disturbance) */
      /* the constant movement of air (or wind) is the vector between VTAS and VGS and is used */
      /* in the equations of motion */
      /* Create output */
      for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
        ((BlockIO_pa34model_dueca_8b *)
          pa34model_dueca_8b_rtM->ModelData.blockIO)->stateo[eml_i0] =
          rtb_TrimState[eml_i0] + rtb_TmpHiddenBufferAtSFunctio_n[9 + eml_i0];
      }

      for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
        ((BlockIO_pa34model_dueca_8b *)
          pa34model_dueca_8b_rtM->ModelData.blockIO)->stateo[eml_i0 + 3] =
          rtb_TrimState[3 + eml_i0] - rtb_TmpHiddenBufferAtSFunctio_n[6 + eml_i0];
      }

      for (eml_i0 = 0; eml_i0 < 6; eml_i0++) {
        ((BlockIO_pa34model_dueca_8b *)
          pa34model_dueca_8b_rtM->ModelData.blockIO)->stateo[eml_i0 + 6] =
          rtb_TrimState[6 + eml_i0];
      }

      for (eml_i0 = 0; eml_i0 < 12; eml_i0++) {
        ((BlockIO_pa34model_dueca_8b *)
          pa34model_dueca_8b_rtM->ModelData.blockIO)->atmoso[eml_i0] =
          rtb_TmpHiddenBufferAtSFunctio_n[eml_i0];
      }
    }

    /* Embedded MATLAB: '<S10>/Setting rudder hardover' incorporates:
     *   Inport: '<Root>/In1'
     */
    {
      int32_T eml_i0;
      real_T eml_Eff_in[3];
      static boolean_T eml_bv0[2] = { false, true };

      for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
        eml_Eff_in[eml_i0] = ((ExternalInputs_pa34model_dueca_ *)
                              pa34model_dueca_8b_rtM->ModelData.inputs)->
          In1[eml_i0+23];
      }

      /*  Deze  module regelt de rudder hardover 11 april 2014 */
      for (eml_i0 = 0; eml_i0 < 10; eml_i0++) {
        ((BlockIO_pa34model_dueca_8b *)
          pa34model_dueca_8b_rtM->ModelData.blockIO)->Pil_uit[eml_i0] =
          ((ExternalInputs_pa34model_dueca_ *)
           pa34model_dueca_8b_rtM->ModelData.inputs)->In1[eml_i0];
      }

      for (eml_i0 = 0; eml_i0 < 2; eml_i0++) {
        ((BlockIO_pa34model_dueca_8b *)
          pa34model_dueca_8b_rtM->ModelData.blockIO)->Ef_uit[eml_i0] =
          ((ExternalInputs_pa34model_dueca_ *)
           pa34model_dueca_8b_rtM->ModelData.inputs)->In1[(int32_T)
          eml_bv0[eml_i0]+23];
      }

      if (((ExternalInputs_pa34model_dueca_ *)
           pa34model_dueca_8b_rtM->ModelData.inputs)->In1[25] != 0.0) {
        if (((ExternalInputs_pa34model_dueca_ *)
             pa34model_dueca_8b_rtM->ModelData.inputs)->In1[25] > 35.0) {
          /*  Detecteer rudder hardover */
          /*  Limiteren max rudder 35 graden */
          eml_Eff_in[2] = 35.0;
        }

        if (eml_Eff_in[2] < -35.0) {
          eml_Eff_in[2] = -35.0;
        }

        ((BlockIO_pa34model_dueca_8b *)
          pa34model_dueca_8b_rtM->ModelData.blockIO)->Pil_uit[2] = eml_Eff_in[2]
          * 3.1415926535897931E+000 / 180.0;

        /*  Effectiviteit moet normaa;l zijn */
        ((BlockIO_pa34model_dueca_8b *)
          pa34model_dueca_8b_rtM->ModelData.blockIO)->Ef_uit[1] = 1.0;
      }
    }

    /* Embedded MATLAB: '<S10>/Engine Params' incorporates:
     *   Inport: '<Root>/In1'
     */
    {
      int32_T eml_i0;

      /*  This block supports the Embedded MATLAB subset. */
      /*  See the help menu for details.  */
      /* pilot_input = col( de, da, dr, dte, dta, dtr, df, gear, pla1, pla2) */
      for (eml_i0 = 0; eml_i0 < 17; eml_i0++) {
        ((BlockIO_pa34model_dueca_8b *)
          pa34model_dueca_8b_rtM->ModelData.blockIO)->engine[eml_i0] = 0.0;
      }

      /* state = col( p, q, r, u, v, w, phi, theta, psi, x, y, z) */
      /*  De positie en de orientatie van de engines in body axis frame */
      ((BlockIO_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->ModelData.blockIO
        )->engine[0] = 2.0;

      /*  Number of engines */
      /* First engine (left) */
      ((BlockIO_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->ModelData.blockIO
        )->engine[1] = 1.66;

      /* X engine */
      ((BlockIO_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->ModelData.blockIO
        )->engine[2] = -1.8974;

      /* Y engine */
      ((BlockIO_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->ModelData.blockIO
        )->engine[3] = -0.096;

      /* Z engine  */
      ((BlockIO_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->ModelData.blockIO
        )->engine[4] = 0.0;

      /*  roll hoek engine always 0 */
      ((BlockIO_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->ModelData.blockIO
        )->engine[5] = -3.4906585039886591E-002;

      /*  pitch hoek is 2 graden down */
      ((BlockIO_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->ModelData.blockIO
        )->engine[6] = 0.0;

      /*  Engine yaw angle=0 */
      /* Second engine (right) */
      ((BlockIO_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->ModelData.blockIO
        )->engine[7] = 1.66;

      /* X engine */
      ((BlockIO_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->ModelData.blockIO
        )->engine[8] = 1.8974;

      /* Y engine */
      ((BlockIO_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->ModelData.blockIO
        )->engine[9] = -0.096;

      /* Z engine  */
      ((BlockIO_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->ModelData.blockIO
        )->engine[10] = 0.0;

      /*  roll hoek engine always 0 */
      ((BlockIO_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->ModelData.blockIO
        )->engine[11] = -3.4906585039886591E-002;

      /*  pitch hoek is 2 graden down */
      ((BlockIO_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->ModelData.blockIO
        )->engine[12] = 0.0;

      /*  Engine yaw angle=0 */
      /*  De throttle scaling */
      /*  hier is de plaats om de pla angle om te zetten naar engine input */
      ((BlockIO_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->ModelData.blockIO
        )->engine[13] = ((BlockIO_pa34model_dueca_8b *)
                         pa34model_dueca_8b_rtM->ModelData.blockIO)->Pil_uit[8];
      ((BlockIO_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->ModelData.blockIO
        )->engine[14] = ((BlockIO_pa34model_dueca_8b *)
                         pa34model_dueca_8b_rtM->ModelData.blockIO)->Pil_uit[9];

      /*  DE maximale rpm settings left en right */
      ((BlockIO_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->ModelData.blockIO
        )->engine[15] = ((ExternalInputs_pa34model_dueca_ *)
                         pa34model_dueca_8b_rtM->ModelData.inputs)->In1[16];
      ((BlockIO_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->ModelData.blockIO
        )->engine[16] = ((ExternalInputs_pa34model_dueca_ *)
                         pa34model_dueca_8b_rtM->ModelData.inputs)->In1[17];
    }

    pa34m_CalculateThrustParameters(pa34model_dueca_8b_rtM);
    pa34model_d_AEROFORCESENMOMENTS(pa34model_dueca_8b_rtM);

    /* SignalConversion: '<S20>/TmpHiddenBufferAt SFunction Inport2' incorporates:
     *  Constant: '<S24>/chord'
     *  Constant: '<S24>/location_AERORP.x'
     *  Constant: '<S24>/location_AERORP.y'
     *  Constant: '<S24>/location_AERORP.z'
     *  Constant: '<S24>/wingarea'
     *  Constant: '<S24>/wingspan'
     */
    rtb_TmpHiddenBufferAtSFunctio_i[0] = 19.39;
    rtb_TmpHiddenBufferAtSFunctio_i[1] = 11.85;
    rtb_TmpHiddenBufferAtSFunctio_i[2] = 1.61;
    rtb_TmpHiddenBufferAtSFunctio_i[3] = 0.0;
    rtb_TmpHiddenBufferAtSFunctio_i[4] = 0.0;
    rtb_TmpHiddenBufferAtSFunctio_i[5] = 0.0;

    /* Embedded MATLAB: '<S6>/Translation to cg' */
    {
      int32_T eml_i0;
      real_T eml_d0;
      real_T eml_d1;
      real_T eml_a[3];
      real_T eml_FAb[3];
      real_T eml_Xcg[3];
      real_T eml_a_0[3];
      real_T eml_FTbr[3];
      real_T eml_dv0[3];
      real_T eml_dv1[3];

      /*  Calculate Aerodynamic Forces and Moments in RFb */
      /* geometry = col (S,b,cbar,Xaero) */
      /* massmodel = col(m, Ixx, Iyy, Izz, Ixy, Xcg(3)) */
      /* shift the forces from the aerodynamic reference point to the cg (introduces an additional moment) */
      /* moments in RFb */
      for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
        eml_d0 = ((BlockIO_pa34model_dueca_8b *)
                  pa34model_dueca_8b_rtM->ModelData.blockIO)->y[5 + eml_i0];

        /* engine = col(No eng (1),X_engine_left(3),Angles */
        /* Eng_L(3),X_engine_R(3),Angles_R(3),Pla(2)  */
        /* position vector between cg and aero_rp */
        /*  aeroforces */
        eml_d1 = ((BlockIO_pa34model_dueca_8b *)
                  pa34model_dueca_8b_rtM->ModelData.blockIO)->FMAb[eml_i0];
        eml_a[eml_i0] = -(eml_d0 - rtb_TmpHiddenBufferAtSFunctio_i[3 + eml_i0]);
        rtb_FMAb[eml_i0] = eml_d1;
        eml_FAb[eml_i0] = eml_d1;
        eml_Xcg[eml_i0] = eml_d0;
      }

      eml_a_0[0] = eml_a[1] * eml_FAb[2] - eml_a[2] * eml_FAb[1];
      eml_a_0[1] = eml_a[2] * eml_FAb[0] - eml_a[0] * eml_FAb[2];
      eml_a_0[2] = eml_a[0] * eml_FAb[1] - eml_a[1] * eml_FAb[0];
      for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
        rtb_FMAb[eml_i0 + 3] = ((BlockIO_pa34model_dueca_8b *)
          pa34model_dueca_8b_rtM->ModelData.blockIO)->FMAb[3 + eml_i0] +
          eml_a_0[eml_i0];
      }

      /* %Caclulate Thrust forces and moments in RFb */
      /* shift the forces from the aerodynamic reference point to the cg (introduces an additional moment) */
      /* moments in RFb */
      /* sum */
      for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
        eml_d0 = ((BlockIO_pa34model_dueca_8b *)
                  pa34model_dueca_8b_rtM->ModelData.blockIO)->Thrust[eml_i0];
        eml_a[eml_i0] = -(eml_Xcg[eml_i0] - ((BlockIO_pa34model_dueca_8b *)
          pa34model_dueca_8b_rtM->ModelData.blockIO)->engine[1 + eml_i0]);

        /* shift the forces from the aerodynamic reference point to the cg (introduces an additional moment) */
        /* moments in RFb */
        eml_d1 = ((BlockIO_pa34model_dueca_8b *)
                  pa34model_dueca_8b_rtM->ModelData.blockIO)->Thrust[6 + eml_i0];
        eml_a_0[eml_i0] = -(eml_Xcg[eml_i0] - ((BlockIO_pa34model_dueca_8b *)
          pa34model_dueca_8b_rtM->ModelData.blockIO)->engine[7 + eml_i0]);
        rtb_FMTb[eml_i0] = eml_d0 + eml_d1;
        eml_FAb[eml_i0] = eml_d0;
        eml_FTbr[eml_i0] = eml_d1;
      }

      eml_dv0[0] = eml_a[1] * eml_FAb[2] - eml_a[2] * eml_FAb[1];
      eml_dv0[1] = eml_a[2] * eml_FAb[0] - eml_a[0] * eml_FAb[2];
      eml_dv0[2] = eml_a[0] * eml_FAb[1] - eml_a[1] * eml_FAb[0];
      eml_dv1[0] = eml_a_0[1] * eml_FTbr[2] - eml_a_0[2] * eml_FTbr[1];
      eml_dv1[1] = eml_a_0[2] * eml_FTbr[0] - eml_a_0[0] * eml_FTbr[2];
      eml_dv1[2] = eml_a_0[0] * eml_FTbr[1] - eml_a_0[1] * eml_FTbr[0];
      for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
        rtb_FMTb[eml_i0 + 3] = (((BlockIO_pa34model_dueca_8b *)
          pa34model_dueca_8b_rtM->ModelData.blockIO)->Thrust[3 + eml_i0] +
          eml_dv0[eml_i0]) + (((BlockIO_pa34model_dueca_8b *)
          pa34model_dueca_8b_rtM->ModelData.blockIO)->Thrust[9 + eml_i0] +
                              eml_dv1[eml_i0]);
      }
    }

    /* Embedded MATLAB: '<S6>/Force due to gravity' */
    {
      real_T eml_phi;
      real_T eml_theta;
      real_T eml_psi;
      int32_T eml_i0;
      static boolean_T eml_bv0[3] = { true, false, false };

      real_T eml_dv0[9];
      real_T eml_dv1[9];
      static boolean_T eml_bv1[3] = { false, true, false };

      real_T eml_dv2[9];
      int32_T eml_i1;
      real_T eml_dv3[9];
      int32_T eml_i2;
      static boolean_T eml_bv2[3] = { false, false, true };

      real_T eml_dv4[3];
      real_T eml_dv5[9];
      real_T eml_dv6[3];

      /* state = col( p, q, r, u, v, w, phi, theta, psi, x, y, z) */
      eml_phi = ((BlockIO_pa34model_dueca_8b *)
                 pa34model_dueca_8b_rtM->ModelData.blockIO)->stateo[6];
      eml_theta = ((BlockIO_pa34model_dueca_8b *)
                   pa34model_dueca_8b_rtM->ModelData.blockIO)->stateo[7];
      eml_psi = ((BlockIO_pa34model_dueca_8b *)
                 pa34model_dueca_8b_rtM->ModelData.blockIO)->stateo[8];

      /* atmos = col(rho, T, g, Vwind (3), Omegawind (3)) */
      /* massmodel = col(m, Ixx, Iyy, Izz, Ixy, cg(3)) */
      /* % Calculate RF transformation matrices */
      /* transformation matrix from RFe (earth) to RFb (body) */
      /* Calculate Force (and Moment) due to gravity */
      /* NOTE: m already includes fuel mass! */
      /* RFb located in cg so no moments introduced */
      for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
        eml_dv0[3 * eml_i0] = (real_T)eml_bv0[eml_i0];
      }

      eml_dv0[1] = 0.0;
      eml_dv0[4] = cos(eml_phi);
      eml_dv0[7] = sin(eml_phi);
      eml_dv0[2] = 0.0;
      eml_dv0[5] = -sin(eml_phi);
      eml_dv0[8] = cos(eml_phi);
      eml_dv1[0] = cos(eml_theta);
      eml_dv1[3] = 0.0;
      eml_dv1[6] = -sin(eml_theta);
      for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
        eml_dv1[1 + 3 * eml_i0] = (real_T)eml_bv1[eml_i0];
      }

      eml_dv1[2] = sin(eml_theta);
      eml_dv1[5] = 0.0;
      eml_dv1[8] = cos(eml_theta);
      eml_dv2[0] = cos(eml_psi);
      eml_dv2[3] = sin(eml_psi);
      eml_dv2[6] = 0.0;
      eml_dv2[1] = -sin(eml_psi);
      eml_dv2[4] = cos(eml_psi);
      eml_dv2[7] = 0.0;
      for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
        for (eml_i1 = 0; eml_i1 < 3; eml_i1++) {
          eml_dv3[eml_i0 + 3 * eml_i1] = 0.0;
          for (eml_i2 = 0; eml_i2 < 3; eml_i2++) {
            eml_dv3[eml_i0 + 3 * eml_i1] += eml_dv0[eml_i0 + 3 * eml_i2] *
              eml_dv1[eml_i2 + 3 * eml_i1];
          }
        }

        eml_dv2[2 + 3 * eml_i0] = (real_T)eml_bv2[eml_i0];
      }

      eml_dv4[0] = 0.0;
      eml_dv4[1] = 0.0;
      eml_dv4[2] = ((BlockIO_pa34model_dueca_8b *)
                    pa34model_dueca_8b_rtM->ModelData.blockIO)->y[0] *
        ((BlockIO_pa34model_dueca_8b *)
         pa34model_dueca_8b_rtM->ModelData.blockIO)->atmoso[2];
      for (eml_i2 = 0; eml_i2 < 3; eml_i2++) {
        for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
          eml_dv5[eml_i2 + 3 * eml_i0] = 0.0;
          for (eml_i1 = 0; eml_i1 < 3; eml_i1++) {
            eml_dv5[eml_i2 + 3 * eml_i0] += eml_dv3[eml_i2 + 3 * eml_i1] *
              eml_dv2[eml_i1 + 3 * eml_i0];
          }
        }

        eml_dv6[eml_i2] = 0.0;
        for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
          eml_dv6[eml_i2] += eml_dv5[eml_i2 + 3 * eml_i0] * eml_dv4[eml_i0];
        }

        rtb_FMGb[eml_i2] = eml_dv6[eml_i2];
      }

      for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
        rtb_FMGb[eml_i0 + 3] = 0.0;
      }
    }

    /* Embedded MATLAB: '<S6>/Conditional Sum1' */
    {
      int32_T eml_i0;

      /*  Sum all forces and moments */
      /*  FMXb = FMAb+FMTb+FMGb+FMLb; */
      for (eml_i0 = 0; eml_i0 < 6; eml_i0++) {
        rtb_FMair[eml_i0] = (rtb_FMAb[eml_i0] + rtb_FMTb[eml_i0]) +
          rtb_FMGb[eml_i0];
      }
    }

    /* SignalConversion: '<S15>/TmpHiddenBufferAt SFunction Inport2' incorporates:
     *  Constant: '<S26>/gear positie1'
     *  Constant: '<S26>/gear positie3'
     *  Constant: '<S26>/main_left_gear tire delfection'
     *  Constant: '<S26>/main_left_gear.dmax'
     *  Constant: '<S26>/main_left_gear.gear'
     *  Constant: '<S26>/main_left_gear.k'
     *  Constant: '<S26>/main_left_gear.location.x'
     *  Constant: '<S26>/main_left_gear.location.y'
     *  Constant: '<S26>/main_left_gear.location.z'
     *  Constant: '<S26>/main_right_gear. tire deflection'
     *  Constant: '<S26>/main_right_gear.dmax'
     *  Constant: '<S26>/main_right_gear.gear'
     *  Constant: '<S26>/main_right_gear.k'
     *  Constant: '<S26>/main_right_gear.location.x'
     *  Constant: '<S26>/main_right_gear.location.y'
     *  Constant: '<S26>/main_right_gear.location.z'
     *  Constant: '<S26>/mu_max'
     *  Constant: '<S26>/mu_min'
     *  Constant: '<S26>/nose_gear._tire ddeflection'
     *  Constant: '<S26>/nose_gear.dmax'
     *  Constant: '<S26>/nose_gear.gear'
     *  Constant: '<S26>/nose_gear.k'
     *  Constant: '<S26>/nose_gear.location.x'
     *  Constant: '<S26>/nose_gear.location.y'
     *  Constant: '<S26>/nose_gear.location.z'
     *  Constant: '<S26>/nose_gear.rotate'
     */
    rtb_TmpHiddenBufferAtSFunctio_g[0] = 0.5;
    rtb_TmpHiddenBufferAtSFunctio_g[1] = 0.05;
    rtb_TmpHiddenBufferAtSFunctio_g[2] = 1500.0;
    rtb_TmpHiddenBufferAtSFunctio_g[3] = 0.025;
    rtb_TmpHiddenBufferAtSFunctio_g[4] = 0.4;
    rtb_TmpHiddenBufferAtSFunctio_g[5] = 1.84;
    rtb_TmpHiddenBufferAtSFunctio_g[6] = 0.0;
    rtb_TmpHiddenBufferAtSFunctio_g[7] = 1.5;
    rtb_TmpHiddenBufferAtSFunctio_g[8] = 6000.0;
    rtb_TmpHiddenBufferAtSFunctio_g[9] = 2.0;
    rtb_TmpHiddenBufferAtSFunctio_g[10] = 1500.0;
    rtb_TmpHiddenBufferAtSFunctio_g[11] = 0.025;
    rtb_TmpHiddenBufferAtSFunctio_g[12] = 0.4;
    rtb_TmpHiddenBufferAtSFunctio_g[13] = -0.35;
    rtb_TmpHiddenBufferAtSFunctio_g[14] = -1.7653;
    rtb_TmpHiddenBufferAtSFunctio_g[15] = 1.5;
    rtb_TmpHiddenBufferAtSFunctio_g[16] = 6000.0;
    rtb_TmpHiddenBufferAtSFunctio_g[17] = 1.0;
    rtb_TmpHiddenBufferAtSFunctio_g[18] = 1500.0;
    rtb_TmpHiddenBufferAtSFunctio_g[19] = 0.025;
    rtb_TmpHiddenBufferAtSFunctio_g[20] = 0.4;
    rtb_TmpHiddenBufferAtSFunctio_g[21] = -0.35;
    rtb_TmpHiddenBufferAtSFunctio_g[22] = 1.7653;
    rtb_TmpHiddenBufferAtSFunctio_g[23] = 1.5;
    rtb_TmpHiddenBufferAtSFunctio_g[24] = 6000.0;
    rtb_TmpHiddenBufferAtSFunctio_g[25] = 3.0;

    /* Embedded MATLAB: '<S6>/Calculate Ground Model Parameters' incorporates:
     *  Constant: '<S6>/TerrainMapLim1'
     */
    {
      real_T eml_u;
      real_T eml_phi;
      real_T eml_theta;
      real_T eml_psi;
      real_T eml_xe;
      real_T eml_ye;
      int32_T eml_offset;
      static boolean_T eml_bv0[3] = { true, false, false };

      real_T eml_dv0[9];
      real_T eml_dv1[9];
      static boolean_T eml_bv1[3] = { false, true, false };

      real_T eml_dv2[9];
      int32_T eml_i0;
      real_T eml_dv3[9];
      int32_T eml_i;
      static boolean_T eml_bv2[3] = { false, false, true };

      real_T eml_Xcg[3];
      real_T eml_Tbe[9];
      real_T eml_dv4[3];
      real_T eml_dv5[3];
      real_T eml_dv6[3];
      static int8_T eml_iv0[9] = { -1, 0, 0, 0, -1, 0, 0, 0, -1 };

      real_T eml_dXge[3];

      /*  This block supports the Embedded MATLAB subset. */
      /*  See the help menu for details.  */
      /* state = col( p, q, r, u, v, w, phi, theta, psi, x, y, z) */
      eml_u = ((BlockIO_pa34model_dueca_8b *)
               pa34model_dueca_8b_rtM->ModelData.blockIO)->stateo[3];
      eml_phi = ((BlockIO_pa34model_dueca_8b *)
                 pa34model_dueca_8b_rtM->ModelData.blockIO)->stateo[6];
      eml_theta = ((BlockIO_pa34model_dueca_8b *)
                   pa34model_dueca_8b_rtM->ModelData.blockIO)->stateo[7];
      eml_psi = ((BlockIO_pa34model_dueca_8b *)
                 pa34model_dueca_8b_rtM->ModelData.blockIO)->stateo[8];
      eml_xe = ((BlockIO_pa34model_dueca_8b *)
                pa34model_dueca_8b_rtM->ModelData.blockIO)->stateo[9];
      eml_ye = ((BlockIO_pa34model_dueca_8b *)
                pa34model_dueca_8b_rtM->ModelData.blockIO)->stateo[10];

      /* % Calculate RF transformation matrices */
      for (eml_offset = 0; eml_offset < 3; eml_offset++) {
        eml_dv0[3 * eml_offset] = (real_T)eml_bv0[eml_offset];
      }

      eml_dv0[1] = 0.0;
      eml_dv0[4] = cos(eml_phi);
      eml_dv0[7] = sin(eml_phi);
      eml_dv0[2] = 0.0;
      eml_dv0[5] = -sin(eml_phi);
      eml_dv0[8] = cos(eml_phi);
      eml_dv1[0] = cos(eml_theta);
      eml_dv1[3] = 0.0;
      eml_dv1[6] = -sin(eml_theta);
      for (eml_offset = 0; eml_offset < 3; eml_offset++) {
        eml_dv1[1 + 3 * eml_offset] = (real_T)eml_bv1[eml_offset];
      }

      eml_dv1[2] = sin(eml_theta);
      eml_dv1[5] = 0.0;
      eml_dv1[8] = cos(eml_theta);
      eml_dv2[0] = cos(eml_psi);
      eml_dv2[3] = sin(eml_psi);
      eml_dv2[6] = 0.0;
      eml_dv2[1] = -sin(eml_psi);
      eml_dv2[4] = cos(eml_psi);
      eml_dv2[7] = 0.0;
      for (eml_offset = 0; eml_offset < 3; eml_offset++) {
        for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
          eml_dv3[eml_offset + 3 * eml_i0] = 0.0;
          for (eml_i = 0; eml_i < 3; eml_i++) {
            eml_dv3[eml_offset + 3 * eml_i0] += eml_dv0[eml_offset + 3 * eml_i] *
              eml_dv1[eml_i + 3 * eml_i0];
          }
        }

        eml_dv2[2 + 3 * eml_offset] = (real_T)eml_bv2[eml_offset];
      }

      /* transformation matrix from RFe (earth) to RFb (body) */
      /* transformation from RFdd (Diamond Datum) to RFb (body) */
      /* massmodel = col(m, Ixx, Iyy, Izz, Ixy, cg(3)) */
      eml_Xcg[0] = ((BlockIO_pa34model_dueca_8b *)
                    pa34model_dueca_8b_rtM->ModelData.blockIO)->y[5];
      eml_Xcg[1] = ((BlockIO_pa34model_dueca_8b *)
                    pa34model_dueca_8b_rtM->ModelData.blockIO)->y[6];
      eml_Xcg[2] = ((BlockIO_pa34model_dueca_8b *)
                    pa34model_dueca_8b_rtM->ModelData.blockIO)->y[7];
      for (eml_offset = 0; eml_offset < 3; eml_offset++) {
        for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
          eml_Tbe[eml_offset + 3 * eml_i0] = 0.0;
          for (eml_i = 0; eml_i < 3; eml_i++) {
            eml_Tbe[eml_offset + 3 * eml_i0] += eml_dv3[eml_offset + 3 * eml_i] *
              eml_dv2[eml_i + 3 * eml_i0];
          }
        }

        /*  landingmodel = col( mu_rol, mu_side, several objects with 7 parameters each: {k,c,dmax,xg,yg,zg,gear}) */
        rtb_xge[eml_offset] = 0.0;
        rtb_yge[eml_offset] = 0.0;
      }

      for (eml_i = 0; eml_i < 3; eml_i++) {
        eml_offset = (eml_i << 3) + 2;

        /* difference vector in Diamond Datumplane */
        /* calculate the vector in RFb */
        eml_dv4[0] = rtb_TmpHiddenBufferAtSFunctio_g[eml_offset + 3];
        eml_dv4[1] = rtb_TmpHiddenBufferAtSFunctio_g[eml_offset + 4];
        eml_dv4[2] = rtb_TmpHiddenBufferAtSFunctio_g[eml_offset + 5];
        for (eml_offset = 0; eml_offset < 3; eml_offset++) {
          eml_dv5[eml_offset] = eml_Xcg[eml_offset] - eml_dv4[eml_offset];
        }

        for (eml_offset = 0; eml_offset < 3; eml_offset++) {
          eml_dv6[eml_offset] = 0.0;
          for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
            eml_dv6[eml_offset] += (real_T)eml_iv0[eml_offset + 3 * eml_i0] *
              eml_dv5[eml_i0];
          }
        }

        for (eml_offset = 0; eml_offset < 3; eml_offset++) {
          eml_dXge[eml_offset] = 0.0;
          for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
            eml_dXge[eml_offset] += eml_Tbe[eml_i0 + 3 * eml_offset] *
              eml_dv6[eml_i0];
          }
        }

        rtb_xge[eml_i] = eml_xe + eml_dXge[0];
        rtb_yge[eml_i] = eml_ye + eml_dXge[1];
        while (rtb_xge[eml_i] > (10.0)) {
          rtb_xge[eml_i] = rtb_xge[eml_i] - (10.0);
        }

        while (rtb_yge[eml_i] > (10.0)) {
          rtb_yge[eml_i] = rtb_yge[eml_i] - (10.0);
        }

        if (eml_u < 5.0) {
          rtb_xge[eml_i] = 0.0;
          rtb_yge[eml_i] = 0.0;
        }
      }
    }

    /* Sum: '<S6>/Sum' incorporates:
     *  Inport: '<Root>/In1'
     *  Lookup2D: '<S6>/TerrainMap'
     */
    rtb_Sum_c[0] = rt_Lookup2D_Normal(&pa34model_dueca_8b_ConstP.pooled9[0], 2,
      &pa34model_dueca_8b_ConstP.pooled9[0], 2,
      &pa34model_dueca_8b_ConstP.TerrainMap_Table[0], rtb_xge[0], rtb_yge[0]) +
      ((ExternalInputs_pa34model_dueca_ *)
       pa34model_dueca_8b_rtM->ModelData.inputs)->In1[18];
    rtb_Sum_c[1] = rt_Lookup2D_Normal(&pa34model_dueca_8b_ConstP.pooled9[0], 2,
      &pa34model_dueca_8b_ConstP.pooled9[0], 2,
      &pa34model_dueca_8b_ConstP.TerrainMap_Table[0], rtb_xge[1], rtb_yge[1]) +
      ((ExternalInputs_pa34model_dueca_ *)
       pa34model_dueca_8b_rtM->ModelData.inputs)->In1[18];
    rtb_Sum_c[2] = rt_Lookup2D_Normal(&pa34model_dueca_8b_ConstP.pooled9[0], 2,
      &pa34model_dueca_8b_ConstP.pooled9[0], 2,
      &pa34model_dueca_8b_ConstP.TerrainMap_Table[0], rtb_xge[2], rtb_yge[2]) +
      ((ExternalInputs_pa34model_dueca_ *)
       pa34model_dueca_8b_rtM->ModelData.inputs)->In1[18];

    /* SignalConversion: '<S19>/TmpHiddenBufferAt SFunction Inport6' incorporates:
     *  Constant: '<S26>/gear positie1'
     *  Constant: '<S26>/gear positie3'
     *  Constant: '<S26>/main_left_gear tire delfection'
     *  Constant: '<S26>/main_left_gear.dmax'
     *  Constant: '<S26>/main_left_gear.gear'
     *  Constant: '<S26>/main_left_gear.k'
     *  Constant: '<S26>/main_left_gear.location.x'
     *  Constant: '<S26>/main_left_gear.location.y'
     *  Constant: '<S26>/main_left_gear.location.z'
     *  Constant: '<S26>/main_right_gear. tire deflection'
     *  Constant: '<S26>/main_right_gear.dmax'
     *  Constant: '<S26>/main_right_gear.gear'
     *  Constant: '<S26>/main_right_gear.k'
     *  Constant: '<S26>/main_right_gear.location.x'
     *  Constant: '<S26>/main_right_gear.location.y'
     *  Constant: '<S26>/main_right_gear.location.z'
     *  Constant: '<S26>/mu_max'
     *  Constant: '<S26>/mu_min'
     *  Constant: '<S26>/nose_gear._tire ddeflection'
     *  Constant: '<S26>/nose_gear.dmax'
     *  Constant: '<S26>/nose_gear.gear'
     *  Constant: '<S26>/nose_gear.k'
     *  Constant: '<S26>/nose_gear.location.x'
     *  Constant: '<S26>/nose_gear.location.y'
     *  Constant: '<S26>/nose_gear.location.z'
     *  Constant: '<S26>/nose_gear.rotate'
     */
    rtb_TmpHiddenBufferAtSFunctio_o[0] = 0.5;
    rtb_TmpHiddenBufferAtSFunctio_o[1] = 0.05;
    rtb_TmpHiddenBufferAtSFunctio_o[2] = 1500.0;
    rtb_TmpHiddenBufferAtSFunctio_o[3] = 0.025;
    rtb_TmpHiddenBufferAtSFunctio_o[4] = 0.4;
    rtb_TmpHiddenBufferAtSFunctio_o[5] = 1.84;
    rtb_TmpHiddenBufferAtSFunctio_o[6] = 0.0;
    rtb_TmpHiddenBufferAtSFunctio_o[7] = 1.5;
    rtb_TmpHiddenBufferAtSFunctio_o[8] = 6000.0;
    rtb_TmpHiddenBufferAtSFunctio_o[9] = 2.0;
    rtb_TmpHiddenBufferAtSFunctio_o[10] = 1500.0;
    rtb_TmpHiddenBufferAtSFunctio_o[11] = 0.025;
    rtb_TmpHiddenBufferAtSFunctio_o[12] = 0.4;
    rtb_TmpHiddenBufferAtSFunctio_o[13] = -0.35;
    rtb_TmpHiddenBufferAtSFunctio_o[14] = -1.7653;
    rtb_TmpHiddenBufferAtSFunctio_o[15] = 1.5;
    rtb_TmpHiddenBufferAtSFunctio_o[16] = 6000.0;
    rtb_TmpHiddenBufferAtSFunctio_o[17] = 1.0;
    rtb_TmpHiddenBufferAtSFunctio_o[18] = 1500.0;
    rtb_TmpHiddenBufferAtSFunctio_o[19] = 0.025;
    rtb_TmpHiddenBufferAtSFunctio_o[20] = 0.4;
    rtb_TmpHiddenBufferAtSFunctio_o[21] = -0.35;
    rtb_TmpHiddenBufferAtSFunctio_o[22] = 1.7653;
    rtb_TmpHiddenBufferAtSFunctio_o[23] = 1.5;
    rtb_TmpHiddenBufferAtSFunctio_o[24] = 6000.0;
    rtb_TmpHiddenBufferAtSFunctio_o[25] = 3.0;

    /* Embedded MATLAB: '<S6>/Ground Model' incorporates:
     *  Constant: '<S2>/Constant'
     */
    {
      real_T eml_dr;
      real_T eml_p;
      real_T eml_q;
      real_T eml_r;
      real_T eml_u;
      real_T eml_phi;
      real_T eml_theta;
      real_T eml_psi;
      real_T eml_he;
      real_T eml_hedot;
      int32_T eml_i0;
      static boolean_T eml_bv0[3] = { true, false, false };

      real_T eml_dv0[9];
      real_T eml_dv1[9];
      static boolean_T eml_bv1[3] = { false, true, false };

      real_T eml_dv2[9];
      int32_T eml_i1;
      real_T eml_dv3[9];
      int32_T eml_offset;
      static boolean_T eml_bv2[3] = { false, false, true };

      real_T eml_dv4[9];
      real_T eml_Vwind_g[3];
      real_T eml_dv5[9];
      real_T eml_u_g;
      real_T eml_v_g;
      real_T eml_dv6[9];
      real_T eml_Xcg[3];
      real_T eml_Tbh[9];
      real_T eml_FbSum[3];
      real_T eml_MbSum[3];
      real_T eml_FXg;
      real_T eml_mu_max;
      real_T eml_mu_roll;
      int32_T eml_i;
      real_T eml_d_tire;
      real_T eml_dmax;
      real_T eml_gear_pos;
      real_T eml_dv7[3];
      real_T eml_Xgb[3];
      real_T eml_Fb[3];
      real_T eml_Mb[3];
      real_T eml_dv8[3];
      real_T eml_d;
      real_T eml_dv9[2];
      real_T eml_dv10[2];
      real_T eml_dv11[3];
      real_T eml_FZg;
      real_T eml_ddot;
      real_T eml_dv12[3];
      real_T eml_dv13[6];

      /* atmos = col(rho, T, g, Vwinde(3), Vgust (3), Omegagust (3)) */
      /* pilot_input = col( de, da, dr, dte, dta, dtr, df, gear, pla1, pla2) */
      eml_dr = ((BlockIO_pa34model_dueca_8b *)
                pa34model_dueca_8b_rtM->ModelData.blockIO)->Pil_uit[2] -
        (7.0881170953002904E-012);

      /* state = col( p, q, r, u, v, w, phi, theta, psi, x, y, z) */
      eml_p = ((BlockIO_pa34model_dueca_8b *)
               pa34model_dueca_8b_rtM->ModelData.blockIO)->stateo[0];
      eml_q = ((BlockIO_pa34model_dueca_8b *)
               pa34model_dueca_8b_rtM->ModelData.blockIO)->stateo[1];
      eml_r = ((BlockIO_pa34model_dueca_8b *)
               pa34model_dueca_8b_rtM->ModelData.blockIO)->stateo[2];
      eml_u = ((BlockIO_pa34model_dueca_8b *)
               pa34model_dueca_8b_rtM->ModelData.blockIO)->stateo[3];
      eml_phi = ((BlockIO_pa34model_dueca_8b *)
                 pa34model_dueca_8b_rtM->ModelData.blockIO)->stateo[6];
      eml_theta = ((BlockIO_pa34model_dueca_8b *)
                   pa34model_dueca_8b_rtM->ModelData.blockIO)->stateo[7];
      eml_psi = ((BlockIO_pa34model_dueca_8b *)
                 pa34model_dueca_8b_rtM->ModelData.blockIO)->stateo[8];

      /* statedot = col(...) */
      ((BlockIO_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->ModelData.blockIO
        )->d1 = 0.0;
      eml_he = -((BlockIO_pa34model_dueca_8b *)
                 pa34model_dueca_8b_rtM->ModelData.blockIO)->stateo[11];

      /* correct for elevation */
      eml_hedot = -((BlockIO_pa34model_dueca_8b *)
                    pa34model_dueca_8b_rtM->ModelData.blockIO)->Init[11];

      /* % Calculate RF transformation matrices */
      /* transformation matrix from RFe (earth) to RFb (body) */
      for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
        eml_dv0[3 * eml_i0] = (real_T)eml_bv0[eml_i0];
      }

      eml_dv0[1] = 0.0;
      eml_dv0[4] = cos(eml_phi);
      eml_dv0[7] = sin(eml_phi);
      eml_dv0[2] = 0.0;
      eml_dv0[5] = -sin(eml_phi);
      eml_dv0[8] = cos(eml_phi);
      eml_dv1[0] = cos(eml_theta);
      eml_dv1[3] = 0.0;
      eml_dv1[6] = -sin(eml_theta);
      for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
        eml_dv1[1 + 3 * eml_i0] = (real_T)eml_bv1[eml_i0];
      }

      eml_dv1[2] = sin(eml_theta);
      eml_dv1[5] = 0.0;
      eml_dv1[8] = cos(eml_theta);
      eml_dv2[0] = cos(eml_psi);
      eml_dv2[3] = sin(eml_psi);
      eml_dv2[6] = 0.0;
      eml_dv2[1] = -sin(eml_psi);
      eml_dv2[4] = cos(eml_psi);
      eml_dv2[7] = 0.0;
      for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
        for (eml_i1 = 0; eml_i1 < 3; eml_i1++) {
          eml_dv3[eml_i0 + 3 * eml_i1] = 0.0;
          for (eml_offset = 0; eml_offset < 3; eml_offset++) {
            eml_dv3[eml_i0 + 3 * eml_i1] += eml_dv0[eml_i0 + 3 * eml_offset] *
              eml_dv1[eml_offset + 3 * eml_i1];
          }
        }

        eml_dv2[2 + 3 * eml_i0] = (real_T)eml_bv2[eml_i0];
      }

      for (eml_offset = 0; eml_offset < 3; eml_offset++) {
        for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
          eml_dv4[eml_offset + 3 * eml_i0] = 0.0;
          for (eml_i1 = 0; eml_i1 < 3; eml_i1++) {
            eml_dv4[eml_offset + 3 * eml_i0] += eml_dv3[eml_offset + 3 * eml_i1]
              * eml_dv2[eml_i1 + 3 * eml_i0];
          }
        }

        eml_Vwind_g[eml_offset] = 0.0;
        for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
          eml_Vwind_g[eml_offset] += eml_dv4[eml_offset + 3 * eml_i0] *
            ((BlockIO_pa34model_dueca_8b *)
             pa34model_dueca_8b_rtM->ModelData.blockIO)->atmoso[3 + eml_i0];
        }

        /*  Spin up bescherming eerste seconde van touchdown */
        /* % Calculate RF transformation matrices */
        eml_dv5[3 * eml_offset] = (real_T)eml_bv0[eml_offset];
      }

      eml_u_g = eml_u + eml_Vwind_g[0];
      eml_v_g = ((BlockIO_pa34model_dueca_8b *)
                 pa34model_dueca_8b_rtM->ModelData.blockIO)->stateo[4] +
        eml_Vwind_g[1];
      eml_dv5[1] = 0.0;
      eml_dv5[4] = cos(eml_phi);
      eml_dv5[7] = sin(eml_phi);
      eml_dv5[2] = 0.0;
      eml_dv5[5] = -sin(eml_phi);
      eml_dv5[8] = cos(eml_phi);
      eml_dv6[0] = cos(eml_theta);
      eml_dv6[3] = 0.0;
      eml_dv6[6] = -sin(eml_theta);
      for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
        eml_dv6[1 + 3 * eml_i0] = (real_T)eml_bv1[eml_i0];
      }

      eml_dv6[2] = sin(eml_theta);
      eml_dv6[5] = 0.0;
      eml_dv6[8] = cos(eml_theta);

      /* transformation matrix from RFh (heading attached) to RFb (body) */
      /* massmodel = col(m, Ixx, Iyy, Izz, Ixy, cg(3)) */
      eml_Xcg[0] = ((BlockIO_pa34model_dueca_8b *)
                    pa34model_dueca_8b_rtM->ModelData.blockIO)->y[5];
      eml_Xcg[1] = ((BlockIO_pa34model_dueca_8b *)
                    pa34model_dueca_8b_rtM->ModelData.blockIO)->y[6];
      eml_Xcg[2] = ((BlockIO_pa34model_dueca_8b *)
                    pa34model_dueca_8b_rtM->ModelData.blockIO)->y[7];
      for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
        for (eml_i1 = 0; eml_i1 < 3; eml_i1++) {
          eml_Tbh[eml_i0 + 3 * eml_i1] = 0.0;
          for (eml_offset = 0; eml_offset < 3; eml_offset++) {
            eml_Tbh[eml_i0 + 3 * eml_i1] += eml_dv5[eml_i0 + 3 * eml_offset] *
              eml_dv6[eml_offset + 3 * eml_i1];
          }
        }

        /*  landingmodel = col( mu_max, mu_min, several objects with 8 parameters each: {k,d_tire,dmax,xg,yg,zg,demp, gear_pos}) */
        eml_FbSum[eml_i0] = 0.0;
        eml_MbSum[eml_i0] = 0.0;
      }

      /*  initialiseren op nul in verband met if loops in rtw */
      eml_FXg = 0.0;
      rtb_landed = 0U;
      if (((BlockIO_pa34model_dueca_8b *)
           pa34model_dueca_8b_rtM->ModelData.blockIO)->Pil_uit[7] != 0.0) {
        eml_mu_max = rtb_TmpHiddenBufferAtSFunctio_o[0];
        eml_mu_roll = rtb_TmpHiddenBufferAtSFunctio_o[1];
        ((BlockIO_pa34model_dueca_8b *)
          pa34model_dueca_8b_rtM->ModelData.blockIO)->d1 =
          rtb_TmpHiddenBufferAtSFunctio_o[5] - rtb_TmpHiddenBufferAtSFunctio_o
          [13];
        for (eml_i = 0; eml_i < 3; eml_i++) {
          eml_offset = (eml_i << 3) + 2;
          eml_psi = rtb_TmpHiddenBufferAtSFunctio_o[eml_offset];
          eml_d_tire = rtb_TmpHiddenBufferAtSFunctio_o[eml_offset + 1];
          eml_dmax = rtb_TmpHiddenBufferAtSFunctio_o[eml_offset + 2];
          eml_gear_pos = rtb_TmpHiddenBufferAtSFunctio_o[eml_offset + 7];

          /*  1=Left 2=Nose  3 =Right */
          /* calcultate landing gear position vector wrt the cg */
          eml_dv7[0] = rtb_TmpHiddenBufferAtSFunctio_o[eml_offset + 3];
          eml_dv7[1] = rtb_TmpHiddenBufferAtSFunctio_o[eml_offset + 4];
          eml_dv7[2] = rtb_TmpHiddenBufferAtSFunctio_o[eml_offset + 5];
          for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
            eml_Xgb[eml_i0] = eml_dv7[eml_i0] - eml_Xcg[eml_i0];
          }

          /*  Transformation only shifted to CG do not invert axis */
          /*  Initialiseer kracht en moment */
          for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
            eml_Fb[eml_i0] = 0.0;
          }

          for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
            eml_Mb[eml_i0] = 0.0;
          }

          /* Calculate spring deflection  */
          /* delta is upwards positive and RFb is downwards positive */
          for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
            eml_dv8[eml_i0] = 0.0;
            for (eml_i1 = 0; eml_i1 < 3; eml_i1++) {
              eml_dv8[eml_i0] += eml_Tbh[eml_i1 + 3 * eml_i0] * eml_Xgb[eml_i1];
            }
          }

          eml_d = eml_dv8[2] - (eml_he - rtb_Sum_c[eml_i]);
          if (eml_d < 0.0) {
            if (eml_gear_pos == 1.0) {
              ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork
                )->wheelspin_left = 0.0;
            }

            if (eml_gear_pos == 3.0) {
              ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork
                )->wheelspin_right = 0.0;
            }
          }

          eml_dv9[0] = 0.0;
          eml_dv9[1] = eml_d;
          eml_dv10[0] = ppphopphfkngdbie_max(eml_dv9);
          eml_dv10[1] = eml_dmax;
          eml_d = djmobaaadjmofkng_min(eml_dv10);
          if (eml_d > 0.0) {
            if (eml_gear_pos == 1.0) {
              /* (>= 0 && < dmax)  */
              ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork
                )->wheelspin_left = ((D_Work_pa34model_dueca_8b *)
                pa34model_dueca_8b_rtM->Work.dwork)->wheelspin_left + 1.0;
            }

            if (eml_gear_pos == 3.0) {
              ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork
                )->wheelspin_right = ((D_Work_pa34model_dueca_8b *)
                pa34model_dueca_8b_rtM->Work.dwork)->wheelspin_right + 1.0;
            }

            /* calc ddot */
            eml_dv11[0] = (-eml_q) * cos(eml_theta);
            eml_dv11[1] = eml_p * cos(eml_phi);
            eml_dv11[2] = 0.0;
            eml_FZg = 0.0;
            for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
              eml_FZg += eml_dv11[eml_i0] * eml_Xgb[eml_i0];
            }

            /* ddot = -hedot/(cos(phi)*cos(theta)); */
            /* gear is deflected */
            eml_Xgb[2] += eml_d;
            if (eml_d < eml_d_tire) {
              /* calc deflected position */
              /* calculate forces on the gear   */
              /*  Geen lineaire veer maar PV=C ter vermijding van door de grond */
              /*  gaan en eerst band indrukken dan oleo */
              eml_FZg = (-eml_d) * eml_psi / eml_d_tire;

              /*  Inveren van band zonder demping tot preload =k is dus ook de veerconstante */
            } else {
              /*  Na indeuken band neemt oleo met voorspanning over  */
              eml_psi = eml_psi * (eml_dmax - eml_d_tire) / ((eml_dmax - eml_d)
                + 0.001) + rtb_TmpHiddenBufferAtSFunctio_o[eml_offset + 6] *
                (eml_FZg - eml_hedot);
              if (!(eml_psi >= 0.0)) {
                eml_psi = 0.0;
              }

              eml_FZg = -eml_psi;

              /* normal force alleen omhoog */
            }

            if (eml_u > 20.0) {
              /*  Als throttles <50% dan wordt er geremd */
              /*  Boven de 20 m/s differential brakes dmv rudder */
              /*  Onder de 20 m/s no differential brakes maar nosewheel steering */
              eml_d_tire = eml_dr;
            } else {
              eml_psi = (eml_u_g - 15.0) / 5.0;
              if (!(eml_psi >= 0.0)) {
                eml_psi = 0.0;
              }

              eml_d_tire = eml_dr * eml_psi;

              /* Blending naar rudder */
            }

            /*  Rudder geeft differential braking, rechts rudder linker brake releasen! */
            eml_psi = -eml_d_tire;
            if (!(eml_psi >= 0.0)) {
              eml_psi = 0.0;
            }

            if ((1.0 <= eml_psi) || ((boolean_T)rtIsNaN(eml_psi))) {
              eml_psi = 1.0;
            }

            eml_dmax = 0.5 - ((BlockIO_pa34model_dueca_8b *)
                              pa34model_dueca_8b_rtM->ModelData.blockIO)
              ->Pil_uit[8];
            if (!(eml_dmax >= 0.0)) {
              eml_dmax = 0.0;
            }

            eml_ddot = 2.0 * eml_dmax * (1.0 - eml_psi);
            if (!(eml_d_tire >= 0.0)) {
              eml_d_tire = 0.0;
            }

            if ((1.0 <= eml_d_tire) || ((boolean_T)rtIsNaN(eml_d_tire))) {
              eml_d_tire = 1.0;
            }

            eml_psi = 0.5 - ((BlockIO_pa34model_dueca_8b *)
                             pa34model_dueca_8b_rtM->ModelData.blockIO)->
              Pil_uit[9];
            if (!(eml_psi >= 0.0)) {
              eml_psi = 0.0;
            }

            eml_d = 2.0 * eml_psi * (1.0 - eml_d_tire);
            if ((eml_gear_pos == 2.0) && (fabs(eml_u_g) < 20.0)) {
              /*  eerst de zijkracht als functie van sliphoek band */
              /*  waarde bij zero slip bij 5 graden slip maximale kracht */
              /*  Vermijd delen door nul bij lage snelheid */
              /*  neuswiel steering available */
              eml_psi = (20.0 - fabs(eml_u_g)) / 5.0;
              if (!(eml_psi <= 1.0)) {
                eml_psi = 1.0;
              }

              /*  De neuswiel geblend met hoek reductie als u_g>15 */
              /*  De rate die bij neuswiel pos. hoort */
              eml_psi = ((BlockIO_pa34model_dueca_8b *)
                         pa34model_dueca_8b_rtM->ModelData.blockIO)->d1 * (eml_r
                - (-(eml_dr / 3.0 * eml_psi)) * eml_u_g /
                ((BlockIO_pa34model_dueca_8b *)
                 pa34model_dueca_8b_rtM->ModelData.blockIO)->d1);

              /*  extra zij snelheid op neuswiel */
              eml_d_tire = fabs(eml_v_g + eml_psi) / (fabs(eml_u_g) + 4.0) *
                11.4592;
              if (!(eml_d_tire <= 1.0)) {
                eml_d_tire = 1.0;
              }

              eml_psi += eml_v_g;
              if ((boolean_T)rtIsNaN(eml_psi)) {
                eml_psi = rtNaN;
              } else if (eml_psi > 0.0) {
                eml_psi = 1.0;
              } else if (eml_psi < 0.0) {
                eml_psi = -1.0;
              }

              eml_dmax = eml_psi * eml_FZg * eml_mu_max * eml_d_tire;
            } else {
              eml_psi = fabs(eml_v_g) / (fabs(eml_u_g) + 4.0) * 11.4592;
              if (!(eml_psi <= 1.0)) {
                eml_psi = 1.0;
              }

              eml_d_tire = eml_v_g;
              if ((boolean_T)rtIsNaN(eml_v_g)) {
                eml_d_tire = rtNaN;
              } else if (eml_v_g > 0.0) {
                eml_d_tire = 1.0;
              } else if (eml_v_g < 0.0) {
                eml_d_tire = -1.0;
              }

              eml_dmax = eml_d_tire * eml_FZg * eml_mu_max * eml_psi;
            }

            /*  Beschikbare remkracht uitrekenen na aftrek zijkracht */
            eml_d_tire = -sqrt(pow(eml_FZg * eml_mu_max, 2.0) - pow(eml_dmax,
              2.0));
            if (((D_Work_pa34model_dueca_8b *)
                 pa34model_dueca_8b_rtM->Work.dwork)->wheelspin_left < 150.0) {
              /*  Spin up protectie */
              eml_ddot = 0.0;
            }

            if (((D_Work_pa34model_dueca_8b *)
                 pa34model_dueca_8b_rtM->Work.dwork)->wheelspin_right < 150.0) {
              eml_d = 0.0;
            }

            if (eml_gear_pos == 1.0) {
              /*  if wheelspin<3000; brakes_L=brakes_L*((wheelspin-1500)/3000);brakes_R=brakes_R*((wheelspin-1500)/3000);end */
              /*  Hoofdwielen met brakes */
              eml_psi = eml_u_g;
              if ((boolean_T)rtIsNaN(eml_u_g)) {
                eml_psi = rtNaN;
              } else if (eml_u_g > 0.0) {
                eml_psi = 1.0;
              } else if (eml_u_g < 0.0) {
                eml_psi = -1.0;
              }

              eml_FXg = (eml_d_tire * eml_ddot + eml_mu_roll * eml_FZg) *
                eml_psi;
            }

            if (eml_gear_pos == 3.0) {
              eml_psi = eml_u_g;
              if ((boolean_T)rtIsNaN(eml_u_g)) {
                eml_psi = rtNaN;
              } else if (eml_u_g > 0.0) {
                eml_psi = 1.0;
              } else if (eml_u_g < 0.0) {
                eml_psi = -1.0;
              }

              eml_FXg = (eml_d_tire * eml_d + eml_mu_roll * eml_FZg) * eml_psi;
            }

            if (eml_gear_pos == 2.0) {
              /*  Geen braking op nose wheel alleen roll frictie */
              eml_psi = eml_u_g;
              if ((boolean_T)rtIsNaN(eml_u_g)) {
                eml_psi = rtNaN;
              } else if (eml_u_g > 0.0) {
                eml_psi = 1.0;
              } else if (eml_u_g < 0.0) {
                eml_psi = -1.0;
              }

              eml_FXg = eml_mu_roll * eml_FZg * eml_psi;
            }

            if (fabs(eml_u_g) < 1.0) {
              /* convert to RFb */
              /*  Forces op het gear  in de body frame ! Stabiliseert! */
              eml_Fb[0] = eml_FXg;
              eml_Fb[1] = eml_dmax;
              eml_Fb[2] = eml_FZg;

              /* braking and ground reaction                */
            } else {
              eml_dv12[0] = eml_FXg;
              eml_dv12[1] = eml_dmax;
              eml_dv12[2] = eml_FZg;
              for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
                eml_Fb[eml_i0] = 0.0;
                for (eml_i1 = 0; eml_i1 < 3; eml_i1++) {
                  eml_Fb[eml_i0] += eml_Tbh[eml_i0 + 3 * eml_i1] *
                    eml_dv12[eml_i1];
                }
              }

              /* braking and ground reaction */
            }

            /* calc moments */
            eml_Mb[0] = eml_Xgb[1] * eml_Fb[2] - eml_Xgb[2] * eml_Fb[1];
            eml_Mb[1] = eml_Xgb[2] * eml_Fb[0] - eml_Xgb[0] * eml_Fb[2];
            eml_Mb[2] = eml_Xgb[0] * eml_Fb[1] - eml_Xgb[1] * eml_Fb[0];

            /* moment introduced by moving the forces from the gear to the cg */
          }

          /* Sum the Forces and Moments of landing gear */
          for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
            eml_FbSum[eml_i0] += eml_Fb[eml_i0];
          }

          for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
            eml_MbSum[eml_i0] += eml_Mb[eml_i0];
          }
        }

        if ((((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork
             )->wheelspin_left > 150.0) && (((D_Work_pa34model_dueca_8b *)
              pa34model_dueca_8b_rtM->Work.dwork)->wheelspin_right > 150.0)) {
          /*  Alpha en beta niet adjusten, anders wordt beta op nul gezet en kan cross */
          /*  wind landing niet worden geoefend. */
          rtb_landed = 1U;

          /* all wheels on the ground   */
        }
      }

      if ((fabs(eml_u_g) < 1.0) && (rtb_landed == 1)) {
        if (fabs(eml_FbSum[0]) > fabs(rtb_FMair[0])) {
          /*    Aanpassen bij u_g => 0 */
          eml_FbSum[0] = (-eml_u_g) * 10000.0 - rtb_FMair[0];
        }

        eml_FbSum[1] = (-eml_v_g) * 10000.0 - rtb_FMair[1];
        eml_FbSum[2] = (-(((BlockIO_pa34model_dueca_8b *)
                           pa34model_dueca_8b_rtM->ModelData.blockIO)->stateo[5]
                          + eml_Vwind_g[2])) * 5000.0 - rtb_FMair[2];

        /*  */
        eml_MbSum[0] = (-eml_p) * 10000.0 - rtb_FMair[3];

        /*  */
        eml_MbSum[1] = (-eml_q) * 10000.0 - rtb_FMair[4];

        /*  */
        eml_MbSum[2] = (-eml_r) * 10000.0 - rtb_FMair[5];
      }

      /* Create output vector */
      for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
        eml_dv13[eml_i0] = eml_FbSum[eml_i0];
      }

      for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
        eml_dv13[eml_i0 + 3] = eml_MbSum[eml_i0];
      }

      for (eml_i0 = 0; eml_i0 < 6; eml_i0++) {
        rtb_FMb[eml_i0] = rtb_FMair[eml_i0] + eml_dv13[eml_i0];
      }
    }

    /* SignalConversion: '<S8>/TmpHiddenBufferAt SFunction Inport1' */
    rtb_TmpHiddenBufferAtSFunctio_a[0] = rtb_rho;
    rtb_TmpHiddenBufferAtSFunctio_a[1] = rtb_T;
    rtb_TmpHiddenBufferAtSFunctio_a[2] = rtb_g;
    rtb_TmpHiddenBufferAtSFunctio_a[3] = rtb_Vwinde[0];
    rtb_TmpHiddenBufferAtSFunctio_a[4] = rtb_Vwinde[1];
    rtb_TmpHiddenBufferAtSFunctio_a[5] = rtb_Vwinde[2];
    rtb_TmpHiddenBufferAtSFunctio_a[6] = fractionTmp_0d;
    rtb_TmpHiddenBufferAtSFunctio_a[7] = rtb_Product_idx;
    rtb_TmpHiddenBufferAtSFunctio_a[8] = rtb_Product_idx_0;
    rtb_TmpHiddenBufferAtSFunctio_a[9] = rtb_Product1_idx;
    rtb_TmpHiddenBufferAtSFunctio_a[10] = rtb_Product1_idx_0;
    rtb_TmpHiddenBufferAtSFunctio_a[11] = rtb_Product1_idx_1;

    /* Embedded MATLAB: '<S1>/Equations of Motion' */
    {
      real_T eml_Ixz;
      real_T eml_Ixy;
      real_T eml_Izy;
      real_T eml_J[9];
      real_T eml_Omega_be[3];
      real_T eml_Vb[3];
      int32_T eml_i0;
      int32_T eml_i1;
      real_T eml_dv0[9];
      real_T eml_dv1[9];
      real_T eml_dv2[3];
      static boolean_T eml_bv0[3] = { true, false, false };

      real_T eml_dv3[9];
      real_T eml_b[3];
      real_T eml_y;
      real_T eml_dv4[3];
      real_T eml_dv5[3];
      real_T eml_dv6[3];
      real_T eml_dv7[9];
      real_T eml_dv8[9];
      static boolean_T eml_bv1[3] = { false, true, false };

      real_T eml_dv9[9];
      real_T eml_dv10[9];
      int32_T eml_i2;
      static boolean_T eml_bv2[3] = { false, false, true };

      real_T eml_dv11[9];
      real_T eml_dv12[3];

      /*  Calculate State derivative  */
      /* % Obtain parameters */
      /* atmos = col(rho, T, g, Vwinde(3), Vgust (3), Omegagust (3)) */
      /* massmodel = col(m, Ixx, Iyy, Izz, Ixy, cg(3), Ixy, Izy) */
      eml_Ixz = ((BlockIO_pa34model_dueca_8b *)
                 pa34model_dueca_8b_rtM->ModelData.blockIO)->y[4];
      eml_Ixy = ((BlockIO_pa34model_dueca_8b *)
                 pa34model_dueca_8b_rtM->ModelData.blockIO)->y[8];
      eml_Izy = ((BlockIO_pa34model_dueca_8b *)
                 pa34model_dueca_8b_rtM->ModelData.blockIO)->y[9];
      eml_J[0] = ((BlockIO_pa34model_dueca_8b *)
                  pa34model_dueca_8b_rtM->ModelData.blockIO)->y[1];
      eml_J[3] = -eml_Ixy;
      eml_J[6] = -eml_Ixz;
      eml_J[1] = -eml_Ixy;
      eml_J[4] = ((BlockIO_pa34model_dueca_8b *)
                  pa34model_dueca_8b_rtM->ModelData.blockIO)->y[2];
      eml_J[7] = -eml_Izy;
      eml_J[2] = -eml_Ixz;
      eml_J[5] = -eml_Izy;
      eml_J[8] = ((BlockIO_pa34model_dueca_8b *)
                  pa34model_dueca_8b_rtM->ModelData.blockIO)->y[3];

      /* state = col( p, q, r, u, v, w, phi, theta, psi, x, y, z) */
      eml_Omega_be[0] = ((BlockIO_pa34model_dueca_8b *)
                         pa34model_dueca_8b_rtM->ModelData.blockIO)->stateo[0];
      eml_Omega_be[1] = ((BlockIO_pa34model_dueca_8b *)
                         pa34model_dueca_8b_rtM->ModelData.blockIO)->stateo[1];
      eml_Omega_be[2] = ((BlockIO_pa34model_dueca_8b *)
                         pa34model_dueca_8b_rtM->ModelData.blockIO)->stateo[2];
      eml_Vb[0] = ((BlockIO_pa34model_dueca_8b *)
                   pa34model_dueca_8b_rtM->ModelData.blockIO)->stateo[3];
      eml_Vb[1] = ((BlockIO_pa34model_dueca_8b *)
                   pa34model_dueca_8b_rtM->ModelData.blockIO)->stateo[4];
      eml_Vb[2] = ((BlockIO_pa34model_dueca_8b *)
                   pa34model_dueca_8b_rtM->ModelData.blockIO)->stateo[5];
      eml_Ixz = ((BlockIO_pa34model_dueca_8b *)
                 pa34model_dueca_8b_rtM->ModelData.blockIO)->stateo[6];
      eml_Ixy = ((BlockIO_pa34model_dueca_8b *)
                 pa34model_dueca_8b_rtM->ModelData.blockIO)->stateo[7];
      eml_Izy = ((BlockIO_pa34model_dueca_8b *)
                 pa34model_dueca_8b_rtM->ModelData.blockIO)->stateo[8];

      /* % Calculate RF transformation matrices */
      /* transformation matrix from RFe (earth) to RFb (body) */
      /* % Sum Forces and Moments in RFb */
      /* total force  (in RFb) = aerodynamic + thrust + gravity + wind correction */
      /* total moment (in RFb) = aerodynamic + thrust */
      /*   */
      /*  Fb(1)=max(min(5000,Fb(1)),-5000); */
      /*  Fb(3)=max(min(15000,Fb(3)),-15000); */
      /* % Calculate and output state derivatives,Fb(1) */
      for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
        for (eml_i1 = 0; eml_i1 < 3; eml_i1++) {
          eml_dv0[eml_i1 + 3 * eml_i0] = eml_J[eml_i1 + 3 * eml_i0];

          /* kinematics */
          /* euler_dot=[0;0;0]; */
          eml_dv1[eml_i1 + 3 * eml_i0] = eml_J[eml_i1 + 3 * eml_i0];
        }

        eml_dv2[eml_i0] = rtb_FMb[3 + eml_i0];
        eml_dv3[3 * eml_i0] = (real_T)eml_bv0[eml_i0];
      }

      lfcbjmglknopimgl_mldivide(eml_dv0, eml_Omega_be, eml_b);

      /*  Omega_be_dot(1)=max(min(10,Omega_be_dot(1)),-10); */
      /*  Omega_be_dot(2)=max(min(10,Omega_be_dot(2)),-10); */
      /*  Omega_be_dot(3)=max(min(10,Omega_be_dot(3)),-10); */
      eml_y = 1.0 / ((BlockIO_pa34model_dueca_8b *)
                     pa34model_dueca_8b_rtM->ModelData.blockIO)->y[0];
      lfcbjmglknopimgl_mldivide(eml_dv1, eml_dv2, eml_dv4);
      eml_dv5[0] = eml_Omega_be[1] * eml_b[2] - eml_Omega_be[2] * eml_b[1];
      eml_dv5[1] = eml_Omega_be[2] * eml_b[0] - eml_Omega_be[0] * eml_b[2];
      eml_dv5[2] = eml_Omega_be[0] * eml_b[1] - eml_Omega_be[1] * eml_b[0];
      lfcbjmglknopimgl_mldivide(eml_J, eml_dv5, eml_b);
      eml_dv6[0] = eml_Omega_be[1] * eml_Vb[2] - eml_Omega_be[2] * eml_Vb[1];
      eml_dv6[1] = eml_Omega_be[2] * eml_Vb[0] - eml_Omega_be[0] * eml_Vb[2];
      eml_dv6[2] = eml_Omega_be[0] * eml_Vb[1] - eml_Omega_be[1] * eml_Vb[0];
      eml_dv7[0] = 1.0;
      eml_dv7[3] = sin(eml_Ixz) * tan(eml_Ixy);
      eml_dv7[6] = cos(eml_Ixz) * tan(eml_Ixy);
      eml_dv7[1] = 0.0;
      eml_dv7[4] = cos(eml_Ixz);
      eml_dv7[7] = -sin(eml_Ixz);
      eml_dv7[2] = 0.0;
      eml_dv7[5] = sin(eml_Ixz) / cos(eml_Ixy);
      eml_dv7[8] = cos(eml_Ixz) / cos(eml_Ixy);
      eml_dv3[1] = 0.0;
      eml_dv3[4] = cos(eml_Ixz);
      eml_dv3[7] = sin(eml_Ixz);
      eml_dv3[2] = 0.0;
      eml_dv3[5] = -sin(eml_Ixz);
      eml_dv3[8] = cos(eml_Ixz);
      eml_dv8[0] = cos(eml_Ixy);
      eml_dv8[3] = 0.0;
      eml_dv8[6] = -sin(eml_Ixy);
      for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
        eml_dv8[1 + 3 * eml_i0] = (real_T)eml_bv1[eml_i0];
      }

      eml_dv8[2] = sin(eml_Ixy);
      eml_dv8[5] = 0.0;
      eml_dv8[8] = cos(eml_Ixy);
      eml_dv9[0] = cos(eml_Izy);
      eml_dv9[3] = sin(eml_Izy);
      eml_dv9[6] = 0.0;
      eml_dv9[1] = -sin(eml_Izy);
      eml_dv9[4] = cos(eml_Izy);
      eml_dv9[7] = 0.0;
      for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
        for (eml_i1 = 0; eml_i1 < 3; eml_i1++) {
          eml_dv10[eml_i0 + 3 * eml_i1] = 0.0;
          for (eml_i2 = 0; eml_i2 < 3; eml_i2++) {
            eml_dv10[eml_i0 + 3 * eml_i1] += eml_dv3[eml_i0 + 3 * eml_i2] *
              eml_dv8[eml_i2 + 3 * eml_i1];
          }
        }

        eml_dv9[2 + 3 * eml_i0] = (real_T)eml_bv2[eml_i0];
      }

      for (eml_i2 = 0; eml_i2 < 3; eml_i2++) {
        for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
          eml_dv11[eml_i2 + 3 * eml_i0] = 0.0;
          for (eml_i1 = 0; eml_i1 < 3; eml_i1++) {
            eml_dv11[eml_i2 + 3 * eml_i0] += eml_dv10[eml_i0 + 3 * eml_i1] *
              eml_dv9[eml_i1 + 3 * eml_i2];
          }
        }

        eml_dv12[eml_i2] = 0.0;
        for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
          eml_dv12[eml_i2] += eml_dv7[eml_i2 + 3 * eml_i0] * eml_Omega_be[eml_i0];
        }
      }

      for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
        eml_Ixz = 0.0;
        for (eml_i1 = 0; eml_i1 < 3; eml_i1++) {
          eml_Ixz += eml_dv11[eml_i0 + 3 * eml_i1] * eml_Vb[eml_i1];
        }

        eml_dv2[eml_i0] = eml_Ixz + rtb_TmpHiddenBufferAtSFunctio_a[3 + eml_i0];
      }

      for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
        ((BlockIO_pa34model_dueca_8b *)
          pa34model_dueca_8b_rtM->ModelData.blockIO)->state_dot[eml_i0] =
          eml_dv4[eml_i0] - eml_b[eml_i0];
      }

      for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
        ((BlockIO_pa34model_dueca_8b *)
          pa34model_dueca_8b_rtM->ModelData.blockIO)->state_dot[eml_i0 + 3] =
          eml_y * rtb_FMb[eml_i0] - eml_dv6[eml_i0];
      }

      for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
        ((BlockIO_pa34model_dueca_8b *)
          pa34model_dueca_8b_rtM->ModelData.blockIO)->state_dot[eml_i0 + 6] =
          eml_dv12[eml_i0];
      }

      for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
        ((BlockIO_pa34model_dueca_8b *)
          pa34model_dueca_8b_rtM->ModelData.blockIO)->state_dot[eml_i0 + 9] =
          eml_dv2[eml_i0];
      }

      /* d/dt of col( Omega_be, Vb, euler, Xe) */
    }

    /* SignalConversion: '<S7>/TmpHiddenBufferAt SFunction Inport1' */
    rtb_TmpHiddenBufferAtSFunctio_p[0] = rtb_rho;
    rtb_TmpHiddenBufferAtSFunctio_p[1] = rtb_T;
    rtb_TmpHiddenBufferAtSFunctio_p[2] = rtb_g;
    rtb_TmpHiddenBufferAtSFunctio_p[3] = rtb_Vwinde[0];
    rtb_TmpHiddenBufferAtSFunctio_p[4] = rtb_Vwinde[1];
    rtb_TmpHiddenBufferAtSFunctio_p[5] = rtb_Vwinde[2];
    rtb_TmpHiddenBufferAtSFunctio_p[6] = fractionTmp_0d;
    rtb_TmpHiddenBufferAtSFunctio_p[7] = rtb_Product_idx;
    rtb_TmpHiddenBufferAtSFunctio_p[8] = rtb_Product_idx_0;
    rtb_TmpHiddenBufferAtSFunctio_p[9] = rtb_Product1_idx;
    rtb_TmpHiddenBufferAtSFunctio_p[10] = rtb_Product1_idx_0;
    rtb_TmpHiddenBufferAtSFunctio_p[11] = rtb_Product1_idx_1;

    /* Embedded MATLAB: '<S1>/Create Output1' incorporates:
     *   Inport: '<Root>/In1'
     */
    {
      real_T eml_p;
      real_T eml_q;
      real_T eml_r;
      real_T eml_u;
      real_T eml_v;
      real_T eml_w;
      real_T eml_Vb[3];
      real_T eml_phi;
      real_T eml_theta;
      real_T eml_psi;
      real_T eml_z;
      real_T eml_ax;
      real_T eml_ay;
      real_T eml_az;
      real_T eml_ue;
      real_T eml_ve;
      real_T eml_we;
      real_T eml_Ve[3];
      real_T eml_Vground;
      int32_T eml_i0;
      real_T eml_vtas;
      real_T eml_alpha;
      real_T eml_beta;
      real_T eml_anzb;
      real_T eml_gamma_true;

      /*  This block supports the Embedded MATLAB subset.~~ */
      /*  See the help menu for details.  */
      /* general parameters */
      /* Flattening (WGS84) */
      /* Equatorial radius of the planet (WGS84) */
      /* % Obtain parameters */
      /* % Obtain parameters */
      /* atmos = col(rho, T, g, Vwinde(3), Vgust (3), Omegagust (3)) */
      /* state = col( p, q, r, u, v, w, phi, theta, psi, x, y, z) */
      eml_p = ((BlockIO_pa34model_dueca_8b *)
               pa34model_dueca_8b_rtM->ModelData.blockIO)->stateo[0];
      eml_q = ((BlockIO_pa34model_dueca_8b *)
               pa34model_dueca_8b_rtM->ModelData.blockIO)->stateo[1];
      eml_r = ((BlockIO_pa34model_dueca_8b *)
               pa34model_dueca_8b_rtM->ModelData.blockIO)->stateo[2];
      eml_u = ((BlockIO_pa34model_dueca_8b *)
               pa34model_dueca_8b_rtM->ModelData.blockIO)->stateo[3];
      eml_v = ((BlockIO_pa34model_dueca_8b *)
               pa34model_dueca_8b_rtM->ModelData.blockIO)->stateo[4];
      eml_w = ((BlockIO_pa34model_dueca_8b *)
               pa34model_dueca_8b_rtM->ModelData.blockIO)->stateo[5];
      eml_Vb[0] = eml_u;
      eml_Vb[1] = eml_v;
      eml_Vb[2] = eml_w;
      eml_phi = ((BlockIO_pa34model_dueca_8b *)
                 pa34model_dueca_8b_rtM->ModelData.blockIO)->stateo[6];
      eml_theta = ((BlockIO_pa34model_dueca_8b *)
                   pa34model_dueca_8b_rtM->ModelData.blockIO)->stateo[7];
      eml_psi = ((BlockIO_pa34model_dueca_8b *)
                 pa34model_dueca_8b_rtM->ModelData.blockIO)->stateo[8];
      eml_z = ((BlockIO_pa34model_dueca_8b *)
               pa34model_dueca_8b_rtM->ModelData.blockIO)->stateo[11];

      /* statedot (see state) */
      /*  Accelerations in body axis */
      eml_ax = ((BlockIO_pa34model_dueca_8b *)
                pa34model_dueca_8b_rtM->ModelData.blockIO)->state_dot[3];
      eml_ay = ((BlockIO_pa34model_dueca_8b *)
                pa34model_dueca_8b_rtM->ModelData.blockIO)->state_dot[4];
      eml_az = ((BlockIO_pa34model_dueca_8b *)
                pa34model_dueca_8b_rtM->ModelData.blockIO)->state_dot[5];
      eml_ue = ((BlockIO_pa34model_dueca_8b *)
                pa34model_dueca_8b_rtM->ModelData.blockIO)->state_dot[9];
      eml_ve = ((BlockIO_pa34model_dueca_8b *)
                pa34model_dueca_8b_rtM->ModelData.blockIO)->state_dot[10];
      eml_we = ((BlockIO_pa34model_dueca_8b *)
                pa34model_dueca_8b_rtM->ModelData.blockIO)->state_dot[11];
      eml_Ve[0] = eml_ue;
      eml_Ve[1] = eml_ve;
      eml_Ve[2] = eml_we;

      /* state_IMU = col(axb_m,ayb_m,azb_m,pdot_m,qdot_m,rdot_m) */
      /* NOTE Ab_m equals Fb/m. (So not Fb/m - omega_b x V_b => Ab) */
      /* % Calculate RF transformation matrices */
      /* transformation matrix from RFe (earth) to RFb (body) */
      /* Tbe_dot'*Vb is not needed, Ae is only a vector transformation from RFb to RFe */
      /* % Calculate vtas, alpha, beta and vtas_dot, alpha_dot, beta_dot */
      eml_Vground = 0.0;
      for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
        eml_Vground += eml_Vb[eml_i0] * eml_Vb[eml_i0];
      }

      eml_vtas = sqrt(eml_Vground);

      /*  if (~landed) */
      eml_alpha = cbaabiecohlncbaa_atan2(eml_w, eml_u);
      eml_beta = asin(eml_v / eml_vtas);

      /*  else */
      /*      %when landed calculations become different */
      /*      alpha = 0; */
      /*      beta = 0; */
      /*      vtas_dot = 0; */
      /*      alpha_dot = 0; */
      /*      beta_dot = 0; */
      /*  end */
      /*  The inertial accelerations measured in body coordinates */
      eml_anzb = ((-9.80665 * cos(eml_theta) * cos(eml_phi) + eml_az) - eml_q *
                  cos(eml_alpha) * eml_vtas) + eml_p * sin(eml_beta) * eml_vtas;

      /* % Calculate Vground, gamma_true, chi_true and Vground_dot, gamma_true_dot, chi_true_dot */
      eml_Vground = 0.0;
      for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
        eml_Vground += eml_Ve[eml_i0] * eml_Ve[eml_i0];
      }

      eml_Vground = sqrt(eml_Vground);
      if (!rtb_landed) {
        eml_gamma_true = -asin(eml_we / eml_Vground);
        eml_ue = cbaabiecohlncbaa_atan2(eml_ve, eml_ue);
      } else {
        eml_gamma_true = 0.0;
        eml_ue = eml_psi;
      }


      /* % Calculate n */
      /*  n = 1+az/g0; */
      /*  Vnv x,y,z, naar lat long */
      /*  if (true) */
      /*      % Convert flat earth to lat lon altitude using WGS84 earth model */
      /*      % x,y,z: local north east down position [m] */
      /*      % hgrnd: altitude of the ground, positive upwards [m] */
      /*      % LLO: Initial geodetic latitude and longitude [deg] */
      /*      % psi: Direction of flat Earth x-axis (degrees clockwise from north) [deg] */
      /*      % */
      /*      % Output: lat (mu), lon (l) [rad] and h [m] */
      /*       */
      /*      mu = LL0(1); */
      /*       */
      /*      %convert deg to rad */
      /*      psi_LL = psi_LL*pi/180; */
      /*      mu = mu*pi/180; */
      /*   */
      /*      %Find Radian/Distance: calc e, eps, denom, Rn, Rm, dNorth and dEast */
      /*      e = 1-F; */
      /*      eps = sqrt(1-e^2); */
      /*      denom = 1-(eps*sin(mu))^2; */
      /*      Rn = R/sqrt(denom); */
      /*      Rm = Rn*(1-eps^2)/denom; */
      /*      dNorth = atan2(1,Rm); */
      /*      dEast = atan2(1,Rn*cos(mu)); */
      /*   */
      /*      %calc mu and l */
      /*      mu = (x*cos(psi_LL)-y*sin(psi_LL))*dNorth; */
      /*      l = (x*sin(psi_LL)+y*cos(psi_LL))*dEast; */
      /*   */
      /*      %convert rad to deg */
      /*      mu = mu*180/pi; */
      /*      l = l*180/pi; */
      /*       */
      /*      %add initial position */
      /*      mu = mu+LL0(1); */
      /*      l = l+LL0(2); */
      /*   */
      /*      %limit lat between +/- 90 */
      /*      mu = rem(mu,360)-fix(rem(mu,360)/180)*360; */
      /*      tmp = fix(sqrt((mu/180*2)*(mu/180*2)))*2; */
      /*      if (tmp) */
      /*          l = l+180; */
      /*      end */
      /*      mu = mu - fix(mu/180)*180 - rem(mu,90)*tmp; */
      /*   */
      /*      %limit lon between +/- 180 */
      /*      l = rem(l,360)-fix(rem(l,360)/180)*360; */
      /*   */
      /*      %convert deg to rad */
      /*      %l = l*pi/180; */
      /*      %mu = mu*pi/180; */
      /*  end */
      /* calc he, hedot */
      /* % Create output */
      /* available outputs: */
      /* Rotational Rates in RFb (Acclerations):    p, q, r, (p_dot, q_dot, r_dot) */
      /* Velocities in RFb (Acclerations):          u, v, w, (ax, ay, az) */
      /* Euler Angles (Euler Rotation):             phi, theta, psi, (phi_dot, theta_dot, psi_dot) */
      /* Velocity Vector in RFa (Acceleration):     vtas, alpha, beta, (vtas_dot, alpha_dot, beta_dot) */
      /* Velocity Vector in RFk (Acceleration):     Vground, gamma_true, chi_true, (Vground_dot, gamma_true_dot, chi_true_dot) */
      /* Position in RFe (Velocity) [Acceleration]: x, y, z, (ue, ve, we), [aex, aey, aez] */
      /* Height (Climb speed):                      he, (he_dot) */
      /* Load factor:                               n */
      /*  Output identiek gemaakt aan Citation output rpm=Torque(l) rpm(L) Torque(R) rpm(R) */
      /*  %1..10 */
      /*  %11..22 */
      /* %23..37 */
      rtb_output[0] = eml_p;
      rtb_output[1] = eml_q;
      rtb_output[2] = eml_r;
      rtb_output[3] = eml_vtas;
      rtb_output[4] = eml_alpha;
      rtb_output[5] = eml_beta;
      rtb_output[6] = eml_phi;
      rtb_output[7] = eml_theta;
      rtb_output[8] = eml_psi;
      rtb_output[9] = -eml_z;
      rtb_output[10] = ((BlockIO_pa34model_dueca_8b *)
                        pa34model_dueca_8b_rtM->ModelData.blockIO)->stateo[9];
      rtb_output[11] = ((BlockIO_pa34model_dueca_8b *)
                        pa34model_dueca_8b_rtM->ModelData.blockIO)->stateo[10];
      rtb_output[12] = ((BlockIO_pa34model_dueca_8b *)
                        pa34model_dueca_8b_rtM->ModelData.blockIO)->state_dot[0];
      rtb_output[13] = ((BlockIO_pa34model_dueca_8b *)
                        pa34model_dueca_8b_rtM->ModelData.blockIO)->state_dot[1];
      rtb_output[14] = ((BlockIO_pa34model_dueca_8b *)
                        pa34model_dueca_8b_rtM->ModelData.blockIO)->state_dot[2];
      rtb_output[15] = ((eml_u * eml_ax + eml_v * eml_ay) + eml_w * eml_az) /
        eml_vtas;
      rtb_output[16] = -eml_we;
      rtb_output[17] = (-eml_z) - ((ExternalInputs_pa34model_dueca_ *)
        pa34model_dueca_8b_rtM->ModelData.inputs)->In1[18];
      rtb_output[18] = eml_vtas / (3.313E+002 * sqrt
        (rtb_TmpHiddenBufferAtSFunctio_p[1] / 2.7315E+002));
      for (eml_i0 = 0; eml_i0 < 3; eml_i0++) {
        rtb_output[eml_i0 + 19] = rtb_TmpHiddenBufferAtSFunctio_p[3 + eml_i0];
      }

      rtb_output[22] = ((9.80665 * sin(eml_theta) + eml_ax) + eml_q * sin
                        (eml_alpha) * eml_vtas) - eml_r * sin(eml_beta) *
        eml_vtas;
      rtb_output[23] = ((-9.80665 * cos(eml_theta) * sin(eml_phi) + eml_ay) +
                        eml_r * cos(eml_alpha) * eml_vtas) - eml_p * sin
        (eml_alpha) * eml_vtas;
      rtb_output[24] = eml_anzb;
      rtb_output[25] = eml_anzb * -1.0197162129779283E-001;
      rtb_output[26] = eml_gamma_true;
      rtb_output[27] = eml_ue;
      rtb_output[28] = eml_Vground;
      rtb_output[29] = ((BlockIO_pa34model_dueca_8b *)
                        pa34model_dueca_8b_rtM->ModelData.blockIO)->n_lr[1];
      rtb_output[30] = ((BlockIO_pa34model_dueca_8b *)
                        pa34model_dueca_8b_rtM->ModelData.blockIO)->n_lr[0];
      rtb_output[31] = ((BlockIO_pa34model_dueca_8b *)
                        pa34model_dueca_8b_rtM->ModelData.blockIO)->n_lr[0];
      rtb_output[32] = ((BlockIO_pa34model_dueca_8b *)
                        pa34model_dueca_8b_rtM->ModelData.blockIO)->n_lr[3];
      rtb_output[33] = ((BlockIO_pa34model_dueca_8b *)
                        pa34model_dueca_8b_rtM->ModelData.blockIO)->n_lr[2];
      rtb_output[34] = ((BlockIO_pa34model_dueca_8b *)
                        pa34model_dueca_8b_rtM->ModelData.blockIO)->n_lr[2];
      rtb_output[35] = 0.0;
      rtb_output[36] = 0.0;


      for (eml_i0 = 0; eml_i0 < 10; eml_i0++) {
        rtb_output[eml_i0 + 37] = ((ExternalInputs_pa34model_dueca_ *)
          pa34model_dueca_8b_rtM->ModelData.inputs)->In1[eml_i0];
      }

      /* 38..47 */

    }

    for (i = 0; i < 47; i++) {
      /* Outport: '<Root>/Out1' */
      ((ExternalOutputs_pa34model_dueca *)
        pa34model_dueca_8b_rtM->ModelData.outputs)->Out1[i] = rtb_output[i];
    }

    /* Clock: '<S12>/Clock' */
    rtb_Clock_o = rtmGetT(pa34model_dueca_8b_rtM);

    /* Embedded MATLAB: '<S12>/Stop Function' incorporates:
     *  Constant: '<S1>/trim input2'
     */
    {
      real_T eml_u;
      real_T eml_w;

      /*  This block supports the Embedded MATLAB subset. */
      /*  See the help menu for details.  */
      ((BlockIO_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->ModelData.blockIO
        )->stop = 0U;

      /* state = col( p, q, r, u, v, w, phi, theta, psi, x, y, z) */
      eml_u = rtb_TrimState[3];
      eml_w = rtb_TrimState[5];
      if ((!((boolean_T)rtIsNaN(eml_u))) && (!((boolean_T)rtIsNaN(eml_w)))) {
        if (((boolean_T)rtIsInf(eml_w)) && ((boolean_T)rtIsInf(eml_u))) {
          if (eml_u > 0.0) {
            eml_u = 7.8539816339744828E-001;
          } else {
            eml_u = 2.3561944901923448E+000;
          }

          if (eml_w < 0.0) {
            eml_u = -eml_u;
          }
        } else if (eml_u == 0.0) {
          if (eml_w > 0.0) {
            eml_u = 1.5707963267948966E+000;
          } else if (eml_w < 0.0) {
            eml_u = -1.5707963267948966E+000;
          } else {
            eml_u = 0.0;
          }
        } else {
          eml_u = rt_atan2(eml_w, eml_u);
        }
      } else {
        eml_u = rtNaN;
      }

      if (-rtb_TrimState[11] < -5000.0) {
        ((BlockIO_pa34model_dueca_8b *)
          pa34model_dueca_8b_rtM->ModelData.blockIO)->stop = 1U;
      }

      if (0.0 != 0.0) {
        if (eml_u < -8.7266462599716474E-002) {
          ((BlockIO_pa34model_dueca_8b *)
            pa34model_dueca_8b_rtM->ModelData.blockIO)->stop = 1U;
        }

        if (eml_u > 2.4434609527920614E-001) {
          ((BlockIO_pa34model_dueca_8b *)
            pa34model_dueca_8b_rtM->ModelData.blockIO)->stop = 1U;
        }
      }
    }

    if (rtmIsSampleHit(pa34model_dueca_8b_rtM, 1, 0)) {
      /* Stop: '<S12>/Stop Simulation' */
      if (((BlockIO_pa34model_dueca_8b *)
           pa34model_dueca_8b_rtM->ModelData.blockIO)->stop) {
        rtmSetStopRequested(pa34model_dueca_8b_rtM, 1);
      }
    }
  }

  /* tid is required for a uniform function interface. This system
   * is single rate, and in this case, tid is not accessed. */
  UNUSED_PARAMETER(tid);
}

/* Update for root system: '<Root>' */
static void MdlUpdate(rtModel_pa34model_dueca_8b *pa34model_dueca_8b_rtM, int_T
                      tid)
{
  {
    int32_T i;
    if (rtmIsSampleHit(pa34model_dueca_8b_rtM, 1, 0)) {
      /* RandomNumber Block: '<S37>/White Noise' */
      ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
        ->NextOutput[0] = rt_NormalRand((uint32_T *)&((D_Work_pa34model_dueca_8b
        *) pa34model_dueca_8b_rtM->Work.dwork)->RandSeed[0]) * 1.0 + 0.0;
      ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
        ->NextOutput[1] = rt_NormalRand((uint32_T *)&((D_Work_pa34model_dueca_8b
        *) pa34model_dueca_8b_rtM->Work.dwork)->RandSeed[1]) * 1.0 + 0.0;
      ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
        ->NextOutput[2] = rt_NormalRand((uint32_T *)&((D_Work_pa34model_dueca_8b
        *) pa34model_dueca_8b_rtM->Work.dwork)->RandSeed[2]) * 1.0 + 0.0;
      ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
        ->NextOutput[3] = rt_NormalRand((uint32_T *)&((D_Work_pa34model_dueca_8b
        *) pa34model_dueca_8b_rtM->Work.dwork)->RandSeed[3]) * 1.0 + 0.0;
      for (i = 0; i < 12; i++) {
        /* Update for UnitDelay: '<S34>/Unit Delay' */
        ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
          ->UnitDelay_DSTATE[i] = ((BlockIO_pa34model_dueca_8b *)
          pa34model_dueca_8b_rtM->ModelData.blockIO)->xgw[i];
      }

      /* Update for Memory: '<S33>/Memory' */
      ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
        ->Memory_PreviousInput[0] = ((BlockIO_pa34model_dueca_8b *)
        pa34model_dueca_8b_rtM->ModelData.blockIO)->cur[0];
      ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
        ->Memory_PreviousInput[1] = ((BlockIO_pa34model_dueca_8b *)
        pa34model_dueca_8b_rtM->ModelData.blockIO)->cur[1];
    }

    if (rtmIsSampleHit(pa34model_dueca_8b_rtM, 1, 0)) {
      /* Update for Memory: '<S9>/Memory1' incorporates:
       *  Constant: '<S9>/FixPt Constant'
       */
      ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
        ->Memory1_PreviousInput = 0.0;
      for (i = 0; i < 12; i++) {
        /* Update for Memory: '<S9>/Memory' */
        ((D_Work_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->Work.dwork)
          ->Memory_PreviousInput_j[i] = ((BlockIO_pa34model_dueca_8b *)
          pa34model_dueca_8b_rtM->ModelData.blockIO)->state_dot[i];
      }
    }
  }

  /* tid is required for a uniform function interface. This system
   * is single rate, and in this case, tid is not accessed. */
  UNUSED_PARAMETER(tid);
}

/* Derivatives for root system: '<Root>' */
static void MdlDerivatives(rtModel_pa34model_dueca_8b *pa34model_dueca_8b_rtM)
{
  /* Integrator Block: '<S1>/Trim State' */
  {
    {
      int_T i1;
      const real_T *u0 = ((BlockIO_pa34model_dueca_8b *)
                          pa34model_dueca_8b_rtM->ModelData.blockIO)->state_dot;
      real_T *xdot = &((StateDerivatives_pa34model_duec *)
                       pa34model_dueca_8b_rtM->ModelData.derivs)
        ->TrimState_CSTATE[0];
      for (i1=0; i1 < 12; i1++) {
        xdot[i1] = u0[i1];
      }
    }
  }

  /* Derivatives for Integrator: '<S33>/Integrator' */
  ((StateDerivatives_pa34model_duec *) pa34model_dueca_8b_rtM->ModelData.derivs
    )->Integrator_CSTATE[0] = ((BlockIO_pa34model_dueca_8b *)
    pa34model_dueca_8b_rtM->ModelData.blockIO)->xgustdot[0];
  ((StateDerivatives_pa34model_duec *) pa34model_dueca_8b_rtM->ModelData.derivs
    )->Integrator_CSTATE[1] = ((BlockIO_pa34model_dueca_8b *)
    pa34model_dueca_8b_rtM->ModelData.blockIO)->xgustdot[1];
  ((StateDerivatives_pa34model_duec *) pa34model_dueca_8b_rtM->ModelData.derivs
    )->Integrator_CSTATE[2] = ((BlockIO_pa34model_dueca_8b *)
    pa34model_dueca_8b_rtM->ModelData.blockIO)->xgustdot[2];

  /* Integrator Block: '<S6>/Initial Engine State' */
  {
    ((StateDerivatives_pa34model_duec *)
      pa34model_dueca_8b_rtM->ModelData.derivs)->InitialEngineState_CSTATE[0] =
      ((BlockIO_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->ModelData.blockIO
      )->eng_state_dot[0];
    ((StateDerivatives_pa34model_duec *)
      pa34model_dueca_8b_rtM->ModelData.derivs)->InitialEngineState_CSTATE[1] =
      ((BlockIO_pa34model_dueca_8b *) pa34model_dueca_8b_rtM->ModelData.blockIO
      )->eng_state_dot[1];
  }
}

/* Projection for root system: '<Root>' */
static void MdlProjection(rtModel_pa34model_dueca_8b *pa34model_dueca_8b_rtM)
{
}

/* Terminate for root system: '<Root>' */
static void MdlTerminate(rtModel_pa34model_dueca_8b *pa34model_dueca_8b_rtM)
{
  rt_FREE(pa34model_dueca_8b_rtM->solverInfo);
  rt_FREE(pa34model_dueca_8b_rtM->sfcnInfo);

  /* model code */
  {
    void *ptr = pa34model_dueca_8b_rtM->ModelData.blockIO;
    rt_FREE(ptr);
  }

  {
    real_T *ptr = (real_T *) pa34model_dueca_8b_rtM->ModelData.contStates;
    rt_FREE(ptr);
  }

  {
    real_T *ptr = (real_T *) pa34model_dueca_8b_rtM->ModelData.inputs;
    rt_FREE(ptr);
  }

  {
    real_T *ptr = (real_T *) pa34model_dueca_8b_rtM->ModelData.outputs;
    rt_FREE(ptr);
  }

  rt_FREE(pa34model_dueca_8b_rtM->Work.dwork);
  rt_FREE(pa34model_dueca_8b_rtM->Timing.sampleTimes);
  rt_FREE(pa34model_dueca_8b_rtM->Timing.offsetTimes);
  rt_FREE(pa34model_dueca_8b_rtM->Timing.sampleTimeTaskIDPtr);
  rt_FREE(rtmGetTPtr(pa34model_dueca_8b_rtM));
  rt_FREE(pa34model_dueca_8b_rtM->Timing.sampleHits);

  {
    void *xptr = (void *) rtliGetLogXSignalPtrs
      (pa34model_dueca_8b_rtM->rtwLogInfo);
    void *yptr = (void *) rtliGetLogYSignalPtrs
      (pa34model_dueca_8b_rtM->rtwLogInfo);
    rt_FREE(xptr);
    rt_FREE(yptr);
  }

  rt_FREE(pa34model_dueca_8b_rtM->rtwLogInfo);
  rt_FREE(pa34model_dueca_8b_rtM);
}

/* Function to initialize sizes */
static void MdlInitializeSizes(rtModel_pa34model_dueca_8b
  *pa34model_dueca_8b_rtM)
{
  pa34model_dueca_8b_rtM->Sizes.numContStates = (17);/* Number of continuous states */
  pa34model_dueca_8b_rtM->Sizes.numY = (47);/* Number of model outputs */
  pa34model_dueca_8b_rtM->Sizes.numU = (26);/* Number of model inputs */
  pa34model_dueca_8b_rtM->Sizes.sysDirFeedThru = (1);/* The model is direct feedthrough */
  pa34model_dueca_8b_rtM->Sizes.numSampTimes = (2);/* Number of sample times */
  pa34model_dueca_8b_rtM->Sizes.numBlocks = (116);/* Number of blocks */
  pa34model_dueca_8b_rtM->Sizes.numBlockIO = (22);/* Number of block outputs */
}

/* Function to initialize sample times */
static void MdlInitializeSampleTimes(rtModel_pa34model_dueca_8b
  *pa34model_dueca_8b_rtM)
{
  /* task periods */
  pa34model_dueca_8b_rtM->Timing.sampleTimes[0] = (0.0);
  pa34model_dueca_8b_rtM->Timing.sampleTimes[1] = (0.01);

  /* task offsets */
  pa34model_dueca_8b_rtM->Timing.offsetTimes[0] = (0.0);
  pa34model_dueca_8b_rtM->Timing.offsetTimes[1] = (0.0);
}

/* Function to register the model */
rtModel_pa34model_dueca_8b *pa34model_dueca_8b(void)
{
  rtModel_pa34model_dueca_8b *pa34model_dueca_8b_rtM;
  pa34model_dueca_8b_rtM = (rtModel_pa34model_dueca_8b *) malloc(sizeof
    (rtModel_pa34model_dueca_8b));
  if (pa34model_dueca_8b_rtM == NULL) {
    return NULL;
  }

  (void) memset((char *)pa34model_dueca_8b_rtM,0,
                sizeof(rtModel_pa34model_dueca_8b));

  {
    /* Setup solver object */
    RTWSolverInfo *rt_SolverInfo = (RTWSolverInfo *) malloc(sizeof(RTWSolverInfo));
    rt_VALIDATE_MEMORY(pa34model_dueca_8b_rtM,rt_SolverInfo);
    pa34model_dueca_8b_rtM->solverInfo = (rt_SolverInfo);
    rtsiSetSimTimeStepPtr(pa34model_dueca_8b_rtM->solverInfo,
                          &pa34model_dueca_8b_rtM->Timing.simTimeStep);
    rtsiSetTPtr(pa34model_dueca_8b_rtM->solverInfo, &rtmGetTPtr
                (pa34model_dueca_8b_rtM));
    rtsiSetStepSizePtr(pa34model_dueca_8b_rtM->solverInfo,
                       &pa34model_dueca_8b_rtM->Timing.stepSize);
    rtsiSetdXPtr(pa34model_dueca_8b_rtM->solverInfo,
                 &pa34model_dueca_8b_rtM->ModelData.derivs);
    rtsiSetContStatesPtr(pa34model_dueca_8b_rtM->solverInfo,
                         &pa34model_dueca_8b_rtM->ModelData.contStates);
    rtsiSetNumContStatesPtr(pa34model_dueca_8b_rtM->solverInfo,
      &pa34model_dueca_8b_rtM->Sizes.numContStates);
    rtsiSetErrorStatusPtr(pa34model_dueca_8b_rtM->solverInfo,
                          (&rtmGetErrorStatus(pa34model_dueca_8b_rtM)));
    rtsiSetModelMethodsPtr(pa34model_dueca_8b_rtM->solverInfo,
      &pa34model_dueca_8b_rtM->modelMethodsInfo);
    rtsiSetRTModelPtr(pa34model_dueca_8b_rtM->solverInfo, pa34model_dueca_8b_rtM);
  }

  /* timing info */
  {
    time_T *mdlPeriod;
    time_T *mdlOffset;
    time_T *mdlTaskTimes;
    int_T *mdlTsMap;
    int_T *mdlSampleHits;
    mdlPeriod = (time_T *) malloc(2 * sizeof(time_T));
    rt_VALIDATE_MEMORY(pa34model_dueca_8b_rtM,mdlPeriod);
    mdlOffset = (time_T *) malloc(2 * sizeof(time_T));
    rt_VALIDATE_MEMORY(pa34model_dueca_8b_rtM,mdlOffset);
    mdlTaskTimes = (time_T *) malloc(2 * sizeof(time_T));
    rt_VALIDATE_MEMORY(pa34model_dueca_8b_rtM,mdlTaskTimes);
    mdlTsMap = (int_T *) malloc(2 * sizeof(int_T));
    rt_VALIDATE_MEMORY(pa34model_dueca_8b_rtM,mdlTsMap);
    mdlSampleHits = (int_T *) malloc(2 * sizeof(int_T));
    rt_VALIDATE_MEMORY(pa34model_dueca_8b_rtM,mdlSampleHits);

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

    pa34model_dueca_8b_rtM->Timing.sampleTimes = (&mdlPeriod[0]);
    pa34model_dueca_8b_rtM->Timing.offsetTimes = (&mdlOffset[0]);
    pa34model_dueca_8b_rtM->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    rtmSetTPtr(pa34model_dueca_8b_rtM, &mdlTaskTimes[0]);
    pa34model_dueca_8b_rtM->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtsiSetSolverMode(pa34model_dueca_8b_rtM->solverInfo,
                    SOLVER_MODE_SINGLETASKING);

  /*
   * initialize model vectors and cache them in SimStruct
   */

  /* block I/O */
  {
    void *b = malloc(sizeof(BlockIO_pa34model_dueca_8b));
    rt_VALIDATE_MEMORY(pa34model_dueca_8b_rtM,b);
    pa34model_dueca_8b_rtM->ModelData.blockIO = (b);
    (void) memset(b,0,
                  sizeof(BlockIO_pa34model_dueca_8b));

    {
      int_T i;
      void *pVoidBlockIORegion;
      pVoidBlockIORegion = (void *)(&((BlockIO_pa34model_dueca_8b *)
        pa34model_dueca_8b_rtM->ModelData.blockIO)->WhiteNoise[0]);
      for (i = 0; i < 30; i++) {
        ((real_T*)pVoidBlockIORegion)[i] = 0.0;
      }

      pVoidBlockIORegion = (void *)(&((BlockIO_pa34model_dueca_8b *)
        pa34model_dueca_8b_rtM->ModelData.blockIO)->x0dot[0]);
      for (i = 0; i < 135; i++) {
        ((real_T*)pVoidBlockIORegion)[i] = 0.0;
      }
    }
  }

  /* external inputs */
  {
    pa34model_dueca_8b_rtM->ModelData.inputs = (ExternalInputs_pa34model_dueca_ *)
      malloc(sizeof(ExternalInputs_pa34model_dueca_));
    rt_VALIDATE_MEMORY(pa34model_dueca_8b_rtM,((ExternalInputs_pa34model_dueca_ *)
      pa34model_dueca_8b_rtM->ModelData.inputs));

    {
      int_T i;
      for (i = 0; i < 26; i++) {
        ((ExternalInputs_pa34model_dueca_ *)
          pa34model_dueca_8b_rtM->ModelData.inputs)->In1[i] = 0.0;
      }
    }
  }

  /* external outputs */
  {
    pa34model_dueca_8b_rtM->ModelData.outputs = (ExternalOutputs_pa34model_dueca
      *) malloc(sizeof(ExternalOutputs_pa34model_dueca));
    rt_VALIDATE_MEMORY(pa34model_dueca_8b_rtM,((ExternalOutputs_pa34model_dueca *)
      pa34model_dueca_8b_rtM->ModelData.outputs));

    {
      int_T i;
      for (i = 0; i < 47; i++) {
        ((ExternalOutputs_pa34model_dueca *)
          pa34model_dueca_8b_rtM->ModelData.outputs)->Out1[i] = 0.0;
      }
    }
  }

  /* constant block I/O */
  pa34model_dueca_8b_rtM->ModelData.constBlockIO =
    (&pa34model_duec_InvariantSignals);

  /* states (continuous)*/
  {
    real_T *x = (real_T *) malloc(sizeof(ContinuousStates_pa34model_duec));
    rt_VALIDATE_MEMORY(pa34model_dueca_8b_rtM,x);
    pa34model_dueca_8b_rtM->ModelData.contStates = (x);
    (void) memset((void *)x,0,
                  sizeof(ContinuousStates_pa34model_duec));
  }

  /* states (dwork) */
  {
    void *dwork = (void *) malloc(sizeof(D_Work_pa34model_dueca_8b));
    rt_VALIDATE_MEMORY(pa34model_dueca_8b_rtM,dwork);
    pa34model_dueca_8b_rtM->Work.dwork = (dwork);
    (void) memset((void *) dwork,0,
                  sizeof(D_Work_pa34model_dueca_8b));

    {
      int_T i;
      real_T *dwork_ptr = (real_T *) &((D_Work_pa34model_dueca_8b *)
        pa34model_dueca_8b_rtM->Work.dwork)->UnitDelay_DSTATE[0];
      for (i = 0; i < 3468; i++) {
        dwork_ptr[i] = 0.0;
      }
    }
  }

  /* Model specific registration */
  pa34model_dueca_8b_rtM->modelName = ("pa34model_dueca_8b");
  pa34model_dueca_8b_rtM->path = ("pa34model_dueca_8b");
  rtmSetTStart(pa34model_dueca_8b_rtM, 0.0);
  rtmSetTFinal(pa34model_dueca_8b_rtM, -1);
  pa34model_dueca_8b_rtM->Timing.stepSize = (0.01);
  rtsiSetFixedStepSize(pa34model_dueca_8b_rtM->solverInfo, 0.01);

  /* Setup for data logging */
  {
    RTWLogInfo *rt_DataLoggingInfo = (RTWLogInfo *) malloc(sizeof(RTWLogInfo));
    rt_VALIDATE_MEMORY(pa34model_dueca_8b_rtM,rt_DataLoggingInfo);
    pa34model_dueca_8b_rtM->rtwLogInfo = (rt_DataLoggingInfo);
    rtliSetLogFormat(pa34model_dueca_8b_rtM->rtwLogInfo, 0);
    rtliSetLogMaxRows(pa34model_dueca_8b_rtM->rtwLogInfo, 0);
    rtliSetLogDecimation(pa34model_dueca_8b_rtM->rtwLogInfo, 1);
    rtliSetLogVarNameModifier(pa34model_dueca_8b_rtM->rtwLogInfo, "rt_");
    rtliSetLogT(pa34model_dueca_8b_rtM->rtwLogInfo, "");
    rtliSetLogX(pa34model_dueca_8b_rtM->rtwLogInfo, "");
    rtliSetLogXFinal(pa34model_dueca_8b_rtM->rtwLogInfo, "");
    rtliSetSigLog(pa34model_dueca_8b_rtM->rtwLogInfo, "");
    rtliSetLogXSignalInfo(pa34model_dueca_8b_rtM->rtwLogInfo, NULL);
    rtliSetLogXSignalPtrs(pa34model_dueca_8b_rtM->rtwLogInfo, NULL);
    rtliSetLogY(pa34model_dueca_8b_rtM->rtwLogInfo, "");
    rtliSetLogYSignalInfo(pa34model_dueca_8b_rtM->rtwLogInfo, NULL);
    rtliSetLogYSignalPtrs(pa34model_dueca_8b_rtM->rtwLogInfo, NULL);
  }

  pa34model_dueca_8b_rtM->Sizes.checksums[0] = (3629054460U);
  pa34model_dueca_8b_rtM->Sizes.checksums[1] = (3658117199U);
  pa34model_dueca_8b_rtM->Sizes.checksums[2] = (146131315U);
  pa34model_dueca_8b_rtM->Sizes.checksums[3] = (1903015893U);
  rtmiSetInitSizesFcn((pa34model_dueca_8b_rtM->modelMethodsInfo),
                      MdlInitializeSizes);
  rtmiSetInitSampTimesFcn((pa34model_dueca_8b_rtM->modelMethodsInfo),
    MdlInitializeSampleTimes);
  rtmiSetStartFcn((pa34model_dueca_8b_rtM->modelMethodsInfo), MdlStart);
  rtmiSetOutputsFcn((pa34model_dueca_8b_rtM->modelMethodsInfo), MdlOutputs);
  rtmiSetUpdateFcn((pa34model_dueca_8b_rtM->modelMethodsInfo), MdlUpdate);
  rtmiSetDervisFcn((pa34model_dueca_8b_rtM->modelMethodsInfo), MdlDerivatives);
  rtmiSetProjectionFcn((pa34model_dueca_8b_rtM->modelMethodsInfo), MdlProjection);
  rtmiSetMassMatrixFcn((pa34model_dueca_8b_rtM->modelMethodsInfo), NULL);
  rtmiSetForcingFunctionFcn((pa34model_dueca_8b_rtM->modelMethodsInfo), NULL);
  rtmiSetTerminateFcn((pa34model_dueca_8b_rtM->modelMethodsInfo), MdlTerminate);
  rtmiSetRTModelPtr((pa34model_dueca_8b_rtM->modelMethodsInfo),
                    pa34model_dueca_8b_rtM);
  return pa34model_dueca_8b_rtM;
}
