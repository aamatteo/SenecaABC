# Scenario - test1 - flap asymmetry
id		301
inco	EHAM_18C_3000ft.inco


APstate 	0
verticalFDstate 0
lateralFDstate 	0
CDI		0
fp_name 	""
lat_zero 0.906905513
lon_zero 0.07771413
alt_zero	-15
psi_zero	0.0

windEvent
eventtime			0
enable_turb			0		0=false 1=true
turb_int			0
wind_vel			6		m/s
wind_dir			270		degrees; 0=north
enable_windshear		0		0=false 1=true
# visibility and clouds
fg_visibility			5000	in meters
fg_cloud0_alt			10000	ft # 0=SCT 1=BKN 2=OVC


controlEvent
eventflapdown		10		trigger event when flaps > 10 deg
flap_asym		10		flap asymmetry - single flap deflection max 10 deg


