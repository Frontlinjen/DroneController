#include "PointReached.h"
#include "std_msgs/String.h"

void chatterCallBack(const std_msgs::String::ConstPtr& msg){
	ROS_INFO("PointReached: I heard: %s", msg->data.c_str());
}

PointReached::PointReached() : loop_rate(10){
	sub = n.subscribe("", 1000, chatterCallBack)
}

void PointReached::listenForPointReached(){
	reached = false;

}

bool isPointReached(){
	return reached;
}