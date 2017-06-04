#include "PointReached.h"
#include "std_msgs/String.h"

void PointReached::chatterCallBack(const std_msgs::String::ConstPtr& msg){
	if(listening && msg->data.find("target reached initially") != std::string::npos){
		ROS_INFO("PointReached");
		reached = true;
		listening = false;
	}
}

PointReached::PointReached() : loop_rate(200){
	sub = n.subscribe("/tum_ardrone/com", 1000, &PointReached::chatterCallBack, this);
}

void PointReached::listenForPointReached(){
	reached = false;
	listening = true;
}

bool PointReached::isPointReached(){
	return reached;
}

bool PointReached::isListening(){
	return listening;
}