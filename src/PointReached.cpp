#include "PointReached.h"
#include "std_msgs/String.h"

void PointReached::chatterCallBack(const std_msgs::String::ConstPtr& msg){
	if(listening && msg->data.find("target reached initially") != std::string::npos){
		ROS_INFO("Point reached");
		reached = true;
		listening = false;
	}
}

PointReached::PointReached() : loop_rate(200){
	sub = n.subscribe("/tum_ardrone/com", 1000, &PointReached::chatterCallBack, this);
}

void PointReached::listenForPointReached(){
	ROS_INFO("Listening for point reached");
	reached = false;
	listening = true;
}

bool PointReached::isPointReached(){
	ros::spinOnce();
	return reached;
}

bool PointReached::isListening(){
	ros::spinOnce();
	return listening;
}