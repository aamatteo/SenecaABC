#!/bin/bash

# I had to change the location of fgfs
#  from /usr/bin/fgfs
#  to /usr/games/fgfs

[[ ! -f /usr/games/fgfs ]] && echo "FlightGear not found";

## STOP if already running
killall fgfs

## START
#/usr/bin/fgfs \
#/usr/games/fgfs \
#--start-date-lat=2016:08:23:14:00:00 \
fgfs \
--generic=socket,in,100,127.0.0.1,5500,udp,duecavisbinary \
--httpd=8080 \
--telnet=5401 \
--fdm=external \
--aircraft=ufo \
--disable-real-weather-fetch \
--enable-clouds3d \
--airport=EHAM \
--start-date-lat=2012:08:23:14:00:00 \
--prop:bool:/sim/menubar/visibility=false \
--enable-splash-screen \
--enable-terrasync \
--disable-random-objects \
--disable-random-buildings \
--enable-random-vegetation \
--disable-ai-traffic \
--disable-clock-freeze \
--disable-sound \
--disable-rembrandt \
--enable-enhanced-lighting \
--enable-distance-attenuation \
--fog-nicest \
--enable-specular-highlight \
--prop:/local-weather/autostart=1 \
--metar="EHAM 231200Z AUTO 00000KT 9999 SKC Q1013 NOSIG" \
--prop:string:/environment/weather-scenario="Manual input" \
--prop:/sim/terrasync/svn-server=http://scenery.lr.tudelft.nl/pub/terrascenery/trunk/data/Scenery \
&

## also start DUECA if asked for
if [ "$1" == "1" ]; #[ -n $* ];
then
	echo also starting DUECA
	../../../dueca_run.x
	
	# stop fg after closing dueca
	killall fgfs
else
	echo no starting DUECA
fi

