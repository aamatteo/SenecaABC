#ifndef ARRAY_NAMES_HXX
#define ARRAY_NAMES_HXX

enum model_input_vec {
  Um_de,
  Um_da,
  Um_dr,
  Um_dte,
  Um_dta,
  Um_dtr,
  Um_df,
  Um_gear,
  Um_pla1,
  Um_pla2,
  Um_brake_l,
  Um_brake_r,
  Um_nws,
  Um_yd,
  Um_gust_u,
  Um_gust_alpha,
  Um_gust_beta,
  Um_gust_udot,
  Um_gust_alphadot,
  Um_gust_betadot,
  Um_gust_ug_asymm,
  Um_gust_ag_asymm,
  Um_terr_elev,
  Um_no_inputs
};

enum model_state_vec {

  // The first 12 are the core aircraft state,
  // the rest is from various systems
  Xm_p,
  Xm_q,
  Xm_r,
  Xm_vtas,
  Xm_alpha,
  Xm_beta,
  Xm_phi,
  Xm_theta,
  Xm_psi,
  Xm_h,
  Xm_x,
  Xm_y,
  Xm_de,
  Xm_da,
  Xm_dr,
  Xm_yawdamper,
  Xm_flaps,
  Xm_gear,
  Xm_n1left,
  Xm_n1right,
  Xm_winddir,
  Xm_windamplitude,
  Xm_n2left,
  Xm_n2right,
  Xm_usedfuel1,
  Xm_usedfuel2,
  Xm_no_states
};

enum output_vec {
  Ym_p,
  Ym_q,
  Ym_r,
  Ym_vtas,
  Ym_alpha,
  Ym_beta,
  Ym_phi,
  Ym_theta,
  Ym_psi,
  Ym_h,
  Ym_x,
  Ym_y,
  Ym_pdot,
  Ym_qdot,
  Ym_rdot,
  Ym_vtasdot,
  Ym_hdot,
  Ym_ralt,
  Ym_m,
  Ym_vcas,
  Ym_uwinde,
  Ym_vwinde,
  Ym_fxcg,
  Ym_fycg,
  Ym_fzcg,
  Ym_n,
  Ym_gamma,
  Ym_ghi,
  Ym_vground,
  Ym_ffleft,
  Ym_n1left,
  Ym_n2left,
  Ym_ffright,
  Ym_n1right,
  Ym_n2right,
  Ym_mass,
  Ym_flaps,
  Ym_gear,
  Ym_de,
  Ym_da,
  Ym_dr,
  Ym_no_outputs
};

// DLR controller
// Input 1: Stick
enum ctrl_input1_vec {
  U1c_stick_x,
  U1c_stick_y,

  U1c_no_inputs
};
// Input 2: AircraftData
enum ctrl_input2_vec {
  U2c_p,
  U2c_q,
  U2c_r,
  U2c_phi,
  U2c_theta,
  U2c_psi,
  U2c_alt_press,
  U2c_vspd,
  U2c_alt_radio,
  U2c_mach,
  U2c_dyn_press,
  U2c_vtas,
  U2c_vcas,
  U2c_veas,
  U2c_alpha_vane,
  U2c_alpha_boom,
  U2c_beta_boom,
  U2c_N1_left,
  U2c_N1_right,
  U2c_FU_left,
  U2c_FU_right,
  U2c_anxb,
  U2c_anyb,
  U2c_anzb,
  U2c_gamma,
  U2c_ghi,
  U2c_gnd_spd,
  U2c_delta_a,
  U2c_delta_e,
  U2c_delta_r,
  U2c_flaps,
  U2c_gear,
  U2c_no_inputs
};
// Enable
enum ctrl_input3_vec {
  U3c_enable,
  U3c_no_inputs
};
// Reset
enum ctrl_input4_vec {
  U4c_reset,
  U4c_no_inputs
};
// Switches
enum ctrl_input5_vec {
  U5c_airborne,
  U5c_indi,
  U5c_pch,
  U5c_cstar,
  U5c_act_mdl_indi,
  U5c_act_mdl_pch,
  U5c_beta_est,
  U5c_alpha_vane,
  U5c_turn_comp,
  U5c_roll_beta,
  
  U5c_no_inputs
};

// TODO: fill in if needed
enum ctrl_state_vec {
  Xc_no_states = 9
};

enum ctrl_output1_vec {
  Y1c_da,
  Y1c_de,
  Y1c_dr,
  Y1c_phi_cmd,

  Y1c_no_outputs
};

enum ctrl_output2_vec {
  Y2c_log1,
  Y2c_log2,
  Y2c_log3,
  Y2c_log4,
  Y2c_log5,
  Y2c_log6,
  Y2c_log7,
  Y2c_log8,
  Y2c_log9,
  Y2c_log10,
  Y2c_log11,
  Y2c_log12,
  Y2c_log13,
  Y2c_log14,
  Y2c_log15,
  Y2c_log16,
  Y2c_log17,

  Y2c_no_outputs
};

#endif
