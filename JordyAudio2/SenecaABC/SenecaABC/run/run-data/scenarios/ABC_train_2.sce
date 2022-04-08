# Scenario - training 2: rudder stuck in neutral position during approach
id		301
inco	EHAM_18C_app2m_99kts.inco


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
wind_vel		10	m/s
wind_dir		90	deg
enable_windshear	0
# visibility and clouds
fg_visibility		100000	in meters
fg_cloud0_alt		10000	ft # 0=SCT 1=BKN 2=OVC


controlEvent
eventtime		50
aileron_power		1
rudder_power		0
rudder_bias		0
ARI
