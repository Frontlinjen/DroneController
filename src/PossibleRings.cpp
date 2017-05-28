#include "PossibleRings.h"
#include "Ring.h"
#include "Vector.h"
#include <vector>

void opencvCallback(const std_msgs::String::ConstPtr& msg){
	ROS_INFO("I heard: [%s]", msg->data.c_str());
	msgHandle(msg);
}

void msgHandle(std_msgs::String::ConstPtr& msg){
	std::getline(std::cin, msg);
	std::stringstream stream(msg);
	Ring r;
	vector<float> fv;
	stream >> f;
	Vector origo, direction;
	if(!stream)
		break;
	while(stream >> f)	
		fv.push_back(f);
		origo.x = fv.at(0);
	Ring(fv.at(0), fv.at(1), fv.at(2), fv.at(3), fv.at(4), fv.at(5), fv.at(6));
}