#!/bin/sh

xterm -hold -e roscore &
sleep 2
xterm -hold -e rosrun ardrone_autonomy ardrone_driver _navdata_demo:=0 _looprate:=500 _realtime_navdata:=True &
xterm -hold -e rosrun tum_ardrone drone_stateestimation &
xterm -hold -e rosrun tum_ardrone drone_autopilot &
xterm -hold -e rosrun tum_ardrone drone_gui 
