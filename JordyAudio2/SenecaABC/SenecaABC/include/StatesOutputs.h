// For PA34

#ifndef StatesOutputs_hh

#define StatesOutputs_hh

/*
The first 12 are the core aircraft state, 
the rest is from various systems

states pa 24 Alleen eerste twaalf gebruikt in model en zijn beschikbaar als input; 
De overigen worden wel gebruikt bij de inco_module en doorgegeven aan de CPI module in PA34 module

I do not see the other being used in the code
Also note that these 17 variables are not the same as the first 17 in the inco file
The last 7 vars of the inco file are send as event over the Trim_inco channel


-*-*-*- The search for the last 5 states: -*-*-*-

From pa34model_dueca_8b.h:
TrimState_CSTATE[12] ??
Integrator_CSTATE[3] ??          starts at 0
InitialEngineState_CSTATE[2] ??  starts at 150

Integrator Block: '<S6>/Initial Engine State'
    if (rtmIsFirstInitCond(pa34model_dueca_8b_rtM)) {
      ((ContinuousStates_pa34model_duec *)
        pa34model_dueca_8b_rtM->ModelData.contStates)->
        InitialEngineState_CSTATE[0] = 150.0;
      ((ContinuousStates_pa34model_duec *)
        pa34model_dueca_8b_rtM->ModelData.contStates)->
        InitialEngineState_CSTATE[1] = 150.0;
    }

*/
enum state_vec {
  X_P,
  X_Q,
  X_R,
  X_u,
  X_v,
  X_w,
  X_PHI,
  X_THETA,
  X_PSI,
  X_X,
  X_Y,
  X_Z,
  // the above 12 variable I found in the Simulink file
  // I'm still looking for the following 5 states in the model
  // when making a snapshot, there is (some kind of) data
  X_DE,
  X_DA,
  X_DR,
  X_TH_LEFT,
  X_TH_RIGHT,
  X_no_states
};

enum output_vec {
  Y_p,
  Y_q,
  Y_r,
  Y_vtas,
  Y_alpha,
  Y_beta,
  Y_phi,
  Y_theta,
  Y_psi,
  Y_h,
  Y_x,
  Y_y,
  Y_pdot,
  Y_qdot,
  Y_rdot,
  Y_vtasdot,
  Y_hdot,
  Y_ralt,
  Y_m,
  Y_uwinde,
  Y_vwinde,
  Y_wwinde,
  Y_fxcg,
  Y_fycg,
  Y_fzcg,
  Y_n,
  Y_gamma,
  Y_chi,
  Y_vground,
// engines
  Y_torqueleft,      // torque (was ff)
  Y_rpmleft,         // rpm (was n1)
  Y_rpmleft_IGNORE,  // copy of above (was n2)
  Y_torqueright,     // torque
  Y_rpmright,        // rpm
  Y_rpmright_IGNORE, // copy of above
// always zero, no flaps and gear state output
  Y_flaps_IGNORE,    // DO NOT USE or find another purpose for these
  Y_gear,
// Inputs
  Y_de0,
  Y_da0,
  Y_dr0,
  Y_dte0,
  Y_dta0,
  Y_dtr0,
  Y_df0,
  Y_gear0,
  Y_pla10,
  Y_pla20,
  Y_no_outputs,
  


};

enum input_vec {
  U_de,
  U_da,
  U_dr,
  U_dte,             // not used
  U_dta,             // not used
  U_dtr,             // not used
  U_df,              // flaps
  U_gear,            // gear
  U_pla1,            // throttle position left [0-1] -> also used for breaking in Simulink model
  U_pla2,            // throttle position right [0-1]
  //
  U_gust_u,          // used for wind_vel
  U_gust_alpha,      // used for wind_dir
  U_gust_beta,       // used for K_turb
  U_gust_udot,       //_IGNORE
  U_gust_alphadot,   //_IGNORE
  U_gust_betadot,    // used for K_shear
  //
  U_max_rpm_left,
  U_max_rpm_right,
  //
  U_terr_elev,
  //
  U_asym_x,
  U_asym_y,
  U_asym_z,
  U_asym_mass,
  //
  U_aileron_power,
  U_rudder_power,
  U_rudder_bias,
  //
  U_no_inputs
};

#endif
