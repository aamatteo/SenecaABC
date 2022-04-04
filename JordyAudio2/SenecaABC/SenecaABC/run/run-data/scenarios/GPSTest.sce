# Scenario
id		0070
inco		EHRD_gps.inco

APstate 	0
verticalFDstate 0
lateralFDstate 	0
CDI		0
fp_name 	GPS1.nav
lat_zero 0.906905513 
lon_zero 0.07771413
alt_zero	-15
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
eventtime		30
GPS_failure		1



