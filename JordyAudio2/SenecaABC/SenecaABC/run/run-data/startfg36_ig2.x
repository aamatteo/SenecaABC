#!/bin/bash

# NVIDIA
export __GL_FSAA_MODE=5
export __GL_LOG_MAX_ANISO=3

LD_LIBRARY_PATH="/data/srs/flightgear/testversion/csflightgear-3.6rc/install/usr/lib64;/data/srs/flightgear/testversion/csflightgear-3.6rc/install/usr/local/lib64/"  \
/data/srs/flightgear/testversion/csflightgear-3.6rc/install/bin/fgfs \
--fg-root=/data/srs/flightgear/testversion/csflightgear-3.6rc/fgdata  \
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
--config=/data/srs/flightgear/testversion/csflightgear-3.6rc/fgdata/ig2_camera_new.xml \
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
--prop:double:/local-weather/config/max-vis-range-m=100000 \
--metar="EHAM 231200Z AUTO 00000KT 9999 SKC Q1013 NOSIG" \
--prop:string:/environment/weather-scenario="Manual input" \
--visibility=40000 \
--prop:/sim/terrasync/svn-server=http://scenery.lr.tudelft.nl/pub/terrascenery/trunk/data/Scenery &

if [ "$1" == "1" ];
then
echo also starting DUECA
../../../dueca_run.x

killall fgfs
else
echo no starting DUECA
fi

#--prop:/sim/terrasync/svn-server=http://foxtrot.mgras.net:8080/terrascenery/trunk/data/Scenery &
