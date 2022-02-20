/*
 * pa34model_dueca_8b_data.c
 *
 * Real-Time Workshop code generation for Simulink model "pa34model_dueca_8b.mdl".
 *
 * Model Version              : 1.20293
 * Real-Time Workshop version : 7.0  (R2007b)  02-Aug-2007
 * C source code generated on : Tue Jul 14 10:39:43 2015
 */

#include "pa34model_dueca_8b.h"
#include "pa34model_dueca_8b_private.h"

/* Constant parameters (auto storage) */
const ConstParam_pa34model_dueca_8b pa34model_dueca_8b_ConstP = {
  /* Expression: h_vec
   * '<S39>/PreLook-Up Index Search  (altitude)'
   */
  { 500.0, 1750.0, 3750.0, 7500.0, 15000.0, 25000.0, 35000.0, 45000.0, 55000.0,
    65000.0, 75000.0, 80000.0 },

  /* Expression: sigma_vec'
   * '<S39>/Medium//High Altitude Intensity'
   */
  { 3.2, 2.2, 1.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 4.2, 3.6, 3.3,
    1.6, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 6.6, 6.9, 7.4, 6.7, 4.6, 2.7,
    0.4, 0.0, 0.0, 0.0, 0.0, 0.0, 8.6, 9.6, 10.6, 10.1, 8.0, 6.6, 5.0, 4.2, 2.7,
    0.0, 0.0, 0.0, 11.8, 13.0, 16.0, 15.1, 11.6, 9.7, 8.1, 8.2, 7.9, 4.9, 3.2,
    2.1, 15.6, 17.6, 23.0, 23.6, 22.1, 20.0, 16.0, 15.1, 12.1, 7.9, 6.2, 5.1,
    18.7, 21.5, 28.4, 30.2, 30.7, 31.0, 25.2, 23.1, 17.5, 10.7, 8.4, 7.2 },

  /* Expression: seed
   * '<S37>/White Noise'
   */
  { 23341.0, 23342.0, 23343.0, 23344.0 },

  /* Expression: zeros(2,6)
   * '<S34>/Unit Delay'
   */
  { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },

  /* Expression: [120 120 80]
   * '<S33>/Gust build up lenght [m]'
   */
  { 120.0, 120.0, 80.0 },

  /* Expression: [3.5 3.0 3.0]
   * '<S33>/Gust amplitude [m//s]'
   */
  { 3.5, 3.0, 3.0 },

  /* Expression: terrainmap.xVec
   * '<S6>/TerrainMap'
   */
  { 0.0, 10.0 },

  /* Expression: terrainmap.hMat
   * '<S6>/TerrainMap'
   */
  { 0.0, 0.0, 0.0, 0.0 },

  /* Computed Parameter: maxIndex
   * '<S39>/Medium//High Altitude Intensity'
   */
  { 11U, 6U }
};
