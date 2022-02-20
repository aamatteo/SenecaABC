# Scenario
id		0070
inco		EHRD_lg.inco

APstate 	0
verticalFDstate 0
lateralFDstate 	0
CDI		0
fp_name 	""
lat_zero    0.9068255191119
lon_zero    0.077508675817
alt_zero	-15
psi_zero	0.0

controlEvent
eventgeardown  0.3 # when the gear is almost deployed a rudder offset is introduced to simulate an asymmetric main gear deployment.
rudder_bias   -3.0 #rudder_offset  5.0

#windEvent
#eventgeardown   0.6	from the start
#enable_turb		0
#turb_int		0
#wind_vel		0	m/s
#wind_dir		0	deg
#enable_windshear	0
# visibility and clouds
#fg_visibility		100000	in meters
#fg_cloud0_alt		10000	ft # 0=SCT 1=BKN 2=OVC

#engineEvent
#eventgeardown 0.8                  #eventtime 10
#power_left 0.5