#include "TransformDataListener.h"
#include "std_msgs/String.h"

tf::TransformListener listener;

void tfCallBack(const std_msgs::String::ConstPtr& msg){
	ROS_INFO("Current position is: %s", msg->data);

}

Vector TransformDataListener::getPosition(){
	return currentPosition;
}

TransformDataListener::TransformDataListener(){
	sub = n.subscribe("/ardrone/predictedPose", 1000, &TransformDataListener::tfCallBack, this);
}



