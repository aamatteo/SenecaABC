# Scenario - training 5 - right engine failure occuring right after rotation (after rotation speed of 80knots - speed to be checked)
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
eventtime		0	from the start
enable_turb		0
turb_int		0
wind_vel		2	m/s
wind_dir		160	deg
enable_windshear	0
# visibility and clouds
fg_visibility		100000	in meters
fg_cloud0_alt		10000	ft # 0=SCT 1=BKN 2=OVC

engineEvent
eventspeed          90
power_right			0
max_rpm_left		2800
max_rpm_right		2800
engine_time_right	0

