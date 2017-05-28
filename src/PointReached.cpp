#include "PointReached.h"
#include "std_msgs/String.h"

void chatterCallBack(const std_msgs::String::ConstPtr& msg){
	ROS_INFO("PointReached: I heard: %s", msg->data.c_str());
	if(listening){
		reached = true;
		listening = false;
	}
}

PointReached::PointReached() : loop_rate(10){
	sub = n.subscribe("", 1000, chatterCallBack)
}

void PointReached::listenForPointReached(){
	reached = false;
	listening = true;
}

bool isPointReached(){
	return reached;
}