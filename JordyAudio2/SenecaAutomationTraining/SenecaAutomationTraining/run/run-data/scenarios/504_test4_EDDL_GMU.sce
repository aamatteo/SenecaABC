# Scenario
id		504
inco		Clean_125kts_eddl.inco
APstate 	1
verticalFDstate 1
lateralFDstate 	1
CDI		1
fp_name 	fp_eddl.nav
lat_zero	0.8950973990601235
lon_zero	0.11784673975753089
alt_zero	34.0
psi_zero	0.0	

windEvent
eventtime		0	from the start
enable_turb		1
turb_int		0.3
wind_vel		5	m/s
wind_dir		40	deg
enable_windshear	0
# visibility and clouds
fg_visibility		20000	in meters
fg_cloud0_alt		10000	ft # 0=SCT 1=BKN 2=OVC

failureEvent
eventtime		60
GMU_failure		1

