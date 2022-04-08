# Scenario
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
wind_vel		5.1	m/s
wind_dir		90	deg
enable_windshear	0
# visibility and clouds
fg_visibility		100000	in meters
fg_cloud0_alt		10000	ft # 0=SCT 1=BKN 2=OVC


# Training 1: Engine failure on takeoff
# Extra’s 2: Engine failure links bij gear up.
# - alleen commando gear up of ook echt het gear ophalen? momenteel het laatste
#
# if gear comes up, beyond 0.95
# power of left engine decreases to 0
# in 1 second

#dummyEvent
#eventtime			2		make sure the next event does not immediately trigger (possible bug in model)

#engineEvent
#eventgear			0.95	gear coming up
#power_left			0		no power available
#engine_time_left	1		time in seconds
#
# other times are default, just listed here for easy editing
#
power_right			1
max_rpm_left		2800
max_rpm_right		2800
engine_time_right	0

