#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Empty.h"
#include "std_srvs/Empty.h"
#include "TransformDataListener.h"
#include <sstream>
#include <string>
#include <iostream>

class Commands{

	private:
		ros::Publisher comPub;
		ros::ServiceClient flattrimClient;
		ros::NodeHandle n;
		ros::Rate loop_rate;
		std_msgs::String command(std::string command);
		TransformDataListener transformDataListener;

	public:
		Commands();
		void comCallback(const std_msgs::String::ConstPtr& msg);
		void autoInit();
		void land();
		void takeoff();
		void flattrim();
		void reset();
		void goTo(float x, float y, float z, float yaw);
		void moveBy(float x, float y, float z, float yaw);
		void setReference();
		void clearCommands();
		void prepare();
		void lookForRings();
};