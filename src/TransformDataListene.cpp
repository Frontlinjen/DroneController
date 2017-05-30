#include "NavadataListen.h"
#include "std_msgs/String.h"

tf::TransformListener listener;

void tfCallBack(const std_msgs::String::ConstPtr& msg){
	ROS_INFO("Current position is: %s", msg->data;

}

CurrentPos::CurrentPos() : loop_rate(10){
	sub = n.subscribe("/ardrone/predictedPose", 1000, tfCallBack)
}



