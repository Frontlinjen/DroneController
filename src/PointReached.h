#include "ros/ros.h"


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
};