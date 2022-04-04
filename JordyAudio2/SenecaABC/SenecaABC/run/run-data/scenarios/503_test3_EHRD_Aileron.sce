  # Scenario
id		503
inco		EHRD_06.inco
APstate 	0
verticalFDstate 0
lateralFDstate 	0
CDI		0
fp_name 	fp_ehrd.nav
lat_zero	0.9067518327156792
lon_zero	0.07732994771049384
alt_zero	-4.6
psi_zero	0.0	

windEvent
eventtime		0	from the start
enable_turb		0
turb_int		0
wind_vel		0	m/s
wind_dir		0	deg
enable_windshear	0
# visibility and clouds
fg_visibility		20000	in meters
fg_cloud0_alt		10000	ft # 0=SCT 1=BKN 2=OVC

windEvent
eventspeed		90	
enable_turb		1
turb_int		0.4
wind_vel		5	m/s
wind_dir		70	deg
enable_windshear	0
# visibility and clouds
fg_visibility		20000	in meters
fg_cloud0_alt		10000	ft # 0=SCT 1=BKN 2=OVC

failureEvent
eventtime		170
AFCS_rol		1

