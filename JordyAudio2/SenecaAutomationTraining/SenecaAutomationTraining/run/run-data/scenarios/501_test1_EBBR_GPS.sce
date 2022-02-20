# Scenario
id		501
inco		Clean_125kts_ebbr.inco
APstate 	1
verticalFDstate 1
lateralFDstate 	1
CDI		0
fp_name 	fp_ebbr.nav
lat_zero	0.8883539330470371
lon_zero	0.07894646163111112
alt_zero	50.0
psi_zero	0.0	

windEvent
eventtime		0	from the start
enable_turb		1
turb_int		0.3
wind_vel		4	m/s
wind_dir		260	deg
enable_windshear	0
# visibility and clouds
fg_visibility		20000	in meters
fg_cloud0_alt		10000	ft # 0=SCT 1=BKN 2=OVC

failureEvent
eventtime		30
GPS_failure		1

