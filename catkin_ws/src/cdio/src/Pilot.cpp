#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Empty.h"
#include "std_srvs/Empty.h"
#include <sstream>
#include <string>

ros::Publisher takeoffPub;
ros::Publisher landPub;
ros::Publisher comPub;
ros::Subscriber takeoffSub;
ros::Subscriber landSub;
ros::Subscriber comSub;
ros::ServiceClient flattrimClient;


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
	ROS_INFO("Sent autoInit");
	//ros::spinOnce();
	//loop_rate.sleep();
}

void land(){
	comPub.publish(command("c land"));
	ROS_INFO("Sent land");
	//ros::spinOnce();
	//loop_rate.sleep();
}

void takeoff(){
	comPub.publish(command("c takeoff"));
	ROS_INFO("Sent takeoff");
	//ros::spinOnce();
	//loop_rate.sleep();
}

void flattrim(){
	comPub.publish(command("c flattrim"));
	ROS_INFO("Sent flattrim");
	//ros::spinOnce();
	//loop_rate.sleep();
}

void reset(){
	comPub.publish(command("c reset"));
	ROS_INFO("Sent reset");
	//ros::spinOnce();
	//loop_rate.sleep();
}

void goTo(float x, float y, float z, float yaw){
	std::stringstream com;
	com << "c goto " << x << " " << y << " " << z << " " << yaw;
	comPub.publish(command(com.str()));
	ROS_INFO("Sent goto");
	//ros::spinOnce();
	//loop_rate.sleep();
}

void prepare(){
	ROS_INFO("Preparing...");
	comPub.publish(command("c start"));
	//ros::spinOnce();
	//loop_rate.sleep();
	//TODO Calibrate
	//ros::spinOnce();
	//loop_rate.sleep();
	//TODO Flattrim
	//ros::spinOnce();
	//loop_rate.sleep();
	ROS_INFO("Done.");
}

int main(int argc, char **argv){

	ros::init(argc,argv,"pilot");
	ros::NodeHandle n;
	ros::Rate loop_rate(10);
	comPub = n.advertise<std_msgs::String>(n.resolveName("tum_ardrone/com"), 50);
	//flattrimClient = n.serviceClient<std_srvs::Empty>(n.resolveName("ardrone/flattrim"),1);
	//ros::spinOnce();
	//loop_rate.sleep();	
	ros::Duration(2).sleep();
	//ROS_INFO(n.resolveName("tum_ardrone/com"));
	//takeoffSub = n.subscribe("ardrone/takeoff", 1000, takeoffCallback);
	//landSub = n.subscribe("ardrone/land", 1000, landCallback);
	//comSub = n.subscribe("/tum_ardrone/com", 1000, comCallback);

	if(ros::ok()){
		//prepare();
		comPub.publish(command("c start"));
		ros::spinOnce();
		loop_rate.sleep();
		std_srvs::Empty flat;
		flattrimClient.call(flat);
		ros::spinOnce();
		loop_rate.sleep();
		autoInit();
		ros::spinOnce();
		loop_rate.sleep();
		goTo(0,1,0,0);
		ros::spinOnce();
		loop_rate.sleep();
		land();
		ros::spinOnce();
		loop_rate.sleep();

	}
	//ros::spin();
}
