#include "ros/ros.h"
#include "std_msgs/String.h"
#include "Ring.h"
#include <string>
#include <sstream>
#include <vector>
#include "Ring.cpp"

void msgHandle(std_msgs::String::ConstPtr& msg){
	std::getline(std::cin, msg);
	std::stringstream stream(msg);
	int ringnumber;
	Vector origo, direction;
	stream >> origo->x >> origo->y >> origo->z >> direction->x >> direction->y >> direction->z >> ringnumber;

	Ring(origo, direction, ringnumber);
}


void opencvCallback(const std_msgs::String::ConstPtr& msg){
	ROS_INFO("I heard: [%s]", msg->data.c_str());
	msgHandle(msg);
}


int main(int argc, char **argv){

	ros::init(argc, argv, "listener");

	ros::NodeHandle n;

	ros::Subscriber sub = n.subscribe("opencv", 50, opencvCallback);

	ros:spin();

	return 0;
}
