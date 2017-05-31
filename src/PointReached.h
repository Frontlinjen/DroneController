#include "ros/ros.h"
#include "std_msgs/String.h"

class PointReached{
	private:
		bool reached = false;
		bool listening = false;
		ros::NodeHandle n;
		ros::Rate loop_rate;
		ros::Subscriber sub;

	public:
		PointReached();
		void listenForPointReached();
		bool isPointReached();
		void chatterCallBack(const std_msgs::String::ConstPtr& msg);
};