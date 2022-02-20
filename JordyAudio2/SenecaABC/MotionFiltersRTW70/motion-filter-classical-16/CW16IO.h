#ifndef CW16IO_h

#define CW16IO_h

enum output_vec {
		Y_ax,
		Y_ay,
		Y_az,
		Y_pdot,
		Y_qdot,
		Y_rdot,
		Y_y1,
		Y_y2,
		Y_y3,
		Y_y4,
		Y_y5,
		Y_y6,
		Y_no_outputs
};

enum input_vec {
		U_fx,
		U_fy,
		U_fz,
		U_p,
		U_q,
		U_r,
		U_pd,
		U_qd,
		U_rd,
		U_xS,
		U_yS,
		U_zS,
		U_xSd,
		U_ySd,
		U_zSd,
		U_phiS,
		U_thetaS,
		U_psiS,
		U_pS,
		U_qS,
		U_rS,
		U_no_inputs
};

enum param_vec {
		P_no_params
};

#endif
