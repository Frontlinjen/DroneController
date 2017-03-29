#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Empty.h"
#include "std_srvs/Empty.h"
#include "Pilot.h"
#include <sstream>
#include <string>

int main(int argc, char **argv){

		ros::init(argc,argv,"pilot");

		Pilot p;

		if(ros::ok()){
			p.prepare();
			p.flattrim();
			p.autoInit();
			p.goTo(0,1,0,0);
			p.land();
		}
	}