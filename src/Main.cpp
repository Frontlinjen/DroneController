#include <ros/ros.h>
#include "Pilot.h"


int main(int argc, char **argv){
	ros::init(argc,argv,"pilot");
	Pilot p;
	p.mainLoop();
}