#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Empty.h"
#include "std_srvs/Empty.h"
#include <sstream>
#include <string>

class Pilot{

	private:
		ros::Publisher comPub;
		ros::ServiceClient flattrimClient;
		ros::NodeHandle n;
		ros::Rate loop_rate;

	public:
		Pilot();
		void comCallback(const std_msgs::String::ConstPtr& msg);
		std_msgs::String command(std::string command);
		void autoInit();
		void land();
		void takeoff();
		void flattrim();
		void reset();
		void goTo(float x, float y, float z, float yaw);
		void moveBy(float x, float y, float z, float yaw);
		void prepare();
};