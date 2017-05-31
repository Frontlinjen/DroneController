#include "TransformDataListener.h"
#include "std_msgs/String.h"


void TransformDataListener::tfCallBack(tum_ardrone::filter_state msg){
	//ROS_INFO("Current position is: %s", msg->data);

	setPosition(Vector(msg.x, msg.y, msg.z));
}

Vector TransformDataListener::getPosition(){
	return position;
}

void TransformDataListener::setPosition(Vector v){
	position = v;
}

TransformDataListener::TransformDataListener(){
	sub = n.subscribe("/ardrone/predictedPose", 1000, &TransformDataListener::tfCallBack, this);
}



