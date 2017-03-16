#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
#include <string>

ros::Publisher takeoffPub;
ros::Publisher landPub;
ros::Publisher comPub;
ros::Subscriber takeoffSub;
ros::Subscriber landSub;
ros::Subscriber comSub;

void takeoffCallback(const std_msgs::String::ConstPtr& msg){
	ROS_INFO("takeoff: I heard: %s", msg->data.c_str());
}

void landCallback(const std_msgs::String::ConstPtr& msg){
	ROS_INFO("land: I heard: %s", msg->data.c_str());
}

void comCallback(const std_msgs::String::ConstPtr& msg){
	ROS_INFO("com: I heard: %s", msg->data.c_str());
}

std_msgs::String command(std::string command){
	std_msgs::String st_cmd;
	st_cmd.data = command;
	return st_cmd;
}

void autoInit(){
	comPub.publish(command("c autoInit 500 800 4000 0.5"));
}

void land(){
	landPub.publish(command("c land"));
}

void goTo(float x, float y, float z, float yaw){
	std::stringstream com;
	com << "c goto " << x << " " << y << " " << z << " " << yaw;
	comPub.publish(command(com.str()));
}

int main(int argc, char **argv){

	ros::init(argc,argv,"pilot");
	ros::NodeHandle n;
	takeoffPub = n.advertise<std_msgs::String>("ardrone/takeoff", 100);
	landPub = n.advertise<std_msgs::String>("ardrone/land", 100);
	comPub  = n.advertise<std_msgs::String>("tum_ardrone/com", 100);
	takeoffSub = n.subscribe("ardrone/takeoff", 100, takeoffCallback);
	landSub = n.subscribe("ardrone/land", 100, landCallback);
	comSub  = n.subscribe("tum_ardrone/com", 100, comCallback);
	ros::Rate loop_rate(10);

	if(ros::ok()){
		autoInit();
		ros::spinOnce();
		loop_rate.sleep();
		goTo(0,1,0,0);
		ros::spinOnce();
		loop_rate.sleep();
		land();
	}
	ros::spin();
}