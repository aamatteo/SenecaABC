#!/bin/bash

#/usr/bin/fgfs --generic=socket,in,100,127.0.0.1,5500,udp,duecavisbinary 
# --fdm=external --generic=socket,in,100,127.0.0.1,5501,udp,duecaweatherbinary 
# --httpd=8080 --aircraft=ufo --disable-real-weather-fetch --airport=EHAM --start-date-lat=2012:08:23:14:00:00 --prop:bool:/sim/menubar/visibility=false 
# --disable-splash-screen --enable-clouds3d --prop:/sim/rendering/clouds3d-vis-range=30000 --prop:/sim/rendering/clouds3d-density=0.50 &

# ../../../dueca_run.x

# killall fgfs

/Applications/FlightGear.app/Contents/MacOS/fgfs \
--fdm=external \
--generic=socket,in,100,127.0.0.1,5500,udp,duecavisbinary \
--httpd=8080 \
--telnet=5401 \
--aircraft=ufo \
--disable-real-weather-fetch \
--enable-clouds3d \
--airport=EHAM \
--start-date-lat=2015:06:01:12:00:00 \
--prop:bool:/sim/menubar/visibility=false \
--enable-splash-screen \
--enable-terrasync \
--disable-random-objects \
--disable-random-buildings \
--disable-random-vegetation \
--disable-ai-traffic \
—-enable-clock-freeze \
--disable-sound \
--disable-rembrandt \
--enable-enhanced-lighting \
--disable-distance-attenuation \
--fog-nicest \
--enable-specular-highlight \
--prop:/local-weather/autostart=0 \
--prop:string:/environment/weather-scenario="Manual input" \
--prop:/sim/terrasync/svn-server=http://scenery.lr.tudelft.nl/terrascenery/trunk/data/Scenery &
#—metar="EHAM 231200Z AUTO 00000KT 0000 SKC Q1013 NOSIG" \



#../../../dueca_run.x

#if [ "$1" == "1" ];
#then
#echo also starting DUECA
#../../../dueca_run.x

#killall fgfs
#else
#echo no starting DUECA
#fi
