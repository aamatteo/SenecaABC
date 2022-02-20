# Scenario
id		404
inco		Clean_125kts_3000ft_zeeland.inco
APstate 	1
verticalFDstate 1
lateralFDstate 	1
CDI		1
fp_name 	fp_navigation_vor_fail.nav
lat_zero	0.8990575503090124
lon_zero	0.06505984928938273
alt_zero	-3.35	
psi_zero	0.0	

windEvent
eventtime		0	from the start
enable_turb		1
turb_int		0.1
wind_vel		0	m/s
wind_dir		0	deg
enable_windshear	0
# visibility and clouds
fg_visibility		100000	in meters
fg_cloud0_alt		10000	ft # 0=SCT 1=BKN 2=OVC

failureEvent
eventtime		80
VOR_failure		1

