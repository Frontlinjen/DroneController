#include "Ring.h"
#include <string>
#include <sstream>
#include <vector>
#include "Ring.cpp"

void opencvCallback(const std_msgs::String::ConstPtr& msg){
	ROS_INFO("I heard: [%s]", msg->data.c_str());
	msgHandle(msg);
}

void msgHandle(std_msgs::String::ConstPtr& msg){
	std::getline(std::cin, msg);
	std::stringstream stream(msg);
	float f;
	vector<float> fv;
	stream >> f;
	if(!stream)
		break;
	while(stream >> f)
		fv.push_back(f);
	Ring(fv.at(0), fv.at(1), fv.at(2), fv.at(3), fv.at(4), fv.at(5), fv.at(6));
}


int main(int argc, char **argv){

	ros::init(argc, argv, "listener");

	ros::NodeHandle n;

	ros::Subscriber sub = n.subscribe("opencv", 50, opencvCallback);



	ros:spin();

	return 0;
}
