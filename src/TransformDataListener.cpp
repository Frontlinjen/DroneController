#include "TransformDataListener.h"
#include "std_msgs/String.h"


void TransformDataListener::tfCallBack(tum_ardrone::filter_state msg){
	//ROS_INFO("Current position is: %s", msg->data);

	setPosition(Vector(msg.x, msg.y, msg.z));
	setDirection(Vector(msg.dx, msg.dy, msg.dz));
	setYaw(msg.yaw);
}

Vector TransformDataListener::getPosition(){
	return position;
}

void TransformDataListener::setPosition(Vector v){
	position = v;
}

Vector TransformDataListener::getDirection(){
	return direction;
}

void TransformDataListener::setDirection(Vector v){
	direction = v;
}

float TransformDataListener::getYaw(){
	return yaw;
}

void TransformDataListener::setYaw(float y){
	yaw = y;
}

void TransformDataListener::spinner(){
	ros::spin();
}

TransformDataListener::TransformDataListener(){
	sub = n.subscribe("/ardrone/predictedPose", 1000, &TransformDataListener::tfCallBack, this);
	std::thread spinThread(spinner);
	spinThread.detach();
}

