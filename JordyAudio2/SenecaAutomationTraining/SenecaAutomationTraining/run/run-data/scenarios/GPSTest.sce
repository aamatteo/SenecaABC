# Scenario
id		0070
inco		EHRD_gps.inco

APstate 	0
verticalFDstate 0
lateralFDstate 	0
CDI		0
fp_name 	GPS1.nav
lat_zero    0.9068255191119
lon_zero    0.077508675817
alt_zero	1500
psi_zero	0.0

windEvent
eventtime		0	from the start
enable_turb		1
turb_int		0.3
wind_vel		4	m/s
wind_dir		260	deg
enable_windshear	0
# visibility and clouds
fg_visibility		8000	in meters
fg_cloud2_alt		2500	ft # 0=SCT 1=BKN 2=OVC

failureEvent
eventtime		30000
GPS_failure		1



